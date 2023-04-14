#ifndef _OUTLINE_H_
#define _OUTLINE_H_

extern INT_PTR CALLBACK    
OutlineDialogProc( HWND hDlg, UINT message, WPARAM wparam, LPARAM lparam );
extern void  SetNavigationTree(void);
extern void ClearNavigationTree(void);
#endif