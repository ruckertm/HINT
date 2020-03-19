/*296:*/
#line 5655 ".\\hint.w"

#ifndef _HRENDER_H
#define _HRENDER_H
/*252:*/
#line 4437 ".\\hint.w"

#define SP2PT(X) ((X)/(double)(1<<16))
/*:252*/
#line 5658 ".\\hint.w"


extern int page_h,page_v;
extern uint64_t hint_blank(void);
extern void hint_render(void);
extern uint64_t hint_page_get(void);
extern uint64_t hint_page_top(uint64_t h);
extern uint64_t hint_page_center(uint64_t h);
extern uint64_t hint_page_bottom(uint64_t h);
extern uint64_t hint_page(void);
extern uint64_t hint_next_page(void);
extern uint64_t hint_prev_page(void);
extern void hint_resize(int px_h,int px_v,double dpi);
extern void hint_clear_fonts(bool rm);

#endif
/*:296*/
