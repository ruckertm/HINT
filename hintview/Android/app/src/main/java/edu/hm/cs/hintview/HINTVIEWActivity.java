
package edu.hm.cs.hintview;

import android.app.SearchManager;
import android.content.ActivityNotFoundException;
import android.content.Context;
//import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.res.Configuration;
import android.graphics.Rect;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.os.Handler;

//import android.util.Log;
import android.os.Looper;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.WindowInsets;

import android.app.Dialog;
import android.widget.Button;
import android.view.View.OnClickListener;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.SearchView;
import android.widget.TextView;
import android.text.method.LinkMovementMethod;
//import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.graphics.drawable.DrawableCompat;

import java.io.FileNotFoundException;
import java.io.IOException;


public class HINTVIEWActivity extends AppCompatActivity {
    private static final String TAG = "HINTVIEWActivity";
    private HINTVIEWView mView;
    private static Toolbar toolbar = null;
    private static SearchView searchView = null;
    private static Menu searchMenu = null;
    private SharedPreferences sharedPref;
    private boolean darkMode = false;

    private static final int FILE_CHOOSER_REQUEST_CODE = 0x01;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

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
        } catch (SecurityException e) {
            openFileChooser();
        }
        mView.setScale(scale);
        mView.setMode(darkMode);

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

       //Log.w(TAG, "onCreate URI= " + fileUriStr);
        if (fileUriStr == null)
            openFileChooser();
    }

    public static void hideToolbar(View view, boolean toolbarVisible) {
        toolbar.setTranslationY(toolbarVisible ? 0 : -toolbar.getHeight());
        //Log.w(TAG, "toolbar translation " + toolbar.getTranslationY());
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
        setSearchWidgetColor(text_color);
    }

    private void setOverflowButtonColor(final int color) {
        Drawable drawable = toolbar.getOverflowIcon();
        if (drawable != null) {
            drawable = DrawableCompat.wrap(drawable);
            DrawableCompat.setTint(drawable.mutate(), color);
            toolbar.setOverflowIcon(drawable);
        }
    }

    private void setSearchWidgetColor (final int color) {
        if (searchView != null) {
            MenuItem searchItem = searchMenu.findItem(R.id.search);
            Drawable drawable = searchItem.getIcon();
            if (drawable != null) {
                drawable = DrawableCompat.wrap(drawable);
                DrawableCompat.setTint(drawable.mutate(), color);
                searchItem.setIcon(drawable);
            }

            //drawable.setColorFilter(BlendModeColorFilterCompat.createBlendModeColorFilterCompat(color, BlendModeCompat.SRC_ATOP));
            EditText searchText = (EditText) searchView.findViewById(searchView.getContext()
                    .getResources()
                    .getIdentifier("android:id/search_src_text", null, null));
            //AutoCompleteTextView searchText = (AutoCompleteTextView) searchView.findViewById(R.id.search_src_text);

            if (searchText != null) {
                searchText.setHintTextColor(color);
                searchText.setTextColor(color);
                searchText.setHighlightColor(color);
                searchText.setLinkTextColor(color);
            }

            ImageView searchIcon = (ImageView) searchView.findViewById(searchView.getContext()
                    .getResources()
                    .getIdentifier("android:id/search_go_btn", null, null));

            if (searchIcon != null) {
                searchIcon.setColorFilter(color);
            }
            searchIcon = (ImageView) searchView.findViewById(searchView.getContext()
                    .getResources()
                    .getIdentifier("android:id/search_close_btn", null, null));

            if (searchIcon != null) {
                searchIcon.setColorFilter(color);
            }

            searchIcon = (ImageView) searchView.findViewById(searchView.getContext()
                    .getResources()
                    .getIdentifier("android:id/search_mag_icon", null, null));

            if (searchIcon != null) {
                searchIcon.setColorFilter(color);
            }

            searchIcon = (ImageView) searchView.findViewById(searchView.getContext()
                    .getResources()
                    .getIdentifier("android:id/search_button", null, null));

            if (searchIcon != null) {
                searchIcon.setColorFilter(color);
            }

            searchIcon = (ImageView) searchView.findViewById(searchView.getContext()
                    .getResources()
                    .getIdentifier("android:id/search_voice_btn", null, null));

            if (searchIcon != null) {
                searchIcon.setColorFilter(color);
            }
        }
    }

    @Override
    protected void onSaveInstanceState(@NonNull Bundle outState) {
        super.onSaveInstanceState(outState);
        outState.putBoolean("toolbarVisible", toolbar.getTranslationY() >= 0);
        outState.putBoolean("darkMode", darkMode);
        //Log.d(TAG, "toolbarVisible: " + (toolbar.getTranslationY() >= 0));
    }

    @Override
    protected void onRestoreInstanceState(final Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);

        new Handler(Looper.getMainLooper()).postDelayed(new Runnable() {
            @Override
            public void run() {
                final boolean toolbarVisible = savedInstanceState.getBoolean("toolbarVisible");
                darkMode = savedInstanceState.getBoolean("darkMode");
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
        //Log.d(TAG, "onStop pos = " + Long.toHexString(filePos));
    }


    @Override
    public boolean onPrepareOptionsMenu(Menu menu) {
        MenuItem checkable;
        checkable = menu.findItem(R.id.dark);
        checkable.setChecked(darkMode);
        return super.onPrepareOptionsMenu(menu);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
	 searchMenu = menu;
        new MenuInflater(this).inflate(R.menu.hintview_menu, menu);
        // Associate searchable configuration with the SearchView
        SearchManager searchManager =
                (SearchManager) getSystemService(Context.SEARCH_SERVICE);
        searchView =
                (SearchView) menu.findItem(R.id.search).getActionView();
        searchView.setSearchableInfo(
                searchManager.getSearchableInfo(getComponentName()));
        searchView.setSubmitButtonEnabled(true);

        final SearchView.OnQueryTextListener queryTextListener = new SearchView.OnQueryTextListener() {
            @Override
            public boolean onQueryTextChange(String newText) {
                return true;
            }

            @Override
            public boolean onQueryTextSubmit(String query) {
                mView.setQueryString(query);
                mView.requestRender();
                return true;
            }
        };

        final SearchView.OnCloseListener closeListener = new SearchView.OnCloseListener(){
            @Override
            public boolean onClose() {
                mView.setQueryString(null);
                mView.requestRender();
                return true;
            }
        };

        searchView.setOnQueryTextListener(queryTextListener);
        searchView.setOnCloseListener(closeListener);

        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        boolean hideToolbar = true, success=true;
        super.onOptionsItemSelected(item);

        switch (item.getItemId()) {
            case R.id.about: {
                final Dialog dialog = new Dialog(this);
                //dialog.setCanceledOnTouchOutside(true);
                //dialog.setOnCancelListener(new DialogInterface.OnCancelListener() {
                //    @Override
                //    public void onCancel(DialogInterface dialogInterface) {
                //       dialog.dismiss();
                //    }
                //});
                dialog.setContentView(R.layout.about);
                Button dialogButton = dialog.findViewById(R.id.OKbutton);
                dialogButton.setOnClickListener(new OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        dialog.dismiss();
                    }
                });
                TextView linkTextView = dialog.findViewById(R.id.textView4);
                linkTextView.setMovementMethod(LinkMovementMethod.getInstance());
                dialog.show();
            }
            break;
            case R.id.dark:
                darkMode = !item.isChecked();
                //Log.d(TAG, "onOptionsItemSelected: dark=" + darkMode);
                mView.setMode(darkMode);
                item.setChecked(darkMode);
                setToolbar(darkMode);
                mView.requestRender();
                break;
            case R.id.fileChooser:
                //Log.d(TAG, "onOptionsItemSelected: File Chooser");
                openFileChooser();
                break;
            case R.id.toHome:
                //Log.d(TAG, "to first page");
                HINTVIEWLib.home();
                mView.requestRender();
                break;
            case R.id.scaleOne:
                //Log.d(TAG, "scale one");
                mView.setScale(1.0);
                mView.clearFonts = true;
                mView.requestRender();
                break;
            case R.id.search:
                hideToolbar = false;
                break;
            default:
                success=false;
                break;
        }
        if (hideToolbar) {
            new Handler(Looper.getMainLooper()).postDelayed(new Runnable() {
                @Override
                public void run() {
                    hideToolbar(mView, false);
                }
            }, 80);
        }
        return success;
    }

    public void openFileChooser() {
        Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
        intent.addCategory(Intent.CATEGORY_OPENABLE);
        intent.setType("*/*");
        try {
            startActivityForResult(intent, FILE_CHOOSER_REQUEST_CODE);
        } catch (ActivityNotFoundException e) {
            //Log.e(TAG, "", e);
        }
    }

         @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == FILE_CHOOSER_REQUEST_CODE && resultCode == RESULT_OK) {
            try {
                //check if file is accessible
                getContentResolver().openInputStream(data.getData()).close();
                getContentResolver().takePersistableUriPermission(data.getData(), Intent.FLAG_GRANT_READ_URI_PERMISSION);

                mView.setFile(data.getData().toString(), 0);
            } catch (FileNotFoundException e) {
                //Log.e(TAG, "", e);
                openFileChooser();
            } catch (java.lang.SecurityException e) {
                //no permissions after restart of the device
                openFileChooser();
            } catch (IOException e) {
               //Log.e(TAG,"Exception in openFileChooser");
            }
        }
    }
}
