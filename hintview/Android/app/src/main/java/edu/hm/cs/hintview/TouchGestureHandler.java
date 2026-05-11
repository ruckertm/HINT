package edu.hm.cs.hintview;

import android.util.Log;
import android.view.GestureDetector;
import android.view.MotionEvent;

public class TouchGestureHandler extends GestureDetector.SimpleOnGestureListener {
    private static String TAG = "TouchGestureDetector";

    private final HINTVIEWView view;
    private final int SWIPE_THRESHOLD = 100;
    private static final int SWIPE_THRESHOLD_VELOCITY = 100;

    TouchGestureHandler(HINTVIEWView view) {
        this.view = view;
    }

    @Override
    public boolean onDown(MotionEvent e) {
        return super.onDown(e);
    }

    @Override
    public boolean onSingleTapUp(MotionEvent e)
    { super.onSingleTapUp(e);
        float x=e.getX(0);
        float y=e.getY(0);
        Log.w(TAG, String.format("onSingleTap (%f/%f)", x, y));
        if (HINTVIEWLib.singleTap(x,y,view.scale*view.xdpi,view.scale*view.ydpi)) {
            view.requestRender();
            view.performClick();
            return true;
        }
        return false;
    }

    @Override
    public boolean onScroll(MotionEvent start, MotionEvent end, float distanceX, float distanceY) {
        float deltaX = start.getX() - end.getX();
        float y = start.getY();
        float deltaY = y - end.getY();
        int height;
        Log.w(TAG, String.format("onScroll %f (%f/%f)", y, deltaX, deltaY));

        if (Math.abs(deltaY) < SWIPE_THRESHOLD/2 ) // movement too small
        {
            Log.w(TAG, String.format("Small %f (%f/%f)", y, deltaX, deltaY));
            return false;
        }
        if ( Math.abs(deltaX)/2>Math.abs(deltaY)) // not vertical enough
        {
            Log.w(TAG, String.format("Horizontal %f (%f/%f)", y, deltaX, deltaY));
            return false;
        }

        height = view.getHeight();
        if (y > height / 3.0 && y < height *2.0/3.0) /* starts in the middle */
        {
            Log.w(TAG, String.format("Middle %f (%f/%f)", y, deltaX, deltaY));
            return false;
        }
        if (y < height / 3.0 && deltaY > 0 || y > height *2.0/ 3.0 && deltaY < 0) {
                // Swipe down
                Log.w(TAG, String.format("Out (%f/%f)", deltaX, deltaY));
                HINTVIEWActivity.hideToolbar(view, false);
            } else if (y < height / 3.0 && deltaY < 0 || y > height *2.0/ 3.0 && deltaY > 0) {
                Log.w(TAG, String.format("In (%f/%f)", deltaX, deltaY));
                HINTVIEWActivity.hideToolbar(view, true);
            }
        return true;

    }

    @Override
    public boolean onFling(MotionEvent start, MotionEvent end, float vx, float vy) {
        float deltaX = start.getX() - end.getX();
        float y = start.getY();
        float deltaY = y - end.getY();
        Log.w(TAG, String.format("onFling (%f/%f)", deltaX, deltaY));
        if (Math.abs(deltaX) > SWIPE_THRESHOLD && Math.abs(deltaY)<Math.abs(deltaX)/2) {
            if (deltaX > 0) {
                // Swipe to right
                //Log.w(TAG, String.format("Right (%f/%f)", deltaX, deltaY));
                HINTVIEWView.Page_next=true;
                view.requestRender();
            } else {
                // Swipe to left
                //Log.w(TAG, String.format("Left (%f/%f)", deltaX, deltaY));
                HINTVIEWView.Page_prev=true;
                view.requestRender();
            }
            return true;
        }
      return false;
    }

}
