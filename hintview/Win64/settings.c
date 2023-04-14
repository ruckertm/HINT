#include "basetypes.h"
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <math.h>
#include "resource.h"
#include "format.h"
#include "hrender.h"
#include "winmain.h"
#include "hint.h"


extern int round_to_pixel_h, round_to_pixel_v, to_nearest;
extern double pixel_size_threshold;
double gamma=2.2;

#pragma warning( disable : 4996 4100)

#define emergency_stretch	dimen_def[emergency_stretch_no]
#define pretolerance integer_def[pretolerance_no]
#define tolerance integer_def[tolerance_no]


enum units {mm=0,in=1,pt=2,pc=3,px=4} unit;
#define MAXUNIT (px+1)
const char unitstr[MAXUNIT][3]={"mm","in","pt","pc","px"};
double sp2unit[MAXUNIT] ={25.4/(72.27*0x10000),1.0/(72.27*0x10000),1.0/0x10000,1.0/(12.0*0x10000),100.0/(72.27*0x10000)  }; /*convert scaled points to unit */
enum units unit=mm;


static double GetDlgItemDouble(HWND hDlg,UINT DlgItem)
{ char c[20];
  GetDlgItemText(hDlg,DlgItem,c,20);
  return atof(c);
}
static double SetDlgItemDouble(HWND hDlg,UINT DlgItem, double x)
{ char c[20];
   _snprintf(c,20,"%0.3f",x);
  SetDlgItemText(hDlg,DlgItem,c);
  return atof(c);
}

void set_unit( HWND hDlg, int i)
{ double x;
   if (i<0 || i>=MAXUNIT) i=0;
   x = GetDlgItemDouble(hDlg,IDC_HSIZE);
   SetDlgItemDouble(hDlg,IDC_HSIZE,sp2unit[i]*x/sp2unit[unit]);
   x = GetDlgItemDouble(hDlg,IDC_VSIZE);
   SetDlgItemDouble(hDlg,IDC_VSIZE,sp2unit[i]*x/sp2unit[unit]);
   x = GetDlgItemDouble(hDlg,IDC_ESSIZE);
   SetDlgItemDouble(hDlg,IDC_ESSIZE,sp2unit[i]*x/sp2unit[unit]);
   x = GetDlgItemDouble(hDlg,IDC_PXSIZE);
   SetDlgItemDouble(hDlg,IDC_PXSIZE,sp2unit[i]*x/sp2unit[unit]);
   unit=i;
   SetDlgItemText(hDlg,IDC_HUNIT,unitstr[unit]);
   SetDlgItemText(hDlg,IDC_VUNIT,unitstr[unit]);
   SetDlgItemText(hDlg,IDC_TUNIT,unitstr[unit]);
   SetDlgItemText(hDlg,IDC_ESUNIT,unitstr[unit]);
}

void adjust_client_size(HWND hDlg)
{ double x, y;
  int w, h;
  x = GetDlgItemDouble(hDlg,IDC_HSIZE);
  x = x/sp2unit[unit];
  x = x*sp2unit[px];
  w= round(x);

  y = GetDlgItemDouble(hDlg,IDC_VSIZE);
  y = y/sp2unit[unit];
  y = y*sp2unit[px];
  h= round(y);

  SetDlgItemInt(hDlg,IDC_PX,w,FALSE);
  SetDlgItemInt(hDlg,IDC_PY,h,FALSE);
}

INT_PTR CALLBACK 
SettingsDialogProc( HWND hDlg, UINT msg, WPARAM wparam, LPARAM lparam )
{ static int size_change=0;
  switch ( msg )
  { case WM_INITDIALOG:
	  SetDlgItemInt(hDlg,IDC_PX,client_width,FALSE);
      SetDlgItemInt(hDlg,IDC_PY,client_height,FALSE);
	  SetDlgItemDouble(hDlg,IDC_XDPI,dpi_x);
	  SetDlgItemDouble(hDlg,IDC_YDPI,dpi_y);
	  sp2unit[px]=(dpi_x+dpi_y)/(2*72.27*0x10000);
	  { int i;
        for (i=0;i<MAXUNIT;i++)
        SendMessage(GetDlgItem(hDlg,IDC_UNITS),CB_ADDSTRING,0,(LPARAM)unitstr[i]);
	  }
	  set_unit(hDlg,unit);
	  SendMessage(GetDlgItem(hDlg,IDC_UNITS),CB_SETCURSEL,unit,0);
	  SetDlgItemDouble(hDlg,IDC_HSIZE,sp2unit[unit]*page_h);
      SetDlgItemDouble(hDlg,IDC_VSIZE,sp2unit[unit]*page_v);
	  if (dimen_def!=NULL)
     	SetDlgItemDouble(hDlg,IDC_ESSIZE,sp2unit[unit]*emergency_stretch);
	  if (integer_def!=NULL)
	  { SetDlgItemInt(hDlg,IDC_TOLERANCE,tolerance,FALSE);
	    SetDlgItemInt(hDlg,IDC_PRETOLERANCE,pretolerance,FALSE);
	  }
      SetDlgItemDouble(hDlg,IDC_PXSIZE,sp2unit[unit]*pixel_size_threshold*ONE);
      SendMessage(GetDlgItem(hDlg,IDC_ROUND_TO_PIXEL_H),BM_SETCHECK,
		  round_to_pixel_h?BST_CHECKED:BST_UNCHECKED,0);
      SendMessage(GetDlgItem(hDlg,IDC_ROUND_TO_PIXEL_V),BM_SETCHECK,
		  round_to_pixel_v?BST_CHECKED:BST_UNCHECKED,0);
	  SendMessage(GetDlgItem(hDlg,IDC_TO_NEAREST),BM_SETCHECK,
		  to_nearest?BST_CHECKED:BST_UNCHECKED,0);

	  /* Slider for Gamma */
#define SLIDER_MAX 30 /* slider positions from 0 to MAX_SLIDER */
#define SLIDER_ONE 18 /* slider position for gamma = 1.0 */
#define SLIDER_STEP 4 /* slider steps to double/half gamma */
	  SendMessage(GetDlgItem(hDlg,IDC_GAMMA),TBM_SETRANGE,TRUE,MAKELONG(0,SLIDER_MAX));
	  SendMessage(GetDlgItem(hDlg,IDC_GAMMA),TBM_SETTIC,0,SLIDER_ONE);
	  { double lg=SLIDER_STEP*log(gamma)/log(2.0);
		int pos = floor(SLIDER_ONE+lg);
	    if (pos <0) pos=0;
	    SendMessage(GetDlgItem(hDlg,IDC_GAMMA),TBM_SETPOS,TRUE,pos);
        SendDlgItemMessage(hDlg,IDC_SPIN_GAMMA,UDM_SETBUDDY,(WPARAM)GetDlgItem(hDlg,IDC_EDIT_GAMMA),0);
        SendDlgItemMessage(hDlg,IDC_SPIN_GAMMA,UDM_SETRANGE,0, MAKEWPARAM(400,1));
		SetDlgItemDouble(hDlg,IDC_EDIT_GAMMA,gamma);
	  }
      return TRUE;
    case WM_SYSCOMMAND:
      if( wparam == SC_CLOSE ) 
      { EndDialog(hDlg, FALSE);
        return TRUE;
      }
      break;
	case WM_HSCROLL:
	{ int pos;
      if (LOWORD(wparam)==SB_THUMBTRACK )
	    pos = HIWORD(wparam);
	  else
	    pos = SendMessage((HWND)lparam,TBM_GETPOS,0,0);
	  //SetDlgItemInt(hDlg,IDC_TOLERANCE,pos,TRUE);
	  if (pos==0) gamma=0.0;
	  else gamma=exp((((double)pos-SLIDER_ONE)/SLIDER_STEP)*log(2.0));
	  //SetDlgItemDouble(hDlg,IDC_ESSIZE,gamma);
	  PostMessage(hMainWnd, WM_GAMMA, 0, 0);
	  return TRUE;
    }
    break;
	case WM_NOTIFY:
		
		{ LPNMHDR p = (LPNMHDR)lparam;
		  if (wparam==IDC_EDIT_GAMMA && p->code==NM_KILLFOCUS)
		  { gamma = GetDlgItemDouble(hDlg,IDC_EDIT_GAMMA);
		  		  PostMessage(hMainWnd, WM_GAMMA, 0, 0);

  		   }
		   else if (wparam==IDC_SPIN_GAMMA)
		   { LPNMUPDOWN dp=(LPNMUPDOWN)lparam;
		     gamma = GetDlgItemDouble(hDlg,IDC_EDIT_GAMMA);
		     gamma=gamma+dp->iDelta/100.0;
			 if (gamma<0.01) gamma=0.01;
			 else if (gamma>4.0) gamma=4.0;
    	     SetDlgItemDouble(hDlg,IDC_EDIT_GAMMA,gamma);
		     PostMessage(hMainWnd, WM_GAMMA, 0, 0);
		   }
		}
		return 0;

    case WM_COMMAND:
	  if (LOWORD(wparam) == IDC_UNITS && HIWORD(wparam)==CBN_SELENDOK)
	  { set_unit(hDlg, (int)SendMessage(GetDlgItem(hDlg,IDC_UNITS),CB_GETCURSEL,0,0));
	    
	  }
      else if(HIWORD (wparam) == EN_SETFOCUS)
	  { if (LOWORD(wparam) == IDC_HSIZE || LOWORD(wparam) == IDC_VSIZE)
	        size_change=0;
           return 0;      
      }
      else if(HIWORD (wparam) == EN_CHANGE)
	  { if (LOWORD(wparam) == IDC_HSIZE || LOWORD(wparam) == IDC_VSIZE)
		   size_change=1;
           return 0;      
      }
      else if(HIWORD (wparam) == EN_KILLFOCUS)
	  { if (LOWORD(wparam) == IDC_HSIZE || LOWORD(wparam) == IDC_VSIZE)
	    { if (size_change)
		  { adjust_client_size(hDlg);
		    size_change=0;
	      }
	    }
	    else if (LOWORD(wparam) == IDC_EDIT_GAMMA)
	    { gamma = GetDlgItemDouble(hDlg,IDC_EDIT_GAMMA);
     	  if (gamma<0.01) { gamma=0.01; SetDlgItemDouble(hDlg,IDC_EDIT_GAMMA,gamma);}
	      else if (gamma>4.0) {gamma=4.0; SetDlgItemDouble(hDlg,IDC_EDIT_GAMMA,gamma);}
		  PostMessage(hMainWnd, WM_GAMMA, 0, 0);
	    }
  	    return 0;      
	  }
	  if(HIWORD (wparam) == BN_CLICKED)
	  { if( LOWORD(wparam) == IDOK )
        { BOOL result=FALSE;
	    int a, v, h, t=0, b=0, l=0, r=0;
		double d;

        d = GetDlgItemDouble(hDlg,IDC_HSIZE);
		d = d/sp2unit[unit];
		h = round(d);
		v = round(GetDlgItemDouble(hDlg,IDC_VSIZE)/sp2unit[unit]);

		if (h!=page_h || v!=page_v ) 
		{page_h=h; page_v=v; result=TRUE; }
	    d=GetDlgItemDouble(hDlg,IDC_XDPI);
		if (d!=dpi_x) { dpi_x=d; result=TRUE; }
	    d=GetDlgItemDouble(hDlg,IDC_YDPI);
		if (d!=dpi_y) { dpi_y=d; result=TRUE; }
		sp2unit[px]=(dpi_x+dpi_y)/(2*72.27*0x10000);
	    a=GetDlgItemInt(hDlg,IDC_PX,NULL,FALSE);
	    b=GetDlgItemInt(hDlg,IDC_PY,NULL,FALSE);
		if (a!=client_width|| b!=client_height)
		{	
			RECT r;
			r.top=r.left=0;
	        r.right=a;
	        r.bottom=b;
	        AdjustWindowRect(&r,WS_TILEDWINDOW ,TRUE);
			SetWindowPos(hMainWnd,HWND_TOPMOST,0,0,r.right-r.left,r.bottom-r.top,SWP_NOMOVE|SWP_NOREDRAW);
			result=FALSE;
		}
		a = round(GetDlgItemDouble(hDlg,IDC_ESSIZE)/sp2unit[unit]);
		if (dimen_def!=NULL && a!=emergency_stretch) 
		{ emergency_stretch=a; 
		  result=TRUE; 
		}
	    a =GetDlgItemInt(hDlg,IDC_TOLERANCE,NULL,FALSE);
		if (integer_def!=NULL&&a!=tolerance) { tolerance=a; result=TRUE; }
		a=GetDlgItemInt(hDlg,IDC_PRETOLERANCE,NULL,FALSE);
		if (integer_def!=NULL && a!=pretolerance ) { pretolerance=a; result=TRUE; }
	    d=GetDlgItemDouble(hDlg,IDC_PXSIZE)/sp2unit[unit]/ONE;
		if (d!=pixel_size_threshold) 
		{  pixel_size_threshold=d; if (round_to_pixel_h||round_to_pixel_v) result=TRUE; }

        EndDialog(hDlg, result);
        return TRUE;
      }
      else if( LOWORD(wparam) == IDCANCEL )
      {
        EndDialog(hDlg, FALSE);
        return TRUE;
      }
	  else if ( LOWORD(wparam) == IDC_ROUND_TO_PIXEL )
	  { int b=SendMessage(GetDlgItem(hDlg,IDC_ROUND_TO_PIXEL),BM_GETCHECK,0,0);
	    if (b==BST_UNCHECKED)
		  round_to_pixel_h=round_to_pixel_v=0;
		else if (b==BST_CHECKED)
		  round_to_pixel_h=round_to_pixel_v=1;
      SendMessage(GetDlgItem(hDlg,IDC_ROUND_TO_PIXEL_H),BM_SETCHECK,
		  round_to_pixel_h?BST_CHECKED:BST_UNCHECKED,0);
      SendMessage(GetDlgItem(hDlg,IDC_ROUND_TO_PIXEL_V),BM_SETCHECK,
		  round_to_pixel_v?BST_CHECKED:BST_UNCHECKED,0);
	    if (round_to_pixel_h||round_to_pixel_v) 
			pixel_size_threshold=GetDlgItemDouble(hDlg,IDC_PXSIZE)/sp2unit[unit]/ONE;
	    InvalidateRect(hMainWnd,NULL,FALSE);
	  }	
	  else if ( LOWORD(wparam) == IDC_ROUND_TO_PIXEL_H )
	  { round_to_pixel_h= BST_CHECKED==SendMessage(GetDlgItem(hDlg,IDC_ROUND_TO_PIXEL_H),BM_GETCHECK,0,0);
	    if (round_to_pixel_h||round_to_pixel_v) 
			pixel_size_threshold=GetDlgItemDouble(hDlg,IDC_PXSIZE)/sp2unit[unit]/ONE;
	    InvalidateRect(hMainWnd,NULL,FALSE);
	  }	
	  else if ( LOWORD(wparam) == IDC_ROUND_TO_PIXEL_V )
	  { round_to_pixel_v= BST_CHECKED==SendMessage(GetDlgItem(hDlg,IDC_ROUND_TO_PIXEL_V),BM_GETCHECK,0,0);
	    if (round_to_pixel_h||round_to_pixel_v) 
			pixel_size_threshold=GetDlgItemDouble(hDlg,IDC_PXSIZE)/sp2unit[unit]/ONE;
	    InvalidateRect(hMainWnd,NULL,FALSE);
	  }	
	  else if ( LOWORD(wparam) == IDC_TO_NEAREST )
	  { to_nearest= BST_CHECKED==SendMessage(GetDlgItem(hDlg,IDC_TO_NEAREST),BM_GETCHECK,0,0);
	    hint_clear_fonts(false)	;  
	    InvalidateRect(hMainWnd,NULL,FALSE);
	  }	

     break;
	}
  }
  return FALSE;
}
