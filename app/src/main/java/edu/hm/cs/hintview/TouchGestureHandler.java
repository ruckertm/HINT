package edu.hm.cs.hintview;

import android.view.GestureDetector;
import android.view.MotionEvent;

public class TouchGestureHandler extends GestureDetector.SimpleOnGestureListener {

    private final HINTVIEWView view;
    private final int SWIPE_THRESHOLD = 100;
    private static final int SWIPE_THRESHOLD_VELOCITY = 100;

    TouchGestureHandler(HINTVIEWView view) {
        this.view = view;
    }

    @Override
    public boolean onFling(MotionEvent start, MotionEvent end, float vx, float vy) {
        float deltaX = start.getX() - end.getX();
        float deltaY = start.getY() - end.getY();

        if (Math.abs(deltaX) > SWIPE_THRESHOLD) {
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
        } else if (Math.abs(deltaY) > SWIPE_THRESHOLD) {
            if (deltaY > 0) {
                // Swipe down
                HINTVIEWActivity.hideToolbar(view, false);
            } else {
                HINTVIEWActivity.hideToolbar(view, true);
            }
            return true;
        }
        return false;
    }

    @Override
    public boolean onDown(MotionEvent e) {
        return super.onDown(e);
    }
}
