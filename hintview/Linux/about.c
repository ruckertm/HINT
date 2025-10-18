#include <gtk/gtk.h>
#include "basetypes.h"
#include "main.h"
#include "error.h"

#define STR(S) EXP(S)
#define EXP(S) #S

static GtkWidget *get_logo(void)
{  static GtkWidget *logo=NULL;
    if (logo==NULL)
    { logo=gtk_image_new_from_resource ("/edu/hm/cs/hintview/logo");
      g_object_ref(logo);
    }
    return logo;
}

void
do_about (void)
{ GtkWidget *dialog,*content_area,*label, *hbox;
  
  dialog = gtk_dialog_new_with_buttons ("About HintView",NULL,
					GTK_DIALOG_MODAL,
					"OK",
                                        GTK_RESPONSE_OK,
					NULL);

  gtk_window_set_resizable(GTK_WINDOW(dialog),FALSE);
  gtk_window_set_type_hint(GTK_WINDOW(dialog),GDK_WINDOW_TYPE_HINT_DIALOG);
  
  content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 8);
  gtk_container_set_border_width (GTK_CONTAINER (hbox), 8);
  gtk_box_pack_start (GTK_BOX (content_area), hbox, FALSE, FALSE, 10);
  
  gtk_box_pack_start (GTK_BOX (hbox), get_logo(), FALSE, FALSE, 0);

  label=gtk_label_new(NULL);
  gtk_label_set_markup (GTK_LABEL (label),
			"<b>HintView: An application to view HINT files.</b>\n");
   gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, FALSE, 20);


  label=gtk_label_new(NULL);
  gtk_label_set_markup (GTK_LABEL (label),
  "© Martin Ruckert 2025\n"
  "\n"				   
  "HintView Version: " STR(VERSION) "." STR(MINOR_VERSION) " (" STR(REVISION) ")\n"
  "HINT File Format Version: " HINT_VERSION_STRING "\n"
  "\n"
  "Documentation:\n"
  "\t<a href=\"https://hint.userweb.mwn.de/hint/hintview.html\">"
     "The HintView home page</a>\n"
  "\n"				   
  "Credits:\n"   				   
  "\t<a href=\"http://www.opengl-tutorial.org\">The OpenGL Tutorial</a>\n"
  "\t<a href=\"https://docs.gtk.org/gtk3/\">GTK-3</a>\n"
  "\t<a href=\"https://www.tug.org/texlive\">TeX Live</a>\n"
  "\t<a href=\"http://freetype.org\">Freetype 2</a>\n"
  "\t<a href=\"https://www.zlib.net\">zlib</a>\n"
  "\n");
  gtk_container_add (GTK_CONTAINER (content_area), label);

  gtk_widget_show_all (dialog);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}


int hint_error(const char *title, const char *message)
{
  GtkWidget *dialog,*content_area,*label;
  
  dialog = gtk_dialog_new_with_buttons (title,NULL,
					GTK_DIALOG_MODAL,
					"OK",
                                        GTK_RESPONSE_OK,
					NULL);

  gtk_window_set_resizable(GTK_WINDOW(dialog),FALSE);
  gtk_window_set_type_hint(GTK_WINDOW(dialog),GDK_WINDOW_TYPE_HINT_DIALOG);
  
  content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
  gtk_box_pack_start (GTK_BOX (content_area), get_logo(), FALSE, FALSE, 10);
  label=gtk_label_new(message);
  gtk_box_pack_start (GTK_BOX (content_area), label, FALSE, FALSE, 10);
  gtk_widget_show_all (dialog);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
  return 0;
}



void hint_message(char *title, char *format, ...)
{ GtkWidget *dialog,*content_area,*label;
  char str[1024];
  va_list vargs;
  va_start(vargs,format);
  vsnprintf(str, 1024, format, vargs);
  
  dialog = gtk_dialog_new_with_buttons (title,NULL,
					GTK_DIALOG_MODAL,
					"OK",
                                        GTK_RESPONSE_OK,
					NULL);

  gtk_window_set_resizable(GTK_WINDOW(dialog),FALSE);
  gtk_window_set_type_hint(GTK_WINDOW(dialog),GDK_WINDOW_TYPE_HINT_DIALOG);
  
  content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
  gtk_box_pack_start (GTK_BOX (content_area), get_logo(), FALSE, FALSE, 10);
  label=gtk_label_new(str);
  gtk_box_pack_start (GTK_BOX (content_area), label, FALSE, FALSE, 10);
  gtk_widget_show_all (dialog);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}

