/*346:*/
#line 6868 "hint.w"

#ifndef _HRENDER_H
#define _HRENDER_H
/*263:*/
#line 4585 "hint.w"

#define MARK_BIT 0x1
#define FOCUS_BIT 0x2
/*:263*//*292:*/
#line 5404 "hint.w"

#define SP2PT(X) ((X)/(double)(1<<16))
/*:292*/
#line 6871 "hint.w"


extern int page_h,page_v;
extern uint64_t hint_blank(void);
extern void hint_render(void);
extern uint64_t hint_page_get(void);
extern uint64_t hint_page_top(uint64_t h);
extern uint64_t hint_page_middle(uint64_t h);
extern uint64_t hint_page_bottom(uint64_t h);
extern uint64_t hint_page(void);
extern uint64_t hint_next_page(void);
extern uint64_t hint_prev_page(void);
extern void hint_resize(int px_h,int px_v,double dpi);
extern void hint_clear_fonts(bool rm);
extern void hmark_page(void);
extern void hint_set_mark(char*m,int s);
extern bool hint_prev_mark(void);
extern bool hint_next_mark(void);


#endif
/*:346*/
