/*340:*/
#line 6659 "hint.w"

#ifndef _HINT_H_
#define _HINT_H_

#ifndef pointer
#define pointer int16_t
typedef int scaled;
#endif

/*27:*/
#line 407 "hint.w"

extern pointer happend_to_vlist(pointer b);
/*:27*//*37:*/
#line 558 "hint.w"

extern uint16_t hglyph_section(uint8_t f);
extern int32_t font_at_size(uint8_t f);

/*:37*//*46:*/
#line 724 "hint.w"

extern void hrestore_param_list(void);
/*:46*//*51:*/
#line 779 "hint.w"

typedef struct{
pointer p,t;
}stream_t;
extern stream_t*streams;
/*:51*//*66:*/
#line 1006 "hint.w"

extern void hfill_page_template(void);
/*:66*//*166:*/
#line 2798 "hint.w"

extern void set_line_break_params(void);
/*:166*//*168:*/
#line 2835 "hint.w"

extern void hget_par_node(uint32_t offset);
/*:168*//*173:*/
#line 2933 "hint.w"

extern void hteg_par_node(uint32_t offset);
/*:173*//*196:*/
#line 3264 "hint.w"

extern pointer*pointer_def[32];
extern scaled*dimen_def;
extern int32_t*integer_def;
/*:196*//*205:*/
#line 3402 "hint.w"

extern stream_t*streams;
extern bool flush_pages(uint32_t pos);
extern pointer skip(uint8_t n);
extern pointer*box_ptr(uint8_t n);
extern int count(uint8_t n);
extern scaled dimen(uint8_t n);
/*:205*//*208:*/
#line 3459 "hint.w"

extern void hpage_init(void);
/*:208*//*210:*/
#line 3476 "hint.w"

extern void hflush_contribution_list(void);
/*:210*//*234:*/
#line 3912 "hint.w"

extern uint64_t page_loc[];
extern int cur_loc;
/*:234*//*236:*/
#line 3961 "hint.w"

extern void hloc_clear(void);
extern bool hloc_next(void);
extern bool hloc_prev(void);
/*:236*//*241:*/
#line 4075 "hint.w"

extern void hloc_init(void);
extern void store_map(pointer p,uint32_t pos,uint32_t offset);
extern uint32_t hposition(pointer p);
extern void hloc_set(uint64_t h);
extern void hloc_set_next(pointer p);
/*:241*//*243:*/
#line 4140 "hint.w"

extern void hint_begin(void);
extern void hint_end(void);
extern uint64_t hint_map(void);
extern uint8_t*hbase;
extern void hint_unmap(void);
/*:243*//*246:*/
#line 4212 "hint.w"

extern bool hint_forward(void);
extern bool hint_backward(void);
/*:246*//*249:*/
#line 4243 "hint.w"

extern scaled hvsize,hhsize;
/*:249*//*339:*/
#line 6643 "hint.w"

extern void leak_in(pointer p,int s);
extern void leak_out(pointer p,int s);
/*:339*/
#line 6668 "hint.w"


#endif
/*:340*/
