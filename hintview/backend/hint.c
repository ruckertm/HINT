/*686:*/
#line 14760 "hint.w"

#include "basetypes.h"
#include <string.h> 
#include <math.h> 
#include <zlib.h> 

#include <ft2build.h> 
#include <freetype/tttags.h> 
#include <freetype/tttables.h> 
#include <freetype/ftglyph.h> 
#include <freetype/ftadvanc.h> 
#include FT_FREETYPE_H

#include "error.h"
#include "format.h"
#include "hint.h"
#include "rendernative.h"
#include "get.h"

#define banner "This is HINT based on TeX, Version 3.141592653" \

#define odd(X) ((X) &1) 
#define abs(X) ((X) > -(X) ?(X) :-(X) ) 
#define round(X) ((int) ((X) >=0.0?floor((X) +0.5) :ceil((X) -0.5) ) )  \

#define mem_bot 0 \

#define mem_top mem_max \
 \

#define font_base 0 \
 \
 \

#define incr(A) A= A+1
#define decr(A) A= A-1
#define negate(A) A= -A
#define loop while(true) 
#define do_nothing 
#define empty 0 \
 \

#define print_lc_hex(A)  \
if((A) <10) print_char((A) +'0') ;else print_char((A) -10+'a') 
#define print_ASCII(k)  \
if((k<' ') ||(k> '~') )  \
{print("^^") ; \
if(k<0100) print_char(k+0100) ; \
else if(k<0200) print_char(k-0100) ; \
else{print_lc_hex(k/16) ;print_lc_hex(k%16) ;} \
} \
else print_char(k)  \

#define unity 0200000 \
 \

#define inf_bad 10000 \

#define set_glue_ratio_zero(A) A= 0.0
#define set_glue_ratio_one(A) A= 1.0
#define unfix(A) ((double) (A) ) 
#define fix(A) ((glue_ratio) (A) ) 
#define float_constant(A) ((double) (A) )  \

#define min_quarterword 0
#define min_halfword 0
#define max_halfword 65535 \
 \

#define qi(A) A+min_quarterword \

#define qo(A) A-min_quarterword \
 \

#define sc i \

#define pointer halfword
#define null min_halfword \

#define link(A) mem[A].hh.rh
#define info(A) mem[A].hh.lh \

#define mem_end mem_top
#define free_avail(A)  \
{link(A) = avail;avail= A; \
decr_dyn_used; \
} \
 \

#define empty_flag max_halfword
#define is_empty(A) (link(A) ==empty_flag) 
#define node_size(A) info(A) 
#define llink(A) info(A+1) 
#define rlink(A) link(A+1)  \

#define type(A) mem[A].hh.b0
#define subtype(A) mem[A].hh.b1 \

#define is_char_node(A) (A>=hi_mem_min)  \

#define font(A) type(A) 
#define character(A) subtype(A)  \

#define hlist_node 0
#define box_node_size 9
#define width_offset 1
#define depth_offset 2
#define height_offset 3
#define width(A) mem[A+width_offset].sc
#define depth(A) mem[A+depth_offset].sc
#define height(A) mem[A+height_offset].sc
#define shift_amount(A) mem[A+4].sc
#define list_offset 5
#define list_ptr(A) link(A+list_offset) 
#define glue_order(A) subtype(A+list_offset) 
#define glue_sign(A) type(A+list_offset) 
#define normal 0
#define stretching 1
#define shrinking 2
#define glue_offset 6
#define glue_set(A) mem[A+glue_offset].gr \
 \

#define vlist_node 1 \

#define rule_node 2
#define rule_node_size 4
#define null_flag -010000000000
#define is_running(A) (A==null_flag)  \

#define ins_node 3
#define ins_node_size 5
#define float_cost(A) mem[A+1].i
#define ins_ptr(A) info(A+4) 
#define split_top_ptr(A) link(A+4)  \

#define adjust_node 5
#define adjust_ptr(A) mem[A+1].i \

#define ligature_node 6
#define small_node_size 2
#define lig_char(A) A+1
#define lig_ptr(A) link(lig_char(A) )  \

#define disc_node 7
#define replace_count(A) (subtype(A) &0x7F) 
#define set_replace_count(A,B) (subtype(A) = (B) &0x7F) 
#define set_auto_disc(A) (subtype(A) |= 0x80) 
#define is_auto_disc(A) (subtype(A) &0x80) 
#define pre_break(A) llink(A) 
#define post_break(A) rlink(A)  \

#define whatsit_node 8 \

#define math_node 9
#define before 0
#define after 1 \

#define precedes_break(A) (type(A) <math_node) 
#define non_discardable(A) (type(A) <math_node)  \

#define glue_node 10
#define mu_glue 99
#define a_leaders 100
#define c_leaders 101
#define x_leaders 102
#define glue_ptr(A) llink(A) 
#define leader_ptr(A) rlink(A)  \

#define glue_spec_size 4
#define glue_ref_count(A) link(A) 
#define stretch(A) mem[A+2].sc
#define shrink(A) mem[A+3].sc
#define stretch_order(A) type(A) 
#define shrink_order(A) subtype(A) 
#define fil 1
#define fill 2
#define filll 3 \

#define kern_node 11
#define explicit 1
#define acc_kern 2 \

#define penalty_node 12
#define inf_penalty inf_bad
#define eject_penalty (-inf_penalty) 
#define penalty(A) mem[A+1].i \

#define unset_node 13
#define glue_stretch(A) mem[A+glue_offset].sc
#define glue_shrink(A) shift_amount(A) 
#define span_count(A) subtype(A)  \

#define zero_glue mem_bot
#define lo_mem_stat_max zero_glue+glue_spec_size-1 \

#define page_ins_head mem_top
#define contrib_head mem_top-1
#define page_head mem_top-2
#define temp_head mem_top-3
#define hold_head mem_top-4
#define adjust_head mem_top-5
#define active mem_top-7
#define lig_trick mem_top-12
#define hi_mem_stat_min mem_top-13 \

#define hi_mem_stat_usage 14 \
 \

#define node_list_display(A)  \
{depth_level++;show_node_list(A) ;depth_level--; \
} \

#define token_ref_count(A) info(A)  \

#define fast_delete_glue_ref(A)  \
{if(glue_ref_count(A) ==null) free_node(A,glue_spec_size) ; \
else decr(glue_ref_count(A) ) ; \
} \

#define add_token_ref(A) incr(token_ref_count(A) ) 
#define add_glue_ref(A) incr(glue_ref_count(A) ) 
#define add_xdimen_ref(A) if(A!=null) incr(xdimen_ref_count(A) )  \

#define ignore_depth -65536000 \

#define head cur_list.head_field
#define tail cur_list.tail_field
#define prev_graf cur_list.pg_field
#define aux cur_list.aux_field
#define prev_depth aux.sc
#define cur_bs cur_list.bs_field
#define cur_ls cur_list.ls_field
#define cur_lsl cur_list.lsl_field
#define needs_bs (cur_list.bs_pos!=NULL) 
#define prev_height cur_list.ht_field
#define node_pos cur_list.np_field
#define node_pos1 (nest_ptr==0?0:nest[nest_ptr-1].np_field)  \

#define tail_append(A) {link(tail) = A;tail= link(tail) ; \
} \

#define right_skip_code 8 \

#define line_skip pointer_def[glue_kind][line_skip_no]
#define baseline_skip pointer_def[glue_kind][baseline_skip_no]
#define left_skip pointer_def[glue_kind][left_skip_no]
#define right_skip pointer_def[glue_kind][right_skip_no]
#define top_skip pointer_def[glue_kind][top_skip_no]
#define split_top_skip pointer_def[glue_kind][split_top_skip_no] \

#define par_shape_ptr null
#define box(A) (*box_ptr(A) )  \

#define pretolerance integer_def[pretolerance_no]
#define tolerance integer_def[tolerance_no]
#define line_penalty integer_def[line_penalty_no]
#define hyphen_penalty integer_def[hyphen_penalty_no]
#define ex_hyphen_penalty integer_def[ex_hyphen_penalty_no]
#define club_penalty integer_def[club_penalty_no]
#define display_widow_penalty integer_def[display_widow_penalty_no]
#define broken_penalty integer_def[broken_penalty_no]
#define pre_display_penalty integer_def[pre_display_penalty_no]
#define post_display_penalty integer_def[post_display_penalty_no]
#define inter_line_penalty integer_def[inter_line_penalty_no]
#define double_hyphen_demerits integer_def[double_hyphen_demerits_no]
#define final_hyphen_demerits integer_def[final_hyphen_demerits_no]
#define adj_demerits integer_def[adj_demerits_no]
#define looseness integer_def[looseness_no]
#define tracing_paragraphs (debugflags&DBGTEX) 
#define tracing_pages (debugflags&DBGPAGE) 
#define hang_after integer_def[hang_after_no] \

#define line_skip_limit dimen_def[line_skip_limit_no]
#define max_depth dimen_def[max_depth_no]
#define pre_display_size cur_list.ds_field
#define display_width cur_list.dw_field
#define display_indent cur_list.di_field
#define hang_indent dimen_def[hang_indent_no]
#define emergency_stretch dimen_def[emergency_stretch_no] \

#define max_dimen 07777777777 \

#define math_quad dimen_def[math_quad_no] \

#define quad_code 6 \

#define char_info(A,B) font_info[char_base[A]+B].qqqq
#define char_width(A,B) (width_base[A]!=0? \
font_info[width_base[A]+char_info(A,B) .b0].sc:ft_char_width(A,B) ) 
#define char_exists(A) (A.b0> min_quarterword) 
#define height_depth(A) qo(A.b1) 
#define char_height(A,B) font_info[height_base[A]+(B) /16].sc
#define char_depth(A,B) font_info[depth_base[A]+(B) %16].sc \
 \

#define param_end(A) param_base[A]].sc
#define param(A) font_info[A+param_end
#define quad param(quad_code)  \

#define abort goto bad_tfm \

#define fget (hpos++) 
#define fskip(A) (hpos+= A) 
#define fskip_four fskip(4) 
#define fbyte (*hpos) 
#define read_sixteen(A) {A= fbyte; \
if(A> 127) abort; \
fget;A= A*0400+fbyte; \
}
#define store_four_quarters(A) {fget;a= fbyte;qw.b0= qi(a) ; \
fget;b= fbyte;qw.b1= qi(b) ; \
fget;c= fbyte;qw.b2= qi(c) ; \
fget;d= fbyte;qw.b3= qi(d) ; \
A= qw; \
} \

#define store_scaled(A) {fget;a= fbyte;fget;b= fbyte; \
fget;c= fbyte;fget;d= fbyte; \
sw= (((((d*z) /0400) +(c*z) ) /0400) +(b*z) ) /beta; \
if(a==0) A= sw;else if(a==255) A= sw-alpha;else abort; \
} \

#define adjust(A) A[f]= qo(A[f])  \
 \

#define exactly 0
#define additional 1
#define natural 0,additional \

#define vpack(A,B) vpackage(A,B,max_dimen)  \

#define tight_fit 3 \

#define loose_fit 1 \

#define very_loose_fit 0 \

#define decent_fit 2 \

#define active_node_size 3
#define fitness(A) subtype(A) 
#define break_node(A) rlink(A) 
#define line_number(A) llink(A) 
#define total_demerits(A) mem[A+2].i
#define unhyphenated 0
#define hyphenated 1
#define last_active active \

#define passive_node_size 2
#define cur_break(A) rlink(A) 
#define prev_break(A) llink(A) 
#define serial(A) info(A)  \

#define delta_node_size 7
#define delta_node 2 \

#define do_all_six(A) A(1) ;A(2) ;A(3) ;A(4) ;A(5) ;A(6)  \

#define check_shrinkage(A) if((shrink_order(A) !=normal) &&(shrink(A) !=0) )  \
{A= finite_shrink(A) ; \
} \

#define copy_to_cur_active(A) cur_active_width[A]= active_width[A]
#define update_width(A)  \
cur_active_width[A]= cur_active_width[A]+mem[r+A].sc \

#define awful_bad 07777777777 \

#define set_break_width_to_background(A) break_width[A]= background[A] \

#define convert_to_break_width(A)  \
mem[prev_r+A].sc= mem[prev_r+A].sc \
-cur_active_width[A]+break_width[A]
#define store_break_width(A) active_width[A]= break_width[A]
#define new_delta_to_break_width(A)  \
mem[q+A].sc= break_width[A]-cur_active_width[A] \

#define new_delta_from_break_width(A) mem[q+A].sc=  \
cur_active_width[A]-break_width[A] \

#define combine_two_deltas(A) mem[prev_r+A].sc= mem[prev_r+A].sc+mem[r+A].sc
#define downdate_width(A) cur_active_width[A]= cur_active_width[A]- \
mem[prev_r+A].sc \

#define update_active(A) active_width[A]= active_width[A]+mem[r+A].sc \

#define store_background(A) active_width[A]= background[A] \

#define act_width active_width[1]
#define kern_break {if(!is_char_node(link(cur_p) ) &&auto_breaking)  \
if(type(link(cur_p) ) ==glue_node) try_break(0,unhyphenated) ; \
act_width= act_width+width(cur_p) ; \
} \

#define next_break prev_break \

#define active_height active_width
#define cur_height active_height[1]
#define set_height_zero(A) active_height[A]= 0 \

#define deplorable 100000 \

#define inserts_only 1 \

#define box_there 2 \

#define page_ins_node_size 4
#define inserting 0
#define split_up 1
#define broken_ptr(A) link(A+1)  \

#define broken_ins(A) info(A+1) 
#define last_ins_ptr(A) link(A+2) 
#define best_ins_ptr(A) info(A+2)  \

#define page_goal page_so_far[0]
#define page_total page_so_far[1]
#define page_shrink page_so_far[6]
#define page_depth page_so_far[7] \

#define print_plus(A,B) if(page_so_far[A]!=0)  \
{print(" plus ") ;print_scaled(page_so_far[A]) ;print(B) ;} \

#define set_page_so_far_zero(A) page_so_far[A]= 0 \

#define contrib_tail nest[0].tail_field \

#define write_node_size 2
#define open_node_size 3
#define open_node 0
#define write_node 1
#define close_node 2
#define special_node 3
#define language_node 4
#define what_lang(A) link(A+1) 
#define what_lhm(A) type(A+1) 
#define what_rhm(A) subtype(A+1) 
#define write_tokens(A) link(A+1)  \

#define hitex_ext language_node+1
#define param_node hitex_ext
#define param_node_size 3
#define param_type(A) type(A+1) 
#define glue_type 2
#define param_no(A) subtype(A+1) 
#define param_value(A) mem[A+2] \

#define par_node hitex_ext+1
#define par_node_size 5
#define par_penalty(A) mem[A+1].i
#define par_extent(A) link(A+3) 
#define par_params(A) info(A+4) 
#define par_list(A) link(A+4)  \

#define disp_node hitex_ext+2
#define disp_node_size 3
#define display_left(A) type(A+1) 
#define display_no_bs(A) subtype(A+1) 
#define display_params(A) link(A+1) 
#define display_formula(A) link(A+2) 
#define display_eqno(A) info(A+2)  \

#define baseline_node hitex_ext+3
#define baseline_node_size small_node_size \

#define image_node hitex_ext+4
#define image_node_size 6
#define image_width(A) mem[A+1].sc
#define image_height(A) mem[A+2].sc
#define image_no(A) link(A+3) 
#define image_alt(A) link(A+5)  \

#define hpack_node hitex_ext+5
#define vpack_node hitex_ext+6
#define pack_node_size box_node_size
#define pack_m(A) type(A+list_offset) 
#define pack_limit(A) mem[(A) +1+list_offset].sc
#define pack_extent(A) link(A+2+list_offset)  \

#define hset_node hitex_ext+7
#define vset_node hitex_ext+8
#define set_node_size box_node_size
#define set_stretch_order glue_sign
#define set_shrink_order glue_order
#define set_stretch(A) mem[(A) +1+list_offset].sc
#define set_extent(A) pack_extent(A) 
#define set_shrink(A) mem[(A) +3+list_offset].sc \

#define align_node hitex_ext+9
#define align_node_size 4
#define align_extent(A) link(A+2) 
#define align_m(A) type(A+2) 
#define align_preamble(A) info(A+3) 
#define align_list(A) link(A+3)  \

#define setpage_node hitex_ext+10
#define setpage_node_size 6
#define setpage_topskip(A) link(A+2) 
#define setpage_height(A) info(A+4) 
#define setpage_width(A) link(A+4) 
#define setpage_list(A) info(A+5) 
#define setpage_streams(A) link(A+5)  \

#define setstream_node hitex_ext+11
#define setstream_node_size 6
#define setstream_max(A) info(A+3) 
#define setstream_width(A) link(A+3) 
#define setstream_topskip(A) info(A+4) 
#define setstream_height(A) link(A+4) 
#define setstream_before(A) info(A+5) 
#define setstream_after(A) link(A+5)  \

#define stream_node hitex_ext+12
#define stream_node_size 2
#define stream_number(A) type(A+1) 
#define stream_insertion(A) subtype(A+1)  \
 \

#define xdimen_node hitex_ext+15
#define xdimen_node_size 4
#define xdimen_ref_count(A) link(A) 
#define xdimen_width(A) mem[A+1].sc
#define xdimen_hfactor(A) mem[A+2].sc
#define xdimen_vfactor(A) mem[A+3].sc \

#define ignore_node hitex_ext+16
#define ignore_node_size small_node_size
#define ignore_info(A) type(A+1) 
#define ignore_list(A) link(A+1)  \

#define color_node hitex_ext+17
#define end_color_node hitex_ext+18
#define no_color_node hitex_ext+22
#define color_node_size small_node_size
#define color_ref(A) type(A+1)  \

#define label_node hitex_ext+23
#define label_node_size 2
#define label_ref(A) link(A+1)  \

#define start_link_node hitex_ext+24
#define end_link_node hitex_ext+25
#define link_node_size 3
#define as_color(A) (A) 
#define as_label(A) ((A) +1)  \

#define outline_node hitex_ext+26
#define outline_node_size 3
#define outline_ptr(A) link(A+2) 
#define outline_depth(A) info(A+2)  \

#define utf_char_node hitex_ext+27
#define utf_char_node_size small_node_size
#define utf_font_char(A) mem[A+1].i
#define utf_font(A) (utf_font_char(A) >>24) 
#define utf_char(A) (utf_font_char(A) &0xFFFFFF)  \
 \
 \

#define adv_past(A) {} \

#define billion float_constant(1000000000) 
#define vet_glue(A) glue_temp= A; \
if(glue_temp> billion)  \
glue_temp= billion; \
else if(glue_temp<-billion)  \
glue_temp= -billion \


#line 14779 "hint.w"

enum{/*5:*/
#line 468 "hint.w"

mem_max= 65534,


mem_min= 0,


max_print_line= 79,
font_max= 255,

font_mem_size= 65535,
nest_size= 400,



/*:5*/
#line 14780 "hint.w"
};
/*15:*/
#line 661 "hint.w"

typedef int scaled;
typedef int32_t nonnegative_integer;
typedef int8_t small_number;


/*:15*//*20:*/
#line 814 "hint.w"

#if __SIZEOF_FLOAT__==4
#else
#line 817 "hint.w"
#error  float type must have size 4
#endif
#line 819 "hint.w"
 typedef float glue_ratio;

/*:20*//*23:*/
#line 897 "hint.w"

typedef uint8_t eight_bits;
typedef uint8_t quarterword;
typedef uint16_t halfword;
typedef int8_t two_choices;
typedef int8_t four_choices;
typedef struct{
halfword rh;
union{
halfword lh;
struct{quarterword b0;quarterword b1;};
};}two_halves;
typedef struct{
quarterword b0;
quarterword b1;
quarterword b2;
quarterword b3;
}four_quarters;
typedef struct{
union{
int i;
glue_ratio gr;
two_halves hh;
four_quarters qqqq;
};}memory_word;
typedef struct{FILE*f;memory_word d;}word_file;


/*:23*//*54:*/
#line 1530 "hint.w"

typedef int8_t glue_ord;

/*:54*//*99:*/
#line 2249 "hint.w"

typedef struct{
pointer head_field,tail_field;
int pg_field;
pointer bs_field,ls_field;
scaled lsl_field;
uint8_t*bs_pos;
scaled hs_field;
scaled ds_field,dw_field,di_field;
scaled ht_field;
uint32_t np_field;
memory_word aux_field;
}list_state_record;

/*:99*//*112:*/
#line 2569 "hint.w"

typedef uint8_t internal_font_number;
typedef uint16_t font_index;

/*:112*//*318:*/
#line 6722 "hint.w"

typedef struct{pointer bs,ls;scaled lsl;}BaselineSkip;
/*:318*//*330:*/
#line 6930 "hint.w"

typedef struct{
uint8_t n,k;
int32_t v;
}Param;

typedef struct ParamDef{
struct ParamDef*next;
Param p;}ParamDef;
/*:330*//*364:*/
#line 7455 "hint.w"

typedef uint32_t ColorSet[12];
/*:364*//*617:*/
#line 12280 "hint.w"

typedef struct{
uint64_t pos;
uint8_t where;
scaled top,bottom,left,right;
}Link;
/*:617*//*624:*/
#line 12528 "hint.w"

typedef enum{no_format= 0,pk_format,ft_format}FontFormat;
/*:624*//*658:*/
#line 13523 "hint.w"

typedef struct{
scaled w,h,hoff,voff;
unsigned int OGLtexture;
/*631:*/
#line 12642 "hint.w"

unsigned char pk_glyph_flags;
unsigned char*pk_glyph_data;
/*:631*/
#line 13527 "hint.w"

}Gcache;
/*:658*/
#line 14781 "hint.w"


/*384:*/
#line 7805 "hint.w"

#define HGET_STRING(S) S= (char*)hpos;\
 while(hpos<hend && *hpos!=0) { RNG("String character",*hpos,0x20,0x7E); hpos++;}\
 hpos++;
/*:384*//*385:*/
#line 7817 "hint.w"

#define HGET_XDIMEN(I,X) \
{ if((I)&b100) HGET32((X).w); else (X).w= 0;\
  if((I)&b010) (X).h= hget_float32();  else (X).h= 0.0;\
  if((I)&b001) (X).v= hget_float32(); else (X).v= 0.0;\
}
/*:385*//*389:*/
#line 7920 "hint.w"

#define HGET_STRETCH(F,O) { Stch _st;  HGET32(_st.u); (O)= _st.u&3;  _st.u&= ~3; (F)= (scaled)(_st.f*ONE); }
/*:389*//*391:*/
#line 7931 "hint.w"

#define HGET_GLYPH(I) \
{uint8_t f; uint32_t c;\
  if (I==1) c= HGET8;\
  else if (I==2) HGET16(c);\
  else if (I==3) HGET24(c);\
  else if (I==4) HGET32(c);\
  f= HGET8; REF_RNG(font_kind,f);\
  if (c<0x100) tail_append(new_character(f,c))\
  else tail_append(new_utf_char(f,c))\
}
/*:391*//*401:*/
#line 8043 "hint.w"

#define HGET_RULE(I)\
pointer p= new_rule();\
if ((I)&b100) HGET32(height(p)); else height(p)= null_flag;\
if ((I)&b010) HGET32(depth(p)); else depth(p)= null_flag;\
if ((I)&b001) HGET32(width(p)); else width(p)= null_flag;
/*:401*//*407:*/
#line 8105 "hint.w"

#define HGET_GLUE(I) \
  p=  get_node(glue_spec_size); \
  if((I)!=b111) { if ((I)&b100) HGET32(width(p)); else width(p)= 0; }\
  if((I)&b010) HGET_STRETCH(stretch(p),stretch_order(p)) else stretch(p)= 0, stretch_order(p)= normal;\
  if((I)&b001) HGET_STRETCH(shrink(p),shrink_order(p)) else shrink(p)= 0, shrink_order(p)= normal;\
  if(I==b111) width(p)= hget_xdimen_node();
/*:407*//*417:*/
#line 8382 "hint.w"

#define HGET_BOX(I) \
p= new_null_box();\
HGET32(height(p));\
if ((I)&b001) HGET32(depth(p));\
HGET32(width(p));\
if ((I)&b010) HGET32(shift_amount(p));\
if ((I)&b100) {int8_t x; glue_set(p)= hget_float32();\
  x= HGET8;  glue_order(p)= x&0xF;\
  x= x>>4; glue_sign(p)= (x<0?shrinking:(x> 0?stretching:normal));}\
list_ptr(p)= hget_list_pointer();
/*:417*//*424:*/
#line 8506 "hint.w"

#define HGET_SET(I) \
 scaled x, st, sh; uint8_t sto, sho; \
 p= new_null_box();\
 HGET32(height(p)); if ((I)&b001) HGET32(depth(p)); HGET32(width(p));\
 if ((I)&b010) HGET32(shift_amount(p));\
 HGET_STRETCH(st,sto);   HGET_STRETCH(sh,sho);\
 if ((I)&b100) x=  hget_xdimen_node();  else x= hget_xdimen_ref(HGET8);\
 list_ptr(p)= hget_list_pointer();
/*:424*//*430:*/
#line 8664 "hint.w"

#define HGET_PACK(K,I) \
{ pointer p; scaled x, s= 0, d;  uint8_t m; \
 if ((I)&b001) m= additional; else m= exactly; \
 if ((I)&b010) HGET32(s);\
 if (K==vpack_kind) HGET32(d); \
 if ((I)&b100) x=  hget_xdimen_node();  else x= hget_xdimen_ref(HGET8);\
 p= hget_list_pointer(); \
 if (K==vpack_kind) { if (d<=MAX_DIMEN && d>=-MAX_DIMEN) p= vpackage(p,x,m,d); else p= vtop(p,x,m,d); } \
 else p= hpack(p,x,m);\
 shift_amount(p)= s;\
 happend_to_vlist(p);}
/*:430*//*435:*/
#line 8750 "hint.w"

#define HGET_KERN(I) \
pointer p; scaled x; \
if (((I)&b011)==0) x= hget_dimen_ref(HGET8);\
else if (((I)&b011)==1) x= hget_xdimen_ref(HGET8);\
else if (((I)&b011)==2) HGET32(x);\
else if (((I)&b011)==3) x= hget_xdimen_node();\
p= new_kern(x);\
if ((I)&b100) subtype(p)= explicit;\
tail_append(p);
/*:435*//*439:*/
#line 8801 "hint.w"

#define HGET_LEADERS(I) \
{pointer p;\
 if ((I)&b100)p= hget_glue_node(); else {p= spec2glue(zero_glue); incr(glue_ref_count(zero_glue));} \
subtype(p)= a_leaders+((I)&b011)-1;\
if (KIND(*hpos)==rule_kind) leader_ptr(p)= hget_rule_node(); \
else if (KIND(*hpos)==hbox_kind) leader_ptr(p)= hget_hbox_node(); \
else  leader_ptr(p)= hget_vbox_node();\
tail_append(p);}
/*:439*//*443:*/
#line 8847 "hint.w"

#define HGET_BASELINE(I) \
  cur_list.bs_pos= hpos-1; \
  if((I)&b001) HGET32(cur_lsl); else cur_lsl= 0; \
  if((I)&b100) cur_bs= hget_glue_spec(); else cur_bs= zero_glue; \
  if((I)&b010) cur_ls= hget_glue_spec(); else cur_ls= zero_glue;
/*:443*//*448:*/
#line 8901 "hint.w"

#define HGET_LIG(I) \
{pointer p,q;uint8_t f;\
f= HGET8;\
if ((I)==7) q= hget_list_pointer(); else q= hget_text_list(I);\
if (q==null) QUIT("Ligature with empty list");\
p= new_ligature(f, character(q), link(q)); tail_append(p);\
link(q)= null; flush_node_list(q);\
}
/*:448*//*452:*/
#line 8953 "hint.w"

#define HGET_DISC(I)\
  pointer p= new_disc(); \
  if ((I)&b100) {uint8_t r; r= HGET8; set_replace_count(p,r); \
                 if ((r&0x80)==0) set_auto_disc(p); }\
  else  set_auto_disc(p); \
  if ((I)&b010) pre_break(p)= hget_list_pointer(); \
  if ((I)&b001) post_break(p)= hget_list_pointer();
/*:452*//*458:*/
#line 9031 "hint.w"

#define HGET_PAR(I) \
{ scaled x= 0;\
  ParamDef *q;\
  if ((I)==b100) q= hget_param_list_ref(HGET8);\
  if ((I)&b100) x= hget_xdimen_node(); else x= hget_xdimen_ref(HGET8);\
  if ((I)&b010) q= hget_param_list_node(); \
  else if ((I)!=b100) q= hget_param_list_ref(HGET8);\
  hget_paragraph(x,0,q);\
}
/*:458*//*480:*/
#line 9508 "hint.w"

#define HGET_MATH(I) \
{ ParamDef *q; pointer p= null, a= null;\
if ((I)&b100) q= hget_param_list_node(); else q= hget_param_list_ref(HGET8);\
if ((I)&b010) a= hget_hbox_node(); \
p= hget_list_pointer(); \
if ((I)&b001) a= hget_hbox_node();\
hset_param_list(q); hdisplay(p,a,((I)&b010)!=0); hrestore_param_list();\
}
/*:480*//*486:*/
#line 9577 "hint.w"

#define HGET_ADJUST(I) \
{ pointer p;\
  p= get_node(small_node_size); type(p)= adjust_node; subtype(p)= normal;\
  adjust_ptr(p)= hget_list_pointer(); \
  tail_append(p);\
}
/*:486*//*488:*/
#line 9593 "hint.w"

#define HGET_TABLE(I) \
if(I&b010) ; else ;\
if ((I)&b001) ; else ;\
if ((I)&b100) hget_xdimen_node(); else hget_xdimen_ref(HGET8);\
hget_list_pointer();  \
hget_list_pointer(); 
/*:488*//*493:*/
#line 9680 "hint.w"

#define HGET_STREAM(I) \
{ ParamDef *q;  pointer p;\
  p= get_node(ins_node_size); type(p)= ins_node;\
  subtype(p)= HGET8;RNG("Stream",subtype(p),1,254); \
  if ((I)&b010) q= hget_param_list_node(); else q= hget_param_list_ref(HGET8); \
  ins_ptr(p)= hget_list_pointer(); \
  hset_stream_params(p,q); \
  tail_append(p);}
/*:493*//*497:*/
#line 9712 "hint.w"

#define HGET_IMAGE(I) \
{pointer p; float32_t a= 0.0; scaled w,h;\
p= get_node(image_node_size);  type(p)= whatsit_node; subtype(p)= image_node;\
HGET16(image_no(p));RNG("Section number",image_no(p),3,max_section_no);  \
if ((I)&b100) { a= hget_float32();\
  if ((I)==b111) {w= hget_xdimen_node();h= hget_xdimen_node();}\
  else if ((I)==b110) {h= hget_xdimen_ref(HGET8);w= hget_xdimen_node();}\
  else if ((I)==b101) {w= hget_xdimen_ref(HGET8);h= hget_xdimen_node();}\
  else  {w= hget_xdimen_ref(HGET8);h= hget_xdimen_ref(HGET8);}\
  if (a!=0.0) { if (h==0) h= round(w/a); else if (w==0) w= round(h*a);\
  else if (w> round(h*a)) w= round(h*a); else if (h> round(w/a)) h= round(w/a);}}\
else if((I)==b011) {HGET32(w);HGET32(h);} \
else if((I)==b010) { a= hget_float32(); HGET32(w); h= round(w/a);}\
else if((I)==b001){ a= hget_float32(); HGET32(h); w= round(h*a);}\
if (w==0 || h==0) {MESSAGE("Incomplete dimensions in image %d",image_no(p));\
  if (w!=0) h= w; else if (h!=0) w= h; else w= h= 100*ONE; }\
image_width(p)= w; image_height(p)= h;\
image_alt(p)= hget_list_pointer();\
tail_append(p);}
/*:497*//*505:*/
#line 9814 "hint.w"

#define HGET_LINK(I) \
{ pointer p;\
  p= get_node(link_node_size);  type(p)= whatsit_node;\
  if (I&b010) subtype(p)= start_link_node; else subtype(p)= end_link_node;\
  if (I&b001) HGET16(label_ref(as_label(p))); else label_ref(as_label(p))= HGET8; \
  if (I&b100) color_ref(as_color(p))= HGET8; else color_ref(as_color(p))= (I&b010)?1:0xFF;\
  RNG("label",label_ref(as_label(p)),0,max_ref[label_kind]);\
  if (color_ref(as_color(p))!=0xFF)\
    RNG("label color",color_ref(as_color(p)),0,max_ref[color_kind]);\
  tail_append(p);}
/*:505*/
#line 14783 "hint.w"

/*386:*/
#line 7825 "hint.w"

#define HTEG_XDIMEN(I,X) \
  if((I)&b001) (X).v= hteg_float32(); else (X).v= 0.0;\
  if((I)&b010) (X).h= hteg_float32();  else (X).h= 0.0;\
  if((I)&b100) HTEG32((X).w); else (X).w= 0;\
/*:386*//*390:*/
#line 7923 "hint.w"

#define HTEG_STRETCH(F,O) { Stch _st;  HTEG32(_st.u); (O)= _st.u&3;  _st.u&= ~3; (F)= (scaled)(_st.f*ONE); }
/*:390*//*392:*/
#line 7944 "hint.w"

#define HTEG_GLYPH(I) \
{uint8_t f; uint32_t c;\
  f= HTEG8; REF_RNG(font_kind,f);\
  if (I==1) c= HTEG8;\
  else if (I==2) HTEG16(c);\
  else if (I==3) HTEG24(c);\
  else if (I==4) HTEG32(c);\
  if (c<0x100) tail_append(new_character(f,c))\
  else tail_append(new_utf_char(f,c))\
}
/*:392*//*402:*/
#line 8052 "hint.w"

#define HTEG_RULE(I)\
pointer p= new_rule();\
if ((I)&b001) HTEG32(width(p)); else width(p)= null_flag;\
if ((I)&b010) HTEG32(depth(p)); else depth(p)= null_flag;\
if ((I)&b100) HTEG32(height(p)); else height(p)= null_flag;
/*:402*//*409:*/
#line 8118 "hint.w"

#define HTEG_GLUE(I) \
  p=  get_node(glue_spec_size); \
  if(I==b111) width(p)= hget_xdimen_node();\
  if((I)&b001) HTEG_STRETCH(shrink(p),shrink_order(p)) else shrink(p)= 0, shrink_order(p)= normal;\
  if((I)&b010) HTEG_STRETCH(stretch(p),stretch_order(p)) else stretch(p)= 0, stretch_order(p)= normal;\
  if((I)!=b111) { if ((I)&b100) HGET32(width(p)); else width(p)= 0; }
/*:409*//*418:*/
#line 8395 "hint.w"

#define HTEG_BOX(I) \
p= new_null_box();\
list_ptr(p)= hteg_list_pointer();\
if ((I)&b100) {int8_t x= HTEG8; glue_order(p)= x&0xF;\
   x= x>>4; glue_sign(p)= (x<0?shrinking:(x> 0?stretching:normal));\
   glue_set(p)= hteg_float32(); }\
if ((I)&b010) HTEG32(shift_amount(p));\
HTEG32(width(p));\
if ((I)&b001) HTEG32(depth(p));\
HTEG32(height(p));\
node_pos= hpos-hstart-1;
/*:418*//*425:*/
#line 8518 "hint.w"

#define HTEG_SET(I) \
  scaled x, st, sh; uint8_t sto, sho; \
  p= new_null_box();\
  list_ptr(p)= hteg_list_pointer();\
  if ((I)&b100) x= hteg_xdimen_node(); else x= hget_xdimen_ref(HTEG8);\
  HTEG_STRETCH(sh,sho);HTEG_STRETCH(st,sto);\
  if ((I)&b010) HTEG32(shift_amount(p)); \
  HTEG32(width(p));if ((I)&b001) HTEG32(depth(p));HTEG32(height(p)); \
  node_pos= hpos-hstart-1;
/*:425*//*431:*/
#line 8678 "hint.w"

#define HTEG_PACK(K,I) \
{ pointer p; scaled x, s= 0, d;  uint8_t m; \
 p= hteg_list_pointer();\
 if ((I)&b100) x= hteg_xdimen_node();  else x= hget_xdimen_ref(HTEG8);\
 if (K==vpack_kind) HTEG32(d); \
 if ((I)&b010) HTEG32(s);\
 if ((I)&b001) m= additional; else m= exactly; \
 node_pos= hpos-hstart-1;\
 if (K==vpack_kind)  { if (d<=MAX_DIMEN && d>=-MAX_DIMEN) p= vpackage(p,x,m,d); else p= vtop(p,x,m,d); } \
 else p= hpack(p,x,m);\
 shift_amount(p)= s;\
 hprepend_to_vlist(p);}
/*:431*//*436:*/
#line 8763 "hint.w"

#define HTEG_KERN(I) \
pointer p; scaled x; \
if (((I)&b011)==0) x= hget_dimen_ref(HTEG8);\
else if (((I)&b011)==1) x= hget_xdimen_ref(HTEG8);\
else if (((I)&b011)==2) HTEG32(x);\
else if (((I)&b011)==3) x= hteg_xdimen_node();\
p= new_kern(x);\
if ((I)&b100) subtype(p)= explicit;\
tail_append(p);
/*:436*//*440:*/
#line 8812 "hint.w"

#define HTEG_LEADERS(I) \
{pointer p,q;\
if (KIND(*(hpos-1))==rule_kind) q= hteg_rule_node(); \
else if (KIND(*(hpos-1))==hbox_kind) q= hteg_hbox_node(); \
else  q= hteg_vbox_node();\
if ((I)&b100) p= hteg_glue_node(); else {p= spec2glue(zero_glue); incr(glue_ref_count(zero_glue));} \
leader_ptr(p)= q;subtype(p)= a_leaders+((I)&b011)-1;\
tail_append(p);}
/*:440*//*444:*/
#line 8855 "hint.w"

#define HTEG_BASELINE(I) \
  if((I)&b010) cur_ls= hteg_glue_spec(); else cur_ls= zero_glue; \
  if((I)&b100) cur_bs= hteg_glue_spec(); else cur_bs= zero_glue; \
  if((I)&b001) HTEG32(cur_lsl); else cur_lsl= 0; \
  cur_list.bs_pos= hpos-1;
/*:444*//*449:*/
#line 8912 "hint.w"

#define HTEG_LIG(I) \
{pointer p,q;\
if ((I)==7) q= hteg_list_pointer();\
else {uint8_t *t= hpos; hpos= t-I; q= hget_text_list(I); hpos= t-I;}\
if (q==null) QUIT("Ligature with empty list");\
p= new_ligature(0, character(q), link(q)); tail_append(p);\
link(q)= null; flush_node_list(q);\
font(lig_char(p))= HTEG8;\
}
/*:449*//*453:*/
#line 8963 "hint.w"

#define HTEG_DISC(I)\
  pointer p= new_disc(); \
  if ((I)&b001) post_break(p)= hteg_list_pointer(); \
  if ((I)&b010) pre_break(p)= hteg_list_pointer(); \
  if ((I)&b100) {uint8_t r; r= HTEG8; set_replace_count(p,r); \
                 if ((r&0x80)==0) set_auto_disc(p); }\
  else  set_auto_disc(p);
/*:453*//*481:*/
#line 9519 "hint.w"

#define HTEG_MATH(I) \
{ ParamDef *q; pointer p= null, a= null;\
if ((I)&b001) a= hteg_hbox_node();\
p= hteg_list_pointer(); \
if ((I)&b010) a= hteg_hbox_node(); \
if ((I)&b100) q= hteg_param_list_node(); else q= hget_param_list_ref(HTEG8);\
hset_param_list(q); hdisplay(p,a,((I)&b010)!=0); hrestore_param_list();\
}
/*:481*//*489:*/
#line 9602 "hint.w"

#define HTEG_TABLE(I) \
if(I&b010) ; else ;\
if ((I)&b001) ; else ;\
hteg_list_pointer();   \
hteg_list_pointer();  \
if ((I)&b100) hteg_xdimen_node(); else hget_xdimen_ref(HTEG8);
/*:489*//*494:*/
#line 9691 "hint.w"

#define HTEG_STREAM(I) \
{pointer p= get_node(ins_node_size); type(p)= ins_node;\
 ins_ptr(p)= hteg_list_pointer();\
 if ((I)&b010) {ParamDef *q= hteg_param_list_node();  hset_stream_params(p,q);}\
 else {ParamDef *q= hget_param_list_ref(HTEG8);  hset_stream_params(p,q);}\
 subtype(p)= HTEG8;RNG("Stream",subtype(p),1,254);\
 tail_append(p);}
/*:494*//*498:*/
#line 9734 "hint.w"

#define HTEG_IMAGE(I) \
{ pointer p; float32_t a= 0.0; scaled w,h;\
p= get_node(image_node_size);  type(p)= whatsit_node; subtype(p)= image_node;\
image_alt(p)= hteg_list_pointer();\
if ((I)&b100) {\
  if ((I)==b111) {h= hteg_xdimen_node();w= hteg_xdimen_node();}\
  else if ((I)==b110) {w= hteg_xdimen_node();h= hget_xdimen_ref(HTEG8);}\
  else if ((I)==b101) {h= hteg_xdimen_node();w= hget_xdimen_ref(HTEG8);}\
  else  {h= hget_xdimen_ref(HTEG8);w= hget_xdimen_ref(HTEG8);}\
  a= hteg_float32();\
  if (a!=0.0) { if (h==0) h= round(w/a); else if (w==0) w= round(h*a);\
  else if (w> round(h*a)) w= round(h*a); else if (h> round(w/a)) h= round(w/a); }}\
else if((I)==b011) {HTEG32(h);HTEG32(w);} \
else if((I)==b010) {  HTEG32(w); a= hteg_float32(); h= round(w/a);}\
else if((I)==b001){ HTEG32(h); a= hteg_float32();  w= round(h*a);}\
HTEG16(image_no(p));RNG("Section number",image_no(p),3,max_section_no);  \
if (w==0 || h==0) {MESSAGE("Incomplete dimensions in image %d",image_no(p));\
  if (w!=0) h= w; else if (h!=0) w= h; else w= h= 100*ONE; }\
image_width(p)= w; image_height(p)= h;\
tail_append(p);}
/*:498*//*506:*/
#line 9827 "hint.w"

#define HTEG_LINK(I) \
{ pointer p;\
  p= get_node(link_node_size);  type(p)= whatsit_node;\
  if (I&b010) subtype(p)= start_link_node; else subtype(p)= end_link_node;\
  if (I&b100) color_ref(as_color(p))= HTEG8; else color_ref(as_color(p))= (I&b010)?1:0xFF;\
  if (I&b001) HTEG16(label_ref(as_label(p))); else label_ref(as_label(p))= HTEG8; \
  RNG("label",label_ref(as_label(p)),0,max_ref[label_kind]);\
  if (color_ref(as_color(p))!=0xFF)\
    RNG("label color",color_ref(as_color(p)),0,max_ref[color_kind]);\
  tail_append(p);}
/*:506*/
#line 14784 "hint.w"


/*24:*/
#line 943 "hint.w"

static pointer temp_ptr;

/*:24*//*25:*/
#line 975 "hint.w"

static memory_word mem0[mem_max-mem_min+1],*const mem= mem0-mem_min;
static pointer lo_mem_max;
static pointer hi_mem_min;

/*:25*//*26:*/
#line 988 "hint.w"

static int var_used,dyn_used;
#ifdef STAT
#define incr_dyn_used incr(dyn_used)
#define decr_dyn_used decr(dyn_used)
#else
#line 994 "hint.w"
#define incr_dyn_used
#define decr_dyn_used
#endif
#line 997 "hint.w"

/*:26*//*27:*/
#line 1012 "hint.w"

static pointer avail;

/*:27*//*30:*/
#line 1077 "hint.w"

static pointer rover;

/*:30*//*132:*/
#line 2943 "hint.w"

static scaled total_stretch0[filll-normal+1],
*const total_stretch= total_stretch0-normal,
total_shrink0[filll-normal+1],*const total_shrink= total_shrink0-normal;


/*:132*//*133:*/
#line 2954 "hint.w"

static pointer adjust_tail= null;


/*:133*//*156:*/
#line 3315 "hint.w"

static pointer just_box;
static int just_color;
static int just_label;

/*:156*//*163:*/
#line 3453 "hint.w"

static pointer passive;
static pointer printed_node;
static halfword pass_number;

/*:163*//*165:*/
#line 3496 "hint.w"

static scaled active_width0[6],*const active_width= active_width0-1;

static scaled cur_active_width0[6],
*const cur_active_width= cur_active_width0-1;
static scaled background0[6],*const background= background0-1;
static scaled break_width0[6],*const break_width= break_width0-1;

/*:165*//*167:*/
#line 3554 "hint.w"

static bool no_shrink_error_yet;

/*:167*//*170:*/
#line 3596 "hint.w"

static pointer cur_p;
static bool second_pass;
static bool final_pass;
static int threshold;

/*:170*//*175:*/
#line 3698 "hint.w"

static int minimal_demerits0[tight_fit-very_loose_fit+1],
*const minimal_demerits= minimal_demerits0-very_loose_fit;

static int minimum_demerits;

static pointer best_place0[tight_fit-very_loose_fit+1],
*const best_place= best_place0-very_loose_fit;

static halfword best_pl_line0[tight_fit-very_loose_fit+1],
*const best_pl_line= best_pl_line0-very_loose_fit;


/*:175*//*181:*/
#line 3819 "hint.w"

static scaled disc_width;

/*:181*//*189:*/
#line 3961 "hint.w"

static halfword easy_line;
static halfword last_special_line;

static scaled first_width;

static scaled second_width;
static scaled first_indent;
static scaled second_indent;

/*:189*//*214:*/
#line 4466 "hint.w"

static pointer best_bet;
static int fewest_demerits;
static halfword best_line;
static int actual_looseness;

static int line_diff;


/*:214*//*237:*/
#line 4887 "hint.w"

static scaled best_height_plus_depth;


/*:237*//*243:*/
#line 5018 "hint.w"

static pointer page_tail;
static int page_contents;
static scaled page_max_depth;
static pointer best_page_break;
static int least_page_cost;
static scaled best_size;

/*:243*//*245:*/
#line 5100 "hint.w"

static scaled page_so_far[8];
static int insert_penalties;


/*:245*//*299:*/
#line 6543 "hint.w"

static pointer*pointer_def[32]= {NULL};
/*:299*//*303:*/
#line 6598 "hint.w"

static int32_t*integer_def;
/*:303*//*307:*/
#line 6628 "hint.w"

static scaled*dimen_def;
/*:307*//*311:*/
#line 6658 "hint.w"

static Xdimen*xdimen_def;
/*:311*//*319:*/
#line 6726 "hint.w"

static BaselineSkip*baseline_def= NULL;
/*:319*//*325:*/
#line 6830 "hint.w"

typedef struct{
char*n;
uint16_t m,q;
scaled s;
pointer g;
pointer h;
pointer p[MAX_FONT_PARAMS+1];
scaled hpxs,vpxs;
FontFormat ff;
FT_Face ft_face;
/*653:*/
#line 13322 "hint.w"

Gcache**g0;
Gcache***g1;
Gcache****g2;
Gcache*****g3;

/*:653*/
#line 6841 "hint.w"

}FontDef;

static FontDef*font_def;
/*:325*//*331:*/
#line 6942 "hint.w"

static ParamDef**param_def;
/*:331*//*338:*/
#line 7097 "hint.w"

typedef struct{
uint8_t pg;
uint32_t f,t;
}RangeDef;
static RangeDef*range_def;
/*:338*//*342:*/
#line 7147 "hint.w"

typedef struct{
pointer p,t;
}Stream;
static Stream*streams;
/*:342*//*345:*/
#line 7164 "hint.w"

typedef struct{
Xdimen x;
int f;
int p,n,r;
pointer b,a;
Xdimen w;
pointer g;
pointer h;
}StreamDef;
/*:345*//*349:*/
#line 7237 "hint.w"

typedef struct{
char*n;
Dimen d;
pointer g;
uint8_t p;
uint32_t t;
Xdimen v,h;
StreamDef*s;
}PageDef;
static PageDef*page_def;
static PageDef*cur_page;
/*:349*//*357:*/
#line 7372 "hint.w"

static hint_Outline*hint_outlines= NULL;
static int outline_no= -1;
/*:357*//*365:*/
#line 7463 "hint.w"

static ColorSet*color_def= color_defaults;
static bool first_color= true;
/*:365*//*471:*/
#line 9352 "hint.w"

static ParamDef*line_break_params= NULL;
/*:471*//*508:*/
#line 9874 "hint.w"

static pointer*pointer_def[32];
static scaled*dimen_def;
static int32_t*integer_def;
/*:508*//*526:*/
#line 10228 "hint.w"

#define PIXEL_SIZE_300_DPI (scaled)((72.27/300)*ONE+0.5)
#define MAX_PIXEL_SIZE (PIXEL_SIZE_300_DPI*10)
#define MIN_PIXEL_SIZE (PIXEL_SIZE_300_DPI/10)

#if 0
static double xdpi= 600.0,ydpi= 600.0;
#endif
#line 10236 "hint.w"
 static scaled x_px_size= PIXEL_SIZE_300_DPI,y_px_size= PIXEL_SIZE_300_DPI;
/*:526*//*529:*/
#line 10348 "hint.w"

static scaled page_height;
static scaled top_so_far[8];
/*:529*//*545:*/
#line 10658 "hint.w"

static scaled hvsize,hhsize;
/*:545*//*546:*/
#line 10684 "hint.w"

static int page_v,page_h,offset_v,offset_h;
/*:546*//*550:*/
#line 10796 "hint.w"

static uint32_t map[0x10000];
/*:550*//*556:*/
#line 10866 "hint.w"

#define MAX_PAGE_POS (1<<3) 

static uint64_t page_loc[MAX_PAGE_POS];
static int cur_loc;
static int lo_loc,hi_loc;
/*:556*//*571:*/
#line 11193 "hint.w"

static bool forward_mode= false,backward_mode= false;
/*:571*//*584:*/
#line 11524 "hint.w"

static hint_Outline*hint_outlines;
/*:584*//*618:*/
#line 12288 "hint.w"

static Link*hlinks= NULL;
static int max_link= -1;
/*:618*//*641:*/
#line 12979 "hint.w"

static FT_Library ft_library= NULL;
static FT_Error ft_err;


/*:641*//*655:*/
#line 13378 "hint.w"

static Gcache g_undefined= {0};
/*:655*//*675:*/
#line 14475 "hint.w"

jmp_buf hint_error_exit;
char hint_error_string[MAX_HINT_ERROR];
/*:675*/
#line 14786 "hint.w"


/*300:*/
#line 6548 "hint.w"

static void hget_font_def(uint8_t a,uint8_t n);
static int32_t hget_integer_def(uint8_t a);
static scaled hget_dimen_def(uint8_t a);
static pointer hget_glue_def(uint8_t a);
static void hget_baseline_def(uint8_t a,uint8_t n);
static ParamDef*hget_param_list(uint8_t a);
static void hget_range_def(uint8_t a,uint8_t pg);
static void hget_page_def(uint8_t a,uint8_t n);
static void hget_outline_or_label_def(Info i,int n);
static void hget_unknown_def(void);
static void hget_font_metrics(void);
static void hget_color_def(uint8_t a,int n);
static pointer hget_definition(uint8_t a);
static int hget_label_ref(void);
static int hget_link_color(void);
static void hpack_page(void);
static void happend_insertion(pointer p);
/*:300*//*324:*/
#line 6813 "hint.w"

static pointer hprepend_to_vlist(pointer b);
/*:324*//*329:*/
#line 6918 "hint.w"

static pointer hget_glue_spec(void);
/*:329*//*337:*/
#line 7090 "hint.w"

static void hrestore_param_list(void);
/*:337*//*356:*/
#line 7360 "hint.w"

static void hfill_page_template(void);
/*:356*//*377:*/
#line 7688 "hint.w"

static void tag_mismatch(uint8_t a,uint8_t z,uint32_t a_pos,uint32_t z_pos);
/*:377*//*379:*/
#line 7742 "hint.w"

static void hget_content(void);
/*:379*//*383:*/
#line 7794 "hint.w"

static void hteg_content(void);
/*:383*//*408:*/
#line 8114 "hint.w"

static scaled hget_xdimen_node(void);
/*:408*//*419:*/
#line 8411 "hint.w"

static pointer hget_list_pointer(void);
static pointer hteg_list_pointer(void);
/*:419*//*461:*/
#line 9119 "hint.w"

static void hprune_unwanted_nodes(void);
/*:461*//*473:*/
#line 9364 "hint.w"

static void set_line_break_params(void);
/*:473*//*509:*/
#line 9883 "hint.w"

static bool flush_pages(uint32_t pos);
static pointer skip(uint8_t n);
static pointer*box_ptr(uint8_t n);
static int count(uint8_t n);
static scaled dimen(uint8_t n);
/*:509*//*512:*/
#line 9939 "hint.w"

static void hpage_init(void);
/*:512*//*514:*/
#line 9956 "hint.w"

static void hflush_contribution_list(void);
/*:514*//*552:*/
#line 10809 "hint.w"

static void clear_map(void);
/*:552*//*554:*/
#line 10834 "hint.w"

#define HINT_NO_LOC 0xFFFFFFFFFFFFFFFF
#define PAGE_LOC(POS0,OFF) (((uint64_t)((POS0)+(OFF))<<32) + (uint64_t)(OFF))
#define LOC_POS(P) ((P)>>32) 
#define LOC_OFF(P) ((P)&0xFFFFFFFF) 
#define LOC_POS0(P) (LOC_POS(P)-LOC_OFF(P)) 
/*:554*//*559:*/
#line 10920 "hint.w"

static uint64_t hlocation(pointer p);
/*:559*//*564:*/
#line 11035 "hint.w"

static void hloc_init(void);
static void store_map(pointer p,uint32_t pos,uint32_t offset);
static uint32_t hposition(pointer p);
static void hloc_set_next(pointer p);
/*:564*//*585:*/
#line 11535 "hint.w"

#define LABEL_UNDEF 0
#define LABEL_TOP 1
#define LABEL_BOT 2
#define LABEL_MID 3
/*:585*//*603:*/
#line 12012 "hint.w"

static void hmark_page(void);
/*:603*//*627:*/
#line 12558 "hint.w"

static void hload_font(uint8_t f);
/*:627*//*652:*/
#line 13296 "hint.w"

#ifdef DEBUG
static bool ft_exists(internal_font_number f,int c);
#endif
#line 13300 "hint.w"

static scaled ft_char_width(uint8_t f,int c);
static void ft_destroy(void);
static FT_Face ft_load_font_face(uint8_t f);
static FT_Face ft_get_font_face(uint8_t f);
static void ft_unload_font_face(uint8_t f);
static scaled ft_glyph_width(FT_Face ft_face,FT_UInt ft_gid,scaled s);
static void ft_glyph_height_depth(FT_Face ft_face,FT_UInt ft_gid,
scaled*h,scaled*d,scaled s);
/*:652*//*685:*/
#line 14750 "hint.w"

static void leak_in(pointer p,int s);
static void leak_out(pointer p,int s);
/*:685*/
#line 14788 "hint.w"


#ifdef HINTTYPE
/*9:*/
#line 539 "hint.w"

static int file_offset= 0;
static int depth_threshold;
static int breadth_max;
static int depth_level= 0;

static void print_ln(void)
{putc('\n',hlog);file_offset= 0;
}

static void print_char(uint8_t s)
{if(s=='\n')
{print_ln();return;
}
putc(s,hlog);file_offset++;
if(file_offset==max_print_line)print_ln();
}

static void print(char*s)
{while(*s!=0)print_char(*s++);
}

static void print_nl(char*s)
{if(file_offset> 0)print_ln();
print(s);
}

static void print_esc(char*s)
{print_char('\\');
print(s);
}

static void print_int(int n)
{file_offset+= fprintf(hlog,"%d",n);
}

static void print_depth_level(void)
{int i;
for(i= 0;i<depth_level;i++)
print_char('.');
}

/*:9*//*16:*/
#line 679 "hint.w"

static void print_scaled(scaled s)

{scaled delta;
if(s<0)
{print_char('-');negate(s);
}
print_int(s/unity);
print_char('.');
s= 10*(s%unity)+5;delta= 10;
do{if(delta> unity)s= s+0100000-50000;
print_char('0'+(s/unity));s= 10*(s%unity);delta= delta*10;
}while(!(s<=delta));
}

static void print_xdimen(pointer p)
{print_scaled(xdimen_width(p));
if(xdimen_hfactor(p)!=0)
{print_char('+');print_scaled(xdimen_hfactor(p));print("*hsize");}
if(xdimen_vfactor(p)!=0)
{print_char('+');print_scaled(xdimen_vfactor(p));print("*vsize");}
}

static void print_label(pointer p)
{print("goto *");print_int(label_ref(p));
}

/*:16*//*66:*/
#line 1711 "hint.w"

static int font_in_short_display;

/*:66*//*67:*/
#line 1717 "hint.w"

static void short_display(int p)
{int n;
while(p> mem_min)
{if(is_char_node(p))
{if(p<=mem_end)
{if(font(p)!=font_in_short_display)
{if((font(p)<font_base)||(font(p)> font_max))
print_char('*');

else print_esc(font_def[font(p)].n);
print_char(' ');font_in_short_display= font(p);
}
print_ASCII(qo(character(p)));
}
}
else/*68:*/
#line 1738 "hint.w"

switch(type(p)){
case hlist_node:case vlist_node:case ins_node:
case whatsit_node:case adjust_node:
case unset_node:print("[]");break;
case rule_node:print_char('|');break;
case glue_node:if(glue_ptr(p)!=zero_glue)print_char(' ');break;
case math_node:print_char('$');break;
case ligature_node:short_display(lig_ptr(p));break;
case disc_node:{short_display(pre_break(p));
short_display(post_break(p));
n= replace_count(p);
while(n> 0)
{if(link(p)!=null)p= link(p);
decr(n);
}
}break;
default:do_nothing;
}

/*:68*/
#line 1733 "hint.w"
;
p= link(p);
}
}

/*:67*//*69:*/
#line 1762 "hint.w"

static void print_font_and_char(int p)
{if(p> mem_end)print_esc("CLOBBERED.");
else{print_esc(font_def[font(p)].n);
print_char(' ');print_ASCII(character(p));
}
}

static void print_mark(int p)
{print_char('{');print_char('}');
}

static void print_rule_dimen(scaled d)
{if(is_running(d))print_char('*');else print_scaled(d);

}

/*:69*//*70:*/
#line 1782 "hint.w"

static void print_glue(scaled d,int order,char*s)

{print_scaled(d);
if((order<normal)||(order> filll))print("foul");
else if(order> normal)
{print("fil");
while(order> fil)
{print_char('l');decr(order);
}
}
else if(s!=0)print(s);
}

/*:70*//*71:*/
#line 1798 "hint.w"

static void print_spec(int p,char*s)

{if((p<mem_min)||(p>=lo_mem_max))print_char('*');

else{print_scaled(width(p));
if(s!=0)print(s);
if(stretch(p)!=0)
{print(" plus ");print_glue(stretch(p),stretch_order(p),s);
}
if(shrink(p)!=0)
{print(" minus ");print_glue(shrink(p),shrink_order(p),s);
}
}
}


/*:71*//*74:*/
#line 1839 "hint.w"

static void print_UTF8(int c);
static void show_node_list(int p)
{
int n;
double g;
if(depth_level> depth_threshold)
{if(p> null)print(" []");

return;
}
n= 0;
while(p> mem_min)
{print_ln();print_depth_level();
if(p> mem_end)
{print("Bad link, display aborted.");return;

}
incr(n);if(n> breadth_max)
{print("etc.");return;

}
/*75:*/
#line 1867 "hint.w"

if(is_char_node(p))print_font_and_char(p);
else switch(type(p)){
case hlist_node:case vlist_node:case unset_node:/*76:*/
#line 1884 "hint.w"

{if(type(p)==hlist_node)print_esc("h");
else if(type(p)==vlist_node)print_esc("v");
else print_esc("unset");
print("box(");print_scaled(height(p));print_char('+');
print_scaled(depth(p));print(")x");print_scaled(width(p));
if(type(p)==unset_node)
/*77:*/
#line 1900 "hint.w"

{if(span_count(p)!=min_quarterword)
{print(" (");print_int(qo(span_count(p))+1);
print(" columns)");
}
if(glue_stretch(p)!=0)
{print(", stretch ");print_glue(glue_stretch(p),glue_order(p),0);
}
if(glue_shrink(p)!=0)
{print(", shrink ");print_glue(glue_shrink(p),glue_sign(p),0);
}
}

/*:77*/
#line 1891 "hint.w"

else{/*78:*/
#line 1923 "hint.w"

g= unfix(glue_set(p));
if((g!=float_constant(0))&&(glue_sign(p)!=normal))
{print(", glue set ");
if(glue_sign(p)==shrinking)print("- ");
if(abs(mem[p+glue_offset].i)<04000000)print("?.?");
else if(abs(g)> float_constant(20000))
{if(g> float_constant(0))print_char('>');
else print("< -");
print_glue(20000*unity,glue_order(p),0);
}
else print_glue(round(unity*g),glue_order(p),0);

}

/*:78*/
#line 1892 "hint.w"
;
if(shift_amount(p)!=0)
{print(", shifted ");print_scaled(shift_amount(p));
}
}
node_list_display(list_ptr(p));
}

/*:76*/
#line 1870 "hint.w"
break;
case rule_node:/*79:*/
#line 1938 "hint.w"

{print_esc("rule(");print_rule_dimen(height(p));print_char('+');
print_rule_dimen(depth(p));print(")x");print_rule_dimen(width(p));
}

/*:79*/
#line 1871 "hint.w"
break;
case ins_node:/*80:*/
#line 1943 "hint.w"

{print_esc("insert");print_int(qo(subtype(p)));
print(", natural size ");print_scaled(height(p));
print("; split(");print_spec(split_top_ptr(p),0);
print_char(',');print_scaled(depth(p));
print("); float cost ");print_int(float_cost(p));
node_list_display(ins_ptr(p));
}

/*:80*/
#line 1872 "hint.w"
break;
case whatsit_node:/*288:*/
#line 6015 "hint.w"

switch(subtype(p)){
case special_node:{print_esc("special");
print_mark(write_tokens(p));
}break;
case language_node:{print_esc("setlanguage");
print_int(what_lang(p));print(" (hyphenmin ");
print_int(what_lhm(p));print_char(',');
print_int(what_rhm(p));print_char(')');
}break;
case param_node:print_esc("parameter ");
print_int(param_type(p));print_char(',');print_int(param_no(p));
print_char(':');print_int(param_value(p).i);
break;
case par_node:print_esc("paragraph(");
print_xdimen(par_extent(p));
print(", ");
print_int(par_penalty(p));
print_char(')');
node_list_display(par_params(p));
node_list_display(par_list(p));
break;
case disp_node:print_esc("display ");
node_list_display(display_eqno(p));
if(display_left(p))print("left ");else print("right ");
node_list_display(display_formula(p));
node_list_display(display_params(p));
break;
case hset_node:case vset_node:
print_char('\\');
print_char(subtype(p)==hset_node?'h':'v');
print("set(");
print_scaled(height(p));print_char('+');
print_scaled(depth(p));print(")x");print_scaled(width(p));
if(shift_amount(p)!=0)
{print(", shifted ");print_scaled(shift_amount(p));
}
if(set_stretch(p)!=0)
{print(", stretch ");print_glue(set_stretch(p),set_stretch_order(p),"pt");
}
if(set_shrink(p)!=0)
{print(", shrink ");print_glue(set_shrink(p),set_shrink_order(p),"pt");
}
print(", extent ");print_xdimen(set_extent(p));
node_list_display(list_ptr(p));
break;
case hpack_node:case vpack_node:
print_char('\\');
print_char(subtype(p)==hpack_node?'h':'v');
print("pack(");
print(pack_m(p)==exactly?"exactly ":"additional ");
print_xdimen(pack_extent(p));
if(subtype(p)==vpack_node&&pack_limit(p)!=max_dimen){print(", limit ");print_scaled(pack_limit(p));}
print_char(')');
node_list_display(list_ptr(p));
break;
case image_node:
print_esc("HINTimage(");
print("width ");print_scaled(image_height(p));
print(" height ");print_scaled(image_width(p));
print("), section ");print_int(image_no(p));
if(dir[image_no(p)].file_name!=NULL){print(", ");print(dir[image_no(p)].file_name);}
break;
case color_node:
print_esc("HINTcolor ");print_int(color_ref(p));
break;
case no_color_node:
print_esc("HINTendcolor ignored");
break;
case end_color_node:
print_esc("HINTendcolor ");
break;
case align_node:
print_esc("align(");
print(align_m(p)==exactly?"exactly ":"additional ");
print_xdimen(align_extent(p));print_char(')');
node_list_display(align_preamble(p));
print_char(':');
node_list_display(align_list(p));
break;
case ignore_node:
print_esc("ignore ");print_int(ignore_info(p));print_char(':');
node_list_display(ignore_list(p));
break;
case start_link_node:
print_esc("HINTstartlink ");
print_label(as_label(p));
if(color_ref(as_color(p))!=1){print("color ");print_int(color_ref(as_color(p)));}
break;
case end_link_node:
print_esc("HINTendlink ");
if(color_ref(as_color(p))!=0xFF){print("color ");print_int(color_ref(as_color(p)));}
break;
case label_node:
print_esc("HINTdest ");
print_label(p);
break;
case outline_node:
print_esc("HINToutline");
print_label(p);
print(" depth ");print_int(outline_depth(p));
if(outline_ptr(p)==null)print("{}");else
{print_ln();print_depth_level();node_list_display(outline_ptr(p));}
break;
case stream_node:
print_esc("HINTstream");print_int(stream_insertion(p));
print_char('(');print_int(stream_number(p));print_char(')');
break;
case utf_char_node:
print_esc(font_def[utf_font(p)].n);print_char(' ');print_UTF8(utf_char(p));
break;
default:print("whatsit?");
}

/*:288*/
#line 1873 "hint.w"
break;
case glue_node:/*81:*/
#line 1952 "hint.w"

if(subtype(p)>=a_leaders)/*82:*/
#line 1956 "hint.w"

{print_esc("");
if(subtype(p)==c_leaders)print_char('c');
else if(subtype(p)==x_leaders)print_char('x');
print("leaders ");print_spec(glue_ptr(p),0);
node_list_display(leader_ptr(p));
}

/*:82*/
#line 1953 "hint.w"

else{print_esc("glue ");print_spec(glue_ptr(p),0);}

/*:81*/
#line 1874 "hint.w"
break;
case kern_node:/*83:*/
#line 1966 "hint.w"

if(subtype(p)!=mu_glue)
{print_esc("kern");
print_char(' ');
print_scaled(width(p));
if(subtype(p)==acc_kern)print(" (for accent)");

}
else{print_esc("mkern");print_scaled(width(p));print("mu");
}

/*:83*/
#line 1875 "hint.w"
break;
case math_node:/*84:*/
#line 1977 "hint.w"

{print_esc("math");
if(subtype(p)==before)print("on");
else print("off");
if(width(p)!=0)
{print(", surrounded ");print_scaled(width(p));
}
}

/*:84*/
#line 1876 "hint.w"
break;
case ligature_node:/*85:*/
#line 1986 "hint.w"

{print_font_and_char(lig_char(p));print(" (ligature ");
if(subtype(p)> 1)print_char('|');
font_in_short_display= font(lig_char(p));short_display(lig_ptr(p));
if(odd(subtype(p)))print_char('|');
print_char(')');
}

/*:85*/
#line 1877 "hint.w"
break;
case penalty_node:/*86:*/
#line 1994 "hint.w"

{print_esc("penalty ");print_int(penalty(p));
}

/*:86*/
#line 1878 "hint.w"
break;
case disc_node:/*87:*/
#line 2001 "hint.w"

{print_esc("discretionary");
if(replace_count(p)> 0)
{print(" replacing ");print_int(replace_count(p));
}
node_list_display(pre_break(p));
node_list_display(post_break(p));
}


/*:87*/
#line 1879 "hint.w"
break;
case adjust_node:/*88:*/
#line 2011 "hint.w"

{print_esc("vadjust");node_list_display(adjust_ptr(p));
}

/*:88*/
#line 1880 "hint.w"
break;
default:print("Unknown node type!");
}

/*:75*/
#line 1861 "hint.w"
;
p= link(p);
}

}

/*:74*//*89:*/
#line 2018 "hint.w"

static void show_box(pointer p)
{depth_threshold= 200;breadth_max= 200;
show_node_list(p);
print_ln();
}

/*:89*//*246:*/
#line 5108 "hint.w"

static void print_totals(void)
{print_scaled(page_total);
print_plus(2,"");
print_plus(3,"fil");
print_plus(4,"fill");
print_plus(5,"filll");
if(page_shrink!=0)
{print(" minus ");print_scaled(page_shrink);
}
}

/*:246*//*396:*/
#line 7982 "hint.w"

static void print_UTF8(int c)
{if(c<0x80)
{putc(c,hlog);}
else if(c<0x800)
{putc(0xC0|(c>>6),hlog);putc(0x80|(c&0x3F),hlog);}
else if(c<0x10000)
{putc(0xE0|(c>>12),hlog);putc(0x80|((c>>6)&0x3F),hlog);putc(0x80|(c&0x3F),hlog);}
else if(c<0x200000)
{putc(0xF0|(c>>18),hlog);putc(0x80|((c>>12)&0x3F),hlog);
putc(0x80|((c>>6)&0x3F),hlog);putc(0x80|(c&0x3F),hlog);}
file_offset++;
if(file_offset==max_print_line)print_ln();
}
/*:396*/
#line 14791 "hint.w"

#endif
#line 14793 "hint.w"

/*11:*/
#line 605 "hint.w"

static void overflow(char*s,int n)
{QUIT("Capacity exceeded, sorry [%s=%d=0x%X]\n",s,n,n);
}

/*:11*//*12:*/
#line 618 "hint.w"

static void confusion(char*s)

{QUIT("This can't happen(%s)",s);}


/*:12*/
#line 14794 "hint.w"


/*14:*/
#line 648 "hint.w"

static int half(int x)
{if(odd(x))return(x+1)/2;
else return x/2;
}

/*:14*//*17:*/
#line 731 "hint.w"

static bool arith_error;
static scaled rem;

/*:17*//*18:*/
#line 737 "hint.w"

static scaled x_over_n(scaled x,int n)
{bool negative;
scaled x_over_n;
negative= false;
if(n==0)
{arith_error= true;x_over_n= 0;rem= x;
}
else{if(n<0)
{negate(x);negate(n);negative= true;
}
if(x>=0)
{x_over_n= x/n;rem= x%n;
}
else{x_over_n= -((-x)/n);rem= -((-x)%n);
}
}
if(negative)negate(rem);
return x_over_n;}


/*:18*//*19:*/
#line 778 "hint.w"

static halfword badness(scaled t,scaled s)
{int r;

if(t==0)return 0;
else if(s<=0)return inf_bad;
else{if(t<=7230584)r= (t*297)/s;
else if(s>=1663497)r= t/(s/297);
else r= t;
if(r> 1290)return inf_bad;
else return(r*r*r+0400000)/01000000;
}
}

/*:19*//*28:*/
#line 1024 "hint.w"

static pointer get_avail(void)
{pointer p;
p= avail;
if(p!=null)avail= link(avail);
else{decr(hi_mem_min);p= hi_mem_min;
if(hi_mem_min<=lo_mem_max)
{
overflow("main memory size",mem_max+1-mem_min);


}
}
link(p)= null;
#ifdef STAT
incr(dyn_used);
#endif
#line 1041 "hint.w"

return p;
}

/*:28*//*31:*/
#line 1088 "hint.w"

static pointer get_node(int s)
{
pointer p;
pointer q;
int r;
int t;
restart:p= rover;
do{/*33:*/
#line 1140 "hint.w"

q= p+node_size(p);

while(is_empty(q))
{t= rlink(q);
if(q==rover)rover= t;
llink(t)= llink(q);rlink(llink(q))= t;
q= q+node_size(q);
}
r= q-s;
if(r> p+1)/*34:*/
#line 1155 "hint.w"

{node_size(p)= r-p;

rover= p;
goto found;
}

/*:34*/
#line 1150 "hint.w"
;
if(r==p)if(rlink(p)!=p)
/*35:*/
#line 1164 "hint.w"

{rover= rlink(p);t= llink(p);
llink(rover)= t;rlink(t)= rover;
goto found;
}

/*:35*/
#line 1152 "hint.w"
;
node_size(p)= q-p

/*:33*/
#line 1097 "hint.w"
;

p= rlink(p);
}while(!(p==rover));
if(s==010000000000)
{return max_halfword;
}
if(lo_mem_max+2<hi_mem_min)if(lo_mem_max+2<=mem_bot+max_halfword)
/*32:*/
#line 1125 "hint.w"

{if(hi_mem_min-lo_mem_max>=1998)t= lo_mem_max+1000;
else t= lo_mem_max+1+(hi_mem_min-lo_mem_max)/2;

p= llink(rover);q= lo_mem_max;rlink(p)= q;llink(rover)= q;
if(t> mem_bot+max_halfword)t= mem_bot+max_halfword;
rlink(q)= rover;llink(q)= p;link(q)= empty_flag;node_size(q)= t-lo_mem_max;
lo_mem_max= t;link(lo_mem_max)= null;info(lo_mem_max)= null;
rover= q;goto restart;
}

/*:32*/
#line 1105 "hint.w"
;
overflow("main memory size",mem_max+1-mem_min);


found:link(r)= null;
#ifdef STAT
var_used= var_used+s;
#endif
#line 1113 "hint.w"

leak_in(r,s);
return r;
}

/*:31*//*36:*/
#line 1175 "hint.w"

static void free_node(pointer p,halfword s)

{pointer q;
leak_out(p,s);
store_map(p,0,0);
node_size(p)= s;link(p)= empty_flag;
q= llink(rover);llink(p)= q;rlink(p)= rover;
llink(rover)= p;rlink(q)= p;
#ifdef STAT
var_used= var_used-s;
#endif
#line 1187 "hint.w"

}

/*:36*//*40:*/
#line 1290 "hint.w"

static pointer new_null_box(void)
{pointer p;
p= get_node(box_node_size);type(p)= hlist_node;
subtype(p)= min_quarterword;
width(p)= 0;depth(p)= 0;height(p)= 0;shift_amount(p)= 0;list_ptr(p)= null;
glue_sign(p)= normal;glue_order(p)= normal;set_glue_ratio_zero(glue_set(p));
return p;
}

/*:40*//*43:*/
#line 1321 "hint.w"

static pointer new_rule(void)
{pointer p;
p= get_node(rule_node_size);type(p)= rule_node;
subtype(p)= 0;
width(p)= null_flag;depth(p)= null_flag;height(p)= null_flag;
return p;
}

/*:43*//*48:*/
#line 1386 "hint.w"

static pointer new_ligature(quarterword f,quarterword c,pointer q)
{pointer p;
p= get_node(small_node_size);type(p)= ligature_node;
font(lig_char(p))= f;character(lig_char(p))= c;lig_ptr(p)= q;
subtype(p)= 0;return p;
}


/*:48*//*49:*/
#line 1420 "hint.w"

static pointer new_disc(void)
{pointer p;
p= get_node(small_node_size);type(p)= disc_node;
subtype(p)= 0;pre_break(p)= null;post_break(p)= null;
return p;
}

/*:49*//*51:*/
#line 1455 "hint.w"

static pointer new_math(scaled w,small_number s)
{pointer p;
p= get_node(small_node_size);type(p)= math_node;
subtype(p)= s;width(p)= w;return p;
}

/*:51*//*55:*/
#line 1537 "hint.w"

static pointer new_spec(pointer p)
{pointer q;
q= get_node(glue_spec_size);
mem[q]= mem[p];glue_ref_count(q)= null;
width(q)= width(p);stretch(q)= stretch(p);shrink(q)= shrink(p);
return q;
}

/*:55*//*56:*/
#line 1549 "hint.w"

static pointer new_glue(pointer q)
{pointer p;
p= get_node(small_node_size);type(p)= glue_node;subtype(p)= normal;
leader_ptr(p)= null;glue_ptr(p)= q;incr(glue_ref_count(q));
return p;
}

/*:56*//*58:*/
#line 1574 "hint.w"

static pointer new_kern(scaled w)
{pointer p;
p= get_node(small_node_size);type(p)= kern_node;
subtype(p)= normal;
width(p)= w;
return p;
}

/*:58*//*60:*/
#line 1598 "hint.w"

static pointer new_penalty(int m)
{pointer p;
p= get_node(small_node_size);type(p)= penalty_node;
subtype(p)= 0;
penalty(p)= m;return p;
}

/*:60*//*64:*/
#line 1663 "hint.w"

static void mem_init(void)
{int k;
/*65:*/
#line 1669 "hint.w"

for(k= mem_bot+1;k<=lo_mem_stat_max;k++)mem[k].sc= 0;


k= mem_bot;while(k<=lo_mem_stat_max)

{glue_ref_count(k)= null+1;
stretch_order(k)= normal;shrink_order(k)= normal;
k= k+glue_spec_size;
}
rover= lo_mem_stat_max+1;
link(rover)= empty_flag;
node_size(rover)= 1000;
llink(rover)= rover;rlink(rover)= rover;
lo_mem_max= rover+1000;link(lo_mem_max)= null;info(lo_mem_max)= null;
for(k= hi_mem_stat_min;k<=mem_top;k++)
mem[k]= mem[lo_mem_max];
/*162:*/
#line 3423 "hint.w"

type(last_active)= hyphenated;line_number(last_active)= max_halfword;
subtype(last_active)= 0;

/*:162*//*244:*/
#line 5071 "hint.w"

subtype(page_ins_head)= qi(255);
type(page_ins_head)= split_up;link(page_ins_head)= page_ins_head;

/*:244*//*248:*/
#line 5165 "hint.w"

type(page_head)= glue_node;subtype(page_head)= normal;

/*:248*/
#line 1686 "hint.w"
;
avail= null;
hi_mem_min= hi_mem_stat_min;
var_used= lo_mem_stat_max+1-mem_bot;dyn_used= hi_mem_stat_usage;



/*:65*/
#line 1666 "hint.w"

}

/*:64*//*92:*/
#line 2047 "hint.w"

static void delete_glue_ref(pointer p)
fast_delete_glue_ref(p)
static void delete_xdimen_ref(pointer p)
{if(p==null)return;
if(xdimen_ref_count(p)==null)free_node(p,xdimen_node_size);
else decr(xdimen_ref_count(p));
}

/*:92*//*93:*/
#line 2061 "hint.w"

static void flush_node_list(pointer p)
{
pointer q;
while(p!=null)

{q= link(p);
if(is_char_node(p))free_avail(p)
else{switch(type(p)){
case hlist_node:case vlist_node:
case unset_node:{flush_node_list(list_ptr(p));
free_node(p,box_node_size);goto done;
}
case rule_node:{free_node(p,rule_node_size);goto done;
}
case ins_node:{flush_node_list(ins_ptr(p));
delete_glue_ref(split_top_ptr(p));
free_node(p,ins_node_size);goto done;
}
case whatsit_node:/*290:*/
#line 6255 "hint.w"

{switch(subtype(p)){
case close_node:case language_node:free_node(p,small_node_size);break;
case param_node:
if(param_type(p)==glue_type)fast_delete_glue_ref(param_value(p).i);
free_node(p,param_node_size);break;
case par_node:
delete_xdimen_ref(par_extent(p));
flush_node_list(par_params(p));
flush_node_list(par_list(p));
free_node(p,par_node_size);break;
case disp_node:
flush_node_list(display_eqno(p));
flush_node_list(display_formula(p));
flush_node_list(display_params(p));
free_node(p,disp_node_size);break;
case baseline_node:
free_node(p,baseline_node_size);break;
case hpack_node:case vpack_node:
delete_xdimen_ref(pack_extent(p));
flush_node_list(list_ptr(p));
free_node(p,pack_node_size);break;
case hset_node:case vset_node:
delete_xdimen_ref(set_extent(p));
flush_node_list(list_ptr(p));
free_node(p,set_node_size);break;
case image_node:
flush_node_list(image_alt(p));
free_node(p,image_node_size);break;
case color_node:
case no_color_node:
case end_color_node:
free_node(p,color_node_size);break;
case align_node:
delete_xdimen_ref(align_extent(p));
flush_node_list(align_preamble(p));
flush_node_list(align_list(p));
free_node(p,align_node_size);break;
case setpage_node:
delete_glue_ref(setpage_topskip(p));
delete_xdimen_ref(setpage_height(p));
delete_xdimen_ref(setpage_width(p));
flush_node_list(setpage_list(p));
flush_node_list(setpage_streams(p));
free_node(p,setpage_node_size);break;
case setstream_node:
delete_xdimen_ref(setstream_max(p));
delete_xdimen_ref(setstream_width(p));
delete_glue_ref(setstream_topskip(p));
delete_glue_ref(setstream_height(p));
flush_node_list(setstream_before(p));
flush_node_list(setstream_after(p));
free_node(p,setstream_node_size);break;
case ignore_node:
flush_node_list(ignore_list(p));
free_node(p,ignore_node_size);break;
case start_link_node:
free_node(p,link_node_size);break;
case end_link_node:
free_node(p,link_node_size);break;
case label_node:
free_node(p,label_node_size);break;
case outline_node:
flush_node_list(outline_ptr(p));
free_node(p,outline_node_size);break;
case stream_node:
free_node(p,stream_node_size);break;
case xdimen_node:
free_node(p,xdimen_node_size);break;
case utf_char_node:
free_node(p,utf_char_node_size);break;
default:confusion("ext3");

}
goto done;
}

/*:290*/
#line 2080 "hint.w"

case glue_node:{fast_delete_glue_ref(glue_ptr(p));
if(leader_ptr(p)!=null)flush_node_list(leader_ptr(p));
}break;
case kern_node:case math_node:case penalty_node:do_nothing;break;
case ligature_node:flush_node_list(lig_ptr(p));break;
case disc_node:{flush_node_list(pre_break(p));
flush_node_list(post_break(p));
}break;
case adjust_node:flush_node_list(adjust_ptr(p));break;
default:QUIT("Confusion while flushing node list");

}
free_node(p,small_node_size);
done:;}
p= q;
}
}

/*:93*//*95:*/
#line 2124 "hint.w"

static pointer copy_node_list(pointer p)

{pointer h;
pointer q;
pointer r;
int words;
h= get_avail();q= h;
while(p!=null)
{/*96:*/
#line 2140 "hint.w"

words= 1;
if(is_char_node(p))r= get_avail();
else/*97:*/
#line 2149 "hint.w"

switch(type(p)){
case hlist_node:case vlist_node:case unset_node:{r= get_node(box_node_size);
mem[r+6]= mem[p+6];mem[r+5]= mem[p+5];
list_ptr(r)= copy_node_list(list_ptr(p));
words= 5;
}break;
case rule_node:{r= get_node(rule_node_size);words= rule_node_size;
}break;
case ins_node:{r= get_node(ins_node_size);mem[r+4]= mem[p+4];
add_glue_ref(split_top_ptr(p));
ins_ptr(r)= copy_node_list(ins_ptr(p));
words= ins_node_size-1;
}break;
case whatsit_node:/*289:*/
#line 6129 "hint.w"

switch(subtype(p)){
case open_node:{r= get_node(open_node_size);words= open_node_size;
}break;
case write_node:case special_node:{r= get_node(write_node_size);
add_token_ref(write_tokens(p));words= write_node_size;
}break;
case close_node:case language_node:{r= get_node(small_node_size);
words= small_node_size;
}break;
case param_node:
{r= get_node(param_node_size);
if(param_type(p)==glue_type)add_glue_ref(param_value(p).i);
words= param_node_size;
}break;
case par_node:
{r= get_node(par_node_size);
add_xdimen_ref(par_extent(p));
par_params(r)= copy_node_list(par_params(p));
par_list(r)= copy_node_list(par_list(p));
words= par_node_size-1;
}break;
case disp_node:
{r= get_node(disp_node_size);
display_left(r)= display_left(p);
display_no_bs(r)= display_no_bs(p);
display_eqno(r)= copy_node_list(display_eqno(p));
display_formula(r)= copy_node_list(display_formula(p));
display_params(r)= copy_node_list(display_params(p));
words= disp_node_size-2;
}break;
case baseline_node:
{r= get_node(baseline_node_size);
words= baseline_node_size;
}break;
case hpack_node:case vpack_node:
{r= get_node(pack_node_size);
mem[r+7]= mem[p+7];mem[r+6]= mem[p+6];mem[r+5]= mem[p+5];
list_ptr(r)= copy_node_list(list_ptr(p));
add_xdimen_ref(pack_extent(p));
words= 5;
}break;
case hset_node:case vset_node:
{r= get_node(set_node_size);
mem[r+8]= mem[p+8];mem[r+7]= mem[p+7];mem[r+6]= mem[p+6];mem[r+5]= mem[p+5];
list_ptr(r)= copy_node_list(list_ptr(p));
add_xdimen_ref(set_extent(p));
words= 5;
}break;
case image_node:
r= get_node(image_node_size);
image_alt(r)= copy_node_list(image_alt(p));
words= image_node_size-1;
break;
case color_node:
case no_color_node:
case end_color_node:
r= get_node(color_node_size);
words= color_node_size;
break;
case align_node:
{r= get_node(align_node_size);
align_preamble(r)= copy_node_list(align_preamble(p));
align_list(r)= copy_node_list(align_list(p));
add_xdimen_ref(align_extent(p));
words= align_node_size-1;
}break;
case setpage_node:
{r= get_node(setpage_node_size);
add_glue_ref(setpage_topskip(p));
add_xdimen_ref(setpage_height(p));
add_xdimen_ref(setpage_width(p));
setpage_list(r)= copy_node_list(setpage_list(p));
setpage_streams(r)= copy_node_list(setpage_streams(p));
words= setpage_node_size-1;
}break;
case setstream_node:
{r= get_node(setstream_node_size);
add_xdimen_ref(setstream_max(p));
add_xdimen_ref(setstream_width(p));
add_glue_ref(setstream_topskip(p));
add_glue_ref(setstream_height(p));
setstream_before(r)= copy_node_list(setstream_before(p));
setstream_after(r)= copy_node_list(setstream_after(p));
words= setstream_node_size-1;
}break;
case ignore_node:
r= get_node(ignore_node_size);
ignore_info(r)= ignore_info(p);
ignore_list(r)= copy_node_list(ignore_list(p));
words= ignore_node_size-1;
break;
case start_link_node:
r= get_node(link_node_size);
words= link_node_size;
break;
case end_link_node:
r= get_node(link_node_size);
words= link_node_size;
break;
case label_node:
r= get_node(label_node_size);
words= label_node_size;
break;
case outline_node:
r= get_node(outline_node_size);
outline_ptr(r)= copy_node_list(outline_ptr(p));
outline_depth(r)= outline_depth(p);
words= outline_node_size-1;
break;
case stream_node:
r= get_node(stream_node_size);
words= stream_node_size;
break;
case xdimen_node:
r= get_node(xdimen_node_size);
words= xdimen_node_size;
break;
case utf_char_node:
r= get_node(utf_char_node_size);
words= utf_char_node_size;
break;
default:confusion("ext2");

}

/*:289*/
#line 2164 "hint.w"
break;
case glue_node:{r= get_node(small_node_size);add_glue_ref(glue_ptr(p));
glue_ptr(r)= glue_ptr(p);leader_ptr(r)= copy_node_list(leader_ptr(p));
}break;
case kern_node:case math_node:case penalty_node:{r= get_node(small_node_size);
words= small_node_size;
}break;
case ligature_node:{r= get_node(small_node_size);
mem[lig_char(r)]= mem[lig_char(p)];
lig_ptr(r)= copy_node_list(lig_ptr(p));
}break;
case disc_node:{r= get_node(small_node_size);
pre_break(r)= copy_node_list(pre_break(p));
post_break(r)= copy_node_list(post_break(p));
}break;
case adjust_node:{r= get_node(small_node_size);
adjust_ptr(r)= copy_node_list(adjust_ptr(p));
}break;
default:confusion("copying");

}


/*:97*/
#line 2144 "hint.w"
;
while(words> 0)
{decr(words);mem[r+words]= mem[p+words];
}

/*:96*/
#line 2133 "hint.w"
;
link(q)= r;q= r;p= link(p);
}
link(q)= null;q= link(h);free_avail(h);
return q;
}

/*:95*//*102:*/
#line 2297 "hint.w"


/*100:*/
#line 2278 "hint.w"

static list_state_record nest[nest_size+1];
static int nest_ptr;
static int max_nest_stack;
static list_state_record cur_list;

/*:100*/
#line 2299 "hint.w"


static void list_init(void)
{
nest_ptr= 0;max_nest_stack= 0;
memset(&cur_list,0,sizeof(cur_list));
head= contrib_head;tail= contrib_head;
prev_height= prev_depth= ignore_depth;
}

/*:102*//*103:*/
#line 2314 "hint.w"

static void push_nest(void)
{if(nest_ptr> max_nest_stack)
{max_nest_stack= nest_ptr;
if(nest_ptr==nest_size)overflow("semantic nest size",nest_size);

}
nest[nest_ptr]= cur_list;
incr(nest_ptr);head= get_avail();tail= head;prev_graf= 0;
cur_list.bs_pos= NULL;cur_bs= baseline_skip;cur_ls= line_skip;cur_lsl= line_skip_limit;
}

/*:103*//*104:*/
#line 2331 "hint.w"

static void pop_nest(void)
{free_avail(head);decr(nest_ptr);cur_list= nest[nest_ptr];
}

/*:104*//*113:*/
#line 2576 "hint.w"

static memory_word font_info[font_mem_size+1];

static font_index fmem_ptr= 0;

static void hclear_font_info(void)
{fmem_ptr= 0;
}
static internal_font_number font_ptr;
static scaled font_size0[font_max-font_base+1],
*const font_size= font_size0-font_base;
static eight_bits font_bc0[font_max-font_base+1],
*const font_bc= font_bc0-font_base;

static eight_bits font_ec0[font_max-font_base+1],
*const font_ec= font_ec0-font_base;

static pointer font_glue0[font_max-font_base+1],
*const font_glue= font_glue0-font_base;

static int hyphen_char0[font_max-font_base+1],
*const hyphen_char= hyphen_char0-font_base;


/*:113*//*114:*/
#line 2609 "hint.w"

static int char_base0[font_max-font_base+1],
*const char_base= char_base0-font_base;

static int width_base0[font_max-font_base+1],
*const width_base= width_base0-font_base;

static int height_base0[font_max-font_base+1],
*const height_base= height_base0-font_base;

static int depth_base0[font_max-font_base+1],
*const depth_base= depth_base0-font_base;

static int param_base0[font_max-font_base+1],
*const param_base= param_base0-font_base;



/*:114*//*117:*/
#line 2689 "hint.w"

static void read_font_info(int f,char*nom,scaled s)
{
int k;
halfword lf,lh,bc,ec,nw,nh,nd,ni,nl,nk,ne,np;

eight_bits a,b,c,d;
four_quarters qw;scaled sw;
scaled z;
int alpha;int beta;

/*118:*/
#line 2707 "hint.w"

/*120:*/
#line 2739 "hint.w"

{read_sixteen(lf);
fget;read_sixteen(lh);
fget;read_sixteen(bc);
fget;read_sixteen(ec);
if((bc> ec+1)||(ec> 255))abort;
if(bc> 255)
{bc= 1;ec= 0;
}
fget;read_sixteen(nw);
fget;read_sixteen(nh);
fget;read_sixteen(nd);
fget;read_sixteen(ni);
fget;read_sixteen(nl);
fget;read_sixteen(nk);
fget;read_sixteen(ne);
fget;read_sixteen(np);
if(lf!=6+lh+(ec-bc+1)+nw+nh+nd+ni+nl+nk+ne+np)abort;
if((nw==0)||(nh==0)||(nd==0)||(ni==0))abort;
}

/*:120*/
#line 2708 "hint.w"
;
/*121:*/
#line 2766 "hint.w"

lf= lf-6-lh;
if(np<7)lf= lf+7-np;
if((font_ptr==font_max)||(fmem_ptr+lf> font_mem_size))
QUIT("Not enough room left for font %s\n",nom);
char_base[f]= fmem_ptr-bc;
width_base[f]= char_base[f]+ec+1;
height_base[f]= width_base[f]+nw;
depth_base[f]= height_base[f]+nh;
param_base[f]= depth_base[f]+nd

/*:121*/
#line 2709 "hint.w"
;
/*122:*/
#line 2779 "hint.w"

{if(lh<2)abort;
fskip_four;
fget;read_sixteen(z);
fget;z= z*0400+fbyte;fget;z= (z*020)+(fbyte/020);

while(lh> 2)
{fget;fget;fget;fget;decr(lh);
}
z= s;
font_size[f]= z;
}

/*:122*/
#line 2710 "hint.w"
;
/*123:*/
#line 2792 "hint.w"

for(k= fmem_ptr;k<=width_base[f]-1;k++)
{store_four_quarters(font_info[k].qqqq);
if((a>=nw)||(b/020>=nh)||(b%020>=nd))
abort;
}

/*:123*/
#line 2711 "hint.w"
;
/*124:*/
#line 2823 "hint.w"

{/*125:*/
#line 2833 "hint.w"

{alpha= 16;
while(z>=040000000)
{z= z/2;alpha= alpha+alpha;
}
beta= 256/alpha;alpha= alpha*z;
}

/*:125*/
#line 2824 "hint.w"
;
for(k= width_base[f];k<=depth_base[f]+nd-1;k++)
store_scaled(font_info[k].sc);
if(font_info[width_base[f]].sc!=0)abort;
if(font_info[height_base[f]].sc!=0)abort;
if(font_info[depth_base[f]].sc!=0)abort;
}
fskip(4*ni)

/*:124*/
#line 2712 "hint.w"
;
/*126:*/
#line 2841 "hint.w"

fskip(4*(nl+nk));

/*:126*/
#line 2713 "hint.w"
;
/*127:*/
#line 2844 "hint.w"

fskip(4*ne);

/*:127*/
#line 2714 "hint.w"
;
/*128:*/
#line 2850 "hint.w"

{for(k= 1;k<=np;k++)
if(k==1)
{fget;sw= fbyte;if(sw> 127)sw= sw-256;
fget;sw= sw*0400+fbyte;fget;sw= sw*0400+fbyte;
fget;font_info[param_base[f]].sc= 
(sw*020)+(fbyte/020);
}
else store_scaled(font_info[param_base[f]+k-1].sc);
if(hpos>=hend)abort;
for(k= np+1;k<=7;k++)font_info[param_base[f]+k-1].sc= 0;
}

/*:128*/
#line 2715 "hint.w"
;
/*129:*/
#line 2870 "hint.w"

hyphen_char[f]= -1;
font_bc[f]= bc;font_ec[f]= ec;font_glue[f]= null;
adjust(char_base);adjust(width_base);
decr(param_base[f]);
fmem_ptr= fmem_ptr+lf;goto done

/*:129*/
#line 2716 "hint.w"


/*:118*/
#line 2702 "hint.w"
;
bad_tfm:QUIT("Bad tfm file: %s\n",nom);
done:;
}

/*:117*//*130:*/
#line 2883 "hint.w"

static pointer new_character(internal_font_number f,eight_bits c)
{pointer p;
if(font_def[f].ff==no_format)hload_font(f);
#ifdef DEBUG

if(font_bc[f]> c||font_ec[f]<c||
(width_base[f]!=0&&!char_exists(char_info(f,qi(c))))||
(width_base[f]==0&&!ft_exists(f,c)))
DBG(DBGFONT,"Warning: Character 0x%0X in font %d does not exist\n",c,f);
#endif
#line 2894 "hint.w"
 p= get_avail();font(p)= f;character(p)= qi(c);
return p;
}

/*:130*//*134:*/
#line 2960 "hint.w"

static pointer hpack(pointer p,scaled w,small_number m)
{
pointer r;
pointer q;
scaled h,d,x;
scaled s;
pointer g;
glue_ord o;
internal_font_number f;
four_quarters i;
eight_bits hd;
r= get_node(box_node_size);type(r)= hlist_node;
subtype(r)= min_quarterword;shift_amount(r)= 0;
q= r+list_offset;link(q)= p;
h= 0;/*135:*/
#line 2986 "hint.w"

d= 0;x= 0;
total_stretch[normal]= 0;total_shrink[normal]= 0;
total_stretch[fil]= 0;total_shrink[fil]= 0;
total_stretch[fill]= 0;total_shrink[fill]= 0;
total_stretch[filll]= 0;total_shrink[filll]= 0

/*:135*/
#line 2975 "hint.w"
;
while(p!=null)/*136:*/
#line 2993 "hint.w"


{reswitch:while(is_char_node(p))
/*139:*/
#line 3038 "hint.w"

{
int c= character(p);
f= font(p);
if(width_base[f]!=0)
{i= char_info(f,c);hd= height_depth(i);
x= x+char_width(f,c);
s= char_height(f,hd);if(s> h)h= s;
s= char_depth(f,hd);if(s> d)d= s;
}
else
/*292:*/
#line 6339 "hint.w"

{scaled ch,cd;
FT_Face ft_face= ft_get_font_face(f);
if(ft_face!=NULL)
{FT_UInt ft_gid= FT_Get_Char_Index(ft_face,c);
if(ft_gid!=0)
x= x+ft_glyph_width(ft_face,ft_gid,font_size[f]);
ft_glyph_height_depth(ft_face,ft_gid,&ch,&cd,font_size[f]);
if(ch> h)h= ch;
if(cd> d)d= cd;
}
}

/*:292*/
#line 3049 "hint.w"

p= link(p);
}

/*:139*/
#line 2997 "hint.w"
;
if(p!=null)
{switch(type(p)){
case hlist_node:case vlist_node:case rule_node:
case unset_node:
/*138:*/
#line 3026 "hint.w"

{x= x+width(p);
if(type(p)>=rule_node)s= 0;else s= shift_amount(p);
if(height(p)-s> h)h= height(p)-s;
if(depth(p)+s> d)d= depth(p)+s;
}

/*:138*/
#line 3003 "hint.w"
break;
case ins_node:case adjust_node:if(adjust_tail!=null)
/*140:*/
#line 3060 "hint.w"

{while(link(q)!=p)q= link(q);
if(type(p)==adjust_node)
{link(adjust_tail)= adjust_ptr(p);
while(link(adjust_tail)!=null)adjust_tail= link(adjust_tail);
p= link(p);free_node(link(q),small_node_size);
}
else{link(adjust_tail)= p;adjust_tail= p;p= link(p);
}
link(q)= p;p= q;
}

/*:140*/
#line 3005 "hint.w"
break;
case whatsit_node:/*293:*/
#line 6352 "hint.w"

switch(subtype(p)){
case image_node:
if(image_height(p)> h)h= image_height(p);
x= x+image_width(p);
break;
case color_node:
just_color= color_ref(p);
break;
case end_color_node:
just_color= -1;
break;
case start_link_node:
just_label= label_ref(as_label(p));just_color= color_ref(as_color(p));
if(just_color==0xFF)just_color= -1;
break;
case end_link_node:
just_label= -1;just_color= color_ref(as_color(p));
if(just_color==0xFF)just_color= -1;
break;
case utf_char_node:
{int f= utf_font(p);
int c= utf_char(p);
/*292:*/
#line 6339 "hint.w"

{scaled ch,cd;
FT_Face ft_face= ft_get_font_face(f);
if(ft_face!=NULL)
{FT_UInt ft_gid= FT_Get_Char_Index(ft_face,c);
if(ft_gid!=0)
x= x+ft_glyph_width(ft_face,ft_gid,font_size[f]);
ft_glyph_height_depth(ft_face,ft_gid,&ch,&cd,font_size[f]);
if(ch> h)h= ch;
if(cd> d)d= cd;
}
}

/*:292*/
#line 6375 "hint.w"

break;
}
default:
break;
}


/*:293*/
#line 3006 "hint.w"
;break;
case glue_node:/*141:*/
#line 3072 "hint.w"

{g= glue_ptr(p);x= x+width(g);
o= stretch_order(g);total_stretch[o]= total_stretch[o]+stretch(g);
o= shrink_order(g);total_shrink[o]= total_shrink[o]+shrink(g);
if(subtype(p)>=a_leaders)
{g= leader_ptr(p);
if(height(g)> h)h= height(g);
if(depth(g)> d)d= depth(g);
}
}

/*:141*/
#line 3007 "hint.w"
break;
case kern_node:case math_node:x= x+width(p);break;
case ligature_node:/*137:*/
#line 3017 "hint.w"

{mem[lig_trick]= mem[lig_char(p)];link(lig_trick)= link(p);
p= lig_trick;goto reswitch;
}

/*:137*/
#line 3009 "hint.w"

default:do_nothing;
}
p= link(p);
}
}


/*:136*/
#line 2978 "hint.w"
;
if(adjust_tail!=null)link(adjust_tail)= null;
height(r)= h;depth(r)= d;
/*142:*/
#line 3086 "hint.w"

if(m==additional)w= x+w;
width(r)= w;x= w-x;
if(x==0)
{glue_sign(r)= normal;glue_order(r)= normal;
set_glue_ratio_zero(glue_set(r));
goto end;
}
else if(x> 0)/*143:*/
#line 3099 "hint.w"

{/*144:*/
#line 3110 "hint.w"

if(total_stretch[filll]!=0)o= filll;
else if(total_stretch[fill]!=0)o= fill;
else if(total_stretch[fil]!=0)o= fil;
else o= normal

/*:144*/
#line 3100 "hint.w"
;
glue_order(r)= o;glue_sign(r)= stretching;
if(total_stretch[o]!=0)glue_set(r)= fix(x/(double)total_stretch[o]);

else{glue_sign(r)= normal;
set_glue_ratio_zero(glue_set(r));
}
goto end;
}

/*:143*/
#line 3095 "hint.w"

else/*145:*/
#line 3116 "hint.w"

{/*146:*/
#line 3129 "hint.w"

if(total_shrink[filll]!=0)o= filll;
else if(total_shrink[fill]!=0)o= fill;
else if(total_shrink[fil]!=0)o= fil;
else o= normal


/*:146*/
#line 3117 "hint.w"
;
glue_order(r)= o;glue_sign(r)= shrinking;
if(total_shrink[o]!=0)glue_set(r)= fix((-x)/(double)total_shrink[o]);

else{glue_sign(r)= normal;
set_glue_ratio_zero(glue_set(r));
}
if((total_shrink[o]<-x)&&(o==normal)&&(list_ptr(r)!=null))
set_glue_ratio_one(glue_set(r));
goto end;
}

/*:145*/
#line 3097 "hint.w"


/*:142*/
#line 2982 "hint.w"
;
end:return r;
}

/*:134*//*147:*/
#line 3145 "hint.w"

static pointer vpackage(pointer p,scaled h,small_number m,scaled l)
{
pointer r;
scaled w,d,x;
scaled s;
pointer g;
glue_ord o;
r= get_node(box_node_size);type(r)= vlist_node;
subtype(r)= min_quarterword;shift_amount(r)= 0;
list_ptr(r)= p;
w= 0;/*135:*/
#line 2986 "hint.w"

d= 0;x= 0;
total_stretch[normal]= 0;total_shrink[normal]= 0;
total_stretch[fil]= 0;total_shrink[fil]= 0;
total_stretch[fill]= 0;total_shrink[fill]= 0;
total_stretch[filll]= 0;total_shrink[filll]= 0

/*:135*/
#line 3156 "hint.w"
;
while(p!=null)/*148:*/
#line 3169 "hint.w"

{if(is_char_node(p))confusion("vpack");

else switch(type(p)){
case hlist_node:case vlist_node:case rule_node:
case unset_node:
/*149:*/
#line 3186 "hint.w"

{x= x+d+height(p);d= depth(p);
if(type(p)>=rule_node)s= 0;else s= shift_amount(p);
if(width(p)+s> w)w= width(p)+s;
}

/*:149*/
#line 3176 "hint.w"
break;
case whatsit_node:/*291:*/
#line 6332 "hint.w"

if(subtype(p)==image_node)
{if(image_width(p)> w)w= image_width(p);
x= x+d+image_height(p);d= 0;
}
/*:291*/
#line 3177 "hint.w"
;break;
case glue_node:/*150:*/
#line 3192 "hint.w"

{x= x+d;d= 0;
g= glue_ptr(p);x= x+width(g);
o= stretch_order(g);total_stretch[o]= total_stretch[o]+stretch(g);
o= shrink_order(g);total_shrink[o]= total_shrink[o]+shrink(g);
if(subtype(p)>=a_leaders)
{g= leader_ptr(p);
if(width(g)> w)w= width(g);
}
}

/*:150*/
#line 3178 "hint.w"
break;
case kern_node:{x= x+d+width(p);d= 0;
}break;
default:do_nothing;
}
p= link(p);
}

/*:148*/
#line 3158 "hint.w"
;
width(r)= w;
if(d> l)
{x= x+d-l;depth(r)= l;
}
else depth(r)= d;
/*151:*/
#line 3206 "hint.w"

if(m==additional)h= x+h;
height(r)= h;x= h-x;
if(x==0)
{glue_sign(r)= normal;glue_order(r)= normal;
set_glue_ratio_zero(glue_set(r));
goto end;
}
else if(x> 0)/*152:*/
#line 3219 "hint.w"

{/*144:*/
#line 3110 "hint.w"

if(total_stretch[filll]!=0)o= filll;
else if(total_stretch[fill]!=0)o= fill;
else if(total_stretch[fil]!=0)o= fil;
else o= normal

/*:144*/
#line 3220 "hint.w"
;
glue_order(r)= o;glue_sign(r)= stretching;
if(total_stretch[o]!=0)glue_set(r)= fix(x/(double)total_stretch[o]);

else{glue_sign(r)= normal;
set_glue_ratio_zero(glue_set(r));
}
goto end;
}


/*:152*/
#line 3215 "hint.w"

else/*153:*/
#line 3231 "hint.w"

{/*146:*/
#line 3129 "hint.w"

if(total_shrink[filll]!=0)o= filll;
else if(total_shrink[fill]!=0)o= fill;
else if(total_shrink[fil]!=0)o= fil;
else o= normal


/*:146*/
#line 3232 "hint.w"
;
glue_order(r)= o;glue_sign(r)= shrinking;
if(total_shrink[o]!=0)glue_set(r)= fix((-x)/(double)total_shrink[o]);

else{glue_sign(r)= normal;
set_glue_ratio_zero(glue_set(r));
}
if((total_shrink[o]<-x)&&(o==normal)&&(list_ptr(r)!=null))
set_glue_ratio_one(glue_set(r));
goto end;
}


/*:153*/
#line 3217 "hint.w"


/*:151*/
#line 3165 "hint.w"
;
end:return r;
}

/*:147*//*157:*/
#line 3325 "hint.w"


/*154:*/
#line 3248 "hint.w"

static pointer happend_to_vlist(pointer b);
static void append_to_vlist(pointer b,uint32_t offset)
{scaled d;
pointer p;
if(prev_depth> ignore_depth)
{d= width(baseline_skip)-prev_depth-height(b);
if(d<line_skip_limit)p= new_glue(line_skip);
else{temp_ptr= new_spec(baseline_skip);
p= new_glue(temp_ptr);glue_ref_count(temp_ptr)= null;
width(temp_ptr)= d;
}
store_map(p,node_pos,offset);
link(tail)= p;tail= p;
}
link(tail)= b;tail= b;prev_depth= depth(b);
}


/*:154*//*168:*/
#line 3557 "hint.w"

static pointer finite_shrink(pointer p)
{pointer q;
QUIT("Infinite glue shrinkage found in a paragraph");
q= new_spec(p);shrink_order(q)= normal;
delete_glue_ref(p);return q;
}

/*:168*//*171:*/
#line 3619 "hint.w"

static void try_break(int pi,small_number break_type)
{
pointer r;
pointer prev_r;
halfword old_l;
bool no_break_yet;
/*172:*/
#line 3647 "hint.w"

pointer prev_prev_r= null;
pointer s;
pointer q;
pointer v;
int t;
internal_font_number f;
halfword l;
bool node_r_stays_active;
scaled line_width= 0;
int fit_class;
halfword b;
int d;
bool artificial_demerits;
#ifdef STAT
pointer save_link;
#endif
#line 3664 "hint.w"
 scaled shortfall;

/*:172*/
#line 3626 "hint.w"

/*173:*/
#line 3666 "hint.w"

if(abs(pi)>=inf_penalty)
{if(pi> 0)goto end;
else pi= eject_penalty;
}

/*:173*/
#line 3627 "hint.w"

no_break_yet= true;prev_r= active;old_l= 0;
do_all_six(copy_to_cur_active);
loop{resume:r= link(prev_r);
/*174:*/
#line 3677 "hint.w"


if(type(r)==delta_node)
{do_all_six(update_width);
prev_prev_r= prev_r;prev_r= r;goto resume;
}

/*:174*/
#line 3632 "hint.w"
;
/*177:*/
#line 3725 "hint.w"

{l= line_number(r);
if(l> old_l)
{
if((minimum_demerits<awful_bad)&&
((old_l!=easy_line)||(r==last_active)))
/*178:*/
#line 3743 "hint.w"

{if(no_break_yet)/*179:*/
#line 3779 "hint.w"

{no_break_yet= false;do_all_six(set_break_width_to_background);
s= cur_p;
if(break_type> unhyphenated)if(cur_p!=null)
/*182:*/
#line 3822 "hint.w"

{t= replace_count(cur_p);v= cur_p;s= post_break(cur_p);
while(t> 0)
{decr(t);v= link(v);
/*183:*/
#line 3840 "hint.w"

if(is_char_node(v))
{f= font(v);
break_width[1]= break_width[1]-char_width(f,character(v));
}
else switch(type(v)){
case ligature_node:{f= font(lig_char(v));
break_width[1]= break_width[1]-
char_width(f,character(lig_char(v)));
}break;
case hlist_node:case vlist_node:case rule_node:
case kern_node:
break_width[1]= break_width[1]-width(v);break;
default:confusion("disc1");

}

/*:183*/
#line 3826 "hint.w"
;
}
while(s!=null)
{/*184:*/
#line 3857 "hint.w"

if(is_char_node(s))
{f= font(s);
break_width[1]= break_width[1]+char_width(f,character(s));
}
else switch(type(s)){
case ligature_node:{f= font(lig_char(s));
break_width[1]= break_width[1]+
char_width(f,character(lig_char(s)));
}break;
case hlist_node:case vlist_node:case rule_node:
case kern_node:
break_width[1]= break_width[1]+width(s);break;
default:confusion("disc2");

}

/*:184*/
#line 3829 "hint.w"
;
s= link(s);
}
break_width[1]= break_width[1]+disc_width;
if(post_break(cur_p)==null)s= link(v);

}

/*:182*/
#line 3783 "hint.w"
;
while(s!=null)
{if(is_char_node(s))goto done;
switch(type(s)){
case glue_node:/*180:*/
#line 3798 "hint.w"

{v= glue_ptr(s);break_width[1]= break_width[1]-width(v);
break_width[2+stretch_order(v)]= break_width[2+stretch_order(v)]-stretch(v);
break_width[6]= break_width[6]-shrink(v);
}

/*:180*/
#line 3787 "hint.w"
break;
case penalty_node:do_nothing;break;
case math_node:break_width[1]= break_width[1]-width(s);break;
case kern_node:if(subtype(s)!=explicit)goto done;
else break_width[1]= break_width[1]-width(s);break;
default:goto done;
}
s= link(s);
}
done:;}

/*:179*/
#line 3744 "hint.w"
;
/*185:*/
#line 3883 "hint.w"

if(type(prev_r)==delta_node)
{do_all_six(convert_to_break_width);
}
else if(prev_r==active)
{do_all_six(store_break_width);
}
else{q= get_node(delta_node_size);link(q)= r;type(q)= delta_node;
subtype(q)= 0;
do_all_six(new_delta_to_break_width);
link(prev_r)= q;prev_prev_r= prev_r;prev_r= q;
}

/*:185*/
#line 3745 "hint.w"
;
if(abs(adj_demerits)>=awful_bad-minimum_demerits)
minimum_demerits= awful_bad-1;
else minimum_demerits= minimum_demerits+abs(adj_demerits);
for(fit_class= very_loose_fit;fit_class<=tight_fit;fit_class++)
{if(minimal_demerits[fit_class]<=minimum_demerits)
/*187:*/
#line 3913 "hint.w"

{q= get_node(passive_node_size);
link(q)= passive;passive= q;cur_break(q)= cur_p;
#ifdef STAT
incr(pass_number);serial(q)= pass_number;
#endif
#line 3919 "hint.w"

prev_break(q)= best_place[fit_class];
q= get_node(active_node_size);break_node(q)= passive;
line_number(q)= best_pl_line[fit_class]+1;
fitness(q)= fit_class;type(q)= break_type;
total_demerits(q)= minimal_demerits[fit_class];
link(q)= r;link(prev_r)= q;prev_r= q;
#ifdef STAT
if(tracing_paragraphs> 0)
/*188:*/
#line 3933 "hint.w"

{print_nl("@@");print_int(serial(passive));

print(": line ");print_int(line_number(q)-1);
print_char('.');print_int(fit_class);
if(break_type==hyphenated)print_char('-');
print(" t=");print_int(total_demerits(q));
print(" -> @@");
if(prev_break(passive)==null)print_char('0');
else print_int(serial(prev_break(passive)));
}

/*:188*/
#line 3928 "hint.w"
;
#endif
#line 3930 "hint.w"

}

/*:187*/
#line 3751 "hint.w"
;
minimal_demerits[fit_class]= awful_bad;
}
minimum_demerits= awful_bad;
/*186:*/
#line 3902 "hint.w"

if(r!=last_active)
{q= get_node(delta_node_size);link(q)= r;type(q)= delta_node;
subtype(q)= 0;
do_all_six(new_delta_from_break_width);
link(prev_r)= q;prev_prev_r= prev_r;prev_r= q;
}

/*:186*/
#line 3755 "hint.w"
;
}

/*:178*/
#line 3731 "hint.w"
;
if(r==last_active)goto end;
/*192:*/
#line 4006 "hint.w"

if(l> easy_line)
{line_width= second_width;old_l= max_halfword-1;
}
else{old_l= l;
if(l> last_special_line)line_width= second_width;
else if(par_shape_ptr==null)line_width= first_width;
else line_width= mem[par_shape_ptr+2*l].sc;
}

/*:192*/
#line 3733 "hint.w"
;
}
}

/*:177*/
#line 3635 "hint.w"
;
/*193:*/
#line 4026 "hint.w"

{artificial_demerits= false;

shortfall= line_width-cur_active_width[1];
if(shortfall> 0)
/*194:*/
#line 4056 "hint.w"

if((cur_active_width[3]!=0)||(cur_active_width[4]!=0)||
(cur_active_width[5]!=0))
{b= 0;fit_class= decent_fit;
}
else{if(shortfall> 7230584)if(cur_active_width[2]<1663497)
{b= inf_bad;fit_class= very_loose_fit;goto done1;
}
b= badness(shortfall,cur_active_width[2]);
if(b> 12)
if(b> 99)fit_class= very_loose_fit;
else fit_class= loose_fit;
else fit_class= decent_fit;
done1:;
}

/*:194*/
#line 4032 "hint.w"

else/*195:*/
#line 4075 "hint.w"

{if(-shortfall> cur_active_width[6])b= inf_bad+1;
else b= badness(-shortfall,cur_active_width[6]);
if(b> 12)fit_class= tight_fit;else fit_class= decent_fit;
}

/*:195*/
#line 4034 "hint.w"
;
if((b> inf_bad)||(pi==eject_penalty))
/*196:*/
#line 4090 "hint.w"

{if(final_pass&&(minimum_demerits==awful_bad)&&
(link(r)==last_active)&&
(prev_r==active))
artificial_demerits= true;
else if(b> threshold)goto deactivate;
node_r_stays_active= false;
}

/*:196*/
#line 4037 "hint.w"

else{prev_r= r;
if(b> threshold)goto resume;
node_r_stays_active= true;
}
/*197:*/
#line 4106 "hint.w"

if(artificial_demerits)d= 0;
else/*201:*/
#line 4167 "hint.w"

{d= line_penalty+b;
if(abs(d)>=10000)d= 100000000;else d= d*d;
if(pi!=0)
{if(pi> 0)d= d+pi*pi;
else if(pi> eject_penalty)d= d-pi*pi;}
if((break_type==hyphenated)&&(type(r)==hyphenated))
{if(cur_p!=null)d= d+double_hyphen_demerits;
else d= d+final_hyphen_demerits;}
if(abs(fit_class-fitness(r))> 1)d= d+adj_demerits;
}

/*:201*/
#line 4108 "hint.w"
;
#ifdef STAT
if(tracing_paragraphs> 0)
/*198:*/
#line 4122 "hint.w"

{if(printed_node!=cur_p)
/*199:*/
#line 4144 "hint.w"

{print_nl("");
if(cur_p==null)short_display(link(printed_node));
else{save_link= link(cur_p);
link(cur_p)= null;print_nl("");short_display(link(printed_node));
link(cur_p)= save_link;
}
printed_node= cur_p;
}

/*:199*/
#line 4124 "hint.w"
;
print_nl("@");

if(cur_p==null)print_esc("par");
else if(type(cur_p)!=glue_node)
{if(type(cur_p)==penalty_node)print_esc("penalty");
else if(type(cur_p)==disc_node)print_esc("discretionary");
else if(type(cur_p)==kern_node)print_esc("kern");
else print_esc("math");
}
print(" via @@");
if(break_node(r)==null)print_char('0');
else print_int(serial(break_node(r)));
print(" b=");
if(b> inf_bad)print_char('*');else print_int(b);

print(" p=");print_int(pi);print(" d=");
if(artificial_demerits)print_char('*');else print_int(d);
}

/*:198*/
#line 4111 "hint.w"
;
#endif
#line 4113 "hint.w"

d= d+total_demerits(r);

if(d<=minimal_demerits[fit_class])
{minimal_demerits[fit_class]= d;
best_place[fit_class]= break_node(r);best_pl_line[fit_class]= l;
if(d<minimum_demerits)minimum_demerits= d;
}

/*:197*/
#line 4042 "hint.w"
;
if(node_r_stays_active)goto resume;
deactivate:/*202:*/
#line 4189 "hint.w"

link(prev_r)= link(r);free_node(r,active_node_size);
if(prev_r==active)/*203:*/
#line 4214 "hint.w"

{r= link(active);
if(type(r)==delta_node)
{do_all_six(update_active);
do_all_six(copy_to_cur_active);
link(active)= link(r);free_node(r,delta_node_size);
}
}

/*:203*/
#line 4192 "hint.w"

else if(type(prev_r)==delta_node)
{r= link(prev_r);
if(r==last_active)
{do_all_six(downdate_width);
link(prev_prev_r)= last_active;
free_node(prev_r,delta_node_size);prev_r= prev_prev_r;
}
else if(type(r)==delta_node)
{do_all_six(update_width);
do_all_six(combine_two_deltas);
link(prev_r)= link(r);free_node(r,delta_node_size);
}
}

/*:202*/
#line 4044 "hint.w"
;
}

/*:193*/
#line 3638 "hint.w"
;
}
end:;
#ifdef STAT
/*200:*/
#line 4159 "hint.w"

if(cur_p==printed_node)if(cur_p!=null)if(type(cur_p)==disc_node)
{t= replace_count(cur_p);
while(t> 0)
{decr(t);printed_node= link(printed_node);
}
}

/*:200*/
#line 3642 "hint.w"
;
#endif
#line 3644 "hint.w"

}

/*:171*//*219:*/
#line 4537 "hint.w"

static void post_line_break(int final_widow_penalty)
{
pointer q,r,s;
bool disc_break;
bool post_disc_break;
bool first_line= true;
uint32_t line_offset,next_offset;
scaled cur_width;
scaled cur_indent;
quarterword t;
int pen;
halfword cur_line;
/*220:*/
#line 4607 "hint.w"

q= break_node(best_bet);cur_p= null;
do{r= q;q= prev_break(q);next_break(r)= cur_p;cur_p= r;
}while(!(q==null))

/*:220*/
#line 4551 "hint.w"
;
cur_line= prev_graf+1;
next_offset= hposition(link(temp_head));
if(next_offset> node_pos)
next_offset= next_offset-node_pos;
else
next_offset= 0;
do{
line_offset= next_offset;
{pointer q= cur_break(cur_p);
if(q==null)
next_offset= (hpos-hstart);
else
next_offset= hposition(q);
if(next_offset> node_pos)
next_offset= next_offset-node_pos;
else
next_offset= 0;
}
/*222:*/
#line 4644 "hint.w"

/*223:*/
#line 4656 "hint.w"

q= cur_break(cur_p);disc_break= false;post_disc_break= false;
if(q!=null)
if(type(q)==glue_node)
{delete_glue_ref(glue_ptr(q));
glue_ptr(q)= right_skip;
subtype(q)= right_skip_code+1;add_glue_ref(right_skip);
goto done;
}
else{if(type(q)==disc_node)
/*224:*/
#line 4675 "hint.w"

{pointer pre_q= pre_break(q);
pointer post_q= post_break(q);
t= replace_count(q);
type(q)= whatsit_node;
subtype(q)= ignore_node;
ignore_info(q)= 1;
/*225:*/
#line 4694 "hint.w"

if(t==0){ignore_list(q)= null;r= link(q);}
else{r= q;
while(t> 1)
{r= link(r);decr(t);
}
s= link(r);
r= link(s);link(s)= null;
ignore_list(q)= link(q);
}

/*:225*/
#line 4682 "hint.w"
;
s= get_node(ignore_node_size);
type(s)= whatsit_node;
subtype(s)= ignore_node;
ignore_info(s)= 0;
ignore_list(s)= null;
link(s)= r;r= s;
if(post_q!=null)/*226:*/
#line 4708 "hint.w"

{s= post_q;
while(link(s)!=null)s= link(s);
link(s)= r;r= post_q;post_disc_break= true;
}

/*:226*/
#line 4689 "hint.w"
;
if(pre_q!=null)/*227:*/
#line 4717 "hint.w"

{s= pre_q;link(q)= s;
while(link(s)!=null)s= link(s);
q= s;
}

/*:227*/
#line 4690 "hint.w"
;
link(q)= r;disc_break= true;
}

/*:224*/
#line 4666 "hint.w"

else if((type(q)==math_node)||(type(q)==kern_node))width(q)= 0;
}
else{q= temp_head;
while(link(q)!=null)q= link(q);
}
/*228:*/
#line 4723 "hint.w"

r= new_glue(right_skip);link(r)= link(q);link(q)= r;q= r

/*:228*/
#line 4672 "hint.w"
;
done:

/*:223*/
#line 4646 "hint.w"
;
/*229:*/
#line 4730 "hint.w"

r= link(q);link(q)= null;q= link(temp_head);link(temp_head)= r;
if(left_skip!=zero_glue)
{r= new_glue(left_skip);
link(r)= q;q= r;
}

/*:229*/
#line 4647 "hint.w"
;
/*231:*/
#line 4759 "hint.w"

if(cur_line> last_special_line)
{cur_width= second_width;cur_indent= second_indent;
}
else if(par_shape_ptr==null)
{cur_width= first_width;cur_indent= first_indent;
}
else{cur_width= mem[par_shape_ptr+2*cur_line].sc;
cur_indent= mem[par_shape_ptr+2*cur_line-1].sc;
}
adjust_tail= adjust_head;just_box= hpack(q,cur_width,exactly);
shift_amount(just_box)= cur_indent

/*:231*/
#line 4648 "hint.w"
;
/*230:*/
#line 4737 "hint.w"

if(first_line)
{pointer p= happend_to_vlist(just_box);
if(p!=null)
store_map(p,node_pos,line_offset);
store_map(just_box,node_pos,line_offset);
first_line= false;
}
else
{append_to_vlist(just_box,line_offset);
store_map(just_box,node_pos,line_offset);
}
if(adjust_head!=adjust_tail)
{link(tail)= link(adjust_head);tail= adjust_tail;
}
adjust_tail= null

/*:230*/
#line 4650 "hint.w"
;
/*232:*/
#line 4779 "hint.w"

if(cur_line+1!=best_line)
{pen= inter_line_penalty;
if(cur_line==prev_graf+1)pen= pen+club_penalty;
if(cur_line+2==best_line)pen= pen+final_widow_penalty;
if(disc_break)pen= pen+broken_penalty;
if(pen!=0)
{r= new_penalty(pen);store_map(r,node_pos,next_offset);
link(tail)= r;tail= r;
}
}


/*:232*/
#line 4651 "hint.w"


/*:222*/
#line 4571 "hint.w"
;
incr(cur_line);cur_p= next_break(cur_p);
if(cur_p!=null)if(!post_disc_break)
/*221:*/
#line 4619 "hint.w"

{r= temp_head;
loop{q= link(r);
if(q==cur_break(cur_p))goto done1;


if(is_char_node(q))goto done1;
if(non_discardable(q))goto done1;
if(type(q)==kern_node)if(subtype(q)!=explicit)goto done1;
r= q;
}
done1:if(r!=temp_head)
{link(r)= null;flush_node_list(link(temp_head));
link(temp_head)= q;
}
}

/*:221*/
#line 4574 "hint.w"
;
if(cur_p!=null)
{if(just_label>=0)
{q= get_node(link_node_size);
type(q)= whatsit_node;subtype(q)= start_link_node;
label_ref(as_label(q))= just_label;
if(just_color>=0)color_ref(as_color(q))= just_color;
else color_ref(as_color(q))= 0xFF;
link(q)= link(temp_head);
link(temp_head)= q;
}
else if(just_color>=0)
{q= get_node(color_node_size);
type(q)= whatsit_node;subtype(q)= color_node;
color_ref(q)= just_color;
link(q)= link(temp_head);
link(temp_head)= q;
}

}
}while(!(cur_p==null));
if((cur_line!=best_line)||(link(temp_head)!=null))
confusion("line breaking");

prev_graf= best_line-1;
}

/*:219*/
#line 3327 "hint.w"


static void line_break(int final_widow_penalty,pointer par_ptr)
{scaled x= cur_list.hs_field;
/*204:*/
#line 4243 "hint.w"

bool auto_breaking;
pointer prev_p;
pointer q,r,s;
internal_font_number f;

/*:204*/
#line 3331 "hint.w"

set_line_break_params();just_color= -1;just_label= -1;
/*158:*/
#line 3352 "hint.w"

link(temp_head)= par_ptr;

/*:158*//*169:*/
#line 3565 "hint.w"

no_shrink_error_yet= true;
check_shrinkage(left_skip);check_shrinkage(right_skip);
q= left_skip;r= right_skip;background[1]= width(q)+width(r);
background[2]= 0;background[3]= 0;background[4]= 0;background[5]= 0;
background[2+stretch_order(q)]= stretch(q);
background[2+stretch_order(r)]= background[2+stretch_order(r)]+stretch(r);
background[6]= shrink(q)+shrink(r);

/*:169*//*176:*/
#line 3711 "hint.w"

minimum_demerits= awful_bad;
minimal_demerits[tight_fit]= awful_bad;
minimal_demerits[decent_fit]= awful_bad;
minimal_demerits[loose_fit]= awful_bad;
minimal_demerits[very_loose_fit]= awful_bad;

/*:176*//*190:*/
#line 3974 "hint.w"

if(par_shape_ptr==null)
if(hang_indent==0)
{last_special_line= 0;second_width= x;
second_indent= 0;
}
else/*191:*/
#line 3985 "hint.w"

{last_special_line= abs(hang_after);
if(hang_after<0)
{first_width= x-abs(hang_indent);
if(hang_indent>=0)first_indent= hang_indent;
else first_indent= 0;
second_width= x;second_indent= 0;
}
else{first_width= x;first_indent= 0;
second_width= x-abs(hang_indent);
if(hang_indent>=0)second_indent= hang_indent;
else second_indent= 0;
}
}

/*:191*/
#line 3980 "hint.w"

else QUIT("parshape not yet implemented");
if(looseness==0)easy_line= last_special_line;
else easy_line= max_halfword

/*:190*/
#line 3333 "hint.w"
;
/*205:*/
#line 4253 "hint.w"

threshold= pretolerance;
if(threshold>=0)
{
#ifdef STAT
if(tracing_paragraphs> 0)
{print_nl("@firstpass");}
#endif
#line 4261 "hint.w"

second_pass= false;final_pass= false;
}
else{threshold= tolerance;second_pass= true;
final_pass= (emergency_stretch<=0);
#ifdef STAT
#endif
#line 4268 "hint.w"

}
loop{if(threshold> inf_bad)threshold= inf_bad;
/*206:*/
#line 4306 "hint.w"

q= get_node(active_node_size);
type(q)= unhyphenated;fitness(q)= decent_fit;
link(q)= last_active;break_node(q)= null;
line_number(q)= prev_graf+1;total_demerits(q)= 0;link(active)= q;
do_all_six(store_background);
passive= null;printed_node= temp_head;pass_number= 0;

/*:206*/
#line 4271 "hint.w"
;
cur_p= link(temp_head);auto_breaking= true;
prev_p= cur_p;
while((cur_p!=null)&&(link(active)!=last_active))
/*208:*/
#line 4341 "hint.w"

{if(is_char_node(cur_p))
/*209:*/
#line 4375 "hint.w"

{prev_p= cur_p;
do{f= font(cur_p);
act_width= act_width+char_width(f,character(cur_p));
cur_p= link(cur_p);
}while(!(!is_char_node(cur_p)));
}

/*:209*/
#line 4343 "hint.w"
;
switch(type(cur_p)){
case hlist_node:case vlist_node:case rule_node:act_width= act_width+width(cur_p);break;
case whatsit_node:/*295:*/
#line 6392 "hint.w"

if(subtype(cur_p)==image_node)
act_width= act_width+image_width(cur_p);
else if(subtype(cur_p)==utf_char_node)
act_width= act_width+ft_char_width(utf_font(cur_p),utf_char(cur_p));
adv_past(cur_p)


/*:295*/
#line 4347 "hint.w"
break;
case glue_node:{/*210:*/
#line 4386 "hint.w"

if(auto_breaking)
{if(is_char_node(prev_p))try_break(0,unhyphenated);
else if(precedes_break(prev_p))try_break(0,unhyphenated);
else if((type(prev_p)==kern_node)&&(subtype(prev_p)!=explicit))
try_break(0,unhyphenated);
}
check_shrinkage(glue_ptr(cur_p));q= glue_ptr(cur_p);
act_width= act_width+width(q);
active_width[2+stretch_order(q)]= 
active_width[2+stretch_order(q)]+stretch(q);
active_width[6]= active_width[6]+shrink(q)

/*:210*/
#line 4349 "hint.w"
;
}break;
case kern_node:if(subtype(cur_p)==explicit)kern_break
else act_width= act_width+width(cur_p);break;
case ligature_node:{f= font(lig_char(cur_p));
act_width= act_width+char_width(f,character(lig_char(cur_p)));
}break;
case disc_node:/*211:*/
#line 4402 "hint.w"

{if(!is_auto_disc(cur_p)||second_pass||final_pass)
{s= pre_break(cur_p);disc_width= 0;
if(s==null)try_break(ex_hyphen_penalty,hyphenated);
else{do{/*212:*/
#line 4422 "hint.w"

if(is_char_node(s))
{f= font(s);
disc_width= disc_width+char_width(f,character(s));
}
else switch(type(s)){
case ligature_node:{f= font(lig_char(s));
disc_width= disc_width+
char_width(f,character(lig_char(s)));
}break;
case hlist_node:case vlist_node:case rule_node:
case kern_node:
disc_width= disc_width+width(s);break;
default:confusion("disc3");

}

/*:212*/
#line 4406 "hint.w"
;
s= link(s);
}while(!(s==null));
act_width= act_width+disc_width;
try_break(hyphen_penalty,hyphenated);
act_width= act_width-disc_width;
}
}
r= replace_count(cur_p);s= link(cur_p);
while(r> 0)
{/*213:*/
#line 4439 "hint.w"

if(is_char_node(s))
{f= font(s);
act_width= act_width+char_width(f,character(s));
}
else switch(type(s)){
case ligature_node:{f= font(lig_char(s));
act_width= act_width+
char_width(f,character(lig_char(s)));
}break;
case hlist_node:case vlist_node:case rule_node:
case kern_node:
act_width= act_width+width(s);break;
default:confusion("disc4");

}

/*:213*/
#line 4416 "hint.w"
;
decr(r);s= link(s);
}
prev_p= cur_p;cur_p= s;goto done5;
}

/*:211*/
#line 4357 "hint.w"

case math_node:{auto_breaking= (subtype(cur_p)==after);kern_break;
}break;
case penalty_node:try_break(penalty(cur_p),unhyphenated);break;
case ins_node:case adjust_node:do_nothing;break;
default:confusion("paragraph");

}
prev_p= cur_p;cur_p= link(cur_p);
done5:;}

/*:208*/
#line 4277 "hint.w"
;
if(cur_p==null)
/*215:*/
#line 4475 "hint.w"

{try_break(eject_penalty,hyphenated);
if(link(active)!=last_active)
{/*216:*/
#line 4485 "hint.w"

r= link(active);fewest_demerits= awful_bad;
do{if(type(r)!=delta_node)if(total_demerits(r)<fewest_demerits)
{fewest_demerits= total_demerits(r);best_bet= r;
}
r= link(r);
}while(!(r==last_active));
best_line= line_number(best_bet)

/*:216*/
#line 4478 "hint.w"
;
if(looseness==0)goto done;
/*217:*/
#line 4499 "hint.w"

{r= link(active);actual_looseness= 0;
do{if(type(r)!=delta_node)
{line_diff= line_number(r)-best_line;
if(((line_diff<actual_looseness)&&(looseness<=line_diff))||
((line_diff> actual_looseness)&&(looseness>=line_diff)))
{best_bet= r;actual_looseness= line_diff;
fewest_demerits= total_demerits(r);
}
else if((line_diff==actual_looseness)&&
(total_demerits(r)<fewest_demerits))
{best_bet= r;fewest_demerits= total_demerits(r);
}
}
r= link(r);
}while(!(r==last_active));
best_line= line_number(best_bet);
}

/*:217*/
#line 4480 "hint.w"
;
if((actual_looseness==looseness)||final_pass)goto done;
}
}

/*:215*/
#line 4280 "hint.w"
;
/*207:*/
#line 4314 "hint.w"

q= link(active);
while(q!=last_active)
{cur_p= link(q);
if(type(q)==delta_node)free_node(q,delta_node_size);
else free_node(q,active_node_size);
q= cur_p;
}
q= passive;
while(q!=null)
{cur_p= link(q);
free_node(q,passive_node_size);
q= cur_p;
}

/*:207*/
#line 4281 "hint.w"
;
if(!second_pass)
{
#ifdef STAT
if(tracing_paragraphs> 0)print_nl("@secondpass");
#endif
#line 4287 "hint.w"
 threshold= tolerance;second_pass= true;final_pass= (emergency_stretch<=0);
}
else{
#ifdef STAT
if(tracing_paragraphs> 0)
print_nl("@emergencypass");
#endif
#line 4294 "hint.w"
 background[2]= background[2]+emergency_stretch;final_pass= true;
}
}
done:
#ifdef STAT
#endif
#line 4300 "hint.w"

/*:205*/
#line 3334 "hint.w"
;
/*218:*/
#line 4523 "hint.w"

post_line_break(final_widow_penalty)

/*:218*/
#line 3336 "hint.w"
;
/*207:*/
#line 4314 "hint.w"

q= link(active);
while(q!=last_active)
{cur_p= link(q);
if(type(q)==delta_node)free_node(q,delta_node_size);
else free_node(q,active_node_size);
q= cur_p;
}
q= passive;
while(q!=null)
{cur_p= link(q);
free_node(q,passive_node_size);
q= cur_p;
}

/*:207*/
#line 3337 "hint.w"
;
hrestore_param_list();
}

/*:157*//*234:*/
#line 4812 "hint.w"


#define ensure_vbox(N) 

static pointer prune_page_top(pointer p)
{pointer prev_p;
pointer q;
prev_p= temp_head;link(temp_head)= p;
while(p!=null)
switch(type(p)){
case hlist_node:case vlist_node:case rule_node:/*235:*/
#line 4835 "hint.w"

{temp_ptr= new_spec(pointer_def[glue_kind][split_top_skip_no]);
q= new_glue(temp_ptr);glue_ref_count(temp_ptr)= null;link(prev_p)= q;link(q)= p;

if(width(temp_ptr)> height(p))width(temp_ptr)= width(temp_ptr)-height(p);
else width(temp_ptr)= 0;
p= null;
}

/*:235*/
#line 4823 "hint.w"
break;
case whatsit_node:case ins_node:{prev_p= p;p= link(prev_p);
}break;
case glue_node:case kern_node:case penalty_node:{q= p;p= link(q);link(q)= null;
link(prev_p)= p;flush_node_list(q);
}break;
default:confusion("pruning");

}
return link(temp_head);
}

/*:234*//*236:*/
#line 4860 "hint.w"

static pointer vert_break(pointer p,scaled h,scaled d)

{
pointer prev_p;

pointer q,r;
int pi;
int b;
int least_cost;
pointer best_place= p;
scaled prev_dp;
small_number t;
prev_p= p;
least_cost= awful_bad;do_all_six(set_height_zero);prev_dp= 0;
loop{/*238:*/
#line 4895 "hint.w"

if(p==null)pi= eject_penalty;
else/*239:*/
#line 4910 "hint.w"

switch(type(p)){
case hlist_node:case vlist_node:case rule_node:{
cur_height= cur_height+prev_dp+height(p);prev_dp= depth(p);
goto not_found;
}
case whatsit_node:/*297:*/
#line 6407 "hint.w"

goto not_found
/*:297*/
#line 4916 "hint.w"
;
case glue_node:if(precedes_break(prev_p))pi= 0;
else goto update_heights;break;
case kern_node:{if(link(p)==null)t= penalty_node;
else t= type(link(p));
if(t==glue_node)pi= 0;else goto update_heights;
}break;
case penalty_node:pi= penalty(p);break;
case ins_node:goto not_found;
default:confusion("vertbreak");

}

/*:239*/
#line 4899 "hint.w"
;
/*240:*/
#line 4931 "hint.w"

if(pi<inf_penalty)
{/*241:*/
#line 4946 "hint.w"

if(cur_height<h)
if((active_height[3]!=0)||(active_height[4]!=0)||
(active_height[5]!=0))b= 0;
else b= badness(h-cur_height,active_height[2]);
else if(cur_height-h> active_height[6])b= awful_bad;
else b= badness(cur_height-h,active_height[6])

/*:241*/
#line 4933 "hint.w"
;
if(b<awful_bad)
{if(pi<=eject_penalty)b= pi;
else if(b<inf_bad)b= b+pi;
else b= deplorable;
}
if(b<=least_cost)
{best_place= p;least_cost= b;
best_height_plus_depth= cur_height+prev_dp;
}
if((b==awful_bad)||(pi<=eject_penalty))goto done;
}

/*:240*/
#line 4901 "hint.w"
;
if((type(p)<glue_node)||(type(p)> kern_node))goto not_found;
update_heights:/*242:*/
#line 4958 "hint.w"

if(type(p)==kern_node)q= p;
else{q= glue_ptr(p);
active_height[2+stretch_order(q)]= 
active_height[2+stretch_order(q)]+stretch(q);
active_height[6]= active_height[6]+shrink(q);
if((shrink_order(q)!=normal)&&(shrink(q)!=0))
{
DBG(DBGTEX,"Infinite glue shrinkage found in box being split");
r= new_spec(q);shrink_order(r)= normal;delete_glue_ref(q);
glue_ptr(p)= r;q= r;
}
}
cur_height= cur_height+prev_dp+width(q);prev_dp= 0


/*:242*/
#line 4904 "hint.w"
;
not_found:if(prev_dp> d)
{cur_height= cur_height+prev_dp-d;
prev_dp= d;
}

/*:238*/
#line 4877 "hint.w"
;
prev_p= p;p= link(prev_p);
}
done:return best_place;
}

/*:236*//*247:*/
#line 5125 "hint.w"

static void freeze_page_specs(small_number s)
{page_contents= s;
page_goal= hvsize;page_max_depth= max_depth;
page_depth= 0;do_all_six(set_page_so_far_zero);
least_page_cost= awful_bad;
#ifdef STAT
if(tracing_pages> 0)
{print_nl("%% goal height=");print_scaled(page_goal);

print(", max depth=");print_scaled(page_max_depth);
}
#endif
#line 5138 "hint.w"

}

/*:247*//*249:*/
#line 5174 "hint.w"

static bool hbuild_page(void)
{
pointer p;
pointer q,r;
int b,c;
int pi;
if(link(contrib_head)==null)return false;
do{resume:p= link(contrib_head);
/*251:*/
#line 5203 "hint.w"

/*254:*/
#line 5232 "hint.w"

switch(type(p)){
case hlist_node:case vlist_node:case rule_node:if(page_contents<box_there)
/*255:*/
#line 5256 "hint.w"

{if(page_contents==empty)freeze_page_specs(box_there);
else page_contents= box_there;
temp_ptr= new_spec(pointer_def[glue_kind][top_skip_no]);
q= new_glue(temp_ptr);glue_ref_count(temp_ptr)= null;
{uint64_t h= hlocation(p);store_map(q,LOC_POS0(h),LOC_OFF(h));}
if(width(temp_ptr)> height(p))width(temp_ptr)= width(temp_ptr)-height(p);
else width(temp_ptr)= 0;
link(q)= p;link(contrib_head)= q;goto resume;
}

/*:255*/
#line 5236 "hint.w"

else/*256:*/
#line 5267 "hint.w"

{page_total= page_total+page_depth+height(p);
page_depth= depth(p);
goto contribute;
}

/*:256*/
#line 5238 "hint.w"
break;
case whatsit_node:/*296:*/
#line 6400 "hint.w"

if(subtype(p)==image_node)
{page_total= page_total+page_depth+image_height(p);
page_depth= 0;
}
goto contribute

/*:296*/
#line 5240 "hint.w"
;
case glue_node:if(page_contents<box_there)goto done1;
else if(precedes_break(page_tail)&&
!(type(page_tail)==whatsit_node&&subtype(page_tail)==color_node))
pi= 0;
else goto update_heights;break;
case kern_node:if(page_contents<box_there)goto done1;
else if(link(p)==null)return false;
else if(type(link(p))==glue_node)pi= 0;
else goto update_heights;break;
case penalty_node:if(page_contents<box_there)goto done1;else pi= penalty(p);break;
case ins_node:happend_insertion(p);goto contribute;
default:confusion("page");

}

/*:254*/
#line 5208 "hint.w"
;
/*259:*/
#line 5295 "hint.w"

if(pi<inf_penalty)
{/*261:*/
#line 5339 "hint.w"

if(page_total<page_goal)
if((page_so_far[3]!=0)||(page_so_far[4]!=0)||
(page_so_far[5]!=0))b= 0;
else b= badness(page_goal-page_total,page_so_far[2]);
else if(page_total-page_goal> page_shrink)b= awful_bad;
else b= badness(page_total-page_goal,page_shrink)

/*:261*/
#line 5298 "hint.w"
;
if(b<awful_bad)
if(pi<=eject_penalty)c= pi;
else if(b<inf_bad)c= b+pi+insert_penalties;
else c= deplorable;
else c= b;
if(insert_penalties>=10000)c= awful_bad;
#ifdef STAT
if(tracing_pages> 0)/*260:*/
#line 5327 "hint.w"

{print(" t=");print_totals();
print(" g=");print_scaled(page_goal);
print(" b=");
if(b==awful_bad)print_char('*');else print_int(b);

print(" p=");print_int(pi);
print(" c=");
if(c==awful_bad)print_char('*');else print_int(c);
if(c<=least_page_cost)print_char('#');
}

/*:260*/
#line 5306 "hint.w"
;
#endif
#line 5308 "hint.w"

if(c<=least_page_cost)
{best_page_break= p;best_size= page_goal;
least_page_cost= c;
r= link(page_ins_head);
while(r!=page_ins_head)
{best_ins_ptr(r)= last_ins_ptr(r);
r= link(r);
}
}
if((c==awful_bad)||(pi<=eject_penalty))
{hloc_set_next(best_page_break);
if(p==best_page_break)best_page_break= null;
hpack_page();
hfill_page_template();
return true;
}
}

/*:259*/
#line 5211 "hint.w"
;
if((type(p)<glue_node)||(type(p)> kern_node))goto contribute;
update_heights:/*258:*/
#line 5280 "hint.w"

if(type(p)==kern_node)q= p;
else{q= glue_ptr(p);
page_so_far[2+stretch_order(q)]= 
page_so_far[2+stretch_order(q)]+stretch(q);
page_shrink= page_shrink+shrink(q);
if((shrink_order(q)!=normal)&&(shrink(q)!=0))
{
DBG(DBGTEX,"Infinite glue shrinkage found on current page");
r= new_spec(q);shrink_order(r)= normal;fast_delete_glue_ref(q);
glue_ptr(p)= r;q= r;
}
}
page_total= page_total+page_depth+width(q);page_depth= 0

/*:258*/
#line 5214 "hint.w"
;
contribute:/*257:*/
#line 5273 "hint.w"

if(page_depth> page_max_depth)
{page_total= 
page_total+page_depth-page_max_depth;
page_depth= page_max_depth;
}

/*:257*/
#line 5215 "hint.w"
;
/*252:*/
#line 5220 "hint.w"

link(page_tail)= p;page_tail= p;
link(contrib_head)= link(p);link(p)= null;goto done

/*:252*/
#line 5216 "hint.w"
;
done1:/*253:*/
#line 5224 "hint.w"

link(contrib_head)= link(p);link(p)= null;flush_node_list(p)

/*:253*/
#line 5217 "hint.w"
;
done:

/*:251*/
#line 5185 "hint.w"
;
}while(!(link(contrib_head)==null));
/*250:*/
#line 5193 "hint.w"

if(nest_ptr==0)tail= contrib_head;
else contrib_tail= contrib_head

/*:250*/
#line 5187 "hint.w"
;
return false;
}

/*:249*//*262:*/
#line 5347 "hint.w"

static void happend_insertion(pointer p)
{uint8_t n;
scaled delta,h,w;
pointer q,r;
if(page_contents==empty)freeze_page_specs(inserts_only);
n= subtype(p);r= page_ins_head;
while(n>=subtype(link(r)))r= link(r);
n= qo(n);
if(subtype(r)!=qi(n))
/*263:*/
#line 5379 "hint.w"

{q= get_node(page_ins_node_size);link(q)= link(r);link(r)= q;r= q;
subtype(r)= qi(n);type(r)= inserting;ensure_vbox(n);
if(box(n)==null)height(r)= 0;
else height(r)= height(box(n))+depth(box(n));
best_ins_ptr(r)= null;
q= skip(n);
if(count(n)==1000)h= height(r);
else h= x_over_n(height(r),1000)*count(n);
page_goal= page_goal-h-width(q);
page_so_far[2+stretch_order(q)]= page_so_far[2+stretch_order(q)]+stretch(q);
page_shrink= page_shrink+shrink(q);
if((shrink_order(q)!=normal)&&(shrink(q)!=0))
DBG(DBGTEX,"Infinite glue shrinkage inserted from stream %d",n);
}

/*:263*/
#line 5358 "hint.w"
;
if(type(r)==split_up)insert_penalties= insert_penalties+float_cost(p);
else{last_ins_ptr(r)= p;
delta= page_goal-page_total-page_depth+page_shrink;

if(count(n)==1000)h= height(p);
else h= x_over_n(height(p),1000)*count(n);
if(((h<=0)||(h<=delta))&&(height(p)+height(r)<=dimen(n)))
{page_goal= page_goal-h;height(r)= height(r)+height(p);
}
else/*264:*/
#line 5405 "hint.w"

{if(count(n)<=0)w= max_dimen;
else{w= page_goal-page_total-page_depth;
if(count(n)!=1000)w= x_over_n(w,count(n))*1000;
}
if(w> dimen(n)-height(r))w= dimen(n)-height(r);
q= vert_break(ins_ptr(p),w,depth(p));
height(r)= height(r)+best_height_plus_depth;
#ifdef STAT
if(tracing_pages> 0)/*265:*/
#line 5425 "hint.w"

{print_nl("% split");print_int(n);

print(" to ");print_scaled(w);
print_char(',');print_scaled(best_height_plus_depth);
print(" p=");
if(q==null)print_int(eject_penalty);
else if(type(q)==penalty_node)print_int(penalty(q));
else print_char('0');
}

/*:265*/
#line 5414 "hint.w"
;
#endif
#line 5416 "hint.w"

if(count(n)!=1000)
best_height_plus_depth= x_over_n(best_height_plus_depth,1000)*count(n);
page_goal= page_goal-best_height_plus_depth;
type(r)= split_up;broken_ptr(r)= q;broken_ins(r)= p;
if(q==null)insert_penalties= insert_penalties+eject_penalty;
else if(type(q)==penalty_node)insert_penalties= insert_penalties+penalty(q);
}

/*:264*/
#line 5369 "hint.w"
;
}
}

/*:262*//*266:*/
#line 5436 "hint.w"

static void hpack_page(void)
{
pointer p,q,r,s;
pointer prev_p;
uint8_t n;
bool wait;
pointer save_split_top_skip;
#if 0
print_str("\npage_head:\n");
show_box(link(page_head));
print_str("\nstream 0:\n");
show_box(streams[0].p);
print_str("\nstream 1:\n");
show_box(streams[1].p);
#endif
#line 5452 "hint.w"
 if(box(0)!=null)
{flush_node_list(box(0));box(0)= null;}
insert_penalties= 0;
save_split_top_skip= split_top_skip;
/*268:*/
#line 5504 "hint.w"

{r= link(page_ins_head);
while(r!=page_ins_head)
{if(best_ins_ptr(r)!=null)
{n= qo(subtype(r));ensure_vbox(n);
if(box(n)==null)box(n)= new_null_box();
p= box(n)+list_offset;
while(link(p)!=null)p= link(p);
last_ins_ptr(r)= p;
}
r= link(r);
}
}

/*:268*/
#line 5456 "hint.w"
;
q= hold_head;link(q)= null;prev_p= page_head;p= link(prev_p);
while(p!=best_page_break)
{if(type(p)==ins_node)
{/*270:*/
#line 5530 "hint.w"

{r= link(page_ins_head);
while(subtype(r)!=subtype(p))r= link(r);
if(best_ins_ptr(r)==null)wait= true;
else{wait= false;s= last_ins_ptr(r);link(s)= ins_ptr(p);
if(best_ins_ptr(r)==p)
/*271:*/
#line 5546 "hint.w"

{if(type(r)==split_up)
if((broken_ins(r)==p)&&(broken_ptr(r)!=null))
{while(link(s)!=broken_ptr(r))s= link(s);
link(s)= null;
split_top_skip= split_top_ptr(p);
ins_ptr(p)= prune_page_top(broken_ptr(r));
if(ins_ptr(p)!=null)
{temp_ptr= vpack(ins_ptr(p),natural);
height(p)= height(temp_ptr)+depth(temp_ptr);
free_node(temp_ptr,box_node_size);wait= true;
}
}
while(link(s)!=null)s= link(s);
best_ins_ptr(r)= null;
n= qo(subtype(r));
temp_ptr= list_ptr(box(n));
free_node(box(n),box_node_size);
streams[n].p= temp_ptr;
streams[n].t= s;
}

/*:271*/
#line 5537 "hint.w"

else{while(link(s)!=null)s= link(s);
last_ins_ptr(r)= s;
}
}
/*272:*/
#line 5568 "hint.w"

link(prev_p)= link(p);link(p)= null;
if(wait)
{link(q)= p;q= p;incr(insert_penalties);
}
else{delete_glue_ref(split_top_ptr(p));
free_node(p,ins_node_size);
}
p= prev_p


/*:272*/
#line 5543 "hint.w"
;
}

/*:270*/
#line 5461 "hint.w"
;
}
prev_p= p;p= link(prev_p);
}
split_top_skip= save_split_top_skip;
/*267:*/
#line 5482 "hint.w"

if(p!=null)
{if(link(contrib_head)==null)
{if(nest_ptr==0)tail= page_tail;
else contrib_tail= page_tail;}
link(page_tail)= link(contrib_head);
link(contrib_head)= p;
link(prev_p)= null;
}
streams[0].p= link(page_head);link(page_head)= null;page_tail= page_head;
streams[0].t= prev_p;
if(q!=hold_head)
{link(q)= link(contrib_head);
link(contrib_head)= link(hold_head);
}

/*:267*/
#line 5467 "hint.w"
;
/*269:*/
#line 5518 "hint.w"

r= link(page_ins_head);
while(r!=page_ins_head)
{q= link(r);free_node(r,page_ins_node_size);r= q;
}
link(page_ins_head)= page_ins_head

/*:269*/
#line 5468 "hint.w"
;
}

/*:266*//*273:*/
#line 5585 "hint.w"

static void hdisplay(pointer p,pointer a,bool l)
{
scaled x;
uint32_t offset= node_pos-node_pos1;
{scaled w;
scaled l;
scaled s;
pointer p;
pointer q;
internal_font_number f;
int n;
scaled v;
scaled d;

if(head==tail)
{pop_nest();w= -max_dimen;x= cur_list.hs_field;offset= 0;
}
else{pointer par_ptr;
hprune_unwanted_nodes();
par_ptr= link(head);
pop_nest();
store_map(par_ptr,node_pos,0);
line_break(display_widow_penalty,par_ptr);
x= cur_list.hs_field;
/*274:*/
#line 5619 "hint.w"

v= shift_amount(just_box)+2*dimen_def[quad_no];w= -max_dimen;
p= list_ptr(just_box);
while(p!=null)
{/*275:*/
#line 5636 "hint.w"

reswitch:if(is_char_node(p))
{f= font(p);d= char_width(f,character(p));
goto found;
}
switch(type(p)){
case hlist_node:case vlist_node:case rule_node:{d= width(p);goto found;
}
case ligature_node:/*137:*/
#line 3017 "hint.w"

{mem[lig_trick]= mem[lig_char(p)];link(lig_trick)= link(p);
p= lig_trick;goto reswitch;
}

/*:137*/
#line 5644 "hint.w"

case kern_node:case math_node:d= width(p);break;
case glue_node:/*276:*/
#line 5658 "hint.w"

{q= glue_ptr(p);d= width(q);
if(glue_sign(just_box)==stretching)
{if((glue_order(just_box)==stretch_order(q))&&
(stretch(q)!=0))
v= max_dimen;
}
else if(glue_sign(just_box)==shrinking)
{if((glue_order(just_box)==shrink_order(q))&&
(shrink(q)!=0))
v= max_dimen;
}
if(subtype(p)>=a_leaders)goto found;
}

/*:276*/
#line 5647 "hint.w"
break;
case whatsit_node:/*294:*/
#line 6383 "hint.w"

if(subtype(p)==image_node)
{d= image_width(p);goto found;}
else if(subtype(p)==utf_char_node)
{d= ft_char_width(utf_font(p),utf_char(p));goto found;}
else d= 0;

/*:294*/
#line 5648 "hint.w"
;break;
default:d= 0;
}

/*:275*/
#line 5624 "hint.w"
;
if(v<max_dimen)v= v+d;
goto not_found;
found:if(v<max_dimen)
{v= v+d;w= v;
}
else{w= max_dimen;goto done;
}
not_found:p= link(p);
}
done:

/*:274*/
#line 5612 "hint.w"
;
}

/*277:*/
#line 5676 "hint.w"

if(par_shape_ptr==null)
if((hang_indent!=0)&&
(((hang_after>=0)&&(prev_graf+2> hang_after))||
(prev_graf+1<-hang_after)))
{l= x-abs(hang_indent);
if(hang_indent> 0)s= hang_indent;else s= 0;
}
else{l= x;s= 0;
}
else{n= info(par_shape_ptr);
if(prev_graf+2>=n)p= par_shape_ptr+2*n;
else p= par_shape_ptr+2*(prev_graf+2);
s= mem[p-1].sc;l= mem[p].sc;
}

/*:277*/
#line 5615 "hint.w"
;
pre_display_size= w;display_width= l;display_indent= s;
}

/*:273*//*280:*/
#line 5720 "hint.w"

{/*279:*/
#line 5704 "hint.w"

pointer b;
scaled w;
scaled z;
scaled e;
scaled q;
scaled d;
scaled s;
small_number g1,g2;
pointer r;
pointer t;

/*:279*/
#line 5721 "hint.w"

adjust_tail= adjust_head;b= hpack(p,natural);p= list_ptr(b);
t= adjust_tail;adjust_tail= null;
w= width(b);z= display_width;s= display_indent;
if(a==null)
{e= 0;q= 0;
}
else{e= width(a);q= e+math_quad;
}
if(w+q> z)
/*281:*/
#line 5747 "hint.w"

{if((e!=0)&&((w-total_shrink[normal]+q<=z)||
(total_shrink[fil]!=0)||(total_shrink[fill]!=0)||
(total_shrink[filll]!=0)))
{free_node(b,box_node_size);
b= hpack(p,z-q,exactly);
}
else{e= 0;
if(w> z)
{free_node(b,box_node_size);
b= hpack(p,z,exactly);
}
}
w= width(b);
}

/*:281*/
#line 5732 "hint.w"
;
/*282:*/
#line 5771 "hint.w"

d= half(z-w);
if((e> 0)&&(d<2*e))
{d= half(z-w-e);
if(p!=null)if(!is_char_node(p))if(type(p)==glue_node)d= 0;
}

/*:282*/
#line 5734 "hint.w"
;
/*283:*/
#line 5784 "hint.w"

tail_append(new_penalty(pre_display_penalty));
store_map(tail,node_pos,offset);
if((d+s<=pre_display_size)||l)
{g1= above_display_skip_no;g2= below_display_skip_no;
}
else{g1= above_display_short_skip_no;
g2= below_display_short_skip_no;
}
if(l&&(e==0))
{shift_amount(a)= s;append_to_vlist(a,offset);
tail_append(new_penalty(inf_penalty));store_map(tail,node_pos,offset);
}
else{tail_append(new_glue(pointer_def[glue_kind][g1]));store_map(tail,node_pos,offset);}

/*:283*/
#line 5735 "hint.w"
;
/*284:*/
#line 5799 "hint.w"

if(e!=0)
{r= new_kern(z-w-e-d);
if(l)
{link(a)= r;link(r)= b;b= a;d= 0;
}
else{link(b)= r;link(r)= a;
}
b= hpack(b,natural);
}
shift_amount(b)= s+d;append_to_vlist(b,offset)

/*:284*/
#line 5736 "hint.w"
;
/*285:*/
#line 5811 "hint.w"

if((a!=null)&&(e==0)&&!l)
{tail_append(new_penalty(inf_penalty));
shift_amount(a)= s+z-width(a);
append_to_vlist(a,offset);
g2= 0;
}
if(t!=adjust_head)
{link(tail)= link(adjust_head);tail= t;
}
tail_append(new_penalty(post_display_penalty));
offset= (hpos-hstart)+1-node_pos;
store_map(tail,node_pos,offset);
if(g2> 0){tail_append(new_glue(pointer_def[glue_kind][g2]));store_map(tail,node_pos,offset);}

/*:285*/
#line 5737 "hint.w"
;
prev_graf= prev_graf+3;
cur_list.bs_pos= hpos+node_pos;
push_nest();
}
}

/*:280*/
#line 14796 "hint.w"


/*306:*/
#line 6611 "hint.w"

static int32_t hget_integer_def(uint8_t a)
{if(INFO(a)==1){int8_t n= HGET8;return n;}
else if(INFO(a)==2){int16_t n;HGET16(n);return n;}
else if(INFO(a)==4){int32_t n;HGET32(n);return n;}
else TAGERR(a);
return 0;
}

static int32_t hget_integer_ref(uint8_t n)
{REF_RNG(int_kind,n);
return integer_def[n];
}
/*:306*//*314:*/
#line 6669 "hint.w"

static scaled xdimen(Xdimen*x)
{return round(x->w+(double)x->h*(double)hhsize+(double)x->v*(double)hvsize);
}
static scaled hget_xdimen_ref(uint8_t n)
{REF_RNG(xdimen_kind,n);
return xdimen(xdimen_def+n);
}
/*:314*//*316:*/
#line 6687 "hint.w"


static pointer hget_glue_ref(uint8_t n)
{REF_RNG(glue_kind,n);
return pointer_def[glue_kind][n];
}

static pointer hget_glue_def(uint8_t a)
{pointer p;
if(INFO(a)==b000)
{p= hget_glue_ref(HGET8);
add_glue_ref(p);
}
else
{HGET_GLUE(INFO(a));}
return p;
}

pointer hget_param_glue(uint8_t n)
{REF_RNG(glue_kind,n);
return new_glue(pointer_def[glue_kind][n]);
}
/*:316*//*328:*/
#line 6884 "hint.w"

static void hget_font_def(uint8_t a,uint8_t i)
{char*t;
FontDef*f= font_def+i;
HGET_STRING(t);f->n= strdup(t);
DBG(DBGDEF,"Font %d: %s\n",i,t);
HGET32(f->s);RNG("Font size",f->s,1,0x7fffffff);
if(INFO(a)==b000)
{HGET16(f->m);RNG("Font metrics",f->m,3,max_section_no);}
else width_base[i]= f->m= 0;
HGET16(f->q);RNG("Font glyphs",f->q,3,max_section_no);
f->g= hget_glue_spec();
hff_hpos();
DBG(DBGDEF,"Start font parameters\n");
while(KIND(*hpos)!=font_kind)
{Kind k;
uint8_t n;
/*374:*/
#line 7666 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:374*/
#line 6901 "hint.w"

k= KIND(a);
n= HGET8;
DBG(DBGDEF,"Reading font parameter %d: %s\n",n,definition_name[k]);
if(k!=penalty_kind&&k!=kern_kind&&k!=ligature_kind&&
k!=disc_kind&&k!=glue_kind&&k!=language_kind&&k!=rule_kind&&k!=image_kind)
QUIT("Font parameter %d has invalid type %s",n,content_name[n]);
RNG("Font parameter",n,0,MAX_FONT_PARAMS);
f->p[n]= hget_definition(a);
/*375:*/
#line 7671 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:375*/
#line 6910 "hint.w"

}
DBG(DBGDEF,"End font definition\n");
}
/*:328*//*334:*/
#line 6959 "hint.w"

static void free_param_list(ParamDef*p)
{while(p!=NULL)
{ParamDef*q= p;
p= p->next;
free(q);
}
}
/*:334*//*335:*/
#line 6971 "hint.w"

static ParamDef*hget_param_list(uint8_t a)
{uint32_t s,t;
ParamDef*p= NULL;
uint8_t*list_start,*list_end;
list_start= hpos;
s= hget_list_size(INFO(a));
hget_size_boundary(INFO(a));
list_end= hpos+s;
if(list_end>=hend)
QUIT("list end after before stream end\n");
while(hpos<list_end)
{ParamDef*r;Param*q;
/*374:*/
#line 7666 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:374*/
#line 6984 "hint.w"

ALLOCATE(r,1,ParamDef);
q= &(r->p);
q->n= HGET8;
q->k= KIND(a);
DBG(DBGTAGS,"Defining %s %d\n",definition_name[KIND(a)],q->n);
if(KIND(a)==int_kind)q->v= hget_integer_def(a);
else if(KIND(a)==dimen_kind)q->v= hget_dimen_def(a);
else if(KIND(a)==glue_kind)q->v= hget_glue_def(a);
else TAGERR(a);
/*375:*/
#line 7671 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:375*/
#line 6994 "hint.w"

r->next= p;
p= r;
}
hget_size_boundary(INFO(a));
t= hget_list_size(INFO(a));
if(t!=s)
QUIT("List sizes at "SIZE_F" and "SIZE_F" do not match 0x%x != 0x%x",list_start-hstart,list_end-hstart,s,t);
return p;
}

static ParamDef*hget_param_list_node(void)
{if(KIND(*hpos)!=param_kind)return NULL;
else
{ParamDef*p;
/*374:*/
#line 7666 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:374*/
#line 7009 "hint.w"

p= hget_param_list(a);
/*375:*/
#line 7671 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:375*/
#line 7011 "hint.w"

return p;
}
}

ParamDef*hget_param_list_ref(uint8_t n)
{REF_RNG(param_kind,n);
return param_def[n];
}
/*:335*//*336:*/
#line 7046 "hint.w"

#define MAX_SAVE 100
#define SAVE_BOUNDARY 0xFF
static Param par_save[MAX_SAVE];
static int par_save_ptr= 0;

static void hset_param(uint8_t k,uint8_t n,int32_t v)
{Param*q;
if(par_save_ptr>=MAX_SAVE)QUIT("Parameter save stack overflow");
q= &(par_save[par_save_ptr++]);
q->k= k;
q->n= n;
if(q->k==int_kind)
{q->v= integer_def[q->n];integer_def[q->n]= v;}
else if(q->k==dimen_kind)
{q->v= dimen_def[q->n];dimen_def[q->n]= (scaled)v;}
else if(q->k==glue_kind)
{q->v= pointer_def[glue_kind][q->n];pointer_def[glue_kind][q->n]= (pointer)v;}
}

static void hset_param_list(ParamDef*p)
{hset_param(SAVE_BOUNDARY,0,0);
while(p!=NULL)
{hset_param(p->p.k,p->p.n,p->p.v);
p= p->next;
}
}

static void hrestore_param_list(void)
{
while(par_save_ptr> 0)
{Param*q;
q= &(par_save[--par_save_ptr]);
if(q->k==SAVE_BOUNDARY)return;
if(q->k==int_kind)
{integer_def[q->n]= q->v;}
else if(q->k==dimen_kind)
{dimen_def[q->n]= (scaled)q->v;}
else if(q->k==glue_kind)
{pointer_def[glue_kind][q->n]= (pointer)q->v;}
}
QUIT("Parameter save stack flow");
}
/*:336*//*341:*/
#line 7113 "hint.w"

static void hget_range_def(uint8_t a,uint8_t pg)
{uint32_t f,t;
max_range++;
REF_RNG(page_kind,pg);
REF_RNG(range_kind,max_range);
if(INFO(a)&b100)
{if(INFO(a)&b001)HGET32(f);else HGET16(f);}
else f= 0;
if(INFO(a)&b010)
{if(INFO(a)&b001)HGET32(t);else HGET16(t);}
else t= HINT_NO_POS;
range_def[max_range].pg= pg;
range_def[max_range].f= f;
range_def[max_range].t= t;
DBG(DBGRANGE,"Range *%d from 0x%x\n",pg,f);
DBG(DBGRANGE,"Range *%d to 0x%x\n",pg,t);
}
#if 0

static uint8_t hget_page_ref(uint32_t pos)
{int i;
for(i= 1;i<=max_ref[range_kind];i++)
if(range_def[i].f<=pos&&pos<range_def[i].t)return range_def[i].pg;
return 0;
}
#endif
#line 7140 "hint.w"
/*:341*//*346:*/
#line 7181 "hint.w"

static void hget_xdimen_def_node(Xdimen*x);

static bool hget_stream_def(StreamDef*s)
{if(KIND(*hpos)!=stream_kind||!(INFO(*hpos)&b100))
return false;
else
{uint8_t n;
/*374:*/
#line 7666 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:374*/
#line 7189 "hint.w"

DBG(DBGDEF,"Defining stream %d at "SIZE_F"\n",*hpos,hpos-hstart-1);
n= HGET8;REF_RNG(stream_kind,n);
s= s+n;
if(n> 0)
{if(INFO(a)==b100)/*347:*/
#line 7212 "hint.w"

{DBG(DBGDEF,"Defining normal stream %d at "SIZE_F"\n",*(hpos-1),hpos-hstart-2);
hget_xdimen_def_node(&(s->x));
HGET16(s->f);RNG("magnification factor",s->f,0,1000);
s->p= HGET8;if(s->p!=255)REF_RNG(stream_kind,s->p);
s->n= HGET8;if(s->n!=255)REF_RNG(stream_kind,s->n);
HGET16(s->r);RNG("split ratio",s->r,0,1000);
}
/*:347*/
#line 7194 "hint.w"

else if(INFO(a)==b101)QUIT("first stream not yet implemented");
else if(INFO(a)==b110)QUIT("last stream not yet implemented");
else if(INFO(a)==b111)QUIT("top stream not yet implemented");
s->b= hget_list_pointer();
hget_xdimen_def_node(&(s->w));
s->g= hget_glue_spec();
s->a= hget_list_pointer();
s->h= hget_glue_spec();
}
/*375:*/
#line 7671 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:375*/
#line 7204 "hint.w"

return true;
}
}
/*:346*//*353:*/
#line 7281 "hint.w"


static void hset_cur_page(void)
{int i;
cur_page= &(page_def[0]);
for(i= 1;i<=max_ref[page_kind];i++)
if(page_def[i].p>=cur_page->p)
cur_page= &(page_def[i]);
}

static void hskip_list(void);
static void hget_page_def(uint8_t a,uint8_t i)
{char*n;
cur_page= &(page_def[i]);
ALLOCATE(cur_page->s,max_ref[stream_kind]+1,StreamDef);
HGET_STRING(n);cur_page->n= strdup(n);
cur_page->p= HGET8;
cur_page->g= hget_glue_spec();
HGET32(cur_page->d);
hget_xdimen_def_node(&(cur_page->v));
hget_xdimen_def_node(&(cur_page->h));
cur_page->t= hpos-hstart;
hskip_list();
while(hget_stream_def(cur_page->s))continue;
}
/*:353*//*368:*/
#line 7480 "hint.w"

static void hset_default_colors(void)
{int i;
for(i= 0;i<=MAX_COLOR_DEFAULT;i++)
memcpy(color_def+i,color_defaults+i,sizeof(ColorSet));
}
/*:368*//*370:*/
#line 7561 "hint.w"

static pointer hget_ligature_ref(uint8_t n)
{REF_RNG(ligature_kind,n);
return copy_node_list(pointer_def[ligature_kind][n]);
}

static pointer hget_rule_ref(uint8_t n)
{REF_RNG(rule_kind,n);
return copy_node_list(pointer_def[rule_kind][n]);
}

static pointer hget_image_ref(uint16_t n)
{REF_RNG(image_kind,n);
return copy_node_list(pointer_def[image_kind][n]);
}

static pointer hget_color_ref(uint8_t n)
{pointer p;
p= get_node(color_node_size);
type(p)= whatsit_node;
if(n==0xFF)subtype(p)= end_color_node;
else
{subtype(p)= color_node;REF_RNG(color_kind,n);
}
color_ref(p)= n;
return p;
}


static pointer hget_hyphen_ref(uint8_t n)
{REF_RNG(disc_kind,n);
return copy_node_list(pointer_def[disc_kind][n]);
}

static pointer hget_leaders_ref(uint8_t n)
{REF_RNG(leaders_kind,n);
return copy_node_list(pointer_def[leaders_kind][n]);
}
/*:370*//*376:*/
#line 7681 "hint.w"

static void tag_mismatch(uint8_t a,uint8_t z,uint32_t a_pos,uint32_t z_pos)
{QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),a_pos,z_pos);
}
/*:376*//*387:*/
#line 7832 "hint.w"


static void hget_xdimen_def(Info i,Xdimen*x)
{switch(i)
{
case b000:
{int n= HGET8;
REF_RNG(xdimen_kind,n);
x->w= xdimen_def[n].w;
x->h= xdimen_def[n].h;
x->v= xdimen_def[n].v;
break;
}
case b001:HGET_XDIMEN(b001,*x);break;
case b010:HGET_XDIMEN(b010,*x);break;
case b011:HGET_XDIMEN(b011,*x);break;
case b100:HGET_XDIMEN(b100,*x);break;
case b101:HGET_XDIMEN(b101,*x);break;
case b110:HGET_XDIMEN(b110,*x);break;
case b111:HGET_XDIMEN(b111,*x);break;
default:
x->w= 0;x->h= x->v= 0.0;
}
}
static scaled hget_xdimen(Info i)
{Xdimen x;
hget_xdimen_def(i,&x);
return xdimen(&x);
}

static void tag_expected(uint8_t b,uint8_t a,uint32_t a_pos)
{QUIT("%s expected at 0x%x got [%s,%d]",NAME(b),a_pos,NAME(a),INFO(a));
}

static scaled hget_xdimen_node(void)
{scaled x= 0;
/*374:*/
#line 7666 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:374*/
#line 7868 "hint.w"

if(KIND(a)==xdimen_kind)
x= hget_xdimen(INFO(a));
else tag_expected(TAG(xdimen_kind,0),a,node_pos);
/*375:*/
#line 7671 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:375*/
#line 7872 "hint.w"

return x;
}

static void hget_xdimen_def_node(Xdimen*x)
{/*374:*/
#line 7666 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:374*/
#line 7877 "hint.w"

if(KIND(a)==xdimen_kind)
hget_xdimen_def(INFO(a),x);
else tag_expected(TAG(xdimen_kind,0),a,node_pos);
/*375:*/
#line 7671 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:375*/
#line 7881 "hint.w"

}
/*:387*//*388:*/
#line 7885 "hint.w"

static scaled hteg_xdimen(uint8_t a)
{Xdimen x;
switch(a)
{
case TAG(xdimen_kind,b000):return hget_xdimen_ref(HTEG8);
case TAG(xdimen_kind,b001):HTEG_XDIMEN(b001,x);break;
case TAG(xdimen_kind,b010):HTEG_XDIMEN(b010,x);break;
case TAG(xdimen_kind,b011):HTEG_XDIMEN(b011,x);break;
case TAG(xdimen_kind,b100):HTEG_XDIMEN(b100,x);break;
case TAG(xdimen_kind,b101):HTEG_XDIMEN(b101,x);break;
case TAG(xdimen_kind,b110):HTEG_XDIMEN(b110,x);break;
case TAG(xdimen_kind,b111):HTEG_XDIMEN(b111,x);break;
default:
x.w= 0;x.h= x.v= 0.0;
tag_expected(TAG(xdimen_kind,0),a,node_pos);
}
return xdimen(&x);
}

static scaled hteg_xdimen_node(void)
{scaled x= 0;
/*380:*/
#line 7751 "hint.w"

uint8_t a,z;
z= HTEG8;DBGTAG(z,hpos);
/*:380*/
#line 7907 "hint.w"

if(KIND(z)==xdimen_kind)
x= hteg_xdimen(z);
else
tag_expected(TAG(xdimen_kind,0),z,node_pos);
/*381:*/
#line 7756 "hint.w"

a= HTEG8;DBGTAG(a,hpos);
if(z!=a)tag_mismatch(a,z,hpos-hstart,node_pos);
/*:381*/
#line 7912 "hint.w"

return x;
}
/*:388*//*395:*/
#line 7972 "hint.w"

static pointer new_utf_char(uint8_t f,int c)
{pointer p;
p= get_node(utf_char_node_size);
type(p)= whatsit_node;subtype(p)= utf_char_node;
utf_font_char(p)= (f<<24)+c;
return p;
}
/*:395*//*406:*/
#line 8090 "hint.w"

static pointer hteg_rule_node(void)
{pointer q= null;
/*380:*/
#line 7751 "hint.w"

uint8_t a,z;
z= HTEG8;DBGTAG(z,hpos);
/*:380*/
#line 8093 "hint.w"

if(KIND(z)==rule_kind){HTEG_RULE(INFO(z));q= p;}
else tag_expected(TAG(rule_kind,0),z,node_pos);
/*381:*/
#line 7756 "hint.w"

a= HTEG8;DBGTAG(a,hpos);
if(z!=a)tag_mismatch(a,z,hpos-hstart,node_pos);
/*:381*/
#line 8096 "hint.w"

return q;
}
/*:406*//*412:*/
#line 8159 "hint.w"

static pointer hget_glue_spec(void)
{pointer p= null;
uint8_t a,z;
if(hpos>=hend||KIND(*hpos)!=glue_kind)
{p= zero_glue;incr(glue_ref_count(p));}
else
{node_pos= hpos-hstart;
HGETTAG(a);
if(INFO(a)==b000)
{p= hget_glue_ref(HGET8);incr(glue_ref_count(p));}
else
{HGET_GLUE(INFO(a));}
/*375:*/
#line 7671 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:375*/
#line 8172 "hint.w"

}
return p;
}

static pointer spec2glue(pointer q)
{pointer p;
p= get_node(small_node_size);type(p)= glue_node;subtype(p)= normal;
leader_ptr(p)= null;glue_ptr(p)= q;
return p;
}

static pointer hget_glue_node(void)
{return spec2glue(hget_glue_spec());
}
/*:412*//*413:*/
#line 8189 "hint.w"

static pointer hteg_glue_spec(void)
{pointer p= null;
uint8_t a,z;
if(hpos<=hstart)return null;
if(KIND(*(hpos-1))!=glue_kind)return null;
z= HTEG8,DBGTAG(z,hpos);
if(INFO(z)==b000)p= hget_glue_ref(HTEG8);
else
{HTEG_GLUE(INFO(z));}
/*381:*/
#line 7756 "hint.w"

a= HTEG8;DBGTAG(a,hpos);
if(z!=a)tag_mismatch(a,z,hpos-hstart,node_pos);
/*:381*/
#line 8199 "hint.w"

return p;
}


static pointer hteg_glue_node(void)
{pointer p= hteg_glue_spec();
if(p!=null)return spec2glue(p);
else return new_glue(zero_glue);
}
/*:413*//*414:*/
#line 8224 "hint.w"

static pointer hget_node_list(uint32_t s)
{uint8_t*list_end= hpos+s;
pointer p;
push_nest();
cur_list.bs_pos= NULL;
while(hpos<list_end)
hget_content();
if(needs_bs)
QUIT("Unexpected trailing baseline node");
p= link(head);
pop_nest();
return p;
}

static pointer hget_text_list(uint32_t s);
static pointer hget_list_pointer(void)
{pointer p= null;
uint32_t s,t;
if(KIND(*hpos)==list_kind)
{/*374:*/
#line 7666 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:374*/
#line 8244 "hint.w"

if((INFO(a)&b011)==0)
HGET8;
else
{s= hget_list_size(INFO(a));
hget_size_boundary(INFO(a));
if((INFO(a)&b100)==0)
p= hget_node_list(s);
else
p= hget_text_list(s);
hget_size_boundary(INFO(a));
t= hget_list_size(INFO(a));
if(t!=s)
QUIT("List sizes at 0x%x and "SIZE_F" do not match 0x%x != 0x%x",
node_pos+1,hpos-hstart-s-1,s,t);
}
/*375:*/
#line 7671 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:375*/
#line 8260 "hint.w"

}
return p;
}
/*:414*//*415:*/
#line 8271 "hint.w"


static void hskip_list(void)
{if(KIND(*hpos)==list_kind||KIND(*hpos)==param_kind)
{Info i;
uint8_t a;
HGETTAG(a);
i= INFO(a)&0x3;
if(i==0)hpos= hpos+2;
else
{uint32_t s= hget_list_size(INFO(a));
if(i==3)i= 4;
hpos= hpos+(1+s+1+i+1);
}
}
}

static void hskip_list_back(void)
{if(KIND(*(hpos-1))==list_kind||KIND(*(hpos-1))==param_kind)
{Info i;
uint8_t z;
z= HTEG8;
i= INFO(z)&0x3;
if(i==0)hpos= hpos-2;
else
{uint32_t s= hteg_list_size(INFO(z));
if(i==3)i= 4;
hpos= hpos-(1+s+1+i+1);
}
}
}

static pointer hteg_list_pointer(void)
{uint8_t*list_start;
pointer p;
hskip_list_back();
list_start= hpos;
p= hget_list_pointer();
hpos= list_start;
return p;
}
/*:415*//*416:*/
#line 8321 "hint.w"

#if 0
static int32_t hteg_integer_def(uint8_t z)
{if(INFO(z)==1){int8_t n= HTEG8;return n;}
else if(INFO(z)==2){int16_t n;HTEG16(n);return n;}
else if(INFO(z)==4){int32_t n;HTEG32(n);return n;}
else TAGERR(z);
return 0;
}

static ParamDef*hteg_param_list(uint8_t z)
{uint32_t s,t;
ParamDef*p= NULL;
uint8_t*list_start,*list_end;
list_end= hpos;
s= hteg_list_size(INFO(z));
hteg_size_boundary(INFO(z));
list_start= hpos-s;
if(list_start<=hstart)
QUIT("list start before stream start\n");
while(list_start<hpos)
{ParamDef*r;Param*q;
/*380:*/
#line 7751 "hint.w"

uint8_t a,z;
z= HTEG8;DBGTAG(z,hpos);
/*:380*/
#line 8343 "hint.w"

ALLOCATE(r,1,ParamDef);
q= &(r->p);
q->k= KIND(z);
if(KIND(z)==int_kind)q->i= hteg_integer_def(a);
else if(KIND(a)==dimen_kind)HTEG32(q->d);
else if(KIND(a)==glue_kind){pointer p;HTEG_GLUE(INFO(z));q->g= p;}
else TAGERR(a);
q->n= HTEG8;
DBG(DBGTAGS,"Defining %s %d\n",definition_name[KIND(z)],q->n);
/*381:*/
#line 7756 "hint.w"

a= HTEG8;DBGTAG(a,hpos);
if(z!=a)tag_mismatch(a,z,hpos-hstart,node_pos);
/*:381*/
#line 8353 "hint.w"

r->next= p;
p= r;
}
hteg_size_boundary(INFO(z));
t= hteg_list_size(INFO(z));
if(t!=s)
QUIT("List sizes at "SIZE_F" and "SIZE_F" do not match 0x%x != 0x%x",list_start-hstart,list_end-hstart,s,t);
return p;
}
#endif
#line 8364 "hint.w"

static ParamDef*hteg_param_list_node(void)
{ParamDef*p;
uint8_t*list_start;
hskip_list_back();
list_start= hpos;
p= hget_param_list_node();
hpos= list_start;
return p;
}
/*:416*//*423:*/
#line 8480 "hint.w"

static pointer hteg_hbox_node(void)
{/*380:*/
#line 7751 "hint.w"

uint8_t a,z;
z= HTEG8;DBGTAG(z,hpos);
/*:380*/
#line 8482 "hint.w"

if(KIND(z)!=hbox_kind)tag_expected(TAG(hbox_kind,0),z,node_pos);
{pointer p;
HTEG_BOX(INFO(z));
/*381:*/
#line 7756 "hint.w"

a= HTEG8;DBGTAG(a,hpos);
if(z!=a)tag_mismatch(a,z,hpos-hstart,node_pos);
/*:381*/
#line 8486 "hint.w"

return p;
}
}
static pointer hteg_vbox_node(void)
{/*380:*/
#line 7751 "hint.w"

uint8_t a,z;
z= HTEG8;DBGTAG(z,hpos);
/*:380*/
#line 8491 "hint.w"

if(KIND(z)!=vbox_kind)tag_expected(TAG(vbox_kind,0),z,node_pos);
{pointer p;
HTEG_BOX(INFO(z));
/*381:*/
#line 7756 "hint.w"

a= HTEG8;DBGTAG(a,hpos);
if(z!=a)tag_mismatch(a,z,hpos-hstart,node_pos);
/*:381*/
#line 8495 "hint.w"

type(p)= vlist_node;
return p;
}
}

/*:423*//*428:*/
#line 8574 "hint.w"

static void hset(pointer p,
uint8_t sto,scaled st,uint8_t sho,scaled sh,scaled w)
{scaled x;
x= width(p);
width(p)= w;

x= w-x;
if(x==0)
{glue_sign(p)= normal;glue_order(p)= normal;
glue_set(p)= 0.0;
}
else if(x> 0)
{glue_order(p)= sto;glue_sign(p)= stretching;
if(st!=0)
glue_set(p)= (float32_t)(x/(double)st);
else
{glue_sign(p)= normal;
glue_set(p)= 0.0;
}
}
else
{glue_order(p)= sho;glue_sign(p)= shrinking;
if(sh!=0)
glue_set(p)= (float32_t)((-x)/(double)sh);
else
{glue_sign(p)= normal;
glue_set(p)= 0.0;
}
if((sh<-x)&&(sho==normal)&&(list_ptr(p)!=null))
glue_set(p)= 1.0;
}
}
/*:428*//*429:*/
#line 8617 "hint.w"


static void vset(pointer p,uint8_t sto,scaled st,
uint8_t sho,scaled sh,scaled h)
{scaled x;
type(p)= vlist_node;
x= height(p);
height(p)= h;
x= h-x;
if(x==0)
{glue_sign(p)= normal;glue_order(p)= normal;
glue_set(p)= 0.0;
}
else if(x> 0)
{glue_order(p)= sto;glue_sign(p)= stretching;
if(st!=0)
glue_set(p)= (float32_t)(x/(double)st);
else
{glue_sign(p)= normal;
glue_set(p)= 0.0;
}
}
else
{glue_order(p)= sho;glue_sign(p)= shrinking;
if(sh!=0)
glue_set(p)= (float32_t)((-x)/(double)sh);
else
{glue_sign(p)= normal;
glue_set(p)= 0.0;
}
}
if(depth(p)==MAX_DIMEN+1)
{if(list_ptr(p)!=null&&(type(list_ptr(p))==hlist_node||type(list_ptr(p))==vlist_node||type(list_ptr(p))==rule_node))
{h= height(list_ptr(p));
depth(p)= height(p)-h;
height(p)= h;
}
else
{depth(p)= depth(p)+height(p);height(p)= 0;}
DBG(DBGTEX,"vset top node adjusted height=%f depth=%f\n",height(p)/(double)ONE,depth(p)/(double)ONE);
}
}
/*:429*//*434:*/
#line 8732 "hint.w"

static pointer vtop(pointer p,scaled h,small_number m,scaled d)
{d= d^0x40000000;
p= vpackage(p,h,m,d);
if(list_ptr(p)!=null&&(type(list_ptr(p))==hlist_node||type(list_ptr(p))==vlist_node||type(list_ptr(p))==rule_node))
{h= height(list_ptr(p));
depth(p)= depth(p)+height(p)-h;
height(p)= h;
}
else
{depth(p)= depth(p)+height(p);height(p)= 0;}
DBG(DBGTEX,"vpack top node adjusted height=%f depth=%f\n",height(p)/(double)ONE,depth(p)/(double)ONE);
return p;
}
/*:434*//*447:*/
#line 8890 "hint.w"

static pointer hget_text_list(uint32_t s)
{pointer p= null;
pointer*pp= &p;
uint8_t*t= hpos+s;
while(hpos<t){*pp= new_character(0,hget_utf8());pp= &link(*pp);}
return p;
}
/*:447*//*456:*/
#line 8997 "hint.w"

#if 0

static pointer hget_disc_node(void)
{/*374:*/
#line 7666 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:374*/
#line 9001 "hint.w"

if(KIND(a)!=disc_kind||INFO(a)==b000)
tag_expected(TAG(disc_kind,1),a,node_pos);
{
HGET_DISC(INFO(a));
/*375:*/
#line 7671 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:375*/
#line 9006 "hint.w"

return p;
}
}
#endif
#line 9011 "hint.w"
/*:456*//*460:*/
#line 9077 "hint.w"

static void transplant_post_break_list(void)
{pointer r,q= link(head);
int t= replace_count(q);
pointer s= post_break(q);
r= q;
while(t> 0&&r!=null){r= link(r);t--;}
if(s!=null)
{while(link(s)!=null)s= link(s);
link(s)= link(r);link(r)= post_break(q);post_break(q)= null;
}
q= link(r);
if(r!=head)
{link(r)= null;flush_node_list(link(head));
link(head)= q;
}
}
static void transplant_pre_break_list(void)
{pointer q= tail;
set_replace_count(q,0);
link(q)= pre_break(q);
pre_break(q)= null;
while(link(q)!=null)q= link(q);
tail= q;
}


static void hprune_unwanted_nodes(void)
{pointer q,r= head;
while(true){q= link(r);
if(q==null)goto done;
if(is_char_node(q))goto done;
if(non_discardable(q))goto done;
if(type(q)==kern_node&&subtype(q)!=explicit)goto done;
r= q;
}
done:if(r!=head)
{link(r)= null;flush_node_list(link(head));
link(head)= q;
}
}
/*:460*//*462:*/
#line 9150 "hint.w"

pointer hget_paragraph_all(scaled x)
{uint8_t*to;
/*463:*/
#line 9164 "hint.w"

pointer par_ptr= null;
if(KIND(*hpos)==list_kind)
{uint32_t s,t;
/*374:*/
#line 7666 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:374*/
#line 9168 "hint.w"

if((INFO(a)&b011)==0)
HGET8;
else if(INFO(a)&b100)
QUIT("Text in paragraph not yet implemented");
else
{uint8_t*list_end;
s= hget_list_size(INFO(a));
hget_size_boundary(INFO(a));
list_end= hpos+s;
cur_list.hs_field= x;
push_nest();
cur_list.bs_pos= NULL;

/*:463*/
#line 9153 "hint.w"

to= list_end;
/*464:*/
#line 9184 "hint.w"

while(hpos<to)
{hget_content();
if(nest_ptr==1)
{pointer p= tail;
if(p!=head&&!is_char_node(p)&&
(type(p)==glue_node||type(p)==kern_node||type(p)==penalty_node
||type(p)==disc_node||type(p)==math_node))
store_map(p,node_pos,0);
}
}

/*:464*/
#line 9155 "hint.w"

/*465:*/
#line 9198 "hint.w"

if(head!=tail)
{par_ptr= link(head);
store_map(par_ptr,node_pos,0);
if(needs_bs)
QUIT("Unexpected trailing baseline node");
}
pop_nest();
}
hget_size_boundary(INFO(a));
t= hget_list_size(INFO(a));
if(t!=s)
QUIT("List sizes at 0x%x and "SIZE_F" do not match 0x%x != 0x%x",
node_pos+1,hpos-hstart-s-1,s,t);
/*375:*/
#line 7671 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:375*/
#line 9212 "hint.w"

}



/*:465*/
#line 9156 "hint.w"

return par_ptr;
}

/*:462*//*466:*/
#line 9223 "hint.w"

pointer hget_paragraph_final(scaled x,uint8_t*from)
{uint8_t*to;
int par_color,par_label_ref;
/*463:*/
#line 9164 "hint.w"

pointer par_ptr= null;
if(KIND(*hpos)==list_kind)
{uint32_t s,t;
/*374:*/
#line 7666 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:374*/
#line 9168 "hint.w"

if((INFO(a)&b011)==0)
HGET8;
else if(INFO(a)&b100)
QUIT("Text in paragraph not yet implemented");
else
{uint8_t*list_end;
s= hget_list_size(INFO(a));
hget_size_boundary(INFO(a));
list_end= hpos+s;
cur_list.hs_field= x;
push_nest();
cur_list.bs_pos= NULL;

/*:463*/
#line 9227 "hint.w"

/*467:*/
#line 9247 "hint.w"

par_color= -1;par_label_ref= -1;
while(hpos<from)
{if(hpos[0]==TAG(color_kind,b000))par_color= hpos[1];
else if(KIND(hpos[0])==link_kind)
{if(INFO(hpos[0])&b010)
{par_label_ref= hget_label_ref();par_color= hget_link_color();}
else
{par_color= hget_link_color();
par_label_ref= -1;
}
}
if(par_color==0xFF)par_color= -1;
hff_hpos();
}
/*:467*/
#line 9228 "hint.w"

hpos= from;to= list_end;
/*464:*/
#line 9184 "hint.w"

while(hpos<to)
{hget_content();
if(nest_ptr==1)
{pointer p= tail;
if(p!=head&&!is_char_node(p)&&
(type(p)==glue_node||type(p)==kern_node||type(p)==penalty_node
||type(p)==disc_node||type(p)==math_node))
store_map(p,node_pos,0);
}
}

/*:464*/
#line 9230 "hint.w"

if(link(head)!=null&&!is_char_node(link(head)))
{if(type(link(head))==disc_node)
transplant_post_break_list();
else
hprune_unwanted_nodes();
}
/*465:*/
#line 9198 "hint.w"

if(head!=tail)
{par_ptr= link(head);
store_map(par_ptr,node_pos,0);
if(needs_bs)
QUIT("Unexpected trailing baseline node");
}
pop_nest();
}
hget_size_boundary(INFO(a));
t= hget_list_size(INFO(a));
if(t!=s)
QUIT("List sizes at 0x%x and "SIZE_F" do not match 0x%x != 0x%x",
node_pos+1,hpos-hstart-s-1,s,t);
/*375:*/
#line 7671 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:375*/
#line 9212 "hint.w"

}



/*:465*/
#line 9237 "hint.w"

/*468:*/
#line 9267 "hint.w"

if(par_ptr!=null)
{if(par_label_ref>=0)
{pointer p;
p= get_node(link_node_size);type(p)= whatsit_node;
subtype(p)= start_link_node;label_ref(as_label(p))= par_label_ref;
link(p)= par_ptr;
if(par_color>=0)color_ref(as_color(p))= par_color;
else color_ref(as_color(p))= 0xFF;
par_ptr= p;
}
else if(par_color>=0)
{pointer p;
p= get_node(color_node_size);
type(p)= whatsit_node;subtype(p)= color_node;
color_ref(p)= par_color;
link(p)= par_ptr;
par_ptr= p;
}
}
/*:468*/
#line 9238 "hint.w"

return par_ptr;
}
/*:466*//*474:*/
#line 9369 "hint.w"

pointer hget_paragraph(scaled x,uint32_t offset,ParamDef*q)
{
pointer p,par_head;
ParamDef*save_lbp= line_break_params;
par_head= tail;
line_break_params= q;
if(offset==0)
{prev_graf= 0;
p= hget_paragraph_all(x);
}
else
{prev_graf= 3;
p= hget_paragraph_final(x,hstart+node_pos+offset);
}
if(p!=null)
line_break(hget_integer_ref(widow_penalty_no),p);
line_break_params= save_lbp;
return par_head;
}
/*:474*//*477:*/
#line 9423 "hint.w"

static void hteg_paragraph(Info i)
{scaled x= 0;
ParamDef*q= null;
pointer par_head;
uint8_t*bs_pos= cur_list.bs_pos;
scaled ph= prev_height;
uint8_t*list_start,*par_start;
hskip_list_back();
list_start= hpos;
if(INFO(i)&b010)q= hteg_param_list_node();
else if(INFO(i)!=b100)q= hget_param_list_ref(HTEG8);
if(INFO(i)&b100)x= hteg_xdimen_node();else x= hget_xdimen_ref(HTEG8);
if(INFO(i)==b100)q= hget_param_list_ref(HTEG8);
par_start= hpos;
node_pos= par_start-hstart-1;
hpos= list_start;
cur_list.bs_pos= NULL;
par_head= hget_paragraph(x,0,q);
/*478:*/
#line 9455 "hint.w"

{pointer p,r,par_tail;
p= null;
r= par_tail= link(par_head);

tail= par_head;
link(tail)= null;
while(r!=null)
{pointer q= link(r);
link(r)= p;
p= r;
r= q;
}
cur_list.bs_pos= bs_pos;
prev_height= ph;
hprepend_to_vlist(p);
tail= par_tail;
if(type(tail)==hlist_node||type(tail)==vlist_node)
prev_height= height(tail);
}
/*:478*/
#line 9442 "hint.w"

hpos= par_start;
}
/*:477*//*492:*/
#line 9663 "hint.w"

static void hset_stream_params(pointer p,ParamDef*q)
{pointer s;
hset_param_list(q);
float_cost(p)= integer_def[floating_penalty_no];
depth(p)= dimen_def[split_max_depth_no];
split_top_ptr(p)= pointer_def[glue_kind][split_top_skip_no];
add_glue_ref(split_top_ptr(p));
hrestore_param_list();
s= vpack(ins_ptr(p),natural);
height(p)= height(s)+depth(s);
ins_ptr(p)= list_ptr(s);
list_ptr(s)= null;flush_node_list(s);
}
/*:492*//*507:*/
#line 9847 "hint.w"

static int hget_label_ref(void)
{if(INFO(hpos[0])&b001)return(hpos[1]<<8)+hpos[2];
else return hpos[1];
}
static int hget_link_color(void)
{if(INFO(hpos[0]&b100))
{if(INFO(hpos[0]&b001))return hpos[3];
else return hpos[2];
}
else
{if(INFO(hpos[0]&b010))return 1;else return 0xFF;}
}
/*:507*//*510:*/
#line 9891 "hint.w"

pointer skip(uint8_t n)
{return cur_page->s[n].g;}
pointer*box_ptr(uint8_t n)
{return&streams[n].p;}
int count(uint8_t n)
{return cur_page->s[n].f;}
scaled dimen(uint8_t n)
{return xdimen(&cur_page->s[n].x);}

/*:510*//*547:*/
#line 10694 "hint.w"

static void hset_margins(void)
{if(cur_page==&(page_def[0])){
offset_h= page_h/8-0x48000;
if(offset_h<0)offset_h= 0;
offset_v= page_v/8-0x48000;
if(offset_v<0)offset_v= 0;
if(offset_h> offset_v)offset_h= offset_v;
else offset_v= offset_h;
hhsize= page_h-2*offset_h;
hvsize= page_v-2*offset_v;
if(hhsize<=0)hhsize= page_h,offset_h= 0;
if(hvsize<=0)hvsize= page_v,offset_v= 0;
}
else
{hhsize= round((double)(page_h-cur_page->h.w)/(double)cur_page->h.h);
if(hhsize> page_h)hhsize= page_h;
hvsize= round((double)(page_v-cur_page->v.w)/(double)cur_page->v.v);
if(hvsize> page_v)hvsize= page_v;
offset_h= (page_h-hhsize)/2;
offset_v= (page_v-hvsize)/2;
}
}
/*:547*//*549:*/
#line 10726 "hint.w"

static void houtput_template(pointer p)
{pointer q,r;
if(p==null)return;
p= vpackage(p,hvsize,exactly,page_max_depth);
if(offset_v!=0)
{r= new_kern(offset_v);
link(r)= p;
}
else
r= p;
q= new_null_box();
type(q)= vlist_node;
width(q)= width(p)+offset_h;
height(q)= height(p)+offset_v;depth(q)= depth(p);
list_ptr(q)= r;
shift_amount(p)+= offset_h;
streams[0].p= q;
}
/*:549*//*555:*/
#line 10842 "hint.w"

uint64_t hlocation(pointer p)
{uint64_t h= PAGE_LOC(map[p],map[p+1]);
while(h==0&&link(p)!=null)
{p= link(p);h= PAGE_LOC(map[p],map[p+1]);}
return h;
}
/*:555*//*557:*/
#line 10887 "hint.w"

#define NEXT_PAGE(X) (X= (X+1)&(MAX_PAGE_POS-1))
#define PREV_PAGE(X) (X= (X-1)&(MAX_PAGE_POS-1))

static void hloc_clear(void)
{lo_loc= hi_loc= cur_loc;PREV_PAGE(lo_loc);NEXT_PAGE(hi_loc);
}
/*:557*//*562:*/
#line 10973 "hint.w"


static void hloc_set_next(pointer p)
{int i= cur_loc;
uint64_t h= hlocation(p);
if(h==page_loc[cur_loc])return;

NEXT_PAGE(i);
if(i==hi_loc)
{if(hi_loc==lo_loc)
NEXT_PAGE(lo_loc);
NEXT_PAGE(hi_loc);
page_loc[i]= h;
}
else if(h!=page_loc[i])
{page_loc[i]= h;
NEXT_PAGE(i);
hi_loc= i;
}
DBG(DBGPAGE,"loc_set_next: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
}
/*:562*//*563:*/
#line 11010 "hint.w"

static void hloc_set_prev(pointer p)
{int i= cur_loc;
uint64_t h= hlocation(p);
PREV_PAGE(i);
if(i==lo_loc)
{if(lo_loc==hi_loc)
PREV_PAGE(hi_loc);
PREV_PAGE(lo_loc);
page_loc[i]= h;
}
else if(h!=page_loc[i])
{page_loc[i]= h;
lo_loc= i;
PREV_PAGE(lo_loc);
}
hi_loc= cur_loc;
NEXT_PAGE(hi_loc);
cur_loc= i;
DBG(DBGPAGE,"loc_set_prev: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
}
/*:563*//*589:*/
#line 11635 "hint.w"

static bool trv_ignore= false;
static bool trv_skip_space= false;
static void(*trv_stream)(uint32_t c);
static void trv_init(void(*f)(uint32_t c))
{trv_ignore= false;trv_skip_space= false;trv_stream= f;}

static void trv_char(uint32_t c)
{if(c==0x20)trv_skip_space= true;
else
{if(trv_skip_space)
{trv_skip_space= false;trv_stream(0x20);}
trv_stream(c);
}
}

static void trv_vlist(pointer p);

static void trv_hlist(pointer p)
{while(p!=null)
{if(is_char_node(p))
{if(!trv_ignore)trv_char(character(p));
}
else switch(type(p))
{case hlist_node:if(list_ptr(p)!=null)trv_hlist(list_ptr(p));break;
case vlist_node:if(list_ptr(p)!=null)trv_vlist(list_ptr(p));break;
case ligature_node:
if(!trv_ignore)
{pointer q= lig_ptr(p);
while(q!=null)
{trv_char(character(q));
q= link(q);
}
}
break;
case glue_node:
if(!trv_ignore)trv_skip_space= true;
break;
case whatsit_node:
if(subtype(p)==ignore_node)
{if(ignore_info(p)==1)
{trv_hlist(ignore_list(p));
trv_ignore= true;
}
else
trv_ignore= false;
}
else if(subtype(p)==utf_char_node)
{if(!trv_ignore)trv_char(utf_char(p));
}
break;
default:break;
}
p= link(p);
}
}

static void trv_vlist(pointer p)
{while(p!=null)
{switch(type(p))
{case hlist_node:if(list_ptr(p)!=null)trv_hlist(list_ptr(p));
if(!trv_ignore)trv_skip_space= true;
break;
case vlist_node:if(list_ptr(p)!=null)trv_vlist(list_ptr(p));break;
default:break;
}
p= link(p);
}
}
/*:589*//*590:*/
#line 11712 "hint.w"

static int trv_string_size= 0;
static char trv_string[256];
#define TRV_UTF8(C) (trv_string[trv_string_size++]= (C))
static void trv_string_collect(uint32_t c)
{if(trv_string_size<256-5)
{if(c<0x80)
TRV_UTF8(c);
else if(c<0x800)
{TRV_UTF8(0xC0|(c>>6));TRV_UTF8(0x80|(c&0x3F));}
else if(c<0x10000)
{TRV_UTF8(0xE0|(c>>12));TRV_UTF8(0x80|((c>>6)&0x3F));TRV_UTF8(0x80|(c&0x3F));}
else if(c<0x200000)
{TRV_UTF8(0xF0|(c>>18));TRV_UTF8(0x80|((c>>12)&0x3F));
TRV_UTF8(0x80|((c>>6)&0x3F));TRV_UTF8(0x80|(c&0x3F));}
else
RNG("character code in outline",c,0,0x1FFFFF);
}
}

static char*hlist_to_string(pointer p)
{trv_string_size= 0;
trv_init(trv_string_collect);
trv_hlist(p);
trv_string[trv_string_size]= 0;
return trv_string;
}
/*:590*//*630:*/
#line 12618 "hint.w"

static void hget_font_metrics(void)
{int f;
font_ptr= max_ref[font_kind];
for(f= 0;f<=max_ref[font_kind];f++)
if(font_def[f].m!=0)
{hget_section(font_def[f].m);
read_font_info(f,font_def[f].n,font_def[f].s);
}
else
font_size[f]= font_def[f].s;
}
/*:630*//*643:*/
#line 13035 "hint.w"

#if 0
static FT_UInt ft_glyph(FT_Face ft_face,int c)
{FT_UInt ft_gid;
ft_gid= FT_Get_Char_Index(ft_face,c);
return ft_gid;
}
#endif
#line 13043 "hint.w"

#ifdef DEBUG
static bool ft_exists(internal_font_number f,int c)
{FT_Face ft_face;
if(font_def[f].ff==no_format)hload_font(f);
ft_face= font_def[f].ft_face;
if(ft_face==NULL)
ft_face= ft_load_font_face(f);
if(ft_face==NULL)return false;
return FT_Get_Char_Index(ft_face,c)!=0;
}
#endif
#line 13055 "hint.w"

static scaled ft_glyph_width(FT_Face ft_face,FT_UInt ft_gid,scaled s)
{FT_Fixed a;
scaled w;
ft_err= FT_Get_Advance(ft_face,ft_gid,FT_LOAD_NO_SCALE,&a);
if(ft_err!=0)return 0;
w= (scaled)((double)s*(double)a/(double)ft_face->units_per_EM+0.5);
return w;
}

static scaled ft_width(FT_Face ft_face,int c,scaled s)
{FT_UInt ft_gid;
ft_gid= FT_Get_Char_Index(ft_face,c);
if(ft_gid==0)return 0;
return ft_glyph_width(ft_face,ft_gid,s);
}
/*:643*//*644:*/
#line 13083 "hint.w"

static FT_Error ft_glyph_bbox(FT_Face ft_face,FT_UInt ft_gid,FT_BBox*ft_bbox)
{FT_Glyph ft_glyph;
ft_err= FT_Load_Glyph(ft_face,ft_gid,FT_LOAD_NO_SCALE);
if(ft_err!=0)return ft_err;
ft_err= FT_Get_Glyph(ft_face->glyph,&ft_glyph);
if(ft_err!=0)return ft_err;
FT_Glyph_Get_CBox(ft_glyph,FT_GLYPH_BBOX_UNSCALED,ft_bbox);
return 0;
}

static void ft_glyph_height_depth(FT_Face ft_face,FT_UInt ft_gid,
scaled*h,scaled*d,scaled s)
{FT_BBox ft_bbox;
*h= *d= 0;
ft_err= ft_glyph_bbox(ft_face,ft_gid,&ft_bbox);
if(ft_err!=0)
return;
if(ft_bbox.yMax> 0)
*h= (scaled)((double)s*(double)(ft_bbox.yMax)/(double)ft_face->units_per_EM+0.5);
if(ft_bbox.yMin<0)
*d= (scaled)((double)s*(double)(-ft_bbox.yMin)/(double)ft_face->units_per_EM+0.5);
}

/*:644*//*645:*/
#line 13116 "hint.w"

#if 0
static int ft_last(FT_Face ft_face)
{return 0x10FFFF;}

static int ft_first(FT_Face ft_face)
{FT_UInt ft_gid;
FT_ULong c;
c= FT_Get_First_Char(ft_face,&ft_gid);
if(ft_gid==0)
return ft_last(ft_face)+1;
else
return c;
}
#endif
#line 13131 "hint.w"
/*:645*//*684:*/
#line 14706 "hint.w"

#ifdef DEBUG
#define MAX_LEAKS (1<<16)
static pointer leaks[MAX_LEAKS]= {0};
#endif
#line 14711 "hint.w"

static void leak_clear(void)
{
#ifdef DEBUG
int i;
for(i= 0;i<MAX_LEAKS;i++)
leaks[i]= 0;
#endif
#line 14719 "hint.w"
}

static void leak_in(pointer p,int s)
{
#ifdef DEBUG
if(0!=leaks[p])
fprintf(stderr,"ERROR leak in: p=%d, s in=%d, leaks[p]= %d != 0\n",p,s,leaks[p]);
leaks[p]= s;
#endif
#line 14728 "hint.w"
}

static void leak_out(pointer p,int s)
{
#ifdef DEBUG
if(s!=leaks[p])
fprintf(stderr,"ERROR: leak out: p=%d, s out=%d != %d = s in\n",p,s,leaks[p]);
leaks[p]= 0;
#endif
#line 14737 "hint.w"
}

static void list_leaks(void)
{
#ifdef DEBUG
int i;
for(i= 0;i<MAX_LEAKS;i++)
if(leaks[i]!=0)
fprintf(stderr,"ERROR:leak final: p=%d, s=%d\n",i,leaks[i]);
#endif
#line 14747 "hint.w"
}
/*:684*/
#line 14798 "hint.w"


/*298:*/
#line 6452 "hint.w"

static void hget_def_node(void)
{Kind k;
int n;
/*374:*/
#line 7666 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:374*/
#line 6456 "hint.w"

k= KIND(a);
if(k==unknown_kind&&INFO(a)==b100)
{hget_unknown_def();
/*375:*/
#line 7671 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:375*/
#line 6460 "hint.w"

return;
}
if(k==label_kind&&(INFO(a)&b001))HGET16(n);
else n= HGET8;
if(max_fixed[k]> max_default[k])
{MESSAGE("Definitions for kind %s not supported\n",definition_name[k]);
while(hpos<hend&&*hpos!=a)hpos++;
/*375:*/
#line 7671 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:375*/
#line 6468 "hint.w"

return;
}
if(k!=range_kind)REF_RNG(k,n);
DBG(DBGTAGS,"Defining %s %d\n",definition_name[KIND(a)],n);
switch(KIND(a))
{case language_kind:{char*t;HGET_STRING(t);(void)t;break;}
case font_kind:hget_font_def(a,n);break;
case int_kind:integer_def[n]= hget_integer_def(a);break;
case dimen_kind:dimen_def[n]= hget_dimen_def(a);break;
case xdimen_kind:hget_xdimen_def(INFO(a),&(xdimen_def[n]));break;
case baseline_kind:hget_baseline_def(a,n);break;
case glue_kind:pointer_def[glue_kind][n]= hget_glue_def(a);break;
case param_kind:param_def[n]= hget_param_list(a);break;
case range_kind:hget_range_def(a,n);break;
case page_kind:hget_page_def(a,n);break;
case label_kind:hget_outline_or_label_def(INFO(a),n);break;
case color_kind:hget_color_def(INFO(a),n);break;
default:pointer_def[KIND(a)][n]= hget_definition(a);break;
}
if(n> max_ref[k]||n<=max_fixed[k])
QUIT("Definition %d for %s out of range [%d - %d]",
n,definition_name[k],max_fixed[k]+1,max_ref[k]);
/*375:*/
#line 7671 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:375*/
#line 6491 "hint.w"

}

static pointer hset_glue(Glue*g)
{if(ZERO_GLUE(*g))
{add_glue_ref(zero_glue);
return zero_glue;
}
else
{pointer p= get_node(glue_spec_size);
width(p)= g->w.w;
stretch(p)= round(g->p.f*ONE);stretch_order(p)= g->p.o;
shrink(p)= round(g->m.f*ONE);shrink_order(p)= g->m.o;
return p;
}
}

static void hset_default_definitions(void)
{int i;
for(i= 0;i<=MAX_INT_DEFAULT;i++)integer_def[i]= int_defaults[i];
for(i= 0;i<=MAX_DIMEN_DEFAULT;i++)dimen_def[i]= dimen_defaults[i];
for(i= 0;i<=MAX_XDIMEN_DEFAULT;i++)xdimen_def[i]= xdimen_defaults[i];
for(i= 0;i<=MAX_GLUE_DEFAULT;i++)pointer_def[glue_kind][i]= hset_glue(&(glue_defaults[i]));
for(i= 0;i<=MAX_BASELINE_DEFAULT;i++)
{baseline_def[i].bs= hset_glue(&(baseline_defaults[i].bs));
baseline_def[i].ls= hset_glue(&(baseline_defaults[i].ls));
baseline_def[i].lsl= baseline_defaults[i].lsl;
}
hset_default_colors();
}

static void free_definitions(void)
{/*302:*/
#line 6584 "hint.w"

{int k;
for(k= 0;k<32;k++)
{free(pointer_def[k]);pointer_def[k]= NULL;}
}
/*:302*//*305:*/
#line 6607 "hint.w"

free(integer_def);integer_def= NULL;
/*:305*//*309:*/
#line 6636 "hint.w"

free(dimen_def);dimen_def= NULL;
/*:309*//*313:*/
#line 6665 "hint.w"

free(xdimen_def);xdimen_def= NULL;
/*:313*//*321:*/
#line 6734 "hint.w"

free(baseline_def);baseline_def= NULL;
/*:321*//*327:*/
#line 6851 "hint.w"

if(font_def!=NULL)
{hint_clear_fonts(true);
ft_destroy();
free(font_def);
font_def= NULL;
}
/*:327*//*333:*/
#line 6950 "hint.w"

if(param_def!=NULL)
{int i;
for(i= 0;i<=max_ref[param_kind];i++)
free_param_list(param_def[i]);
}
free(param_def);param_def= NULL;
/*:333*//*340:*/
#line 7109 "hint.w"

free(range_def);range_def= NULL;
/*:340*//*344:*/
#line 7158 "hint.w"

free(streams);streams= NULL;
/*:344*//*352:*/
#line 7271 "hint.w"

if(page_def!=NULL)
{int k;
for(k= 0;k<=max_ref[page_kind];k++)
{free(page_def[k].s);free(page_def[k].n);
}
free(page_def);page_def= NULL;cur_page= NULL;
}
/*:352*//*359:*/
#line 7384 "hint.w"

free(labels);labels= NULL;
{int k;
for(k= 0;k<=max_outline;k++)free(hint_outlines[k].title);
}
free(hint_outlines);hint_outlines= NULL;outline_no= -1;
max_outline= -1;
/*:359*//*367:*/
#line 7474 "hint.w"

if(color_def!=color_defaults){free(color_def);color_def= color_defaults;}
/*:367*/
#line 6523 "hint.w"

}

static void hget_definition_section(void)
{DBG(DBGDEF,"Definitions\n");
hget_section(1);
DBG(DBGDEF,"Reading list of maximum values\n");
free_definitions();
hget_max_definitions();
/*301:*/
#line 6569 "hint.w"

{Kind k;
for(k= 0;k<32;k++)
{if(k==font_kind||k==int_kind||k==dimen_kind||k==xdimen_kind||
k==glue_kind||k==baseline_kind||k==range_kind||k==page_kind||k==param_kind||k==stream_kind||k==label_kind)
continue;
if(max_ref[k]>=0&&max_ref[k]<=256)
{DBG(DBGDEF,"Allocating definitions for %s (kind %d): %d entries of "SIZE_F" byte each\n",
definition_name[k],k,max_ref[k]+1,sizeof(pointer));
ALLOCATE(pointer_def[k],max_ref[k]+1,pointer);
}
}
}
/*:301*//*304:*/
#line 6603 "hint.w"

ALLOCATE(integer_def,max_ref[int_kind]+1,int32_t);
/*:304*//*308:*/
#line 6632 "hint.w"

ALLOCATE(dimen_def,max_ref[dimen_kind]+1,Dimen);
/*:308*//*312:*/
#line 6662 "hint.w"

ALLOCATE(xdimen_def,max_ref[xdimen_kind]+1,Xdimen);
/*:312*//*317:*/
#line 6711 "hint.w"

ALLOCATE(pointer_def[glue_kind],max_ref[glue_kind]+1,pointer);
/*:317*//*320:*/
#line 6730 "hint.w"

ALLOCATE(baseline_def,max_ref[baseline_kind]+1,BaselineSkip);
/*:320*//*326:*/
#line 6847 "hint.w"

ALLOCATE(font_def,max_ref[font_kind]+1,FontDef);
/*:326*//*332:*/
#line 6946 "hint.w"

ALLOCATE(param_def,max_ref[param_kind]+1,ParamDef*);
/*:332*//*339:*/
#line 7104 "hint.w"

ALLOCATE(range_def,max_ref[range_kind]+1,RangeDef);
max_range= -1;
/*:339*//*343:*/
#line 7154 "hint.w"

ALLOCATE(streams,max_ref[stream_kind]+1,Stream);
/*:343*//*350:*/
#line 7251 "hint.w"

ALLOCATE(page_def,max_ref[page_kind]+1,PageDef);
/*:350*//*358:*/
#line 7377 "hint.w"

if(max_ref[label_kind]>=0)
ALLOCATE(labels,max_ref[label_kind]+1,Label);
if(max_outline>=0)
ALLOCATE(hint_outlines,max_outline+1,hint_Outline);
/*:358*//*366:*/
#line 7468 "hint.w"

if(color_def!=color_defaults){free(color_def);color_def= color_defaults;}
ALLOCATE(color_def,max_ref[color_kind]+1,ColorSet);
first_color= true;
/*:366*/
#line 6532 "hint.w"

hset_default_definitions();
DBG(DBGDEF,"Reading list of definitions\n");
while(hpos<hend)
hget_def_node();
hget_font_metrics();
/*351:*/
#line 7255 "hint.w"

page_def[0].d= max_depth;
page_def[0].g= top_skip;add_glue_ref(top_skip);
page_def[0].p= 0;
page_def[0].n= strdup("default");
page_def[0].v.w= -9*ONE;
page_def[0].v.h= 0.0;
page_def[0].v.v= 1.25;
page_def[0].h.w= -9*ONE;
page_def[0].h.h= 1.25;
page_def[0].h.v= 0.0;
page_def[0].t= 0;
ALLOCATE(page_def[0].s,max_ref[stream_kind]+1,StreamDef);
cur_page= &(page_def[0]);
/*:351*/
#line 6538 "hint.w"

}
/*:298*//*310:*/
#line 6640 "hint.w"

scaled hget_dimen_ref(uint8_t n)
{REF_RNG(dimen_kind,n);
return dimen_def[n];
}

static scaled hget_dimen_def(uint8_t a)
{if(INFO(a)==b000)
return hget_dimen_ref(HGET8);
else
{scaled d;HGET32(d);return d;}
}
/*:310*//*322:*/
#line 6738 "hint.w"

static void hget_baseline_def(uint8_t a,uint8_t n)
{HGET_BASELINE(INFO(a));
baseline_def[n].bs= cur_bs;add_glue_ref(cur_bs);
baseline_def[n].ls= cur_ls;add_glue_ref(cur_ls);
baseline_def[n].lsl= cur_lsl;
}

static void hget_baseline_ref(uint8_t n)
{REF_RNG(baseline_kind,n);
cur_bs= baseline_def[n].bs;
cur_ls= baseline_def[n].ls;
cur_lsl= baseline_def[n].lsl;
}

pointer happend_to_vlist(pointer b)
{scaled d;
pointer p= null;

if(needs_bs&&prev_depth> ignore_depth)
{d= width(cur_bs)-prev_depth-height(b);
if(d<cur_lsl)p= new_glue(cur_ls);
else{pointer q= new_spec(cur_bs);
width(q)= d;p= new_glue(q);glue_ref_count(q)= null;
}
link(tail)= p;tail= p;
if(nest_ptr==0)
store_map(p,cur_list.bs_pos-hstart,0);
}
link(tail)= b;tail= b;prev_depth= depth(b);
cur_list.bs_pos= NULL;
return p;
}
/*:322*//*323:*/
#line 6792 "hint.w"

static pointer hprepend_to_vlist(pointer b)
{scaled d;
pointer p= null;

if(needs_bs&&prev_height> ignore_depth)
{d= width(cur_bs)-prev_height-depth(b);
if(d<cur_lsl)p= new_glue(cur_ls);
else{pointer q= new_spec(cur_bs);
width(q)= d;p= new_glue(q);glue_ref_count(q)= null;
}
link(tail)= p;tail= p;
if(nest_ptr==0)
store_map(p,cur_list.bs_pos-hstart,0);
}
link(tail)= b;tail= b;prev_height= height(b);
cur_list.bs_pos= NULL;
return p;
}
/*:323*//*360:*/
#line 7397 "hint.w"

static void hget_outline_or_label_def(Info i,int n)
{if(i&b100)
/*362:*/
#line 7418 "hint.w"

{hint_Outline*t;
uint64_t pos;
uint8_t where;
outline_no++;
RNG("Outline",outline_no,0,max_outline);
t= hint_outlines+outline_no;
t->depth= HGET8;
t->p= hget_list_pointer();
t->title= strdup(hlist_to_string(t->p));
/*363:*/
#line 7434 "hint.w"

if(labels==NULL||n> max_ref[label_kind])
{where= LABEL_TOP;pos= 0;}
else
{where= labels[n].where;
#if 1
pos= ((uint64_t)labels[n].pos<<32)+(labels[n].pos-labels[n].pos0);
#else
#line 7442 "hint.w"
 pos= ((uint64_t)labels[n].pos0<<32);

#endif
#line 7445 "hint.w"
}
/*:363*/
#line 7428 "hint.w"

t->where= where;
t->pos= pos;
}
/*:362*/
#line 7400 "hint.w"

else
/*361:*/
#line 7406 "hint.w"

{Label*t= labels+n;
HGET32(t->pos);
t->where= HGET8;
if(t->where> LABEL_MID)t->where= LABEL_UNDEF;
if(i&b010)
{HGET32(t->pos0);t->f= HGET8;}
else t->pos0= t->pos;
DBG(DBGDEF,"Label 0x%x+0x%x where=%d font=%d\n",t->pos0,t->pos,t->where,t->f);
}
/*:361*/
#line 7402 "hint.w"

}
/*:360*//*369:*/
#line 7497 "hint.w"

static void hget_color_def(uint8_t a,int i)
{int j,k;
if(INFO(a)!=b000)
QUIT("Color Definition %d with Info value %d!=000",i,INFO(a));
k= HGET8;
if(k!=6)
QUIT("Definition %d of color set needs 6 color pairs %d given\n",i,k);
if(i==0&&!first_color)
QUIT("Definition of color 0 must come first");
first_color= false;
for(j= 0;j<6*2;j++)
HGET32(color_def[i][j]);
}
/*:369*//*371:*/
#line 7602 "hint.w"

static void hget_unknown_def(void)
{Tag t;signed char i;
t= HGET8;
i= HGET8;
if(i==0)
QUIT("Zero not allowed for unknown node size at 0x%x\n",(uint32_t)(hpos-hstart-2));
if(hnode_size[t]==0)
{hnode_size[t]= i;
DBG(DBGTAGS,"Defining node size %d,%d for tag 0x%x (%s)\n",NODE_HEAD(i),NODE_TAIL(i),t,content_name[KIND(t)]);
}
}
/*:371*//*372:*/
#line 7620 "hint.w"

int hget_unknown(Tag a)
{DBG(DBGTAGS,"Trying unknown tag 0x%x at 0x%x\n",a,(uint32_t)(hpos-hstart-1));
hpos--;
hff_hpos();
hpos--;
return 1;
}
/*:372*//*373:*/
#line 7652 "hint.w"

static void hget_content_section()
{DBG(DBGDIR,"Reading Content Section\n");
hget_section(2);
}
/*:373*//*405:*/
#line 8079 "hint.w"

static pointer hget_rule_node(void)
{pointer q= null;
/*374:*/
#line 7666 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:374*/
#line 8082 "hint.w"

if(KIND(a)==rule_kind){HGET_RULE(INFO(a));q= p;}
else tag_expected(TAG(rule_kind,0),a,node_pos);
/*375:*/
#line 7671 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:375*/
#line 8085 "hint.w"

return q;
}
/*:405*//*422:*/
#line 8455 "hint.w"

static pointer hget_hbox_node(void)
{/*374:*/
#line 7666 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:374*/
#line 8457 "hint.w"

if(KIND(a)!=hbox_kind)tag_expected(TAG(hbox_kind,0),a,node_pos);
{pointer p;
HGET_BOX(INFO(a));
/*375:*/
#line 7671 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:375*/
#line 8461 "hint.w"

return p;
}
}


static pointer hget_vbox_node(void)
{
/*374:*/
#line 7666 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:374*/
#line 8469 "hint.w"

if(KIND(a)!=vbox_kind)tag_expected(TAG(vbox_kind,0),a,node_pos);
{pointer p;
HGET_BOX(INFO(a));
/*375:*/
#line 7671 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:375*/
#line 8473 "hint.w"

type(p)= vlist_node;
return p;
}
}
/*:422*//*469:*/
#line 9292 "hint.w"

pointer hget_paragraph_initial(scaled x,uint8_t*to)
{/*463:*/
#line 9164 "hint.w"

pointer par_ptr= null;
if(KIND(*hpos)==list_kind)
{uint32_t s,t;
/*374:*/
#line 7666 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:374*/
#line 9168 "hint.w"

if((INFO(a)&b011)==0)
HGET8;
else if(INFO(a)&b100)
QUIT("Text in paragraph not yet implemented");
else
{uint8_t*list_end;
s= hget_list_size(INFO(a));
hget_size_boundary(INFO(a));
list_end= hpos+s;
cur_list.hs_field= x;
push_nest();
cur_list.bs_pos= NULL;

/*:463*/
#line 9294 "hint.w"

if(to> list_end)
{LOG("Value of to greater than list_end");
to= list_end;
}
/*464:*/
#line 9184 "hint.w"

while(hpos<to)
{hget_content();
if(nest_ptr==1)
{pointer p= tail;
if(p!=head&&!is_char_node(p)&&
(type(p)==glue_node||type(p)==kern_node||type(p)==penalty_node
||type(p)==disc_node||type(p)==math_node))
store_map(p,node_pos,0);
}
}

/*:464*/
#line 9299 "hint.w"

if(KIND(*to)==disc_kind)
{hget_content();
store_map(tail,node_pos,0);
transplant_pre_break_list();
}
if(head!=tail)
/*470:*/
#line 9320 "hint.w"

{if(is_char_node(tail))tail_append(new_penalty(inf_penalty))
else if(type(tail)!=glue_node)tail_append(new_penalty(inf_penalty))
else
{type(tail)= penalty_node;delete_glue_ref(glue_ptr(tail));
flush_node_list(leader_ptr(tail));penalty(tail)= inf_penalty;
}
tail_append(new_glue(zero_glue));
}
/*:470*/
#line 9306 "hint.w"

hpos= list_end;
/*465:*/
#line 9198 "hint.w"

if(head!=tail)
{par_ptr= link(head);
store_map(par_ptr,node_pos,0);
if(needs_bs)
QUIT("Unexpected trailing baseline node");
}
pop_nest();
}
hget_size_boundary(INFO(a));
t= hget_list_size(INFO(a));
if(t!=s)
QUIT("List sizes at 0x%x and "SIZE_F" do not match 0x%x != 0x%x",
node_pos+1,hpos-hstart-s-1,s,t);
/*375:*/
#line 7671 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:375*/
#line 9212 "hint.w"

}



/*:465*/
#line 9308 "hint.w"

return par_ptr;
}
/*:469*/
#line 14800 "hint.w"

/*382:*/
#line 7767 "hint.w"

static void hteg_node(uint8_t z)
{switch(z)
{
/*394:*/
#line 7963 "hint.w"

case TAG(glyph_kind,1):HTEG_GLYPH(1);break;
case TAG(glyph_kind,2):HTEG_GLYPH(2);break;
case TAG(glyph_kind,3):HTEG_GLYPH(3);break;
case TAG(glyph_kind,4):HTEG_GLYPH(4);break;
/*:394*//*398:*/
#line 8006 "hint.w"

case TAG(penalty_kind,0):tail_append(new_penalty(hget_integer_ref(HTEG8)));break;
case TAG(penalty_kind,1):{tail_append(new_penalty(HTEG8));}break;
case TAG(penalty_kind,2):{int16_t n;HTEG16(n);RNG("Penalty",n,-20000,+20000);tail_append(new_penalty(n));}break;
/*:398*//*400:*/
#line 8026 "hint.w"

case TAG(language_kind,b000):(void)HTEG8;
case TAG(language_kind,1):
case TAG(language_kind,2):
case TAG(language_kind,3):
case TAG(language_kind,4):
case TAG(language_kind,5):
case TAG(language_kind,6):
case TAG(language_kind,7):break;
/*:400*//*404:*/
#line 8069 "hint.w"

case TAG(rule_kind,b000):tail_append(hget_rule_ref(HTEG8));prev_height= ignore_depth;break;
case TAG(rule_kind,b011):{HTEG_RULE(b011);tail_append(p);prev_height= ignore_depth;}break;
case TAG(rule_kind,b101):{HTEG_RULE(b101);tail_append(p);prev_height= ignore_depth;}break;
case TAG(rule_kind,b001):{HTEG_RULE(b001);tail_append(p);prev_height= ignore_depth;}break;
case TAG(rule_kind,b110):{HTEG_RULE(b110);tail_append(p);prev_height= ignore_depth;}break;
case TAG(rule_kind,b111):{HTEG_RULE(b111);tail_append(p);prev_height= ignore_depth;}break;
/*:404*//*411:*/
#line 8140 "hint.w"

case TAG(glue_kind,b000):tail_append(new_glue(hget_glue_ref(HTEG8)));break;
case TAG(glue_kind,b001):{pointer p;HTEG_GLUE(b001);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b010):{pointer p;HTEG_GLUE(b010);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b011):{pointer p;HTEG_GLUE(b011);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b100):{pointer p;HTEG_GLUE(b100);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b101):{pointer p;HTEG_GLUE(b101);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b110):{pointer p;HTEG_GLUE(b110);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b111):{pointer p;HTEG_GLUE(b111);tail_append(spec2glue(p));}break;
/*:411*//*421:*/
#line 8436 "hint.w"

case TAG(hbox_kind,b000):{pointer p;HTEG_BOX(b000);hprepend_to_vlist(p);}break;
case TAG(hbox_kind,b001):{pointer p;HTEG_BOX(b001);hprepend_to_vlist(p);}break;
case TAG(hbox_kind,b010):{pointer p;HTEG_BOX(b010);hprepend_to_vlist(p);}break;
case TAG(hbox_kind,b011):{pointer p;HTEG_BOX(b011);hprepend_to_vlist(p);}break;
case TAG(hbox_kind,b100):{pointer p;HTEG_BOX(b100);hprepend_to_vlist(p);}break;
case TAG(hbox_kind,b101):{pointer p;HTEG_BOX(b101);hprepend_to_vlist(p);}break;
case TAG(hbox_kind,b110):{pointer p;HTEG_BOX(b110);hprepend_to_vlist(p);}break;
case TAG(hbox_kind,b111):{pointer p;HTEG_BOX(b111);hprepend_to_vlist(p);}break;
case TAG(vbox_kind,b000):{pointer p;HTEG_BOX(b000);type(p)= vlist_node;hprepend_to_vlist(p);}break;
case TAG(vbox_kind,b001):{pointer p;HTEG_BOX(b001);type(p)= vlist_node;hprepend_to_vlist(p);}break;
case TAG(vbox_kind,b010):{pointer p;HTEG_BOX(b010);type(p)= vlist_node;hprepend_to_vlist(p);}break;
case TAG(vbox_kind,b011):{pointer p;HTEG_BOX(b011);type(p)= vlist_node;hprepend_to_vlist(p);}break;
case TAG(vbox_kind,b100):{pointer p;HTEG_BOX(b100);type(p)= vlist_node;hprepend_to_vlist(p);}break;
case TAG(vbox_kind,b101):{pointer p;HTEG_BOX(b101);type(p)= vlist_node;hprepend_to_vlist(p);}break;
case TAG(vbox_kind,b110):{pointer p;HTEG_BOX(b110);type(p)= vlist_node;hprepend_to_vlist(p);}break;
case TAG(vbox_kind,b111):{pointer p;HTEG_BOX(b111);type(p)= vlist_node;hprepend_to_vlist(p);}break;
/*:421*//*427:*/
#line 8552 "hint.w"

case TAG(hset_kind,b000):{pointer p;HTEG_SET(b000);hset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(hset_kind,b001):{pointer p;HTEG_SET(b001);hset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(hset_kind,b010):{pointer p;HTEG_SET(b010);hset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(hset_kind,b011):{pointer p;HTEG_SET(b011);hset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(hset_kind,b100):{pointer p;HTEG_SET(b100);hset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(hset_kind,b101):{pointer p;HTEG_SET(b101);hset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(hset_kind,b110):{pointer p;HTEG_SET(b110);hset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(hset_kind,b111):{pointer p;HTEG_SET(b111);hset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;

case TAG(vset_kind,b000):{pointer p;HTEG_SET(b000);vset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(vset_kind,b001):{pointer p;HTEG_SET(b001);vset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(vset_kind,b010):{pointer p;HTEG_SET(b010);vset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(vset_kind,b011):{pointer p;HTEG_SET(b011);vset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(vset_kind,b100):{pointer p;HTEG_SET(b100);vset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(vset_kind,b101):{pointer p;HTEG_SET(b101);vset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(vset_kind,b110):{pointer p;HTEG_SET(b110);vset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(vset_kind,b111):{pointer p;HTEG_SET(b111);vset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
/*:427*//*433:*/
#line 8712 "hint.w"

case TAG(hpack_kind,b000):HTEG_PACK(hpack_kind,b000);break;
case TAG(hpack_kind,b010):HTEG_PACK(hpack_kind,b010);break;
case TAG(hpack_kind,b100):HTEG_PACK(hpack_kind,b100);break;
case TAG(hpack_kind,b110):HTEG_PACK(hpack_kind,b110);break;
case TAG(hpack_kind,b001):HTEG_PACK(hpack_kind,b001);break;
case TAG(hpack_kind,b011):HTEG_PACK(hpack_kind,b011);break;
case TAG(hpack_kind,b101):HTEG_PACK(hpack_kind,b101);break;
case TAG(hpack_kind,b111):HTEG_PACK(hpack_kind,b111);break;

case TAG(vpack_kind,b000):HTEG_PACK(vpack_kind,b000);break;
case TAG(vpack_kind,b010):HTEG_PACK(vpack_kind,b010);break;
case TAG(vpack_kind,b100):HTEG_PACK(vpack_kind,b100);break;
case TAG(vpack_kind,b110):HTEG_PACK(vpack_kind,b110);break;
case TAG(vpack_kind,b001):HTEG_PACK(vpack_kind,b001);break;
case TAG(vpack_kind,b011):HTEG_PACK(vpack_kind,b011);break;
case TAG(vpack_kind,b101):HTEG_PACK(vpack_kind,b101);break;
case TAG(vpack_kind,b111):HTEG_PACK(vpack_kind,b111);break;
/*:433*//*438:*/
#line 8787 "hint.w"

case TAG(kern_kind,b000):{HTEG_KERN(b000);}break;
case TAG(kern_kind,b001):{HTEG_KERN(b001);}break;
case TAG(kern_kind,b010):{HTEG_KERN(b010);}break;
case TAG(kern_kind,b011):{HTEG_KERN(b011);}break;
case TAG(kern_kind,b100):{HTEG_KERN(b100);}break;
case TAG(kern_kind,b101):{HTEG_KERN(b101);}break;
case TAG(kern_kind,b110):{HTEG_KERN(b110);}break;
case TAG(kern_kind,b111):{HTEG_KERN(b111);}break;
/*:438*//*442:*/
#line 8834 "hint.w"

case TAG(leaders_kind,0):tail_append(hget_leaders_ref(HTEG8));break;
case TAG(leaders_kind,1):HTEG_LEADERS(1);break;
case TAG(leaders_kind,2):HTEG_LEADERS(2);break;
case TAG(leaders_kind,3):HTEG_LEADERS(3);break;
case TAG(leaders_kind,b100|1):HTEG_LEADERS(b100|1);break;
case TAG(leaders_kind,b100|2):HTEG_LEADERS(b100|2);break;
case TAG(leaders_kind,b100|3):HTEG_LEADERS(b100|3);break;
/*:442*//*446:*/
#line 8875 "hint.w"

case TAG(baseline_kind,b000):{hget_baseline_ref(HTEG8);cur_list.bs_pos= hpos-1;}break;
case TAG(baseline_kind,b010):{HTEG_BASELINE(b010);}break;
case TAG(baseline_kind,b011):{HTEG_BASELINE(b011);}break;
case TAG(baseline_kind,b100):{HTEG_BASELINE(b100);}break;
case TAG(baseline_kind,b101):{HTEG_BASELINE(b101);}break;
case TAG(baseline_kind,b110):{HTEG_BASELINE(b110);}break;
case TAG(baseline_kind,b111):{HTEG_BASELINE(b111);}break;
/*:446*//*451:*/
#line 8936 "hint.w"

case TAG(ligature_kind,0):tail_append(hget_ligature_ref(HTEG8));break;
case TAG(ligature_kind,1):HTEG_LIG(1);break;
case TAG(ligature_kind,2):HTEG_LIG(2);break;
case TAG(ligature_kind,3):HTEG_LIG(3);break;
case TAG(ligature_kind,4):HTEG_LIG(4);break;
case TAG(ligature_kind,5):HTEG_LIG(5);break;
case TAG(ligature_kind,6):HTEG_LIG(6);break;
case TAG(ligature_kind,7):HTEG_LIG(7);break;
/*:451*//*455:*/
#line 8985 "hint.w"

case TAG(disc_kind,b000):tail_append(hget_hyphen_ref(HTEG8));break;
case TAG(disc_kind,b001):{HTEG_DISC(b001);tail_append(p);}break;
case TAG(disc_kind,b010):{HTEG_DISC(b010);tail_append(p);}break;
case TAG(disc_kind,b011):{HTEG_DISC(b011);tail_append(p);}break;
case TAG(disc_kind,b100):{HTEG_DISC(b100);tail_append(p);}break;
case TAG(disc_kind,b101):{HTEG_DISC(b101);tail_append(p);}break;
case TAG(disc_kind,b110):{HTEG_DISC(b110);tail_append(p);}break;
case TAG(disc_kind,b111):{HTEG_DISC(b111);tail_append(p);}break;
/*:455*//*476:*/
#line 9410 "hint.w"

case TAG(par_kind,b000):hteg_paragraph(b000);break;
case TAG(par_kind,b010):hteg_paragraph(b010);break;
case TAG(par_kind,b100):hteg_paragraph(b100);break;
case TAG(par_kind,b110):hteg_paragraph(b110);break;
/*:476*//*483:*/
#line 9540 "hint.w"

case TAG(math_kind,b000):HTEG_MATH(b000);break;
case TAG(math_kind,b001):HTEG_MATH(b001);break;
case TAG(math_kind,b010):HTEG_MATH(b010);break;
case TAG(math_kind,b100):HTEG_MATH(b100);break;
case TAG(math_kind,b101):HTEG_MATH(b101);break;
case TAG(math_kind,b110):HTEG_MATH(b110);break;
/*:483*//*485:*/
#line 9564 "hint.w"

case TAG(math_kind,b111):tail_append(new_math(0,before));break;
case TAG(math_kind,b011):tail_append(new_math(0,after));break;
/*:485*//*491:*/
#line 9634 "hint.w"

case TAG(table_kind,b000):HTEG_TABLE(b000);break;
case TAG(table_kind,b001):HTEG_TABLE(b001);break;
case TAG(table_kind,b010):HTEG_TABLE(b010);break;
case TAG(table_kind,b011):HTEG_TABLE(b011);break;
case TAG(table_kind,b100):HTEG_TABLE(b100);break;
case TAG(table_kind,b101):HTEG_TABLE(b101);break;
case TAG(table_kind,b110):HTEG_TABLE(b110);break;
case TAG(table_kind,b111):HTEG_TABLE(b111);break;

case TAG(item_kind,b000):hteg_list_pointer();break;
case TAG(item_kind,b001):hteg_content();break;
case TAG(item_kind,b010):hteg_content();break;
case TAG(item_kind,b011):hteg_content();break;
case TAG(item_kind,b100):hteg_content();break;
case TAG(item_kind,b101):hteg_content();break;
case TAG(item_kind,b110):hteg_content();break;
case TAG(item_kind,b111):hteg_content();(void)HTEG8;break;
/*:491*//*496:*/
#line 9706 "hint.w"

case TAG(stream_kind,b000):HTEG_STREAM(b000);break;
case TAG(stream_kind,b010):HTEG_STREAM(b010);break;
/*:496*//*500:*/
#line 9767 "hint.w"

case TAG(image_kind,b000):hget_image_ref(HTEG8);break;
case TAG(image_kind,b001):HTEG_IMAGE(b001);break;
case TAG(image_kind,b010):HTEG_IMAGE(b010);break;
case TAG(image_kind,b011):HTEG_IMAGE(b011);break;
case TAG(image_kind,b100):HTEG_IMAGE(b100);break;
case TAG(image_kind,b101):HTEG_IMAGE(b101);break;
case TAG(image_kind,b110):HTEG_IMAGE(b110);break;
case TAG(image_kind,b111):HTEG_IMAGE(b111);break;
/*:500*//*502:*/
#line 9782 "hint.w"

case TAG(color_kind,b000):tail_append(hget_color_ref(HTEG8));break;
/*:502*//*504:*/
#line 9800 "hint.w"

case TAG(link_kind,b000):HTEG_LINK(b000);break;
case TAG(link_kind,b001):HTEG_LINK(b001);break;
case TAG(link_kind,b010):HTEG_LINK(b010);break;
case TAG(link_kind,b011):HTEG_LINK(b011);break;
case TAG(link_kind,b100):HTEG_LINK(b100);break;
case TAG(link_kind,b101):HTEG_LINK(b101);break;
case TAG(link_kind,b110):HTEG_LINK(b110);break;
case TAG(link_kind,b111):HTEG_LINK(b111);break;
/*:504*/
#line 7771 "hint.w"

default:
TAGERR(z);
}
}

static void hteg_content(void)
{/*380:*/
#line 7751 "hint.w"

uint8_t a,z;
z= HTEG8;DBGTAG(z,hpos);
/*:380*/
#line 7778 "hint.w"

node_pos= hpos-hstart;
hteg_node(z);
/*381:*/
#line 7756 "hint.w"

a= HTEG8;DBGTAG(a,hpos);
if(z!=a)tag_mismatch(a,z,hpos-hstart,node_pos);
/*:381*/
#line 7781 "hint.w"

node_pos= hpos-hstart;
if(nest_ptr==0&&tail!=head
#if 0
&&(type(tail)==penalty_node||type(tail)==glue_node
||type(tail)==hlist_node||type(tail)==vlist_node
||type(tail)==kern_node)
#endif
#line 7789 "hint.w"
)
store_map(tail,node_pos,0);
}
/*:382*//*457:*/
#line 9013 "hint.w"

#if 0
static pointer hteg_disc_node(void)
{/*380:*/
#line 7751 "hint.w"

uint8_t a,z;
z= HTEG8;DBGTAG(z,hpos);
/*:380*/
#line 9016 "hint.w"

if(KIND(z)!=disc_kind||INFO(z)==b000)
tag_expected(TAG(disc_kind,1),z,node_pos);
{
HTEG_DISC(INFO(z));
/*381:*/
#line 7756 "hint.w"

a= HTEG8;DBGTAG(a,hpos);
if(z!=a)tag_mismatch(a,z,hpos-hstart,node_pos);
/*:381*/
#line 9021 "hint.w"

return p;
}
}
#endif
#line 9026 "hint.w"
/*:457*/
#line 14801 "hint.w"


/*642:*/
#line 12987 "hint.w"


static void ft_init(void)
{
if(ft_library)return;
ft_err= FT_Init_FreeType(&ft_library);
if(ft_err)
{ft_library= NULL;
QUIT("Unable to initialize the FreeType Library.");
}
}

static void ft_unload_faces(void)
{int i;
if(ft_library==NULL)return;
if(font_def==NULL)return;
for(i= 0;i<=max_ref[font_kind];i++)
if(font_def[i].ft_face!=NULL)
ft_unload_font_face(i);
}

static void ft_destroy(void)
{ft_unload_faces();
ft_err= FT_Done_FreeType(ft_library);
if(ft_err)
MESSAGE("Error releasing the FreeType Library.");
ft_library= NULL;
}
/*:642*//*646:*/
#line 13149 "hint.w"


static FT_Face ft_load_font_face(uint8_t f)
{int ft_err;
FT_Face ft_face;
unsigned char*ft_data;
int ft_size;
{unsigned char*spos,*sstart,*send;
spos= hpos;sstart= hstart;send= hend;
hget_section(font_def[f].q);
ft_data= hstart;
ft_size= hend-hstart;
hpos= spos;hstart= sstart;hend= send;
}
ft_err= FT_New_Memory_Face(ft_library,
ft_data,ft_size,0,&ft_face);
if(ft_err)
{LOG("Unable to create font %d\n",f);
return NULL;
}
font_def[f].ft_face= ft_face;
/*647:*/
#line 13191 "hint.w"

if(width_base[f]==0)
ft_err= FT_Select_Charmap(ft_face,FT_ENCODING_UNICODE);
else
{ft_err= FT_Select_Charmap(ft_face,FT_ENCODING_ADOBE_CUSTOM);
if(ft_err)ft_err= FT_Select_Charmap(ft_face,FT_ENCODING_UNICODE);
}
if(ft_err)LOG("Unable to select encoding for font %d\n",f);
/*:647*/
#line 13170 "hint.w"

/*648:*/
#line 13211 "hint.w"

if(font_def[f].hpxs!=x_px_size||font_def[f].vpxs!=y_px_size)
{FT_F26Dot6 ft_size;
ft_size= font_def[f].s*(72.00/72.27)*((double)(1<<6)/(double)(1<<16))+0.5;
font_def[f].hpxs= x_px_size;
font_def[f].vpxs= y_px_size;
ft_err= FT_Set_Char_Size(
ft_face,
0,
ft_size,
72.27/(font_def[f].hpxs/(double)ONE),
72.27/(font_def[f].vpxs/(double)ONE));
if(ft_err)QUIT("Unable to set FreeType glyph size");
}
/*:648*/
#line 13171 "hint.w"

FT_Set_Transform(ft_face,NULL,NULL);
return ft_face;
}

static void ft_unload_font_face(uint8_t f)
{ft_err= FT_Done_Face(font_def[f].ft_face);
font_def[f].ft_face= NULL;
}

/*:646*//*650:*/
#line 13277 "hint.w"

static FT_Face ft_get_font_face(uint8_t f)
{FT_Face ft_face;
if(font_def[f].ff==no_format)hload_font(f);
ft_face= font_def[f].ft_face;
if(ft_face==NULL)
ft_face= ft_load_font_face(f);
return ft_face;
}
static scaled ft_char_width(uint8_t f,int c)
{FT_Face ft_face= ft_get_font_face(f);
if(ft_face==NULL)
return 0;
else
return ft_width(ft_face,c,font_size[f]);
}
/*:650*/
#line 14803 "hint.w"



/*628:*/
#line 12570 "hint.w"

static void hfree_glyph_cache(FontDef*f,bool rm);

void hint_clear_fonts(bool rm)
{int f;
if(font_def==NULL)return;
DBG(DBGFONT,rm?"Clear font data":"Clear native glyph data");
for(f= 0;f<=max_ref[font_kind];f++)
{hfree_glyph_cache(font_def+f,rm);
if(rm&&font_def[f].ff==pk_format)
font_def[f].ff= no_format;
}
}
/*:628*/
#line 14806 "hint.w"


#ifdef HINTTYPE

/*604:*/
#line 12017 "hint.w"

static void hmark_page(void)
{return;}
/*:604*//*629:*/
#line 12586 "hint.w"



unsigned int nativeFreeTexture(unsigned int t){return 0;}
unsigned int nativeTexture(unsigned char*bits,int w,int h){return 0;}
void nativeGlyph(double x,double y,double w,double h,
unsigned int t){return;}
static void hfree_glyph_cache(FontDef*f,bool rm){}
void nativeSetSize(int px_h,int px_v,double pt_x,double pt_v){}
/*:629*//*640:*/
#line 12960 "hint.w"

static int unpack_pk_file(internal_font_number f)
{return 1;}
/*:640*//*683:*/
#line 14694 "hint.w"

void hint_show_page(void)
{show_box(streams[0].p);
}
/*:683*/
#line 14810 "hint.w"

#else
#line 14812 "hint.w"

/*591:*/
#line 11750 "hint.w"

static char*m_str;
static int m_length,m_chars;
/*:591*//*594:*/
#line 11821 "hint.w"

#define MAX_M_DIST 512
static uint8_t m_dist[MAX_M_DIST+5];
static int m_ptr,m_max;
/*:594*//*595:*/
#line 11859 "hint.w"

static int m_ptr,m_max;
/*:595*//*598:*/
#line 11932 "hint.w"

static int m_state,m_spaces;
static uint32_t m_d;
/*:598*//*601:*/
#line 11985 "hint.w"

static int m_focus;
static uint64_t m_page;
/*:601*//*605:*/
#line 12023 "hint.w"

static bool c_ignore;
/*:605*//*612:*/
#line 12224 "hint.w"

static int cur_link= -1;
/*:612*//*664:*/
#line 13700 "hint.w"

static int cur_style= 0,cur_mode= 0,cur_color= 0,next_style= 0;
static uint32_t cur_fg;
/*:664*//*668:*/
#line 13760 "hint.w"

static scaled cur_h,cur_v;
static scaled rule_ht,rule_dp,rule_wd;
/*:668*/
#line 14813 "hint.w"

/*632:*/
#line 12651 "hint.w"

#define PK_READ_1_BYTE() (pk_data[i++])
#define PK_READ_2_BYTE() (k= PK_READ_1_BYTE(),k= k<<8,k= k+pk_data[i++],k)
#define PK_READ_3_BYTE() (k= PK_READ_2_BYTE(),k= k<<8,k= k+pk_data[i++],k)
#define PK_READ_4_BYTE() (k= PK_READ_3_BYTE(),k= k<<8,k= k+pk_data[i++],k)
/*:632*//*633:*/
#line 12667 "hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*pk_data;
}PKparse;
/*:633*//*634:*/
#line 12678 "hint.w"

#define read_nybble(P) ((P).j&1?((P).pk_data[(P).j++>>1]&0xF):(((P).pk_data[(P).j++>>1]>>4)&0xF))
/*:634*//*635:*/
#line 12704 "hint.w"

static int packed_number(PKparse*p)
{int i,k;
i= read_nybble(*p);
if(i==0)
{do{k= read_nybble(*p);i++;}while(k==0);
while(i--> 0)k= k*16+read_nybble(*p);
return k-15+(13-p->f)*16+p->f;
}
else if(i<=p->f)return i;
else if(i<14)return(i-p->f-1)*16+read_nybble(*p)+p->f+1;
else
{if(i==14)p->r= packed_number(p);
else p->r= 1;
return packed_number(p);
}
}
/*:635*//*636:*/
#line 12733 "hint.w"

static unsigned char*pk_runlength(Gcache*g,unsigned char*pk_data){
PKparse p;
int x,y;
unsigned char*bits;
int n;
unsigned char gray;
bits= (unsigned char*)calloc(g->w*g->h,1);
if(bits==NULL){g->w= g->h= 0;return NULL;}
p.j= 0;
p.r= 0;
p.f= g->pk_glyph_flags>>4;
p.pk_data= pk_data;
n= 0;
if((g->pk_glyph_flags>>3)&1)gray= 0x00;
else gray= 0xff;
y= 0;
while(y<g->h){
x= 0;
while(x<(int)g->w)
{int d;
if(n<=0){
n= packed_number(&p);
gray= ~gray;
}
d= g->w-x;
if(d> n)d= n;
for(;d> 0;d--,x++,n--)
bits[y*g->w+x]= gray;
}
y++;
while(p.r> 0&&y<g->h)
{int k;
for(k= 0;k<g->w;k++)
bits[y*g->w+k]= bits[(y-1)*g->w+k];
p.r--;
y++;
}
}
return bits;
}
/*:636*//*637:*/
#line 12786 "hint.w"

static unsigned char*pk_bitmap(Gcache*g,unsigned char*pk_data){
unsigned char*bits;
int x,y;
unsigned char mask;

bits= (unsigned char*)calloc(g->w*g->h,1);
if(bits==NULL){g->w= g->h= 0;return NULL;}
mask= 0x80;
for(y= 0;y<g->h;y++)
for(x= 0;x<g->w;x++)
{if(*pk_data&mask)
bits[y*g->w+x]= 0x00;
else
bits[y*g->w+x]= 0xFF;
mask= mask>>1;
if(mask==0){pk_data++;mask= 0x80;}
}
return bits;
}
/*:637*//*638:*/
#line 12810 "hint.w"


static void pk_unpack_glyph(uint8_t f,Gcache*g)
{int i,k;
unsigned char*pk_data;
unsigned char*bits;
if(g==NULL||g->pk_glyph_data==NULL)return;
if(g->OGLtexture!=0)return;
#if 0
DBG(DBGRENDER,"Unpacking glyph %c (0x%x)",g->cc,g->cc);
#endif
#line 12821 "hint.w"
 pk_data= g->pk_glyph_data;
i= 0;
if((g->pk_glyph_flags&7)<4)
{i= i+3;
i= i+1;
g->w= PK_READ_1_BYTE();
g->h= PK_READ_1_BYTE();
g->hoff= (signed char)PK_READ_1_BYTE();
g->voff= (signed char)PK_READ_1_BYTE();
}
else if((g->pk_glyph_flags&7)<7)
{i= i+3;
i= i+2;
g->w= PK_READ_2_BYTE();
g->h= PK_READ_2_BYTE();
g->hoff= (signed short int)PK_READ_2_BYTE();
g->voff= (signed short int)PK_READ_2_BYTE();
}
else
{i= i+4;
i= i+8;
g->w= PK_READ_4_BYTE();
g->h= PK_READ_4_BYTE();
g->hoff= (signed int)PK_READ_4_BYTE();
g->voff= (signed int)PK_READ_4_BYTE();
}
if((g->pk_glyph_flags>>4)==14)bits= pk_bitmap(g,pk_data+i);
else bits= pk_runlength(g,pk_data+i);
if(bits!=NULL)
{g->OGLtexture= nativeTexture(bits,g->w,g->h);
free(bits);
}
g->hoff*= font_def[f].hpxs;
g->voff*= font_def[f].vpxs;
g->w*= font_def[f].hpxs;
g->h*= font_def[f].vpxs;
}
/*:638*//*639:*/
#line 12864 "hint.w"





#define PK_XXX1 240
#define PK_XXX2 241
#define PK_XXX3 242
#define PK_XXX4 243
#define PK_YYY  244
#define PK_POST 245
#define PK_NO_OP 246
#define PK_PRE   247
#define PK_ID    89

static Gcache*hnew_glyph(FontDef*fp,unsigned int cc);

static int unpack_pk_file(internal_font_number f)

{int i,j;
unsigned int k;
unsigned char flag;
unsigned char*pk_data;
int pk_size;
{unsigned char*spos,*sstart,*send;
spos= hpos;sstart= hstart;send= hend;
hget_section(font_def[f].q);
pk_data= hstart;
pk_size= hend-hstart;
hpos= spos;hstart= sstart;hend= send;
}
if(pk_data[0]!=PK_PRE||pk_data[1]!=PK_ID)
return 0;
i= 0;
while(i<pk_size)
switch(flag= pk_data[i++])
{case PK_XXX1:j= PK_READ_1_BYTE();i= i+j;break;
case PK_XXX2:j= PK_READ_2_BYTE();i= i+j;break;
case PK_XXX3:j= PK_READ_3_BYTE();i= i+j;break;
case PK_XXX4:j= PK_READ_4_BYTE();i= i+j;break;
case PK_YYY:i= i+4;break;
case PK_NO_OP:break;
case PK_PRE:
{int csize;
unsigned int ds;
unsigned char id;
unsigned sdpp;
id= PK_READ_1_BYTE();
if(id!=PK_ID)return 0;
csize= PK_READ_1_BYTE();
i= i+csize;
ds= PK_READ_4_BYTE();
i= i+4;
sdpp= PK_READ_4_BYTE();
font_def[f].hpxs= ((uint64_t)1<<32)/sdpp;
sdpp= PK_READ_4_BYTE();
font_def[f].vpxs= ((uint64_t)1<<32)/sdpp;
if(ds!=(font_def[f].s<<4))
{double m= (double)(font_def[f].s<<4)/ds;
font_def[f].hpxs*= m;
font_def[f].vpxs*= m;
}
}
break;
case PK_POST:break;
case 248:case 249:case 250:case 251:case 252:case 253:case 254:case 255:break;
default:
{unsigned int pl;
unsigned int cc;
Gcache*g;
if((flag&7)==7)
{pl= PK_READ_4_BYTE();
cc= PK_READ_4_BYTE();
}else if((flag&4)==4)
{pl= PK_READ_2_BYTE();
cc= PK_READ_1_BYTE();
pl= pl+((flag&3)<<16);
}else
{pl= PK_READ_1_BYTE();
cc= PK_READ_1_BYTE();
pl= pl+((flag&3)<<8);
}
g= hnew_glyph(font_def+f,cc);
g->pk_glyph_flags= flag;
g->pk_glyph_data= pk_data+i;
i= i+pl;
}
break;
}
return 1;
}

/*:639*/
#line 14814 "hint.w"

/*475:*/
#line 9391 "hint.w"

static void hget_par_node(uint32_t offset)
{scaled x= 0;
ParamDef*q;
/*374:*/
#line 7666 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:374*/
#line 9395 "hint.w"

node_pos= (hpos-hstart)-1;
if(KIND(a)!=par_kind)
tag_expected(TAG(par_kind,0),a,node_pos);
node_pos= (hpos-hstart)-1;
if(INFO(a)==b100)q= hget_param_list_ref(HGET8);
if(INFO(a)&b100)x= hget_xdimen_node();else x= hget_xdimen_ref(HGET8);
if(INFO(a)&b010)q= hget_param_list_node();else q= hget_param_list_ref(HGET8);
hget_paragraph(x,offset,q);
/*375:*/
#line 7671 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:375*/
#line 9404 "hint.w"

}
/*:475*//*479:*/
#line 9479 "hint.w"

static void hteg_par_node(uint32_t offset)
{scaled x= 0;
ParamDef*save_lbp= line_break_params;
pointer p;
pointer par_head= tail;
uint8_t*bs_pos= cur_list.bs_pos;
scaled ph= prev_height;
/*374:*/
#line 7666 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:374*/
#line 9487 "hint.w"

node_pos= (hpos-hstart)-1;
if(INFO(a)&b100)x= hget_xdimen_node();else x= hget_xdimen_ref(HGET8);
if(INFO(a)&b010)line_break_params= hget_param_list_node();else line_break_params= hget_param_list_ref(HGET8);
prev_graf= 0;
p= hget_paragraph_initial(x,hstart+node_pos+offset);
/*375:*/
#line 7671 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:375*/
#line 9493 "hint.w"

cur_list.bs_pos= NULL;
if(p!=null)
line_break(hget_integer_ref(widow_penalty_no),p);
if(par_head!=tail)
/*478:*/
#line 9455 "hint.w"

{pointer p,r,par_tail;
p= null;
r= par_tail= link(par_head);

tail= par_head;
link(tail)= null;
while(r!=null)
{pointer q= link(r);
link(r)= p;
p= r;
r= q;
}
cur_list.bs_pos= bs_pos;
prev_height= ph;
hprepend_to_vlist(p);
tail= par_tail;
if(type(tail)==hlist_node||type(tail)==vlist_node)
prev_height= height(tail);
}
/*:478*/
#line 9498 "hint.w"

hpos= hstart+node_pos;
line_break_params= save_lbp;
}

/*:479*//*558:*/
#line 10896 "hint.w"

static bool hloc_next(void)
{int i= cur_loc;
if(hstart+LOC_POS(page_loc[cur_loc])>=hend)
return false;
NEXT_PAGE(i);
if(i==hi_loc)
return false;
cur_loc= i;
return true;
}

static bool hloc_prev(void)
{int i= cur_loc;
if(page_loc[cur_loc]==0)
return false;
PREV_PAGE(i);
if(i==lo_loc)
return false;
cur_loc= i;
return true;
}
/*:558*//*561:*/
#line 10947 "hint.w"


static void hloc_set(uint64_t h)
{int i;
if(page_loc[cur_loc]==h)return;
for(i= lo_loc,NEXT_PAGE(i);i!=hi_loc;NEXT_PAGE(i))
if(page_loc[i]==h)
{cur_loc= i;
DBG(DBGPAGE,"loc_set: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
return;}
page_loc[cur_loc]= h;
hloc_clear();
DBG(DBGPAGE,"loc_set: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
}
/*:561*//*565:*/
#line 11059 "hint.w"


uint64_t hint_page_top(uint64_t h)
{if(hin_addr==NULL)return 0;
hpos= hstart+LOC_POS0(h);
if(hpos>=hend)
return hint_page_bottom(hend-hstart);
hflush_contribution_list();
hloc_set(h);
if(LOC_OFF(h))
hget_par_node(LOC_OFF(h));
hint_forward();
forward_mode= true;
backward_mode= false;
return h;
}
/*:565*//*566:*/
#line 11079 "hint.w"

uint64_t hint_page_get(void)
{
DBG(DBGPAGE,"page_get: %d : 0x%"PRIx64"\n",cur_loc,page_loc[cur_loc]);

if(hin_addr==NULL)return 0;
return page_loc[cur_loc];
}
/*:566*//*567:*/
#line 11095 "hint.w"

uint64_t hint_page(void)
{uint64_t i;
if(streams==NULL)return 0;
i= hint_page_get();
if(streams[0].p!=null)
return i;
else
return hint_page_top(i);
}
/*:567*//*568:*/
#line 11111 "hint.w"

uint64_t hint_page_home(void)
{uint64_t pos;
uint8_t where;
int n= zero_label_no;
if(hin_addr==NULL)return 0;
/*363:*/
#line 7434 "hint.w"

if(labels==NULL||n> max_ref[label_kind])
{where= LABEL_TOP;pos= 0;}
else
{where= labels[n].where;
#if 1
pos= ((uint64_t)labels[n].pos<<32)+(labels[n].pos-labels[n].pos0);
#else
#line 7442 "hint.w"
 pos= ((uint64_t)labels[n].pos0<<32);

#endif
#line 7445 "hint.w"
}
/*:363*/
#line 11117 "hint.w"

/*587:*/
#line 11557 "hint.w"

if(where==LABEL_TOP)return hint_page_top(pos);
else if(where==LABEL_BOT)return hint_page_bottom(pos);
else if(where==LABEL_MID)return hint_page_middle(pos);
else return hint_page_get();
/*:587*/
#line 11118 "hint.w"

}
/*:568*//*569:*/
#line 11139 "hint.w"

double hint_get_fpos(void)
{
DBG(DBGPAGE,"get_fpos: %d : 0x%"PRIx64"\n",cur_loc,page_loc[cur_loc]);

if(hin_addr==NULL)return 0.0;
return(double)LOC_POS(page_loc[cur_loc])/(double)(hend-hstart);
}
/*:569*//*570:*/
#line 11153 "hint.w"

uint64_t hint_set_fpos(double fpos)
{uint32_t pos,pos0;
uint8_t*p,*q;
DBG(DBGPAGE,"set_fpos: %f\n",fpos);
if(hin_addr==NULL)return 0;
if(fpos<0.0)fpos= 0.0;
if(fpos> 1.0)fpos= 1.0;
pos= round((hend-hstart)*fpos);
p= hstart+pos;
q= hpos= hstart;
while(hpos<p)
{q= hpos;hff_hpos();}
if(hpos> p)
{pos= pos0= q-hstart;
if(KIND(*q)==par_kind&&KIND(hff_tag)==list_kind&&hff_list_size> 0)
{if(p>=hstart+hff_list_pos+hff_list_size)
pos= pos0= hpos-hstart;
else
{q= hpos= hstart+hff_list_pos;
while(hpos<=p)
{if(KIND(*hpos)==glue_kind||KIND(*hpos)==penalty_kind||KIND(*hpos)==disc_kind)
q= hpos;
hff_hpos();
}
pos= q-hstart;
}
}
}
else
pos= pos0= hpos-hstart;
return hint_page_top(PAGE_LOC(pos0,pos-pos0));
}
/*:570*//*572:*/
#line 11198 "hint.w"

uint64_t hint_page_next(void)
{if(hin_addr==NULL)return 0;
if(hloc_next()&&forward_mode)
{if(!hint_forward())
{hloc_prev();return hint_page();}
forward_mode= true;
backward_mode= false;
return hint_page_get();
}
else
{hflush_contribution_list();hpage_init();
return hint_page();
}
}
/*:572*//*573:*/
#line 11223 "hint.w"

uint64_t hint_page_prev(void)
{if(hin_addr==NULL)return 0;
if(hloc_prev())
{hflush_contribution_list();hpage_init();
return hint_page();
}
else if(backward_mode)
{if(!hint_backward())return hint_page_top(0);
backward_mode= true;
forward_mode= false;
return hint_page_get();
}
else
return hint_page_bottom(hint_page_get());
}
/*:573*//*574:*/
#line 11249 "hint.w"

uint64_t hint_page_bottom(uint64_t h)
{if(hin_addr==NULL)return 0;
hloc_set(h);
hflush_contribution_list();
hpos= hstart+LOC_POS0(h);
if(LOC_OFF(h))
hteg_par_node(LOC_OFF(h));
if(!hint_backward())return hint_page();
backward_mode= true;
forward_mode= false;
return hint_page_get();
}
/*:574*//*575:*/
#line 11280 "hint.w"

uint64_t hint_page_middle(uint64_t l)
{uint32_t target_pos,pos0,offset;
pointer p;
scaled h= 0,d= 0,hp,dp,target_dist= 0,break_dist= 0;
int pi= 0;
if(hin_addr==NULL)return 0;
target_pos= LOC_POS(l);
offset= LOC_OFF(l);
pos0= LOC_POS0(l);
if(hstart+pos0+offset>=hend)
return hint_page_bottom(hend-hstart);
hflush_contribution_list();
hpos= hstart+pos0;
hget_content();

if(offset> 0)
/*576:*/
#line 11322 "hint.w"

{pointer q,target_q;
/*577:*/
#line 11339 "hint.w"

target_q= null;
q= contrib_head;p= link(q);
h= d= target_dist= break_dist= 0;
while(p!=null)
{pointer qq;
/*579:*/
#line 11383 "hint.w"

switch(type(p))
{case hlist_node:case vlist_node:case rule_node:
hp= height(p);dp= depth(p);
pi= inf_penalty;
break;
case glue_node:
hp= width(glue_ptr(p));dp= 0;
pi= 0;
break;
case kern_node:
hp= width(p);dp= 0;
pi= inf_penalty;
break;
case penalty_node:
hp= dp= 0;
pi= penalty(p);
break;
default:
pi= hp= dp= 0;
}
/*:579*/
#line 11345 "hint.w"

qq= q;
q= p;
p= link(p);
if(target_q!=null)
{if(pi<=0)
break;
}
else if(p==null||LOC_POS(hlocation(p))> target_pos)
{target_q= qq;
target_dist= h+d;
h= d= 0;
}
h+= d+hp;
d= dp;
}
if(target_q==null)
{target_dist= h;break_dist= 0;}
else
break_dist= h;
/*:577*/
#line 11324 "hint.w"

if(target_dist+break_dist<=hvsize)
offset= 0;
else
{if(break_dist>=hvsize)
q= target_q;
else
/*580:*/
#line 11412 "hint.w"

{scaled dh;
dh= target_dist+break_dist-hvsize;
if(target_dist-dh> hvsize/2)
dh= target_dist-hvsize/2;
q= contrib_head;
p= link(q);
d= 0;
while(p!=null&&q!=target_q&&dh> 0)
{/*579:*/
#line 11383 "hint.w"

switch(type(p))
{case hlist_node:case vlist_node:case rule_node:
hp= height(p);dp= depth(p);
pi= inf_penalty;
break;
case glue_node:
hp= width(glue_ptr(p));dp= 0;
pi= 0;
break;
case kern_node:
hp= width(p);dp= 0;
pi= inf_penalty;
break;
case penalty_node:
hp= dp= 0;
pi= penalty(p);
break;
default:
pi= hp= dp= 0;
}
/*:579*/
#line 11421 "hint.w"

dh= dh-hp-d;
d= dp;
q= p;
p= link(p);
}
}
/*:580*/
#line 11332 "hint.w"

/*578:*/
#line 11368 "hint.w"

{p= link(q);
offset= LOC_OFF(hlocation(p));
link(q)= null;
flush_node_list(link(contrib_head));
link(contrib_head)= p;
}
/*:578*/
#line 11333 "hint.w"

goto found;
}
}
/*:576*/
#line 11297 "hint.w"

/*581:*/
#line 11435 "hint.w"

{pointer h_save= link(contrib_head);
pointer t_save= tail;
uint8_t*hpos_save= hpos;
pointer best_p= null;
int best_pi= 0;
link(contrib_head)= null;tail= contrib_head;
hpos= hstart+pos0;
h= target_dist+break_dist;
d= 0;
p= tail;
while(h<hvsize)
{while(link(p)==null&&hpos> hstart)
hteg_content();
if(link(p)==null)break;
p= link(p);
/*579:*/
#line 11383 "hint.w"

switch(type(p))
{case hlist_node:case vlist_node:case rule_node:
hp= height(p);dp= depth(p);
pi= inf_penalty;
break;
case glue_node:
hp= width(glue_ptr(p));dp= 0;
pi= 0;
break;
case kern_node:
hp= width(p);dp= 0;
pi= inf_penalty;
break;
case penalty_node:
hp= dp= 0;
pi= penalty(p);
break;
default:
pi= hp= dp= 0;
}
/*:579*/
#line 11451 "hint.w"

if(hpos==hstart)pi= eject_penalty;
if(h+hp+d> hvsize)
break;
h= h+d+hp;d= dp;
if(pi<best_pi)
{best_pi= pi;
best_p= p;
if(best_pi<=eject_penalty)break;
}
}
if(best_p==null)
{flush_node_list(link(contrib_head));
hpos= hstart+pos0;
offset= 0;
}
else
{p= link(contrib_head);
do{pointer q;
q= link(p);
link(p)= h_save;
h_save= p;
p= q;
}while(h_save!=best_p);
flush_node_list(p);
pos0= LOC_POS0(hlocation(best_p));
offset= 0;
}
link(contrib_head)= h_save;
if(t_save!=contrib_head)
tail= t_save;
hpos= hpos_save;
}
/*:581*/
#line 11298 "hint.w"

found:
hloc_set(PAGE_LOC(pos0,offset));
if(!hint_forward())return hint_page_top(0);
forward_mode= true;
backward_mode= false;
return hint_page_get();
}
/*:575*//*586:*/
#line 11546 "hint.w"

uint64_t hint_outline_page(int i)
{uint64_t pos;
uint8_t where;
if(i<0||i> max_outline||hint_outlines==NULL)return hint_page_get();
pos= hint_outlines[i].pos;
where= hint_outlines[i].where;
/*587:*/
#line 11557 "hint.w"

if(where==LABEL_TOP)return hint_page_top(pos);
else if(where==LABEL_BOT)return hint_page_bottom(pos);
else if(where==LABEL_MID)return hint_page_middle(pos);
else return hint_page_get();
/*:587*/
#line 11553 "hint.w"

}
/*:586*//*592:*/
#line 11755 "hint.w"

void hint_set_mark(char*m,int s)
{m_str= m;
m_length= s;
/*593:*/
#line 11766 "hint.w"

if(m_length> 0)
{int i,j,k;
for(i= j= k= 0;i<m_length&&m_str[i]==' ';i++)continue;
for(;i<m_length;i++)
if(m_str[i]!=' '||m_str[i+1]!=' ')
{m_str[k]= m_str[i];
if(m_str[k]==' ')j++;
k++;
}
m_str[k]= 0;
m_length= k;
m_chars= m_length-j;
}
/*:593*/
#line 11759 "hint.w"

hmark_page();
}
/*:592*//*596:*/
#line 11863 "hint.w"

static void m_put(uint32_t d)
{if(m_ptr<MAX_M_DIST)
{if(d==HINT_NO_POS)
m_dist[m_max= m_ptr]= 0xFF;
else if(d<0x7F)
m_dist[m_ptr++]= 0x80+d;
else
{if(d<(1<<14))
{
two_byte:
m_dist[m_ptr++]= d>>7;
m_dist[m_ptr++]= 0x80+(d&0x7F);
return;
}
if(d>=(1<<28))m_dist[m_ptr++]= d>>28;
if(d>=(1<<21))m_dist[m_ptr++]= (d>>21)&0x7F;
if(d>=(1<<14))m_dist[m_ptr++]= (d>>14)&0x7F;
d= d&((1<<14)-1);
goto two_byte;
}
}
}

static uint32_t m_get(void)
{uint32_t x,y;
x= m_dist[m_ptr++];
if(x==0xFF)return HINT_NO_POS;
if(x&0x80)return x&0x7F;
while(true)
{y= m_dist[m_ptr++];
if(y&0x80)return(x<<7)+(y&0x7F);
x= (x<<7)+y;
}
}
/*:596*//*597:*/
#line 11906 "hint.w"

static int m_next(int i)
{while((0x80&m_dist[i])==0)i++;
if(m_dist[i]==0xFF)return 0;
else return i+1;
}

static int m_prev(int i)
{if(i<=0)return m_max;
i--;
while(i> 0&&(0x80&m_dist[i-1])==0)i--;
return i;
}
/*:597*//*599:*/
#line 11937 "hint.w"

static void next_m_char(uint32_t c)
{
reconsider:
if(m_state==0&&c!=m_str[0])
{if(c!=' ')
m_d++;
}
else if(c==m_str[m_state])
{if(m_state==0)m_spaces= 0;
m_state++;
if(m_state==m_length)
{m_put(m_d);
m_d= 0;
m_state= 0;
}
}
else
/*600:*/
#line 11971 "hint.w"

{int i= 0,j= 0;
do{
if(m_str[i]==' ')j++;
i++;
}while(i<m_state&&strncmp(m_str,m_str+i,m_state-i)!=0);
m_d= m_d+i-j;
m_state= m_state-i;
goto reconsider;
}
/*:600*/
#line 11955 "hint.w"



}
/*:599*//*602:*/
#line 11990 "hint.w"

static void hmark_page(void)
{if(streams==NULL||streams[0].p==null)return;
m_ptr= 0;
if(m_page!=page_loc[cur_loc])
{m_page= page_loc[cur_loc];
m_focus= 0;
}
if(m_length> 0)
{m_d= 0;
m_state= 0;
trv_init(next_m_char);
if(type(streams[0].p)==vlist_node)
trv_vlist(list_ptr(streams[0].p));
else
trv_hlist(list_ptr(streams[0].p));
}
m_put(HINT_NO_POS);
if(m_focus>=m_max)m_focus= 0;
}
/*:602*//*610:*/
#line 12125 "hint.w"

static void hSetColor(int c);

static void c_ignore_list(pointer p)
{int s,max_s;
s= cur_style;
max_s= 0;
while(p!=null)
{if((is_char_node(p)&&character(p)!=' ')||
(type(p)==whatsit_node&&subtype(p)==utf_char_node))
{/*607:*/
#line 12057 "hint.w"

next_style= cur_style;
while(m_d==0)
{next_style= next_style> 0?0:1;
if(next_style> 0)
{if(m_ptr==m_focus)next_style= 2;
m_d= m_chars;
}
else
m_d= m_get();
}
m_d--;
/*:607*/
#line 12135 "hint.w"

cur_style= next_style;
if(next_style> max_s)max_s= next_style;
}
else
{switch(type(p))
{case hlist_node:
case vlist_node:c_ignore_list(list_ptr(p));break;
case ligature_node:
{pointer q= lig_ptr(p);
while(q!=null)
{/*607:*/
#line 12057 "hint.w"

next_style= cur_style;
while(m_d==0)
{next_style= next_style> 0?0:1;
if(next_style> 0)
{if(m_ptr==m_focus)next_style= 2;
m_d= m_chars;
}
else
m_d= m_get();
}
m_d--;
/*:607*/
#line 12146 "hint.w"

cur_style= next_style;
if(next_style> max_s)max_s= next_style;
q= link(q);
}
}
break;
}
}
p= link(p);
}
if(s!=max_s)
{cur_style= max_s;
hSetColor(cur_color);
}
else
cur_style= s;
}
/*:610*//*611:*/
#line 12186 "hint.w"

bool hint_prev_mark(void)
{m_focus= m_prev(m_focus);
while(m_focus==0&&m_page> 0)
{hint_page_prev();
m_focus= m_prev(0);
}
return(m_focus!=0);
}

bool hint_next_mark(void)
{m_focus= m_next(m_focus);
while(m_focus==0)
{uint64_t p= m_page;
if(p==hint_page_next())break;
m_focus= m_next(0);
}
return(m_focus!=0);
}
/*:611*//*619:*/
#line 12296 "hint.w"

static int links_allocated= 0;
static void add_new_link(int n,pointer p,scaled h,scaled v)
{Link*t;
uint64_t pos;
uint8_t where;
max_link++;
if(max_link>=links_allocated)
{if(links_allocated<=0)
{links_allocated= 32;
ALLOCATE(hlinks,links_allocated,Link);
}
else
{links_allocated= links_allocated*1.4142136+0.5;
REALLOCATE(hlinks,links_allocated,Link);
}
DBG(DBGLABEL,"Links allocated %d\n",links_allocated);
}
t= hlinks+max_link;
DBG(DBGLABEL,"Link add %d\n",max_link);
REF_RNG(label_kind,n);
/*363:*/
#line 7434 "hint.w"

if(labels==NULL||n> max_ref[label_kind])
{where= LABEL_TOP;pos= 0;}
else
{where= labels[n].where;
#if 1
pos= ((uint64_t)labels[n].pos<<32)+(labels[n].pos-labels[n].pos0);
#else
#line 7442 "hint.w"
 pos= ((uint64_t)labels[n].pos0<<32);

#endif
#line 7445 "hint.w"
}
/*:363*/
#line 12317 "hint.w"

t->where= where;
t->pos= pos;
if(type(p)==hlist_node)
{scaled hp= height(p),dp= depth(p);
t->top= v-hp;
t->bottom= v+dp;
t->left= h;
t->right= h;
}
else
{t->top= v;
t->bottom= v;
t->left= h;
t->right= h+width(p);
}
}

static void end_new_link(int n,pointer p,scaled h,scaled v)
{Link*t;
if(max_link<0)return;
t= hlinks+max_link;
DBG(DBGLABEL,"Link end %d\n",max_link);
if(type(p)==hlist_node)
t->right= h;
else
t->bottom= v;
}
/*:619*//*620:*/
#line 12369 "hint.w"

static scaled hlink_distance(scaled x,scaled y,Link*t)
{scaled d,dx= 0,dy= 0;
d= t->top-y;
if(d> 0)dy= d;
else
{d= y-t->bottom;
if(d> 0)dy= d;
}
d= x-t->right;
if(d> 0)dx= d;
else
{d= t->left-x;
if(d> 0)dx= d;
}
if(dx> dy)return dx;
else return dy;

}

static int last_hit_link= -1;

int hint_find_link(int x_px,int y_px,int precission_px)
{scaled x,y,precission;
int i;
Link*t;
if(max_link<0)return-1;
if(last_hit_link<0||last_hit_link> max_link)last_hit_link= max_link/2;
i= last_hit_link;
t= hlinks+i;
DBG(DBGLABEL,"Link find %d\n",max_link);
x= x_px*x_px_size;
y= y_px*y_px_size;
precission= precission_px*y_px_size;
if(hlink_distance(x,y,t)<=precission)
return i;
else if(y<t->top)
{while(i> 0)
{i--;
t= hlinks+i;
DBG(DBGLABEL,"Link up %d\n",max_link);
if(hlink_distance(x,y,t)<=precission)
{last_hit_link= i;return i;}
}
return-1;
}
else
{int k;
scaled d,min_d= precission;
int min_i= -1;
for(k= 0;k<=max_link;k++)
{i= i+1;
if(i> max_link)i= 0;
t= hlinks+i;
DBG(DBGLABEL,"Link scan %d\n",max_link);
d= hlink_distance(x,y,t);
if(d<min_d)
{min_d= d;min_i= i;}
}
last_hit_link= min_i;
return last_hit_link;
}
}
/*:620*//*621:*/
#line 12438 "hint.w"

uint64_t hint_link_page(int i)
{uint64_t h;
uint8_t w;
if(i<0||i> max_link)return hint_page_get();
DBG(DBGLABEL,"Link page %d\n",max_link);
h= hlinks[i].pos;
w= hlinks[i].where;
if(w==LABEL_TOP)return hint_page_top(h);
else if(w==LABEL_BOT)return hint_page_bottom(h);
else if(w==LABEL_MID)return hint_page_middle(h);
else return hint_page_get();
}
/*:621*//*622:*/
#line 12470 "hint.w"

#define CUR_FG FG(CURCOLOR(cur_mode,cur_style,color_def[cur_color]))
#define CUR_BG BG(CURCOLOR(cur_mode,cur_style,color_def[cur_color]))

static void hSetColor(int c)
{cur_color= c;
cur_fg= CUR_FG;
nativeSetForeground(cur_fg);
}

void hint_render_on(void)
{nativeInit();
hSetColor(0);

}

void hint_render_off(void)
{hint_clear_fonts(false);
nativeClear();
}
/*:622*//*623:*/
#line 12494 "hint.w"


void hint_dark(int dark)
{cur_mode= dark?1:0;
hSetColor(cur_color);
}

void hint_gamma(double gamma)
{nativeSetGamma(gamma);
}
/*:623*//*649:*/
#line 13239 "hint.w"

static void ft_unpack_glyph(uint8_t f,Gcache*g,uint32_t cc)
{int e,i;
unsigned char*bits;
FT_Face ft_face= font_def[f].ft_face;
if(ft_face==NULL)
ft_face= ft_load_font_face(f);
if(ft_face==NULL)
QUIT("Unable to create FreeType face for font %d (%s)",f,font_def[f].n);
/*648:*/
#line 13211 "hint.w"

if(font_def[f].hpxs!=x_px_size||font_def[f].vpxs!=y_px_size)
{FT_F26Dot6 ft_size;
ft_size= font_def[f].s*(72.00/72.27)*((double)(1<<6)/(double)(1<<16))+0.5;
font_def[f].hpxs= x_px_size;
font_def[f].vpxs= y_px_size;
ft_err= FT_Set_Char_Size(
ft_face,
0,
ft_size,
72.27/(font_def[f].hpxs/(double)ONE),
72.27/(font_def[f].vpxs/(double)ONE));
if(ft_err)QUIT("Unable to set FreeType glyph size");
}
/*:648*/
#line 13248 "hint.w"

i= FT_Get_Char_Index(ft_face,cc);
e= FT_Load_Glyph(
ft_face,
i,
FT_LOAD_RENDER|FT_LOAD_TARGET_NORMAL);
if(e)MESSAGE("0x%xUnable to render FreeType glyph '%c' (%u)",e,(char)cc,cc);

g->w= ft_face->glyph->bitmap.width;
g->h= ft_face->glyph->bitmap.rows;
g->hoff= -ft_face->glyph->bitmap_left;
g->voff= ft_face->glyph->bitmap_top-1;
bits= calloc(g->w*g->h,1);
if(bits==NULL)QUIT("Out of memory for FreeType glyph %c (%u)",(char)cc,cc);
memcpy(bits,ft_face->glyph->bitmap.buffer,g->w*g->h);
g->OGLtexture= nativeTexture(bits,g->w,g->h);
free(bits);
g->hoff*= font_def[f].hpxs;
g->voff*= font_def[f].vpxs;
g->w*= font_def[f].hpxs;
g->h*= font_def[f].vpxs;
}

/*:649*//*654:*/
#line 13335 "hint.w"

#define G0_BITS 7
#define G0_SIZE (1<<G0_BITS)
#define G0_MASK (G0_SIZE-1)
#define G123_BITS 6
#define G123_SIZE (1<<G123_BITS)
#define G123_MASK (G123_SIZE-1)

static Gcache*g_lookup(FontDef*f,unsigned int cc)

{if(cc>>G0_BITS){
unsigned int cc1= (cc>>G0_BITS);
if(cc1>>G123_BITS){
unsigned int cc2= cc1>>G123_BITS;
if(cc2>>G123_BITS){
unsigned int cc3= cc2>>G123_BITS;
if(cc3>>G123_BITS)return NULL;
else if(f->g3&&
f->g3[cc3&G123_MASK]&&
f->g3[cc3&G123_MASK][cc2&G123_MASK]&&
f->g3[cc3&G123_MASK][cc2&G123_MASK][cc1&G123_MASK])
return f->g3[cc3&G123_MASK][cc2&G123_MASK][cc1&G123_MASK][cc&G0_MASK];
}
else if(f->g2&&f->g2[cc2&G123_MASK]&&f->g2[cc2&G123_MASK][cc1&G123_MASK])
return f->g2[cc2&G123_MASK][cc1&G123_MASK][cc&G0_MASK];
}
else if(f->g1&&f->g1[cc1&G123_MASK])
return f->g1[cc1&G123_MASK][cc&G0_MASK];
}
else if(f->g0)
return f->g0[cc];
return NULL;
}
/*:654*//*656:*/
#line 13382 "hint.w"

static Gcache*hnew_g(Gcache**g)
{if(*g==NULL)
*g= calloc(1,sizeof(Gcache));
if(*g==NULL)
return&g_undefined;
(*g)->OGLtexture= 0;
return*g;
}

static Gcache*hnew_g0(Gcache***g,unsigned int cc)
{unsigned int cc0= cc&G0_MASK;
if(*g==NULL)
*g= calloc(G0_SIZE,sizeof(Gcache*));
if(*g==NULL)
return&g_undefined;
return hnew_g((*g)+cc0);
}

static Gcache*hnew_g1(Gcache****g,unsigned int cc)
{unsigned int cc1= (cc>>G0_BITS)&G123_MASK;
if(*g==NULL)
*g= calloc(G123_SIZE,sizeof(Gcache**));
if(*g==NULL)
return&g_undefined;
return hnew_g0((*g)+cc1,cc);
}
static Gcache*hnew_g2(Gcache*****g,unsigned int cc)
{unsigned int cc2= (cc>>(G123_BITS+G0_BITS))&G123_MASK;
if(*g==NULL)
*g= calloc(G123_SIZE,sizeof(Gcache***));
if(*g==NULL)
return&g_undefined;
return hnew_g1((*g)+cc2,cc);
}

static Gcache*hnew_g3(Gcache******g,unsigned int cc)
{unsigned int cc3= (cc>>(G123_BITS+G123_BITS+G0_BITS))&G123_MASK;
if(*g==NULL)
*g= calloc(G123_SIZE,sizeof(Gcache****));
if(*g==NULL)
return&g_undefined;
return hnew_g2((*g)+cc3,cc);
}


static Gcache*hnew_glyph(FontDef*f,unsigned int cc)
{if(cc<G0_SIZE)return hnew_g0(&(f->g0),cc);
else if(cc<G123_SIZE*G0_SIZE)return hnew_g1(&(f->g1),cc);
else if(cc<G123_SIZE*G123_SIZE*G0_SIZE)return hnew_g2(&(f->g2),cc);
else if(cc<G123_SIZE*G123_SIZE*G123_SIZE*G0_SIZE)return hnew_g3(&(f->g3),cc);
else return&g_undefined;
}
/*:656*//*657:*/
#line 13446 "hint.w"

static void hfree_g0(Gcache**g,bool rm)
{int i;
if(g==NULL)return;
for(i= 0;i<G0_SIZE;i++)
if(g[i]!=NULL)
{if(g[i]->OGLtexture!=0)
g[i]->OGLtexture= nativeFreeTexture(g[i]->OGLtexture);
if(rm){
free(g[i]);g[i]= NULL;}
}
}

static void hfree_g1(Gcache***g,bool rm)
{int i;
if(g==NULL)return;
for(i= 0;i<G123_SIZE;i++)
if(g[i]!=NULL)
{hfree_g0(g[i],rm);
if(rm){free(g[i]);g[i]= NULL;}
}
}

static void hfree_g2(Gcache****g,bool rm)
{int i;
if(g==NULL)return;
for(i= 0;i<G123_SIZE;i++)
if(g[i]!=NULL)
{hfree_g1(g[i],rm);
if(rm){free(g[i]);g[i]= NULL;}
}
}


static void hfree_g3(Gcache*****g,bool rm)
{int i;
if(g==NULL)return;
for(i= 0;i<G123_SIZE;i++)
if(g[i]!=NULL)
{hfree_g2(g[i],rm);
if(rm){free(g[i]);g[i]= NULL;}
}
}


static void hfree_glyph_cache(FontDef*f,bool rm)
{if(f->g0!=NULL)
{hfree_g0(f->g0,rm);
if(rm){free(f->g0);f->g0= NULL;}
}
if(f->g1!=NULL)
{hfree_g1(f->g1,rm);
if(rm){free(f->g1);f->g1= NULL;}
}
if(f->g2!=NULL)
{hfree_g2(f->g2,rm);
if(rm){free(f->g2);f->g2= NULL;}
}
if(f->g3!=NULL)
{hfree_g3(f->g3,rm);
if(rm){free(f->g3);f->g3= NULL;}
}
}
/*:657*//*659:*/
#line 13562 "hint.w"

static void ft_unpack_glyph(uint8_t f,Gcache*g,uint32_t cc);

static Gcache*hload_glyph(uint8_t f,unsigned int cc)
{
Gcache*g= NULL;
g= g_lookup(font_def+f,cc);
if(g==NULL)
{if(font_def[f].ff==no_format)hload_font(f);
if(font_def[f].ff==ft_format)
g= hnew_glyph(font_def+f,cc);
else
return NULL;
}
if(g->OGLtexture==0)
{if(font_def[f].ff==pk_format)pk_unpack_glyph(f,g);
else if(font_def[f].ff==ft_format)ft_unpack_glyph(f,g,cc);
else QUIT("Font format not supported");
}
return g;
}
/*:659*//*660:*/
#line 13599 "hint.w"

static bool round_to_pixel= 0;
static scaled pxs_threshold= ONE/2;

void hint_round_position(bool r,double t)
{round_to_pixel= r;
pxs_threshold= ONE*72.27/t+0.5;
}

static void render_char(int x,int y,uint8_t f,uint32_t cc)

{scaled w,h,dx,dy,top,left;
Gcache*g;
if(font_def[f].ff==no_format)hload_font(f);
g= hload_glyph(f,cc);
if(g==NULL||g->OGLtexture==0)return;

dx= g->hoff;
dy= g->voff;
w= g->w;
h= g->h;

left= x-dx;
top= y+h-dy;

#if 0
if(round_to_pixel)
{double pxs;
if(xdpi<dpi_threshold)
{pxs= 72.27/xdpi;
left= left/pxs;
left= floor(left+0.5);
left= left*pxs;
}
if(ydpi<dpi_threshold)
{pxs= 72.27/ydpi;
top= top/pxs;
top= floor(top+0.5);
top= top*pxs;
}
}
#endif
#line 13641 "hint.w"
 if(round_to_pixel)
{
if(x_px_size> pxs_threshold)
{left= (left+(x_px_size/2))/x_px_size;
left= left*x_px_size;
}
if(y_px_size> pxs_threshold)
{top= (top+(y_px_size/2))/y_px_size;
top= top*y_px_size;
}
}
nativeGlyph(left,top,w,h,g->OGLtexture);
}

/*:660*//*661:*/
#line 13661 "hint.w"

static void render_rule(int x,int y,int w,int h)
{if(w> 0&&h> 0)
nativeRule(x,y,w,h);
}
/*:661*//*662:*/
#line 13673 "hint.w"

static void render_image(int x,int y,int w,int h,uint32_t n)
{
uint8_t*spos,*sstart,*send;
spos= hpos;sstart= hstart;send= hend;
hget_section(n);
nativeImage(x,y,w,h,hstart,hend);
hpos= spos;hstart= sstart;hend= send;
}
/*:662*//*667:*/
#line 13740 "hint.w"

uint64_t hint_blank(void)
{hSetColor(0);
nativeBlank(CUR_BG);
return 0;
}
/*:667*//*669:*/
#line 13772 "hint.w"

static void vlist_render(pointer this_box);
static scaled hcolor_distance(pointer p,
uint8_t g_sign,glue_ord g_order,glue_ratio g_set);
static scaled vcolor_distance(pointer p,
uint8_t g_sign,glue_ord g_order,glue_ratio g_set);
static void hlist_render(pointer this_box)
{scaled base_line;
scaled left_edge;
scaled h_save;
glue_ord g_order;
uint8_t g_sign;
pointer p;
pointer leader_box;
scaled leader_wd;
scaled lx;
scaled edge;
double glue_temp;
double cur_glue;
scaled cur_g;
int list_color= cur_color;
int local_link= -1;
uint8_t f;
uint32_t c;

cur_g= 0;
cur_glue= 0.0;
g_order= glue_order(this_box);
g_sign= glue_sign(this_box);
p= list_ptr(this_box);
#ifdef DEBUG
if(p==0xffff)
QUIT("Undefined list pointer in hbox 0x%x-> mem[0x%x] -> 0x%x\n",
this_box,mem[this_box].i,p);
#endif
#line 13807 "hint.w"
 base_line= cur_v;
left_edge= cur_h;
/*616:*/
#line 12264 "hint.w"

if(cur_link>=0)
{add_new_link(cur_link,this_box,cur_h,cur_v);
local_link= cur_link;
cur_link= -1;
}
/*:616*/
#line 13809 "hint.w"

while(p!=null)
{
#ifdef DEBUG
if(p==0xffff)
QUIT("Undefined pointer in hlist 0x%x\n",p);
if(link(p)==0xffff)
QUIT("Undefined link in hlist mem[0x%x]=0x%x\n",p,mem[p].i);
#endif
#line 13818 "hint.w"
 if(is_char_node(p))
{do
{f= font(p);
c= character(p);
style_c:
if(!c_ignore&&c!=' ')
{/*607:*/
#line 12057 "hint.w"

next_style= cur_style;
while(m_d==0)
{next_style= next_style> 0?0:1;
if(next_style> 0)
{if(m_ptr==m_focus)next_style= 2;
m_d= m_chars;
}
else
m_d= m_get();
}
m_d--;
/*:607*/
#line 13824 "hint.w"

if(next_style!=cur_style)
{cur_style= next_style;
hSetColor(cur_color);
}
}
render_c:
#ifdef DEBUG
if(f> max_ref[font_kind])
QUIT("Undefined Font %d mem[0x%x]=0x%x\n",
f,p,mem[p].i);
#endif
#line 13836 "hint.w"
 render_char(cur_h,cur_v,f,c);
cur_h= cur_h+char_width(f,c);
#ifdef DEBUG
if(link(p)==0xffff)
QUIT("Undefined link in charlist mem[0x%x]=0x%x\n",p,mem[p].i);
#endif
#line 13842 "hint.w"
 p= link(p);
}while(is_char_node(p));
}
else
{switch(type(p))
{case hlist_node:
case vlist_node:
#ifdef DEBUG
if(list_ptr(p)==0xffff)
QUIT("Undefined list pointer in hlist mem[0x%x] = 0x%x -> 0x%x\n",
p,mem[p].i,list_ptr(p));
#endif
#line 13854 "hint.w"
 if(list_ptr(p)==null)cur_h= cur_h+width(p);
else
{int cur_c= cur_color;
cur_v= base_line+shift_amount(p);
edge= cur_h;
if(type(p)==vlist_node)
vlist_render(p);
else
hlist_render(p);
if(cur_color!=cur_c)
hSetColor(cur_c);
cur_h= edge+width(p);cur_v= base_line;
}
break;
case rule_node:
rule_ht= height(p);rule_dp= depth(p);rule_wd= width(p);
goto fin_rule;
case whatsit_node:
switch(subtype(p))
{case ignore_node:/*609:*/
#line 12104 "hint.w"

if(ignore_info(p)==1)
{next_style= 0;
c_ignore_list(ignore_list(p));
c_ignore= true;
}
else
c_ignore= false;
/*:609*/
#line 13873 "hint.w"
break;
case color_node:
hSetColor(color_ref(p));
/*665:*/
#line 13709 "hint.w"

if(cur_color!=list_color&&(CUR_BG&0xFF)> 0)
{scaled x,y,w,h;
x= cur_h;
y= cur_v+depth(this_box);
w= hcolor_distance(link(p),g_sign,g_order,glue_set(this_box));
h= height(this_box)+depth(this_box);
if(w> 0&&h> 0)
nativeBackground(x,y,w,h,CUR_BG);
}

/*:665*/
#line 13876 "hint.w"

break;
case end_color_node:
hSetColor(list_color);
break;
case start_link_node:
/*613:*/
#line 12228 "hint.w"

local_link= label_ref(as_label(p));
add_new_link(local_link,this_box,cur_h,cur_v);
{uint32_t c= color_ref(as_color(p));
if(c==0xFF)
hSetColor(list_color);
else
hSetColor(c);
}

/*:613*/
#line 13882 "hint.w"

/*665:*/
#line 13709 "hint.w"

if(cur_color!=list_color&&(CUR_BG&0xFF)> 0)
{scaled x,y,w,h;
x= cur_h;
y= cur_v+depth(this_box);
w= hcolor_distance(link(p),g_sign,g_order,glue_set(this_box));
h= height(this_box)+depth(this_box);
if(w> 0&&h> 0)
nativeBackground(x,y,w,h,CUR_BG);
}

/*:665*/
#line 13883 "hint.w"

break;
case end_link_node:
/*614:*/
#line 12240 "hint.w"

end_new_link(local_link,this_box,cur_h,cur_v);
local_link= -1;
{uint32_t c= color_ref(as_color(p));
if(c==0xFF)
hSetColor(list_color);
else
hSetColor(c);
}
/*:614*/
#line 13886 "hint.w"

/*665:*/
#line 13709 "hint.w"

if(cur_color!=list_color&&(CUR_BG&0xFF)> 0)
{scaled x,y,w,h;
x= cur_h;
y= cur_v+depth(this_box);
w= hcolor_distance(link(p),g_sign,g_order,glue_set(this_box));
h= height(this_box)+depth(this_box);
if(w> 0&&h> 0)
nativeBackground(x,y,w,h,CUR_BG);
}

/*:665*/
#line 13887 "hint.w"

break;
case image_node:
{scaled h,w;
w= image_width(p);
h= image_height(p);
render_image(cur_h,cur_v,w,h,image_no(p));
cur_h= cur_h+w;
}break;
case utf_char_node:
f= utf_font(p);
c= utf_char(p);
goto style_c;
default:break;
}
break;
case glue_node:
{pointer g;
g= glue_ptr(p);rule_wd= width(g)-cur_g;
if(g_sign!=normal)
{if(g_sign==stretching)
{if(stretch_order(g)==g_order)
{cur_glue= cur_glue+stretch(g);
vet_glue((double)(glue_set(this_box))*cur_glue);
cur_g= round(glue_temp);
}
}
else if(shrink_order(g)==g_order)
{cur_glue= cur_glue-shrink(g);
vet_glue((double)(glue_set(this_box))*cur_glue);
cur_g= round(glue_temp);
}
}
rule_wd= rule_wd+cur_g;
if(subtype(p)>=a_leaders)
{leader_box= leader_ptr(p);
if(type(leader_box)==rule_node)
{rule_ht= height(leader_box);rule_dp= depth(leader_box);
goto fin_rule;
}
leader_wd= width(leader_box);
if((leader_wd> 0)&&(rule_wd> 0))
{rule_wd= rule_wd+10;
edge= cur_h+rule_wd;lx= 0;

if(subtype(p)==a_leaders)
{h_save= cur_h;
cur_h= left_edge+leader_wd*((cur_h-left_edge)/leader_wd);
if(cur_h<h_save)cur_h= cur_h+leader_wd;
}
else
{int lq= rule_wd/leader_wd;
int lr= rule_wd%leader_wd;
if(subtype(p)==c_leaders)cur_h= cur_h+(lr/2);
else{lx= lr/(lq+1);
cur_h= cur_h+((lr-(lq-1)*lx)/2);
}
}
while(cur_h+leader_wd<=edge)

{int cur_c= cur_color;
cur_v= base_line+shift_amount(leader_box);
h_save= cur_h;
c_ignore= true;
if(type(leader_box)==vlist_node)
vlist_render(leader_box);
else
hlist_render(leader_box);
if(cur_color!=cur_c)
hSetColor(cur_c);
c_ignore= false;
cur_v= base_line;
cur_h= h_save+leader_wd+lx;
}
cur_h= edge-10;goto next_p;
}
}
goto move_past;
}
case kern_node:
case math_node:
cur_h= cur_h+width(p);
break;
case ligature_node:
f= font(lig_char(p));
c= character(lig_char(p));
/*608:*/
#line 12074 "hint.w"

if(!c_ignore)
{pointer q;
int s,max_s;
s= cur_style;
max_s= 0;
q= lig_ptr(p);
while(q!=null)
{if(is_char_node(q)&&character(q)!=' ')
{/*607:*/
#line 12057 "hint.w"

next_style= cur_style;
while(m_d==0)
{next_style= next_style> 0?0:1;
if(next_style> 0)
{if(m_ptr==m_focus)next_style= 2;
m_d= m_chars;
}
else
m_d= m_get();
}
m_d--;
/*:607*/
#line 12083 "hint.w"

cur_style= next_style;
if(next_style> max_s)max_s= next_style;
}
q= link(q);
}
if(s!=max_s)
{cur_style= max_s;
hSetColor(cur_color);
}
else
cur_style= s;
}
/*:608*/
#line 13973 "hint.w"

goto render_c;
default:;
}
goto next_p;
fin_rule:
if(is_running(rule_ht))
rule_ht= height(this_box);
if(is_running(rule_dp))
rule_dp= depth(this_box);
rule_ht= rule_ht+rule_dp;
if((rule_ht> 0)&&(rule_wd> 0))
{cur_v= base_line+rule_dp;
render_rule(cur_h,cur_v,rule_wd,rule_ht);
cur_v= base_line;
}
move_past:cur_h= cur_h+rule_wd;
next_p:
#ifdef DEBUG
if(link(p)==0xffff)
QUIT("Undefined link in hlist mem[0x%x]=0x%x\n",p,mem[p].i);
#endif
#line 13995 "hint.w"
 p= link(p);
}
}
/*615:*/
#line 12254 "hint.w"

if(local_link>=0)
{end_new_link(local_link,this_box,cur_h,cur_v);
cur_link= local_link;
}
/*:615*/
#line 13998 "hint.w"

}

static void vlist_render(pointer this_box)
{
scaled left_edge;
scaled top_edge;
scaled save_v;
glue_ord g_order;
uint8_t g_sign;
pointer p;
pointer leader_box;
scaled leader_ht;
scaled lx;
scaled edge;
double glue_temp;
double cur_glue;
scaled cur_g;
int local_link= -1;
cur_g= 0;cur_glue= float_constant(0);
int list_color= cur_color;
g_order= glue_order(this_box);
g_sign= glue_sign(this_box);p= list_ptr(this_box);
#ifdef DEBUG
if(p==0xffff)
QUIT("Undefined list pointer in vbox 0x%x-> mem[0x%x] -> 0x%x\n",
this_box,mem[this_box].i,p);
#endif
#line 14026 "hint.w"
 left_edge= cur_h;cur_v= cur_v-height(this_box);
top_edge= cur_v;
while(p!=null)
{if(is_char_node(p))DBG(DBGTEX,"Glyph in vertical list ignored");
else
{switch(type(p))
{case hlist_node:
case vlist_node:
#ifdef DEBUG
if(list_ptr(p)==0xffff)
QUIT("Undefined list pointer in vlist mem[0x%x] = 0x%x -> 0x%x\n",
p,mem[p].i,list_ptr(p));
#endif
#line 14039 "hint.w"
 if(list_ptr(p)==null)cur_v= cur_v+height(p)+depth(p);
else
{int cur_c= cur_color;
cur_v= cur_v+height(p);save_v= cur_v;
cur_h= left_edge+shift_amount(p);
if(type(p)==vlist_node)
vlist_render(p);
else
hlist_render(p);
if(cur_color!=cur_c)
hSetColor(cur_c);
cur_v= save_v+depth(p);cur_h= left_edge;
}
break;
case rule_node:
rule_ht= height(p);rule_dp= depth(p);rule_wd= width(p);
goto fin_rule;
case whatsit_node:
switch(subtype(p))
{case color_node:
hSetColor(color_ref(p));
/*666:*/
#line 13722 "hint.w"

if(cur_color!=list_color&&(CUR_BG&0xFF)> 0)
{scaled x,y,w,h;
x= left_edge;
h= vcolor_distance(link(p),g_sign,g_order,glue_set(this_box));
y= cur_v+h;
w= width(this_box);
if(w> 0&&h> 0)
nativeBackground(x,y,w,h,CUR_BG);
}
/*:666*/
#line 14060 "hint.w"

break;
case end_color_node:
hSetColor(list_color);
break;
case start_link_node:
/*613:*/
#line 12228 "hint.w"

local_link= label_ref(as_label(p));
add_new_link(local_link,this_box,cur_h,cur_v);
{uint32_t c= color_ref(as_color(p));
if(c==0xFF)
hSetColor(list_color);
else
hSetColor(c);
}

/*:613*/
#line 14066 "hint.w"

/*666:*/
#line 13722 "hint.w"

if(cur_color!=list_color&&(CUR_BG&0xFF)> 0)
{scaled x,y,w,h;
x= left_edge;
h= vcolor_distance(link(p),g_sign,g_order,glue_set(this_box));
y= cur_v+h;
w= width(this_box);
if(w> 0&&h> 0)
nativeBackground(x,y,w,h,CUR_BG);
}
/*:666*/
#line 14067 "hint.w"

break;
case end_link_node:
/*614:*/
#line 12240 "hint.w"

end_new_link(local_link,this_box,cur_h,cur_v);
local_link= -1;
{uint32_t c= color_ref(as_color(p));
if(c==0xFF)
hSetColor(list_color);
else
hSetColor(c);
}
/*:614*/
#line 14070 "hint.w"

/*666:*/
#line 13722 "hint.w"

if(cur_color!=list_color&&(CUR_BG&0xFF)> 0)
{scaled x,y,w,h;
x= left_edge;
h= vcolor_distance(link(p),g_sign,g_order,glue_set(this_box));
y= cur_v+h;
w= width(this_box);
if(w> 0&&h> 0)
nativeBackground(x,y,w,h,CUR_BG);
}
/*:666*/
#line 14071 "hint.w"

break;
case image_node:
{scaled h,w;
w= image_width(p);
h= image_height(p);
cur_v= cur_v+h;
render_image(cur_h,cur_v,w,h,image_no(p));
}
break;
default:break;
}
break;
case glue_node:
{pointer g= glue_ptr(p);rule_ht= width(g)-cur_g;
if(g_sign!=normal)
{if(g_sign==stretching)
{if(stretch_order(g)==g_order)
{cur_glue= cur_glue+stretch(g);
vet_glue((double)(glue_set(this_box))*cur_glue);
cur_g= round(glue_temp);
}
}
else if(shrink_order(g)==g_order)
{cur_glue= cur_glue-shrink(g);
vet_glue((double)(glue_set(this_box))*cur_glue);
cur_g= round(glue_temp);
}
}
rule_ht= rule_ht+cur_g;
if(subtype(p)>=a_leaders)
{leader_box= leader_ptr(p);
if(type(leader_box)==rule_node)
{rule_wd= width(leader_box);rule_dp= 0;
goto fin_rule;
}
leader_ht= height(leader_box)+depth(leader_box);
if((leader_ht> 0)&&(rule_ht> 0))
{rule_ht= rule_ht+10;
edge= cur_v+rule_ht;lx= 0;
if(subtype(p)==a_leaders)
{save_v= cur_v;
cur_v= top_edge+leader_ht*((cur_v-top_edge)/leader_ht);
if(cur_v<save_v)cur_v= cur_v+leader_ht;
}
else
{int lq= rule_ht/leader_ht;
int lr= rule_ht%leader_ht;
if(subtype(p)==c_leaders)cur_v= cur_v+(lr/2);
else
{lx= lr/(lq+1);
cur_v= cur_v+((lr-(lq-1)*lx)/2);
}
}
while(cur_v+leader_ht<=edge)
{int cur_c= cur_color;
cur_h= left_edge+shift_amount(leader_box);
cur_v= cur_v+height(leader_box);save_v= cur_v;
c_ignore= true;
if(type(leader_box)==vlist_node)
vlist_render(leader_box);
else
hlist_render(leader_box);
if(cur_color!=cur_c)
hSetColor(cur_c);
c_ignore= false;
cur_h= left_edge;
cur_v= save_v-height(leader_box)+leader_ht+lx;
}
cur_v= edge-10;goto next_p;
}
}
}
goto move_past;
case kern_node:
cur_v= cur_v+width(p);
break;
default:;
}
goto next_p;

fin_rule:
if(is_running(rule_wd))rule_wd= width(this_box);
rule_ht= rule_ht+rule_dp;
cur_v= cur_v+rule_ht;
if((rule_ht> 0)&&(rule_wd> 0))
{render_rule(cur_h,cur_v,rule_wd,rule_ht);
}
goto next_p;

move_past:
cur_v= cur_v+rule_ht;
}
next_p:
p= link(p);
}
}

/*:669*//*670:*/
#line 14174 "hint.w"

static scaled hcolor_distance(pointer p,uint8_t g_sign,glue_ord g_order,glue_ratio g_set)
{scaled dist= 0;
double cur_glue= 0.0;
scaled cur_g= 0;
double glue_temp;
uint8_t f;
uint32_t c;
while(p!=null)
{if(is_char_node(p))
{do
{f= font(p);
c= character(p);
character_distance:
dist= dist+char_width(f,c);
p= link(p);
}while(is_char_node(p));
}
else
{switch(type(p))
{case hlist_node:
case vlist_node:
case rule_node:
case kern_node:
case math_node:
dist= dist+width(p);
break;
case ligature_node:
f= font(lig_char(p));
c= character(lig_char(p));
goto character_distance;
case whatsit_node:
switch(subtype(p))
{case start_link_node:
case end_link_node:
case color_node:
case end_color_node:
return dist;
case image_node:
dist= dist+image_width(p);
break;
case utf_char_node:
dist= dist+ft_char_width(utf_font(p),utf_char(p));
break;
default:break;
}
break;
case glue_node:
{pointer g;
scaled wd;
g= glue_ptr(p);wd= width(g)-cur_g;
if(g_sign!=normal)
{if(g_sign==stretching)
{if(stretch_order(g)==g_order)
{cur_glue= cur_glue+stretch(g);
vet_glue(g_set*cur_glue);
cur_g= round(glue_temp);
}
}
else if(shrink_order(g)==g_order)
{cur_glue= cur_glue-shrink(g);
vet_glue(g_set*cur_glue);
cur_g= round(glue_temp);
}
}
wd= wd+cur_g;
dist= dist+wd;
}
break;
default:;
}
p= link(p);
}
}
return dist;
}

/*:670*//*671:*/
#line 14253 "hint.w"

static scaled vcolor_distance(pointer p,uint8_t g_sign,glue_ord g_order,glue_ratio g_set)
{scaled dist= 0;
double cur_glue= 0.0;
scaled cur_g= 0;
double glue_temp;

while(p!=null)
{if(is_char_node(p))DBG(DBGTEX,"Glyph in vertical list ignored");
else
{switch(type(p))
{case hlist_node:
case vlist_node:
case rule_node:
dist= dist+height(p)+depth(p);
break;
case kern_node:
dist= dist+width(p);
break;
case whatsit_node:
switch(subtype(p))
{case start_link_node:
case end_link_node:
case color_node:
case end_color_node:
return dist;
case image_node:
dist= dist+image_height(p);
break;
default:break;
}
break;
case glue_node:
{pointer g;
scaled wd;
g= glue_ptr(p);wd= width(g)-cur_g;
if(g_sign!=normal)
{if(g_sign==stretching)
{if(stretch_order(g)==g_order)
{cur_glue= cur_glue+stretch(g);
vet_glue(g_set*cur_glue);
cur_g= round(glue_temp);
}
}
else if(shrink_order(g)==g_order)
{cur_glue= cur_glue-shrink(g);
vet_glue(g_set*cur_glue);
cur_g= round(glue_temp);
}
}
wd= wd+cur_g;
dist= dist+wd;
}
break;
default:;
}
p= link(p);
}
}
return dist;
}

/*:671*//*672:*/
#line 14319 "hint.w"


void hint_render(void)
{cur_style= 0;
hSetColor(0);
nativeBlank(CUR_BG);
if(streams==NULL||streams[0].p==null)return;
cur_h= 0;
cur_v= height(streams[0].p);
cur_link= -1;max_link= -1;last_hit_link= -1;
/*606:*/
#line 12040 "hint.w"

m_ptr= 0;m_d= m_get();c_ignore= false;cur_style= next_style= 0;
/*:606*/
#line 14329 "hint.w"

if(type(streams[0].p)==vlist_node)
vlist_render(streams[0].p);
else
hlist_render(streams[0].p);
}
/*:672*//*673:*/
#line 14357 "hint.w"

int hint_print_on(int w,int h,int bpr,int bpp,unsigned char*bits)
{return nativePrintStart(w,h,bpr,bpp,bits);
}

int hint_print_off(void)
{return nativePrintEnd();
}

int hint_print(unsigned char*bits)
{return nativePrint(bits);
}
/*:673*/
#line 14815 "hint.w"

#endif
#line 14817 "hint.w"


/*354:*/
#line 7309 "hint.w"

static void hinsert_stream(uint8_t n)
{REF_RNG(stream_kind,n);
if(streams[n].p==null)return;
DBG(DBGPAGE,"Filling in stream %d\n",n);
if(n> 0&&cur_page->s[n].b!=0)
{pointer p= copy_node_list(cur_page->s[n].b);
link(tail)= p;
while(link(p)!=null)p= link(p);
tail= p;
DBG(DBGPAGE,"Filling in before list %d\n",n);
}
link(tail)= streams[n].p;
tail= streams[n].t;
if(tail==null)QUIT("Tail of nonempty stream %d is null\n",n);
streams[n].p= streams[n].t= null;
DBG(DBGPAGE,"Filling in content list %d\n",n);
if(n> 0&&cur_page->s[n].a!=0)
{pointer p= copy_node_list(cur_page->s[n].a);
link(tail)= p;
while(link(p)!=null)p= link(p);
tail= p;
DBG(DBGPAGE,"Filling in after list %d\n",n);
}
}
/*:354*//*355:*/
#line 7339 "hint.w"

static void hfill_page_template(void)
{pointer p;
if(cur_page->t!=0)
{
uint8_t*spos= hpos,*sstart= hstart,*send= hend;
hget_section(1);
hpos= hpos+cur_page->t;
p= hget_list_pointer();
hpos= spos,hstart= sstart,hend= send;
if(streams[0].p!=null)flush_node_list(streams[0].p);
}
else
{p= streams[0].p;
}
streams[0].p= streams[0].t= null;
houtput_template(p);
hmark_page();
}
/*:355*//*378:*/
#line 7705 "hint.w"


static void hget_node(uint8_t a)
{switch(a)
{
/*348:*/
#line 7230 "hint.w"

case TAG(stream_kind,b100):hinsert_stream(HGET8);break;
/*:348*//*393:*/
#line 7957 "hint.w"

case TAG(glyph_kind,1):HGET_GLYPH(1);break;
case TAG(glyph_kind,2):HGET_GLYPH(2);break;
case TAG(glyph_kind,3):HGET_GLYPH(3);break;
case TAG(glyph_kind,4):HGET_GLYPH(4);break;
/*:393*//*397:*/
#line 8000 "hint.w"

case TAG(penalty_kind,0):tail_append(new_penalty(hget_integer_ref(HGET8)));break;
case TAG(penalty_kind,1):{tail_append(new_penalty(HGET8));}break;
case TAG(penalty_kind,2):{int16_t n;HGET16(n);RNG("Penalty",n,-20000,+20000);tail_append(new_penalty(n));}break;
/*:397*//*399:*/
#line 8014 "hint.w"

case TAG(language_kind,b000):(void)HGET8;
case TAG(language_kind,1):
case TAG(language_kind,2):
case TAG(language_kind,3):
case TAG(language_kind,4):
case TAG(language_kind,5):
case TAG(language_kind,6):
case TAG(language_kind,7):break;
/*:399*//*403:*/
#line 8060 "hint.w"

case TAG(rule_kind,b000):tail_append(hget_rule_ref(HGET8));prev_depth= ignore_depth;break;
case TAG(rule_kind,b011):{HGET_RULE(b011);tail_append(p);prev_depth= ignore_depth;}break;
case TAG(rule_kind,b101):{HGET_RULE(b101);tail_append(p);prev_depth= ignore_depth;}break;
case TAG(rule_kind,b001):{HGET_RULE(b001);tail_append(p);prev_depth= ignore_depth;}break;
case TAG(rule_kind,b110):{HGET_RULE(b110);tail_append(p);prev_depth= ignore_depth;}break;
case TAG(rule_kind,b111):{HGET_RULE(b111);tail_append(p);prev_depth= ignore_depth;}break;
/*:403*//*410:*/
#line 8128 "hint.w"

case TAG(glue_kind,b000):tail_append(new_glue(hget_glue_ref(HGET8)));break;
case TAG(glue_kind,b001):{pointer p;HGET_GLUE(b001);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b010):{pointer p;HGET_GLUE(b010);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b011):{pointer p;HGET_GLUE(b011);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b100):{pointer p;HGET_GLUE(b100);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b101):{pointer p;HGET_GLUE(b101);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b110):{pointer p;HGET_GLUE(b110);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b111):{pointer p;HGET_GLUE(b111);tail_append(spec2glue(p));}break;
/*:410*//*420:*/
#line 8417 "hint.w"

case TAG(hbox_kind,b000):{pointer p;HGET_BOX(b000);happend_to_vlist(p);}break;
case TAG(hbox_kind,b001):{pointer p;HGET_BOX(b001);happend_to_vlist(p);}break;
case TAG(hbox_kind,b010):{pointer p;HGET_BOX(b010);happend_to_vlist(p);}break;
case TAG(hbox_kind,b011):{pointer p;HGET_BOX(b011);happend_to_vlist(p);}break;
case TAG(hbox_kind,b100):{pointer p;HGET_BOX(b100);happend_to_vlist(p);}break;
case TAG(hbox_kind,b101):{pointer p;HGET_BOX(b101);happend_to_vlist(p);}break;
case TAG(hbox_kind,b110):{pointer p;HGET_BOX(b110);happend_to_vlist(p);}break;
case TAG(hbox_kind,b111):{pointer p;HGET_BOX(b111);happend_to_vlist(p);}break;
case TAG(vbox_kind,b000):{pointer p;HGET_BOX(b000);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b001):{pointer p;HGET_BOX(b001);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b010):{pointer p;HGET_BOX(b010);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b011):{pointer p;HGET_BOX(b011);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b100):{pointer p;HGET_BOX(b100);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b101):{pointer p;HGET_BOX(b101);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b110):{pointer p;HGET_BOX(b110);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b111):{pointer p;HGET_BOX(b111);type(p)= vlist_node;happend_to_vlist(p);}break;
/*:420*//*426:*/
#line 8531 "hint.w"

case TAG(hset_kind,b000):{pointer p;HGET_SET(b000);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(hset_kind,b001):{pointer p;HGET_SET(b001);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(hset_kind,b010):{pointer p;HGET_SET(b010);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(hset_kind,b011):{pointer p;HGET_SET(b011);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(hset_kind,b100):{pointer p;HGET_SET(b100);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(hset_kind,b101):{pointer p;HGET_SET(b101);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(hset_kind,b110):{pointer p;HGET_SET(b110);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(hset_kind,b111):{pointer p;HGET_SET(b111);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;

case TAG(vset_kind,b000):{pointer p;HGET_SET(b000);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(vset_kind,b001):{pointer p;HGET_SET(b001);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(vset_kind,b010):{pointer p;HGET_SET(b010);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(vset_kind,b011):{pointer p;HGET_SET(b011);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(vset_kind,b100):{pointer p;HGET_SET(b100);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(vset_kind,b101):{pointer p;HGET_SET(b101);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(vset_kind,b110):{pointer p;HGET_SET(b110);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(vset_kind,b111):{pointer p;HGET_SET(b111);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
/*:426*//*432:*/
#line 8693 "hint.w"

case TAG(hpack_kind,b000):HGET_PACK(hpack_kind,b000);break;
case TAG(hpack_kind,b010):HGET_PACK(hpack_kind,b010);break;
case TAG(hpack_kind,b100):HGET_PACK(hpack_kind,b100);break;
case TAG(hpack_kind,b110):HGET_PACK(hpack_kind,b110);break;
case TAG(hpack_kind,b001):HGET_PACK(hpack_kind,b001);break;
case TAG(hpack_kind,b011):HGET_PACK(hpack_kind,b011);break;
case TAG(hpack_kind,b101):HGET_PACK(hpack_kind,b101);break;
case TAG(hpack_kind,b111):HGET_PACK(hpack_kind,b111);break;

case TAG(vpack_kind,b000):HGET_PACK(vpack_kind,b000);break;
case TAG(vpack_kind,b010):HGET_PACK(vpack_kind,b010);break;
case TAG(vpack_kind,b100):HGET_PACK(vpack_kind,b100);break;
case TAG(vpack_kind,b110):HGET_PACK(vpack_kind,b110);break;
case TAG(vpack_kind,b001):HGET_PACK(vpack_kind,b001);break;
case TAG(vpack_kind,b011):HGET_PACK(vpack_kind,b011);break;
case TAG(vpack_kind,b101):HGET_PACK(vpack_kind,b101);break;
case TAG(vpack_kind,b111):HGET_PACK(vpack_kind,b111);break;
/*:432*//*437:*/
#line 8776 "hint.w"

case TAG(kern_kind,b000):{HGET_KERN(b000);}break;
case TAG(kern_kind,b001):{HGET_KERN(b001);}break;
case TAG(kern_kind,b010):{HGET_KERN(b010);}break;
case TAG(kern_kind,b011):{HGET_KERN(b011);}break;
case TAG(kern_kind,b100):{HGET_KERN(b100);}break;
case TAG(kern_kind,b101):{HGET_KERN(b101);}break;
case TAG(kern_kind,b110):{HGET_KERN(b110);}break;
case TAG(kern_kind,b111):{HGET_KERN(b111);}break;
/*:437*//*441:*/
#line 8825 "hint.w"

case TAG(leaders_kind,0):tail_append(hget_leaders_ref(HGET8));break;
case TAG(leaders_kind,1):HGET_LEADERS(1);break;
case TAG(leaders_kind,2):HGET_LEADERS(2);break;
case TAG(leaders_kind,3):HGET_LEADERS(3);break;
case TAG(leaders_kind,b100|1):HGET_LEADERS(b100|1);break;
case TAG(leaders_kind,b100|2):HGET_LEADERS(b100|2);break;
case TAG(leaders_kind,b100|3):HGET_LEADERS(b100|3);break;
/*:441*//*445:*/
#line 8865 "hint.w"

case TAG(baseline_kind,b000):{cur_list.bs_pos= hpos-1;hget_baseline_ref(HGET8);}break;
case TAG(baseline_kind,b010):{HGET_BASELINE(b010);}break;
case TAG(baseline_kind,b011):{HGET_BASELINE(b011);}break;
case TAG(baseline_kind,b100):{HGET_BASELINE(b100);}break;
case TAG(baseline_kind,b101):{HGET_BASELINE(b101);}break;
case TAG(baseline_kind,b110):{HGET_BASELINE(b110);}break;
case TAG(baseline_kind,b111):{HGET_BASELINE(b111);}break;
/*:445*//*450:*/
#line 8925 "hint.w"

case TAG(ligature_kind,0):tail_append(hget_ligature_ref(HGET8));break;
case TAG(ligature_kind,1):HGET_LIG(1);break;
case TAG(ligature_kind,2):HGET_LIG(2);break;
case TAG(ligature_kind,3):HGET_LIG(3);break;
case TAG(ligature_kind,4):HGET_LIG(4);break;
case TAG(ligature_kind,5):HGET_LIG(5);break;
case TAG(ligature_kind,6):HGET_LIG(6);break;
case TAG(ligature_kind,7):HGET_LIG(7);break;
/*:450*//*454:*/
#line 8975 "hint.w"

case TAG(disc_kind,b000):tail_append(hget_hyphen_ref(HGET8));break;
case TAG(disc_kind,b001):{HGET_DISC(b001);tail_append(p);}break;
case TAG(disc_kind,b010):{HGET_DISC(b010);tail_append(p);}break;
case TAG(disc_kind,b011):{HGET_DISC(b011);tail_append(p);}break;
case TAG(disc_kind,b100):{HGET_DISC(b100);tail_append(p);}break;
case TAG(disc_kind,b101):{HGET_DISC(b101);tail_append(p);}break;
case TAG(disc_kind,b110):{HGET_DISC(b110);tail_append(p);}break;
case TAG(disc_kind,b111):{HGET_DISC(b111);tail_append(p);}break;
/*:454*//*459:*/
#line 9043 "hint.w"

case TAG(par_kind,b000):HGET_PAR(b000);break;
case TAG(par_kind,b010):HGET_PAR(b010);break;
case TAG(par_kind,b100):HGET_PAR(b100);break;
case TAG(par_kind,b110):HGET_PAR(b110);break;
/*:459*//*482:*/
#line 9531 "hint.w"

case TAG(math_kind,b000):HGET_MATH(b000);break;
case TAG(math_kind,b001):HGET_MATH(b001);break;
case TAG(math_kind,b010):HGET_MATH(b010);break;
case TAG(math_kind,b100):HGET_MATH(b100);break;
case TAG(math_kind,b101):HGET_MATH(b101);break;
case TAG(math_kind,b110):HGET_MATH(b110);break;
/*:482*//*484:*/
#line 9560 "hint.w"

case TAG(math_kind,b111):tail_append(new_math(0,before));break;
case TAG(math_kind,b011):tail_append(new_math(0,after));break;
/*:484*//*487:*/
#line 9586 "hint.w"

case TAG(adjust_kind,1):HGET_ADJUST(1);break;
/*:487*//*490:*/
#line 9614 "hint.w"

case TAG(table_kind,b000):HGET_TABLE(b000);break;
case TAG(table_kind,b001):HGET_TABLE(b001);break;
case TAG(table_kind,b010):HGET_TABLE(b010);break;
case TAG(table_kind,b011):HGET_TABLE(b011);break;
case TAG(table_kind,b100):HGET_TABLE(b100);break;
case TAG(table_kind,b101):HGET_TABLE(b101);break;
case TAG(table_kind,b110):HGET_TABLE(b110);break;
case TAG(table_kind,b111):HGET_TABLE(b111);break;

case TAG(item_kind,b000):hget_list_pointer();break;
case TAG(item_kind,b001):hget_content();break;
case TAG(item_kind,b010):hget_content();break;
case TAG(item_kind,b011):hget_content();break;
case TAG(item_kind,b100):hget_content();break;
case TAG(item_kind,b101):hget_content();break;
case TAG(item_kind,b110):hget_content();break;
case TAG(item_kind,b111):(void)HGET8;hget_content();break;
/*:490*//*495:*/
#line 9701 "hint.w"

case TAG(stream_kind,b000):HGET_STREAM(b000);break;
case TAG(stream_kind,b010):HGET_STREAM(b010);break;
/*:495*//*499:*/
#line 9757 "hint.w"

case TAG(image_kind,b000):hget_image_ref(HGET8);break;
case TAG(image_kind,b001):HGET_IMAGE(b001);break;
case TAG(image_kind,b010):HGET_IMAGE(b010);break;
case TAG(image_kind,b011):HGET_IMAGE(b011);break;
case TAG(image_kind,b100):HGET_IMAGE(b100);break;
case TAG(image_kind,b101):HGET_IMAGE(b101);break;
case TAG(image_kind,b110):HGET_IMAGE(b110);break;
case TAG(image_kind,b111):HGET_IMAGE(b111);break;
/*:499*//*501:*/
#line 9779 "hint.w"

case TAG(color_kind,b000):tail_append(hget_color_ref(HGET8));break;
/*:501*//*503:*/
#line 9790 "hint.w"

case TAG(link_kind,b000):HGET_LINK(b000);break;
case TAG(link_kind,b001):HGET_LINK(b001);break;
case TAG(link_kind,b010):HGET_LINK(b010);break;
case TAG(link_kind,b011):HGET_LINK(b011);break;
case TAG(link_kind,b100):HGET_LINK(b100);break;
case TAG(link_kind,b101):HGET_LINK(b101);break;
case TAG(link_kind,b110):HGET_LINK(b110);break;
case TAG(link_kind,b111):HGET_LINK(b111);break;
/*:503*/
#line 7710 "hint.w"

default:
if(!hget_unknown(a))
TAGERR(a);
break;
}
}

static void hget_content(void)
{/*374:*/
#line 7666 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:374*/
#line 7719 "hint.w"

node_pos= (hpos-hstart)-1;
hget_node(a);
/*375:*/
#line 7671 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:375*/
#line 7722 "hint.w"

if(nest_ptr==0&&tail!=head&&
(type(tail)==penalty_node||type(tail)==glue_node||type(tail)==kern_node||
type(tail)==hlist_node||type(tail)==vlist_node||type(tail)==rule_node)
)
store_map(tail,node_pos,0);
}

static pointer hget_definition(uint8_t a)
{pointer p;
if(link(head)!=null)QUIT("Calling get_node with nonempty current list");
hget_node(a);
p= link(head);
if(p!=null&&link(p)!=null)QUIT("get_node returns multiple nodes");
link(head)= null;
tail= head;
return p;
}
/*:378*//*472:*/
#line 9359 "hint.w"

static void set_line_break_params(void)
{hset_param_list(line_break_params);
}
/*:472*//*511:*/
#line 9916 "hint.w"

static void hpage_init(void)
{int i;
if(streams==NULL||cur_page==NULL)return;
for(i= 0;i<=max_ref[stream_kind];i++)
if(streams[i].p!=null)
{flush_node_list(streams[i].p);
streams[i].p= streams[i].t= null;
}
page_contents= empty;page_tail= page_head;link(page_head)= null;
hset_cur_page();
hset_margins();
page_depth= page_height= 0;
memset(top_so_far,0,sizeof(top_so_far));
max_depth= cur_page->d;
if(top_skip!=cur_page->g)
{delete_glue_ref(top_skip);
top_skip= cur_page->g;
add_glue_ref(top_skip);
}
}
/*:511*//*513:*/
#line 9947 "hint.w"

static void hflush_contribution_list(void)
{if(link(contrib_head)!=null)
{flush_node_list(link(contrib_head));
link(contrib_head)= null;tail= contrib_head;
}
}
/*:513*//*524:*/
#line 10065 "hint.w"

int hint_begin(void)
{if(!hint_map())return 0;
hpos= hstart= hin_addr;
hend= hstart+hin_size;
ft_init();
hflush_contribution_list();hpage_init();
flush_node_list(link(page_head));
mem_init();
list_init();
hclear_dir();
hclear_font_info();
hget_banner();
if(!hcheck_banner("hint"))
{hint_unmap();return 0;}
hget_directory();
hget_definition_section();
hvsize= dimen_def[vsize_dimen_no];
hhsize= dimen_def[hsize_dimen_no];
hget_content_section();
leak_clear();
clear_map();
hloc_init();
return 1;
}

void hint_end(void)
{if(hin_addr==NULL)return;
hflush_contribution_list();hpage_init();
flush_node_list(link(page_head));
list_leaks();
free_definitions();
hclear_dir();
hint_unmap();
hin_addr= hpos= hstart= hend= NULL;
}
/*:524*//*525:*/
#line 10109 "hint.w"

scaled hint_hsize(void)
{if(dimen_def!=NULL)return dimen_def[hsize_dimen_no];
else return 0;
}

scaled hint_vsize(void)
{if(dimen_def!=NULL)return dimen_def[vsize_dimen_no];
else return 0;
}
/*:525*//*527:*/
#line 10239 "hint.w"

void hint_resize(int px_h,int px_v,double x_dpi,double y_dpi)
{
x_px_size= (scaled)((72.27/x_dpi)*ONE+0.5);
if(x_px_size<MIN_PIXEL_SIZE)x_px_size= MIN_PIXEL_SIZE;
else if(x_px_size> MAX_PIXEL_SIZE)x_px_size= MAX_PIXEL_SIZE;

y_px_size= (scaled)((72.27/y_dpi)*ONE+0.5);
if(y_px_size<MIN_PIXEL_SIZE)y_px_size= MIN_PIXEL_SIZE;
else if(y_px_size> MAX_PIXEL_SIZE)y_px_size= MAX_PIXEL_SIZE;

page_h= px_h*x_px_size;
page_v= px_v*y_px_size;

nativeSetSize(px_h,px_v,page_h,page_v);
hloc_clear();
hflush_contribution_list();hpage_init();
forward_mode= false;
backward_mode= false;
}
/*:527*//*528:*/
#line 10292 "hint.w"

static bool hbuild_page_up(void)
{
static scaled page_top_height;
pointer p;
pointer q,r;
int b,c;
int pi= 0;
if(link(contrib_head)==null)return false;
do{p= link(contrib_head);
/*533:*/
#line 10414 "hint.w"

switch(type(p)){
case hlist_node:case vlist_node:case rule_node:
/*530:*/
#line 10358 "hint.w"

if(page_contents<box_there)
{if(page_contents==empty)freeze_page_specs(box_there);
else page_contents= box_there;
if(depth(p)> page_max_depth)
page_total= depth(p)-page_max_depth;
depth(p)= 0;
/*531:*/
#line 10384 "hint.w"

{page_top_height= width(top_skip);
page_total= page_total+page_top_height;
}
/*:531*/
#line 10365 "hint.w"

}
/*532:*/
#line 10393 "hint.w"

{int i;
for(i= 1;i<=6;i++)
{page_so_far[i]+= top_so_far[i];
top_so_far[i]= 0;
}
}
/*:532*/
#line 10367 "hint.w"

page_total+= page_height+depth(p);
if(height(p)> page_top_height)
{page_total= page_total+height(p)-page_top_height;
page_height= page_top_height;
}
else
page_height= height(p);
/*:530*/
#line 10417 "hint.w"
goto contribute;
case whatsit_node:goto contribute;
case glue_node:/*535:*/
#line 10449 "hint.w"

if(link(p)==null)return false;
/*536:*/
#line 10456 "hint.w"

#define top_shrink top_so_far[6]
#define top_total top_so_far[1]

{pointer q= glue_ptr(p);
top_so_far[2+stretch_order(q)]+= stretch(q);
if((shrink_order(q)!=normal)&&(shrink(q)!=0))
DBG(DBGTEX,"Infinite glue shrinkage found on current page");
top_shrink+= shrink(q);
top_total+= width(q);
}
/*:536*/
#line 10451 "hint.w"

if(page_contents==empty||!precedes_break(link(p)))goto contribute;
pi= 0;
/*:535*/
#line 10419 "hint.w"
break;
case kern_node:/*537:*/
#line 10472 "hint.w"

top_total+= width(p);
if(page_contents==empty||
link(page_head)==null||
type(link(page_head))!=glue_node)
goto contribute;
pi= 0;
/*:537*/
#line 10420 "hint.w"
break;
case penalty_node:if(page_contents==empty)goto done1;else pi= penalty(p);break;
case ins_node:happend_insertion(p);goto contribute;
default:DBG(DBGTEX,"Unexpected node type %d in build_page_up ignored\n",type(p));
}
/*539:*/
#line 10497 "hint.w"

if(pi<inf_penalty)
{/*538:*/
#line 10486 "hint.w"

/*261:*/
#line 5339 "hint.w"

if(page_total<page_goal)
if((page_so_far[3]!=0)||(page_so_far[4]!=0)||
(page_so_far[5]!=0))b= 0;
else b= badness(page_goal-page_total,page_so_far[2]);
else if(page_total-page_goal> page_shrink)b= awful_bad;
else b= badness(page_total-page_goal,page_shrink)

/*:261*/
#line 10487 "hint.w"
;
if(b<awful_bad)
{if(pi<=eject_penalty)c= pi;
else if(b<inf_bad)c= b+pi+insert_penalties;
else c= deplorable;
}
else c= b;
if(insert_penalties>=10000)c= awful_bad;
/*:538*/
#line 10499 "hint.w"

if(c<=least_page_cost)
{best_page_break= p;best_size= page_goal;
least_page_cost= c;
r= link(page_ins_head);
while(r!=page_ins_head)
{best_ins_ptr(r)= last_ins_ptr(r);
r= link(r);
}
}
if((c==awful_bad)||(pi<=eject_penalty))
{
/*540:*/
#line 10527 "hint.w"

if(p!=best_page_break)
{while(link(page_head)!=best_page_break)
{q= link(page_head);
link(page_head)= link(q);
link(q)= null;
link(q)= link(head);
link(head)= q;
}
}
/*:540*/
#line 10511 "hint.w"

/*541:*/
#line 10545 "hint.w"

hloc_set_prev(link(page_head));
while(true){
q= link(page_head);
if(q==null)return false;
else if(q==best_page_break)
break;
else if(type(q)==penalty_node||type(q)==glue_node||type(q)==kern_node)
{link(page_head)= link(q);link(q)= null;flush_node_list(q);}
else break;
}
temp_ptr= new_spec(top_skip);
q= new_glue(temp_ptr);glue_ref_count(temp_ptr)= null;
if(width(temp_ptr)> page_height)width(temp_ptr)= width(temp_ptr)-page_height;
else width(temp_ptr)= 0;
link(q)= link(page_head);
link(page_head)= q;
best_page_break= null;
/*:541*/
#line 10512 "hint.w"

hpack_page();
hfill_page_template();
return true;
}
}
/*:539*/
#line 10425 "hint.w"

contribute:
/*534:*/
#line 10432 "hint.w"

link(contrib_head)= link(p);
link(p)= link(page_head);
if(link(page_head)==null)page_tail= p;
link(page_head)= p;
goto done;
/*:534*/
#line 10427 "hint.w"

done1:/*253:*/
#line 5224 "hint.w"

link(contrib_head)= link(p);link(p)= null;flush_node_list(p)

/*:253*/
#line 10428 "hint.w"
;
done:
/*:533*/
#line 10302 "hint.w"
;
}while(link(contrib_head)!=null);
tail= contrib_head;
return false;
}
/*:528*//*542:*/
#line 10575 "hint.w"

bool hint_forward(void)
{hpage_init();
if(hbuild_page())return true;
while(hpos<hend)
{hget_content();
if(hbuild_page())return true;
}
while(!flush_pages(hend-hstart))
if(hbuild_page())return true;
return false;
}
/*:542*//*543:*/
#line 10616 "hint.w"

bool hint_backward(void)
{hpage_init();
if(hbuild_page_up())return true;
while(hpos> hstart)
{hteg_content();
if(hbuild_page_up())return true;
}
while(!flush_pages(0x0))
if(hbuild_page_up())return true;
return false;
}
/*:543*//*544:*/
#line 10640 "hint.w"

bool flush_pages(uint32_t pos)
{pointer p= link(head);
while(p!=null&&
(type(p)==penalty_node||type(p)==glue_node||type(p)==kern_node))
p= link(p);
if(p==null&&link(page_head)==null)return true;
tail_append(new_null_box());
width(tail)= hhsize;
tail_append(hget_param_glue(fill_skip_no));
store_map(tail,pos,0);
tail_append(new_penalty(-010000000000));
store_map(tail,pos,0);
return false;
}
/*:544*//*551:*/
#line 10803 "hint.w"

static void clear_map(void)
{memset(map,0,sizeof(map));
}
/*:551*//*553:*/
#line 10820 "hint.w"

static void store_map(pointer p,uint32_t pos0,uint32_t offset)
{map[p]= pos0;
map[p+1]= offset;
}

uint32_t hposition(pointer p)
{return map[p];
}
/*:553*//*560:*/
#line 10927 "hint.w"

static void hloc_init(void)
{cur_loc= 0;
hloc_clear();
page_loc[cur_loc]= 0;
DBG(DBGPAGE,"loc_init: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
}
/*:560*//*582:*/
#line 11501 "hint.w"

int hint_get_outline_max(void)
{return max_outline;}
/*:582*//*588:*/
#line 11584 "hint.w"

hint_Outline*hint_get_outlines(void)
{return hint_outlines;
}
/*:588*//*625:*/
#line 12543 "hint.w"

static void hload_font(uint8_t f)
{DBG(DBGFONT,"Decoding new font %d\n",f);
if(f> max_ref[font_kind])
QUIT("Undefined font %d\n",f);
if(unpack_pk_file(f))
font_def[f].ff= pk_format;
else
{font_def[f].ff= ft_format;
font_def[f].hpxs= 0;
font_def[f].vpxs= 0;
}
}
/*:625*/
#line 14819 "hint.w"


/*:686*/
