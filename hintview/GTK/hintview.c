#include <gtk/gtk.h>
#include <GL/gl.h>

#include <setjmp.h>
#include "error.h"
#include "basetypes.h"

#include "rendernative.h"

static double  x_dpi=300, y_dpi=300;

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
  g_print("%s dpi %f x %f\n", gdk_monitor_get_model(m),x_dpi,y_dpi);
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
  GdkDisplay* d=gdk_window_get_display (event->configure.window);
  int x=event->configure.x, y=event->configure.y;
  GdkMonitor* m= gdk_display_get_monitor_at_point (d,x,y);
  if (p!=m)
    { g_print("Move %d x %d: %s\n",x,y, gdk_monitor_get_model(m));
      p=m;
      set_monitor_dpi(m);
    }
}

#if 0 /* could not get it to work */
static void
cb_screen_changed (GtkWidget* self,  GdkScreen* previous_screen, gpointer user_data)
{ g_print("Change\n");
  set_dpi(self);
}
#endif

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
    nativeInit();
}

int w=400,h=300;

static gboolean
  cb_render (GtkGLArea *area, GdkGLContext *context)
  {
    // inside this function it's safe to use GL; the given
    // `GdkGLContext` has been made current to the drawable
    // surface used by the `GtkGLArea` and the viewport has
    // already been set to be the size of the allocation
#define ONE 0x10000
   
    nativeSetSize(w, h, 72.27*w*ONE/x_dpi, 72.27*h*ONE/y_dpi);
    nativeBlank(0x80808000);
    nativeRule(10*ONE,50*ONE,30*ONE,40*ONE);
    g_print("render\n");

    // we completed our drawing; the draw commands will be
    // flushed at the end of the signal emission chain, and
    // the buffers will be drawn on the window
    return TRUE;
  }


void cb_resize(  GtkGLArea* self, gint width,  gint height,  gpointer user_data)
{          
   w = width;
   h = height;
   g_print(" resize w=%d, h=%d\n", w, h);
}


static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window, *area;

 
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "hintview");
  gtk_window_set_default_size (GTK_WINDOW (window), 400, 300);
  g_signal_connect(G_OBJECT(window), "configure-event", G_CALLBACK(cb_configure), NULL);

  area= gtk_gl_area_new();
  gtk_container_add (GTK_CONTAINER (window), area);
  g_signal_connect (area, "render", G_CALLBACK (cb_render), NULL);
  g_signal_connect (area, "realize", G_CALLBACK (cb_realize), NULL);
  g_signal_connect (area, "resize", G_CALLBACK (cb_resize), NULL);
  
  gtk_widget_show_all (window);
}

FILE *hlog;
char hint_error_string[1024];

void hint_end(void)
{}

jmp_buf hint_error_exit;

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  hlog=stderr;
  if (setjmp(hint_error_exit)!=0) return 1;

  app = gtk_application_new ("edu.hm.cs.hintview", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
