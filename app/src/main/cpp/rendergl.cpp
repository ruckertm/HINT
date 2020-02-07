
// OpenGL ES 2.0 code

#include <jni.h>
#include <android/log.h>


#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtc/matrix_transform.hpp"

extern "C" {
#include "stb_truetype.h"
#include "hfonts.h"
#include "hrender.h"
#include "rendernative.h"
#include "stb_image.h"
};

#define min(X, Y) ((X)<(Y)?(X):(Y))
#define DARK_MODE 1
#define LIGHT_MODE 0

#define  LOG_TAG    "glrender"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

static void checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGE("after %s() glError (0x%x)\n", op, error);
    }
}

static GLuint gProgram;
static GLuint gvPositionHandle;
static int mode;


auto gVertexShader =
        "#version 100\n"
        "attribute vec4 vPosition;\n"
        "varying vec2 TexCoord;\n"
        "uniform mat4 projection;\n"
        "void main() {\n"
        "  gl_Position = projection*vec4(vPosition.x,vPosition.y,1.0,1.0);\n"
        "  TexCoord=vec2(vPosition.z,vPosition.w);\n"
        "}\n";

auto gFragmentShader =
        "precision mediump float;\n"
        "varying vec2 TexCoord;\n"
        "uniform sampler2D ourTexture;\n"
        "uniform vec4 ourColor;\n"
        "uniform int ourMode;\n"
        "void main() {\n"
        "  if(ourMode==1) { \n"
        "     vec3 invColor = (vec3(1.0)-texture2D(ourTexture,TexCoord).xyz);"
        "     gl_FragColor = vec4(invColor.xyz, texture2D(ourTexture,TexCoord).w);\n"
        "  } else {\n"
        "     gl_FragColor = vec4(texture2D(ourTexture,TexCoord));\n"
        "  } \n"
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
                    LOGE("Could not compile shader %d:\n%s\n",
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
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}


static GLuint RuleTexture;

static void mkRuleTexture() { /* the texture used for rules */
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &RuleTexture);
    glBindTexture(GL_TEXTURE_2D, RuleTexture);
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


extern "C" void nativeInit(void) {
    LOGI("nativeInit GL Graphics\n");

    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    gProgram = createProgram(gVertexShader, gFragmentShader);
    if (!gProgram) {
        LOGE("Could not create program.");
        return;
    }
    gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");
    checkGlError("glGetAttribLocation");
    //LOGI("glGetAttribLocation(\"vPosition\") = %d\n", gvPositionHandle);

    glEnableVertexAttribArray(gvPositionHandle);
    checkGlError("glEnableVertexAttribArray");

    int ourColorLocation = glGetUniformLocation(gProgram, "ourColor");
    //int ourProjectionLocation = glGetUniformLocation(gProgram, "projection");
    glUseProgram(gProgram);

    mkRuleTexture();
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

    LOGI("nativeInit done\n");
}

static void nativeSetColors(GLfloat fr, GLfloat fg, GLfloat fb, GLfloat br, GLfloat bg, GLfloat bb)
/* set foreground and background rgb colors */
{
    int ourColorLocation = glGetUniformLocation(gProgram, "ourColor");
    glClearColor(br, bg, bb, 1.0f);
    glUniform4f(ourColorLocation, fr, fg, fb, 0.0f);
}

extern "C" void nativeSetDark(int dark) {
    LOGI("SetDark %d GL Graphics\n", dark);
    // set dark mode (= inverted texture colors)
    if (dark) {
        int ourModeLocation = glGetUniformLocation(gProgram, "ourMode");
        glUniform1i(ourModeLocation, DARK_MODE);
        mode = DARK_MODE;
        nativeSetColors(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
    } else {
        int ourModeLocation = glGetUniformLocation(gProgram, "ourMode");
        glUniform1i(ourModeLocation, LIGHT_MODE);
        mode = LIGHT_MODE;
        nativeSetColors(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    }
}

static int cur_h=600, cur_v=800;
extern "C" void nativeSetSize(int px_h, int px_v, double dpi)
/* Given the size of the output area px_h,px_v in pixel and the resolution in dpi,
   make sure the projection is set up properly.
 */
{
    float pt_h, pt_v;
    int ourProjectionLocation;

    /* convert pixel to point */
    pt_h = px_h * 72.27 / dpi;
    pt_v = px_v * 72.27 / dpi;
    /* convert point to scaled point*/
    page_h = round(pt_h * (1 << 16));
    page_v = round(pt_v * (1 << 16));

    LOGI("native SetSize to %f pt x %f pt (%d px x %d px)", pt_h, pt_v, px_h, px_v);

    // GL Coordinates are in points
    ourProjectionLocation = glGetUniformLocation(gProgram, "projection");
    glm::mat4 projection = glm::ortho(0.0f, pt_h, pt_v, 0.0f);
    glUniformMatrix4fv(ourProjectionLocation, 1, 0, glm::value_ptr(projection));
    glViewport(0, 0, px_h, px_v);
    cur_h=px_h;
    cur_v=px_v;
}


static void GLtexture(gcache_t *g) {
    unsigned GLtex;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    checkGlError("glPixelStorei");
    glGenTextures(1, &GLtex);
    checkGlError("glGenTextures");
    glBindTexture(GL_TEXTURE_2D, GLtex);
    checkGlError("glBindTexture");
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

extern "C" void nativeGlyph(double x, double y, double w, double h, gcache_t *g)
/* Using GL to render a character texture
   Coordinates in points, origin bottom left, x and w right, y and h up
   x,y position
   w,h width and height

  */
{ //LOGI("Rendering texture %i at (%f,%f) sized %fx%f",GLtexture,x/SPf,y/SPf,w/SPf,h/SPf);

    if (g->GLtexture == 0)
        GLtexture(g);

    GLfloat gQuad[] = {(GLfloat) x, (GLfloat) y, 0.0f, 1.0f,
                       (GLfloat) x, (GLfloat) (y + h), 0.0f, 0.0f,
                       (GLfloat) (x + w), (GLfloat) (y + h), 1.0f, 0.0f,
                       (GLfloat) x, (GLfloat) y, 0.0f, 1.0f,
                       (GLfloat) (x + w), (GLfloat) (y + h), 1.0f, 0.0f,
                       (GLfloat) (x + w), (GLfloat) y, 1.0f, 1.0f
    };
    glBindTexture(GL_TEXTURE_2D, g->GLtexture);
    checkGlError("glBindTexture");
    glVertexAttribPointer(gvPositionHandle, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), gQuad);
    checkGlError("glVertexAttribPointer");
    glDrawArrays(GL_TRIANGLES, 0, 6);
    checkGlError("glDrawArrays");
}


extern "C" void nativeRule(double x, double y, double w, double h)
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
    glBindTexture(GL_TEXTURE_2D, RuleTexture);
    checkGlError("glBindTexture");
    glVertexAttribPointer(gvPositionHandle, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), gQuad);
    checkGlError("glVertexAttribPointer");
    glDrawArrays(GL_TRIANGLES, 0, 6);
    checkGlError("glDrawArrays");
}


extern "C" void
nativeImage(double x, double y, double w, double h, unsigned char *b, unsigned char *e)
/* new image loading function using stb_image.h as image loader.
 It follows the example of https://learnopengl.com/Getting-started/Textures
 */
{
    int width, height, nrChannels;
    int ourModeLocation = glGetUniformLocation(gProgram, "ourMode");
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
        if (mode == DARK_MODE) {
            //set light mode
            glUniform1i(ourModeLocation, LIGHT_MODE);
        }
        glDrawArrays(GL_TRIANGLES, 0, 6);
        checkGlError("glDrawArrays");
        stbi_image_free(data);
        // make sure that image is always rendered in correct colors and not inverted in dark mode
        if (mode == DARK_MODE) {
            //set back to dark mode
            glUniform1i(ourModeLocation, DARK_MODE);
        }
    } else {
        LOGI("Can not read image %p", *b);
    }
}

/*extern "C" void nativeImage(double x, double y, double w, double h, unsigned char *b, unsigned char *e)
*//* WARNING: This function currently works only with grayscale images using
   the grayscale as alpha value, resulting in an inverted image (except in dark mode).
   We would like to have no inversion or even arbitrary colored images, retaining color in dark mode.
*//*

{
    uint32_t dataPos, imageSize, width, height;
    unsigned char *data;
    *//* check signature *//*
    if (b[0]!='B' || b[1]!='M')
    { LOGE("This is not a BMP image\n");
        return;
    }
    *//* extracting header data (little-endian) *//*
#define LittleEndian32(X)   (b[(X)]+(b[(X)+1]<<8)+(b[(X)+2]<<16)+(b[(X)+3]<<24))
    dataPos    = LittleEndian32(0xA);
    width      = LittleEndian32(0x12);
    height     = LittleEndian32(0x16);
    imageSize  = LittleEndian32(0x22);

    LOGI("BMP image at %d, size=%d, width=%d, height=%d\n", dataPos, imageSize, width, height);
    data=b+dataPos;

    GLuint textureID;
    glGenTextures(1, &textureID);
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,GL_ALPHA, width, height, 0, *//* GL_BGR  GL_RGB *//* GL_ALPHA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    GLfloat gQuad[] = {   (GLfloat)x ,        (GLfloat)y,     0.0f,0.0f,
                          (GLfloat)x,     (GLfloat)(y-h),     0.0f,1.0f,
                          (GLfloat)(x+w), (GLfloat)(y-h),     1.0f,1.0f,
                          (GLfloat)x,         (GLfloat)y,     0.0f,0.0f,
                          (GLfloat)(x+w), (GLfloat)(y-h),     1.0f,1.0f,
                          (GLfloat)(x+w),     (GLfloat)y,     1.0f,0.0f
    };
    glVertexAttribPointer(gvPositionHandle, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), gQuad);
    checkGlError("glVertexAttribPointer");
    glDrawArrays(GL_TRIANGLES, 0, 6);
    checkGlError("glDrawArrays");
}*/

extern "C" void nativeBlank(void) {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}


/* reading packed numbers from pk files */

static int j; /* position of next nybble in data */
static int r; /* current repeat count */
static int dyn_f; /* dynamic f value */
#define read_nybble() (j&1?(data[j++>>1]&0xF):((data[j++>>1]>>4)&0xF))

static int packed_number(unsigned char *data) {
    int i, k;
    i = read_nybble();
    if (i == 0) {
        do {
            k = read_nybble();
            i++;
        } while (k == 0);
        while (i-- > 0) k = k * 16 + read_nybble();
        return k - 15 + (13 - dyn_f) * 16 + dyn_f;
    } else if (i <= dyn_f) return i;
    else if (i < 14) return (i - dyn_f - 1) * 16 + read_nybble() + dyn_f + 1;
    else {
        if (i == 14) r = packed_number(data);
        else r = 1;
        return packed_number(data);
    }
}


extern "C" void nativeSetRunlength(gcache_t *g, unsigned char *data) {
    int x, y; /* position in bitmap */
    unsigned int n; /* number of pixel left in current run */
    int white = (g->pk.flag >> 3) & 1; /* whether pixel is white in current run */
    unsigned char *line;
    g->bits = (unsigned char *) calloc(g->w * g->h, 1);
    if (g->bits == NULL) {
        g->w = g->h = 0;
        return;
    } /* out of memory */
    j = 0; /* static nybble position to start of data */
    r = 0; /* static repeat count = 0 */
    dyn_f = g->pk.flag >> 4; /* static dynamic f value */
    n = 0;
    x = g->h - 1;
    line = g->bits + x * g->w;
    while (x >= 0) {
        int d;
        y = 0;
        while (y < (int) g->w) /* fill current line */
        {
            if (n <= 0) {
                n = packed_number(data);
                white = !white;
            }
            d = min(g->w - y, n); /* remaining pixel in current run and current line */
            while (d > 0) {
                line[y] = white ? 0x00 : 0xFF; /* White or Black */
                d--;
                y++;
                n--;
            }
        }
        x--;
        line = g->bits + x * g->w;
        while (r > 0 && x >= 0) /* copy previous line */
        {
            unsigned int k;
            for (k = 0; k < g->w; k++) line[k] = line[k + g->w];
            r--;
            x--;
            line = g->bits + x * g->w;
        }
    }
    GLtexture(g);
}

extern "C" void nativeSetBitmaped(gcache_t *g, unsigned char *data) {
    unsigned char *t = g->bits; /* byte=bit position in bits */
    int j = 0; /* bit position in data */
    int jj = 0; /* byte position in data */
    unsigned char next; /* next byte at data[jj] */
    int k = 0; /* bit position in next byte */
    //MESSAGE("Unpacking bitmap");
    g->bits = (unsigned char *) calloc(g->w * g->h, 1);
    if (g->bits == NULL) {
        g->w = g->h = 0;
        return;
    } /* out of memory */
    for (j = 0; j < g->h * g->w; j++, t++) {
        jj = j >> 3;
        k = j & 0x7;
        if (k == 0) {
            next = data[jj];
            k = 7;
        }
        if ((next >> (7 - k)) & 1) *t = 0x00; else *t = 0xFF;
    }
    GLtexture(g);
}


void nativeFreeGlyph(gcache_t *g)
/* Free resources associated with g. */
{
    if (g->GLtexture != 0) {
        glDeleteTextures(1, &(g->GLtexture));
        g->GLtexture = 0;
    }
}

extern "C" void nativeSetTrueType(struct gcache_s *g) {
    unsigned int x, y; /* position in bitmap */
    unsigned char *bits;
    unsigned int ww; /* width in Bytes */
    unsigned char *line;

    bits = g->bits;
    g->bits = NULL;
    ww = g->w;
    g->bits = (unsigned char *) calloc(ww * g->h, 1);
    if (g->bits == NULL) {
        g->w = g->h = 0;
        return;
    } /* out of memory */
    for (y = 0; y < g->h; y++) {
        line = g->bits + (g->h - y - 1) * ww;
        for (x = 0; x < g->w; x++)
            line[x] = bits[y * g->w + x];
    }
    free(bits);
    g->voff = -g->voff;
    g->hoff = -g->hoff;
    GLtexture(g);
}

/* ZOOMING */

static GLuint GLzoom=0;
static double zScale;
extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_zoomBegin(JNIEnv *env, jclass obj) {
    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    //glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    if (GLzoom!=0) return;
    LOGI("GL Zoom Begin\n");
    unsigned int fbo;
    glGenFramebuffers(1, &fbo); // create framebuffer object
    checkGlError("glGenFramebuffers");
    glBindFramebuffer(GL_FRAMEBUFFER, fbo); // bind it
    checkGlError("glBindFramebuffer");

    // creating the texture attachment
    glGenTextures(1, &GLzoom);
    glBindTexture(GL_TEXTURE_2D, GLzoom);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cur_h, cur_v, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // attach to framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, GLzoom, 0);

    // we skip the attachment of depth and stencil attachments
#if 0
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo)
#endif
    // check for completeness
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        LOGE("ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n");

    glClearColor(1.0f, 1.0f, 0.5f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, cur_h, cur_v);
    hint_render();
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // unbind
    checkGlError("glBindFramebuffer");
    glDeleteFramebuffers(1, &fbo); // delete
    checkGlError("glDeleteFramebuffers");


    zScale=1.0;
    LOGI("GL Zoom Begin done\n");

}

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_zoomEnd(JNIEnv *env, jclass obj) {
    LOGI("GL Zoom End\n");
    glDeleteTextures(1, &GLzoom);
    GLzoom=0;
}

extern "C" JNIEXPORT jdouble JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_zoom(JNIEnv *env, jclass obj, jdouble f, jdouble xf, jdouble yf) {
    zScale*=f;
    LOGI("GL Zooming scale=%f x=%f y=%f\n",zScale,xf,yf);
    GLfloat x = 30.0;
    GLfloat y = 30.0;
    GLfloat w = cur_h*0.1;
    GLfloat h = cur_v*0.1;
    GLfloat gQuad[] = {(GLfloat) x, (GLfloat) y, 0.0f, 1.0f,
                       (GLfloat) x, (GLfloat) (y + h), 0.0f, 0.0f,
                       (GLfloat) (x + w), (GLfloat) (y + h), 1.0f, 0.0f,
                       (GLfloat) x, (GLfloat) y, 0.0f, 1.0f,
                       (GLfloat) (x + w), (GLfloat) (y + h), 1.0f, 0.0f,
                       (GLfloat) (x + w), (GLfloat) y, 1.0f, 1.0f
    };

    glBindTexture(GL_TEXTURE_2D, GLzoom);
    checkGlError("glBindTexture");
    glVertexAttribPointer(gvPositionHandle, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), gQuad);
    checkGlError("glVertexAttribPointer");
    glDrawArrays(GL_TRIANGLES, 0, 6);
    checkGlError("glDrawArrays");
    return zScale;
}
