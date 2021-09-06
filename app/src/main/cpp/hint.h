/*366:*/
#line 7298 "hint.w"

#ifndef _HINT_H_
#define _HINT_H_

typedef uint16_t pointer;
typedef int scaled;

/*44:*/
#line 728 "hint.w"

extern void hrestore_param_list(void);
/*:44*//*49:*/
#line 783 "hint.w"

typedef struct{
pointer p,t;
}stream_t;
extern stream_t*streams;
/*:49*//*64:*/
#line 1009 "hint.w"

extern void hfill_page_template(void);
/*:64*//*164:*/
#line 2773 "hint.w"

extern void set_line_break_params(void);
/*:164*//*166:*/
#line 2812 "hint.w"

extern void hget_par_node(uint32_t offset);
/*:166*//*171:*/
#line 2912 "hint.w"

extern void hteg_par_node(uint32_t offset);
/*:171*//*197:*/
#line 3265 "hint.w"

extern pointer*pointer_def[32];
extern scaled*dimen_def;
extern int32_t*integer_def;
/*:197*//*198:*/
#line 3320 "hint.w"

extern stream_t*streams;
extern bool flush_pages(uint32_t pos);
extern pointer skip(uint8_t n);
extern pointer*box_ptr(uint8_t n);
extern int count(uint8_t n);
extern scaled dimen(uint8_t n);
/*:198*//*201:*/
#line 3377 "hint.w"

extern void hpage_init(void);
/*:201*//*203:*/
#line 3394 "hint.w"

extern void hflush_contribution_list(void);
/*:203*//*223:*/
#line 3797 "hint.w"

#define HINT_NO_LOC 0xFFFFFFFFFFFFFFFF
#define PAGE_LOC(POS0,OFF) (((uint64_t)((POS0)+(OFF))<<32) + (uint64_t)(OFF))
#define LOC_POS(P) ((P)>>32) 
#define LOC_OFF(P) ((P)&0xFFFFFFFF) 
#define LOC_POS0(P) (LOC_POS(P)-LOC_OFF(P)) 
/*:223*//*226:*/
#line 3834 "hint.w"

extern uint64_t page_loc[];
extern int cur_loc;
/*:226*//*228:*/
#line 3883 "hint.w"

extern void hloc_clear(void);
extern bool hloc_next(void);
extern bool hloc_prev(void);
/*:228*//*233:*/
#line 3997 "hint.w"

extern void hloc_init(void);
extern void store_map(pointer p,uint32_t pos,uint32_t offset);
extern uint32_t hposition(pointer p);
extern void hloc_set(uint64_t h);
extern void hloc_set_next(pointer p);
/*:233*//*235:*/
#line 4063 "hint.w"

extern void hint_begin(void);
extern void hint_end(void);
extern bool hint_map(void);
extern void hint_unmap(void);
/*:235*//*239:*/
#line 4156 "hint.w"

extern bool hint_forward(void);
extern bool hint_backward(void);
/*:239*//*242:*/
#line 4187 "hint.w"

extern scaled hvsize,hhsize;
/*:242*//*259:*/
#line 4524 "hint.w"

typedef struct{
uint64_t pos;
uint8_t depth;
uint8_t where;
int p;
char*title;
}hint_outline_t;
extern hint_outline_t*hint_outlines;
/*:259*//*260:*/
#line 4542 "hint.w"

#define LABEL_UNDEF 0
#define LABEL_TOP 1
#define LABEL_BOT 2
#define LABEL_MID 3
/*:260*//*264:*/
#line 4601 "hint.w"

extern int hint_get_outline_max(void);
extern hint_outline_t*hint_get_outlines(void);
extern uint64_t hint_outline_page(int i);
/*:264*//*266:*/
#line 4716 "hint.w"

extern void trv_init(void(*f)(uint32_t c));
extern void trv_vlist(pointer p);
extern void trv_hlist(pointer p);
/*:266*//*295:*/
#line 5308 "hint.w"

typedef struct{
uint64_t pos;
uint8_t where;
int top,bottom,left,right;
}hint_link_t;
extern hint_link_t*hint_links;
extern int max_link;
/*:295*//*300:*/
#line 5470 "hint.w"

extern int hint_find_link(scaled x,scaled y,scaled precission);
extern uint64_t hint_link_page(int i);
/*:300*//*365:*/
#line 7281 "hint.w"

extern void leak_in(pointer p,int s);
extern void leak_out(pointer p,int s);
/*:365*/
#line 7305 "hint.w"


#endif
/*:366*/
