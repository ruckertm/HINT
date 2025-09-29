#include <gtk/gtk.h>

/* TreeItem structure */
typedef struct _TreeItem TreeItem;
struct _TreeItem
{
  const gchar    *label;
  int             link;
  TreeItem       *children;
};

/* columns */
enum
{
  SECTION_COL = 0,
  LINK_COL,
  NUM_COLUMNS
};

/* tree data */
static TreeItem january[] =
{
  {"New Years Day", 1, NULL },
  {"Presidential Inauguration", 2, NULL },
  {"Martin Luther King Jr. day", 3, NULL },
  { NULL }
};

static TreeItem february[] =
{
  { "Presidents' Day", 4, NULL },
  { "Groundhog Day", 5,  NULL },
  { "Valentine's Day", 6, NULL },
  { NULL }
};


static TreeItem toplevel[] =
{
  {"January", 7, january},
  {"February", 8, february},
  {NULL}
};


static GtkTreeModel *
create_model (void)
{
  GtkTreeStore *model;
  GtkTreeIter iter;
  TreeItem *section = toplevel;

  /* create tree store */
  model = gtk_tree_store_new (NUM_COLUMNS,
                              G_TYPE_STRING,
			      G_TYPE_INT);


  /* add data to the tree store */
  while (section->label)
    {
      TreeItem *subsection = section->children;

      gtk_tree_store_append (model, &iter, NULL);
      gtk_tree_store_set (model, &iter,
                          SECTION_COL, section->label,
                          LINK_COL, section->link,
                          -1);

      /* add children */
      while (subsection->label)
        {
          GtkTreeIter child_iter;

          gtk_tree_store_append (model, &child_iter, &iter);
          gtk_tree_store_set (model, &child_iter,
                              SECTION_COL, subsection->label,
 			      LINK_COL, subsection->link,
                               -1);

          subsection++;
        }

      section++;
    }

  return GTK_TREE_MODEL (model);
}

#if 0
void
cb_column_clicked (
  GtkTreeViewColumn* self,
  gpointer user_data)
{
  g_print("Clicked\n");
}
#endif


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

#if 0
gboolean cb_selected (
  GtkTreeSelection* selection,
  GtkTreeModel* model,
  GtkTreePath* path,
  gboolean path_currently_selected,
  gpointer data
)
{
  g_print("Selected\n");
  return TRUE;
}
#endif

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
  g_print("Activated %s %d\n",s,l);
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
#if 0      
      gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (sw),
                                           GTK_SHADOW_ETCHED_IN);
#endif
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

#if 0
      gtk_tree_selection_set_select_function(
	     gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview)),
	     cb_selected,NULL,NULL);
#endif
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


#if 0
int
main(int argc, char **argv)
{
    GtkWidget *window;

    gtk_init(&argc, &argv);
    window = do_tree_store(NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_main();
    return 0;
}

#endif
