/* This code is taken form the gtk-3 demo collection
   and was simplified to meet the needs of the hintview application.
*/
#include <glib/gi18n.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include "main.h"

static GtkWidget *search_window = NULL;

static void
cb_next_click (GtkButton *button,
              GtkEntry  *entry)
{ GtkEntryBuffer *b=gtk_entry_get_buffer(entry);
  g_print("Next %s\n", gtk_entry_buffer_get_text(b));
  search_next(TRUE);
}


static void
cb_prev_click (GtkButton *button,
             gpointer   data)
{
   search_next(FALSE);
}

static void
search_entry_destroyed (GtkWidget *widget)
{
  search_window = NULL;
}

void cb_search_changed(GtkEntry* entry,  gpointer user_data )
{ GtkEntryBuffer *b=gtk_entry_get_buffer(entry);
  const char *str=gtk_entry_buffer_get_text(b);
  g_print("Search %s\n", str);
  search_string(str);
}

#if 0
void cb_search_quit(void)
{ //g_print("Close Search\n");
}
#endif

GtkWidget *
search_open (GtkWidget *parent_widget)
{
  GtkWidget *vbox;
  GtkWidget *hbox;
  GtkWidget *entry;
  GtkWidget *next_button;
  GtkWidget *previous_button;

  if (!search_window)
    {
      search_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
      gtk_window_set_screen (GTK_WINDOW (search_window), gtk_widget_get_screen (parent_widget));
      gtk_window_set_title (GTK_WINDOW (search_window), "Search");
      //gtk_window_set_resizable (GTK_WINDOW (search_window), FALSE);
      g_signal_connect (search_window, "destroy",
                        G_CALLBACK (search_entry_destroyed), &search_window);
#if 0      
       g_signal_connect(search_window, "destroy",
			G_CALLBACK(cb_search_quit), NULL);
#endif
      vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
      gtk_container_add (GTK_CONTAINER (search_window), vbox);
      gtk_container_set_border_width (GTK_CONTAINER (vbox), 5);

      hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
      gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 0);
      gtk_container_set_border_width (GTK_CONTAINER (hbox), 0);

      /* Create our entry */
      entry = gtk_search_entry_new ();
      gtk_box_pack_start (GTK_BOX (hbox), entry, TRUE, TRUE, 0);
      g_signal_connect (entry, "search-changed",
                        G_CALLBACK (cb_search_changed), NULL);
      /* Create the next and previous buttons */
      previous_button = gtk_button_new_with_label ("Previous");
      g_signal_connect (previous_button, "clicked",
                        G_CALLBACK (cb_prev_click), NULL);
      gtk_box_pack_end (GTK_BOX (hbox), previous_button, FALSE, FALSE, 0);
      gtk_widget_show (previous_button);

      next_button = gtk_button_new_with_label ("Next");
      g_signal_connect (next_button, "clicked",
                        G_CALLBACK (cb_next_click), entry);
      gtk_box_pack_end (GTK_BOX (hbox), next_button, FALSE, FALSE, 0);
      gtk_widget_show (next_button);

     }

  if (!gtk_widget_get_visible (search_window))
    gtk_widget_show_all (search_window);
  else
    {
      gtk_widget_destroy (search_window);
    }

  return search_window;
}



