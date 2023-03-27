#ifndef WINMAIN_H
#define WINMAIN_H

#define VERSION "Version 2.0.0"

#if 0
extern HDC hDCMain;  
extern HDC hPage; /* The memory device context for the rendered page */
extern HBITMAP hBmpPage; /* the memory bitmap for rendering */

extern int page_t, page_b,page_l,page_r; /* margins of client area in scaled points*/
extern double dpmm, dpmmx, dpmmy; /* dots per mm */

//extern char data_path[MAX_PATH+1];


/* conversion between units and scaled points */
extern int Page_width, Page_height, Page_dpi; /* size and dpi of page scaled for rendering */
#endif

extern HWND hMainWnd;
extern HWND hSearchWnd;
extern HWND hOutlineWnd;
extern HDC hDCMain;
extern char szClassName[];
extern HINSTANCE hInst;
extern int client_width, client_height; /* size of client aerea in pixel */
extern double xdpi, ydpi; /* dots per inch */
extern char *hin_name;
extern uint64_t pos;
extern double scale, dpi_x, dpi_y; /* universal scale factor between TeX sizes and client sizes */
extern int dark;
extern int autoreload;
#define round(X)     ((int)((X)>=0.0?floor((X)+0.5):ceil((X)-0.5)))

#define WM_GAMMA WM_USER

extern double gamma;

/* colors foreground and background for day and night mode */
#define FG_DAY RGB(0x00,0x00,0x00) /* black */
#define BG_DAY RGB(0xFF,0xFF,0xFF) /* white */
#define FG_NIGHT RGB(0xFF,0xFF,230) /* warm white */
#define BG_NIGHT RGB(0x00,0x00,0x00) /* dark blue */

#define BF_ON_DAY RGB(0xD0,0xD0,0xD0) /* lighter grey */
#define BF_OFF_DAY RGB(0xA0,0xA0,0xA0) /* light grey */
#define BF_ON_NIGHT RGB(0x90,0x90, 0x90) /* medium grey */
#define BF_OFF_NIGHT RGB(0x60,0x60, 0x60) /* dark grey */



#endif
//include "error.h"