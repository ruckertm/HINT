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
#include <GL/gl.h>
#include <setjmp.h>

#define VERSION 2
#define MINOR_VERSION 2
#define REVISION 1

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

#define SCALE_MIN 0.2
#define SCALE_NORMAL 1.0
#define SCALE_MAX 5.0
static double scale=SCALE_NORMAL;
static uint64_t pos; /* position of current page */

static int px_h=1024, px_v=768; // size in pixel
static double  x_dpi=300, y_dpi=300;

GtkWidget *area;


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
      set_monitor_dpi(m);
      hint_clear_fonts(false);
      rerender=TRUE;
      p=m;
    }
  }
  if (event->configure.width!=w ||event->configure.height!=h)
  { px_h=w=event->configure.width;
    px_v=h=event->configure.height;
    hint_resize(px_h,px_v,scale*x_dpi,scale*y_dpi);
    hint_page();
    rerender=TRUE;
    LOG("Size %d x %d\n",w,h);
  }
  if (rerender)
    gtk_gl_area_queue_render (GTK_GL_AREA(area));
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
  LOG("File open\n");
return 1;
} 

static void reload_file(void)
{ double fpos=hint_get_fpos();
  hint_end();
  hint_begin();
  pos=hint_set_fpos(fpos);
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
    //hint_render();
    LOG("Realize\n");
}

static void
cb_unrealize (GtkGLArea* area, gpointer user_data)
{ gtk_gl_area_make_current (area);
  nativeClear();
  LOG("Unrealize");
}

int w=400,h=300;

static gboolean
  cb_render (GtkGLArea *area, GdkGLContext *context)
  {
    // inside this function it's safe to use GL; the given
    // `GdkGLContext` has been made current to the drawable
    // surface used by the `GtkGLArea` and the viewport has
    // already been set to be the size of the allocation
#if 0
    nativeSetSize(w, h, 72.27*w*ONE/x_dpi, 72.27*h*ONE/y_dpi);
    nativeBlank(0x80808000);
    nativeRule(10*ONE,50*ONE,30*ONE,40*ONE);
#endif
    hint_render();
    LOG("Render\n");

    // we completed our drawing; the draw commands will be
    // flushed at the end of the signal emission chain, and
    // the buffers will be drawn on the window
    return TRUE;
  }



static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;

 
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "hintview");
  gtk_window_set_default_size (GTK_WINDOW (window), px_h, px_v);
  g_signal_connect(G_OBJECT(window), "configure-event", G_CALLBACK(cb_configure), NULL);

  area= gtk_gl_area_new();
  g_signal_connect (area, "render", G_CALLBACK (cb_render), NULL);
  g_signal_connect (area, "realize", G_CALLBACK (cb_realize), NULL);
  //g_signal_connect (area, "unrealize", G_CALLBACK (cb_unrealize), NULL);
  //g_signal_connect (area, "resize", G_CALLBACK (cb_resize), NULL);
  gtk_container_add (GTK_CONTAINER (window), area);

  gtk_widget_show_all (window);

  
}


int main (int argc, char **argv)
{ GtkApplication *app;
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
