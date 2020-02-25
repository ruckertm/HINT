/*167:*/
#line 2678 ".\\hint.w"

#ifndef _TEXEXTERN_H_
#define _TEXEXTERN_H_
#include "basetypes.h"
#include "textypes.h"
#include "error.h"
#include "hformat.h"

/*17:*/
#line 294 ".\\hint.w"

extern void print_xdimen(int i);
/*:17*//*21:*/
#line 337 ".\\hint.w"

extern pointer hget_param_glue(uint8_t n);
/*:21*//*28:*/
#line 404 ".\\hint.w"

extern void print_baseline_skip(int i);
extern pointer happend_to_vlist(pointer b);
/*:28*//*77:*/
#line 1116 ".\\hint.w"

extern pointer new_character(uint8_t f,uint8_t c);
/*:77*//*80:*/
#line 1135 ".\\hint.w"

extern pointer new_penalty(int m);
/*:80*//*85:*/
#line 1182 ".\\hint.w"

extern pointer new_math(scaled w,small_number s);
/*:85*//*99:*/
#line 1348 ".\\hint.w"

extern pointer new_glue(pointer q);
/*:99*//*168:*/
#line 2731 ".\\hint.w"

extern pointer*pointer_def[32];
extern scaled*dimen_def;
extern int32_t*integer_def;
/*:168*//*169:*/
#line 2742 ".\\hint.w"

extern void print_str(char*s);
extern void print_int(int n);
extern void print_char(ASCII_code s);
extern void overflow(char*s,int n);
extern void show_box(pointer p);
extern void confusion(str_number s);
/*:169*//*170:*/
#line 2757 ".\\hint.w"

extern int half(int x);
extern scaled x_over_n(scaled x,int n);
extern scaled xn_over_d(scaled x,int n,int d);
/*:170*//*171:*/
#line 2772 ".\\hint.w"

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
/*:171*//*172:*/
#line 2795 ".\\hint.w"

extern pointer new_null_box(void);
extern pointer new_rule(void);
extern pointer new_disc(void);
extern pointer new_kern(scaled w);
extern pointer new_spec(pointer p);
extern pointer new_ligature(quarterword f,quarterword c,pointer q);
extern void delete_glue_ref(pointer p);
extern pointer copy_node_list(pointer p);

/*:172*//*173:*/
#line 2817 ".\\hint.w"

extern void list_init(void);
extern list_state_record cur_list;
extern list_state_record nest[];
extern uint8_t nest_ptr;
extern void push_nest(void);
extern void pop_nest(void);
/*:173*//*174:*/
#line 2832 ".\\hint.w"

extern scaled*const active_width;
extern void line_break(int final_widow_penalty,pointer par_ptr);
extern void add_par_fill_skip(void);
extern pointer just_box;
extern pointer adjust_tail;
extern void append_to_vlist(pointer b,uint32_t offset);

/*:174*//*175:*/
#line 2846 ".\\hint.w"

extern void hdisplay(pointer p,pointer a,bool l);
/*:175*//*176:*/
#line 2853 ".\\hint.w"

extern pointer hpack(pointer p,scaled w,small_number m);
extern pointer vpackage(pointer p,scaled h,small_number m,scaled l);
scaled*const total_stretch,*const total_shrink;
/*:176*//*177:*/
#line 2864 ".\\hint.w"

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

/*:177*//*181:*/
#line 2938 ".\\hint.w"

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
/*:181*//*213:*/
#line 3547 ".\\hint.w"

extern void hloc_init(void);
extern void store_map(pointer p,uint32_t pos,uint32_t offset);
extern uint32_t hposition(pointer p);
extern void hloc_set(uint64_t h);
extern void hloc_set_next(pointer p);
/*:213*//*221:*/
#line 3708 ".\\hint.w"

extern scaled hvsize,hhsize;
/*:221*//*290:*/
#line 5439 ".\\hint.w"

extern void leak_in(pointer p,int s);
extern void leak_out(pointer p,int s);
/*:290*/
#line 2686 ".\\hint.w"

#endif
/*:167*/
