#include <gtk/gtk.h>

extern void do_open_file(void);

void
cb_open_file (GtkButton* self, gpointer user_data)
{ 
  do_open_file();
}

void
cb_document_open (GtkButton* self, gpointer user_data)
{ g_print("Open document\n");
}

void
cb_search (GtkButton* self, gpointer user_data)
{ g_print("Search\n");
}

void
cb_zoom1 (GtkButton* self, gpointer user_data)
{ g_print("Zoom 1\n");
}

void
cb_home (GtkButton* self, gpointer user_data)
{ g_print("Home\n");
}

static GtkWidget *day, *night;

void
cb_day_night (GtkButton* self, gpointer user_data)
{ static int dark=0;
  dark=!dark;
  if (dark)
    { gtk_button_set_image (self, day);
       g_print("Night\n");
    }
  else 
    { gtk_button_set_image (self, night);
      g_print("Day\n");
    }
}

void
cb_refresh (GtkButton* self, gpointer user_data)
{ g_print("Refresh\n");
}


void
cb_menu (GtkButton* self, gpointer user_data)
{ 
  g_print("Menu\n");
}

void
cb_preferences (GtkButton* self, gpointer user_data)
{ g_print("Preferences\n");
}


void
cb_help (GtkButton* self, gpointer user_data)
{ g_print("Help\n");
}

static GtkWidget *
create_menu (gint depth);

GtkWidget *
create_headerbar (void)
{
 
  GtkWidget *header;
  GtkWidget *button;
   GtkWidget *menu;
   menu=create_menu(2);

      header = gtk_header_bar_new ();
      gtk_header_bar_set_show_close_button (GTK_HEADER_BAR (header), TRUE);
      gtk_header_bar_set_title (GTK_HEADER_BAR (header), "Hintview");
      gtk_header_bar_set_has_subtitle (GTK_HEADER_BAR (header), FALSE);

      button = gtk_menu_button_new();
      gtk_button_set_image (GTK_BUTTON(button),
			    gtk_image_new_from_icon_name ("open-menu-symbolic",GTK_ICON_SIZE_BUTTON));
      gtk_menu_button_set_popup (GTK_MENU_BUTTON(button), menu);
      gtk_widget_set_tooltip_text (button,"Open application menu");
      gtk_header_bar_pack_start (GTK_HEADER_BAR (header), button);
      
      button = gtk_button_new_from_icon_name ("document-open-symbolic",GTK_ICON_SIZE_BUTTON);
      gtk_widget_set_tooltip_text (button,"Open file (Ctrl+F)");
      gtk_header_bar_pack_start (GTK_HEADER_BAR (header), button);
      g_signal_connect (button, "clicked", G_CALLBACK (cb_open_file), NULL);

      button = gtk_button_new_from_icon_name ("go-home-symbolic",GTK_ICON_SIZE_BUTTON);
      gtk_widget_set_tooltip_text (button,"Go to the document's home page");
      gtk_header_bar_pack_start (GTK_HEADER_BAR (header), button);
      g_signal_connect (button, "clicked", G_CALLBACK (cb_home), NULL);

      button = gtk_button_new_from_icon_name ("system-search-symbolic",GTK_ICON_SIZE_BUTTON);
      gtk_widget_set_tooltip_text (button,"Search text (Ctrl+S)");
      gtk_header_bar_pack_start (GTK_HEADER_BAR (header), button);
      g_signal_connect (button, "clicked", G_CALLBACK (cb_search), NULL);

      button = gtk_button_new_from_icon_name ("zoom-original-symbolic",GTK_ICON_SIZE_BUTTON);
      gtk_widget_set_tooltip_text (button,"Zoom to 100% (Ctrl+Z)");
      gtk_header_bar_pack_start (GTK_HEADER_BAR (header), button);
      g_signal_connect (button, "clicked", G_CALLBACK (cb_zoom1), NULL);

      night=gtk_image_new_from_icon_name ("weather-clear-night", GTK_ICON_SIZE_BUTTON);
      g_object_ref(night);
      day=gtk_image_new_from_icon_name ("weather-clear", GTK_ICON_SIZE_BUTTON);
      g_object_ref(day);
       
      button = gtk_button_new();
      gtk_button_set_image (GTK_BUTTON(button),night);
      gtk_widget_set_tooltip_text (button,"Switch beween dark and light mode (Ctrl+N)");
      gtk_header_bar_pack_start (GTK_HEADER_BAR (header), button);
      g_signal_connect (button, "clicked", G_CALLBACK (cb_day_night), NULL);

      button = gtk_button_new_from_icon_name ("view-refresh-symbolic",GTK_ICON_SIZE_BUTTON);
      gtk_widget_set_tooltip_text (button,"Reload document (Ctrl+R)");
      gtk_header_bar_pack_start (GTK_HEADER_BAR (header), button);
      g_signal_connect (button, "clicked", G_CALLBACK (cb_refresh), NULL);

      button = gtk_button_new_from_icon_name ("preferences-system-symbolic",GTK_ICON_SIZE_BUTTON);
      gtk_widget_set_tooltip_text (button,"Set Preferences");
      gtk_header_bar_pack_start (GTK_HEADER_BAR (header), button);
      g_signal_connect (button, "clicked", G_CALLBACK (cb_preferences), NULL);

      /* I need an icon to open the outlines window */
      
      button = gtk_button_new_from_icon_name ("help-contents",GTK_ICON_SIZE_BUTTON);
      gtk_widget_set_tooltip_text (button,"Help");
      gtk_header_bar_pack_end (GTK_HEADER_BAR (header), button);
      g_signal_connect (button, "clicked", G_CALLBACK (cb_help), NULL);

      
      return header;
 
}

/* use gtk_widget_hide(GTK_WIDGET(button)); to hide the button */

static GtkWidget *create_item(GtkWidget *menu, const char *label, GCallback cb_item)
{  GtkWidget *item;
   item=gtk_menu_item_new_with_label(label);
    gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);
    if (cb_item!=NULL)
      g_signal_connect(item, "activate", cb_item, NULL);
    gtk_widget_show (item);
    return item;
}

static GtkWidget *create_separator(GtkWidget *menu)
{  GtkWidget *item;
   item=gtk_separator_menu_item_new();
   gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);
   gtk_widget_show (item);
   return item;
}


static GtkWidget *
create_menu (gint depth)
{
  GtkWidget *menu, *item, *submenu;
  

  menu = gtk_menu_new ();
  /* File */
  item=create_item(menu,"File",NULL);
  submenu= gtk_menu_new ();
    create_item(submenu,"Open File...", G_CALLBACK(cb_open_file));
    create_item(submenu,"Quit", G_CALLBACK(cb_menu));
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (item), submenu);

  /* View */
  item=create_item(menu,"View",NULL);
  submenu= gtk_menu_new ();
    create_item(submenu,"Search...", G_CALLBACK(cb_menu));
    create_item(submenu,"Outline...", G_CALLBACK(cb_menu));
    create_separator(submenu);
    create_item(submenu,"Dark mode...", G_CALLBACK(cb_menu));
    create_item(submenu,"Zoom to 100%", G_CALLBACK(cb_menu));
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (item), submenu);


  /*Preferences*/
  create_item(menu,"Preferences", G_CALLBACK(cb_menu));

  /* Help */
  item=create_item(menu,"Help", NULL);
  submenu= gtk_menu_new ();
    create_item(submenu,"Get help...", G_CALLBACK(cb_menu));
    create_separator(submenu);
    create_item(submenu,"About Hintview", G_CALLBACK(cb_menu));
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (item), submenu);

  return menu;
}


#if 0
/* needed for stand alone test */

int
main(int argc, char **argv)
{  GtkWidget *window = NULL;
   GtkWidget *header;
   
    gtk_init(&argc, &argv);
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    //    gtk_window_set_screen (GTK_WINDOW (window), gtk_widget_get_screen (NULL));
    g_signal_connect (window, "destroy",
                      G_CALLBACK (gtk_widget_destroyed), &window);


    gtk_window_set_default_size (GTK_WINDOW (window), 600, 400);
    header = create_headerbar();
    gtk_window_set_titlebar (GTK_WINDOW (window), header);
    gtk_container_add (GTK_CONTAINER (window), gtk_text_view_new ());

    gtk_widget_show_all (window);
 
    gtk_main();
    return 0;
}

#endif
