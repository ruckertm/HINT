/*177:*/
#line 3040 "hint.w"

#ifndef _TEXEXTERN_H_
#define _TEXEXTERN_H_
#include "basetypes.h"
#include "textypes.h"
#include "hformat.h"
#include "hdefaults.h"
#include "error.h"
/*27:*/
#line 662 "hint.w"

extern void print_xdimen(int i);
/*:27*//*31:*/
#line 705 "hint.w"

extern pointer hget_param_glue(uint8_t n);
/*:31*//*38:*/
#line 772 "hint.w"

extern void print_baseline_skip(int i);
extern pointer happend_to_vlist(pointer b);
/*:38*//*87:*/
#line 1478 "hint.w"

extern pointer new_character(uint8_t f,uint8_t c);
/*:87*//*90:*/
#line 1497 "hint.w"

extern pointer new_penalty(int m);
/*:90*//*95:*/
#line 1544 "hint.w"

extern pointer new_math(scaled w,small_number s);
/*:95*//*109:*/
#line 1710 "hint.w"

extern pointer new_glue(pointer q);
/*:109*//*178:*/
#line 3091 "hint.w"

extern pointer*pointer_def[32];
extern scaled*dimen_def;
extern int32_t*integer_def;
/*:178*//*179:*/
#line 3102 "hint.w"

extern void print_str(char*s);
extern void print_char(ASCII_code s);
extern void overflow(char*s,int n);
extern void show_box(pointer p);
extern void confusion(str_number s);
/*:179*//*180:*/
#line 3116 "hint.w"

extern int half(int x);
extern scaled x_over_n(scaled x,int n);
extern scaled xn_over_d(scaled x,int n,int d);
/*:180*//*181:*/
#line 3131 "hint.w"

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
/*:181*//*182:*/
#line 3154 "hint.w"

extern pointer new_null_box(void);
extern pointer new_rule(void);
extern pointer new_disc(void);
extern pointer new_kern(scaled w);
extern pointer new_spec(pointer p);
extern pointer new_ligature(quarterword f,quarterword c,pointer q);
extern void delete_glue_ref(pointer p);
extern pointer copy_node_list(pointer p);

/*:182*//*183:*/
#line 3176 "hint.w"

extern void list_init(void);
extern list_state_record cur_list;
extern list_state_record nest[];
extern uint8_t nest_ptr;
extern void push_nest(void);
extern void pop_nest(void);
/*:183*//*184:*/
#line 3191 "hint.w"

extern scaled*const active_width;
extern void line_break(int final_widow_penalty,pointer par_ptr);
extern void add_par_fill_skip(void);
extern pointer just_box;
extern pointer adjust_tail;
extern void append_to_vlist(pointer b,uint32_t offset);

/*:184*//*185:*/
#line 3205 "hint.w"

extern void hdisplay(pointer p,pointer a,bool l);
/*:185*//*186:*/
#line 3212 "hint.w"

extern pointer hpack(pointer p,scaled w,small_number m);
extern pointer vpackage(pointer p,scaled h,small_number m,scaled l);
scaled*const total_stretch,*const total_shrink;
/*:186*//*187:*/
#line 3223 "hint.w"

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

/*:187*//*191:*/
#line 3297 "hint.w"

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
/*:191*//*223:*/
#line 3906 "hint.w"

extern void hloc_init(void);
extern void store_map(pointer p,uint32_t pos,uint32_t offset);
extern uint32_t hposition(pointer p);
extern void hloc_set(uint64_t h);
extern void hloc_set_next(pointer p);
/*:223*//*231:*/
#line 4060 "hint.w"

extern scaled hvsize,hhsize;
/*:231*//*297:*/
#line 5674 "hint.w"

extern void leak_in(pointer p,int s);
extern void leak_out(pointer p,int s);
/*:297*/
#line 3048 "hint.w"

#endif
/*:177*/
