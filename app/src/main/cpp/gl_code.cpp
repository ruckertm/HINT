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
//include "stb_truetype.h"
//include "hfonts.h"
#include "basetypes.h"
#include "error.h"
#include "hformat.h"
#include "hget.h"
#include "hint.h"
#include "hrender.h"
#include "rendernative.h"
char *in_name=NULL; /* to keep hget happy */

//DEPRECATED
//extern void nativeSetColors(double fr, double fg, double fb, double br, double bg, double bb);
};


#define  LOG_TAG    "libhintview"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


extern "C" {
JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_init(JNIEnv *env, jclass obj);
JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_begin(JNIEnv *env, jclass obj, jint fileDescriptor);
JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_change(JNIEnv *env, jclass obj, jint width, jint height,
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
JNIEXPORT jdouble JNICALL
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
    debugflags=DBGBASIC;
    nativeInit();
 }


int fd=-1;
static size_t hbase_size;
extern "C" void hint_map(void) {
    struct stat st;
    HINT_TRY {
    if (fd < 0) QUIT("Unable to open file");
    if (fstat(fd, &st) < 0) QUIT("Unable to get file size");
    hbase_size = st.st_size;
    hbase = (uint8_t *) mmap(NULL, hbase_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (hbase == MAP_FAILED) QUIT("Unable to map file into memory");
    close(fd);
    hpos = hstart = hbase;
    hend = hstart + hbase_size;
  }
}

extern "C" void hint_unmap(void) {
    if (hbase != NULL)
        munmap(hbase, hbase_size);
    hbase = NULL;
    hpos = hstart = hend = NULL;
}


extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_begin(JNIEnv *env, jclass obj, jint fileDescriptor) {
    LOGI("begin\n");
     fd=fileDescriptor;
     HINT_TRY {
        //nativeSetColors(0.0f, 0.0f, 0.5f, 1.0f, 1.0f, 0.8f);
        //hint_open("/storage/emulated/0/Download/paging.hnt");
        //hint_open("/storage/emulated/0/Download/math.hnt");
        //hint_open("/storage/emulated/0/Download/mfpreface.hnt");
        //hint_open("/storage/emulated/0/Download/bmp.hnt");
        //hint_open("/storage/emulated/0/Download/png.hnt");
        //hint_open("/storage/emulated/0/Download/display.hnt");
        //hint_open("/storage/emulated/0/Download/opentype.hnt");
        //hint_open("/storage/emulated/0/Download/truetype.hnt");
        //hint_open("/storage/emulated/0/Download/ligature.hnt");
        //hint_open("/storage/emulated/0/Download/jpg.hnt");
        hint_end();
        hint_clear_fonts(true);
        hint_begin();
        LOGI("done begin");
    }
}

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_change(JNIEnv *env, jclass obj, jint width, jint height,
                                           jdouble xdpi, jdouble ydpi) {
    //LOGI("change(width=%d height=%d xdpi=%f ydpi=%f))\n", width, height, xdpi, ydpi);
    HINT_TRY {
    hint_resize(width, height, xdpi);
    hint_page();
    }
}


extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_draw(JNIEnv *env, jclass obj) {
    LOGI("draw\n");
    HINT_TRY hint_render();
}

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_next(JNIEnv *env, jclass obj) {
    LOGI("next()\n");
    HINT_TRY hint_next_page();
}

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_prev(JNIEnv *env, jclass obj) {
    LOGI("prev()\n");
    HINT_TRY hint_prev_page();
}

extern "C" JNIEXPORT jlong JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_getPos(JNIEnv *env, jclass obj) {
    uint64_t hpos;
    jlong pos;
    hpos = hint_page_get();
    pos = hpos;
    LOGI("getPos(0x%x %x)-> (0x%x %x)\n", (int) (hpos >> 32), (int) (hpos & 0xffffffff),
         (int) (pos >> 32), (int) (pos & 0xffffffff));
    return pos;
}

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_setPos(JNIEnv *env, jclass obj, jlong pos) {
    LOGI("setPos(0x%x %x)\n", (int)(pos>>32), (int)(pos&0xffffffff));
    HINT_TRY hint_page_top(pos);
}

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_setMode(JNIEnv *env, jclass obj, jboolean mode) {
    if (mode) nativeSetDark(true);
    else nativeSetDark(false);
}

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_home(JNIEnv *env, jclass obj) {
    // go to first page
    LOGI("hpos_home()\n");
    HINT_TRY hint_page_top(0);
}

