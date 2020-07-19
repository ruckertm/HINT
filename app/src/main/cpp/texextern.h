/*194:*/
#line 3214 "hint.w"

#ifndef _TEXEXTERN_H_
#define _TEXEXTERN_H_
#include "basetypes.h"
#include "textypes.h"
#include "error.h"
#include "hformat.h"

/*17:*/
#line 298 "hint.w"

extern void print_xdimen(int i);

/*:17*//*21:*/
#line 347 "hint.w"

extern pointer hget_param_glue(uint8_t n);
/*:21*//*28:*/
#line 414 "hint.w"

extern void print_baseline_skip(int i);
extern pointer happend_to_vlist(pointer b);
/*:28*//*47:*/
#line 735 "hint.w"

extern void hrestore_param_list(void);
/*:47*//*91:*/
#line 1400 "hint.w"

extern pointer new_character(uint8_t f,uint8_t c);
/*:91*//*94:*/
#line 1419 "hint.w"

extern pointer new_penalty(int m);
/*:94*//*110:*/
#line 1625 "hint.w"

extern pointer new_glue(pointer q);
/*:110*//*164:*/
#line 2789 "hint.w"

extern void set_line_break_params(void);
/*:164*//*178:*/
#line 2992 "hint.w"

extern pointer new_math(scaled w,small_number s);

/*:178*//*195:*/
#line 3267 "hint.w"

extern pointer*pointer_def[32];
extern scaled*dimen_def;
extern int32_t*integer_def;
/*:195*//*196:*/
#line 3278 "hint.w"

extern void print_str(char*s);
extern void print_int(int n);
extern void print_char(ASCII_code s);
extern void overflow(char*s,int n);
extern void show_box(pointer p);
extern void confusion(str_number s);
/*:196*//*197:*/
#line 3293 "hint.w"

extern int half(int x);
extern scaled x_over_n(scaled x,int n);
extern scaled xn_over_d(scaled x,int n,int d);
/*:197*//*198:*/
#line 3308 "hint.w"

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
/*:198*//*199:*/
#line 3331 "hint.w"

extern pointer new_null_box(void);
extern pointer new_rule(void);
extern pointer new_disc(void);
extern pointer new_kern(scaled w);
extern pointer new_spec(pointer p);
extern pointer new_ligature(quarterword f,quarterword c,pointer q);
extern void delete_glue_ref(pointer p);
extern pointer copy_node_list(pointer p);

/*:199*//*200:*/
#line 3353 "hint.w"

extern void list_init(void);
extern list_state_record cur_list;
extern list_state_record nest[];
extern uint16_t nest_ptr;
extern void push_nest(void);
extern void pop_nest(void);
/*:200*//*201:*/
#line 3368 "hint.w"

extern scaled*const active_width;
extern void line_break(int final_widow_penalty,pointer par_ptr);
extern pointer just_box;
extern pointer adjust_tail;
extern void append_to_vlist(pointer b,uint32_t offset);

/*:201*//*202:*/
#line 3381 "hint.w"

extern void hdisplay(pointer p,pointer a,bool l);
/*:202*//*203:*/
#line 3388 "hint.w"

extern pointer hpack(pointer p,scaled w,small_number m);
extern pointer vpackage(pointer p,scaled h,small_number m,scaled l);
scaled*const total_stretch,*const total_shrink;
/*:203*//*204:*/
#line 3405 "hint.w"

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
/*:204*//*209:*/
#line 3496 "hint.w"

extern void happend_insertion(pointer p);
extern void hpack_page(void);
/*:209*//*210:*/
#line 3510 "hint.w"

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
/*:210*//*214:*/
#line 3634 "hint.w"

extern void freeze_page_specs(small_number s);
/*:214*//*244:*/
#line 4125 "hint.w"

extern void hloc_init(void);
extern void store_map(pointer p,uint32_t pos,uint32_t offset);
extern uint32_t hposition(pointer p);
extern void hloc_set(uint64_t h);
extern void hloc_set_next(pointer p);
/*:244*//*252:*/
#line 4292 "hint.w"

extern scaled hvsize,hhsize;
/*:252*//*322:*/
#line 6114 "hint.w"

extern void leak_in(pointer p,int s);
extern void leak_out(pointer p,int s);
/*:322*/
#line 3222 "hint.w"

#endif
/*:194*/
