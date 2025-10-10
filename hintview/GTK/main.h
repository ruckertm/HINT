#define VERSION 2
#define MINOR_VERSION 2
#define REVISION 1

extern double gcorrection, scale, rpxthreshold;
extern bool dark, autoreload, home, rpx;
extern uint64_t position;
extern char *document;

extern void do_render(int d, int s, int g);
extern void do_rpx(void);
