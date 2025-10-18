#define VERSION 3
#define MINOR_VERSION 0
#define REVISION 0

/* in main.c */
extern double gcorrection, scale, rpxthreshold;
extern int dark, autoreload, home, rpx;
extern uint64_t position;
extern char *document;

extern void do_render(int d, int s, int g);
extern void do_rpx(void);
extern void do_open_file(void);
extern void do_reload(void);
extern void do_search(void);
extern void do_zoom_1(void);
extern void do_home(void);
extern void do_outlines(void);
extern void do_quit(void);
extern int  do_dark(int toggle);
extern void goto_outline(int i);
extern int search_string(const char *str);
extern int search_next(int next);
extern int main (int argc, char *argv[]);
