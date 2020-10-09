/*195:*/
#line 3219 ".\\hint.w"

#ifndef _TEXEXTERN_H_
#define _TEXEXTERN_H_
#include "basetypes.h"
#include "textypes.h"
#include "error.h"
#include "hformat.h"

/*17:*/
#line 298 ".\\hint.w"

extern void print_xdimen(int i);

/*:17*//*21:*/
#line 347 ".\\hint.w"

extern pointer hget_param_glue(uint8_t n);
/*:21*//*28:*/
#line 414 ".\\hint.w"

extern void print_baseline_skip(int i);
extern pointer happend_to_vlist(pointer b);
/*:28*//*48:*/
#line 740 ".\\hint.w"

extern void hrestore_param_list(void);
/*:48*//*92:*/
#line 1405 ".\\hint.w"

extern pointer new_character(uint8_t f,uint8_t c);
/*:92*//*95:*/
#line 1424 ".\\hint.w"

extern pointer new_penalty(int m);
/*:95*//*111:*/
#line 1630 ".\\hint.w"

extern pointer new_glue(pointer q);
/*:111*//*165:*/
#line 2794 ".\\hint.w"

extern void set_line_break_params(void);
/*:165*//*179:*/
#line 2997 ".\\hint.w"

extern pointer new_math(scaled w,small_number s);

/*:179*//*196:*/
#line 3272 ".\\hint.w"

extern pointer*pointer_def[32];
extern scaled*dimen_def;
extern int32_t*integer_def;
/*:196*//*197:*/
#line 3283 ".\\hint.w"

extern void print_str(char*s);
extern void print_int(int n);
extern void print_char(ASCII_code s);
extern void overflow(char*s,int n);
extern void show_box(pointer p);
extern void confusion(str_number s);
/*:197*//*198:*/
#line 3298 ".\\hint.w"

extern int half(int x);
extern scaled x_over_n(scaled x,int n);
extern scaled xn_over_d(scaled x,int n,int d);
/*:198*//*199:*/
#line 3313 ".\\hint.w"

extern memory_word*const mem;
extern pointer temp_ptr;
extern pointer lo_mem_max;
extern pointer hi_mem_min;
extern pointer avail;
extern int var_used,dyn_used;
extern pointer get_avail(void);
extern pointer get_node(int s);
extern void free_node(pointer p,halfword s);
extern void flush_node_list(pointer p);
extern void mem_init(void);
/*:199*//*200:*/
#line 3336 ".\\hint.w"

extern pointer new_null_box(void);
extern pointer new_rule(void);
extern pointer new_disc(void);
extern pointer new_kern(scaled w);
extern pointer new_spec(pointer p);
extern pointer new_ligature(quarterword f,quarterword c,pointer q);
extern void delete_glue_ref(pointer p);
extern pointer copy_node_list(pointer p);

/*:200*//*201:*/
#line 3358 ".\\hint.w"

extern void list_init(void);
extern list_state_record cur_list;
extern list_state_record nest[];
extern uint16_t nest_ptr;
extern void push_nest(void);
extern void pop_nest(void);
/*:201*//*202:*/
#line 3373 ".\\hint.w"

extern scaled*const active_width;
extern void line_break(int final_widow_penalty,pointer par_ptr);
extern pointer just_box;
extern pointer adjust_tail;
extern void append_to_vlist(pointer b,uint32_t offset);

/*:202*//*203:*/
#line 3386 ".\\hint.w"

extern void hdisplay(pointer p,pointer a,bool l);
/*:203*//*204:*/
#line 3393 ".\\hint.w"

extern pointer hpack(pointer p,scaled w,small_number m);
extern pointer vpackage(pointer p,scaled h,small_number m,scaled l);
scaled*const total_stretch,*const total_shrink;
/*:204*//*205:*/
#line 3410 ".\\hint.w"

extern stream_t*streams;
extern bool hbuild_page(void);
extern halfword badness(scaled t,scaled s);
extern bool flush_pages(uint32_t pos);
extern uint8_t page_contents;
extern pointer page_tail;
extern scaled page_max_depth;
extern scaled page_depth;
extern scaled page_so_far[7];
extern int least_page_cost;
extern int insert_penalties;
extern pointer best_page_break;
extern scaled best_size;
extern void hfill_page_template(void);
extern pointer skip(uint8_t n);
extern pointer*box_ptr(uint8_t n);
extern int count(uint8_t n);
extern scaled dimen(uint8_t n);
/*:205*//*210:*/
#line 3501 ".\\hint.w"

extern void happend_insertion(pointer p);
extern void hpack_page(void);
/*:210*//*211:*/
#line 3515 ".\\hint.w"

extern char**const font_name;
extern int*const width_base;
extern int*const height_base;
extern int*const depth_base;
extern void read_font_info(int f,char*n,scaled s);
extern memory_word font_info[];
extern int*const char_base;
extern eight_bits*const font_bc;
extern eight_bits*const font_ec;
extern scaled*const font_size;
extern scaled*const font_dsize;

extern void hclear_fonts(void);
/*:211*//*215:*/
#line 3639 ".\\hint.w"

extern void freeze_page_specs(small_number s);
/*:215*//*241:*/
#line 4110 ".\\hint.w"

extern void hloc_init(void);
extern void store_map(pointer p,uint32_t pos,uint32_t offset);
extern uint32_t hposition(pointer p);
extern void hloc_set(uint64_t h);
extern void hloc_set_next(pointer p);
/*:241*//*249:*/
#line 4277 ".\\hint.w"

extern scaled hvsize,hhsize;
/*:249*//*326:*/
#line 6307 ".\\hint.w"

extern void leak_in(pointer p,int s);
extern void leak_out(pointer p,int s);
/*:326*/
#line 3227 ".\\hint.w"

#endif
/*:195*/
