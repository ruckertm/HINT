
package edu.hm.cs.hintview;
/*
 * Copyright (C) 2008 The Android Open Source Project
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


import android.app.Dialog;
import android.content.Context;
import android.graphics.Bitmap;
import android.net.Uri;
import android.opengl.GLSurfaceView;
import android.os.ParcelFileDescriptor;
import android.util.AttributeSet;
import android.util.DisplayMetrics;
//import android.util.Log;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;


import java.io.FileNotFoundException;
import java.io.IOException;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

public class HINTVIEWView extends GLSurfaceView implements View.OnTouchListener {
    private static String TAG = "HINTVIEWView";
    private static final boolean DEBUG = false;
    public static double xdpi, ydpi;
    public static double scale = 1.0;
    private static int width, height;
    protected Renderer fileRenderer;
    private static boolean darkMode = false;
    protected static boolean ZoomOn = false, ZoomOff = false, Zooming = false;
    protected static boolean Page_next = false, Page_prev = false;
    private GestureDetector touchGestureDetector;
    private ScaleGestureDetector scaleGestureDetector;
    protected final Context context;

    public HINTVIEWView(Context context) {
        super(context);
        this.context=context;
    }

    public HINTVIEWView(Context context, AttributeSet attrs) {
        super(context, attrs);
        this.context=context;
    }

    public HINTVIEWView(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs);
        this.context=context;
    }

    public void init() {
        DisplayMetrics metrics = context.getResources().getDisplayMetrics();
        //Log.w(TAG, String.format("Resolution xdpi=%f ydpi=%f\n", metrics.xdpi, metrics.ydpi));
        xdpi = metrics.xdpi;
        ydpi = metrics.ydpi;

        setEGLContextFactory(new ContextFactory());
        setEGLConfigChooser(new ConfigChooser(5, 6, 5, 0, 0, 0));

        // Add gesture detector
        touchGestureDetector = new GestureDetector(context, new TouchGestureHandler(this));
        scaleGestureDetector = new ScaleGestureDetector(context, new ScaleGestureHandler(this));
        setOnTouchListener(this);
        fileRenderer = new Renderer(context, this);
        setRenderer(fileRenderer);
        setRenderMode(RENDERMODE_WHEN_DIRTY);
    }

    public void setFile(String fileUriStr, long pos) {
        fileRenderer.setFile(fileUriStr, pos);

    }

    public long getPos() {
        if (fileRenderer == null) return 0;
        else return fileRenderer.getPos();
    }

    public String getFileUriStr() {
        if (fileRenderer == null) return null;
        return fileRenderer.getFileUriStr();
    }


    @Override
    public boolean onTouch(View view, MotionEvent motionEvent) {
        boolean s = scaleGestureDetector.onTouchEvent(motionEvent);
        if (scaleGestureDetector.isInProgress()) return true;
        boolean t = touchGestureDetector.onTouchEvent(motionEvent);

        return t;
    }

    public double getScale() {
        return scale;
    }

    public void setScale(double s) {
        scale = s;
        if (scale < 0.1) scale = 0.1;
    }

    public boolean getMode() {
        return darkMode;
    }

    public void setMode(boolean mode) {
        darkMode = mode;
    }



    private static class ContextFactory implements GLSurfaceView.EGLContextFactory {

        public EGLContext createContext(EGL10 egl, EGLDisplay display, EGLConfig eglConfig) {
            //Log.w(TAG, "creating OpenGL ES 2.0 context");
            checkEglError("Before eglCreateContext", egl);
            int EGL_CONTEXT_CLIENT_VERSION = 0x3098;
            int[] attrib_list = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL10.EGL_NONE};
            EGLContext egl_context = egl.eglCreateContext(display, eglConfig, EGL10.EGL_NO_CONTEXT, attrib_list);
            checkEglError("After eglCreateContext", egl);
            return egl_context;
        }

        public void destroyContext(EGL10 egl, EGLDisplay display, EGLContext egl_context) {
            egl.eglDestroyContext(display, egl_context);
        }
    }

    private static void checkEglError(String prompt, EGL10 egl) {
        int error;
        while ((error = egl.eglGetError()) != EGL10.EGL_SUCCESS) {
            //Log.e(TAG, String.format("%s: EGL error: 0x%x", prompt, error));
        }
    }

    private static class ConfigChooser implements GLSurfaceView.EGLConfigChooser {

        ConfigChooser(int r, int g, int b, int a, int depth, int stencil) {
            mRedSize = r;
            mGreenSize = g;
            mBlueSize = b;
            mAlphaSize = a;
            mDepthSize = depth;
            mStencilSize = stencil;
        }

        /* This EGL config specification is used to specify 2.0 rendering.
         * We use a minimum size of 4 bits for red/green/blue, but will
         * perform actual matching in chooseConfig() below.
         */
        private static int EGL_OPENGL_ES2_BIT = 4;
        private static int[] s_configAttribs2 =
                {
                        EGL10.EGL_RED_SIZE, 4,
                        EGL10.EGL_GREEN_SIZE, 4,
                        EGL10.EGL_BLUE_SIZE, 4,
                        EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                        EGL10.EGL_NONE
                };

        public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display) {

            /* Get the number of minimally matching EGL configurations
             */
            int[] num_config = new int[1];
            egl.eglChooseConfig(display, s_configAttribs2, null, 0, num_config);

            int numConfigs = num_config[0];

            if (numConfigs <= 0) {
                throw new IllegalArgumentException("No configs match configSpec");
            }

            /* Allocate then read the array of minimally matching EGL configs
             */
            EGLConfig[] configs = new EGLConfig[numConfigs];
            egl.eglChooseConfig(display, s_configAttribs2, configs, numConfigs, num_config);

             /* Now return the "best" one
             */
            return chooseConfig(egl, display, configs);
        }

        EGLConfig chooseConfig(EGL10 egl, EGLDisplay display,
                               EGLConfig[] configs) {
            for (EGLConfig config : configs) {
                int d = findConfigAttrib(egl, display, config,
                        EGL10.EGL_DEPTH_SIZE, 0);
                int s = findConfigAttrib(egl, display, config,
                        EGL10.EGL_STENCIL_SIZE, 0);

                // We need at least mDepthSize and mStencilSize bits
                if (d < mDepthSize || s < mStencilSize)
                    continue;

                // We want an *exact* match for red/green/blue/alpha
                int r = findConfigAttrib(egl, display, config,
                        EGL10.EGL_RED_SIZE, 0);
                int g = findConfigAttrib(egl, display, config,
                        EGL10.EGL_GREEN_SIZE, 0);
                int b = findConfigAttrib(egl, display, config,
                        EGL10.EGL_BLUE_SIZE, 0);
                int a = findConfigAttrib(egl, display, config,
                        EGL10.EGL_ALPHA_SIZE, 0);

                if (r == mRedSize && g == mGreenSize && b == mBlueSize && a == mAlphaSize)
                    return config;
            }
            return null;
        }

        private int findConfigAttrib(EGL10 egl, EGLDisplay display,
                                     EGLConfig config, int attribute, int defaultValue) {

            if (egl.eglGetConfigAttrib(display, config, attribute, mValue)) {
                return mValue[0];
            }
            return defaultValue;
        }


        // Subclasses can adjust these values:
        protected int mRedSize;
        protected int mGreenSize;
        protected int mBlueSize;
        protected int mAlphaSize;
        protected int mDepthSize;
        protected int mStencilSize;
        private int[] mValue = new int[1];
    }




    protected static class Renderer implements GLSurfaceView.Renderer {
        private HINTVIEWView view;
        private final Context context;
        private String fileUriStr;
        private String ErrorMsg;
        private long pos;

        Renderer(Context context,HINTVIEWView view) {
            this.view = view;
            this.context = context;
        }

        private boolean render_OK() {
            ErrorMsg = HINTVIEWLib.error();
            if (ErrorMsg != null) {
                //Log.w(TAG, "Error in renderer: " + ErrorMsg + "!");
                view.post(new Runnable() {
                    public void run() {
                        final Dialog dialog = new Dialog(context);
                        dialog.setContentView(R.layout.render_error);
                        TextView t=dialog.findViewById(R.id.ErrorMsg);
                        t.setText(ErrorMsg);
                        Button dialogButton = (Button) dialog.findViewById(R.id.OKbutton);
                        dialogButton.setOnClickListener(new OnClickListener() {
                            @Override
                            public void onClick(View v) {
                                dialog.dismiss();
                            }
                        });
                        dialog.show();
                    }
                });
                this.fileUriStr = null;
                this.pos = 0;
                return false;
            } else
                return true;
        }


        public void setFile(String fileUriStr, long pos) throws java.lang.SecurityException{
            if (fileUriStr != null)
                try {   //Gets called every time, after app gets maximized. So passing just the fileDescriptor to the renderer will result in an error
                    //bc it got already closed in the cpp code
                    //Log.w(TAG, "setFile " + fileUriStr + " at " + Long.toHexString(pos));
                    Uri fileURI = Uri.parse(fileUriStr);
                    ParcelFileDescriptor pfd = context.getContentResolver().openFileDescriptor(fileURI, "r");
                    int fd = pfd.detachFd();
                    //Log.w(TAG, "setFile fd = " + fd);

                    HINTVIEWLib.begin(fd);
                    if (render_OK()) {
                        HINTVIEWLib.setPos(pos);
                        this.fileUriStr = fileUriStr;
                        this.pos = pos;
                    }
                    pfd.close();
                } catch (FileNotFoundException e) {
                    //Log.e("", "", e);
                } catch (IOException e) {
                    //Log.e("", "", e);
                }
        }

        public long getPos() {
            long pos = 0;
            if (fileUriStr != null) pos = HINTVIEWLib.getPos();
            //Log.w(TAG, "getPos = " + Long.toHexString(pos));
            return pos;
        }

        public String getFileUriStr() {
            return fileUriStr;
        }

        public void onDrawFrame(GL10 gl) {

            HINTVIEWLib.setMode(darkMode);
            HINTVIEWLib.change(width, height, scale * xdpi, scale * ydpi); /* needed for zooming */
            if (HINTVIEWView.Page_prev) {
                HINTVIEWLib.prev();
                HINTVIEWView.Page_prev = false;
            }
            if (HINTVIEWView.Page_next) {
                HINTVIEWLib.next();
                HINTVIEWView.Page_next = false;
            }
            if (!render_OK()) return;

            HINTVIEWLib.draw();
            render_OK();
        }

        public void onSurfaceChanged(GL10 gl, int w, int h) {
            width = w;
            height = h;
            HINTVIEWLib.setMode(darkMode);
            HINTVIEWLib.change(width, height, scale * xdpi, scale * ydpi);
            render_OK();
        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            HINTVIEWLib.init();
        }

    }
}

