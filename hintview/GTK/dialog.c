#include <gtk/gtk.h>
#include "basetypes.h"
#include "main.h"

#define STR(S) EXP(S)
#define EXP(S) #S

void
do_about (void)
{
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new (GTK_WINDOW (NULL),
                                   GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                   GTK_MESSAGE_INFO,
                                   GTK_BUTTONS_OK,				   
				   "HintView: An application to view HINT files\n");
  gtk_message_dialog_format_secondary_markup (GTK_MESSAGE_DIALOG (dialog),
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

  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}


#if 0
int
main(int argc, char **argv)
{
    GtkWidget *window;

    gtk_init(&argc, &argv);
    do_about();
    gtk_main();
    return 0;
}
#endif

