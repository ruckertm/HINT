#include "basetypes.h"
#include <windows.h>
#include <commctrl.h>
#include "resource.h"
#include "error.h"
#include "winmain.h"
#include "hrender.h"

char *search_string=NULL;
static int search_max=0;
int search_length=0;

INT_PTR CALLBACK 
SearchDialogProc( HWND hDlg, UINT msg, WPARAM wparam, LPARAM lparam )
{ switch ( msg )
  { case WM_COMMAND: 
    switch(wparam) 
	{ case MAKEWPARAM(IDC_SEARCH,EN_CHANGE): 
	    search_length = (int) SendDlgItemMessage(hDlg,IDC_SEARCH, EM_LINELENGTH,0,0); 
        if (search_length<32) 
		{ if (search_max<32)
		  { search_string=realloc(search_string,32+1);
		    if (search_string==NULL) MESSAGE("Out of memory for search string");
			search_max=32;
		  }
		} 
		else
		{ if (search_length>search_max)
		  { int i= search_length+(search_length/4);
		    search_string=realloc(search_string,i+1);
		    if (search_string==NULL) MESSAGE("Out of memory for search string");
			search_max=i;
		  }
		}
		SendDlgItemMessage(hDlg,IDC_SEARCH,WM_GETTEXT,search_max+1,(LPARAM)search_string); 
		hint_set_mark(search_string,search_length);
        InvalidateRect(hMainWnd,NULL,FALSE);
        return TRUE;
      case MAKEWPARAM(IDC_SEARCH_PREV,BN_CLICKED): 
		  { uint64_t h=hint_page_get();
	        if (!hint_prev_mark())
				hint_page_top(h);
	        InvalidateRect(hMainWnd,NULL,FALSE);
		  }
        return TRUE;
      case MAKEWPARAM(IDC_SEARCH_NEXT,BN_CLICKED): 
        { uint64_t h=hint_page_get();
          if (!hint_next_mark())
			  hint_page_top(h);
	      InvalidateRect(hMainWnd,NULL,FALSE);
		}
        return TRUE;
      case IDCANCEL: 
	    search_length=0;
		hint_set_mark(search_string,search_length);
        InvalidateRect(hMainWnd,NULL,FALSE);
		DestroyWindow(hDlg); 
        hSearchWnd = NULL; 
        return TRUE; 
    } 
    return 0; 
  } 
  return FALSE;   
  UNREFERENCED_PARAMETER(lparam); 
}