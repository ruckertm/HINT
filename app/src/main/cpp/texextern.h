/*176:*/
#line 2905 ".\\hint.w"

#ifndef _TEXEXTERN_H_
#define _TEXEXTERN_H_
#include "basetypes.h"
#include "textypes.h"
#include "hformat.h"
#include "hdefaults.h"
#include "error.h"
/*26:*/
#line 527 ".\\hint.w"

extern void print_xdimen(int i);
/*:26*//*30:*/
#line 570 ".\\hint.w"

extern pointer hget_param_glue(uint8_t n);
/*:30*//*37:*/
#line 637 ".\\hint.w"

extern void print_baseline_skip(int i);
extern pointer happend_to_vlist(pointer b);
/*:37*//*86:*/
#line 1343 ".\\hint.w"

extern pointer new_character(uint8_t f,uint8_t c);
/*:86*//*89:*/
#line 1362 ".\\hint.w"

extern pointer new_penalty(int m);
/*:89*//*94:*/
#line 1409 ".\\hint.w"

extern pointer new_math(scaled w,small_number s);
/*:94*//*108:*/
#line 1575 ".\\hint.w"

extern pointer new_glue(pointer q);
/*:108*//*177:*/
#line 2956 ".\\hint.w"

extern pointer*pointer_def[32];
extern scaled*dimen_def;
extern int32_t*integer_def;
/*:177*//*178:*/
#line 2967 ".\\hint.w"

extern void print_str(char*s);
extern void print_char(ASCII_code s);
extern void overflow(char*s,int n);
extern void show_box(pointer p);
extern void confusion(str_number s);
/*:178*//*179:*/
#line 2981 ".\\hint.w"

extern int half(int x);
extern scaled x_over_n(scaled x,int n);
extern scaled xn_over_d(scaled x,int n,int d);
/*:179*//*180:*/
#line 2996 ".\\hint.w"

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
/*:180*//*181:*/
#line 3019 ".\\hint.w"

extern pointer new_null_box(void);
extern pointer new_rule(void);
extern pointer new_disc(void);
extern pointer new_kern(scaled w);
extern pointer new_spec(pointer p);
extern pointer new_ligature(quarterword f,quarterword c,pointer q);
extern void delete_glue_ref(pointer p);
extern pointer copy_node_list(pointer p);

/*:181*//*182:*/
#line 3041 ".\\hint.w"

extern void list_init(void);
extern list_state_record cur_list;
extern list_state_record nest[];
extern uint8_t nest_ptr;
extern void push_nest(void);
extern void pop_nest(void);
/*:182*//*183:*/
#line 3056 ".\\hint.w"

extern scaled*const active_width;
extern void line_break(int final_widow_penalty,pointer par_ptr);
extern void add_par_fill_skip(void);
extern pointer just_box;
extern pointer adjust_tail;
extern void append_to_vlist(pointer b,uint32_t offset);

/*:183*//*184:*/
#line 3070 ".\\hint.w"

extern void hdisplay(pointer p,pointer a,bool l);
/*:184*//*185:*/
#line 3077 ".\\hint.w"

extern pointer hpack(pointer p,scaled w,small_number m);
extern pointer vpackage(pointer p,scaled h,small_number m,scaled l);
scaled*const total_stretch,*const total_shrink;
/*:185*//*186:*/
#line 3088 ".\\hint.w"

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

/*:186*//*190:*/
#line 3162 ".\\hint.w"

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
/*:190*//*222:*/
#line 3771 ".\\hint.w"

extern void hloc_init(void);
extern void store_map(pointer p,uint32_t pos,uint32_t offset);
extern uint32_t hposition(pointer p);
extern void hloc_set(uint64_t h);
extern void hloc_set_next(pointer p);
/*:222*//*233:*/
#line 4004 ".\\hint.w"

extern scaled hvsize,hhsize;
/*:233*//*299:*/
#line 5620 ".\\hint.w"

extern void leak_in(pointer p,int s);
extern void leak_out(pointer p,int s);
/*:299*/
#line 2913 ".\\hint.w"

#endif
/*:176*/
