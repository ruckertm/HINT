#define _WIN32_WINNT  0x501
#include <windows.h>			/* must include this before GL/gl.h */
#include "basetypes.h"
#include "resource.h"
#include "error.h"

#include "winmain.h"
#include "button.h"


#define BWIN_SIZE 40
#define BBORDER_SIZE 2
#define BUTTON_SIZE (BWIN_SIZE-2*BBORDER_SIZE)
#define RIM_SIZE 2
#define BICON_OFFSET (BBORDER_SIZE+RIM_SIZE)
#define BICON_SIZE (BUTTON_SIZE-2*RIM_SIZE)
#define MAX_BUTTON 11

typedef struct {
	int key; 
	bool on; 
	HWND h; /* window handle */
	HDC hDCday,hDCnight;
} button_info;


static button_info bi[MAX_BUTTON]={{0}};
static HDC hDay_on, hDay_off, hNight_on, hNight_off;
static HBRUSH hDayBG, hNightBG;

/* User interface: toolbar */
static LRESULT CALLBACK ButtonProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
    {
    case WM_CREATE:
		{ CREATESTRUCT *p = (LPCREATESTRUCT)lParam;
		  SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)(p->lpCreateParams));
		}
       return 0;
	//case WM_ERASEBKGND:
	//	return 0;
    case WM_LBUTTONDOWN:
		{ button_info *i;
		  i = (button_info *)(LONG_PTR)GetWindowLongPtr(hWnd, GWLP_USERDATA);
          SendMessage(hMainWnd,WM_COMMAND,i->key,0);
		}
       return TRUE;

	case WM_MOUSELEAVE : /* mouse leaves the window */
		{ button_info *i;
		  i = (button_info *)(LONG_PTR)GetWindowLongPtr(hWnd, GWLP_USERDATA);
          i->on=0;
		}
	    InvalidateRect(hWnd,NULL,FALSE);
        return 0;
    case WM_SETCURSOR: /* mouse enters the window */
		if (LOWORD(lParam)== 1)
		{ TRACKMOUSEEVENT mev;
          button_info *i;
		  i = (button_info *)(LONG_PTR)GetWindowLongPtr(hWnd, GWLP_USERDATA);
          i->on=1;
		  InvalidateRect(hWnd,NULL,FALSE);
		  mev.cbSize=sizeof(TRACKMOUSEEVENT);
          mev.hwndTrack=hWnd;
          mev.dwFlags=TME_LEAVE;
          mev.dwHoverTime=0;
          TrackMouseEvent(&mev);
		}
		return 1;

    case WM_PAINT:
	  { PAINTSTRUCT ps;
	  	BLENDFUNCTION bf; 
        button_info *i;
        static int error=0;
        bf.BlendOp = AC_SRC_OVER;
        bf.BlendFlags = 0;
        bf.AlphaFormat = AC_SRC_ALPHA;   
        bf.SourceConstantAlpha = 0xff;  

		i = (button_info *)(LONG_PTR)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        BeginPaint(hWnd, &ps);
        SelectObject(ps.hdc,dark?hNightBG:hDayBG);
		PatBlt(ps.hdc,0,0,BWIN_SIZE,BWIN_SIZE,PATCOPY); /* erase background */
		if (!AlphaBlend(ps.hdc, BBORDER_SIZE, BBORDER_SIZE, BUTTON_SIZE,BUTTON_SIZE,
			dark?(i->on?hNight_on:hNight_off):(i->on?hDay_on:hDay_off), 0, 0, BUTTON_SIZE,BUTTON_SIZE, bf)) /* button face */
          error++;
		if (!AlphaBlend(ps.hdc, BICON_OFFSET, BICON_OFFSET, BICON_SIZE,BICON_SIZE,
			dark?i->hDCnight:i->hDCday, 0, 0, BICON_SIZE,BICON_SIZE, bf)) /* icon */
          error++;
	    EndPaint(hWnd, &ps);
	  }
      return TRUE;
    } 
    return DefWindowProc(hWnd, uMsg, wParam, lParam); 
}

HDC create_face(COLORREF c, BITMAP *bm)
/* given color c and alpha bitmap a return the handle to the device context */
{   unsigned char *alpha=(unsigned char *)(bm->bmBits);
	int dy=bm->bmWidthBytes; /* bytes per scanline */
	int dx=bm->bmBitsPixel/8; /*bytes per pixel*/
	UINT32 r=GetRValue(c),g=GetGValue(c),b=GetBValue(c);
	HDC hDC = GetDC(hMainWnd);
    HDC hButton;
	BITMAPINFO bmi;
	HBITMAP  hBmp;
    VOID *bits; 
    int x,y;



    ZeroMemory(&bmi, sizeof(BITMAPINFO));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;         // four 8-bit components
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biWidth = BUTTON_SIZE;
    bmi.bmiHeader.biHeight = BUTTON_SIZE;
    bmi.bmiHeader.biSizeImage = BUTTON_SIZE*BUTTON_SIZE*4;
        
	hButton = CreateCompatibleDC(hDC);
    hBmp = CreateDIBSection(hButton, &bmi, DIB_RGB_COLORS, &bits, NULL, 0x0);
    SelectObject(hButton, hBmp);

    for(y=0;y<BUTTON_SIZE;y++)
	  for(x=0;x<BUTTON_SIZE;x++)
	  { UINT32 a=alpha[x*dx+y*dy];
		((UINT32 *)bits)[x + y * BUTTON_SIZE] = (((((a<<8)|(a*r/255))<<8)|(a*g/255))<<8)|(a*b/255);
	  }
   DeleteDC(hDC);
   return hButton;
}


void create_button(int n, int i,int j,int key, BITMAP *bm)
/* n=Button number i=icon number day, j = icon number night,
   in bitmap bm, key = key in WM_KEYDOWN message*/
{ HRGN br;
  BITMAPINFO bmi;
  HDC hDC;
  HBITMAP  hBmpDay,hBmpNight;
  VOID *day,*night; 
  int x,y;

  unsigned char *alpha=(unsigned char *)(bm->bmBits);
	int dy=bm->bmWidthBytes; /* bytes per scanline */
	int dx=bm->bmBitsPixel/8; /*bytes per pixel*/

  if (n>=MAX_BUTTON)
    hint_error("Error","Button number out of range");
  bi[n].key=key;
  bi[n].on=0;
  bi[n].h=CreateWindow("RoundButtons","RoundButton",WS_CHILD|WS_CLIPSIBLINGS,
	  n*BWIN_SIZE,0,BWIN_SIZE,BWIN_SIZE,hMainWnd,NULL,hInst,bi+n);
  br= CreateEllipticRgn(BBORDER_SIZE+1,BBORDER_SIZE+1,BBORDER_SIZE+BUTTON_SIZE+1-1,BBORDER_SIZE+BUTTON_SIZE+1-1);
  SetWindowRgn(bi[n].h, br, FALSE);

  hDC = GetDC(bi[n].h);
  bi[n].hDCday = CreateCompatibleDC(hDC);
  ZeroMemory(&bmi, sizeof(BITMAPINFO));
  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 32;         // four 8-bit components
  bmi.bmiHeader.biCompression = BI_RGB;
  bmi.bmiHeader.biWidth = BICON_SIZE;
  bmi.bmiHeader.biHeight = BICON_SIZE;
  bmi.bmiHeader.biSizeImage = BICON_SIZE*BICON_SIZE*4;
  hBmpDay = CreateDIBSection(bi[n].hDCday, &bmi, DIB_RGB_COLORS, &day, NULL, 0x0);
  SelectObject(bi[n].hDCday, hBmpDay);

  bi[n].hDCnight = CreateCompatibleDC(hDC);
  ZeroMemory(&bmi, sizeof(BITMAPINFO));
  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 32;         // four 8-bit components
  bmi.bmiHeader.biCompression = BI_RGB;
  bmi.bmiHeader.biWidth = BICON_SIZE;
  bmi.bmiHeader.biHeight = BICON_SIZE;
  bmi.bmiHeader.biSizeImage = BICON_SIZE*BICON_SIZE*4;
  hBmpNight = CreateDIBSection(bi[n].hDCnight, &bmi, DIB_RGB_COLORS, &night, NULL, 0x0);
  SelectObject(bi[n].hDCnight, hBmpNight);

    for(y=0;y<BICON_SIZE;y++)
    for(x=0;x<BICON_SIZE;x++)
	{ UINT32 a=0xFF-alpha[(x+i*BICON_SIZE)*dx+y*dy];
		((UINT32 *)day)[x + y * BICON_SIZE] = ((UINT32)a << 24) | 0x000000; /* BLACK */
	  if (i!=j) a=0xFF-alpha[(x+j*BICON_SIZE)*dx+y*dy];
		((UINT32 *)night)[x + y * BICON_SIZE] = ((((a<<8)|a)<<8)|a<<8)|a;/* WHITE */ 
	}
}

void init_button_class(void)
{ 
    WNDCLASSEX wcex;
	BITMAP bm;

    HANDLE hBFaceABmp;
    HANDLE hToolbarBmp;
    ZeroMemory(&wcex, sizeof(wcex));
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			= CS_CLASSDC;
	wcex.lpfnWndProc	= (WNDPROC)ButtonProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInst;
	wcex.hIcon			= NULL;
	wcex.hCursor		= NULL;
	wcex.hbrBackground	= GetStockObject(NULL_BRUSH);//(HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName = "RoundButtons";
	wcex.hIconSm		= NULL;
	if (!RegisterClassEx(&wcex)) 
	  hint_error("Fatal Error", "Unable to register window class.");

	/* Background Brushes */
    hDayBG=CreateSolidBrush(BG_DAY);
	hNightBG=CreateSolidBrush(BG_NIGHT);

    /* get alpha chnannel of the button face */
	hBFaceABmp = LoadImage(hInst, MAKEINTRESOURCE(IDB_BFACE_A),IMAGE_BITMAP,  
					   0, 0, LR_CREATEDIBSECTION|LR_DEFAULTCOLOR);
	GetObject(hBFaceABmp, sizeof(bm), &bm);

	/* create DC for button faces */
    hDay_on= create_face(BF_ON_DAY,&bm);
    hDay_off= create_face(BF_OFF_DAY,&bm);
    hNight_on= create_face(BF_ON_NIGHT,&bm);
    hNight_off= create_face(BF_OFF_NIGHT,&bm);

	hToolbarBmp = LoadImage(hInst, MAKEINTRESOURCE(IDB_TOOLBAR),IMAGE_BITMAP,  
					   0, 0, LR_CREATEDIBSECTION|LR_VGACOLOR);

	GetObject(hToolbarBmp, sizeof(bm), &bm);

  create_button(BUTTON_MENU,0,0,ID_KEY_MENU,&bm);
  create_button(BUTTON_SETTINGS,1,1,ID_KEY_SETTINGS,&bm);
  create_button(BUTTON_NIGHT,2,7,ID_KEY_NIGHT,&bm);
  create_button(BUTTON_ZOOM,3,3,ID_KEY_ZOOM,&bm);
  create_button(BUTTON_PREV,4,4,ID_KEY_PAGE_PREV,&bm);
  create_button(BUTTON_NEXT,5,5,ID_KEY_PAGE_NEXT,&bm);
  create_button(BUTTON_HELP,6,6,ID_KEY_HELP,&bm);
  create_button(BUTTON_HOME,8,8,ID_KEY_HOME,&bm);
  create_button(BUTTON_SEARCH,9,9,ID_KEY_SEARCH,&bm);
  create_button(BUTTON_NAVIGATE,10,10,ID_KEY_OUTLINE,&bm);

	DeleteObject(hBFaceABmp);
	DeleteObject(hToolbarBmp);
	
}







void show_buttons(int cmd)
{ int i;
  for (i=0;i<MAX_BUTTON;i++)
	if (bi[i].h!=NULL)
	{ ShowWindow(bi[i].h, cmd);
    }
}


void buttons_change(void)
{ int i;
  for (i=0;i<MAX_BUTTON;i++)
	if (bi[i].h!=NULL)
	{  InvalidateRect(bi[i].h,NULL,FALSE);
    }
}

void button_pos(int i, POINT *p)
{ p->x=i*BWIN_SIZE+BWIN_SIZE/2;
  p->y=BWIN_SIZE/2;
}

