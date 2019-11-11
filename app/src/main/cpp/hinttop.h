#ifndef _HINTTOP_H_
#define _HINTTOP_H_

extern void hint_start(const char *file_name);
extern void hint_init(void);
extern void hint_page(void);
extern void hint_home_page(void);
extern void hint_next_page(void);
extern void hint_prev_page(void);
extern void hint_stop(void);
extern int hint_close(void);
extern void init_display_math(void);

extern int  page_h, page_v; /* page size in scaled points */
#endif
