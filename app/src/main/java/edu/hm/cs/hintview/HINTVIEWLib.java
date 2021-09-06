package edu.hm.cs.hintview;

// Wrapper for native library

import android.graphics.Bitmap;

import java.util.BitSet;

public class HINTVIEWLib {

    static {
        System.loadLibrary("hintview");
    }

    public static native String error();

    public static native void init();

    public static native void begin(int fileDescriptor);

    public static native void change(int width, int height, double xdpi, double ydpi);

    public static native boolean singleTap(double x, double y, double xdpi, double ydpi);

    public static native void draw();

    public static native void next();

    public static native void prev();

    public static native long getPos();

    public static native void setPos(long pos);

    public static native void setMode(boolean mode);

    public static native void home();

    public static native void zoomBegin();

    public static native void zoomEnd();

    public static native void zoom();

}
