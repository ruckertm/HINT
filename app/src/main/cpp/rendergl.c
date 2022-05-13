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

#include <jni.h>
#include <android/log.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "basetypes.h"
#include "error.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "hint.h"
#include "hfonts.h"
#include "hrender.h"
#include "rendernative.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"




#ifdef DEBUG
#define  LOG_TAG    "glrender"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

static void checkGlError(const char *op)
{ GLint error;
  while( (error= glGetError())!= GL_NO_ERROR)
	  LOGE("OGL Error after %s: 0x%x\n", op, error);
}
#else
#define  LOG_TAG    "glrender"
#define  LOGI(...)  (void)0
#define  LOGE(...)  (void)0

#define printGLString(N,S)	(void)0
#define checkGlError(OP)	(void)0
#endif

static GLuint gvPositionHandle;
static GLuint ProgramID, RuleID, GammaID, FGcolorID, IsImageID;

static const char *VertexShader =
        "#version 100\n"
        "attribute vec4 vPosition;\n"
        "varying vec2 TexCoord;\n"
        "uniform mat4 projection;\n"
        "void main() {\n"
        "  gl_Position = projection*vec4(vPosition.x,vPosition.y,1.0,1.0);\n"
        "  TexCoord=vec2(vPosition.z,vPosition.w);\n"
        "}\n";

static const char *FragmentShader =
        "precision mediump float;\n"
        "varying vec2 TexCoord;\n"
        "uniform sampler2D theTexture;\n"
        "uniform vec3 FGcolor;\n"
        "uniform float Gamma;\n"
        "uniform int isImage;\n"
        "void main() {\n"
        "  if(isImage==0) { \n"
        "     gl_FragColor.a = pow(texture2D(theTexture,TexCoord).a,Gamma);\n"
        "     gl_FragColor.rgb = FGcolor;\n"
        "  } else {\n"
        "     gl_FragColor = vec4(texture2D(theTexture,TexCoord));\n"
        "  } \n"
        "}\n";

static GLuint loadShader(GLenum shaderType, const char *pSource) {
    GLuint shaderID;
    GLint result = 0;
    shaderID = glCreateShader(shaderType);
    if (shaderID) {
        glShaderSource(shaderID, 1, &pSource, NULL);
        glCompileShader(shaderID);
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
        if (!result) {
            GLint infoLen = 0;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char *buf = (char *) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shaderID, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n",
                         shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shaderID);
                shaderID = 0;
            }
        }
    }
    return shaderID;
}

static void createProgram(void)
{ GLuint vertexID = loadShader(GL_VERTEX_SHADER, VertexShader);
  GLuint fragmentID = loadShader(GL_FRAGMENT_SHADER, FragmentShader);
  GLint result = GL_FALSE;

    if (!vertexID || !fragmentID) return;

    ProgramID = glCreateProgram();
    if (ProgramID) {
        glAttachShader(ProgramID, vertexID);
        checkGlError("glAttachShader");
        glAttachShader(ProgramID, fragmentID);
        checkGlError("glAttachShader");
        glLinkProgram(ProgramID);
        glGetProgramiv(ProgramID, GL_LINK_STATUS, &result);
        if (!result) {
            GLint bufLength = 0;
            glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char *buf = (char *) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(ProgramID, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(ProgramID);
            ProgramID = 0;
        }
        glDetachShader(ProgramID, vertexID);
        glDetachShader(ProgramID, fragmentID);
    }
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
}



static void mkRuleTexture() { /* the texture used for rules */
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &RuleID);
    glBindTexture(GL_TEXTURE_2D, RuleID);
    uint8_t buffer[1];
    buffer[0] = 0xFF;
    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_ALPHA,
            1,
            1,
            0,
            GL_ALPHA,
            GL_UNSIGNED_BYTE,
            buffer
    );
    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


extern void nativeInit(void) {
    LOGI("nativeInit GL Graphics\n");

    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    createProgram();
    if (!ProgramID) {
        LOGE("Could not create program.");
        return;
    }
    gvPositionHandle = glGetAttribLocation(ProgramID, "vPosition");
    checkGlError("glGetAttribLocation");

    glEnableVertexAttribArray(gvPositionHandle);
    checkGlError("glEnableVertexAttribArray");

    FGcolorID = glGetUniformLocation(ProgramID, "FGcolor");
    GammaID  = glGetUniformLocation(ProgramID, "Gamma");
    IsImageID = glGetUniformLocation(ProgramID, "isImage");

    //int ourProjectionLocation = glGetUniformLocation(ProgramID, "projection");
    glUseProgram(ProgramID);

    glUniform1f(GammaID, 1.0f/2.2f);
    glUniform1i(IsImageID, 0);
    glUniform3f(FGcolorID, 0.0, 0.0, 0.0); // black as default foreground
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // white as default background


    glEnable(GL_BLEND);
    checkGlError("glEnable BLEND");
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    checkGlError("glBlendFunc");
#if 0
    // not in EGL
    glEnable(GL_MULTISAMPLE);
    checkGlError("GL_MULTISAMPLE");
    glEnable(GL_FRAMEBUFFER_SRGB);
    checkGlError("GL_FRAMEBUFFER_SRGB");
#endif
    hint_clear_fonts(true);
    mkRuleTexture();
    LOGI("nativeInit done\n");
}

// Unused ?
#if 0
void nativeClear(void)
{ glDeleteBuffers(1, &xybuffer);
    glDeleteBuffers(1, &uvbuffer);
    glDeleteProgram(ProgramID);
    glDeleteTextures(1, &RuleID);
    if (ImageID != 0) {
        glDeleteTextures(1, &ImageID);
        ImageID = 0;
    }
}
#endif

void nativeBlank(void) {
    glClear(GL_COLOR_BUFFER_BIT);
}

void nativeSetGamma(double gamma)
{ glUniform1f(GammaID, 1.0/gamma);
    checkGlError("glsetgamma");
}


static GLfloat curfr=0.0f, curfg=0.0f, curfb=0.0f;
static uint8_t last_style=0;
static void nativeSetColors(GLfloat fr, GLfloat fg, GLfloat fb, GLfloat br, GLfloat bg, GLfloat bb)
/* set foreground and background rgb colors */
{
    glClearColor(br, bg, bb, 1.0f);
    curfr=fr; curfg=fg; curfb=fb;
    glUniform3f(FGcolorID, fr, fg, fb);
    last_style=0;
}

static int dark_mode;

extern void nativeSetDark(int dark) {
    LOGI("SetDark %d GL Graphics\n", dark);

    if (dark) {
        nativeSetColors(1.0f, 1.0f, 0.95f, 0.0f, 0.0f, 0.05f);
    } else {
        nativeSetColors(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    }
}

static int cur_h=600, cur_v=800;
static float pt_h=600.0, pt_v=800.0;

extern void nativeSetSize(int px_h, int px_v, double xdpi, double ydpi)
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

    LOGI("native SetSize to %f pt x %f pt (%d px x %d px)", pt_h, pt_v, px_h, px_v);

    // GL Coordinates are in points
    ourProjectionLocation = glGetUniformLocation(ProgramID, "projection");
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
extern void  nativeGlyph(double x,double dx,double y,double dy,double w,double h,struct gcache_s*g,uint8_t s)
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
            glUniform3f(FGcolorID, 0.0f, 1.0f, 0.0f);
        else if (s&MARK_BIT)
            glUniform3f(FGcolorID, 1.0f, 0.0f, 0.0f);
        else if (s&LINK_BIT)
            glUniform3f(FGcolorID, 0.0f, 0.0f, 1.0f);
        else
           glUniform3f(FGcolorID, curfr, curfg,curfb);
        last_style=s;
    }
    glDrawArrays(GL_TRIANGLES, 0, 6);
    checkGlError("glDrawArrays");
}


extern void nativeRule(double x, double y, double w, double h)
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
    glDrawArrays(GL_TRIANGLES, 0, 6);
    checkGlError("glDrawArrays");
}


extern void
nativeImage(double x, double y, double w, double h, unsigned char *b, unsigned char *e)
/* new image loading function using stb_image.h as image loader.
 It follows the example of https://learnopengl.com/Getting-started/Textures
 */
{
    int width, height, nrChannels;
    unsigned char *data = stbi_load_from_memory(b, (int) (e - b), &width, &height, &nrChannels, 0);
    if (data) {
        LOGI("image width=%d, height=%d nrChannels=%d\n", width, height, nrChannels);

        GLuint textureID;
        glGenTextures(1, &textureID);
        // "Bind" the newly created texture : all future texture functions will modify this texture
        glBindTexture(GL_TEXTURE_2D, textureID);
        // Give the image to OpenGL
        GLenum format = GL_RGB;
        if (nrChannels == 4) {
            format = GL_RGBA;
        } else if (nrChannels == 3) {
            format = GL_RGB;
        } else if (nrChannels == 1) {
            format = GL_ALPHA;
        }
        LOGI("image format=%d\n", format);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        checkGlError("glTexImage2D");
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        GLfloat gQuad[] = {(GLfloat) x, (GLfloat) y, 0.0f, 1.0f,
                           (GLfloat) x, (GLfloat) (y - h), 0.0f, 0.0f,
                           (GLfloat) (x + w), (GLfloat) (y - h), 1.0f, 0.0f,
                           (GLfloat) x, (GLfloat) y, 0.0f, 1.0f,
                           (GLfloat) (x + w), (GLfloat) (y - h), 1.0f, 0.0f,
                           (GLfloat) (x + w), (GLfloat) y, 1.0f, 1.0f
        };

        glVertexAttribPointer(gvPositionHandle, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), gQuad);
        checkGlError("glVertexAttribPointer");
        // make sure that image is always rendered in correct colors
        glUniform1i(IsImageID, 1);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        checkGlError("glDrawArrays");
        glUniform1i(IsImageID, 0);
        stbi_image_free(data);
    } else {
        LOGI("Can not read image %p", b);
    }
}

