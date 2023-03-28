#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <gl/gl.h>
#include "basetypes.h"
#include "winmain.h"
#include "error.h"
#include "hrender.h"
#include "glcontext.h"
#include "print.h"


#pragma warning(disable : 4996)

static RECT user_margins={2000,2000,2000,2000}; /* in 1/100 mm */
static POINT papersize={21000,29700}; /* in 1/100 mm */
static HGLOBAL hMode=NULL, hNames=NULL;


void printer_init(void)
{ PAGESETUPDLG psd;    
  ZeroMemory(&psd, sizeof(psd));
  psd.lStructSize = sizeof(psd);
  psd.Flags=PSD_RETURNDEFAULT|PSD_NOWARNING;
  if (PageSetupDlg(&psd)==TRUE) {
	  hMode=psd.hDevMode;
	  hNames=psd.hDevNames;
  }
  else
	  hMode=hNames=NULL;
}

int page_setup(void)
{ PAGESETUPDLG psd;   

ZeroMemory(&psd, sizeof(psd));
psd.lStructSize = sizeof(psd);
psd.hwndOwner   = hMainWnd;
psd.hDevMode    = hMode; 
psd.hDevNames   = hNames; 
psd.Flags       = PSD_INHUNDREDTHSOFMILLIMETERS
 | PSD_DISABLEMARGINS /* dont let the user set margins; determined by HINT */
 | PSD_MARGINS /*  use psd.rtMargins */
 ;
psd.rtMargin.top = user_margins.top;
psd.rtMargin.left = user_margins.left;
psd.rtMargin.right = user_margins.right;
psd.rtMargin.bottom = user_margins.bottom;
psd.ptPaperSize.x = papersize.x;
psd.ptPaperSize.y = papersize.y;

psd.lpfnPagePaintHook = NULL;

if (PageSetupDlg(&psd)==TRUE) {
	user_margins.top=psd.rtMargin.top;
    user_margins.left=psd.rtMargin.left;
    user_margins.right = psd.rtMargin.right;
    user_margins.bottom = psd.rtMargin.bottom;
	papersize.x=psd.ptPaperSize.x;
	papersize.y=psd.ptPaperSize.y;
    hMode=psd.hDevMode;
	hNames=psd.hDevNames;
    // check paper size and margin values here
}
return 1;
}

static PRINTDLG pd;
static POINT size,resolution;
static BOOL start_printer(void)
{ RECT printable,margin;
  DOCINFO di;

  // Initialize PRINTDLG
  ZeroMemory(&pd, sizeof(pd));
  pd.lStructSize = sizeof(pd);
  pd.hwndOwner   = hMainWnd;
  pd.hDevMode    = hMode;     // Don't forget to free or store hDevMode
  pd.hDevNames   = hNames;     // Don't forget to free or store hDevNames
  pd.Flags       = PD_USEDEVMODECOPIESANDCOLLATE | PD_RETURNDC
                | PD_NOSELECTION /* Disables the selection checkbox */
#if 0
				| PD_NOPAGENUMS /* Disables page ranges */
#endif
				| PD_NOCURRENTPAGE; /* disables current page */
  /* pd.nMinPage   = 1;   pd.nMaxPage     = 0xFFFF; not valid because of PD_NOPAGENUMS */
  pd.nCopies     = 1;
  pd.nFromPage = 1;
  pd.nToPage = 1;
  pd.nMinPage = 1;
  pd.nMaxPage = 0xffff;

  if (!PrintDlg(&pd)) return FALSE;

  /* get information about the page */
  hMode=  pd.hDevMode;     
  hNames = pd.hDevNames ;   
  resolution.x = GetDeviceCaps(pd.hDC, LOGPIXELSX);    // dpi in X direction
  resolution.y = GetDeviceCaps(pd.hDC, LOGPIXELSY);    // dpi in Y direction
  size.x = GetDeviceCaps(pd.hDC, PHYSICALWIDTH);   // width of page in pixels
  size.y = GetDeviceCaps(pd.hDC, PHYSICALHEIGHT);  // height of page in pixels
  printable.left = GetDeviceCaps(pd.hDC, PHYSICALOFFSETX); //unprintable pixels
  printable.top = GetDeviceCaps(pd.hDC, PHYSICALOFFSETY); // unprintable pixels
  printable.right=size.x- GetDeviceCaps(pd.hDC, HORZRES)- printable.left;
  printable.bottom=size.y- GetDeviceCaps(pd.hDC, VERTRES)- printable.top;
  margin.left=MulDiv(user_margins.left,resolution.x,2540);
  margin.right=MulDiv(user_margins.right,resolution.x,2540);
  margin.top=MulDiv(user_margins.top,resolution.y,2540);
  margin.bottom=MulDiv(user_margins.bottom,resolution.y,2540);

  margin.left=max(margin.left,printable.left);
  margin.right=max(margin.right,printable.right);
  margin.top=max(margin.top,printable.top);
  margin.bottom=max(margin.bottom,printable.bottom);

  memset( &di, 0, sizeof(DOCINFO) );
  di.cbSize = sizeof(DOCINFO); 
  di.lpszDocName = hin_name;
  di.lpszOutput = (LPTSTR) NULL; 
  di.lpszDatatype = (LPTSTR) NULL; 
  di.fwType = 0; 
  if (StartDoc(pd.hDC, &di) == SP_ERROR) 
    return hint_error("Printer Error","Unable to start printing");
  return TRUE;
}

static void end_printer(void)
{ DeleteDC(pd.hDC);
}

static bool page_before(uint64_t p, uint64_t q)
/* return true if the page position p is before page position q */
{ if ((p&0xffffffff) < (q&0xffffffff)) return true; /* top level before */
  if ((p&0xffffffff) > (q&0xffffffff)) return false; /* top level after */
  if ((p>>32) < (q>>32)) return true; /* offset before */
  return false;
}


int print_pages(void)
{
  uint64_t this_pos, next_pos;
  unsigned int page, first_page, last_page;
  BITMAPINFO bmi;
  unsigned char *bits;
  HBITMAP hBmp=NULL, hOldBmp=NULL;
  HDC hDCPage=NULL;
  if (!start_printer()) goto Error;
  //if (!start_renderer()) goto Error;

  if (pd.Flags & PD_PAGENUMS)
  {	first_page=pd.nFromPage;
    last_page =pd.nToPage;
  }
  else
  { first_page=1;
    last_page=0xffff;
  }
  next_pos=0;
  
  hDCPage= CreateCompatibleDC(pd.hDC);
  memset(&bmi, 0, sizeof(bmi));
  bmi.bmiHeader.biSize=sizeof(bmi.bmiHeader);
  bmi.bmiHeader.biWidth = size.x;
  bmi.bmiHeader.biHeight = size.y;
  bmi.bmiHeader.biPlanes = 1;			/* must be 1 */
  bmi.bmiHeader.biBitCount = 32;
  bmi.bmiHeader.biCompression = BI_RGB;
  hBmp=CreateDIBSection(pd.hDC,&bmi,DIB_RGB_COLORS,&bits,NULL,0);
  hOldBmp = SelectObject(hDCPage, hBmp);

  hint_print_on(size.x, size.y,4*size.x ,4, bits); 
  hint_dark(0);
  hint_gamma(1.0);
  hint_resize(size.x, size.y, resolution.x, resolution.y);
  hint_page_top(0);

  page=1;
  do
  { this_pos=next_pos;
	if (page>=first_page)
	{ if (StartPage(pd.hDC) <= 0) goto Error; 
      hint_render();
	  hint_print(bits);


      if (BitBlt(pd.hDC,0,0,size.x,size.y,hDCPage,0,0,SRCCOPY) == 0) goto Error;
      if (EndPage(pd.hDC) <= 0)  goto Error; 
	}
	next_pos=hint_page_next();
	page++;
  } while (page<=last_page && page_before(this_pos, next_pos));
	
  if (page<=first_page) /* empty document */
  { StartPage(pd.hDC);
    PatBlt(pd.hDC,0,0,size.x,size.y,WHITENESS); 
    EndPage(pd.hDC);
  }
  EndDoc(pd.hDC); 
Error:
  hint_print_off();
  if (hBmp!=NULL)
  { SelectObject(hDCPage, hOldBmp);
    DeleteObject(hBmp);
  }
  if (hDCPage!=NULL) DeleteDC(hDCPage);
  end_printer();
  EnableWindow(hMainWnd, TRUE); 
  return 1;
}