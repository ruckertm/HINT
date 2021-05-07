/*344:*/
#line 6824 "hint.w"

#ifndef _HINT_H_
#define _HINT_H_

#ifndef pointer
#define pointer int16_t
typedef int scaled;
#endif

/*26:*/
#line 411 "hint.w"

extern pointer happend_to_vlist(pointer b);
/*:26*//*36:*/
#line 562 "hint.w"

extern uint16_t hglyph_section(uint8_t f);
extern int32_t font_at_size(uint8_t f);

/*:36*//*45:*/
#line 728 "hint.w"

extern void hrestore_param_list(void);
/*:45*//*50:*/
#line 783 "hint.w"

typedef struct{
pointer p,t;
}stream_t;
extern stream_t*streams;
/*:50*//*65:*/
#line 1009 "hint.w"

extern void hfill_page_template(void);
/*:65*//*166:*/
#line 2818 "hint.w"

extern void set_line_break_params(void);
/*:166*//*168:*/
#line 2855 "hint.w"

extern void hget_par_node(uint32_t offset);
/*:168*//*173:*/
#line 2953 "hint.w"

extern void hteg_par_node(uint32_t offset);
/*:173*//*199:*/
#line 3310 "hint.w"

extern pointer*pointer_def[32];
extern scaled*dimen_def;
extern int32_t*integer_def;
/*:199*//*200:*/
#line 3365 "hint.w"

extern stream_t*streams;
extern bool flush_pages(uint32_t pos);
extern pointer skip(uint8_t n);
extern pointer*box_ptr(uint8_t n);
extern int count(uint8_t n);
extern scaled dimen(uint8_t n);
/*:200*//*203:*/
#line 3422 "hint.w"

extern void hpage_init(void);
/*:203*//*205:*/
#line 3439 "hint.w"

extern void hflush_contribution_list(void);
/*:205*//*225:*/
#line 3842 "hint.w"

#define HINT_NO_LOC 0xFFFFFFFFFFFFFFFF
#define PAGE_LOC(P,Q) (((uint64_t)((P)+(Q))<<32) + (uint64_t)(Q))
#define LOC_POS(P) ((P)>>32) 
#define LOC_OFF(P) ((P)&0xFFFFFFFF) 
#define LOC_POS0(P) (LOC_POS(P)-LOC_OFF(P)) 
/*:225*//*228:*/
#line 3879 "hint.w"

extern uint64_t page_loc[];
extern int cur_loc;
/*:228*//*230:*/
#line 3928 "hint.w"

extern void hloc_clear(void);
extern bool hloc_next(void);
extern bool hloc_prev(void);
/*:230*//*235:*/
#line 4042 "hint.w"

extern void hloc_init(void);
extern void store_map(pointer p,uint32_t pos,uint32_t offset);
extern uint32_t hposition(pointer p);
extern void hloc_set(uint64_t h);
extern void hloc_set_next(pointer p);
/*:235*//*237:*/
#line 4108 "hint.w"

extern void hint_begin(void);
extern void hint_end(void);
extern uint64_t hint_map(void);
extern uint8_t*hbase;
extern void hint_unmap(void);
/*:237*//*241:*/
#line 4202 "hint.w"

extern bool hint_forward(void);
extern bool hint_backward(void);
/*:241*//*244:*/
#line 4233 "hint.w"

extern scaled hvsize,hhsize;
/*:244*//*257:*/
#line 4481 "hint.w"

typedef struct{uint64_t pos;uint8_t major,minor;uint8_t where;char title[];}hint_label_t;
/*:257*//*260:*/
#line 4545 "hint.w"

#define HINT_TOP 1
#define HINT_BOTTOM 2
#define HINT_MIDDLE 3
/*:260*//*262:*/
#line 4569 "hint.w"

extern int hint_get_label_max(void);
extern hint_label_t*hint_get_label(int i);
extern uint64_t hint_get_label_pos(int i);
extern uint8_t hint_get_label_where(int i);
extern uint64_t hint_get_label_page(int i);
/*:262*//*343:*/
#line 6808 "hint.w"

extern void leak_in(pointer p,int s);
extern void leak_out(pointer p,int s);
/*:343*/
#line 6833 "hint.w"


#endif
/*:344*/
