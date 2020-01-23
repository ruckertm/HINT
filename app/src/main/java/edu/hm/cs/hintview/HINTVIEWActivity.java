/*
 * Copyright (C) 2007 The Android Open Source Project
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

package edu.hm.cs.hintview;

import android.content.res.Configuration;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewTreeObserver;
import android.view.WindowInsets;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.content.ContextCompat;

import static edu.hm.cs.hintview.HINTVIEWLib.darkMode;
import static edu.hm.cs.hintview.HINTVIEWLib.lightMode;


public class HINTVIEWActivity extends AppCompatActivity {

    HINTVIEWView mView;
    int background_color;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //mView = new HINTVIEWView(getApplication());
        //setContentView(mView);
        setContentView(R.layout.activity_hintview);

        final Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        findViewById(R.id.root).setOnApplyWindowInsetsListener(new View.OnApplyWindowInsetsListener() {
            @Override
            public WindowInsets onApplyWindowInsets(View v, WindowInsets insets) {
                toolbar.setPadding(toolbar.getPaddingStart() + insets.getSystemWindowInsetLeft(),
                        toolbar.getPaddingTop() + insets.getSystemWindowInsetTop(),
                        toolbar.getPaddingEnd() + insets.getSystemWindowInsetRight(),
                        toolbar.getPaddingBottom());

                v.setOnApplyWindowInsetsListener(null);

                return insets;
            }
        });

        mView = findViewById(R.id.hintview);
        mView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                hideToolbar(toolbar.getTranslationY() < 0);
            }
        });

        background_color = mView.getContext().getResources().getColor(R.color.background_color);

        //example on how to get colors of color theme
        //int color = ContextCompat.getColor(this, R.color.toolbar_color);
    }

    void hideToolbar(boolean toolbarVisible) {
        Toolbar toolbar = findViewById(R.id.toolbar);
        toolbar.setTranslationY(toolbarVisible ? 0 : -toolbar.getHeight());
        // hide Nav- & Status-bar
        getWindow().getDecorView().setSystemUiVisibility(toolbarVisible ?
                View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                        | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                        | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN :
                View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                        | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                        | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                        | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION // hide nav bar
                        | View.SYSTEM_UI_FLAG_FULLSCREEN // hide status bar
                        | View.SYSTEM_UI_FLAG_IMMERSIVE
                        | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
    }

    @Override
    protected void onSaveInstanceState(@NonNull Bundle outState) {
        super.onSaveInstanceState(outState);
        Toolbar toolbar = findViewById(R.id.toolbar);
        outState.putBoolean("toolbarVisible", toolbar.getTranslationY() >= 0);
        Log.d("HINTVIEWActivity", "toolbarVisible: " + (toolbar.getTranslationY() >= 0));
    }

    @Override
    protected void onRestoreInstanceState(final Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);

        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                Toolbar toolbar = findViewById(R.id.toolbar);
                final boolean toolbarVisible = savedInstanceState.getBoolean("toolbarVisible");

                hideToolbar(toolbarVisible);
            }
        }, 80);
    }

    @Override
    public void onConfigurationChanged(@NonNull Configuration newConfig) {
        //check if theme is changed
        super.onConfigurationChanged(newConfig);
        /*int background_color = mView.getContext().getResources().getColor(R.color.background_color);

        Log.d("HINTVIEWActivity", "Configuration " + newConfig.toString());
        int currentNightMode = newConfig.uiMode & Configuration.UI_MODE_NIGHT_MASK;
        Log.d("HINTVIEWActivity", "currentNightMode: " + currentNightMode);
        switch (currentNightMode) {
            case Configuration.UI_MODE_NIGHT_NO:
                Log.d("HINTVIEWActivity", "lightMode");
                lightMode();
                break;
            case Configuration.UI_MODE_NIGHT_YES:
                Log.d("HINTVIEWActivity", "darkMode");
                darkMode();
                break;
        }
         //HINTVIEWLib.draw(mView.width, mView.height, mView.scale * mView.xdpi, mView.scale * mView.ydpi, background_color);
*/
        // Checks the orientation of the screen
        /*int background_color = mView.getContext().getResources().getColor(R.color.background_color);
        if (newConfig.orientation == Configuration.ORIENTATION_LANDSCAPE) {
            Log.d("HINTVIEWActivity", "orientation landscape");
            HINTVIEWLib.draw(mView.height, mView.width, mView.scale * mView.ydpi, mView.scale * mView.xdpi, background_color);
        } else if (newConfig.orientation == Configuration.ORIENTATION_PORTRAIT) {
            Log.d("HINTVIEWActivity", "orientation portrait");
            HINTVIEWLib.draw(mView.width, mView.height, mView.scale * mView.xdpi, mView.scale * mView.ydpi, background_color);
        }*/
    }

    @Override
    protected void onPause() {
        super.onPause();
        mView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        mView.onResume();
    }

    private boolean isChecked = false;


    @Override
    public boolean onPrepareOptionsMenu(Menu menu) {
        MenuItem checkable  = menu.findItem(R.id.dark);
        checkable.setChecked(isChecked);
        return super.onPrepareOptionsMenu(menu);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        new MenuInflater(this).inflate(R.menu.hintview_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        super.onOptionsItemSelected(item);
        switch (item.getItemId()) {
            case R.id.dark:
                Log.d("HINTVIEWActivity", "onOptionsItemSelected: dark" + item.isChecked());
                if (item.isChecked()) {
                    darkMode();
                    background_color = (background_color & 0xFF000000) | (~background_color & 0x00FFFFFF);
                }
                else {
                    lightMode();
                    background_color = mView.getContext().getResources().getColor(R.color.background_color);
                }
                HINTVIEWLib.draw(mView.width, mView.height, mView.scale * mView.xdpi, mView.scale * mView.ydpi, background_color);
                isChecked = !item.isChecked();
                item.setChecked(isChecked);
                return true;
            case R.id.item2:
                Log.d("HINTVIEWActivity", "onOptionsItemSelected: Item 2");
                return true;
            default:
                return false;
        }
    }
}
