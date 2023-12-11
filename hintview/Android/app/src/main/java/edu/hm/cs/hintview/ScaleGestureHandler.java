package edu.hm.cs.hintview;

//import android.util.Log;
import android.view.ScaleGestureDetector;

public class ScaleGestureHandler extends ScaleGestureDetector.SimpleOnScaleGestureListener {
    //private static final String TAG = "ScaleGestureDetector";

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
        HINTVIEWView.clearFonts =true;
        //Log.w(TAG, "onScaleEnd "+ detector.isInProgress());
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
