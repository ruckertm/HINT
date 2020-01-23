/*313:*/
#line 5718 ".\\hint.w"

#ifndef _LIBRENDER_H
#define _LIBRENDER_H
/*274:*/
#line 4687 ".\\hint.w"

#define SP2PT(X) ((X)/(double)(1<<16))
/*:274*/
#line 5721 ".\\hint.w"

extern int page_h, page_v;
extern void render_blank(void);
extern uint64_t hint_page_at(uint64_t h);
extern uint64_t hint_page(void);
extern uint64_t hint_home_page(void);
extern uint64_t hint_next_page(void);
extern uint64_t hint_prev_page(void);
extern void hint_resize(int px_h,int px_v,double dpi);

#endif
/*:313*/
