package edu.hm.cs.hintview;

import android.view.ScaleGestureDetector;

public class ScaleGestureHandler extends ScaleGestureDetector.SimpleOnScaleGestureListener {

    private final HINTVIEWView view;

    public ScaleGestureHandler(HINTVIEWView view) {
        super();
        this.view = view;
    }

    @Override
    public boolean onScaleBegin(ScaleGestureDetector detector) {
        if (view.TeXzoom)
            view.fileRenderer.zoomBegin();
              return true;
    }
    @Override
    public void onScaleEnd(ScaleGestureDetector detector) {
        if (view.TeXzoom) {
            HINTVIEWView.scale *= view.fileRenderer.zoomEnd();;
            view.requestRender();
        }
    }
    @Override
    public boolean onScale(ScaleGestureDetector detector) {
        float f = detector.getScaleFactor();
        float x = detector.getFocusX();
        float y = detector.getFocusY();

        if (view.TeXzoom)
            view.fileRenderer.zoom(f,x,y);
        else
            HINTVIEWView.scale *= f;

        view.requestRender();

        return true;
    }
}
