/*170:*/
#line 2760 "hint.w"

#ifndef _TEXEXTERN_H_
#define _TEXEXTERN_H_
#include "basetypes.h"
#include "textypes.h"
#include "error.h"
#include "hformat.h"

/*17:*/
#line 296 "hint.w"

extern void print_xdimen(int i);
/*:17*//*21:*/
#line 339 "hint.w"

extern pointer hget_param_glue(uint8_t n);
/*:21*//*28:*/
#line 406 "hint.w"

extern void print_baseline_skip(int i);
extern pointer happend_to_vlist(pointer b);
/*:28*//*79:*/
#line 1161 "hint.w"

extern pointer new_character(uint8_t f,uint8_t c);
/*:79*//*82:*/
#line 1180 "hint.w"

extern pointer new_penalty(int m);
/*:82*//*87:*/
#line 1227 "hint.w"

extern pointer new_math(scaled w,small_number s);
/*:87*//*101:*/
#line 1393 "hint.w"

extern pointer new_glue(pointer q);
/*:101*//*171:*/
#line 2813 "hint.w"

extern pointer*pointer_def[32];
extern scaled*dimen_def;
extern int32_t*integer_def;
/*:171*//*172:*/
#line 2824 "hint.w"

extern void print_str(char*s);
extern void print_int(int n);
extern void print_char(ASCII_code s);
extern void overflow(char*s,int n);
extern void show_box(pointer p);
extern void confusion(str_number s);
/*:172*//*173:*/
#line 2839 "hint.w"

extern int half(int x);
extern scaled x_over_n(scaled x,int n);
extern scaled xn_over_d(scaled x,int n,int d);
/*:173*//*174:*/
#line 2854 "hint.w"

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
/*:174*//*175:*/
#line 2877 "hint.w"

extern pointer new_null_box(void);
extern pointer new_rule(void);
extern pointer new_disc(void);
extern pointer new_kern(scaled w);
extern pointer new_spec(pointer p);
extern pointer new_ligature(quarterword f,quarterword c,pointer q);
extern void delete_glue_ref(pointer p);
extern pointer copy_node_list(pointer p);

/*:175*//*176:*/
#line 2899 "hint.w"

extern void list_init(void);
extern list_state_record cur_list;
extern list_state_record nest[];
extern uint16_t nest_ptr;
extern void push_nest(void);
extern void pop_nest(void);
/*:176*//*177:*/
#line 2914 "hint.w"

extern scaled*const active_width;
extern void line_break(int final_widow_penalty,pointer par_ptr);
extern void add_par_fill_skip(void);
extern pointer just_box;
extern pointer adjust_tail;
extern void append_to_vlist(pointer b,uint32_t offset);

/*:177*//*178:*/
#line 2928 "hint.w"

extern void hdisplay(pointer p,pointer a,bool l);
/*:178*//*179:*/
#line 2935 "hint.w"

extern pointer hpack(pointer p,scaled w,small_number m);
extern pointer vpackage(pointer p,scaled h,small_number m,scaled l);
scaled*const total_stretch,*const total_shrink;
/*:179*//*180:*/
#line 2946 "hint.w"

extern stream_t stream[256];
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

/*:180*//*184:*/
#line 3020 "hint.w"

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
/*:184*//*216:*/
#line 3629 "hint.w"

extern void hloc_init(void);
extern void store_map(pointer p,uint32_t pos,uint32_t offset);
extern uint32_t hposition(pointer p);
extern void hloc_set(uint64_t h);
extern void hloc_set_next(pointer p);
/*:216*//*224:*/
#line 3790 "hint.w"

extern scaled hvsize,hhsize;
/*:224*//*293:*/
#line 5540 "hint.w"

extern void leak_in(pointer p,int s);
extern void leak_out(pointer p,int s);
/*:293*/
#line 2768 "hint.w"

#endif
/*:170*/
