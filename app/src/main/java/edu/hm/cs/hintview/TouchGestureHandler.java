package edu.hm.cs.hintview;

//import android.util.Log;
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
    public boolean onFling(MotionEvent start, MotionEvent end, float vx, float vy) {
        float deltaX = start.getX() - end.getX();
        float deltaY = start.getY() - end.getY();

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
        } else if (Math.abs(deltaY) > SWIPE_THRESHOLD && Math.abs(deltaX)<Math.abs(deltaY)/2) {
            if (deltaY > 0) {
                // Swipe down
                //Log.w(TAG, String.format("Up (%f/%f)", deltaX, deltaY));
                HINTVIEWActivity.hideToolbar(view, false);
            } else {
                //Log.w(TAG, String.format("Down (%f/%f)", deltaX, deltaY));
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
    @Override
    public boolean onSingleTapUp(MotionEvent e)
    { float x=e.getX(0);
      float y=e.getY(0);
      HINTVIEWLib.singleTap(x,y,view.scale*view.xdpi,view.scale*view.ydpi);
      view.requestRender();
      return true;
    }
}
