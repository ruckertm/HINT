#ifndef _SEARCH_H_
#define _SEARCH_H_

extern char *search_string;
extern int search_length;

INT_PTR CALLBACK    
SearchDialogProc( HWND hDlg, UINT message, WPARAM wparam, LPARAM lparam );

#endif