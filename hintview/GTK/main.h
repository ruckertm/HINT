#define VERSION 2
#define MINOR_VERSION 2
#define REVISION 1

extern double gcorrection;
extern gboolean dark, autoreload, home;
extern gboolean rpx;
extern double rpx_t;
extern void do_render(int d, int s, int g);
extern void do_rpx(void);
