/*
 * Copyright (C) 2007 The Android Open Source Project
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

package edu.hm.cs.hintview;

// Wrapper for native library

public class HINTVIEWLib {

    static {
        System.loadLibrary("hintview");
    }

    public static native void create(int fileDescriptor);

    public static native void change(int width, int height, double xdpi, double ydpi);

    public static native void draw();

    public static native void next();

    public static native void prev();

    public static native long getPos();

    public static native void setPos(long pos);

    public static native void setMode(boolean mode);

    public static native void home();
}
