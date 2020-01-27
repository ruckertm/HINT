/*295:*/
#line 5540 "hint.w"

#ifndef _HRENDER_H
#define _HRENDER_H
/*256:*/
#line 4509 "hint.w"

#define SP2PT(X) ((X)/(double)(1<<16))
/*:256*/
#line 5543 "hint.w"


extern int page_h,page_v;
extern uint64_t hint_blank(void);
extern uint64_t hint_page_get(void);
extern uint64_t hint_page_top(uint64_t h);
extern uint64_t hint_page_center(uint64_t h);
extern uint64_t hint_page_bottom(uint64_t h);
extern uint64_t hint_page(void);
extern uint64_t hint_next_page(void);
extern uint64_t hint_prev_page(void);
extern void hint_resize(int px_h,int px_v,double dpi);

#endif
/*:295*/
