/*342:*/
#line 6639 "hint.w"

#ifndef _HRENDER_H
#define _HRENDER_H
/*261:*/
#line 4473 "hint.w"

#define MARK_BIT 0x1
#define FOCUS_BIT 0x2
/*:261*//*289:*/
#line 5181 "hint.w"

#define SP2PT(X) ((X)/(double)(1<<16))
/*:289*/
#line 6642 "hint.w"


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
extern void hint_set_mark(char*m,int s);
extern void hmark_page(void);
extern void hint_set_focus(char*f,int s);
extern uint64_t hint_next_focus(uint64_t pos);
extern uint64_t hint_prev_focus(uint64_t pos);

#endif
/*:342*/
