#include <gtk/gtk.h>
#include "basetypes.h"
#include "main.h"
#include "gui.h"

static GtkWidget *dialog=NULL;
static int is_running=FALSE;

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
cb_response (GtkDialog* self, gint response, gpointer user_data)
{ gtk_widget_destroy(GTK_WIDGET(self));

}

void cb_dialog_unrealize(GtkWidget* self, gpointer user_data)
{
     is_running=FALSE;
     // g_print("Preferences Unrealize\n");
}


  void
do_preferences (void)
  { GtkWidget *content_area, *left_column, *right_column, *check, *spin;
    GtkWidget *label, *hbox, *frame;

  if (is_running) return;
  is_running=TRUE;
  
  dialog = gtk_dialog_new_with_buttons ("HintView Preferences",NULL,
					GTK_DIALOG_DESTROY_WITH_PARENT,
					"OK",
                                        GTK_RESPONSE_OK,
					NULL);

  gtk_window_set_resizable(GTK_WINDOW(dialog),FALSE);
  gtk_window_set_modal(GTK_WINDOW(dialog),FALSE);
  gtk_window_set_type_hint(GTK_WINDOW(dialog),GDK_WINDOW_TYPE_HINT_DIALOG);
  g_signal_connect (dialog, "unrealize", G_CALLBACK (cb_dialog_unrealize), NULL);
   
  content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
  gtk_box_set_spacing(GTK_BOX(content_area),10);
  gtk_container_set_border_width (GTK_CONTAINER (content_area), 10);

  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 16);
  gtk_box_pack_start (GTK_BOX (content_area), hbox, FALSE, FALSE, 0);
  
  frame = gtk_frame_new("Settings");
  left_column = gtk_box_new (GTK_ORIENTATION_VERTICAL, 8);
  gtk_container_set_border_width (GTK_CONTAINER (left_column), 10);
  gtk_container_add (GTK_CONTAINER (frame), left_column);
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 0);

  frame = gtk_frame_new("Header Buttons");
  right_column = button_preferences ();
  gtk_container_set_border_width (GTK_CONTAINER (right_column), 10);
  gtk_container_add (GTK_CONTAINER (frame), right_column);
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 0);
  
  check=gtk_check_button_new_with_label("Autoreload");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check),autoreload); 
  g_signal_connect (check, "toggled",
                    G_CALLBACK (cb_toggled_autoreload), NULL);
  gtk_box_pack_start (GTK_BOX (left_column), check, FALSE, FALSE, 0);
  
  check=gtk_check_button_new_with_label("Start with home page");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check),home); 
  g_signal_connect (check, "toggled",
                    G_CALLBACK (cb_toggled_home), NULL);
  gtk_box_pack_start (GTK_BOX (left_column), check, FALSE, FALSE, 0);

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
  gtk_box_pack_start (GTK_BOX (left_column), check, FALSE, FALSE, 0);

  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 8);
  gtk_box_pack_start (GTK_BOX (left_column), hbox, FALSE, FALSE, 0);
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
  gtk_box_pack_start (GTK_BOX (left_column), hbox, FALSE, FALSE, 0);

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
                    G_CALLBACK (cb_response), NULL);
  //gtk_dialog_run (GTK_DIALOG (dialog));
  //gtk_widget_destroy (dialog);
}



