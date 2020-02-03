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

import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.res.Configuration;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.WindowInsets;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import java.io.FileNotFoundException;
import java.io.IOException;

import static edu.hm.cs.hintview.HINTVIEWLib.darkMode;
import static edu.hm.cs.hintview.HINTVIEWLib.lightMode;


public class HINTVIEWActivity extends AppCompatActivity {

    private HINTVIEWView mView;
    private SharedPreferences sharedPref;
    private static final int FILE_CHOOSER_REQUEST_CODE = 0x01;
    private Uri fileURI;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //mView = new HINTVIEWView(getApplication());
        //setContentView(mView);

        setContentView(R.layout.activity_hintview);

        //get shared preferences: file handle, page, scale
        sharedPref = this.getPreferences(Context.MODE_PRIVATE);
        if (sharedPref.getString("fileURI", null) == null) {
            openFileChooser();
            return;
        }
        fileURI = Uri.parse(sharedPref.getString("fileURI", null));
        long curPos = sharedPref.getLong("curPos", 0);
        double scale = sharedPref.getFloat("textSize", (float) 1.0);

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
        mView.init(fileURI);
        HINTVIEWLib.setPos(curPos);
        HINTVIEWView.setScale(scale);
        mView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                hideToolbar(toolbar.getTranslationY() < 0);
            }
        });

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
    protected void onPause() {
        super.onPause();
        if (mView != null) {
            mView.onPause();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        if (mView != null) {
            mView.onResume();
        }
    }

    @Override
    protected void onStop() {
        super.onStop();
        SharedPreferences.Editor editor = sharedPref.edit();
        editor.putString("fileURI", fileURI == null ? null : fileURI.toString());
        editor.putLong("curPos", HINTVIEWLib.getPos());
        editor.putFloat("textSize", (float)HINTVIEWView.getScale());
        editor.apply();
    }

    private boolean isChecked = false;


    @Override
    public boolean onPrepareOptionsMenu(Menu menu) {
        MenuItem checkable = menu.findItem(R.id.dark);
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
                } else {
                    lightMode();
                }
                HINTVIEWLib.change(HINTVIEWView.width, HINTVIEWView.height, HINTVIEWView.scale * HINTVIEWView.xdpi, HINTVIEWView.scale * HINTVIEWView.ydpi);
                HINTVIEWLib.draw();
                isChecked = !item.isChecked();
                item.setChecked(isChecked);
                return true;
            case R.id.fileChooser:
                Log.d("HINTVIEWActivity", "onOptionsItemSelected: File Chooser");
                openFileChooser();
                return true;
            default:
                return false;
        }
    }

    public void openFileChooser() {
        Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
        intent.addCategory(Intent.CATEGORY_OPENABLE);
        intent.setType("*/*");
        try {
            startActivityForResult(intent, FILE_CHOOSER_REQUEST_CODE);
        } catch (ActivityNotFoundException e) {
            Log.e("", "", e);
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == FILE_CHOOSER_REQUEST_CODE && resultCode == RESULT_OK) {
            try {
                //check if file is accessible
                getContentResolver().openInputStream(data.getData()).close();
                fileURI = data.getData();
                //restart activity to render new hint document
                this.recreate();
            } catch (FileNotFoundException e) {
                Log.e("","",e);
                openFileChooser();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

}
