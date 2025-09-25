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

#define DEBUG 1

#define VERSION 2
#define MINOR_VERSION 2
#define REVISION 1

#include "error.h"
#include "basetypes.h"
#include "format.h"
#include "get.h"
#include "hint.h"
#include "rendernative.h"
#line 45 "main.c"
/* Error Handling */
static int hint_error(const char *title, const char *message)
{ fprintf(stderr,"ERROR %s: %s\n",title,message);
  return 0;
}

static void error_callback(int error, const char* description)
{ hint_error("OpenGL",description);
  longjmp(hint_error_exit,1);
}

#define DIR_SEP '/'

/* variables checked before rendering */
static bool dpi_change=FALSE; /*set to call hint_clear_fonts*/
static bool size_change=FALSE; /* set to call hint_resize */
static bool gamma_change=FALSE; /* set to call hint_gamma */


#define SCALE_MIN 0.5
#define SCALE_NORMAL 1.0
#define SCALE_MAX 4.0
static double scale=SCALE_NORMAL;
static uint64_t pos; /* position of current page */

static int px_h=1024, px_v=768; // size in pixel
static double  x_dpi=300, y_dpi=300;
static double gamma=1.8;

static GtkApplication *app;
static GtkWidget *window;
static GtkWidget *area;

#define RENDER gtk_gl_area_queue_render (GTK_GL_AREA(area))

static void
set_monitor_dpi(GdkMonitor* m)
{ GdkRectangle r;
  int w_mm,h_mm,s;
  w_mm = gdk_monitor_get_width_mm (m);
  h_mm = gdk_monitor_get_height_mm (m);
  gdk_monitor_get_geometry (m,&r);
  s=gdk_monitor_get_scale_factor (m);
  x_dpi=25.4*s*r.width/w_mm;
  y_dpi=25.4*s*r.height/h_mm;
  LOG("%s dpi %f x %f\n", gdk_monitor_get_model(m),x_dpi,y_dpi);
}

static void
set_dpi(GtkWidget* a)
{ GdkWindow *w = gtk_widget_get_window(a);
  GdkDisplay* d=gdk_window_get_display (w);
  GdkMonitor* m= gdk_display_get_monitor_at_window (d,w);
  set_monitor_dpi(m);
}

static void
cb_configure(GtkWindow *window, GdkEvent *event, gpointer data)
{ static GdkMonitor *p=NULL;
  static int x=INT_MIN,y=INT_MIN,w=INT_MIN,h=INT_MIN;
  bool rerender=FALSE;
  LOG("Configure\n");
  if (event->configure.x!=x ||event->configure.y!=y)
  { GdkDisplay* d;
    GdkMonitor* m;
    x=event->configure.x;
    y=event->configure.y;
    LOG("Move %d x %d\n",x,y);
    d=gdk_window_get_display (event->configure.window);
    m= gdk_display_get_monitor_at_point (d,x,y);
    if (p!=m)
    { LOG("Monitor %s\n", gdk_monitor_get_model(m));
      gtk_gl_area_make_current (GTK_GL_AREA(area));
      set_monitor_dpi(m);
      dpi_change=size_change=TRUE;
      rerender=1;
      p=m;
    }
  }
  if (event->configure.width!=w ||event->configure.height!=h)
  { px_h=w=event->configure.width;
    px_v=h=event->configure.height;
    size_change=TRUE;
    rerender=TRUE;
    LOG("Size %d x %d\n",w,h);
  }
  if (rerender)
    RENDER;
}

#if 0 /* could not get it to work */
static void
cb_screen_changed (GtkWidget* self,  GdkScreen* previous_screen, gpointer user_data)
{ LOG("Change\n");
  set_dpi(self);
}
#endif

#if 0 /* is not called reliably if using cb_configure */
void cb_resize(  GtkGLArea* self, gint width,  gint height,  gpointer user_data)
{          
   px_h = width;
   px_v = height;
   hint_resize(px_h,px_v,scale*x_dpi,scale*y_dpi);
   hint_page();
   gtk_gl_area_queue_render (self);

   LOG("resize w=%d, h=%d\n",px_h , px_v);
}
#endif

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
    //  strncpy(title_name,hin_name,MAX_PATH);
    //	SetNavigationTree();
   //SetWindowText(hMainWnd,title_name);
  { char *p, *q;
       p=q=hin_name;
    while (*q!=0)
      {  if (*q==DIR_SEP) p=q+1;
	q++;
      }
      gtk_window_set_title (GTK_WINDOW (window), p);
  }
  LOG("File open\n");
return 1;
} 

static void reload_file(void)
{ double fpos=hint_get_fpos();
  hint_end();
  hint_begin();
  pos=hint_set_fpos(fpos);
  LOG("reloading...\n");
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
  {  hint_error("Unknown File Type, I dont know how to open this file", hin_name);
    return 0;
  }
 
  return 1;
}



static gboolean
dialog_key_press_event_cb (GtkWidget *window,
    GdkEvent *event,
    GtkSearchBar *search)
{ LOG("Dialog\n");
  return gtk_search_bar_handle_event (search, event);
}

static int
search_bar(void)
{ static GtkWidget *dialog, *search, *label, *button, *content_area, *entry, *box;
  int res;
  #if 0
  dialog = gtk_dialog_new();
  content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
  #endif
  search = gtk_search_bar_new ();
  gtk_container_add (GTK_CONTAINER (window), search);
  gtk_widget_show (search);
  box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 6);
  gtk_container_add (GTK_CONTAINER (search), box);
  gtk_widget_show (box);
  entry = gtk_search_entry_new ();
  gtk_box_pack_start (GTK_BOX (box), entry, TRUE, TRUE, 0);
  gtk_widget_show (entry);
  gtk_search_bar_connect_entry (GTK_SEARCH_BAR (search), GTK_ENTRY (entry));
  g_signal_connect (dialog, "key-press-event",
                    G_CALLBACK (dialog_key_press_event_cb),
                    search);
  gtk_widget_show_all (window);

			 //res = gtk_dialog_run (GTK_DIALOG (dialog));

  
#if 0
  //GtkWidget *window;
  GtkWidget *search_bar;
  GtkWidget *box;
  GtkWidget *entry;
  GtkWidget *menu_button;
  //window = gtk_application_window_new (app);
  //gtk_widget_show (window);
  search_bar = gtk_search_bar_new ();
  gtk_container_add (GTK_CONTAINER (window), search_bar);
  gtk_widget_show (search_bar);
  //box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 6);
  //gtk_container_add (GTK_CONTAINER (search_bar), box);
  //gtk_widget_show (box);
  entry = gtk_search_entry_new ();
  gtk_box_pack_start (GTK_BOX (box), entry, TRUE, TRUE, 0);
  gtk_widget_show (entry);
  menu_button = gtk_menu_button_new ();
  gtk_box_pack_start (GTK_BOX (box), menu_button, FALSE, FALSE, 0);
  gtk_widget_show (menu_button);
  gtk_search_bar_connect_entry (GTK_SEARCH_BAR (search_bar), GTK_ENTRY (entry));
  g_signal_connect (window, "key-press-event",
                    G_CALLBACK (window_key_press_event_cb),
                    search_bar);
#endif  
  return 0;
}


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

static int set_input_file(char *fn)
{ 
  if (fn!=NULL)
    return set_hin_name(fn);
  else  
    return file_chooser();
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
   "  -n         Start in night mode.\n"	  
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
	      { fprintf(stdout,"hintview version %d.%d.%d\n"
			"HINT file format version %d.%d\n", 
			VERSION, MINOR_VERSION, REVISION,
			HINT_VERSION, HINT_MINOR_VERSION);
	        return 0;
	      }
	    else
	      return usage();
	case 'a': autoreload=1; break;
        case 'd': 
          i++; if (argv[i]==NULL) debugflags = -1;
          else debugflags=strtol(argv[i],NULL,16);
          break;
        case 'n': dark=1; break;
        case 'o': break;
        case 'z': scale=SCALE_NORMAL; break;
        case 'h': home=1; break;  
        default: return usage();
      }
    }
  if (argv[i]!=NULL && !set_input_file(argv[i]))
    return usage();
  return 1;	
}

static void
cb_realize (GtkGLArea *area)
  {
    set_dpi(GTK_WIDGET(area));
    // We need to make the context current if we want to
    // call GL API
    gtk_gl_area_make_current (area);

    // If there were errors during the initialization or
    // when trying to make the context current, this
    // function will return a `GError` for you to catch
    if (gtk_gl_area_get_error (area) != NULL)
      return;
    gtk_gl_area_set_auto_render (area,FALSE);

    hint_render_on();
    hint_dark(dark);
    if (!open_file(home))
      return;
    gtk_gl_area_queue_render (area);
    LOG("Realize\n");
}

static void
cb_unrealize (GtkGLArea* area, gpointer user_data)
{ gtk_gl_area_make_current (area);
  hint_render_off();
  LOG("Unrealize");
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
	hint_gamma(gamma);
    }
    if (dpi_change)
      { dpi_change=FALSE;
	hint_clear_fonts(false);
      }
    if (size_change)
      { size_change=FALSE;
	hint_resize(px_h,px_v,scale*x_dpi,scale*y_dpi);
        hint_page();
      }
    
    hint_render();
    LOG("Render\n");

    // we completed our drawing; the draw commands will be
    // flushed at the end of the signal emission chain, and
    // the buffers will be drawn on the window
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
  if (!is_scaling) /*we dont know whether this is a click or a drag */  
  { d = (x-down_x)*(x-down_x)+(y-down_y)*(y-down_y);
    if (d<=DELTA_XY && event->time-down_time <= DELTA_T)
      return TRUE; /* click */
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
  return TRUE;
}

static gboolean
cb_key_press(GtkWidget* widget, GdkEventKey* event, gpointer data)
{
  if (event->state & GDK_CONTROL_MASK)
  switch (event->keyval)
  { case GDK_KEY_a: /* auto reload */
    autoreload=!autoreload;
    if (autoreload)
      goto reload;
  case GDK_KEY_f: /* file */
    if (set_input_file(NULL))
    { open_file(home);
      RENDER;
    }
    break;
  case GDK_KEY_n:
    dark=!dark;
    gtk_gl_area_make_current (GTK_GL_AREA(area));
    hint_dark(dark);
    //LOG("Dark %d\n",dark);
    RENDER;
    break;
  case GDK_KEY_o: /* outlines */
    break;
  case GDK_KEY_p: /* round position to pixel */
    { static bool rpx=true;
      static double th=1000; /*allmost no threshold*/
      rpx=!rpx;
      gtk_gl_area_make_current (GTK_GL_AREA(area));
      hint_round_position(rpx,th);
      LOG("Round to pixel %d\n",rpx);
      RENDER;
    }
    break;
  case GDK_KEY_q:
    g_application_quit(G_APPLICATION (app));
    //gtk_application_remove_window(app,GTK_WINDOW (window));
    break;
  case GDK_KEY_r: /* reload */
  reload:
    if (!loading)
    { loading=1;
      HINT_TRY reload_file();
      loading=0;
      RENDER;
    }
    //clear_cursor();
    break;

  case GDK_KEY_s: /* search */
    search_bar();
    break;

  case GDK_KEY_z: 
    scale=SCALE_NORMAL;
    dpi_change=size_change=TRUE;
    RENDER;
    //clear_cursor();
    break;
  case GDK_KEY_h:
  //case KEY(GLFW_KEY_HOME:
    HINT_TRY hint_page_home();
    RENDER;
    //clear_cursor();
    break;
  default:
    if (event->length > 0)
      LOG("The key event's string is `%s'\n", event->string);
    LOG("The name of this keysym is `%s'\n", gdk_keyval_name(event->keyval));
    break;
  }
  else
  switch (event->keyval)  {
  case GDK_KEY_KP_Add: /* increase gamma */
    { gamma=gamma+0.1;
      if (gamma>4.0) gamma=4.0;
      gamma_change=TRUE;
      RENDER;
    }
    break;
  case GDK_KEY_KP_Subtract: /* decrease gamma */
    { gamma=gamma-0.1;
      if (gamma<0.1) gamma=0.1;
      gamma_change=TRUE;
      RENDER;
    }
    break;
  case GDK_KEY_Page_Down:
    pos=hint_page_next();
    hint_page();
    RENDER;
    //clear_cursor();
    break;
  case GDK_KEY_Page_Up:
    pos=hint_page_prev();
    hint_page();
    RENDER;
    //clear_cursor();
    break;
  case GDK_KEY_Home:
    HINT_TRY hint_page_home();
    RENDER;
    //clear_cursor();
    break;
  default:
    if (event->length > 0)
      LOG("The key event's string is `%s'\n", event->string);
    LOG("The name of this keysym is `%s'\n", gdk_keyval_name(event->keyval));
    break;
    }
  return TRUE;
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{ window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "hintview");
  gtk_window_set_default_size (GTK_WINDOW (window), px_h, px_v);
  g_signal_connect(G_OBJECT(window), "configure-event", G_CALLBACK(cb_configure), NULL);
  g_signal_connect (G_OBJECT (window), "key_press_event", G_CALLBACK (cb_key_press), NULL);
  area= gtk_gl_area_new();
  g_signal_connect (area, "render", G_CALLBACK (cb_render), NULL);
  g_signal_connect (area, "realize", G_CALLBACK (cb_realize), NULL);
  g_signal_connect (area, "unrealize", G_CALLBACK (cb_unrealize), NULL);
  //g_signal_connect (area, "resize", G_CALLBACK (cb_resize), NULL);
  gtk_container_add (GTK_CONTAINER (window), area);

  gtk_widget_set_events (area, GDK_BUTTON_PRESS_MASK
		       | GDK_BUTTON_RELEASE_MASK
		       | GDK_BUTTON1_MOTION_MASK );
   g_signal_connect (area, "button_press_event", G_CALLBACK (cb_mouse_button_down), NULL);
   g_signal_connect (area, "button_release_event", G_CALLBACK (cb_mouse_button_up), NULL);
   g_signal_connect (area, "motion_notify_event", G_CALLBACK (cb_mouse_motion), NULL);
   gamma_change=TRUE;
   gtk_widget_show_all (window);
}

int main (int argc, char *argv[])
{ 
  int status;

  hlog=stderr;
  if (setjmp(hint_error_exit)!=0) return 1;
  if (!command_line(argc,argv))  return 1;

  app = gtk_application_new ("edu.hm.cs.hintview", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), 0, NULL);
  g_object_unref (app);

  return status;
}

