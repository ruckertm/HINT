/* This file is part of HINT
 * Copyright 2017-2021 Martin Ruckert, Hochschule Muenchen, Lothstrasse 64, 80336 Muenchen
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
 * OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Except as contained in this notice, the name of the copyright holders shall
 * not be used in advertising or otherwise to promote the sale, use or other
 * dealings in this Software without prior written authorization from the
 * copyright holders.
 */
#include "basetypes.h"
#include <windows.h>
#include <commctrl.h>
#include "resource.h"
#include "error.h"
#include "winmain.h"
#include "hint.h"

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
