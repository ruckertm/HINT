#include <windows.h>			/* must include this before GL/gl.h */
#include <commctrl.h>
#include <wingdi.h>
#include <afxres.h>
#include <stdio.h>
#include <math.h>
#include "resource.h"
#include "basetypes.h"
#include "error.h"
#include "glcontext.h"
#include "format.h"
#include "hrender.h"
#include "winreg.h"
#include "saveimage.h"
#include "winmain.h"
#include "settings.h"
#include "search.h"
#include "outline.h"
#include "print.h"
#include "button.h"
#include "get.h"
#include "hint.h"


/* Windows */
char szClassName[]="HintView";    
HINSTANCE hInst = NULL;          
HWND hMainWnd=NULL;	   
HWND hSearchWnd=NULL;
HWND hOutlineWnd=NULL;
HDC hDCMain=NULL;				  /* Device context */
static HGLRC hRCMain=NULL;		  /* OpenGL render context */
static HMENU hMenu;               
static HCURSOR hSizeNWSE, hArrow, hHand; /* scaling, non-scaling, link cursor */
/* Layout */
int dark=0;
int client_width=0, client_height=0; /* size of client aerea in pixel */
#define SCALE_MIN 0.2
#define SCALE_NORMAL 1.0
#define SCALE_MAX 5.0
double scale=SCALE_NORMAL, dpi_x, dpi_y; /* dpi and scale factor to zoom the rendering */

void init_layout(void)
/* collect system Information */
{ 
  int screen_width, screen_height,hpix, vpix;
  double dpmmx,dpmmy; /* dots per mm on target device */
  HDC hdc;
  hdc=GetDC(NULL);
  screen_width = GetDeviceCaps(hdc, HORZSIZE);
  screen_height =  GetDeviceCaps(hdc, VERTSIZE);
  hpix = GetDeviceCaps(hdc, HORZRES);
  vpix =  GetDeviceCaps(hdc, VERTRES);
  dpmmx = (double)hpix/screen_width;
  dpmmy = (double)vpix/screen_height;
  dpi_x = dpmmx*25.4;
  dpi_y = dpmmy*25.4;
}

/* Rendering Functions */

uint64_t pos; /* position of current page */
int autoreload=0;


static void render_page(void)
{ pos=hint_page();
  InvalidateRect(hMainWnd,NULL,FALSE);
}

static void render_next_page(void)
{ pos=hint_page_next();
  InvalidateRect(hMainWnd,NULL,FALSE);
}

static void render_prev_page(void)
{ pos=hint_page_prev();
  InvalidateRect(hMainWnd,NULL,FALSE);
}
static void render_home_page(void)
{ pos=hint_page_home();
  InvalidateRect(hMainWnd,NULL,FALSE);
}

static void show_page(void)
{  pos=hint_page_top(pos); 
  InvalidateRect(hMainWnd,NULL,FALSE);
}

static void resize_page(void)
/* we know client_width, client_heigt, scale, and dpi
   and compute Page_width, Page_height */
{ hint_resize(client_width,client_height,dpi_x*scale,dpi_y*scale);
  render_page();
}

/* Saving an Image */
static void save_image(void)
{	static char asname[MAX_PATH+1] = "";
	OPENFILENAME ofn ={0};
	ofn.lStructSize= sizeof(ofn);
	ofn.lpstrFile = asname;
	ofn.hwndOwner = hMainWnd;
	ofn.hInstance = hInst;
	ofn.lpstrFile = asname;
	ofn.lpstrFilter = "Bitmap (.bmp)\0*.bmp\0" "All Files (*.*)\0*.*\0\0";
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Save Image";
	ofn.lpstrDefExt = "bmp";
	ofn.Flags = OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT;

	if (GetSaveFileName(&ofn))
	   write_bmp(asname);
}


/* File Handling */
static char title_name[MAX_PATH+1]={0};

static void normalize_file_name(char *n)
{ if (n==NULL) return;
  while(*n!=0)
  { if (*n=='\\') *n='/';
    n++;
  }	  
}

static int assign_file_name(char *new_name)
{ normalize_file_name(new_name);
  if (hin_name!=NULL) free(hin_name);
  hin_name=malloc(strlen(new_name)+1);
  if (hin_name==NULL) 
	return hint_error("Out of memory",new_name);
  strcpy(hin_name,new_name);
  return 1;
}

static int get_file_name(void)
{	char new_name[MAX_PATH+1];
	OPENFILENAME ofn ={0};
	//if (hin_name==NULL)
		new_name[0]=0;
	//else
    //  strncpy(new_name,hin_name,MAX_PATH);
	ofn.lStructSize= sizeof(ofn);
	ofn.lpstrFile = new_name;
	ofn.hwndOwner = hMainWnd;
	ofn.hInstance = hInst;
	ofn.lpstrFilter = "HINT File (.hnt)\0*.hnt\0\0";
    ofn.nFilterIndex = 1;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = title_name;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrDefExt = "hnt";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (!GetOpenFileName(&ofn)) 
	{ DWORD d=CommDlgExtendedError();
	  if (d==0)
		return 0;
	  else 
	    return hint_error("Error","Open File Dialog failed");	
	}
	assign_file_name(new_name);
	return 1;
}

#ifdef MAP
/* use a file mapping to map the file into memory:
   advantage: fast
   disadvantage: locks the file and you can't run TeX on it and reload
*/

static HANDLE hMap;
uint64_t hint_map(void)
{ HANDLE hFile;
  uint64_t s;
  DWORD hs,ls;
  hin_addr=NULL;

  hFile = CreateFile(hin_name,FILE_READ_DATA,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_READONLY,NULL);
  if (hFile==INVALID_HANDLE_VALUE)
  {	MESSAGE("Unable to open file %s", hin_name);
	return 0;
  }
  ls=GetFileSize(hFile,&hs); 
  s=hs;
  s=s<<32;
  s=s+ls; 
 
  if (s==0)
  { MESSAGE("File %s is empty", hin_name);
    CloseHandle(hFile);
    return 0;
  }
  hMap = CreateFileMapping( 
           hFile, /* use paging file */
           NULL,                 /* no security attributes */
           PAGE_READONLY,       /* read only access */
           0,                    /* size: high 32-bits */
           0,            /* size: low 32-bits */
           NULL);     /* name of map object */
  if (hMap == NULL) 
  { MESSAGE("Unable to map file into memory");
    CloseHandle(hFile);
    return 0;
  }
  hin_addr = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);  
  if (hin_addr==NULL)
  { MESSAGE("Unable to obtain address of mapping for file %s", hin_name);
    CloseHandle(hMap);
    CloseHandle(hFile);
	return 0;
  } 
  CloseHandle(hFile);
  return s;
}


void hint_unmap(void)
{ UnmapViewOfFile(hin_addr);
  if (hMap!=NULL) CloseHandle(hMap);
  hMap=NULL;
  hin_addr=NULL;
}

#else
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void hint_unmap(void)
{ hget_unmap();
}

bool hint_map(void)
{ return hget_map();
}
#endif




static void open_file(void)
{ size_t sl;
  if (hin_name==NULL || hin_name[0]==0) return;
  sl=strlen(hin_name);
  if (sl>4 && strncmp(hin_name+sl-4,".hnt",4)==0)
  { hint_clear_fonts(true);
    hint_begin();
	strncpy(title_name,hin_name,MAX_PATH);
	SetNavigationTree();
  }
  else
    hint_message("Unknown File Type","I dont know how to open this file");
  SetWindowText(hMainWnd,title_name);
}

static void close_file(void)
{ hint_end();
  hint_clear_fonts(true);
  ClearNavigationTree();
  title_name[0]=0;
  SetWindowText(hMainWnd,title_name);
}

static void	render_file(void)
{ open_file();
  show_page();
}

static void reload_file(void)
{ double fpos=hint_get_fpos();
  open_file();
  pos=hint_set_fpos(fpos);
  InvalidateRect(hMainWnd,NULL,FALSE);
}


static bool new_file_time(void)
{ struct _stat st;
  if (hin_name!=NULL && hin_name[0]!=0 &&
      _stat(hin_name,&st)==0 &&
	  st.st_size>0 &&
      st.st_mtime>(__time64_t)hin_time)
	  return true;
  else
	  return false;

}

/* Help  About */

INT_PTR CALLBACK 
AboutDialogProc( HWND hDlg, UINT message, WPARAM wparam, LPARAM lparam )
{
  switch ( message )
  { case WM_INITDIALOG:
      SetDlgItemText(hDlg,IDC_VERSION,VERSION);
	  { char format_version[100];
	    _snprintf(format_version,99,"HINT Format Version %d.%d",HINT_VERSION, HINT_SUB_VERSION);
         SetDlgItemText(hDlg,IDC_HINT_VERSION,format_version);
	  }
      return TRUE;
    case WM_SYSCOMMAND:
      if( wparam == SC_CLOSE ) 
      { EndDialog(hDlg, TRUE);
        return TRUE;
      }
      break;
    case WM_COMMAND:
      if( wparam == IDOK )
      {
        EndDialog(hDlg, TRUE);
        return TRUE;
      }
      else if( wparam == IDCANCEL )
      {
        EndDialog(hDlg, TRUE);
        return TRUE;
      }
     break;
  }
  return FALSE;
}




 /* Resources */

static void init_handles(void)
/* create all necessary global Window handles */
{   
	hDCMain=GetDC(hMainWnd);
    hRCMain=GetGLContext(hDCMain);
    if (!hRCMain) 
	{  hint_error("Fatal Error","Unable to create rendering context");
		 exit(1);
	}
	else
	  hint_render_on();
	hMenu = LoadMenu(hInst,MAKEINTRESOURCE(IDR_MENU));
	hSizeNWSE=LoadCursor(NULL,IDC_SIZENWSE);
	hArrow=LoadCursor(NULL,IDC_ARROW);
	hHand=LoadCursor(NULL,IDC_HAND); 
}

static void release_handles(void)
/* release all handles created by init_handles */
{   hint_render_off();
    wglMakeCurrent(hDCMain, NULL);
    if (hRCMain!=NULL) wglDeleteContext(hRCMain);
	hRCMain=NULL;
	if (hDCMain!=NULL) ReleaseDC(hMainWnd, hDCMain);
	hDCMain=NULL;
}

bool onTop=false;
/* Windows message processing */

static LRESULT CALLBACK 
WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{ 
    static PAINTSTRUCT ps;
    static bool draging=false;
	static POINT drag;
	static double scale0;
    static bool OnLink=false;
    static bool loading=false;

    switch(uMsg) {
	case WM_CREATE:
	  hMainWnd=hWnd;
	  DragAcceptFiles(hWnd,TRUE);
	  return 0;
	case WM_DESTROY:
	  hint_end(); hint_clear_fonts(true);
	  release_handles();
      PostQuitMessage(0);
      return 0;
	case WM_DROPFILES:
	  { HDROP hDrop = (HDROP)wParam;
	    char new_name[MAX_PATH+1];
		DragQueryFile(hDrop,0,new_name,MAX_PATH);
		assign_file_name(new_name);
        DragFinish(hDrop);
		if (loading) return 0;
		loading=true;
        pos=0;
	    HINT_TRY render_file();
		loading=false;
	  }
	  return 0;

	case WM_COMMAND:
#if 0
      if (HIWORD(wParam)==0) /* 0==Menu 1==Accelerator */
#endif
      switch(LOWORD(wParam))
	{ case ID_FILE_OPEN:
	    if (get_file_name())
		{ if (loading) return 0;
		  loading=true;
		  pos=0;
	      HINT_TRY render_file();
		  loading=false;
		}
	    return 0;
	  case ID_FILE_CLOSE:
		close_file();
		if (hin_name!=NULL) free(hin_name);
        hin_name=NULL;
        pos=0;
        hint_blank();
        InvalidateRect(hWnd,NULL,FALSE);
		return 0;
	  case ID_FILE_AUTORELOAD:
		  if (GetMenuState(hMenu,ID_FILE_AUTORELOAD,MF_BYCOMMAND)&MF_CHECKED) 
			  SendMessage(hMainWnd,WM_COMMAND,ID_KEY_AUTORELOAD,0);
		  else			  
			  SendMessage(hMainWnd,WM_COMMAND,ID_KEY_AUTORELOAD,1);
		  return 0;
	  case ID_FILE_SAVE_IMAGE:
		save_image();
		return 0;
	  case ID_FILE_PAGE_SETUP:
		  page_setup();
		  return 0;
	  case ID_FILE_PRINT:
	      { uint64_t pos= hint_page_get();
		    //wglMakeCurrent (NULL, NULL);
		    print_pages();
			//wglMakeCurrent (hDCMain, hRCMain);
			HINT_TRY {resize_page(); show_page(); }
		  }
		  return 0;
      case ID_APP_EXIT:
        PostMessage(hMainWnd,WM_CLOSE,0,0);
  	    return 0;
	  case ID_KEY_MENU: /* system menu */
		{ RECT      rc={0};
		  HMENU     hPopupMenu = NULL;
	      MapWindowPoints(hMainWnd,
                         HWND_DESKTOP, (LPPOINT)&rc, 2);                         
          hPopupMenu = GetSubMenu(hMenu,0);
          TrackPopupMenuEx(hPopupMenu,
            TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL,               
            rc.left, rc.bottom, hMainWnd, NULL); 
        }
		 return 0;
		 case ID_KEY_SETTINGS: /* settings dialog */
		   if (DialogBox(hInst,MAKEINTRESOURCE(IDD_SETTINGS),hWnd,SettingsDialogProc))
		     HINT_TRY resize_page();
		   return 0;
		 case ID_KEY_NIGHT: /* toggle day or night mode */
  		   dark=!dark;
           hint_dark(dark);
           buttons_change();
           InvalidateRect(hMainWnd,NULL,FALSE);
		   return 0;
		 case ID_KEY_ZOOM: /* zoom to 100% */
		  scale=SCALE_NORMAL;
		  hint_clear_fonts(true);
		  HINT_TRY resize_page();
		   return 0;
		case ID_KEY_OUTLINE: /* outline window */
           if (!IsWindow(hOutlineWnd)) 
		   {   hOutlineWnd=CreateDialog(hInst,MAKEINTRESOURCE(IDD_OUTLINE),hWnd,OutlineDialogProc);
		       ShowWindow(hOutlineWnd,SW_SHOW);
		   }
		   return 0;
	     case ID_KEY_PAGE_PREV: /* page up */
		   HINT_TRY render_prev_page();
		   return 0;
	    case ID_KEY_PAGE_NEXT: /* page down */
		   HINT_TRY render_next_page();
		   return 0;
        case ID_KEY_HELP: /* Help */
           DialogBox(hInst,MAKEINTRESOURCE(IDD_ABOUT),hWnd,AboutDialogProc);
		   return 0;
	     case ID_KEY_HOME: /* home page */
		   HINT_TRY render_home_page();
		   return 0;
	  case ID_KEY_SEARCH:
        if (!IsWindow(hSearchWnd)) 
 	    { hSearchWnd = CreateDialog(hInst,MAKEINTRESOURCE(IDD_SEARCH),hWnd,SearchDialogProc);
	     ShowWindow(hSearchWnd,SW_SHOW);
	    }
	    return 0;
	  case ID_KEY_RELOAD:
	  	  if (loading) return 0;
		  loading=true;
 		  HINT_TRY reload_file();
		  loading=false;
		return 0;
	  case ID_KEY_AUTORELOAD:
		  autoreload=lParam;
		  CheckMenuItem(hMenu,ID_FILE_AUTORELOAD,autoreload?MF_CHECKED:MF_UNCHECKED);
		  return 0;
	  case ID_KEY_QUIT:
		  PostMessage(hMainWnd,WM_CLOSE,0,0);
		  return 0;
	}
    return 0;
#if DEBUG
	case WM_KEYDOWN:
      switch (wParam)
	  { 
	
	    case VK_TAB: /* mark the current page */
		  pos=hint_page_get();
		  return 0;
		case VK_BACK: /* return to the marked page */
		  HINT_TRY show_page();
          return 0;


	  }
	  break;
#endif 
	case WM_GAMMA:
		  hint_gamma(gamma);
          InvalidateRect(hMainWnd,NULL,FALSE);
		  return 0;
    case WM_PAINT:
	  BeginPaint(hWnd, &ps);
	  HINT_TRY hint_render();
      SwapBuffers(hDCMain);
	  EndPaint(hWnd, &ps);
	  return 0;
	case WM_SETFOCUS:
		if (autoreload && new_file_time())
		  SendMessage(hMainWnd,WM_COMMAND,ID_KEY_RELOAD,0);
		return 0;
    case WM_SIZE:
	  client_width=LOWORD(lParam);
	  client_height=HIWORD(lParam);
  	  HINT_TRY resize_page();
	  return 0;
    case WM_LBUTTONDOWN:
	{ drag.x = LOWORD(lParam), drag.y=HIWORD(lParam);
      if (!DragDetect(hWnd,drag))
	  { int link;
	    HINT_TRY {
	      link=hint_find_link(round((drag.x<<16)*72.27/(dpi_x*scale)),
	                            round((drag.y<<16)*72.27/(dpi_y*scale)),2*ONE);
		  if (link>=0)
	        hint_link_page(link);
		}
		InvalidateRect(hMainWnd,NULL,FALSE);
	  }
	  else
	  { draging =true;
	    scale0=scale;
	    SetCursor(hSizeNWSE); 
	    SetCapture(hWnd); 
	  }
	}
	return 0;
    case WM_LBUTTONUP:
      if (!draging) return 0;
	  draging =false;
  	  ReleaseCapture();
	  SetCursor(hArrow); 
	  hint_clear_fonts(true);
      InvalidateRect(hMainWnd,NULL,FALSE);
	return 0;
    case WM_SETCURSOR: 
	  if (OnLink) SetCursor(hHand);
	  else SetCursor(hArrow);
	  break;
    case WM_MOUSEMOVE:
	{ POINTS mouse = MAKEPOINTS(lParam);
      static bool TBshown=false;
  
      if (!TBshown && mouse.y < 32)
	  {  show_buttons(SW_SHOW),TBshown=1;
	     //SetWindowPos(hMainWnd,HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
	  }
	  else if (TBshown && mouse.y >= 32)
	  { show_buttons(SW_HIDE),TBshown=0; 
	  }
	  if (draging && (wParam & MK_LBUTTON)) {
	    scale=scale0*((double)(drag.x*mouse.x+drag.y*mouse.y)/
			          (double)(drag.x*drag.x+drag.y*drag.y));
		if (scale < SCALE_MIN) scale=SCALE_MIN;
		if (scale > SCALE_MAX) scale=SCALE_MAX;
		HINT_TRY resize_page();
	  }
	  else
	  {	int link;
	    link=hint_find_link(round(((int)mouse.x<<16)*72.27/(dpi_x*scale)),
	                            round(((int)mouse.y<<16)*72.27/(dpi_y*scale)),2*ONE);
        if (link>=0 && !OnLink)
	    { SetCursor(hHand); OnLink=true; }
	    else if (link<0 && OnLink)
   	    { SetCursor(hArrow); OnLink=false; }

	  }
	  return 0;
	}
  }
  return DefWindowProc(hWnd, uMsg, wParam, lParam); 
} 


/* Command line */

static int do_command_line(char *c)
{ int i;
  /* scan arguments */
  while (*c!=0)
  { if (isspace(*c)) c++;
    else if (*c=='-')
	{ /* scan option */
      c++;
	  if (*c=='d')
	  { c++;
	    debugflags=strtol(c,&c,16);
	  }
	  else
  	    while (*c!=0 && !isspace(*c)) c++; /* skip option */
	}
	else
	{ bool quoted=false;
	  char new_name[MAX_PATH+1];
	  /* scan filename */
	  if (*c=='"') { c++; quoted=true; }
      i=0;
      while (*c!=0 && !isspace(*c) && i<MAX_PATH)
	    new_name[i++]=*c++;
	  if (quoted && new_name[i-1]=='"') i--;
      new_name[i]=0;
      if (i>MAX_PATH)
		return hint_error("Error: File name too long, truncated!", new_name);
	  normalize_file_name(new_name);
	  if (hin_name==NULL || strcmp(new_name,hin_name)!=0)
	  { pos=0;
		if (hin_name!=NULL) free(hin_name);
	    hin_name=malloc(strlen(new_name)+1);
        if (hin_name==NULL)
		  return hint_error("Out of memory for file name", new_name);
	    strcpy(hin_name,new_name);
	  }
	  return 1; /* ignore the rest */
	}
  }
  return 1;
}

/* Start Up */
BOOL InitInstance(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;
	if (hInst!=0) return TRUE;
    hInst = hInstance; 
    ZeroMemory(&wcex, sizeof(wcex));
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			= CS_OWNDC|CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	=  (WNDPROC)WindowProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	wcex.hCursor		= NULL;
	wcex.hbrBackground	= NULL;// GetStockObject(WHITE_BRUSH);//(HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName = szClassName;
	wcex.hIconSm		= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	if (!RegisterClassEx(&wcex)) 
	  return hint_error("Fatal Error", "Unable to register window class.");
    return TRUE;
}



int APIENTRY
WinMain(HINSTANCE hCurrentInst, HINSTANCE hPreviousInst,
	LPSTR lpCmdLine, int nCmdShow)
{   MSG   msg;
	RECT r;
	BOOL b;
	INITCOMMONCONTROLSEX ic;
    HACCEL hAccel;

#if 0
    hlog=freopen("hintview.log","w",stdout);
	debugflags|=1;
#else
	hlog=stderr;
#endif 

	if (!InitInstance (hCurrentInst)) return FALSE;
	InitGLextensions(); 

	ic.dwSize=sizeof(ic);
	ic.dwICC= ICC_TREEVIEW_CLASSES;
	if (!InitCommonControlsEx(&ic )) return FALSE;        
	init_layout();
    client_width=round(320*dpi_x/72.27); /* 320 pt */
    client_height=round(400*dpi_y/72.27); /* 400 pt */
	r.top=r.left=0;
	r.right=client_width;
	r.bottom=client_height;
	AdjustWindowRect(&r,WS_TILEDWINDOW ,FALSE);

#if 1
    CreateWindow(szClassName, szClassName,
			WS_OVERLAPPED| WS_TILEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
			CW_USEDEFAULT,CW_USEDEFAULT, r.right-r.left, r.bottom-r.top,
			NULL, NULL, hInst, NULL);
#else
	CreateWindowEx(WS_EX_TOPMOST,szClassName, szClassName,
			WS_TILEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
			CW_USEDEFAULT,CW_USEDEFAULT, r.right-r.left, r.bottom-r.top,
			NULL, NULL, hInst, NULL);
#endif

    if (hMainWnd == NULL) 
	  return hint_error("Fatal Error","Unable to create window");
	init_handles();

	read_regtab(); 
	do_command_line(lpCmdLine);
	SetWindowText(hMainWnd,title_name);
	printer_init();
	init_button_class();
    hint_dark(dark);
    hint_gamma(gamma);
	if (autoreload) SendMessage(hMainWnd,WM_COMMAND,ID_KEY_START_AUTORELOAD,0);
	hAccel = LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_ACCELERATOR));

    ShowWindow(hMainWnd, SW_SHOW);
	HINT_TRY render_file();

	//SetFocus(hMainWnd);
	 //BringWindowToTop(hMainWnd);
    //SetWindowPos(hMainWnd,HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);

    while ((b= GetMessage(&msg, NULL, 0, 0)) != 0) 
    { if (b == -1)
      { hint_error("ERROR","Unexpected end of message loop");
        break;
      }
#if 0
      else if (IsWindow(hSearchWnd) && IsDialogMessage(hSearchWnd, &msg))
		  continue;
#endif 
	  else if (TranslateAccelerator(hMainWnd, hAccel, &msg)) 
		  continue;
	  else
      { TranslateMessage(&msg); 
        DispatchMessage(&msg); 
      } 
    } 
	write_regtab();
    return (int)msg.wParam;
}

/* Error Handling */
int hint_error(char *title, char *message)
{ MessageBox(NULL,message,title,MB_OK|MB_ICONEXCLAMATION);
  return 0;
}


void hint_message(char *title, char *format, ...)
{ char str[1024];
  va_list vargs;
  va_start(vargs,format);
  vsnprintf(str, 1024, format, vargs);
  MessageBox(NULL,str,title,MB_OK);
}
