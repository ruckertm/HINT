package edu.hm.cs.hintview;

import android.view.GestureDetector;
import android.view.MotionEvent;

public class TouchGestureHandler extends GestureDetector.SimpleOnGestureListener {

    private final HINTVIEWView view;
    private final int HORIZONTAL_SWIPE_THRESHOLD = 100;

    TouchGestureHandler(HINTVIEWView view) {
        this.view = view;
    }

    @Override
    public boolean onFling(MotionEvent start, MotionEvent end, float v, float v1) {
        float deltaX = start.getX() - end.getX();
        if (Math.abs(deltaX) > HORIZONTAL_SWIPE_THRESHOLD) {
            if (deltaX > 0) {
                // Swipe to right
                HINTVIEWLib.next();
                view.requestRender();
            } else {
                // Swipe to left
                HINTVIEWLib.prev();
                view.requestRender();
            }
            return true;
        }
        return false;
    }
}
