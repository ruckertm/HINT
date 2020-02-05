package edu.hm.cs.hintview;

import android.view.ScaleGestureDetector;

public class ScaleGestureHandler extends ScaleGestureDetector.SimpleOnScaleGestureListener {

    private final HINTVIEWView view;

    public ScaleGestureHandler(HINTVIEWView view) {
        super();
        this.view = view;
    }

    @Override
    public boolean onScale(ScaleGestureDetector detector) {
        float scaleFactor = detector.getScaleFactor();
        view.multScale(scaleFactor);
        //view.scale *= scaleFactor;
        view.requestRender();
        return true;
    }
}
