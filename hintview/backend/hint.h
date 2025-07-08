/*759:*/
#line 16005 "hint.w"

#ifndef _HRENDER_H
#define _HRENDER_H

typedef int scaled;



extern int hint_begin(void);
extern void hint_end(void);
extern uint64_t hint_blank(void);
extern void hint_render(void);
extern bool hint_forward(void);
extern bool hint_backward(void);
extern uint64_t hint_page_get(void);
extern uint64_t hint_page_top(uint64_t h);
extern uint64_t hint_page_middle(uint64_t h);
extern uint64_t hint_page_bottom(uint64_t h);
extern uint64_t hint_page(void);
extern uint64_t hint_page_next(void);
extern uint64_t hint_page_prev(void);
extern uint64_t hint_page_home(void);
extern void hint_resize(int px_h,int px_v,double xdpi,double ydpi);
extern scaled hint_hsize(void);
extern scaled hint_vsize(void);
extern void hint_clear_fonts(bool rm);
extern void hint_set_mark(char*m,int s);
extern bool hint_prev_mark(void);
extern bool hint_next_mark(void);
extern double hint_get_fpos(void);
extern uint64_t hint_set_fpos(double fpos);
extern void hint_render_on(void);
extern void hint_render_off(void);
extern void hint_dark(int dark);
extern void hint_gamma(double gamma);
extern int hint_print_on(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int hint_print_off(void);
extern int hint_print(unsigned char*bits);
extern int hint_find_link(scaled x,scaled y,scaled precission);
extern uint64_t hint_link_page(int i);
extern void hint_show_page(void);
extern void hint_round_position(bool r,double t);



extern bool hint_map(void);
extern void hint_unmap(void);









#endif
/*:759*/
