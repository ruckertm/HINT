/* This code is taken form the gtk-3 demo collection
   and was simplified to meet the needs of the hintview application.
*/

#include <gtk/gtk.h>
#include "basetypes.h"
#include "hint.h"
#include "main.h"


static hint_Outline *outlines;
static int outlines_max;

static GtkWidget *outline_window = NULL;
static GtkWidget *tree_view=NULL;

/* columns */
#define SECTION_COL 0
#define LINK_COL    1
#define NUM_COLUMNS 2

/* add the outlines to the tree view model */
static int
add_outlines(int i, int depth, GtkTreeIter *base, GtkTreeStore *model)
{ GtkTreeIter iter;
  while (i<=outlines_max)
  {
    //g_print("Outline[%d]: %s %d\n",i, outlines[i].title,outlines[i].depth);
    if (outlines[i].depth<depth) return i;
    if (outlines[i].depth==depth)
    { gtk_tree_store_append (model, &iter, base);
      gtk_tree_store_set (model, &iter,
                          SECTION_COL, outlines[i].title,
                          LINK_COL, i,
		        -1);
      i++;
    }
    else /* subitems */
      i=add_outlines(i, outlines[i].depth, &iter,model);
  }
  return i;
}  

/* create the tree view model and fill it with outlines */
static GtkTreeModel *
create_model (void)
{
  GtkTreeStore *model;

  outlines_max= hint_get_outline_max(); /*outlines numbered 0 to n*/
  if (outlines_max<0)
  { return GTK_TREE_MODEL (NULL);
  }
   /* create tree store */
  model = gtk_tree_store_new (NUM_COLUMNS,
                              G_TYPE_STRING,
			      G_TYPE_INT);
  outlines=hint_get_outlines();
  add_outlines(0, 0, NULL, model);

  return GTK_TREE_MODEL (model);
}


/* call back: after a click to to an item show the corresponding page */
void
static cb_activated (
  GtkTreeView* self,
  GtkTreePath* path,
  GtkTreeViewColumn* column,
  gpointer user_data
)
{ char *s;
  int l;
  GtkTreeIter i;
  GtkTreeModel* m;
  m= gtk_tree_view_get_model(self);
  gtk_tree_model_get_iter (m,&i,path); 
  gtk_tree_model_get (m,&i,SECTION_COL,&s,LINK_COL,&l,-1);
  // g_print("Activated %s %d\n",s,l);
  goto_outline(l);
}

/* call back: when the outline window closes, reset auxiliar variables */
static void cb_outlines_quit(void)
{ outlines=NULL;
  outlines_max=-1;
  tree_view=NULL;
  //  g_print("Quit Tree Store\n");
}



/* set the model in the outline window */
void
outlines_set(void)
{       GtkTreeModel *model;
  if (outline_window==NULL) return;
  if (tree_view==NULL) return;
  model = create_model ();
  gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(model));
  g_object_unref (model);
  //g_print("Outline set\n");  
}

/* clear the model in the outline window */
void
outlines_clear(void)
{ if (outline_window==NULL) return;
  if (tree_view==NULL) return;
  gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), NULL); 
}

/* create the outline window */
void
outlines_open (GtkWidget *parent_widget)
{
  if (!outline_window)
  {
    GtkWidget *vbox;
    GtkWidget *scroll_window;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    //g_print("Creating ts window\n");
    /* create outline_window, etc */
    outline_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_screen (GTK_WINDOW (outline_window),
                           gtk_widget_get_screen (parent_widget));
    gtk_window_set_title (GTK_WINDOW (outline_window), "Outline");

    g_signal_connect (outline_window, "destroy",
                      G_CALLBACK (gtk_widget_destroyed), &outline_window);
    g_signal_connect(outline_window, "destroy",
		     G_CALLBACK(cb_outlines_quit), NULL);
    
    vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 8);
    gtk_container_set_border_width (GTK_CONTAINER (vbox), 8);
    gtk_container_add (GTK_CONTAINER (outline_window), vbox);
    scroll_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scroll_window),
                                    GTK_POLICY_AUTOMATIC,
                                    GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start (GTK_BOX (vbox), scroll_window, TRUE, TRUE, 0);

    /* adding the tree view */
    tree_view = gtk_tree_view_new();
      
    gtk_tree_selection_set_mode (gtk_tree_view_get_selection (GTK_TREE_VIEW (tree_view)),
                                 GTK_SELECTION_SINGLE);
    gtk_tree_view_set_headers_visible (GTK_TREE_VIEW (tree_view),FALSE);
    g_signal_connect(tree_view, "row-activated", G_CALLBACK(cb_activated), NULL);
    gtk_tree_view_set_activate_on_single_click (GTK_TREE_VIEW (tree_view), TRUE);

    /* column for subsection names */
    renderer = gtk_cell_renderer_text_new ();
    g_object_set (renderer, "xalign", 0.0, NULL);

    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (tree_view),
                                                      SECTION_COL, "Sections",
                                                      renderer,
						      "text", SECTION_COL,
                                                       NULL);
    column = gtk_tree_view_get_column (GTK_TREE_VIEW (tree_view), 0);
    gtk_tree_view_column_set_clickable (GTK_TREE_VIEW_COLUMN (column), TRUE);

    gtk_container_add (GTK_CONTAINER (scroll_window), tree_view);
    gtk_window_set_default_size (GTK_WINDOW (outline_window), 300, 400);

  }

  outlines_set();

  if (!gtk_widget_get_visible (outline_window))
      gtk_widget_show_all (outline_window);

}

