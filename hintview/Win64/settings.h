#ifndef _SETTINGS_H_
#define _SETTINGS_H_

extern double gamma;
extern int dark;
extern enum units unit;

INT_PTR CALLBACK    
SettingsDialogProc( HWND hDlg, UINT message, WPARAM wparam, LPARAM lparam );

#endif