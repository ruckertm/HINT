#include <gtk/gtk.h>
#include "basetypes.h"
#include "main.h"

static GtkWidget *dialog=NULL;
static int is_running=FALSE;

gboolean toggle_autoreload, toggle_home, toggle_rpx;
double spin_gcorrection, spin_rpxthreshold;

static void save_preferences(void)
{ toggle_autoreload=autoreload;
  toggle_home=home;
  toggle_rpx=rpx;
  spin_gcorrection=gcorrection;
  spin_rpxthreshold=rpxthreshold;
}

static void restore_preferences(void)
{ autoreload=toggle_autoreload;
  home=toggle_home;
  rpx=toggle_rpx;
  gcorrection=spin_gcorrection;
  rpxthreshold=spin_rpxthreshold;
  do_rpx(); 
  do_render(0,0,1);
}

void cb_toggled_autoreload(GtkToggleButton* self, gpointer user_data)
{ if (gtk_toggle_button_get_active (self))
    autoreload=1;
  else
    autoreload=0;
}

void cb_toggled_home(GtkToggleButton* self, gpointer user_data)
{ if (gtk_toggle_button_get_active (self))
    home=1;
  else
    home=0;
}


void cb_toggled_rpx(GtkToggleButton* self, gpointer user_data)
{  if (gtk_toggle_button_get_active (self))
    rpx=1;
  else
    rpx=0;
  do_rpx();
  do_render(0,0,0);
}

void
cb_spin_rpx_threshold(GtkSpinButton* self, gpointer user_data)
{ rpxthreshold = gtk_spin_button_get_value (self);
  do_rpx();
  do_render(0,0,0);
}


void
cb_spin_gcorrection (GtkSpinButton* self, gpointer user_data)
{ gcorrection = gtk_spin_button_get_value (self);
  g_print("Gamma %f\n", gcorrection);
  do_render(0,0,1);
}

void
cb_dialog (GtkDialog* self, gint response, gpointer user_data)
{ if (response==GTK_RESPONSE_OK)
    ;
  else if (response==GTK_RESPONSE_CANCEL)
    {  restore_preferences();
      g_print("Cancel\n");
    }
  else
    {// g_print("Other\n");
      return;
    }
   gtk_widget_destroy(GTK_WIDGET(self));

}

void cb_dialog_unrealize(GtkWidget* self, gpointer user_data)
{
     is_running=FALSE;
     // g_print("Preferences Unrealize\n");
}


  void
do_preferences (void)
{ GtkWidget *content_area, *check, *spin;
  GtkWidget *label, *hbox;

  if (is_running) return;
  is_running=TRUE;
  save_preferences();
  
  dialog = gtk_dialog_new_with_buttons ("HintView Preferences",NULL,
					GTK_DIALOG_DESTROY_WITH_PARENT,
					"OK",
                                        GTK_RESPONSE_OK,
					"Cancel",
                                        GTK_RESPONSE_CANCEL,			
					NULL);

  gtk_window_set_resizable(GTK_WINDOW(dialog),FALSE);
  gtk_window_set_modal(GTK_WINDOW(dialog),FALSE);
  gtk_window_set_type_hint(GTK_WINDOW(dialog),GDK_WINDOW_TYPE_HINT_DIALOG);
  g_signal_connect (dialog, "unrealize", G_CALLBACK (cb_dialog_unrealize), NULL);
   
  content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
  gtk_box_set_spacing(GTK_BOX(content_area),8);
  gtk_widget_set_margin_start (content_area,8);
  gtk_widget_set_margin_end (content_area,8);
  gtk_widget_set_margin_top (content_area,8);
  gtk_widget_set_margin_bottom (content_area,8);

  check=gtk_check_button_new_with_label("Autoreload");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check),autoreload); 
  g_signal_connect (check, "toggled",
                    G_CALLBACK (cb_toggled_autoreload), NULL);
  gtk_box_pack_start (GTK_BOX (content_area), check, FALSE, FALSE, 0);
  
  check=gtk_check_button_new_with_label("Start with home page");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check),home); 
  g_signal_connect (check, "toggled",
                    G_CALLBACK (cb_toggled_home), NULL);
  gtk_box_pack_start (GTK_BOX (content_area), check, FALSE, FALSE, 0);

#if 0
  /* round to pixel does not work with GTK because GTK
     renders the framebuffer produced by hintview using its own
     scaling factor to the screen. So pixel precision is not 
     possible.
  */ 
  check=gtk_check_button_new_with_label("Round position to pixel");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check),rpx); 
  g_signal_connect (check, "toggled",
                    G_CALLBACK (cb_toggled_rpx), NULL);
  gtk_box_pack_start (GTK_BOX (content_area), check, FALSE, FALSE, 0);

  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 8);
  gtk_box_pack_start (GTK_BOX (content_area), hbox, FALSE, FALSE, 0);
  spin=gtk_spin_button_new (
			    gtk_adjustment_new(120,0,999,10,100,1),
			    1, /*climb rate*/
			    0); /*digits*/

   gtk_spin_button_set_numeric (GTK_SPIN_BUTTON(spin),TRUE);
   gtk_spin_button_set_value (GTK_SPIN_BUTTON(spin),rpxthreshold);

   g_signal_connect (spin, "value-changed",
                    G_CALLBACK (cb_spin_rpx_threshold), NULL);

   
   gtk_box_pack_start(GTK_BOX(hbox),spin,FALSE, FALSE, 0);
   label =  gtk_label_new ("DPI rounding threshold");
   gtk_box_pack_start(GTK_BOX(hbox),label,FALSE, FALSE, 0);
#endif
   
  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 8);
  gtk_box_pack_start (GTK_BOX (content_area), hbox, FALSE, FALSE, 0);

  spin=gtk_spin_button_new (
			    gtk_adjustment_new(2.2,0.1,4.0,0.05,0.1,0.00),
			    1, /*climb rate*/
			    2); /*digits*/

   gtk_spin_button_set_numeric (GTK_SPIN_BUTTON(spin),TRUE);
   gtk_spin_button_set_value (GTK_SPIN_BUTTON(spin),gcorrection);

   g_signal_connect (spin, "value-changed",
                    G_CALLBACK (cb_spin_gcorrection), NULL);

   
   gtk_box_pack_start(GTK_BOX(hbox),spin,FALSE, FALSE, 0);
   label =  gtk_label_new ("Set gamma");
   gtk_box_pack_start(GTK_BOX(hbox),label,FALSE, FALSE, 0);

   gtk_widget_show_all (dialog);
    g_signal_connect (dialog, "response",
                    G_CALLBACK (cb_dialog), NULL);
  //gtk_dialog_run (GTK_DIALOG (dialog));
  //gtk_widget_destroy (dialog);
}


#if 0
int
main(int argc, char **argv)
{


    gtk_init(&argc, &argv);
    do_preferences();
    gtk_main();
    return 0;
}
#endif

