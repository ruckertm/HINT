#include <windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>
#include "basetypes.h"
#include "error.h"
#include "winmain.h"


/* we create a dummy window,
   and an GL context
   obtain the extension functions
   and destroy window and context again.
   In a second step we create the final
   context
 */

static BOOL
WinPixelFormat(HDC hDC)
{   int         pf;
    PIXELFORMATDESCRIPTOR pfd;
 
	memset(&pfd, 0, sizeof(pfd));
    pfd.nSize        = sizeof(pfd);
    pfd.nVersion     = 1;
    pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType   = PFD_TYPE_RGBA;
    pfd.cColorBits   = 32;
	pfd.cDepthBits	 = 24;
	pfd.cStencilBits = 8;

    pf = ChoosePixelFormat(hDC, &pfd);
    if (pf == 0) 
	 return hint_error("Fatal Error", "Unable to find usable Pixel Format");
	 
    //DescribePixelFormat(hDCMain, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
    if (SetPixelFormat(hDC, pf, &pfd) == FALSE) 
	  return hint_error("Fatal Error", "Unable to set usable Pixel Format");
  	
    return TRUE;
}    

/* this is the function that we need */
static PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB=NULL;
static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB=NULL;
/* this is how we get it */
void* glGetAnyProcAddress(const char* name) {
    void *pointer = (void *)wglGetProcAddress(name);
    if (pointer == 0 || (pointer == (void*)0x1) || (pointer == (void*)0x2) || (pointer == (void*)0x3) || (pointer == (void*)-1)) 
	{ hint_error("Fatal Error: Unable to addess",(char*)name);
	  return NULL;
	}
	return pointer;
};


char tmpClassName[]="tmpClass";
/* the next function must be called
   after InitInstance and before Create Window */
BOOL InitGLextensions(void)
{  HWND hWnd;
   HDC hDC;
   HGLRC hRC;
   WNDCLASSEX wcex;
   HINSTANCE hInst;
   hInst=GetModuleHandle(0);
   ZeroMemory(&wcex, sizeof(wcex));
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			=  CS_HREDRAW | CS_VREDRAW |CS_OWNDC;
	wcex.lpfnWndProc	=  (WNDPROC)DefWindowProcA;
	wcex.hInstance		= hInst;
	wcex.lpszClassName = tmpClassName;
	if (!RegisterClassEx(&wcex)) 
	  return hint_error("Fatal Error", "Unable to register window class.");
      
   hWnd=CreateWindow(tmpClassName, tmpClassName,
			0,
			CW_USEDEFAULT,CW_USEDEFAULT, CW_USEDEFAULT,CW_USEDEFAULT,
			NULL, NULL, hInst, NULL);
   if (!hWnd) return FALSE;
   hDC=GetDC(hWnd);
   if (!hDC) return FALSE;
   if (!WinPixelFormat(hDC)) return FALSE;
   hRC = wglCreateContext(hDC);
   if (!hRC) return FALSE;
   wglMakeCurrent(hDC, hRC); 
   wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)glGetAnyProcAddress("wglChoosePixelFormatARB");
   if (!wglChoosePixelFormatARB) return FALSE;
   wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)glGetAnyProcAddress("wglCreateContextAttribsARB");
   if (!wglCreateContextAttribsARB) return FALSE;

   /* we have what we wanted, now lets clean up */
   wglMakeCurrent(hDC, NULL); 
   wglDeleteContext(hRC);
   ReleaseDC(hWnd, hDC);
   DestroyWindow(hWnd);
   return TRUE;
}

int glminor, glmajor;
const char *glversion, *glrenderer;

/* this function must be called after the main window is created */
HGLRC GetGLContext(HDC hDC)
{ PIXELFORMATDESCRIPTOR pfd;
  int attributes[] = {
    WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
	WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
	WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
	WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
	WGL_COLOR_BITS_ARB, 32,
	WGL_DEPTH_BITS_ARB, 24,
	WGL_STENCIL_BITS_ARB, 8,
	WGL_SAMPLE_BUFFERS_ARB, 1, // Enable multisampling
	WGL_SAMPLES_ARB, 16, // Number of samples
	0,0};

  int pixelFormat;
  UINT numFormats;
  float fAttributes[] = {0,0};
  BOOL valid;
  HGLRC hRC;

  valid = wglChoosePixelFormatARB (hDC, attributes, 0, 1, &pixelFormat, &numFormats);
  if (!valid || numFormats < 1) return FALSE;
  // pixel format with multisampling have been found, create new OpenGL context for it
  DescribePixelFormat(hDC, pixelFormat, sizeof(pfd), &pfd);
  if (!SetPixelFormat(hDC, pixelFormat, &pfd)) 
	  hint_error("Error:", "Failed to set the OpenGL 3.3 pixel format.");
	  
    hRC = wglCreateContext(hDC);

  if (!hRC)
	 hint_error("Error:","Failed to create OpenGL 3.3 context.");
  wglMakeCurrent (hDC, hRC);
  glversion=glGetString(GL_VERSION);
  glrenderer=glGetString(GL_RENDERER);
  //glmajor=glGetIntegerv(GL_MAJOR_VERSION, *);
  //glminor=glGetIntegerv(GL_MINOR_VERSION, *);
  return hRC;
}

HGLRC GetGLPrintContext(HDC hDC)
{
#if 0
  PIXELFORMATDESCRIPTOR pfd;
  BOOL valid;
  int pixelFormat[50];
  UINT numFormats;
#endif
  int attributes[] = {
    WGL_DRAW_TO_BITMAP_ARB, GL_TRUE,
	WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
	//WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
	//WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
	//WGL_COLOR_BITS_ARB, 32,
	//WGL_DEPTH_BITS_ARB, 24,
	//WGL_STENCIL_BITS_ARB, 8,
	//WGL_SAMPLE_BUFFERS_ARB, 1, // Enable multisampling
	//WGL_SAMPLES_ARB, 16, // Number of samples
	0,0};

  float fAttributes[] = {0,0};
  HGLRC hRC;
  GLint context_attributes[] = {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
    WGL_CONTEXT_MINOR_VERSION_ARB, 3,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
    0
    };
#if 1
     hRC= wglCreateContextAttribsARB(hDC, 0, context_attributes);
#else
  valid = wglChoosePixelFormatARB (hDC, attributes, 0, 50, pixelFormat, &numFormats);
  if (!valid || numFormats < 1) return FALSE;
  // pixel format with multisampling have been found, create new OpenGL context for it
  DescribePixelFormat(hDC, pixelFormat[0], sizeof(pfd), &pfd);
  if (!SetPixelFormat(hDC, pixelFormat[0], &pfd)) 
	  hint_error("Error:", "Failed to set the OpenGL 3.3 pixel format.");
	  
    hRC = wglCreateContext(hDC);
#endif
  if (!hRC)
	 hint_error("Error:","Failed to create OpenGL 3.3 context.");
  wglMakeCurrent (hDC, hRC);
  glversion=glGetString(GL_VERSION);
  glrenderer=glGetString(GL_RENDERER);
  //glmajor=glGetIntegerv(GL_MAJOR_VERSION, *);
  //glminor=glGetIntegerv(GL_MINOR_VERSION, *);
  return hRC;
}
