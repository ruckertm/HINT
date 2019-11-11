/*254:*/
#line 3909 ".\\hint.w"

#include "basetypes.h"
#include "error.h"
/*22:*/
#line 529 ".\\hint.w"

typedef int32_t scaled;
/*:22*//*35:*/
#line 611 ".\\hint.w"

typedef uint16_t pointer;
/*:35*//*38:*/
#line 631 ".\\hint.w"

typedef struct{pointer bs,ls;scaled lsl;}bs_t;
/*:38*//*49:*/
#line 761 ".\\hint.w"


extern void read_font_info(int f,char*n,scaled s);
/*:49*//*104:*/
#line 1497 ".\\hint.w"

typedef uint8_t small_number;
/*:104*//*119:*/
#line 1652 ".\\hint.w"

typedef uint8_t glue_ord;
typedef float32_t glue_ratio;
/*:119*//*200:*/
#line 2961 ".\\hint.w"

typedef uint8_t quarterword;
typedef uint16_t halfword;
typedef uint8_t eight_bits;
typedef halfword pointer;
typedef int32_t scaled;

typedef struct{
uint16_t rh;
union{
uint16_t lh;
struct{uint8_t b0;uint8_t b1;};
};}two_halves;
typedef struct{uint8_t b0,b1,b2,b3;}four_quarters;
typedef union{
int32_t i;
uint32_t u;
float32_t gr;
two_halves hh;
four_quarters qqqq;
}memory_word;

enum{mem_max= 30000};
enum{mem_min= 0};
/*:200*//*203:*/
#line 3019 ".\\hint.w"

typedef struct{int16_t mode_field;
pointer head_field,tail_field;
int pg_field,ml_field;
memory_word aux_field;
bs_t bs_field;
bool insert_bs;
scaled ds_field,dw_field,di_field,hs_field;
uint32_t np_field;
}list_state_record;
/*:203*//*208:*/
#line 3088 ".\\hint.w"

typedef struct{
pointer p;
int i;
pointer g;
scaled s;
}stream_t;
/*:208*//*253:*/
#line 3895 ".\\hint.w"

extern uint8_t*hpos,*hend;

enum{font_mem_size= 20000};
typedef uint16_t font_index;
typedef uint8_t internal_font_number;
enum{font_max= 75};
typedef uint16_t font_index;
/*:253*/
#line 3912 ".\\hint.w"

/*13:*/
#line 456 ".\\hint.w"

extern pointer*pointer_def[32];
extern scaled hhsize,hvsize;
/*:13*//*18:*/
#line 500 ".\\hint.w"

extern int32_t*integer_def;
/*:18*//*27:*/
#line 556 ".\\hint.w"

extern scaled*dimen_def;
/*:27*//*31:*/
#line 572 ".\\hint.w"

extern void print_xdimen(int i);
/*:31*//*34:*/
#line 607 ".\\hint.w"

extern pointer hget_param_glue(uint8_t n);
/*:34*//*43:*/
#line 678 ".\\hint.w"

extern void print_baseline_skip(int i);
extern pointer happend_to_vlist(pointer b);
/*:43*//*95:*/
#line 1425 ".\\hint.w"

extern pointer new_character(uint8_t f,uint8_t c);
/*:95*//*98:*/
#line 1444 ".\\hint.w"

extern pointer new_penalty(int m);
/*:98*//*105:*/
#line 1501 ".\\hint.w"

extern pointer new_math(scaled w,small_number s);
/*:105*//*123:*/
#line 1718 ".\\hint.w"

extern pointer new_glue(pointer q);
extern pointer get_node(int s);
extern pointer avail;
extern pointer get_avail(void);
/*:123*//*137:*/
#line 2069 ".\\hint.w"

extern pointer new_null_box(void);
/*:137*//*148:*/
#line 2270 ".\\hint.w"

extern pointer hpack(pointer p,scaled w,small_number m);
/*:148*//*154:*/
#line 2329 ".\\hint.w"

extern pointer new_kern(scaled w);
/*:154*//*169:*/
#line 2468 ".\\hint.w"

extern pointer new_ligature(uint8_t f,uint8_t c,pointer q);
/*:169*//*182:*/
#line 2725 ".\\hint.w"

extern void line_break(int final_widow_penalty);
extern pointer just_box;
extern void pop_nest(void);
/*:182*//*198:*/
#line 2928 ".\\hint.w"

extern int half(int x);
extern scaled x_over_n(scaled x,int n);
extern scaled xn_over_d(scaled x,int n,int d);
extern halfword badness(scaled t,scaled s);
/*:198*//*199:*/
#line 2943 ".\\hint.w"

extern memory_word font_info[];
extern char**const font_name;
extern int*const width_base;
extern int*const height_base;
extern int*const depth_base;
extern int*const char_base;
extern int*const param_base;

extern eight_bits*const font_bc,*const font_ec;
/*:199*//*201:*/
#line 2987 ".\\hint.w"

extern memory_word*const mem;
extern pointer temp_ptr;
extern pointer lo_mem_max;
extern pointer hi_mem_min;
extern pointer mem_end;
extern void free_node(pointer p,halfword s);
extern void flush_node_list(pointer p);
extern void hmem_init(void);
/*:201*//*202:*/
#line 3003 ".\\hint.w"

extern void delete_glue_ref(pointer p);
extern pointer copy_node_list(pointer p);

/*:202*//*204:*/
#line 3032 ".\\hint.w"

extern list_state_record cur_list;
extern pointer new_rule(void);
extern pointer get_node(int s);
extern void hlist_init(void);

extern int var_used,dyn_used;

enum{nest_size= 40};
extern list_state_record nest[nest_size+1];
extern uint8_t nest_ptr;
extern uint8_t max_nest_stack;

extern void push_nest(void);
extern void pop_nest(void);
/*:204*//*207:*/
#line 3078 ".\\hint.w"

extern void print_ln(void);
extern int font_in_short_display;
/*:207*//*210:*/
#line 3121 ".\\hint.w"

extern scaled*const total_stretch,*const total_shrink;
extern stream_t stream[256];
extern bool hbuild_page(void);
extern bool hits_all_over(void);
extern void hpage_init(void);
extern void hresume_after_output(void);
extern uint8_t page_contents;
extern scaled page_depth,page_max_depth;
extern int insert_penalties;
extern pointer best_page_break;
extern scaled best_size;
/*:210*//*213:*/
#line 3160 ".\\hint.w"

extern scaled*const active_width;
/*:213*//*214:*/
#line 3167 ".\\hint.w"

extern pointer hpack(pointer p,scaled w,small_number m);
#define vpack(...) vpackage(__VA_ARGS__, max_dimen)  
extern pointer vpackage(pointer p,scaled h,small_number m,scaled l);
extern pointer adjust_tail;
/*:214*//*215:*/
#line 3177 ".\\hint.w"

extern void hdisplay(pointer p,pointer a,bool l);
/*:215*//*217:*/
#line 3196 ".\\hint.w"

extern pointer new_spec(pointer p);
extern void append_to_vlist(pointer b,uint32_t offset);
/*:217*//*220:*/
#line 3259 ".\\hint.w"

extern bool hbuild_page_up(void);
/*:220*//*225:*/
#line 3353 ".\\hint.w"

extern scaled page_so_far[8];
extern int least_page_cost;
/*:225*//*246:*/
#line 3698 ".\\hint.w"

extern void show_box(pointer p);
/*:246*//*248:*/
#line 3782 ".\\hint.w"

#if 0
extern scaled hsize,vsize;
#endif
/*:248*/
#line 3913 ".\\hint.w"

/*:254*/
