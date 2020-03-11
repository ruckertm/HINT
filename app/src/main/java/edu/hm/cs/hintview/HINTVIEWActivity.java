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

import android.Manifest;
import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.content.res.Configuration;
import android.graphics.Rect;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.os.Handler;
import android.os.Messenger;
import android.print.PrintManager;
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
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.core.graphics.drawable.DrawableCompat;

import java.io.FileNotFoundException;
import java.io.IOException;

import static edu.hm.cs.hintview.HINTVIEWView.*;
import static java.security.AccessController.getContext;

public class HINTVIEWActivity extends AppCompatActivity implements HINTVIEWView.Renderer.RenderErrorCallback {

    private HINTVIEWView mView;
    private static Toolbar toolbar;

    private SharedPreferences sharedPref;
    private boolean darkMode = false;
    private boolean TeXzoom = false;


    private static final int MY_PERMISSIONS_REQUEST_READ_EXTERNAL_STORAGE = 2;
    private static final int FILE_CHOOSER_REQUEST_CODE = 0x01;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        //check if storage permissions are there
        if (ContextCompat.checkSelfPermission(this,
                Manifest.permission.READ_EXTERNAL_STORAGE)
                != PackageManager.PERMISSION_GRANTED) {
            final int MY_PERMISSIONS_REQUEST_READ_EXTERNAL_STORAGE = 2;
            ActivityCompat.requestPermissions(this,
                    new String[]{Manifest.permission.READ_EXTERNAL_STORAGE},
                    MY_PERMISSIONS_REQUEST_READ_EXTERNAL_STORAGE);
        }

        setContentView(R.layout.activity_hintview);

        //get shared preferences: file, pos, scale, mode
        sharedPref = this.getPreferences(Context.MODE_PRIVATE);
        String fileUriStr = sharedPref.getString("fileURI", null);
        long filePos;
        if (fileUriStr == null)
            filePos = 0;
        else
            filePos = sharedPref.getLong("curPos", 0);
        double scale = sharedPref.getFloat("textSize", (float) 1.0);
        darkMode = sharedPref.getBoolean("darkMode", false);

        mView = findViewById(R.id.hintview);
        mView.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                //Gesture Handlers in HINTVIEWView are taking care of touchEvents
                //  hideToolbar(mView, toolbar.getTranslationY() < 0);
            }
        });


        mView.init();
        try {
            mView.setFile(fileUriStr, filePos);
        } catch (java.lang.SecurityException e) {
            openFileChooser();
        }
        mView.setScale(scale);
        mView.setMode(darkMode);
        mView.setZoom(TeXzoom);

        toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        setToolbar(darkMode);

        findViewById(R.id.root).setOnApplyWindowInsetsListener(new View.OnApplyWindowInsetsListener() {

            Rect padding = null;

            @Override
            public WindowInsets onApplyWindowInsets(View v, WindowInsets insets) {
                if (padding == null) {
                    padding = new Rect(toolbar.getPaddingStart(),
                            toolbar.getPaddingTop(),
                            toolbar.getPaddingEnd(),
                            toolbar.getPaddingBottom());
                }
                toolbar.setPadding(padding.left + insets.getSystemWindowInsetLeft(),
                        padding.top + insets.getSystemWindowInsetTop(),
                        padding.right + insets.getSystemWindowInsetRight(),
                        padding.bottom);

                return insets;
            }
        });

        Log.w("HINTVIEWActivity", "onCreate URI= " + fileUriStr);
        if (fileUriStr == null) openFileChooser();
    }

    public static void hideToolbar(View view, boolean toolbarVisible) {
        toolbar.setTranslationY(toolbarVisible ? 0 : -toolbar.getHeight());
        Log.w("HINTVIEWActivity", "toolbar translation " + toolbar.getTranslationY());
        toolbar.requestTransparentRegion(toolbar);
        // hide Nav- & Status-bar
        view.setSystemUiVisibility(toolbarVisible ?
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

    void setToolbar(boolean darkMode) {
        int toolbar_color = mView.getContext().getResources().getColor(R.color.toolbar_color);
        int text_color = mView.getContext().getResources().getColor(R.color.foreground_color);
        int nightModeFlags = mView.getContext().getResources().getConfiguration().uiMode &
                Configuration.UI_MODE_NIGHT_MASK;

        if (darkMode && (nightModeFlags == Configuration.UI_MODE_NIGHT_NO)) {
            toolbar_color = mView.getContext().getResources().getColor(R.color.toolbar_dark_color);
            text_color = mView.getContext().getResources().getColor(R.color.foreground_dark_color);
        }

        toolbar.setBackgroundColor(toolbar_color);
        toolbar.setTitleTextColor(text_color);
        setOverflowButtonColor(text_color);

        //toolbar.bringToFront();
    }

    private void setOverflowButtonColor(final int color) {
        Drawable drawable = toolbar.getOverflowIcon();
        if (drawable != null) {
            drawable = DrawableCompat.wrap(drawable);
            DrawableCompat.setTint(drawable.mutate(), color);
            toolbar.setOverflowIcon(drawable);
        }
    }


    @Override
    protected void onSaveInstanceState(@NonNull Bundle outState) {
        super.onSaveInstanceState(outState);
        outState.putBoolean("toolbarVisible", toolbar.getTranslationY() >= 0);
        outState.putBoolean("darkMode", darkMode);
        outState.putBoolean("TeXzoom", TeXzoom);
        Log.d("HINTVIEWActivity", "toolbarVisible: " + (toolbar.getTranslationY() >= 0));
    }

    @Override
    protected void onRestoreInstanceState(final Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);

        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                final boolean toolbarVisible = savedInstanceState.getBoolean("toolbarVisible");
                darkMode = savedInstanceState.getBoolean("darkMode");
                TeXzoom = savedInstanceState.getBoolean("TeXzoom");
                mView.setZoom(TeXzoom);
                hideToolbar(mView, toolbarVisible);
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
            mView.requestRender();
        }
    }

    @Override
    protected void onStop() {
        super.onStop();
        SharedPreferences.Editor editor = sharedPref.edit();
        String fileUriStr = mView.getFileUriStr();
        editor.putString("fileURI", fileUriStr);
        long filePos = mView.getPos();
        editor.putLong("curPos", filePos);
        editor.putFloat("textSize", (float) mView.getScale());
        editor.putBoolean("darkMode", mView.getMode());
        editor.apply();
        Log.d("HINTVIEWActivity", "onStop pos = " + Long.toHexString(filePos));
    }


    @Override
    public boolean onPrepareOptionsMenu(Menu menu) {
        MenuItem checkable;
        checkable = menu.findItem(R.id.dark);
        checkable.setChecked(darkMode);
        checkable = menu.findItem(R.id.zoom);
        checkable.setChecked(TeXzoom);
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
            case R.id.zoom:
                TeXzoom = !item.isChecked();
                Log.d("HINTVIEWActivity", "onOptionsItemSelected: TeXzoom=" + TeXzoom);
                mView.setZoom(TeXzoom);
                item.setChecked(TeXzoom);
                return true;
            case R.id.dark:
                darkMode = !item.isChecked();
                Log.d("HINTVIEWActivity", "onOptionsItemSelected: dark=" + darkMode);
                mView.setMode(darkMode);
                item.setChecked(darkMode);
                setToolbar(darkMode);
                mView.requestRender();
                return true;
            case R.id.fileChooser:
                Log.d("HINTVIEWActivity", "onOptionsItemSelected: File Chooser");
                openFileChooser();
                return true;
            case R.id.toHome:
                Log.d("HINTVIEWActivity", "to first page");
                HINTVIEWLib.home();
                mView.requestRender();
                return true;
            case R.id.scaleOne:
                Log.d("HINTVIEWActivity", "scale one");
                mView.setScale(1.0);
                mView.requestRender();
                return true;
            case R.id.print:
                Log.d("HINTVIEWActivity", "print");
                doPrint();
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

    private void doPrint() {
        // Get a PrintManager instance
        PrintManager printManager = (PrintManager) getSystemService(Context.PRINT_SERVICE);

        // Set job name, which will be displayed in the print queue
        String jobName = getString(R.string.hintview_activity) + "_" + mView.getFileUriStr();

        PrintHintDocumentAdapter adapter = new PrintHintDocumentAdapter(mView.getFileUriStr());

        // Start a print job, passing in a PrintDocumentAdapter implementation
        // to handle the generation of a print document
        printManager.print(jobName, adapter, null); //
    }


    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == FILE_CHOOSER_REQUEST_CODE && resultCode == RESULT_OK) {
            try {
                //check if file is accessible
                getContentResolver().openInputStream(data.getData()).close();
                mView.setFile(data.getData().toString(), 0);
            } catch (FileNotFoundException e) {
                Log.e("", "", e);
                openFileChooser();
            } catch (java.lang.SecurityException e) {
                //no permissions after restart of the device
                openFileChooser();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        if (requestCode == MY_PERMISSIONS_REQUEST_READ_EXTERNAL_STORAGE) {
            // If request is cancelled, the result arrays are empty.
            if (grantResults.length < 1
                    || grantResults[0] != PackageManager.PERMISSION_GRANTED) {
                //continue asking for permissions until granted
                Toast.makeText(this, "Permission required to access files!", Toast.LENGTH_LONG).show();
                try {
                    Thread.sleep(2000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                ActivityCompat.requestPermissions(this,
                        new String[]{Manifest.permission.READ_EXTERNAL_STORAGE},
                        MY_PERMISSIONS_REQUEST_READ_EXTERNAL_STORAGE);
            }
        }
    }

    @Override
    public void renderErrorCallbackOccurred(String errMsg) {
        Toast.makeText(this, errMsg, Toast.LENGTH_LONG).show();
    }
}
