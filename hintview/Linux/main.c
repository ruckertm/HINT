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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <GL/gl.h>
#include <setjmp.h>


//define DEBUG 1

#include "main.h"
#include "error.h"
#include "basetypes.h"
#include "format.h"
#include "get.h"
#include "hint.h"
#include "rendernative.h"
#include "gui.h"
#include "resources.h"

/* Error Handling */

#if 0 /* not yet used */
static void error_callback(int error, const char* description)
{ hint_error("OpenGL",description);
  longjmp(hint_error_exit,1);
}
#endif


/* variables checked before rendering */

static bool dpi_change=FALSE; /*set to call hint_clear_fonts*/
static bool size_change=FALSE; /* set to call hint_resize */
static bool gamma_change=FALSE; /* set to call hint_gamma */
 
/* global state variables */

#define SCALE_MIN 0.5
#define SCALE_NORMAL 1.0
#define SCALE_MAX 4.0
double scale=SCALE_NORMAL;
guint64 position; /* position of current page */
gchar *document=NULL;

static int px_h=1024, px_v=768; // size in pixel
static double  x_dpi=300, y_dpi=300;
double gcorrection=1.8;

int dark = FALSE, autoreload=FALSE, home=FALSE;

int rpx=TRUE;
double rpxthreshold=160;

static GtkApplication *app;
static GtkWidget *window;
static GtkWidget *area;

/* System utilities */
static int
set_monitor_dpi(GdkMonitor* m)
{ GdkRectangle r;
  int w_mm,h_mm,s;
  double new_x_dpi, new_y_dpi;
  w_mm = gdk_monitor_get_width_mm (m);
  h_mm = gdk_monitor_get_height_mm (m);
  gdk_monitor_get_geometry (m,&r);
  s=gdk_monitor_get_scale_factor (m);
  new_x_dpi=25.4*s*r.width/w_mm;
  new_y_dpi=25.4*s*r.height/h_mm;
  LOG("%s dpi %f x %f\n", gdk_monitor_get_model(m),x_dpi,y_dpi);
  if (new_x_dpi!=x_dpi || new_y_dpi!=y_dpi)
  { x_dpi=new_x_dpi;
    y_dpi=new_y_dpi;
    LOG("Scale factor %d, mm=%d, px=%d\n",s,w_mm,r.width);
    return 1;
  }
  else
    return 0;
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

/* Interface to the hintview backend */

#define RENDER gtk_gl_area_queue_render (GTK_GL_AREA(area)) /* invoke the renderer */

void hint_unmap(void)
{ hget_unmap(); 
}

bool hint_map(void)
{ if (hin_name!=NULL && hin_name[0]!=0)
  return hget_map();
  else
    return false;
}

static char *search_buf=NULL;
static int search_len=0;
int search_string(const char *str)
  { int len = strlen(str);
    if (len<search_len)
      strncpy(search_buf,str,search_len);
    else
      { free(search_buf); search_len=0;
	search_buf=strdup(str);
	if (search_buf==NULL) return FALSE; /* just in case */
	search_len=len;
      }
  hint_set_mark(search_buf,len);
  RENDER;
  return TRUE;
}

int find_next(int next)
{ uint64_t h=hint_page_get();
  bool success;
  HINT_TRY{
  if(next)
    success=hint_next_mark();
 else
   success=hint_prev_mark();
  if (!success)
	hint_page_top(h);
  RENDER;
  return success;
  }
  else
    return 0;
}



void goto_outline(int i)
{ hint_outline_page(i);
  RENDER;
}

#define DIR_SEP '/'

static int open_file(int home)
{
  LOG("File open %d\n", home);
  HINT_TRY {
  hint_end();
  if (!hint_begin())
    return 0;
  if (home)
    hint_page_home();
  else
    hint_page_top(0);
  if (document!=NULL) free(document);
  document=strdup(hin_name);
  outlines_set();
  { char *p, *q;
       p=q=hin_name;
    while (*q!=0)
      {  if (*q==DIR_SEP) p=q+1;
	q++;
      }
      gtk_window_set_title (GTK_WINDOW (window), p);
  }
  LOG("File open\n");
  }
  else
    return 0;
return 1;
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
  {  hint_error("Unknown File Type, I don't know how to open this file", hin_name);
    return 0;
  }
 
  return 1;
}


/* the file chooser should probably move to a separate file */

static int file_chooser(void)
{ GtkWidget *dialog;
  GtkFileFilter *filter;
  gint res;

  dialog = gtk_file_chooser_dialog_new ("Open File",
					NULL,/* no parent */
                                      GTK_FILE_CHOOSER_ACTION_OPEN,
                                      "_Cancel", GTK_RESPONSE_CANCEL,
                                      "_Open", GTK_RESPONSE_ACCEPT,
                                      NULL);
  
  filter = gtk_file_filter_new();
  gtk_file_filter_set_name( filter, "HINT file" );
  gtk_file_filter_add_pattern( filter, "*.hnt");
  gtk_file_chooser_add_filter( GTK_FILE_CHOOSER(dialog), filter );

  res = gtk_dialog_run (GTK_DIALOG (dialog));
  if (res == GTK_RESPONSE_ACCEPT)
  { char *fn;
    fn = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
    res=set_hin_name(fn);
    g_free (fn);
  }
  else
    res=0;
  gtk_widget_destroy (dialog);
  while (gtk_events_pending()) gtk_main_iteration();
  return res;
}



/* Actions */

void do_open_file(void)
{ if (file_chooser())
  { open_file(home);
    RENDER;
  }
}

void do_reload(void)
{ static int loading=0;
  if (!loading)
    { double fpos;
      loading=1;
      LOG("reloading...\n");
      HINT_TRY {
        fpos=hint_get_fpos();
        hint_end();
        hint_begin();
        position=hint_set_fpos(fpos);
      }
      //clear_cursor();
      loading=0;
      RENDER;
    }
}

int do_dark(int toggle)
{ if (toggle) dark=!dark;
  set_dark_button(dark);
  gtk_gl_area_make_current (GTK_GL_AREA(area));
  hint_dark(dark);
  LOG("Dark %d\n",dark);
  RENDER;
  return dark;
}

void do_zoom_1(void)
{ scale=SCALE_NORMAL;
  dpi_change=size_change=TRUE;
  RENDER;
  //clear_cursor();
}

void do_rpx(void) /* round glyph positions to pixel */
{ gtk_gl_area_make_current (GTK_GL_AREA(area));
  hint_round_position(rpx,rpxthreshold);
  LOG("Round to pixel %d\n",rpx);
}


void do_home(void)
{ HINT_TRY{
    hint_page_home();
    RENDER;
  //clear_cursor();
  }
}

void do_outlines(void)
{  outlines_open(window);
}

void do_find(void)
{  search_open(window);
}

void do_quit(void)
{ g_application_quit(G_APPLICATION (app));
  //gtk_application_remove_window(app,GTK_WINDOW (window));
}



void do_render(int d, int s, int g)
{ dpi_change|=d;
  size_change|=s;
  gamma_change|=g;
  RENDER;
}

/* OpenGL area callbacks */

static void
cb_realize (GtkGLArea *area)
  { LOG("Realize\n");
    //   set_dpi(GTK_WIDGET(area));
    // We need to make the context current if we want to
    // call GL API


    gtk_gl_area_make_current (area);

    // If there were errors during the initialization or
    // when trying to make the context current, this
    // function will return a `GError` for you to catch
    if (gtk_gl_area_get_error (area) != NULL)
      return;
    gtk_gl_area_set_auto_render (area,FALSE);
    HINT_TRY{
      hint_render_on();
      hint_dark(dark);
      do_dark(0);
      if (!open_file(home))
        return;
      do_render(1,1,1);
    }
    LOG("Realize Done\n");
}

static void
cb_unrealize (GtkGLArea* area, gpointer user_data)
{ gtk_gl_area_make_current (area);
  hint_render_off();
  LOG("Unrealize\n");
}

static GdkGLContext* cb_create_context (GtkGLArea* self, gpointer user_data)
{ GdkGLContext* c;
  GError* error=NULL;
  GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(self));
  c = gtk_gl_area_get_context(self);

 if (c!=NULL)
   LOG("Has context\n");
 else
 {   LOG("Has no context\n");
     c = gdk_window_create_gl_context (gdk_window,&error);
     if (c!=NULL)
       LOG("Has context\n");
     gdk_gl_context_set_required_version (c,3,3);
 }
  LOG("Create Context\n");
 
  return c;

}
static gboolean
cb_render (GtkGLArea *area, GdkGLContext *context)
  {
    // inside this function it's safe to use GL; the given
    // `GdkGLContext` has been made current to the drawable
   // surface used by the `GtkGLArea` and the viewport has
    // already been set to be the size of the allocation
    if (gamma_change)
    { gamma_change=FALSE;
	hint_gamma(gcorrection);
    }
    if (dpi_change)
      { dpi_change=FALSE;
	hint_clear_fonts(false);
      }
    if (size_change)
      { size_change=FALSE;
	HINT_TRY{
	hint_resize(px_h,px_v,scale*x_dpi,scale*y_dpi);
        hint_page();
	}
      }
    HINT_TRY hint_render();
    LOG("Render\n");

    // we completed our drawing; the draw commands will be
    // flushed at the end of the signal emission chain, and
    // the buffers will be drawn on the window
    return TRUE;
  }


static gboolean
cb_scroll( GtkEventControllerScroll* self,  gdouble dx,  gdouble dy,  gpointer user_data)
{ if (dy > 0.0)
    { HINT_TRY { position=hint_page_next();
    hint_page();
    //clear_cursor();
      }
    RENDER;
  }
  else if (dy< 0.0)
    { HINT_TRY{ position=hint_page_prev();
    hint_page();
    //clear_cursor();
    }
    RENDER;
  }
  return TRUE;
}

static gboolean
cb_enter_notify_event (  GtkWidget* self, GdkEventCrossing event,  gpointer user_data)
{ if (autoreload && event.focus && new_file_time())
    do_reload();
  return TRUE;
} 

static double down_x, down_y, down_xy, down_scale;
static uint32_t down_time;
static gboolean is_scaling;

static gboolean cb_mouse_button_down(GtkWidget *area, GdkEventButton *event, gpointer data)
{ if (event->button!=1) return FALSE;
  down_x=event->x;
  down_y=event->y;
  down_time=event->time;
  down_scale=scale;
  is_scaling=FALSE;
  LOG("Mouse button down %d,%d,  %f x %f\n", event->type,event->button, down_x-event->x, down_y-event->y);
  return TRUE;
}

#define DELTA_T 400
#define DELTA_XY 16.0
static gboolean cb_mouse_motion(GtkWidget *area, GdkEventMotion *event, gpointer data)
{ double x,y,d,f;
  x=event->x;
  y=event->y;
  LOG("Mouse move %f x %f \n", x-down_x, y-down_y);
  if (!is_scaling) /*we don't know whether this is a click or a drag */  
  { d = (x-down_x)*(x-down_x)+(y-down_y)*(y-down_y);
    if (d<=DELTA_XY && event->time-down_time <= DELTA_T)
      return TRUE; /* still don't know */
    is_scaling=TRUE;
    down_xy=down_x*down_x+down_y*down_y;
  }
  f=(down_x*x+down_y*y)/down_xy; /* projection of (x,y) on (down_x,down_y) */
  scale=down_scale*f;
  if (scale < SCALE_MIN) scale=SCALE_MIN;
  if (scale > SCALE_MAX) scale=SCALE_MAX;
  size_change=TRUE;
  RENDER;
  return TRUE;
}


static gboolean cb_mouse_button_up(GtkWidget *area, GdkEventButton *event, gpointer data)
{ if (event->button!=1) return FALSE;
  LOG("Mouse up %d,  %f x %f\n", event->time-down_time, down_x-event->x, down_y-event->y);
  if (is_scaling)
  { dpi_change=TRUE;
    is_scaling=FALSE;
    RENDER;
  }
  else /* click */
  { int link;
    LOG("Click %f x %f\n",down_x,down_y);
    HINT_TRY {
      link=hint_find_link((int)(down_x+0.5), (int)(down_y+0.5), y_dpi/36);
      if (link>=0)
        hint_link_page(link);
    }
    RENDER;
  }
  return TRUE;
}


/* window callbacks */
static gboolean
cb_key_press(GtkWidget* widget, GdkEventKey* event, gpointer data)
{
  if (event->state & GDK_CONTROL_MASK)
  switch (event->keyval)
  { case GDK_KEY_a: /* auto reload */
    autoreload=!autoreload;
    if (autoreload) do_reload();
    break;
  case GDK_KEY_d: do_dark(1); break;
  case GDK_KEY_f: do_find(); break;
  case GDK_KEY_g: find_next(TRUE); break;
  case GDK_KEY_h: do_home();   break;
  case GDK_KEY_o: do_open_file(); break;
#if 0 /*this doesnt seem to work on a GTK3 glarea*/
  case GDK_KEY_x: /* round position to pixel */
    { rpx=!rpx;
      do_rpx();
      do_render(0,0,0);
   }
   break;
#endif
  case GDK_KEY_p: do_preferences(); break;
  case GDK_KEY_q: do_quit();   break;
  case GDK_KEY_r: do_reload(); break;
  case GDK_KEY_t: do_outlines(); break;
  case GDK_KEY_z: do_zoom_1(); break;
  default:
    if (event->length > 0)
      LOG("The key event's string is `%s'\n", event->string);
    LOG("The name of this keysym is `%s'\n", gdk_keyval_name(event->keyval));
    break;
  }
  else
  switch (event->keyval)  {
  case GDK_KEY_KP_Add: /* increase gcorrection */
    { gcorrection=gcorrection+0.1;
      if (gcorrection>4.0) gcorrection=4.0;
      gamma_change=TRUE;
      RENDER;
    }
    break;
  case GDK_KEY_KP_Subtract: /* decrease gcorrection */
    { gcorrection=gcorrection-0.1;
      if (gcorrection<0.1) gcorrection=0.1;
      gamma_change=TRUE;
      RENDER;
    }
    break;
  case GDK_KEY_Page_Down:
    HINT_TRY{
      position=hint_page_next();
      hint_page();
      RENDER;
    //clear_cursor();
    }
    break;
  case GDK_KEY_Page_Up:
    HINT_TRY{
      position=hint_page_prev();
      hint_page();
      RENDER;
      //clear_cursor();
    }
    break;
  case GDK_KEY_Home: do_home(); break;
  default:
    if (event->length > 0)
      LOG("The key event's string is `%s'\n", event->string);
    LOG("The name of this keysym is `%s'\n", gdk_keyval_name(event->keyval));
    break;
    }
  return TRUE;
}

static void
cb_configure(GtkWindow *window, GdkEvent *event, gpointer data)
{ //static GdkMonitor *p=NULL;
  static int x=INT_MIN,y=INT_MIN,w=INT_MIN,h=INT_MIN;
  bool rerender=FALSE;
  GtkAllocation a;
  LOG("Configure %d\n",event->type);
  //  if (event->configure.x!=x ||event->configure.y!=y)
  // LOG("Move %d x %d\n",x,y);
  if (event->type==GDK_CONFIGURE)
  { GdkDisplay* d;
    GdkMonitor* m;
    x=event->configure.x;
    y=event->configure.y;
    d=gdk_window_get_display (event->configure.window);
    m= gdk_display_get_monitor_at_point (d,x,y);
    //if (p!=m)
    { LOG("Monitor %s\n", gdk_monitor_get_model(m));
      gtk_gl_area_make_current (GTK_GL_AREA(area));
      if (set_monitor_dpi(m))
      { dpi_change=size_change=TRUE;
        rerender=TRUE;
      }
      //p=m;
    }
  }
  gtk_widget_get_allocation (area,&a);
  if (a.width!=w || a.height!=h)
  { 
    px_h=w=a.width;
    px_v=h=a.height;  
    size_change=TRUE;
    rerender=TRUE;
    LOG("Size %d x %d or %d x %d\n",w,h,a.width,a.height);
  }
  LOG("Configure done\n");
  if (rerender)
    RENDER;
}



static void
activate (GtkApplication *app,
          gpointer        user_data)
{ GtkEventController* scroll_controler;

  LOG("Activate\n");
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "HintView");
  gtk_window_set_default_size (GTK_WINDOW (window), px_h, px_v);

  g_signal_connect(G_OBJECT(window), "configure-event", G_CALLBACK(cb_configure), NULL);
  g_signal_connect (G_OBJECT (window), "key_press_event", G_CALLBACK (cb_key_press), NULL);

  area= gtk_gl_area_new();
  g_signal_connect (area, "render", G_CALLBACK (cb_render), NULL);
  g_signal_connect (area, "realize", G_CALLBACK (cb_realize), NULL);
  g_signal_connect (area, "create-context", G_CALLBACK (cb_create_context), NULL);
  g_signal_connect (area, "unrealize", G_CALLBACK (cb_unrealize), NULL);

  scroll_controler= gtk_event_controller_scroll_new (area,
		   GTK_EVENT_CONTROLLER_SCROLL_VERTICAL
		 | GTK_EVENT_CONTROLLER_SCROLL_DISCRETE);
  g_signal_connect (scroll_controler, "scroll", G_CALLBACK (cb_scroll), NULL);

  gtk_container_add (GTK_CONTAINER (window), area);

  gtk_widget_set_events (area, GDK_BUTTON_PRESS_MASK
		       | GDK_BUTTON_RELEASE_MASK
		       | GDK_BUTTON1_MOTION_MASK
		       | GDK_ENTER_NOTIFY_MASK
		       );
  g_signal_connect (area, "button_press_event", G_CALLBACK (cb_mouse_button_down), NULL);
  g_signal_connect (area, "button_release_event", G_CALLBACK (cb_mouse_button_up), NULL);
  g_signal_connect (area, "motion_notify_event", G_CALLBACK (cb_mouse_motion), NULL);
  g_signal_connect (area, "enter-notify-event", G_CALLBACK (cb_enter_notify_event), NULL);

  gtk_window_set_titlebar (GTK_WINDOW (window), create_headerbar());
  LOG("Show all\n");
  gtk_widget_show_all (window);
  LOG("Activate done\n"); 
}


static int usage(void)
{ fprintf(stderr,"Usage: hintview [options] [file]\n"
                 "Call 'hintview --help' for details.\n");
  return 0;
}

static int help(void)
{ fprintf(stdout,"%s",
   "Usage: hintview [options] [file]\n"
   "Options:\n"
   "  -a         Start in autoreload mode.\n"	  
   "  -h         Start with the documents home page.\n"	  
   "  -d         Start in dark mode.\n"	  
#if 0
   "  -o         Show the documents outline.\n"
#endif
   "  -z         Start with zoom level 100%.\n"	  
   "  --help     Display this message.\n"	  
   "  --version  Display the version.\n"	  
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
	      { fprintf(stdout,"HintView version %d.%d.%d\n"
			"HINT file format version %d.%d\n", 
			VERSION, MINOR_VERSION, REVISION,
			HINT_VERSION, HINT_MINOR_VERSION);
	        return 0;
	      }
	    else
	      return usage();
	case 'a': autoreload=1; break;
#ifdef DEBUG
      case 'D': 
          i++; if (argv[i]==NULL) debugflags = -1;
          else debugflags=strtol(argv[i],NULL,16);
          break;
#endif	  
        case 'd': dark=1; break;
	  //case 'o': break; /* show outlines */
        case 'z': scale=SCALE_NORMAL; break;
        case 'h': home=1; break;  
        default: return usage();
      }
    }
  if (argv[i]!=NULL && !set_hin_name(argv[i]))
    return usage();
  return 1;	
}

int main (int argc, char *argv[])
{ 
  int status;
  GSettings *settings;
  GResource *resources;
  
  hlog=stderr;
  if (setjmp(hint_error_exit)!=0) return 1;

  settings = g_settings_new("edu.hm.cs.hintview");
  read_settings(settings);
  if (document!=NULL && document[0]!=0) set_hin_name(document);
  if (!command_line(argc,argv))  return 1;


  resources=resources_get_resource ();
  g_resources_register (resources);

  app = gtk_application_new ("edu.hm.cs.hintview", G_APPLICATION_NON_UNIQUE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  
  status = g_application_run (G_APPLICATION (app), 0, NULL);
  write_settings(settings);
  g_resources_unregister (resources);
  g_object_unref (app);

  return status;
}

