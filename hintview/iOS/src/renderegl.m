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
//
//  renderegl.m
//  iOSHintView
//
//  Created by Martin Ruckert on 10.10.22.
//

#include <Foundation/Foundation.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <ft2build.h>

// OpenGL ES 2.0 code


#include "basetypes.h"
#include "error.h"
#include FT_FREETYPE_H
#include "hint.h"
#include "hfonts.h"
#include "hrender.h"
#include "rendernative.h"
#define STBI_ONLY_JPEG
#define STBI_ONLY_PNG
#define STBI_ONLY_BMP
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#if 1
static void checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOG("after %s() glError (0x%x)\n", op, error);
    }
}

static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOG("GL %s = %s\n", name, v);
}
#else

#define printGLString(N,S)	(void)0
#define checkGlError(OP)	(void)0
#endif

static GLuint gvPositionHandle;
static GLuint ProgramID, RuleID, ourColorLocation, isImageID;
static unsigned char *last_b=NULL;

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
             "gl_FragColor.a = texColor.a;\n"
             "gl_FragColor.rgb = FGcolor.rgb;\n"
          "}\n"
          "else gl_FragColor = texColor;\n"
        "}\n";

static GLuint loadShader(GLenum shaderType, const char *pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char *buf = (char *) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    NSLog(@"Could not compile shader %d:\n%s\n",
                         shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

static GLuint createProgram(const char *pVertexSource, const char *pFragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        checkGlError("glAttachShader");
        glAttachShader(program, pixelShader);
        checkGlError("glAttachShader");
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char *buf = (char *) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    NSLog(@"Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}



static void mkRuleTexture() { /* the texture used for rules */
#define NO_TEST 1
#if NO_TEST
  GLubyte rule[1][1][1]={{{0xFF}}};
  /* for testing only */
#else /* for testing only */
  GLubyte rule[2][2][3]={{{0}}};
  rule[0][0][0]=0xFF; // red top left
  rule[0][1][0]=rule[0][1][1]=0xFF; // yellow top right
  rule[1][0][2]=0xFF; // blue bottom left
  rule[1][1][1]=0xFF; // green bottom right
#endif

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    checkGlError("glPixelStorei");
    glGenTextures(1, &RuleID);
    glBindTexture(GL_TEXTURE_2D, RuleID);
    checkGlError("glBindTexture RuleID");
#if NO_TEST
  glTexImage2D(GL_TEXTURE_2D, 0,GL_ALPHA, 1, 1 , 0, GL_ALPHA, GL_UNSIGNED_BYTE, rule);
#else
  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, 2, 2 , 0, GL_RGB, GL_UNSIGNED_BYTE, rule);
#endif
    checkGlError("glTeXImage2D Rule");
    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


void nativeInit(void) {
  //  LOG("nativeInit EGL Graphics\n");

  //  printGLString("Version", GL_VERSION);
 //   printGLString("Vendor", GL_VENDOR);
 //   printGLString("Renderer", GL_RENDERER);

    ProgramID = createProgram(VertexShader, FragmentShader);
    if (!ProgramID) {
        NSLog(@"Could not create program.");
        return;
    }
    gvPositionHandle = glGetAttribLocation(ProgramID, "vPosition");
    checkGlError("glGetAttribLocation");
    //LOGI("glGetAttribLocation(\"vPosition\") = %d\n", gvPositionHandle);

    glEnableVertexAttribArray(gvPositionHandle);
    checkGlError("glEnableVertexAttribArray");

    ourColorLocation = glGetUniformLocation(ProgramID, "FGcolor");
    isImageID = glGetUniformLocation(ProgramID, "IsImage");

    //int ourProjectionLocation = glGetUniformLocation(ProgramID, "MVP");
    glUseProgram(ProgramID);

    mkRuleTexture();
    //hint_clear_fonts(true);
#if 0
    GLfloat mv[4];
    glGetFloatv(GL_MAX_VIEWPORT_DIMS,mv);
    LOGI("maxviewport(%f, %f)", mv[0], mv[1]);
    glGetFloatv(GL_VIEWPORT,mv);
    LOGI("viewport(%f, %f)", mv[2], mv[3]);
    SurfaceTexture.
#endif
    //glViewport(0,0,1920,1080); // seems unnecessary mv[2]==1920 and mv[3]==1080

    glEnable(GL_BLEND);
    checkGlError("glEnable BLEND");

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    checkGlError("glBlendFunc");

  //  NSLog(@"nativeInit done\n");
}

static GLfloat curfr=0.0f, curfg=0.0f, curfb=0.0f;
static GLfloat lnkr=0.0f, lnkg=0.0f, lnkb=0.8f;
    
static uint8_t last_style=0;
static void nativeSetColors(GLfloat fr, GLfloat fg, GLfloat fb, GLfloat br, GLfloat bg, GLfloat bb)
/* set foreground and background rgb colors */
{
    glClearColor(br, bg, bb, 1.0f);
    curfr=fr; curfg=fg; curfb=fb;
    glUniform4f(ourColorLocation, fr, fg, fb, 1.0f);
}

void nativeSetDark(int dark) {
 //  NSLog(@"SetDark %d GL Graphics\n", dark);

    if (dark) {
        nativeSetColors(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
        lnkr=0.6f; lnkg=0.6f; lnkb=1.0f;
    } else {
        nativeSetColors(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
        lnkr=0.0f; lnkg=0.0f; lnkb=1.0f;
    }
}

static int cur_h=600, cur_v=800;
static float pt_h=600.0, pt_v=800.0;

void nativeSetSize(int px_h, int px_v, double xdpi, double ydpi)
/* Given the size of the output area px_h,px_v in pixel and the resolution in dpi,
   make sure the projection is set up properly.
 */
{
    int ourProjectionLocation;

    /* convert pixel to point */
    pt_h = px_h * 72.27 / xdpi;
    pt_v = px_v * 72.27 / ydpi;
    /* convert point to scaled point*/
    page_h = round(pt_h * (1 << 16));
    page_v = round(pt_v * (1 << 16));

   // NSLog(@"native SetSize to %f pt x %f pt (%d px x %d px)", pt_h, pt_v, px_h, px_v);

    // GL Coordinates are in points
    ourProjectionLocation = glGetUniformLocation(ProgramID, "MVP");

    GLfloat MVP[4][4]= {{0}};
    MVP[0][0]=2.0/pt_h; // x: scale to -1 to +1
    MVP[1][1]=-2.0/pt_v; // y: scale to 1 to -1
    MVP[2][2]=0.0f; // z: don't care
    MVP[3][0]=-1.0f; // x position: left
    MVP[3][1]=1.0f; // y position: up
    MVP[3][2]=0.0f; // don't care
    MVP[3][3]=1.0f; // w: identity
    glUniformMatrix4fv(ourProjectionLocation, 1, 0, &MVP[0][0]);

    glViewport(0, 0, px_h, px_v);
    cur_h=px_h;
    cur_v=px_v;
}


static void GLtexture(Gcache *g) {
    unsigned GLtex;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    checkGlError("glPixelStorei");
    glGenTextures(1, &GLtex);
    checkGlError("glGenTextures");
    glBindTexture(GL_TEXTURE_2D, GLtex);
    checkGlError("glBindTexture");
    /* the first element in g->bits corresponds to the lower left pixel,
     * the last element in g->bits to the upper right pixel. */
    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_ALPHA,
            g->w,
            g->h,
            0,
            GL_ALPHA,
            GL_UNSIGNED_BYTE,
            g->bits
    );
    checkGlError("glTeXImage2D");

    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    g->GLtexture = GLtex;
    //MESSAGE("Generated GL texture %d",g->GLtexture);
}

void nativeSetPK(struct gcache_s*g)
{GLtexture(g); /* can I free g->bits ? */}

void nativeSetFreeType(struct gcache_s*g)
{GLtexture(g);}


void nativeFreeGlyph(Gcache *g)
/* Free resources associated with g. */
{
    if (g->GLtexture != 0) {
        glDeleteTextures(1, &(g->GLtexture)); // probably not needed
        g->GLtexture = 0;
    }
}

void  nativeGlyph(double x,double dx,double y,double dy,double w,double h,struct gcache_s*g,uint8_t s)
/* Using GL to render a character texture
   Coordinates in points, origin bottom left, x and w right, y and h up
   x,y position
   w,h width and height
   s style bits
  */
{ //LOGI("Rendering texture %i at (%f,%f) sized %fx%f",GLtexture,x/SPf,y/SPf,w/SPf,h/SPf);
    x=x-dx;
    y=y-dy;
    if (g->GLtexture == 0)
        GLtexture(g);

    GLfloat gQuad[] = {(GLfloat) x, (GLfloat) y, 0.0f, 0.0f,
                       (GLfloat) x, (GLfloat) (y + h), 0.0f, 1.0f,
                       (GLfloat) (x + w), (GLfloat) (y + h), 1.0f, 1.0f,
                       (GLfloat) x, (GLfloat) y, 0.0f, 0.0f,
                       (GLfloat) (x + w), (GLfloat) (y + h), 1.0f, 1.0f,
                       (GLfloat) (x + w), (GLfloat) y, 1.0f, 0.0f
    };
    glBindTexture(GL_TEXTURE_2D, g->GLtexture);
    checkGlError("glBindTexture");
    glVertexAttribPointer(gvPositionHandle, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), gQuad);
    checkGlError("glVertexAttribPointer");
    if (s!=last_style)
    { if (s&FOCUS_BIT)
           glUniform4f(ourColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);
      else if (s&MARK_BIT)
            glUniform4f(ourColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
      else if (s&LINK_BIT)
           glUniform4f(ourColorLocation, lnkr, lnkg, lnkb, 1.0f);
      else
           glUniform4f(ourColorLocation, curfr, curfg,curfb, 1.0f);
        last_style=s;
    }
    glDrawArrays(GL_TRIANGLES, 0, 6);
    checkGlError("glDrawArrays");
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
                       (GLfloat) x, (GLfloat) y, 0.0f, 1.0f,
                       (GLfloat) (x + w), (GLfloat) (y - h), 1.0f, 0.0f,
                       (GLfloat) (x + w), (GLfloat) y, 1.0f, 1.0f
    };
    glBindTexture(GL_TEXTURE_2D, RuleID);
    checkGlError("glBindTexture");
    glVertexAttribPointer(gvPositionHandle, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), gQuad);
    checkGlError("glVertexAttribPointer");
#if !NO_TEST
    glUniform1i(isImageID, 1);
#endif
    glDrawArrays(GL_TRIANGLES, 0, 6);
    checkGlError("glDrawArrays");
#if !NO_TEST
    glUniform1i(isImageID, 0);
#endif
}

static GLuint PictureID=0;
void
nativeImage(double x, double y, double w, double h, unsigned char *b, unsigned char *e)
/* new image loading function using stb_image.h as image loader.
 It follows the example of https://learnopengl.com/Getting-started/Textures
 */
{
    static unsigned char *last_b=NULL;
    GLenum format, internal_format;
    int width, height, nrChannels;
    unsigned char *data;
    static unsigned char grey[4]={0,0,0,0x80};
    if (b!=last_b)
    { if (PictureID != 0) {
          glDeleteTextures(1, &PictureID);
          PictureID = 0;
      }
      last_b=b;
      data = stbi_load_from_memory(b, (int) (e - b), &width, &height, &nrChannels, 0);
      if (data == NULL) {
        LOG("Unable to display image\n");
        data=grey; width=height=1; nrChannels=4;
      }
      //LOG("image width=%d, height=%d nrChannels=%d\n", width, height, nrChannels);

         // Give the image to OpenGL
        internal_format = format=GL_RGB;
        if (nrChannels == 4) {
            format = GL_RGBA; internal_format = GL_RGBA;
        } else if (nrChannels == 3) {
            format = GL_RGB;
        } else if (nrChannels == 1) {
            format = GL_ALPHA;
        }
        
        //LOG("image format=%d\n", format);
        
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        checkGlError("glPixelStorei");
 
        glGenTextures(1, &PictureID);
        checkGlError("glGenTextures PictureID");
      
        // "Bind" the newly created texture : all future texture functions will modify this texture
        glBindTexture(GL_TEXTURE_2D, PictureID);
        glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        checkGlError("glTexImage2D");
        if (data!=grey) stbi_image_free(data);

        //glGenerateMipmap(GL_TEXTURE_2D);
        checkGlError("glGenerateMipmap");
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    else
    {  glBindTexture(GL_TEXTURE_2D, PictureID);
       checkGlError("glBindTexture old PictureID");
    }
        GLfloat gQuad[] = {(GLfloat) x, (GLfloat) y, 0.0f, 1.0f,
                           (GLfloat) x, (GLfloat) (y - h), 0.0f, 0.0f,
                           (GLfloat) (x + w), (GLfloat) (y - h), 1.0f, 0.0f,
                           (GLfloat) x, (GLfloat) y, 0.0f, 1.0f,
                           (GLfloat) (x + w), (GLfloat) (y - h), 1.0f, 0.0f,
                           (GLfloat) (x + w), (GLfloat) y, 1.0f, 1.0f
        };
        checkGlError("qQuad");
   //     glBindTexture(GL_TEXTURE_2D, PictureID);
        glVertexAttribPointer(gvPositionHandle, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), gQuad);
        checkGlError("glVertexAttribPointer");
        // make sure that image is always rendered in correct colors
        glUniform1i(isImageID, 1);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        checkGlError("glDrawArrays");
        glUniform1i(isImageID, 0);
      
}

void nativeBlank(void) {
    glClear(GL_COLOR_BUFFER_BIT);
}

/* dummy implementations */
void nativeClear(void) {}
int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits) { return 0; }
int nativePrintEnd(void) { return 0; }
int nativePrint(unsigned char*bits){ return 0; }
void nativeSetGamma(double gamma) {}
