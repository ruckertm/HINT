#include <gtk/gtk.h>
#include "basetypes.h"
#include "main.h"
#include "gui.h"

#define SR_BOOL(VAL) VAL=g_settings_get_boolean(settings,#VAL) 
#define SR_DOUBLE(VAL) VAL=g_settings_get_double(settings,#VAL) 
#define SR_INT(VAL) VAL=g_settings_get_int(settings,#VAL) 

void read_settings(GSettings *settings)
{ SR_BOOL(autoreload); 
  SR_BOOL(dark);
  SR_BOOL(home);
  SR_DOUBLE(gcorrection); 
  SR_DOUBLE(scale);
  SR_DOUBLE(rpxthreshold);
  SR_BOOL(rpx);
  SR_INT(buttonvisibility);
  position=g_settings_get_uint64(settings,"position");
  document=g_settings_get_string(settings,"document");
  LOG("Reading buttons=%x\n", buttonvisibility);
}

#define SW_BOOL(VAL) fail|=! g_settings_set_boolean (settings,#VAL,VAL)
#define SW_DOUBLE(VAL) fail|=! g_settings_set_double (settings,#VAL,VAL)
#define SW_INT(VAL) fail|=! g_settings_set_int (settings,#VAL,VAL)

void write_settings(GSettings *settings)
{ gboolean fail=FALSE;
  
  SW_BOOL(autoreload);
  SW_BOOL(dark);
  SW_BOOL(home);
  SW_DOUBLE(gcorrection);
  SW_DOUBLE(scale);
  SW_BOOL(rpx);
  SW_DOUBLE(rpxthreshold);
  SW_INT(buttonvisibility);
  LOG("Writing buttons=%x\n", buttonvisibility);

  fail|=! g_settings_set_uint64 (settings,"position",position);
  fail|=! g_settings_set_string (settings,"document",document);
  if (fail)
    LOG("Failing to write all settings\n");
}


#if 0
void do_settings(void)
{
  GSettings *settings = g_settings_new("edu.hm.cs.hintview");
  if (settings!=NULL)
    LOG("Settings created\n");
  read_settings(settings);
  //LOG("autoreload=%d\n",autoreload);
  gcorrection=gcorrection+0.01;
  autoreload=!autoreload;
  LOG("Position=0x%lx\n",position);
  position+=0x100000001;
  write_settings(settings);
}

int
main(int argc, char **argv)
{
    GtkWidget *window;

    gtk_init(&argc, &argv);
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size (GTK_WINDOW (window), 600, 400);

    do_settings();
    
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all (window);

    gtk_main();
    return 0;
}
#endif
