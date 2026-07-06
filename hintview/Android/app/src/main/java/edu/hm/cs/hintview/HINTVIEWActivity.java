
package edu.hm.cs.hintview;

import android.app.SearchManager;
import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.content.SharedPreferences;
import android.content.res.Configuration;
import android.graphics.Rect;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.WindowInsets;
import android.app.Dialog;
import android.view.WindowInsetsController;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.view.View.OnClickListener;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.SearchView;
import android.widget.TextView;
import android.text.method.LinkMovementMethod;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.content.ContextCompat;
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

        // Load preferences
        sharedPref = this.getPreferences(Context.MODE_PRIVATE);
        String fileUriStr = sharedPref.getString("fileURI", null);
        long filePos = sharedPref.getLong("curPos", 0);
        double scale = sharedPref.getFloat("textSize", (float) 1.0);
        darkMode = sharedPref.getBoolean("darkMode", false);

        mView = findViewById(R.id.hintview);
        mView.init();
        mView.setScale(scale);
        mView.setMode(darkMode);

	    // Handle incoming tap (Intent)
        Intent intent = getIntent();
        boolean intentHandled = false;
        if (intent != null && (Intent.ACTION_VIEW.equals(intent.getAction()) || Intent.ACTION_SEND.equals(intent.getAction()))) {
            intentHandled = handleIntent(intent);
        }

        // Fallback to SharedPreferences if no intent was handled
        if (!intentHandled)
	{ if (fileUriStr==null)
	     openFileChooser();
	  else
	  {
	    try {
            mView.setFile(fileUriStr, filePos);
            } catch (SecurityException e) {
              openFileChooser();
            }
	  }
	}
	
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
                toolbar.setPadding(
                        padding.left + insets.getInsets(WindowInsets.Type.systemBars()).left,
                        padding.top + insets.getInsets(WindowInsets.Type.systemBars()).top,
                        padding.right + insets.getInsets(WindowInsets.Type.systemBars()).right,
                        padding.bottom
                );
                return insets;
            }
        });
       //Log.w(TAG, "onCreate URI= " + fileUriStr);
    }

    @Override
    protected void onNewIntent(Intent intent) {
        super.onNewIntent(intent);
        setIntent(intent);
        handleIntent(intent);
    }

    private boolean handleIntent(Intent intent) {
        Uri uri = null;
        if (Intent.ACTION_VIEW.equals(intent.getAction())) {
            uri = intent.getData();
        } else if (Intent.ACTION_SEND.equals(intent.getAction())) {
            uri = intent.getParcelableExtra(Intent.EXTRA_STREAM);
        }

        if (uri != null) {
            try {
                if ("content".equals(uri.getScheme())) {
                    try {
                        getContentResolver().takePersistableUriPermission(uri, Intent.FLAG_GRANT_READ_URI_PERMISSION);
                    } catch (SecurityException e) {
                        // Temporary permission only.
                    }
                }
                mView.setFile(uri.toString(), 0);
                return true;
            } catch (Exception e) {
                Log.e(TAG, "Error handling intent", e);
            }
        }
        return false;
    }

    public static void hideToolbar(View view, boolean toolbarVisible) {
        toolbar.setTranslationY(toolbarVisible ? 0 : -toolbar.getHeight());
        toolbar.requestTransparentRegion(toolbar);
        WindowInsetsController windowInsetsController = view.getWindowInsetsController();
        if (!toolbarVisible) {
            windowInsetsController.hide(WindowInsets.Type.systemBars() | WindowInsets.Type.displayCutout());
        } else {
            windowInsetsController.show(WindowInsets.Type.systemBars());
        }
    }

    void setToolbar(boolean darkMode) {
        int toolbar_color = ContextCompat.getColor(mView.getContext(), R.color.toolbar_color);
        int text_color = ContextCompat.getColor(mView.getContext(), R.color.foreground_color);
        int nightModeFlags = mView.getContext().getResources().getConfiguration().uiMode & Configuration.UI_MODE_NIGHT_MASK;

        if (darkMode && (nightModeFlags == Configuration.UI_MODE_NIGHT_NO)) {
            toolbar_color = ContextCompat.getColor(mView.getContext(), R.color.toolbar_dark_color);
            text_color = ContextCompat.getColor(mView.getContext(), R.color.foreground_dark_color);
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

    private void setSearchWidgetColor(final int color) {
        if (searchView != null) {
            MenuItem searchItem = searchMenu.findItem(R.id.search);
            Drawable drawable = searchItem.getIcon();
            if (drawable != null) {
                drawable = DrawableCompat.wrap(drawable);
                DrawableCompat.setTint(drawable.mutate(), color);
                searchItem.setIcon(drawable);
            }
            EditText searchText = (EditText) searchView.findViewById(searchView.getContext().getResources().getIdentifier("android:id/search_src_text", null, null));
            if (searchText != null) {
                searchText.setHintTextColor(color);
                searchText.setTextColor(color);
                searchText.setHighlightColor(color);
                searchText.setLinkTextColor(color);
            }
            String[] iconIds = {"android:id/search_go_btn", "android:id/search_close_btn", "android:id/search_mag_icon", "android:id/search_button", "android:id/search_voice_btn"};
            for (String id : iconIds) {
                ImageView icon = (ImageView) searchView.findViewById(searchView.getContext().getResources().getIdentifier(id, null, null));
                if (icon != null) icon.setColorFilter(color);
            }
        }
    }

    @Override
    protected void onSaveInstanceState(@NonNull Bundle outState) {
        super.onSaveInstanceState(outState);
        outState.putBoolean("toolbarVisible", toolbar.getTranslationY() >= 0);
        outState.putBoolean("darkMode", darkMode);
    }

    @Override
    protected void onRestoreInstanceState(final Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);
        new Handler(Looper.getMainLooper()).postDelayed(new Runnable() {
            @Override
            public void run() {
                hideToolbar(mView, savedInstanceState.getBoolean("toolbarVisible"));
                darkMode = savedInstanceState.getBoolean("darkMode");
            }
        }, 80);
    }

    @Override
    protected void onPause() {
        super.onPause();
        if (mView != null)
            mView.onPause();
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
        editor.putString("fileURI", mView.getFileUriStr());
        editor.putLong("curPos", mView.getPos());
        editor.putFloat("textSize", (float) HINTVIEWView.scale);
        editor.putBoolean("darkMode", mView.getMode());
        editor.apply();
        //Log.d(TAG,"onStop\n");
    }

    @Override
    public boolean onPrepareOptionsMenu(Menu menu) {
        MenuItem checkable = menu.findItem(R.id.dark);
        if (checkable != null) checkable.setChecked(darkMode);
        return super.onPrepareOptionsMenu(menu);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        searchMenu = menu;
        new MenuInflater(this).inflate(R.menu.hintview_menu, menu);
        SearchManager searchManager = (SearchManager) getSystemService(Context.SEARCH_SERVICE);
        searchView = (SearchView) menu.findItem(R.id.search).getActionView();
        searchView.setSearchableInfo(searchManager.getSearchableInfo(getComponentName()));
        searchView.setSubmitButtonEnabled(true);

        searchView.setOnQueryTextListener(new SearchView.OnQueryTextListener() {
            @Override
            public boolean onQueryTextChange(String query) {
                mView.setQueryString(query);
                mView.requestRender();
                return true;
            }
            @Override
            public boolean onQueryTextSubmit(String query) {
                HINTVIEWView.Search_next = true;
                mView.requestRender();
                ((InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE)).hideSoftInputFromWindow(mView.getWindowToken(), 0);
                return true;
            }
        });
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
                HINTVIEWView.clearFonts = true;
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
                @Override public void run() { hideToolbar(mView, false); }
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
            Log.e(TAG, "No file chooser found", e);
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == FILE_CHOOSER_REQUEST_CODE && resultCode == RESULT_OK && data != null) {
            try {
                //check if file is accessible
                //getContentResolver().openInputStream(data.getData()).close();
                getContentResolver().takePersistableUriPermission(data.getData(), Intent.FLAG_GRANT_READ_URI_PERMISSION);
                mView.setFile(data.getData().toString(), 0);
            } catch (Exception e) {
               //Log.e(TAG,"Exception in openFileChooser");
                openFileChooser();
            }
        }
    }
}
