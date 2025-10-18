/* in about.c */
extern void do_about(void);
extern int hint_error(const char *title, const char *msg);

/* in preferences.c */
extern void do_preferences(void);

/* in search-bar.c */
extern void cb_search_quit(void);
extern GtkWidget *search_open (GtkWidget *parent_widget);

/* in outline.c */
extern void outlines_open(GtkWidget *parent_widget);
extern void outlines_set(void);
extern void outlines_clear(void);

/* in header.c */
extern GtkWidget *create_headerbar (void);
extern void set_dark_button(int dark);
extern GtkWidget *button_preferences (void);
extern int buttonvisibility;
/* in settings.c */
extern void read_settings(GSettings *settings);
extern void write_settings(GSettings *settings);
