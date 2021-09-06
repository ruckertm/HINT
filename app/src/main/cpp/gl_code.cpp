/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// OpenGL ES 2.0 code

#include <jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>



extern "C" {
#include <android/bitmap.h>
#include "basetypes.h"
#include "error.h"
#include "hformat.h"
#include "hget.h"
#include "hint.h"
#include "hrender.h"
#include "rendernative.h"

// Functions from rendergl.c
#if 0
/Ü used for classic zoom removed in release 1.1 */
extern void glZoomBegin(void);
extern void glZoom(void);
extern void glZoomEnd(void);
#endif
#if 0
/* used for prining never got it working */
extern void glDrawBitmap(uint32_t width, uint32_t height, uint32_t stride, void *pixel);
#endif
//DEPRECATED
//extern void nativeSetColors(double fr, double fg, double fb, double br, double bg, double bb);
};


#define  LOG_TAG    "libhintview"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#define HINT_CATCH(X) else LOGE("HINT_TRY Error exit " X "\n")

extern "C" {
JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_init(JNIEnv *env, jclass obj);
JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_begin(JNIEnv *env, jclass obj, jint fileDescriptor);
JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_change(JNIEnv *env, jclass obj, jint width, jint height,
                                           jdouble xdpi, jdouble ydpi);
JNIEXPORT jboolean JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_singleTap(JNIEnv *env, jclass obj, jdouble x, jdouble y,
                                           jdouble xdpi, jdouble ydpi);
JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_draw(JNIEnv *env, jclass obj);
JNIEXPORT void JNICALL Java_edu_hm_cs_hintview_HINTVIEWLib_next(JNIEnv *env, jclass obj);
JNIEXPORT void JNICALL Java_edu_hm_cs_hintview_HINTVIEWLib_prev(JNIEnv *env, jclass obj);
JNIEXPORT jlong JNICALL Java_edu_hm_cs_hintview_HINTVIEWLib_getPos(JNIEnv *env, jclass obj);
JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_setPos(JNIEnv *env, jclass obj, jlong pos);
JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_setMode(JNIEnv *env, jclass obj, jboolean mode);
JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_home(JNIEnv *env, jclass obj);
JNIEXPORT jstring JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_error(JNIEnv *env, jclass obj);
JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_zoomBegin(JNIEnv *env, jclass obj);
JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_zoomEnd(JNIEnv *env, jclass obj);
JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_zoom(JNIEnv *env, jclass obj);
};


//char herror_string[MAX_HERROR];
//jmp_buf error_exit;

extern "C" JNIEXPORT jstring JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_error(JNIEnv *env, jclass obj) {
    if (herror_string[0]!=0) return (*env).NewStringUTF(herror_string);
    else return nullptr;
}



extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_init(JNIEnv *env, jclass obj) {
    LOGI("Native init\n");
    debugflags=0x1;
    nativeInit();
 }


int fd=-1;

extern "C" bool hint_map(void) {
    struct stat st;
    LOGI("hint_map\n");
     if (fd < 0) MESSAGE("Unable to open file");
    if (fstat(fd, &st) < 0) MESSAGE("Unable to get file size");
    hin_size = st.st_size;
	hin_time = st.st_mtime;
    hin_addr = (uint8_t *) mmap(NULL, hin_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (hin_addr == MAP_FAILED) MESSAGE("Unable to map file into memory");
    close(fd);
    return true;
 }

extern "C" void hint_unmap(void) {
    LOGI("hint_unmap\n");
    if (hin_addr != NULL)
        munmap(hin_addr, hin_size);
    hin_addr = NULL;
    hin_size=0;
}


extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_begin(JNIEnv *env, jclass obj, jint fileDescriptor) {
    LOGI("hint_end;hint_clear_fonts(true);hint_begin\n");
     fd=fileDescriptor;
     HINT_TRY {
        hint_end();
        hint_clear_fonts(true);
        hint_begin();
    }HINT_CATCH("begin");
}

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_change(JNIEnv *env, jclass obj, jint width, jint height,
                                           jdouble xdpi, jdouble ydpi) {
    LOGI("hint_resize(width=%d height=%d xdpi=%f ydpi=%f))\n", width, height, xdpi, ydpi);
    HINT_TRY {
    hint_resize(width, height, xdpi);
    hint_page();
    }HINT_CATCH("resize");
}

extern "C" JNIEXPORT jboolean JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_singleTap(JNIEnv *env, jclass obj, jdouble x, jdouble y,
                                           jdouble xdpi, jdouble ydpi) {
    int link;
    LOGI("hint_find_link(x=%f y=%f xdpi=%f ydpi=%f))\n", x, y, xdpi, ydpi);
    HINT_TRY {
        link=hint_find_link(round((x*0x10000)*72.27/xdpi),
                    round((y*0x10000)*72.27/ydpi),3*ONE);
        if (link>=0) hint_link_page(link);
    } HINT_CATCH("singleTap");
    return link>=0;
}


extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_draw(JNIEnv *env, jclass obj) {
    LOGI("hint_render\n");
    HINT_TRY hint_render();HINT_CATCH("render");
}

#if 0
/* used in printing but never completed */
extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_drawBitmap(JNIEnv *env, jclass obj, jobject bitmap) {

    AndroidBitmapInfo  info;
    void*              pixels;
    int                ret;
    LOGI("drawBitmap\n");

    if ((ret = AndroidBitmap_getInfo(env, bitmap, &info)) < 0) {
        LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
        return;
    }

    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGE("Bitmap format is not RGBA_8888 !");
        return;
    }

    if ((ret = AndroidBitmap_lockPixels(env, bitmap, &pixels)) < 0) {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
    }


    glDrawBitmap(info.width, info.height, info.stride, pixels);


    if ((ret = AndroidBitmap_unlockPixels(env, bitmap))< 0) {
        LOGE("AndroidBitmap_unlockPixels() failed ! error=%d", ret);
    }
}
#endif

#if 0
/* used for traditional zoom, removed in release 1.1 */
extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_zoomBegin(JNIEnv *env, jclass obj) {
    LOGI("Zoom Begin\n");
    glZoomBegin();
}

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_zoomEnd(JNIEnv *env, jclass obj) {
    LOGI("Zoom End\n");
    glZoomEnd();
}

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_zoom(JNIEnv *env, jclass obj) {
    LOGI("Zoom\n");
    glZoom();
}
#endif

    extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_next(JNIEnv *env, jclass obj) {
    LOGI("hint_next_page\n");
    HINT_TRY hint_next_page();HINT_CATCH("next");
}

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_prev(JNIEnv *env, jclass obj) {
    LOGI("hint_prev_page\n");
    HINT_TRY hint_prev_page();HINT_CATCH("prev");
}

extern "C" JNIEXPORT jlong JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_getPos(JNIEnv *env, jclass obj) {
    uint64_t hpos;
    jlong pos;
    hpos = hint_page_get();
    pos = hpos;
    LOGI("hint_page_get: (0x%x %x)-> (0x%x %x)\n", (int) (hpos >> 32), (int) (hpos & 0xffffffff),
         (int) (pos >> 32), (int) (pos & 0xffffffff));
    return pos;
}

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_setPos(JNIEnv *env, jclass obj, jlong pos) {
    LOGI("hint_page_top(0x%x %x)\n", (int)(pos>>32), (int)(pos&0xffffffff));
    HINT_TRY hint_page_top(pos);HINT_CATCH("top");
}

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_setMode(JNIEnv *env, jclass obj, jboolean mode) {
    if (mode) nativeSetDark(true);
    else nativeSetDark(false);
}

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_home(JNIEnv *env, jclass obj) {
    // go to home page
    LOGI("hint_home_page()\n");
    HINT_TRY hint_home_page();HINT_CATCH("home page");
}

