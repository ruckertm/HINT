#include <gtk/gtk.h>
#include "basetypes.h"
#include "main.h"
#include "gui.h"
#include "error.h"

void
cb_document_open (GtkButton* self, gpointer user_data)
{ do_open_file();
}

void
cb_search (GtkButton* self, gpointer user_data)
{ do_find();
}

void
cb_zoom_1 (GtkButton* self, gpointer user_data)
{ do_zoom_1();
}

void
cb_home (GtkButton* self, gpointer user_data)
{ do_home();
}

static GtkWidget *day, *night;


void
cb_day_night (GtkButton* self, gpointer user_data)
{ do_dark(1);
}

void
cb_reload (GtkButton* self, gpointer user_data)
{ do_reload();
}


void
cb_about (GtkButton* self, gpointer user_data)
{ do_about();
}

void
cb_help (GtkButton* self, gpointer user_data)
{ 
  do_help();
}

void
cb_quit (GtkButton* self, gpointer user_data)
{ 
  do_quit();
}

void
cb_preferences (GtkButton* self, gpointer user_data)
{ do_preferences();
}

void
cb_outline (GtkButton* self, gpointer user_data)
{ do_outlines();
}



static GtkWidget *
create_menu (void);

enum {open_id=0, home_id, search_id, zoom_id,dark_id,reload_id,outline_id,pref_id};

int buttonvisibility;

struct button_def {
  int id;
  char * label;
  char* icon_name;
  char* tool_tip;
  void (*cb)(GtkButton* self, gpointer user_data);
  GtkWidget *button;
} button_def[] = {
  {open_id, "Open file", "document-open-symbolic", "Open file (Ctrl+O)", cb_document_open, NULL},
  {home_id, "Home", "go-home-symbolic","Go to the document's home page (Ctrl+H)", cb_home,NULL},
  {search_id, "Search", "system-search-symbolic", "Find text (Ctrl+F)", cb_search, NULL},
  {zoom_id, "Zoom to 100%","zoom-original-symbolic", "Zoom to 100% (Ctrl+Z)", cb_zoom_1,NULL},
  {dark_id, "Dark mode",NULL,"Switch beween dark and light mode (Ctrl+D)", cb_day_night,NULL},
  {reload_id, "Reload file", "view-refresh-symbolic","Reload document (Ctrl+R)", cb_reload,NULL},
  {outline_id, "Outline", "view-list-symbolic","Show Outline (Ctrl+T)", cb_outline,NULL},
  {pref_id, "Preferences", "preferences-system-symbolic","Set Preferences (Ctrl+P)", cb_preferences,NULL},
};


void set_dark_button(gboolean dark)
{  if (dark)
    gtk_button_set_image (GTK_BUTTON(button_def[dark_id].button), day);
  else 
    gtk_button_set_image (GTK_BUTTON(button_def[dark_id].button), night);
}

GtkWidget *
create_headerbar (void)
{ GtkWidget *header;
  GtkWidget *button;
  GtkWidget *menu, *menu_button;
  int i;

  header = gtk_header_bar_new ();
  gtk_header_bar_set_show_close_button (GTK_HEADER_BAR (header), TRUE);
  gtk_header_bar_set_title (GTK_HEADER_BAR (header), "Hintview");
  gtk_header_bar_set_has_subtitle (GTK_HEADER_BAR (header), FALSE);

  menu_button=
  button= gtk_menu_button_new();
  gtk_button_set_image (GTK_BUTTON(button),
    gtk_image_new_from_icon_name ("open-menu-symbolic",GTK_ICON_SIZE_BUTTON));
  gtk_widget_set_tooltip_text (button,"Open application menu");
  gtk_header_bar_pack_start (GTK_HEADER_BAR (header), button);

  
  for (i=0; i< sizeof(button_def)/sizeof(struct button_def); i++)
  { struct button_def *b;
    b=button_def+i;
    b->button=button= gtk_button_new();
    if (b->icon_name!=NULL)
      gtk_button_set_image (GTK_BUTTON(button),
        gtk_image_new_from_icon_name (b->icon_name,GTK_ICON_SIZE_BUTTON));
    gtk_widget_set_tooltip_text (button,b->tool_tip);
    gtk_header_bar_pack_start (GTK_HEADER_BAR (header), button);
    if (b->cb!=NULL)
      { g_signal_connect (button, "clicked", G_CALLBACK (b->cb), NULL);
	//LOG("Connect cb\n"); 
      }
    //LOG("Button %d %d\n",i,buttonvisibility & (1<<i));
    gtk_widget_set_no_show_all (GTK_WIDGET(button),TRUE);
    if (buttonvisibility & (1<<i))
      gtk_widget_show(GTK_WIDGET(button));
    else 
      gtk_widget_hide(GTK_WIDGET(button));
  }
  

  night=gtk_image_new_from_icon_name ("weather-clear-night", GTK_ICON_SIZE_BUTTON);
  g_object_ref(night);
  day=gtk_image_new_from_icon_name ("weather-clear", GTK_ICON_SIZE_BUTTON);
  g_object_ref(day);
  set_dark_button(dark);

      
  button = gtk_button_new_from_icon_name ("help-contents",GTK_ICON_SIZE_BUTTON);
  gtk_widget_set_tooltip_text (button,"Help");
  gtk_header_bar_pack_end (GTK_HEADER_BAR (header), button);
  g_signal_connect (button, "clicked", G_CALLBACK (cb_help), NULL);

  menu=create_menu();
  gtk_menu_button_set_popup (GTK_MENU_BUTTON(menu_button), menu);

  return header;
 
}

/* use gtk_widget_hide(GTK_WIDGET(button)); to hide the button */

static GtkWidget *create_item(GtkWidget *menu, const char *label, GCallback cb_item)
{ GtkWidget *item;
  item=gtk_menu_item_new_with_label(label);
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);
  if (cb_item!=NULL)
    g_signal_connect(item, "activate", cb_item, NULL);
  gtk_widget_show (item);
  return item;
}

static GtkWidget *create_separator(GtkWidget *menu)
{ GtkWidget *item;
  item=gtk_separator_menu_item_new();
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);
  gtk_widget_show (item);
  return item;
}

void
cb_toggled_button_preference(GtkToggleButton* self, gpointer data)
{ uintptr_t i= (uintptr_t)data;
  if(gtk_toggle_button_get_active (self))
  { gtk_widget_show(GTK_WIDGET(button_def[i].button));
    buttonvisibility |= (1<<i);
  }
  else
  { gtk_widget_hide(GTK_WIDGET(button_def[i].button));
    buttonvisibility &= ~(1<<i);
  }
}

GtkWidget *
button_preferences (void)
{ GtkWidget *vbox, *check;
  int i;
  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 8);
  for (i=open_id; i<=pref_id; i++)
  { check=gtk_check_button_new_with_label(button_def[i].label);
     gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check),
				  gtk_widget_get_visible (GTK_WIDGET(button_def[i].button)));
     g_signal_connect (check, "toggled",
		       G_CALLBACK (cb_toggled_button_preference), (gpointer)(uintptr_t)i);
     gtk_box_pack_start (GTK_BOX (vbox), check, FALSE, FALSE, 0);
  }
 return vbox;
}





static GtkWidget *
create_menu (void)
{ GtkWidget *menu, *item, *submenu;
  menu = gtk_menu_new ();
  /* File */
  item=create_item(menu,"File",NULL);
  submenu= gtk_menu_new ();
    create_item(submenu,"Open File...", G_CALLBACK(cb_document_open));
    create_item(submenu,"Reload File", G_CALLBACK(cb_reload));
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (item), submenu);

  /* View */
  item=create_item(menu,"View",NULL);
  submenu= gtk_menu_new ();
    create_item(submenu,"Find...", G_CALLBACK(cb_search));
    create_item(submenu,"Outline...", G_CALLBACK(cb_outline));
    create_separator(submenu);
    create_item(submenu,"Dark mode", G_CALLBACK(cb_day_night));
    create_item(submenu,"Zoom to 100%", G_CALLBACK(cb_zoom_1));
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (item), submenu);


  /*Preferences*/
  create_item(menu,"Preferences...", G_CALLBACK(cb_preferences));

  /* Help */
  item=create_item(menu,"Help", NULL);
  submenu= gtk_menu_new ();
    create_item(submenu,"Get Help", G_CALLBACK(cb_help));
    create_separator(submenu);
    create_item(submenu,"About HintView", G_CALLBACK(cb_about));
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (item), submenu);

  create_separator(menu);
  create_item(menu,"Quit", G_CALLBACK(cb_quit));

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
