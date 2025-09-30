/* This code is taken form the gtk-3 demo collection
   and was simplified to meet the needs of the hintview application.
*/

#include <gtk/gtk.h>
#include "basetypes.h"
#include "hint.h"

extern void goto_outline(int i);

/* columns */
enum
{
  SECTION_COL = 0,
  LINK_COL,
  NUM_COLUMNS
};

static int
add_outlines(hint_Outline *t, int i, int n, int depth, GtkTreeIter *base,GtkTreeStore *model)
{ GtkTreeIter iter;
  while (i<=n)
    { g_print("Outline[%d]: %s %d\n",i, t[i].title,t[i].depth);
    if (t[i].depth<depth) return i;
    if (t[i].depth==depth)
    { gtk_tree_store_append (model, &iter, base);
      gtk_tree_store_set (model, &iter,
                          SECTION_COL, t[i].title,
                          LINK_COL, i,
		        -1);
      i++;
    }
    else /* subitems */
      i=add_outlines(t, i, n, t[i].depth, &iter,model);
  }
  return i;
}  


static GtkTreeModel *
create_model (void)
{
  GtkTreeStore *model;
  int n;

  
  /* create tree store */
  model = gtk_tree_store_new (NUM_COLUMNS,
                              G_TYPE_STRING,
			      G_TYPE_INT);

  n= hint_get_outline_max(); /*outlines numbered 0 to n*/

  if (n<0)
  { return GTK_TREE_MODEL (model);
  }

  add_outlines(hint_get_outlines(), 0, n, 0, NULL, model);

  return GTK_TREE_MODEL (model);
}

static void
add_columns (GtkTreeView *treeview)
{
  gint col_offset;
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;

  /* column for subsection names */
  renderer = gtk_cell_renderer_text_new ();
  g_object_set (renderer, "xalign", 0.0, NULL);

  col_offset = gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
                                                            -1, "Sections",
                                                            renderer, "text",
                                                            SECTION_COL,
                                                            NULL);
  column = gtk_tree_view_get_column (GTK_TREE_VIEW (treeview), col_offset - 1);
  gtk_tree_view_column_set_clickable (GTK_TREE_VIEW_COLUMN (column), TRUE);
#if 0  
  g_signal_connect(column,"clicked",G_CALLBACK(cb_column_clicked),NULL);
#endif
  }


void
cb_activated (
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

GtkWidget *
do_tree_store (GtkWidget *do_widget)
{
  static GtkWidget *window = NULL;

  if (!window)
    {
      GtkWidget *vbox;
      GtkWidget *sw;
      GtkWidget *treeview;
      GtkTreeModel *model;

      /* create window, etc */
      window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
      gtk_window_set_screen (GTK_WINDOW (window),
                             gtk_widget_get_screen (do_widget));
      gtk_window_set_title (GTK_WINDOW (window), "Outline");
      g_signal_connect (window, "destroy",
                        G_CALLBACK (gtk_widget_destroyed), &window);

      vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 8);
      gtk_container_set_border_width (GTK_CONTAINER (vbox), 8);
      gtk_container_add (GTK_CONTAINER (window), vbox);

      sw = gtk_scrolled_window_new (NULL, NULL);
      gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (sw),
                                      GTK_POLICY_AUTOMATIC,
                                      GTK_POLICY_AUTOMATIC);
      gtk_box_pack_start (GTK_BOX (vbox), sw, TRUE, TRUE, 0);

      /* create model */
      model = create_model ();

      /* create tree view */
      treeview = gtk_tree_view_new_with_model (model);
      g_object_unref (model);
      gtk_tree_selection_set_mode (gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview)),
                                   GTK_SELECTION_SINGLE);
      gtk_tree_view_set_headers_visible (GTK_TREE_VIEW (treeview),FALSE);

     g_signal_connect(treeview, "row-activated", G_CALLBACK(cb_activated), NULL);
     gtk_tree_view_set_activate_on_single_click (GTK_TREE_VIEW (treeview), TRUE);


      add_columns (GTK_TREE_VIEW (treeview));

      gtk_container_add (GTK_CONTAINER (sw), treeview);

     gtk_window_set_default_size (GTK_WINDOW (window), 300, 400);
     
    }

  if (!gtk_widget_get_visible (window))
    gtk_widget_show_all (window);
  else
    gtk_widget_destroy (window);

  return window;
}


void cb_tree_store_quit(void)
{ g_print("Close Tree Store\n");
}

