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
#include "rendernative.h"
#include "hinttop.h"
#include "htex.h"
#include "hpos.h"
};



#define  LOG_TAG    "libhintview"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


extern "C" {
JNIEXPORT void JNICALL Java_edu_hm_cs_hintview_HINTVIEWLib_create(JNIEnv * env, jobject obj,  jdouble xdpi, jdouble ydpi, jint foreground_color, jint background_color);
JNIEXPORT void JNICALL Java_edu_hm_cs_hintview_HINTVIEWLib_change(JNIEnv * env, jobject obj,  jint width, jint height);
JNIEXPORT void JNICALL Java_edu_hm_cs_hintview_HINTVIEWLib_draw(JNIEnv * env, jobject obj, jint width, jint height, jdouble xdpi, jdouble ydpi);
JNIEXPORT void JNICALL Java_edu_hm_cs_hintview_HINTVIEWLib_next(JNIEnv * env, jobject obj);
JNIEXPORT void JNICALL Java_edu_hm_cs_hintview_HINTVIEWLib_prev(JNIEnv *env, jobject obj);
};


static void renderFrame(void) {
    LOGI("Render Frame");
    nativeBlank();
    hint_page();
}

GLfloat hdpi, vdpi; // resolution of canvas
// converting pixel to pointe and back
#define px2pt(X)   (72.27f*(X)/hdpi)
#define pt2px(T)   ((T)*hdpi/72.27f)

JNIEXPORT void JNICALL Java_edu_hm_cs_hintview_HINTVIEWLib_create(JNIEnv * env, jobject obj,  jdouble xdpi, jdouble ydpi, jint foreground_color, jint background_color)
{   LOGI("create(xdpi=%f ydpi=%f)\n", xdpi, ydpi);
    hdpi=xdpi;
    vdpi=ydpi;
    nativeInit();
    LOGI("change(foreground_color=%i background_color=%i)\n", foreground_color, background_color);

    double foreground_R = (foreground_color >> 16) & 0xff;
    double foreground_G = (foreground_color >>  8) & 0xff;
    double foreground_B = (foreground_color      ) & 0xff;
    double background_R = (background_color >> 16) & 0xff;
    double background_G = (background_color >>  8) & 0xff;
    double background_B = (background_color      ) & 0xff;

    nativeSetColors(foreground_R, foreground_G, foreground_B, background_R, background_G, background_B);
    //nativeSetColors(0.0f, 0.0f, 0.5f, 1.0f, 1.0f, 0.8f);
    //hint_start("/sdcard/Download/head.hnt");
    //hint_start("/storage/emulated/0/Download/image.hnt");
    //hint_start("/storage/emulated/0/Download/math.hnt");
    hint_start("/storage/emulated/0/Download/mfpreface.hnt");
}


JNIEXPORT void JNICALL Java_edu_hm_cs_hintview_HINTVIEWLib_change(JNIEnv * env, jobject obj,  jint width, jint height)
{   LOGI("change(width=%d height=%d)\n", width, height);

    nativeSetSize(width,height,hdpi);

    //renderFrame();
}

JNIEXPORT void JNICALL Java_edu_hm_cs_hintview_HINTVIEWLib_draw(JNIEnv * env, jobject obj, jint width, jint height, jdouble xdpi, jdouble ydpi)
{   LOGI("draw(width=%d height=%d xdpi=%f ydpi=%f))\n", width, height, xdpi, ydpi);
    hdpi=xdpi;
    vdpi=ydpi;

    nativeSetSize(width,height,hdpi);
    renderFrame();

}

JNIEXPORT void JNICALL Java_edu_hm_cs_hintview_HINTVIEWLib_next(JNIEnv * env, jobject obj)
{   LOGI("next()\n");
    hpos_next();
}

JNIEXPORT void JNICALL Java_edu_hm_cs_hintview_HINTVIEWLib_prev(JNIEnv *env, jobject obj) {
    LOGI("prev()\n");
    hpos_prev();
}

