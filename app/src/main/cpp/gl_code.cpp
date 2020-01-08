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

extern "C" {
#include "fonts.h"
#include "rendergl.h"
#include "hinttop.h"
#include "htex.h"
#include "hpos.h"
};


#define  LOG_TAG    "libhintview"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


extern "C" {
JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_create(JNIEnv *env, jclass obj, jdouble xdpi, jdouble ydpi,
                                           jint background_color, jint mode);
JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_change(JNIEnv *env, jclass obj, jint width, jint height);
JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_draw(JNIEnv *env, jclass obj, jint width, jint height,
                                         jdouble xdpi, jdouble ydpi, jint background_color);
JNIEXPORT void JNICALL Java_edu_hm_cs_hintview_HINTVIEWLib_next(JNIEnv *env, jclass obj);
JNIEXPORT void JNICALL Java_edu_hm_cs_hintview_HINTVIEWLib_prev(JNIEnv *env, jclass obj);
JNIEXPORT int JNICALL Java_edu_hm_cs_hintview_HINTVIEWLib_getPos(JNIEnv *env, jclass obj);
JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_setPos(JNIEnv *env, jclass obj, jint pos);
JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_home(JNIEnv *env, jclass obj);
JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_lightMode(JNIEnv *env, jclass obj);
JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_darkMode(JNIEnv *env, jclass obj);
};


static void renderFrame() {
    LOGI("Render Frame");
    nativeBlank();
    hint_page();
}

GLfloat hdpi, vdpi; // resolution of canvas
// converting pixel to point and back
#define px2pt(X)   (72.27f*(X)/hdpi)
#define pt2px(T)   ((T)*hdpi/72.27f)

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_create(JNIEnv *env, jclass obj, jdouble xdpi, jdouble ydpi,
                                           jint background_color, jint mode) {
    LOGI("create(xdpi=%f ydpi=%f)\n", xdpi, ydpi);
    hdpi = xdpi;
    vdpi = ydpi;
    nativeInit();
    LOGI("change(background_color=%i)\n", background_color);

//    double foreground_R = (foreground_color >> 16) & 0xff;
//    double foreground_G = (foreground_color >> 8) & 0xff;
//    double foreground_B = (foreground_color) & 0xff;
    double background_R = (background_color >> 16) & 0xff;
    double background_G = (background_color >> 8) & 0xff;
    double background_B = (background_color) & 0xff;

    nativeSetColors(0, 0, 0, background_R, background_G, background_B);
    if (mode > 0){
        setDarkMode();
    } else{
        setLightMode();
    }
    //nativeSetColors(0.0f, 0.0f, 0.5f, 1.0f, 1.0f, 0.8f);
    //hint_start("/storage/emulated/0/Download/paging.hnt");
    //hint_start("/storage/emulated/0/Download/math.hnt");
    //hint_start("/storage/emulated/0/Download/mfpreface.hnt");
    //hint_start("/storage/emulated/0/Download/bmp.hnt");
    hint_start("/storage/emulated/0/Download/png.hnt");
    //hint_start("/storage/emulated/0/Download/display.hnt");
    //hint_start("/storage/emulated/0/Download/opentype.hnt");
    //hint_start("/storage/emulated/0/Download/ligature.hnt");
    //hint_start("/storage/emulated/0/Download/jpg.hnt");
}

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_change(JNIEnv *env, jclass obj, jint width, jint height) {
    LOGI("change(width=%d height=%d)\n", width, height);

    nativeSetSize(width, height, hdpi);

    //renderFrame();
}

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_draw(JNIEnv *env, jclass obj, jint width, jint height,
                                         jdouble xdpi, jdouble ydpi, jint background_color) {
    LOGI("draw(width=%d height=%d xdpi=%f ydpi=%f background_color=%d))\n", width, height, xdpi, ydpi, background_color);
    hdpi = xdpi;
    vdpi = ydpi;

    double background_R = (background_color >> 16) & 0xff;
    double background_G = (background_color >> 8) & 0xff;
    double background_B = (background_color) & 0xff;

    nativeSetColors(0, 0, 0, background_R, background_G, background_B);

    nativeSetSize(width, height, hdpi);
    renderFrame();

}

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_next(JNIEnv *env, jclass obj) {
    LOGI("next()\n");
    hpos_next();
}

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_prev(JNIEnv *env, jclass obj) {
    LOGI("prev()\n");
    hpos_prev();
}

extern "C" JNIEXPORT int JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_getPos(JNIEnv *env, jclass obj) {
    LOGI("getPos()\n");
    return hpos_get_cur();
}

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_setPos(JNIEnv *env, jclass obj, jint pos) {
    LOGI("setPos(%d)\n", pos);
    /* TODO implement correctly */
}

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_home(JNIEnv *env, jclass obj) {
    // go to first page
    LOGI("hpos_home()\n");
    hpos_home();
}

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_lightMode(JNIEnv *env, jclass obj) {
    setLightMode();
    renderFrame();
}

extern "C" JNIEXPORT void JNICALL
Java_edu_hm_cs_hintview_HINTVIEWLib_darkMode(JNIEnv *env, jclass obj) {
    setDarkMode();
    renderFrame();
}
