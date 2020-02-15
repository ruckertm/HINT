package edu.hm.cs.hintview;

import android.util.Log;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;

public class ScaleGestureHandler extends ScaleGestureDetector.SimpleOnScaleGestureListener {
    private static String TAG = "ScaleGestureDetector";

    private final HINTVIEWView view;

    public ScaleGestureHandler(HINTVIEWView view) {
        super();
        this.view = view;
    }

    @Override
    public boolean onScaleBegin(ScaleGestureDetector detector) {
       HINTVIEWView.ZoomOn=true;
        view.requestRender();
        return true;
    }
    @Override
    public void onScaleEnd(ScaleGestureDetector detector) {
        HINTVIEWView.ZoomOff=true;
        Log.w(TAG, "onScaleEnd ");
        view.requestRender();
    }
    @Override
    public boolean onScale(ScaleGestureDetector detector) {
        float f = detector.getScaleFactor();
        //float x = detector.getFocusX();
        //float y = detector.getFocusY();

        HINTVIEWView.scale *= f;
        HINTVIEWView.Zooming = true;

        view.requestRender();

        return true;
    }
}
