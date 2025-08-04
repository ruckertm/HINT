/* This file is part of HINT
 * Copyright 2017-2021 Martin Ruckert, Hochschule Muenchen, Lothstrasse 64, 80336 Muenchen
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
 * OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Except as contained in this notice, the name of the copyright holders shall
 * not be used in advertising or otherwise to promote the sale, use or other
 * dealings in this Software without prior written authorization from the
 * copyright holders.
 */

// OpenGL ES 2.0 code

#include <Foundation/Foundation.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#include "basetypes.h"
#include "error.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "rendernative.h"
#define STBI_ONLY_JPEG
#define STBI_ONLY_PNG
#define STBI_ONLY_BMP
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#ifdef DEBUG
#define  LOGI(...)  NSLog(@__VA_ARGS__)
#define  LOGE(...)  NSLog(@__VA_ARGS__)

static void checkGlError(const char *op)
{    for (GLint error = glGetError(); error; error = glGetError()) {
        NSLog(@"after %s() glError (0x%x)\n", op, error);
    }
}

static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    NSLog(@"GL %s = %s\n", name, v);
}

#else
#define  LOGI(...)  (void)0
#define  LOGE(...)  (void)0

#define printGLString(N,S) (void)0
#define checkGlError(OP)   (void)0
#endif

#define MAX_INFOLOG 512
static GLuint gvPositionHandle;
static GLuint ProgramID, MatrixID, RuleID, GammaID, FGcolorID, IsImageID, ImageID=0;
static unsigned char *last_b=NULL;
static uint32_t cur_fg=0; /*the current foreground color*/

static const char *VertexShader =
        "#version 100\n"
        "attribute vec4 vPosition;\n"
        "varying vec2 UV;\n"
        "uniform mat4 MVP;\n"
        "void main() {\n"
        "  gl_Position = MVP*vec4(vPosition.x,vPosition.y,1.0,1.0);\n"
        "  UV=vec2(vPosition.z,vPosition.w);\n"
        "}\n";

static const char *FragmentShader =
        "precision mediump float;\n"
        "varying vec2 UV;\n"
        "uniform sampler2D theTexture;\n"
        "uniform vec4 FGcolor;\n"
        "uniform float Gamma;\n"
        "uniform int IsImage;\n"
        "void main()\n"
        "{ vec4 texColor = texture2D(theTexture, UV);\n"
          "if(IsImage==0) {\n"
             "gl_FragColor.a = pow(texColor.a*FGcolor.a,Gamma);\n"
             "gl_FragColor.r = FGcolor.r;\n"
             "gl_FragColor.g = FGcolor.g;\n"
             "gl_FragColor.b = FGcolor.b;\n"
          "}\n"
          "else gl_FragColor = texColor;\n"
        "}\n";

static GLuint loadShader(GLenum shaderType, const char *shaderSource)
{ GLuint shaderID;
  GLint result = GL_FALSE;

  /* Compile and check vertex shader */
  shaderID = glCreateShader(shaderType);
  if (shaderID) {
    glShaderSource(shaderID, 1, &shaderSource, NULL);
    glCompileShader(shaderID);
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    if (!result)
    { char InfoLog[MAX_INFOLOG];
      glGetShaderInfoLog(shaderID, MAX_INFOLOG, NULL, InfoLog);
      glDeleteShader(shaderID);
      shaderID = 0;
      LOGE("Error compiling shader (%d): %s\n", shaderType, InfoLog);
    }
  }
  return shaderID;
}

static void createProgram(void)
{ GLuint vertexID=loadShader(GL_VERTEX_SHADER,VertexShader);
  GLuint fragmentID=loadShader(GL_FRAGMENT_SHADER,FragmentShader);
  GLint result=GL_FALSE;

  if (!vertexID  || !fragmentID) return;

  /* Create, linking, and check the program */
  ProgramID = glCreateProgram();
  if (ProgramID) {
    glAttachShader(ProgramID, vertexID);
    checkGlError("glAttachShader");
    glAttachShader(ProgramID, fragmentID);
    checkGlError("glAttachShader");
    glLinkProgram(ProgramID);
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &result);
    if (!result)
    { char InfoLog[MAX_INFOLOG];
      glGetProgramInfoLog(ProgramID, MAX_INFOLOG, NULL, InfoLog);
      glDeleteProgram(ProgramID);
      ProgramID = 0;
      QUIT("Error linking shader program: %s\n", InfoLog);
    }
    glDetachShader(ProgramID, vertexID);
    glDetachShader(ProgramID, fragmentID);
  }
  glDeleteShader(vertexID);
  glDeleteShader(fragmentID);
  //LOG("createProgram Done\n");
}

/* the 4x4 Model-View-Projection Matrix */
static GLfloat MVP[4][4] = {
  {0.5, 0.0, 0.0, 0.0 }, // x scale
  {0.0, 0.5, 0.0, 0.0 }, // y scale
  {0.0, 0.0, 0.0, 0.0 }, // z scale
  {0.0, 0.0, 0.0, 1.0 }}; // translation x, y, z

static void mkRuleTexture() { /* the texture used for rules */
  GLubyte rule[1][1][1]={{{0xFF}}};

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  checkGlError("glPixelStorei");

  glGenTextures(1, &RuleID);
  glBindTexture(GL_TEXTURE_2D, RuleID);
  checkGlError("glBindTexture RuleID");
  glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 1, 1, 0, GL_ALPHA, GL_UNSIGNED_BYTE, rule);
  /* Set texture options */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

extern void nativeInit(void)
{ LOGI("nativeInit GL Graphics\n");

  printGLString("Version", GL_VERSION);
  printGLString("Vendor", GL_VENDOR);
  printGLString("Renderer", GL_RENDERER);
 
  createProgram();
  if (!ProgramID) {
        LOGE("Could not create program.");
        return;
  }
  gvPositionHandle = glGetAttribLocation(ProgramID, "vPosition");
  checkGlError("glGetAttribLocation");

  glEnableVertexAttribArray(gvPositionHandle);
  checkGlError("glEnableVertexAttribArray");

  MatrixID = glGetUniformLocation(ProgramID, "MVP");
  FGcolorID = glGetUniformLocation(ProgramID, "FGcolor");
  GammaID  = glGetUniformLocation(ProgramID, "Gamma");
  IsImageID = glGetUniformLocation(ProgramID, "IsImage");
  checkGlError("get IDs"); 

  glUseProgram(ProgramID);

  glUniform1f(GammaID, 1.0f/2.2f);
  glUniform1i(IsImageID, 0);
  glUniform4f(FGcolorID, 0.0, 0.0, 0.0, 1.0); // black as default foreground
  cur_fg=0x000000FF; /* possibly better: use nativeSetForeground */
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // white as default background

  /* Make the alpha channel work */
  glEnable(GL_BLEND);
  checkGlError("glEnable BLEND");
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  checkGlError("glBlendFunc");
#if 0 /* not in EGL */
  glEnable(GL_MULTISAMPLE);
  checkGlError("GL_MULTISAMPLE");
  glEnable(GL_FRAMEBUFFER_SRGB);
  checkGlError("GL_FRAMEBUFFER_SRGB");
#endif
  mkRuleTexture();
  ImageID=0;
  last_b=NULL;
  //LOG("nativeInit done\n");
}


#if 0
void nativeClear(void)
{ glDeleteBuffers(1, &xybuffer);
  glDeleteBuffers(1, &uvbuffer);
  glDeleteProgram(ProgramID);
  glDeleteTextures(1, &RuleID);
  if (ImageID != 0) {
        glDeleteTextures(1, &ImageID);
        ImageID = 0; last_b=NULL;
  }
}
#else
void nativeClear(void)
{ }
#endif

void nativeSetGamma(double gamma)
{ glUniform1f(GammaID, 1.0/gamma);
  checkGlError("glsetgamma");
}



void nativeSetForeground(uint32_t fg)
/* set foreground rgba colors */
{ if (fg!=cur_fg)
  { uint8_t r,g,b,a;
    cur_fg=fg;
    a=fg&0xFF;fg=fg>>8;
    b=fg&0xFF;fg=fg>>8;
    g=fg&0xFF;fg=fg>>8;
    r=fg&0xFF;
    glUniform4f(FGcolorID, r/255.0f,g/255.0f,b/255.0f,a/255.0f);
  }
}


void nativeBackground(double x, double y, double w, double h, uint32_t bg)
{ uint32_t fg=cur_fg;
  nativeSetForeground(bg);
  nativeRule(x,y,w,h);
  nativeSetForeground(fg);
}

void nativeBlank(uint32_t bg)
{ uint8_t r,g,b,a;
  a=bg&0xFF;bg=bg>>8;
  b=bg&0xFF;bg=bg>>8;
  g=bg&0xFF;bg=bg>>8;
  r=bg&0xFF;
  glClearColor(	r/255.0f,g/255.0f,b/255.0f,a/255.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void nativeSetSize(int px_h, int px_v, double pt_h, double pt_v)
{
  MVP[0][0]=2.0/pt_h; // x: scale to -1 to +1
  MVP[1][1]=-2.0/pt_v; // y: scale to 1 to -1
  //MVP[2][2]=0.0f; // z: don't care
  MVP[3][0]=-1.0f; // x position: left
  MVP[3][1]=1.0f; // y position: up
  //MVP[3][2]=-1.0f; // don't care
  //MVP[3][3]=1.0f; // w: identity, already there
  glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
  glViewport(0, 0, px_h, px_v);
}

void nativeRule(double x, double y, double w, double h)
/* Using GL to render a rule (a black rectangle)
   Coordinates in points, origin bottom left, x and w right, y and h up
   x,y position
   w,h width and height
  */
{ //LOGI("Rendering rule at (%f,%f) sized %fx%f",x/SPf,y/SPf,w/SPf,h/SPf);

  GLfloat gQuad[] = {(GLfloat) x, (GLfloat) y, 0.0f, 1.0f,
                       (GLfloat) x, (GLfloat) (y - h), 0.0f, 0.0f,
                       (GLfloat) (x + w), (GLfloat) (y - h), 1.0f, 0.0f,
                       (GLfloat) (x +w), (GLfloat) y, 1.0f, 1.0f,
                       (GLfloat) x, (GLfloat) y, 0.0f, 1.0f,
                       (GLfloat) (x + w), (GLfloat) (y - h), 1.0f, 0.0f
    };
    glBindTexture(GL_TEXTURE_2D, RuleID);
    checkGlError("glBindTexture RuleID");
    glVertexAttribPointer(gvPositionHandle, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), gQuad);
    checkGlError("glVertexAttribPointer");
    glDrawArrays(GL_TRIANGLES, 0, 2*3);
    checkGlError("glDrawArrays");
}

void nativeImage(double x, double y, double w, double h, unsigned char *b, unsigned char *e)
/* render the image found between *b and *e at x,y with size w,h.
   x, y, w, h are given in point
*/
{ GLenum format, internal_format;
  int width, height, nrChannels;

  if (b!=last_b||ImageID==0)
  { unsigned char *data;
    static unsigned char grey[4]={0x80,0x80,0x80,0x80};
    if (ImageID != 0) {
        glDeleteTextures(1, &ImageID);
        ImageID = 0;
    }
    last_b=b;
    data = stbi_load_from_memory(b, (int) (e - b), &width, &height, &nrChannels, 4 );
      /* Possibly use 4 instead of 0 above for the number of desired chanels
        and set format=internal_format=GL_RGBA
      */
    if (data == NULL)
    { LOG("Unable to display image\n");
      data=grey; width=height=1; nrChannels=4;
    }
    LOGI("image width=%d, height=%d nrChannels=%d\n", width, height, nrChannels);
    internal_format = GL_RGBA;
    format = GL_RGBA;
#if 0
    if (nrChannels == 4)
        internal_format = format = GL_RGBA;
    else if (nrChannels == 3)
        internal_format = format = GL_RGB;
    else if (nrChannels == 2) /* I need test cases for this */
        format = GL_LUMINANCE_ALPHA;
    else if (nrChannels == 1)
        format = GL_ALPHA;
#endif
    LOGI("image format=%d\n", format);
 
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    checkGlError("glPixelStorei");
    glGenTextures(1, &ImageID);

    glBindTexture(GL_TEXTURE_2D, ImageID);
    checkGlError("glBindTexture ImageID");

    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0,
                 format, GL_UNSIGNED_BYTE, data);
//  if (glGetError()!= GL_NO_ERROR)
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
//                 format, GL_UNSIGNED_BYTE, data);
    checkGlError("glTexImage2D(image)");
    if (data!=grey) { stbi_image_free(data); data=NULL; }
    glGenerateMipmap(GL_TEXTURE_2D);
    checkGlError("glGenerateMipmap(image)");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  }
  else
  {  glBindTexture(GL_TEXTURE_2D, ImageID);
     checkGlError("glBindTexture old ImageID");
  }

  GLfloat gQuad[] = {(GLfloat) x, (GLfloat) y, 0.0f, 1.0f,
                     (GLfloat) x, (GLfloat) (y - h), 0.0f, 0.0f,
                     (GLfloat) (x + w), (GLfloat) (y - h), 1.0f, 0.0f,
                     (GLfloat) (x +w), (GLfloat) y, 1.0f, 1.0f,
                     (GLfloat) x, (GLfloat) y, 0.0f, 1.0f,
                     (GLfloat) (x + w), (GLfloat) (y - h), 1.0f, 0.0f
                    };
  glVertexAttribPointer(gvPositionHandle, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), gQuad);
  checkGlError("glVertexAttribPointer");

  glUniform1i(IsImageID, 1);
  glDrawArrays(GL_TRIANGLES, 0, 2*3);
  glUniform1i(IsImageID, 0);
}

static const int to_nearest=1;

unsigned int nativeTexture(unsigned char *bits, int w, int h) {
    unsigned int textureID;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    checkGlError("glPixelStorei");
    glGenTextures(1, &textureID);
    checkGlError("glGenTextures");
    glBindTexture(GL_TEXTURE_2D, textureID);
    checkGlError("glBindTexture textureID");
    /* the first element in bits corresponds to the lower left pixel,
     * the last element in bits to the upper right pixel. */
    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_ALPHA,
            w,
            h,
            0,
            GL_ALPHA,
            GL_UNSIGNED_BYTE,
            bits
    );
    checkGlError("glTeXImage2D Glyph");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    if (to_nearest) 
    { glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    else
    { glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    //MESSAGE("Generated GL texture %d",textureID);
    return textureID;
}

unsigned int nativeFreeTexture(unsigned int t)
{ if (t != 0) {
    glDeleteTextures(1, &t); // probably not needed
  }
  return 0;
}


void nativeGlyph(double x, double y, double w, double h, unsigned int t)
/* display texture t at position x,y in size w, h.
   x, y, w, h are given in point */
{  
  GLfloat gQuad[] = {(GLfloat) x, (GLfloat) y, 0.0f, 1.0f,
                     (GLfloat) x, (GLfloat) (y - h), 0.0f, 0.0f,
                     (GLfloat) (x + w), (GLfloat) (y - h), 1.0f, 0.0f,
                     (GLfloat) (x +w), (GLfloat) y, 1.0f, 1.0f,
                     (GLfloat) x, (GLfloat) y, 0.0f, 1.0f,
                     (GLfloat) (x + w), (GLfloat) (y - h), 1.0f, 0.0f
  };
  glBindTexture(GL_TEXTURE_2D, t);
  checkGlError("glBindTexture t");
  glVertexAttribPointer(gvPositionHandle, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), gQuad);
  checkGlError("glVertexAttribPointer");
  glDrawArrays(GL_TRIANGLES, 0, 2*3);
  //checkGlError("glDrawArrays");
}


/* no printing support so far, just placeholders */

int nativePrintStart(int w, int h, int bpr, int bpp, unsigned char *bits)
{ return 0;
}

int nativePrint(unsigned char *bits)
{ return 0;
}

int nativePrintEnd(void)
{ return 0;
}
