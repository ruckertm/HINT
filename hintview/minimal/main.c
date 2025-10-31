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
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define VERSION 2
#define MINOR_VERSION 2
#define REVISION 2

#include "error.h"
#include "basetypes.h"
#include "format.h"
#include "get.h"
#include "hint.h"
#include "rendernative.h"

/* Error Handling */
static int hint_error(const char *title, const char *message)
{ fprintf(stderr,"ERROR %s: %s\n",title,message);
  return 0;
}

static void error_callback(int error, const char* description)
{ hint_error("OpenGL",description);
  longjmp(hint_error_exit,1);
}

GLFWwindow* window;
#define SCALE_MIN 0.2
#define SCALE_NORMAL 1.0
#define SCALE_MAX 5.0
static double scale=SCALE_NORMAL;
static uint64_t pos; /* position of current page */


/* Getting the dpi for a window is not as simple as one might think,
   because windows might dynamically move between monitors.


   To get a list of monitors use:
   int monitor_count;
   GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);

   To get notified about connecting or disconnecting of monitors use:
   glfwSetMonitorCallback(monitor_callback)
   the callback should refresh the pointer and count returned
   from  glfwGetMonitors.

   for a monitor, we can get:

   - its physical size:
   int width_mm, height_mm;
   glfwGetMonitorPhysicalSize(monitor, &width_mm, &height_mm);

   - its position (upper left) in screen coordinates:
   int xpos, ypos;
   glfwGetMonitorPos(monitor, &xpos, &ypos);

   - its video mode:
   GLFWvidmode* mode = glfwGetVideoMode(monitor);
 
   and through the video mode the mode->width and mode->height
   in screen coordinates.

   Using this information, we can 
   - get the area of a monitor by its position width and height
     in screen coordinates and
   - convert screen coordinates
     for the monitor into physical coordinates.
   
   To determine the monitor where a window is currently displayed
   screen coordinates must be used.

   we get the window size in screen coordinates using:
   int width, height;
   glfwGetWindowSize(window, &width, &height);

   we get the window position (upper left) in screen coordinates using:
   int xpos, ypos;
   glfwGetWindowPos(window, &xpos, &ypos);
   
   Matching the window position against the monitor area we can find
   the monitor on which we have the window position.

   Using the information about the monitor, we can convert the
   size of the window from screen coordinates to physical sizes.

   To obtain the resolution of a window we use the size of the
   windows framebuffer, which is in pixels either with
   int width, height;
   glfwGetFramebufferSize(window, &width, &height);

   or by getting a notification using:
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   void framebuffer_size_callback(GLFWwindow* window, int width, int height)
   {
    glViewport(0, 0, width, height);
   }

*/

/* Monitors */
static int monitor_count;
static GLFWmonitor** monitors;

static void monitor_callback(GLFWmonitor* monitor, int event)
{  monitors=glfwGetMonitors(&monitor_count);
  if (monitors==NULL || monitor_count==0)
    error_callback(0,"Unable to find a monitor");
  LOG("monitors %d\n",monitor_count);
}

static void init_monitors(void)
{ monitor_callback(NULL,0);
  glfwSetMonitorCallback(monitor_callback);
}

static int m_width, m_height;
static int width_mm, height_mm;

static int find_monitor(int x, int y)
/* return monitor for screen coordinates (x, y) */
{ int i;
  for (i=0; i< monitor_count; i++)
  {  int mx, my;
    glfwGetMonitorPos(monitors[i], &mx, &my);
    if (x>= mx && y >= my ) 
    { const GLFWvidmode *mode = glfwGetVideoMode(monitors[i]); 	
      if (x <= mx+mode->width && y<=my+mode->height)
      { m_width=mode->width; m_height=mode->height;
        glfwGetMonitorPhysicalSize(monitors[i], &width_mm, &height_mm);
        //LOG("Monitor pos: %d x %d, size: %d x %d, %dmm x %dmm\n",mx,my,m_width,m_height,width_mm, height_mm);
        return i;
      }
    }
  }
  return 0;
}

static int px_h=1024, px_v=768; // size in pixel
static double x_dpi, y_dpi;

static void set_dpi(GLFWwindow* window, int px, int py)
{ int wx, wy, ww, wh;
  glfwGetWindowPos(window, &wx, &wy);
  glfwGetWindowSize(window, &ww, &wh);
  find_monitor(wx,wy);
  x_dpi=25.4*px*m_width/width_mm/ww;
  y_dpi=25.4*py*m_height/height_mm/wh;
  //LOG("Window pos:  %d x %d, size: %d x %d,  %dpx x %dpx\n",wx, wy,ww,wh,px,py);
  //LOG("dpi: %f x %f\n",x_dpi,y_dpi);
}

static int request_render=0;

static void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{ px_h=w; px_v=h;
  glViewport(0, 0, w, h);
  set_dpi(window,w,h);
  //LOG("w=%d, h=%d\n",w,h);
  hint_resize(px_h,px_v,scale*x_dpi,scale*y_dpi);
  hint_page();
  request_render=1;
}

static void init_dpi(GLFWwindow* window)
{ int px,py;
  glfwGetFramebufferSize(window, &px, &py);
  set_dpi(window,px,py);
}

void hint_unmap(void)
{ hget_unmap();
}

bool hint_map(void)
{ return hget_map();
}

static int open_file(int home)
{ hint_end();
  if (!hint_begin()) return 0;
  if (home)
    hint_page_home();
  else
    hint_page_top(0);
   request_render=1;
return 1;
} 

static void reload_file(void)
{ double fpos=hint_get_fpos();
  hint_end();
  hint_begin();
  pos=hint_set_fpos(fpos);
  request_render=1;
  //LOG("reloading...\n");
}

static int new_file_time(void)
{ struct stat st;
  if (hin_name!=NULL &&
      stat(hin_name,&st)==0 &&
      st.st_size>0)
  {
    //LOG("file %s %lu\n",hin_name,st.st_mtime);
    if (st.st_mtime>hin_time)
    return 1;
  else
    return 0;
  }
  return 0;
}


static int set_hin_name(char *fn)
{  size_t sl;
  if (hin_name!=NULL) { free(hin_name); hin_name=NULL; }
  { hin_name=malloc(strlen(fn)+1);
    if (hin_name==NULL)
    { hint_error("Out of memory for file name", fn);
      return 0;
    }
    strcpy(hin_name,fn);
  }
  sl=strlen(hin_name);
  if (sl>4 && strncmp(hin_name+sl-4,".hnt",4)!=0)
  {  hint_error("Unknown File Type,I dont know how to open this file", hin_name);
    return 0;
  }
  return 1;
}



static int dark = 0, loading=0, autoreload=0, home=0;

static int usage(void)
{    return hint_error("Usage:", "hintview [options] file\n"
		  "Call 'hintview --help' for details.\n");
}

static int help(void)
{ fprintf(stdout,"%s",
   "Usage: hintview [options] file\n"
   "Options:\n"
   "  -a         Start in autoreload mode.\n"	  
   "  -h         Start with the documents home page.\n"	  
   "  -d         Start in night mode.\n"	  
#if 0
   "  -o         Show the documents outline.\n"
#endif
   "  -z         Start with zoom level 100%.\n"	  
   "  --help     Display this message.\n"	  
   "  --version  Display the version.\n"
#ifdef DEBUG
   "  -D xxx     Set HINT debug flags to xxx.\n"
#endif	  
   "\n"
   "See the hintview man page for more details.\n"
  );
  return 0;
}

static int command_line(int argc, char *argv[])
{ int i;
  for (i=1; argv[i]!=NULL && argv[i][0]=='-'; i++)
    { switch (argv[i][1])
      { case '-':
	    if (strcmp(argv[i]+2,"help")==0) return help();
	    else if (strcmp(argv[i]+2,"version")==0)
	      { fprintf(stdout,"hintview version %d.%d.%d\n"
			"HINT file format version %d.%d\n", 
			VERSION, MINOR_VERSION, REVISION,
			HINT_VERSION, HINT_MINOR_VERSION);
	        return 0;
	      }
	    else
	      return usage();
	case 'a': autoreload=1; break;
        case 'D': 
          i++; if (argv[i]==NULL) debugflags = -1;
          else debugflags=strtol(argv[i],NULL,16);
          break;
        case 'd': dark=1; break;
        case 'o': break;
        case 'z': scale=SCALE_NORMAL; break;
        case 'h': home=1; break;  
        default: return usage();
      }
    }
  if (argv[i]==NULL || !set_hin_name(argv[i]))
    return usage();
  return 1;	
}

static GLFWcursor *drag_cursor, *hand_cursor, *arrow_cursor;
static int mouse_down=0, drag=0, on_link=0;

static void clear_cursor(void)
{ if (on_link||drag) 
  { glfwSetCursor(window, arrow_cursor); on_link=drag=0;}
}

/* combining the key with the shift, control, alt or super flag */
#define KEY_MOD(K,M) (((K)<<4)|((M)&0xF))
#define KEY(K) KEY_MOD(K,0)
#define CTRL(K) KEY_MOD(K,GLFW_MOD_CONTROL)

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{ static double gamma=1.8;
  if (action!=GLFW_PRESS) return;
  switch (KEY_MOD(key,mods)) {
  case CTRL(GLFW_KEY_A): /* auto reload */
    autoreload=!autoreload;
    if (autoreload)
      goto reload;
  case CTRL(GLFW_KEY_D):
    dark=!dark;
    hint_dark(dark);
    request_render=1;
    break;
  case CTRL(GLFW_KEY_O): /* outlines */
    break;
  case CTRL(GLFW_KEY_F): /* open file dialog */
    break;
  case CTRL(GLFW_KEY_P): /* round position to pixel */
    { static bool rpx=true;
      static double th=1000; /*allmost no threshold*/
      rpx=!rpx;
      hint_round_position(rpx,th);
      request_render=1;
    }
    break;
  case CTRL(GLFW_KEY_KP_ADD): /* round position to pixel */
    { gamma=gamma+0.1;
      if (gamma>4.0) gamma=4.0;
      hint_gamma(gamma);
      request_render=1;
    }
    break;
  case CTRL(GLFW_KEY_KP_SUBTRACT): /* round position to pixel */
    { gamma=gamma-0.1;
      if (gamma<0.1) gamma=0.1;
      hint_gamma(gamma);
      request_render=1;
    }
    break;
  case CTRL(GLFW_KEY_Q):
    glfwSetWindowShouldClose(window,1);
    break;
  case CTRL(GLFW_KEY_R): /* reload */
  reload:
    if (!loading)
    { loading=1;
      HINT_TRY reload_file();
      loading=0;
    }
    clear_cursor();
    break;
  case CTRL(GLFW_KEY_S): /* search */
    break;
  case CTRL(GLFW_KEY_Y): /* US keyboard */
  case CTRL(GLFW_KEY_Z): 
    scale=SCALE_NORMAL;
    hint_resize(px_h,px_v,scale*x_dpi,scale*y_dpi);
    hint_page();
    hint_clear_fonts(false);
    clear_cursor();
    request_render=1;
    break;
  case KEY(GLFW_KEY_HOME):
  case CTRL(GLFW_KEY_H):
    hint_page_home();
    clear_cursor();
    request_render=1;
    break;
  case KEY(GLFW_KEY_PAGE_DOWN):
    pos=hint_page_next();
    hint_page();
    clear_cursor();
    request_render=1;
    break;
  case KEY(GLFW_KEY_PAGE_UP):
    pos=hint_page_prev();
    hint_page();
    clear_cursor();
    request_render=1;
    break;
  default:
    // LOG("key %d, scan %d, action %d, mosd %d\n",key, scancode, action, mods);
    break;
  }
}

/* convert pixel to scaled points (including scale) */

static void mouse_click(void)
{ double x,y;
  int link;
  glfwGetCursorPos(window, &x, &y);
  //LOG("xy= %fx%f\n", x,y);
  HINT_TRY {
    link=hint_find_link(x,y,y_dpi/36); /*about 2pt precission*/ 
    if (link>=0)
    { hint_link_page(link);
      clear_cursor();
      request_render=1;
    }
  }
}

static double x_start, y_start, xy_start, scale_start, time_start;
#define DELTA_T 0.4
#define DELTA_XY 16.0

static void cursor_position_callback(GLFWwindow* window, double x, double y)
{ //LOG("xy= %fx%f\n", x-x_start,y-y_start);
  double f;
  if (!mouse_down)
  { int link;
    link=hint_find_link(x,y,y_dpi/36); /*about 2pt precission*/ 
    if (link>=0 && !on_link)
    { glfwSetCursor(window, hand_cursor); on_link=1; }
    else if (link<0 && on_link)
    { glfwSetCursor(window, arrow_cursor); on_link=0; }
    return;
  }
  if (!drag) /* we dont know whether this is a click or a drag */  
  { double d = (x-x_start)*(x-x_start)+(y-y_start)*(y-y_start);
    if (d<= DELTA_XY)
    { double t=glfwGetTime();
      if (t<=time_start+DELTA_T)
	return;
    }
    /* start dragging */
    drag=1;
    glfwSetCursor(window, drag_cursor);
    xy_start=x_start*x_start+y_start*y_start;
  }
    /* dragging */
  f=(x_start*x+y_start*y)/xy_start; /* projection of (x,y) on (x_start,y_start) */
  scale=scale_start*f;
  if (scale < SCALE_MIN) scale=SCALE_MIN;
  if (scale > SCALE_MAX) scale=SCALE_MAX;
  hint_resize(px_h,px_v,scale*x_dpi,scale*y_dpi);
  hint_page();
  request_render=1;
}


static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{ if (button == GLFW_MOUSE_BUTTON_LEFT)
  { if (action == GLFW_PRESS)
    { glfwGetCursorPos(window, &x_start, &y_start);
      time_start=glfwGetTime();
      scale_start=scale;
      drag=0;
      mouse_down =1;
    }
    else if (action == GLFW_RELEASE)
    { mouse_down=0;
      if (drag) /* end dragging */
      {	hint_clear_fonts(false);
        clear_cursor();
	request_render=1;
      }
      else
        mouse_click();
    }
  }      
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  if (yoffset > 0.0)
  {
    pos=hint_page_prev();
    hint_page();
    clear_cursor();
  } else if (yoffset < 0.0)
  {
    pos=hint_page_next();
    hint_page();
    clear_cursor();
  }
  request_render=1;
}

static void cursor_enter_callback(GLFWwindow* window, int entered)
{ if (entered && autoreload && new_file_time())
    reload_file();
  //LOG("entered=%d auto=%d\n",entered, autoreload);
}

static int create_window(void)
{ if( !glfwInit() )
  {
    hint_error("GLFW", "Failed to initialize GLFW\n" );
    getchar();
    return 0;
  }
  glfwSetErrorCallback(error_callback);
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  /* Open a window and create its OpenGL context */
  window = glfwCreateWindow( px_h, px_v, "HintView", NULL, NULL);
  if( window == NULL ){
    hint_error("GLFW","Failed to open GLFW window.\n"
	   "If you have an Intel GPU, they are not 3.3 compatible.\n"
	   "Try the 2.1 version of the tutorials.\n" );
    glfwTerminate();
    return 0;
  }
  glfwMakeContextCurrent(window);
      
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  
  drag_cursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
  hand_cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
  arrow_cursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);

  //getDPI();
  init_monitors();
  init_dpi(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorEnterCallback(window,cursor_enter_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetCursorPosCallback(window, cursor_position_callback);

  glfwSetCursorPos(window, px_h/2, px_v/2);
 
  hint_render_on();
  return 1;
}

int main(int argc, char *argv[])
{ hlog=stderr;
  if (setjmp(hint_error_exit)!=0) return 1;
  if (!command_line(argc,argv))
    return 1;
   if (!create_window())
    return 1;
  hint_dark(dark);
  hint_resize(px_h,px_v,scale*x_dpi,scale*y_dpi);
  if (!open_file(home))
    return 1;
  request_render=1;
  if (setjmp(hint_error_exit)==0)
    do
    { if (request_render)
      {	request_render=0;
	hint_render();
        glfwSwapBuffers(window);
      }
      glfwWaitEvents();
    } // Check if the Ctrl-Q key was pressed or the window was closed
    while(glfwWindowShouldClose(window) == 0 );
  //  nativeClear();
  glfwDestroyWindow(window); // part of glfwTerminate
  glfwTerminate();
  return 0;
}

