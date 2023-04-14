#include "basetypes.h"
#include <windows.h>
#include <commctrl.h>
#include "resource.h"
#include "error.h"
#include "winmain.h"
#include "hrender.h"
#include "hint.h"

// AddItemToTree - adds items to a tree-view control. 
// Returns the handle to the newly added item. 
// hTV - handle to the tree-view control. 
// title - text of the item to add. 
// depth - level at which to add the item. 

static HWND hTV=NULL;




HTREEITEM AddItemToTree(HTREEITEM hParent, LPSTR title, int i)
{ 
    TVITEM tvi; 
    TVINSERTSTRUCT tvins; 
    HTREEITEM hTVI;

    tvi.mask = TVIF_TEXT | TVIF_PARAM; 
    tvi.pszText = title;  // Set the text of the item. 
    tvi.cchTextMax = sizeof(tvi.pszText)/sizeof(tvi.pszText[0]); 
    tvi.lParam = (LPARAM)i; 

    tvins.item = tvi; 
    tvins.hInsertAfter = TVI_LAST; 
    tvins.hParent = hParent; 
    
    hTVI = (HTREEITEM)SendMessage(hTV, 
                                   TVM_INSERTITEM, 
                                   0,
                                   (LPARAM)(LPTVINSERTSTRUCT)&tvins); 

    return hTVI;
} 


/* Navigation Menu */

int iItem;       /* current Item index */

void makeNavTree(hint_Outline *t, int n, HTREEITEM hParent, int depth)
/* make a menu with all outline items starting at NavItem with depth >=d */
{ HTREEITEM hPrev=TVI_ROOT; /* previous item handle*/
  while (iItem<=n)
  { if (t[iItem].depth==depth) 
    {  hPrev=AddItemToTree(hParent ,t[iItem].title,iItem); 
	   iItem++;
    }
    else if (t[iItem].depth>depth) 
	{ makeNavTree(t,n,hPrev,t[iItem].depth);
    }
	else
	  break;
  }
}

void ClearNavigationTree(void)
{ if (hTV==NULL) return;
  if (TreeView_GetCount(hTV)>0) 
	TreeView_DeleteAllItems(hTV); 
}

void  SetNavigationTree(void)
{ int n;
  hint_Outline *t;	  
  if (hTV==NULL) return;
  ClearNavigationTree();
  n=hint_get_outline_max();
  if (n<0) return;
  t=hint_get_outlines();
  if (t==NULL) return;
  iItem=0;
  makeNavTree(t,n,TVI_ROOT,0);
}



INT_PTR CALLBACK 
OutlineDialogProc( HWND hDlg, UINT msg, WPARAM wparam, LPARAM lparam )
{ static POINTS pt;
  switch ( msg )
  { case WM_INITDIALOG:
    { RECT r;
	  hTV=GetDlgItem(hDlg,IDC_OUTLINE);
	  GetClientRect(hDlg, &r); 
	  MoveWindow(hTV,0,0,r.right,r.bottom,TRUE);
	  SetNavigationTree();
	  TreeView_SelectItem(hTV,NULL);
	}
	  return 0;
	case WM_COMMAND: 
      switch(wparam) 
	  {	case IDCANCEL: 
	      DestroyWindow(hDlg); 
          hOutlineWnd = NULL; 
		  hTV=NULL;
          return TRUE; 
      } 
      break;
	case WM_NOTIFY:
		{ LPNMHDR lpnmh = (LPNMHDR) lparam; 
#if 0
	      if (lpnmh->code == TVN_SELCHANGED )
		  { LPNMTREEVIEW p = (LPNMTREEVIEW) lparam;
			if (p->action==TVC_BYMOUSE|| p->action==TVC_BYKEYBOARD)
			{ hint_outline_page(p->itemNew.lParam);
			  InvalidateRect(hMainWnd,NULL,FALSE);
			}
	         
 	      }
#endif
		  if (lpnmh->code ==  NM_CLICK)
		  {  TVHITTESTINFO ht;
             HTREEITEM htr;

             GetCursorPos(&ht.pt);
			 ScreenToClient(hTV,&ht.pt);
             htr=TreeView_HitTest(hTV,&ht); //here is the object of the leaf that got clicked
             if (ht.flags& TVHT_ONITEMLABEL)
			 { TVITEMEX tvi;
			   tvi.hItem=ht.hItem;
			   tvi.mask=TVIF_PARAM;

			   TreeView_GetItem(hTV,&tvi);
			   hint_outline_page(tvi.lParam);
   			  InvalidateRect(hMainWnd,NULL,FALSE);

			 }
		  }
  		}
	  return 0;
    case WM_SIZE:
	  { int w,h;
	    h=HIWORD(lparam);
		w=LOWORD(lparam);
		MoveWindow(GetDlgItem(hDlg,IDC_OUTLINE),0,0,w,h,TRUE);
	  }
  }
  return FALSE;   
}