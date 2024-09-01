/*4:*/
#line 401 "texprof.w"
/*9:*/
#line 467 "texprof.w"

#include <stdbool.h> 
#include <string.h> 
#include <math.h> 

/*:9*//*1686:*/
#line 29759 "texprof.w"

#ifdef WEB2CVERSION
#define TL_VERSION "(TeX Live "WEB2CVERSION")"
#else
#line 29763 "texprof.w"
#define TL_VERSION
#endif
#line 29765 "texprof.w"

/*:1686*//*1699:*/
#line 29992 "texprof.w"

#include <kpathsea/kpathsea.h> 
static int argument_is(struct option*opt,char*s)
{return STREQ(opt->name,s);}
#define ARGUMENT_IS(S) argument_is(long_options+option_index,S)

/*:1699*//*1736:*/
#line 30771 "texprof.w"

#include <time.h> 
static time_t start_time= ((time_t)-1);
static char*source_date_epoch,*force_source_date;

#if defined(_MSC_VER) && _MSC_VER < 1800
#define strtoull _strtoui64
#endif
#line 30779 "texprof.w"

static struct tm*tl_now(void)
{struct tm*tp;
time_t t;
source_date_epoch= getenv("SOURCE_DATE_EPOCH");
force_source_date= getenv("FORCE_SOURCE_DATE");
if(force_source_date!=NULL&&
(force_source_date[0]!='1'||force_source_date[1]!=0))
force_source_date= NULL;

if(source_date_epoch!=NULL)
{start_time= (time_t)strtoull(source_date_epoch,NULL,10);
if(force_source_date!=NULL)
t= start_time;
else
t= time(NULL);
}
else
t= start_time= time(NULL);
if(force_source_date)
tp= gmtime(&t);
else
tp= localtime(&t);
return tp;
}

/*:1736*//*1737:*/
#line 30807 "texprof.w"

#define TIME_STR_SIZE 30
static char time_str[TIME_STR_SIZE];
static void get_creation_date(void);
static void get_file_mod_date(void);
static int get_file_size(void);

#include <md5.h> 
#define DIGEST_SIZE 16
#define FILE_BUF_SIZE 1024
static md5_byte_t md5_digest[DIGEST_SIZE];

static int get_md5_sum(int s,int file);

/*:1737*/
#line 401 "texprof.w"

#define eTeX_version 2
#define eTeX_revision ".6"
#define eTeX_version_string "-2.6" \

#define TeX_banner "This is TeX, Version 3.141592653" \
 \

#define TEX ETEX \

#define eTeX_states 1 \

#define Prote_version_string "3.141592653-2.6-1.1.0"
#define Prote_version 1
#define Prote_revision ".1.0" \

#define Prote_banner "This is Prote, Version "Prote_version_string \
 \

#define banner Prote_banner \

#define odd(X) ((X) &1) 
#define chr(X) ((unsigned char) (X) ) 
#define ord(X) ((unsigned int) (X) ) 
#define abs(X) ((X) > -(X) ?(X) :-(X) ) 
#define round(X) ((int) ((X) >=0.0?floor((X) +0.5) :ceil((X) -0.5) ) )  \

#define mem_bot 0 \

#define mem_top 5000000 \
 \

#define font_base 0 \

#define hash_size 45000 \

#define hash_prime 35999
#define hyph_size 8191 \
 \

#define incr(A) A= A+1
#define decr(A) A= A-1
#define negate(A) A= -A
#define loop while(true) 
#define do_nothing 
#define empty 0 \

#define text_char unsigned char
#define first_text_char 0
#define last_text_char 255 \

#define null_code 00
#define carriage_return 015
#define invalid_code 0177 \

#define t_open_in term_in.f= stdin
#define t_open_out term_out.f= stdout \

#define update_terminal fflush(term_out.f) 
#define clear_terminal fflush(term_in.f) 
#define wake_up_terminal do_nothing \

#define loc cur_input.loc_field \

#define si(A) A
#define so(A) A \

#define length(A) (str_start[A+1]-str_start[A])  \
 \

#define cur_length (pool_ptr-str_start[str_ptr])  \

#define append_char(A)  \
{str_pool[pool_ptr]= si(A) ;incr(pool_ptr) ; \
}
#define flush_char decr(pool_ptr) 
#define str_room(A)  \
{if(pool_ptr+A> pool_size)  \
overflow("pool size",pool_size-init_pool_ptr) ; \
 \
} \

#define flush_string {decr(str_ptr) ;pool_ptr= str_start[str_ptr]; \
} \

#define app_lc_hex(A) l= A; \
if(l<10) append_char(l+'0') else append_char(l-10+'a')  \

#define no_print 16
#define term_only 17
#define log_only 18
#define term_and_log 19
#define pseudo 20
#define new_string 21
#define max_selector 21 \

#define print_ASCII printn \

#define prompt_input(A) {wake_up_terminal;print(A) ;term_input() ; \
} \

#define batch_mode 0
#define nonstop_mode 1
#define scroll_mode 2
#define error_stop_mode 3 \

#define spotless 0
#define warning_issued 1
#define error_message_issued 2
#define fatal_error_stop 3 \

#define hlp1(A) help_line[0]= A;}
#define hlp2(A,B) help_line[1]= A;help_line[0]= B;}
#define hlp3(A,B,C) help_line[2]= A;help_line[1]= B;help_line[0]= C;}
#define hlp4(A,B,C,D) help_line[3]= A;help_line[2]= B;help_line[1]= C;help_line[0]= D;}
#define hlp5(A,B,C,D,E) help_line[4]= A;help_line[3]= B;help_line[2]= C;help_line[1]= D;help_line[0]= E;}
#define hlp6(A,B,C,D,E,F) help_line[5]= A;help_line[4]= B;help_line[3]= C;help_line[2]= D;help_line[1]= E;help_line[0]= F;}
#define help0 help_ptr= 0
#define help1(A) {help_ptr= 1;hlp1(A) 
#define help2(A,B) {help_ptr= 2;hlp2(A,B) 
#define help3(A,B,C) {help_ptr= 3;hlp3(A,B,C) 
#define help4(A,B,C,D) {help_ptr= 4;hlp4(A,B,C,D) 
#define help5(A,B,C,D,E) {help_ptr= 5;hlp5(A,B,C,D,E) 
#define help6(A,B,C,D,E,F) {help_ptr= 6;hlp6(A,B,C,D,E,F)  \

#define succumb {if(interaction==error_stop_mode)  \
interaction= scroll_mode; \
if(log_opened) error() ; \
if(interaction> batch_mode) debug_help() ; \
history= fatal_error_stop;jump_out() ; \
} \

#define check_interrupt {if(interrupt!=0) pause_for_instructions() ; \
} \

#define unity 0200000
#define two 0400000 \

#define nx_plus_y(A,B,C) mult_and_add(A,B,C,07777777777) 
#define mult_integers(A,B) mult_and_add(A,B,0,017777777777)  \

#define inf_bad 10000 \

#define set_glue_ratio_zero(A) A= 0.0
#define set_glue_ratio_one(A) A= 1.0
#define unfix(A) ((double) (A) ) 
#define fix(A) ((glue_ratio) (A) ) 
#define float_constant(A) ((double) (A) )  \

#define min_quarterword 0
#define max_quarterword 65535
#define min_halfword 0
#define max_halfword 0x3FFFFFFF \

#define qi(A) A+min_quarterword \

#define qo(A) A-min_quarterword \

#define hi(A) A+min_halfword \

#define ho(A) A-min_halfword \
 \

#define sc i \

#define pointer halfword
#define null min_halfword \

#define link(A) mem[A].hh.rh
#define info(A) mem[A].hh.lh \

#define free_avail(A)  \
{link(A) = avail;avail= A; \
decr_dyn_used; \
} \

#define fast_get_avail(A)  \
{A= avail; \
if(A==null) A= get_avail() ; \
else{avail= link(A) ;link(A) = null; \
incr_dyn_used; \
} \
} \

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
#define box_node_size 7
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

#define mark_node 4
#define small_node_size 2
#define mark_ptr(A) link(A+1) 
#define mark_class(A) info(A+1)  \

#define adjust_node 5
#define adjust_ptr(A) mem[A+1].i \
 \

#define ligature_node 6
#define lig_char(A) A+1
#define lig_ptr(A) link(lig_char(A) )  \

#define disc_node 7
#define replace_count(A) subtype(A) 
#define pre_break(A) llink(A) 
#define post_break(A) rlink(A)  \

#define whatsit_node 8 \

#define math_node 9
#define before 0
#define after 1 \

#define precedes_break(A) (type(A) <math_node) 
#define non_discardable(A) (type(A) <math_node)  \

#define glue_node 10
#define cond_math_glue 98
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
#define fil_glue zero_glue+glue_spec_size
#define fill_glue fil_glue+glue_spec_size
#define ss_glue fill_glue+glue_spec_size
#define fil_neg_glue ss_glue+glue_spec_size
#define lo_mem_stat_max fil_neg_glue+glue_spec_size-1 \
 \

#define page_ins_head mem_top
#define contrib_head mem_top-1
#define page_head mem_top-2
#define temp_head mem_top-3
#define hold_head mem_top-4
#define adjust_head mem_top-5
#define active mem_top-7
#define align_head mem_top-8
#define end_span mem_top-9
#define omit_template mem_top-10
#define null_list mem_top-11
#define lig_trick mem_top-12
#define garbage mem_top-12
#define backup_head mem_top-13
#define hi_mem_stat_min mem_top-13 \

#define hi_mem_stat_usage 14 \

#define node_list_display(A)  \
{append_char('.') ;show_node_list(A) ;flush_char; \
} \

#define token_ref_count(A) info(A)  \

#define fast_delete_glue_ref(A)  \
{if(glue_ref_count(A) ==null) free_node(A,glue_spec_size) ; \
else decr(glue_ref_count(A) ) ; \
} \

#define add_token_ref(A) incr(token_ref_count(A) ) 
#define add_glue_ref(A) incr(glue_ref_count(A) )  \

#define escape 0 \

#define relax 0
#define left_brace 1
#define right_brace 2
#define math_shift 3
#define tab_mark 4
#define car_ret 5
#define out_param 5
#define mac_param 6
#define sup_mark 7
#define sub_mark 8
#define ignore 9
#define endv 9
#define spacer 10
#define letter 11
#define other_char 12
#define active_char 13
#define par_end 13
#define match 13
#define comment 14
#define end_match 14
#define stop 14
#define invalid_char 15
#define delim_num 15
#define max_char_code 15 \

#define char_num 16
#define math_char_num 17
#define mark 18
#define xray 19
#define make_box 20
#define hmove 21
#define vmove 22
#define un_hbox 23
#define un_vbox 24 \

#define remove_item 25 \

#define hskip 26
#define vskip 27
#define mskip 28
#define kern 29
#define mkern 30
#define leader_ship 31
#define halign 32
#define valign 33
#define no_align 34
#define vrule 35
#define hrule 36
#define insert 37
#define vadjust 38
#define ignore_spaces 39
#define after_assignment 40
#define after_group 41
#define break_penalty 42
#define start_par 43
#define ital_corr 44
#define accent 45
#define math_accent 46
#define discretionary 47
#define eq_no 48
#define left_right 49 \

#define math_comp 50
#define limit_switch 51
#define above 52
#define math_style 53
#define math_choice 54
#define non_script 55
#define vcenter 56
#define case_shift 57
#define message 58
#define extension 59
#define in_stream 60
#define begin_group 61
#define end_group 62
#define omit 63
#define ex_space 64
#define no_boundary 65
#define radical 66
#define end_cs_name 67
#define min_internal 68
#define char_given 68
#define math_given 69
#define last_item 70 \

#define max_non_prefixed_command 70 \

#define toks_register 71
#define assign_toks 72
#define assign_int 73
#define assign_dimen 74
#define assign_glue 75
#define assign_mu_glue 76
#define assign_font_dimen 77
#define assign_font_int 78 \

#define set_aux 79
#define set_prev_graf 80
#define set_page_dimen 81
#define set_page_int 82 \
 \

#define set_box_dimen 83
#define set_shape 84 \

#define def_code 85
#define def_family 86
#define set_font 87
#define def_font 88
#define internal_register 89
#define max_internal 89
#define advance 90
#define multiply 91
#define divide 92
#define prefix 93 \

#define let 94
#define shorthand_def 95
#define read_to_cs 96 \

#define def 97
#define set_box 98
#define hyph_data 99
#define set_interaction 100
#define max_command 100 \

#define undefined_cs (max_command+1) 
#define expand_after (max_command+2) 
#define no_expand (max_command+3) 
#define input (max_command+4)  \

#define if_test (max_command+5) 
#define fi_or_else (max_command+6) 
#define cs_name (max_command+7) 
#define convert (max_command+8) 
#define the (max_command+9)  \

#define top_bot_mark (max_command+10) 
#define call (max_command+11) 
#define long_call (max_command+12) 
#define outer_call (max_command+13) 
#define long_outer_call (max_command+14) 
#define end_template (max_command+15) 
#define dont_expand (max_command+16) 
#define glue_ref (max_command+17) 
#define shape_ref (max_command+18) 
#define box_ref (max_command+19) 
#define data (max_command+20)  \

#define vmode 1
#define hmode (vmode+max_command+1) 
#define mmode (hmode+max_command+1)  \

#define ignore_depth -65536000 \

#define mode cur_list.mode_field
#define head cur_list.head_field
#define tail cur_list.tail_field
#define eTeX_aux cur_list.eTeX_aux_field
#define LR_save eTeX_aux
#define LR_box eTeX_aux
#define delim_ptr eTeX_aux
#define prev_graf cur_list.pg_field
#define aux cur_list.aux_field
#define prev_depth aux.sc
#define space_factor aux.hh.lh
#define clang aux.hh.rh
#define incompleat_noad aux.i
#define mode_line cur_list.ml_field \

#define tail_append(A) {link(tail) = A;tail= link(tail) ; \
} \

#define eq_level_field(A) A.hh.b1
#define eq_type_field(A) A.hh.b0
#define equiv_field(A) A.hh.rh
#define eq_level(A) eq_level_field(eqtb[A]) 
#define eq_type(A) eq_type_field(eqtb[A]) 
#define equiv(A) equiv_field(eqtb[A]) 
#define level_zero min_quarterword
#define level_one (level_zero+1)  \

#define active_base 1
#define single_base (active_base+256) 
#define null_cs (single_base+256) 
#define hash_base (null_cs+1) 
#define frozen_control_sequence (hash_base+hash_size) 
#define frozen_protection frozen_control_sequence
#define frozen_cr (frozen_control_sequence+1) 
#define frozen_end_group (frozen_control_sequence+2) 
#define frozen_right (frozen_control_sequence+3) 
#define frozen_fi (frozen_control_sequence+4) 
#define frozen_end_template (frozen_control_sequence+5) 
#define frozen_endv (frozen_control_sequence+6) 
#define frozen_relax (frozen_control_sequence+7) 
#define end_write (frozen_control_sequence+8) 
#define frozen_dont_expand (frozen_control_sequence+9)  \

#define frozen_primitive (frozen_control_sequence+10)  \

#define frozen_null_font (frozen_control_sequence+11)  \

#define font_id_base (frozen_null_font-font_base)  \

#define undefined_control_sequence (frozen_null_font+257) 
#define glue_base (undefined_control_sequence+1)  \

#define line_skip_code 0
#define baseline_skip_code 1
#define par_skip_code 2
#define above_display_skip_code 3
#define below_display_skip_code 4
#define above_display_short_skip_code 5 \

#define below_display_short_skip_code 6 \

#define left_skip_code 7
#define right_skip_code 8
#define top_skip_code 9
#define split_top_skip_code 10
#define tab_skip_code 11
#define space_skip_code 12
#define xspace_skip_code 13
#define par_fill_skip_code 14
#define thin_mu_skip_code 15
#define med_mu_skip_code 16
#define thick_mu_skip_code 17
#define glue_pars 18
#define skip_base (glue_base+glue_pars) 
#define mu_skip_base (skip_base+256) 
#define local_base (mu_skip_base+256)  \

#define skip(A) equiv(skip_base+A) 
#define mu_skip(A) equiv(mu_skip_base+A) 
#define glue_par(A) equiv(glue_base+A) 
#define line_skip glue_par(line_skip_code) 
#define baseline_skip glue_par(baseline_skip_code) 
#define par_skip glue_par(par_skip_code) 
#define above_display_skip glue_par(above_display_skip_code) 
#define below_display_skip glue_par(below_display_skip_code) 
#define above_display_short_skip glue_par(above_display_short_skip_code) 
#define below_display_short_skip glue_par(below_display_short_skip_code) 
#define left_skip glue_par(left_skip_code) 
#define right_skip glue_par(right_skip_code) 
#define top_skip glue_par(top_skip_code) 
#define split_top_skip glue_par(split_top_skip_code) 
#define tab_skip glue_par(tab_skip_code) 
#define space_skip glue_par(space_skip_code) 
#define xspace_skip glue_par(xspace_skip_code) 
#define par_fill_skip glue_par(par_fill_skip_code) 
#define thin_mu_skip glue_par(thin_mu_skip_code) 
#define med_mu_skip glue_par(med_mu_skip_code) 
#define thick_mu_skip glue_par(thick_mu_skip_code)  \

#define par_shape_loc local_base
#define output_routine_loc (local_base+1) 
#define every_par_loc (local_base+2) 
#define every_math_loc (local_base+3) 
#define every_display_loc (local_base+4) 
#define every_hbox_loc (local_base+5) 
#define every_vbox_loc (local_base+6) 
#define every_job_loc (local_base+7) 
#define every_cr_loc (local_base+8) 
#define err_help_loc (local_base+9) 
#define tex_toks (local_base+10)  \

#define etex_toks_base pdf_toks
#define every_eof_loc etex_toks_base
#define etex_toks (etex_toks_base+1)  \

#define toks_base etex_toks \

#define etex_pen_base (toks_base+256) 
#define inter_line_penalties_loc etex_pen_base
#define club_penalties_loc (etex_pen_base+1) 
#define widow_penalties_loc (etex_pen_base+2) 
#define display_widow_penalties_loc (etex_pen_base+3) 
#define etex_pens (etex_pen_base+4)  \

#define box_base etex_pens
#define cur_font_loc (box_base+256) 
#define math_font_base (cur_font_loc+1) 
#define cat_code_base (math_font_base+48)  \

#define lc_code_base (cat_code_base+256) 
#define uc_code_base (lc_code_base+256) 
#define sf_code_base (uc_code_base+256) 
#define math_code_base (sf_code_base+256) 
#define int_base (math_code_base+256)  \

#define par_shape_ptr equiv(par_shape_loc) 
#define output_routine equiv(output_routine_loc) 
#define every_par equiv(every_par_loc) 
#define every_math equiv(every_math_loc) 
#define every_display equiv(every_display_loc) 
#define every_hbox equiv(every_hbox_loc) 
#define every_vbox equiv(every_vbox_loc) 
#define every_job equiv(every_job_loc) 
#define every_cr equiv(every_cr_loc) 
#define err_help equiv(err_help_loc) 
#define toks(X) equiv(toks_base+X) 
#define box(A) equiv(box_base+A) 
#define cur_font equiv(cur_font_loc) 
#define fam_fnt(A) equiv(math_font_base+A) 
#define cat_code(A) equiv(cat_code_base+A) 
#define lc_code(A) equiv(lc_code_base+A) 
#define uc_code(A) equiv(uc_code_base+A) 
#define sf_code(A) equiv(sf_code_base+A) 
#define math_code(A) equiv(math_code_base+A)  \
 \

#define null_font font_base
#define var_code 070000 \

#define pretolerance_code 0
#define tolerance_code 1
#define line_penalty_code 2
#define hyphen_penalty_code 3
#define ex_hyphen_penalty_code 4
#define club_penalty_code 5
#define widow_penalty_code 6
#define display_widow_penalty_code 7
#define broken_penalty_code 8
#define bin_op_penalty_code 9
#define rel_penalty_code 10
#define pre_display_penalty_code 11 \

#define post_display_penalty_code 12 \

#define inter_line_penalty_code 13
#define double_hyphen_demerits_code 14
#define final_hyphen_demerits_code 15
#define adj_demerits_code 16
#define mag_code 17
#define delimiter_factor_code 18
#define looseness_code 19
#define time_code 20
#define day_code 21
#define month_code 22
#define year_code 23
#define show_box_breadth_code 24
#define show_box_depth_code 25
#define hbadness_code 26
#define vbadness_code 27
#define pausing_code 28
#define tracing_online_code 29
#define tracing_macros_code 30
#define tracing_stats_code 31
#define tracing_paragraphs_code 32
#define tracing_pages_code 33
#define tracing_output_code 34
#define tracing_lost_chars_code 35
#define tracing_commands_code 36
#define tracing_restores_code 37
#define uc_hyph_code 38
#define output_penalty_code 39
#define max_dead_cycles_code 40
#define hang_after_code 41
#define floating_penalty_code 42
#define global_defs_code 43
#define cur_fam_code 44
#define escape_char_code 45
#define default_hyphen_char_code 46
#define default_skew_char_code 47
#define end_line_char_code 48
#define new_line_char_code 49
#define language_code 50
#define left_hyphen_min_code 51
#define right_hyphen_min_code 52
#define holding_inserts_code 53
#define error_context_lines_code 54
#define tex_int_pars 55 \

#define etex_int_base pdf_int_pars
#define tracing_assigns_code etex_int_base
#define tracing_groups_code (etex_int_base+1) 
#define tracing_ifs_code (etex_int_base+2) 
#define tracing_scan_tokens_code (etex_int_base+3) 
#define tracing_nesting_code (etex_int_base+4) 
#define saving_vdiscards_code (etex_int_base+5) 
#define saving_hyph_codes_code (etex_int_base+6) 
#define expand_depth_code (etex_int_base+7) 
#define eTeX_state_code (etex_int_base+8) 
#define etex_int_pars (eTeX_state_code+eTeX_states)  \

#define int_pars etex_int_pars
#define count_base (int_base+int_pars) 
#define del_code_base (count_base+256) 
#define dimen_base (del_code_base+256)  \

#define del_code(A) eqtb[del_code_base+A].i
#define count(A) eqtb[count_base+A].i
#define int_par(A) eqtb[int_base+A].i
#define pretolerance int_par(pretolerance_code) 
#define tolerance int_par(tolerance_code) 
#define line_penalty int_par(line_penalty_code) 
#define hyphen_penalty int_par(hyphen_penalty_code) 
#define ex_hyphen_penalty int_par(ex_hyphen_penalty_code) 
#define club_penalty int_par(club_penalty_code) 
#define widow_penalty int_par(widow_penalty_code) 
#define display_widow_penalty int_par(display_widow_penalty_code) 
#define broken_penalty int_par(broken_penalty_code) 
#define bin_op_penalty int_par(bin_op_penalty_code) 
#define rel_penalty int_par(rel_penalty_code) 
#define pre_display_penalty int_par(pre_display_penalty_code) 
#define post_display_penalty int_par(post_display_penalty_code) 
#define inter_line_penalty int_par(inter_line_penalty_code) 
#define double_hyphen_demerits int_par(double_hyphen_demerits_code) 
#define final_hyphen_demerits int_par(final_hyphen_demerits_code) 
#define adj_demerits int_par(adj_demerits_code) 
#define mag int_par(mag_code) 
#define delimiter_factor int_par(delimiter_factor_code) 
#define looseness int_par(looseness_code) 
#define time int_par(time_code) 
#define day int_par(day_code) 
#define month int_par(month_code) 
#define year int_par(year_code) 
#define show_box_breadth int_par(show_box_breadth_code) 
#define show_box_depth int_par(show_box_depth_code) 
#define hbadness int_par(hbadness_code) 
#define vbadness int_par(vbadness_code) 
#define pausing int_par(pausing_code) 
#define tracing_online int_par(tracing_online_code) 
#define tracing_macros int_par(tracing_macros_code) 
#define tracing_stats int_par(tracing_stats_code) 
#define tracing_paragraphs int_par(tracing_paragraphs_code) 
#define tracing_pages int_par(tracing_pages_code) 
#define tracing_output int_par(tracing_output_code) 
#define tracing_lost_chars int_par(tracing_lost_chars_code) 
#define tracing_commands int_par(tracing_commands_code) 
#define tracing_restores int_par(tracing_restores_code) 
#define uc_hyph int_par(uc_hyph_code) 
#define output_penalty int_par(output_penalty_code) 
#define max_dead_cycles int_par(max_dead_cycles_code) 
#define hang_after int_par(hang_after_code) 
#define floating_penalty int_par(floating_penalty_code) 
#define global_defs int_par(global_defs_code) 
#define cur_fam int_par(cur_fam_code) 
#define escape_char int_par(escape_char_code) 
#define default_hyphen_char int_par(default_hyphen_char_code) 
#define default_skew_char int_par(default_skew_char_code) 
#define end_line_char int_par(end_line_char_code) 
#define new_line_char int_par(new_line_char_code) 
#define language int_par(language_code) 
#define left_hyphen_min int_par(left_hyphen_min_code) 
#define right_hyphen_min int_par(right_hyphen_min_code) 
#define holding_inserts int_par(holding_inserts_code) 
#define error_context_lines int_par(error_context_lines_code)  \

#define tracing_assigns int_par(tracing_assigns_code) 
#define tracing_groups int_par(tracing_groups_code) 
#define tracing_ifs int_par(tracing_ifs_code) 
#define tracing_scan_tokens int_par(tracing_scan_tokens_code) 
#define tracing_nesting int_par(tracing_nesting_code) 
#define saving_vdiscards int_par(saving_vdiscards_code) 
#define saving_hyph_codes int_par(saving_hyph_codes_code) 
#define expand_depth int_par(expand_depth_code)  \

#define par_indent_code 0
#define math_surround_code 1
#define line_skip_limit_code 2
#define hsize_code 3
#define vsize_code 4
#define max_depth_code 5
#define split_max_depth_code 6
#define box_max_depth_code 7
#define hfuzz_code 8
#define vfuzz_code 9
#define delimiter_shortfall_code 10
#define null_delimiter_space_code 11
#define script_space_code 12
#define pre_display_size_code 13
#define display_width_code 14
#define display_indent_code 15
#define overfull_rule_code 16
#define hang_indent_code 17
#define h_offset_code 18
#define v_offset_code 19
#define emergency_stretch_code 20
#define page_width_code 21
#define page_height_code 22
#define dimen_pars (pdftex_last_dimen_code+1) 
#define scaled_base (dimen_base+dimen_pars)  \

#define eqtb_size (scaled_base+255)  \

#define dimen(A) eqtb[scaled_base+A].sc
#define dimen_par(A) eqtb[dimen_base+A].sc
#define par_indent dimen_par(par_indent_code) 
#define math_surround dimen_par(math_surround_code) 
#define line_skip_limit dimen_par(line_skip_limit_code) 
#define hsize dimen_par(hsize_code) 
#define vsize dimen_par(vsize_code) 
#define max_depth dimen_par(max_depth_code) 
#define split_max_depth dimen_par(split_max_depth_code) 
#define box_max_depth dimen_par(box_max_depth_code) 
#define hfuzz dimen_par(hfuzz_code) 
#define vfuzz dimen_par(vfuzz_code) 
#define delimiter_shortfall dimen_par(delimiter_shortfall_code) 
#define null_delimiter_space dimen_par(null_delimiter_space_code) 
#define script_space dimen_par(script_space_code) 
#define pre_display_size dimen_par(pre_display_size_code) 
#define display_width dimen_par(display_width_code) 
#define display_indent dimen_par(display_indent_code) 
#define overfull_rule dimen_par(overfull_rule_code) 
#define hang_indent dimen_par(hang_indent_code) 
#define h_offset dimen_par(h_offset_code) 
#define v_offset dimen_par(v_offset_code) 
#define emergency_stretch dimen_par(emergency_stretch_code) 
#define page_height dimen_par(page_height_code)  \

#define next(A) hash[A].lh
#define text(A) hash[A].rh
#define hash_is_full (hash_used==hash_base) 
#define font_id_text(A) text(font_id_base+A)  \

#define save_type(A) save_stack[A].hh.b0
#define save_level(A) save_stack[A].hh.b1 \

#define save_index(A) save_stack[A].hh.rh \

#define restore_old_value 0
#define restore_zero 1
#define insert_token 2
#define level_boundary 3
#define restore_sa 4 \

#define bottom_level 0
#define simple_group 1
#define hbox_group 2
#define adjusted_hbox_group 3
#define vbox_group 4
#define vtop_group 5
#define align_group 6
#define no_align_group 7
#define output_group 8
#define math_group 9
#define disc_group 10
#define insert_group 11
#define vcenter_group 12
#define math_choice_group 13
#define semi_simple_group 14
#define math_shift_group 15
#define math_left_group 16
#define max_group_code 16 \

#define check_full_save_stack if(save_ptr> max_save_stack)  \
{max_save_stack= save_ptr; \
if(max_save_stack> save_size-7) overflow("save size",save_size) ; \
 \
} \

#define saved(A) save_stack[save_ptr+A].i \

#define cs_token_flag 07777 \

#define left_brace_token 00400
#define left_brace_limit 01000
#define right_brace_token 01000
#define right_brace_limit 01400
#define math_shift_token 01400
#define tab_token 02000
#define out_param_token 02400
#define space_token 05040
#define letter_token 05400
#define other_token 06000
#define match_token 06400
#define end_match_token 07000
#define protected_token 07001 \

#define chr_cmd(A) {print(A) ;print_ASCII(chr_code) ; \
} \

#define state cur_input.state_field
#define index cur_input.index_field
#define start cur_input.start_field
#define limit cur_input.limit_field
#define name cur_input.name_field
#define cur_depth cur_input.depth_field \

#define mid_line 1
#define skip_blanks (2+max_char_code) 
#define new_line (3+max_char_code+max_char_code)  \

#define terminal_input (name==0) 
#define cur_file input_file[index] \

#define skipping 1
#define defining 2
#define matching 3
#define aligning 4
#define absorbing 5 \

#define token_list 0
#define token_type index
#define param_start limit
#define parameter 0
#define u_template 1
#define v_template 2
#define backed_up 3
#define inserted 4
#define macro 5
#define output_text 6
#define every_par_text 7
#define every_math_text 8
#define every_display_text 9
#define every_hbox_text 10
#define every_vbox_text 11
#define every_job_text 12
#define every_cr_text 13
#define mark_text 14 \

#define eTeX_text_offset (output_routine_loc-output_text) 
#define every_eof_text (every_eof_loc-eTeX_text_offset)  \
 \

#define write_text (toks_base-eTeX_text_offset)  \

#define begin_pseudoprint  \
{l= tally;tally= 0;selector= pseudo; \
trick_count= 1000000; \
}
#define set_trick_count  \
{first_count= tally; \
trick_count= tally+1+error_line-half_error_line; \
if(trick_count<error_line) trick_count= error_line; \
} \

#define push_input  \
{if(input_ptr> max_in_stack)  \
{max_in_stack= input_ptr; \
if(input_ptr==stack_size) overflow("input stack size",stack_size) ; \
 \
} \
input_stack[input_ptr]= cur_input; \
incr(input_ptr) ; \
} \

#define pop_input  \
{decr(input_ptr) ;cur_input= input_stack[input_ptr]; \
} \

#define back_list(A) begin_token_list(A,backed_up) 
#define ins_list(A) begin_token_list(A,inserted)  \

#define any_state_plus(A) case mid_line+A: \
case skip_blanks+A:case new_line+A \

#define add_delims_to(A) A+math_shift:A+tab_mark:A+mac_param: \
A+sub_mark:A+letter:A+other_char \

#define is_hex(A) (((A>='0') &&(A<='9') ) ||((A>='a') &&(A<='f') ) ) 
#define hex_to_cur_chr  \
if(c<='9') cur_chr= c-'0';else cur_chr= c-'a'+10; \
if(cc<='9') cur_chr= 16*cur_chr+cc-'0'; \
else cur_chr= 16*cur_chr+cc-'a'+10 \

#define no_expand_flag 257 \

#define end_line_char_inactive (end_line_char<0) ||(end_line_char> 255)  \

#define store_new_token(A) {q= get_avail() ;link(p) = q;info(q) = A; \
fl_mem[q]= cur_file_line; \
p= q; \
}
#define fast_store_new_token(A) {fast_get_avail(q) ;link(p) = q;info(q) = A; \
fl_mem[q]= cur_file_line; \
p= q; \
} \

#define marks_code 5 \

#define top_mark_code 0
#define first_mark_code 1
#define bot_mark_code 2
#define split_first_mark_code 3
#define split_bot_mark_code 4
#define top_mark cur_mark[top_mark_code]
#define first_mark cur_mark[first_mark_code]
#define bot_mark cur_mark[bot_mark_code]
#define split_first_mark cur_mark[split_first_mark_code]
#define split_bot_mark cur_mark[split_bot_mark_code] \

#define int_val 0
#define dimen_val 1
#define glue_val 2
#define mu_val 3
#define ident_val 4
#define tok_val 5 \

#define scanned_result(A,B) {cur_val= A;cur_val_level= B;} \

#define last_node_type_code (glue_val+1) 
#define input_line_no_code (glue_val+2) 
#define badness_code (input_line_no_code+1)  \

#define eTeX_int (pdftex_last_item_codes+1) 
#define eTeX_dim (eTeX_int+8) 
#define eTeX_glue (eTeX_dim+9) 
#define eTeX_mu (eTeX_glue+1) 
#define eTeX_expr (eTeX_mu+1) 
#define eTeX_last_last_item_cmd_mod (eTeX_expr-int_val+mu_val)  \

#define max_dimen 07777777777 \

#define octal_token (other_token+'\'') 
#define hex_token (other_token+'"') 
#define alpha_token (other_token+'`') 
#define point_token (other_token+'.') 
#define continental_point_token (other_token+',')  \

#define infinity 017777777777
#define zero_token (other_token+'0') 
#define A_token (letter_token+'A') 
#define other_A_token (other_token+'A')  \

#define scan_normal_dimen scan_dimen(false,false,false)  \

#define set_conversion(A,B) {num= A;denom= B;} \

#define default_rule 26214 \

#define number_code 0
#define roman_numeral_code 1
#define string_code 2
#define meaning_code 3
#define font_name_code 4
#define etex_convert_base 5
#define eTeX_revision_code etex_convert_base
#define etex_convert_codes (etex_convert_base+1) 
#define eTeX_last_convert_cmd_mod etex_convert_codes \
 \
 \

#define job_name_code pdftex_convert_codes \

#define closed 2
#define just_open 1 \

#define unless_code 32 \

#define if_char_code 0
#define if_cat_code 1
#define if_int_code 2
#define if_dim_code 3
#define if_odd_code 4
#define if_vmode_code 5
#define if_hmode_code 6
#define if_mmode_code 7
#define if_inner_code 8
#define if_void_code 9
#define if_hbox_code 10
#define if_vbox_code 11
#define ifx_code 12
#define if_eof_code 13
#define if_true_code 14
#define if_false_code 15
#define if_case_code 16 \

#define if_node_size 2
#define if_line_field(A) mem[A+1].i
#define if_code 1
#define fi_code 2
#define else_code 3
#define or_code 4 \

#define get_x_token_or_active_char  \
{get_x_token() ; \
if(cur_cmd==relax) if(cur_chr==no_expand_flag)  \
{cur_cmd= active_char; \
cur_chr= cur_tok-cs_token_flag-active_base; \
} \
} \

#define TEX_area "TeXinputs/" \

#define TEX_font_area "TeXfonts/" \
 \

#define append_to_name(A) {c= A;incr(k) ; \
if(k<=file_name_size) name_of_file[k]= xchr[c]; \
} \

#define format_extension ".fmt" \

#define pack_cur_name(A) if(cur_ext==empty_string) pack_file_name(cur_name,cur_area,cur_ext,A) ; \
else pack_file_name(cur_name,cur_area,cur_ext,NULL)  \

#define ensure_dvi_open if(output_file_name==0)  \
{if(job_name==0) open_log_file() ; \
pack_job_name(".dvi") ; \
while(!b_open_out(&dvi_file) )  \
prompt_file_name("file name for output",".dvi") ; \
output_file_name= b_make_name_string(&dvi_file) ; \
} \

#define no_tag 0
#define lig_tag 1
#define list_tag 2
#define ext_tag 3 \

#define stop_flag qi(128) 
#define kern_flag qi(128) 
#define skip_byte(A) A.b0
#define next_char(A) A.b1
#define op_byte(A) A.b2
#define rem_byte(A) A.b3 \

#define ext_top(A) A.b0
#define ext_mid(A) A.b1
#define ext_bot(A) A.b2
#define ext_rep(A) A.b3 \

#define slant_code 1
#define space_code 2
#define space_stretch_code 3
#define space_shrink_code 4
#define x_height_code 5
#define quad_code 6
#define extra_space_code 7 \

#define non_char qi(256) 
#define non_address 0 \

#define char_info(A,B) font_info[char_base[A]+B].qqqq
#define char_width(A,B) font_info[width_base[A]+B.b0].sc
#define char_exists(A) (A.b0> min_quarterword) 
#define char_italic(A,B) font_info[italic_base[A]+(qo(B.b2) ) /4].sc
#define height_depth(A) qo(A.b1) 
#define char_height(A,B) font_info[height_base[A]+(B) /16].sc
#define char_depth(A,B) font_info[depth_base[A]+(B) %16].sc
#define char_tag(A) ((qo(A.b2) ) %4)  \

#define char_kern(A,B) font_info[kern_base[A]+256*op_byte(B) +rem_byte(B) ].sc
#define kern_base_offset 256*(128+min_quarterword) 
#define lig_kern_start(A,B) lig_kern_base[A]+B.b3
#define lig_kern_restart(A,B) lig_kern_base[A]+256*op_byte(B) +rem_byte(B) +32768-kern_base_offset \

#define param_end(A) param_base[A]].sc
#define param(A) font_info[A+param_end
#define slant param(slant_code) 
#define space param(space_code) 
#define space_stretch param(space_stretch_code) 
#define space_shrink param(space_shrink_code) 
#define x_height param(x_height_code) 
#define quad param(quad_code) 
#define extra_space param(extra_space_code)  \

#define abort goto bad_tfm \

#define start_font_error_message print_err("Font ") ;sprint_cs(u) ; \
print_char('=') ;print_file_name(nom,aire,empty_string) ; \
if(s>=0)  \
{print(" at ") ;print_scaled(s) ;print("pt") ; \
} \
else if(s!=-1000)  \
{print(" scaled ") ;print_int(-s) ; \
} \

#define fget get(tfm_file) 
#define fbyte tfm_file.d
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

#define check_byte_range(A) {if((A<bc) ||(A> ec) ) abort;}
#define current_character_being_worked_on k+bc-fmem_ptr \

#define store_scaled(A) {fget;a= fbyte;fget;b= fbyte; \
fget;c= fbyte;fget;d= fbyte; \
sw= (((((d*z) /0400) +(c*z) ) /0400) +(b*z) ) /beta; \
if(a==0) A= sw;else if(a==255) A= sw-alpha;else abort; \
} \

#define check_existence(A)  \
{check_byte_range(A) ; \
qw= char_info(f,A) ; \
if(!char_exists(qw) ) abort; \
} \

#define adjust(A) A[f]= qo(A[f])  \
 \

#define set_char_0 0
#define set1 128
#define set_rule 132
#define put_rule 137
#define nop 138
#define bop 139
#define eop 140
#define push 141
#define pop 142
#define right1 143
#define w0 147
#define w1 148
#define x0 152
#define x1 153
#define down1 157
#define y0 161
#define y1 162
#define z0 166
#define z1 167
#define fnt_num_0 171
#define fnt1 235
#define xxx1 239
#define xxx4 242
#define fnt_def1 243
#define pre 247
#define post 248
#define post_post 249 \

#define id_byte 2 \

#define dvi_out(A) {dvi_buf[dvi_ptr]= A;incr(dvi_ptr) ; \
if(dvi_ptr==dvi_limit) dvi_swap() ; \
} \

#define movement_node_size 3
#define location(A) mem[A+2].i \

#define y_here 1
#define z_here 2
#define yz_OK 3
#define y_OK 4
#define z_OK 5
#define d_fixed 6 \

#define none_seen 0
#define y_seen 6
#define z_seen 12 \

#define synch_h if(cur_h!=dvi_h)  \
{movement(cur_h-dvi_h,right1) ;dvi_h= cur_h; \
}
#define synch_v if(cur_v!=dvi_v)  \
{movement(cur_v-dvi_v,down1) ;dvi_v= cur_v; \
} \

#define billion float_constant(1000000000) 
#define vet_glue(A) glue_temp= A; \
if(glue_temp> billion)  \
glue_temp= billion; \
else if(glue_temp<-billion)  \
glue_temp= -billion \

#define exactly 0
#define additional 1
#define natural 0,additional \

#define noad_size 4
#define nucleus(A) A+1
#define supscr(A) A+2
#define subscr(A) A+3
#define math_type(A) link(A) 
#define fam font
#define math_char 1
#define sub_box 2
#define sub_mlist 3
#define math_text_char 4 \

#define ord_noad (unset_node+3) 
#define op_noad (ord_noad+1) 
#define bin_noad (ord_noad+2) 
#define rel_noad (ord_noad+3) 
#define open_noad (ord_noad+4) 
#define close_noad (ord_noad+5) 
#define punct_noad (ord_noad+6) 
#define inner_noad (ord_noad+7) 
#define limits 1
#define no_limits 2 \

#define left_delimiter(A) A+4
#define right_delimiter(A) A+5
#define radical_noad (inner_noad+1) 
#define radical_noad_size 5
#define fraction_noad (radical_noad+1) 
#define fraction_noad_size 6
#define small_fam(A) mem[A].qqqq.b0
#define small_char(A) mem[A].qqqq.b1
#define large_fam(A) mem[A].qqqq.b2
#define large_char(A) mem[A].qqqq.b3
#define thickness(A) width(A) 
#define default_code 010000000000
#define numerator(A) supscr(A) 
#define denominator(A) subscr(A)  \

#define under_noad (fraction_noad+1) 
#define over_noad (under_noad+1) 
#define accent_noad (over_noad+1) 
#define accent_noad_size 5
#define accent_chr(A) A+4
#define vcenter_noad (accent_noad+1) 
#define left_noad (vcenter_noad+1) 
#define right_noad (left_noad+1) 
#define delimiter(A) nucleus(A) 
#define middle_noad 1
#define scripts_allowed(A) (type(A) >=ord_noad) &&(type(A) <left_noad)  \

#define style_node (unset_node+1) 
#define style_node_size 3
#define display_style 0
#define text_style 2
#define script_style 4
#define script_script_style 6
#define cramped 1 \

#define choice_node (unset_node+2) 
#define display_mlist(A) info(A+1) 
#define text_mlist(A) link(A+1) 
#define script_mlist(A) info(A+2) 
#define script_script_mlist(A) link(A+2)  \

#define text_size 0
#define script_size 16
#define script_script_size 32 \

#define mathsy_end(A) fam_fnt(2+A) ]].sc
#define mathsy(A) font_info[A+param_base[mathsy_end
#define math_x_height mathsy(5) 
#define math_quad mathsy(6) 
#define num1 mathsy(8) 
#define num2 mathsy(9) 
#define num3 mathsy(10) 
#define denom1 mathsy(11) 
#define denom2 mathsy(12) 
#define sup1 mathsy(13) 
#define sup2 mathsy(14) 
#define sup3 mathsy(15) 
#define sub1 mathsy(16) 
#define sub2 mathsy(17) 
#define sup_drop mathsy(18) 
#define sub_drop mathsy(19) 
#define delim1 mathsy(20)  \

#define delim2 mathsy(21) 
#define axis_height mathsy(22) 
#define total_mathsy_params 22 \

#define mathex(A) font_info[A+param_base[fam_fnt(3+cur_size) ]].sc
#define default_rule_thickness mathex(8) 
#define big_op_spacing1 mathex(9) 
#define big_op_spacing2 mathex(10) 
#define big_op_spacing3 mathex(11) 
#define big_op_spacing4 mathex(12) 
#define big_op_spacing5 mathex(13) 
#define total_mathex_params 13 \

#define cramped_style(A) 2*(A/2) +cramped
#define sub_style(A) 2*(A/4) +script_style+cramped
#define sup_style(A) 2*(A/4) +script_style+(A%2) 
#define num_style(A) A+2-2*(A/6) 
#define denom_style(A) 2*(A/2) +cramped+2-2*(A/6)  \

#define mu_mult(A) nx_plus_y(n,A,xn_over_d(A,f,0200000) )  \

#define new_hlist(A) mem[nucleus(A) ].i \

#define choose_mlist(A) {p= A(q) ;A(q) = null;} \

#define math_spacing  \
 \
"0234000122*4000133**3**344*0400400*000000234000111*1111112341011" \
 \

#define u_part(A) mem[A+height_offset].i
#define v_part(A) mem[A+depth_offset].i
#define extra_info(A) info(A+list_offset)  \

#define preamble link(align_head) 
#define align_stack_node_size 5 \

#define span_code 256
#define cr_code 257
#define cr_cr_code (cr_code+1) 
#define end_template_token cs_token_flag+frozen_end_template \

#define span_node_size 2 \

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

#define append_charnode_to_t(A) {link(t) = get_avail() ;t= link(t) ; \
font(t) = hf;character(t) = A; \
}
#define set_cur_r {if(j<n) cur_r= qi(hu[j+1]) ;else cur_r= bchar; \
if(odd(hyf[j]) ) cur_rh= hchar;else cur_rh= non_char; \
} \

#define wrap_lig(A) if(ligature_present)  \
{p= new_ligature(hf,cur_l,link(cur_q) ) ; \
if(lft_hit)  \
{subtype(p) = 2;lft_hit= false; \
} \
if(A) if(lig_stack==null)  \
{incr(subtype(p) ) ;rt_hit= false; \
} \
link(cur_q) = p;t= p;ligature_present= false; \
}
#define pop_lig_stack {if(lig_ptr(lig_stack) > null)  \
{link(t) = lig_ptr(lig_stack) ; \
t= link(t) ;incr(j) ; \
} \
p= lig_stack;lig_stack= link(p) ;free_node(p,small_node_size) ; \
if(lig_stack==null) set_cur_r else cur_r= character(lig_stack) ; \
} \

#define advance_major_tail {major_tail= link(major_tail) ;incr(r_count) ; \
} \

#define trie_link(A) trie[A].rh
#define trie_char(A) trie[A].b1
#define trie_op(A) trie[A].b0 \

#define set_cur_lang if(language<=0) cur_lang= 0; \
else if(language> 255) cur_lang= 0; \
else cur_lang= language \

#define trie_root trie_l[0] \

#define trie_ref trie_hash
#define trie_back(A) trie[A].lh \

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

#define adjust_space_factor  \
main_s= sf_code(cur_chr) ; \
if(main_s==1000) space_factor= 1000; \
else if(main_s<1000)  \
{if(main_s> 0) space_factor= main_s; \
} \
else if(space_factor<1000) space_factor= 1000; \
else space_factor= main_s \

#define pack_lig(X)  \
{main_p= new_ligature(main_f,cur_l,link(cur_q) ) ; \
if(lft_hit)  \
{subtype(main_p) = 2;lft_hit= false; \
} \
if(X) if(lig_stack==null)  \
{incr(subtype(main_p) ) ;rt_hit= false; \
} \
link(cur_q) = main_p;tail= main_p;ligature_present= false; \
} \

#define wrapup(A) if(cur_l<non_char)  \
{if(link(cur_q) > null)  \
if(character(tail) ==qi(hyphen_char[main_f]) ) ins_disc= true; \
if(ligature_present) pack_lig(A) ; \
if(ins_disc)  \
{ins_disc= false; \
if(mode> 0) tail_append(new_disc() ) ; \
} \
} \

#define any_mode(A) case vmode+A:case hmode+A: \
case mmode+A \

#define non_math(A) case vmode+A:case hmode+A \

#define fil_code 0
#define fill_code 1
#define ss_code 2
#define fil_neg_code 3
#define skip_code 4
#define mskip_code 5 \

#define box_flag 010000000000
#define global_box_flag 010000100000
#define ship_out_flag 010000200000
#define leader_flag 010000200001
#define box_code 0
#define copy_code 1
#define last_box_code 2
#define vsplit_code 3
#define vtop_code 4 \

#define fam_in_range ((cur_fam>=0) &&(cur_fam<16) )  \

#define above_code 0
#define over_code 1
#define atop_code 2
#define delimited_code 3 \

#define global (a>=4) 
#define define(A,B,C) if(global) geq_define(A,B,C) ;else eq_define(A,B,C) 
#define word_define(A,B) if(global) geq_word_define(A,B) ;else eq_word_define(A,B)  \

#define char_def_code 0
#define math_char_def_code 1
#define count_def_code 2
#define dimen_def_code 3
#define skip_def_code 4
#define mu_skip_def_code 5
#define toks_def_code 6 \

#define show_code 0
#define show_box_code 1
#define show_the_code 2
#define show_lists_code 3 \

#define too_small(X) {wake_up_terminal; \
wterm_ln("---! Must increase the %s",X) ; \
 \
goto bad_fmt; \
} \

#define dump_wd(A) {fmt_file.d= A;put(fmt_file) ;}
#define dump_int(A) {fmt_file.d.i= A;put(fmt_file) ;}
#define dump_hh(A) {fmt_file.d.hh= A;put(fmt_file) ;}
#define dump_qqqq(A) {fmt_file.d.qqqq= A;put(fmt_file) ;} \

#define undump_wd(A) {get(fmt_file) ;A= fmt_file.d;}
#define undump_int(A) {get(fmt_file) ;A= fmt_file.d.i;}
#define undump_hh(A) {get(fmt_file) ;A= fmt_file.d.hh;}
#define undump_qqqq(A) {get(fmt_file) ;A= fmt_file.d.qqqq;}
#define undump(A,B,C) {undump_int(x) ;if((x<A) ||(x> B) ) goto bad_fmt;else C= x;}
#define undump_size(A,B,C,D) {undump_int(x) ; \
if(x<A) goto bad_fmt;if(x> B) too_small(C) else D= x;} \

#define dump_four_ASCII  \
w.b0= qi(so(str_pool[k]) ) ;w.b1= qi(so(str_pool[k+1]) ) ; \
w.b2= qi(so(str_pool[k+2]) ) ;w.b3= qi(so(str_pool[k+3]) ) ; \
dump_qqqq(w)  \

#define undump_four_ASCII  \
undump_qqqq(w) ; \
str_pool[k]= si(qo(w.b0) ) ;str_pool[k+1]= si(qo(w.b1) ) ; \
str_pool[k+2]= si(qo(w.b2) ) ;str_pool[k+3]= si(qo(w.b3) )  \

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
#define write_tokens(A) link(A+1) 
#define write_stream(A) info(A+1) 
#define open_name(A) link(A+1) 
#define open_area(A) info(A+2) 
#define open_ext(A) link(A+2)  \

#define immediate_code 4
#define latex_first_extension_code 5
#define latespecial_node (latex_first_extension_code+0) 
#define set_language_code (latex_first_extension_code+1) 
#define TeX_last_extension_cmd_mod set_language_code \

#define adv_past(A) if(subtype(A) ==language_node)  \
{cur_lang= what_lang(A) ;l_hyf= what_lhm(A) ;r_hyf= what_rhm(A) ; \
set_hyph_index; \
} \

#define end_write_token cs_token_flag+end_write \

#define eTeX_state_base (int_base+eTeX_state_code) 
#define eTeX_state(A) eqtb[eTeX_state_base+A].i \

#define eTeX_version_code eTeX_int \

#define eTeX_ex (eTeX_mode==1)  \

#define every_eof equiv(every_eof_loc)  \

#define current_group_level_code (eTeX_int+1) 
#define current_group_type_code (eTeX_int+2)  \

#define current_if_level_code (eTeX_int+3) 
#define current_if_type_code (eTeX_int+4) 
#define current_if_branch_code (eTeX_int+5)  \

#define font_char_wd_code eTeX_dim
#define font_char_ht_code (eTeX_dim+1) 
#define font_char_dp_code (eTeX_dim+2) 
#define font_char_ic_code (eTeX_dim+3)  \

#define par_shape_length_code (eTeX_dim+4) 
#define par_shape_indent_code (eTeX_dim+5) 
#define par_shape_dimen_code (eTeX_dim+6)  \

#define show_groups 4 \

#define show_tokens 5 \

#define show_ifs 6 \

#define print_if_line(A) if(A!=0)  \
{print(" entered on line ") ;print_int(A) ; \
} \

#define if_def_code 17
#define if_cs_code 18
#define if_font_char_code 19
#define eTeX_last_if_test_cmd_mod if_font_char_code
#define eTeX_last_expand_after_cmd_mod 1 \

#define expr_none 0
#define expr_add 1
#define expr_sub 2
#define expr_mult 3
#define expr_div 4
#define expr_scale 5 \
 \

#define expr_node_size 4
#define expr_e_field(A) mem[A+1].i
#define expr_t_field(A) mem[A+2].i
#define expr_n_field(A) mem[A+3].i \

#define num_error(A)  \
{arith_error= true;A= 0; \
}
#define glue_error(A)  \
{arith_error= true;delete_glue_ref(A) ;A= new_spec(zero_glue) ; \
} \

#define normalize_glue(A)  \
if(stretch(A) ==0) stretch_order(A) = normal; \
if(shrink(A) ==0) shrink_order(A) = normal \

#define expr_add_sub(A,B,C) add_or_sub(A,B,C,r==expr_sub) 
#define expr_a(A,B) expr_add_sub(A,B,max_dimen)  \

#define expr_m(A) A= nx_plus_y(A,f,0)  \

#define expr_d(A) A= quotient(A,f)  \

#define expr_s(A) A= fract(A,n,f,max_dimen)  \

#define glue_stretch_order_code (eTeX_int+6) 
#define glue_shrink_order_code (eTeX_int+7) 
#define glue_stretch_code (eTeX_dim+7) 
#define glue_shrink_code (eTeX_dim+8)  \

#define mu_to_glue_code eTeX_glue
#define glue_to_mu_code eTeX_mu \

#define box_val 4
#define mark_val 6 \

#define dimen_val_limit 0x20
#define mu_val_limit 0x40
#define box_val_limit 0x50
#define tok_val_limit 0x60 \

#define index_node_size 9
#define sa_index(A) type(A) 
#define sa_used(A) subtype(A)  \

#define sa_mark sa_root[mark_val] \

#define if_cur_ptr_is_null_then_return_or_goto(A)  \
{if(cur_ptr==null)  \
if(w) goto A;else return; \
} \

#define hex_dig1(A) A/4096
#define hex_dig2(A) (A/256) %16
#define hex_dig3(A) (A/16) %16
#define hex_dig4(A) A%16 \

#define get_sa_ptr if(odd(i) ) cur_ptr= link(q+(i/2) +1) ; \
else cur_ptr= info(q+(i/2) +1)  \

#define put_sa_ptr(A) if(odd(i) ) link(q+(i/2) +1) = A; \
else info(q+(i/2) +1) = A \

#define add_sa_ptr {put_sa_ptr(cur_ptr) ;incr(sa_used(q) ) ; \
}
#define delete_sa_ptr {put_sa_ptr(null) ;decr(sa_used(q) ) ; \
} \

#define sa_lev sa_used
#define pointer_node_size 2
#define sa_type(A) (sa_index(A) /16) 
#define sa_ref(A) info(A+1) 
#define sa_ptr(A) link(A+1)  \

#define word_node_size 3
#define sa_num(A) sa_ptr(A) 
#define sa_int(A) mem[A+2].i
#define sa_dim(A) mem[A+2].sc \

#define mark_class_node_size 4 \

#define fetch_box(A)  \
if(cur_val<256) A= box(cur_val) ; \
else{find_sa_element(box_val,cur_val,false) ; \
if(cur_ptr==null) A= null;else A= sa_ptr(cur_ptr) ; \
} \

#define add_sa_ref(A) incr(sa_ref(A) )  \

#define change_box(A)  \
if(cur_val<256) box(cur_val) = A;else set_sa_box(A)  \

#define set_sa_box(X) {find_sa_element(box_val,cur_val,false) ; \
if(cur_ptr!=null)  \
{sa_ptr(cur_ptr) = X;add_sa_ref(cur_ptr) ;delete_sa_ref(cur_ptr) ; \
} \
} \

#define vsplit_init 0
#define fire_up_init 1
#define fire_up_done 2
#define destroy_marks 3 \

#define sa_top_mark(A) info(A+1) 
#define sa_first_mark(A) link(A+1) 
#define sa_bot_mark(A) info(A+2) 
#define sa_split_first_mark(A) link(A+2) 
#define sa_split_bot_mark(A) info(A+3)  \

#define sa_loc(A) sa_ref(A)  \

#define sa_define(A,B,C,D,E) if(e)  \
if(global) gsa_def(A,B) ;else sa_def(A,B) ; \
else if(global) geq_define(C,D,E) ;else eq_define(C,D,E)  \

#define sa_def_box  \
{find_sa_element(box_val,cur_val,true) ; \
if(global) gsa_def(cur_ptr,cur_box) ;else sa_def(cur_ptr,cur_box) ; \
} \

#define sa_word_define(A,B) if(e)  \
if(global) gsa_w_def(A,B) ;else sa_w_def(A,B) ; \
else word_define(A,B)  \

#define hyph_root trie_r[0] \

#define set_hyph_index  \
if(trie_char(hyph_start+cur_lang) !=qi(cur_lang)  \
) hyph_index= 0; \
else hyph_index= trie_link(hyph_start+cur_lang)  \

#define set_lc_code(A)  \
if(hyph_index==0) hc[0]= lc_code(A) ; \
else if(trie_char(hyph_index+A) !=qi(A) ) hc[0]= 0; \
else hc[0]= qo(trie_op(hyph_index+A) )  \

#define tail_page_disc disc_ptr[copy_code]
#define page_disc disc_ptr[last_box_code]
#define split_disc disc_ptr[vsplit_code] \

#define inter_line_penalties_ptr equiv(inter_line_penalties_loc) 
#define Prote_ex (Prote_mode==1)  \

#define if_incsname_code (eTeX_last_if_test_cmd_mod+1) 
#define if_primitive_code (eTeX_last_if_test_cmd_mod+2) 
#define Prote_version_code (eTeX_last_last_item_cmd_mod+1)  \

#define random_seed_code (eTeX_last_last_item_cmd_mod+2) 
#define elapsed_time_code (eTeX_last_last_item_cmd_mod+3) 
#define shell_escape_code (eTeX_last_last_item_cmd_mod+4) 
#define last_xpos_code (eTeX_last_last_item_cmd_mod+5) 
#define last_ypos_code (eTeX_last_last_item_cmd_mod+6)  \

#define Prote_revision_code (eTeX_last_convert_cmd_mod+1) 
#define strcmp_code (eTeX_last_convert_cmd_mod+2) 
#define set_random_seed_code (eTeX_last_convert_cmd_mod+3) 
#define normal_deviate_code (eTeX_last_convert_cmd_mod+4) 
#define uniform_deviate_code (eTeX_last_convert_cmd_mod+5) 
#define creation_date_code (eTeX_last_convert_cmd_mod+6) 
#define file_size_code (eTeX_last_convert_cmd_mod+7) 
#define file_mod_date_code (eTeX_last_convert_cmd_mod+8) 
#define file_dump_code (eTeX_last_convert_cmd_mod+9) 
#define mdfive_sum_code (eTeX_last_convert_cmd_mod+10) 
#define Prote_last_convert_code mdfive_sum_code \

#define primitive_code (eTeX_last_expand_after_cmd_mod+1) 
#define expanded_code (eTeX_last_expand_after_cmd_mod+2) 
#define eTeX_last_extension_cmd_mod TeX_last_extension_cmd_mod
#define reset_timer_code (eTeX_last_extension_cmd_mod+1) 
#define save_pos_code (eTeX_last_extension_cmd_mod+2)  \

#define ROM_base 1
#define ROM_size (256+1+hash_size) 
#define ROM_undefined_primitive 257
#define ROM_type_field(A) A.hh.b0
#define ROM_equiv_field(X) X.hh.rh
#define ROM_type(A) ROM_type_field(ROM[A]) 
#define set_ROM_p_from_cs(A) if((A>=single_base)  \
&&(A<frozen_control_sequence) )  \
p= A-single_base+ROM_base; \
else p= ROM_undefined_primitive \

#define get_elapsed_time infinity \

#define get_file_mtime xchg_buffer_length= 0 \

#define double(A) A= A+A
#define halfp(A) (A) /2 \

#define el_gordo 017777777777
#define mpfract_half 01000000000
#define mpfract_one 02000000000
#define mpfract_four 010000000000 \

#define next_random if(j_random==0) new_randoms() ; \
else decr(j_random)  \

#define return_sign(A) {return A; \
} \

#define DVI_std_x_offset 4736286
#define DVI_std_y_offset 4736286 \

#define profile_on_code (eTeX_last_extension_cmd_mod+3) 
#define profile_off_code (eTeX_last_extension_cmd_mod+4) 
#define pdftex_first_extension_code profile_off_code+1 \

#define cur_file_num input_file_num[index] \

#define unknown_file 0
#define system_file 1
#define terminal_file 2
#define system_unknown 0
#define system_start 1
#define system_end 2
#define system_ship_out 3
#define system_line_break 4
#define system_init_trie 5
#define system_build_page 6
#define system_input_ln 7
#define system_insert 8 \
 \

#define system_cmd (max_command+1) 
#define system_profile_on (system_cmd+1) 
#define system_profile_off (system_cmd+2) 
#define system_macro_push (system_cmd+3) 
#define system_macro_pop (system_cmd+4) 
#define system_macro_pop_small (system_cmd+5) 
#define system_macro_pop_0 (system_cmd+6)  \
 \

#define SHOW_RECORD_TIMING 0 \

#define CALL_DEPTH(A) ((A) >>48) 
#define CALL_EQTB(A) (((A) >>32) &0xFFFF) 
#define CALL_FILE(A) (((A) >>16) &0xFF) 
#define CALL_LINE(A) ((A) &0xFFFF) 
#define CALL_DE(A) ((A) >>32) 
#define CALL_CFL(A) ((A) &0xFFFFFFFF) 
#define CALL_INFO(D,C,FL) (((uint64_t) (D) <<48) |((uint64_t) (C) <<32) | \
(system_macro_push<<24) |FL)  \

#define PUT1(N) fputc((N) &0xFF,prof) 
#define PUT2(N) PUT1((N) >>8) ,PUT1(N) 
#define PUT4(N) PUT2((N) >>16) ,PUT2(N)  \
 \

#define SHOW_WRITE_TIMING 0 \

#define pdftex_version 140
#define pdftex_revision "25"
#define pdftex_version_string "-1.40.25" \

#define pdftex_first_rint_code (badness_code+1) 
#define pdftex_version_code (pdftex_first_rint_code+0) 
#define pdf_last_obj_code (pdftex_first_rint_code+1) 
#define pdf_last_xform_code (pdftex_first_rint_code+2) 
#define pdf_last_ximage_code (pdftex_first_rint_code+3) 
#define pdf_last_ximage_pages_code (pdftex_first_rint_code+4) 
#define pdf_last_annot_code (pdftex_first_rint_code+5) 
#define pdf_retval_code (pdftex_first_rint_code+6) 
#define pdf_last_ximage_colordepth_code (pdftex_first_rint_code+7) 
#define pdf_last_link_code (pdftex_first_rint_code+8) 
#define pdftex_last_item_codes (pdftex_first_rint_code+8)  \

#define pdftex_first_loc tex_toks
#define pdf_pages_attr_loc (pdftex_first_loc+0) 
#define pdf_page_attr_loc (pdftex_first_loc+1) 
#define pdf_page_resources_loc (pdftex_first_loc+2) 
#define pdf_pk_mode_loc (pdftex_first_loc+3) 
#define pdf_toks (pdftex_first_loc+4)  \

#define pdftex_first_integer_code tex_int_pars
#define pdf_output_code (pdftex_first_integer_code+0) 
#define pdf_compress_level_code (pdftex_first_integer_code+1) 
#define pdf_decimal_digits_code (pdftex_first_integer_code+2) 
#define pdf_move_chars_code (pdftex_first_integer_code+3) 
#define pdf_image_resolution_code (pdftex_first_integer_code+4) 
#define pdf_pk_resolution_code (pdftex_first_integer_code+5) 
#define pdf_unique_resname_code (pdftex_first_integer_code+6) 
#define pdf_option_always_use_pdfpagebox_code (pdftex_first_integer_code+7) 
#define pdf_option_pdf_inclusion_errorlevel_code (pdftex_first_integer_code+8) 
#define pdf_major_version_code (pdftex_first_integer_code+9) 
#define pdf_minor_version_code (pdftex_first_integer_code+10) 
#define pdf_force_pagebox_code (pdftex_first_integer_code+11) 
#define pdf_pagebox_code (pdftex_first_integer_code+12) 
#define pdf_inclusion_errorlevel_code (pdftex_first_integer_code+13) 
#define pdf_gamma_code (pdftex_first_integer_code+14) 
#define pdf_image_gamma_code (pdftex_first_integer_code+15) 
#define pdf_image_hicolor_code (pdftex_first_integer_code+16) 
#define pdf_image_apply_gamma_code (pdftex_first_integer_code+17) 
#define pdf_adjust_spacing_code (pdftex_first_integer_code+18) 
#define pdf_protrude_chars_code (pdftex_first_integer_code+19) 
#define pdf_tracing_fonts_code (pdftex_first_integer_code+20) 
#define pdf_objcompresslevel_code (pdftex_first_integer_code+21) 
#define pdf_adjust_interword_glue_code (pdftex_first_integer_code+22) 
#define pdf_prepend_kern_code (pdftex_first_integer_code+23) 
#define pdf_append_kern_code (pdftex_first_integer_code+24) 
#define pdf_gen_tounicode_code (pdftex_first_integer_code+25) 
#define pdf_draftmode_code (pdftex_first_integer_code+26) 
#define pdf_inclusion_copy_font_code (pdftex_first_integer_code+27) 
#define pdf_suppress_warning_dup_dest_code (pdftex_first_integer_code+28) 
#define pdf_suppress_warning_dup_map_code (pdftex_first_integer_code+29) 
#define pdf_suppress_warning_page_group_code (pdftex_first_integer_code+30) 
#define pdf_info_omit_date_code (pdftex_first_integer_code+31) 
#define pdf_suppress_ptex_info_code (pdftex_first_integer_code+32) 
#define pdf_omit_charset_code (pdftex_first_integer_code+33) 
#define pdf_omit_info_dict_code (pdftex_first_integer_code+34) 
#define pdf_omit_procset_code (pdftex_first_integer_code+35) 
#define pdf_int_pars (pdftex_first_integer_code+36)  \

#define pdftex_first_dimen_code 23
#define pdf_h_origin_code (pdftex_first_dimen_code+0) 
#define pdf_v_origin_code (pdftex_first_dimen_code+1) 
#define pdf_link_margin_code (pdftex_first_dimen_code+2) 
#define pdf_dest_margin_code (pdftex_first_dimen_code+3) 
#define pdf_thread_margin_code (pdftex_first_dimen_code+4) 
#define pdf_first_line_height_code (pdftex_first_dimen_code+5) 
#define pdf_last_line_depth_code (pdftex_first_dimen_code+6) 
#define pdf_each_line_height_code (pdftex_first_dimen_code+7) 
#define pdf_each_line_depth_code (pdftex_first_dimen_code+8) 
#define pdf_ignored_dimen_code (pdftex_first_dimen_code+9) 
#define pdf_px_dimen_code (pdftex_first_dimen_code+10) 
#define pdftex_last_dimen_code (pdftex_first_dimen_code+10) 
#define dimen_pars (pdftex_last_dimen_code+1)  \

#define pdftex_first_convert_code (Prote_last_convert_code+1) 
#define pdftex_revision_code (pdftex_first_convert_code+0) 
#define pdftex_banner_code (pdftex_first_convert_code+1) 
#define pdf_font_name_code (pdftex_first_convert_code+2) 
#define pdf_font_objnum_code (pdftex_first_convert_code+3) 
#define pdf_font_size_code (pdftex_first_convert_code+4) 
#define pdf_page_ref_code (pdftex_first_convert_code+5) 
#define pdf_xform_name_code (pdftex_first_convert_code+6) 
#define pdf_escape_string_code (pdftex_first_convert_code+7) 
#define pdf_escape_name_code (pdftex_first_convert_code+8) 
#define left_margin_kern_code (pdftex_first_convert_code+9) 
#define right_margin_kern_code (pdftex_first_convert_code+10) 
#define pdf_colorstack_init_code (pdftex_first_convert_code+11) 
#define pdf_escape_hex_code (pdftex_first_convert_code+12) 
#define pdf_unescape_hex_code (pdftex_first_convert_code+13) 
#define pdf_match_code (pdftex_first_convert_code+14) 
#define pdf_last_match_code (pdftex_first_convert_code+15) 
#define pdf_insert_ht_code (pdftex_first_convert_code+16) 
#define pdf_ximage_bbox_code (pdftex_first_convert_code+17) 
#define pdftex_convert_codes (pdftex_first_convert_code+18)  \
 \

#define pdf_literal_node (pdftex_first_extension_code+0)  \

#define pdf_lateliteral_node (pdftex_first_extension_code+1)  \

#define pdf_obj_code (pdftex_first_extension_code+2) 
#define pdf_refobj_node (pdftex_first_extension_code+3) 
#define pdf_xform_code (pdftex_first_extension_code+4) 
#define pdf_refxform_node (pdftex_first_extension_code+5) 
#define pdf_ximage_code (pdftex_first_extension_code+6) 
#define pdf_refximage_node (pdftex_first_extension_code+7) 
#define pdf_annot_node (pdftex_first_extension_code+8) 
#define pdf_start_link_node (pdftex_first_extension_code+9) 
#define pdf_end_link_node (pdftex_first_extension_code+10) 
#define pdf_outline_code (pdftex_first_extension_code+11) 
#define pdf_dest_node (pdftex_first_extension_code+12) 
#define pdf_thread_node (pdftex_first_extension_code+13) 
#define pdf_start_thread_node (pdftex_first_extension_code+14) 
#define pdf_end_thread_node (pdftex_first_extension_code+15)  \

#define pdf_info_code (pdftex_first_extension_code+16) 
#define pdf_catalog_code (pdftex_first_extension_code+17) 
#define pdf_names_code (pdftex_first_extension_code+18)  \

#define pdf_font_attr_code (pdftex_first_extension_code+19) 
#define pdf_include_chars_code (pdftex_first_extension_code+20) 
#define pdf_map_file_code (pdftex_first_extension_code+21) 
#define pdf_map_line_code (pdftex_first_extension_code+22) 
#define pdf_trailer_code (pdftex_first_extension_code+23) 
#define pdf_trailer_id_code (pdftex_first_extension_code+24)  \

#define pdf_font_expand_code (pdftex_first_extension_code+25)  \

#define pdf_snap_ref_point_node (pdftex_first_extension_code+26) 
#define pdf_snapy_node (pdftex_first_extension_code+27) 
#define pdf_snapy_comp_node (pdftex_first_extension_code+28) 
#define pdf_glyph_to_unicode_code (pdftex_first_extension_code+29) 
#define pdf_colorstack_node (pdftex_first_extension_code+30) 
#define pdf_setmatrix_node (pdftex_first_extension_code+31) 
#define pdf_save_node (pdftex_first_extension_code+32) 
#define pdf_restore_node (pdftex_first_extension_code+33) 
#define pdf_nobuiltin_tounicode_code (pdftex_first_extension_code+34) 
#define pdf_interword_space_on_node (pdftex_first_extension_code+35) 
#define pdf_interword_space_off_node (pdftex_first_extension_code+36) 
#define pdf_fake_space_node (pdftex_first_extension_code+37) 
#define pdf_running_link_off_node (pdftex_first_extension_code+38) 
#define pdf_running_link_on_node (pdftex_first_extension_code+39) 
#define pdf_space_font_code (pdftex_first_extension_code+40)  \

#define tracing_stack_level_code (pdftex_first_extension_code+41) 
#define pdf_par_token_context_code (pdftex_first_extension_code+42) 
#define pdf_par_token_name_code (pdftex_first_extension_code+43) 
#define pdf_show_stream_code (pdftex_first_extension_code+44)  \

#define pdftex_last_extension_code (pdftex_first_extension_code+44)  \

#define pdf_action_page 0
#define pdf_action_goto 1
#define pdf_action_thread 2
#define pdf_action_user 3 \

#define pdf_dest_xyz 0
#define pdf_dest_fit 1
#define pdf_dest_fith 2
#define pdf_dest_fitv 3
#define pdf_dest_fitb 4
#define pdf_dest_fitbh 5
#define pdf_dest_fitbv 6
#define pdf_dest_fitr 7 \

#define colorstack_set 0
#define colorstack_push 1
#define colorstack_data 1
#define colorstack_pop 2
#define colorstack_current 3 \


#line 402 "texprof.w"

enum{/*11:*/
#line 488 "texprof.w"

mem_max= 5000000,


mem_min= 0,


buf_size= 2000000,


error_line= 79,
half_error_line= 50,

max_print_line= 79,
stack_size= 5000,
max_in_open= 15,

font_max= 255,

font_mem_size= 8000000,
param_size= 10000,
nest_size= 500,
max_strings= 500000,
string_vacancies= 90000,


pool_size= 6250000,



save_size= 100000,

trie_size= 1000000,

trie_op_size= 35111,
dvi_buf_size= 16384,
file_name_size= 1024,
xchg_buffer_size= 64,


/*:11*/
#line 403 "texprof.w"

empty_string= 256
};
/*18:*/
#line 629 "texprof.w"

typedef uint8_t ASCII_code;

/*:18*//*25:*/
#line 865 "texprof.w"

typedef uint8_t eight_bits;
typedef struct{FILE*f;text_char d;}alpha_file;
typedef struct{FILE*f;eight_bits d;}byte_file;

/*:25*//*38:*/
#line 1193 "texprof.w"

typedef int32_t pool_pointer;
typedef int32_t str_number;
typedef uint8_t packed_ASCII_code;

/*:38*//*100:*/
#line 2231 "texprof.w"

typedef int scaled;
typedef int32_t nonnegative_integer;
typedef int8_t small_number;

/*:100*//*108:*/
#line 2426 "texprof.w"

#if __SIZEOF_FLOAT__==4
typedef float float32_t;
#else
#line 2430 "texprof.w"
#error  float type must have size 4
#endif
#line 2432 "texprof.w"
 typedef float glue_ratio;

/*:108*//*112:*/
#line 2535 "texprof.w"

typedef uint16_t quarterword;
typedef int32_t halfword;
typedef int8_t two_choices;
typedef int8_t four_choices;
typedef uint64_t fullword;
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
fullword w;
int i;
glue_ratio gr;
two_halves hh;
four_quarters qqqq;
};}memory_word;
typedef struct{FILE*f;memory_word d;}word_file;

/*:112*//*149:*/
#line 3261 "texprof.w"

typedef int8_t glue_ord;

/*:149*//*211:*/
#line 4441 "texprof.w"

typedef struct{int16_t mode_field;
pointer head_field,tail_field;
pointer eTeX_aux_field;
int pg_field,ml_field;
memory_word aux_field;
}list_state_record;

/*:211*//*268:*/
#line 6111 "texprof.w"

typedef int8_t group_code;

/*:268*//*299:*/
#line 6760 "texprof.w"

typedef struct{
quarterword state_field,index_field;
halfword start_field,loc_field,limit_field,name_field;
halfword depth_field;
}in_state_record;

/*:299*//*547:*/
#line 11220 "texprof.w"

typedef uint8_t internal_font_number;
typedef int32_t font_index;

/*:547*//*593:*/
#line 12421 "texprof.w"

typedef int16_t dvi_index;

/*:593*//*919:*/
#line 18718 "texprof.w"

typedef int32_t trie_pointer;

/*:919*//*924:*/
#line 18787 "texprof.w"

typedef int16_t hyph_pointer;

/*:924*//*1408:*/
#line 26187 "texprof.w"

typedef int32_t save_pointer;

/*:1408*//*1636:*/
#line 29166 "texprof.w"

typedef int mpfract;

/*:1636*/
#line 406 "texprof.w"

/*52:*/
#line 1386 "texprof.w"

static int s_no(const char*str);

/*:52*//*1560:*/
#line 28338 "texprof.w"

static void scan_general_x_text(void);

/*:1560*//*1562:*/
#line 28353 "texprof.w"

static void toks_to_str(void);

/*:1562*//*1690:*/
#line 29802 "texprof.w"

static void main_init(int ac,char*av[]);


/*:1690*//*1697:*/
#line 29960 "texprof.w"

static void parse_options(int argc,char*argv[]);

/*:1697*//*1710:*/
#line 30179 "texprof.w"

static void recorder_change_filename(const char*new_name);

/*:1710*//*1714:*/
#line 30245 "texprof.w"

static void recorder_record_input(const char*fname);

/*:1714*//*1730:*/
#line 30583 "texprof.w"

static int input_command_line(void);


/*:1730*/
#line 407 "texprof.w"

/*13:*/
#line 558 "texprof.w"

static int bad;

/*:13*//*20:*/
#line 670 "texprof.w"

static ASCII_code xord[256];

static text_char xchr[256];


/*:20*//*26:*/
#line 882 "texprof.w"

static unsigned char name_of_file0[file_name_size+1]= {0},
*const name_of_file= name_of_file0-1;

static int name_length;


/*:26*//*30:*/
#line 953 "texprof.w"

static ASCII_code buffer[buf_size+1];
static int first;
static int last;
static int max_buf_stack;

/*:30*//*32:*/
#line 1026 "texprof.w"

static alpha_file term_in;
static alpha_file term_out;

/*:32*//*39:*/
#line 1198 "texprof.w"

static packed_ASCII_code str_pool[pool_size+1];
static pool_pointer str_start[max_strings+1];
static pool_pointer pool_ptr;
static str_number str_ptr;
static pool_pointer init_pool_ptr;
static str_number init_str_ptr;

/*:39*//*53:*/
#line 1437 "texprof.w"

static alpha_file log_file;
static int selector;
static int8_t dig[23];
static int tally;
static int term_offset;

static int file_offset;

static ASCII_code trick_buf[error_line+1];

static int trick_count;
static int first_count;

/*:53*//*72:*/
#line 1796 "texprof.w"

static int interaction;

/*:72*//*75:*/
#line 1839 "texprof.w"

static bool deletions_allowed;
static bool set_box_allowed;
static int history;
static int error_count;


/*:75*//*78:*/
#line 1898 "texprof.w"

static char*help_line[6];
static int help_ptr;
static bool use_err_help;

/*:78*//*95:*/
#line 2168 "texprof.w"

static int interrupt;
static bool OK_to_interrupt;

/*:95*//*103:*/
#line 2301 "texprof.w"

static bool arith_error;
static scaled rem;

/*:103*//*114:*/
#line 2600 "texprof.w"

static pointer temp_ptr;

/*:114*//*115:*/
#line 2632 "texprof.w"

static memory_word mem0[mem_max-mem_min+1],
*const mem= mem0-mem_min;
static pointer lo_mem_max;
static pointer hi_mem_min;

/*:115*//*116:*/
#line 2646 "texprof.w"

static int var_used,dyn_used;
#ifdef STAT
#define incr_dyn_used incr(dyn_used)
#define decr_dyn_used decr(dyn_used)
#else
#line 2652 "texprof.w"
#define incr_dyn_used
#define decr_dyn_used
#endif
#line 2655 "texprof.w"

/*:116*//*117:*/
#line 2669 "texprof.w"

static pointer avail;
static pointer mem_end;

/*:117*//*123:*/
#line 2774 "texprof.w"

static pointer rover;

/*:123*//*164:*/
#line 3477 "texprof.w"

#ifdef DEBUG
static bool is_free0[mem_max-mem_min+1],
*const is_free= is_free0-mem_min;
static bool was_free0[mem_max-mem_min+1],
*const was_free= was_free0-mem_min;

static pointer was_mem_end,was_lo_max,was_hi_min;

static bool panicking;
#endif
#line 3488 "texprof.w"

/*:164*//*172:*/
#line 3633 "texprof.w"

static int font_in_short_display;

/*:172*//*180:*/
#line 3762 "texprof.w"

static int depth_threshold;
static int breadth_max;

/*:180*//*212:*/
#line 4464 "texprof.w"

static list_state_record nest[nest_size+1];
static int nest_ptr;
static int max_nest_stack;
static list_state_record cur_list;
static int shown_mode;

/*:212*//*245:*/
#line 5469 "texprof.w"

static int old_setting;
static int sys_time,sys_day,sys_month,sys_year;


/*:245*//*252:*/
#line 5649 "texprof.w"

static memory_word eqtb0[eqtb_size-active_base+1],
*const eqtb= eqtb0-active_base;
static quarterword xeq_level0[eqtb_size-int_base+1],
*const xeq_level= xeq_level0-int_base;

/*:252*//*255:*/
#line 5699 "texprof.w"

static two_halves hash0[undefined_control_sequence-hash_base],
*const hash= hash0-hash_base;

static pointer hash_used;
static bool no_new_control_sequence;
static int cs_count;

/*:255*//*270:*/
#line 6120 "texprof.w"

static memory_word save_stack[save_size+1];
static int save_ptr;
static int max_save_stack;
static quarterword cur_level;
static group_code cur_group;
static int cur_boundary;

/*:270*//*285:*/
#line 6408 "texprof.w"

static int mag_set;

/*:285*//*296:*/
#line 6669 "texprof.w"

static eight_bits cur_cmd;
static halfword cur_chr;
static pointer cur_cs;
static halfword cur_tok;

/*:296*//*300:*/
#line 6767 "texprof.w"

static in_state_record input_stack[stack_size+1];
static int input_ptr;
static int max_in_stack;
static in_state_record cur_input;


/*:300*//*303:*/
#line 6872 "texprof.w"

static int in_open;
static int open_parens;
static alpha_file input_file0[max_in_open],
*const input_file= input_file0-1;
static int line;
static int line_stack0[max_in_open],
*const line_stack= line_stack0-1;

/*:303*//*304:*/
#line 6917 "texprof.w"

static int scanner_status;
static pointer warning_index;
static pointer def_ref;

/*:304*//*307:*/
#line 7049 "texprof.w"

static pointer param_stack[param_size+1];

static int param_ptr;
static int max_param_stack;


/*:307*//*308:*/
#line 7069 "texprof.w"

static int align_state;
static int incsname_state;

/*:308*//*309:*/
#line 7081 "texprof.w"

static int base_ptr;

/*:309*//*332:*/
#line 7491 "texprof.w"

static pointer par_loc;
static halfword par_token;
static pointer input_loc;
static halfword input_token;

/*:332*//*360:*/
#line 7921 "texprof.w"

static bool force_eof;

/*:360*//*381:*/
#line 8276 "texprof.w"

static pointer cur_mark0[split_bot_mark_code-top_mark_code+1],
*const cur_mark= cur_mark0-top_mark_code;


/*:381*//*386:*/
#line 8331 "texprof.w"

static int long_state;

/*:386*//*387:*/
#line 8342 "texprof.w"

static pointer pstack[9];

/*:387*//*409:*/
#line 8729 "texprof.w"

static int cur_val;
static int cur_val_level;

/*:409*//*437:*/
#line 9166 "texprof.w"

static small_number radix;

/*:437*//*446:*/
#line 9301 "texprof.w"

static glue_ord cur_order;

/*:446*//*479:*/
#line 9938 "texprof.w"

static alpha_file read_file[16];
static int8_t read_open[17];

/*:479*//*488:*/
#line 10131 "texprof.w"

static pointer cond_ptr;
static int if_limit;
static small_number cur_if;
static int if_line;

/*:488*//*492:*/
#line 10157 "texprof.w"

static int skip_line;

/*:492*//*511:*/
#line 10495 "texprof.w"

static str_number cur_name;
static str_number cur_area;
static str_number cur_ext;

/*:511*//*512:*/
#line 10511 "texprof.w"

static pool_pointer area_delimiter;
static pool_pointer ext_delimiter;

/*:512*//*526:*/
#line 10722 "texprof.w"

static bool name_in_progress;
static str_number job_name;
static bool log_opened;

/*:526*//*531:*/
#line 10799 "texprof.w"

static byte_file dvi_file;
static str_number output_file_name;
static str_number log_name;

/*:531*//*538:*/
#line 10942 "texprof.w"

static byte_file tfm_file;

/*:538*//*548:*/
#line 11229 "texprof.w"

static memory_word font_info[font_mem_size+1];

static font_index fmem_ptr;
static internal_font_number font_ptr;
static four_quarters font_check0[font_max-font_base+1],
*const font_check= font_check0-font_base;
static scaled font_size0[font_max-font_base+1],
*const font_size= font_size0-font_base;
static scaled font_dsize0[font_max-font_base+1],
*const font_dsize= font_dsize0-font_base;
static font_index font_params0[font_max-font_base+1],
*const font_params= font_params0-font_base;

static str_number font_name0[font_max-font_base+1],
*const font_name= font_name0-font_base;
static str_number font_area0[font_max-font_base+1],
*const font_area= font_area0-font_base;
static eight_bits font_bc0[font_max-font_base+1],
*const font_bc= font_bc0-font_base;

static eight_bits font_ec0[font_max-font_base+1],
*const font_ec= font_ec0-font_base;

static pointer font_glue0[font_max-font_base+1],
*const font_glue= font_glue0-font_base;

static bool font_used0[font_max-font_base+1],
*const font_used= font_used0-font_base;

static int hyphen_char0[font_max-font_base+1],
*const hyphen_char= hyphen_char0-font_base;

static int skew_char0[font_max-font_base+1],
*const skew_char= skew_char0-font_base;

static font_index bchar_label0[font_max-font_base+1],
*const bchar_label= bchar_label0-font_base;


static int16_t font_bchar0[font_max-font_base+1],
*const font_bchar= font_bchar0-font_base;

static int16_t font_false_bchar0[font_max-font_base+1],
*const font_false_bchar= font_false_bchar0-font_base;


/*:548*//*549:*/
#line 11285 "texprof.w"

static int char_base0[font_max-font_base+1],
*const char_base= char_base0-font_base;

static int width_base0[font_max-font_base+1],
*const width_base= width_base0-font_base;

static int height_base0[font_max-font_base+1],
*const height_base= height_base0-font_base;

static int depth_base0[font_max-font_base+1],
*const depth_base= depth_base0-font_base;

static int italic_base0[font_max-font_base+1],
*const italic_base= italic_base0-font_base;

static int lig_kern_base0[font_max-font_base+1],
*const lig_kern_base= lig_kern_base0-font_base;

static int kern_base0[font_max-font_base+1],
*const kern_base= kern_base0-font_base;

static int exten_base0[font_max-font_base+1],
*const exten_base= exten_base0-font_base;

static int param_base0[font_max-font_base+1],
*const param_base= param_base0-font_base;


/*:549*//*554:*/
#line 11383 "texprof.w"

static four_quarters null_character;

/*:554*//*591:*/
#line 12380 "texprof.w"

static int total_pages;
static scaled max_v;
static scaled max_h;
static int max_push;
static int last_bop;
static int dead_cycles;
static bool doing_leaders;

static quarterword c,f;
static scaled rule_ht,rule_dp,rule_wd;
static pointer g;
static int lq,lr;

/*:591*//*594:*/
#line 12428 "texprof.w"

static eight_bits dvi_buf[dvi_buf_size+1];
static dvi_index half_buf;
static dvi_index dvi_limit;
static dvi_index dvi_ptr;
static int dvi_offset;

static int dvi_gone;

/*:594*//*604:*/
#line 12593 "texprof.w"

static pointer down_ptr,right_ptr;

/*:604*//*615:*/
#line 12819 "texprof.w"

static scaled dvi_h,dvi_v;
static scaled cur_h,cur_v;
static internal_font_number dvi_f;
static int cur_s;

/*:615*//*645:*/
#line 13430 "texprof.w"

static scaled total_stretch0[filll-normal+1],
*const total_stretch= total_stretch0-normal,
total_shrink0[filll-normal+1],*const total_shrink= total_shrink0-normal;

static int last_badness;

/*:645*//*646:*/
#line 13442 "texprof.w"

static pointer adjust_tail;

/*:646*//*660:*/
#line 13619 "texprof.w"

static int pack_begin_line;


/*:660*//*683:*/
#line 14040 "texprof.w"

static two_halves empty_field;
static four_quarters null_delimiter;

/*:683*//*718:*/
#line 14704 "texprof.w"

static pointer cur_mlist;
static small_number cur_style;
static small_number cur_size;
static scaled cur_mu;
static bool mlist_penalties;

/*:718*//*723:*/
#line 14794 "texprof.w"

static internal_font_number cur_f;
static quarterword cur_c;
static four_quarters cur_i;


/*:723*//*764:*/
#line 15617 "texprof.w"

static const int magic_offset= -9*ord_noad;

/*:764*//*769:*/
#line 15815 "texprof.w"

static pointer cur_align;
static pointer cur_span;
static pointer cur_loop;
static pointer align_ptr;
static pointer cur_head,cur_tail;

/*:769*//*813:*/
#line 16595 "texprof.w"

static pointer just_box;

/*:813*//*820:*/
#line 16743 "texprof.w"

static pointer passive;
static pointer printed_node;
static halfword pass_number;

/*:820*//*822:*/
#line 16782 "texprof.w"

static scaled active_width0[6],*const active_width= active_width0-1;

static scaled cur_active_width0[6],
*const cur_active_width= cur_active_width0-1;
static scaled background0[6],*const background= background0-1;
static scaled break_width0[6],*const break_width= break_width0-1;

/*:822*//*824:*/
#line 16840 "texprof.w"

static bool no_shrink_error_yet;

/*:824*//*827:*/
#line 16900 "texprof.w"

static pointer cur_p;
static bool second_pass;
static bool final_pass;
static int threshold;

/*:827*//*832:*/
#line 17001 "texprof.w"

static int minimal_demerits0[tight_fit-very_loose_fit+1],
*const minimal_demerits= minimal_demerits0-very_loose_fit;

static int minimum_demerits;

static pointer best_place0[tight_fit-very_loose_fit+1],
*const best_place= best_place0-very_loose_fit;

static halfword best_pl_line0[tight_fit-very_loose_fit+1],
*const best_pl_line= best_pl_line0-very_loose_fit;


/*:832*//*838:*/
#line 17122 "texprof.w"

static scaled disc_width;

/*:838*//*846:*/
#line 17264 "texprof.w"

static halfword easy_line;
static halfword last_special_line;

static scaled first_width;

static scaled second_width;
static scaled first_indent;
static scaled second_indent;

/*:846*//*871:*/
#line 17778 "texprof.w"

static pointer best_bet;
static int fewest_demerits;
static halfword best_line;
static int actual_looseness;

static int line_diff;


/*:871*//*891:*/
#line 18115 "texprof.w"

static int16_t hc[66];
static int hn;

static pointer ha,hb;
static internal_font_number hf;
static int16_t hu[64];
static int hyf_char;
static ASCII_code cur_lang,init_cur_lang;
static int l_hyf,r_hyf,init_l_hyf,init_r_hyf;
static halfword hyf_bchar;

/*:891*//*899:*/
#line 18255 "texprof.w"

static int8_t hyf[65];
static pointer init_list;
static bool init_lig;
static bool init_lft;

/*:899*//*904:*/
#line 18379 "texprof.w"

static small_number hyphen_passed;

/*:904*//*906:*/
#line 18420 "texprof.w"

static halfword cur_l,cur_r;
static pointer cur_q;
static pointer lig_stack;
static bool ligature_present;
static bool lft_hit,rt_hit;

/*:906*//*920:*/
#line 18725 "texprof.w"

static two_halves trie[trie_size+1];
static small_number hyf_distance0[trie_op_size],
*const hyf_distance= hyf_distance0-1;
static small_number hyf_num0[trie_op_size],
*const hyf_num= hyf_num0-1;
static quarterword hyf_next0[trie_op_size],
*const hyf_next= hyf_next0-1;
static uint16_t op_start[256];

/*:920*//*925:*/
#line 18790 "texprof.w"

static str_number hyph_word[hyph_size+1];
static pointer hyph_list[hyph_size+1];
static hyph_pointer hyph_count;

/*:925*//*942:*/
#line 19009 "texprof.w"

#ifdef INIT
static uint16_t trie_op_hash0[trie_op_size+trie_op_size+1],
*const trie_op_hash= trie_op_hash0+trie_op_size;

static quarterword trie_used[256];

static ASCII_code trie_op_lang0[trie_op_size],
*const trie_op_lang= trie_op_lang0-1;

static quarterword trie_op_val0[trie_op_size],
*const trie_op_val= trie_op_val0-1;

static int trie_op_ptr;
#endif
#line 19024 "texprof.w"

/*:942*//*946:*/
#line 19105 "texprof.w"

#ifdef INIT
static packed_ASCII_code trie_c[trie_size+1];

static quarterword trie_o[trie_size+1];

static trie_pointer trie_l[trie_size+1];

static trie_pointer trie_r[trie_size+1];

static trie_pointer trie_ptr;
static trie_pointer trie_hash[trie_size+1];

#endif
#line 19119 "texprof.w"

/*:946*//*949:*/
#line 19192 "texprof.w"

#ifdef INIT
static bool trie_taken0[trie_size],
*const trie_taken= trie_taken0-1;

static trie_pointer trie_min[256];

static trie_pointer trie_max;
static bool trie_not_ready;
#endif
#line 19202 "texprof.w"

/*:949*//*970:*/
#line 19570 "texprof.w"

static scaled best_height_plus_depth;


/*:970*//*979:*/
#line 19783 "texprof.w"

static pointer page_tail;
static int page_contents;
static scaled page_max_depth;
static pointer best_page_break;
static int least_page_cost;
static scaled best_size;

/*:979*//*981:*/
#line 19866 "texprof.w"

static scaled page_so_far[8];
static pointer last_glue;
static int last_penalty;
static scaled last_kern;
static int last_node_type;
static int insert_penalties;


/*:981*//*988:*/
#line 20001 "texprof.w"

static bool output_active;

/*:988*//*1031:*/
#line 20751 "texprof.w"

static internal_font_number main_f;
static four_quarters main_i;
static four_quarters main_j;
static font_index main_k;
static pointer main_p;
static int main_s;
static halfword bchar;
static halfword false_bchar;
static bool cancel_boundary;
static bool ins_disc;

/*:1031*//*1073:*/
#line 21540 "texprof.w"

static pointer cur_box;

/*:1073*//*1265:*/
#line 24239 "texprof.w"

static halfword after_token;

/*:1265*//*1280:*/
#line 24344 "texprof.w"

static bool long_help_seen;

/*:1280*//*1298:*/
#line 24540 "texprof.w"

static str_number format_ident,frozen_format_ident;

/*:1298*//*1304:*/
#line 24627 "texprof.w"

static word_file fmt_file;

/*:1304*//*1330:*/
#line 25093 "texprof.w"

static int ready_already;

/*:1330*//*1341:*/
#line 25438 "texprof.w"

static alpha_file write_file[16];
static bool write_open[18];

/*:1341*//*1344:*/
#line 25472 "texprof.w"

static pointer write_loc;

/*:1344*//*1382:*/
#line 25908 "texprof.w"

static int eTeX_mode;

/*:1382*//*1390:*/
#line 25979 "texprof.w"

static bool eof_seen0[max_in_open],
*const eof_seen= eof_seen0-1;

/*:1390*//*1432:*/
#line 26474 "texprof.w"

static pointer pseudo_files;

/*:1432*//*1455:*/
#line 26737 "texprof.w"

static save_pointer grp_stack[max_in_open+1];
static pointer if_stack[max_in_open+1];

/*:1455*//*1496:*/
#line 27379 "texprof.w"

static halfword max_reg_num;
static char*max_reg_help_line;

/*:1496*//*1498:*/
#line 27446 "texprof.w"

static pointer sa_root0[mark_val-int_val+1],
*const sa_root= sa_root0-int_val;
static pointer cur_ptr;
static memory_word sa_null;

/*:1498*//*1517:*/
#line 27842 "texprof.w"

static pointer sa_chain;
static quarterword sa_level;

/*:1517*//*1528:*/
#line 28089 "texprof.w"

static trie_pointer hyph_start;
static trie_pointer hyph_index;

/*:1528*//*1529:*/
#line 28101 "texprof.w"

static pointer disc_ptr0[vsplit_code-copy_code+1],
*const disc_ptr= disc_ptr0-copy_code;

/*:1529*//*1537:*/
#line 28165 "texprof.w"

static int expand_depth_count;

/*:1537*//*1541:*/
#line 28189 "texprof.w"

static int Prote_mode;

/*:1541*//*1565:*/
#line 28408 "texprof.w"

static eight_bits xchg_buffer0[xchg_buffer_size],
*const xchg_buffer= xchg_buffer0-1;

static int xchg_buffer_length;
/*:1565*//*1580:*/
#line 28584 "texprof.w"

static memory_word ROM0[ROM_size-ROM_base+1],
*const ROM= ROM0-ROM_base;

/*:1580*//*1607:*/
#line 28827 "texprof.w"

static double reset_timer= 0.0;


/*:1607*//*1631:*/
#line 29086 "texprof.w"

static int two_to_the[31];
static int spec_log0[28],*const spec_log= spec_log0-1;

/*:1631*//*1642:*/
#line 29304 "texprof.w"

static mpfract randoms[55];
static int j_random;

/*:1642*//*1643:*/
#line 29311 "texprof.w"

static int random_seed;

/*:1643*//*1668:*/
#line 29599 "texprof.w"

static scaled last_saved_xpos,last_saved_ypos;

/*:1668*//*1674:*/
#line 29647 "texprof.w"

static int last_save_pos_number;

/*:1674*//*1688:*/
#line 29779 "texprof.w"

static char**argv;
static int argc;

/*:1688*//*1694:*/
#line 29908 "texprof.w"

static int iniversion= false,etexp= false,ltxp= false,recorder_enabled= false;
static int parsefirstlinep= -1,filelineerrorstylep= -1,interaction_option= -1;
static const char*user_progname= NULL,*output_directory= NULL,*c_job_name= NULL,
*dump_name= NULL;

/*:1694*//*1716:*/
#line 30281 "texprof.w"

static char**cnf_lines= NULL;
static int cnf_count= 0;

/*:1716*//*1725:*/
#line 30438 "texprof.w"

static char*source_filename_stack0[max_in_open]= {NULL},**const source_filename_stack= source_filename_stack0-1;
static char*full_source_filename_stack0[max_in_open]= {NULL},**const full_source_filename_stack= full_source_filename_stack0-1;
static char*full_name_of_file= NULL;

/*:1725*//*1741:*/
#line 30999 "texprof.w"

static int profile_on= false;

/*:1741*//*1745:*/
#line 31050 "texprof.w"

static uint8_t input_file_num0[max_in_open],
*const input_file_num= input_file_num0-1;
static uint8_t read_file_num[20];

/*:1745*//*1746:*/
#line 31063 "texprof.w"

#define FILE_NUM_BITS 8
#define MAX_FILE_NUM ((1<<FILE_NUM_BITS)-1)
#define LINE_BITS 16
#define MAX_LINE ((1<<LINE_BITS)-1)
#define FILE_LINE(F,L) (((F)<<(LINE_BITS))|(L))
#define FL_FILE(FL) ((FL)>>LINE_BITS)
#define FL_LINE(FL) ((FL)&MAX_LINE)
static char*file_num_name[MAX_FILE_NUM+1];
static int file_from_cmd[MAX_FILE_NUM+1];
static int file_to_cmd[MAX_FILE_NUM+1];
static int file_num;
static uint32_t cur_file_line= 0;

/*:1746*//*1754:*/
#line 31160 "texprof.w"

static uint32_t fl_mem0[mem_max-mem_min+1],
*const fl_mem= fl_mem0-mem_min;

/*:1754*//*1755:*/
#line 31187 "texprof.w"

static long start_nsec,start_sec,diff_nsec;
struct timespec ts;
static int time_error;

/*:1755*//*1758:*/
#line 31238 "texprof.w"

#define MAX_STAMPS 80000000
#define MAX_MACRO_STACK  40000
#define POP_BIT 0x80

static uint32_t stamp[MAX_STAMPS];
static uint32_t st_count= 0;
static uint32_t cmd_count= 0;
static int prof_cmd= 0;
static uint32_t prof_file_line= 0;

/*:1758*//*1772:*/
#line 31544 "texprof.w"

static uint64_t macro_stack[MAX_MACRO_STACK]= {0};
static int prof_depth;
static int last_depth;
static int unchanged_depth;
static int prof_max_depth;

/*:1772*//*1797:*/
#line 32082 "texprof.w"

static int pdf_on= false;

/*:1797*//*1801:*/
#line 32150 "texprof.w"

static int
pdf_last_obj,
pdf_last_xform,
pdf_last_ximage,
pdf_last_ximage_pages,
pdf_last_annot,
pdf_retval,
pdf_last_ximage_colordepth,
pdf_last_link;


/*:1801*/
#line 408 "texprof.w"


static void initialize(void)
{/*19:*/
#line 663 "texprof.w"

int i;

/*:19*//*162:*/
#line 3436 "texprof.w"

int k;

/*:162*//*926:*/
#line 18795 "texprof.w"

int z;

/*:926*/
#line 411 "texprof.w"

/*8:*/
#line 456 "texprof.w"

/*21:*/
#line 685 "texprof.w"

xchr[040]= ' ';
xchr[041]= '!';
xchr[042]= '"';
xchr[043]= '#';
xchr[044]= '$';
xchr[045]= '%';
xchr[046]= '&';
xchr[047]= '\'';
xchr[050]= '(';
xchr[051]= ')';
xchr[052]= '*';
xchr[053]= '+';
xchr[054]= ',';
xchr[055]= '-';
xchr[056]= '.';
xchr[057]= '/';
xchr[060]= '0';
xchr[061]= '1';
xchr[062]= '2';
xchr[063]= '3';
xchr[064]= '4';
xchr[065]= '5';
xchr[066]= '6';
xchr[067]= '7';
xchr[070]= '8';
xchr[071]= '9';
xchr[072]= ':';
xchr[073]= ';';
xchr[074]= '<';
xchr[075]= '=';
xchr[076]= '>';
xchr[077]= '?';
xchr[0100]= '@';
xchr[0101]= 'A';
xchr[0102]= 'B';
xchr[0103]= 'C';
xchr[0104]= 'D';
xchr[0105]= 'E';
xchr[0106]= 'F';
xchr[0107]= 'G';
xchr[0110]= 'H';
xchr[0111]= 'I';
xchr[0112]= 'J';
xchr[0113]= 'K';
xchr[0114]= 'L';
xchr[0115]= 'M';
xchr[0116]= 'N';
xchr[0117]= 'O';
xchr[0120]= 'P';
xchr[0121]= 'Q';
xchr[0122]= 'R';
xchr[0123]= 'S';
xchr[0124]= 'T';
xchr[0125]= 'U';
xchr[0126]= 'V';
xchr[0127]= 'W';
xchr[0130]= 'X';
xchr[0131]= 'Y';
xchr[0132]= 'Z';
xchr[0133]= '[';
xchr[0134]= '\\';
xchr[0135]= ']';
xchr[0136]= '^';
xchr[0137]= '_';
xchr[0140]= '`';
xchr[0141]= 'a';
xchr[0142]= 'b';
xchr[0143]= 'c';
xchr[0144]= 'd';
xchr[0145]= 'e';
xchr[0146]= 'f';
xchr[0147]= 'g';
xchr[0150]= 'h';
xchr[0151]= 'i';
xchr[0152]= 'j';
xchr[0153]= 'k';
xchr[0154]= 'l';
xchr[0155]= 'm';
xchr[0156]= 'n';
xchr[0157]= 'o';
xchr[0160]= 'p';
xchr[0161]= 'q';
xchr[0162]= 'r';
xchr[0163]= 's';
xchr[0164]= 't';
xchr[0165]= 'u';
xchr[0166]= 'v';
xchr[0167]= 'w';
xchr[0170]= 'x';
xchr[0171]= 'y';
xchr[0172]= 'z';
xchr[0173]= '{';
xchr[0174]= '|';
xchr[0175]= '}';
xchr[0176]= '~';

/*:21*//*23:*/
#line 816 "texprof.w"

for(i= 0;i<=037;i++)xchr[i]= chr(i);
for(i= 0177;i<=0377;i++)xchr[i]= chr(i);

/*:23*//*24:*/
#line 826 "texprof.w"

for(i= first_text_char;i<=last_text_char;i++)xord[chr(i)]= invalid_code;
for(i= 0200;i<=0377;i++)xord[xchr[i]]= i;
for(i= 0;i<=0176;i++)xord[xchr[i]]= i;

/*:24*//*73:*/
#line 1799 "texprof.w"

if(interaction_option<0)interaction= error_stop_mode;
else interaction= interaction_option;

/*:73*//*76:*/
#line 1849 "texprof.w"

deletions_allowed= true;set_box_allowed= true;
error_count= 0;

/*:76*//*79:*/
#line 1903 "texprof.w"

help_ptr= 0;use_err_help= false;

/*:79*//*96:*/
#line 2172 "texprof.w"

interrupt= 0;OK_to_interrupt= true;

/*:96*//*165:*/
#line 3489 "texprof.w"

#ifdef DEBUG
was_mem_end= mem_min;
was_lo_max= mem_min;was_hi_min= mem_max;
panicking= false;
#endif
#line 3495 "texprof.w"

/*:165*//*214:*/
#line 4484 "texprof.w"

nest_ptr= 0;max_nest_stack= 0;
mode= vmode;head= contrib_head;tail= contrib_head;
eTeX_aux= null;
prev_depth= ignore_depth;mode_line= 0;
prev_graf= 0;shown_mode= 0;
/*990:*/
#line 20011 "texprof.w"

page_contents= empty;page_tail= page_head;link(page_head)= null;
last_glue= max_halfword;last_penalty= 0;last_kern= 0;
last_node_type= -1;
page_depth= 0;page_max_depth= 0

/*:990*/
#line 4490 "texprof.w"
;

/*:214*//*253:*/
#line 5655 "texprof.w"

for(k= int_base;k<=eqtb_size;k++)xeq_level[k]= level_one;

/*:253*//*256:*/
#line 5707 "texprof.w"

no_new_control_sequence= true;
next(hash_base)= 0;text(hash_base)= 0;
for(k= hash_base+1;k<=undefined_control_sequence-1;k++)hash[k]= hash[hash_base];

/*:256*//*271:*/
#line 6133 "texprof.w"

save_ptr= 0;cur_level= level_one;cur_group= bottom_level;cur_boundary= 0;
max_save_stack= 0;

/*:271*//*286:*/
#line 6411 "texprof.w"

mag_set= 0;

/*:286*//*382:*/
#line 8281 "texprof.w"

top_mark= null;first_mark= null;bot_mark= null;
split_first_mark= null;split_bot_mark= null;

/*:382*//*438:*/
#line 9173 "texprof.w"

cur_val= 0;cur_val_level= int_val;radix= 0;cur_order= normal;

/*:438*//*480:*/
#line 9942 "texprof.w"

for(k= 0;k<=16;k++)read_open[k]= closed;

/*:480*//*489:*/
#line 10137 "texprof.w"

cond_ptr= null;if_limit= normal;cur_if= 0;if_line= 0;

/*:489*//*550:*/
#line 11314 "texprof.w"

for(k= font_base;k<=font_max;k++)font_used[k]= false;

/*:550*//*555:*/
#line 11386 "texprof.w"

null_character.b0= min_quarterword;null_character.b1= min_quarterword;
null_character.b2= min_quarterword;null_character.b3= min_quarterword;

/*:555*//*592:*/
#line 12394 "texprof.w"

total_pages= 0;max_v= 0;max_h= 0;max_push= 0;last_bop= -1;
doing_leaders= false;dead_cycles= 0;cur_s= -1;

/*:592*//*595:*/
#line 12440 "texprof.w"

half_buf= dvi_buf_size/2;dvi_limit= dvi_buf_size;dvi_ptr= 0;
dvi_offset= 0;dvi_gone= 0;

/*:595*//*605:*/
#line 12596 "texprof.w"

down_ptr= null;right_ptr= null;

/*:605*//*647:*/
#line 13445 "texprof.w"
adjust_tail= null;last_badness= 0;

/*:647*//*661:*/
#line 13623 "texprof.w"

pack_begin_line= 0;

/*:661*//*684:*/
#line 14044 "texprof.w"

empty_field.rh= empty;empty_field.lh= null;
null_delimiter.b0= 0;null_delimiter.b1= min_quarterword;
null_delimiter.b2= 0;null_delimiter.b3= min_quarterword;

/*:684*//*770:*/
#line 15824 "texprof.w"

align_ptr= null;cur_align= null;cur_span= null;cur_loop= null;
cur_head= null;cur_tail= null;

/*:770*//*927:*/
#line 18798 "texprof.w"

for(z= 0;z<=hyph_size;z++)
{hyph_word[z]= 0;hyph_list[z]= null;
}
hyph_count= 0;

/*:927*//*989:*/
#line 20004 "texprof.w"

output_active= false;insert_penalties= 0;

/*:989*//*1032:*/
#line 20767 "texprof.w"

ligature_present= false;cancel_boundary= false;lft_hit= false;rt_hit= false;
ins_disc= false;

/*:1032*//*1266:*/
#line 24242 "texprof.w"

after_token= 0;

/*:1266*//*1281:*/
#line 24347 "texprof.w"
long_help_seen= false;

/*:1281*//*1299:*/
#line 24543 "texprof.w"

format_ident= frozen_format_ident= 0;

/*:1299*//*1342:*/
#line 25442 "texprof.w"

for(k= 0;k<=17;k++)write_open[k]= false;

/*:1342*//*1433:*/
#line 26477 "texprof.w"

pseudo_files= null;

/*:1433*//*1499:*/
#line 27452 "texprof.w"

sa_mark= null;sa_null.hh.lh= null;sa_null.hh.rh= null;

/*:1499*//*1518:*/
#line 27846 "texprof.w"

sa_chain= null;sa_level= level_zero;

/*:1518*//*1530:*/
#line 28105 "texprof.w"

page_disc= null;split_disc= null;

/*:1530*//*1751:*/
#line 31127 "texprof.w"

file_num_name[unknown_file]= "unknown";
file_num_name[system_file]= "system";
file_num_name[terminal_file]= "terminal";
file_num= terminal_file;

/*:1751*/
#line 457 "texprof.w"

#ifdef INIT
if(iniversion)
{/*163:*/
#line 3439 "texprof.w"

for(k= mem_bot+1;k<=lo_mem_stat_max;k++)mem[k].sc= 0;


k= mem_bot;while(k<=lo_mem_stat_max)

{glue_ref_count(k)= null+1;
stretch_order(k)= normal;shrink_order(k)= normal;
k= k+glue_spec_size;
}
stretch(fil_glue)= unity;stretch_order(fil_glue)= fil;
stretch(fill_glue)= unity;stretch_order(fill_glue)= fill;
stretch(ss_glue)= unity;stretch_order(ss_glue)= fil;
shrink(ss_glue)= unity;shrink_order(ss_glue)= fil;
stretch(fil_neg_glue)= -unity;stretch_order(fil_neg_glue)= fil;
rover= lo_mem_stat_max+1;
link(rover)= empty_flag;
node_size(rover)= 1000;
llink(rover)= rover;rlink(rover)= rover;
lo_mem_max= rover+1000;link(lo_mem_max)= null;info(lo_mem_max)= null;
for(k= hi_mem_stat_min;k<=mem_top;k++)
mem[k]= mem[lo_mem_max];
/*789:*/
#line 16137 "texprof.w"

info(omit_template)= end_template_token;

/*:789*//*796:*/
#line 16246 "texprof.w"

link(end_span)= max_quarterword+1;info(end_span)= null;

/*:796*//*819:*/
#line 16713 "texprof.w"

type(last_active)= hyphenated;line_number(last_active)= max_halfword;
subtype(last_active)= 0;

/*:819*//*980:*/
#line 19836 "texprof.w"

subtype(page_ins_head)= qi(255);
type(page_ins_head)= split_up;link(page_ins_head)= page_ins_head;

/*:980*//*987:*/
#line 19995 "texprof.w"

type(page_head)= glue_node;subtype(page_head)= normal;

/*:987*/
#line 3461 "texprof.w"
;
avail= null;mem_end= mem_top;
hi_mem_min= hi_mem_stat_min;
var_used= lo_mem_stat_max+1-mem_bot;dyn_used= hi_mem_stat_usage;


/*:163*//*221:*/
#line 4677 "texprof.w"

eq_type(undefined_control_sequence)= undefined_cs;
equiv(undefined_control_sequence)= null;
eq_level(undefined_control_sequence)= level_zero;
for(k= active_base;k<=undefined_control_sequence-1;k++)
eqtb[k]= eqtb[undefined_control_sequence];

/*:221*//*227:*/
#line 4832 "texprof.w"

equiv(glue_base)= zero_glue;eq_level(glue_base)= level_one;
eq_type(glue_base)= glue_ref;
for(k= glue_base+1;k<=local_base-1;k++)eqtb[k]= eqtb[glue_base];
glue_ref_count(zero_glue)= glue_ref_count(zero_glue)+local_base-glue_base;

/*:227*//*231:*/
#line 4966 "texprof.w"

par_shape_ptr= null;eq_type(par_shape_loc)= shape_ref;
eq_level(par_shape_loc)= level_one;
for(k= etex_pen_base;k<=etex_pens-1;k++)
eqtb[k]= eqtb[par_shape_loc];
for(k= output_routine_loc;k<=toks_base+255;k++)
eqtb[k]= eqtb[undefined_control_sequence];
box(0)= null;eq_type(box_base)= box_ref;eq_level(box_base)= level_one;
for(k= box_base+1;k<=box_base+255;k++)eqtb[k]= eqtb[box_base];
cur_font= null_font;eq_type(cur_font_loc)= data;
eq_level(cur_font_loc)= level_one;
for(k= math_font_base;k<=math_font_base+47;k++)eqtb[k]= eqtb[cur_font_loc];
equiv(cat_code_base)= 0;eq_type(cat_code_base)= data;
eq_level(cat_code_base)= level_one;
for(k= cat_code_base+1;k<=int_base-1;k++)eqtb[k]= eqtb[cat_code_base];
for(k= 0;k<=255;k++)
{cat_code(k)= other_char;math_code(k)= hi(k);sf_code(k)= 1000;
}
cat_code(carriage_return)= car_ret;cat_code(' ')= spacer;
cat_code('\\')= escape;cat_code('%')= comment;
cat_code(invalid_code)= invalid_char;cat_code(null_code)= ignore;
for(k= '0';k<='9';k++)math_code(k)= hi(k+var_code);
for(k= 'A';k<='Z';k++)
{cat_code(k)= letter;cat_code(k+'a'-'A')= letter;
math_code(k)= hi(k+var_code+0x100);
math_code(k+'a'-'A')= hi(k+'a'-'A'+var_code+0x100);
lc_code(k)= k+'a'-'A';lc_code(k+'a'-'A')= k+'a'-'A';
uc_code(k)= k;uc_code(k+'a'-'A')= k;
sf_code(k)= 999;
}

/*:231*//*239:*/
#line 5406 "texprof.w"

for(k= int_base;k<=del_code_base-1;k++)eqtb[k].i= 0;
mag= 1000;tolerance= 10000;hang_after= 1;max_dead_cycles= 25;
escape_char= '\\';end_line_char= carriage_return;
for(k= 0;k<=255;k++)del_code(k)= -1;
del_code('.')= 0;

/*:239*//*249:*/
#line 5618 "texprof.w"

for(k= dimen_base;k<=eqtb_size;k++)eqtb[k].sc= 0;

/*:249*//*257:*/
#line 5712 "texprof.w"

hash_used= frozen_control_sequence;
cs_count= 0;
eq_type(frozen_dont_expand)= dont_expand;
text(frozen_dont_expand)= s_no("notexpanded:");


/*:257*//*551:*/
#line 11320 "texprof.w"

font_ptr= null_font;fmem_ptr= 7;
font_name[null_font]= s_no("nullfont");font_area[null_font]= empty_string;
hyphen_char[null_font]= '-';skew_char[null_font]= -1;
bchar_label[null_font]= non_address;
font_bchar[null_font]= non_char;font_false_bchar[null_font]= non_char;
font_bc[null_font]= 1;font_ec[null_font]= 0;
font_size[null_font]= 0;font_dsize[null_font]= 0;
char_base[null_font]= 0;width_base[null_font]= 0;
height_base[null_font]= 0;depth_base[null_font]= 0;
italic_base[null_font]= 0;lig_kern_base[null_font]= 0;
kern_base[null_font]= 0;exten_base[null_font]= 0;
font_glue[null_font]= null;font_params[null_font]= 7;
param_base[null_font]= -1;
for(k= 0;k<=6;k++)font_info[k].sc= 0;

/*:551*//*945:*/
#line 19082 "texprof.w"

for(k= -trie_op_size;k<=trie_op_size;k++)trie_op_hash[k]= 0;
for(k= 0;k<=255;k++)trie_used[k]= min_quarterword;
trie_op_ptr= 0;

/*:945*//*950:*/
#line 19209 "texprof.w"

trie_not_ready= true;trie_root= 0;trie_c[0]= si(0);trie_ptr= 0;

/*:950*//*1215:*/
#line 23523 "texprof.w"

text(frozen_protection)= s_no("inaccessible");


/*:1215*//*1300:*/
#line 24548 "texprof.w"

format_ident= frozen_format_ident= s_no(" (INITEX)");

/*:1300*//*1368:*/
#line 25691 "texprof.w"

text(end_write)= s_no("endwrite");eq_level(end_write)= level_one;
eq_type(end_write)= outer_call;equiv(end_write)= null;

/*:1368*//*1383:*/
#line 25911 "texprof.w"

eTeX_mode= 0;
/*1494:*/
#line 27371 "texprof.w"

max_reg_num= 255;
max_reg_help_line= "A register number must be between 0 and 255.";

/*:1494*/
#line 25913 "texprof.w"


/*:1383*//*1500:*/
#line 27455 "texprof.w"

for(i= int_val;i<=tok_val;i++)sa_root[i]= null;

/*:1500*//*1524:*/
#line 28036 "texprof.w"

hyph_root= 0;hyph_start= 0;

/*:1524*//*1542:*/
#line 28197 "texprof.w"

Prote_mode= 0;

/*:1542*//*1581:*/
#line 28593 "texprof.w"

ROM[ROM_undefined_primitive]= eqtb[undefined_control_sequence];
for(k= ROM_base;k<=256;k++)ROM[k]= ROM[ROM_undefined_primitive];
for(k= ROM_undefined_primitive+1;k<=ROM_size;k++)
ROM[k]= ROM[ROM_undefined_primitive];

/*:1581*//*1807:*/
#line 32416 "texprof.w"

dimen_par(pdf_h_origin_code)= 4736287;
dimen_par(pdf_v_origin_code)= 4736287;
int_par(pdf_compress_level_code)= 9;
int_par(pdf_objcompresslevel_code)= 0;
int_par(pdf_decimal_digits_code)= 3;
int_par(pdf_image_resolution_code)= 72;
int_par(pdf_major_version_code)= 1;
int_par(pdf_minor_version_code)= 4;
int_par(pdf_gamma_code)= 1000;
int_par(pdf_image_gamma_code)= 2200;
int_par(pdf_image_hicolor_code)= 1;
int_par(pdf_image_apply_gamma_code)= 0;
int_par(pdf_draftmode_code)= 0;
dimen_par(pdf_px_dimen_code)= 65782;

/*:1807*/
#line 460 "texprof.w"
}
#endif
#line 462 "texprof.w"

/*:8*/
#line 412 "texprof.w"
;
}
/*55:*/
#line 1460 "texprof.w"

#define put(F)    fwrite(&((F).d),sizeof((F).d),1,(F).f)
#define get(F)    (void)fread(&((F).d),sizeof((F).d),1,(F).f)

#define pascal_close(F)    fclose((F).f)
#define eof(F)    feof((F).f)
#define eoln(F)    ((F).d=='\n'||eof(F))
#define erstat(F)   ((F).f==NULL?-1:ferror((F).f))

#define pascal_read(F,X) ((X)= (F).d,get(F))
#define read_ln(F)  do get(F); while (!eoln(F))

#define pascal_write(F, FMT,...)    fprintf(F.f,FMT,## __VA_ARGS__)
#define write_ln(F,...)    pascal_write(F,__VA_ARGS__"\n")

#define wterm(FMT,...) pascal_write(term_out,FMT, ## __VA_ARGS__)
#define wterm_ln(FMT,...) wterm(FMT "\n", ## __VA_ARGS__)
#define wterm_cr         pascal_write(term_out,"\n")
#define wlog(FMT, ...) pascal_write(log_file,FMT, ## __VA_ARGS__)
#define wlog_ln(FMT, ...)   wlog(FMT "\n", ## __VA_ARGS__)
#define wlog_cr         pascal_write(log_file,"\n")

/*:55*//*56:*/
#line 1484 "texprof.w"

static void print_ln(void)
{switch(selector){
case term_and_log:{wterm_cr;wlog_cr;
term_offset= 0;file_offset= 0;
}break;
case log_only:{wlog_cr;file_offset= 0;
}break;
case term_only:{wterm_cr;term_offset= 0;
}break;
case no_print:case pseudo:case new_string:do_nothing;break;
default:write_ln(write_file[selector]);
}
}

/*:56*//*57:*/
#line 1503 "texprof.w"

static void print_char(ASCII_code s)
{
if(/*243:*/
#line 5445 "texprof.w"
s==new_line_char

/*:243*/
#line 1506 "texprof.w"
)
if(selector<pseudo)
{print_ln();return;
}
switch(selector){
case term_and_log:{wterm("%c",xchr[s]);wlog("%c",xchr[s]);
incr(term_offset);incr(file_offset);
if(term_offset==max_print_line)
{wterm_cr;term_offset= 0;
}
if(file_offset==max_print_line)
{wlog_cr;file_offset= 0;
}
}break;
case log_only:{wlog("%c",xchr[s]);incr(file_offset);
if(file_offset==max_print_line)print_ln();
}break;
case term_only:{wterm("%c",xchr[s]);incr(term_offset);
if(term_offset==max_print_line)print_ln();
}break;
case no_print:do_nothing;break;
case pseudo:if(tally<trick_count)trick_buf[tally%error_line]= s;break;
case new_string:{if(pool_ptr<pool_size)append_char(s);
}break;
default:pascal_write(write_file[selector],"%c",xchr[s]);
}
incr(tally);
}

/*:57*//*58:*/
#line 1543 "texprof.w"

static void print(char*s)
{if(s==NULL)s= "???";
while(*s!=0)print_char(*s++);
}

static void printn(int s)
{
pool_pointer j;
int nl;
if(s>=str_ptr){print("???");return;}

else if(s<256)
if(s<0){print("???");return;}
else{if(selector> pseudo)
{print_char(s);return;
}
if((/*243:*/
#line 5445 "texprof.w"
s==new_line_char

/*:243*/
#line 1560 "texprof.w"
))
if(selector<pseudo)
{print_ln();return;
}
nl= new_line_char;new_line_char= -1;

j= str_start[s];
while(j<str_start[s+1])
{print_char(so(str_pool[j]));incr(j);
}
new_line_char= nl;return;
}
j= str_start[s];
while(j<str_start[s+1])
{print_char(so(str_pool[j]));incr(j);
}
}

/*:58*//*59:*/
#line 1582 "texprof.w"

static void slow_print(int s)
{pool_pointer j;
if((s>=str_ptr)||(s<256))printn(s);
else{j= str_start[s];
while(j<str_start[s+1])
{printn(so(str_pool[j]));incr(j);
}
}
}

/*:59*//*61:*/
#line 1611 "texprof.w"

static void print_nl(char*s)
{if(((term_offset> 0)&&(odd(selector)))||
((file_offset> 0)&&(selector>=log_only)))print_ln();
print(s);
}

/*:61*//*62:*/
#line 1621 "texprof.w"

static void printn_esc(str_number s)
{int c;
/*242:*/
#line 5443 "texprof.w"
c= escape_char

/*:242*/
#line 1624 "texprof.w"
;
if(c>=0)if(c<256)printn(c);
slow_print(s);
}

static void print_esc(char*s)
{int c;
/*242:*/
#line 5443 "texprof.w"
c= escape_char

/*:242*/
#line 1631 "texprof.w"
;
if(c>=0)if(c<256)printn(c);
print(s);
}

/*:62*//*63:*/
#line 1638 "texprof.w"

static void print_the_digs(eight_bits k)

{while(k> 0)
{decr(k);
if(dig[k]<10)print_char('0'+dig[k]);
else print_char('A'-10+dig[k]);
}
}

/*:63*//*64:*/
#line 1654 "texprof.w"

static void print_int(int n)
{int k;
int m;
k= 0;
if(n<0)
{print_char('-');
if(n> -100000000)negate(n);
else{m= -1-n;n= m/10;m= (m%10)+1;k= 1;
if(m<10)dig[0]= m;
else{dig[0]= 0;incr(n);
}
}
}
do{dig[k]= n%10;n= n/10;incr(k);
}while(!(n==0));
print_the_digs(k);
}

/*:64*//*261:*/
#line 5791 "texprof.w"

static void print_cs(int p)
{if(p<hash_base)
if(p>=single_base)
if(p==null_cs)
{print_esc("csname");print_esc("endcsname");print_char(' ');
}
else{printn_esc(p-single_base);
if(cat_code(p-single_base)==letter)print_char(' ');
}
else if(p<active_base)print_esc("IMPOSSIBLE.");

else printn(p-active_base);
else if(p>=undefined_control_sequence)print_esc("IMPOSSIBLE.");
else if((text(p)<0)||(text(p)>=str_ptr))print_esc("NONEXISTENT.");

else{if(p==frozen_primitive)print_esc("primitive");
printn_esc(text(p));print_char(' ');
}
}

/*:261*//*262:*/
#line 5815 "texprof.w"

static void sprint_cs(pointer p)
{if(p<hash_base)
if(p<single_base)printn(p-active_base);
else if(p<null_cs)printn_esc(p-single_base);
else{print_esc("csname");print_esc("endcsname");
}
else printn_esc(text(p));
}

/*:262*//*517:*/
#line 10576 "texprof.w"

static void print_file_name(int n,int a,int e)
{slow_print(a);slow_print(n);slow_print(e);
}

/*:517*//*698:*/
#line 14347 "texprof.w"

static void print_size(int s)
{if(s==text_size)print_esc("textfont");
else if(s==script_size)print_esc("scriptfont");
else print_esc("scriptscriptfont");
}

/*:698*//*1354:*/
#line 25575 "texprof.w"

static void print_write_whatsit(char*s,pointer p)
{print_esc(s);
if(write_stream(p)<16)print_int(write_stream(p));
else if(write_stream(p)==16)print_char('*');

else print_char('-');
}

/*:1354*//*1504:*/
#line 27623 "texprof.w"

static void print_sa_num(pointer q)
{halfword n;
if(sa_index(q)<dimen_val_limit)n= sa_num(q);
else{n= hex_dig4(sa_index(q));q= link(q);n= n+16*sa_index(q);
q= link(q);n= n+256*(sa_index(q)+16*sa_index(link(q)));
}
print_int(n);
}

/*:1504*//*1726:*/
#line 30448 "texprof.w"

static void print_file_line(void)
{int level= in_open;
while(level> 0&&full_source_filename_stack[level]==NULL)level--;
if(level==0)print_nl("! ");
else
{print_nl("");print(full_source_filename_stack[level]);print_char(':');
if(level==in_open)print_int(line);
else print_int(line_stack[level]);
print(": ");
}
}

/*:1726*/
#line 414 "texprof.w"

/*71:*/
#line 1780 "texprof.w"

static void print_err(char*s)
{if(interaction==error_stop_mode)wake_up_terminal;
if(filelineerrorstylep)print_file_line();
else print_nl("! ");
print(s);
}

/*:71*//*77:*/
#line 1864 "texprof.w"

static void normalize_selector(void);
static void get_token(void);
static void term_input(void);
static void show_context(void);
static void begin_file_reading(void);
static void open_log_file(void);
static void close_files_and_terminate(void);
static void clear_for_error_prompt(void);
static void give_err_help(void);
#ifdef DEBUG
static void debug_help(void);
#else
#line 1877 "texprof.w"
#define debug_help() do_nothing
#endif
#line 1879 "texprof.w"

/*:77*//*80:*/
#line 1916 "texprof.w"

static void jump_out(void)
{close_files_and_terminate();exit(0);
}

/*:80*//*81:*/
#line 1923 "texprof.w"

static void error(void)
{
ASCII_code c;
int s1,s2,s3,s4;

if(history<error_message_issued)history= error_message_issued;
print_char('.');show_context();
if(interaction==error_stop_mode)
/*82:*/
#line 1942 "texprof.w"

loop{resume:if(interaction!=error_stop_mode)return;
clear_for_error_prompt();prompt_input("? ");

if(last==first)return;
c= buffer[first];
if(c>='a')c= c+'A'-'a';
/*83:*/
#line 1964 "texprof.w"

switch(c){
case'0':case'1':case'2':case'3':
case'4':case'5':case'6':case'7':
case'8':case'9':if(deletions_allowed)
/*87:*/
#line 2040 "texprof.w"

{s1= cur_tok;s2= cur_cmd;s3= cur_chr;s4= align_state;
align_state= 1000000;OK_to_interrupt= false;
if((last> first+1)&&(buffer[first+1]>='0')&&(buffer[first+1]<='9'))
c= c*10+buffer[first+1]-'0'*11;
else c= c-'0';
while(c> 0)
{get_token();
decr(c);
}
cur_tok= s1;cur_cmd= s2;cur_chr= s3;align_state= s4;OK_to_interrupt= true;
help2("I have just deleted some text, as you asked.",
"You can now delete more, or insert, or whatever.");
show_context();goto resume;
}

/*:87*/
#line 1969 "texprof.w"
break;

#ifdef DEBUG
case'D':{debug_help();goto resume;}
#endif
#line 1974 "texprof.w"
 case'E':if(base_ptr> 0)if(input_stack[base_ptr].name_field>=256)
{print_nl("You want to edit file ");

slow_print(input_stack[base_ptr].name_field);
print(" at line ");print_int(line);
interaction= scroll_mode;jump_out();
}break;
case'H':/*88:*/
#line 2056 "texprof.w"

{if(use_err_help)
{give_err_help();use_err_help= false;
}
else{if(help_ptr==0)
help2("Sorry, I don't know how to help in this situation.",
"Maybe you should try asking a human?");
do{decr(help_ptr);print(help_line[help_ptr]);print_ln();
}while(!(help_ptr==0));
}
help4("Sorry, I already gave what help I could...",
"Maybe you should try asking a human?",
"An error might have occurred before I noticed any problems.",
"``If all else fails, read the instructions.'");
goto resume;
}

/*:88*/
#line 1981 "texprof.w"

case'I':/*86:*/
#line 2024 "texprof.w"

{begin_file_reading();

if(last> first+1)
{loc= first+1;buffer[first]= ' ';
}
else{prompt_input("insert>");loc= first;

}
first= last;
cur_input.limit_field= last-1;
return;
}

/*:86*/
#line 1982 "texprof.w"

case'Q':case'R':case'S':/*85:*/
#line 2007 "texprof.w"

{error_count= 0;interaction= batch_mode+c-'Q';
print("OK, entering ");
switch(c){
case'Q':{print_esc("batchmode");decr(selector);
}break;
case'R':print_esc("nonstopmode");break;
case'S':print_esc("scrollmode");
}
print("...");print_ln();update_terminal;return;
}

/*:85*/
#line 1983 "texprof.w"

case'X':{interaction= scroll_mode;jump_out();
}break;
default:do_nothing;
}
/*84:*/
#line 1990 "texprof.w"

{print("Type <return> to proceed, S to scroll future error messages,");

print_nl("R to run without stopping, Q to run quietly,");
print_nl("I to insert something, ");
if(base_ptr> 0)if(input_stack[base_ptr].name_field>=256)
print("E to edit your file,");
if(deletions_allowed)
print_nl("1 or ... or 9 to ignore the next 1 to 9 tokens of input,");
print_nl("H for help, X to quit.");
}

/*:84*/
#line 1988 "texprof.w"


/*:83*/
#line 1949 "texprof.w"
;
}

/*:82*/
#line 1932 "texprof.w"
;
incr(error_count);
if(error_count==100)
{print_nl("(That makes 100 errors; please try again.)");

history= fatal_error_stop;jump_out();
}
/*89:*/
#line 2073 "texprof.w"

if(interaction> batch_mode)decr(selector);
if(use_err_help)
{print_ln();give_err_help();
}
else while(help_ptr> 0)
{decr(help_ptr);print_nl(help_line[help_ptr]);
}
print_ln();
if(interaction> batch_mode)incr(selector);
print_ln()

/*:89*/
#line 1939 "texprof.w"
;
}

/*:81*//*92:*/
#line 2112 "texprof.w"

static void fatal_error(char*s)
{normalize_selector();
print_err("Emergency stop");help1(s);succumb;

}

/*:92*//*93:*/
#line 2121 "texprof.w"

static void overflow(char*s,int n)
{normalize_selector();
print_err("TeX capacity exceeded, sorry [");

print(s);print_char('=');print_int(n);print_char(']');
help2("If you really absolutely need more capacity,",
"you can ask a wizard to enlarge me.");
succumb;
}

/*:93*//*94:*/
#line 2140 "texprof.w"

static void confusion(char*s)

{normalize_selector();
if(history<error_message_issued)
{print_err("This can't happen (");print(s);print_char(')');

help1("I'm broken. Please show this to someone who can fix can fix");
}
else{print_err("I can't go on meeting you like this");

help2("One of your faux pas seems to have wounded me deeply...",
"in fact, I'm barely conscious. Please fix it and try again.");
}
succumb;
}

/*:94*//*1813:*/
#line 32629 "texprof.w"

static void pdf_error(char*t,char*p)
{
normalize_selector();
print_err("pdfTeX error");
if(t!=0){
print(" (");
print(t);
print(")");
}
print(": ");print(p);
succumb;
}


/*:1813*/
#line 415 "texprof.w"


/*:4*//*27:*/
#line 903 "texprof.w"

static FILE*open_in(char*filename,kpse_file_format_type t,const char*rwb);
static bool a_open_in(alpha_file*f);
static bool b_open_in(byte_file*f);
static bool w_open_in(word_file*f);
static FILE*open_out(const char*file_name,const char*file_mode);
static bool a_open_out(alpha_file*f);
static bool b_open_out(byte_file*f);
#ifdef INIT
static bool w_open_out(word_file*f);
#endif
#line 914 "texprof.w"

/*:27*//*28:*/
#line 926 "texprof.w"
static void a_close(alpha_file*f)
{pascal_close((*f));
}

static void b_close(byte_file*f)
{pascal_close((*f));
}

static void w_close(word_file*f)
{pascal_close((*f));
}

/*:28*//*31:*/
#line 999 "texprof.w"
static bool input_ln(alpha_file*f,bool bypass_eoln)

{int last_nonblank;
if(bypass_eoln)if(!eof((*f)))get((*f));

last= first;
if(eof((*f)))return false;
else{last_nonblank= first;
while(!eoln((*f)))
{if(last>=max_buf_stack)
{max_buf_stack= last+1;
if(max_buf_stack==buf_size)
/*35:*/
#line 1085 "texprof.w"

if(format_ident==0)
{write_ln(term_out,"Buffer size exceeded!");exit(0);

}
else{cur_input.loc_field= first;cur_input.limit_field= last-1;
overflow("buffer size",buf_size);

}

/*:35*/
#line 1011 "texprof.w"
;
}
buffer[last]= xord[(*f).d];get((*f));incr(last);
if(buffer[last-1]!=' ')last_nonblank= last;
}
last= last_nonblank;return true;
}
}

/*:31*//*37:*/
#line 1127 "texprof.w"
static bool init_terminal(void)
{
t_open_in;
if(input_command_line())return true;
loop{wake_up_terminal;pascal_write(term_out,"**");update_terminal;

if(!input_ln(&term_in,true))
{write_ln(term_out);
pascal_write(term_out,"! End of file on the terminal... why?");

return false;
}
loc= first;
while((loc<last)&&(buffer[loc]==' '))incr(loc);
if(loc<last)
{return true;

}
write_ln(term_out,"Please type the name of your input file.");
}
}

/*:37*//*43:*/
#line 1245 "texprof.w"
static str_number make_string(void)
{if(str_ptr==max_strings)
overflow("number of strings",max_strings-init_str_ptr);

incr(str_ptr);str_start[str_ptr]= pool_ptr;
return str_ptr-1;
}

/*:43*//*45:*/
#line 1264 "texprof.w"
static bool str_eq_buf(str_number s,int k)

{
pool_pointer j;
bool result;
j= str_start[s];
while(j<str_start[s+1])
{if(so(str_pool[j])!=buffer[k])
{result= false;goto not_found;
}
incr(j);incr(k);
}
result= true;
not_found:return result;
}

/*:45*//*46:*/
#line 1283 "texprof.w"
static bool str_eq_str(str_number s,str_number t)

{
pool_pointer j,k;
bool result;
result= false;
if(length(s)!=length(t))goto not_found;
j= str_start[s];k= str_start[t];
while(j<str_start[s+1])
{if(str_pool[j]!=str_pool[k])goto not_found;
incr(j);incr(k);
}
result= true;
not_found:return result;
}
/*1564:*/
#line 28379 "texprof.w"

static void str_to_name(str_number s)
{int k;
ASCII_code c;
int j;
k= 0;for(j= str_start[s];j<=str_start[s+1]-1;j++){
c= so(str_pool[j]);incr(k);
if(k<=file_name_size)name_of_file[k]= xchr[c];
}
name_length= k;
name_of_file[name_length+1]= 0;
}

/*:1564*/
#line 1298 "texprof.w"


/*:46*//*47:*/
#line 1306 "texprof.w"

static bool get_strings_started(void)
{
int k,l;
pool_ptr= 0;str_ptr= 0;str_start[0]= 0;
/*48:*/
#line 1319 "texprof.w"

for(k= 0;k<=255;k++)
{if((/*49:*/
#line 1359 "texprof.w"

(k<' ')||(k> '~')

/*:49*/
#line 1321 "texprof.w"
))
{append_char('^');append_char('^');
if(k<0100)append_char(k+0100)
else if(k<0200)append_char(k-0100)
else{app_lc_hex(k/16);app_lc_hex(k%16);
}
}
else append_char(k);
make_string();
}

/*:48*/
#line 1311 "texprof.w"
;
/*50:*/
#line 1366 "texprof.w"

make_string();

/*:50*/
#line 1312 "texprof.w"
;
return true;
}

/*:47*//*51:*/
#line 1374 "texprof.w"
static int s_no(const char*str)
{
if(str[0]==0)return empty_string;
if(str[1]==0)return str[0];
str_room(strlen(str));
while(*str!=0)append_char(*str++);
return make_string();
}

/*:51*//*65:*/
#line 1676 "texprof.w"
static void print_two(int n)
{n= abs(n)%100;print_char('0'+(n/10));
print_char('0'+(n%10));
}

/*:65*//*66:*/
#line 1683 "texprof.w"
static void print_hex(int n)

{int k;
k= 0;print_char('"');
do{dig[k]= n%16;n= n/16;incr(k);
}while(!(n==0));
print_the_digs(k);
}

/*:66*//*68:*/
#line 1703 "texprof.w"
static void print_roman_int(int n)
{
pool_pointer j,k;
nonnegative_integer u,v;
const char mystery[]= "m2d5c2l5x2v5i";
j= 0;v= 1000;
loop{while(n>=v)
{print_char(so(mystery[j]));n= n-v;
}
if(n<=0)return;
k= j+2;u= v/(so(mystery[k-1])-'0');
if(mystery[k-1]==si('2'))
{k= k+2;u= u/(so(mystery[k-1])-'0');
}
if(n+u>=v)
{print_char(so(mystery[k]));n= n+u;
}
else{j= j+2;v= v/(so(mystery[j-1])-'0');
}
}
}

/*:68*//*69:*/
#line 1728 "texprof.w"
static void print_current_string(void)
{pool_pointer j;
j= str_start[str_ptr];
while(j<pool_ptr)
{print_char(so(str_pool[j]));incr(j);
}
}

/*:69*//*70:*/
#line 1746 "texprof.w"
static void term_input(void)
{int k;
update_terminal;
if(!input_ln(&term_in,true))fatal_error("End of file on the terminal!");

term_offset= 0;
decr(selector);
if(last!=first)for(k= first;k<=last-1;k++)printn(buffer[k]);
print_ln();incr(selector);
}

/*:70*//*90:*/
#line 2088 "texprof.w"
static void int_error(int n)
{print(" (");print_int(n);print_char(')');error();
}

/*:90*//*91:*/
#line 2096 "texprof.w"
static void normalize_selector(void)
{if(log_opened)selector= term_and_log;
else selector= term_only;
if(job_name==0)open_log_file();
if(interaction==batch_mode)decr(selector);
}

/*:91*//*97:*/
#line 2180 "texprof.w"
static void pause_for_instructions(void)
{if(OK_to_interrupt)
{interaction= error_stop_mode;
if((selector==log_only)||(selector==no_print))
incr(selector);
print_err("Interruption");

help3("You rang?",
"Try to insert an instruction for me (e.g., `I\\showlists'),",
"unless you just want to quit by typing `X'.");
deletions_allowed= false;error();deletions_allowed= true;
interrupt= 0;
}
}

/*:97*//*99:*/
#line 2219 "texprof.w"
static int half(int x)
{if(odd(x))return(x+1)/2;
else return x/2;
}

/*:99*//*101:*/
#line 2240 "texprof.w"
static scaled round_decimals(small_number k)

{int a;
a= 0;
while(k> 0)
{decr(k);a= (a+dig[k]*two)/10;
}
return(a+1)/2;
}

/*:101*//*102:*/
#line 2262 "texprof.w"
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

/*:102*//*104:*/
#line 2312 "texprof.w"
static scaled mult_and_add(int n,scaled x,scaled y,scaled max_answer)
{if(n<0)
{negate(x);negate(n);
}
if(n==0)return y;
else if(((x<=(max_answer-y)/n)&&(-x<=(max_answer+y)/n)))
return n*x+y;
else{arith_error= true;return 0;
}
}

/*:104*//*105:*/
#line 2325 "texprof.w"
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

/*:105*//*106:*/
#line 2351 "texprof.w"
static scaled xn_over_d(scaled x,int n,int d)
{bool positive;
nonnegative_integer t,u,v;
scaled xn_over_d;
if(x>=0)positive= true;
else{negate(x);positive= false;
}
t= (x%0100000)*n;
u= (x/0100000)*n+(t/0100000);
v= (u%d)*0100000+(t%0100000);
if(u/d>=0100000)arith_error= true;
else u= 0100000*(u/d)+(v/d);
if(positive)
{xn_over_d= u;rem= v%d;
}
else{xn_over_d= -u;rem= -(v%d);
}
return xn_over_d;}

/*:106*//*107:*/
#line 2390 "texprof.w"
/*1633:*/
#line 29123 "texprof.w"

static scaled m_log(scaled x)
{int y,z;
int k;
if(x<=0)/*1635:*/
#line 29150 "texprof.w"

{print_err("Logarithm of ");

print_scaled(x);print(" has been replaced by 0");
help2("Since I don't take logs of non-positive numbers,",
"I'm zeroing this one. Proceed, with fingers crossed.");
error();return 0;
}

/*:1635*/
#line 29127 "texprof.w"

else{y= 1302456956+4-100;
z= 27595+6553600;
while(x<mpfract_four)
{double(x);y= y-93032639;z= z-48782;
}

y= y+(z/unity);k= 2;
while(x> mpfract_four+4)
/*1634:*/
#line 29142 "texprof.w"

{z= ((x-1)/two_to_the[k])+1;
while(x<mpfract_four+z)
{z= halfp(z+1);k= k+1;
}
y= y+spec_log[k];x= x-z;
}

/*:1634*/
#line 29137 "texprof.w"
;
return y/8;
}
}

/*:1633*//*1637:*/
#line 29195 "texprof.w"

static mpfract make_mpfract(int p,int q)
{int f;
int n;
bool negative;
int be_careful;
if(p>=0)negative= false;
else{negate(p);negative= true;
}
if(q<=0)
{
#ifdef DEBUG
if(q==0)confusion("/");
#endif
#line 29209 "texprof.w"


negate(q);negative= !negative;
}
n= p/q;p= p%q;
if(n>=8)
{arith_error= true;
if(negative)return-el_gordo;else return el_gordo;
}
else{n= (n-1)*mpfract_one;
/*1638:*/
#line 29237 "texprof.w"

f= 1;
do{be_careful= p-q;p= be_careful+p;
if(p>=0)f= f+f+1;
else{double(f);p= p+q;
}
}while(!(f>=mpfract_one));
be_careful= p-q;
if(be_careful+p>=0)incr(f)

/*:1638*/
#line 29219 "texprof.w"
;
if(negative)return-(f+n);else return f+n;
}
}

/*:1637*//*1639:*/
#line 29252 "texprof.w"

static int take_mpfract(int q,mpfract f)
{int p;
bool negative;
int n;
int be_careful;
/*1640:*/
#line 29275 "texprof.w"

if(f>=0)negative= false;
else{negate(f);negative= true;
}
if(q<0)
{negate(q);negative= !negative;
}

/*:1640*/
#line 29258 "texprof.w"
;
if(f<mpfract_one)n= 0;
else{n= f/mpfract_one;f= f%mpfract_one;
if(q<=el_gordo/n)n= n*q;
else{arith_error= true;n= el_gordo;
}
}
f= f+mpfract_one;
/*1641:*/
#line 29288 "texprof.w"

p= mpfract_half;
if(q<mpfract_four)
do{if(odd(f))p= halfp(p+q);else p= halfp(p);
f= halfp(f);
}while(!(f==1));
else do{if(odd(f))p= p+halfp(q-p);else p= halfp(p);
f= halfp(f);
}while(!(f==1))

/*:1641*/
#line 29266 "texprof.w"
;
be_careful= n-el_gordo;
if(be_careful+p> 0)
{arith_error= true;n= el_gordo-p;
}
if(negative)return-(n+p);
else return n+p;
}

/*:1639*//*1652:*/
#line 29378 "texprof.w"

static void new_randoms(void)
{int k;
int x;
for(k= 0;k<=23;k++)
{x= randoms[k]-randoms[k+31];
if(x<0)x= x+mpfract_one;
randoms[k]= x;
}
for(k= 24;k<=54;k++)
{x= randoms[k]-randoms[k-24];
if(x<0)x= x+mpfract_one;
randoms[k]= x;
}
j_random= 54;
}

/*:1652*//*1653:*/
#line 29397 "texprof.w"

static void init_randoms(void)
{mpfract j,jj,k;
int i;
j= abs(random_seed);
while(j>=mpfract_one)j= halfp(j);
k= 1;
for(i= 0;i<=54;i++)
{jj= k;k= j-k;j= jj;
if(k<0)k= k+mpfract_one;
randoms[(i*21)%55]= j;
}
new_randoms();new_randoms();new_randoms();
}

/*:1653*//*1654:*/
#line 29419 "texprof.w"

static scaled unif_rand(scaled x)
{scaled y;
next_random;y= take_mpfract(abs(x),randoms[j_random]);
if(y==abs(x))return 0;
else if(x> 0)return y;
else return-y;
}

/*:1654*//*1659:*/
#line 29464 "texprof.w"

static int ab_vs_cd(int a,int b,int c,int d)
{
int q,r;
/*1660:*/
#line 29480 "texprof.w"

if(a<0)
{negate(a);negate(b);
}
if(c<0)
{negate(c);negate(d);
}
if(d<=0)
{if(b>=0)
if(((a==0)||(b==0))&&((c==0)||(d==0)))return_sign(0)
else return_sign(1);
if(d==0)
if(a==0)return_sign(0)else return_sign(-1);
q= a;a= c;c= q;q= -b;b= -d;d= q;
}
else if(b<=0)
{if(b<0)if(a> 0)return_sign(-1);
if(c==0)return_sign(0)else return_sign(-1);
}

/*:1660*/
#line 29468 "texprof.w"
;
loop{q= a/d;r= c/b;
if(q!=r)
if(q> r)return_sign(1)else return_sign(-1);
q= a%d;r= c%b;
if(r==0)
if(q==0)return_sign(0)else return_sign(1);
if(q==0)return_sign(-1);
a= b;b= q;c= d;d= r;
}
}

/*:1659*//*1661:*/
#line 29504 "texprof.w"

static scaled norm_rand(void)
{int x,u,l;

do{
do{next_random;
x= take_mpfract(112429,randoms[j_random]-mpfract_half);

next_random;u= randoms[j_random];
}while(!(abs(x)<u));
x= make_mpfract(x,u);
l= 139548960-m_log(u);
}while(!(ab_vs_cd(1024,l,x,x)>=0));
return x;
}

/*:1661*/
#line 2390 "texprof.w"

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

/*:107*//*113:*/
#line 2567 "texprof.w"

#ifdef DEBUG
static void print_word(memory_word w)

{print_int(w.i);print_char(' ');
print_scaled(w.sc);print_char(' ');
print_scaled(round(unity*unfix(w.gr)));print_ln();

print_int(w.hh.lh);print_char('=');print_int(w.hh.b0);print_char(':');
print_int(w.hh.b1);print_char(';');print_int(w.hh.rh);print_char(' ');
print_int(w.qqqq.b0);print_char(':');print_int(w.qqqq.b1);print_char(':');
print_int(w.qqqq.b2);print_char(':');print_int(w.qqqq.b3);
}
#endif
#line 2581 "texprof.w"

/*:113*//*118:*/
#line 2677 "texprof.w"
/*291:*/
#line 6546 "texprof.w"

static void show_token_list(int p,int q,int l)
{
int m,c;
ASCII_code match_chr;
ASCII_code n;
match_chr= '#';n= '0';tally= 0;
while((p!=null)&&(tally<l))
{if(p==q)/*319:*/
#line 7269 "texprof.w"
set_trick_count

/*:319*/
#line 6554 "texprof.w"
;
/*292:*/
#line 6563 "texprof.w"

if((p<hi_mem_min)||(p> mem_end))
{print_esc("CLOBBERED.");return;

}
if(info(p)>=cs_token_flag)print_cs(info(p)-cs_token_flag);
else{m= info(p)/0400;c= info(p)%0400;
if(info(p)<0)print_esc("BAD.");

else/*293:*/
#line 6579 "texprof.w"

switch(m){
case left_brace:case right_brace:case math_shift:
case tab_mark:case sup_mark:case sub_mark:
case spacer:
case letter:case other_char:printn(c);break;
case mac_param:{printn(c);printn(c);
}break;
case out_param:{printn(match_chr);
if(c<=9)print_char(c+'0');
else{print_char('!');return;
}
}break;
case match:{match_chr= c;printn(c);incr(n);print_char(n);
if(n> '9')return;
}break;
case end_match:if(c==0)print("->");break;

default:print_esc("BAD.");

}

/*:293*/
#line 6572 "texprof.w"
;
}

/*:292*/
#line 6555 "texprof.w"
;
p= link(p);
}
if(p!=null)print_esc("ETC.");


}

/*:291*/
#line 2677 "texprof.w"

/*305:*/
#line 6925 "texprof.w"

static void runaway(void)
{pointer p;
if(scanner_status> skipping)
{print_nl("Runaway ");

switch(scanner_status){
case defining:{print("definition");p= def_ref;
}break;
case matching:{print("argument");p= temp_head;
}break;
case aligning:{print("preamble");p= hold_head;
}break;
case absorbing:{print("text");p= def_ref;
}
}
print_char('?');print_ln();show_token_list(link(p),null,error_line-10);
}
}

/*:305*/
#line 2678 "texprof.w"


/*:118*//*119:*/
#line 2689 "texprof.w"
static pointer get_avail(void)
{pointer p;
p= avail;
if(p!=null)avail= link(avail);
else if(mem_end<mem_max)
{incr(mem_end);p= mem_end;
}
else{decr(hi_mem_min);p= hi_mem_min;
if(hi_mem_min<=lo_mem_max)
{runaway();
overflow("main memory size",mem_max+1-mem_min);


}
}
link(p)= null;
#ifdef STAT
incr(dyn_used);
#endif
#line 2708 "texprof.w"

return p;
}

/*:119*//*122:*/
#line 2738 "texprof.w"
static void flush_list(pointer p)

{pointer q,r;
if(p!=null)
{r= p;
do{q= r;r= link(r);
#ifdef STAT
decr(dyn_used);
#endif
#line 2747 "texprof.w"
}while(!(r==null));
link(q)= avail;avail= p;
}
}

/*:122*//*124:*/
#line 2785 "texprof.w"
static pointer get_node(int s)
{
pointer p;
pointer q;
int r;
int t;
restart:p= rover;
do{/*126:*/
#line 2835 "texprof.w"

q= p+node_size(p);

while(is_empty(q))
{t= rlink(q);
if(q==rover)rover= t;
llink(t)= llink(q);rlink(llink(q))= t;
q= q+node_size(q);
}
r= q-s;
if(r> p+1)/*127:*/
#line 2850 "texprof.w"

{node_size(p)= r-p;

rover= p;
goto found;
}

/*:127*/
#line 2845 "texprof.w"
;
if(r==p)if(rlink(p)!=p)
/*128:*/
#line 2859 "texprof.w"

{rover= rlink(p);t= llink(p);
llink(rover)= t;rlink(t)= rover;
goto found;
}

/*:128*/
#line 2847 "texprof.w"
;
node_size(p)= q-p

/*:126*/
#line 2793 "texprof.w"
;

p= rlink(p);
}while(!(p==rover));
if(s==010000000000)
{return max_halfword;
}
if(lo_mem_max+2<hi_mem_min)if(lo_mem_max+2<=mem_bot+max_halfword)
/*125:*/
#line 2820 "texprof.w"

{if(hi_mem_min-lo_mem_max>=1998)t= lo_mem_max+1000;
else t= lo_mem_max+1+(hi_mem_min-lo_mem_max)/2;

p= llink(rover);q= lo_mem_max;rlink(p)= q;llink(rover)= q;
if(t> mem_bot+max_halfword)t= mem_bot+max_halfword;
rlink(q)= rover;llink(q)= p;link(q)= empty_flag;node_size(q)= t-lo_mem_max;
lo_mem_max= t;link(lo_mem_max)= null;info(lo_mem_max)= null;
rover= q;goto restart;
}

/*:125*/
#line 2801 "texprof.w"
;
overflow("main memory size",mem_max+1-mem_min);


found:link(r)= null;
#ifdef STAT
var_used= var_used+s;
#endif
#line 2809 "texprof.w"

return r;
}

/*:124*//*129:*/
#line 2870 "texprof.w"
static void free_node(pointer p,halfword s)

{pointer q;
node_size(p)= s;link(p)= empty_flag;
q= llink(rover);llink(p)= q;rlink(p)= rover;
llink(rover)= p;rlink(q)= p;
#ifdef STAT
var_used= var_used-s;
#endif
#line 2879 "texprof.w"

}

/*:129*//*130:*/
#line 2887 "texprof.w"

#ifdef INIT
static void sort_avail(void)

{pointer p,q,r;
pointer old_rover;
p= get_node(010000000000);
p= rlink(rover);rlink(rover)= max_halfword;old_rover= rover;
while(p!=old_rover)/*131:*/
#line 2909 "texprof.w"

if(p<rover)
{q= p;p= rlink(q);rlink(q)= rover;rover= q;
}
else{q= rover;
while(rlink(q)<p)q= rlink(q);
r= rlink(p);rlink(p)= rlink(q);rlink(q)= p;p= r;
}

/*:131*/
#line 2896 "texprof.w"
;
p= rover;
while(rlink(p)!=max_halfword)
{llink(rlink(p))= p;p= rlink(p);
}
rlink(p)= rover;llink(rover)= p;
}
#endif
#line 2904 "texprof.w"

/*:130*//*135:*/
#line 3018 "texprof.w"
static pointer new_null_box(void)
{pointer p;
p= get_node(box_node_size);type(p)= hlist_node;
subtype(p)= min_quarterword;
width(p)= 0;depth(p)= 0;height(p)= 0;shift_amount(p)= 0;list_ptr(p)= null;
glue_sign(p)= normal;glue_order(p)= normal;set_glue_ratio_zero(glue_set(p));
return p;
}

/*:135*//*138:*/
#line 3048 "texprof.w"
static pointer new_rule(void)
{pointer p;
p= get_node(rule_node_size);type(p)= rule_node;
subtype(p)= 0;
width(p)= null_flag;depth(p)= null_flag;height(p)= null_flag;
return p;
}

/*:138*//*143:*/
#line 3117 "texprof.w"
static pointer new_ligature(quarterword f,quarterword c,pointer q)
{pointer p;
p= get_node(small_node_size);type(p)= ligature_node;
font(lig_char(p))= f;character(lig_char(p))= c;lig_ptr(p)= q;
subtype(p)= 0;return p;
}

static pointer new_lig_item(quarterword c)
{pointer p;
p= get_node(small_node_size);character(p)= c;lig_ptr(p)= null;
return p;
}

/*:143*//*144:*/
#line 3152 "texprof.w"
static pointer new_disc(void)
{pointer p;
p= get_node(small_node_size);type(p)= disc_node;
replace_count(p)= 0;pre_break(p)= null;post_break(p)= null;
return p;
}

/*:144*//*146:*/
#line 3186 "texprof.w"
static pointer new_math(scaled w,small_number s)
{pointer p;
p= get_node(small_node_size);type(p)= math_node;
subtype(p)= s;width(p)= w;return p;
}

/*:146*//*150:*/
#line 3268 "texprof.w"
static pointer new_spec(pointer p)
{pointer q;
q= get_node(glue_spec_size);
mem[q]= mem[p];glue_ref_count(q)= null;
width(q)= width(p);stretch(q)= stretch(p);shrink(q)= shrink(p);
return q;
}

/*:150*//*151:*/
#line 3281 "texprof.w"
static pointer new_param_glue(small_number n)
{pointer p;
pointer q;
p= get_node(small_node_size);type(p)= glue_node;subtype(p)= n+1;
leader_ptr(p)= null;
q= /*223:*/
#line 4746 "texprof.w"
glue_par(n)

/*:223*/
#line 3286 "texprof.w"
;
glue_ptr(p)= q;incr(glue_ref_count(q));
return p;
}

/*:151*//*152:*/
#line 3294 "texprof.w"
static pointer new_glue(pointer q)
{pointer p;
p= get_node(small_node_size);type(p)= glue_node;subtype(p)= normal;
leader_ptr(p)= null;glue_ptr(p)= q;incr(glue_ref_count(q));
return p;
}

/*:152*//*153:*/
#line 3308 "texprof.w"
static pointer new_skip_param(small_number n)
{pointer p;
temp_ptr= new_spec(/*223:*/
#line 4746 "texprof.w"
glue_par(n)

/*:223*/
#line 3310 "texprof.w"
);
p= new_glue(temp_ptr);glue_ref_count(temp_ptr)= null;subtype(p)= n+1;
return p;
}

/*:153*//*155:*/
#line 3332 "texprof.w"
static pointer new_kern(scaled w)
{pointer p;
p= get_node(small_node_size);type(p)= kern_node;
subtype(p)= normal;
width(p)= w;
return p;
}

/*:155*//*157:*/
#line 3355 "texprof.w"
static pointer new_penalty(int m)
{pointer p;
p= get_node(small_node_size);type(p)= penalty_node;
subtype(p)= 0;
penalty(p)= m;return p;
}

/*:157*//*166:*/
#line 3500 "texprof.w"

#ifdef DEBUG
static void check_mem(bool print_locs)
{
int p,q;
bool clobbered;
for(p= mem_min;p<=lo_mem_max;p++)is_free[p]= false;

for(p= hi_mem_min;p<=mem_end;p++)is_free[p]= false;
/*167:*/
#line 3520 "texprof.w"

p= avail;q= null;clobbered= false;
while(p!=null)
{if((p> mem_end)||(p<hi_mem_min))clobbered= true;
else if(is_free[p])clobbered= true;
if(clobbered)
{print_nl("AVAIL list clobbered at ");

print_int(q);goto done1;
}
is_free[p]= true;q= p;p= link(q);
}
done1:

/*:167*/
#line 3509 "texprof.w"
;
/*168:*/
#line 3534 "texprof.w"

p= rover;q= null;clobbered= false;
do{if((p>=lo_mem_max)||(p<mem_min))clobbered= true;
else if((rlink(p)>=lo_mem_max)||(rlink(p)<mem_min))clobbered= true;
else if(!(is_empty(p))||(node_size(p)<2)||
(p+node_size(p)> lo_mem_max)||(llink(rlink(p))!=p))clobbered= true;
if(clobbered)
{print_nl("Double-AVAIL list clobbered at ");
print_int(q);goto done2;
}
for(q= p;q<=p+node_size(p)-1;q++)
{if(is_free[q])
{print_nl("Doubly free location at ");

print_int(q);goto done2;
}
is_free[q]= true;
}
q= p;p= rlink(p);
}while(!(p==rover));
done2:

/*:168*/
#line 3510 "texprof.w"
;
/*169:*/
#line 3556 "texprof.w"

p= mem_min;
while(p<=lo_mem_max)
{if(is_empty(p))
{print_nl("Bad flag at ");print_int(p);

}
while((p<=lo_mem_max)&&!is_free[p])incr(p);
while((p<=lo_mem_max)&&is_free[p])incr(p);
}

/*:169*/
#line 3511 "texprof.w"
;
if(print_locs)/*170:*/
#line 3567 "texprof.w"

{print_nl("New busy locs:");
for(p= mem_min;p<=lo_mem_max;p++)
if(!is_free[p]&&((p> was_lo_max)||was_free[p]))
{print_char(' ');print_int(p);
}
for(p= hi_mem_min;p<=mem_end;p++)
if(!is_free[p]&&
((p<was_hi_min)||(p> was_mem_end)||was_free[p]))
{print_char(' ');print_int(p);
}
}

/*:170*/
#line 3512 "texprof.w"
;
for(p= mem_min;p<=lo_mem_max;p++)was_free[p]= is_free[p];
for(p= hi_mem_min;p<=mem_end;p++)was_free[p]= is_free[p];

was_mem_end= mem_end;was_lo_max= lo_mem_max;was_hi_min= hi_mem_min;
}
#endif
#line 3519 "texprof.w"

/*:166*//*171:*/
#line 3589 "texprof.w"

#ifdef DEBUG
static void search_mem(pointer p)
{int q;
for(q= mem_min;q<=lo_mem_max;q++)
{if(link(q)==p)
{print_nl("LINK(");print_int(q);print_char(')');
}
if(info(q)==p)
{print_nl("INFO(");print_int(q);print_char(')');
}
}
for(q= hi_mem_min;q<=mem_end;q++)
{if(link(q)==p)
{print_nl("LINK(");print_int(q);print_char(')');
}
if(info(q)==p)
{print_nl("INFO(");print_int(q);print_char(')');
}
}
/*254:*/
#line 5662 "texprof.w"

for(q= active_base;q<=box_base+255;q++)
{if(equiv(q)==p)
{print_nl("EQUIV(");print_int(q);print_char(')');
}
}

/*:254*/
#line 3609 "texprof.w"
;
/*284:*/
#line 6395 "texprof.w"

if(save_ptr> 0)for(q= 0;q<=save_ptr-1;q++)
{if(equiv_field(save_stack[q])==p)
{print_nl("SAVE(");print_int(q);print_char(')');
}
}

/*:284*/
#line 3610 "texprof.w"
;
/*932:*/
#line 18846 "texprof.w"

for(q= 0;q<=hyph_size;q++)
{if(hyph_list[q]==p)
{print_nl("HYPH(");print_int(q);print_char(')');
}
}

/*:932*/
#line 3611 "texprof.w"
;
}
#endif
#line 3614 "texprof.w"

/*:171*//*173:*/
#line 3639 "texprof.w"
static void short_display(int p)
{int n;
while(p> mem_min)
{if(is_char_node(p))
{if(p<=mem_end)
{if(font(p)!=font_in_short_display)
{if((font(p)<font_base)||(font(p)> font_max))
print_char('*');

else/*266:*/
#line 6022 "texprof.w"

printn_esc(font_id_text(font(p)))

/*:266*/
#line 3648 "texprof.w"
;
print_char(' ');font_in_short_display= font(p);
}
print_ASCII(qo(character(p)));
}
}
else/*174:*/
#line 3659 "texprof.w"

switch(type(p)){
case hlist_node:case vlist_node:case ins_node:
case whatsit_node:case mark_node:case adjust_node:
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

/*:174*/
#line 3654 "texprof.w"
;
p= link(p);
}
}

/*:173*//*175:*/
#line 3683 "texprof.w"
static void print_font_and_char(int p)
{if(p> mem_end)print_esc("CLOBBERED.");
else{if((font(p)<font_base)||(font(p)> font_max))print_char('*');

else/*266:*/
#line 6022 "texprof.w"

printn_esc(font_id_text(font(p)))

/*:266*/
#line 3687 "texprof.w"
;
print_char(' ');print_ASCII(qo(character(p)));
}
}

static void print_mark(int p)
{print_char('{');
if((p<hi_mem_min)||(p> mem_end))print_esc("CLOBBERED.");
else show_token_list(link(p),null,max_print_line-10);
print_char('}');
}

static void print_rule_dimen(scaled d)
{if(is_running(d))print_char('*');else print_scaled(d);

}

/*:175*//*176:*/
#line 3707 "texprof.w"
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

/*:176*//*177:*/
#line 3722 "texprof.w"
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

/*:177*//*178:*/
#line 3740 "texprof.w"
/*690:*/
#line 14168 "texprof.w"

static void print_fam_and_char(pointer p)
{print_esc("fam");print_int(fam(p));print_char(' ');
print_ASCII(qo(character(p)));
}

static void print_delimiter(pointer p)
{int a;
a= small_fam(p)*256+qo(small_char(p));
a= a*0x1000+large_fam(p)*256+qo(large_char(p));
if(a<0)print_int(a);
else print_hex(a);
}

/*:690*//*691:*/
#line 14189 "texprof.w"

static void show_info(void);
static void print_subsidiary_data(pointer p,ASCII_code c)

{if(cur_length>=depth_threshold)
{if(math_type(p)!=empty)print(" []");
}
else{append_char(c);
temp_ptr= p;
switch(math_type(p)){
case math_char:{print_ln();print_current_string();print_fam_and_char(p);
}break;
case sub_box:show_info();break;
case sub_mlist:if(info(p)==null)
{print_ln();print_current_string();print("{}");
}
else show_info();break;
default:do_nothing;
}
flush_char;
}
}

/*:691*//*693:*/
#line 14226 "texprof.w"

static void print_style(int c)
{switch(c/2){
case 0:print_esc("displaystyle");break;
case 1:print_esc("textstyle");break;
case 2:print_esc("scriptstyle");break;
case 3:print_esc("scriptscriptstyle");break;
default:print("Unknown style!");
}
}

/*:693*/
#line 3740 "texprof.w"

/*224:*/
#line 4752 "texprof.w"

static void print_skip_param(int n)
{switch(n){
case line_skip_code:print_esc("lineskip");break;
case baseline_skip_code:print_esc("baselineskip");break;
case par_skip_code:print_esc("parskip");break;
case above_display_skip_code:print_esc("abovedisplayskip");break;
case below_display_skip_code:print_esc("belowdisplayskip");break;
case above_display_short_skip_code:print_esc("abovedisplayshortskip");break;
case below_display_short_skip_code:print_esc("belowdisplayshortskip");break;
case left_skip_code:print_esc("leftskip");break;
case right_skip_code:print_esc("rightskip");break;
case top_skip_code:print_esc("topskip");break;
case split_top_skip_code:print_esc("splittopskip");break;
case tab_skip_code:print_esc("tabskip");break;
case space_skip_code:print_esc("spaceskip");break;
case xspace_skip_code:print_esc("xspaceskip");break;
case par_fill_skip_code:print_esc("parfillskip");break;
case thin_mu_skip_code:print_esc("thinmuskip");break;
case med_mu_skip_code:print_esc("medmuskip");break;
case thick_mu_skip_code:print_esc("thickmuskip");break;
default:print("[unknown glue parameter!]");
}
}

/*:224*/
#line 3741 "texprof.w"


/*:178*//*181:*/
#line 3778 "texprof.w"
static void show_node_list(int p)
{
int n;
double g;
if(cur_length> depth_threshold)
{if(p> null)print(" []");

return;
}
n= 0;
while(p> mem_min)
{print_ln();print_current_string();
if(p> mem_end)
{print("Bad link, display aborted.");return;

}
incr(n);if(n> breadth_max)
{print("etc.");return;

}
/*182:*/
#line 3804 "texprof.w"

if(is_char_node(p))print_font_and_char(p);
else switch(type(p)){
case hlist_node:case vlist_node:case unset_node:/*183:*/
#line 3823 "texprof.w"

{if(type(p)==hlist_node)print_esc("h");
else if(type(p)==vlist_node)print_esc("v");
else print_esc("unset");
print("box(");print_scaled(height(p));print_char('+');
print_scaled(depth(p));print(")x");print_scaled(width(p));
if(type(p)==unset_node)
/*184:*/
#line 3839 "texprof.w"

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

/*:184*/
#line 3830 "texprof.w"

else{/*185:*/
#line 3862 "texprof.w"

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

/*:185*/
#line 3831 "texprof.w"
;
if(shift_amount(p)!=0)
{print(", shifted ");print_scaled(shift_amount(p));
}
}
node_list_display(list_ptr(p));
}

/*:183*/
#line 3807 "texprof.w"
break;
case rule_node:/*186:*/
#line 3877 "texprof.w"

{print_esc("rule(");print_rule_dimen(height(p));print_char('+');
print_rule_dimen(depth(p));print(")x");print_rule_dimen(width(p));
}

/*:186*/
#line 3808 "texprof.w"
break;
case ins_node:/*187:*/
#line 3882 "texprof.w"

{print_esc("insert");print_int(qo(subtype(p)));
print(", natural size ");print_scaled(height(p));
print("; split(");print_spec(split_top_ptr(p),0);
print_char(',');print_scaled(depth(p));
print("); float cost ");print_int(float_cost(p));
node_list_display(ins_ptr(p));
}

/*:187*/
#line 3809 "texprof.w"
break;
case whatsit_node:/*1355:*/
#line 25584 "texprof.w"

switch(subtype(p)){
case open_node:{print_write_whatsit("openout",p);
print_char('=');print_file_name(open_name(p),open_area(p),open_ext(p));
}break;
case write_node:{print_write_whatsit("write",p);
print_mark(write_tokens(p));
}break;
case close_node:print_write_whatsit("closeout",p);break;
case latespecial_node:{print_esc("special");print(" shipout");
print_mark(write_tokens(p));
}break;
case special_node:{print_esc("special");
print_mark(write_tokens(p));
}break;
case language_node:{print_esc("setlanguage");
print_int(what_lang(p));print(" (hyphenmin ");
print_int(what_lhm(p));print_char(',');
print_int(what_rhm(p));print_char(')');
}break;
/*1680:*/
#line 29679 "texprof.w"

case save_pos_code:
if(pdf_on)print_esc("pdfsavepos");
else print_esc("savepos");
break;
/*:1680*/
#line 25604 "texprof.w"

default:print("whatsit?");
}

/*:1355*/
#line 3810 "texprof.w"
break;
case glue_node:/*188:*/
#line 3891 "texprof.w"

if(subtype(p)>=a_leaders)/*189:*/
#line 3909 "texprof.w"

{print_esc("");
if(subtype(p)==c_leaders)print_char('c');
else if(subtype(p)==x_leaders)print_char('x');
print("leaders ");print_spec(glue_ptr(p),0);
node_list_display(leader_ptr(p));
}

/*:189*/
#line 3892 "texprof.w"

else{print_esc("glue");
if(subtype(p)!=normal)
{print_char('(');
if(subtype(p)<cond_math_glue)
print_skip_param(subtype(p)-1);
else if(subtype(p)==cond_math_glue)print_esc("nonscript");
else print_esc("mskip");
print_char(')');
}
if(subtype(p)!=cond_math_glue)
{print_char(' ');
if(subtype(p)<cond_math_glue)print_spec(glue_ptr(p),0);
else print_spec(glue_ptr(p),"mu");
}
}

/*:188*/
#line 3811 "texprof.w"
break;
case kern_node:/*190:*/
#line 3919 "texprof.w"

if(subtype(p)!=mu_glue)
{print_esc("kern");
if(subtype(p)!=normal)print_char(' ');
print_scaled(width(p));
if(subtype(p)==acc_kern)print(" (for accent)");

}
else{print_esc("mkern");print_scaled(width(p));print("mu");
}

/*:190*/
#line 3812 "texprof.w"
break;
case math_node:/*191:*/
#line 3930 "texprof.w"

{print_esc("math");
if(subtype(p)==before)print("on");
else print("off");
if(width(p)!=0)
{print(", surrounded ");print_scaled(width(p));
}
}

/*:191*/
#line 3813 "texprof.w"
break;
case ligature_node:/*192:*/
#line 3939 "texprof.w"

{print_font_and_char(lig_char(p));print(" (ligature ");
if(subtype(p)> 1)print_char('|');
font_in_short_display= font(lig_char(p));short_display(lig_ptr(p));
if(odd(subtype(p)))print_char('|');
print_char(')');
}

/*:192*/
#line 3814 "texprof.w"
break;
case penalty_node:/*193:*/
#line 3947 "texprof.w"

{print_esc("penalty ");print_int(penalty(p));
}

/*:193*/
#line 3815 "texprof.w"
break;
case disc_node:/*194:*/
#line 3954 "texprof.w"

{print_esc("discretionary");
if(replace_count(p)> 0)
{print(" replacing ");print_int(replace_count(p));
}
node_list_display(pre_break(p));
append_char('|');show_node_list(post_break(p));flush_char;
}

/*:194*/
#line 3816 "texprof.w"
break;
case mark_node:/*195:*/
#line 3963 "texprof.w"

{print_esc("mark");
if(mark_class(p)!=0)
{print_char('s');print_int(mark_class(p));
}
print_mark(mark_ptr(p));
}

/*:195*/
#line 3817 "texprof.w"
break;
case adjust_node:/*196:*/
#line 3971 "texprof.w"

{print_esc("vadjust");node_list_display(adjust_ptr(p));
}

/*:196*/
#line 3818 "texprof.w"
break;
/*689:*/
#line 14155 "texprof.w"

case style_node:print_style(subtype(p));break;
case choice_node:/*694:*/
#line 14237 "texprof.w"

{print_esc("mathchoice");
append_char('D');show_node_list(display_mlist(p));flush_char;
append_char('T');show_node_list(text_mlist(p));flush_char;
append_char('S');show_node_list(script_mlist(p));flush_char;
append_char('s');show_node_list(script_script_mlist(p));flush_char;
}

/*:694*/
#line 14157 "texprof.w"
break;
case ord_noad:case op_noad:case bin_noad:
case rel_noad:case open_noad:case close_noad:
case punct_noad:case inner_noad:
case radical_noad:case over_noad:case under_noad:
case vcenter_noad:case accent_noad:
case left_noad:case right_noad:/*695:*/
#line 14245 "texprof.w"

{switch(type(p)){
case ord_noad:print_esc("mathord");break;
case op_noad:print_esc("mathop");break;
case bin_noad:print_esc("mathbin");break;
case rel_noad:print_esc("mathrel");break;
case open_noad:print_esc("mathopen");break;
case close_noad:print_esc("mathclose");break;
case punct_noad:print_esc("mathpunct");break;
case inner_noad:print_esc("mathinner");break;
case over_noad:print_esc("overline");break;
case under_noad:print_esc("underline");break;
case vcenter_noad:print_esc("vcenter");break;
case radical_noad:{print_esc("radical");print_delimiter(left_delimiter(p));
}break;
case accent_noad:{print_esc("accent");print_fam_and_char(accent_chr(p));
}break;
case left_noad:{print_esc("left");print_delimiter(delimiter(p));
}break;
case right_noad:{if(subtype(p)==normal)print_esc("right");
else print_esc("middle");
print_delimiter(delimiter(p));
}
}
if(type(p)<left_noad)
{if(subtype(p)!=normal)
if(subtype(p)==limits)print_esc("limits");
else print_esc("nolimits");
print_subsidiary_data(nucleus(p),'.');
}
print_subsidiary_data(supscr(p),'^');
print_subsidiary_data(subscr(p),'_');
}

/*:695*/
#line 14163 "texprof.w"
break;
case fraction_noad:/*696:*/
#line 14279 "texprof.w"

{print_esc("fraction, thickness ");
if(thickness(p)==default_code)print("= default");
else print_scaled(thickness(p));
if((small_fam(left_delimiter(p))!=0)||
(small_char(left_delimiter(p))!=min_quarterword)||
(large_fam(left_delimiter(p))!=0)||
(large_char(left_delimiter(p))!=min_quarterword))
{print(", left-delimiter ");print_delimiter(left_delimiter(p));
}
if((small_fam(right_delimiter(p))!=0)||
(small_char(right_delimiter(p))!=min_quarterword)||
(large_fam(right_delimiter(p))!=0)||
(large_char(right_delimiter(p))!=min_quarterword))
{print(", right-delimiter ");print_delimiter(right_delimiter(p));
}
print_subsidiary_data(numerator(p),'\\');
print_subsidiary_data(denominator(p),'/');
}

/*:696*/
#line 14164 "texprof.w"
break;

/*:689*/
#line 3819 "texprof.w"

default:print("Unknown node type!");
}

/*:182*/
#line 3798 "texprof.w"
;
p= link(p);
}

}

/*:181*//*197:*/
#line 3978 "texprof.w"
static void show_box(pointer p)
{/*235:*/
#line 5211 "texprof.w"

depth_threshold= show_box_depth;
breadth_max= show_box_breadth

/*:235*/
#line 3979 "texprof.w"
;
if(breadth_max<=0)breadth_max= 5;
if(pool_ptr+depth_threshold>=pool_size)
depth_threshold= pool_size-pool_ptr-1;

show_node_list(p);
print_ln();
}

/*:197*//*199:*/
#line 4002 "texprof.w"
static void delete_token_ref(pointer p)

{if(token_ref_count(p)==null)flush_list(p);
else decr(token_ref_count(p));
}

/*:199*//*200:*/
#line 4016 "texprof.w"
static void delete_glue_ref(pointer p)
fast_delete_glue_ref(p)

/*:200*//*201:*/
#line 4024 "texprof.w"
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
case whatsit_node:/*1357:*/
#line 25623 "texprof.w"

{switch(subtype(p)){
case open_node:free_node(p,open_node_size);break;
case write_node:case special_node:case latespecial_node:{delete_token_ref(write_tokens(p));
free_node(p,write_node_size);goto done;
}
case close_node:case language_node:free_node(p,small_node_size);break;
/*1682:*/
#line 29689 "texprof.w"

case save_pos_code:free_node(p,small_node_size);break;

/*:1682*/
#line 25630 "texprof.w"

default:confusion("ext3");

}
goto done;
}

/*:1357*/
#line 4042 "texprof.w"

case glue_node:{fast_delete_glue_ref(glue_ptr(p));
if(leader_ptr(p)!=null)flush_node_list(leader_ptr(p));
}break;
case kern_node:case math_node:case penalty_node:do_nothing;break;
case ligature_node:flush_node_list(lig_ptr(p));break;
case mark_node:delete_token_ref(mark_ptr(p));break;
case disc_node:{flush_node_list(pre_break(p));
flush_node_list(post_break(p));
}break;
case adjust_node:flush_node_list(adjust_ptr(p));break;
/*697:*/
#line 14301 "texprof.w"

case style_node:{free_node(p,style_node_size);goto done;
}
case choice_node:{flush_node_list(display_mlist(p));
flush_node_list(text_mlist(p));
flush_node_list(script_mlist(p));
flush_node_list(script_script_mlist(p));
free_node(p,style_node_size);goto done;
}
case ord_noad:case op_noad:case bin_noad:
case rel_noad:case open_noad:case close_noad:
case punct_noad:case inner_noad:
case radical_noad:case over_noad:case under_noad:
case vcenter_noad:case accent_noad:
{if(math_type(nucleus(p))>=sub_box)
flush_node_list(info(nucleus(p)));
if(math_type(supscr(p))>=sub_box)
flush_node_list(info(supscr(p)));
if(math_type(subscr(p))>=sub_box)
flush_node_list(info(subscr(p)));
if(type(p)==radical_noad)free_node(p,radical_noad_size);
else if(type(p)==accent_noad)free_node(p,accent_noad_size);
else free_node(p,noad_size);
goto done;
}
case left_noad:case right_noad:{free_node(p,noad_size);goto done;
}
case fraction_noad:{flush_node_list(info(numerator(p)));
flush_node_list(info(denominator(p)));
free_node(p,fraction_noad_size);goto done;
}

/*:697*/
#line 4053 "texprof.w"

default:confusion("flushing");

}
free_node(p,small_node_size);
done:;}
p= q;
}
}

/*:201*//*203:*/
#line 4087 "texprof.w"
static pointer copy_node_list(pointer p)

{pointer h;
pointer q;
pointer r;
int words;
h= get_avail();q= h;
while(p!=null)
{/*204:*/
#line 4102 "texprof.w"

words= 1;
if(is_char_node(p))r= get_avail();
else/*205:*/
#line 4111 "texprof.w"

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
case whatsit_node:/*1356:*/
#line 25608 "texprof.w"

switch(subtype(p)){
case open_node:{r= get_node(open_node_size);words= open_node_size;
}break;
case write_node:case special_node:case latespecial_node:{r= get_node(write_node_size);
add_token_ref(write_tokens(p));words= write_node_size;
}break;
case close_node:case language_node:{r= get_node(small_node_size);
words= small_node_size;
}break;
/*1681:*/
#line 29684 "texprof.w"

case save_pos_code:{r= get_node(small_node_size);
words= small_node_size;
}break;

/*:1681*/
#line 25618 "texprof.w"

default:confusion("ext2");

}

/*:1356*/
#line 4126 "texprof.w"
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
case mark_node:{r= get_node(small_node_size);add_token_ref(mark_ptr(p));
words= small_node_size;
}break;
case adjust_node:{r= get_node(small_node_size);
adjust_ptr(r)= copy_node_list(adjust_ptr(p));
}break;
default:confusion("copying");

}

/*:205*/
#line 4106 "texprof.w"
;
while(words> 0)
{decr(words);mem[r+words]= mem[p+words];
}

/*:204*/
#line 4095 "texprof.w"
;
link(q)= r;q= r;p= link(p);
}
link(q)= null;q= link(h);free_avail(h);
return q;
}

/*:203*//*210:*/
#line 4369 "texprof.w"
static void print_mode(int m)
{if(m> 0)
switch(m/(max_command+1)){
case 0:print("vertical");break;
case 1:print("horizontal");break;
case 2:print("display math");
}
else if(m==0)print("no");
else switch((-m)/(max_command+1)){
case 0:print("internal vertical");break;
case 1:print("restricted horizontal");break;
case 2:print("math");
}
print(" mode");
}

/*:210*//*215:*/
#line 4496 "texprof.w"
static void push_nest(void)
{if(nest_ptr> max_nest_stack)
{max_nest_stack= nest_ptr;
if(nest_ptr==nest_size)overflow("semantic nest size",nest_size);

}
nest[nest_ptr]= cur_list;
incr(nest_ptr);head= get_avail();tail= head;prev_graf= 0;mode_line= line;
eTeX_aux= null;
}

/*:215*//*216:*/
#line 4512 "texprof.w"
static void pop_nest(void)
{free_avail(head);decr(nest_ptr);cur_list= nest[nest_ptr];
}

/*:216*//*217:*/
#line 4518 "texprof.w"
static void print_totals(void);
static void show_activities(void)
{int p;
int m;
memory_word a;
pointer q,r;
int t;
nest[nest_ptr]= cur_list;
print_nl("");print_ln();
for(p= nest_ptr;p>=0;p--)
{m= nest[p].mode_field;a= nest[p].aux_field;
print_nl("### ");print_mode(m);
print(" entered at line ");print_int(abs(nest[p].ml_field));
if(m==hmode)if(nest[p].pg_field!=040600000)
{print(" (language");print_int(nest[p].pg_field%0200000);
print(":hyphenmin");print_int(nest[p].pg_field/020000000);
print_char(',');print_int((nest[p].pg_field/0200000)%0100);
print_char(')');
}
if(nest[p].ml_field<0)print(" (\\output routine)");
if(p==0)
{/*985:*/
#line 19919 "texprof.w"

if(page_head!=page_tail)
{print_nl("### current page:");
if(output_active)print(" (held over for next output)");

show_box(link(page_head));
if(page_contents> empty)
{print_nl("total height ");print_totals();

print_nl(" goal height ");print_scaled(page_goal);

r= link(page_ins_head);
while(r!=page_ins_head)
{print_ln();print_esc("insert");t= qo(subtype(r));
print_int(t);print(" adds ");
if(count(t)==1000)t= height(r);
else t= x_over_n(height(r),1000)*count(t);
print_scaled(t);
if(type(r)==split_up)
{q= page_head;t= 0;
do{q= link(q);
if((type(q)==ins_node)&&(subtype(q)==subtype(r)))incr(t);
}while(!(q==broken_ins(r)));
print(", #");print_int(t);print(" might split");
}
r= link(r);
}
}
}

/*:985*/
#line 4539 "texprof.w"
;
if(link(contrib_head)!=null)
print_nl("### recent contributions:");
}
show_box(link(nest[p].head_field));
/*218:*/
#line 4548 "texprof.w"

switch(abs(m)/(max_command+1)){
case 0:{print_nl("prevdepth ");
if(a.sc<=ignore_depth)print("ignored");
else print_scaled(a.sc);
if(nest[p].pg_field!=0)
{print(", prevgraf ");
print_int(nest[p].pg_field);print(" line");
if(nest[p].pg_field!=1)print_char('s');
}
}break;
case 1:{print_nl("spacefactor ");print_int(a.hh.lh);
if(m> 0)if(a.hh.rh> 0)
{print(", current language ");print_int(a.hh.rh);
}
}break;
case 2:if(a.i!=null)
{print("this will begin denominator of:");show_box(a.i);
}
}

/*:218*/
#line 4544 "texprof.w"
;
}
}

/*:217*//*236:*/
#line 5217 "texprof.w"
static void print_param(int n)
{switch(n){
case pretolerance_code:print_esc("pretolerance");break;
case tolerance_code:print_esc("tolerance");break;
case line_penalty_code:print_esc("linepenalty");break;
case hyphen_penalty_code:print_esc("hyphenpenalty");break;
case ex_hyphen_penalty_code:print_esc("exhyphenpenalty");break;
case club_penalty_code:print_esc("clubpenalty");break;
case widow_penalty_code:print_esc("widowpenalty");break;
case display_widow_penalty_code:print_esc("displaywidowpenalty");break;
case broken_penalty_code:print_esc("brokenpenalty");break;
case bin_op_penalty_code:print_esc("binoppenalty");break;
case rel_penalty_code:print_esc("relpenalty");break;
case pre_display_penalty_code:print_esc("predisplaypenalty");break;
case post_display_penalty_code:print_esc("postdisplaypenalty");break;
case inter_line_penalty_code:print_esc("interlinepenalty");break;
case double_hyphen_demerits_code:print_esc("doublehyphendemerits");break;
case final_hyphen_demerits_code:print_esc("finalhyphendemerits");break;
case adj_demerits_code:print_esc("adjdemerits");break;
case mag_code:print_esc("mag");break;
case delimiter_factor_code:print_esc("delimiterfactor");break;
case looseness_code:print_esc("looseness");break;
case time_code:print_esc("time");break;
case day_code:print_esc("day");break;
case month_code:print_esc("month");break;
case year_code:print_esc("year");break;
case show_box_breadth_code:print_esc("showboxbreadth");break;
case show_box_depth_code:print_esc("showboxdepth");break;
case hbadness_code:print_esc("hbadness");break;
case vbadness_code:print_esc("vbadness");break;
case pausing_code:print_esc("pausing");break;
case tracing_online_code:print_esc("tracingonline");break;
case tracing_macros_code:print_esc("tracingmacros");break;
case tracing_stats_code:print_esc("tracingstats");break;
case tracing_paragraphs_code:print_esc("tracingparagraphs");break;
case tracing_pages_code:print_esc("tracingpages");break;
case tracing_output_code:print_esc("tracingoutput");break;
case tracing_lost_chars_code:print_esc("tracinglostchars");break;
case tracing_commands_code:print_esc("tracingcommands");break;
case tracing_restores_code:print_esc("tracingrestores");break;
case uc_hyph_code:print_esc("uchyph");break;
case output_penalty_code:print_esc("outputpenalty");break;
case max_dead_cycles_code:print_esc("maxdeadcycles");break;
case hang_after_code:print_esc("hangafter");break;
case floating_penalty_code:print_esc("floatingpenalty");break;
case global_defs_code:print_esc("globaldefs");break;
case cur_fam_code:print_esc("fam");break;
case escape_char_code:print_esc("escapechar");break;
case default_hyphen_char_code:print_esc("defaulthyphenchar");break;
case default_skew_char_code:print_esc("defaultskewchar");break;
case end_line_char_code:print_esc("endlinechar");break;
case new_line_char_code:print_esc("newlinechar");break;
case language_code:print_esc("language");break;
case left_hyphen_min_code:print_esc("lefthyphenmin");break;
case right_hyphen_min_code:print_esc("righthyphenmin");break;
case holding_inserts_code:print_esc("holdinginserts");break;
case error_context_lines_code:print_esc("errorcontextlines");break;
/*1389:*/
#line 25967 "texprof.w"

case tracing_assigns_code:print_esc("tracingassigns");break;
case tracing_groups_code:print_esc("tracinggroups");break;
case tracing_ifs_code:print_esc("tracingifs");break;
case tracing_scan_tokens_code:print_esc("tracingscantokens");break;
case tracing_nesting_code:print_esc("tracingnesting");break;
case saving_vdiscards_code:print_esc("savingvdiscards");break;
case saving_hyph_codes_code:print_esc("savinghyphcodes");break;

/*:1389*//*1539:*/
#line 28172 "texprof.w"

case expand_depth_code:print_esc("expanddepth");break;

/*:1539*//*1805:*/
#line 32363 "texprof.w"

case pdf_output_code:print_esc("pdfoutput");break;
case pdf_compress_level_code:print_esc("pdfcompresslevel");break;
case pdf_objcompresslevel_code:print_esc("pdfobjcompresslevel");break;
case pdf_decimal_digits_code:print_esc("pdfdecimaldigits");break;
case pdf_move_chars_code:print_esc("pdfmovechars");break;
case pdf_image_resolution_code:print_esc("pdfimageresolution");break;
case pdf_pk_resolution_code:print_esc("pdfpkresolution");break;
case pdf_unique_resname_code:print_esc("pdfuniqueresname");break;
case pdf_option_always_use_pdfpagebox_code:print_esc("pdfoptionalwaysusepdfpagebox");break;
case pdf_option_pdf_inclusion_errorlevel_code:print_esc("pdfoptionpdfinclusionerrorlevel");break;
case pdf_major_version_code:print_esc("pdfmajorversion");break;
case pdf_minor_version_code:print_esc("pdfminorversion");break;
case pdf_force_pagebox_code:print_esc("pdfforcepagebox");break;
case pdf_pagebox_code:print_esc("pdfpagebox");break;
case pdf_inclusion_errorlevel_code:print_esc("pdfinclusionerrorlevel");break;
case pdf_gamma_code:print_esc("pdfgamma");break;
case pdf_image_gamma_code:print_esc("pdfimagegamma");break;
case pdf_image_hicolor_code:print_esc("pdfimagehicolor");break;
case pdf_image_apply_gamma_code:print_esc("pdfimageapplygamma");break;
case pdf_adjust_spacing_code:print_esc("pdfadjustspacing");break;
case pdf_protrude_chars_code:print_esc("pdfprotrudechars");break;
case pdf_tracing_fonts_code:print_esc("pdftracingfonts");break;
case pdf_adjust_interword_glue_code:print_esc("pdfadjustinterwordglue");break;
case pdf_prepend_kern_code:print_esc("pdfprependkern");break;
case pdf_append_kern_code:print_esc("pdfappendkern");break;
case pdf_gen_tounicode_code:print_esc("pdfgentounicode");break;
case pdf_draftmode_code:print_esc("pdfdraftmode");break;
case pdf_inclusion_copy_font_code:print_esc("pdfinclusioncopyfonts");break;
case pdf_suppress_warning_dup_dest_code:print_esc("pdfsuppresswarningdupdest");break;
case pdf_suppress_warning_dup_map_code:print_esc("pdfsuppresswarningdupmap");break;
case pdf_suppress_warning_page_group_code:print_esc("pdfsuppresswarningpagegroup");break;
case pdf_info_omit_date_code:print_esc("pdfinfoomitdate");break;
case pdf_suppress_ptex_info_code:print_esc("pdfsuppressptexinfo");break;
case pdf_omit_charset_code:print_esc("pdfomitcharset");break;
case pdf_omit_info_dict_code:print_esc("pdfomitinfodict");break;
case pdf_omit_procset_code:print_esc("pdfomitprocset");break;

/*:1805*/
#line 5274 "texprof.w"

default:print("[unknown integer parameter!]");
}
}

/*:236*//*240:*/
#line 5425 "texprof.w"
static void fix_date_and_time(void)
{struct tm*t= tl_now();
time= sys_time= t->tm_hour*60+t->tm_min;
day= sys_day= t->tm_mday;
month= sys_month= t->tm_mon+1;
year= sys_year= t->tm_year+1900;
}

/*:240*//*244:*/
#line 5451 "texprof.w"
static void begin_diagnostic(void)
{old_setting= selector;
if((tracing_online<=0)&&(selector==term_and_log))
{decr(selector);
if(history==spotless)history= warning_issued;
}
}

static void end_diagnostic(bool blank_line)

{print_nl("");
if(blank_line)print_ln();
selector= old_setting;
}

/*:244*//*246:*/
#line 5530 "texprof.w"
static void print_length_param(int n)
{switch(n){
case par_indent_code:print_esc("parindent");break;
case math_surround_code:print_esc("mathsurround");break;
case line_skip_limit_code:print_esc("lineskiplimit");break;
case hsize_code:print_esc("hsize");break;
case vsize_code:print_esc("vsize");break;
case max_depth_code:print_esc("maxdepth");break;
case split_max_depth_code:print_esc("splitmaxdepth");break;
case box_max_depth_code:print_esc("boxmaxdepth");break;
case hfuzz_code:print_esc("hfuzz");break;
case vfuzz_code:print_esc("vfuzz");break;
case delimiter_shortfall_code:print_esc("delimitershortfall");break;
case null_delimiter_space_code:print_esc("nulldelimiterspace");break;
case script_space_code:print_esc("scriptspace");break;
case pre_display_size_code:print_esc("predisplaysize");break;
case display_width_code:print_esc("displaywidth");break;
case display_indent_code:print_esc("displayindent");break;
case overfull_rule_code:print_esc("overfullrule");break;
case hang_indent_code:print_esc("hangindent");break;
case h_offset_code:print_esc("hoffset");break;
case v_offset_code:print_esc("voffset");break;
case emergency_stretch_code:print_esc("emergencystretch");break;
case page_width_code:
if(pdf_on)print_esc("pdfpagewidth");
else print_esc("pagewidth");
break;
case page_height_code:
if(pdf_on)print_esc("pdfpageheight");
else print_esc("pageheight");
break;
/*1806:*/
#line 32401 "texprof.w"

case pdf_h_origin_code:print_esc("pdfhorigin");break;
case pdf_v_origin_code:print_esc("pdfvorigin");break;
case pdf_link_margin_code:print_esc("pdflinkmargin");break;
case pdf_dest_margin_code:print_esc("pdfdestmargin");break;
case pdf_thread_margin_code:print_esc("pdfthreadmargin");break;
case pdf_first_line_height_code:print_esc("pdffirstlineheight");break;
case pdf_last_line_depth_code:print_esc("pdflastlinedepth");break;
case pdf_each_line_height_code:print_esc("pdfeachlineheight");break;
case pdf_each_line_depth_code:print_esc("pdfeachlinedepth");break;
case pdf_ignored_dimen_code:print_esc("pdfignoreddimen");break;
case pdf_px_dimen_code:print_esc("pdfpxdimen");break;

/*:1806*/
#line 5561 "texprof.w"

default:print("[unknown dimen parameter!]");
}
}

/*:246*//*251:*/
#line 5631 "texprof.w"
/*297:*/
#line 6689 "texprof.w"

static void print_cmd_chr(quarterword cmd,halfword chr_code)
{int n;
switch(cmd){
case left_brace:chr_cmd("begin-group character ")break;
case right_brace:chr_cmd("end-group character ")break;
case math_shift:chr_cmd("math shift character ")break;
case mac_param:chr_cmd("macro parameter character ")break;
case sup_mark:chr_cmd("superscript character ")break;
case sub_mark:chr_cmd("subscript character ")break;
case endv:print("end of alignment template");break;
case spacer:chr_cmd("blank space ")break;
case letter:chr_cmd("the letter ")break;
case other_char:chr_cmd("the character ")break;
/*226:*/
#line 4821 "texprof.w"

case assign_glue:case assign_mu_glue:if(chr_code<skip_base)
print_skip_param(chr_code-glue_base);
else if(chr_code<mu_skip_base)
{print_esc("skip");print_int(chr_code-skip_base);
}
else{print_esc("muskip");print_int(chr_code-mu_skip_base);
}break;

/*:226*//*230:*/
#line 4936 "texprof.w"

case assign_toks:if(chr_code>=toks_base)
{print_esc("toks");print_int(chr_code-toks_base);
}
else switch(chr_code){
case output_routine_loc:print_esc("output");break;
case every_par_loc:print_esc("everypar");break;
case every_math_loc:print_esc("everymath");break;
case every_display_loc:print_esc("everydisplay");break;
case every_hbox_loc:print_esc("everyhbox");break;
case every_vbox_loc:print_esc("everyvbox");break;
case every_job_loc:print_esc("everyjob");break;
case every_cr_loc:print_esc("everycr");break;
/*1388:*/
#line 25964 "texprof.w"

case every_eof_loc:print_esc("everyeof");break;

/*:1388*//*1804:*/
#line 32357 "texprof.w"

case pdf_pages_attr_loc:print_esc("pdfpagesattr");break;
case pdf_page_attr_loc:print_esc("pdfpageattr");break;
case pdf_page_resources_loc:print_esc("pdfpageresources");break;
case pdf_pk_mode_loc:print_esc("pdfpkmode");break;

/*:1804*/
#line 4949 "texprof.w"

default:print_esc("errhelp");
}break;

/*:230*//*238:*/
#line 5396 "texprof.w"

case assign_int:if(chr_code<count_base)print_param(chr_code-int_base);
else{print_esc("count");print_int(chr_code-count_base);
}break;

/*:238*//*248:*/
#line 5612 "texprof.w"

case assign_dimen:if(chr_code<scaled_base)
print_length_param(chr_code-dimen_base);
else{print_esc("dimen");print_int(chr_code-scaled_base);
}break;

/*:248*//*265:*/
#line 5954 "texprof.w"

case accent:print_esc("accent");break;
case advance:print_esc("advance");break;
case after_assignment:print_esc("afterassignment");break;
case after_group:print_esc("aftergroup");break;
case assign_font_dimen:print_esc("fontdimen");break;
case begin_group:print_esc("begingroup");break;
case break_penalty:print_esc("penalty");break;
case char_num:print_esc("char");break;
case cs_name:print_esc("csname");break;
case def_font:print_esc("font");break;
case delim_num:print_esc("delimiter");break;
case divide:print_esc("divide");break;
case end_cs_name:print_esc("endcsname");break;
case end_group:print_esc("endgroup");break;
case ex_space:print_esc(" ");break;
case expand_after:switch(chr_code){
case 0:print_esc("expandafter");break;
/*1445:*/
#line 26625 "texprof.w"

case 1:print_esc("unless");break;

/*:1445*//*1579:*/
#line 28525 "texprof.w"

case primitive_code:
if(pdf_on)print_esc("pdfprimitive");
else print_esc("primitive");
break;

/*:1579*//*1589:*/
#line 28647 "texprof.w"

case expanded_code:print_esc("expanded");

/*:1589*/
#line 5972 "texprof.w"

}break;
case halign:print_esc("halign");break;
case hrule:print_esc("hrule");break;
case ignore_spaces:print_esc("ignorespaces");break;
case insert:print_esc("insert");break;
case ital_corr:print_esc("/");break;
case mark:{print_esc("mark");
if(chr_code> 0)print_char('s');
}break;
case math_accent:print_esc("mathaccent");break;
case math_char_num:print_esc("mathchar");break;
case math_choice:print_esc("mathchoice");break;
case multiply:print_esc("multiply");break;
case no_align:print_esc("noalign");break;
case no_boundary:print_esc("noboundary");break;
case no_expand:print_esc("noexpand");break;
case non_script:print_esc("nonscript");break;
case omit:print_esc("omit");break;
case radical:print_esc("radical");break;
case read_to_cs:if(chr_code==0)print_esc("read")
/*1442:*/
#line 26592 "texprof.w"
;
else print_esc("readline")

/*:1442*/
#line 5993 "texprof.w"
;break;
case relax:print_esc("relax");break;
case set_box:print_esc("setbox");break;
case set_prev_graf:print_esc("prevgraf");break;
case set_shape:switch(chr_code){
case par_shape_loc:print_esc("parshape");break;
/*1535:*/
#line 28144 "texprof.w"

case inter_line_penalties_loc:print_esc("interlinepenalties");break;
case club_penalties_loc:print_esc("clubpenalties");break;
case widow_penalties_loc:print_esc("widowpenalties");break;
case display_widow_penalties_loc:print_esc("displaywidowpenalties");

/*:1535*/
#line 5999 "texprof.w"

}break;
case the:if(chr_code==0)print_esc("the")
/*1417:*/
#line 26368 "texprof.w"
;
else if(chr_code==1)print_esc("unexpanded");
else print_esc("detokenize")

/*:1417*/
#line 6002 "texprof.w"
;break;
case toks_register:/*1515:*/
#line 27823 "texprof.w"

{print_esc("toks");
if(chr_code!=mem_bot)print_sa_num(chr_code);
}

/*:1515*/
#line 6003 "texprof.w"
break;
case vadjust:print_esc("vadjust");break;
case valign:print_esc("valign");break;
case vcenter:print_esc("vcenter");break;
case vrule:print_esc("vrule");break;

/*:265*//*334:*/
#line 7502 "texprof.w"

case par_end:print_esc("par");break;

/*:334*//*376:*/
#line 8200 "texprof.w"

case input:if(chr_code==0)print_esc("input")
/*1430:*/
#line 26462 "texprof.w"
;
else if(chr_code==2)print_esc("scantokens")

/*:1430*/
#line 8202 "texprof.w"
;
else print_esc("endinput");break;

/*:376*//*384:*/
#line 8297 "texprof.w"

case top_bot_mark:{switch((chr_code%marks_code)){
case first_mark_code:print_esc("firstmark");break;
case bot_mark_code:print_esc("botmark");break;
case split_first_mark_code:print_esc("splitfirstmark");break;
case split_bot_mark_code:print_esc("splitbotmark");break;
default:print_esc("topmark");
}
if(chr_code>=marks_code)print_char('s');
}break;

/*:384*//*411:*/
#line 8749 "texprof.w"

case internal_register:/*1514:*/
#line 27807 "texprof.w"

{if((chr_code<mem_bot)||(chr_code> lo_mem_stat_max))
cmd= sa_type(chr_code);
else{cmd= chr_code-mem_bot;chr_code= null;
}
if(cmd==int_val)print_esc("count");
else if(cmd==dimen_val)print_esc("dimen");
else if(cmd==glue_val)print_esc("skip");
else print_esc("muskip");
if(chr_code!=null)print_sa_num(chr_code);
}

/*:1514*/
#line 8750 "texprof.w"
break;

/*:411*//*416:*/
#line 8878 "texprof.w"

case set_aux:if(chr_code==vmode)print_esc("prevdepth");
else print_esc("spacefactor");break;
case set_page_int:if(chr_code==0)print_esc("deadcycles")
/*1423:*/
#line 26423 "texprof.w"
;
else if(chr_code==2)print_esc("interactionmode")

/*:1423*/
#line 8882 "texprof.w"
;
else print_esc("insertpenalties");break;
case set_box_dimen:if(chr_code==width_offset)print_esc("wd");
else if(chr_code==height_offset)print_esc("ht");
else print_esc("dp");break;
case last_item:switch(chr_code){
case int_val:print_esc("lastpenalty");break;
case dimen_val:print_esc("lastkern");break;
case glue_val:print_esc("lastskip");break;
case input_line_no_code:print_esc("inputlineno");break;
/*1380:*/
#line 25899 "texprof.w"

case last_node_type_code:print_esc("lastnodetype");break;
case eTeX_version_code:print_esc("eTeXversion");break;

/*:1380*//*1394:*/
#line 26051 "texprof.w"

case current_group_level_code:print_esc("currentgrouplevel");break;
case current_group_type_code:print_esc("currentgrouptype");break;

/*:1394*//*1397:*/
#line 26075 "texprof.w"

case current_if_level_code:print_esc("currentiflevel");break;
case current_if_type_code:print_esc("currentiftype");break;
case current_if_branch_code:print_esc("currentifbranch");break;

/*:1397*//*1400:*/
#line 26113 "texprof.w"

case font_char_wd_code:print_esc("fontcharwd");break;
case font_char_ht_code:print_esc("fontcharht");break;
case font_char_dp_code:print_esc("fontchardp");break;
case font_char_ic_code:print_esc("fontcharic");break;

/*:1400*//*1403:*/
#line 26152 "texprof.w"

case par_shape_length_code:print_esc("parshapelength");break;
case par_shape_indent_code:print_esc("parshapeindent");break;
case par_shape_dimen_code:print_esc("parshapedimen");break;

/*:1403*//*1461:*/
#line 26853 "texprof.w"

case eTeX_expr-int_val+int_val:print_esc("numexpr");break;
case eTeX_expr-int_val+dimen_val:print_esc("dimexpr");break;
case eTeX_expr-int_val+glue_val:print_esc("glueexpr");break;
case eTeX_expr-int_val+mu_val:print_esc("muexpr");break;

/*:1461*//*1484:*/
#line 27273 "texprof.w"

case glue_stretch_order_code:print_esc("gluestretchorder");break;
case glue_shrink_order_code:print_esc("glueshrinkorder");break;
case glue_stretch_code:print_esc("gluestretch");break;
case glue_shrink_code:print_esc("glueshrink");break;

/*:1484*//*1488:*/
#line 27308 "texprof.w"

case mu_to_glue_code:print_esc("mutoglue");break;
case glue_to_mu_code:print_esc("gluetomu");break;

/*:1488*//*1554:*/
#line 28306 "texprof.w"

case Prote_version_code:print_esc("Proteversion");break;

/*:1554*//*1569:*/
#line 28439 "texprof.w"

case shell_escape_code:
if(pdf_on)print_esc("pdfshellescape");
else print_esc("shellescape");
break;

/*:1569*//*1604:*/
#line 28798 "texprof.w"

case elapsed_time_code:
if(pdf_on)print_esc("pdfelapsedtime");
else print_esc("elapsedtime");
break;

/*:1604*//*1645:*/
#line 29323 "texprof.w"

case random_seed_code:
if(pdf_on)print_esc("pdfrandomseed");
else print_esc("randomseed");
break;

/*:1645*//*1672:*/
#line 29622 "texprof.w"

case last_xpos_code:
if(pdf_on)print_esc("pdflastxpos");
else print_esc("lastxpos");
break;
case last_ypos_code:
if(pdf_on)print_esc("pdflastypos");
else print_esc("lastypos");
break;

/*:1672*//*1800:*/
#line 32137 "texprof.w"

case pdftex_version_code:print_esc("pdftexversion");break;
case pdf_last_obj_code:print_esc("pdflastobj");break;
case pdf_last_xform_code:print_esc("pdflastxform");break;
case pdf_last_ximage_code:print_esc("pdflastximage");break;
case pdf_last_ximage_pages_code:print_esc("pdflastximagepages");break;
case pdf_last_annot_code:print_esc("pdflastannot");break;
case pdf_retval_code:print_esc("pdfretval");break;
case pdf_last_ximage_colordepth_code:print_esc("pdflastximagecolordepth");break;
case pdf_last_link_code:print_esc("pdflastlink");break;

/*:1800*/
#line 8892 "texprof.w"

default:print_esc("badness");
}break;

/*:416*//*468:*/
#line 9726 "texprof.w"

case convert:switch(chr_code){
case number_code:print_esc("number");break;
case roman_numeral_code:print_esc("romannumeral");break;
case string_code:print_esc("string");break;
case meaning_code:print_esc("meaning");break;
case font_name_code:print_esc("fontname");break;
case job_name_code:print_esc("jobname");break;
case eTeX_revision_code:print_esc("eTeXrevision");break;
/*1556:*/
#line 28312 "texprof.w"

case Prote_revision_code:print_esc("Proterevision");break;

/*:1556*//*1592:*/
#line 28678 "texprof.w"

case strcmp_code:
if(pdf_on)print_esc("pdfstrcmp");
else print_esc("strcmp");
break;

/*:1592*//*1599:*/
#line 28750 "texprof.w"

case creation_date_code:
if(pdf_on)print_esc("pdfcreationdate");
else print_esc("creationdate");
break;

/*:1599*//*1611:*/
#line 28860 "texprof.w"

case file_size_code:
if(pdf_on)print_esc("pdffilesize");
else print_esc("filesize");
break;

/*:1611*//*1616:*/
#line 28898 "texprof.w"

case file_mod_date_code:
if(pdf_on)print_esc("pdffilemoddate");
else print_esc("filemoddate");
break;

/*:1616*//*1621:*/
#line 28949 "texprof.w"

case file_dump_code:
if(pdf_on)print_esc("pdffiledump");
else print_esc("filedump");
break;

/*:1621*//*1626:*/
#line 29023 "texprof.w"

case mdfive_sum_code:
if(pdf_on)print_esc("pdfmdfivesum");
else print_esc("mdfivesum");
break;

/*:1626*//*1649:*/
#line 29355 "texprof.w"

case set_random_seed_code:
if(pdf_on)print_esc("pdfsetrandomseed");
else print_esc("setrandomseed");
break;

/*:1649*//*1656:*/
#line 29439 "texprof.w"

case uniform_deviate_code:
if(pdf_on)print_esc("pdfuniformdeviate");
else print_esc("uniformdeviate");
break;

/*:1656*//*1663:*/
#line 29531 "texprof.w"

case normal_deviate_code:
if(pdf_on)print_esc("pdfnormaldeviate");
else print_esc("normaldeviate");
break;


/*:1663*/
#line 9735 "texprof.w"

}break;

/*:468*//*487:*/
#line 10084 "texprof.w"

case if_test:{if(chr_code>=unless_code)print_esc("unless");
switch(chr_code%unless_code){
case if_cat_code:print_esc("ifcat");break;
case if_int_code:print_esc("ifnum");break;
case if_dim_code:print_esc("ifdim");break;
case if_odd_code:print_esc("ifodd");break;
case if_vmode_code:print_esc("ifvmode");break;
case if_hmode_code:print_esc("ifhmode");break;
case if_mmode_code:print_esc("ifmmode");break;
case if_inner_code:print_esc("ifinner");break;
case if_void_code:print_esc("ifvoid");break;
case if_hbox_code:print_esc("ifhbox");break;
case if_vbox_code:print_esc("ifvbox");break;
case ifx_code:print_esc("ifx");break;
case if_eof_code:print_esc("ifeof");break;
case if_true_code:print_esc("iftrue");break;
case if_false_code:print_esc("iffalse");break;
case if_case_code:print_esc("ifcase");break;
/*1446:*/
#line 26628 "texprof.w"

case if_def_code:print_esc("ifdefined");break;
case if_cs_code:print_esc("ifcsname");break;
case if_font_char_code:print_esc("iffontchar");break;

/*:1446*//*1572:*/
#line 28463 "texprof.w"

case if_incsname_code:print_esc("ifincsname");break;
case if_primitive_code:
if(pdf_on)print_esc("ifpdfprimitive");
else print_esc("ifprimitive");
break;

/*:1572*/
#line 10103 "texprof.w"

default:print_esc("if");
}
}break;

/*:487*//*491:*/
#line 10149 "texprof.w"

case fi_or_else:if(chr_code==fi_code)print_esc("fi");
else if(chr_code==or_code)print_esc("or");
else print_esc("else");break;

/*:491*//*780:*/
#line 15970 "texprof.w"

case tab_mark:if(chr_code==span_code)print_esc("span");
else chr_cmd("alignment tab character ")break;
case car_ret:if(chr_code==cr_code)print_esc("cr");
else print_esc("crcr");break;

/*:780*//*983:*/
#line 19893 "texprof.w"

case set_page_dimen:switch(chr_code){
case 0:print_esc("pagegoal");break;
case 1:print_esc("pagetotal");break;
case 2:print_esc("pagestretch");break;
case 3:print_esc("pagefilstretch");break;
case 4:print_esc("pagefillstretch");break;
case 5:print_esc("pagefilllstretch");break;
case 6:print_esc("pageshrink");break;
default:print_esc("pagedepth");
}break;

/*:983*//*1052:*/
#line 21139 "texprof.w"

case stop:if(chr_code==1)print_esc("dump");else print_esc("end");break;

/*:1052*//*1058:*/
#line 21238 "texprof.w"

case hskip:switch(chr_code){
case skip_code:print_esc("hskip");break;
case fil_code:print_esc("hfil");break;
case fill_code:print_esc("hfill");break;
case ss_code:print_esc("hss");break;
default:print_esc("hfilneg");
}break;
case vskip:switch(chr_code){
case skip_code:print_esc("vskip");break;
case fil_code:print_esc("vfil");break;
case fill_code:print_esc("vfill");break;
case ss_code:print_esc("vss");break;
default:print_esc("vfilneg");
}break;
case mskip:print_esc("mskip");break;
case kern:print_esc("kern");break;
case mkern:print_esc("mkern");break;

/*:1058*//*1071:*/
#line 21506 "texprof.w"

case hmove:if(chr_code==1)print_esc("moveleft");else print_esc("moveright");break;
case vmove:if(chr_code==1)print_esc("raise");else print_esc("lower");break;
case make_box:switch(chr_code){
case box_code:print_esc("box");break;
case copy_code:print_esc("copy");break;
case last_box_code:print_esc("lastbox");break;
case vsplit_code:print_esc("vsplit");break;
case vtop_code:print_esc("vtop");break;
case vtop_code+vmode:print_esc("vbox");break;
default:print_esc("hbox");
}break;
case leader_ship:if(chr_code==a_leaders)print_esc("leaders");
else if(chr_code==c_leaders)print_esc("cleaders");
else if(chr_code==x_leaders)print_esc("xleaders");
else print_esc("shipout");break;

/*:1071*//*1088:*/
#line 21774 "texprof.w"

case start_par:if(chr_code==0)print_esc("noindent");else print_esc("indent");break;

/*:1088*//*1107:*/
#line 22003 "texprof.w"

case remove_item:if(chr_code==glue_node)print_esc("unskip");
else if(chr_code==kern_node)print_esc("unkern");
else print_esc("unpenalty");break;
case un_hbox:if(chr_code==copy_code)print_esc("unhcopy");
else print_esc("unhbox");break;
case un_vbox:if(chr_code==copy_code)print_esc("unvcopy")
/*1532:*/
#line 28120 "texprof.w"
;
else if(chr_code==last_box_code)print_esc("pagediscards");
else if(chr_code==vsplit_code)print_esc("splitdiscards")

/*:1532*/
#line 22010 "texprof.w"
;
else print_esc("unvbox");break;

/*:1107*//*1114:*/
#line 22078 "texprof.w"

case discretionary:if(chr_code==1)
print_esc("-");else print_esc("discretionary");break;

/*:1114*//*1142:*/
#line 22437 "texprof.w"

case eq_no:if(chr_code==1)print_esc("leqno");else print_esc("eqno");break;

/*:1142*//*1156:*/
#line 22686 "texprof.w"

case math_comp:switch(chr_code){
case ord_noad:print_esc("mathord");break;
case op_noad:print_esc("mathop");break;
case bin_noad:print_esc("mathbin");break;
case rel_noad:print_esc("mathrel");break;
case open_noad:print_esc("mathopen");break;
case close_noad:print_esc("mathclose");break;
case punct_noad:print_esc("mathpunct");break;
case inner_noad:print_esc("mathinner");break;
case under_noad:print_esc("underline");break;
default:print_esc("overline");
}break;
case limit_switch:if(chr_code==limits)print_esc("limits");
else if(chr_code==no_limits)print_esc("nolimits");
else print_esc("displaylimits");break;

/*:1156*//*1169:*/
#line 22822 "texprof.w"

case math_style:print_style(chr_code);break;

/*:1169*//*1178:*/
#line 22925 "texprof.w"

case above:switch(chr_code){
case over_code:print_esc("over");break;
case atop_code:print_esc("atop");break;
case delimited_code+above_code:print_esc("abovewithdelims");break;
case delimited_code+over_code:print_esc("overwithdelims");break;
case delimited_code+atop_code:print_esc("atopwithdelims");break;
default:print_esc("above");
}break;

/*:1178*//*1188:*/
#line 23046 "texprof.w"

case left_right:if(chr_code==left_noad)print_esc("left")
/*1428:*/
#line 26452 "texprof.w"
;
else if(chr_code==middle_noad)print_esc("middle")

/*:1428*/
#line 23048 "texprof.w"
;
else print_esc("right");break;

/*:1188*//*1208:*/
#line 23376 "texprof.w"

case prefix:if(chr_code==1)print_esc("long");
else if(chr_code==2)print_esc("outer")
/*1453:*/
#line 26712 "texprof.w"
;
else if(chr_code==8)print_esc("protected")

/*:1453*/
#line 23379 "texprof.w"
;
else print_esc("global");break;
case def:if(chr_code==0)print_esc("def");
else if(chr_code==1)print_esc("gdef");
else if(chr_code==2)print_esc("edef");
else print_esc("xdef");break;

/*:1208*//*1219:*/
#line 23558 "texprof.w"

case let:if(chr_code!=normal)print_esc("futurelet");else print_esc("let");break;

/*:1219*//*1222:*/
#line 23613 "texprof.w"

case shorthand_def:switch(chr_code){
case char_def_code:print_esc("chardef");break;
case math_char_def_code:print_esc("mathchardef");break;
case count_def_code:print_esc("countdef");break;
case dimen_def_code:print_esc("dimendef");break;
case skip_def_code:print_esc("skipdef");break;
case mu_skip_def_code:print_esc("muskipdef");break;
default:print_esc("toksdef");
}break;
case char_given:{print_esc("char");print_hex(chr_code);
}break;
case math_given:{print_esc("mathchar");print_hex(chr_code);
}break;

/*:1222*//*1230:*/
#line 23782 "texprof.w"

case def_code:if(chr_code==cat_code_base)print_esc("catcode");
else if(chr_code==math_code_base)print_esc("mathcode");
else if(chr_code==lc_code_base)print_esc("lccode");
else if(chr_code==uc_code_base)print_esc("uccode");
else if(chr_code==sf_code_base)print_esc("sfcode");
else print_esc("delcode");break;
case def_family:print_size(chr_code-math_font_base);break;

/*:1230*//*1250:*/
#line 24076 "texprof.w"

case hyph_data:if(chr_code==1)print_esc("patterns");
else print_esc("hyphenation");break;

/*:1250*//*1254:*/
#line 24113 "texprof.w"

case assign_font_int:if(chr_code==0)print_esc("hyphenchar");
else print_esc("skewchar");break;

/*:1254*//*1260:*/
#line 24198 "texprof.w"

case set_font:{print("select font ");slow_print(font_name[chr_code]);
if(font_size[chr_code]!=font_dsize[chr_code])
{print(" at ");print_scaled(font_size[chr_code]);
print("pt");
}
}break;

/*:1260*//*1262:*/
#line 24216 "texprof.w"

case set_interaction:switch(chr_code){
case batch_mode:print_esc("batchmode");break;
case nonstop_mode:print_esc("nonstopmode");break;
case scroll_mode:print_esc("scrollmode");break;
default:print_esc("errorstopmode");
}break;

/*:1262*//*1272:*/
#line 24278 "texprof.w"

case in_stream:if(chr_code==0)print_esc("closein");
else print_esc("openin");break;

/*:1272*//*1277:*/
#line 24315 "texprof.w"

case message:if(chr_code==0)print_esc("message");
else print_esc("errmessage");break;

/*:1277*//*1286:*/
#line 24382 "texprof.w"

case case_shift:if(chr_code==lc_code_base)print_esc("lowercase");
else print_esc("uppercase");break;

/*:1286*//*1291:*/
#line 24433 "texprof.w"

case xray:switch(chr_code){
case show_box_code:print_esc("showbox");break;
case show_the_code:print_esc("showthe");break;
case show_lists_code:print_esc("showlists");break;
/*1406:*/
#line 26180 "texprof.w"

case show_groups:print_esc("showgroups");break;

/*:1406*//*1415:*/
#line 26351 "texprof.w"

case show_tokens:print_esc("showtokens");break;

/*:1415*//*1420:*/
#line 26392 "texprof.w"

case show_ifs:print_esc("showifs");break;

/*:1420*/
#line 24438 "texprof.w"

default:print_esc("show");
}break;

/*:1291*//*1294:*/
#line 24489 "texprof.w"

case undefined_cs:print("undefined");break;
case call:case long_call:case outer_call:
case long_outer_call:{n= cmd-call;
if(info(link(chr_code))==protected_token)n= n+4;
if(odd(n/4))print_esc("protected");
if(odd(n))print_esc("long");
if(odd(n/2))print_esc("outer");
if(n> 0)print_char(' ');
print("macro");
}break;
case end_template:print_esc("outer endtemplate");break;

/*:1294*//*1345:*/
#line 25475 "texprof.w"

case extension:switch(chr_code){
case open_node:print_esc("openout");break;
case write_node:print_esc("write");break;
case close_node:print_esc("closeout");break;
case special_node:print_esc("special");break;
case immediate_code:print_esc("immediate");break;
case set_language_code:print_esc("setlanguage");break;
/*1605:*/
#line 28804 "texprof.w"

case reset_timer_code:
if(pdf_on)print_esc("pdfresettimer");
else print_esc("resettimer");
break;

/*:1605*//*1677:*/
#line 29662 "texprof.w"

case save_pos_code:
if(pdf_on)print_esc("pdfsavepos");
else print_esc("savepos");
break;
/*:1677*//*1743:*/
#line 31015 "texprof.w"

case profile_on_code:print_esc("profileon");break;
case profile_off_code:print_esc("profileoff");break;

/*:1743*//*1815:*/
#line 32801 "texprof.w"

case pdf_annot_node:print_esc("pdfannot");break;
case pdf_catalog_code:print_esc("pdfcatalog");break;
case pdf_dest_node:print_esc("pdfdest");break;
case pdf_end_link_node:print_esc("pdfendlink");break;
case pdf_end_thread_node:print_esc("pdfendthread");break;
case pdf_font_attr_code:print_esc("pdffontattr");break;
case pdf_font_expand_code:print_esc("pdffontexpand");break;
case pdf_include_chars_code:print_esc("pdfincludechars");break;
case pdf_info_code:print_esc("pdfinfo");break;
case pdf_literal_node:print_esc("pdfliteral");break;
case pdf_colorstack_node:print_esc("pdfcolorstack");break;
case pdf_setmatrix_node:print_esc("pdfsetmatrix");break;
case pdf_save_node:print_esc("pdfsave");break;
case pdf_restore_node:print_esc("pdfrestore");break;
case pdf_map_file_code:print_esc("pdfmapfile");break;
case pdf_map_line_code:print_esc("pdfmapline");break;
case pdf_names_code:print_esc("pdfnames");break;
case pdf_obj_code:print_esc("pdfobj");break;
case pdf_outline_code:print_esc("pdfoutline");break;
case pdf_refobj_node:print_esc("pdfrefobj");break;
case pdf_refxform_node:print_esc("pdfrefxform");break;
case pdf_refximage_node:print_esc("pdfrefximage");break;
case pdf_snap_ref_point_node:print_esc("pdfsnaprefpoint");break;
case pdf_snapy_comp_node:print_esc("pdfsnapycomp");break;
case pdf_snapy_node:print_esc("pdfsnapy");break;
case pdf_start_link_node:print_esc("pdfstartlink");break;
case pdf_start_thread_node:print_esc("pdfstartthread");break;
case pdf_thread_node:print_esc("pdfthread");break;
case pdf_trailer_code:print_esc("pdftrailer");break;
case pdf_trailer_id_code:print_esc("pdftrailerid");break;
case pdf_xform_code:print_esc("pdfxform");break;
case pdf_ximage_code:print_esc("pdfximage");break;
case pdf_nobuiltin_tounicode_code:print_esc("pdfnobuiltintounicode");break;
case pdf_glyph_to_unicode_code:print_esc("pdfglyphtounicode");break;
case pdf_interword_space_on_node:print_esc("pdfinterwordspaceon");break;
case pdf_interword_space_off_node:print_esc("pdfinterwordspaceoff");break;
case pdf_fake_space_node:print_esc("pdffakespace");break;
case pdf_running_link_off_node:print_esc("pdfrunninglinkoff");break;
case pdf_running_link_on_node:print_esc("pdfrunninglinkon");break;
case pdf_space_font_code:print_esc("pdfspacefont");break;
case tracing_stack_level_code:print_esc("tracingstacklevels");break;
case pdf_par_token_context_code:print_esc("partokencontext");break;
case pdf_par_token_name_code:print_esc("partokenname");break;
case pdf_show_stream_code:print_esc("showstream");break;


/*:1815*/
#line 25483 "texprof.w"

default:print("[unknown extension!]");
}break;



/*:1345*/
#line 6703 "texprof.w"

default:print("[unknown command code!]");
}
}

/*:297*/
#line 5631 "texprof.w"

#ifdef STAT
static void show_eqtb(pointer n)
{if(n<active_base)print_char('?');
else if(n<glue_base)/*222:*/
#line 4688 "texprof.w"

{sprint_cs(n);print_char('=');print_cmd_chr(eq_type(n),equiv(n));
if(eq_type(n)>=call)
{print_char(':');show_token_list(link(equiv(n)),null,32);
}
}

/*:222*/
#line 5635 "texprof.w"

else if(n<local_base)/*228:*/
#line 4838 "texprof.w"

if(n<skip_base)
{print_skip_param(n-glue_base);print_char('=');
if(n<glue_base+thin_mu_skip_code)print_spec(equiv(n),"pt");
else print_spec(equiv(n),"mu");
}
else if(n<mu_skip_base)
{print_esc("skip");print_int(n-skip_base);print_char('=');
print_spec(equiv(n),"pt");
}
else{print_esc("muskip");print_int(n-mu_skip_base);print_char('=');
print_spec(equiv(n),"mu");
}

/*:228*/
#line 5636 "texprof.w"

else if(n<int_base)/*232:*/
#line 4997 "texprof.w"

if((n==par_shape_loc)||((n>=etex_pen_base)&&(n<etex_pens)))
{print_cmd_chr(set_shape,n);print_char('=');
if(equiv(n)==null)print_char('0');
else if(n> par_shape_loc)
{print_int(penalty(equiv(n)));print_char(' ');
print_int(penalty(equiv(n)+1));
if(penalty(equiv(n))> 1)print_esc("ETC.");
}
else print_int(info(par_shape_ptr));
}
else if(n<toks_base)
{print_cmd_chr(assign_toks,n);print_char('=');
if(equiv(n)!=null)show_token_list(link(equiv(n)),null,32);
}
else if(n<box_base)
{print_esc("toks");print_int(n-toks_base);print_char('=');
if(equiv(n)!=null)show_token_list(link(equiv(n)),null,32);
}
else if(n<cur_font_loc)
{print_esc("box");print_int(n-box_base);print_char('=');
if(equiv(n)==null)print("void");
else{depth_threshold= 0;breadth_max= 1;show_node_list(equiv(n));
}
}
else if(n<cat_code_base)/*233:*/
#line 5025 "texprof.w"

{if(n==cur_font_loc)print("current font");
else if(n<math_font_base+16)
{print_esc("textfont");print_int(n-math_font_base);
}
else if(n<math_font_base+32)
{print_esc("scriptfont");print_int(n-math_font_base-16);
}
else{print_esc("scriptscriptfont");print_int(n-math_font_base-32);
}
print_char('=');
printn_esc(hash[font_id_base+equiv(n)].rh);

}

/*:233*/
#line 5022 "texprof.w"

else/*234:*/
#line 5040 "texprof.w"

if(n<math_code_base)
{if(n<lc_code_base)
{print_esc("catcode");print_int(n-cat_code_base);
}
else if(n<uc_code_base)
{print_esc("lccode");print_int(n-lc_code_base);
}
else if(n<sf_code_base)
{print_esc("uccode");print_int(n-uc_code_base);
}
else{print_esc("sfcode");print_int(n-sf_code_base);
}
print_char('=');print_int(equiv(n));
}
else{print_esc("mathcode");print_int(n-math_code_base);
print_char('=');print_int(ho(equiv(n)));
}

/*:234*/
#line 5023 "texprof.w"


/*:232*/
#line 5637 "texprof.w"

else if(n<dimen_base)/*241:*/
#line 5433 "texprof.w"

{if(n<count_base)print_param(n-int_base);
else if(n<del_code_base)
{print_esc("count");print_int(n-count_base);
}
else{print_esc("delcode");print_int(n-del_code_base);
}
print_char('=');print_int(eqtb[n].i);
}

/*:241*/
#line 5638 "texprof.w"

else if(n<=eqtb_size)/*250:*/
#line 5621 "texprof.w"

{if(n<scaled_base)print_length_param(n-dimen_base);
else{print_esc("dimen");print_int(n-scaled_base);
}
print_char('=');print_scaled(eqtb[n].sc);print("pt");
}

/*:250*/
#line 5639 "texprof.w"

else print_char('?');
}
#endif
#line 5643 "texprof.w"

/*:251*//*258:*/
#line 5727 "texprof.w"
static pointer id_lookup(int j,int l)
{
int h;
int d;
pointer p;
int k;
/*260:*/
#line 5775 "texprof.w"

h= buffer[j];
for(k= j+1;k<=j+l-1;k++)
{h= h+h+buffer[k];
while(h>=hash_prime)h= h-hash_prime;
}

/*:260*/
#line 5733 "texprof.w"
;
p= h+hash_base;
loop{if(text(p)> 0)if(length(text(p))==l)
if(str_eq_buf(text(p),j))goto found;
if(next(p)==0)
{if(no_new_control_sequence)
p= undefined_control_sequence;
else/*259:*/
#line 5749 "texprof.w"

{if(text(p)> 0)
{do{if(hash_is_full)overflow("hash size",hash_size);

decr(hash_used);
}while(!(text(hash_used)==0));
next(p)= hash_used;p= hash_used;
}
str_room(l);d= cur_length;
while(pool_ptr> str_start[str_ptr])
{decr(pool_ptr);str_pool[pool_ptr+l]= str_pool[pool_ptr];
}
for(k= j;k<=j+l-1;k++)append_char(buffer[k]);
text(p)= make_string();pool_ptr= pool_ptr+d;
#ifdef STAT
incr(cs_count);
#endif
#line 5766 "texprof.w"

}

/*:259*/
#line 5741 "texprof.w"
;
goto found;
}
p= next(p);
}
found:return p;
}

/*:258*//*263:*/
#line 5831 "texprof.w"

#ifdef INIT
static void primitive(char*str,quarterword c,halfword o)
{str_number s= s_no(str);
int k;
int j;
small_number l;
pointer p;
if(s<256)cur_val= s+single_base;
else{k= str_start[s];l= str_start[s+1]-k;

if(first+l> buf_size+1)
overflow("buffer size",buf_size);

for(j= 0;j<=l-1;j++)buffer[first+j]= so(str_pool[k+j]);
cur_val= id_lookup(first,l);
flush_string;text(cur_val)= s;
}
eq_level(cur_val)= level_one;eq_type(cur_val)= c;equiv(cur_val)= o;
/*1583:*/
#line 28605 "texprof.w"

set_ROM_p_from_cs(cur_val);
ROM[p]= eqtb[cur_val];

/*:1583*/
#line 5850 "texprof.w"
;
}
#endif
#line 5853 "texprof.w"

/*:263*//*267:*/
#line 6079 "texprof.w"
/*283:*/
#line 6378 "texprof.w"

#ifdef STAT
static void restore_trace(pointer p,char*s)

{begin_diagnostic();print_char('{');print(s);print_char(' ');
show_eqtb(p);print_char('}');
end_diagnostic(false);
}
#endif
#line 6387 "texprof.w"

/*:283*//*1391:*/
#line 25986 "texprof.w"

static void print_group(bool e)
{
switch(cur_group){
case bottom_level:{print("bottom level");return;
}
case simple_group:case semi_simple_group:
{if(cur_group==semi_simple_group)print("semi ");
print("simple");
}break;
case hbox_group:case adjusted_hbox_group:
{if(cur_group==adjusted_hbox_group)print("adjusted ");
print("hbox");
}break;
case vbox_group:print("vbox");break;
case vtop_group:print("vtop");break;
case align_group:case no_align_group:
{if(cur_group==no_align_group)print("no ");
print("align");
}break;
case output_group:print("output");break;
case disc_group:print("disc");break;
case insert_group:print("insert");break;
case vcenter_group:print("vcenter");break;
case math_group:case math_choice_group:
case math_shift_group:case math_left_group:
{print("math");
if(cur_group==math_choice_group)print(" choice");
else if(cur_group==math_shift_group)print(" shift");
else if(cur_group==math_left_group)print(" left");
}
}
print(" group (level ");print_int(qo(cur_level));print_char(')');
if(saved(-1)!=0)
{if(e)print(" entered at line ");else print(" at line ");
print_int(saved(-1));
}
}

/*:1391*//*1392:*/
#line 26029 "texprof.w"

#ifdef STAT
static void group_trace(bool e)
{begin_diagnostic();print_char('{');
if(e)print("leaving ");else print("entering ");
print_group(e);print_char('}');end_diagnostic(false);
}
#endif
#line 26037 "texprof.w"

/*:1392*//*1438:*/
#line 26547 "texprof.w"

static bool pseudo_input(void)
{pointer p;
int sz;
four_quarters w;
int r;
last= first;
p= info(pseudo_files);
if(p==null)return false;
else{info(pseudo_files)= link(p);sz= ho(info(p));
if(4*sz-3>=buf_size-last)
/*35:*/
#line 1085 "texprof.w"

if(format_ident==0)
{write_ln(term_out,"Buffer size exceeded!");exit(0);

}
else{cur_input.loc_field= first;cur_input.limit_field= last-1;
overflow("buffer size",buf_size);

}

/*:35*/
#line 26558 "texprof.w"
;
last= first;
for(r= p+1;r<=p+sz-1;r++)
{w= mem[r].qqqq;
buffer[last]= w.b0;buffer[last+1]= w.b1;
buffer[last+2]= w.b2;buffer[last+3]= w.b3;
last= last+4;
}
if(last>=max_buf_stack)max_buf_stack= last+1;
while((last> first)&&(buffer[last-1]==' '))decr(last);
free_node(p,sz);
return true;
}
}

/*:1438*//*1439:*/
#line 26575 "texprof.w"

static void pseudo_close(void)
{pointer p,q;
p= link(pseudo_files);q= info(pseudo_files);
free_avail(pseudo_files);pseudo_files= p;
while(q!=null)
{p= q;q= link(p);free_node(p,ho(info(p)));
}
}

/*:1439*//*1456:*/
#line 26751 "texprof.w"

static void group_warning(void)
{int i;
bool w;
base_ptr= input_ptr;input_stack[base_ptr]= cur_input;

i= in_open;w= false;
while((grp_stack[i]==cur_boundary)&&(i> 0))
{/*1457:*/
#line 26774 "texprof.w"

if(tracing_nesting> 0)
{while((input_stack[base_ptr].state_field==token_list)||
(input_stack[base_ptr].index_field> i))decr(base_ptr);
if(input_stack[base_ptr].name_field> 17)w= true;
}

/*:1457*/
#line 26759 "texprof.w"
;
grp_stack[i]= save_index(save_ptr);decr(i);
}
if(w)
{print_nl("Warning: end of ");print_group(true);

print(" of a different file");print_ln();
if(tracing_nesting> 1)show_context();
if(history==spotless)history= warning_issued;
}
}

/*:1456*//*1458:*/
#line 26786 "texprof.w"

static void if_warning(void)
{int i;
bool w;
base_ptr= input_ptr;input_stack[base_ptr]= cur_input;

i= in_open;w= false;
while(if_stack[i]==cond_ptr)
{/*1457:*/
#line 26774 "texprof.w"

if(tracing_nesting> 0)
{while((input_stack[base_ptr].state_field==token_list)||
(input_stack[base_ptr].index_field> i))decr(base_ptr);
if(input_stack[base_ptr].name_field> 17)w= true;
}

/*:1457*/
#line 26794 "texprof.w"
;
if_stack[i]= link(cond_ptr);decr(i);
}
if(w)
{print_nl("Warning: end of ");print_cmd_chr(if_test,cur_if);

print_if_line(if_line);print(" of a different file");print_ln();
if(tracing_nesting> 1)show_context();
if(history==spotless)history= warning_issued;
}
}

/*:1458*//*1459:*/
#line 26810 "texprof.w"

static void file_warning(void)
{pointer p;
quarterword l;
quarterword c;
int i;
p= save_ptr;l= cur_level;c= cur_group;save_ptr= cur_boundary;
while(grp_stack[in_open]!=save_ptr)
{decr(cur_level);
print_nl("Warning: end of file when ");

print_group(true);print(" is incomplete");
cur_group= save_level(save_ptr);save_ptr= save_index(save_ptr);
}
save_ptr= p;cur_level= l;cur_group= c;
p= cond_ptr;l= if_limit;c= cur_if;i= if_line;
while(if_stack[in_open]!=cond_ptr)
{print_nl("Warning: end of file when ");

print_cmd_chr(if_test,cur_if);
if(if_limit==fi_code)print_esc("else");
print_if_line(if_line);print(" is incomplete");
if_line= if_line_field(cond_ptr);cur_if= subtype(cond_ptr);
if_limit= type(cond_ptr);cond_ptr= link(cond_ptr);
}
cond_ptr= p;if_limit= l;cur_if= c;if_line= i;
print_ln();
if(tracing_nesting> 1)show_context();
if(history==spotless)history= warning_issued;
}

/*:1459*//*1503:*/
#line 27595 "texprof.w"

static void delete_sa_ref(pointer q)
{
pointer p;
small_number i;
small_number s;
decr(sa_ref(q));
if(sa_ref(q)!=null)return;
if(sa_index(q)<dimen_val_limit)
if(sa_int(q)==0)s= word_node_size;
else return;
else{if(sa_index(q)<mu_val_limit)
if(sa_ptr(q)==zero_glue)delete_glue_ref(zero_glue);
else return;
else if(sa_ptr(q)!=null)return;
s= pointer_node_size;
}
do{i= hex_dig4(sa_index(q));p= q;q= link(p);free_node(p,s);
if(q==null)
{sa_root[i]= null;return;
}
delete_sa_ptr;s= index_node_size;
}while(!(sa_used(q)> 0));
}

/*:1503*//*1505:*/
#line 27638 "texprof.w"

#ifdef STAT
static void show_sa(pointer p,char*s)
{small_number t;
begin_diagnostic();print_char('{');print(s);print_char(' ');
if(p==null)print_char('?');
else{t= sa_type(p);
if(t<box_val)print_cmd_chr(internal_register,p);
else if(t==box_val)
{print_esc("box");print_sa_num(p);
}
else if(t==tok_val)print_cmd_chr(toks_register,p);
else print_char('?');
print_char('=');
if(t==int_val)print_int(sa_int(p));
else if(t==dimen_val)
{print_scaled(sa_dim(p));print("pt");
}
else{p= sa_ptr(p);
if(t==glue_val)print_spec(p,"pt");
else if(t==mu_val)print_spec(p,"mu");
else if(t==box_val)
if(p==null)print("void");
else{depth_threshold= 0;breadth_max= 1;show_node_list(p);
}
else if(t==tok_val)
{if(p!=null)show_token_list(link(p),null,32);
}
else print_char('?');
}
}
print_char('}');end_diagnostic(false);
}
#endif
#line 27672 "texprof.w"

/*:1505*//*1519:*/
#line 27856 "texprof.w"

static void sa_save(pointer p)
{pointer q;
quarterword i;
if(cur_level!=sa_level)
{check_full_save_stack;save_type(save_ptr)= restore_sa;
save_level(save_ptr)= sa_level;save_index(save_ptr)= sa_chain;
incr(save_ptr);sa_chain= null;sa_level= cur_level;
}
i= sa_index(p);
if(i<dimen_val_limit)
{if(sa_int(p)==0)
{q= get_node(pointer_node_size);i= tok_val_limit;
}
else{q= get_node(word_node_size);sa_int(q)= sa_int(p);
}
sa_ptr(q)= null;
}
else{q= get_node(pointer_node_size);sa_ptr(q)= sa_ptr(p);
}
sa_loc(q)= p;sa_index(q)= i;sa_lev(q)= sa_lev(p);
link(q)= sa_chain;sa_chain= q;add_sa_ref(p);
}

/*:1519*//*1520:*/
#line 27880 "texprof.w"

static void sa_destroy(pointer p)
{if(sa_index(p)<mu_val_limit)delete_glue_ref(sa_ptr(p));
else if(sa_ptr(p)!=null)
if(sa_index(p)<box_val_limit)flush_node_list(sa_ptr(p));
else delete_token_ref(sa_ptr(p));
}

/*:1520*//*1521:*/
#line 27906 "texprof.w"

static void sa_def(pointer p,halfword e)

{add_sa_ref(p);
if(sa_ptr(p)==e)
{
#ifdef STAT
if(tracing_assigns> 0)show_sa(p,"reassigning");
#endif
#line 27915 "texprof.w"

sa_destroy(p);
}
else{
#ifdef STAT
if(tracing_assigns> 0)show_sa(p,"changing");
#endif
#line 27922 "texprof.w"

if(sa_lev(p)==cur_level)sa_destroy(p);else sa_save(p);
sa_lev(p)= cur_level;sa_ptr(p)= e;
#ifdef STAT
if(tracing_assigns> 0)show_sa(p,"into");
#endif
#line 27928 "texprof.w"

}
delete_sa_ref(p);
}

static void sa_w_def(pointer p,int w)
{add_sa_ref(p);
if(sa_int(p)==w)
{
#ifdef STAT
if(tracing_assigns> 0)show_sa(p,"reassigning");
#endif
#line 27940 "texprof.w"

}
else{
#ifdef STAT
if(tracing_assigns> 0)show_sa(p,"changing");
#endif
#line 27946 "texprof.w"

if(sa_lev(p)!=cur_level)sa_save(p);
sa_lev(p)= cur_level;sa_int(p)= w;
#ifdef STAT
if(tracing_assigns> 0)show_sa(p,"into");
#endif
#line 27952 "texprof.w"

}
delete_sa_ref(p);
}

/*:1521*//*1522:*/
#line 27962 "texprof.w"

static void gsa_def(pointer p,halfword e)
{add_sa_ref(p);
#ifdef STAT
if(tracing_assigns> 0)show_sa(p,"globally changing");
#endif
#line 27968 "texprof.w"

sa_destroy(p);sa_lev(p)= level_one;sa_ptr(p)= e;
#ifdef STAT
if(tracing_assigns> 0)show_sa(p,"into");
#endif
#line 27973 "texprof.w"

delete_sa_ref(p);
}

static void gsa_w_def(pointer p,int w)
{add_sa_ref(p);
#ifdef STAT
if(tracing_assigns> 0)show_sa(p,"globally changing");
#endif
#line 27982 "texprof.w"

sa_lev(p)= level_one;sa_int(p)= w;
#ifdef STAT
if(tracing_assigns> 0)show_sa(p,"into");
#endif
#line 27987 "texprof.w"

delete_sa_ref(p);
}

/*:1522*//*1523:*/
#line 27994 "texprof.w"

static void sa_restore(void)
{pointer p;
do{p= sa_loc(sa_chain);
if(sa_lev(p)==level_one)
{if(sa_index(p)>=dimen_val_limit)sa_destroy(sa_chain);
#ifdef STAT
if(tracing_restores> 0)show_sa(p,"retaining");
#endif
#line 28003 "texprof.w"

}
else{if(sa_index(p)<dimen_val_limit)
if(sa_index(sa_chain)<dimen_val_limit)sa_int(p)= sa_int(sa_chain);
else sa_int(p)= 0;
else{sa_destroy(p);sa_ptr(p)= sa_ptr(sa_chain);
}
sa_lev(p)= sa_lev(sa_chain);
#ifdef STAT
if(tracing_restores> 0)show_sa(p,"restoring");
#endif
#line 28014 "texprof.w"

}
delete_sa_ref(p);
p= sa_chain;sa_chain= link(p);
if(sa_index(p)<dimen_val_limit)free_node(p,word_node_size);
else free_node(p,pointer_node_size);
}while(!(sa_chain==null));
}

/*:1523*/
#line 6079 "texprof.w"


/*:267*//*273:*/
#line 6164 "texprof.w"
static void new_save_level(group_code c)
{check_full_save_stack;
if(eTeX_ex)
{saved(0)= line;incr(save_ptr);
}
save_type(save_ptr)= level_boundary;save_level(save_ptr)= cur_group;
save_index(save_ptr)= cur_boundary;
if(cur_level==max_quarterword)overflow("grouping levels",

max_quarterword-min_quarterword);

cur_boundary= save_ptr;cur_group= c;
#ifdef STAT
if(tracing_groups> 0)group_trace(false);
#endif
#line 6179 "texprof.w"

incr(cur_level);incr(save_ptr);
}

/*:273*//*274:*/
#line 6189 "texprof.w"
static void eq_destroy(memory_word w)
{pointer q;
switch(eq_type_field(w)){
case call:case long_call:case outer_call:
case long_outer_call:delete_token_ref(equiv_field(w));break;
case glue_ref:delete_glue_ref(equiv_field(w));break;
case shape_ref:{q= equiv_field(w);
if(q!=null)free_node(q,info(q)+info(q)+1);
}break;
case box_ref:flush_node_list(equiv_field(w));break;
/*1516:*/
#line 27831 "texprof.w"

case toks_register:case internal_register:
if((equiv_field(w)<mem_bot)||(equiv_field(w)> lo_mem_stat_max))
delete_sa_ref(equiv_field(w));break;

/*:1516*/
#line 6199 "texprof.w"

default:do_nothing;
}
}

/*:274*//*275:*/
#line 6207 "texprof.w"
static void eq_save(pointer p,quarterword l)
{check_full_save_stack;
if(l==level_zero)save_type(save_ptr)= restore_zero;
else{save_stack[save_ptr]= eqtb[p];incr(save_ptr);
save_type(save_ptr)= restore_old_value;
}
save_level(save_ptr)= l;save_index(save_ptr)= p;incr(save_ptr);
}

/*:275*//*276:*/
#line 6224 "texprof.w"

#ifdef STAT
#define  assign_trace(A, B) if (tracing_assigns >  0) restore_trace(A, B);
#else
#line 6228 "texprof.w"
#define  assign_trace(A, B)
#endif
#line 6230 "texprof.w"

static void eq_define(pointer p,quarterword t,halfword e)

{
if(eTeX_ex&&(eq_type(p)==t)&&(equiv(p)==e))
{assign_trace(p,"reassigning")
eq_destroy(eqtb[p]);return;
}
assign_trace(p,"changing")
if(eq_level(p)==cur_level)eq_destroy(eqtb[p]);
else if(cur_level> level_one)eq_save(p,eq_level(p));
eq_level(p)= cur_level;eq_type(p)= t;equiv(p)= e;
assign_trace(p,"into")
}

/*:276*//*277:*/
#line 6249 "texprof.w"
static void eq_word_define(pointer p,int w)
{
if(eTeX_ex&&(eqtb[p].i==w))
{assign_trace(p,"reassigning")
return;
}
assign_trace(p,"changing")
if(xeq_level[p]!=cur_level)
{eq_save(p,xeq_level[p]);xeq_level[p]= cur_level;
}
eqtb[p].i= w;
assign_trace(p,"into")
}

/*:277*//*278:*/
#line 6268 "texprof.w"
static void geq_define(pointer p,quarterword t,halfword e)

{assign_trace(p,"globally changing")
{eq_destroy(eqtb[p]);
eq_level(p)= level_one;eq_type(p)= t;equiv(p)= e;
}
assign_trace(p,"into");
}

static void geq_word_define(pointer p,int w)
{assign_trace(p,"globally changing")
{eqtb[p].i= w;xeq_level[p]= level_one;
}
assign_trace(p,"into");
}

/*:278*//*279:*/
#line 6286 "texprof.w"
static void save_for_after(halfword t)
{if(cur_level> level_one)
{check_full_save_stack;
save_type(save_ptr)= insert_token;save_level(save_ptr)= level_zero;
save_index(save_ptr)= t;incr(save_ptr);
}
}

/*:279*//*280:*/
#line 6298 "texprof.w"

static void back_input(void);
static void unsave(void)
{
pointer p;
quarterword l;
halfword t;
bool a;
a= false;
if(cur_level> level_one)
{decr(cur_level);
/*281:*/
#line 6315 "texprof.w"

loop{decr(save_ptr);
if(save_type(save_ptr)==level_boundary)goto done;
p= save_index(save_ptr);
if(save_type(save_ptr)==insert_token)
/*325:*/
#line 7370 "texprof.w"

{t= cur_tok;cur_tok= p;
if(a)
{p= get_avail();info(p)= cur_tok;link(p)= loc;loc= p;start= p;
if(cur_tok<right_brace_limit)
if(cur_tok<left_brace_limit)decr(align_state);
else incr(align_state);
}
else{back_input();a= eTeX_ex;
}
cur_tok= t;
}

/*:325*/
#line 6320 "texprof.w"

else if(save_type(save_ptr)==restore_sa)
{sa_restore();sa_chain= p;sa_level= save_level(save_ptr);
}
else{if(save_type(save_ptr)==restore_old_value)
{l= save_level(save_ptr);decr(save_ptr);
}
else save_stack[save_ptr]= eqtb[undefined_control_sequence];
/*282:*/
#line 6348 "texprof.w"

if(p<int_base)
if(eq_level(p)==level_one)
{eq_destroy(save_stack[save_ptr]);
#ifdef STAT
if(tracing_restores> 0)restore_trace(p,"retaining");
#endif
#line 6355 "texprof.w"

}
else{eq_destroy(eqtb[p]);
eqtb[p]= save_stack[save_ptr];
#ifdef STAT
if(tracing_restores> 0)restore_trace(p,"restoring");
#endif
#line 6362 "texprof.w"

}
else if(xeq_level[p]!=level_one)
{eqtb[p]= save_stack[save_ptr];xeq_level[p]= l;
#ifdef STAT
if(tracing_restores> 0)restore_trace(p,"restoring");
#endif
#line 6369 "texprof.w"

}
else{
#ifdef STAT
if(tracing_restores> 0)restore_trace(p,"retaining");
#endif
#line 6375 "texprof.w"

}

/*:282*/
#line 6329 "texprof.w"
;
}
}
done:
#ifdef STAT
if(tracing_groups> 0)group_trace(true);
#endif
#line 6336 "texprof.w"

if(grp_stack[in_open]==cur_boundary)group_warning();

cur_group= save_level(save_ptr);cur_boundary= save_index(save_ptr);
if(eTeX_ex)decr(save_ptr)

/*:281*/
#line 6309 "texprof.w"
;
}
else confusion("curlevel");

}

/*:280*//*287:*/
#line 6417 "texprof.w"
static void prepare_mag(void)
{if((mag_set> 0)&&(mag!=mag_set))
{print_err("Incompatible magnification (");print_int(mag);

print(");");print_nl(" the previous value will be retained");
help2("I can handle only one magnification ratio per job. So I've",
"reverted to the magnification you used earlier on this run.");
int_error(mag_set);
geq_word_define(int_base+mag_code,mag_set);
}
if((mag<=0)||(mag> 32768))
{print_err("Illegal magnification has been changed to 1000");

help1("The magnification ratio must be between 1 and 32768.");
int_error(mag);geq_word_define(int_base+mag_code,1000);
}
mag_set= mag;
}

/*:287*//*294:*/
#line 6604 "texprof.w"
static void token_show(pointer p)
{if(p!=null)show_token_list(link(p),null,10000000);
}

/*:294*//*295:*/
#line 6611 "texprof.w"
static void print_meaning(void)
{print_cmd_chr(cur_cmd,cur_chr);
if(cur_cmd>=call)
{print_char(':');print_ln();token_show(cur_chr);
}
else if((cur_cmd==top_bot_mark)&&(cur_chr<marks_code))
{print_char(':');print_ln();
token_show(cur_mark[cur_chr]);
}
}

/*:295*//*298:*/
#line 6710 "texprof.w"
static void show_cur_cmd_chr(void)
{int n;
int l;
pointer p;
begin_diagnostic();print_nl("{");
if(mode!=shown_mode)
{print_mode(mode);print(": ");shown_mode= mode;
}
print_cmd_chr(cur_cmd,cur_chr);
if(tracing_ifs> 0)
if(cur_cmd>=if_test)if(cur_cmd<=fi_or_else)
{print(": ");
if(cur_cmd==fi_or_else)
{print_cmd_chr(if_test,cur_if);print_char(' ');
n= 0;l= if_line;
}
else{n= 1;l= line;
}
p= cond_ptr;
while(p!=null)
{incr(n);p= link(p);
}
print("(level ");print_int(n);print_char(')');print_if_line(l);
}
print_char('}');
end_diagnostic(false);
}

/*:298*//*310:*/
#line 7091 "texprof.w"
static void show_context(void)
{
int old_setting;
int nn;
bool bottom_line;
/*314:*/
#line 7206 "texprof.w"

int i;
int j;
int l;
int m;
int n;
int p;
int q;

/*:314*/
#line 7096 "texprof.w"

base_ptr= input_ptr;input_stack[base_ptr]= cur_input;

nn= -1;bottom_line= false;
loop{cur_input= input_stack[base_ptr];
if((state!=token_list))
if((name> 19)||(base_ptr==0))bottom_line= true;
if((base_ptr==input_ptr)||bottom_line||(nn<error_context_lines))
/*311:*/
#line 7114 "texprof.w"

{if((base_ptr==input_ptr)||(state!=token_list)||
(token_type!=backed_up)||(loc!=null))

{tally= 0;
old_setting= selector;
if(state!=token_list)
{/*312:*/
#line 7138 "texprof.w"

if(name<=17)
if(terminal_input)
if(base_ptr==0)print_nl("<*>");else print_nl("<insert> ");
else{print_nl("<read ");
if(name==17)print_char('*');else print_int(name-1);

print_char('>');
}
else{print_nl("l.");
if(index==in_open)print_int(line);
else print_int(line_stack[index+1]);
}
print_char(' ')

/*:312*/
#line 7121 "texprof.w"
;
/*317:*/
#line 7252 "texprof.w"

begin_pseudoprint;
if(buffer[limit]==end_line_char)j= limit;
else j= limit+1;
if(j> 0)for(i= start;i<=j-1;i++)
{if(i==loc)set_trick_count;
printn(buffer[i]);
}

/*:317*/
#line 7122 "texprof.w"
;
}
else{/*313:*/
#line 7153 "texprof.w"

switch(token_type){
case parameter:print_nl("<argument> ");break;
case u_template:case v_template:print_nl("<template> ");break;
case backed_up:if(loc==null)print_nl("<recently read> ");
else print_nl("<to be read again> ");break;
case inserted:print_nl("<inserted text> ");break;
case macro:{print_ln();print_cs(name);
}break;
case output_text:print_nl("<output> ");break;
case every_par_text:print_nl("<everypar> ");break;
case every_math_text:print_nl("<everymath> ");break;
case every_display_text:print_nl("<everydisplay> ");break;
case every_hbox_text:print_nl("<everyhbox> ");break;
case every_vbox_text:print_nl("<everyvbox> ");break;
case every_job_text:print_nl("<everyjob> ");break;
case every_cr_text:print_nl("<everycr> ");break;
case mark_text:print_nl("<mark> ");break;
case every_eof_text:print_nl("<everyeof> ");break;
case write_text:print_nl("<write> ");break;
default:print_nl("?");
}

/*:313*/
#line 7124 "texprof.w"
;
/*318:*/
#line 7261 "texprof.w"

begin_pseudoprint;
if(token_type<macro)show_token_list(start,loc,100000);
else show_token_list(link(start),loc,100000)

/*:318*/
#line 7125 "texprof.w"
;
}
selector= old_setting;
/*316:*/
#line 7230 "texprof.w"

if(trick_count==1000000)set_trick_count;

if(tally<trick_count)m= tally-first_count;
else m= trick_count-first_count;
if(l+first_count<=half_error_line)
{p= 0;n= l+first_count;
}
else{print("...");p= l+first_count-half_error_line+3;
n= half_error_line;
}
for(q= p;q<=first_count-1;q++)print_char(trick_buf[q%error_line]);
print_ln();
for(q= 1;q<=n;q++)print_char(' ');
if(m+n<=error_line)p= first_count+m;else p= first_count+(error_line-n-3);
for(q= first_count;q<=p-1;q++)print_char(trick_buf[q%error_line]);
if(m+n> error_line)print("...")

/*:316*/
#line 7128 "texprof.w"
;
incr(nn);
}
}

/*:311*/
#line 7104 "texprof.w"

else if(nn==error_context_lines)
{print_nl("...");incr(nn);
}
if(bottom_line)goto done;
decr(base_ptr);
}
done:cur_input= input_stack[input_ptr];
}

/*:310*//*322:*/
#line 7300 "texprof.w"
static void begin_token_list(pointer p,quarterword t)
{push_input;state= token_list;start= p;token_type= t;
if(t>=macro)
{add_token_ref(p);
if(t==macro)param_start= param_ptr;
else{
/*1777:*/
#line 31589 "texprof.w"

uint32_t macro_fl= fl_mem[p];
int macro_cs= undefined_control_sequence+t;

int macro_depth= cur_depth;


/*:1777*/
#line 7306 "texprof.w"

loc= link(p);
if(tracing_macros> 1)
{begin_diagnostic();print_nl("");
switch(t){
case mark_text:print_esc("mark");break;
case write_text:print_esc("write");break;
default:print_cmd_chr(assign_toks,t-output_text+output_routine_loc);
}
print("->");token_show(p);end_diagnostic(false);
}
/*1775:*/
#line 31573 "texprof.w"

macro_depth++;
cur_depth= macro_depth;
if(macro_depth>=MAX_MACRO_STACK)
overflow("macro stack size",macro_depth);
macro_stack[macro_depth]= CALL_INFO(macro_depth,macro_cs,macro_fl);
if(macro_depth<=unchanged_depth)
unchanged_depth= macro_depth-1;

/*:1775*/
#line 7317 "texprof.w"

}
}
else loc= p;
}

/*:322*//*323:*/
#line 7328 "texprof.w"
static void end_token_list(void)
{if(token_type>=backed_up)
{if(token_type<=inserted)flush_list(start);
else{delete_token_ref(start);
if(token_type==macro)
while(param_ptr> param_start)
{decr(param_ptr);
flush_list(param_stack[param_ptr]);
}
}
}
else if(token_type==u_template)
if(align_state> 500000)align_state= 0;
else fatal_error("(interwoven alignment preambles are not allowed)");

pop_input;
check_interrupt;
}

/*:323*//*324:*/
#line 7358 "texprof.w"
static void back_input(void)
{pointer p;
while((state==token_list)&&(loc==null)&&(token_type!=v_template))
end_token_list();
p= get_avail();info(p)= cur_tok;fl_mem[p]= prof_file_line;
if(cur_tok<right_brace_limit)
if(cur_tok<left_brace_limit)decr(align_state);
else incr(align_state);
push_input;state= token_list;start= p;token_type= backed_up;
loc= p;
}

/*:324*//*326:*/
#line 7388 "texprof.w"
static void back_error(void)
{OK_to_interrupt= false;back_input();OK_to_interrupt= true;error();
}

static void ins_error(void)
{OK_to_interrupt= false;back_input();token_type= inserted;
OK_to_interrupt= true;error();
}

/*:326*//*327:*/
#line 7403 "texprof.w"
static void begin_file_reading(void)
{if(in_open==max_in_open)overflow("text input levels",max_in_open);

if(first==buf_size)overflow("buffer size",buf_size);

incr(in_open);push_input;index= in_open;
source_filename_stack[index]= NULL;
full_source_filename_stack[index]= NULL;
eof_seen[index]= false;
grp_stack[index]= cur_boundary;if_stack[index]= cond_ptr;
line_stack[index]= line;start= first;state= mid_line;
name= 0;
cur_file_num= terminal_file;
}

/*:327*//*328:*/
#line 7421 "texprof.w"
static void end_file_reading(void)
{first= start;line= line_stack[index];
if((name==18)||(name==19))pseudo_close();else
if(name> 17)a_close(&cur_file);
if(full_source_filename_stack[in_open]!=NULL)
{free(full_source_filename_stack[in_open]);
full_source_filename_stack[in_open]= NULL;
}
pop_input;decr(in_open);
}

/*:328*//*329:*/
#line 7436 "texprof.w"
static void clear_for_error_prompt(void)
{while((state!=token_list)&&terminal_input&&
(input_ptr> 0)&&(loc> limit))end_file_reading();
print_ln();clear_terminal;
}

/*:329*//*335:*/
#line 7510 "texprof.w"
static void check_outer_validity(void)
{pointer p;
pointer q;
if(scanner_status!=normal)
{deletions_allowed= false;
/*336:*/
#line 7536 "texprof.w"

if(cur_cs!=0)
{if((state==token_list)||(name<1)||(name> 17))
{p= get_avail();info(p)= cs_token_flag+cur_cs;
back_list(p);
}
cur_cmd= spacer;cur_chr= ' ';
}

/*:336*/
#line 7515 "texprof.w"
;
if(scanner_status> skipping)
/*337:*/
#line 7545 "texprof.w"

{runaway();
if(cur_cs==0)print_err("File ended");

else{cur_cs= 0;print_err("Forbidden control sequence found");

}
print(" while scanning ");
/*338:*/
#line 7571 "texprof.w"

p= get_avail();
switch(scanner_status){
case defining:{print("definition");info(p)= right_brace_token+'}';
}break;
case matching:{print("use");info(p)= par_token;long_state= outer_call;
}break;
case aligning:{print("preamble");info(p)= right_brace_token+'}';q= p;
p= get_avail();link(p)= q;info(p)= cs_token_flag+frozen_cr;
align_state= -1000000;
}break;
case absorbing:{print("text");info(p)= right_brace_token+'}';
}
}
ins_list(p)

/*:338*/
#line 7554 "texprof.w"
;
print(" of ");sprint_cs(warning_index);
help4("I suspect you have forgotten a `}', causing me",
"to read past where you wanted me to stop.",
"I'll try to recover; but if the error is serious,",
"you'd better type `E' or `X' now and fix your file.");
error();
}

/*:337*/
#line 7517 "texprof.w"

else{print_err("Incomplete ");print_cmd_chr(if_test,cur_if);

print("; all text was ignored after line ");print_int(skip_line);
help3("A forbidden control sequence occurred in skipped text.",
"This kind of error happens when you say `\\if...' and forget",
"the matching `\\fi'. I've inserted a `\\fi'; this might work.");
if(cur_cs!=0)cur_cs= 0;
else help_line[2]= 
"The file ended while I was skipping conditional text.";
cur_tok= cs_token_flag+frozen_fi;ins_error();
}
deletions_allowed= true;
}
}

/*:335*//*339:*/
#line 7589 "texprof.w"
static void firm_up_the_line(void);

/*:339*//*340:*/
#line 7595 "texprof.w"
static void get_next(void)
{





int k;
halfword t;
int cat;
ASCII_code c,cc;
int d;
restart:cur_cs= 0;
if(state!=token_list)
/*342:*/
#line 7625 "texprof.w"


{get_cur_chr:if(loc<=limit)
{cur_chr= buffer[loc];incr(loc);
/*1752:*/
#line 31137 "texprof.w"

if(terminal_input)
cur_file_line= FILE_LINE(terminal_file,0);
else if(name<=19)
cur_file_line= FILE_LINE(read_file_num[name-1],0);
else
cur_file_line= FILE_LINE(cur_file_num,line);

/*:1752*/
#line 7629 "texprof.w"

reswitch:cur_cmd= cat_code(cur_chr);
/*343:*/
#line 7652 "texprof.w"

switch(state+cur_cmd){
/*344:*/
#line 7666 "texprof.w"

any_state_plus(ignore):case skip_blanks+spacer:
case new_line+spacer

/*:344*/
#line 7654 "texprof.w"
:goto get_cur_chr;
any_state_plus(escape):/*353:*/
#line 7774 "texprof.w"

{if(loc> limit)cur_cs= null_cs;
else{start_cs:k= loc;cur_chr= buffer[k];cat= cat_code(cur_chr);
incr(k);
if(cat==letter)state= skip_blanks;
else if(cat==spacer)state= skip_blanks;
else state= mid_line;
if((cat==letter)&&(k<=limit))
/*355:*/
#line 7820 "texprof.w"

{do{cur_chr= buffer[k];cat= cat_code(cur_chr);incr(k);
}while(!((cat!=letter)||(k> limit)));
/*354:*/
#line 7799 "texprof.w"

{if(buffer[k]==cur_chr)if(cat==sup_mark)if(k<limit)
{c= buffer[k+1];if(c<0200)
{d= 2;
if(is_hex(c))if(k+2<=limit)
{cc= buffer[k+2];if(is_hex(cc))incr(d);
}
if(d> 2)
{hex_to_cur_chr;buffer[k-1]= cur_chr;
}
else if(c<0100)buffer[k-1]= c+0100;
else buffer[k-1]= c-0100;
limit= limit-d;first= first-d;
while(k<=limit)
{buffer[k]= buffer[k+d];incr(k);
}
goto start_cs;
}
}
}

/*:354*/
#line 7823 "texprof.w"
;
if(cat!=letter)decr(k);

if(k> loc+1)
{cur_cs= id_lookup(loc,k-loc);loc= k;goto found;
}
}

/*:355*/
#line 7784 "texprof.w"

else/*354:*/
#line 7799 "texprof.w"

{if(buffer[k]==cur_chr)if(cat==sup_mark)if(k<limit)
{c= buffer[k+1];if(c<0200)
{d= 2;
if(is_hex(c))if(k+2<=limit)
{cc= buffer[k+2];if(is_hex(cc))incr(d);
}
if(d> 2)
{hex_to_cur_chr;buffer[k-1]= cur_chr;
}
else if(c<0100)buffer[k-1]= c+0100;
else buffer[k-1]= c-0100;
limit= limit-d;first= first-d;
while(k<=limit)
{buffer[k]= buffer[k+d];incr(k);
}
goto start_cs;
}
}
}

/*:354*/
#line 7785 "texprof.w"
;
cur_cs= single_base+buffer[loc];incr(loc);
}
found:cur_cmd= eq_type(cur_cs);cur_chr= equiv(cur_cs);
if(cur_cmd>=outer_call)check_outer_validity();
}

/*:353*/
#line 7656 "texprof.w"
break;
any_state_plus(active_char):/*352:*/
#line 7753 "texprof.w"

{cur_cs= cur_chr+active_base;
cur_cmd= eq_type(cur_cs);cur_chr= equiv(cur_cs);state= mid_line;
if(cur_cmd>=outer_call)check_outer_validity();
}

/*:352*/
#line 7658 "texprof.w"
break;
any_state_plus(sup_mark):/*351:*/
#line 7737 "texprof.w"

{if(cur_chr==buffer[loc])if(loc<limit)
{c= buffer[loc+1];if(c<0200)
{loc= loc+2;
if(is_hex(c))if(loc<=limit)
{cc= buffer[loc];if(is_hex(cc))
{incr(loc);hex_to_cur_chr;goto reswitch;
}
}
if(c<0100)cur_chr= c+0100;else cur_chr= c-0100;
goto reswitch;
}
}
state= mid_line;
}

/*:351*/
#line 7660 "texprof.w"
break;
any_state_plus(invalid_char):/*345:*/
#line 7674 "texprof.w"

{print_err("Text line contains an invalid character");

help2("A funny symbol that I can't read has just been input.",
"Continue, and I'll forget that it ever happened.");
deletions_allowed= false;error();deletions_allowed= true;
goto restart;
}

/*:345*/
#line 7661 "texprof.w"

/*346:*/
#line 7686 "texprof.w"

case mid_line+spacer:/*348:*/
#line 7715 "texprof.w"

{state= skip_blanks;cur_chr= ' ';
}

/*:348*/
#line 7687 "texprof.w"
break;
case mid_line+car_ret:/*347:*/
#line 7709 "texprof.w"

{loc= limit+1;cur_cmd= spacer;cur_chr= ' ';
}

/*:347*/
#line 7688 "texprof.w"
break;
case skip_blanks+car_ret:any_state_plus(comment):
/*349:*/
#line 7719 "texprof.w"

{loc= limit+1;goto get_cur_chr;
}

/*:349*/
#line 7690 "texprof.w"

case new_line+car_ret:/*350:*/
#line 7723 "texprof.w"

{loc= limit+1;cur_cs= par_loc;cur_cmd= eq_type(cur_cs);
cur_chr= equiv(cur_cs);
if(cur_cmd>=outer_call)check_outer_validity();
}

/*:350*/
#line 7691 "texprof.w"
break;
case mid_line+left_brace:incr(align_state);break;
case skip_blanks+left_brace:case new_line+left_brace:{
state= mid_line;incr(align_state);
}break;
case mid_line+right_brace:decr(align_state);break;
case skip_blanks+right_brace:case new_line+right_brace:{
state= mid_line;decr(align_state);
}break;
add_delims_to(case skip_blanks):add_delims_to(
case new_line):state= mid_line;break;

/*:346*/
#line 7662 "texprof.w"

default:do_nothing;
}

/*:343*/
#line 7633 "texprof.w"
;
}
else{state= new_line;
/*359:*/
#line 7886 "texprof.w"

if(name> 17)/*361:*/
#line 7925 "texprof.w"

{incr(line);first= start;
/*1747:*/
#line 31077 "texprof.w"

if(line>=MAX_LINE)overflow("too many input lines",MAX_LINE);

/*:1747*/
#line 7927 "texprof.w"

if(!force_eof)
if(name<=19)
{if(pseudo_input())
firm_up_the_line();
else if((every_eof!=null)&&!eof_seen[index])
{limit= first-1;eof_seen[index]= true;
begin_token_list(every_eof,every_eof_text);goto restart;
}
else force_eof= true;
}
else
{if(input_ln(&cur_file,true))
firm_up_the_line();
else if((every_eof!=null)&&!eof_seen[index])
{limit= first-1;eof_seen[index]= true;
begin_token_list(every_eof,every_eof_text);goto restart;
}
else force_eof= true;
}
if(force_eof)
{if(tracing_nesting> 0)
if((grp_stack[in_open]!=cur_boundary)||
(if_stack[in_open]!=cond_ptr))file_warning();

if(name>=19)
{print_char(')');decr(open_parens);
update_terminal;
}
force_eof= false;
end_file_reading();
check_outer_validity();goto restart;
}
if(end_line_char_inactive)decr(limit);
else buffer[limit]= end_line_char;
first= limit+1;loc= start;
}

/*:361*/
#line 7888 "texprof.w"

else{if(!terminal_input)
{cur_cmd= 0;cur_chr= 0;
/*1753:*/
#line 31146 "texprof.w"

cur_file_line= FILE_LINE(read_file_num[name-1],0);


/*:1753*/
#line 7891 "texprof.w"

return;
}
if(input_ptr> 0)
{end_file_reading();goto restart;
}
if(selector<log_only)open_log_file();
if(interaction> nonstop_mode)
{if(end_line_char_inactive)incr(limit);
if(limit==start)
print_nl("(Please type a command or say `\\end')");

print_ln();first= start;
prompt_input("*");

limit= last;
if(end_line_char_inactive)decr(limit);
else buffer[limit]= end_line_char;
first= limit+1;
loc= start;
}
else fatal_error("*** (job aborted, no legal \\end found)");



}

/*:359*/
#line 7637 "texprof.w"
;
check_interrupt;
goto get_cur_chr;
}
}

/*:342*/
#line 7609 "texprof.w"

else/*356:*/
#line 7836 "texprof.w"

if(loc!=null)

{t= info(loc);cur_file_line= fl_mem[loc];
loc= link(loc);
if(t>=cs_token_flag)
{cur_cs= t-cs_token_flag;
cur_cmd= eq_type(cur_cs);cur_chr= equiv(cur_cs);
if(cur_cmd>=outer_call)
if(cur_cmd==dont_expand)
/*357:*/
#line 7868 "texprof.w"

{cur_cs= info(loc)-cs_token_flag;loc= null;
cur_cmd= eq_type(cur_cs);cur_chr= equiv(cur_cs);
if(cur_cmd> max_command)
{cur_cmd= relax;cur_chr= no_expand_flag;
}
}

/*:357*/
#line 7846 "texprof.w"

else check_outer_validity();
}
else{cur_cmd= t/0400;cur_chr= t%0400;
switch(cur_cmd){
case left_brace:incr(align_state);break;
case right_brace:decr(align_state);break;
case out_param:/*358:*/
#line 7876 "texprof.w"

{begin_token_list(param_stack[param_start+cur_chr-1],parameter);
goto restart;
}

/*:358*/
#line 7853 "texprof.w"

default:do_nothing;
}
}
}
else{
end_token_list();goto restart;
}

/*:356*/
#line 7611 "texprof.w"
;
/*341:*/
#line 7621 "texprof.w"

if(cur_cmd<=car_ret)if(cur_cmd>=tab_mark)if(align_state==0)
/*788:*/
#line 16124 "texprof.w"

{if((scanner_status==aligning)||(cur_align==null))
fatal_error("(interwoven alignment preambles are not allowed)");

cur_cmd= extra_info(cur_align);extra_info(cur_align)= cur_chr;
if(cur_cmd==omit)begin_token_list(omit_template,v_template);
else begin_token_list(v_part(cur_align),v_template);
align_state= 1000000;goto restart;
}

/*:788*/
#line 7623 "texprof.w"


/*:341*/
#line 7612 "texprof.w"
;
}

/*:340*//*362:*/
#line 7972 "texprof.w"
static void firm_up_the_line(void)
{int k;
limit= last;
if(pausing> 0)if(interaction> nonstop_mode)
{wake_up_terminal;print_ln();
if(start<limit)for(k= start;k<=limit-1;k++)printn(buffer[k]);
first= limit;prompt_input("=>");

if(last> first)
{for(k= first;k<=last-1;k++)
buffer[k+start-first]= buffer[k];
limit= start+last-first;
}
}
}

/*:362*//*364:*/
#line 8011 "texprof.w"
static void get_token(void)
{no_new_control_sequence= false;get_next();no_new_control_sequence= true;

if(cur_cs==0)cur_tok= (cur_cmd*0400)+cur_chr;
else cur_tok= cs_token_flag+cur_cs;
}

/*:364*//*365:*/
#line 8037 "texprof.w"
/*388:*/
#line 8358 "texprof.w"

static void macro_call(void)
{
pointer r;
pointer p;
pointer q;
pointer s;
pointer t;
pointer u,v;
pointer rbrace_ptr;
small_number n;
halfword unbalance;
int m;
pointer ref_count;
small_number save_scanner_status;
pointer save_warning_index;
ASCII_code match_chr;
/*1774:*/
#line 31565 "texprof.w"

uint32_t macro_fl= fl_mem[cur_chr];
int macro_cs= cur_cs;
int macro_depth= cur_depth;

/*:1774*/
#line 8375 "texprof.w"

save_scanner_status= scanner_status;save_warning_index= warning_index;
warning_index= cur_cs;ref_count= cur_chr;r= link(ref_count);n= 0;
if(tracing_macros> 0)/*400:*/
#line 8585 "texprof.w"

{begin_diagnostic();print_ln();print_cs(warning_index);
token_show(ref_count);end_diagnostic(false);
}

/*:400*/
#line 8378 "texprof.w"
;
if(info(r)==protected_token)r= link(r);
if(info(r)!=end_match_token)
/*390:*/
#line 8417 "texprof.w"

{scanner_status= matching;unbalance= 0;
long_state= eq_type(cur_cs);
if(long_state>=outer_call)long_state= long_state-2;
do{link(temp_head)= null;
if((info(r)> match_token+255)||(info(r)<match_token))s= null;
else{match_chr= info(r)-match_token;s= link(r);r= s;
p= temp_head;m= 0;
}
/*391:*/
#line 8437 "texprof.w"

resume:get_token();
if(cur_tok==info(r))
/*393:*/
#line 8469 "texprof.w"

{r= link(r);
if((info(r)>=match_token)&&(info(r)<=end_match_token))
{if(cur_tok<left_brace_limit)decr(align_state);
goto found;
}
else goto resume;
}

/*:393*/
#line 8441 "texprof.w"
;
/*396:*/
#line 8525 "texprof.w"

if(s!=r)
if(s==null)/*397:*/
#line 8542 "texprof.w"

{print_err("Use of ");sprint_cs(warning_index);

print(" doesn't match its definition");
help4("If you say, e.g., `\\def\\a1{...}', then you must always",
"put `1' after `\\a', since control sequence names are",
"made up of letters only. The macro here has not been",
"followed by the required stuff, so I'm ignoring it.");
error();goto end;
}

/*:397*/
#line 8527 "texprof.w"

else{t= s;
do{store_new_token(info(t));incr(m);u= link(t);v= s;
loop{if(u==r)
if(cur_tok!=info(v))goto done;
else{r= link(v);goto resume;
}
if(info(u)!=info(v))goto done;
u= link(u);v= link(v);
}
done:t= link(t);
}while(!(t==r));
r= s;
}

/*:396*/
#line 8443 "texprof.w"
;
if(cur_tok==par_token)if(long_state!=long_call)
/*395:*/
#line 8494 "texprof.w"

{if(long_state==call)
{runaway();print_err("Paragraph ended before ");

sprint_cs(warning_index);print(" was complete");
help3("I suspect you've forgotten a `}', causing me to apply this",
"control sequence to too much text. How can we recover?",
"My plan is to forget the whole thing and hope for the best.");
back_error();
}
pstack[n]= link(temp_head);align_state= align_state-unbalance;
for(m= 0;m<=n;m++)flush_list(pstack[m]);
goto end;
}

/*:395*/
#line 8445 "texprof.w"
;
if(cur_tok<right_brace_limit)
if(cur_tok<left_brace_limit)
/*398:*/
#line 8553 "texprof.w"

{unbalance= 1;

loop{fast_store_new_token(cur_tok);get_token();
if(cur_tok==par_token)if(long_state!=long_call)
/*395:*/
#line 8494 "texprof.w"

{if(long_state==call)
{runaway();print_err("Paragraph ended before ");

sprint_cs(warning_index);print(" was complete");
help3("I suspect you've forgotten a `}', causing me to apply this",
"control sequence to too much text. How can we recover?",
"My plan is to forget the whole thing and hope for the best.");
back_error();
}
pstack[n]= link(temp_head);align_state= align_state-unbalance;
for(m= 0;m<=n;m++)flush_list(pstack[m]);
goto end;
}

/*:395*/
#line 8558 "texprof.w"
;
if(cur_tok<right_brace_limit)
if(cur_tok<left_brace_limit)incr(unbalance);
else{decr(unbalance);
if(unbalance==0)goto done1;
}
}
done1:rbrace_ptr= p;store_new_token(cur_tok);
}

/*:398*/
#line 8448 "texprof.w"

else/*394:*/
#line 8478 "texprof.w"

{back_input();print_err("Argument of ");sprint_cs(warning_index);

print(" has an extra }");
help6("I've run across a `}' that doesn't seem to match anything.",
"For example, `\\def\\a#1{...}' and `\\a}' would produce",
"this error. If you simply proceed now, the `\\par' that",
"I've just inserted will cause me to report a runaway",
"argument that might be the root of the problem. But if",
"your `}' was spurious, just type `2' and it will go away.");
incr(align_state);long_state= call;cur_tok= par_token;ins_error();
goto resume;
}

/*:394*/
#line 8449 "texprof.w"

else/*392:*/
#line 8457 "texprof.w"

{if(cur_tok==space_token)
if(info(r)<=end_match_token)
if(info(r)>=match_token)goto resume;
store_new_token(cur_tok);
}

/*:392*/
#line 8451 "texprof.w"
;
incr(m);
if(info(r)> end_match_token)goto resume;
if(info(r)<match_token)goto resume;
found:if(s!=null)/*399:*/
#line 8571 "texprof.w"

{if((m==1)&&(info(p)<right_brace_limit))
{link(rbrace_ptr)= null;free_avail(p);
p= link(temp_head);pstack[n]= link(p);free_avail(p);
}
else pstack[n]= link(temp_head);
incr(n);
if(tracing_macros> 0)
{begin_diagnostic();print_nl("");printn(match_chr);print_int(n);
print("<-");show_token_list(pstack[n-1],null,1000);
end_diagnostic(false);
}
}

/*:399*/
#line 8455 "texprof.w"


/*:391*/
#line 8427 "texprof.w"
;

}while(!(info(r)==end_match_token));
}

/*:390*/
#line 8382 "texprof.w"
;
/*389:*/
#line 8392 "texprof.w"

while((state==token_list)&&(loc==null)&&(token_type!=v_template))
end_token_list();
begin_token_list(ref_count,macro);name= warning_index;loc= link(r);
if(n> 0)
{if(param_ptr+n> max_param_stack)
{max_param_stack= param_ptr+n;
if(max_param_stack> param_size)
overflow("parameter stack size",param_size);

}
for(m= 0;m<=n-1;m++)param_stack[param_ptr+m]= pstack[m];
param_ptr= param_ptr+n;
}

/*:389*/
#line 8383 "texprof.w"
;
end:scanner_status= save_scanner_status;warning_index= save_warning_index;
/*1775:*/
#line 31573 "texprof.w"

macro_depth++;
cur_depth= macro_depth;
if(macro_depth>=MAX_MACRO_STACK)
overflow("macro stack size",macro_depth);
macro_stack[macro_depth]= CALL_INFO(macro_depth,macro_cs,macro_fl);
if(macro_depth<=unchanged_depth)
unchanged_depth= macro_depth-1;

/*:1775*/
#line 8385 "texprof.w"

}

/*:388*/
#line 8037 "texprof.w"

/*378:*/
#line 8214 "texprof.w"

static void insert_relax(void)
{cur_tok= cs_token_flag+cur_cs;back_input();
cur_tok= cs_token_flag+frozen_relax;back_input();token_type= inserted;
}

/*:378*/
#line 8038 "texprof.w"

/*1434:*/
#line 26482 "texprof.w"

static void pseudo_start(void);

/*:1434*//*1492:*/
#line 27357 "texprof.w"

static void scan_register_num(void);

/*:1492*//*1497:*/
#line 27431 "texprof.w"

static void new_index(quarterword i,pointer q)
{int k;
cur_ptr= get_node(index_node_size);sa_index(cur_ptr)= i;
sa_used(cur_ptr)= 0;link(cur_ptr)= q;
for(k= 1;k<=index_node_size-1;k++)
mem[cur_ptr+k]= sa_null;
}

/*:1497*//*1501:*/
#line 27491 "texprof.w"

static void find_sa_element(small_number t,halfword n,bool w)

{
pointer q;
small_number i;
cur_ptr= sa_root[t];
if_cur_ptr_is_null_then_return_or_goto(not_found);
q= cur_ptr;i= hex_dig1(n);get_sa_ptr;
if_cur_ptr_is_null_then_return_or_goto(not_found1);
q= cur_ptr;i= hex_dig2(n);get_sa_ptr;
if_cur_ptr_is_null_then_return_or_goto(not_found2);
q= cur_ptr;i= hex_dig3(n);get_sa_ptr;
if_cur_ptr_is_null_then_return_or_goto(not_found3);
q= cur_ptr;i= hex_dig4(n);get_sa_ptr;
if((cur_ptr==null)&&w)goto not_found4;
return;
not_found:new_index(t,null);
sa_root[t]= cur_ptr;q= cur_ptr;i= hex_dig1(n);
not_found1:new_index(i,q);
add_sa_ptr;q= cur_ptr;i= hex_dig2(n);
not_found2:new_index(i,q);
add_sa_ptr;q= cur_ptr;i= hex_dig3(n);
not_found3:new_index(i,q);
add_sa_ptr;q= cur_ptr;i= hex_dig4(n);
not_found4:/*1502:*/
#line 27556 "texprof.w"

if(t==mark_val)
{cur_ptr= get_node(mark_class_node_size);
mem[cur_ptr+1]= sa_null;mem[cur_ptr+2]= sa_null;mem[cur_ptr+3]= sa_null;
}
else{if(t<=dimen_val)
{cur_ptr= get_node(word_node_size);sa_int(cur_ptr)= 0;
sa_num(cur_ptr)= n;
}
else{cur_ptr= get_node(pointer_node_size);
if(t<=mu_val)
{sa_ptr(cur_ptr)= zero_glue;add_glue_ref(zero_glue);
}
else sa_ptr(cur_ptr)= null;
}
sa_ref(cur_ptr)= null;
}
sa_index(cur_ptr)= 16*t+i;sa_lev(cur_ptr)= level_one

/*:1502*/
#line 27516 "texprof.w"
;
link(cur_ptr)= q;add_sa_ptr;
}

/*:1501*/
#line 8039 "texprof.w"

static void pass_text(void);
static void start_input(void);
static void conditional(void);
static void get_x_token(void);
static void conv_toks(void);
static void ins_the_toks(void);
static void expand(void)
{
halfword t;
pointer p,q,r;
int j;
int cv_backup;
small_number cvl_backup,radix_backup,co_backup;

pointer backup_backup;
small_number save_scanner_status;
cv_backup= cur_val;cvl_backup= cur_val_level;radix_backup= radix;
co_backup= cur_order;backup_backup= link(backup_head);
reswitch:
if(cur_cmd<call)/*366:*/
#line 8066 "texprof.w"

{if(tracing_commands> 1)show_cur_cmd_chr();
switch(cur_cmd){
case top_bot_mark:/*385:*/
#line 8311 "texprof.w"

{t= cur_chr%marks_code;
if(cur_chr>=marks_code)scan_register_num();else cur_val= 0;
if(cur_val==0)cur_ptr= cur_mark[t];
else/*1506:*/
#line 27676 "texprof.w"

{find_sa_element(mark_val,cur_val,false);
if(cur_ptr!=null)
if(odd(t))cur_ptr= link(cur_ptr+(t/2)+1);
else cur_ptr= info(cur_ptr+(t/2)+1);
}

/*:1506*/
#line 8315 "texprof.w"
;
if(cur_ptr!=null)begin_token_list(cur_ptr,mark_text);
}

/*:385*/
#line 8069 "texprof.w"
break;
case expand_after:switch(cur_chr){
case 0:/*367:*/
#line 8088 "texprof.w"

{get_token();t= cur_tok;get_token();
if(cur_cmd> max_command)expand();else back_input();
cur_tok= t;back_input();
}

/*:367*/
#line 8071 "texprof.w"
break;
case 1:/*1447:*/
#line 26636 "texprof.w"

{get_token();
if((cur_cmd==if_test)&&(cur_chr!=if_case_code))
{cur_chr= cur_chr+unless_code;goto reswitch;
}
print_err("You can't use `");print_esc("unless");print("' before `");

print_cmd_chr(cur_cmd,cur_chr);print_char('\'');
help1("Continue, and I'll forget that it ever happened.");
back_error();
}

/*:1447*/
#line 8072 "texprof.w"
break;
/*1586:*/
#line 28628 "texprof.w"

case primitive_code:{get_token();
set_ROM_p_from_cs(cur_cs);
if((p!=ROM_undefined_primitive)&&(ROM_type(p)!=undefined_cs)){
eqtb[frozen_primitive]= ROM[p];
text(frozen_primitive)= text(cur_cs);
cur_tok= cs_token_flag+frozen_primitive;
}
back_input();
}break;

/*:1586*//*1590:*/
#line 28653 "texprof.w"

case expanded_code:{scan_general_x_text();
back_list(link(link(garbage)));
free_avail(link(garbage));
}

/*:1590*/
#line 8073 "texprof.w"

}break;
case no_expand:/*368:*/
#line 8102 "texprof.w"

{save_scanner_status= scanner_status;scanner_status= normal;
get_token();scanner_status= save_scanner_status;t= cur_tok;
back_input();
if(t>=cs_token_flag)
{p= get_avail();info(p)= cs_token_flag+frozen_dont_expand;
link(p)= loc;start= p;loc= p;
}
}

/*:368*/
#line 8075 "texprof.w"
break;
case cs_name:/*371:*/
#line 8138 "texprof.w"

{r= get_avail();p= r;
incr(incsname_state);
do{get_x_token();
if(cur_cs==0)store_new_token(cur_tok);
}while(!(cur_cs!=0));
if(cur_cmd!=end_cs_name)/*372:*/
#line 8154 "texprof.w"

{print_err("Missing ");print_esc("endcsname");print(" inserted");

help2("The control sequence marked <to be read again> should",
"not appear between \\csname and \\endcsname.");
back_error();
}

/*:372*/
#line 8144 "texprof.w"
;
decr(incsname_state);
/*373:*/
#line 8162 "texprof.w"

j= first;p= link(r);
while(p!=null)
{if(j>=max_buf_stack)
{max_buf_stack= j+1;
if(max_buf_stack==buf_size)
overflow("buffer size",buf_size);

}
buffer[j]= info(p)%0400;incr(j);p= link(p);
}
if(j==first)cur_cs= null_cs;
else if(j> first+1)
{no_new_control_sequence= false;cur_cs= id_lookup(first,j-first);
no_new_control_sequence= true;
}
else cur_cs= single_base+buffer[first]

/*:373*/
#line 8146 "texprof.w"
;
flush_list(r);
if(eq_type(cur_cs)==undefined_cs)
{eq_define(cur_cs,relax,256);
}
cur_tok= cur_cs+cs_token_flag;back_input();
}

/*:371*/
#line 8076 "texprof.w"
break;
case convert:conv_toks();break;
case the:ins_the_toks();break;
case if_test:conditional();break;
case fi_or_else:/*509:*/
#line 10411 "texprof.w"

{if(tracing_ifs> 0)if(tracing_commands<=1)show_cur_cmd_chr();
if(cur_chr> if_limit)
if(if_limit==if_code)insert_relax();
else{print_err("Extra ");print_cmd_chr(fi_or_else,cur_chr);



help1("I'm ignoring this; it doesn't match any \\if.");
error();
}
else{while(cur_chr!=fi_code)pass_text();
/*495:*/
#line 10195 "texprof.w"

{if(if_stack[in_open]==cond_ptr)if_warning();

p= cond_ptr;if_line= if_line_field(p);
cur_if= subtype(p);if_limit= type(p);cond_ptr= link(p);
free_node(p,if_node_size);
}

/*:495*/
#line 10423 "texprof.w"
;
}
}

/*:509*/
#line 8080 "texprof.w"
break;
case input:/*377:*/
#line 8205 "texprof.w"

if(cur_chr==1)force_eof= true
/*1431:*/
#line 26465 "texprof.w"
;
else if(cur_chr==2)pseudo_start()

/*:1431*/
#line 8207 "texprof.w"
;
else if(name_in_progress)insert_relax();
else start_input()

/*:377*/
#line 8081 "texprof.w"
;break;
default:/*369:*/
#line 8112 "texprof.w"

{print_err("Undefined control sequence");

help5("The control sequence at the end of the top line",
"of your error message was never \\def'ed. If you have",
"misspelled it (e.g., `\\hobx'), type `I' and the correct",
"spelling (e.g., `I\\hbox'). Otherwise just continue,",
"and I'll forget about whatever was undefined.");
error();
}

/*:369*/
#line 8082 "texprof.w"

}
}

/*:366*/
#line 8059 "texprof.w"

else if(cur_cmd<end_template)macro_call();
else/*374:*/
#line 8186 "texprof.w"

{cur_tok= cs_token_flag+frozen_endv;back_input();
}

/*:374*/
#line 8061 "texprof.w"
;
cur_val= cv_backup;cur_val_level= cvl_backup;radix= radix_backup;
cur_order= co_backup;link(backup_head)= backup_backup;
}

/*:365*//*379:*/
#line 8224 "texprof.w"
static void get_x_token(void)

{
restart:get_next();

if(cur_cmd<=max_command)goto done;
if(cur_cmd>=call)
if(cur_cmd<end_template)macro_call();
else{cur_cs= frozen_endv;cur_cmd= endv;
goto done;
}
else expand();
goto restart;
done:if(cur_cs==0)cur_tok= (cur_cmd*0400)+cur_chr;
else cur_tok= cs_token_flag+cur_cs;
}

/*:379*//*380:*/
#line 8244 "texprof.w"
static void x_token(void)
{while(cur_cmd> max_command)
{expand();
get_next();
}
if(cur_cs==0)cur_tok= (cur_cmd*0400)+cur_chr;
else cur_tok= cs_token_flag+cur_cs;
}

/*:380*//*402:*/
#line 8603 "texprof.w"
static void scan_left_brace(void)
{/*403:*/
#line 8617 "texprof.w"

do{get_x_token();
}while(!((cur_cmd!=spacer)&&(cur_cmd!=relax)))

/*:403*/
#line 8604 "texprof.w"
;
if(cur_cmd!=left_brace)
{print_err("Missing { inserted");

help4("A left brace was mandatory here, so I've put one in.",
"You might want to delete and/or insert some corrections",
"so that I will find a matching right brace soon.",
"(If you're confused by all this, try typing `I}' now.)");
back_error();cur_tok= left_brace_token+'{';cur_cmd= left_brace;
cur_chr= '{';incr(align_state);
}
}

/*:402*//*404:*/
#line 8624 "texprof.w"
static void scan_optional_equals(void)
{/*405:*/
#line 8629 "texprof.w"

do{get_x_token();
}while(!(cur_cmd!=spacer))

/*:405*/
#line 8625 "texprof.w"
;
if(cur_tok!=other_token+'=')back_input();
}

/*:404*//*406:*/
#line 8648 "texprof.w"
static bool scan_keyword(char*s)
{
pointer p;
pointer q;
p= backup_head;link(p)= null;
while(*s!=0)
{get_x_token();

if((cur_cs==0)&&
((cur_chr==so(*s))||(cur_chr==so(*s)-'a'+'A')))
{store_new_token(cur_tok);incr(s);
}
else if((cur_cmd!=spacer)||(p!=backup_head))
{back_input();
if(p!=backup_head)back_list(link(backup_head));
return false;
}
}
flush_list(link(backup_head));return true;
}

/*:406*//*407:*/
#line 8672 "texprof.w"
static void mu_error(void)
{print_err("Incompatible glue units");

help1("I'm going to assume that 1mu=1pt when they're mixed.");
error();
}

/*:407*//*408:*/
#line 8689 "texprof.w"
static void scan_int(void);
/*432:*/
#line 9092 "texprof.w"

static void scan_eight_bit_int(void)
{scan_int();
if((cur_val<0)||(cur_val> 255))
{print_err("Bad register code");

help2("A register number must be between 0 and 255.",
"I changed this one to zero.");int_error(cur_val);cur_val= 0;
}
}

/*:432*//*433:*/
#line 9103 "texprof.w"

static void scan_char_num(void)
{scan_int();
if((cur_val<0)||(cur_val> 255))
{print_err("Bad character code");

help2("A character number must be between 0 and 255.",
"I changed this one to zero.");int_error(cur_val);cur_val= 0;
}
}

/*:433*//*434:*/
#line 9117 "texprof.w"

static void scan_four_bit_int(void)
{scan_int();
if((cur_val<0)||(cur_val> 15))
{print_err("Bad number");

help2("Since I expected to read a number between 0 and 15,",
"I changed this one to zero.");int_error(cur_val);cur_val= 0;
}
}

/*:434*//*435:*/
#line 9128 "texprof.w"

static void scan_fifteen_bit_int(void)
{scan_int();
if((cur_val<0)||(cur_val> 077777))
{print_err("Bad mathchar");

help2("A mathchar number must be between 0 and 32767.",
"I changed this one to zero.");int_error(cur_val);cur_val= 0;
}
}

/*:435*//*436:*/
#line 9139 "texprof.w"

static void scan_twenty_seven_bit_int(void)
{scan_int();
if((cur_val<0)||(cur_val> 0777777777))
{print_err("Bad delimiter code");

help2("A numeric delimiter code must be between 0 and 2^{27}-1.",
"I changed this one to zero.");int_error(cur_val);cur_val= 0;
}
}

/*:436*//*1493:*/
#line 27360 "texprof.w"

static void scan_register_num(void)
{scan_int();
if((cur_val<0)||(cur_val> max_reg_num))
{print_err("Bad register code");

help2(max_reg_help_line,"I changed this one to zero.");
int_error(cur_val);cur_val= 0;
}
}

/*:1493*/
#line 8690 "texprof.w"

/*1412:*/
#line 26308 "texprof.w"

static void scan_general_text(void);

/*:1412*//*1454:*/
#line 26718 "texprof.w"

static void get_x_or_protected(void)

{
loop{get_token();
if(cur_cmd<=max_command)return;
if((cur_cmd>=call)&&(cur_cmd<end_template))
if(info(link(cur_chr))==protected_token)return;
expand();
}
}

/*:1454*//*1463:*/
#line 26895 "texprof.w"

static void scan_expr(void);

/*:1463*//*1468:*/
#line 26987 "texprof.w"

static void scan_normal_glue(void);
static void scan_mu_glue(void);

/*:1468*/
#line 8691 "texprof.w"

/*576:*/
#line 11758 "texprof.w"

static void scan_font_ident(void)
{internal_font_number f;
halfword m;
/*405:*/
#line 8629 "texprof.w"

do{get_x_token();
}while(!(cur_cmd!=spacer))

/*:405*/
#line 11762 "texprof.w"
;
if(cur_cmd==def_font)f= cur_font;
else if(cur_cmd==set_font)f= cur_chr;
else if(cur_cmd==def_family)
{m= cur_chr;scan_four_bit_int();f= equiv(m+cur_val);
}
else{print_err("Missing font identifier");

help2("I was looking for a control sequence whose",
"current meaning has been defined by \\font.");
back_error();f= null_font;
}
cur_val= f;
}

/*:576*//*577:*/
#line 11781 "texprof.w"

static void find_font_dimen(bool writing)

{internal_font_number f;
int n;
scan_int();n= cur_val;scan_font_ident();f= cur_val;
if(n<=0)cur_val= fmem_ptr;
else{if(writing&&(n<=space_shrink_code)&&
(n>=space_code)&&(font_glue[f]!=null))
{delete_glue_ref(font_glue[f]);
font_glue[f]= null;
}
if(n> font_params[f])
if(f<font_ptr)cur_val= fmem_ptr;
else/*579:*/
#line 11812 "texprof.w"

{do{if(fmem_ptr==font_mem_size)
overflow("font memory",font_mem_size);

font_info[fmem_ptr].sc= 0;incr(fmem_ptr);incr(font_params[f]);
}while(!(n==font_params[f]));
cur_val= fmem_ptr-1;
}

/*:579*/
#line 11795 "texprof.w"

else cur_val= n+param_base[f];
}
/*578:*/
#line 11801 "texprof.w"

if(cur_val==fmem_ptr)
{print_err("Font ");printn_esc(font_id_text(f));
print(" has only ");print_int(font_params[f]);
print(" fontdimen parameters");

help2("To increase the number of font parameters, you must",
"use \\fontdimen immediately after the \\font is loaded.");
error();
}

/*:578*/
#line 11798 "texprof.w"
;
}

/*:577*/
#line 8692 "texprof.w"


/*:408*//*412:*/
#line 8760 "texprof.w"
static void scan_something_internal(small_number level,bool negative)

{
halfword m;
pointer q,r;
pointer tx;
four_quarters i;
int p;
m= cur_chr;
switch(cur_cmd){
case def_code:/*413:*/
#line 8795 "texprof.w"

{scan_char_num();
if(m==math_code_base)scanned_result(ho(math_code(cur_val)),int_val)
else if(m<math_code_base)scanned_result(equiv(m+cur_val),int_val)
else scanned_result(eqtb[m+cur_val].i,int_val);
}

/*:413*/
#line 8770 "texprof.w"
break;
case toks_register:case assign_toks:
case def_family:case set_font:case def_font:/*414:*/
#line 8802 "texprof.w"

if(level!=tok_val)
{print_err("Missing number, treated as zero");

help3("A number should have been here; I inserted `0'.",
"(If you can't figure out why I needed to see a number,",
"look up `weird error' in the index to The TeXbook.)");

back_error();scanned_result(0,dimen_val);
}
else if(cur_cmd<=assign_toks)
{if(cur_cmd<assign_toks)
if(m==mem_bot)
{scan_register_num();
if(cur_val<256)cur_val= equiv(toks_base+cur_val);
else{find_sa_element(tok_val,cur_val,false);
if(cur_ptr==null)cur_val= null;
else cur_val= sa_ptr(cur_ptr);
}
}
else cur_val= sa_ptr(m);
else cur_val= equiv(m);
cur_val_level= tok_val;
}
else{back_input();scan_font_ident();
scanned_result(font_id_base+cur_val,ident_val);
}

/*:414*/
#line 8773 "texprof.w"
break;
case assign_int:scanned_result(eqtb[m].i,int_val)break;
case assign_dimen:scanned_result(eqtb[m].sc,dimen_val)break;
case assign_glue:scanned_result(equiv(m),glue_val)break;
case assign_mu_glue:scanned_result(equiv(m),mu_val)break;
case set_aux:/*417:*/
#line 8896 "texprof.w"

if(abs(mode)!=m)
{print_err("Improper ");print_cmd_chr(set_aux,m);


help4("You can refer to \\spacefactor only in horizontal mode;",
"you can refer to \\prevdepth only in vertical mode; and",
"neither of these is meaningful inside \\write. So",
"I'm forgetting what you said and using zero instead.");
error();
if(level!=tok_val)scanned_result(0,dimen_val)
else scanned_result(0,int_val);
}
else if(m==vmode)scanned_result(prev_depth,dimen_val)
else scanned_result(space_factor,int_val)

/*:417*/
#line 8778 "texprof.w"
break;
case set_prev_graf:/*421:*/
#line 8937 "texprof.w"

if(mode==0)scanned_result(0,int_val)
else{nest[nest_ptr]= cur_list;p= nest_ptr;
while(abs(nest[p].mode_field)!=vmode)decr(p);
scanned_result(nest[p].pg_field,int_val);
}

/*:421*/
#line 8779 "texprof.w"
break;
case set_page_int:/*418:*/
#line 8912 "texprof.w"

{if(m==0)cur_val= dead_cycles
/*1424:*/
#line 26426 "texprof.w"
;
else if(m==2)cur_val= interaction

/*:1424*/
#line 8914 "texprof.w"
;
else cur_val= insert_penalties;
cur_val_level= int_val;
}

/*:418*/
#line 8780 "texprof.w"
break;
case set_page_dimen:/*420:*/
#line 8930 "texprof.w"

{if((page_contents==empty)&&(!output_active))
if(m==0)cur_val= max_dimen;else cur_val= 0;
else cur_val= page_so_far[m];
cur_val_level= dimen_val;
}

/*:420*/
#line 8781 "texprof.w"
break;
case set_shape:/*422:*/
#line 8944 "texprof.w"

{if(m> par_shape_loc)/*1536:*/
#line 28150 "texprof.w"

{scan_int();
if((equiv(m)==null)||(cur_val<0))cur_val= 0;
else{if(cur_val> penalty(equiv(m)))cur_val= penalty(equiv(m));
cur_val= penalty(equiv(m)+cur_val);
}
}

/*:1536*/
#line 8945 "texprof.w"

else if(par_shape_ptr==null)cur_val= 0;
else cur_val= info(par_shape_ptr);
cur_val_level= int_val;
}

/*:422*/
#line 8782 "texprof.w"
break;
case set_box_dimen:/*419:*/
#line 8919 "texprof.w"

{scan_register_num();fetch_box(q);
if(q==null)cur_val= 0;else cur_val= mem[q+m].sc;
cur_val_level= dimen_val;
}

/*:419*/
#line 8783 "texprof.w"
break;
case char_given:case math_given:scanned_result(cur_chr,int_val)break;
case assign_font_dimen:/*424:*/
#line 9009 "texprof.w"

{find_font_dimen(false);font_info[fmem_ptr].sc= 0;
scanned_result(font_info[cur_val].sc,dimen_val);
}

/*:424*/
#line 8785 "texprof.w"
break;
case assign_font_int:/*425:*/
#line 9014 "texprof.w"

{scan_font_ident();
if(m==0)scanned_result(hyphen_char[cur_val],int_val)
else scanned_result(skew_char[cur_val],int_val);
}

/*:425*/
#line 8786 "texprof.w"
break;
case internal_register:/*426:*/
#line 9020 "texprof.w"

{if((m<mem_bot)||(m> lo_mem_stat_max))
{cur_val_level= sa_type(m);
if(cur_val_level<glue_val)cur_val= sa_int(m);
else cur_val= sa_ptr(m);
}
else{scan_register_num();cur_val_level= m-mem_bot;
if(cur_val> 255)
{find_sa_element(cur_val_level,cur_val,false);
if(cur_ptr==null)
if(cur_val_level<glue_val)cur_val= 0;
else cur_val= zero_glue;
else if(cur_val_level<glue_val)cur_val= sa_int(cur_ptr);
else cur_val= sa_ptr(cur_ptr);
}
else
switch(cur_val_level){
case int_val:cur_val= count(cur_val);break;
case dimen_val:cur_val= dimen(cur_val);break;
case glue_val:cur_val= skip(cur_val);break;
case mu_val:cur_val= mu_skip(cur_val);
}
}
}

/*:426*/
#line 8787 "texprof.w"
break;
case last_item:/*423:*/
#line 8958 "texprof.w"

if(m> eTeX_last_last_item_cmd_mod)
{switch(m){
/*1555:*/
#line 28309 "texprof.w"

case Prote_version_code:cur_val= Prote_version;break;

/*:1555*//*1570:*/
#line 28445 "texprof.w"

case shell_escape_code:cur_val= 0;break;

/*:1570*//*1606:*/
#line 28810 "texprof.w"

case elapsed_time_code:
{double t= (start_sec*1.0+start_nsec/1000000000.0-reset_timer)*0x10000;
if(t>=infinity)cur_val= infinity;
else cur_val= (scaled)t;
break;
}

/*:1606*//*1646:*/
#line 29329 "texprof.w"

case random_seed_code:cur_val= random_seed;break;

/*:1646*//*1673:*/
#line 29632 "texprof.w"

case last_xpos_code:cur_val= last_saved_xpos;break;
case last_ypos_code:cur_val= last_saved_ypos;

/*:1673*/
#line 8961 "texprof.w"

}
cur_val_level= int_val;
}
else if(m>=input_line_no_code)
{if(m>=eTeX_glue)/*1462:*/
#line 26864 "texprof.w"

{if(m<eTeX_mu)
{switch(m){
/*1489:*/
#line 27312 "texprof.w"

case mu_to_glue_code:scan_mu_glue();

/*:1489*/
#line 26867 "texprof.w"

}
cur_val_level= glue_val;
}
else if(m<eTeX_expr)
{switch(m){
/*1490:*/
#line 27315 "texprof.w"

case glue_to_mu_code:scan_normal_glue();

/*:1490*/
#line 26873 "texprof.w"

}
cur_val_level= mu_val;
}
else{cur_val_level= m-eTeX_expr+int_val;scan_expr();
}
while(cur_val_level> level)
{if(cur_val_level==glue_val)
{m= cur_val;cur_val= width(m);delete_glue_ref(m);
}
else if(cur_val_level==mu_val)mu_error();
decr(cur_val_level);
}
if(negative)
if(cur_val_level>=glue_val)
{m= cur_val;cur_val= new_spec(m);delete_glue_ref(m);
/*430:*/
#line 9081 "texprof.w"

{negate(width(cur_val));
negate(stretch(cur_val));
negate(shrink(cur_val));
}

/*:430*/
#line 26889 "texprof.w"
;
}
else negate(cur_val);
return;
}

/*:1462*/
#line 8966 "texprof.w"

else if(m>=eTeX_dim)
{switch(m){
/*1401:*/
#line 26119 "texprof.w"

case font_char_wd_code:
case font_char_ht_code:
case font_char_dp_code:
case font_char_ic_code:{scan_font_ident();q= cur_val;scan_char_num();
if((font_bc[q]<=cur_val)&&(font_ec[q]>=cur_val))
{i= char_info(q,qi(cur_val));
switch(m){
case font_char_wd_code:cur_val= char_width(q,i);break;
case font_char_ht_code:cur_val= char_height(q,height_depth(i));break;
case font_char_dp_code:cur_val= char_depth(q,height_depth(i));break;
case font_char_ic_code:cur_val= char_italic(q,i);
}
}
else cur_val= 0;
}break;

/*:1401*//*1404:*/
#line 26157 "texprof.w"

case par_shape_length_code:
case par_shape_indent_code:
case par_shape_dimen_code:{q= cur_chr-par_shape_length_code;scan_int();
if((par_shape_ptr==null)||(cur_val<=0))cur_val= 0;
else{if(q==2)
{q= cur_val%2;cur_val= (cur_val+q)/2;
}
if(cur_val> info(par_shape_ptr))cur_val= info(par_shape_ptr);
cur_val= mem[par_shape_ptr+2*cur_val-q].sc;
}
cur_val_level= dimen_val;
}break;

/*:1404*//*1486:*/
#line 27287 "texprof.w"

case glue_stretch_code:case glue_shrink_code:
{scan_normal_glue();q= cur_val;
if(m==glue_stretch_code)cur_val= stretch(q);
else cur_val= shrink(q);
delete_glue_ref(q);
}

/*:1486*/
#line 8969 "texprof.w"

}
cur_val_level= dimen_val;
}
else
{switch(m){
case input_line_no_code:cur_val= line;break;
case badness_code:cur_val= last_badness;break;
/*1381:*/
#line 25903 "texprof.w"

case eTeX_version_code:cur_val= eTeX_version;break;

/*:1381*//*1395:*/
#line 26055 "texprof.w"

case current_group_level_code:cur_val= cur_level-level_one;break;
case current_group_type_code:cur_val= cur_group;break;

/*:1395*//*1398:*/
#line 26080 "texprof.w"

case current_if_level_code:{q= cond_ptr;cur_val= 0;
while(q!=null)
{incr(cur_val);q= link(q);
}
}break;
case current_if_type_code:if(cond_ptr==null)cur_val= 0;
else if(cur_if<unless_code)cur_val= cur_if+1;
else cur_val= -(cur_if-unless_code+1);break;
case current_if_branch_code:
if((if_limit==or_code)||(if_limit==else_code))cur_val= 1;
else if(if_limit==fi_code)cur_val= -1;
else cur_val= 0;break;

/*:1398*//*1485:*/
#line 27279 "texprof.w"

case glue_stretch_order_code:case glue_shrink_order_code:
{scan_normal_glue();q= cur_val;
if(m==glue_stretch_order_code)cur_val= stretch_order(q);
else cur_val= shrink_order(q);
delete_glue_ref(q);
}

/*:1485*//*1802:*/
#line 32163 "texprof.w"

case pdftex_version_code:cur_val= pdftex_version;break;
case pdf_last_obj_code:cur_val= pdf_last_obj;break;
case pdf_last_xform_code:cur_val= pdf_last_xform;break;
case pdf_last_ximage_code:cur_val= pdf_last_ximage;break;
case pdf_last_ximage_pages_code:cur_val= pdf_last_ximage_pages;break;
case pdf_last_annot_code:cur_val= pdf_last_annot;break;
case pdf_retval_code:cur_val= pdf_retval;break;
case pdf_last_ximage_colordepth_code:cur_val= pdf_last_ximage_colordepth;break;
case pdf_last_link_code:cur_val= pdf_last_link;break;


/*:1802*/
#line 8977 "texprof.w"

}
cur_val_level= int_val;
}
}
else{if(cur_chr==glue_val)cur_val= zero_glue;else cur_val= 0;
tx= tail;
if(cur_chr==last_node_type_code)
{cur_val_level= int_val;
if((tx==head)||(mode==0))cur_val= -1;
}
else cur_val_level= cur_chr;
if(!is_char_node(tx)&&(mode!=0))
switch(cur_chr){
case int_val:if(type(tx)==penalty_node)cur_val= penalty(tx);break;
case dimen_val:if(type(tx)==kern_node)cur_val= width(tx);break;
case glue_val:if(type(tx)==glue_node)
{cur_val= glue_ptr(tx);
if(subtype(tx)==mu_glue)cur_val_level= mu_val;
}break;
case last_node_type_code:if(type(tx)<=unset_node)cur_val= type(tx)+1;
else cur_val= unset_node+2;
}
else if((mode==vmode)&&(tx==head))
switch(cur_chr){
case int_val:cur_val= last_penalty;break;
case dimen_val:cur_val= last_kern;break;
case glue_val:if(last_glue!=max_halfword)cur_val= last_glue;break;
case last_node_type_code:cur_val= last_node_type;
}
}

/*:423*/
#line 8788 "texprof.w"
break;
default:/*427:*/
#line 9045 "texprof.w"

{print_err("You can't use `");print_cmd_chr(cur_cmd,cur_chr);

print("' after ");print_esc("the");
help1("I'm forgetting what you said and using zero instead.");
error();
if(level!=tok_val)scanned_result(0,dimen_val)
else scanned_result(0,int_val);
}

/*:427*/
#line 8789 "texprof.w"

}
while(cur_val_level> level)/*428:*/
#line 9061 "texprof.w"

{if(cur_val_level==glue_val)cur_val= width(cur_val);
else if(cur_val_level==mu_val)mu_error();
decr(cur_val_level);
}

/*:428*/
#line 8791 "texprof.w"
;
/*429:*/
#line 9071 "texprof.w"

if(negative)
if(cur_val_level>=glue_val)
{cur_val= new_spec(cur_val);
/*430:*/
#line 9081 "texprof.w"

{negate(width(cur_val));
negate(stretch(cur_val));
negate(shrink(cur_val));
}

/*:430*/
#line 9075 "texprof.w"
;
}
else negate(cur_val);
else if((cur_val_level>=glue_val)&&(cur_val_level<=mu_val))
add_glue_ref(cur_val)

/*:429*/
#line 8792 "texprof.w"
;
}

/*:412*//*439:*/
#line 9182 "texprof.w"
static void scan_int(void)
{
bool negative;
int m;
small_number d;
bool vacuous;
bool OK_so_far;
radix= 0;OK_so_far= true;
/*440:*/
#line 9198 "texprof.w"

negative= false;
do{/*405:*/
#line 8629 "texprof.w"

do{get_x_token();
}while(!(cur_cmd!=spacer))

/*:405*/
#line 9200 "texprof.w"
;
if(cur_tok==other_token+'-')
{negative= !negative;cur_tok= other_token+'+';
}
}while(!(cur_tok!=other_token+'+'))

/*:440*/
#line 9190 "texprof.w"
;
if(cur_tok==alpha_token)/*441:*/
#line 9209 "texprof.w"

{get_token();
if(cur_tok<cs_token_flag)
{cur_val= cur_chr;
if(cur_cmd<=right_brace)
if(cur_cmd==right_brace)incr(align_state);
else decr(align_state);
}
else if(cur_tok<cs_token_flag+single_base)
cur_val= cur_tok-cs_token_flag-active_base;
else cur_val= cur_tok-cs_token_flag-single_base;
if(cur_val> 255)
{print_err("Improper alphabetic constant");

help2("A one-character control sequence belongs after a ` mark.",
"So I'm essentially inserting \\0 here.");
cur_val= '0';back_error();
}
else/*442:*/
#line 9230 "texprof.w"

{get_x_token();if(cur_cmd!=spacer)back_input();
}

/*:442*/
#line 9227 "texprof.w"
;
}

/*:441*/
#line 9191 "texprof.w"

else if((cur_cmd>=min_internal)&&(cur_cmd<=max_internal))
scan_something_internal(int_val,false);
else/*443:*/
#line 9234 "texprof.w"

{radix= 10;m= 214748364;
if(cur_tok==octal_token)
{radix= 8;m= 02000000000;get_x_token();
}
else if(cur_tok==hex_token)
{radix= 16;m= 01000000000;get_x_token();
}
vacuous= true;cur_val= 0;
/*444:*/
#line 9253 "texprof.w"

loop{if((cur_tok<zero_token+radix)&&(cur_tok>=zero_token)&&
(cur_tok<=zero_token+9))d= cur_tok-zero_token;
else if(radix==16)
if((cur_tok<=A_token+5)&&(cur_tok>=A_token))d= cur_tok-A_token+10;
else if((cur_tok<=other_A_token+5)&&(cur_tok>=other_A_token))
d= cur_tok-other_A_token+10;
else goto done;
else goto done;
vacuous= false;
if((cur_val>=m)&&((cur_val> m)||(d> 7)||(radix!=10)))
{if(OK_so_far)
{print_err("Number too big");

help2("I can only go up to 2147483647='17777777777=\"7FFFFFFF,",
"so I'm using that number instead of yours.");
error();cur_val= infinity;OK_so_far= false;
}
}
else cur_val= cur_val*radix+d;
get_x_token();
}
done:

/*:444*/
#line 9243 "texprof.w"
;
if(vacuous)/*445:*/
#line 9277 "texprof.w"

{print_err("Missing number, treated as zero");

help3("A number should have been here; I inserted `0'.",
"(If you can't figure out why I needed to see a number,",
"look up `weird error' in the index to The TeXbook.)");

back_error();
}

/*:445*/
#line 9244 "texprof.w"

else if(cur_cmd!=spacer)back_input();
}

/*:443*/
#line 9194 "texprof.w"
;
if(negative)negate(cur_val);
}

/*:439*//*447:*/
#line 9316 "texprof.w"
static void scan_dimen(bool mu,bool inf,bool shortcut)

{
bool negative;
int f;
/*449:*/
#line 9359 "texprof.w"

int num,denom;
int k,kk;
pointer p,q;
scaled v;
int save_cur_val;

/*:449*/
#line 9321 "texprof.w"

f= 0;arith_error= false;cur_order= normal;negative= false;
if(!shortcut)
{/*440:*/
#line 9198 "texprof.w"

negative= false;
do{/*405:*/
#line 8629 "texprof.w"

do{get_x_token();
}while(!(cur_cmd!=spacer))

/*:405*/
#line 9200 "texprof.w"
;
if(cur_tok==other_token+'-')
{negative= !negative;cur_tok= other_token+'+';
}
}while(!(cur_tok!=other_token+'+'))

/*:440*/
#line 9324 "texprof.w"
;
if((cur_cmd>=min_internal)&&(cur_cmd<=max_internal))
/*448:*/
#line 9348 "texprof.w"

if(mu)
{scan_something_internal(mu_val,false);
/*450:*/
#line 9370 "texprof.w"

if(cur_val_level>=glue_val)
{v= width(cur_val);delete_glue_ref(cur_val);cur_val= v;
}

/*:450*/
#line 9351 "texprof.w"
;
if(cur_val_level==mu_val)goto attach_sign;
if(cur_val_level!=int_val)mu_error();
}
else{scan_something_internal(dimen_val,false);
if(cur_val_level==dimen_val)goto attach_sign;
}

/*:448*/
#line 9327 "texprof.w"

else{back_input();
if(cur_tok==continental_point_token)cur_tok= point_token;
if(cur_tok!=point_token)scan_int();
else{radix= 10;cur_val= 0;
}
if(cur_tok==continental_point_token)cur_tok= point_token;
if((radix==10)&&(cur_tok==point_token))/*451:*/
#line 9381 "texprof.w"

{k= 0;p= null;get_token();
loop{get_x_token();
if((cur_tok> zero_token+9)||(cur_tok<zero_token))goto done1;
if(k<17)
{q= get_avail();link(q)= p;info(q)= cur_tok-zero_token;
p= q;incr(k);
}
}
done1:for(kk= k;kk>=1;kk--)
{dig[kk-1]= info(p);q= p;p= link(p);free_avail(q);
}
f= round_decimals(k);
if(cur_cmd!=spacer)back_input();
}

/*:451*/
#line 9334 "texprof.w"
;
}
}
if(cur_val<0)
{negative= !negative;negate(cur_val);
}
/*452:*/
#line 9404 "texprof.w"

if(inf)/*453:*/
#line 9422 "texprof.w"

if(scan_keyword("fil"))

{cur_order= fil;
while(scan_keyword("l"))
{if(cur_order==filll)
{print_err("Illegal unit of measure (");

print("replaced by filll)");
help1("I dddon't go any higher than filll.");error();
}
else incr(cur_order);
}
goto attach_fraction;
}

/*:453*/
#line 9405 "texprof.w"
;
/*454:*/
#line 9438 "texprof.w"

save_cur_val= cur_val;
/*405:*/
#line 8629 "texprof.w"

do{get_x_token();
}while(!(cur_cmd!=spacer))

/*:405*/
#line 9440 "texprof.w"
;
if((cur_cmd<min_internal)||(cur_cmd> max_internal))back_input();
else{if(mu)
{scan_something_internal(mu_val,false);/*450:*/
#line 9370 "texprof.w"

if(cur_val_level>=glue_val)
{v= width(cur_val);delete_glue_ref(cur_val);cur_val= v;
}

/*:450*/
#line 9443 "texprof.w"
;
if(cur_val_level!=mu_val)mu_error();
}
else scan_something_internal(dimen_val,false);
v= cur_val;goto found;
}
if(mu)goto not_found;
if(scan_keyword("em"))v= (/*557:*/
#line 11418 "texprof.w"
quad(cur_font)

/*:557*/
#line 9450 "texprof.w"
);

else if(scan_keyword("ex"))v= (/*558:*/
#line 11420 "texprof.w"
x_height(cur_font)

/*:558*/
#line 9452 "texprof.w"
);

else goto not_found;
/*442:*/
#line 9230 "texprof.w"

{get_x_token();if(cur_cmd!=spacer)back_input();
}

/*:442*/
#line 9455 "texprof.w"
;
found:cur_val= nx_plus_y(save_cur_val,v,xn_over_d(v,f,0200000));
goto attach_sign;
not_found:

/*:454*/
#line 9407 "texprof.w"
;
if(mu)/*455:*/
#line 9460 "texprof.w"

if(scan_keyword("mu"))goto attach_fraction;

else{print_err("Illegal unit of measure (");print("mu inserted)");

help4("The unit of measurement in math glue must be mu.",
"To recover gracefully from this error, it's best to",
"delete the erroneous units; e.g., type `2' to delete",
"two letters. (See Chapter 27 of The TeXbook.)");

error();goto attach_fraction;
}

/*:455*/
#line 9408 "texprof.w"
;
if(scan_keyword("true"))/*456:*/
#line 9473 "texprof.w"

{prepare_mag();
if(mag!=1000)
{cur_val= xn_over_d(cur_val,1000,mag);
f= (1000*f+0200000*rem)/mag;
cur_val= cur_val+(f/0200000);f= f%0200000;
}
}

/*:456*/
#line 9409 "texprof.w"
;

if(scan_keyword("pt"))goto attach_fraction;

/*457:*/
#line 9491 "texprof.w"

if(scan_keyword("in"))set_conversion(7227,100)

else if(scan_keyword("pc"))set_conversion(12,1)

else if(scan_keyword("cm"))set_conversion(7227,254)

else if(scan_keyword("mm"))set_conversion(7227,2540)

else if(scan_keyword("bp"))set_conversion(7227,7200)

else if(scan_keyword("dd"))set_conversion(1238,1157)

else if(scan_keyword("cc"))set_conversion(14856,1157)

else if(scan_keyword("sp"))goto done;

else/*458:*/
#line 9514 "texprof.w"

{print_err("Illegal unit of measure (");print("pt inserted)");

help6("Dimensions can be in units of em, ex, in, pt, pc,",
"cm, mm, dd, cc, bp, or sp; but yours is a new one!",
"I'll assume that you meant to say pt, for printer's points.",
"To recover gracefully from this error, it's best to",
"delete the erroneous units; e.g., type `2' to delete",
"two letters. (See Chapter 27 of The TeXbook.)");

error();goto done2;
}


/*:458*/
#line 9508 "texprof.w"
;
cur_val= xn_over_d(cur_val,num,denom);
f= (num*f+0200000*rem)/denom;
cur_val= cur_val+(f/0200000);f= f%0200000;
done2:

/*:457*/
#line 9414 "texprof.w"
;
attach_fraction:if(cur_val>=040000)arith_error= true;
else cur_val= cur_val*unity+f;
done:

/*:452*/
#line 9341 "texprof.w"
;
/*442:*/
#line 9230 "texprof.w"

{get_x_token();if(cur_cmd!=spacer)back_input();
}

/*:442*/
#line 9342 "texprof.w"
;
attach_sign:if(arith_error||(abs(cur_val)>=010000000000))
/*459:*/
#line 9528 "texprof.w"

{print_err("Dimension too large");

help2("I can't work with sizes bigger than about 19 feet.",
"Continue and I'll use the largest value I can.");
error();cur_val= max_dimen;arith_error= false;
}

/*:459*/
#line 9344 "texprof.w"
;
if(negative)negate(cur_val);
}

/*:447*//*460:*/
#line 9546 "texprof.w"
static void scan_glue(small_number level)

{
bool negative;
pointer q;
bool mu;
mu= (level==mu_val);/*440:*/
#line 9198 "texprof.w"

negative= false;
do{/*405:*/
#line 8629 "texprof.w"

do{get_x_token();
}while(!(cur_cmd!=spacer))

/*:405*/
#line 9200 "texprof.w"
;
if(cur_tok==other_token+'-')
{negative= !negative;cur_tok= other_token+'+';
}
}while(!(cur_tok!=other_token+'+'))

/*:440*/
#line 9552 "texprof.w"
;
if((cur_cmd>=min_internal)&&(cur_cmd<=max_internal))
{scan_something_internal(level,negative);
if(cur_val_level>=glue_val)
{if(cur_val_level!=level)mu_error();
return;
}
if(cur_val_level==int_val)scan_dimen(mu,false,true);
else if(level==mu_val)mu_error();
}
else{back_input();scan_dimen(mu,false,false);
if(negative)negate(cur_val);
}
/*461:*/
#line 9571 "texprof.w"

q= new_spec(zero_glue);width(q)= cur_val;
if(scan_keyword("plus"))

{scan_dimen(mu,true,false);
stretch(q)= cur_val;stretch_order(q)= cur_order;
}
if(scan_keyword("minus"))

{scan_dimen(mu,true,false);
shrink(q)= cur_val;shrink_order(q)= cur_order;
}
cur_val= q

/*:461*/
#line 9566 "texprof.w"
;
}

/*1464:*/
#line 26900 "texprof.w"

/*1475:*/
#line 27092 "texprof.w"

static int add_or_sub(int x,int y,int max_answer,bool negative)
{int a;
if(negative)negate(y);
if(x>=0)
if(y<=max_answer-x)a= x+y;else num_error(a)
else if(y>=-max_answer-x)a= x+y;else num_error(a);
return a;
}

/*:1475*//*1479:*/
#line 27147 "texprof.w"

static int quotient(int n,int d)
{bool negative;
int a;
if(d==0)num_error(a)
else{if(d> 0)negative= false;
else{negate(d);negative= true;
}
if(n<0)
{negate(n);negative= !negative;
}
a= n/d;n= n-a*d;d= n-d;
if(d+n>=0)incr(a);
if(negative)negate(a);
}
return a;
}

/*:1479*//*1481:*/
#line 27184 "texprof.w"

static int fract(int x,int n,int d,int max_answer)
{
bool negative;
int a;
int f;
int h;
int r;
int t;
if(d==0)goto too_big;
a= 0;
if(d> 0)negative= false;
else{negate(d);negative= true;
}
if(x<0)
{negate(x);negative= !negative;
}
else if(x==0)goto done;
if(n<0)
{negate(n);negative= !negative;
}
t= n/d;
if(t> max_answer/x)goto too_big;
a= t*x;n= n-t*d;
if(n==0)goto found;
t= x/d;
if(t> (max_answer-a)/n)goto too_big;
a= a+t*n;x= x-t*d;
if(x==0)goto found;
if(x<n)
{t= x;x= n;n= t;
}
/*1482:*/
#line 27234 "texprof.w"

f= 0;r= (d/2)-d;h= -r;
loop{if(odd(n))
{r= r+x;
if(r>=0)
{r= r-d;incr(f);
}
}
n= n/2;
if(n==0)goto found1;
if(x<h)x= x+x;
else{t= x-d;x= t+x;f= f+n;
if(x<n)
{if(x==0)goto found1;
t= x;x= n;n= t;
}
}
}
found1:

/*:1482*/
#line 27216 "texprof.w"

if(f> (max_answer-a))goto too_big;
a= a+f;
found:if(negative)negate(a);
goto done;
too_big:num_error(a);
done:return a;
}

/*:1481*/
#line 26901 "texprof.w"

static void scan_expr(void)
{
bool a,b;
small_number l;
small_number r;
small_number s;
small_number o;
int e;
int t;
int f;
int n;
pointer p;
pointer q;
l= cur_val_level;a= arith_error;b= false;p= null;
/*1465:*/
#line 26944 "texprof.w"

restart:r= expr_none;e= 0;s= expr_none;t= 0;n= 0;
resume:if(s==expr_none)o= l;else o= int_val;
/*1467:*/
#line 26976 "texprof.w"

/*405:*/
#line 8629 "texprof.w"

do{get_x_token();
}while(!(cur_cmd!=spacer))

/*:405*/
#line 26977 "texprof.w"
;
if(cur_tok==other_token+'(')
/*1470:*/
#line 27016 "texprof.w"

{q= get_node(expr_node_size);link(q)= p;type(q)= l;
subtype(q)= 4*s+r;
expr_e_field(q)= e;expr_t_field(q)= t;expr_n_field(q)= n;
p= q;l= o;goto restart;
}

/*:1470*/
#line 26979 "texprof.w"
;
back_input();
if(o==int_val)scan_int();
else if(o==dimen_val)scan_normal_dimen;
else if(o==glue_val)scan_normal_glue();
else scan_mu_glue();
f= cur_val

/*:1467*/
#line 26947 "texprof.w"
;
found:/*1466:*/
#line 26958 "texprof.w"

/*405:*/
#line 8629 "texprof.w"

do{get_x_token();
}while(!(cur_cmd!=spacer))

/*:405*/
#line 26959 "texprof.w"
;
if(cur_tok==other_token+'+')o= expr_add;
else if(cur_tok==other_token+'-')o= expr_sub;
else if(cur_tok==other_token+'*')o= expr_mult;
else if(cur_tok==other_token+'/')o= expr_div;
else{o= expr_none;
if(p==null)
{if(cur_cmd!=relax)back_input();
}
else if(cur_tok!=other_token+')')
{print_err("Missing ) inserted for expression");

help1("I was expecting to see `+', `-', `*', `/', or `)'. Didn't.");
back_error();
}
}

/*:1466*/
#line 26948 "texprof.w"
;
arith_error= b;
/*1472:*/
#line 27044 "texprof.w"

if((l==int_val)||(s> expr_sub))
{if((f> infinity)||(f<-infinity))num_error(f);
}
else if(l==dimen_val)
{if(abs(f)> max_dimen)num_error(f);
}
else{if((abs(width(f))> max_dimen)||
(abs(stretch(f))> max_dimen)||
(abs(shrink(f))> max_dimen))glue_error(f);
}

/*:1472*/
#line 26950 "texprof.w"
;
switch(s){/*1473:*/
#line 27066 "texprof.w"

case expr_none:if((l>=glue_val)&&(o!=expr_none))
{t= new_spec(f);delete_glue_ref(f);normalize_glue(t);
}
else t= f;break;

/*:1473*//*1477:*/
#line 27126 "texprof.w"

case expr_mult:if(o==expr_div)
{n= f;o= expr_scale;
}
else if(l==int_val)t= mult_integers(t,f);
else if(l==dimen_val)expr_m(t);
else{expr_m(width(t));expr_m(stretch(t));expr_m(shrink(t));
}break;

/*:1477*//*1478:*/
#line 27139 "texprof.w"

case expr_div:if(l<glue_val)expr_d(t);
else{expr_d(width(t));expr_d(stretch(t));expr_d(shrink(t));
}break;

/*:1478*//*1480:*/
#line 27169 "texprof.w"

case expr_scale:if(l==int_val)t= fract(t,n,f,infinity);
else if(l==dimen_val)expr_s(t);
else{expr_s(width(t));expr_s(stretch(t));expr_s(shrink(t));
}

/*:1480*/
#line 26951 "texprof.w"

}
if(o> expr_sub)s= o;else/*1474:*/
#line 27078 "texprof.w"

{s= expr_none;
if(r==expr_none)e= t;
else if(l==int_val)e= expr_add_sub(e,t,infinity);
else if(l==dimen_val)e= expr_a(e,t);
else/*1476:*/
#line 27105 "texprof.w"

{width(e)= expr_a(width(e),width(t));
if(stretch_order(e)==stretch_order(t))
stretch(e)= expr_a(stretch(e),stretch(t));
else if((stretch_order(e)<stretch_order(t))&&(stretch(t)!=0))
{stretch(e)= stretch(t);stretch_order(e)= stretch_order(t);
}
if(shrink_order(e)==shrink_order(t))
shrink(e)= expr_a(shrink(e),shrink(t));
else if((shrink_order(e)<shrink_order(t))&&(shrink(t)!=0))
{shrink(e)= shrink(t);shrink_order(e)= shrink_order(t);
}
delete_glue_ref(t);normalize_glue(e);
}

/*:1476*/
#line 27083 "texprof.w"
;
r= o;
}

/*:1474*/
#line 26953 "texprof.w"
;
b= arith_error;
if(o!=expr_none)goto resume;
if(p!=null)/*1471:*/
#line 27023 "texprof.w"

{f= e;q= p;
e= expr_e_field(q);t= expr_t_field(q);n= expr_n_field(q);
s= subtype(q)/4;r= subtype(q)%4;
l= type(q);p= link(q);free_node(q,expr_node_size);
goto found;
}

/*:1471*/
#line 26956 "texprof.w"


/*:1465*/
#line 26916 "texprof.w"
;
if(b)
{print_err("Arithmetic overflow");

help2("I can't evaluate this expression,",
"since the result is out of range.");
error();
if(l>=glue_val)
{delete_glue_ref(e);e= zero_glue;add_glue_ref(e);
}
else e= 0;
}
arith_error= a;cur_val= e;cur_val_level= l;
}

/*:1464*//*1469:*/
#line 26994 "texprof.w"

static void scan_normal_glue(void)
{scan_glue(glue_val);
}

static void scan_mu_glue(void)
{scan_glue(mu_val);
}

/*:1469*/
#line 9569 "texprof.w"


/*:460*//*462:*/
#line 9594 "texprof.w"
static pointer scan_rule_spec(void)
{
pointer q;
q= new_rule();
if(cur_cmd==vrule)width(q)= default_rule;
else{height(q)= default_rule;depth(q)= 0;
}
reswitch:if(scan_keyword("width"))

{scan_normal_dimen;width(q)= cur_val;goto reswitch;
}
if(scan_keyword("height"))

{scan_normal_dimen;height(q)= cur_val;goto reswitch;
}
if(scan_keyword("depth"))

{scan_normal_dimen;depth(q)= cur_val;goto reswitch;
}
return q;
}

/*:462*//*463:*/
#line 9628 "texprof.w"
/*1413:*/
#line 26315 "texprof.w"

static void scan_general_text(void)
{
int s;
pointer w;
pointer d;
pointer p;
pointer q;
halfword unbalance;
s= scanner_status;w= warning_index;d= def_ref;
scanner_status= absorbing;warning_index= cur_cs;
def_ref= get_avail();token_ref_count(def_ref)= null;p= def_ref;
scan_left_brace();
unbalance= 1;
loop{get_token();
if(cur_tok<right_brace_limit)
if(cur_cmd<right_brace)incr(unbalance);
else{decr(unbalance);
if(unbalance==0)goto found;
}
store_new_token(cur_tok);
}
found:q= link(def_ref);free_avail(def_ref);
if(q==null)cur_val= temp_head;else cur_val= p;
link(temp_head)= q;
scanner_status= s;warning_index= w;def_ref= d;
}

/*:1413*//*1435:*/
#line 26485 "texprof.w"

static void pseudo_start(void)
{int old_setting;
str_number s;
pool_pointer l,m;
pointer p,q,r;
four_quarters w;
int nl,sz;
scan_general_text();
old_setting= selector;selector= new_string;
token_show(temp_head);selector= old_setting;
flush_list(link(temp_head));
str_room(1);s= make_string();
/*1436:*/
#line 26503 "texprof.w"

str_pool[pool_ptr]= si(' ');l= str_start[s];
nl= si(new_line_char);
p= get_avail();q= p;
while(l<pool_ptr)
{m= l;
while((l<pool_ptr)&&(str_pool[l]!=nl))incr(l);
sz= (l-m+7)/4;
if(sz==1)sz= 2;
r= get_node(sz);link(q)= r;q= r;info(q)= hi(sz);
while(sz> 2)
{decr(sz);incr(r);
w.b0= qi(so(str_pool[m]));w.b1= qi(so(str_pool[m+1]));
w.b2= qi(so(str_pool[m+2]));w.b3= qi(so(str_pool[m+3]));
mem[r].qqqq= w;m= m+4;
}
w.b0= qi(' ');w.b1= qi(' ');w.b2= qi(' ');w.b3= qi(' ');
if(l> m)
{w.b0= qi(so(str_pool[m]));
if(l> m+1)
{w.b1= qi(so(str_pool[m+1]));
if(l> m+2)
{w.b2= qi(so(str_pool[m+2]));
if(l> m+3)w.b3= qi(so(str_pool[m+3]));
}
}
}
mem[r+1].qqqq= w;
if(str_pool[l]==nl)incr(l);
}
info(p)= link(p);link(p)= pseudo_files;pseudo_files= p

/*:1436*/
#line 26498 "texprof.w"
;
flush_string;
/*1437:*/
#line 26535 "texprof.w"

begin_file_reading();
line= 0;limit= start;loc= limit+1;
if(tracing_scan_tokens> 0)
{if(term_offset> max_print_line-3)print_ln();
else if((term_offset> 0)||(file_offset> 0))print_char(' ');
name= 19;print("( ");incr(open_parens);update_terminal;
}
else name= 18

/*:1437*/
#line 26500 "texprof.w"
;
}

/*:1435*/
#line 9628 "texprof.w"

static pointer str_toks(pool_pointer b)

{pointer p;
pointer q;
halfword t;
pool_pointer k;
str_room(1);
p= temp_head;link(p)= null;k= b;
while(k<pool_ptr)
{t= so(str_pool[k]);
if(t==' ')t= space_token;
else t= other_token+t;
fast_store_new_token(t);
incr(k);
}
pool_ptr= b;return p;
}

/*:463*//*464:*/
#line 9654 "texprof.w"
static pointer the_toks(void)
{
int old_setting;
pointer p,q,r;
pool_pointer b;
small_number c;
/*1418:*/
#line 26372 "texprof.w"

if(odd(cur_chr))
{c= cur_chr;scan_general_text();
if(c==1)return cur_val;
else{old_setting= selector;selector= new_string;b= pool_ptr;
p= get_avail();link(p)= link(temp_head);
token_show(p);flush_list(p);
selector= old_setting;return str_toks(b);
}

}

/*:1418*/
#line 9660 "texprof.w"
;
get_x_token();scan_something_internal(tok_val,false);
if(cur_val_level>=ident_val)/*465:*/
#line 9677 "texprof.w"

{p= temp_head;link(p)= null;
if(cur_val_level==ident_val)store_new_token(cs_token_flag+cur_val)
else if(cur_val!=null)
{r= link(cur_val);
while(r!=null)
{fast_store_new_token(info(r));r= link(r);
}
}
return p;
}

/*:465*/
#line 9662 "texprof.w"

else{old_setting= selector;selector= new_string;b= pool_ptr;
switch(cur_val_level){
case int_val:print_int(cur_val);break;
case dimen_val:{print_scaled(cur_val);print("pt");
}break;
case glue_val:{print_spec(cur_val,"pt");delete_glue_ref(cur_val);
}break;
case mu_val:{print_spec(cur_val,"mu");delete_glue_ref(cur_val);
}
}
selector= old_setting;return str_toks(b);
}
}

/*:464*//*466:*/
#line 9691 "texprof.w"
static void ins_the_toks(void)
{link(garbage)= the_toks();ins_list(link(temp_head));
}

/*:466*//*469:*/
#line 9742 "texprof.w"
static void scan_pdf_ext_toks(void);
static void conv_toks(void)
{int old_setting;
int c;
small_number save_scanner_status;
pool_pointer b;
int i,k,l;
pool_pointer m,n;
bool r;
str_number s,t;
c= cur_chr;/*470:*/
#line 9758 "texprof.w"

switch(c){
case number_code:case roman_numeral_code:scan_int();break;
case string_code:case meaning_code:{save_scanner_status= scanner_status;
scanner_status= normal;get_token();scanner_status= save_scanner_status;
}break;
case font_name_code:scan_font_ident();break;
case job_name_code:if(job_name==0)open_log_file();break;
case eTeX_revision_code:do_nothing;break;
/*1557:*/
#line 28315 "texprof.w"

case Prote_revision_code:do_nothing;break;

/*:1557*//*1593:*/
#line 28693 "texprof.w"

case strcmp_code:/*1594:*/
#line 28696 "texprof.w"

{scan_general_x_text();toks_to_str();
s= info(garbage);flush_list(link(garbage));
scan_general_x_text();toks_to_str();
t= info(garbage);flush_list(link(garbage));
if((length(s)==0)&&(length(t)==0))cur_val= 0;
else if(length(s)==0)cur_val= -1;
else if(length(t)==0)cur_val= 1;
else{m= str_start[s];n= str_start[t];r= false;
while((!r)&&(m<str_start[s+1])&&(n<str_start[t+1])){
cur_val= str_pool[m]-str_pool[n];if(cur_val!=0)r= true;
incr(m);incr(n);
}
if(cur_val==0){if(length(s)!=length(t))
if(m!=str_start[s+1])cur_val= 1;else cur_val= -1;
}
else cur_val= cur_val/(double)abs(cur_val);
}
flush_string;flush_string;
}

/*:1594*/
#line 28694 "texprof.w"
break;

/*:1593*//*1600:*/
#line 28759 "texprof.w"

case creation_date_code:get_creation_date();break;

/*:1600*//*1612:*/
#line 28872 "texprof.w"

case file_size_code:/*1613:*/
#line 28875 "texprof.w"

{scan_general_x_text();toks_to_str();
s= info(garbage);flush_list(link(garbage));str_to_name(s);
cur_val= -1;
cur_val= get_file_size();
flush_string;
}

/*:1613*/
#line 28873 "texprof.w"
break;

/*:1612*//*1617:*/
#line 28915 "texprof.w"

case file_mod_date_code:/*1618:*/
#line 28918 "texprof.w"

{scan_general_x_text();toks_to_str();
s= info(garbage);flush_list(link(garbage));str_to_name(s);
get_file_mod_date();
flush_string;
}break;

/*:1618*/
#line 28916 "texprof.w"
break;

/*:1617*//*1622:*/
#line 28966 "texprof.w"

case file_dump_code:/*1623:*/
#line 28969 "texprof.w"

{k= 0;l= 0;
if(scan_keyword("offset")){scan_int();
if(cur_val<0){print_err("Bad ");print_esc("filedump");

help2("I allow only nonnegative values here.",
"I changed this one to zero.");int_error(cur_val);
}
else k= cur_val;
}
if(scan_keyword("length")){scan_int();
if(cur_val<0){print_err("Bad ");print_esc("filedump");

help2("I allow only nonnegative values here.",
"I changed this one to zero.");int_error(cur_val);
}
else l= cur_val;
}
scan_general_x_text();toks_to_str();s= info(garbage);
flush_list(link(garbage));str_to_name(s);
flush_string;
}

/*:1623*/
#line 28967 "texprof.w"
break;

/*:1622*//*1627:*/
#line 29045 "texprof.w"

case mdfive_sum_code:/*1628:*/
#line 29048 "texprof.w"

{r= scan_keyword("file");scan_general_x_text();
toks_to_str();s= info(garbage);flush_list(link(garbage));
l= get_md5_sum(s,r);
flush_string;
}

/*:1628*/
#line 29046 "texprof.w"
break;

/*:1627*//*1650:*/
#line 29364 "texprof.w"

case set_random_seed_code:{scan_int();random_seed= cur_val;
init_randoms();
}break;

/*:1650*//*1657:*/
#line 29448 "texprof.w"

case uniform_deviate_code:{scan_int();
cur_val= unif_rand(cur_val);
}break;

/*:1657*//*1664:*/
#line 29538 "texprof.w"

case normal_deviate_code:cur_val= norm_rand();break;

/*:1664*//*1810:*/
#line 32523 "texprof.w"

case pdftex_revision_code:do_nothing;break;
case pdftex_banner_code:do_nothing;break;
case pdf_font_name_code:case pdf_font_objnum_code:
case pdf_font_size_code:{
scan_font_ident();
if(cur_val==null_font)
pdf_error("font","invalid font identifier");
}break;
case pdf_page_ref_code:{
scan_int();
if(cur_val<=0)
pdf_error("pageref","invalid page number");
}break;
case left_margin_kern_code:case right_margin_kern_code:{
pointer p;
scan_register_num();
fetch_box(p);
if((p==null)||(type(p)!=hlist_node))
pdf_error("marginkern","a non-empty hbox expected");
}break;
case pdf_xform_name_code:{
scan_int();
}break;
case pdf_escape_string_code:
case pdf_escape_name_code:
case pdf_escape_hex_code:
case pdf_unescape_hex_code:
scan_general_x_text();
ins_list(link(link(garbage)));
free_avail(link(garbage));
return;
case pdf_match_code:
scan_keyword("icase");
if(scan_keyword("subcount"))scan_int();
scan_pdf_ext_toks();
scan_pdf_ext_toks();
break;
case pdf_last_match_code:
{pointer p,q;
scan_int();

p= temp_head;link(p)= null;
store_new_token(other_token+'-');
store_new_token(other_token+'1');
store_new_token(other_token+'-');
store_new_token(other_token+'>');
ins_list(link(temp_head));
return;
}
case pdf_colorstack_init_code:
{
scan_keyword("page");
if(!scan_keyword("direct"))
scan_keyword("page");
scan_pdf_ext_toks();
cur_val= 0;
}break;
case pdf_insert_ht_code:scan_register_num();break;
case pdf_ximage_bbox_code:{
scan_int();
scan_int();
}break;


/*:1810*/
#line 9767 "texprof.w"

}

/*:470*/
#line 9752 "texprof.w"
;
old_setting= selector;selector= new_string;b= pool_ptr;
/*471:*/
#line 9770 "texprof.w"

switch(c){
case number_code:print_int(cur_val);break;
case roman_numeral_code:print_roman_int(cur_val);break;
case string_code:if(cur_cs!=0)sprint_cs(cur_cs);
else print_char(cur_chr);break;
case meaning_code:print_meaning();break;
case font_name_code:{printn(font_name[cur_val]);
if(font_size[cur_val]!=font_dsize[cur_val])
{print(" at ");print_scaled(font_size[cur_val]);
print("pt");
}
}break;
case eTeX_revision_code:print(eTeX_revision);break;
case job_name_code:printn(job_name);break;
/*1558:*/
#line 28318 "texprof.w"

case Prote_revision_code:print(Prote_revision);break;

/*:1558*//*1595:*/
#line 28717 "texprof.w"

case strcmp_code:print_int(cur_val);break;

/*:1595*//*1601:*/
#line 28765 "texprof.w"

case creation_date_code:for(k= 0;time_str[k]!='\0';k++)
print_char(time_str[k]);break;

/*:1601*//*1614:*/
#line 28883 "texprof.w"

case file_size_code:if(cur_val!=-1)print_int(cur_val);break;

/*:1614*//*1619:*/
#line 28929 "texprof.w"

case file_mod_date_code:for(k= 0;time_str[k]!='\0';k++)
print_char(time_str[k]);break;

/*:1619*//*1624:*/
#line 28997 "texprof.w"

case file_dump_code:
{FILE*f= fopen((char*)name_of_file0,"rb");
if(f!=NULL){
fseek(f,k,SEEK_SET);
do{i= fgetc(f);if(i==EOF)break;
dig[0]= i%16;dig[1]= i/16;
print_the_digs(2);decr(l);
}while(!(feof(f)||(l==0)));
fclose(f);
}
}break;

/*:1624*//*1629:*/
#line 29059 "texprof.w"

case mdfive_sum_code:for(k= 0;k<l;k++)
{dig[0]= md5_digest[k]%16;dig[1]= md5_digest[k]/16;print_the_digs(2);
}break;

/*:1629*//*1651:*/
#line 29369 "texprof.w"

case set_random_seed_code:print_int(random_seed);break;

/*:1651*//*1658:*/
#line 29453 "texprof.w"

case uniform_deviate_code:print_int(cur_val);break;

/*:1658*//*1665:*/
#line 29541 "texprof.w"

case normal_deviate_code:print_int(cur_val);break;

/*:1665*//*1812:*/
#line 32604 "texprof.w"

case pdftex_revision_code:print(pdftex_revision);break;
case pdftex_banner_code:print("This is pdfTeX, Version 3.141592653");break;
case pdf_font_name_code:case pdf_font_objnum_code:print_int(cur_val);break;
case pdf_font_size_code:
print_scaled(font_size[cur_val]);
print("pt");break;
case pdf_page_ref_code:print_int(1);break;
case pdf_xform_name_code:print_int(cur_val);break;
case pdf_escape_string_code:
case pdf_escape_name_code:
case left_margin_kern_code:print("0pt");break;
case right_margin_kern_code:print("0pt");break;
case pdf_colorstack_init_code:print_int(cur_val);break;
case pdf_escape_hex_code:
case pdf_unescape_hex_code:
case pdf_match_code:
case pdf_last_match_code:
case pdf_insert_ht_code:print("10pt");break;
case pdf_ximage_bbox_code:print("10pt");break;


/*:1812*/
#line 9785 "texprof.w"

}

/*:471*/
#line 9754 "texprof.w"
;
selector= old_setting;link(garbage)= str_toks(b);ins_list(link(temp_head));
}

/*:469*//*472:*/
#line 9812 "texprof.w"
static pointer scan_toks(bool macro_def,bool xpand)
{
halfword t;
halfword s;
pointer p;
pointer q;
halfword unbalance;
halfword hash_brace;
if(macro_def)scanner_status= defining;
else scanner_status= absorbing;
warning_index= cur_cs;def_ref= get_avail();token_ref_count(def_ref)= null;
p= def_ref;hash_brace= 0;t= zero_token;
if(macro_def)/*473:*/
#line 9833 "texprof.w"

{loop{resume:get_token();
if(cur_tok<right_brace_limit)goto done1;
if(cur_cmd==mac_param)
/*475:*/
#line 9854 "texprof.w"

{s= match_token+cur_chr;get_token();
if(cur_tok<left_brace_limit)
{hash_brace= cur_tok;
store_new_token(cur_tok);store_new_token(end_match_token);
goto done;
}
if(t==zero_token+9)
{print_err("You already have nine parameters");

help2("I'm going to ignore the # sign you just used,",
"as well as the token that followed it.");error();goto resume;
}
else{incr(t);
if(cur_tok!=t)
{print_err("Parameters must be numbered consecutively");

help2("I've inserted the digit you should have used after the #.",
"Type `1' to delete what you did use.");back_error();
}
cur_tok= s;
}
}

/*:475*/
#line 9839 "texprof.w"
;
store_new_token(cur_tok);
}
done1:store_new_token(end_match_token);
if(cur_cmd==right_brace)
/*474:*/
#line 9847 "texprof.w"

{print_err("Missing { inserted");incr(align_state);

help2("Where was the left brace? You said something like `\\def\\a}',",
"which I'm going to interpret as `\\def\\a{}'.");error();goto found;
}

/*:474*/
#line 9844 "texprof.w"
;
done:;}

/*:473*/
#line 9824 "texprof.w"

else scan_left_brace();
/*476:*/
#line 9878 "texprof.w"

unbalance= 1;
loop{if(xpand)/*477:*/
#line 9895 "texprof.w"

{loop{get_next();
if(cur_cmd>=call)
if(info(link(cur_chr))==protected_token)
{cur_cmd= relax;cur_chr= no_expand_flag;
}
if(cur_cmd<=max_command)goto done2;
if(cur_cmd!=the)expand();
else{q= the_toks();
if(link(temp_head)!=null)
{link(p)= link(temp_head);p= q;
}
}
}
done2:x_token();
}

/*:477*/
#line 9880 "texprof.w"

else get_token();
if(cur_tok<right_brace_limit)
if(cur_cmd<right_brace)incr(unbalance);
else{decr(unbalance);
if(unbalance==0)goto found;
}
else if(cur_cmd==mac_param)
if(macro_def)/*478:*/
#line 9912 "texprof.w"

{s= cur_tok;
if(xpand)get_x_token();else get_token();
if(cur_cmd!=mac_param)
if((cur_tok<=zero_token)||(cur_tok> t))
{print_err("Illegal parameter number in definition of ");

sprint_cs(warning_index);
help3("You meant to type ## instead of #, right?",
"Or maybe a } was forgotten somewhere earlier, and things",
"are all screwed up? I'm going to assume that you meant ##.");
back_error();cur_tok= s;
}
else cur_tok= out_param_token-'0'+cur_chr;
}

/*:478*/
#line 9888 "texprof.w"
;
store_new_token(cur_tok);
}

/*:476*/
#line 9826 "texprof.w"
;
found:scanner_status= normal;
if(hash_brace!=0)store_new_token(hash_brace);
return p;
}
/*1561:*/
#line 28341 "texprof.w"

static void scan_general_x_text(void)
{pointer d;
d= def_ref;info(garbage)= scan_toks(false,true);
link(garbage)= def_ref;
def_ref= d;
}

/*:1561*//*1563:*/
#line 28358 "texprof.w"

static void toks_to_str(void)
{int old_setting;
old_setting= selector;selector= new_string;
token_show(link(garbage));selector= old_setting;
str_room(1);
info(garbage)= make_string();
}

/*:1563*/
#line 9831 "texprof.w"


/*:472*//*481:*/
#line 9949 "texprof.w"
static void read_toks(int n,pointer r,halfword j)
{
pointer p;
pointer q;
int s;
small_number m;
scanner_status= defining;warning_index= r;
def_ref= get_avail();token_ref_count(def_ref)= null;
p= def_ref;
store_new_token(end_match_token);
if((n<0)||(n> 15))m= 16;else m= n;
s= align_state;align_state= 1000000;
do{/*482:*/
#line 9966 "texprof.w"

begin_file_reading();name= m+1;
if(read_open[m]==closed)/*483:*/
#line 9991 "texprof.w"

if(interaction> nonstop_mode)
if(n<0)prompt_input("")
else{wake_up_terminal;
print_ln();sprint_cs(r);prompt_input("=");n= -1;
}
else fatal_error("*** (cannot \\read from terminal in nonstop modes)")


/*:483*/
#line 9968 "texprof.w"
;
else if(read_open[m]==just_open)/*484:*/
#line 10004 "texprof.w"

if(input_ln(&read_file[m],false))read_open[m]= normal;
else{a_close(&read_file[m]);read_open[m]= closed;
}

/*:484*/
#line 9969 "texprof.w"

else/*485:*/
#line 10012 "texprof.w"

{if(!input_ln(&read_file[m],true))
{a_close(&read_file[m]);read_open[m]= closed;
if(align_state!=1000000)
{runaway();
print_err("File ended within ");print_esc("read");

help1("This \\read has unbalanced braces.");
align_state= 1000000;limit= 0;error();
}
}
}

/*:485*/
#line 9970 "texprof.w"
;
limit= last;
if(end_line_char_inactive)decr(limit);
else buffer[limit]= end_line_char;
first= limit+1;loc= start;state= new_line;
/*1443:*/
#line 26595 "texprof.w"

if(j==1)
{while(loc<=limit)
{cur_chr= buffer[loc];incr(loc);
if(cur_chr==' ')cur_tok= space_token;
else cur_tok= cur_chr+other_token;
store_new_token(cur_tok);
}
goto done;
}

/*:1443*/
#line 9975 "texprof.w"
;
loop{get_token();
if(cur_tok==0)goto done;

if(align_state<1000000)
{do{get_token();}while(!(cur_tok==0));
align_state= 1000000;goto done;
}
store_new_token(cur_tok);
}
done:end_file_reading()

/*:482*/
#line 9961 "texprof.w"
;
}while(!(align_state==1000000));
cur_val= def_ref;scanner_status= normal;align_state= s;
}

/*:481*//*493:*/
#line 10166 "texprof.w"
static void pass_text(void)
{
int l;
small_number save_scanner_status;
save_scanner_status= scanner_status;scanner_status= skipping;l= 0;
skip_line= line;
loop{get_next();
if(cur_cmd==fi_or_else)
{if(l==0)goto done;
if(cur_chr==fi_code)decr(l);
}
else if(cur_cmd==if_test)incr(l);
}
done:scanner_status= save_scanner_status;
if(tracing_ifs> 0)show_cur_cmd_chr();
}

/*:493*//*496:*/
#line 10206 "texprof.w"
static void change_if_limit(small_number l,pointer p)
{
pointer q;
if(p==cond_ptr)if_limit= l;
else{q= cond_ptr;
loop{if(q==null)confusion("if");

if(link(q)==p)
{type(q)= l;return;
}
q= link(q);
}
}
}

/*:496*//*497:*/
#line 10226 "texprof.w"
static void conditional(void)
{
bool b;
int r;
int m,n;
pointer p,q;
small_number save_scanner_status;
pointer save_cond_ptr;
small_number this_if;
bool is_unless;
if(tracing_ifs> 0)if(tracing_commands<=1)show_cur_cmd_chr();
/*494:*/
#line 10189 "texprof.w"

{p= get_node(if_node_size);link(p)= cond_ptr;type(p)= if_limit;
subtype(p)= cur_if;if_line_field(p)= if_line;
cond_ptr= p;cur_if= cur_chr;if_limit= if_code;if_line= line;
}

/*:494*/
#line 10237 "texprof.w"
;save_cond_ptr= cond_ptr;
is_unless= (cur_chr>=unless_code);this_if= cur_chr%unless_code;
/*500:*/
#line 10268 "texprof.w"

switch(this_if){
case if_char_code:case if_cat_code:/*505:*/
#line 10341 "texprof.w"

{get_x_token_or_active_char;
if((cur_cmd> active_char)||(cur_chr> 255))
{m= relax;n= 256;
}
else{m= cur_cmd;n= cur_chr;
}
get_x_token_or_active_char;
if((cur_cmd> active_char)||(cur_chr> 255))
{cur_cmd= relax;cur_chr= 256;
}
if(this_if==if_char_code)b= (n==cur_chr);else b= (m==cur_cmd);
}

/*:505*/
#line 10270 "texprof.w"
break;
case if_int_code:case if_dim_code:/*502:*/
#line 10298 "texprof.w"

{if(this_if==if_int_code)scan_int();else scan_normal_dimen;
n= cur_val;/*405:*/
#line 8629 "texprof.w"

do{get_x_token();
}while(!(cur_cmd!=spacer))

/*:405*/
#line 10300 "texprof.w"
;
if((cur_tok>=other_token+'<')&&(cur_tok<=other_token+'>'))
r= cur_tok-other_token;
else{print_err("Missing = inserted for ");

print_cmd_chr(if_test,this_if);
help1("I was expecting to see `<', `=', or `>'. Didn't.");
back_error();r= '=';
}
if(this_if==if_int_code)scan_int();else scan_normal_dimen;
switch(r){
case'<':b= (n<cur_val);break;
case'=':b= (n==cur_val);break;
case'>':b= (n> cur_val);
}
}

/*:502*/
#line 10271 "texprof.w"
break;
case if_odd_code:/*503:*/
#line 10317 "texprof.w"

{scan_int();b= odd(cur_val);
}

/*:503*/
#line 10272 "texprof.w"
break;
case if_vmode_code:b= (abs(mode)==vmode);break;
case if_hmode_code:b= (abs(mode)==hmode);break;
case if_mmode_code:b= (abs(mode)==mmode);break;
case if_inner_code:b= (mode<0);break;
case if_void_code:case if_hbox_code:
case if_vbox_code:/*504:*/
#line 10321 "texprof.w"

{scan_register_num();fetch_box(p);
if(this_if==if_void_code)b= (p==null);
else if(p==null)b= false;
else if(this_if==if_hbox_code)b= (type(p)==hlist_node);
else b= (type(p)==vlist_node);
}

/*:504*/
#line 10278 "texprof.w"
break;
case ifx_code:/*506:*/
#line 10362 "texprof.w"

{save_scanner_status= scanner_status;scanner_status= normal;
get_next();n= cur_cs;p= cur_cmd;q= cur_chr;
get_next();if(cur_cmd!=p)b= false;
else if(cur_cmd<call)b= (cur_chr==q);
else/*507:*/
#line 10379 "texprof.w"

{p= link(cur_chr);q= link(equiv(n));
if(p==q)b= true;
else{while((p!=null)&&(q!=null))
if(info(p)!=info(q))p= null;
else{p= link(p);q= link(q);
}
b= ((p==null)&&(q==null));
}
}

/*:507*/
#line 10367 "texprof.w"
;
scanner_status= save_scanner_status;
}

/*:506*/
#line 10279 "texprof.w"
break;
case if_eof_code:{scan_four_bit_int();b= (read_open[cur_val]==closed);
}break;
case if_true_code:b= true;break;
case if_false_code:b= false;break;
/*1448:*/
#line 26654 "texprof.w"

case if_def_code:{save_scanner_status= scanner_status;
scanner_status= normal;
get_next();b= (cur_cmd!=undefined_cs);
scanner_status= save_scanner_status;
}break;

/*:1448*//*1449:*/
#line 26666 "texprof.w"

case if_cs_code:{n= get_avail();p= n;
do{get_x_token();
if(cur_cs==0)store_new_token(cur_tok);
}while(!(cur_cs!=0));
if(cur_cmd!=end_cs_name)/*372:*/
#line 8154 "texprof.w"

{print_err("Missing ");print_esc("endcsname");print(" inserted");

help2("The control sequence marked <to be read again> should",
"not appear between \\csname and \\endcsname.");
back_error();
}

/*:372*/
#line 26671 "texprof.w"
;
/*1450:*/
#line 26677 "texprof.w"

m= first;p= link(n);
while(p!=null)
{if(m>=max_buf_stack)
{max_buf_stack= m+1;
if(max_buf_stack==buf_size)
overflow("buffer size",buf_size);

}
buffer[m]= info(p)%0400;incr(m);p= link(p);
}
if(m==first)cur_cs= null_cs;
else if(m> first+1)
cur_cs= id_lookup(first,m-first);
else cur_cs= single_base+buffer[first]

/*:1450*/
#line 26672 "texprof.w"
;
flush_list(n);
b= (eq_type(cur_cs)!=undefined_cs);
}break;

/*:1449*//*1451:*/
#line 26696 "texprof.w"

case if_font_char_code:{scan_font_ident();n= cur_val;scan_char_num();
if((font_bc[n]<=cur_val)&&(font_ec[n]>=cur_val))
b= char_exists(char_info(n,qi(cur_val)));
else b= false;
}break;

/*:1451*//*1574:*/
#line 28478 "texprof.w"

case if_incsname_code:b= (incsname_state> 0);break;

/*:1574*//*1576:*/
#line 28488 "texprof.w"

case if_primitive_code:{do{get_token();}while(!(cur_tok!=space_token));
if((cur_cs!=0)&&(cur_cmd!=undefined_cs)&&(cur_cmd<call))b= true;else b= false;
}break;

/*:1576*/
#line 10284 "texprof.w"

case if_case_code:/*508:*/
#line 10390 "texprof.w"

{scan_int();n= cur_val;
if(tracing_commands> 1)
{begin_diagnostic();print("{case ");print_int(n);print_char('}');
end_diagnostic(false);
}
while(n!=0)
{pass_text();
if(cond_ptr==save_cond_ptr)
if(cur_chr==or_code)decr(n);
else goto common_ending;
else if(cur_chr==fi_code)/*495:*/
#line 10195 "texprof.w"

{if(if_stack[in_open]==cond_ptr)if_warning();

p= cond_ptr;if_line= if_line_field(p);
cur_if= subtype(p);if_limit= type(p);cond_ptr= link(p);
free_node(p,if_node_size);
}

/*:495*/
#line 10401 "texprof.w"
;
}
change_if_limit(or_code,save_cond_ptr);
return;
}

/*:508*/
#line 10285 "texprof.w"
;
}

/*:500*/
#line 10239 "texprof.w"
;
if(is_unless)b= !b;
if(tracing_commands> 1)/*501:*/
#line 10288 "texprof.w"

{begin_diagnostic();
if(b)print("{true}");else print("{false}");
end_diagnostic(false);
}

/*:501*/
#line 10241 "texprof.w"
;
if(b)
{change_if_limit(else_code,save_cond_ptr);
return;
}
/*499:*/
#line 10256 "texprof.w"

loop{pass_text();
if(cond_ptr==save_cond_ptr)
{if(cur_chr!=or_code)goto common_ending;
print_err("Extra ");print_esc("or");

help1("I'm ignoring this; it doesn't match any \\if.");
error();
}
else if(cur_chr==fi_code)/*495:*/
#line 10195 "texprof.w"

{if(if_stack[in_open]==cond_ptr)if_warning();

p= cond_ptr;if_line= if_line_field(p);
cur_if= subtype(p);if_limit= type(p);cond_ptr= link(p);
free_node(p,if_node_size);
}

/*:495*/
#line 10265 "texprof.w"
;
}

/*:499*/
#line 10246 "texprof.w"
;
common_ending:if(cur_chr==fi_code)/*495:*/
#line 10195 "texprof.w"

{if(if_stack[in_open]==cond_ptr)if_warning();

p= cond_ptr;if_line= if_line_field(p);
cur_if= subtype(p);if_limit= type(p);cond_ptr= link(p);
free_node(p,if_node_size);
}

/*:495*/
#line 10247 "texprof.w"

else if_limit= fi_code;
}

/*:497*//*514:*/
#line 10530 "texprof.w"
static bool quoted_filename;
static void begin_name(void)
{area_delimiter= 0;ext_delimiter= 0;quoted_filename= false;
}

/*:514*//*515:*/
#line 10541 "texprof.w"
static bool more_name(ASCII_code c)
{if(c==' '&&!quoted_filename)return false;
else if(c=='"'){quoted_filename= !quoted_filename;return true;}
else{str_room(1);append_char(c);
if(IS_DIR_SEP(c)){area_delimiter= cur_length;ext_delimiter= 0;}
else if(c=='.')ext_delimiter= cur_length;
return true;
}
}

/*:515*//*516:*/
#line 10554 "texprof.w"
static void end_name(void)
{if(str_ptr+3> max_strings)
overflow("number of strings",max_strings-init_str_ptr);

if(area_delimiter==0)cur_area= empty_string;
else{cur_area= str_ptr;
str_start[str_ptr+1]= str_start[str_ptr]+area_delimiter;incr(str_ptr);
}
if(ext_delimiter==0)
{cur_ext= empty_string;cur_name= make_string();
}
else{cur_name= str_ptr;
str_start[str_ptr+1]= str_start[str_ptr]+ext_delimiter-area_delimiter-1;
incr(str_ptr);cur_ext= make_string();
}
}

/*:516*//*518:*/
#line 10591 "texprof.w"
static void pack_file_name(str_number n,str_number a,str_number e,char*f)
{int k;
ASCII_code c;
int j;
k= 0;
for(j= str_start[a];j<=str_start[a+1]-1;j++)append_to_name(so(str_pool[j]))
for(j= str_start[n];j<=str_start[n+1]-1;j++)append_to_name(so(str_pool[j]))
if(f==NULL)
for(j= str_start[e];j<=str_start[e+1]-1;j++)append_to_name(so(str_pool[j]))
else
while(*f!=0)append_to_name(so(*f++))
if(k<=file_name_size)name_length= k;else name_length= file_name_size;
name_of_file[name_length+1]= 0;
}



/*:518*//*524:*/
#line 10645 "texprof.w"
static str_number make_name_string(void)
{int k;
if((pool_ptr+name_length> pool_size)||(str_ptr==max_strings)||
(cur_length> 0))
return'?';
else{for(k= 1;k<=name_length;k++)append_char(xord[name_of_file[k]]);
return make_string();
}
}
static str_number a_make_name_string(alpha_file*f)
{return make_name_string();
}
static str_number b_make_name_string(byte_file*f)
{return make_name_string();
}
#ifdef INIT
static str_number w_make_name_string(word_file*f)
{return make_name_string();
}
#endif
#line 10665 "texprof.w"

/*:524*//*525:*/
#line 10685 "texprof.w"
static void scan_file_name(void)
{
pool_pointer j,k;
int old_setting;
name_in_progress= true;begin_name();
/*403:*/
#line 8617 "texprof.w"

do{get_x_token();
}while(!((cur_cmd!=spacer)&&(cur_cmd!=relax)))

/*:403*/
#line 10690 "texprof.w"
;
if(cur_cmd==left_brace)
/*1707:*/
#line 30117 "texprof.w"

{back_input();name_in_progress= false;
cur_cs= input_loc;
scan_general_x_text();
old_setting= selector;selector= new_string;
token_show(link(garbage));selector= old_setting;
/*1708:*/
#line 30137 "texprof.w"

for(k= j= str_start[str_ptr];k<pool_ptr;k++){
if(str_pool[k]!='"'){str_pool[j]= str_pool[k];incr(j);}
}
pool_ptr= j;

/*:1708*/
#line 30123 "texprof.w"

j= pool_ptr-1;while((j>=str_start[str_ptr])&&(area_delimiter==0))
{
if((str_pool[j]=='/'))area_delimiter= j-str_start[str_ptr];
if((ext_delimiter==0)&&(str_pool[j]=='.'))
ext_delimiter= j-str_start[str_ptr];
decr(j);
}
flush_list(link(garbage));
goto done;
}

/*:1707*/
#line 10692 "texprof.w"

loop{if((cur_cmd> other_char)||(cur_chr> 255))
{back_input();goto done;
}
#if 0





if(cur_chr==' '&&state!=token_list&&loc> limit)goto done;
#endif
#line 10704 "texprof.w"
 if(!more_name(cur_chr))goto done;
get_x_token();
}
done:end_name();name_in_progress= false;
}

/*:525*//*528:*/
#line 10741 "texprof.w"
static void pack_job_name(char*s)

{cur_area= empty_string;cur_ext= empty_string;
cur_name= job_name;pack_cur_name(s);
}

/*:528*//*529:*/
#line 10758 "texprof.w"
static void prompt_file_name(char*s,char*e)
{
int k;
if(interaction==scroll_mode)wake_up_terminal;
if(strcmp(s,"input file name")==0)print_err("I can't find file `");

else print_err("I can't write on file `");

print_file_name(cur_name,cur_area,cur_ext);print("'.");
if(strcmp(e,".tex")==0)show_context();
print_nl("Please type another ");print(s);

if(interaction<scroll_mode)
fatal_error("*** (job aborted, file error in nonstop mode)");

clear_terminal;prompt_input(": ");/*530:*/
#line 10777 "texprof.w"

{
begin_name();k= first;
while((buffer[k]==' ')&&(k<last))incr(k);
loop{if(k==last)goto done;
if(!more_name(buffer[k]))goto done;
incr(k);
}
done:end_name();
}

/*:530*/
#line 10773 "texprof.w"
;
pack_cur_name(e);
}

/*:529*//*533:*/
#line 10809 "texprof.w"
static void open_log_file(void)
{int old_setting;
int k;
int l;
char months[]= " JANFEBMARAPRMAYJUNJULAUGSEPOCTNOVDEC";
old_setting= selector;
if(job_name==0)job_name= s_no(c_job_name?c_job_name:"texput");
pack_job_name(".fls");
recorder_change_filename((char*)name_of_file+1);

pack_job_name(".log");
while(!a_open_out(&log_file))/*534:*/
#line 10848 "texprof.w"

{selector= term_only;
prompt_file_name("transcript file name",".log");
}

/*:534*/
#line 10820 "texprof.w"
;
log_name= a_make_name_string(&log_file);
selector= log_only;log_opened= true;
/*535:*/
#line 10853 "texprof.w"

{wlog("%s",banner);
slow_print(format_ident);print("  ");
print_int(sys_day);print_char(' ');
for(k= 3*sys_month-2;k<=3*sys_month;k++)wlog("%c",months[k]);
print_char(' ');print_int(sys_year);print_char(' ');
print_two(sys_time/60);print_char(':');print_two(sys_time%60);
if(eTeX_ex)
{;wlog_cr;wlog("entering extended mode");
}
if(Prote_ex)
{;wlog_cr;wlog("entering Prote mode");
}
}

/*:535*/
#line 10823 "texprof.w"
;
input_stack[input_ptr]= cur_input;
print_nl("**");

l= input_stack[0].limit_field;
if(buffer[l]==end_line_char)decr(l);
for(k= 1;k<=l;k++)printn(buffer[k]);
print_ln();
selector= old_setting+2;
}

/*:533*//*536:*/
#line 10874 "texprof.w"
static void start_input(void)
{
scan_file_name();
pack_cur_name("");
loop{begin_file_reading();
if(kpse_in_name_ok((char*)name_of_file+1)&&a_open_in(&cur_file))goto done;
end_file_reading();
prompt_file_name("input file name",".tex");
}
done:name= a_make_name_string(&cur_file);
if(source_filename_stack[in_open]!=NULL)
free(source_filename_stack[in_open]);
source_filename_stack[in_open]= strdup((char*)name_of_file+1);
if(full_source_filename_stack[in_open]!=NULL)
free(full_source_filename_stack[in_open]);
full_source_filename_stack[in_open]= strdup(full_name_of_file);
/*1749:*/
#line 31092 "texprof.w"

/*1748:*/
#line 31083 "texprof.w"

if(file_num>=MAX_FILE_NUM)overflow("file number",file_num);
else file_num++;
file_num_name[file_num]= strdup(full_name_of_file);
file_from_cmd[file_num]= cmd_count;

/*:1748*/
#line 31093 "texprof.w"

cur_file_num= file_num;

/*:1749*/
#line 10890 "texprof.w"


{/*1776:*/
#line 31583 "texprof.w"

uint32_t macro_fl= FILE_LINE(cur_file_num,0);
int macro_cs= 0;
int macro_depth= cur_depth;

/*:1776*/
#line 10892 "texprof.w"

/*1775:*/
#line 31573 "texprof.w"

macro_depth++;
cur_depth= macro_depth;
if(macro_depth>=MAX_MACRO_STACK)
overflow("macro stack size",macro_depth);
macro_stack[macro_depth]= CALL_INFO(macro_depth,macro_cs,macro_fl);
if(macro_depth<=unchanged_depth)
unchanged_depth= macro_depth-1;

/*:1775*/
#line 10893 "texprof.w"

}
if(job_name==0)
{if(c_job_name==NULL)job_name= cur_name;
else job_name= s_no(c_job_name);open_log_file();
}

if(term_offset+strlen(full_source_filename_stack[in_open])> max_print_line-2)
print_ln();
else if((term_offset> 0)||(file_offset> 0))print_char(' ');
print_char('(');incr(open_parens);
print(full_source_filename_stack[in_open]);update_terminal;
state= new_line;
if(name==str_ptr-1)
{flush_string;name= cur_name;
}
/*537:*/
#line 10918 "texprof.w"

{line= 1;
if(input_ln(&cur_file,false))do_nothing;
firm_up_the_line();
if(end_line_char_inactive)decr(limit);
else buffer[limit]= end_line_char;
first= limit+1;loc= start;
}

/*:537*/
#line 10909 "texprof.w"
;
}

/*:536*//*559:*/
#line 11440 "texprof.w"
static internal_font_number read_font_info(pointer u,str_number nom,str_number aire,
scaled s)
{
int k;
bool file_opened;
halfword lf,lh,bc,ec,nw,nh,nd,ni,nl,nk,ne,np;

internal_font_number f;
internal_font_number g;
eight_bits a,b,c,d;
four_quarters qw;scaled sw;
int bch_label;
int bchar;
scaled z;
int alpha;int beta;

g= null_font;
/*561:*/
#line 11493 "texprof.w"

/*562:*/
#line 11505 "texprof.w"

file_opened= false;
pack_file_name(nom,empty_string,empty_string,".tfm");
if(!b_open_in(&tfm_file))abort;
file_opened= true

/*:562*/
#line 11494 "texprof.w"
;
/*564:*/
#line 11532 "texprof.w"

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

/*:564*/
#line 11495 "texprof.w"
;
/*565:*/
#line 11559 "texprof.w"

lf= lf-6-lh;
if(np<7)lf= lf+7-np;
if((font_ptr==font_max)||(fmem_ptr+lf> font_mem_size))
/*566:*/
#line 11575 "texprof.w"

{start_font_error_message;
print(" not loaded: Not enough room left");

help4("I'm afraid I won't be able to make use of this font,",
"because my memory for character-size data is too small.",
"If you're really stuck, ask a wizard to enlarge me.",
"Or maybe try `I\\font<same font id>=<name of loaded font>'.");
error();goto done;
}

/*:566*/
#line 11563 "texprof.w"
;
f= font_ptr+1;
char_base[f]= fmem_ptr-bc;
width_base[f]= char_base[f]+ec+1;
height_base[f]= width_base[f]+nw;
depth_base[f]= height_base[f]+nh;
italic_base[f]= depth_base[f]+nd;
lig_kern_base[f]= italic_base[f]+ni;
kern_base[f]= lig_kern_base[f]+nl-kern_base_offset;
exten_base[f]= kern_base[f]+kern_base_offset+nk;
param_base[f]= exten_base[f]+ne

/*:565*/
#line 11496 "texprof.w"
;
/*567:*/
#line 11588 "texprof.w"

{if(lh<2)abort;
store_four_quarters(font_check[f]);
fget;read_sixteen(z);
fget;z= z*0400+fbyte;fget;z= (z*020)+(fbyte/020);
if(z<unity)abort;
while(lh> 2)
{fget;fget;fget;fget;decr(lh);
}
font_dsize[f]= z;
if(s!=-1000)
if(s>=0)z= s;
else z= xn_over_d(z,-s,1000);
font_size[f]= z;
}

/*:567*/
#line 11497 "texprof.w"
;
/*568:*/
#line 11604 "texprof.w"

for(k= fmem_ptr;k<=width_base[f]-1;k++)
{store_four_quarters(font_info[k].qqqq);
if((a>=nw)||(b/020>=nh)||(b%020>=nd)||
(c/4>=ni))abort;
switch(c%4){
case lig_tag:if(d>=nl)abort;break;
case ext_tag:if(d>=ne)abort;break;
case list_tag:/*569:*/
#line 11625 "texprof.w"

{check_byte_range(d);
while(d<current_character_being_worked_on)
{qw= char_info(f,d);

if(char_tag(qw)!=list_tag)goto not_found;
d= qo(rem_byte(qw));
}
if(d==current_character_being_worked_on)abort;
not_found:;}

/*:569*/
#line 11612 "texprof.w"
break;
default:do_nothing;
}
}

/*:568*/
#line 11498 "texprof.w"
;
/*570:*/
#line 11660 "texprof.w"

{/*571:*/
#line 11670 "texprof.w"

{alpha= 16;
while(z>=040000000)
{z= z/2;alpha= alpha+alpha;
}
beta= 256/alpha;alpha= alpha*z;
}

/*:571*/
#line 11661 "texprof.w"
;
for(k= width_base[f];k<=lig_kern_base[f]-1;k++)
store_scaled(font_info[k].sc);
if(font_info[width_base[f]].sc!=0)abort;
if(font_info[height_base[f]].sc!=0)abort;
if(font_info[depth_base[f]].sc!=0)abort;
if(font_info[italic_base[f]].sc!=0)abort;
}

/*:570*/
#line 11499 "texprof.w"
;
/*572:*/
#line 11684 "texprof.w"

bch_label= 077777;bchar= 256;
if(nl> 0)
{for(k= lig_kern_base[f];k<=kern_base[f]+kern_base_offset-1;k++)
{store_four_quarters(font_info[k].qqqq);
if(a> 128)
{if(256*c+d>=nl)abort;
if(a==255)if(k==lig_kern_base[f])bchar= b;
}
else{if(b!=bchar)check_existence(b);
if(c<128)check_existence(d)
else if(256*(c-128)+d>=nk)abort;
if(a<128)if(k-lig_kern_base[f]+a+1>=nl)abort;
}
}
if(a==255)bch_label= 256*c+d;
}
for(k= kern_base[f]+kern_base_offset;k<=exten_base[f]-1;k++)
store_scaled(font_info[k].sc);

/*:572*/
#line 11500 "texprof.w"
;
/*573:*/
#line 11704 "texprof.w"

for(k= exten_base[f];k<=param_base[f]-1;k++)
{store_four_quarters(font_info[k].qqqq);
if(a!=0)check_existence(a);
if(b!=0)check_existence(b);
if(c!=0)check_existence(c);
check_existence(d);
}

/*:573*/
#line 11501 "texprof.w"
;
/*574:*/
#line 11716 "texprof.w"

{for(k= 1;k<=np;k++)
if(k==1)
{fget;sw= fbyte;if(sw> 127)sw= sw-256;
fget;sw= sw*0400+fbyte;fget;sw= sw*0400+fbyte;
fget;font_info[param_base[f]].sc= 
(sw*020)+(fbyte/020);
}
else store_scaled(font_info[param_base[f]+k-1].sc);
if(eof(tfm_file))abort;
for(k= np+1;k<=7;k++)font_info[param_base[f]+k-1].sc= 0;
}

/*:574*/
#line 11502 "texprof.w"
;
/*575:*/
#line 11736 "texprof.w"

if(np>=7)font_params[f]= np;else font_params[f]= 7;
hyphen_char[f]= default_hyphen_char;skew_char[f]= default_skew_char;
if(bch_label<nl)bchar_label[f]= bch_label+lig_kern_base[f];
else bchar_label[f]= non_address;
font_bchar[f]= qi(bchar);
font_false_bchar[f]= qi(bchar);
if(bchar<=ec)if(bchar>=bc)
{qw= char_info(f,bchar);
if(char_exists(qw))font_false_bchar[f]= non_char;
}
font_name[f]= nom;
font_area[f]= aire;
font_bc[f]= bc;font_ec[f]= ec;font_glue[f]= null;
adjust(char_base);adjust(width_base);adjust(lig_kern_base);
adjust(kern_base);adjust(exten_base);
decr(param_base[f]);
fmem_ptr= fmem_ptr+lf;font_ptr= f;g= f;goto done

/*:575*/
#line 11503 "texprof.w"


/*:561*/
#line 11459 "texprof.w"
;
bad_tfm:/*560:*/
#line 11481 "texprof.w"

start_font_error_message;

if(file_opened)print(" not loadable: Bad metric (TFM) file");
else print(" not loadable: Metric (TFM) file not found");
help5("I wasn't able to read the size data for this font,",
"so I will ignore the font specification.",
"[Wizards can fix TFM files using TFtoPL/PLtoTF.]",
"You might try inserting a different font spec;",
"e.g., type `I\\font<same font id>=<substitute font name>'.");
error()

/*:560*/
#line 11460 "texprof.w"
;
done:if(file_opened)b_close(&tfm_file);
return g;
}

/*:559*//*580:*/
#line 11826 "texprof.w"
static void char_warning(internal_font_number f,eight_bits c)
{int old_setting;
if(tracing_lost_chars> 0)
{old_setting= tracing_online;
if(eTeX_ex&&(tracing_lost_chars> 1))tracing_online= 1;
{begin_diagnostic();
print_nl("Missing character: There is no ");

print_ASCII(c);print(" in font ");
slow_print(font_name[f]);print_char('!');end_diagnostic(false);
}
tracing_online= old_setting;
}
}

/*:580*//*581:*/
#line 11845 "texprof.w"
static pointer new_character(internal_font_number f,eight_bits c)
{
pointer p;
if(font_bc[f]<=c)if(font_ec[f]>=c)
if(char_exists(char_info(f,qi(c))))
{p= get_avail();font(p)= f;character(p)= qi(c);
return p;
}
char_warning(f,c);
return null;
}

/*:581*//*596:*/
#line 12455 "texprof.w"
static void write_dvi(dvi_index a,dvi_index b)
{int k;
for(k= a;k<=b;k++)pascal_write(dvi_file,"%c",dvi_buf[k]);
}

/*:596*//*597:*/
#line 12467 "texprof.w"
static void dvi_swap(void)
{if(dvi_limit==dvi_buf_size)
{write_dvi(0,half_buf-1);dvi_limit= half_buf;
dvi_offset= dvi_offset+dvi_buf_size;dvi_ptr= 0;
}
else{write_dvi(half_buf,dvi_buf_size-1);dvi_limit= dvi_buf_size;
}
dvi_gone= dvi_gone+half_buf;
}

/*:597*//*599:*/
#line 12487 "texprof.w"
static void dvi_four(int x)
{if(x>=0)dvi_out(x/0100000000)
else{x= x+010000000000;
x= x+010000000000;
dvi_out((x/0100000000)+128);
}
x= x%0100000000;dvi_out(x/0200000);
x= x%0200000;dvi_out(x/0400);
dvi_out(x%0400);
}

/*:599*//*600:*/
#line 12503 "texprof.w"
static void dvi_pop(int l)
{if((l==dvi_offset+dvi_ptr)&&(dvi_ptr> 0))decr(dvi_ptr);
else dvi_out(pop);
}

/*:600*//*601:*/
#line 12511 "texprof.w"
static void dvi_font_def(internal_font_number f)
{int k;
dvi_out(fnt_def1);
dvi_out(f-font_base-1);
dvi_out(qo(font_check[f].b0));
dvi_out(qo(font_check[f].b1));
dvi_out(qo(font_check[f].b2));
dvi_out(qo(font_check[f].b3));
dvi_four(font_size[f]);
dvi_four(font_dsize[f]);
dvi_out(length(font_area[f]));
dvi_out(length(font_name[f]));
/*602:*/
#line 12526 "texprof.w"

for(k= str_start[font_area[f]];k<=str_start[font_area[f]+1]-1;k++)
dvi_out(so(str_pool[k]));
for(k= str_start[font_name[f]];k<=str_start[font_name[f]+1]-1;k++)
dvi_out(so(str_pool[k]))

/*:602*/
#line 12523 "texprof.w"
;
}

/*:601*//*606:*/
#line 12605 "texprof.w"
static void movement(scaled w,eight_bits o)
{
small_number mstate;
pointer p,q;
int k;
q= get_node(movement_node_size);
width(q)= w;location(q)= dvi_offset+dvi_ptr;
if(o==down1)
{link(q)= down_ptr;down_ptr= q;
}
else{link(q)= right_ptr;right_ptr= q;
}
/*610:*/
#line 12721 "texprof.w"

p= link(q);mstate= none_seen;
while(p!=null)
{if(width(p)==w)/*611:*/
#line 12740 "texprof.w"

switch(mstate+info(p)){
case none_seen+yz_OK:case none_seen+y_OK:
case z_seen+yz_OK:case z_seen+y_OK:
if(location(p)<dvi_gone)goto not_found;
else/*612:*/
#line 12755 "texprof.w"

{k= location(p)-dvi_offset;
if(k<0)k= k+dvi_buf_size;
dvi_buf[k]= dvi_buf[k]+y1-down1;
info(p)= y_here;goto found;
}

/*:612*/
#line 12745 "texprof.w"
break;
case none_seen+z_OK:case y_seen+yz_OK:
case y_seen+z_OK:
if(location(p)<dvi_gone)goto not_found;
else/*613:*/
#line 12762 "texprof.w"

{k= location(p)-dvi_offset;
if(k<0)k= k+dvi_buf_size;
dvi_buf[k]= dvi_buf[k]+z1-down1;
info(p)= z_here;goto found;
}

/*:613*/
#line 12749 "texprof.w"
break;
case none_seen+y_here:case none_seen+z_here:
case y_seen+z_here:case z_seen+y_here:goto found;
default:do_nothing;
}

/*:611*/
#line 12725 "texprof.w"

else switch(mstate+info(p)){
case none_seen+y_here:mstate= y_seen;break;
case none_seen+z_here:mstate= z_seen;break;
case y_seen+z_here:case z_seen+y_here:goto not_found;
default:do_nothing;
}
p= link(p);
}
not_found:

/*:610*/
#line 12618 "texprof.w"
;
/*609:*/
#line 12688 "texprof.w"

info(q)= yz_OK;
if(abs(w)>=040000000)
{dvi_out(o+3);
dvi_four(w);return;
}
if(abs(w)>=0100000)
{dvi_out(o+2);
if(w<0)w= w+0100000000;
dvi_out(w/0200000);w= w%0200000;goto label2;
}
if(abs(w)>=0200)
{dvi_out(o+1);
if(w<0)w= w+0200000;
goto label2;
}
dvi_out(o);
if(w<0)w= w+0400;
goto label1;
label2:dvi_out(w/0400);
label1:dvi_out(w%0400);return

/*:609*/
#line 12619 "texprof.w"
;
found:/*608:*/
#line 12664 "texprof.w"

info(q)= info(p);
if(info(q)==y_here)
{dvi_out(o+y0-down1);
while(link(q)!=p)
{q= link(q);
switch(info(q)){
case yz_OK:info(q)= z_OK;break;
case y_OK:info(q)= d_fixed;break;
default:do_nothing;
}
}
}
else{dvi_out(o+z0-down1);
while(link(q)!=p)
{q= link(q);
switch(info(q)){
case yz_OK:info(q)= y_OK;break;
case z_OK:info(q)= d_fixed;break;
default:do_nothing;
}
}
}

/*:608*/
#line 12621 "texprof.w"
;
}

/*:606*//*614:*/
#line 12775 "texprof.w"
static void prune_movements(int l)

{
pointer p;
while(down_ptr!=null)
{if(location(down_ptr)<l)goto done;
p= down_ptr;down_ptr= link(p);free_node(p,movement_node_size);
}
done:while(right_ptr!=null)
{if(location(right_ptr)<l)return;
p= right_ptr;right_ptr= link(p);free_node(p,movement_node_size);
}
}

/*:614*//*617:*/
#line 12852 "texprof.w"
static void vlist_out(void);


/*:617*//*618:*/
#line 12861 "texprof.w"
/*1367:*/
#line 25670 "texprof.w"

static void special_out(pointer p)
{pointer q,r;
int old_mode;

if(subtype(p)==latespecial_node)
{/*1370:*/
#line 25722 "texprof.w"

q= get_avail();info(q)= right_brace_token+'}';
fl_mem[q]= FILE_LINE(system_file,system_insert);
r= get_avail();link(q)= r;info(r)= end_write_token;ins_list(q);
fl_mem[r]= FILE_LINE(system_file,system_insert);
begin_token_list(write_tokens(p),write_text);
q= get_avail();info(q)= left_brace_token+'{';ins_list(q);
fl_mem[q]= FILE_LINE(system_file,system_insert);



old_mode= mode;mode= 0;

cur_cs= write_loc;q= scan_toks(false,true);
get_token();if(cur_tok!=end_write_token)
/*1371:*/
#line 25741 "texprof.w"

{print_err("Unbalanced write command");

help2("On this page there's a \\write with fewer real {'s than }'s.",
"I can't handle that very well; good luck.");error();
do{get_token();
}while(!(cur_tok==end_write_token));
}

/*:1371*/
#line 25737 "texprof.w"
;
mode= old_mode;
end_token_list()

/*:1370*/
#line 25677 "texprof.w"
;
write_tokens(p)= def_ref;
}
}

/*:1367*//*1369:*/
#line 25695 "texprof.w"

static void write_out(pointer p)
{int old_setting;
int old_mode;
small_number j;
pointer q,r;
/*1370:*/
#line 25722 "texprof.w"

q= get_avail();info(q)= right_brace_token+'}';
fl_mem[q]= FILE_LINE(system_file,system_insert);
r= get_avail();link(q)= r;info(r)= end_write_token;ins_list(q);
fl_mem[r]= FILE_LINE(system_file,system_insert);
begin_token_list(write_tokens(p),write_text);
q= get_avail();info(q)= left_brace_token+'{';ins_list(q);
fl_mem[q]= FILE_LINE(system_file,system_insert);



old_mode= mode;mode= 0;

cur_cs= write_loc;q= scan_toks(false,true);
get_token();if(cur_tok!=end_write_token)
/*1371:*/
#line 25741 "texprof.w"

{print_err("Unbalanced write command");

help2("On this page there's a \\write with fewer real {'s than }'s.",
"I can't handle that very well; good luck.");error();
do{get_token();
}while(!(cur_tok==end_write_token));
}

/*:1371*/
#line 25737 "texprof.w"
;
mode= old_mode;
end_token_list()

/*:1370*/
#line 25701 "texprof.w"
;
old_setting= selector;j= write_stream(p);
if(write_open[j])selector= j;
else{
if((j==17)&&(selector==term_and_log))selector= log_only;
print_nl("");
}
token_show(def_ref);print_ln();
flush_list(def_ref);selector= old_setting;
}

/*:1369*//*1372:*/
#line 25753 "texprof.w"

/*1683:*/
#line 29704 "texprof.w"

static void save_pos_out(pointer p)
{int old_setting;
int k;
synch_h;synch_v;incr(last_save_pos_number);
/*1670:*/
#line 29605 "texprof.w"

last_saved_xpos= cur_h+DVI_std_x_offset;
last_saved_ypos= page_height-(cur_v+DVI_std_y_offset);

/*:1670*/
#line 29709 "texprof.w"

old_setting= selector;selector= new_string;
print("warning __PROTE_");print("SAVEPOS");print_char('=');
print_int(last_save_pos_number);print_char(' ');
print("XPOS");print("=");print_int(last_saved_xpos);print_char(' ');
print("YPOS");print("=");print_int(last_saved_ypos);
selector= old_setting;
str_room(1);
dvi_out(xxx1);dvi_out(cur_length);
for(k= str_start[str_ptr];k<=pool_ptr-1;k++)dvi_out(so(str_pool[k]));
pool_ptr= str_start[str_ptr];
}

/*:1683*/
#line 25754 "texprof.w"

static void out_what(pointer p)
{small_number j;
switch(subtype(p)){
case open_node:case write_node:case close_node:/*1373:*/
#line 25773 "texprof.w"

if(!doing_leaders)
{j= write_stream(p);
if(subtype(p)==write_node)write_out(p);
else{if(write_open[j])a_close(&write_file[j]);
if(subtype(p)==close_node)write_open[j]= false;
else if(j<16)
{cur_name= open_name(p);cur_area= open_area(p);
cur_ext= open_ext(p);
pack_cur_name(".tex");
while(!a_open_out(&write_file[j]))
prompt_file_name("output file name",".tex");
write_open[j]= true;
}
}
}

/*:1373*/
#line 25759 "texprof.w"
break;
case special_node:special_out(p);break;
case language_node:do_nothing;break;
/*1684:*/
#line 29722 "texprof.w"

case save_pos_code:save_pos_out(p);break;

/*:1684*/
#line 25762 "texprof.w"

default:confusion("ext4");

}
}

/*:1372*/
#line 12861 "texprof.w"

static void hlist_out(void)
{
scaled base_line;
scaled left_edge;
scaled save_h,save_v;
pointer this_box;
glue_ord g_order;
int g_sign;
pointer p;
int save_loc;
pointer leader_box;
scaled leader_wd;
scaled lx;
bool outer_doing_leaders;
scaled edge;
double glue_temp;
double cur_glue;
scaled cur_g;
cur_g= 0;cur_glue= float_constant(0);
this_box= temp_ptr;g_order= glue_order(this_box);
g_sign= glue_sign(this_box);p= list_ptr(this_box);
incr(cur_s);
if(cur_s> 0)dvi_out(push);
if(cur_s> max_push)max_push= cur_s;
save_loc= dvi_offset+dvi_ptr;base_line= cur_v;left_edge= cur_h;
while(p!=null)/*619:*/
#line 12900 "texprof.w"

reswitch:if(is_char_node(p))
{synch_h;synch_v;
do{f= font(p);c= character(p);
if(f!=dvi_f)/*620:*/
#line 12915 "texprof.w"

{if(!font_used[f])
{dvi_font_def(f);font_used[f]= true;
}
if(f<=64+font_base)dvi_out(f-font_base-1+fnt_num_0)
else{dvi_out(fnt1);dvi_out(f-font_base-1);
}
dvi_f= f;
}

/*:620*/
#line 12904 "texprof.w"
;
if(c>=qi(128))dvi_out(set1);
dvi_out(qo(c));
cur_h= cur_h+char_width(f,char_info(f,c));
p= link(p);
}while(!(!is_char_node(p)));
dvi_h= cur_h;
}
else/*621:*/
#line 12925 "texprof.w"

{switch(type(p)){
case hlist_node:case vlist_node:/*622:*/
#line 12943 "texprof.w"

if(list_ptr(p)==null)cur_h= cur_h+width(p);
else{save_h= dvi_h;save_v= dvi_v;
cur_v= base_line+shift_amount(p);
temp_ptr= p;edge= cur_h;
if(type(p)==vlist_node)vlist_out();else hlist_out();
dvi_h= save_h;dvi_v= save_v;
cur_h= edge+width(p);cur_v= base_line;
}

/*:622*/
#line 12927 "texprof.w"
break;
case rule_node:{rule_ht= height(p);rule_dp= depth(p);rule_wd= width(p);
goto fin_rule;
}
case whatsit_node:/*1366:*/
#line 25663 "texprof.w"

out_what(p)

/*:1366*/
#line 12931 "texprof.w"
;break;
case glue_node:/*624:*/
#line 12970 "texprof.w"

{g= glue_ptr(p);rule_wd= width(g)-cur_g;
if(g_sign!=normal)
{if(g_sign==stretching)
{if(stretch_order(g)==g_order)
{cur_glue= cur_glue+stretch(g);
vet_glue(unfix(glue_set(this_box))*cur_glue);

cur_g= round(glue_temp);
}
}
else if(shrink_order(g)==g_order)
{cur_glue= cur_glue-shrink(g);
vet_glue(unfix(glue_set(this_box))*cur_glue);
cur_g= round(glue_temp);
}
}
rule_wd= rule_wd+cur_g;
if(subtype(p)>=a_leaders)
/*625:*/
#line 12994 "texprof.w"

{leader_box= leader_ptr(p);
if(type(leader_box)==rule_node)
{rule_ht= height(leader_box);rule_dp= depth(leader_box);
goto fin_rule;
}
leader_wd= width(leader_box);
if((leader_wd> 0)&&(rule_wd> 0))
{rule_wd= rule_wd+10;
edge= cur_h+rule_wd;lx= 0;
/*626:*/
#line 13028 "texprof.w"

if(subtype(p)==a_leaders)
{save_h= cur_h;
cur_h= left_edge+leader_wd*((cur_h-left_edge)/leader_wd);
if(cur_h<save_h)cur_h= cur_h+leader_wd;
}
else{lq= rule_wd/leader_wd;
lr= rule_wd%leader_wd;
if(subtype(p)==c_leaders)cur_h= cur_h+(lr/2);
else{lx= lr/(lq+1);
cur_h= cur_h+((lr-(lq-1)*lx)/2);
}
}

/*:626*/
#line 13005 "texprof.w"
;
while(cur_h+leader_wd<=edge)
/*627:*/
#line 13045 "texprof.w"

{cur_v= base_line+shift_amount(leader_box);synch_v;save_v= dvi_v;
synch_h;save_h= dvi_h;temp_ptr= leader_box;
outer_doing_leaders= doing_leaders;doing_leaders= true;
if(type(leader_box)==vlist_node)vlist_out();else hlist_out();
doing_leaders= outer_doing_leaders;
dvi_v= save_v;dvi_h= save_h;cur_v= base_line;
cur_h= save_h+leader_wd+lx;
}

/*:627*/
#line 13007 "texprof.w"
;
cur_h= edge-10;goto next_p;
}
}

/*:625*/
#line 12990 "texprof.w"
;
goto move_past;
}

/*:624*/
#line 12932 "texprof.w"

case kern_node:case math_node:cur_h= cur_h+width(p);break;
case ligature_node:/*651:*/
#line 13507 "texprof.w"

{mem[lig_trick]= mem[lig_char(p)];link(lig_trick)= link(p);
p= lig_trick;goto reswitch;
}

/*:651*/
#line 12934 "texprof.w"

default:do_nothing;
}
goto next_p;
fin_rule:/*623:*/
#line 12953 "texprof.w"

if(is_running(rule_ht))rule_ht= height(this_box);
if(is_running(rule_dp))rule_dp= depth(this_box);
rule_ht= rule_ht+rule_dp;
if((rule_ht> 0)&&(rule_wd> 0))
{synch_h;cur_v= base_line+rule_dp;synch_v;
dvi_out(set_rule);dvi_four(rule_ht);dvi_four(rule_wd);
cur_v= base_line;dvi_h= dvi_h+rule_wd;
}

/*:623*/
#line 12938 "texprof.w"
;
move_past:cur_h= cur_h+rule_wd;
next_p:p= link(p);
}

/*:621*/
#line 12913 "texprof.w"


/*:619*/
#line 12888 "texprof.w"
;
prune_movements(save_loc);
if(cur_s> 0)dvi_pop(save_loc);
decr(cur_s);
}

/*:618*//*628:*/
#line 13057 "texprof.w"
static void vlist_out(void)
{
scaled left_edge;
scaled top_edge;
scaled save_h,save_v;
pointer this_box;
glue_ord g_order;
int g_sign;
pointer p;
int save_loc;
pointer leader_box;
scaled leader_ht;
scaled lx;
bool outer_doing_leaders;
scaled edge;
double glue_temp;
double cur_glue;
scaled cur_g;
cur_g= 0;cur_glue= float_constant(0);
this_box= temp_ptr;g_order= glue_order(this_box);
g_sign= glue_sign(this_box);p= list_ptr(this_box);
incr(cur_s);
if(cur_s> 0)dvi_out(push);
if(cur_s> max_push)max_push= cur_s;
save_loc= dvi_offset+dvi_ptr;left_edge= cur_h;cur_v= cur_v-height(this_box);
top_edge= cur_v;
while(p!=null)/*629:*/
#line 13090 "texprof.w"

{if(is_char_node(p))confusion("vlistout");

else/*630:*/
#line 13097 "texprof.w"

{switch(type(p)){
case hlist_node:case vlist_node:/*631:*/
#line 13117 "texprof.w"

if(list_ptr(p)==null)cur_v= cur_v+height(p)+depth(p);
else{cur_v= cur_v+height(p);synch_v;
save_h= dvi_h;save_v= dvi_v;
cur_h= left_edge+shift_amount(p);
temp_ptr= p;
if(type(p)==vlist_node)vlist_out();else hlist_out();
dvi_h= save_h;dvi_v= save_v;
cur_v= save_v+depth(p);cur_h= left_edge;
}

/*:631*/
#line 13099 "texprof.w"
break;
case rule_node:{rule_ht= height(p);rule_dp= depth(p);rule_wd= width(p);
goto fin_rule;
}
case whatsit_node:/*1365:*/
#line 25660 "texprof.w"

out_what(p)

/*:1365*/
#line 13103 "texprof.w"
;break;
case glue_node:/*633:*/
#line 13138 "texprof.w"

{g= glue_ptr(p);rule_ht= width(g)-cur_g;
if(g_sign!=normal)
{if(g_sign==stretching)
{if(stretch_order(g)==g_order)
{cur_glue= cur_glue+stretch(g);
vet_glue(unfix(glue_set(this_box))*cur_glue);

cur_g= round(glue_temp);
}
}
else if(shrink_order(g)==g_order)
{cur_glue= cur_glue-shrink(g);
vet_glue(unfix(glue_set(this_box))*cur_glue);
cur_g= round(glue_temp);
}
}
rule_ht= rule_ht+cur_g;
if(subtype(p)>=a_leaders)
/*634:*/
#line 13162 "texprof.w"

{leader_box= leader_ptr(p);
if(type(leader_box)==rule_node)
{rule_wd= width(leader_box);rule_dp= 0;
goto fin_rule;
}
leader_ht= height(leader_box)+depth(leader_box);
if((leader_ht> 0)&&(rule_ht> 0))
{rule_ht= rule_ht+10;
edge= cur_v+rule_ht;lx= 0;
/*635:*/
#line 13180 "texprof.w"

if(subtype(p)==a_leaders)
{save_v= cur_v;
cur_v= top_edge+leader_ht*((cur_v-top_edge)/leader_ht);
if(cur_v<save_v)cur_v= cur_v+leader_ht;
}
else{lq= rule_ht/leader_ht;
lr= rule_ht%leader_ht;
if(subtype(p)==c_leaders)cur_v= cur_v+(lr/2);
else{lx= lr/(lq+1);
cur_v= cur_v+((lr-(lq-1)*lx)/2);
}
}

/*:635*/
#line 13173 "texprof.w"
;
while(cur_v+leader_ht<=edge)
/*636:*/
#line 13197 "texprof.w"

{cur_h= left_edge+shift_amount(leader_box);synch_h;save_h= dvi_h;
cur_v= cur_v+height(leader_box);synch_v;save_v= dvi_v;
temp_ptr= leader_box;
outer_doing_leaders= doing_leaders;doing_leaders= true;
if(type(leader_box)==vlist_node)vlist_out();else hlist_out();
doing_leaders= outer_doing_leaders;
dvi_v= save_v;dvi_h= save_h;cur_h= left_edge;
cur_v= save_v-height(leader_box)+leader_ht+lx;
}

/*:636*/
#line 13175 "texprof.w"
;
cur_v= edge-10;goto next_p;
}
}

/*:634*/
#line 13158 "texprof.w"
;
goto move_past;
}

/*:633*/
#line 13104 "texprof.w"

case kern_node:cur_v= cur_v+width(p);break;
default:do_nothing;
}
goto next_p;
fin_rule:/*632:*/
#line 13128 "texprof.w"

if(is_running(rule_wd))rule_wd= width(this_box);
rule_ht= rule_ht+rule_dp;
cur_v= cur_v+rule_ht;
if((rule_ht> 0)&&(rule_wd> 0))
{synch_h;synch_v;
dvi_out(put_rule);dvi_four(rule_ht);dvi_four(rule_wd);
}
goto next_p

/*:632*/
#line 13109 "texprof.w"
;
move_past:cur_v= cur_v+rule_ht;
}

/*:630*/
#line 13093 "texprof.w"
;
next_p:p= link(p);
}

/*:629*/
#line 13084 "texprof.w"
;
prune_movements(save_loc);
if(cur_s> 0)dvi_pop(save_loc);
decr(cur_s);
}

/*:628*//*637:*/
#line 13211 "texprof.w"
static void ship_out(pointer p)
{
int page_loc;
int j,k;
int s;
int old_setting;
/*1766:*/
#line 31393 "texprof.w"

int tmp_cmd;
int tmp_file_line;
int tmp_depth;

/*:1766*/
#line 13217 "texprof.w"

/*1771:*/
#line 31442 "texprof.w"

if(profile_on)
{/*1761:*/
#line 31310 "texprof.w"

if(profile_on)
{if(st_count+3> MAX_STAMPS)
overflow("profile data",MAX_STAMPS);
/*1779:*/
#line 31656 "texprof.w"

if(last_depth> prof_depth)
{if(last_depth==prof_depth+1)
prof_cmd= prof_cmd|POP_BIT;
else
stamp[st_count++]= (system_macro_pop<<24)|(last_depth-prof_depth);
#if SHOW_RECORD_TIMING
print_char('{');print_int(cmd_count);
print_char(':');print_int(system_macro_pop);
print_char(':');print_int(last_depth);
print_char('>');print_int(prof_depth);
print_char('}');print_ln();
#endif
#line 31669 "texprof.w"
 cmd_count++;
last_depth= unchanged_depth= prof_depth;
}


/*:1779*/
#line 31314 "texprof.w"

stamp[st_count++]= (prof_cmd<<24)|prof_file_line;
prof_cmd= prof_cmd&~POP_BIT;
#if SHOW_RECORD_TIMING
print_char('<');print_int(cmd_count);
print_char(':');
if(prof_cmd&POP_BIT)print_char('-');
print_int(prof_cmd&~POP_BIT);
print_char(':');print_int(prof_depth);
print_char('>');print_ln();
#endif
#line 31325 "texprof.w"
 cmd_count++;
/*1756:*/
#line 31198 "texprof.w"

#if GETTIME==0
time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#elif GETTIME==1
#line 31202 "texprof.w"
 time_error= clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&ts);
#elif GETTIME==2
#line 31204 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
#elif GETTIME==3
#line 31206 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC,&ts);
#else
#line 31208 "texprof.w"
 time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#endif
#line 31210 "texprof.w"

/*:1756*/
#line 31326 "texprof.w"

/*1757:*/
#line 31215 "texprof.w"

diff_nsec= (ts.tv_sec-start_sec)*1000000000+(ts.tv_nsec-start_nsec);
#if 0
printf("time: %ld %ld %ld\n",diff_nsec,(ts.tv_sec),(ts.tv_nsec));
#endif
#line 31220 "texprof.w"

start_nsec= ts.tv_nsec;
start_sec= ts.tv_sec;

/*:1757*/
#line 31327 "texprof.w"

stamp[st_count++]= diff_nsec;
}


/*:1761*/
#line 31444 "texprof.w"

tmp_file_line= prof_file_line;
tmp_cmd= prof_cmd;
tmp_depth= prof_depth;
prof_file_line= FILE_LINE(system_file,system_ship_out);
prof_cmd= system_cmd;
}


/*:1771*/
#line 13218 "texprof.w"

if(tracing_output> 0)
{print_nl("");print_ln();
print("Completed box being shipped out");

}
if(term_offset> max_print_line-9)print_ln();
else if((term_offset> 0)||(file_offset> 0))print_char(' ');
print_char('[');j= 9;
while((count(j)==0)&&(j> 0))decr(j);
for(k= 0;k<=j;k++)
{print_int(count(k));
if(k<j)print_char('.');
}
update_terminal;
if(tracing_output> 0)
{print_char(']');
begin_diagnostic();show_box(p);end_diagnostic(true);
}
/*639:*/
#line 13264 "texprof.w"

/*640:*/
#line 13281 "texprof.w"

if((height(p)> max_dimen)||(depth(p)> max_dimen)||
(height(p)+depth(p)+v_offset> max_dimen)||
(width(p)+h_offset> max_dimen))
{print_err("Huge page cannot be shipped out");

help2("The page just created is more than 18 feet tall or",
"more than 18 feet wide, so I suspect something went wrong.");
error();
if(tracing_output<=0)
{begin_diagnostic();
print_nl("The following box has been deleted:");

show_box(p);
end_diagnostic(true);
}
goto done;
}
if(height(p)+depth(p)+v_offset> max_v)max_v= height(p)+depth(p)+v_offset;
if(width(p)+h_offset> max_h)max_h= width(p)+h_offset

/*:640*/
#line 13266 "texprof.w"
;
/*616:*/
#line 12825 "texprof.w"

dvi_h= 0;dvi_v= 0;cur_h= h_offset;dvi_f= null_font;
ensure_dvi_open;
if(total_pages==0)
{dvi_out(pre);dvi_out(id_byte);

dvi_four(25400000);dvi_four(473628672);
prepare_mag();dvi_four(mag);
old_setting= selector;selector= new_string;
print(" TeX output ");print_int(year);print_char('.');
print_two(month);print_char('.');print_two(day);
print_char(':');print_two(time/60);
print_two(time%60);
selector= old_setting;dvi_out(cur_length);
for(s= str_start[str_ptr];s<=pool_ptr-1;s++)dvi_out(so(str_pool[s]));
pool_ptr= str_start[str_ptr];
}

/*:616*/
#line 13267 "texprof.w"
;
page_loc= dvi_offset+dvi_ptr;
dvi_out(bop);
for(k= 0;k<=9;k++)dvi_four(count(k));
dvi_four(last_bop);last_bop= page_loc;
cur_v= height(p)+v_offset;temp_ptr= p;
if(type(p)==vlist_node)vlist_out();else hlist_out();
dvi_out(eop);incr(total_pages);cur_s= -1;
done:

/*:639*/
#line 13237 "texprof.w"
;
if(tracing_output<=0)print_char(']');
dead_cycles= 0;
update_terminal;
/*638:*/
#line 13245 "texprof.w"

#ifdef STAT
if(tracing_stats> 1)
{print_nl("Memory usage before: ");

print_int(var_used);print_char('&');
print_int(dyn_used);print_char(';');
}
#endif
#line 13254 "texprof.w"
 flush_node_list(p);
#ifdef STAT
if(tracing_stats> 1)
{print(" after: ");
print_int(var_used);print_char('&');
print_int(dyn_used);print("; still untouched: ");
print_int(hi_mem_min-lo_mem_max-1);print_ln();
}
#endif
#line 13263 "texprof.w"

/*:638*/
#line 13241 "texprof.w"
;
/*1768:*/
#line 31409 "texprof.w"

if(profile_on)
{/*1761:*/
#line 31310 "texprof.w"

if(profile_on)
{if(st_count+3> MAX_STAMPS)
overflow("profile data",MAX_STAMPS);
/*1779:*/
#line 31656 "texprof.w"

if(last_depth> prof_depth)
{if(last_depth==prof_depth+1)
prof_cmd= prof_cmd|POP_BIT;
else
stamp[st_count++]= (system_macro_pop<<24)|(last_depth-prof_depth);
#if SHOW_RECORD_TIMING
print_char('{');print_int(cmd_count);
print_char(':');print_int(system_macro_pop);
print_char(':');print_int(last_depth);
print_char('>');print_int(prof_depth);
print_char('}');print_ln();
#endif
#line 31669 "texprof.w"
 cmd_count++;
last_depth= unchanged_depth= prof_depth;
}


/*:1779*/
#line 31314 "texprof.w"

stamp[st_count++]= (prof_cmd<<24)|prof_file_line;
prof_cmd= prof_cmd&~POP_BIT;
#if SHOW_RECORD_TIMING
print_char('<');print_int(cmd_count);
print_char(':');
if(prof_cmd&POP_BIT)print_char('-');
print_int(prof_cmd&~POP_BIT);
print_char(':');print_int(prof_depth);
print_char('>');print_ln();
#endif
#line 31325 "texprof.w"
 cmd_count++;
/*1756:*/
#line 31198 "texprof.w"

#if GETTIME==0
time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#elif GETTIME==1
#line 31202 "texprof.w"
 time_error= clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&ts);
#elif GETTIME==2
#line 31204 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
#elif GETTIME==3
#line 31206 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC,&ts);
#else
#line 31208 "texprof.w"
 time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#endif
#line 31210 "texprof.w"

/*:1756*/
#line 31326 "texprof.w"

/*1757:*/
#line 31215 "texprof.w"

diff_nsec= (ts.tv_sec-start_sec)*1000000000+(ts.tv_nsec-start_nsec);
#if 0
printf("time: %ld %ld %ld\n",diff_nsec,(ts.tv_sec),(ts.tv_nsec));
#endif
#line 31220 "texprof.w"

start_nsec= ts.tv_nsec;
start_sec= ts.tv_sec;

/*:1757*/
#line 31327 "texprof.w"

stamp[st_count++]= diff_nsec;
}


/*:1761*/
#line 31411 "texprof.w"

prof_file_line= tmp_file_line;
prof_cmd= tmp_cmd;
prof_depth= tmp_depth;
}



/*:1768*/
#line 13242 "texprof.w"

}

/*:637*//*644:*/
#line 13392 "texprof.w"
static void scan_spec(group_code c,bool three_codes)

{
int s;
int spec_code;
if(three_codes)s= saved(0);
if(scan_keyword("to"))spec_code= exactly;

else if(scan_keyword("spread"))spec_code= additional;

else{spec_code= additional;cur_val= 0;
goto found;
}
scan_normal_dimen;
found:if(three_codes)
{saved(0)= s;incr(save_ptr);
}
saved(0)= spec_code;saved(1)= cur_val;save_ptr= save_ptr+2;
new_save_level(c);scan_left_brace();
}

/*:644*//*648:*/
#line 13449 "texprof.w"
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
last_badness= 0;r= get_node(box_node_size);type(r)= hlist_node;
subtype(r)= min_quarterword;shift_amount(r)= 0;
q= r+list_offset;link(q)= p;
h= 0;/*649:*/
#line 13476 "texprof.w"

d= 0;x= 0;
total_stretch[normal]= 0;total_shrink[normal]= 0;
total_stretch[fil]= 0;total_shrink[fil]= 0;
total_stretch[fill]= 0;total_shrink[fill]= 0;
total_stretch[filll]= 0;total_shrink[filll]= 0

/*:649*/
#line 13463 "texprof.w"
;
while(p!=null)/*650:*/
#line 13483 "texprof.w"


{reswitch:while(is_char_node(p))
/*653:*/
#line 13528 "texprof.w"

{f= font(p);i= char_info(f,character(p));hd= height_depth(i);
x= x+char_width(f,i);
s= char_height(f,hd);if(s> h)h= s;
s= char_depth(f,hd);if(s> d)d= s;
p= link(p);
}

/*:653*/
#line 13487 "texprof.w"
;
if(p!=null)
{switch(type(p)){
case hlist_node:case vlist_node:case rule_node:
case unset_node:
/*652:*/
#line 13516 "texprof.w"

{x= x+width(p);
if(type(p)>=rule_node)s= 0;else s= shift_amount(p);
if(height(p)-s> h)h= height(p)-s;
if(depth(p)+s> d)d= depth(p)+s;
}

/*:652*/
#line 13493 "texprof.w"
break;
case ins_node:case mark_node:case adjust_node:if(adjust_tail!=null)
/*654:*/
#line 13543 "texprof.w"

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

/*:654*/
#line 13495 "texprof.w"
break;
case whatsit_node:/*1359:*/
#line 25639 "texprof.w"
do_nothing

/*:1359*/
#line 13496 "texprof.w"
;break;
case glue_node:/*655:*/
#line 13555 "texprof.w"

{g= glue_ptr(p);x= x+width(g);
o= stretch_order(g);total_stretch[o]= total_stretch[o]+stretch(g);
o= shrink_order(g);total_shrink[o]= total_shrink[o]+shrink(g);
if(subtype(p)>=a_leaders)
{g= leader_ptr(p);
if(height(g)> h)h= height(g);
if(depth(g)> d)d= depth(g);
}
}

/*:655*/
#line 13497 "texprof.w"
break;
case kern_node:case math_node:x= x+width(p);break;
case ligature_node:/*651:*/
#line 13507 "texprof.w"

{mem[lig_trick]= mem[lig_char(p)];link(lig_trick)= link(p);
p= lig_trick;goto reswitch;
}

/*:651*/
#line 13499 "texprof.w"

default:do_nothing;
}
p= link(p);
}
}


/*:650*/
#line 13466 "texprof.w"
;
if(adjust_tail!=null)link(adjust_tail)= null;
height(r)= h;depth(r)= d;
/*656:*/
#line 13569 "texprof.w"

if(m==additional)w= x+w;
width(r)= w;x= w-x;
if(x==0)
{glue_sign(r)= normal;glue_order(r)= normal;
set_glue_ratio_zero(glue_set(r));
goto end;
}
else if(x> 0)/*657:*/
#line 13582 "texprof.w"

{/*658:*/
#line 13596 "texprof.w"

if(total_stretch[filll]!=0)o= filll;
else if(total_stretch[fill]!=0)o= fill;
else if(total_stretch[fil]!=0)o= fil;
else o= normal

/*:658*/
#line 13583 "texprof.w"
;
glue_order(r)= o;glue_sign(r)= stretching;
if(total_stretch[o]!=0)glue_set(r)= fix(x/(double)total_stretch[o]);

else{glue_sign(r)= normal;
set_glue_ratio_zero(glue_set(r));
}
if(o==normal)if(list_ptr(r)!=null)
/*659:*/
#line 13602 "texprof.w"

{last_badness= badness(x,total_stretch[normal]);
if(last_badness> hbadness)
{print_ln();
if(last_badness> 100)print_nl("Underfull");else print_nl("Loose");
print(" \\hbox (badness ");print_int(last_badness);


goto common_ending;
}
}

/*:659*/
#line 13592 "texprof.w"
;
goto end;
}

/*:657*/
#line 13578 "texprof.w"

else/*663:*/
#line 13641 "texprof.w"

{/*664:*/
#line 13661 "texprof.w"

if(total_shrink[filll]!=0)o= filll;
else if(total_shrink[fill]!=0)o= fill;
else if(total_shrink[fil]!=0)o= fil;
else o= normal

/*:664*/
#line 13642 "texprof.w"
;
glue_order(r)= o;glue_sign(r)= shrinking;
if(total_shrink[o]!=0)glue_set(r)= fix((-x)/(double)total_shrink[o]);

else{glue_sign(r)= normal;
set_glue_ratio_zero(glue_set(r));
}
if((total_shrink[o]<-x)&&(o==normal)&&(list_ptr(r)!=null))
{last_badness= 1000000;
set_glue_ratio_one(glue_set(r));
/*665:*/
#line 13667 "texprof.w"

if((-x-total_shrink[normal]> hfuzz)||(hbadness<100))
{if((overfull_rule> 0)&&(-x-total_shrink[normal]> hfuzz))
{while(link(q)!=null)q= link(q);
link(q)= new_rule();
width(link(q))= overfull_rule;
}
print_ln();print_nl("Overfull \\hbox (");

print_scaled(-x-total_shrink[normal]);print("pt too wide");
goto common_ending;
}

/*:665*/
#line 13653 "texprof.w"
;
}
else if(o==normal)if(list_ptr(r)!=null)
/*666:*/
#line 13680 "texprof.w"

{last_badness= badness(-x,total_shrink[normal]);
if(last_badness> hbadness)
{print_ln();print_nl("Tight \\hbox (badness ");print_int(last_badness);

goto common_ending;
}
}

/*:666*/
#line 13657 "texprof.w"
;
goto end;
}

/*:663*/
#line 13580 "texprof.w"


/*:656*/
#line 13470 "texprof.w"
;
common_ending:/*662:*/
#line 13626 "texprof.w"

if(output_active)print(") has occurred while \\output is active");
else{if(pack_begin_line!=0)
{if(pack_begin_line> 0)print(") in paragraph at lines ");
else print(") in alignment at lines ");
print_int(abs(pack_begin_line));
print("--");
}
else print(") detected at line ");
print_int(line);
}
print_ln();
font_in_short_display= null_font;short_display(list_ptr(r));print_ln();
begin_diagnostic();show_box(r);end_diagnostic(true)

/*:662*/
#line 13472 "texprof.w"
;
end:return r;
}

/*:648*//*667:*/
#line 13697 "texprof.w"

#define vpack(...) vpackage(__VA_ARGS__, max_dimen) 
static pointer vpackage(pointer p,scaled h,small_number m,scaled l)
{
pointer r;
scaled w,d,x;
scaled s;
pointer g;
glue_ord o;
last_badness= 0;r= get_node(box_node_size);type(r)= vlist_node;
subtype(r)= min_quarterword;shift_amount(r)= 0;
list_ptr(r)= p;
w= 0;/*649:*/
#line 13476 "texprof.w"

d= 0;x= 0;
total_stretch[normal]= 0;total_shrink[normal]= 0;
total_stretch[fil]= 0;total_shrink[fil]= 0;
total_stretch[fill]= 0;total_shrink[fill]= 0;
total_stretch[filll]= 0;total_shrink[filll]= 0

/*:649*/
#line 13709 "texprof.w"
;
while(p!=null)/*668:*/
#line 13724 "texprof.w"

{if(is_char_node(p))confusion("vpack");

else switch(type(p)){
case hlist_node:case vlist_node:case rule_node:
case unset_node:
/*669:*/
#line 13741 "texprof.w"

{x= x+d+height(p);d= depth(p);
if(type(p)>=rule_node)s= 0;else s= shift_amount(p);
if(width(p)+s> w)w= width(p)+s;
}

/*:669*/
#line 13731 "texprof.w"
break;
case whatsit_node:/*1358:*/
#line 25637 "texprof.w"
do_nothing

/*:1358*/
#line 13732 "texprof.w"
;break;
case glue_node:/*670:*/
#line 13747 "texprof.w"

{x= x+d;d= 0;
g= glue_ptr(p);x= x+width(g);
o= stretch_order(g);total_stretch[o]= total_stretch[o]+stretch(g);
o= shrink_order(g);total_shrink[o]= total_shrink[o]+shrink(g);
if(subtype(p)>=a_leaders)
{g= leader_ptr(p);
if(width(g)> w)w= width(g);
}
}

/*:670*/
#line 13733 "texprof.w"
break;
case kern_node:{x= x+d+width(p);d= 0;
}break;
default:do_nothing;
}
p= link(p);
}

/*:668*/
#line 13711 "texprof.w"
;
width(r)= w;
if(d> l)
{x= x+d-l;depth(r)= l;
}
else depth(r)= d;
/*671:*/
#line 13761 "texprof.w"

if(m==additional)h= x+h;
height(r)= h;x= h-x;
if(x==0)
{glue_sign(r)= normal;glue_order(r)= normal;
set_glue_ratio_zero(glue_set(r));
goto end;
}
else if(x> 0)/*672:*/
#line 13774 "texprof.w"

{/*658:*/
#line 13596 "texprof.w"

if(total_stretch[filll]!=0)o= filll;
else if(total_stretch[fill]!=0)o= fill;
else if(total_stretch[fil]!=0)o= fil;
else o= normal

/*:658*/
#line 13775 "texprof.w"
;
glue_order(r)= o;glue_sign(r)= stretching;
if(total_stretch[o]!=0)glue_set(r)= fix(x/(double)total_stretch[o]);

else{glue_sign(r)= normal;
set_glue_ratio_zero(glue_set(r));
}
if(o==normal)if(list_ptr(r)!=null)
/*673:*/
#line 13788 "texprof.w"

{last_badness= badness(x,total_stretch[normal]);
if(last_badness> vbadness)
{print_ln();
if(last_badness> 100)print_nl("Underfull");else print_nl("Loose");
print(" \\vbox (badness ");print_int(last_badness);


goto common_ending;
}
}

/*:673*/
#line 13784 "texprof.w"
;
goto end;
}

/*:672*/
#line 13770 "texprof.w"

else/*675:*/
#line 13813 "texprof.w"

{/*664:*/
#line 13661 "texprof.w"

if(total_shrink[filll]!=0)o= filll;
else if(total_shrink[fill]!=0)o= fill;
else if(total_shrink[fil]!=0)o= fil;
else o= normal

/*:664*/
#line 13814 "texprof.w"
;
glue_order(r)= o;glue_sign(r)= shrinking;
if(total_shrink[o]!=0)glue_set(r)= fix((-x)/(double)total_shrink[o]);

else{glue_sign(r)= normal;
set_glue_ratio_zero(glue_set(r));
}
if((total_shrink[o]<-x)&&(o==normal)&&(list_ptr(r)!=null))
{last_badness= 1000000;
set_glue_ratio_one(glue_set(r));
/*676:*/
#line 13833 "texprof.w"

if((-x-total_shrink[normal]> vfuzz)||(vbadness<100))
{print_ln();print_nl("Overfull \\vbox (");

print_scaled(-x-total_shrink[normal]);print("pt too high");
goto common_ending;
}

/*:676*/
#line 13825 "texprof.w"
;
}
else if(o==normal)if(list_ptr(r)!=null)
/*677:*/
#line 13841 "texprof.w"

{last_badness= badness(-x,total_shrink[normal]);
if(last_badness> vbadness)
{print_ln();print_nl("Tight \\vbox (badness ");print_int(last_badness);

goto common_ending;
}
}

/*:677*/
#line 13829 "texprof.w"
;
goto end;
}

/*:675*/
#line 13772 "texprof.w"


/*:671*/
#line 13718 "texprof.w"
;
common_ending:/*674:*/
#line 13800 "texprof.w"

if(output_active)print(") has occurred while \\output is active");
else{if(pack_begin_line!=0)
{print(") in alignment at lines ");
print_int(abs(pack_begin_line));
print("--");
}
else print(") detected at line ");
print_int(line);
print_ln();
}
begin_diagnostic();show_box(r);end_diagnostic(true)

/*:674*/
#line 13720 "texprof.w"
;
end:return r;
}

/*:667*//*678:*/
#line 13853 "texprof.w"
static void append_to_vlist(pointer b)
{scaled d;
pointer p;
if(prev_depth> ignore_depth)
{d= width(baseline_skip)-prev_depth-height(b);
if(d<line_skip_limit)p= new_param_glue(line_skip_code);
else{p= new_skip_param(baseline_skip_code);
width(temp_ptr)= d;
}
link(tail)= p;tail= p;
}
link(tail)= b;tail= b;prev_depth= depth(b);
}

/*:678*//*685:*/
#line 14051 "texprof.w"
static pointer new_noad(void)
{pointer p;
p= get_node(noad_size);
type(p)= ord_noad;subtype(p)= normal;
mem[nucleus(p)].hh= empty_field;
mem[subscr(p)].hh= empty_field;
mem[supscr(p)].hh= empty_field;
return p;
}

/*:685*//*687:*/
#line 14114 "texprof.w"
static pointer new_style(small_number s)
{pointer p;
p= get_node(style_node_size);type(p)= style_node;
subtype(p)= s;width(p)= 0;depth(p)= 0;
return p;
}

/*:687*//*688:*/
#line 14131 "texprof.w"
static pointer new_choice(void)
{pointer p;
p= get_node(style_node_size);type(p)= choice_node;
subtype(p)= 0;
display_mlist(p)= null;text_mlist(p)= null;script_mlist(p)= null;
script_script_mlist(p)= null;
return p;
}

/*:688*//*692:*/
#line 14222 "texprof.w"
static void show_info(void)
{show_node_list(info(temp_ptr));
}

/*:692*//*703:*/
#line 14424 "texprof.w"
static pointer fraction_rule(scaled t)

{pointer p;
p= new_rule();height(p)= t;depth(p)= 0;return p;
}

/*:703*//*704:*/
#line 14434 "texprof.w"
static pointer overbar(pointer b,scaled k,scaled t)
{pointer p,q;
p= new_kern(k);link(p)= b;q= fraction_rule(t);link(q)= p;
p= new_kern(t);link(p)= q;return vpack(p,natural);
}

/*:704*//*705:*/
#line 14455 "texprof.w"
/*708:*/
#line 14527 "texprof.w"

static pointer char_box(internal_font_number f,quarterword c)
{four_quarters q;
eight_bits hd;
pointer b,p;
q= char_info(f,c);hd= height_depth(q);
b= new_null_box();width(b)= char_width(f,q)+char_italic(f,q);
height(b)= char_height(f,hd);depth(b)= char_depth(f,hd);
p= get_avail();character(p)= c;font(p)= f;list_ptr(b)= p;return b;
}

/*:708*//*710:*/
#line 14551 "texprof.w"

static void stack_into_box(pointer b,internal_font_number f,
quarterword c)
{pointer p;
p= char_box(f,c);link(p)= list_ptr(b);list_ptr(b)= p;
height(b)= height(p);
}

/*:710*//*711:*/
#line 14562 "texprof.w"

static scaled height_plus_depth(internal_font_number f,quarterword c)
{four_quarters q;
eight_bits hd;
q= char_info(f,c);hd= height_depth(q);
return char_height(f,hd)+char_depth(f,hd);
}

/*:711*/
#line 14455 "texprof.w"

static pointer var_delimiter(pointer d,small_number s,scaled v)
{
pointer b;
internal_font_number f,g;
quarterword c,x,y;
int m,n;
scaled u;
scaled w;
four_quarters q;
eight_bits hd;
four_quarters r;
small_number z;
bool large_attempt;
f= null_font;w= 0;large_attempt= false;
z= small_fam(d);x= small_char(d);
loop{/*706:*/
#line 14489 "texprof.w"

if((z!=0)||(x!=min_quarterword))
{z= z+s+16;
do{z= z-16;g= fam_fnt(z);
if(g!=null_font)
/*707:*/
#line 14500 "texprof.w"

{y= x;
if((qo(y)>=font_bc[g])&&(qo(y)<=font_ec[g]))
{resume:q= char_info(g,y);
if(char_exists(q))
{if(char_tag(q)==ext_tag)
{f= g;c= y;goto found;
}
hd= height_depth(q);
u= char_height(g,hd)+char_depth(g,hd);
if(u> w)
{f= g;c= y;w= u;
if(u>=v)goto found;
}
if(char_tag(q)==list_tag)
{y= rem_byte(q);goto resume;
}
}
}
}

/*:707*/
#line 14496 "texprof.w"
;
}while(!(z<16));
}

/*:706*/
#line 14472 "texprof.w"
;
if(large_attempt)goto found;
large_attempt= true;z= large_fam(d);x= large_char(d);
}
found:if(f!=null_font)
/*709:*/
#line 14541 "texprof.w"

if(char_tag(q)==ext_tag)
/*712:*/
#line 14570 "texprof.w"

{b= new_null_box();
type(b)= vlist_node;
r= font_info[exten_base[f]+rem_byte(q)].qqqq;
/*713:*/
#line 14595 "texprof.w"

c= ext_rep(r);u= height_plus_depth(f,c);
w= 0;q= char_info(f,c);width(b)= char_width(f,q)+char_italic(f,q);
c= ext_bot(r);if(c!=min_quarterword)w= w+height_plus_depth(f,c);
c= ext_mid(r);if(c!=min_quarterword)w= w+height_plus_depth(f,c);
c= ext_top(r);if(c!=min_quarterword)w= w+height_plus_depth(f,c);
n= 0;
if(u> 0)while(w<v)
{w= w+u;incr(n);
if(ext_mid(r)!=min_quarterword)w= w+u;
}

/*:713*/
#line 14575 "texprof.w"
;
c= ext_bot(r);
if(c!=min_quarterword)stack_into_box(b,f,c);
c= ext_rep(r);
for(m= 1;m<=n;m++)stack_into_box(b,f,c);
c= ext_mid(r);
if(c!=min_quarterword)
{stack_into_box(b,f,c);c= ext_rep(r);
for(m= 1;m<=n;m++)stack_into_box(b,f,c);
}
c= ext_top(r);
if(c!=min_quarterword)stack_into_box(b,f,c);
depth(b)= w-height(b);
}

/*:712*/
#line 14544 "texprof.w"

else b= char_box(f,c)

/*:709*/
#line 14477 "texprof.w"
;
else{b= new_null_box();
width(b)= null_delimiter_space;
}
shift_amount(b)= half(height(b)-depth(b))-axis_height(s);
return b;
}

/*:705*//*714:*/
#line 14620 "texprof.w"
static pointer rebox(pointer b,scaled w)
{pointer p;
internal_font_number f;
scaled v;
if((width(b)!=w)&&(list_ptr(b)!=null))
{if(type(b)==vlist_node)b= hpack(b,natural);
p= list_ptr(b);
if((is_char_node(p))&&(link(p)==null))
{f= font(p);v= char_width(f,char_info(f,character(p)));
if(v!=width(b))link(p)= new_kern(width(b)-v);
}
free_node(b,box_node_size);
b= new_glue(ss_glue);link(b)= p;
while(link(p)!=null)p= link(p);
link(p)= new_glue(ss_glue);
return hpack(b,w,exactly);
}
else{width(b)= w;return b;
}
}

/*:714*//*715:*/
#line 14646 "texprof.w"
static pointer math_glue(pointer g,scaled m)
{pointer p;
int n;
scaled f;
n= x_over_n(m,0200000);f= rem;
if(f<0)
{decr(n);f= f+0200000;
}
p= get_node(glue_spec_size);
width(p)= mu_mult(width(g));
stretch_order(p)= stretch_order(g);
if(stretch_order(p)==normal)stretch(p)= mu_mult(stretch(g));
else stretch(p)= stretch(g);
shrink_order(p)= shrink_order(g);
if(shrink_order(p)==normal)shrink(p)= mu_mult(shrink(g));
else shrink(p)= shrink(g);
return p;
}

/*:715*//*716:*/
#line 14668 "texprof.w"
static void math_kern(pointer p,scaled m)
{int n;
scaled f;
if(subtype(p)==mu_glue)
{n= x_over_n(m,0200000);f= rem;
if(f<0)
{decr(n);f= f+0200000;
}
width(p)= mu_mult(width(p));subtype(p)= explicit;
}
}

/*:716*//*717:*/
#line 14683 "texprof.w"
static void flush_math(void)
{flush_node_list(link(head));flush_node_list(incompleat_noad);
link(head)= null;tail= head;incompleat_noad= null;
}

/*:717*//*719:*/
#line 14720 "texprof.w"
static void mlist_to_hlist(void);
static pointer clean_box(pointer p,small_number s)
{
pointer q;
small_number save_style;
pointer x;
pointer r;
switch(math_type(p)){
case math_char:{cur_mlist= new_noad();mem[nucleus(cur_mlist)]= mem[p];
}break;
case sub_box:{q= info(p);goto found;
}
case sub_mlist:cur_mlist= info(p);break;
default:{q= new_null_box();goto found;
}
}
save_style= cur_style;cur_style= s;mlist_penalties= false;
mlist_to_hlist();q= link(temp_head);
cur_style= save_style;
/*702:*/
#line 14414 "texprof.w"

{if(cur_style<script_style)cur_size= text_size;
else cur_size= 16*((cur_style-text_style)/2);
cur_mu= x_over_n(math_quad(cur_size),18);
}

/*:702*/
#line 14739 "texprof.w"
;
found:if(is_char_node(q)||(q==null))x= hpack(q,natural);
else if((link(q)==null)&&(type(q)<=vlist_node)&&(shift_amount(q)==0))
x= q;
else x= hpack(q,natural);
/*720:*/
#line 14750 "texprof.w"

q= list_ptr(x);
if(is_char_node(q))
{r= link(q);
if(r!=null)if(link(r)==null)if(!is_char_node(r))
if(type(r)==kern_node)
{free_node(r,small_node_size);link(q)= null;
}
}

/*:720*/
#line 14744 "texprof.w"
;
return x;
}

/*:719*//*721:*/
#line 14767 "texprof.w"
static void fetch(pointer a)
{cur_c= character(a);cur_f= fam_fnt(fam(a)+cur_size);
if(cur_f==null_font)
/*722:*/
#line 14781 "texprof.w"

{print_err("");print_size(cur_size);print_char(' ');
print_int(fam(a));print(" is undefined (character ");
print_ASCII(qo(cur_c));print_char(')');
help4("Somewhere in the math formula just ended, you used the",
"stated character from an undefined font family. For example,",
"plain TeX doesn't allow \\it or \\sl in subscripts. Proceed,",
"and I'll try to forget that I needed that character.");
error();cur_i= null_character;math_type(a)= empty;
}

/*:722*/
#line 14770 "texprof.w"

else{if((qo(cur_c)>=font_bc[cur_f])&&(qo(cur_c)<=font_ec[cur_f]))
cur_i= char_info(cur_f,cur_c);
else cur_i= null_character;
if(!(char_exists(cur_i)))
{char_warning(cur_f,qo(cur_c));
math_type(a)= empty;cur_i= null_character;
}
}
}

/*:721*//*725:*/
#line 14821 "texprof.w"
/*733:*/
#line 14981 "texprof.w"

static void make_over(pointer q)
{info(nucleus(q))= 
overbar(clean_box(nucleus(q),cramped_style(cur_style)),
3*default_rule_thickness,default_rule_thickness);
math_type(nucleus(q))= sub_box;
}

/*:733*//*734:*/
#line 14989 "texprof.w"

static void make_under(pointer q)
{pointer p,x,y;
scaled delta;
x= clean_box(nucleus(q),cur_style);
p= new_kern(3*default_rule_thickness);link(x)= p;
link(p)= fraction_rule(default_rule_thickness);
y= vpack(x,natural);
delta= height(y)+depth(y)+default_rule_thickness;
height(y)= height(x);depth(y)= delta-height(y);
info(nucleus(q))= y;math_type(nucleus(q))= sub_box;
}

/*:734*//*735:*/
#line 15002 "texprof.w"

static void make_vcenter(pointer q)
{pointer v;
scaled delta;
v= info(nucleus(q));
if(type(v)!=vlist_node)confusion("vcenter");

delta= height(v)+depth(v);
height(v)= axis_height(cur_size)+half(delta);
depth(v)= delta-height(v);
}

/*:735*//*736:*/
#line 15023 "texprof.w"

static void make_radical(pointer q)
{pointer x,y;
scaled delta,clr;
x= clean_box(nucleus(q),cramped_style(cur_style));
if(cur_style<text_style)
clr= default_rule_thickness+(abs(math_x_height(cur_size))/4);
else{clr= default_rule_thickness;clr= clr+(abs(clr)/4);
}
y= var_delimiter(left_delimiter(q),cur_size,height(x)+depth(x)+clr+
default_rule_thickness);
delta= depth(y)-(height(x)+depth(x)+clr);
if(delta> 0)clr= clr+half(delta);
shift_amount(y)= -(height(x)+clr);
link(y)= overbar(x,clr,height(y));
info(nucleus(q))= hpack(y,natural);math_type(nucleus(q))= sub_box;
}

/*:736*//*737:*/
#line 15045 "texprof.w"

static void make_math_accent(pointer q)
{
pointer p,x,y;
int a;
quarterword c;
internal_font_number f;
four_quarters i;
scaled s;
scaled h;
scaled delta;
scaled w;
fetch(accent_chr(q));
if(char_exists(cur_i))
{i= cur_i;c= cur_c;f= cur_f;
/*740:*/
#line 15092 "texprof.w"

s= 0;
if(math_type(nucleus(q))==math_char)
{fetch(nucleus(q));
if(char_tag(cur_i)==lig_tag)
{a= lig_kern_start(cur_f,cur_i);
cur_i= font_info[a].qqqq;
if(skip_byte(cur_i)> stop_flag)
{a= lig_kern_restart(cur_f,cur_i);
cur_i= font_info[a].qqqq;
}
loop{if(qo(next_char(cur_i))==skew_char[cur_f])
{if(op_byte(cur_i)>=kern_flag)
if(skip_byte(cur_i)<=stop_flag)s= char_kern(cur_f,cur_i);
goto done1;
}
if(skip_byte(cur_i)>=stop_flag)goto done1;
a= a+qo(skip_byte(cur_i))+1;
cur_i= font_info[a].qqqq;
}
}
}
done1:

/*:740*/
#line 15060 "texprof.w"
;
x= clean_box(nucleus(q),cramped_style(cur_style));w= width(x);h= height(x);
/*739:*/
#line 15082 "texprof.w"

loop{if(char_tag(i)!=list_tag)goto done;
y= rem_byte(i);
i= char_info(f,y);
if(!char_exists(i))goto done;
if(char_width(f,i)> w)goto done;
c= y;
}
done:

/*:739*/
#line 15062 "texprof.w"
;
if(h<x_height(f))delta= h;else delta= x_height(f);
if((math_type(supscr(q))!=empty)||(math_type(subscr(q))!=empty))
if(math_type(nucleus(q))==math_char)
/*741:*/
#line 15116 "texprof.w"

{flush_node_list(x);x= new_noad();
mem[nucleus(x)]= mem[nucleus(q)];
mem[supscr(x)]= mem[supscr(q)];
mem[subscr(x)]= mem[subscr(q)];
mem[supscr(q)].hh= empty_field;
mem[subscr(q)].hh= empty_field;
math_type(nucleus(q))= sub_mlist;info(nucleus(q))= x;
x= clean_box(nucleus(q),cur_style);delta= delta+height(x)-h;h= height(x);
}

/*:741*/
#line 15066 "texprof.w"
;
y= char_box(f,c);
shift_amount(y)= s+half(w-width(y));
width(y)= 0;p= new_kern(-delta);link(p)= x;link(y)= p;
y= vpack(y,natural);width(y)= width(x);
if(height(y)<h)/*738:*/
#line 15077 "texprof.w"

{p= new_kern(h-height(y));link(p)= list_ptr(y);list_ptr(y)= p;
height(y)= h;
}

/*:738*/
#line 15071 "texprof.w"
;
info(nucleus(q))= y;
math_type(nucleus(q))= sub_box;
}
}

/*:737*//*742:*/
#line 15130 "texprof.w"

static void make_fraction(pointer q)
{pointer p,v,x,y,z;
scaled delta,delta1,delta2,shift_up,shift_down,clr;

if(thickness(q)==default_code)thickness(q)= default_rule_thickness;
/*743:*/
#line 15147 "texprof.w"

x= clean_box(numerator(q),num_style(cur_style));
z= clean_box(denominator(q),denom_style(cur_style));
if(width(x)<width(z))x= rebox(x,width(z));
else z= rebox(z,width(x));
if(cur_style<text_style)
{shift_up= num1(cur_size);shift_down= denom1(cur_size);
}
else{shift_down= denom2(cur_size);
if(thickness(q)!=0)shift_up= num2(cur_size);
else shift_up= num3(cur_size);
}

/*:743*/
#line 15138 "texprof.w"
;
if(thickness(q)==0)/*744:*/
#line 15164 "texprof.w"

{if(cur_style<text_style)clr= 7*default_rule_thickness;
else clr= 3*default_rule_thickness;
delta= half(clr-((shift_up-depth(x))-(height(z)-shift_down)));
if(delta> 0)
{shift_up= shift_up+delta;
shift_down= shift_down+delta;
}
}

/*:744*/
#line 15140 "texprof.w"

else/*745:*/
#line 15177 "texprof.w"

{if(cur_style<text_style)clr= 3*thickness(q);
else clr= thickness(q);
delta= half(thickness(q));
delta1= clr-((shift_up-depth(x))-(axis_height(cur_size)+delta));
delta2= clr-((axis_height(cur_size)-delta)-(height(z)-shift_down));
if(delta1> 0)shift_up= shift_up+delta1;
if(delta2> 0)shift_down= shift_down+delta2;
}

/*:745*/
#line 15141 "texprof.w"
;
/*746:*/
#line 15187 "texprof.w"

v= new_null_box();type(v)= vlist_node;
height(v)= shift_up+height(x);depth(v)= depth(z)+shift_down;
width(v)= width(x);
if(thickness(q)==0)
{p= new_kern((shift_up-depth(x))-(height(z)-shift_down));
link(p)= z;
}
else{y= fraction_rule(thickness(q));
p= new_kern((axis_height(cur_size)-delta)-(height(z)-shift_down));
link(y)= p;link(p)= z;
p= new_kern((shift_up-depth(x))-(axis_height(cur_size)+delta));
link(p)= y;
}
link(x)= p;list_ptr(v)= x

/*:746*/
#line 15142 "texprof.w"
;
/*747:*/
#line 15203 "texprof.w"

if(cur_style<text_style)delta= delim1(cur_size);
else delta= delim2(cur_size);
x= var_delimiter(left_delimiter(q),cur_size,delta);link(x)= v;
z= var_delimiter(right_delimiter(q),cur_size,delta);link(v)= z;
new_hlist(q)= hpack(x,natural)

/*:747*/
#line 15144 "texprof.w"
;
}

/*:742*//*748:*/
#line 15225 "texprof.w"

static scaled make_op(pointer q)
{scaled delta;
pointer p,v,x,y,z;
quarterword c;four_quarters i;
scaled shift_up,shift_down;
if((subtype(q)==normal)&&(cur_style<text_style))
subtype(q)= limits;
if(math_type(nucleus(q))==math_char)
{fetch(nucleus(q));
if((cur_style<text_style)&&(char_tag(cur_i)==list_tag))
{c= rem_byte(cur_i);i= char_info(cur_f,c);
if(char_exists(i))
{cur_c= c;cur_i= i;character(nucleus(q))= c;
}
}
delta= char_italic(cur_f,cur_i);x= clean_box(nucleus(q),cur_style);
if((math_type(subscr(q))!=empty)&&(subtype(q)!=limits))
width(x)= width(x)-delta;
shift_amount(x)= half(height(x)-depth(x))-axis_height(cur_size);

math_type(nucleus(q))= sub_box;info(nucleus(q))= x;
}
else delta= 0;
if(subtype(q)==limits)
/*749:*/
#line 15257 "texprof.w"

{x= clean_box(supscr(q),sup_style(cur_style));
y= clean_box(nucleus(q),cur_style);
z= clean_box(subscr(q),sub_style(cur_style));
v= new_null_box();type(v)= vlist_node;width(v)= width(y);
if(width(x)> width(v))width(v)= width(x);
if(width(z)> width(v))width(v)= width(z);
x= rebox(x,width(v));y= rebox(y,width(v));z= rebox(z,width(v));
shift_amount(x)= half(delta);shift_amount(z)= -shift_amount(x);
height(v)= height(y);depth(v)= depth(y);
/*750:*/
#line 15277 "texprof.w"

if(math_type(supscr(q))==empty)
{free_node(x,box_node_size);list_ptr(v)= y;
}
else{shift_up= big_op_spacing3-depth(x);
if(shift_up<big_op_spacing1)shift_up= big_op_spacing1;
p= new_kern(shift_up);link(p)= y;link(x)= p;
p= new_kern(big_op_spacing5);link(p)= x;list_ptr(v)= p;
height(v)= height(v)+big_op_spacing5+height(x)+depth(x)+shift_up;
}
if(math_type(subscr(q))==empty)free_node(z,box_node_size);
else{shift_down= big_op_spacing4-height(z);
if(shift_down<big_op_spacing2)shift_down= big_op_spacing2;
p= new_kern(shift_down);link(y)= p;link(p)= z;
p= new_kern(big_op_spacing5);link(z)= p;
depth(v)= depth(v)+big_op_spacing5+height(z)+depth(z)+shift_down;
}

/*:750*/
#line 15268 "texprof.w"
;
new_hlist(q)= v;
}

/*:749*/
#line 15250 "texprof.w"
;
return delta;
}

/*:748*//*751:*/
#line 15305 "texprof.w"

static void make_ord(pointer q)
{
int a;
pointer p,r;
restart:
if(math_type(subscr(q))==empty)if(math_type(supscr(q))==empty)
if(math_type(nucleus(q))==math_char)
{p= link(q);
if(p!=null)if((type(p)>=ord_noad)&&(type(p)<=punct_noad))
if(math_type(nucleus(p))==math_char)
if(fam(nucleus(p))==fam(nucleus(q)))
{math_type(nucleus(q))= math_text_char;
fetch(nucleus(q));
if(char_tag(cur_i)==lig_tag)
{a= lig_kern_start(cur_f,cur_i);
cur_c= character(nucleus(p));
cur_i= font_info[a].qqqq;
if(skip_byte(cur_i)> stop_flag)
{a= lig_kern_restart(cur_f,cur_i);
cur_i= font_info[a].qqqq;
}
loop{/*752:*/
#line 15348 "texprof.w"

if(next_char(cur_i)==cur_c)if(skip_byte(cur_i)<=stop_flag)
if(op_byte(cur_i)>=kern_flag)
{p= new_kern(char_kern(cur_f,cur_i));
link(p)= link(q);link(q)= p;return;
}
else{check_interrupt;
switch(op_byte(cur_i)){
case qi(1):case qi(5):character(nucleus(q))= rem_byte(cur_i);break;
case qi(2):case qi(6):character(nucleus(p))= rem_byte(cur_i);break;
case qi(3):case qi(7):case qi(11):{r= new_noad();
character(nucleus(r))= rem_byte(cur_i);
fam(nucleus(r))= fam(nucleus(q));
link(q)= r;link(r)= p;
if(op_byte(cur_i)<qi(11))math_type(nucleus(r))= math_char;
else math_type(nucleus(r))= math_text_char;
}break;
default:{link(q)= link(p);
character(nucleus(q))= rem_byte(cur_i);
mem[subscr(q)]= mem[subscr(p)];mem[supscr(q)]= mem[supscr(p)];
free_node(p,noad_size);
}
}
if(op_byte(cur_i)> qi(3))return;
math_type(nucleus(q))= math_char;goto restart;
}

/*:752*/
#line 15330 "texprof.w"
;
if(skip_byte(cur_i)>=stop_flag)return;
a= a+qo(skip_byte(cur_i))+1;
cur_i= font_info[a].qqqq;
}
}
}
}
}

/*:751*//*755:*/
#line 15430 "texprof.w"

static void make_scripts(pointer q,scaled delta)
{pointer p,x,y,z;
scaled shift_up,shift_down,clr;
small_number t;
p= new_hlist(q);
if(is_char_node(p))
{shift_up= 0;shift_down= 0;
}
else{z= hpack(p,natural);
if(cur_style<script_style)t= script_size;else t= script_script_size;
shift_up= height(z)-sup_drop(t);
shift_down= depth(z)+sub_drop(t);
free_node(z,box_node_size);
}
if(math_type(supscr(q))==empty)
/*756:*/
#line 15462 "texprof.w"

{x= clean_box(subscr(q),sub_style(cur_style));
width(x)= width(x)+script_space;
if(shift_down<sub1(cur_size))shift_down= sub1(cur_size);
clr= height(x)-(abs(math_x_height(cur_size)*4)/5);
if(shift_down<clr)shift_down= clr;
shift_amount(x)= shift_down;
}

/*:756*/
#line 15446 "texprof.w"

else{/*757:*/
#line 15474 "texprof.w"

{x= clean_box(supscr(q),sup_style(cur_style));
width(x)= width(x)+script_space;
if(odd(cur_style))clr= sup3(cur_size);
else if(cur_style<text_style)clr= sup1(cur_size);
else clr= sup2(cur_size);
if(shift_up<clr)shift_up= clr;
clr= depth(x)+(abs(math_x_height(cur_size))/4);
if(shift_up<clr)shift_up= clr;
}

/*:757*/
#line 15447 "texprof.w"
;
if(math_type(subscr(q))==empty)shift_amount(x)= -shift_up;
else/*758:*/
#line 15491 "texprof.w"

{y= clean_box(subscr(q),sub_style(cur_style));
width(y)= width(y)+script_space;
if(shift_down<sub2(cur_size))shift_down= sub2(cur_size);
clr= 4*default_rule_thickness-
((shift_up-depth(x))-(height(y)-shift_down));
if(clr> 0)
{shift_down= shift_down+clr;
clr= (abs(math_x_height(cur_size)*4)/5)-(shift_up-depth(x));
if(clr> 0)
{shift_up= shift_up+clr;
shift_down= shift_down-clr;
}
}
shift_amount(x)= delta;
p= new_kern((shift_up-depth(x))-(height(y)-shift_down));link(x)= p;link(p)= y;
x= vpack(x,natural);shift_amount(x)= shift_down;
}

/*:758*/
#line 15450 "texprof.w"
;
}
if(new_hlist(q)==null)new_hlist(q)= x;
else{p= new_hlist(q);
while(link(p)!=null)p= link(p);
link(p)= x;
}
}

/*:755*//*761:*/
#line 15567 "texprof.w"

static small_number make_left_right(pointer q,small_number style,
scaled max_d,scaled max_h)
{scaled delta,delta1,delta2;
cur_style= style;/*702:*/
#line 14414 "texprof.w"

{if(cur_style<script_style)cur_size= text_size;
else cur_size= 16*((cur_style-text_style)/2);
cur_mu= x_over_n(math_quad(cur_size),18);
}

/*:702*/
#line 15571 "texprof.w"
;
delta2= max_d+axis_height(cur_size);
delta1= max_h+max_d-delta2;
if(delta2> delta1)delta1= delta2;
delta= (delta1/500)*delimiter_factor;
delta2= delta1+delta1-delimiter_shortfall;
if(delta<delta2)delta= delta2;
new_hlist(q)= var_delimiter(delimiter(q),cur_size,delta);
return type(q)-(left_noad-open_noad);
}

/*:761*/
#line 14821 "texprof.w"

static void mlist_to_hlist(void)
{

pointer mlist;
bool penalties;
small_number style;
small_number save_style;
pointer q;
pointer r;
small_number r_type;
small_number t;
pointer p,x,y,z;
int pen;
small_number s;
scaled max_h,max_d;
scaled delta;
mlist= cur_mlist;penalties= mlist_penalties;
style= cur_style;
q= mlist;r= null;r_type= op_noad;max_h= 0;max_d= 0;
/*702:*/
#line 14414 "texprof.w"

{if(cur_style<script_style)cur_size= text_size;
else cur_size= 16*((cur_style-text_style)/2);
cur_mu= x_over_n(math_quad(cur_size),18);
}

/*:702*/
#line 14841 "texprof.w"
;
while(q!=null)/*726:*/
#line 14853 "texprof.w"

{/*727:*/
#line 14872 "texprof.w"

reswitch:delta= 0;
switch(type(q)){
case bin_noad:switch(r_type){
case bin_noad:case op_noad:case rel_noad:
case open_noad:case punct_noad:case left_noad:
{type(q)= ord_noad;goto reswitch;
}
default:do_nothing;
}break;
case rel_noad:case close_noad:case punct_noad:
case right_noad:{
/*728:*/
#line 14895 "texprof.w"

if(r_type==bin_noad)type(r)= ord_noad

/*:728*/
#line 14884 "texprof.w"
;
if(type(q)==right_noad)goto done_with_noad;
}break;
/*732:*/
#line 14960 "texprof.w"

case left_noad:goto done_with_noad;
case fraction_noad:{make_fraction(q);goto check_dimensions;
}
case op_noad:{delta= make_op(q);
if(subtype(q)==limits)goto check_dimensions;
}break;
case ord_noad:make_ord(q);break;
case open_noad:case inner_noad:do_nothing;break;
case radical_noad:make_radical(q);break;
case over_noad:make_over(q);break;
case under_noad:make_under(q);break;
case accent_noad:make_math_accent(q);break;
case vcenter_noad:make_vcenter(q);break;

/*:732*/
#line 14887 "texprof.w"

/*729:*/
#line 14898 "texprof.w"

case style_node:{cur_style= subtype(q);
/*702:*/
#line 14414 "texprof.w"

{if(cur_style<script_style)cur_size= text_size;
else cur_size= 16*((cur_style-text_style)/2);
cur_mu= x_over_n(math_quad(cur_size),18);
}

/*:702*/
#line 14900 "texprof.w"
;
goto done_with_node;
}
case choice_node:/*730:*/
#line 14919 "texprof.w"

{switch(cur_style/2){
case 0:choose_mlist(display_mlist)break;
case 1:choose_mlist(text_mlist)break;
case 2:choose_mlist(script_mlist)break;
case 3:choose_mlist(script_script_mlist);
}
flush_node_list(display_mlist(q));
flush_node_list(text_mlist(q));
flush_node_list(script_mlist(q));
flush_node_list(script_script_mlist(q));
type(q)= style_node;subtype(q)= cur_style;width(q)= 0;depth(q)= 0;
if(p!=null)
{z= link(q);link(q)= p;
while(link(p)!=null)p= link(p);
link(p)= z;
}
goto done_with_node;
}

/*:730*/
#line 14904 "texprof.w"

case ins_node:case mark_node:case adjust_node:
case whatsit_node:case penalty_node:
case disc_node:goto done_with_node;
case rule_node:{if(height(q)> max_h)max_h= height(q);
if(depth(q)> max_d)max_d= depth(q);goto done_with_node;
}
case glue_node:{/*731:*/
#line 14947 "texprof.w"

if(subtype(q)==mu_glue)
{x= glue_ptr(q);
y= math_glue(x,cur_mu);delete_glue_ref(x);glue_ptr(q)= y;
subtype(q)= normal;
}
else if((cur_size!=text_size)&&(subtype(q)==cond_math_glue))
{p= link(q);
if(p!=null)if((type(p)==glue_node)||(type(p)==kern_node))
{link(q)= link(p);link(p)= null;flush_node_list(p);
}
}

/*:731*/
#line 14911 "texprof.w"
;
goto done_with_node;
}
case kern_node:{math_kern(q,cur_mu);goto done_with_node;
}

/*:729*/
#line 14889 "texprof.w"

default:confusion("mlist1");

}
/*753:*/
#line 15387 "texprof.w"

switch(math_type(nucleus(q))){
case math_char:case math_text_char:
/*754:*/
#line 15409 "texprof.w"

{fetch(nucleus(q));
if(char_exists(cur_i))
{delta= char_italic(cur_f,cur_i);p= new_character(cur_f,qo(cur_c));
if((math_type(nucleus(q))==math_text_char)&&(space(cur_f)!=0))
delta= 0;
if((math_type(subscr(q))==empty)&&(delta!=0))
{link(p)= new_kern(delta);delta= 0;
}
}
else p= null;
}

/*:754*/
#line 15392 "texprof.w"
break;
case empty:p= null;break;
case sub_box:p= info(nucleus(q));break;
case sub_mlist:{cur_mlist= info(nucleus(q));save_style= cur_style;
mlist_penalties= false;mlist_to_hlist();

cur_style= save_style;/*702:*/
#line 14414 "texprof.w"

{if(cur_style<script_style)cur_size= text_size;
else cur_size= 16*((cur_style-text_style)/2);
cur_mu= x_over_n(math_quad(cur_size),18);
}

/*:702*/
#line 15398 "texprof.w"
;
p= hpack(link(temp_head),natural);
}break;
default:confusion("mlist2");

}
new_hlist(q)= p;
if((math_type(subscr(q))==empty)&&(math_type(supscr(q))==empty))
goto check_dimensions;
make_scripts(q,delta)

/*:753*/
#line 14893 "texprof.w"


/*:727*/
#line 14856 "texprof.w"
;
check_dimensions:z= hpack(new_hlist(q),natural);
if(height(z)> max_h)max_h= height(z);
if(depth(z)> max_d)max_d= depth(z);
free_node(z,box_node_size);
done_with_noad:r= q;r_type= type(r);
if(r_type==right_noad)
{r_type= left_noad;cur_style= style;/*702:*/
#line 14414 "texprof.w"

{if(cur_style<script_style)cur_size= text_size;
else cur_size= 16*((cur_style-text_style)/2);
cur_mu= x_over_n(math_quad(cur_size),18);
}

/*:702*/
#line 14863 "texprof.w"
;
}
done_with_node:q= link(q);
}

/*:726*/
#line 14844 "texprof.w"
;
/*728:*/
#line 14895 "texprof.w"

if(r_type==bin_noad)type(r)= ord_noad

/*:728*/
#line 14845 "texprof.w"
;
/*759:*/
#line 15516 "texprof.w"

p= temp_head;link(p)= null;q= mlist;r_type= 0;cur_style= style;
/*702:*/
#line 14414 "texprof.w"

{if(cur_style<script_style)cur_size= text_size;
else cur_size= 16*((cur_style-text_style)/2);
cur_mu= x_over_n(math_quad(cur_size),18);
}

/*:702*/
#line 15518 "texprof.w"
;
while(q!=null)
{/*760:*/
#line 15534 "texprof.w"

t= ord_noad;s= noad_size;pen= inf_penalty;
switch(type(q)){
case op_noad:case open_noad:case close_noad:
case punct_noad:case inner_noad:t= type(q);break;
case bin_noad:{t= bin_noad;pen= bin_op_penalty;
}break;
case rel_noad:{t= rel_noad;pen= rel_penalty;
}break;
case ord_noad:case vcenter_noad:case over_noad:
case under_noad:do_nothing;break;
case radical_noad:s= radical_noad_size;break;
case accent_noad:s= accent_noad_size;break;
case fraction_noad:s= fraction_noad_size;break;
case left_noad:case right_noad:t= make_left_right(q,style,max_d,max_h);break;
case style_node:/*762:*/
#line 15582 "texprof.w"

{cur_style= subtype(q);s= style_node_size;
/*702:*/
#line 14414 "texprof.w"

{if(cur_style<script_style)cur_size= text_size;
else cur_size= 16*((cur_style-text_style)/2);
cur_mu= x_over_n(math_quad(cur_size),18);
}

/*:702*/
#line 15584 "texprof.w"
;
goto delete_q;
}

/*:762*/
#line 15549 "texprof.w"

case whatsit_node:case penalty_node:
case rule_node:case disc_node:case adjust_node:
case ins_node:case mark_node:
case glue_node:case kern_node:
{link(p)= q;p= q;q= link(q);link(p)= null;goto done;
}
default:confusion("mlist3");

}

/*:760*/
#line 15523 "texprof.w"
;
/*765:*/
#line 15620 "texprof.w"

if(r_type> 0)
{switch(so(math_spacing[r_type*8+t+magic_offset])){
case'0':x= 0;break;
case'1':if(cur_style<script_style)x= thin_mu_skip_code;else x= 0;break;
case'2':x= thin_mu_skip_code;break;
case'3':if(cur_style<script_style)x= med_mu_skip_code;else x= 0;break;
case'4':if(cur_style<script_style)x= thick_mu_skip_code;else x= 0;break;
default:confusion("mlist4");

}
if(x!=0)
{y= math_glue(glue_par(x),cur_mu);
z= new_glue(y);glue_ref_count(y)= null;link(p)= z;p= z;
subtype(z)= x+1;
}
}

/*:765*/
#line 15524 "texprof.w"
;
/*766:*/
#line 15642 "texprof.w"

if(new_hlist(q)!=null)
{link(p)= new_hlist(q);
do{p= link(p);
}while(!(link(p)==null));
}
if(penalties)if(link(q)!=null)if(pen<inf_penalty)
{r_type= type(link(q));
if(r_type!=penalty_node)if(r_type!=rel_noad)
{z= new_penalty(pen);link(p)= z;p= z;
}
}

/*:766*/
#line 15525 "texprof.w"
;
if(type(q)==right_noad)t= open_noad;
r_type= t;
delete_q:r= q;q= link(q);free_node(r,s);
done:;}

/*:759*/
#line 14847 "texprof.w"
;
}

/*:725*//*771:*/
#line 15831 "texprof.w"
static void push_alignment(void)
{pointer p;
p= get_node(align_stack_node_size);
link(p)= align_ptr;info(p)= cur_align;
llink(p)= preamble;rlink(p)= cur_span;
mem[p+2].i= cur_loop;mem[p+3].i= align_state;
info(p+4)= cur_head;link(p+4)= cur_tail;
align_ptr= p;
cur_head= get_avail();
}

static void pop_alignment(void)
{pointer p;
free_avail(cur_head);
p= align_ptr;
cur_tail= link(p+4);cur_head= info(p+4);
align_state= mem[p+3].i;cur_loop= mem[p+2].i;
cur_span= rlink(p);preamble= llink(p);
cur_align= info(p);align_ptr= link(p);
free_node(p,align_stack_node_size);
}

/*:771*//*773:*/
#line 15871 "texprof.w"
/*781:*/
#line 15984 "texprof.w"

static void get_preamble_token(void)
{
restart:get_token();
while((cur_chr==span_code)&&(cur_cmd==tab_mark))
{get_token();
if(cur_cmd> max_command)
{expand();get_token();
}
}
if(cur_cmd==endv)
fatal_error("(interwoven alignment preambles are not allowed)");

if((cur_cmd==assign_glue)&&(cur_chr==glue_base+tab_skip_code))
{scan_optional_equals();scan_glue(glue_val);
if(global_defs> 0)geq_define(glue_base+tab_skip_code,glue_ref,cur_val);
else eq_define(glue_base+tab_skip_code,glue_ref,cur_val);
goto restart;
}
}

/*:781*/
#line 15871 "texprof.w"

static void align_peek(void);
static void normal_paragraph(void);
static void init_align(void)
{
pointer save_cs_ptr;
pointer p;
save_cs_ptr= cur_cs;
push_alignment();align_state= -1000000;
/*775:*/
#line 15904 "texprof.w"

if((mode==mmode)&&((tail!=head)||(incompleat_noad!=null)))
{print_err("Improper ");print_esc("halign");print(" inside $$'s");

help3("Displays can use special alignments (like \\eqalignno)",
"only if nothing but the alignment itself is between $$'s.",
"So I've deleted the formulas that preceded this alignment.");
error();flush_math();
}

/*:775*/
#line 15880 "texprof.w"
;
push_nest();
/*774:*/
#line 15895 "texprof.w"

if(mode==mmode)
{mode= -vmode;prev_depth= nest[nest_ptr-2].aux_field.sc;
}
else if(mode> 0)negate(mode)

/*:774*/
#line 15882 "texprof.w"
;
scan_spec(align_group,false);
/*776:*/
#line 15914 "texprof.w"

preamble= null;cur_align= align_head;cur_loop= null;scanner_status= aligning;
warning_index= save_cs_ptr;align_state= -1000000;

loop{/*777:*/
#line 15925 "texprof.w"

link(cur_align)= new_param_glue(tab_skip_code);
cur_align= link(cur_align)

/*:777*/
#line 15918 "texprof.w"
;
if(cur_cmd==car_ret)goto done;
/*778:*/
#line 15929 "texprof.w"

/*782:*/
#line 16007 "texprof.w"

p= hold_head;link(p)= null;
loop{get_preamble_token();
if(cur_cmd==mac_param)goto done1;
if((cur_cmd<=car_ret)&&(cur_cmd>=tab_mark)&&(align_state==-1000000))
if((p==hold_head)&&(cur_loop==null)&&(cur_cmd==tab_mark)
)cur_loop= cur_align;
else{print_err("Missing # inserted in alignment preamble");

help3("There should be exactly one # between &'s, when an",
"\\halign or \\valign is being set up. In this case you had",
"none, so I've put one in; maybe that will work.");
back_error();goto done1;
}
else if((cur_cmd!=spacer)||(p!=hold_head))
{link(p)= get_avail();p= link(p);info(p)= cur_tok;
}
}
done1:

/*:782*/
#line 15930 "texprof.w"
;
link(cur_align)= new_null_box();cur_align= link(cur_align);
info(cur_align)= end_span;width(cur_align)= null_flag;
u_part(cur_align)= link(hold_head);
/*783:*/
#line 16027 "texprof.w"

p= hold_head;link(p)= null;
loop{resume:get_preamble_token();
if((cur_cmd<=car_ret)&&(cur_cmd>=tab_mark)&&(align_state==-1000000))
goto done2;
if(cur_cmd==mac_param)
{print_err("Only one # is allowed per tab");

help3("There should be exactly one # between &'s, when an",
"\\halign or \\valign is being set up. In this case you had",
"more than one, so I'm ignoring all but the first.");
error();goto resume;
}
link(p)= get_avail();p= link(p);info(p)= cur_tok;
}
done2:link(p)= get_avail();p= link(p);
info(p)= end_template_token

/*:783*/
#line 15934 "texprof.w"
;
v_part(cur_align)= link(hold_head)

/*:778*/
#line 15921 "texprof.w"
;
}
done:scanner_status= normal

/*:776*/
#line 15884 "texprof.w"
;
new_save_level(align_group);
if(every_cr!=null)begin_token_list(every_cr,every_cr_text);
align_peek();
}

/*:773*//*785:*/
#line 16079 "texprof.w"
/*786:*/
#line 16092 "texprof.w"

static void init_span(pointer p)
{push_nest();
if(mode==-hmode)space_factor= 1000;
else{prev_depth= ignore_depth;normal_paragraph();
}
cur_span= p;
}

/*:786*/
#line 16079 "texprof.w"

static void init_row(void)
{push_nest();mode= (-hmode-vmode)-mode;
if(mode==-hmode)space_factor= 0;else prev_depth= 0;
tail_append(new_glue(glue_ptr(preamble)));
subtype(tail)= tab_skip_code+1;
cur_align= link(preamble);cur_tail= cur_head;init_span(cur_align);
}

/*:785*//*787:*/
#line 16108 "texprof.w"
static void init_col(void)
{extra_info(cur_align)= cur_cmd;
if(cur_cmd==omit)align_state= 0;
else{back_input();begin_token_list(u_part(cur_align),u_template);
}
}

/*:787*//*790:*/
#line 16145 "texprof.w"
static bool fin_col(void)
{
pointer p;
pointer q,r;
pointer s;
pointer u;
scaled w;
glue_ord o;
halfword n;
if(cur_align==null)confusion("endv");
q= link(cur_align);if(q==null)confusion("endv");

if(align_state<500000)
fatal_error("(interwoven alignment preambles are not allowed)");

p= link(q);
/*791:*/
#line 16178 "texprof.w"

if((p==null)&&(extra_info(cur_align)<cr_code))
if(cur_loop!=null)/*792:*/
#line 16190 "texprof.w"

{link(q)= new_null_box();p= link(q);
info(p)= end_span;width(p)= null_flag;cur_loop= link(cur_loop);
/*793:*/
#line 16199 "texprof.w"

q= hold_head;r= u_part(cur_loop);
while(r!=null)
{link(q)= get_avail();q= link(q);info(q)= info(r);r= link(r);
}
link(q)= null;u_part(p)= link(hold_head);
q= hold_head;r= v_part(cur_loop);
while(r!=null)
{link(q)= get_avail();q= link(q);info(q)= info(r);r= link(r);
}
link(q)= null;v_part(p)= link(hold_head)

/*:793*/
#line 16193 "texprof.w"
;
cur_loop= link(cur_loop);
link(p)= new_glue(glue_ptr(cur_loop));
subtype(link(p))= tab_skip_code+1;
}

/*:792*/
#line 16180 "texprof.w"

else{print_err("Extra alignment tab has been changed to ");

print_esc("cr");
help3("You have given more \\span or & marks than there were",
"in the preamble to the \\halign or \\valign now in progress.",
"So I'll assume that you meant to type \\cr instead.");
extra_info(cur_align)= cr_code;error();
}

/*:791*/
#line 16161 "texprof.w"
;
if(extra_info(cur_align)!=span_code)
{unsave();new_save_level(align_group);
/*795:*/
#line 16215 "texprof.w"

{if(mode==-hmode)
{adjust_tail= cur_tail;u= hpack(link(head),natural);w= width(u);
cur_tail= adjust_tail;adjust_tail= null;
}
else{u= vpackage(link(head),natural,0);w= height(u);
}
n= min_quarterword;
if(cur_span!=cur_align)/*797:*/
#line 16249 "texprof.w"

{q= cur_span;
do{incr(n);q= link(link(q));
}while(!(q==cur_align));
if(n> max_quarterword)confusion("256 spans");


q= cur_span;while(link(info(q))<n)q= info(q);
if(link(info(q))> n)
{s= get_node(span_node_size);info(s)= info(q);link(s)= n;
info(q)= s;width(s)= w;
}
else if(width(info(q))<w)width(info(q))= w;
}

/*:797*/
#line 16223 "texprof.w"

else if(w> width(cur_align))width(cur_align)= w;
type(u)= unset_node;span_count(u)= n;
/*658:*/
#line 13596 "texprof.w"

if(total_stretch[filll]!=0)o= filll;
else if(total_stretch[fill]!=0)o= fill;
else if(total_stretch[fil]!=0)o= fil;
else o= normal

/*:658*/
#line 16226 "texprof.w"
;
glue_order(u)= o;glue_stretch(u)= total_stretch[o];
/*664:*/
#line 13661 "texprof.w"

if(total_shrink[filll]!=0)o= filll;
else if(total_shrink[fill]!=0)o= fill;
else if(total_shrink[fil]!=0)o= fil;
else o= normal

/*:664*/
#line 16228 "texprof.w"
;
glue_sign(u)= o;glue_shrink(u)= total_shrink[o];
pop_nest();link(tail)= u;tail= u;
}

/*:795*/
#line 16164 "texprof.w"
;
/*794:*/
#line 16211 "texprof.w"

tail_append(new_glue(glue_ptr(link(cur_align))));
subtype(tail)= tab_skip_code+1

/*:794*/
#line 16165 "texprof.w"
;
if(extra_info(cur_align)>=cr_code)
{return true;
}
init_span(p);
}
align_state= 1000000;
do{get_x_or_protected();
}while(!(cur_cmd!=spacer));
cur_align= p;
init_col();return false;
}

/*:790*//*798:*/
#line 16269 "texprof.w"
static void fin_row(void)
{pointer p;
if(mode==-hmode)
{p= hpack(link(head),natural);
pop_nest();append_to_vlist(p);
if(cur_head!=cur_tail)
{link(tail)= link(cur_head);tail= cur_tail;
}
}
else{p= vpack(link(head),natural);pop_nest();
link(tail)= p;tail= p;space_factor= 1000;
}
type(p)= unset_node;glue_stretch(p)= 0;
if(every_cr!=null)begin_token_list(every_cr,every_cr_text);
align_peek();
}

/*:798*//*799:*/
#line 16290 "texprof.w"
static void do_assignments(void);
static void resume_after_display(void);
static void build_page(void);
static void fin_align(void)
{pointer p,q,r,s,u,v;
scaled t,w;
scaled o;
halfword n;
scaled rule_save;
memory_word aux_save;
if(cur_group!=align_group)confusion("align1");

unsave();
if(cur_group!=align_group)confusion("align0");
unsave();
if(nest[nest_ptr-1].mode_field==mmode)o= display_indent;
else o= 0;
/*800:*/
#line 16340 "texprof.w"

q= link(preamble);
do{flush_list(u_part(q));flush_list(v_part(q));
p= link(link(q));
if(width(q)==null_flag)
/*801:*/
#line 16354 "texprof.w"

{width(q)= 0;r= link(q);s= glue_ptr(r);
if(s!=zero_glue)
{add_glue_ref(zero_glue);delete_glue_ref(s);
glue_ptr(r)= zero_glue;
}
}

/*:801*/
#line 16345 "texprof.w"
;
if(info(q)!=end_span)
/*802:*/
#line 16369 "texprof.w"

{t= width(q)+width(glue_ptr(link(q)));
r= info(q);s= end_span;info(s)= p;n= min_quarterword+1;
do{width(r)= width(r)-t;u= info(r);
while(link(r)> n)
{s= info(s);n= link(info(s))+1;
}
if(link(r)<n)
{info(r)= info(s);info(s)= r;decr(link(r));s= r;
}
else{if(width(r)> width(info(s)))width(info(s))= width(r);
free_node(r,span_node_size);
}
r= u;
}while(!(r==end_span));
}

/*:802*/
#line 16348 "texprof.w"
;
type(q)= unset_node;span_count(q)= min_quarterword;height(q)= 0;
depth(q)= 0;glue_order(q)= normal;glue_sign(q)= normal;
glue_stretch(q)= 0;glue_shrink(q)= 0;q= p;
}while(!(q==null))

/*:800*/
#line 16308 "texprof.w"
;
/*803:*/
#line 16392 "texprof.w"

save_ptr= save_ptr-2;pack_begin_line= -mode_line;
if(mode==-vmode)
{rule_save= overfull_rule;
overfull_rule= 0;
p= hpack(preamble,saved(1),saved(0));overfull_rule= rule_save;
}
else{q= link(preamble);
do{height(q)= width(q);width(q)= 0;q= link(link(q));
}while(!(q==null));
p= vpack(preamble,saved(1),saved(0));
q= link(preamble);
do{width(q)= height(q);height(q)= 0;q= link(link(q));
}while(!(q==null));
}
pack_begin_line= 0

/*:803*/
#line 16310 "texprof.w"
;
/*804:*/
#line 16409 "texprof.w"

q= link(head);s= head;
while(q!=null)
{if(!is_char_node(q))
if(type(q)==unset_node)
/*806:*/
#line 16434 "texprof.w"

{if(mode==-vmode)
{type(q)= hlist_node;width(q)= width(p);
}
else{type(q)= vlist_node;height(q)= height(p);
}
glue_order(q)= glue_order(p);glue_sign(q)= glue_sign(p);
glue_set(q)= glue_set(p);shift_amount(q)= o;
r= link(list_ptr(q));s= link(list_ptr(p));
do{/*807:*/
#line 16453 "texprof.w"

n= span_count(r);t= width(s);w= t;u= hold_head;
while(n> min_quarterword)
{decr(n);
/*808:*/
#line 16470 "texprof.w"

s= link(s);v= glue_ptr(s);link(u)= new_glue(v);u= link(u);
subtype(u)= tab_skip_code+1;t= t+width(v);
if(glue_sign(p)==stretching)
{if(stretch_order(v)==glue_order(p))
t= t+round(unfix(glue_set(p))*stretch(v));

}
else if(glue_sign(p)==shrinking)
{if(shrink_order(v)==glue_order(p))
t= t-round(unfix(glue_set(p))*shrink(v));
}
s= link(s);link(u)= new_null_box();u= link(u);t= t+width(s);
if(mode==-vmode)width(u)= width(s);else
{type(u)= vlist_node;height(u)= width(s);
}

/*:808*/
#line 16458 "texprof.w"
;
}
if(mode==-vmode)
/*809:*/
#line 16487 "texprof.w"

{height(r)= height(q);depth(r)= depth(q);
if(t==width(r))
{glue_sign(r)= normal;glue_order(r)= normal;
set_glue_ratio_zero(glue_set(r));
}
else if(t> width(r))
{glue_sign(r)= stretching;
if(glue_stretch(r)==0)set_glue_ratio_zero(glue_set(r));
else glue_set(r)= fix((t-width(r))/(double)glue_stretch(r));

}
else{glue_order(r)= glue_sign(r);glue_sign(r)= shrinking;
if(glue_shrink(r)==0)set_glue_ratio_zero(glue_set(r));
else if((glue_order(r)==normal)&&(width(r)-t> glue_shrink(r)))
set_glue_ratio_one(glue_set(r));
else glue_set(r)= fix((width(r)-t)/(double)glue_shrink(r));
}
width(r)= w;type(r)= hlist_node;
}

/*:809*/
#line 16462 "texprof.w"

else/*810:*/
#line 16508 "texprof.w"

{width(r)= width(q);
if(t==height(r))
{glue_sign(r)= normal;glue_order(r)= normal;
set_glue_ratio_zero(glue_set(r));
}
else if(t> height(r))
{glue_sign(r)= stretching;
if(glue_stretch(r)==0)set_glue_ratio_zero(glue_set(r));
else glue_set(r)= fix((t-height(r))/(double)glue_stretch(r));

}
else{glue_order(r)= glue_sign(r);glue_sign(r)= shrinking;
if(glue_shrink(r)==0)set_glue_ratio_zero(glue_set(r));
else if((glue_order(r)==normal)&&(height(r)-t> glue_shrink(r)))
set_glue_ratio_one(glue_set(r));
else glue_set(r)= fix((height(r)-t)/(double)glue_shrink(r));
}
height(r)= w;type(r)= vlist_node;
}

/*:810*/
#line 16464 "texprof.w"
;
shift_amount(r)= 0;
if(u!=hold_head)
{link(u)= link(r);link(r)= link(hold_head);r= u;
}

/*:807*/
#line 16443 "texprof.w"
;
r= link(link(r));s= link(link(s));
}while(!(r==null));
}

/*:806*/
#line 16414 "texprof.w"

else if(type(q)==rule_node)
/*805:*/
#line 16421 "texprof.w"

{if(is_running(width(q)))width(q)= width(p);
if(is_running(height(q)))height(q)= height(p);
if(is_running(depth(q)))depth(q)= depth(p);
if(o!=0)
{r= link(q);link(q)= null;q= hpack(q,natural);
shift_amount(q)= o;link(q)= r;link(s)= q;
}
}

/*:805*/
#line 16417 "texprof.w"
;
s= q;q= link(q);
}

/*:804*/
#line 16311 "texprof.w"
;
flush_node_list(p);pop_alignment();
/*811:*/
#line 16539 "texprof.w"

aux_save= aux;p= link(head);q= tail;pop_nest();
if(mode==mmode)/*1205:*/
#line 23323 "texprof.w"

{do_assignments();
if(cur_cmd!=math_shift)/*1206:*/
#line 23337 "texprof.w"

{print_err("Missing $$ inserted");

help2("Displays can use special alignments (like \\eqalignno)",
"only if nothing but the alignment itself is between $$'s.");
back_error();
}

/*:1206*/
#line 23325 "texprof.w"

else/*1196:*/
#line 23175 "texprof.w"

{get_x_token();
if(cur_cmd!=math_shift)
{print_err("Display math should end with $$");

help2("The `$' that I just saw supposedly matches a previous `$$'.",
"So I shall assume that you typed `$$' both times.");
back_error();
}
}

/*:1196*/
#line 23326 "texprof.w"
;
pop_nest();
tail_append(new_penalty(pre_display_penalty));
tail_append(new_param_glue(above_display_skip_code));
link(tail)= p;
if(p!=null)tail= q;
tail_append(new_penalty(post_display_penalty));
tail_append(new_param_glue(below_display_skip_code));
prev_depth= aux_save.sc;resume_after_display();
}

/*:1205*/
#line 16541 "texprof.w"

else{aux= aux_save;link(tail)= p;
if(p!=null)tail= q;
if(mode==vmode)build_page();
}

/*:811*/
#line 16313 "texprof.w"
;
}
/*784:*/
#line 16055 "texprof.w"

static void align_peek(void)
{
restart:align_state= 1000000;
do{get_x_or_protected();
}while(!(cur_cmd!=spacer));
if(cur_cmd==no_align)
{scan_left_brace();new_save_level(no_align_group);
if(mode==-vmode)normal_paragraph();
}
else if(cur_cmd==right_brace)fin_align();
else if((cur_cmd==car_ret)&&(cur_chr==cr_cr_code))
goto restart;
else{init_row();
init_col();
}
}

/*:784*/
#line 16315 "texprof.w"


/*:799*//*814:*/
#line 16603 "texprof.w"
/*825:*/
#line 16843 "texprof.w"

static pointer finite_shrink(pointer p)
{pointer q;
if(no_shrink_error_yet)
{no_shrink_error_yet= false;
#ifdef STAT
if(tracing_paragraphs> 0)end_diagnostic(true);
#endif
#line 16851 "texprof.w"

print_err("Infinite glue shrinkage found in a paragraph");

help5("The paragraph just ended includes some glue that has",
"infinite shrinkability, e.g., `\\hskip 0pt minus 1fil'.",
"Such glue doesn't belong there---it allows a paragraph",
"of any length to fit on one line. But it's safe to proceed,",
"since the offensive shrinkability has been made finite.");
error();
#ifdef STAT
if(tracing_paragraphs> 0)begin_diagnostic();
#endif
#line 16863 "texprof.w"

}
q= new_spec(p);shrink_order(q)= normal;
delete_glue_ref(p);return q;
}

/*:825*//*828:*/
#line 16923 "texprof.w"

static void try_break(int pi,small_number break_type)
{
pointer r;
pointer prev_r;
halfword old_l;
bool no_break_yet;
/*829:*/
#line 16951 "texprof.w"

pointer prev_prev_r;
pointer s;
pointer q;
pointer v;
int t;
internal_font_number f;
halfword l;
bool node_r_stays_active;
scaled line_width;
int fit_class;
halfword b;
int d;
bool artificial_demerits;
#ifdef STAT
pointer save_link;
#endif
#line 16968 "texprof.w"
 scaled shortfall;

/*:829*/
#line 16930 "texprof.w"

/*830:*/
#line 16970 "texprof.w"

if(abs(pi)>=inf_penalty)
if(pi> 0)goto end;
else pi= eject_penalty

/*:830*/
#line 16931 "texprof.w"
;
no_break_yet= true;prev_r= active;old_l= 0;
do_all_six(copy_to_cur_active);
loop{resume:r= link(prev_r);
/*831:*/
#line 16980 "texprof.w"


if(type(r)==delta_node)
{do_all_six(update_width);
prev_prev_r= prev_r;prev_r= r;goto resume;
}

/*:831*/
#line 16936 "texprof.w"
;
/*834:*/
#line 17028 "texprof.w"

{l= line_number(r);
if(l> old_l)
{
if((minimum_demerits<awful_bad)&&
((old_l!=easy_line)||(r==last_active)))
/*835:*/
#line 17046 "texprof.w"

{if(no_break_yet)/*836:*/
#line 17082 "texprof.w"

{no_break_yet= false;do_all_six(set_break_width_to_background);
s= cur_p;
if(break_type> unhyphenated)if(cur_p!=null)
/*839:*/
#line 17125 "texprof.w"

{t= replace_count(cur_p);v= cur_p;s= post_break(cur_p);
while(t> 0)
{decr(t);v= link(v);
/*840:*/
#line 17143 "texprof.w"

if(is_char_node(v))
{f= font(v);
break_width[1]= break_width[1]-char_width(f,char_info(f,character(v)));
}
else switch(type(v)){
case ligature_node:{f= font(lig_char(v));
break_width[1]= break_width[1]-
char_width(f,char_info(f,character(lig_char(v))));
}break;
case hlist_node:case vlist_node:case rule_node:
case kern_node:
break_width[1]= break_width[1]-width(v);break;
default:confusion("disc1");

}

/*:840*/
#line 17129 "texprof.w"
;
}
while(s!=null)
{/*841:*/
#line 17160 "texprof.w"

if(is_char_node(s))
{f= font(s);
break_width[1]= break_width[1]+char_width(f,char_info(f,character(s)));
}
else switch(type(s)){
case ligature_node:{f= font(lig_char(s));
break_width[1]= break_width[1]+
char_width(f,char_info(f,character(lig_char(s))));
}break;
case hlist_node:case vlist_node:case rule_node:
case kern_node:
break_width[1]= break_width[1]+width(s);break;
default:confusion("disc2");

}

/*:841*/
#line 17132 "texprof.w"
;
s= link(s);
}
break_width[1]= break_width[1]+disc_width;
if(post_break(cur_p)==null)s= link(v);

}

/*:839*/
#line 17086 "texprof.w"
;
while(s!=null)
{if(is_char_node(s))goto done;
switch(type(s)){
case glue_node:/*837:*/
#line 17101 "texprof.w"

{v= glue_ptr(s);break_width[1]= break_width[1]-width(v);
break_width[2+stretch_order(v)]= break_width[2+stretch_order(v)]-stretch(v);
break_width[6]= break_width[6]-shrink(v);
}

/*:837*/
#line 17090 "texprof.w"
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

/*:836*/
#line 17047 "texprof.w"
;
/*842:*/
#line 17186 "texprof.w"

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

/*:842*/
#line 17048 "texprof.w"
;
if(abs(adj_demerits)>=awful_bad-minimum_demerits)
minimum_demerits= awful_bad-1;
else minimum_demerits= minimum_demerits+abs(adj_demerits);
for(fit_class= very_loose_fit;fit_class<=tight_fit;fit_class++)
{if(minimal_demerits[fit_class]<=minimum_demerits)
/*844:*/
#line 17216 "texprof.w"

{q= get_node(passive_node_size);
link(q)= passive;passive= q;cur_break(q)= cur_p;
#ifdef STAT
incr(pass_number);serial(q)= pass_number;
#endif
#line 17222 "texprof.w"

prev_break(q)= best_place[fit_class];
q= get_node(active_node_size);break_node(q)= passive;
line_number(q)= best_pl_line[fit_class]+1;
fitness(q)= fit_class;type(q)= break_type;
total_demerits(q)= minimal_demerits[fit_class];
link(q)= r;link(prev_r)= q;prev_r= q;
#ifdef STAT
if(tracing_paragraphs> 0)
/*845:*/
#line 17236 "texprof.w"

{print_nl("@@");print_int(serial(passive));

print(": line ");print_int(line_number(q)-1);
print_char('.');print_int(fit_class);
if(break_type==hyphenated)print_char('-');
print(" t=");print_int(total_demerits(q));
print(" -> @@");
if(prev_break(passive)==null)print_char('0');
else print_int(serial(prev_break(passive)));
}

/*:845*/
#line 17231 "texprof.w"
;
#endif
#line 17233 "texprof.w"

}

/*:844*/
#line 17054 "texprof.w"
;
minimal_demerits[fit_class]= awful_bad;
}
minimum_demerits= awful_bad;
/*843:*/
#line 17205 "texprof.w"

if(r!=last_active)
{q= get_node(delta_node_size);link(q)= r;type(q)= delta_node;
subtype(q)= 0;
do_all_six(new_delta_from_break_width);
link(prev_r)= q;prev_prev_r= prev_r;prev_r= q;
}

/*:843*/
#line 17058 "texprof.w"
;
}

/*:835*/
#line 17034 "texprof.w"
;
if(r==last_active)goto end;
/*849:*/
#line 17312 "texprof.w"

if(l> easy_line)
{line_width= second_width;old_l= max_halfword-1;
}
else{old_l= l;
if(l> last_special_line)line_width= second_width;
else if(par_shape_ptr==null)line_width= first_width;
else line_width= mem[par_shape_ptr+2*l].sc;
}

/*:849*/
#line 17036 "texprof.w"
;
}
}

/*:834*/
#line 16939 "texprof.w"
;
/*850:*/
#line 17332 "texprof.w"

{artificial_demerits= false;

shortfall= line_width-cur_active_width[1];
if(shortfall> 0)
/*851:*/
#line 17362 "texprof.w"

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

/*:851*/
#line 17338 "texprof.w"

else/*852:*/
#line 17381 "texprof.w"

{if(-shortfall> cur_active_width[6])b= inf_bad+1;
else b= badness(-shortfall,cur_active_width[6]);
if(b> 12)fit_class= tight_fit;else fit_class= decent_fit;
}

/*:852*/
#line 17340 "texprof.w"
;
if((b> inf_bad)||(pi==eject_penalty))
/*853:*/
#line 17396 "texprof.w"

{if(final_pass&&(minimum_demerits==awful_bad)&&
(link(r)==last_active)&&
(prev_r==active))
artificial_demerits= true;
else if(b> threshold)goto deactivate;
node_r_stays_active= false;
}

/*:853*/
#line 17343 "texprof.w"

else{prev_r= r;
if(b> threshold)goto resume;
node_r_stays_active= true;
}
/*854:*/
#line 17412 "texprof.w"

if(artificial_demerits)d= 0;
else/*858:*/
#line 17473 "texprof.w"

{d= line_penalty+b;
if(abs(d)>=10000)d= 100000000;else d= d*d;
if(pi!=0)
if(pi> 0)d= d+pi*pi;
else if(pi> eject_penalty)d= d-pi*pi;
if((break_type==hyphenated)&&(type(r)==hyphenated))
if(cur_p!=null)d= d+double_hyphen_demerits;
else d= d+final_hyphen_demerits;
if(abs(fit_class-fitness(r))> 1)d= d+adj_demerits;
}

/*:858*/
#line 17414 "texprof.w"
;
#ifdef STAT
if(tracing_paragraphs> 0)
/*855:*/
#line 17428 "texprof.w"

{if(printed_node!=cur_p)
/*856:*/
#line 17450 "texprof.w"

{print_nl("");
if(cur_p==null)short_display(link(printed_node));
else{save_link= link(cur_p);
link(cur_p)= null;print_nl("");short_display(link(printed_node));
link(cur_p)= save_link;
}
printed_node= cur_p;
}

/*:856*/
#line 17430 "texprof.w"
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

/*:855*/
#line 17417 "texprof.w"
;
#endif
#line 17419 "texprof.w"

d= d+total_demerits(r);

if(d<=minimal_demerits[fit_class])
{minimal_demerits[fit_class]= d;
best_place[fit_class]= break_node(r);best_pl_line[fit_class]= l;
if(d<minimum_demerits)minimum_demerits= d;
}

/*:854*/
#line 17348 "texprof.w"
;
if(node_r_stays_active)goto resume;
deactivate:/*859:*/
#line 17495 "texprof.w"

link(prev_r)= link(r);free_node(r,active_node_size);
if(prev_r==active)/*860:*/
#line 17520 "texprof.w"

{r= link(active);
if(type(r)==delta_node)
{do_all_six(update_active);
do_all_six(copy_to_cur_active);
link(active)= link(r);free_node(r,delta_node_size);
}
}

/*:860*/
#line 17498 "texprof.w"

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

/*:859*/
#line 17350 "texprof.w"
;
}

/*:850*/
#line 16942 "texprof.w"
;
}
end:;
#ifdef STAT
/*857:*/
#line 17465 "texprof.w"

if(cur_p==printed_node)if(cur_p!=null)if(type(cur_p)==disc_node)
{t= replace_count(cur_p);
while(t> 0)
{decr(t);printed_node= link(printed_node);
}
}

/*:857*/
#line 16946 "texprof.w"
;
#endif
#line 16948 "texprof.w"

}

/*:828*//*876:*/
#line 17849 "texprof.w"

static void post_line_break(int final_widow_penalty)
{
pointer q,r,s;
bool disc_break;
bool post_disc_break;
scaled cur_width;
scaled cur_indent;
quarterword t;
int pen;
halfword cur_line;
/*877:*/
#line 17881 "texprof.w"

q= break_node(best_bet);cur_p= null;
do{r= q;q= prev_break(q);next_break(r)= cur_p;cur_p= r;
}while(!(q==null))

/*:877*/
#line 17861 "texprof.w"
;
cur_line= prev_graf+1;
do{/*879:*/
#line 17918 "texprof.w"

/*880:*/
#line 17930 "texprof.w"

q= cur_break(cur_p);disc_break= false;post_disc_break= false;
if(q!=null)
if(type(q)==glue_node)
{delete_glue_ref(glue_ptr(q));
glue_ptr(q)= right_skip;
subtype(q)= right_skip_code+1;add_glue_ref(right_skip);
goto done;
}
else{if(type(q)==disc_node)
/*881:*/
#line 17949 "texprof.w"

{t= replace_count(q);
/*882:*/
#line 17958 "texprof.w"

if(t==0)r= link(q);
else{r= q;
while(t> 1)
{r= link(r);decr(t);
}
s= link(r);
r= link(s);link(s)= null;
flush_node_list(link(q));replace_count(q)= 0;
}

/*:882*/
#line 17952 "texprof.w"
;
if(post_break(q)!=null)/*883:*/
#line 17972 "texprof.w"

{s= post_break(q);
while(link(s)!=null)s= link(s);
link(s)= r;r= post_break(q);post_break(q)= null;post_disc_break= true;
}

/*:883*/
#line 17953 "texprof.w"
;
if(pre_break(q)!=null)/*884:*/
#line 17981 "texprof.w"

{s= pre_break(q);link(q)= s;
while(link(s)!=null)s= link(s);
pre_break(q)= null;q= s;
}

/*:884*/
#line 17954 "texprof.w"
;
link(q)= r;disc_break= true;
}

/*:881*/
#line 17940 "texprof.w"

else if((type(q)==math_node)||(type(q)==kern_node))width(q)= 0;
}
else{q= temp_head;
while(link(q)!=null)q= link(q);
}
/*885:*/
#line 17987 "texprof.w"

r= new_param_glue(right_skip_code);link(r)= link(q);link(q)= r;q= r

/*:885*/
#line 17946 "texprof.w"
;
done:

/*:880*/
#line 17920 "texprof.w"
;
/*886:*/
#line 17994 "texprof.w"

r= link(q);link(q)= null;q= link(temp_head);link(temp_head)= r;
if(left_skip!=zero_glue)
{r= new_param_glue(left_skip_code);
link(r)= q;q= r;
}

/*:886*/
#line 17921 "texprof.w"
;
/*888:*/
#line 18013 "texprof.w"

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

/*:888*/
#line 17922 "texprof.w"
;
/*887:*/
#line 18001 "texprof.w"

append_to_vlist(just_box);
if(adjust_head!=adjust_tail)
{link(tail)= link(adjust_head);tail= adjust_tail;
}
adjust_tail= null

/*:887*/
#line 17924 "texprof.w"
;
/*889:*/
#line 18033 "texprof.w"

if(cur_line+1!=best_line)
{pen= inter_line_penalty;
if(cur_line==prev_graf+1)pen= pen+club_penalty;
if(cur_line+2==best_line)pen= pen+final_widow_penalty;
if(disc_break)pen= pen+broken_penalty;
if(pen!=0)
{r= new_penalty(pen);
link(tail)= r;tail= r;
}
}

/*:889*/
#line 17925 "texprof.w"


/*:879*/
#line 17864 "texprof.w"
;
incr(cur_line);cur_p= next_break(cur_p);
if(cur_p!=null)if(!post_disc_break)
/*878:*/
#line 17893 "texprof.w"

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

/*:878*/
#line 17867 "texprof.w"
;
}while(!(cur_p==null));
if((cur_line!=best_line)||(link(temp_head)!=null))
confusion("line breaking");

prev_graf= best_line-1;
}

/*:876*//*894:*/
#line 18148 "texprof.w"

/*905:*/
#line 18382 "texprof.w"

static
small_number reconstitute(small_number j,small_number n,halfword bchar,halfword hchar)
{
pointer p;
pointer t;
four_quarters q;
halfword cur_rh;
halfword test_char;
scaled w;
font_index k;
hyphen_passed= 0;t= hold_head;w= 0;link(hold_head)= null;

/*907:*/
#line 18434 "texprof.w"

cur_l= qi(hu[j]);cur_q= t;
if(j==0)
{ligature_present= init_lig;p= init_list;
if(ligature_present)lft_hit= init_lft;
while(p> null)
{append_charnode_to_t(character(p));p= link(p);
}
}
else if(cur_l<non_char)append_charnode_to_t(cur_l);
lig_stack= null;set_cur_r

/*:907*/
#line 18395 "texprof.w"
;
resume:/*908:*/
#line 18450 "texprof.w"

if(cur_l==non_char)
{k= bchar_label[hf];
if(k==non_address)goto done;else q= font_info[k].qqqq;
}
else{q= char_info(hf,cur_l);
if(char_tag(q)!=lig_tag)goto done;
k= lig_kern_start(hf,q);q= font_info[k].qqqq;
if(skip_byte(q)> stop_flag)
{k= lig_kern_restart(hf,q);q= font_info[k].qqqq;
}
}
if(cur_rh<non_char)test_char= cur_rh;else test_char= cur_r;
loop{if(next_char(q)==test_char)if(skip_byte(q)<=stop_flag)
if(cur_rh<non_char)
{hyphen_passed= j;hchar= non_char;cur_rh= non_char;
goto resume;
}
else{if(hchar<non_char)if(odd(hyf[j]))
{hyphen_passed= j;hchar= non_char;
}
if(op_byte(q)<kern_flag)
/*910:*/
#line 18513 "texprof.w"

{if(cur_l==non_char)lft_hit= true;
if(j==n)if(lig_stack==null)rt_hit= true;
check_interrupt;
switch(op_byte(q)){
case qi(1):case qi(5):{cur_l= rem_byte(q);
ligature_present= true;
}break;
case qi(2):case qi(6):{cur_r= rem_byte(q);
if(lig_stack> null)character(lig_stack)= cur_r;
else{lig_stack= new_lig_item(cur_r);
if(j==n)bchar= non_char;
else{p= get_avail();lig_ptr(lig_stack)= p;
character(p)= qi(hu[j+1]);font(p)= hf;
}
}
}break;
case qi(3):{cur_r= rem_byte(q);
p= lig_stack;lig_stack= new_lig_item(cur_r);link(lig_stack)= p;
}break;
case qi(7):case qi(11):{wrap_lig(false);
cur_q= t;cur_l= rem_byte(q);ligature_present= true;
}break;
default:{cur_l= rem_byte(q);ligature_present= true;
if(lig_stack> null)pop_lig_stack
else if(j==n)goto done;
else{append_charnode_to_t(cur_r);incr(j);set_cur_r;
}
}
}
if(op_byte(q)> qi(4))if(op_byte(q)!=qi(7))goto done;
goto resume;
}

/*:910*/
#line 18474 "texprof.w"
;
w= char_kern(hf,q);goto done;
}
if(skip_byte(q)>=stop_flag)
if(cur_rh==non_char)goto done;
else{cur_rh= non_char;goto resume;
}
k= k+qo(skip_byte(q))+1;q= font_info[k].qqqq;
}
done:

/*:908*/
#line 18397 "texprof.w"
;
/*909:*/
#line 18503 "texprof.w"

wrap_lig(rt_hit);
if(w!=0)
{link(t)= new_kern(w);t= link(t);w= 0;
}
if(lig_stack> null)
{cur_q= t;cur_l= character(lig_stack);ligature_present= true;
pop_lig_stack;goto resume;
}

/*:909*/
#line 18399 "texprof.w"
;
return j;
}

/*:905*/
#line 18149 "texprof.w"

static void hyphenate(void)
{
/*900:*/
#line 18261 "texprof.w"

int i,j,l;
pointer q,r,s;
halfword bchar;

/*:900*//*911:*/
#line 18556 "texprof.w"

pointer major_tail,minor_tail;

ASCII_code c;
int c_loc;
int r_count;
pointer hyf_node;

/*:911*//*921:*/
#line 18735 "texprof.w"

trie_pointer z;
int v;

/*:921*//*928:*/
#line 18807 "texprof.w"

hyph_pointer h;
str_number k;
pool_pointer u;

/*:928*/
#line 18152 "texprof.w"

/*922:*/
#line 18744 "texprof.w"

for(j= 0;j<=hn;j++)hyf[j]= 0;
/*929:*/
#line 18816 "texprof.w"

h= hc[1];incr(hn);hc[hn]= cur_lang;
for(j= 2;j<=hn;j++)h= (h+h+hc[j])%hyph_size;
loop{/*930:*/
#line 18826 "texprof.w"

k= hyph_word[h];if(k==0)goto not_found;
if(length(k)<hn)goto not_found;
if(length(k)==hn)
{j= 1;u= str_start[k];
do{if(so(str_pool[u])<hc[j])goto not_found;
if(so(str_pool[u])> hc[j])goto done;
incr(j);incr(u);
}while(!(j> hn));
/*931:*/
#line 18840 "texprof.w"

s= hyph_list[h];
while(s!=null)
{hyf[info(s)]= 1;s= link(s);
}

/*:931*/
#line 18835 "texprof.w"
;
decr(hn);goto found;
}
done:

/*:930*/
#line 18821 "texprof.w"
;
if(h> 0)decr(h);else h= hyph_size;
}
not_found:decr(hn)

/*:929*/
#line 18747 "texprof.w"
;
if(trie_char(cur_lang+1)!=qi(cur_lang))return;
hc[0]= 0;hc[hn+1]= 0;hc[hn+2]= 256;
for(j= 0;j<=hn-r_hyf+1;j++)
{z= trie_link(cur_lang+1)+hc[j];l= j;
while(hc[l]==qo(trie_char(z)))
{if(trie_op(z)!=min_quarterword)
/*923:*/
#line 18761 "texprof.w"

{v= trie_op(z);
do{v= v+op_start[cur_lang];i= l-hyf_distance[v];
if(hyf_num[v]> hyf[i])hyf[i]= hyf_num[v];
v= hyf_next[v];
}while(!(v==min_quarterword));
}

/*:923*/
#line 18754 "texprof.w"
;
incr(l);z= trie_link(z)+hc[l];
}
}
found:for(j= 0;j<=l_hyf-1;j++)hyf[j]= 0;
for(j= 0;j<=r_hyf-1;j++)hyf[hn-j]= 0

/*:922*/
#line 18153 "texprof.w"
;
/*901:*/
#line 18273 "texprof.w"

for(j= l_hyf;j<=hn-r_hyf;j++)if(odd(hyf[j]))goto found1;
return;
found1:

/*:901*/
#line 18154 "texprof.w"
;
/*902:*/
#line 18289 "texprof.w"

q= link(hb);link(hb)= null;r= link(ha);link(ha)= null;bchar= hyf_bchar;
if(is_char_node(ha))
if(font(ha)!=hf)goto found2;
else{init_list= ha;init_lig= false;hu[0]= qo(character(ha));
}
else if(type(ha)==ligature_node)
if(font(lig_char(ha))!=hf)goto found2;
else{init_list= lig_ptr(ha);init_lig= true;init_lft= (subtype(ha)> 1);
hu[0]= qo(character(lig_char(ha)));
if(init_list==null)if(init_lft)
{hu[0]= 256;init_lig= false;
}
free_node(ha,small_node_size);
}
else{
if(!is_char_node(r))if(type(r)==ligature_node)
if(subtype(r)> 1)goto found2;
j= 1;s= ha;init_list= null;goto common_ending;
}
s= cur_p;
while(link(s)!=ha)s= link(s);
j= 0;goto common_ending;
found2:s= ha;j= 0;hu[0]= 256;init_lig= false;init_list= null;
common_ending:flush_node_list(r);
/*912:*/
#line 18566 "texprof.w"

do{l= j;j= reconstitute(j,hn,bchar,qi(hyf_char))+1;
if(hyphen_passed==0)
{link(s)= link(hold_head);
while(link(s)> null)s= link(s);
if(odd(hyf[j-1]))
{l= j;hyphen_passed= j-1;link(hold_head)= null;
}
}
if(hyphen_passed> 0)
/*913:*/
#line 18591 "texprof.w"

do{r= get_node(small_node_size);
link(r)= link(hold_head);type(r)= disc_node;
major_tail= r;r_count= 0;
while(link(major_tail)> null)advance_major_tail;
i= hyphen_passed;hyf[i]= 0;
/*914:*/
#line 18608 "texprof.w"

minor_tail= null;pre_break(r)= null;hyf_node= new_character(hf,hyf_char);
if(hyf_node!=null)
{incr(i);c= hu[i];hu[i]= hyf_char;free_avail(hyf_node);
}
while(l<=i)
{l= reconstitute(l,i,font_bchar[hf],non_char)+1;
if(link(hold_head)> null)
{if(minor_tail==null)pre_break(r)= link(hold_head);
else link(minor_tail)= link(hold_head);
minor_tail= link(hold_head);
while(link(minor_tail)> null)minor_tail= link(minor_tail);
}
}
if(hyf_node!=null)
{hu[i]= c;
l= i;decr(i);
}

/*:914*/
#line 18597 "texprof.w"
;
/*915:*/
#line 18629 "texprof.w"

minor_tail= null;post_break(r)= null;c_loc= 0;
if(bchar_label[hf]!=non_address)
{decr(l);c= hu[l];c_loc= l;hu[l]= 256;
}
while(l<j)
{do{l= reconstitute(l,hn,bchar,non_char)+1;
if(c_loc> 0)
{hu[c_loc]= c;c_loc= 0;
}
if(link(hold_head)> null)
{if(minor_tail==null)post_break(r)= link(hold_head);
else link(minor_tail)= link(hold_head);
minor_tail= link(hold_head);
while(link(minor_tail)> null)minor_tail= link(minor_tail);
}
}while(!(l>=j));
while(l> j)
/*916:*/
#line 18650 "texprof.w"

{j= reconstitute(j,hn,bchar,non_char)+1;
link(major_tail)= link(hold_head);
while(link(major_tail)> null)advance_major_tail;
}

/*:916*/
#line 18647 "texprof.w"
;
}

/*:915*/
#line 18599 "texprof.w"
;
/*917:*/
#line 18660 "texprof.w"

if(r_count> 127)
{link(s)= link(r);link(r)= null;flush_node_list(r);
}
else{link(s)= r;replace_count(r)= r_count;
}
s= major_tail

/*:917*/
#line 18601 "texprof.w"
;
hyphen_passed= j-1;link(hold_head)= null;
}while(!(!odd(hyf[j-1])))

/*:913*/
#line 18577 "texprof.w"
;
}while(!(j> hn));
link(s)= q

/*:912*/
#line 18314 "texprof.w"
;
flush_list(init_list)

/*:902*/
#line 18156 "texprof.w"
;
}

/*:894*//*941:*/
#line 18982 "texprof.w"

#ifdef INIT
/*943:*/
#line 19032 "texprof.w"

static quarterword new_trie_op(small_number d,small_number n,quarterword v)
{
int h;
quarterword u;
int l;
h= abs(n+313*d+361*v+1009*cur_lang)%(trie_op_size+trie_op_size)
-trie_op_size;
loop{l= trie_op_hash[h];
if(l==0)
{if(trie_op_ptr==trie_op_size)
overflow("pattern memory ops",trie_op_size);
u= trie_used[cur_lang];
if(u==max_quarterword)
overflow("pattern memory ops per language",
max_quarterword-min_quarterword);
incr(trie_op_ptr);incr(u);trie_used[cur_lang]= u;
hyf_distance[trie_op_ptr]= d;
hyf_num[trie_op_ptr]= n;hyf_next[trie_op_ptr]= v;
trie_op_lang[trie_op_ptr]= cur_lang;trie_op_hash[h]= trie_op_ptr;
trie_op_val[trie_op_ptr]= u;return u;
}
if((hyf_distance[l]==d)&&(hyf_num[l]==n)&&(hyf_next[l]==v)
&&(trie_op_lang[l]==cur_lang))
{return trie_op_val[l];
}
if(h> -trie_op_size)decr(h);else h= trie_op_size;
}
}

/*:943*//*947:*/
#line 19134 "texprof.w"

static trie_pointer trie_node(trie_pointer p)

{
trie_pointer h;
trie_pointer q;
h= abs(trie_c[p]+1009*trie_o[p]+
2718*trie_l[p]+3142*trie_r[p])%trie_size;
loop{q= trie_hash[h];
if(q==0)
{trie_hash[h]= p;return p;
}
if((trie_c[q]==trie_c[p])&&(trie_o[q]==trie_o[p])&&
(trie_l[q]==trie_l[p])&&(trie_r[q]==trie_r[p]))
{return q;
}
if(h> 0)decr(h);else h= trie_size;
}
}

/*:947*//*948:*/
#line 19160 "texprof.w"

static trie_pointer compress_trie(trie_pointer p)
{if(p==0)return 0;
else{trie_l[p]= compress_trie(trie_l[p]);
trie_r[p]= compress_trie(trie_r[p]);
return trie_node(p);
}
}

/*:948*//*952:*/
#line 19233 "texprof.w"

static void first_fit(trie_pointer p)
{
trie_pointer h;
trie_pointer z;
trie_pointer q;
ASCII_code c;
trie_pointer l,r;
int ll;
c= so(trie_c[p]);
z= trie_min[c];
loop{h= z-c;
/*953:*/
#line 19258 "texprof.w"

if(trie_max<h+256)
{if(trie_size<=h+256)overflow("pattern memory",trie_size);

do{incr(trie_max);trie_taken[trie_max]= false;
trie_link(trie_max)= trie_max+1;trie_back(trie_max)= trie_max-1;
}while(!(trie_max==h+256));
}

/*:953*/
#line 19245 "texprof.w"
;
if(trie_taken[h])goto not_found;
/*954:*/
#line 19267 "texprof.w"

q= trie_r[p];
while(q> 0)
{if(trie_link(h+so(trie_c[q]))==0)goto not_found;
q= trie_r[q];
}
goto found

/*:954*/
#line 19248 "texprof.w"
;
not_found:z= trie_link(z);
}
found:/*955:*/
#line 19275 "texprof.w"

trie_taken[h]= true;trie_ref[p]= h;q= p;
do{z= h+so(trie_c[q]);l= trie_back(z);r= trie_link(z);
trie_back(r)= l;trie_link(l)= r;trie_link(z)= 0;
if(l<256)
{if(z<256)ll= z;else ll= 256;
do{trie_min[l]= r;incr(l);
}while(!(l==ll));
}
q= trie_r[q];
}while(!(q==0))

/*:955*/
#line 19251 "texprof.w"
;
}

/*:952*//*956:*/
#line 19290 "texprof.w"

static void trie_pack(trie_pointer p)
{trie_pointer q;
do{q= trie_l[p];
if((q> 0)&&(trie_ref[q]==0))
{first_fit(q);trie_pack(q);
}
p= trie_r[p];
}while(!(p==0));
}

/*:956*//*958:*/
#line 19327 "texprof.w"

static void trie_fix(trie_pointer p)
{trie_pointer q;
ASCII_code c;
trie_pointer z;
z= trie_ref[p];
do{q= trie_l[p];c= so(trie_c[p]);
trie_link(z+c)= trie_ref[q];trie_char(z+c)= qi(c);trie_op(z+c)= trie_o[p];
if(q> 0)trie_fix(q);
p= trie_r[p];
}while(!(p==0));
}

/*:958*//*959:*/
#line 19344 "texprof.w"

static void new_patterns(void)
{
int k,l;

bool digit_sensed;
quarterword v;
trie_pointer p,q;
bool first_child;
int c;
if(trie_not_ready)
{set_cur_lang;scan_left_brace();
/*960:*/
#line 19371 "texprof.w"

k= 0;hyf[0]= 0;digit_sensed= false;
loop{get_x_token();
switch(cur_cmd){
case letter:case other_char:/*961:*/
#line 19389 "texprof.w"

if(digit_sensed||(cur_chr<'0')||(cur_chr> '9'))
{if(cur_chr=='.')cur_chr= 0;
else{cur_chr= lc_code(cur_chr);
if(cur_chr==0)
{print_err("Nonletter");

help1("(See Appendix H.)");error();
}
}
if(k<63)
{incr(k);hc[k]= cur_chr;hyf[k]= 0;digit_sensed= false;
}
}
else if(k<63)
{hyf[k]= cur_chr-'0';digit_sensed= true;
}

/*:961*/
#line 19375 "texprof.w"
break;
case spacer:case right_brace:{if(k> 0)
/*962:*/
#line 19411 "texprof.w"

{/*964:*/
#line 19439 "texprof.w"

if(hc[1]==0)hyf[0]= 0;
if(hc[k]==0)hyf[k]= 0;
l= k;v= min_quarterword;
loop{if(hyf[l]!=0)v= new_trie_op(k-l,hyf[l],v);
if(l> 0)decr(l);else goto done1;
}
done1:

/*:964*/
#line 19412 "texprof.w"
;
q= 0;hc[0]= cur_lang;
while(l<=k)
{c= hc[l];incr(l);p= trie_l[q];first_child= true;
while((p> 0)&&(c> so(trie_c[p])))
{q= p;p= trie_r[q];first_child= false;
}
if((p==0)||(c<so(trie_c[p])))
/*963:*/
#line 19431 "texprof.w"

{if(trie_ptr==trie_size)overflow("pattern memory",trie_size);

incr(trie_ptr);trie_r[trie_ptr]= p;p= trie_ptr;trie_l[p]= 0;
if(first_child)trie_l[q]= p;else trie_r[q]= p;
trie_c[p]= si(c);trie_o[p]= min_quarterword;
}

/*:963*/
#line 19420 "texprof.w"
;
q= p;
}
if(trie_o[q]!=min_quarterword)
{print_err("Duplicate pattern");

help1("(See Appendix H.)");error();
}
trie_o[q]= v;
}

/*:962*/
#line 19377 "texprof.w"
;
if(cur_cmd==right_brace)goto done;
k= 0;hyf[0]= 0;digit_sensed= false;
}break;
default:{print_err("Bad ");print_esc("patterns");

help1("(See Appendix H.)");error();
}
}
}
done:

/*:960*/
#line 19357 "texprof.w"
;
if(saving_hyph_codes> 0)
/*1525:*/
#line 28039 "texprof.w"

{c= cur_lang;first_child= false;p= 0;
do{q= p;p= trie_r[q];
}while(!((p==0)||(c<=so(trie_c[p]))));
if((p==0)||(c<so(trie_c[p])))
/*963:*/
#line 19431 "texprof.w"

{if(trie_ptr==trie_size)overflow("pattern memory",trie_size);

incr(trie_ptr);trie_r[trie_ptr]= p;p= trie_ptr;trie_l[p]= 0;
if(first_child)trie_l[q]= p;else trie_r[q]= p;
trie_c[p]= si(c);trie_o[p]= min_quarterword;
}

/*:963*/
#line 28044 "texprof.w"
;
q= p;
/*1526:*/
#line 28054 "texprof.w"

p= trie_l[q];first_child= true;
for(c= 0;c<=255;c++)
if((lc_code(c)> 0)||((c==255)&&first_child))
{if(p==0)
/*963:*/
#line 19431 "texprof.w"

{if(trie_ptr==trie_size)overflow("pattern memory",trie_size);

incr(trie_ptr);trie_r[trie_ptr]= p;p= trie_ptr;trie_l[p]= 0;
if(first_child)trie_l[q]= p;else trie_r[q]= p;
trie_c[p]= si(c);trie_o[p]= min_quarterword;
}

/*:963*/
#line 28060 "texprof.w"

else trie_c[p]= si(c);
trie_o[p]= qi(lc_code(c));
q= p;p= trie_r[q];first_child= false;
}
if(first_child)trie_l[q]= 0;else trie_r[q]= 0

/*:1526*/
#line 28046 "texprof.w"
;
}

/*:1525*/
#line 19359 "texprof.w"
;
}
else{print_err("Too late for ");print_esc("patterns");
help1("All patterns must be given before typesetting begins.");
error();link(garbage)= scan_toks(false,false);flush_list(def_ref);
}
}

/*:959*//*965:*/
#line 19455 "texprof.w"

static void init_trie(void)
{int p;
int j,k,t;
int r,s;
two_halves h;
/*1766:*/
#line 31393 "texprof.w"

int tmp_cmd;
int tmp_file_line;
int tmp_depth;

/*:1766*/
#line 19461 "texprof.w"

/*1769:*/
#line 31419 "texprof.w"

if(profile_on)
{/*1761:*/
#line 31310 "texprof.w"

if(profile_on)
{if(st_count+3> MAX_STAMPS)
overflow("profile data",MAX_STAMPS);
/*1779:*/
#line 31656 "texprof.w"

if(last_depth> prof_depth)
{if(last_depth==prof_depth+1)
prof_cmd= prof_cmd|POP_BIT;
else
stamp[st_count++]= (system_macro_pop<<24)|(last_depth-prof_depth);
#if SHOW_RECORD_TIMING
print_char('{');print_int(cmd_count);
print_char(':');print_int(system_macro_pop);
print_char(':');print_int(last_depth);
print_char('>');print_int(prof_depth);
print_char('}');print_ln();
#endif
#line 31669 "texprof.w"
 cmd_count++;
last_depth= unchanged_depth= prof_depth;
}


/*:1779*/
#line 31314 "texprof.w"

stamp[st_count++]= (prof_cmd<<24)|prof_file_line;
prof_cmd= prof_cmd&~POP_BIT;
#if SHOW_RECORD_TIMING
print_char('<');print_int(cmd_count);
print_char(':');
if(prof_cmd&POP_BIT)print_char('-');
print_int(prof_cmd&~POP_BIT);
print_char(':');print_int(prof_depth);
print_char('>');print_ln();
#endif
#line 31325 "texprof.w"
 cmd_count++;
/*1756:*/
#line 31198 "texprof.w"

#if GETTIME==0
time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#elif GETTIME==1
#line 31202 "texprof.w"
 time_error= clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&ts);
#elif GETTIME==2
#line 31204 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
#elif GETTIME==3
#line 31206 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC,&ts);
#else
#line 31208 "texprof.w"
 time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#endif
#line 31210 "texprof.w"

/*:1756*/
#line 31326 "texprof.w"

/*1757:*/
#line 31215 "texprof.w"

diff_nsec= (ts.tv_sec-start_sec)*1000000000+(ts.tv_nsec-start_nsec);
#if 0
printf("time: %ld %ld %ld\n",diff_nsec,(ts.tv_sec),(ts.tv_nsec));
#endif
#line 31220 "texprof.w"

start_nsec= ts.tv_nsec;
start_sec= ts.tv_sec;

/*:1757*/
#line 31327 "texprof.w"

stamp[st_count++]= diff_nsec;
}


/*:1761*/
#line 31421 "texprof.w"

tmp_file_line= prof_file_line;
tmp_cmd= prof_cmd;
tmp_depth= prof_depth;
prof_file_line= FILE_LINE(system_file,system_init_trie);
prof_cmd= system_cmd;
}


/*:1769*/
#line 19462 "texprof.w"

/*951:*/
#line 19217 "texprof.w"

/*944:*/
#line 19066 "texprof.w"

op_start[0]= -min_quarterword;
for(j= 1;j<=255;j++)op_start[j]= op_start[j-1]+qo(trie_used[j-1]);
for(j= 1;j<=trie_op_ptr;j++)
trie_op_hash[j]= op_start[trie_op_lang[j]]+trie_op_val[j];
for(j= 1;j<=trie_op_ptr;j++)while(trie_op_hash[j]> j)
{k= trie_op_hash[j];
t= hyf_distance[k];hyf_distance[k]= hyf_distance[j];hyf_distance[j]= t;
t= hyf_num[k];hyf_num[k]= hyf_num[j];hyf_num[j]= t;
t= hyf_next[k];hyf_next[k]= hyf_next[j];hyf_next[j]= t;
trie_op_hash[j]= trie_op_hash[k];trie_op_hash[k]= k;
}

/*:944*/
#line 19218 "texprof.w"
;
for(p= 0;p<=trie_size;p++)trie_hash[p]= 0;
hyph_root= compress_trie(hyph_root);
trie_root= compress_trie(trie_root);
for(p= 0;p<=trie_ptr;p++)trie_ref[p]= 0;
for(p= 0;p<=255;p++)trie_min[p]= p+1;
trie_link(0)= 1;trie_max= 0

/*:951*/
#line 19463 "texprof.w"
;
if(trie_root!=0)
{first_fit(trie_root);trie_pack(trie_root);
}
if(hyph_root!=0)/*1527:*/
#line 28070 "texprof.w"

{if(trie_root==0)for(p= 0;p<=255;p++)trie_min[p]= p+2;
first_fit(hyph_root);trie_pack(hyph_root);
hyph_start= trie_ref[hyph_root];
}

/*:1527*/
#line 19467 "texprof.w"
;
/*957:*/
#line 19306 "texprof.w"

h.rh= 0;h.b0= min_quarterword;h.b1= min_quarterword;

if(trie_max==0)
{for(r= 0;r<=256;r++)trie[r]= h;
trie_max= 256;
}
else{if(hyph_root> 0)trie_fix(hyph_root);
if(trie_root> 0)trie_fix(trie_root);
r= 0;
do{s= trie_link(r);trie[r]= h;r= s;
}while(!(r> trie_max));
}
trie_char(0)= qi('?');

/*:957*/
#line 19468 "texprof.w"
;
trie_not_ready= false;
/*1768:*/
#line 31409 "texprof.w"

if(profile_on)
{/*1761:*/
#line 31310 "texprof.w"

if(profile_on)
{if(st_count+3> MAX_STAMPS)
overflow("profile data",MAX_STAMPS);
/*1779:*/
#line 31656 "texprof.w"

if(last_depth> prof_depth)
{if(last_depth==prof_depth+1)
prof_cmd= prof_cmd|POP_BIT;
else
stamp[st_count++]= (system_macro_pop<<24)|(last_depth-prof_depth);
#if SHOW_RECORD_TIMING
print_char('{');print_int(cmd_count);
print_char(':');print_int(system_macro_pop);
print_char(':');print_int(last_depth);
print_char('>');print_int(prof_depth);
print_char('}');print_ln();
#endif
#line 31669 "texprof.w"
 cmd_count++;
last_depth= unchanged_depth= prof_depth;
}


/*:1779*/
#line 31314 "texprof.w"

stamp[st_count++]= (prof_cmd<<24)|prof_file_line;
prof_cmd= prof_cmd&~POP_BIT;
#if SHOW_RECORD_TIMING
print_char('<');print_int(cmd_count);
print_char(':');
if(prof_cmd&POP_BIT)print_char('-');
print_int(prof_cmd&~POP_BIT);
print_char(':');print_int(prof_depth);
print_char('>');print_ln();
#endif
#line 31325 "texprof.w"
 cmd_count++;
/*1756:*/
#line 31198 "texprof.w"

#if GETTIME==0
time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#elif GETTIME==1
#line 31202 "texprof.w"
 time_error= clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&ts);
#elif GETTIME==2
#line 31204 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
#elif GETTIME==3
#line 31206 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC,&ts);
#else
#line 31208 "texprof.w"
 time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#endif
#line 31210 "texprof.w"

/*:1756*/
#line 31326 "texprof.w"

/*1757:*/
#line 31215 "texprof.w"

diff_nsec= (ts.tv_sec-start_sec)*1000000000+(ts.tv_nsec-start_nsec);
#if 0
printf("time: %ld %ld %ld\n",diff_nsec,(ts.tv_sec),(ts.tv_nsec));
#endif
#line 31220 "texprof.w"

start_nsec= ts.tv_nsec;
start_sec= ts.tv_sec;

/*:1757*/
#line 31327 "texprof.w"

stamp[st_count++]= diff_nsec;
}


/*:1761*/
#line 31411 "texprof.w"

prof_file_line= tmp_file_line;
prof_cmd= tmp_cmd;
prof_depth= tmp_depth;
}



/*:1768*/
#line 19470 "texprof.w"

}

/*:965*/
#line 18984 "texprof.w"

#endif
#line 18986 "texprof.w"

/*:941*/
#line 16603 "texprof.w"

static void line_break(int final_widow_penalty)
{
/*861:*/
#line 17549 "texprof.w"

bool auto_breaking;
pointer prev_p;
pointer q,r,s,prev_s;
internal_font_number f;

/*:861*//*892:*/
#line 18129 "texprof.w"

small_number j;
int c;

/*:892*/
#line 16606 "texprof.w"

/*1766:*/
#line 31393 "texprof.w"

int tmp_cmd;
int tmp_file_line;
int tmp_depth;

/*:1766*/
#line 16607 "texprof.w"

/*1767:*/
#line 31398 "texprof.w"

if(profile_on)
{/*1761:*/
#line 31310 "texprof.w"

if(profile_on)
{if(st_count+3> MAX_STAMPS)
overflow("profile data",MAX_STAMPS);
/*1779:*/
#line 31656 "texprof.w"

if(last_depth> prof_depth)
{if(last_depth==prof_depth+1)
prof_cmd= prof_cmd|POP_BIT;
else
stamp[st_count++]= (system_macro_pop<<24)|(last_depth-prof_depth);
#if SHOW_RECORD_TIMING
print_char('{');print_int(cmd_count);
print_char(':');print_int(system_macro_pop);
print_char(':');print_int(last_depth);
print_char('>');print_int(prof_depth);
print_char('}');print_ln();
#endif
#line 31669 "texprof.w"
 cmd_count++;
last_depth= unchanged_depth= prof_depth;
}


/*:1779*/
#line 31314 "texprof.w"

stamp[st_count++]= (prof_cmd<<24)|prof_file_line;
prof_cmd= prof_cmd&~POP_BIT;
#if SHOW_RECORD_TIMING
print_char('<');print_int(cmd_count);
print_char(':');
if(prof_cmd&POP_BIT)print_char('-');
print_int(prof_cmd&~POP_BIT);
print_char(':');print_int(prof_depth);
print_char('>');print_ln();
#endif
#line 31325 "texprof.w"
 cmd_count++;
/*1756:*/
#line 31198 "texprof.w"

#if GETTIME==0
time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#elif GETTIME==1
#line 31202 "texprof.w"
 time_error= clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&ts);
#elif GETTIME==2
#line 31204 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
#elif GETTIME==3
#line 31206 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC,&ts);
#else
#line 31208 "texprof.w"
 time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#endif
#line 31210 "texprof.w"

/*:1756*/
#line 31326 "texprof.w"

/*1757:*/
#line 31215 "texprof.w"

diff_nsec= (ts.tv_sec-start_sec)*1000000000+(ts.tv_nsec-start_nsec);
#if 0
printf("time: %ld %ld %ld\n",diff_nsec,(ts.tv_sec),(ts.tv_nsec));
#endif
#line 31220 "texprof.w"

start_nsec= ts.tv_nsec;
start_sec= ts.tv_sec;

/*:1757*/
#line 31327 "texprof.w"

stamp[st_count++]= diff_nsec;
}


/*:1761*/
#line 31400 "texprof.w"

tmp_file_line= prof_file_line;
tmp_cmd= prof_cmd;
tmp_depth= prof_depth;
prof_file_line= FILE_LINE(system_file,system_line_break);
prof_cmd= system_cmd;
}


/*:1767*/
#line 16608 "texprof.w"

pack_begin_line= mode_line;
/*815:*/
#line 16632 "texprof.w"

link(temp_head)= link(head);
if(is_char_node(tail))tail_append(new_penalty(inf_penalty))
else if(type(tail)!=glue_node)tail_append(new_penalty(inf_penalty))
else{type(tail)= penalty_node;delete_glue_ref(glue_ptr(tail));
flush_node_list(leader_ptr(tail));penalty(tail)= inf_penalty;
}
link(tail)= new_param_glue(par_fill_skip_code);
init_cur_lang= prev_graf%0200000;
init_l_hyf= prev_graf/020000000;
init_r_hyf= (prev_graf/0200000)%0100;
pop_nest();

/*:815*//*826:*/
#line 16869 "texprof.w"

no_shrink_error_yet= true;
check_shrinkage(left_skip);check_shrinkage(right_skip);
q= left_skip;r= right_skip;background[1]= width(q)+width(r);
background[2]= 0;background[3]= 0;background[4]= 0;background[5]= 0;
background[2+stretch_order(q)]= stretch(q);
background[2+stretch_order(r)]= background[2+stretch_order(r)]+stretch(r);
background[6]= shrink(q)+shrink(r);

/*:826*//*833:*/
#line 17014 "texprof.w"

minimum_demerits= awful_bad;
minimal_demerits[tight_fit]= awful_bad;
minimal_demerits[decent_fit]= awful_bad;
minimal_demerits[loose_fit]= awful_bad;
minimal_demerits[very_loose_fit]= awful_bad;

/*:833*//*847:*/
#line 17277 "texprof.w"

if(par_shape_ptr==null)
if(hang_indent==0)
{last_special_line= 0;second_width= hsize;
second_indent= 0;
}
else/*848:*/
#line 17291 "texprof.w"

{last_special_line= abs(hang_after);
if(hang_after<0)
{first_width= hsize-abs(hang_indent);
if(hang_indent>=0)first_indent= hang_indent;
else first_indent= 0;
second_width= hsize;second_indent= 0;
}
else{first_width= hsize;first_indent= 0;
second_width= hsize-abs(hang_indent);
if(hang_indent>=0)second_indent= hang_indent;
else second_indent= 0;
}
}

/*:848*/
#line 17283 "texprof.w"

else{last_special_line= info(par_shape_ptr)-1;
second_width= mem[par_shape_ptr+2*(last_special_line+1)].sc;
second_indent= mem[par_shape_ptr+2*last_special_line+1].sc;
}
if(looseness==0)easy_line= last_special_line;
else easy_line= max_halfword

/*:847*/
#line 16610 "texprof.w"
;
/*862:*/
#line 17559 "texprof.w"

threshold= pretolerance;
if(threshold>=0)
{
#ifdef STAT
if(tracing_paragraphs> 0)
{begin_diagnostic();print_nl("@firstpass");}
#endif
#line 17567 "texprof.w"

second_pass= false;final_pass= false;
}
else{threshold= tolerance;second_pass= true;
final_pass= (emergency_stretch<=0);
#ifdef STAT
if(tracing_paragraphs> 0)begin_diagnostic();
#endif
#line 17575 "texprof.w"

}
loop{if(threshold> inf_bad)threshold= inf_bad;
if(second_pass)/*890:*/
#line 18100 "texprof.w"

{
#ifdef INIT
if(trie_not_ready)init_trie();
#endif
#line 18105 "texprof.w"

cur_lang= init_cur_lang;l_hyf= init_l_hyf;r_hyf= init_r_hyf;
set_hyph_index;
}

/*:890*/
#line 17578 "texprof.w"
;
/*863:*/
#line 17617 "texprof.w"

q= get_node(active_node_size);
type(q)= unhyphenated;fitness(q)= decent_fit;
link(q)= last_active;break_node(q)= null;
line_number(q)= prev_graf+1;total_demerits(q)= 0;link(active)= q;
do_all_six(store_background);
passive= null;printed_node= temp_head;pass_number= 0;
font_in_short_display= null_font

/*:863*/
#line 17579 "texprof.w"
;
cur_p= link(temp_head);auto_breaking= true;
prev_p= cur_p;
while((cur_p!=null)&&(link(active)!=last_active))
/*865:*/
#line 17653 "texprof.w"

{if(is_char_node(cur_p))
/*866:*/
#line 17689 "texprof.w"

{prev_p= cur_p;
do{f= font(cur_p);
act_width= act_width+char_width(f,char_info(f,character(cur_p)));
cur_p= link(cur_p);
}while(!(!is_char_node(cur_p)));
}

/*:866*/
#line 17655 "texprof.w"
;
switch(type(cur_p)){
case hlist_node:case vlist_node:case rule_node:act_width= act_width+width(cur_p);break;
case whatsit_node:/*1361:*/
#line 25648 "texprof.w"

adv_past(cur_p)

/*:1361*/
#line 17659 "texprof.w"
break;
case glue_node:{/*867:*/
#line 17700 "texprof.w"

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

/*:867*/
#line 17661 "texprof.w"
;
if(second_pass&&auto_breaking)
/*893:*/
#line 18136 "texprof.w"

{prev_s= cur_p;s= link(prev_s);
if(s!=null)
{/*895:*/
#line 18162 "texprof.w"

loop{if(is_char_node(s))
{c= qo(character(s));hf= font(s);
}
else if(type(s)==ligature_node)
if(lig_ptr(s)==null)goto resume;
else{q= lig_ptr(s);c= qo(character(q));hf= font(q);
}
else if((type(s)==kern_node)&&(subtype(s)==normal))goto resume;
else if(type(s)==whatsit_node)
{/*1362:*/
#line 25651 "texprof.w"

adv_past(s)

/*:1362*/
#line 18172 "texprof.w"
;
goto resume;
}
else goto done1;
set_lc_code(c);
if(hc[0]!=0)
if((hc[0]==c)||(uc_hyph> 0))goto done2;
else goto done1;
resume:prev_s= s;s= link(prev_s);
}
done2:hyf_char= hyphen_char[hf];
if(hyf_char<0)goto done1;
if(hyf_char> 255)goto done1;
ha= prev_s

/*:895*/
#line 18139 "texprof.w"
;
if(l_hyf+r_hyf> 63)goto done1;
/*896:*/
#line 18189 "texprof.w"

hn= 0;
loop{if(is_char_node(s))
{if(font(s)!=hf)goto done3;
hyf_bchar= character(s);c= qo(hyf_bchar);
set_lc_code(c);
if(hc[0]==0)goto done3;
if(hn==63)goto done3;
hb= s;incr(hn);hu[hn]= c;hc[hn]= hc[0];hyf_bchar= non_char;
}
else if(type(s)==ligature_node)
/*897:*/
#line 18216 "texprof.w"

{if(font(lig_char(s))!=hf)goto done3;
j= hn;q= lig_ptr(s);if(q> null)hyf_bchar= character(q);
while(q> null)
{c= qo(character(q));
set_lc_code(c);
if(hc[0]==0)goto done3;
if(j==63)goto done3;
incr(j);hu[j]= c;hc[j]= hc[0];
q= link(q);
}
hb= s;hn= j;
if(odd(subtype(s)))hyf_bchar= font_bchar[hf];else hyf_bchar= non_char;
}

/*:897*/
#line 18201 "texprof.w"

else if((type(s)==kern_node)&&(subtype(s)==normal))
{hb= s;
hyf_bchar= font_bchar[hf];
}
else goto done3;
s= link(s);
}
done3:

/*:896*/
#line 18141 "texprof.w"
;
/*898:*/
#line 18231 "texprof.w"

if(hn<l_hyf+r_hyf)goto done1;
loop{if(!(is_char_node(s)))
switch(type(s)){
case ligature_node:do_nothing;break;
case kern_node:if(subtype(s)!=normal)goto done4;break;
case whatsit_node:case glue_node:
case penalty_node:case ins_node:case adjust_node:
case mark_node:
goto done4;
default:goto done1;
}
s= link(s);
}
done4:

/*:898*/
#line 18143 "texprof.w"
;
hyphenate();
}
done1:;}

/*:893*/
#line 17663 "texprof.w"
;
}break;
case kern_node:if(subtype(cur_p)==explicit)kern_break
else act_width= act_width+width(cur_p);break;
case ligature_node:{f= font(lig_char(cur_p));
act_width= act_width+char_width(f,char_info(f,character(lig_char(cur_p))));
}break;
case disc_node:/*868:*/
#line 17716 "texprof.w"

{s= pre_break(cur_p);disc_width= 0;
if(s==null)try_break(ex_hyphen_penalty,hyphenated);
else{do{/*869:*/
#line 17734 "texprof.w"

if(is_char_node(s))
{f= font(s);
disc_width= disc_width+char_width(f,char_info(f,character(s)));
}
else switch(type(s)){
case ligature_node:{f= font(lig_char(s));
disc_width= disc_width+
char_width(f,char_info(f,character(lig_char(s))));
}break;
case hlist_node:case vlist_node:case rule_node:
case kern_node:
disc_width= disc_width+width(s);break;
default:confusion("disc3");

}

/*:869*/
#line 17719 "texprof.w"
;
s= link(s);
}while(!(s==null));
act_width= act_width+disc_width;
try_break(hyphen_penalty,hyphenated);
act_width= act_width-disc_width;
}
r= replace_count(cur_p);s= link(cur_p);
while(r> 0)
{/*870:*/
#line 17751 "texprof.w"

if(is_char_node(s))
{f= font(s);
act_width= act_width+char_width(f,char_info(f,character(s)));
}
else switch(type(s)){
case ligature_node:{f= font(lig_char(s));
act_width= act_width+
char_width(f,char_info(f,character(lig_char(s))));
}break;
case hlist_node:case vlist_node:case rule_node:
case kern_node:
act_width= act_width+width(s);break;
default:confusion("disc4");

}

/*:870*/
#line 17728 "texprof.w"
;
decr(r);s= link(s);
}
prev_p= cur_p;cur_p= s;goto done5;
}

/*:868*/
#line 17671 "texprof.w"

case math_node:{auto_breaking= (subtype(cur_p)==after);kern_break;
}break;
case penalty_node:try_break(penalty(cur_p),unhyphenated);break;
case mark_node:case ins_node:case adjust_node:do_nothing;break;
default:confusion("paragraph");

}
prev_p= cur_p;cur_p= link(cur_p);
done5:;}

/*:865*/
#line 17585 "texprof.w"
;
if(cur_p==null)
/*872:*/
#line 17787 "texprof.w"

{try_break(eject_penalty,hyphenated);
if(link(active)!=last_active)
{/*873:*/
#line 17797 "texprof.w"

r= link(active);fewest_demerits= awful_bad;
do{if(type(r)!=delta_node)if(total_demerits(r)<fewest_demerits)
{fewest_demerits= total_demerits(r);best_bet= r;
}
r= link(r);
}while(!(r==last_active));
best_line= line_number(best_bet)

/*:873*/
#line 17790 "texprof.w"
;
if(looseness==0)goto done;
/*874:*/
#line 17811 "texprof.w"

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

/*:874*/
#line 17792 "texprof.w"
;
if((actual_looseness==looseness)||final_pass)goto done;
}
}

/*:872*/
#line 17588 "texprof.w"
;
/*864:*/
#line 17626 "texprof.w"

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

/*:864*/
#line 17589 "texprof.w"
;
if(!second_pass)
{
#ifdef STAT
if(tracing_paragraphs> 0)print_nl("@secondpass");
#endif
#line 17595 "texprof.w"
 threshold= tolerance;second_pass= true;final_pass= (emergency_stretch<=0);
}
else{
#ifdef STAT
if(tracing_paragraphs> 0)
print_nl("@emergencypass");
#endif
#line 17602 "texprof.w"
 background[2]= background[2]+emergency_stretch;final_pass= true;
}
}
done:
#ifdef STAT
if(tracing_paragraphs> 0)
{end_diagnostic(true);normalize_selector();
}
#endif
#line 17611 "texprof.w"

/*:862*/
#line 16611 "texprof.w"
;
/*875:*/
#line 17835 "texprof.w"

post_line_break(final_widow_penalty)

/*:875*/
#line 16613 "texprof.w"
;
/*864:*/
#line 17626 "texprof.w"

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

/*:864*/
#line 16614 "texprof.w"
;
pack_begin_line= 0;
/*1768:*/
#line 31409 "texprof.w"

if(profile_on)
{/*1761:*/
#line 31310 "texprof.w"

if(profile_on)
{if(st_count+3> MAX_STAMPS)
overflow("profile data",MAX_STAMPS);
/*1779:*/
#line 31656 "texprof.w"

if(last_depth> prof_depth)
{if(last_depth==prof_depth+1)
prof_cmd= prof_cmd|POP_BIT;
else
stamp[st_count++]= (system_macro_pop<<24)|(last_depth-prof_depth);
#if SHOW_RECORD_TIMING
print_char('{');print_int(cmd_count);
print_char(':');print_int(system_macro_pop);
print_char(':');print_int(last_depth);
print_char('>');print_int(prof_depth);
print_char('}');print_ln();
#endif
#line 31669 "texprof.w"
 cmd_count++;
last_depth= unchanged_depth= prof_depth;
}


/*:1779*/
#line 31314 "texprof.w"

stamp[st_count++]= (prof_cmd<<24)|prof_file_line;
prof_cmd= prof_cmd&~POP_BIT;
#if SHOW_RECORD_TIMING
print_char('<');print_int(cmd_count);
print_char(':');
if(prof_cmd&POP_BIT)print_char('-');
print_int(prof_cmd&~POP_BIT);
print_char(':');print_int(prof_depth);
print_char('>');print_ln();
#endif
#line 31325 "texprof.w"
 cmd_count++;
/*1756:*/
#line 31198 "texprof.w"

#if GETTIME==0
time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#elif GETTIME==1
#line 31202 "texprof.w"
 time_error= clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&ts);
#elif GETTIME==2
#line 31204 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
#elif GETTIME==3
#line 31206 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC,&ts);
#else
#line 31208 "texprof.w"
 time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#endif
#line 31210 "texprof.w"

/*:1756*/
#line 31326 "texprof.w"

/*1757:*/
#line 31215 "texprof.w"

diff_nsec= (ts.tv_sec-start_sec)*1000000000+(ts.tv_nsec-start_nsec);
#if 0
printf("time: %ld %ld %ld\n",diff_nsec,(ts.tv_sec),(ts.tv_nsec));
#endif
#line 31220 "texprof.w"

start_nsec= ts.tv_nsec;
start_sec= ts.tv_sec;

/*:1757*/
#line 31327 "texprof.w"

stamp[st_count++]= diff_nsec;
}


/*:1761*/
#line 31411 "texprof.w"

prof_file_line= tmp_file_line;
prof_cmd= tmp_cmd;
prof_depth= tmp_depth;
}



/*:1768*/
#line 16616 "texprof.w"

}

/*1386:*/
#line 25932 "texprof.w"

static bool eTeX_enabled(bool b,quarterword j,halfword k)
{if(!b)
{print_err("Improper ");print_cmd_chr(j,k);
help1("Sorry, this optional e-TeX feature has been disabled.");error();
}
return b;
}

/*:1386*//*1409:*/
#line 26199 "texprof.w"

static void show_save_groups(void)
{
int p;
int m;
save_pointer v;
quarterword l;
group_code c;
int a;
int i;
quarterword j;
char*s;
p= nest_ptr;nest[p]= cur_list;
v= save_ptr;l= cur_level;c= cur_group;
save_ptr= cur_boundary;decr(cur_level);
a= 1;
print_nl("");print_ln();
loop{print_nl("### ");print_group(true);
if(cur_group==bottom_level)goto done;
do{m= nest[p].mode_field;
if(p> 0)decr(p);else m= vmode;
}while(!(m!=hmode));
print(" (");
switch(cur_group){
case simple_group:{incr(p);goto found2;
}
case hbox_group:case adjusted_hbox_group:s= "hbox";break;
case vbox_group:s= "vbox";break;
case vtop_group:s= "vtop";break;
case align_group:if(a==0)
{if(m==-vmode)s= "halign";else s= "valign";
a= 1;goto found1;
}
else{if(a==1)print("align entry");else print_esc("cr");
if(p>=a)p= p-a;
a= 0;goto found;
}break;
case no_align_group:
{incr(p);a= -1;print_esc("noalign");goto found2;
}
case output_group:
{print_esc("output");goto found;
}
case math_group:goto found2;
case disc_group:case math_choice_group:
{if(cur_group==disc_group)print_esc("discretionary");
else print_esc("mathchoice");
for(i= 1;i<=3;i++)if(i<=saved(-2))print("{}");
goto found2;
}
case insert_group:
{if(saved(-2)==255)print_esc("vadjust");
else{print_esc("insert");print_int(saved(-2));
}
goto found2;
}
case vcenter_group:{s= "vcenter";goto found1;
}
case semi_simple_group:{incr(p);print_esc("begingroup");goto found;
}
case math_shift_group:
{if(m==mmode)print_char('$');
else if(nest[p].mode_field==mmode)
{print_cmd_chr(eq_no,saved(-2));goto found;
}
print_char('$');goto found;
}
case math_left_group:
{if(type(nest[p+1].eTeX_aux_field)==left_noad)print_esc("left");
else print_esc("middle");
goto found;
}
}
/*1411:*/
#line 26288 "texprof.w"

i= saved(-4);
if(i!=0)
if(i<box_flag)
{if(abs(nest[p].mode_field)==vmode)j= hmove;else j= vmove;
if(i> 0)print_cmd_chr(j,0);else print_cmd_chr(j,1);
print_scaled(abs(i));print("pt");
}
else if(i<ship_out_flag)
{if(i>=global_box_flag)
{print_esc("global");i= i-(global_box_flag-box_flag);
}
print_esc("setbox");print_int(i-box_flag);print_char('=');
}
else print_cmd_chr(leader_ship,i-(leader_flag-a_leaders))

/*:1411*/
#line 26272 "texprof.w"
;
found1:print_esc(s);/*1410:*/
#line 26281 "texprof.w"

if(saved(-2)!=0)
{print_char(' ');
if(saved(-3)==exactly)print("to");else print("spread");
print_scaled(saved(-2));print("pt");
}

/*:1410*/
#line 26273 "texprof.w"
;
found2:print_char('{');
found:print_char(')');decr(cur_level);
cur_group= save_level(save_ptr);save_ptr= save_index(save_ptr);
}
done:save_ptr= v;cur_level= l;cur_group= c;
}

/*:1409*//*1425:*/
#line 26429 "texprof.w"

static void new_interaction(void);

/*:1425*/
#line 16619 "texprof.w"


/*:814*//*933:*/
#line 18864 "texprof.w"
static void new_hyph_exceptions(void)
{
int n;
int j;
hyph_pointer h;
str_number k;
pointer p;
pointer q;
str_number s,t;
pool_pointer u,v;
scan_left_brace();
set_cur_lang;
#ifdef INIT
if(trie_not_ready)
{hyph_index= 0;goto not_found1;
}
#endif
#line 18881 "texprof.w"
 set_hyph_index;
not_found1:
/*934:*/
#line 18887 "texprof.w"

n= 0;p= null;
loop{get_x_token();
reswitch:switch(cur_cmd){
case letter:case other_char:case char_given:/*936:*/
#line 18913 "texprof.w"

if(cur_chr=='-')/*937:*/
#line 18928 "texprof.w"

{if(n<63)
{q= get_avail();link(q)= p;info(q)= n;p= q;
}
}

/*:937*/
#line 18914 "texprof.w"

else{set_lc_code(cur_chr);
if(hc[0]==0)
{print_err("Not a letter");

help2("Letters in \\hyphenation words must have \\lccode>0.",
"Proceed; I'll ignore the character I just read.");
error();
}
else if(n<63)
{incr(n);hc[n]= hc[0];
}
}

/*:936*/
#line 18892 "texprof.w"
break;
case char_num:{scan_char_num();cur_chr= cur_val;cur_cmd= char_given;
goto reswitch;
}
case spacer:case right_brace:{if(n> 1)/*938:*/
#line 18934 "texprof.w"

{incr(n);hc[n]= cur_lang;str_room(n);h= 0;
for(j= 1;j<=n;j++)
{h= (h+h+hc[j])%hyph_size;
append_char(hc[j]);
}
s= make_string();
/*939:*/
#line 18944 "texprof.w"

if(hyph_count==hyph_size)overflow("exception dictionary",hyph_size);

incr(hyph_count);
while(hyph_word[h]!=0)
{/*940:*/
#line 18955 "texprof.w"

k= hyph_word[h];
if(length(k)<length(s))goto found;
if(length(k)> length(s))goto not_found;
u= str_start[k];v= str_start[s];
do{if(str_pool[u]<str_pool[v])goto found;
if(str_pool[u]> str_pool[v])goto not_found;
incr(u);incr(v);
}while(!(u==str_start[k+1]));
found:q= hyph_list[h];hyph_list[h]= p;p= q;
t= hyph_word[h];hyph_word[h]= s;s= t;
not_found:

/*:940*/
#line 18950 "texprof.w"
;
if(h> 0)decr(h);else h= hyph_size;
}
hyph_word[h]= s;hyph_list[h]= p

/*:939*/
#line 18941 "texprof.w"
;
}

/*:938*/
#line 18896 "texprof.w"
;
if(cur_cmd==right_brace)return;
n= 0;p= null;
}break;
default:/*935:*/
#line 18904 "texprof.w"

{print_err("Improper ");print_esc("hyphenation");

print(" will be flushed");
help2("Hyphenation exceptions must contain only letters",
"and hyphens. But continue; I'll forgive and forget.");
error();
}

/*:935*/
#line 18900 "texprof.w"

}
}

/*:934*/
#line 18884 "texprof.w"
;
}

/*:933*//*967:*/
#line 19495 "texprof.w"
static pointer prune_page_top(pointer p,bool s)

{pointer prev_p;
pointer q,r;
prev_p= temp_head;link(temp_head)= p;
while(p!=null)
switch(type(p)){
case hlist_node:case vlist_node:case rule_node:/*968:*/
#line 19520 "texprof.w"

{q= new_skip_param(split_top_skip_code);link(prev_p)= q;link(q)= p;

if(width(temp_ptr)> height(p))width(temp_ptr)= width(temp_ptr)-height(p);
else width(temp_ptr)= 0;
p= null;
}

/*:968*/
#line 19503 "texprof.w"
break;
case whatsit_node:case mark_node:case ins_node:{prev_p= p;p= link(prev_p);
}break;
case glue_node:case kern_node:case penalty_node:{q= p;p= link(q);link(q)= null;
link(prev_p)= p;
if(s)
{if(split_disc==null)split_disc= q;else link(r)= q;
r= q;
}
else flush_node_list(q);
}break;
default:confusion("pruning");

}
return link(temp_head);
}

/*:967*//*969:*/
#line 19544 "texprof.w"
static pointer vert_break(pointer p,scaled h,scaled d)

{
pointer prev_p;

pointer q,r;
int pi;
int b;
int least_cost;
pointer best_place;
scaled prev_dp;
small_number t;
prev_p= p;
least_cost= awful_bad;do_all_six(set_height_zero);prev_dp= 0;
loop{/*971:*/
#line 19578 "texprof.w"

if(p==null)pi= eject_penalty;
else/*972:*/
#line 19593 "texprof.w"

switch(type(p)){
case hlist_node:case vlist_node:case rule_node:{
cur_height= cur_height+prev_dp+height(p);prev_dp= depth(p);
goto not_found;
}
case whatsit_node:/*1364:*/
#line 25657 "texprof.w"

goto not_found

/*:1364*/
#line 19599 "texprof.w"
;
case glue_node:if(precedes_break(prev_p))pi= 0;
else goto update_heights;break;
case kern_node:{if(link(p)==null)t= penalty_node;
else t= type(link(p));
if(t==glue_node)pi= 0;else goto update_heights;
}break;
case penalty_node:pi= penalty(p);break;
case mark_node:case ins_node:goto not_found;
default:confusion("vertbreak");

}

/*:972*/
#line 19582 "texprof.w"
;
/*973:*/
#line 19614 "texprof.w"

if(pi<inf_penalty)
{/*974:*/
#line 19628 "texprof.w"

if(cur_height<h)
if((active_height[3]!=0)||(active_height[4]!=0)||
(active_height[5]!=0))b= 0;
else b= badness(h-cur_height,active_height[2]);
else if(cur_height-h> active_height[6])b= awful_bad;
else b= badness(cur_height-h,active_height[6])

/*:974*/
#line 19616 "texprof.w"
;
if(b<awful_bad)
if(pi<=eject_penalty)b= pi;
else if(b<inf_bad)b= b+pi;
else b= deplorable;
if(b<=least_cost)
{best_place= p;least_cost= b;
best_height_plus_depth= cur_height+prev_dp;
}
if((b==awful_bad)||(pi<=eject_penalty))goto done;
}

/*:973*/
#line 19584 "texprof.w"
;
if((type(p)<glue_node)||(type(p)> kern_node))goto not_found;
update_heights:/*975:*/
#line 19640 "texprof.w"

if(type(p)==kern_node)q= p;
else{q= glue_ptr(p);
active_height[2+stretch_order(q)]= 
active_height[2+stretch_order(q)]+stretch(q);
active_height[6]= active_height[6]+shrink(q);
if((shrink_order(q)!=normal)&&(shrink(q)!=0))
{
print_err("Infinite glue shrinkage found in box being split");

help4("The box you are \\vsplitting contains some infinitely",
"shrinkable glue, e.g., `\\vss' or `\\vskip 0pt minus 1fil'.",
"Such glue doesn't belong there; but you can safely proceed,",
"since the offensive shrinkability has been made finite.");
error();r= new_spec(q);shrink_order(r)= normal;delete_glue_ref(q);
glue_ptr(p)= r;q= r;
}
}
cur_height= cur_height+prev_dp+width(q);prev_dp= 0

/*:975*/
#line 19587 "texprof.w"
;
not_found:if(prev_dp> d)
{cur_height= cur_height+prev_dp-d;
prev_dp= d;
}

/*:971*/
#line 19560 "texprof.w"
;
prev_p= p;p= link(prev_p);
}
done:return best_place;
}

/*:969*//*976:*/
#line 19675 "texprof.w"
/*1507:*/
#line 27706 "texprof.w"

static bool do_marks(small_number a,small_number l,pointer q)
{int i;
if(l<4)
{for(i= 0;i<=15;i++)
{get_sa_ptr;
if(cur_ptr!=null)if(do_marks(a,l+1,cur_ptr))delete_sa_ptr;
}
if(sa_used(q)==0)
{free_node(q,index_node_size);q= null;
}
}
else
{switch(a){
/*1508:*/
#line 27732 "texprof.w"

case vsplit_init:if(sa_split_first_mark(q)!=null)
{delete_token_ref(sa_split_first_mark(q));sa_split_first_mark(q)= null;
delete_token_ref(sa_split_bot_mark(q));sa_split_bot_mark(q)= null;
}break;

/*:1508*//*1510:*/
#line 27759 "texprof.w"

case fire_up_init:if(sa_bot_mark(q)!=null)
{if(sa_top_mark(q)!=null)delete_token_ref(sa_top_mark(q));
delete_token_ref(sa_first_mark(q));sa_first_mark(q)= null;
if(link(sa_bot_mark(q))==null)
{delete_token_ref(sa_bot_mark(q));sa_bot_mark(q)= null;
}
else add_token_ref(sa_bot_mark(q));
sa_top_mark(q)= sa_bot_mark(q);
}break;

/*:1510*//*1511:*/
#line 27770 "texprof.w"

case fire_up_done:if((sa_top_mark(q)!=null)&&(sa_first_mark(q)==null))
{sa_first_mark(q)= sa_top_mark(q);add_token_ref(sa_top_mark(q));
}break;

/*:1511*//*1513:*/
#line 27793 "texprof.w"

#ifdef INIT
case destroy_marks:for(i= top_mark_code;i<=split_bot_mark_code;i++)
{get_sa_ptr;
if(cur_ptr!=null)
{delete_token_ref(cur_ptr);put_sa_ptr(null);
}
}
#endif
#line 27802 "texprof.w"

/*:1513*/
#line 27720 "texprof.w"

}
if(sa_bot_mark(q)==null)if(sa_split_bot_mark(q)==null)
{free_node(q,mark_class_node_size);q= null;
}
}
return(q==null);
}

/*:1507*/
#line 19675 "texprof.w"

static pointer vsplit(halfword n,scaled h)

{
pointer v;
pointer p;
pointer q;
cur_val= n;fetch_box(v);
flush_node_list(split_disc);split_disc= null;
if(sa_mark!=null)
if(do_marks(vsplit_init,0,sa_mark))sa_mark= null;
if(split_first_mark!=null)
{delete_token_ref(split_first_mark);split_first_mark= null;
delete_token_ref(split_bot_mark);split_bot_mark= null;
}
/*977:*/
#line 19701 "texprof.w"

if(v==null)
{return null;
}
if(type(v)!=vlist_node)
{print_err("");print_esc("vsplit");print(" needs a ");
print_esc("vbox");

help2("The box you are trying to split is an \\hbox.",
"I can't split such a box, so I'll leave it alone.");
error();return null;
}

/*:977*/
#line 19690 "texprof.w"
;
q= vert_break(list_ptr(v),h,split_max_depth);
/*978:*/
#line 19717 "texprof.w"

p= list_ptr(v);
if(p==q)list_ptr(v)= null;
else loop{if(type(p)==mark_node)
if(mark_class(p)!=0)/*1509:*/
#line 27741 "texprof.w"

{find_sa_element(mark_val,mark_class(p),true);
if(sa_split_first_mark(cur_ptr)==null)
{sa_split_first_mark(cur_ptr)= mark_ptr(p);
add_token_ref(mark_ptr(p));
}
else delete_token_ref(sa_split_bot_mark(cur_ptr));
sa_split_bot_mark(cur_ptr)= mark_ptr(p);
add_token_ref(mark_ptr(p));
}

/*:1509*/
#line 19721 "texprof.w"

else if(split_first_mark==null)
{split_first_mark= mark_ptr(p);
split_bot_mark= split_first_mark;
token_ref_count(split_first_mark)= 
token_ref_count(split_first_mark)+2;
}
else{delete_token_ref(split_bot_mark);
split_bot_mark= mark_ptr(p);
add_token_ref(split_bot_mark);
}
if(link(p)==q)
{link(p)= null;goto done;
}
p= link(p);
}
done:

/*:978*/
#line 19693 "texprof.w"
;
q= prune_page_top(q,saving_vdiscards> 0);
p= list_ptr(v);free_node(v,box_node_size);
if(q!=null)q= vpack(q,natural);
change_box(q);
return vpackage(p,h,exactly,split_max_depth);
}

/*:976*//*984:*/
#line 19908 "texprof.w"
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

/*:984*//*986:*/
#line 19954 "texprof.w"
static void freeze_page_specs(small_number s)
{page_contents= s;
page_goal= vsize;page_max_depth= max_depth;
page_depth= 0;do_all_six(set_page_so_far_zero);
least_page_cost= awful_bad;
#ifdef STAT
if(tracing_pages> 0)
{begin_diagnostic();
print_nl("%% goal height=");print_scaled(page_goal);

print(", max depth=");print_scaled(page_max_depth);
end_diagnostic(false);
}
#endif
#line 19968 "texprof.w"

}

/*:986*//*991:*/
#line 20022 "texprof.w"
static void box_error(eight_bits n)
{error();begin_diagnostic();
print_nl("The following box has been deleted:");

show_box(box(n));end_diagnostic(true);
flush_node_list(box(n));box(n)= null;
}

/*:991*//*992:*/
#line 20033 "texprof.w"
static void ensure_vbox(eight_bits n)
{pointer p;
p= box(n);
if(p!=null)if(type(p)==hlist_node)
{print_err("Insertions can only be added to a vbox");

help3("Tut tut: You're trying to \\insert into a",
"\\box register that now contains an \\hbox.",
"Proceed, and I'll discard its present contents.");
box_error(n);
}
}

/*:992*//*993:*/
#line 20052 "texprof.w"
/*1011:*/
#line 20362 "texprof.w"

static void fire_up(pointer c)
{
pointer p,q,r,s;
pointer prev_p;
int n;
bool wait;
int save_vbadness;
scaled save_vfuzz;
pointer save_split_top_skip;
/*1012:*/
#line 20395 "texprof.w"

if(type(best_page_break)==penalty_node)
{geq_word_define(int_base+output_penalty_code,penalty(best_page_break));
penalty(best_page_break)= inf_penalty;
}
else geq_word_define(int_base+output_penalty_code,inf_penalty)

/*:1012*/
#line 20372 "texprof.w"
;
if(sa_mark!=null)
if(do_marks(fire_up_init,0,sa_mark))sa_mark= null;
if(bot_mark!=null)
{if(top_mark!=null)delete_token_ref(top_mark);
top_mark= bot_mark;add_token_ref(top_mark);
delete_token_ref(first_mark);first_mark= null;
}
/*1013:*/
#line 20407 "texprof.w"

if(c==best_page_break)best_page_break= null;
/*1014:*/
#line 20431 "texprof.w"

if(box(255)!=null)
{print_err("");print_esc("box");print("255 is not void");

help2("You shouldn't use \\box255 except in \\output routines.",
"Proceed, and I'll discard its present contents.");
box_error(255);
}

/*:1014*/
#line 20409 "texprof.w"
;
insert_penalties= 0;
save_split_top_skip= split_top_skip;
if(holding_inserts<=0)
/*1017:*/
#line 20485 "texprof.w"

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

/*:1017*/
#line 20413 "texprof.w"
;
q= hold_head;link(q)= null;prev_p= page_head;p= link(prev_p);
while(p!=best_page_break)
{if(type(p)==ins_node)
{if(holding_inserts<=0)
/*1019:*/
#line 20511 "texprof.w"

{r= link(page_ins_head);
while(subtype(r)!=subtype(p))r= link(r);
if(best_ins_ptr(r)==null)wait= true;
else{wait= false;s= last_ins_ptr(r);link(s)= ins_ptr(p);
if(best_ins_ptr(r)==p)
/*1020:*/
#line 20527 "texprof.w"

{if(type(r)==split_up)
if((broken_ins(r)==p)&&(broken_ptr(r)!=null))
{while(link(s)!=broken_ptr(r))s= link(s);
link(s)= null;
split_top_skip= split_top_ptr(p);
ins_ptr(p)= prune_page_top(broken_ptr(r),false);
if(ins_ptr(p)!=null)
{temp_ptr= vpack(ins_ptr(p),natural);
height(p)= height(temp_ptr)+depth(temp_ptr);
free_node(temp_ptr,box_node_size);wait= true;
}
}
best_ins_ptr(r)= null;
n= qo(subtype(r));
temp_ptr= list_ptr(box(n));
free_node(box(n),box_node_size);
box(n)= vpack(temp_ptr,natural);
}

/*:1020*/
#line 20518 "texprof.w"

else{while(link(s)!=null)s= link(s);
last_ins_ptr(r)= s;
}
}
/*1021:*/
#line 20547 "texprof.w"

link(prev_p)= link(p);link(p)= null;
if(wait)
{link(q)= p;q= p;incr(insert_penalties);
}
else{delete_glue_ref(split_top_ptr(p));
free_node(p,ins_node_size);
}
p= prev_p

/*:1021*/
#line 20524 "texprof.w"
;
}

/*:1019*/
#line 20419 "texprof.w"
;
}
else if(type(p)==mark_node)
if(mark_class(p)!=0)/*1512:*/
#line 27775 "texprof.w"

{find_sa_element(mark_val,mark_class(p),true);
if(sa_first_mark(cur_ptr)==null)
{sa_first_mark(cur_ptr)= mark_ptr(p);
add_token_ref(mark_ptr(p));
}
if(sa_bot_mark(cur_ptr)!=null)delete_token_ref(sa_bot_mark(cur_ptr));
sa_bot_mark(cur_ptr)= mark_ptr(p);add_token_ref(mark_ptr(p));
}

/*:1512*/
#line 20422 "texprof.w"

else/*1015:*/
#line 20440 "texprof.w"

{if(first_mark==null)
{first_mark= mark_ptr(p);
add_token_ref(first_mark);
}
if(bot_mark!=null)delete_token_ref(bot_mark);
bot_mark= mark_ptr(p);add_token_ref(bot_mark);
}

/*:1015*/
#line 20423 "texprof.w"
;
prev_p= p;p= link(prev_p);
}
split_top_skip= save_split_top_skip;
/*1016:*/
#line 20460 "texprof.w"

if(p!=null)
{if(link(contrib_head)==null)
if(nest_ptr==0)tail= page_tail;
else contrib_tail= page_tail;
link(page_tail)= link(contrib_head);
link(contrib_head)= p;
link(prev_p)= null;
}
save_vbadness= vbadness;vbadness= inf_bad;
save_vfuzz= vfuzz;vfuzz= max_dimen;
box(255)= vpackage(link(page_head),best_size,exactly,page_max_depth);
vbadness= save_vbadness;vfuzz= save_vfuzz;
if(last_glue!=max_halfword)delete_glue_ref(last_glue);
/*990:*/
#line 20011 "texprof.w"

page_contents= empty;page_tail= page_head;link(page_head)= null;
last_glue= max_halfword;last_penalty= 0;last_kern= 0;
last_node_type= -1;
page_depth= 0;page_max_depth= 0

/*:990*/
#line 20474 "texprof.w"
;
if(q!=hold_head)
{link(page_head)= link(hold_head);page_tail= q;
}

/*:1016*/
#line 20428 "texprof.w"
;
/*1018:*/
#line 20499 "texprof.w"

r= link(page_ins_head);
while(r!=page_ins_head)
{q= link(r);free_node(r,page_ins_node_size);r= q;
}
link(page_ins_head)= page_ins_head

/*:1018*/
#line 20429 "texprof.w"


/*:1013*/
#line 20382 "texprof.w"
;
if(sa_mark!=null)
if(do_marks(fire_up_done,0,sa_mark))sa_mark= null;
if((top_mark!=null)&&(first_mark==null))
{first_mark= top_mark;add_token_ref(top_mark);
}
if(output_routine!=null)
if(dead_cycles>=max_dead_cycles)
/*1023:*/
#line 20573 "texprof.w"

{print_err("Output loop---");print_int(dead_cycles);

print(" consecutive dead cycles");
help3("I've concluded that your \\output is awry; it never does a",
"\\shipout, so I'm shipping \\box255 out myself. Next time",
"increase \\maxdeadcycles if you want me to be more patient!");error();
}

/*:1023*/
#line 20390 "texprof.w"

else/*1024:*/
#line 20582 "texprof.w"

{output_active= true;
incr(dead_cycles);
push_nest();mode= -vmode;prev_depth= ignore_depth;mode_line= -line;
begin_token_list(output_routine,output_text);
new_save_level(output_group);normal_paragraph();
scan_left_brace();
return;
}

/*:1024*/
#line 20391 "texprof.w"
;
/*1022:*/
#line 20561 "texprof.w"

{if(link(page_head)!=null)
{if(link(contrib_head)==null)
if(nest_ptr==0)tail= page_tail;else contrib_tail= page_tail;
else link(page_tail)= link(contrib_head);
link(contrib_head)= link(page_head);
link(page_head)= null;page_tail= page_head;
}
flush_node_list(page_disc);page_disc= null;
ship_out(box(255));box(255)= null;
}

/*:1022*/
#line 20392 "texprof.w"
;
}

/*:1011*/
#line 20052 "texprof.w"

static void build_page(void)
{
pointer p;
pointer q,r;
int b,c;
int pi;
int n;
scaled delta,h,w;
/*1766:*/
#line 31393 "texprof.w"

int tmp_cmd;
int tmp_file_line;
int tmp_depth;

/*:1766*/
#line 20061 "texprof.w"

if((link(contrib_head)==null)||output_active)return;
/*1770:*/
#line 31430 "texprof.w"

if(profile_on)
{/*1761:*/
#line 31310 "texprof.w"

if(profile_on)
{if(st_count+3> MAX_STAMPS)
overflow("profile data",MAX_STAMPS);
/*1779:*/
#line 31656 "texprof.w"

if(last_depth> prof_depth)
{if(last_depth==prof_depth+1)
prof_cmd= prof_cmd|POP_BIT;
else
stamp[st_count++]= (system_macro_pop<<24)|(last_depth-prof_depth);
#if SHOW_RECORD_TIMING
print_char('{');print_int(cmd_count);
print_char(':');print_int(system_macro_pop);
print_char(':');print_int(last_depth);
print_char('>');print_int(prof_depth);
print_char('}');print_ln();
#endif
#line 31669 "texprof.w"
 cmd_count++;
last_depth= unchanged_depth= prof_depth;
}


/*:1779*/
#line 31314 "texprof.w"

stamp[st_count++]= (prof_cmd<<24)|prof_file_line;
prof_cmd= prof_cmd&~POP_BIT;
#if SHOW_RECORD_TIMING
print_char('<');print_int(cmd_count);
print_char(':');
if(prof_cmd&POP_BIT)print_char('-');
print_int(prof_cmd&~POP_BIT);
print_char(':');print_int(prof_depth);
print_char('>');print_ln();
#endif
#line 31325 "texprof.w"
 cmd_count++;
/*1756:*/
#line 31198 "texprof.w"

#if GETTIME==0
time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#elif GETTIME==1
#line 31202 "texprof.w"
 time_error= clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&ts);
#elif GETTIME==2
#line 31204 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
#elif GETTIME==3
#line 31206 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC,&ts);
#else
#line 31208 "texprof.w"
 time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#endif
#line 31210 "texprof.w"

/*:1756*/
#line 31326 "texprof.w"

/*1757:*/
#line 31215 "texprof.w"

diff_nsec= (ts.tv_sec-start_sec)*1000000000+(ts.tv_nsec-start_nsec);
#if 0
printf("time: %ld %ld %ld\n",diff_nsec,(ts.tv_sec),(ts.tv_nsec));
#endif
#line 31220 "texprof.w"

start_nsec= ts.tv_nsec;
start_sec= ts.tv_sec;

/*:1757*/
#line 31327 "texprof.w"

stamp[st_count++]= diff_nsec;
}


/*:1761*/
#line 31432 "texprof.w"

tmp_file_line= prof_file_line;
tmp_cmd= prof_cmd;
tmp_depth= prof_depth;
prof_file_line= FILE_LINE(system_file,system_build_page);
prof_cmd= system_cmd;
}



/*:1770*/
#line 20063 "texprof.w"

do{resume:p= link(contrib_head);
/*995:*/
#line 20080 "texprof.w"

if(last_glue!=max_halfword)delete_glue_ref(last_glue);
last_penalty= 0;last_kern= 0;
last_node_type= type(p)+1;
if(type(p)==glue_node)
{last_glue= glue_ptr(p);add_glue_ref(last_glue);
}
else{last_glue= max_halfword;
if(type(p)==penalty_node)last_penalty= penalty(p);
else if(type(p)==kern_node)last_kern= width(p);
}

/*:995*/
#line 20065 "texprof.w"
;
/*996:*/
#line 20098 "texprof.w"

/*999:*/
#line 20132 "texprof.w"

switch(type(p)){
case hlist_node:case vlist_node:case rule_node:if(page_contents<box_there)
/*1000:*/
#line 20155 "texprof.w"

{if(page_contents==empty)freeze_page_specs(box_there);
else page_contents= box_there;
q= new_skip_param(top_skip_code);
if(width(temp_ptr)> height(p))width(temp_ptr)= width(temp_ptr)-height(p);
else width(temp_ptr)= 0;
link(q)= p;link(contrib_head)= q;goto resume;
}

/*:1000*/
#line 20136 "texprof.w"

else/*1001:*/
#line 20164 "texprof.w"

{page_total= page_total+page_depth+height(p);
page_depth= depth(p);
goto contribute;
}

/*:1001*/
#line 20138 "texprof.w"
break;
case whatsit_node:/*1363:*/
#line 25654 "texprof.w"

goto contribute

/*:1363*/
#line 20140 "texprof.w"
;
case glue_node:if(page_contents<box_there)goto done1;
else if(precedes_break(page_tail))pi= 0;
else goto update_heights;break;
case kern_node:if(page_contents<box_there)goto done1;
else if(link(p)==null)return;
else if(type(link(p))==glue_node)pi= 0;
else goto update_heights;break;
case penalty_node:if(page_contents<box_there)goto done1;else pi= penalty(p);break;
case mark_node:goto contribute;
case ins_node:/*1007:*/
#line 20253 "texprof.w"

{if(page_contents==empty)freeze_page_specs(inserts_only);
n= subtype(p);r= page_ins_head;
while(n>=subtype(link(r)))r= link(r);
n= qo(n);
if(subtype(r)!=qi(n))
/*1008:*/
#line 20282 "texprof.w"

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
{print_err("Infinite glue shrinkage inserted from ");print_esc("skip");

print_int(n);
help3("The correction glue for page breaking with insertions",
"must have finite shrinkability. But you may proceed,",
"since the offensive shrinkability has been made finite.");
error();
}
}

/*:1008*/
#line 20260 "texprof.w"
;
if(type(r)==split_up)insert_penalties= insert_penalties+float_cost(p);
else{last_ins_ptr(r)= p;
delta= page_goal-page_total-page_depth+page_shrink;

if(count(n)==1000)h= height(p);
else h= x_over_n(height(p),1000)*count(n);
if(((h<=0)||(h<=delta))&&(height(p)+height(r)<=dimen(n)))
{page_goal= page_goal-h;height(r)= height(r)+height(p);
}
else/*1009:*/
#line 20315 "texprof.w"

{if(count(n)<=0)w= max_dimen;
else{w= page_goal-page_total-page_depth;
if(count(n)!=1000)w= x_over_n(w,count(n))*1000;
}
if(w> dimen(n)-height(r))w= dimen(n)-height(r);
q= vert_break(ins_ptr(p),w,depth(p));
height(r)= height(r)+best_height_plus_depth;
#ifdef STAT
if(tracing_pages> 0)/*1010:*/
#line 20335 "texprof.w"

{begin_diagnostic();print_nl("% split");print_int(n);

print(" to ");print_scaled(w);
print_char(',');print_scaled(best_height_plus_depth);
print(" p=");
if(q==null)print_int(eject_penalty);
else if(type(q)==penalty_node)print_int(penalty(q));
else print_char('0');
end_diagnostic(false);
}

/*:1010*/
#line 20324 "texprof.w"
;
#endif
#line 20326 "texprof.w"

if(count(n)!=1000)
best_height_plus_depth= x_over_n(best_height_plus_depth,1000)*count(n);
page_goal= page_goal-best_height_plus_depth;
type(r)= split_up;broken_ptr(r)= q;broken_ins(r)= p;
if(q==null)insert_penalties= insert_penalties+eject_penalty;
else if(type(q)==penalty_node)insert_penalties= insert_penalties+penalty(q);
}

/*:1009*/
#line 20271 "texprof.w"
;
}
goto contribute;
}

/*:1007*/
#line 20150 "texprof.w"

default:confusion("page");

}

/*:999*/
#line 20103 "texprof.w"
;
/*1004:*/
#line 20198 "texprof.w"

if(pi<inf_penalty)
{/*1006:*/
#line 20245 "texprof.w"

if(page_total<page_goal)
if((page_so_far[3]!=0)||(page_so_far[4]!=0)||
(page_so_far[5]!=0))b= 0;
else b= badness(page_goal-page_total,page_so_far[2]);
else if(page_total-page_goal> page_shrink)b= awful_bad;
else b= badness(page_total-page_goal,page_shrink)

/*:1006*/
#line 20201 "texprof.w"
;
if(b<awful_bad)
if(pi<=eject_penalty)c= pi;
else if(b<inf_bad)c= b+pi+insert_penalties;
else c= deplorable;
else c= b;
if(insert_penalties>=10000)c= awful_bad;
#ifdef STAT
if(tracing_pages> 0)/*1005:*/
#line 20231 "texprof.w"

{begin_diagnostic();print_nl("%");
print(" t=");print_totals();
print(" g=");print_scaled(page_goal);
print(" b=");
if(b==awful_bad)print_char('*');else print_int(b);

print(" p=");print_int(pi);
print(" c=");
if(c==awful_bad)print_char('*');else print_int(c);
if(c<=least_page_cost)print_char('#');
end_diagnostic(false);
}

/*:1005*/
#line 20209 "texprof.w"
;
#endif
#line 20211 "texprof.w"

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
{fire_up(p);
if(output_active)
{/*1768:*/
#line 31409 "texprof.w"

if(profile_on)
{/*1761:*/
#line 31310 "texprof.w"

if(profile_on)
{if(st_count+3> MAX_STAMPS)
overflow("profile data",MAX_STAMPS);
/*1779:*/
#line 31656 "texprof.w"

if(last_depth> prof_depth)
{if(last_depth==prof_depth+1)
prof_cmd= prof_cmd|POP_BIT;
else
stamp[st_count++]= (system_macro_pop<<24)|(last_depth-prof_depth);
#if SHOW_RECORD_TIMING
print_char('{');print_int(cmd_count);
print_char(':');print_int(system_macro_pop);
print_char(':');print_int(last_depth);
print_char('>');print_int(prof_depth);
print_char('}');print_ln();
#endif
#line 31669 "texprof.w"
 cmd_count++;
last_depth= unchanged_depth= prof_depth;
}


/*:1779*/
#line 31314 "texprof.w"

stamp[st_count++]= (prof_cmd<<24)|prof_file_line;
prof_cmd= prof_cmd&~POP_BIT;
#if SHOW_RECORD_TIMING
print_char('<');print_int(cmd_count);
print_char(':');
if(prof_cmd&POP_BIT)print_char('-');
print_int(prof_cmd&~POP_BIT);
print_char(':');print_int(prof_depth);
print_char('>');print_ln();
#endif
#line 31325 "texprof.w"
 cmd_count++;
/*1756:*/
#line 31198 "texprof.w"

#if GETTIME==0
time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#elif GETTIME==1
#line 31202 "texprof.w"
 time_error= clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&ts);
#elif GETTIME==2
#line 31204 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
#elif GETTIME==3
#line 31206 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC,&ts);
#else
#line 31208 "texprof.w"
 time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#endif
#line 31210 "texprof.w"

/*:1756*/
#line 31326 "texprof.w"

/*1757:*/
#line 31215 "texprof.w"

diff_nsec= (ts.tv_sec-start_sec)*1000000000+(ts.tv_nsec-start_nsec);
#if 0
printf("time: %ld %ld %ld\n",diff_nsec,(ts.tv_sec),(ts.tv_nsec));
#endif
#line 31220 "texprof.w"

start_nsec= ts.tv_nsec;
start_sec= ts.tv_sec;

/*:1757*/
#line 31327 "texprof.w"

stamp[st_count++]= diff_nsec;
}


/*:1761*/
#line 31411 "texprof.w"

prof_file_line= tmp_file_line;
prof_cmd= tmp_cmd;
prof_depth= tmp_depth;
}



/*:1768*/
#line 20224 "texprof.w"

return;
}
goto done;
}
}

/*:1004*/
#line 20106 "texprof.w"
;
if((type(p)<glue_node)||(type(p)> kern_node))goto contribute;
update_heights:/*1003:*/
#line 20177 "texprof.w"

if(type(p)==kern_node)q= p;
else{q= glue_ptr(p);
page_so_far[2+stretch_order(q)]= 
page_so_far[2+stretch_order(q)]+stretch(q);
page_shrink= page_shrink+shrink(q);
if((shrink_order(q)!=normal)&&(shrink(q)!=0))
{
print_err("Infinite glue shrinkage found on current page");

help4("The page about to be output contains some infinitely",
"shrinkable glue, e.g., `\\vss' or `\\vskip 0pt minus 1fil'.",
"Such glue doesn't belong there; but you can safely proceed,",
"since the offensive shrinkability has been made finite.");
error();
r= new_spec(q);shrink_order(r)= normal;delete_glue_ref(q);
glue_ptr(p)= r;q= r;
}
}
page_total= page_total+page_depth+width(q);page_depth= 0

/*:1003*/
#line 20109 "texprof.w"
;
contribute:/*1002:*/
#line 20170 "texprof.w"

if(page_depth> page_max_depth)
{page_total= 
page_total+page_depth-page_max_depth;
page_depth= page_max_depth;
}

/*:1002*/
#line 20110 "texprof.w"
;
/*997:*/
#line 20115 "texprof.w"

link(page_tail)= p;page_tail= p;
link(contrib_head)= link(p);link(p)= null;goto done

/*:997*/
#line 20111 "texprof.w"
;
done1:/*998:*/
#line 20119 "texprof.w"

link(contrib_head)= link(p);link(p)= null;
if(saving_vdiscards> 0)
{if(page_disc==null)page_disc= p;else link(tail_page_disc)= p;
tail_page_disc= p;
}
else flush_node_list(p)

/*:998*/
#line 20112 "texprof.w"
;
done:

/*:996*/
#line 20068 "texprof.w"
;
}while(!(link(contrib_head)==null));
/*994:*/
#line 20076 "texprof.w"

if(nest_ptr==0)tail= contrib_head;
else contrib_tail= contrib_head

/*:994*/
#line 20070 "texprof.w"
;
/*1768:*/
#line 31409 "texprof.w"

if(profile_on)
{/*1761:*/
#line 31310 "texprof.w"

if(profile_on)
{if(st_count+3> MAX_STAMPS)
overflow("profile data",MAX_STAMPS);
/*1779:*/
#line 31656 "texprof.w"

if(last_depth> prof_depth)
{if(last_depth==prof_depth+1)
prof_cmd= prof_cmd|POP_BIT;
else
stamp[st_count++]= (system_macro_pop<<24)|(last_depth-prof_depth);
#if SHOW_RECORD_TIMING
print_char('{');print_int(cmd_count);
print_char(':');print_int(system_macro_pop);
print_char(':');print_int(last_depth);
print_char('>');print_int(prof_depth);
print_char('}');print_ln();
#endif
#line 31669 "texprof.w"
 cmd_count++;
last_depth= unchanged_depth= prof_depth;
}


/*:1779*/
#line 31314 "texprof.w"

stamp[st_count++]= (prof_cmd<<24)|prof_file_line;
prof_cmd= prof_cmd&~POP_BIT;
#if SHOW_RECORD_TIMING
print_char('<');print_int(cmd_count);
print_char(':');
if(prof_cmd&POP_BIT)print_char('-');
print_int(prof_cmd&~POP_BIT);
print_char(':');print_int(prof_depth);
print_char('>');print_ln();
#endif
#line 31325 "texprof.w"
 cmd_count++;
/*1756:*/
#line 31198 "texprof.w"

#if GETTIME==0
time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#elif GETTIME==1
#line 31202 "texprof.w"
 time_error= clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&ts);
#elif GETTIME==2
#line 31204 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
#elif GETTIME==3
#line 31206 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC,&ts);
#else
#line 31208 "texprof.w"
 time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#endif
#line 31210 "texprof.w"

/*:1756*/
#line 31326 "texprof.w"

/*1757:*/
#line 31215 "texprof.w"

diff_nsec= (ts.tv_sec-start_sec)*1000000000+(ts.tv_nsec-start_nsec);
#if 0
printf("time: %ld %ld %ld\n",diff_nsec,(ts.tv_sec),(ts.tv_nsec));
#endif
#line 31220 "texprof.w"

start_nsec= ts.tv_nsec;
start_sec= ts.tv_sec;

/*:1757*/
#line 31327 "texprof.w"

stamp[st_count++]= diff_nsec;
}


/*:1761*/
#line 31411 "texprof.w"

prof_file_line= tmp_file_line;
prof_cmd= tmp_cmd;
prof_depth= tmp_depth;
}



/*:1768*/
#line 20071 "texprof.w"

}

/*:993*//*1029:*/
#line 20682 "texprof.w"
/*1042:*/
#line 21015 "texprof.w"

static void app_space(void)
{pointer q;
if((space_factor>=2000)&&(xspace_skip!=zero_glue))
q= new_param_glue(xspace_skip_code);
else{if(space_skip!=zero_glue)main_p= space_skip;
else/*1041:*/
#line 21004 "texprof.w"

{main_p= font_glue[cur_font];
if(main_p==null)
{main_p= new_spec(zero_glue);main_k= param_base[cur_font]+space_code;
width(main_p)= font_info[main_k].sc;
stretch(main_p)= font_info[main_k+1].sc;
shrink(main_p)= font_info[main_k+2].sc;
font_glue[cur_font]= main_p;
}
}

/*:1041*/
#line 21021 "texprof.w"
;
main_p= new_spec(main_p);
/*1043:*/
#line 21029 "texprof.w"

if(space_factor>=2000)width(main_p)= width(main_p)+extra_space(cur_font);
stretch(main_p)= xn_over_d(stretch(main_p),space_factor,1000);
shrink(main_p)= xn_over_d(shrink(main_p),1000,space_factor)

/*:1043*/
#line 21023 "texprof.w"
;
q= new_glue(main_p);glue_ref_count(main_p)= null;
}
link(tail)= q;tail= q;
}

/*:1042*//*1046:*/
#line 21075 "texprof.w"

static void insert_dollar_sign(void)
{back_input();cur_tok= math_shift_token+'$';
print_err("Missing $ inserted");

help2("I've inserted a begin-math/end-math symbol since I think",
"you left one out. Proceed, with fingers crossed.");ins_error();
}

/*:1046*//*1048:*/
#line 21100 "texprof.w"

static void you_cant(void)
{print_err("You can't use `");

print_cmd_chr(cur_cmd,cur_chr);
print("' in ");print_mode(mode);
}

/*:1048*//*1049:*/
#line 21108 "texprof.w"

static void report_illegal_case(void)
{you_cant();
help4("Sorry, but I'm not programmed to handle this case;",
"I'll just pretend that you didn't ask for it.",
"If you're in the wrong mode, you might be able to",
"return to the right one by typing `I}' or `I$' or `I\\par'.");
error();
}

/*:1049*//*1050:*/
#line 21123 "texprof.w"

static bool privileged(void)
{if(mode> 0)return true;
else{report_illegal_case();return false;
}
}

/*:1050*//*1053:*/
#line 21150 "texprof.w"

static bool its_all_over(void)
{
if(privileged())
{if((page_head==page_tail)&&(head==tail)&&(dead_cycles==0))
{return true;
}
back_input();
tail_append(new_null_box());
width(tail)= hsize;
tail_append(new_glue(fill_glue));
tail_append(new_penalty(-010000000000));
build_page();
}
return false;
}

/*:1053*//*1059:*/
#line 21261 "texprof.w"

static void append_glue(void)
{small_number s;
s= cur_chr;
switch(s){
case fil_code:cur_val= fil_glue;break;
case fill_code:cur_val= fill_glue;break;
case ss_code:cur_val= ss_glue;break;
case fil_neg_code:cur_val= fil_neg_glue;break;
case skip_code:scan_glue(glue_val);break;
case mskip_code:scan_glue(mu_val);
}
tail_append(new_glue(cur_val));
if(s>=skip_code)
{decr(glue_ref_count(cur_val));
if(s> skip_code)subtype(tail)= mu_glue;
}
}

/*:1059*//*1060:*/
#line 21280 "texprof.w"

static void append_kern(void)
{quarterword s;
s= cur_chr;scan_dimen(s==mu_glue,false,false);
tail_append(new_kern(cur_val));subtype(tail)= s;
}

/*:1060*//*1063:*/
#line 21324 "texprof.w"

static void off_save(void)
{pointer p;
if(cur_group==bottom_level)
/*1065:*/
#line 21364 "texprof.w"

{print_err("Extra ");print_cmd_chr(cur_cmd,cur_chr);

help1("Things are pretty mixed up, but I think the worst is over.");
error();
}

/*:1065*/
#line 21328 "texprof.w"

else{back_input();p= get_avail();link(temp_head)= p;
print_err("Missing ");
/*1064:*/
#line 21345 "texprof.w"

switch(cur_group){
case semi_simple_group:{info(p)= cs_token_flag+frozen_end_group;
print_esc("endgroup");

}break;
case math_shift_group:{info(p)= math_shift_token+'$';print_char('$');

}break;
case math_left_group:{info(p)= cs_token_flag+frozen_right;link(p)= get_avail();
p= link(p);info(p)= other_token+'.';print_esc("right.");


}break;
default:{info(p)= right_brace_token+'}';print_char('}');

}
}

/*:1064*/
#line 21332 "texprof.w"
;
print(" inserted");ins_list(link(temp_head));
help5("I've inserted something that you may have forgotten.",
"(See the <inserted text> above.)",
"With luck, this will get me unwedged. But if you",
"really didn't forget anything, try typing `2' now; then",
"my insertion and my current dilemma will both disappear.");
error();
}
}

/*:1063*//*1068:*/
#line 21402 "texprof.w"

static void extra_right_brace(void)
{print_err("Extra }, or forgotten ");

switch(cur_group){
case semi_simple_group:print_esc("endgroup");break;
case math_shift_group:print_char('$');break;
case math_left_group:print_esc("right");
}
help5("I've deleted a group-closing symbol because it seems to be",
"spurious, as in `$x}$'. But perhaps the } is legitimate and",
"you forgot something else, as in `\\hbox{$x}'. In such cases",
"the way to recover is to insert both the forgotten and the",
"deleted material, e.g., by typing `I$}'.");error();
incr(align_state);
}

/*:1068*//*1069:*/
#line 21422 "texprof.w"

static void normal_paragraph(void)
{if(looseness!=0)eq_word_define(int_base+looseness_code,0);
if(hang_indent!=0)eq_word_define(dimen_base+hang_indent_code,0);
if(hang_after!=1)eq_word_define(int_base+hang_after_code,1);
if(par_shape_ptr!=null)eq_define(par_shape_loc,shape_ref,null);
if(inter_line_penalties_ptr!=null)
eq_define(inter_line_penalties_loc,shape_ref,null);
}

/*:1069*//*1074:*/
#line 21546 "texprof.w"

static void box_end(int box_context)
{pointer p;
small_number a;
if(box_context<box_flag)/*1075:*/
#line 21562 "texprof.w"

{if(cur_box!=null)
{shift_amount(cur_box)= box_context;
if(abs(mode)==vmode)
{append_to_vlist(cur_box);
if(adjust_tail!=null)
{if(adjust_head!=adjust_tail)
{link(tail)= link(adjust_head);tail= adjust_tail;
}
adjust_tail= null;
}
if(mode> 0)build_page();
}
else{if(abs(mode)==hmode)space_factor= 1000;
else{p= new_noad();
math_type(nucleus(p))= sub_box;
info(nucleus(p))= cur_box;cur_box= p;
}
link(tail)= cur_box;tail= cur_box;
}
}
}

/*:1075*/
#line 21551 "texprof.w"

else if(box_context<ship_out_flag)/*1076:*/
#line 21585 "texprof.w"

{if(box_context<global_box_flag)
{cur_val= box_context-box_flag;a= 0;
}
else{cur_val= box_context-global_box_flag;a= 4;
}
if(cur_val<256)define(box_base+cur_val,box_ref,cur_box);
else sa_def_box;
}

/*:1076*/
#line 21552 "texprof.w"

else if(cur_box!=null)
if(box_context> ship_out_flag)/*1077:*/
#line 21595 "texprof.w"

{/*403:*/
#line 8617 "texprof.w"

do{get_x_token();
}while(!((cur_cmd!=spacer)&&(cur_cmd!=relax)))

/*:403*/
#line 21596 "texprof.w"
;
if(((cur_cmd==hskip)&&(abs(mode)!=vmode))||
((cur_cmd==vskip)&&(abs(mode)==vmode)))
{append_glue();subtype(tail)= box_context-(leader_flag-a_leaders);
leader_ptr(tail)= cur_box;
}
else{print_err("Leaders not followed by proper glue");

help3("You should say `\\leaders <box or rule><hskip or vskip>'.",
"I found the <box or rule>, but there's no suitable",
"<hskip or vskip>, so I'm ignoring these leaders.");back_error();
flush_node_list(cur_box);
}
}

/*:1077*/
#line 21554 "texprof.w"

else ship_out(cur_box);
}

/*:1074*//*1078:*/
#line 21616 "texprof.w"

static void begin_box(int box_context)
{
pointer p,q;
int m;
halfword k;
halfword n;
switch(cur_chr){
case box_code:{scan_register_num();fetch_box(cur_box);
change_box(null);
}break;
case copy_code:{scan_register_num();fetch_box(q);cur_box= copy_node_list(q);
}break;
case last_box_code:/*1079:*/
#line 21641 "texprof.w"

{cur_box= null;
if(abs(mode)==mmode)
{you_cant();help1("Sorry; this \\lastbox will be void.");error();
}
else if((mode==vmode)&&(head==tail))
{you_cant();
help2("Sorry...I usually can't take things from the current page.",
"This \\lastbox will therefore be void.");error();
}
else{if(!is_char_node(tail))
if((type(tail)==hlist_node)||(type(tail)==vlist_node))
/*1080:*/
#line 21657 "texprof.w"

{q= head;
do{p= q;
if(!is_char_node(q))if(type(q)==disc_node)
{for(m= 1;m<=replace_count(q);m++)p= link(p);
if(p==tail)goto done;
}
q= link(p);
}while(!(q==tail));
cur_box= tail;shift_amount(cur_box)= 0;
tail= p;link(p)= null;
done:;}

/*:1080*/
#line 21653 "texprof.w"
;
}
}

/*:1079*/
#line 21630 "texprof.w"
break;
case vsplit_code:/*1081:*/
#line 21672 "texprof.w"

{scan_register_num();n= cur_val;
if(!scan_keyword("to"))

{print_err("Missing `to' inserted");

help2("I'm working on `\\vsplit<box number> to <dimen>';",
"will look for the <dimen> next.");error();
}
scan_normal_dimen;
cur_box= vsplit(n,cur_val);
}

/*:1081*/
#line 21632 "texprof.w"
break;
default:/*1082:*/
#line 21688 "texprof.w"

{k= cur_chr-vtop_code;saved(0)= box_context;
if(k==hmode)
if((box_context<box_flag)&&(abs(mode)==vmode))
scan_spec(adjusted_hbox_group,true);
else scan_spec(hbox_group,true);
else{if(k==vmode)scan_spec(vbox_group,true);
else{scan_spec(vtop_group,true);k= vmode;
}
normal_paragraph();
}
push_nest();mode= -k;
if(k==vmode)
{prev_depth= ignore_depth;
if(every_vbox!=null)begin_token_list(every_vbox,every_vbox_text);
}
else{space_factor= 1000;
if(every_hbox!=null)begin_token_list(every_hbox,every_hbox_text);
}
return;
}

/*:1082*/
#line 21633 "texprof.w"

}
box_end(box_context);
}

/*:1078*//*1083:*/
#line 21710 "texprof.w"

static void scan_box(int box_context)

{/*403:*/
#line 8617 "texprof.w"

do{get_x_token();
}while(!((cur_cmd!=spacer)&&(cur_cmd!=relax)))

/*:403*/
#line 21713 "texprof.w"
;
if(cur_cmd==make_box)begin_box(box_context);
else if((box_context>=leader_flag)&&((cur_cmd==hrule)||(cur_cmd==vrule)))
{cur_box= scan_rule_spec();box_end(box_context);
}
else{
print_err("A <box> was supposed to be here");

help3("I was expecting to see \\hbox or \\vbox or \\copy or \\box or",
"something like that. So you might find something missing in",
"your output. But keep trying; you can fix this later.");back_error();
}
}

/*:1083*//*1085:*/
#line 21740 "texprof.w"

static void package(small_number c)
{scaled h;
pointer p;
scaled d;
d= box_max_depth;unsave();save_ptr= save_ptr-3;
if(mode==-hmode)cur_box= hpack(link(head),saved(2),saved(1));
else{cur_box= vpackage(link(head),saved(2),saved(1),d);
if(c==vtop_code)/*1086:*/
#line 21758 "texprof.w"

{h= 0;p= list_ptr(cur_box);
if(p!=null)if(type(p)<=rule_node)h= height(p);
depth(cur_box)= depth(cur_box)-h+height(cur_box);height(cur_box)= h;
}

/*:1086*/
#line 21748 "texprof.w"
;
}
pop_nest();box_end(saved(0));
}

/*:1085*//*1090:*/
#line 21789 "texprof.w"

static small_number norm_min(int h)
{if(h<=0)return 1;else if(h>=63)return 63;
else return h;
}

static void new_graf(bool indented)
{prev_graf= 0;
if((mode==vmode)||(head!=tail))
tail_append(new_param_glue(par_skip_code));
push_nest();mode= hmode;space_factor= 1000;set_cur_lang;clang= cur_lang;
prev_graf= (norm_min(left_hyphen_min)*0100+norm_min(right_hyphen_min))
*0200000+cur_lang;
if(indented)
{tail= new_null_box();link(head)= tail;width(tail)= par_indent;
}
if(every_par!=null)begin_token_list(every_par,every_par_text);
if(nest_ptr==1)build_page();
}

/*:1090*//*1092:*/
#line 21812 "texprof.w"

static void indent_in_hmode(void)
{pointer p,q;
if(cur_chr> 0)
{p= new_null_box();width(p)= par_indent;
if(abs(mode)==hmode)space_factor= 1000;
else{q= new_noad();math_type(nucleus(q))= sub_box;
info(nucleus(q))= p;p= q;
}
tail_append(p);
}
}

/*:1092*//*1094:*/
#line 21841 "texprof.w"

static void head_for_vmode(void)
{if(mode<0)
if(cur_cmd!=hrule)off_save();
else{print_err("You can't use `");
print_esc("hrule");print("' here except with leaders");

help2("To put a horizontal rule in an hbox or an alignment,",
"you should use \\leaders or \\hrulefill (see The TeXbook).");
error();
}
else{back_input();cur_tok= par_token;back_input();token_type= inserted;
}
}

/*:1094*//*1095:*/
#line 21856 "texprof.w"

static void end_graf(void)
{if(mode==hmode)
{if(head==tail)pop_nest();
else line_break(widow_penalty);
normal_paragraph();
error_count= 0;
}
}

/*:1095*//*1098:*/
#line 21877 "texprof.w"

static void begin_insert_or_adjust(void)
{if(cur_cmd==vadjust)cur_val= 255;
else{scan_eight_bit_int();
if(cur_val==255)
{print_err("You can't ");print_esc("insert");print_int(255);

help1("I'm changing to \\insert0; box 255 is special.");
error();cur_val= 0;
}
}
saved(0)= cur_val;incr(save_ptr);
new_save_level(insert_group);scan_left_brace();normal_paragraph();
push_nest();mode= -vmode;prev_depth= ignore_depth;
}

/*:1098*//*1100:*/
#line 21914 "texprof.w"

static void make_mark(void)
{pointer p;
halfword c;
if(cur_chr==0)c= 0;
else{scan_register_num();c= cur_val;
}
p= scan_toks(false,true);p= get_node(small_node_size);
mark_class(p)= c;
type(p)= mark_node;subtype(p)= 0;
mark_ptr(p)= def_ref;link(tail)= p;tail= p;
}

/*:1100*//*1102:*/
#line 21933 "texprof.w"

static void append_penalty(void)
{scan_int();tail_append(new_penalty(cur_val));
if(mode==vmode)build_page();
}

/*:1102*//*1104:*/
#line 21952 "texprof.w"

static void delete_last(void)
{
pointer p,q;
int m;
if((mode==vmode)&&(tail==head))
/*1105:*/
#line 21974 "texprof.w"

{if((cur_chr!=glue_node)||(last_glue!=max_halfword))
{you_cant();
help2("Sorry...I usually can't take things from the current page.",
"Try `I\\vskip-\\lastskip' instead.");
if(cur_chr==kern_node)help_line[0]= 
("Try `I\\kern-\\lastkern' instead.");
else if(cur_chr!=glue_node)help_line[0]= 
("Perhaps you can make the output routine do it.");
error();
}
}

/*:1105*/
#line 21959 "texprof.w"

else{if(!is_char_node(tail))if(type(tail)==cur_chr)
{q= head;
do{p= q;
if(!is_char_node(q))if(type(q)==disc_node)
{for(m= 1;m<=replace_count(q);m++)p= link(p);
if(p==tail)return;
}
q= link(p);
}while(!(q==tail));
link(p)= null;flush_node_list(tail);tail= p;
}
}
}

/*:1104*//*1109:*/
#line 22019 "texprof.w"

static void unpackage(void)
{
pointer p;
int c;
if(cur_chr> copy_code)/*1533:*/
#line 28124 "texprof.w"

{link(tail)= disc_ptr[cur_chr];disc_ptr[cur_chr]= null;
goto done;
}

/*:1533*/
#line 22024 "texprof.w"
;
c= cur_chr;scan_register_num();fetch_box(p);
if(p==null)return;
if((abs(mode)==mmode)||((abs(mode)==vmode)&&(type(p)!=vlist_node))||
((abs(mode)==hmode)&&(type(p)!=hlist_node)))
{print_err("Incompatible list can't be unboxed");

help3("Sorry, Pandora. (You sneaky devil.)",
"I refuse to unbox an \\hbox in vertical mode or vice versa.",
"And I can't open any boxes in math mode.");
error();return;
}
if(c==copy_code)link(tail)= copy_node_list(list_ptr(p));
else{link(tail)= list_ptr(p);change_box(null);
free_node(p,box_node_size);
}
done:
while(link(tail)!=null)tail= link(tail);
}

/*:1109*//*1112:*/
#line 22054 "texprof.w"

static void append_italic_correction(void)
{
pointer p;
internal_font_number f;
if(tail!=head)
{if(is_char_node(tail))p= tail;
else if(type(tail)==ligature_node)p= lig_char(tail);
else return;
f= font(p);
tail_append(new_kern(char_italic(f,char_info(f,character(p)))));
subtype(tail)= explicit;
}
}

/*:1112*//*1116:*/
#line 22088 "texprof.w"

static void append_discretionary(void)
{int c;
tail_append(new_disc());
if(cur_chr==1)
{c= hyphen_char[cur_font];
if(c>=0)if(c<256)pre_break(tail)= new_character(cur_font,c);
}
else{incr(save_ptr);saved(-1)= 0;new_save_level(disc_group);
scan_left_brace();push_nest();mode= -hmode;space_factor= 1000;
}
}

/*:1116*//*1118:*/
#line 22108 "texprof.w"

static void build_discretionary(void)
{
pointer p,q;
int n;
unsave();
/*1120:*/
#line 22150 "texprof.w"

q= head;p= link(q);n= 0;
while(p!=null)
{if(!is_char_node(p))if(type(p)> rule_node)
if(type(p)!=kern_node)if(type(p)!=ligature_node)
{print_err("Improper discretionary list");

help1("Discretionary lists must contain only boxes and kerns.");
error();
begin_diagnostic();
print_nl("The following discretionary sublist has been deleted:");

show_box(p);
end_diagnostic(true);
flush_node_list(p);link(q)= null;goto done;
}
q= p;p= link(q);incr(n);
}
done:

/*:1120*/
#line 22116 "texprof.w"
;
p= link(head);pop_nest();
switch(saved(-1)){
case 0:pre_break(tail)= p;break;
case 1:post_break(tail)= p;break;
case 2:/*1119:*/
#line 22128 "texprof.w"

{if((n> 0)&&(abs(mode)==mmode))
{print_err("Illegal math ");print_esc("discretionary");

help2("Sorry: The third part of a discretionary break must be",
"empty, in math formulas. I had to delete your third part.");
flush_node_list(p);n= 0;error();
}
else link(tail)= p;
if(n<=max_quarterword)replace_count(tail)= n;
else{print_err("Discretionary list is too long");

help2("Wow---I never thought anybody would tweak me here.",
"You can't seriously need such a huge discretionary list?");
error();
}
if(n> 0)tail= q;
decr(save_ptr);return;
}

/*:1119*/
#line 22122 "texprof.w"
;
}
incr(saved(-1));new_save_level(disc_group);scan_left_brace();
push_nest();mode= -hmode;space_factor= 1000;
}

/*:1118*//*1122:*/
#line 22184 "texprof.w"

static void make_accent(void)
{double s,t;
pointer p,q,r;
internal_font_number f;
scaled a,h,x,w,delta;
four_quarters i;
scan_char_num();f= cur_font;p= new_character(f,cur_val);
if(p!=null)
{x= x_height(f);s= slant(f)/float_constant(65536);

a= char_width(f,char_info(f,character(p)));
do_assignments();
/*1123:*/
#line 22204 "texprof.w"

q= null;f= cur_font;
if((cur_cmd==letter)||(cur_cmd==other_char)||(cur_cmd==char_given))
q= new_character(f,cur_chr);
else if(cur_cmd==char_num)
{scan_char_num();q= new_character(f,cur_val);
}
else back_input()

/*:1123*/
#line 22198 "texprof.w"
;
if(q!=null)/*1124:*/
#line 22220 "texprof.w"

{t= slant(f)/float_constant(65536);

i= char_info(f,character(q));
w= char_width(f,i);h= char_height(f,height_depth(i));
if(h!=x)
{p= hpack(p,natural);shift_amount(p)= x-h;
}
delta= round((w-a)/float_constant(2)+h*t-x*s);


r= new_kern(delta);subtype(r)= acc_kern;link(tail)= r;link(r)= p;
tail= new_kern(-a-delta);subtype(tail)= acc_kern;link(p)= tail;p= q;
}

/*:1124*/
#line 22199 "texprof.w"
;
link(tail)= p;tail= p;space_factor= 1000;
}
}

/*:1122*//*1126:*/
#line 22248 "texprof.w"

static void align_error(void)
{if(abs(align_state)> 2)
/*1127:*/
#line 22268 "texprof.w"

{print_err("Misplaced ");print_cmd_chr(cur_cmd,cur_chr);



if(cur_tok==tab_token+'&')
{help6("I can't figure out why you would want to use a tab mark",
"here. If you just want an ampersand, the remedy is",
"simple: Just type `I\\&' now. But if some right brace",
"up above has ended a previous alignment prematurely,",
"you're probably due for more error messages, and you",
"might try typing `S' now just to see what is salvageable.");
}
else{help5("I can't figure out why you would want to use a tab mark",
"or \\cr or \\span just now. If something like a right brace",
"up above has ended a previous alignment prematurely,",
"you're probably due for more error messages, and you",
"might try typing `S' now just to see what is salvageable.");
}
error();
}

/*:1127*/
#line 22251 "texprof.w"

else{back_input();
if(align_state<0)
{print_err("Missing { inserted");

incr(align_state);cur_tok= left_brace_token+'{';
}
else{print_err("Missing } inserted");

decr(align_state);cur_tok= right_brace_token+'}';
}
help3("I've put in what seems to be necessary to fix",
"the current column of the current alignment.",
"Try to go on, since this might almost work.");ins_error();
}
}

/*:1126*//*1128:*/
#line 22293 "texprof.w"

static void no_align_error(void)
{print_err("Misplaced ");print_esc("noalign");

help2("I expect to see \\noalign only after the \\cr of",
"an alignment. Proceed, and I'll ignore this case.");error();
}
static void omit_error(void)
{print_err("Misplaced ");print_esc("omit");

help2("I expect to see \\omit only after tab marks or the \\cr of",
"an alignment. Proceed, and I'll ignore this case.");error();
}

/*:1128*//*1130:*/
#line 22323 "texprof.w"

static void do_endv(void)
{base_ptr= input_ptr;input_stack[base_ptr]= cur_input;
while((input_stack[base_ptr].index_field!=v_template)&&
(input_stack[base_ptr].loc_field==null)&&
(input_stack[base_ptr].state_field==token_list))decr(base_ptr);
if((input_stack[base_ptr].index_field!=v_template)||
(input_stack[base_ptr].loc_field!=null)||
(input_stack[base_ptr].state_field!=token_list))
fatal_error("(interwoven alignment preambles are not allowed)");

if(cur_group==align_group)
{end_graf();
if(fin_col())fin_row();
}
else off_save();
}

/*:1130*//*1134:*/
#line 22358 "texprof.w"

static void cs_error(void)
{print_err("Extra ");print_esc("endcsname");

help1("I'm ignoring this, since I wasn't doing a \\csname.");
error();
}

/*:1134*//*1135:*/
#line 22376 "texprof.w"

static void push_math(group_code c)
{push_nest();mode= -mmode;incompleat_noad= null;new_save_level(c);
}

/*:1135*//*1137:*/
#line 22389 "texprof.w"

static void init_math(void)
{
scaled w;
scaled l;
scaled s;
pointer p;
pointer q;
internal_font_number f;
int n;
scaled v;
scaled d;
get_token();
if((cur_cmd==math_shift)&&(mode> 0))/*1144:*/
#line 22447 "texprof.w"

{if(head==tail)
{pop_nest();w= -max_dimen;
}
else{line_break(display_widow_penalty);
/*1145:*/
#line 22467 "texprof.w"

v= shift_amount(just_box)+2*quad(cur_font);w= -max_dimen;
p= list_ptr(just_box);
while(p!=null)
{/*1146:*/
#line 22484 "texprof.w"

reswitch:if(is_char_node(p))
{f= font(p);d= char_width(f,char_info(f,character(p)));
goto found;
}
switch(type(p)){
case hlist_node:case vlist_node:case rule_node:{d= width(p);goto found;
}
case ligature_node:/*651:*/
#line 13507 "texprof.w"

{mem[lig_trick]= mem[lig_char(p)];link(lig_trick)= link(p);
p= lig_trick;goto reswitch;
}

/*:651*/
#line 22492 "texprof.w"

case kern_node:case math_node:d= width(p);break;
case glue_node:/*1147:*/
#line 22506 "texprof.w"

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

/*:1147*/
#line 22495 "texprof.w"
break;
case whatsit_node:/*1360:*/
#line 25641 "texprof.w"
d= 0

/*:1360*/
#line 22496 "texprof.w"
;break;
default:d= 0;
}

/*:1146*/
#line 22472 "texprof.w"
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

/*:1145*/
#line 22454 "texprof.w"
;
}

/*1148:*/
#line 22524 "texprof.w"

if(par_shape_ptr==null)
if((hang_indent!=0)&&
(((hang_after>=0)&&(prev_graf+2> hang_after))||
(prev_graf+1<-hang_after)))
{l= hsize-abs(hang_indent);
if(hang_indent> 0)s= hang_indent;else s= 0;
}
else{l= hsize;s= 0;
}
else{n= info(par_shape_ptr);
if(prev_graf+2>=n)p= par_shape_ptr+2*n;
else p= par_shape_ptr+2*(prev_graf+2);
s= mem[p-1].sc;l= mem[p].sc;
}

/*:1148*/
#line 22457 "texprof.w"
;
push_math(math_shift_group);mode= mmode;
eq_word_define(int_base+cur_fam_code,-1);
eq_word_define(dimen_base+pre_display_size_code,w);
eq_word_define(dimen_base+display_width_code,l);
eq_word_define(dimen_base+display_indent_code,s);
if(every_display!=null)begin_token_list(every_display,every_display_text);
if(nest_ptr==1)build_page();
}

/*:1144*/
#line 22402 "texprof.w"

else{back_input();/*1138:*/
#line 22407 "texprof.w"

{push_math(math_shift_group);eq_word_define(int_base+cur_fam_code,-1);
if(every_math!=null)begin_token_list(every_math,every_math_text);
}

/*:1138*/
#line 22403 "texprof.w"
;
}
}

/*:1137*//*1141:*/
#line 22431 "texprof.w"

static void start_eq_no(void)
{saved(0)= cur_chr;incr(save_ptr);
/*1138:*/
#line 22407 "texprof.w"

{push_math(math_shift_group);eq_word_define(int_base+cur_fam_code,-1);
if(every_math!=null)begin_token_list(every_math,every_math_text);
}

/*:1138*/
#line 22434 "texprof.w"
;
}

/*:1141*//*1150:*/
#line 22568 "texprof.w"

static void scan_math(pointer p)
{
int c;
restart:/*403:*/
#line 8617 "texprof.w"

do{get_x_token();
}while(!((cur_cmd!=spacer)&&(cur_cmd!=relax)))

/*:403*/
#line 22572 "texprof.w"
;
reswitch:switch(cur_cmd){
case letter:case other_char:case char_given:{c= ho(math_code(cur_chr));
if(c==0100000)
{/*1151:*/
#line 22597 "texprof.w"

{cur_cs= cur_chr+active_base;
cur_cmd= eq_type(cur_cs);cur_chr= equiv(cur_cs);
x_token();back_input();
}

/*:1151*/
#line 22576 "texprof.w"
;
goto restart;
}
}break;
case char_num:{scan_char_num();cur_chr= cur_val;cur_cmd= char_given;
goto reswitch;
}
case math_char_num:{scan_fifteen_bit_int();c= cur_val;
}break;
case math_given:c= cur_chr;break;
case delim_num:{scan_twenty_seven_bit_int();c= cur_val/010000;
}break;
default:/*1152:*/
#line 22606 "texprof.w"

{back_input();scan_left_brace();
saved(0)= p;incr(save_ptr);push_math(math_group);return;
}

/*:1152*/
#line 22588 "texprof.w"

}
math_type(p)= math_char;character(p)= qi(c%256);
if((c>=var_code)&&fam_in_range)fam(p)= cur_fam;
else fam(p)= (c/256)%16;
}

/*:1150*//*1154:*/
#line 22637 "texprof.w"

static void set_math_char(int c)
{pointer p;
if(c>=0100000)
/*1151:*/
#line 22597 "texprof.w"

{cur_cs= cur_chr+active_base;
cur_cmd= eq_type(cur_cs);cur_chr= equiv(cur_cs);
x_token();back_input();
}

/*:1151*/
#line 22641 "texprof.w"

else{p= new_noad();math_type(nucleus(p))= math_char;
character(nucleus(p))= qi(c%256);
fam(nucleus(p))= (c/256)%16;
if(c>=var_code)
{if(fam_in_range)fam(nucleus(p))= cur_fam;
type(p)= ord_noad;
}
else type(p)= ord_noad+(c/010000);
link(tail)= p;tail= p;
}
}

/*:1154*//*1158:*/
#line 22709 "texprof.w"

static void math_limit_switch(void)
{
if(head!=tail)if(type(tail)==op_noad)
{subtype(tail)= cur_chr;return;
}
print_err("Limit controls must follow a math operator");

help1("I'm ignoring this misplaced \\limits or \\nolimits command.");error();
}

/*:1158*//*1159:*/
#line 22725 "texprof.w"

static void scan_delimiter(pointer p,bool r)
{if(r)scan_twenty_seven_bit_int();
else{/*403:*/
#line 8617 "texprof.w"

do{get_x_token();
}while(!((cur_cmd!=spacer)&&(cur_cmd!=relax)))

/*:403*/
#line 22728 "texprof.w"
;
switch(cur_cmd){
case letter:case other_char:cur_val= del_code(cur_chr);break;
case delim_num:scan_twenty_seven_bit_int();break;
default:cur_val= -1;
}
}
if(cur_val<0)/*1160:*/
#line 22743 "texprof.w"

{print_err("Missing delimiter (. inserted)");

help6("I was expecting to see something like `(' or `\\{' or",
"`\\}' here. If you typed, e.g., `{' instead of `\\{', you",
"should probably delete the `{' by typing `1' now, so that",
"braces don't get unbalanced. Otherwise just proceed.",
"Acceptable delimiters are characters whose \\delcode is",
"nonnegative, or you can use `\\delimiter <delimiter code>'.");
back_error();cur_val= 0;
}

/*:1160*/
#line 22736 "texprof.w"
;
small_fam(p)= (cur_val/04000000)%16;
small_char(p)= qi((cur_val/010000)%256);
large_fam(p)= (cur_val/256)%16;
large_char(p)= qi(cur_val%256);
}

/*:1159*//*1162:*/
#line 22758 "texprof.w"

static void math_radical(void)
{tail_append(get_node(radical_noad_size));
type(tail)= radical_noad;subtype(tail)= normal;
mem[nucleus(tail)].hh= empty_field;
mem[subscr(tail)].hh= empty_field;
mem[supscr(tail)].hh= empty_field;
scan_delimiter(left_delimiter(tail),true);scan_math(nucleus(tail));
}

/*:1162*//*1164:*/
#line 22771 "texprof.w"

static void math_ac(void)
{if(cur_cmd==accent)
/*1165:*/
#line 22788 "texprof.w"

{print_err("Please use ");print_esc("mathaccent");
print(" for accents in math mode");

help2("I'm changing \\accent to \\mathaccent here; wish me luck.",
"(Accents are not the same in formulas as they are in text.)");
error();
}

/*:1165*/
#line 22774 "texprof.w"
;
tail_append(get_node(accent_noad_size));
type(tail)= accent_noad;subtype(tail)= normal;
mem[nucleus(tail)].hh= empty_field;
mem[subscr(tail)].hh= empty_field;
mem[supscr(tail)].hh= empty_field;
math_type(accent_chr(tail))= math_char;
scan_fifteen_bit_int();
character(accent_chr(tail))= qi(cur_val%256);
if((cur_val>=var_code)&&fam_in_range)fam(accent_chr(tail))= cur_fam;
else fam(accent_chr(tail))= (cur_val/256)%16;
scan_math(nucleus(tail));
}

/*:1164*//*1171:*/
#line 22835 "texprof.w"

static void append_choices(void)
{tail_append(new_choice());incr(save_ptr);saved(-1)= 0;
push_math(math_choice_group);scan_left_brace();
}

/*:1171*//*1173:*/
#line 22844 "texprof.w"

/*1183:*/
#line 22989 "texprof.w"

static pointer fin_mlist(pointer p)
{pointer q;
if(incompleat_noad!=null)/*1184:*/
#line 22998 "texprof.w"

{math_type(denominator(incompleat_noad))= sub_mlist;
info(denominator(incompleat_noad))= link(head);
if(p==null)q= incompleat_noad;
else{q= info(numerator(incompleat_noad));
if((type(q)!=left_noad)||(delim_ptr==null))confusion("right");

info(numerator(incompleat_noad))= link(delim_ptr);
link(delim_ptr)= incompleat_noad;link(incompleat_noad)= p;
}
}

/*:1184*/
#line 22992 "texprof.w"

else{link(tail)= p;q= link(head);
}
pop_nest();return q;
}

/*:1183*/
#line 22845 "texprof.w"

static void build_choices(void)
{
pointer p;
unsave();p= fin_mlist(null);
switch(saved(-1)){
case 0:display_mlist(tail)= p;break;
case 1:text_mlist(tail)= p;break;
case 2:script_mlist(tail)= p;break;
case 3:{script_script_mlist(tail)= p;decr(save_ptr);return;
}
}
incr(saved(-1));push_math(math_choice_group);scan_left_brace();
}

/*:1173*//*1175:*/
#line 22868 "texprof.w"

static void sub_sup(void)
{small_number t;
pointer p;
t= empty;p= null;
if(tail!=head)if(scripts_allowed(tail))
{p= supscr(tail)+cur_cmd-sup_mark;
t= math_type(p);
}
if((p==null)||(t!=empty))/*1176:*/
#line 22881 "texprof.w"

{tail_append(new_noad());
p= supscr(tail)+cur_cmd-sup_mark;
if(t!=empty)
{if(cur_cmd==sup_mark)
{print_err("Double superscript");

help1("I treat `x^1^2' essentially like `x^1{}^2'.");
}
else{print_err("Double subscript");

help1("I treat `x_1_2' essentially like `x_1{}_2'.");
}
error();
}
}

/*:1176*/
#line 22877 "texprof.w"
;
scan_math(p);
}

/*:1175*//*1180:*/
#line 22938 "texprof.w"

static void math_fraction(void)
{small_number c;
c= cur_chr;
if(incompleat_noad!=null)
/*1182:*/
#line 22970 "texprof.w"

{if(c>=delimited_code)
{scan_delimiter(garbage,false);scan_delimiter(garbage,false);
}
if(c%delimited_code==above_code)scan_normal_dimen;
print_err("Ambiguous; you need another { and }");

help3("I'm ignoring this fraction specification, since I don't",
"know whether a construction like `x \\over y \\over z'",
"means `{x \\over y} \\over z' or `x \\over {y \\over z}'.");
error();
}

/*:1182*/
#line 22943 "texprof.w"

else{incompleat_noad= get_node(fraction_noad_size);
type(incompleat_noad)= fraction_noad;
subtype(incompleat_noad)= normal;
math_type(numerator(incompleat_noad))= sub_mlist;
info(numerator(incompleat_noad))= link(head);
mem[denominator(incompleat_noad)].hh= empty_field;
mem[left_delimiter(incompleat_noad)].qqqq= null_delimiter;
mem[right_delimiter(incompleat_noad)].qqqq= null_delimiter;
link(head)= null;tail= head;
/*1181:*/
#line 22957 "texprof.w"

if(c>=delimited_code)
{scan_delimiter(left_delimiter(incompleat_noad),false);
scan_delimiter(right_delimiter(incompleat_noad),false);
}
switch(c%delimited_code){
case above_code:{scan_normal_dimen;
thickness(incompleat_noad)= cur_val;
}break;
case over_code:thickness(incompleat_noad)= default_code;break;
case atop_code:thickness(incompleat_noad)= 0;
}

/*:1181*/
#line 22953 "texprof.w"
;
}
}

/*:1180*//*1190:*/
#line 23054 "texprof.w"

static void math_left_right(void)
{small_number t;
pointer p;
pointer q;
t= cur_chr;
if((t!=left_noad)&&(cur_group!=math_left_group))
/*1191:*/
#line 23082 "texprof.w"

{if(cur_group==math_shift_group)
{scan_delimiter(garbage,false);
print_err("Extra ");
if(t==middle_noad)
{print_esc("middle");

help1("I'm ignoring a \\middle that had no matching \\left.");
}
else{print_esc("right");

help1("I'm ignoring a \\right that had no matching \\left.");
}
error();
}
else off_save();
}

/*:1191*/
#line 23061 "texprof.w"

else{p= new_noad();type(p)= t;
scan_delimiter(delimiter(p),false);
if(t==middle_noad)
{type(p)= right_noad;subtype(p)= middle_noad;
}
if(t==left_noad)q= p;
else{q= fin_mlist(p);unsave();
}
if(t!=right_noad)
{push_math(math_left_group);link(head)= q;tail= p;
delim_ptr= p;
}
else{
tail_append(new_noad());type(tail)= inner_noad;
math_type(nucleus(tail))= sub_mlist;
info(nucleus(tail))= q;
}
}
}

/*:1190*//*1193:*/
#line 23106 "texprof.w"

static void after_math(void)
{bool l;
bool danger;
int m;
pointer p;
pointer a;
/*1197:*/
#line 23190 "texprof.w"

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

/*:1197*/
#line 23113 "texprof.w"

danger= false;
/*1194:*/
#line 23136 "texprof.w"

if((font_params[fam_fnt(2+text_size)]<total_mathsy_params)||
(font_params[fam_fnt(2+script_size)]<total_mathsy_params)||
(font_params[fam_fnt(2+script_script_size)]<total_mathsy_params))
{print_err("Math formula deleted: Insufficient symbol fonts");

help3("Sorry, but I can't typeset math unless \\textfont 2",
"and \\scriptfont 2 and \\scriptscriptfont 2 have all",
"the \\fontdimen values needed in math symbol fonts.");
error();flush_math();danger= true;
}
else if((font_params[fam_fnt(3+text_size)]<total_mathex_params)||
(font_params[fam_fnt(3+script_size)]<total_mathex_params)||
(font_params[fam_fnt(3+script_script_size)]<total_mathex_params))
{print_err("Math formula deleted: Insufficient extension fonts");
help3("Sorry, but I can't typeset math unless \\textfont 3",
"and \\scriptfont 3 and \\scriptscriptfont 3 have all",
"the \\fontdimen values needed in math extension fonts.");
error();flush_math();danger= true;
}

/*:1194*/
#line 23116 "texprof.w"
;
m= mode;l= false;p= fin_mlist(null);
if(mode==-m)
{/*1196:*/
#line 23175 "texprof.w"

{get_x_token();
if(cur_cmd!=math_shift)
{print_err("Display math should end with $$");

help2("The `$' that I just saw supposedly matches a previous `$$'.",
"So I shall assume that you typed `$$' both times.");
back_error();
}
}

/*:1196*/
#line 23119 "texprof.w"
;
cur_mlist= p;cur_style= text_style;mlist_penalties= false;
mlist_to_hlist();a= hpack(link(temp_head),natural);
unsave();decr(save_ptr);
if(saved(0)==1)l= true;
danger= false;
/*1194:*/
#line 23136 "texprof.w"

if((font_params[fam_fnt(2+text_size)]<total_mathsy_params)||
(font_params[fam_fnt(2+script_size)]<total_mathsy_params)||
(font_params[fam_fnt(2+script_script_size)]<total_mathsy_params))
{print_err("Math formula deleted: Insufficient symbol fonts");

help3("Sorry, but I can't typeset math unless \\textfont 2",
"and \\scriptfont 2 and \\scriptscriptfont 2 have all",
"the \\fontdimen values needed in math symbol fonts.");
error();flush_math();danger= true;
}
else if((font_params[fam_fnt(3+text_size)]<total_mathex_params)||
(font_params[fam_fnt(3+script_size)]<total_mathex_params)||
(font_params[fam_fnt(3+script_script_size)]<total_mathex_params))
{print_err("Math formula deleted: Insufficient extension fonts");
help3("Sorry, but I can't typeset math unless \\textfont 3",
"and \\scriptfont 3 and \\scriptscriptfont 3 have all",
"the \\fontdimen values needed in math extension fonts.");
error();flush_math();danger= true;
}

/*:1194*/
#line 23126 "texprof.w"
;
m= mode;p= fin_mlist(null);
}
else a= null;
if(m<0)/*1195:*/
#line 23163 "texprof.w"

{tail_append(new_math(math_surround,before));
cur_mlist= p;cur_style= text_style;mlist_penalties= (mode> 0);mlist_to_hlist();
link(tail)= link(temp_head);
while(link(tail)!=null)tail= link(tail);
tail_append(new_math(math_surround,after));
space_factor= 1000;unsave();
}

/*:1195*/
#line 23130 "texprof.w"

else{if(a==null)/*1196:*/
#line 23175 "texprof.w"

{get_x_token();
if(cur_cmd!=math_shift)
{print_err("Display math should end with $$");

help2("The `$' that I just saw supposedly matches a previous `$$'.",
"So I shall assume that you typed `$$' both times.");
back_error();
}
}

/*:1196*/
#line 23131 "texprof.w"
;
/*1198:*/
#line 23206 "texprof.w"

cur_mlist= p;cur_style= display_style;mlist_penalties= false;
mlist_to_hlist();p= link(temp_head);
adjust_tail= adjust_head;b= hpack(p,natural);p= list_ptr(b);
t= adjust_tail;adjust_tail= null;
w= width(b);z= display_width;s= display_indent;
if((a==null)||danger)
{e= 0;q= 0;
}
else{e= width(a);q= e+math_quad(text_size);
}
if(w+q> z)
/*1200:*/
#line 23242 "texprof.w"

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

/*:1200*/
#line 23219 "texprof.w"
;
/*1201:*/
#line 23266 "texprof.w"

d= half(z-w);
if((e> 0)&&(d<2*e))
{d= half(z-w-e);
if(p!=null)if(!is_char_node(p))if(type(p)==glue_node)d= 0;
}

/*:1201*/
#line 23221 "texprof.w"
;
/*1202:*/
#line 23279 "texprof.w"

tail_append(new_penalty(pre_display_penalty));
if((d+s<=pre_display_size)||l)
{g1= above_display_skip_code;g2= below_display_skip_code;
}
else{g1= above_display_short_skip_code;
g2= below_display_short_skip_code;
}
if(l&&(e==0))
{shift_amount(a)= s;append_to_vlist(a);
tail_append(new_penalty(inf_penalty));
}
else tail_append(new_param_glue(g1))

/*:1202*/
#line 23222 "texprof.w"
;
/*1203:*/
#line 23293 "texprof.w"

if(e!=0)
{r= new_kern(z-w-e-d);
if(l)
{link(a)= r;link(r)= b;b= a;d= 0;
}
else{link(b)= r;link(r)= a;
}
b= hpack(b,natural);
}
shift_amount(b)= s+d;append_to_vlist(b)

/*:1203*/
#line 23223 "texprof.w"
;
/*1204:*/
#line 23305 "texprof.w"

if((a!=null)&&(e==0)&&!l)
{tail_append(new_penalty(inf_penalty));
shift_amount(a)= s+z-width(a);
append_to_vlist(a);
g2= 0;
}
if(t!=adjust_head)
{link(tail)= link(adjust_head);tail= t;
}
tail_append(new_penalty(post_display_penalty));
if(g2> 0)tail_append(new_param_glue(g2))

/*:1204*/
#line 23224 "texprof.w"
;
resume_after_display()

/*:1198*/
#line 23132 "texprof.w"
;
}
}

/*:1193*//*1199:*/
#line 23227 "texprof.w"

static void resume_after_display(void)
{if(cur_group!=math_shift_group)confusion("display");

unsave();prev_graf= prev_graf+3;
push_nest();mode= hmode;space_factor= 1000;set_cur_lang;clang= cur_lang;
prev_graf= (norm_min(left_hyphen_min)*0100+norm_min(right_hyphen_min))
*0200000+cur_lang;
/*442:*/
#line 9230 "texprof.w"

{get_x_token();if(cur_cmd!=spacer)back_input();
}

/*:442*/
#line 23235 "texprof.w"
;
if(nest_ptr==1)build_page();
}

/*:1199*//*1210:*/
#line 23426 "texprof.w"

/*1214:*/
#line 23504 "texprof.w"

static void get_r_token(void)
{
restart:do{get_token();
}while(!(cur_tok!=space_token));
if((cur_cs==0)||(cur_cs> frozen_control_sequence))
{print_err("Missing control sequence inserted");

help5("Please don't say `\\def cs{...}', say `\\def\\cs{...}'.",
"I've inserted an inaccessible control sequence so that your",
"definition will be completed without mixing me up too badly.",
"You can recover graciously from this error, if you're",
"careful; see exercise 27.2 in The TeXbook.");

if(cur_cs==0)back_input();
cur_tok= cs_token_flag+frozen_protection;ins_error();goto restart;
}
}

/*:1214*//*1228:*/
#line 23751 "texprof.w"

static void trap_zero_glue(void)
{if((width(cur_val)==0)&&(stretch(cur_val)==0)&&(shrink(cur_val)==0))
{add_glue_ref(zero_glue);
delete_glue_ref(cur_val);cur_val= zero_glue;
}
}

/*:1228*//*1235:*/
#line 23832 "texprof.w"

static void do_register_command(small_number a)
{
pointer l,q,r,s;
int p;
bool e;
int w;
q= cur_cmd;
e= false;
/*1236:*/
#line 23864 "texprof.w"

{if(q!=internal_register)
{get_x_token();
if((cur_cmd>=assign_int)&&(cur_cmd<=assign_mu_glue))
{l= cur_chr;p= cur_cmd-assign_int;goto found;
}
if(cur_cmd!=internal_register)
{print_err("You can't use `");print_cmd_chr(cur_cmd,cur_chr);

print("' after ");print_cmd_chr(q,0);
help1("I'm forgetting what you said and not changing anything.");
error();return;
}
}
if((cur_chr<mem_bot)||(cur_chr> lo_mem_stat_max))
{l= cur_chr;p= sa_type(l);e= true;
}
else{p= cur_chr-mem_bot;scan_register_num();
if(cur_val> 255)
{find_sa_element(p,cur_val,true);l= cur_ptr;e= true;
}
else
switch(p){
case int_val:l= cur_val+count_base;break;
case dimen_val:l= cur_val+scaled_base;break;
case glue_val:l= cur_val+skip_base;break;
case mu_val:l= cur_val+mu_skip_base;
}
}
}
found:if(p<glue_val)if(e)w= sa_int(l);else w= eqtb[l].i;
else if(e)s= sa_ptr(l);else s= equiv(l)

/*:1236*/
#line 23841 "texprof.w"
;
if(q==internal_register)scan_optional_equals();
else if(scan_keyword("by"))do_nothing;

arith_error= false;
if(q<multiply)/*1237:*/
#line 23897 "texprof.w"

if(p<glue_val)
{if(p==int_val)scan_int();else scan_normal_dimen;
if(q==advance)cur_val= cur_val+w;
}
else{scan_glue(p);
if(q==advance)/*1238:*/
#line 23906 "texprof.w"

{q= new_spec(cur_val);r= s;
delete_glue_ref(cur_val);
width(q)= width(q)+width(r);
if(stretch(q)==0)stretch_order(q)= normal;
if(stretch_order(q)==stretch_order(r))stretch(q)= stretch(q)+stretch(r);
else if((stretch_order(q)<stretch_order(r))&&(stretch(r)!=0))
{stretch(q)= stretch(r);stretch_order(q)= stretch_order(r);
}
if(shrink(q)==0)shrink_order(q)= normal;
if(shrink_order(q)==shrink_order(r))shrink(q)= shrink(q)+shrink(r);
else if((shrink_order(q)<shrink_order(r))&&(shrink(r)!=0))
{shrink(q)= shrink(r);shrink_order(q)= shrink_order(r);
}
cur_val= q;
}

/*:1238*/
#line 23903 "texprof.w"
;
}

/*:1237*/
#line 23846 "texprof.w"

else/*1239:*/
#line 23923 "texprof.w"

{scan_int();
if(p<glue_val)
if(q==multiply)
if(p==int_val)cur_val= mult_integers(w,cur_val);
else cur_val= nx_plus_y(w,cur_val,0);
else cur_val= x_over_n(w,cur_val);
else{r= new_spec(s);
if(q==multiply)
{width(r)= nx_plus_y(width(s),cur_val,0);
stretch(r)= nx_plus_y(stretch(s),cur_val,0);
shrink(r)= nx_plus_y(shrink(s),cur_val,0);
}
else{width(r)= x_over_n(width(s),cur_val);
stretch(r)= x_over_n(stretch(s),cur_val);
shrink(r)= x_over_n(shrink(s),cur_val);
}
cur_val= r;
}
}

/*:1239*/
#line 23847 "texprof.w"
;
if(arith_error)
{print_err("Arithmetic overflow");

help2("I can't carry out that multiplication or division,",
"since the result is out of range.");
if(p>=glue_val)delete_glue_ref(cur_val);
error();return;
}
if(p<glue_val)sa_word_define(l,cur_val);
else{trap_zero_glue();sa_define(l,cur_val,l,glue_ref,cur_val);
}
}

/*:1235*//*1242:*/
#line 23975 "texprof.w"

static void alter_aux(void)
{halfword c;
if(cur_chr!=abs(mode))report_illegal_case();
else{c= cur_chr;scan_optional_equals();
if(c==vmode)
{scan_normal_dimen;prev_depth= cur_val;
}
else{scan_int();
if((cur_val<=0)||(cur_val> 32767))
{print_err("Bad space factor");

help1("I allow only values in the range 1..32767 here.");
int_error(cur_val);
}
else space_factor= cur_val;
}
}
}

/*:1242*//*1243:*/
#line 23995 "texprof.w"

static void alter_prev_graf(void)
{int p;
nest[nest_ptr]= cur_list;p= nest_ptr;
while(abs(nest[p].mode_field)!=vmode)decr(p);
scan_optional_equals();scan_int();
if(cur_val<0)
{print_err("Bad ");print_esc("prevgraf");

help1("I allow only nonnegative values here.");
int_error(cur_val);
}
else{nest[p].pg_field= cur_val;cur_list= nest[nest_ptr];
}
}

/*:1243*//*1244:*/
#line 24011 "texprof.w"

static void alter_page_so_far(void)
{int c;
c= cur_chr;scan_optional_equals();scan_normal_dimen;
page_so_far[c]= cur_val;
}

/*:1244*//*1245:*/
#line 24018 "texprof.w"

static void alter_integer(void)
{small_number c;

c= cur_chr;scan_optional_equals();scan_int();
if(c==0)dead_cycles= cur_val
/*1426:*/
#line 26432 "texprof.w"
;
else if(c==2)
{if((cur_val<batch_mode)||(cur_val> error_stop_mode))
{print_err("Bad interaction mode");

help2("Modes are 0=batch, 1=nonstop, 2=scroll, and",
"3=errorstop. Proceed, and I'll ignore this case.");
int_error(cur_val);
}
else{cur_chr= cur_val;new_interaction();
}
}

/*:1426*/
#line 24024 "texprof.w"

else insert_penalties= cur_val;
}

/*:1245*//*1246:*/
#line 24028 "texprof.w"

static void alter_box_dimen(void)
{small_number c;
pointer b;
c= cur_chr;scan_register_num();fetch_box(b);scan_optional_equals();
scan_normal_dimen;
if(b!=null)mem[b+c].sc= cur_val;
}

/*:1246*//*1256:*/
#line 24122 "texprof.w"

static void new_font(small_number a)
{
pointer u;
scaled s;
int f;
str_number t;
int old_setting;
str_number flushable_string;
if(job_name==0)open_log_file();


get_r_token();u= cur_cs;
if(u>=hash_base)t= text(u);
else if(u>=single_base)
if(u==null_cs)t= s_no("FONT");else t= u-single_base;
else{old_setting= selector;selector= new_string;
print("FONT");printn(u-active_base);selector= old_setting;

str_room(1);t= make_string();
}
define(u,set_font,null_font);scan_optional_equals();scan_file_name();
/*1257:*/
#line 24151 "texprof.w"

name_in_progress= true;
if(scan_keyword("at"))/*1258:*/
#line 24168 "texprof.w"

{scan_normal_dimen;s= cur_val;
if((s<=0)||(s>=01000000000))
{print_err("Improper `at' size (");
print_scaled(s);print("pt), replaced by 10pt");

help2("I can only handle fonts at positive sizes that are",
"less than 2048pt, so I've changed what you said to 10pt.");
error();s= 10*unity;
}
}

/*:1258*/
#line 24153 "texprof.w"


else if(scan_keyword("scaled"))

{scan_int();s= -cur_val;
if((cur_val<=0)||(cur_val> 32768))
{print_err("Illegal magnification has been changed to 1000");

help1("The magnification ratio must be between 1 and 32768.");
int_error(cur_val);s= -1000;
}
}
else s= -1000;
name_in_progress= false

/*:1257*/
#line 24144 "texprof.w"
;
/*1259:*/
#line 24184 "texprof.w"

flushable_string= str_ptr-1;
for(f= font_base+1;f<=font_ptr;f++)
if(str_eq_str(font_name[f],cur_name)&&str_eq_str(font_area[f],cur_area))
{if(cur_name==flushable_string)
{flush_string;cur_name= font_name[f];
}
if(s> 0)
{if(s==font_size[f])goto common_ending;
}
else if(font_size[f]==xn_over_d(font_dsize[f],-s,1000))
goto common_ending;
}

/*:1259*/
#line 24146 "texprof.w"
;
f= read_font_info(u,cur_name,cur_area,s);
common_ending:define(u,set_font,f);eqtb[font_id_base+f]= eqtb[u];font_id_text(f)= t;
}

/*:1256*//*1264:*/
#line 24227 "texprof.w"

static void new_interaction(void)
{print_ln();
interaction= cur_chr;
/*74:*/
#line 1816 "texprof.w"

if(interaction==batch_mode)selector= no_print;else selector= term_only

/*:74*/
#line 24231 "texprof.w"
;
if(log_opened)selector= selector+2;
}

/*:1264*/
#line 23427 "texprof.w"

static void prefixed_command(void)
{
small_number a;
internal_font_number f;
int j;
font_index k;
pointer p,q;
int n;
bool e;
a= 0;
while(cur_cmd==prefix)
{if(!odd(a/cur_chr))a= a+cur_chr;
/*403:*/
#line 8617 "texprof.w"

do{get_x_token();
}while(!((cur_cmd!=spacer)&&(cur_cmd!=relax)))

/*:403*/
#line 23440 "texprof.w"
;
if(cur_cmd<=max_non_prefixed_command)
/*1211:*/
#line 23455 "texprof.w"

{print_err("You can't use a prefix with `");

print_cmd_chr(cur_cmd,cur_chr);print_char('\'');
help1("I'll pretend you didn't say \\long or \\outer or \\global.");
if(eTeX_ex)help_line[0]= 
"I'll pretend you didn't say \\long or \\outer or \\global or \\protected.";
back_error();return;
}

/*:1211*/
#line 23442 "texprof.w"
;
if(tracing_commands> 2)if(eTeX_ex)show_cur_cmd_chr();
}
/*1212:*/
#line 23465 "texprof.w"

if(a>=8)
{j= protected_token;a= a-8;
}
else j= 0;
if((cur_cmd!=def)&&((a%4!=0)||(j!=0)))
{print_err("You can't use `");print_esc("long");print("' or `");
print_esc("outer");
help1("I'll pretend you didn't say \\long or \\outer here.");
if(eTeX_ex)
{help_line[0]= 
"I'll pretend you didn't say \\long or \\outer or \\protected here.";
print("' or `");print_esc("protected");
}
print("' with `");

print_cmd_chr(cur_cmd,cur_chr);print_char('\'');
error();
}

/*:1212*/
#line 23445 "texprof.w"
;
/*1213:*/
#line 23492 "texprof.w"

if(global_defs!=0)
if(global_defs<0)
{if(global)a= a-4;
}
else{if(!global)a= a+4;
}

/*:1213*/
#line 23446 "texprof.w"
;
switch(cur_cmd){
/*1216:*/
#line 23530 "texprof.w"

case set_font:define(cur_font_loc,data,cur_chr);break;

/*:1216*//*1217:*/
#line 23537 "texprof.w"

case def:{uint32_t def_fl;
if(odd(cur_chr)&&!global&&(global_defs>=0))a= a+4;
e= (cur_chr>=2);get_r_token();p= cur_cs;def_fl= cur_file_line;
q= scan_toks(true,e);
if(j!=0)
{q= get_avail();info(q)= j;link(q)= link(def_ref);
link(def_ref)= q;
}
define(p,call+(a%4),def_ref);
fl_mem[def_ref]= def_fl;
}break;

/*:1217*//*1220:*/
#line 23561 "texprof.w"

case let:{n= cur_chr;
get_r_token();p= cur_cs;
if(n==normal)
{do{get_token();
}while(!(cur_cmd!=spacer));
if(cur_tok==other_token+'=')
{get_token();
if(cur_cmd==spacer)get_token();
}
}
else{get_token();q= cur_tok;get_token();back_input();
cur_tok= q;back_input();
}
if(cur_cmd>=call)add_token_ref(cur_chr);
else if((cur_cmd==internal_register)||(cur_cmd==toks_register))
if((cur_chr<mem_bot)||(cur_chr> lo_mem_stat_max))
add_sa_ref(cur_chr);
define(p,cur_cmd,cur_chr);
}break;

/*:1220*//*1223:*/
#line 23633 "texprof.w"

case shorthand_def:{n= cur_chr;get_r_token();p= cur_cs;define(p,relax,256);
scan_optional_equals();
switch(n){
case char_def_code:{scan_char_num();define(p,char_given,cur_val);
}break;
case math_char_def_code:{scan_fifteen_bit_int();define(p,math_given,cur_val);
}break;
default:{scan_register_num();
if(cur_val> 255)
{j= n-count_def_code;
if(j> mu_val)j= tok_val;
find_sa_element(j,cur_val,true);add_sa_ref(cur_ptr);
if(j==tok_val)j= toks_register;else j= internal_register;
define(p,j,cur_ptr);
}
else
switch(n){
case count_def_code:define(p,assign_int,count_base+cur_val);break;
case dimen_def_code:define(p,assign_dimen,scaled_base+cur_val);break;
case skip_def_code:define(p,assign_glue,skip_base+cur_val);break;
case mu_skip_def_code:define(p,assign_mu_glue,mu_skip_base+cur_val);break;
case toks_def_code:define(p,assign_toks,toks_base+cur_val);
}
}
}
}break;

/*:1223*//*1224:*/
#line 23661 "texprof.w"

case read_to_cs:{j= cur_chr;scan_int();n= cur_val;
if(!scan_keyword("to"))

{print_err("Missing `to' inserted");

help2("You should have said `\\read<number> to \\cs'.",
"I'm going to look for the \\cs now.");error();
}
get_r_token();
p= cur_cs;read_toks(n,p,j);define(p,call,cur_val);
}break;

/*:1224*//*1225:*/
#line 23678 "texprof.w"

case toks_register:case assign_toks:{uint32_t def_fl= cur_file_line;q= cur_cs;
e= false;
if(cur_cmd==toks_register)
if(cur_chr==mem_bot)
{scan_register_num();
if(cur_val> 255)
{find_sa_element(tok_val,cur_val,true);
cur_chr= cur_ptr;e= true;
}
else cur_chr= toks_base+cur_val;
}
else e= true;
p= cur_chr;
scan_optional_equals();
/*403:*/
#line 8617 "texprof.w"

do{get_x_token();
}while(!((cur_cmd!=spacer)&&(cur_cmd!=relax)))

/*:403*/
#line 23693 "texprof.w"
;
if(cur_cmd!=left_brace)/*1226:*/
#line 23713 "texprof.w"

if((cur_cmd==toks_register)||(cur_cmd==assign_toks))
{if(cur_cmd==toks_register)
if(cur_chr==mem_bot)
{scan_register_num();
if(cur_val<256)q= equiv(toks_base+cur_val);
else{find_sa_element(tok_val,cur_val,false);
if(cur_ptr==null)q= null;
else q= sa_ptr(cur_ptr);
}
}
else q= sa_ptr(cur_chr);
else q= equiv(cur_chr);
if(q==null)sa_define(p,null,p,undefined_cs,null);
else{add_token_ref(q);sa_define(p,q,p,call,q);
}
goto done;
}

/*:1226*/
#line 23695 "texprof.w"
;
back_input();cur_cs= q;q= scan_toks(false,false);
if(link(def_ref)==null)
{sa_define(p,null,p,undefined_cs,null);free_avail(def_ref);
}
else{if((p==output_routine_loc)&&!e)
{link(q)= get_avail();q= link(q);
info(q)= right_brace_token+'}';
fl_mem[q]= FILE_LINE(system_file,system_insert);
q= get_avail();info(q)= left_brace_token+'{';
fl_mem[q]= FILE_LINE(system_file,system_insert);
link(q)= link(def_ref);link(def_ref)= q;
}
sa_define(p,def_ref,p,call,def_ref);
fl_mem[def_ref]= def_fl;
}
}break;

/*:1225*//*1227:*/
#line 23734 "texprof.w"

case assign_int:{p= cur_chr;scan_optional_equals();scan_int();
word_define(p,cur_val);
}break;
case assign_dimen:{p= cur_chr;scan_optional_equals();
scan_normal_dimen;word_define(p,cur_val);
}break;
case assign_glue:case assign_mu_glue:{p= cur_chr;n= cur_cmd;scan_optional_equals();
if(n==assign_mu_glue)scan_glue(mu_val);else scan_glue(glue_val);
trap_zero_glue();
define(p,glue_ref,cur_val);
}break;

/*:1227*//*1231:*/
#line 23794 "texprof.w"

case def_code:{/*1232:*/
#line 23812 "texprof.w"

if(cur_chr==cat_code_base)n= max_char_code;
else if(cur_chr==math_code_base)n= 0100000;
else if(cur_chr==sf_code_base)n= 077777;
else if(cur_chr==del_code_base)n= 077777777;
else n= 255

/*:1232*/
#line 23795 "texprof.w"
;
p= cur_chr;scan_char_num();p= p+cur_val;scan_optional_equals();
scan_int();
if(((cur_val<0)&&(p<del_code_base))||(cur_val> n))
{print_err("Invalid code (");print_int(cur_val);

if(p<del_code_base)print("), should be in the range 0..");
else print("), should be at most ");
print_int(n);
help1("I'm going to use 0 instead of that illegal code value.");
error();cur_val= 0;
}
if(p<math_code_base)define(p,data,cur_val);
else if(p<del_code_base)define(p,data,hi(cur_val));
else word_define(p,cur_val);
}break;

/*:1231*//*1233:*/
#line 23819 "texprof.w"

case def_family:{p= cur_chr;scan_four_bit_int();p= p+cur_val;
scan_optional_equals();scan_font_ident();define(p,data,cur_val);
}break;

/*:1233*//*1234:*/
#line 23826 "texprof.w"

case internal_register:case advance:
case multiply:case divide:do_register_command(a);break;

/*:1234*//*1240:*/
#line 23948 "texprof.w"

case set_box:{scan_register_num();
if(global)n= global_box_flag+cur_val;else n= box_flag+cur_val;
scan_optional_equals();
if(set_box_allowed)scan_box(n);
else{print_err("Improper ");print_esc("setbox");

help2("Sorry, \\setbox is not allowed after \\halign in a display,",
"or between \\accent and an accented character.");error();
}
}break;

/*:1240*//*1241:*/
#line 23968 "texprof.w"

case set_aux:alter_aux();break;
case set_prev_graf:alter_prev_graf();break;
case set_page_dimen:alter_page_so_far();break;
case set_page_int:alter_integer();break;
case set_box_dimen:alter_box_dimen();break;

/*:1241*//*1247:*/
#line 24039 "texprof.w"

case set_shape:{q= cur_chr;scan_optional_equals();scan_int();n= cur_val;
if(n<=0)p= null;
else if(q> par_shape_loc)
{n= (cur_val/2)+1;p= get_node(2*n+1);info(p)= n;
n= cur_val;mem[p+1].i= n;
for(j= p+2;j<=p+n+1;j++)
{scan_int();mem[j].i= cur_val;
}
if(!odd(n))mem[p+n+2].i= 0;
}
else{p= get_node(2*n+1);info(p)= n;
for(j= 1;j<=n;j++)
{scan_normal_dimen;
mem[p+2*j-1].sc= cur_val;
scan_normal_dimen;
mem[p+2*j].sc= cur_val;
}
}
define(q,shape_ref,p);
}break;

/*:1247*//*1251:*/
#line 24080 "texprof.w"

case hyph_data:if(cur_chr==1)
{
#ifdef INIT
new_patterns();goto done;
#endif
#line 24086 "texprof.w"
 print_err("Patterns can be loaded only by INITEX");

help0;error();
do{get_token();}while(!(cur_cmd==right_brace));
return;
}
else{new_hyph_exceptions();goto done;
}break;

/*:1251*//*1252:*/
#line 24098 "texprof.w"

case assign_font_dimen:{find_font_dimen(true);k= cur_val;
scan_optional_equals();scan_normal_dimen;font_info[k].sc= cur_val;
}break;
case assign_font_int:{n= cur_chr;scan_font_ident();f= cur_val;
scan_optional_equals();scan_int();
if(n==0)hyphen_char[f]= cur_val;else skew_char[f]= cur_val;
}break;

/*:1252*//*1255:*/
#line 24119 "texprof.w"

case def_font:new_font(a);break;

/*:1255*//*1263:*/
#line 24224 "texprof.w"

case set_interaction:new_interaction();break;

/*:1263*/
#line 23448 "texprof.w"

default:confusion("prefix");

}
done:/*1268:*/
#line 24249 "texprof.w"

if(after_token!=0)
{cur_tok= after_token;back_input();after_token= 0;
}

/*:1268*/
#line 23452 "texprof.w"
;
}

/*:1210*//*1269:*/
#line 24257 "texprof.w"

static void do_assignments(void)
{
loop{/*403:*/
#line 8617 "texprof.w"

do{get_x_token();
}while(!((cur_cmd!=spacer)&&(cur_cmd!=relax)))

/*:403*/
#line 24260 "texprof.w"
;
if(cur_cmd<=max_non_prefixed_command)return;
set_box_allowed= false;prefixed_command();set_box_allowed= true;
}
}

/*:1269*//*1274:*/
#line 24285 "texprof.w"

static void open_or_close_in(void)
{int c;
int n;
c= cur_chr;scan_four_bit_int();n= cur_val;
if(read_open[n]!=closed)
{a_close(&read_file[n]);read_open[n]= closed;
}
if(c!=0)
{scan_optional_equals();scan_file_name();
pack_cur_name(".tex");
if(a_open_in(&read_file[n]))
{read_open[n]= just_open;
/*1750:*/
#line 31097 "texprof.w"

/*1748:*/
#line 31083 "texprof.w"

if(file_num>=MAX_FILE_NUM)overflow("file number",file_num);
else file_num++;
file_num_name[file_num]= strdup(full_name_of_file);
file_from_cmd[file_num]= cmd_count;

/*:1748*/
#line 31098 "texprof.w"

read_file_num[n]= file_num;

/*:1750*/
#line 24298 "texprof.w"

}
}
}

/*:1274*//*1278:*/
#line 24319 "texprof.w"

static void issue_message(void)
{int old_setting;
int c;
str_number s;
c= cur_chr;link(garbage)= scan_toks(false,true);
old_setting= selector;selector= new_string;
token_show(def_ref);selector= old_setting;
flush_list(def_ref);
str_room(1);s= make_string();
if(c==0)/*1279:*/
#line 24334 "texprof.w"

{if(term_offset+length(s)> max_print_line-2)print_ln();
else if((term_offset> 0)||(file_offset> 0))print_char(' ');
slow_print(s);update_terminal;
}

/*:1279*/
#line 24329 "texprof.w"

else/*1282:*/
#line 24349 "texprof.w"

{print_err("");slow_print(s);
if(err_help!=null)use_err_help= true;
else if(long_help_seen)help1("(That was another \\errmessage.)")
else{if(interaction<error_stop_mode)long_help_seen= true;
help4("This error message was generated by an \\errmessage",
"command, so I can't give any explicit help.",
"Pretend that you're Hercule Poirot: Examine all clues,",

"and deduce the truth by order and method.");
}
error();use_err_help= false;
}

/*:1282*/
#line 24330 "texprof.w"
;
flush_string;
}

/*:1278*//*1287:*/
#line 24386 "texprof.w"

static void shift_case(void)
{pointer b;
pointer p;
halfword t;
eight_bits c;
b= cur_chr;p= scan_toks(false,false);p= link(def_ref);
while(p!=null)
{/*1288:*/
#line 24405 "texprof.w"

t= info(p);
if(t<cs_token_flag+single_base)
{c= t%256;
if(equiv(b+c)!=0)info(p)= t-c+equiv(b+c);
}

/*:1288*/
#line 24394 "texprof.w"
;
p= link(p);
}
back_list(link(def_ref));free_avail(def_ref);
}

/*:1287*//*1292:*/
#line 24442 "texprof.w"

static void show_whatever(void)
{
pointer p;
small_number t;
int m;
int l;
int n;
switch(cur_chr){
case show_lists_code:{begin_diagnostic();show_activities();
}break;
case show_box_code:/*1295:*/
#line 24502 "texprof.w"

{scan_register_num();fetch_box(p);begin_diagnostic();
print_nl("> \\box");print_int(cur_val);print_char('=');
if(p==null)print("void");else show_box(p);
}

/*:1295*/
#line 24453 "texprof.w"
break;
case show_code:/*1293:*/
#line 24479 "texprof.w"

{get_token();
if(interaction==error_stop_mode)wake_up_terminal;
print_nl("> ");
if(cur_cs!=0)
{sprint_cs(cur_cs);print_char('=');
}
print_meaning();goto common_ending;
}

/*:1293*/
#line 24454 "texprof.w"

/*1407:*/
#line 26183 "texprof.w"

case show_groups:{begin_diagnostic();show_save_groups();
}break;

/*:1407*//*1421:*/
#line 26399 "texprof.w"

case show_ifs:{begin_diagnostic();print_nl("");print_ln();
if(cond_ptr==null)
{print_nl("### ");print("no active conditionals");
}
else{p= cond_ptr;n= 0;
do{incr(n);p= link(p);}while(!(p==null));
p= cond_ptr;t= cur_if;l= if_line;m= if_limit;
do{print_nl("### level ");print_int(n);print(": ");
print_cmd_chr(if_test,t);
if(m==fi_code)print_esc("else");
print_if_line(l);
decr(n);t= subtype(p);l= if_line_field(p);m= type(p);p= link(p);
}while(!(p==null));
}
}break;

/*:1421*/
#line 24455 "texprof.w"

default:/*1296:*/
#line 24508 "texprof.w"

{the_toks();
if(interaction==error_stop_mode)wake_up_terminal;
print_nl("> ");token_show(temp_head);
flush_list(link(temp_head));goto common_ending;
}

/*:1296*/
#line 24457 "texprof.w"

}
/*1297:*/
#line 24515 "texprof.w"

end_diagnostic(true);print_err("OK");

if(selector==term_and_log)if(tracing_online<=0)
{selector= term_only;print(" (see the transcript file)");
selector= term_and_log;
}

/*:1297*/
#line 24459 "texprof.w"
;
common_ending:if(interaction<error_stop_mode)
{help0;decr(error_count);
}
else if(tracing_online> 0)
{
help3("This isn't an error message; I'm just \\showing something.",
"Type `I\\show...' to show more (e.g., \\show\\cs,",
"\\showthe\\count10, \\showbox255, \\showlists).");
}
else{
help5("This isn't an error message; I'm just \\showing something.",
"Type `I\\show...' to show more (e.g., \\show\\cs,",
"\\showthe\\count10, \\showbox255, \\showlists).",
"And type `I\\tracingonline=1\\show...' to show boxes and",
"lists on your terminal as well as in the transcript file.");
}
error();
}

/*:1292*//*1301:*/
#line 24551 "texprof.w"

#ifdef INIT
static void store_fmt_file(void)
{
int j,k,l;
int p,q;
int x;
four_quarters w;
/*1303:*/
#line 24612 "texprof.w"

if(save_ptr!=0)
{print_err("You can't dump inside a group");

help1("`{...\\dump}' is a no-no.");succumb;
}

/*:1303*/
#line 24559 "texprof.w"
;
/*1327:*/
#line 25021 "texprof.w"

selector= new_string;
print(" (preloaded format=");printn(job_name);print_char(' ');
print_int(year);print_char('.');
print_int(month);print_char('.');print_int(day);print_char(')');
if(interaction==batch_mode)selector= log_only;
else selector= term_and_log;
str_room(1);
format_ident= make_string();
pack_job_name(format_extension);
while(!w_open_out(&fmt_file))
prompt_file_name("format file name",format_extension);
print_nl("Beginning to dump on file ");

slow_print(w_make_name_string(&fmt_file));flush_string;
print_nl("");slow_print(format_ident)

/*:1327*/
#line 24561 "texprof.w"
;
/*1306:*/
#line 24647 "texprof.w"

dump_int(0);
/*1384:*/
#line 25915 "texprof.w"

dump_int(eTeX_mode);
for(j= 0;j<=eTeX_states-1;j++)eTeX_state(j)= 0;

/*:1384*//*1440:*/
#line 26585 "texprof.w"

while(pseudo_files!=null)pseudo_close();

/*:1440*/
#line 24649 "texprof.w"

/*1543:*/
#line 28200 "texprof.w"

dump_int(Prote_mode);

/*:1543*/
#line 24650 "texprof.w"

/*1584:*/
#line 28612 "texprof.w"

for(k= ROM_base;k<=ROM_size;k++)dump_wd(ROM[k]);

/*:1584*/
#line 24651 "texprof.w"

dump_int(mem_bot);
dump_int(mem_top);
dump_int(eqtb_size);
dump_int(hash_prime);
dump_int(hyph_size)

/*:1306*/
#line 24562 "texprof.w"
;
/*1308:*/
#line 24686 "texprof.w"

dump_int(pool_ptr);
dump_int(str_ptr);
for(k= 0;k<=str_ptr;k++)dump_int(str_start[k]);
k= 0;
while(k+4<pool_ptr)
{dump_four_ASCII;k= k+4;
}
k= pool_ptr-4;dump_four_ASCII;
print_ln();print_int(str_ptr);print(" strings of total length ");
print_int(pool_ptr)

/*:1308*/
#line 24563 "texprof.w"
;
/*1310:*/
#line 24721 "texprof.w"

sort_avail();var_used= 0;
dump_int(lo_mem_max);dump_int(rover);
if(eTeX_ex)for(k= int_val;k<=tok_val;k++)dump_int(sa_root[k]);
p= mem_bot;q= rover;x= 0;
do{for(k= p;k<=q+1;k++)dump_wd(mem[k]);
x= x+q+2-p;var_used= var_used+q-p;
p= q+node_size(q);q= rlink(q);
}while(!(q==rover));
var_used= var_used+lo_mem_max-p;dyn_used= mem_end+1-hi_mem_min;
for(k= p;k<=lo_mem_max;k++)dump_wd(mem[k]);
x= x+lo_mem_max+1-p;
dump_int(hi_mem_min);dump_int(avail);
for(k= hi_mem_min;k<=mem_end;k++)dump_wd(mem[k]);
p= avail;
while(p!=null)
{fl_mem[p]= 0;
decr(dyn_used);p= link(p);
}
dump_int(var_used);dump_int(dyn_used);
print_ln();print_int(x);print_char('&');print_int(mem_end+1-hi_mem_min);
print(" memory locations dumped; current usage is ");
print_int(var_used);print_char('&');print_int(dyn_used)

/*:1310*/
#line 24564 "texprof.w"
;
/*1312:*/
#line 24769 "texprof.w"

/*1314:*/
#line 24790 "texprof.w"

k= active_base;
do{j= k;
while(j<int_base-1)
{if((equiv(j)==equiv(j+1))&&(eq_type(j)==eq_type(j+1))&&
(eq_level(j)==eq_level(j+1)))goto found1;
incr(j);
}
l= int_base;goto done1;
found1:incr(j);l= j;
while(j<int_base-1)
{if((equiv(j)!=equiv(j+1))||(eq_type(j)!=eq_type(j+1))||
(eq_level(j)!=eq_level(j+1)))goto done1;
incr(j);
}
done1:dump_int(l-k);
while(k<l)
{dump_wd(eqtb[k]);incr(k);
}
k= j+1;dump_int(k-l);
}while(!(k==int_base))

/*:1314*/
#line 24770 "texprof.w"
;
/*1315:*/
#line 24812 "texprof.w"

do{j= k;
while(j<eqtb_size)
{if(eqtb[j].i==eqtb[j+1].i)goto found2;
incr(j);
}
l= eqtb_size+1;goto done2;
found2:incr(j);l= j;
while(j<eqtb_size)
{if(eqtb[j].i!=eqtb[j+1].i)goto done2;
incr(j);
}
done2:dump_int(l-k);
while(k<l)
{dump_wd(eqtb[k]);incr(k);
}
k= j+1;dump_int(k-l);
}while(!(k> eqtb_size))

/*:1315*/
#line 24771 "texprof.w"
;
dump_int(par_loc);dump_int(write_loc);
dump_int(input_loc);
/*1317:*/
#line 24848 "texprof.w"

dump_int(hash_used);cs_count= frozen_control_sequence-1-hash_used;
for(p= hash_base;p<=hash_used;p++)if(text(p)!=0)
{dump_int(p);dump_hh(hash[p]);incr(cs_count);
}
for(p= hash_used+1;p<=undefined_control_sequence-1;p++)dump_hh(hash[p]);
dump_int(cs_count);
print_ln();print_int(cs_count);print(" multiletter control sequences")

/*:1317*/
#line 24774 "texprof.w"


/*:1312*/
#line 24565 "texprof.w"
;
/*1319:*/
#line 24864 "texprof.w"

dump_int(fmem_ptr);
for(k= 0;k<=fmem_ptr-1;k++)dump_wd(font_info[k]);
dump_int(font_ptr);
for(k= null_font;k<=font_ptr;k++)
/*1321:*/
#line 24881 "texprof.w"

{dump_qqqq(font_check[k]);
dump_int(font_size[k]);
dump_int(font_dsize[k]);
dump_int(font_params[k]);
dump_int(hyphen_char[k]);
dump_int(skew_char[k]);
dump_int(font_name[k]);
dump_int(font_area[k]);
dump_int(font_bc[k]);
dump_int(font_ec[k]);
dump_int(char_base[k]);
dump_int(width_base[k]);
dump_int(height_base[k]);
dump_int(depth_base[k]);
dump_int(italic_base[k]);
dump_int(lig_kern_base[k]);
dump_int(kern_base[k]);
dump_int(exten_base[k]);
dump_int(param_base[k]);
dump_int(font_glue[k]);
dump_int(bchar_label[k]);
dump_int(font_bchar[k]);
dump_int(font_false_bchar[k]);
print_nl("\\font");printn_esc(font_id_text(k));print_char('=');
print_file_name(font_name[k],font_area[k],empty_string);
if(font_size[k]!=font_dsize[k])
{print(" at ");print_scaled(font_size[k]);print("pt");
}
}

/*:1321*/
#line 24869 "texprof.w"
;
print_ln();print_int(fmem_ptr-7);print(" words of font info for ");
print_int(font_ptr-font_base);print(" preloaded font");
if(font_ptr!=font_base+1)print_char('s')

/*:1319*/
#line 24566 "texprof.w"
;
/*1323:*/
#line 24938 "texprof.w"

dump_int(hyph_count);
for(k= 0;k<=hyph_size;k++)if(hyph_word[k]!=0)
{dump_int(k);dump_int(hyph_word[k]);dump_int(hyph_list[k]);
}
print_ln();print_int(hyph_count);print(" hyphenation exception");
if(hyph_count!=1)print_char('s');
if(trie_not_ready)init_trie();
dump_int(trie_max);
dump_int(hyph_start);
for(k= 0;k<=trie_max;k++)dump_hh(trie[k]);
dump_int(trie_op_ptr);
for(k= 1;k<=trie_op_ptr;k++)
{dump_int(hyf_distance[k]);
dump_int(hyf_num[k]);
dump_int(hyf_next[k]);
}
print_nl("Hyphenation trie of length ");print_int(trie_max);

print(" has ");print_int(trie_op_ptr);print(" op");
if(trie_op_ptr!=1)print_char('s');
print(" out of ");print_int(trie_op_size);
for(k= 255;k>=0;k--)if(trie_used[k]> min_quarterword)
{print_nl("  ");print_int(qo(trie_used[k]));
print(" for language ");print_int(k);
dump_int(k);dump_int(qo(trie_used[k]));
}

/*:1323*/
#line 24567 "texprof.w"
;
/*1788:*/
#line 31909 "texprof.w"

{two_halves hw;
int i,j;
hw.rh= file_num;
i= 0;
for(k= 0;k<=file_num;k++)
{j= strlen(file_num_name[k]);
if(j> i)i= j;
}
hw.lh= i;
dump_hh(hw);
}
{memory_word m;
int word_count= 0;
int byte_count= 0;
m.w= 0;
for(k= 0;k<=file_num;k++)
{char*s= file_num_name[k];
do
{m.w= (m.w<<8)|*s;
byte_count++;
if(byte_count==8)
{dump_wd(m);word_count++;
m.w= 0;byte_count= 0;
}
}while(*s++!=0);
}
if(byte_count> 0)
{while(byte_count<8)
{m.w= (m.w<<8)|0;
byte_count++;
}
dump_wd(m);word_count++;
}
print_ln();print_int(file_num);
print(" file names dumped; total size ");print_int(word_count*8);
}

/*:1788*/
#line 24568 "texprof.w"
;
/*1790:*/
#line 31995 "texprof.w"

{int word_count= 0;
k= hi_mem_min;
while(k<=mem_end)
{two_halves hw;
halfword e;
int word_count= 0;
/*1791:*/
#line 32013 "texprof.w"

if(fl_mem[k]!=0)e= fl_mem[k++]|0x80000000;
else
{int i;
i= 1;k++;
while(k<=mem_end&&fl_mem[k]==0)
{i++;k++;}
e= i;
}

/*:1791*/
#line 32002 "texprof.w"

hw.rh= e;
if(k> mem_end)e= 0;
else
{/*1791:*/
#line 32013 "texprof.w"

if(fl_mem[k]!=0)e= fl_mem[k++]|0x80000000;
else
{int i;
i= 1;k++;
while(k<=mem_end&&fl_mem[k]==0)
{i++;k++;}
e= i;
}

/*:1791*/
#line 32006 "texprof.w"
}
hw.lh= e;
dump_hh(hw);word_count++;
}
print_ln();print_int(word_count);
print(" words of file/line information dumped.");
}
/*:1790*/
#line 24569 "texprof.w"
;
/*1325:*/
#line 25010 "texprof.w"

dump_int(interaction);dump_int(format_ident);dump_int(69069);
tracing_stats= 0

/*:1325*/
#line 24570 "texprof.w"
;
/*1328:*/
#line 25038 "texprof.w"

w_close(&fmt_file)

/*:1328*/
#line 24571 "texprof.w"
;
}
#endif
#line 24574 "texprof.w"

/*:1301*//*1347:*/
#line 25495 "texprof.w"

/*1348:*/
#line 25517 "texprof.w"

static void new_whatsit(small_number s,small_number w)
{pointer p;
p= get_node(w);type(p)= whatsit_node;subtype(p)= s;
link(tail)= p;tail= p;
}

/*:1348*//*1349:*/
#line 25527 "texprof.w"

static void new_write_whatsit(small_number w)
{new_whatsit(cur_chr,w);
if(w!=write_node_size)scan_four_bit_int();
else{scan_int();
if(cur_val<0)cur_val= 17;
else if(cur_val> 15)cur_val= 16;
}
write_stream(tail)= cur_val;
}

/*:1349*//*1811:*/
#line 32591 "texprof.w"

static void scan_pdf_ext_toks(void)
{scan_toks(false,true);
flush_list(def_ref);
}
static void scan_pdf_ext_late_toks(void)
{scan_toks(false,false);
flush_list(def_ref);
}


/*:1811*//*1819:*/
#line 32918 "texprof.w"

static void scan_action(void)
{int pdf_action;
int pdf_action_file= 0;
int pdf_action_new_window= 0;
if(scan_keyword("user"))
pdf_action= pdf_action_user;
else if(scan_keyword("goto"))
pdf_action= pdf_action_goto;
else if(scan_keyword("thread"))
pdf_action= pdf_action_thread;
else
pdf_error("ext1","action type missing");
if(pdf_action==pdf_action_user){
scan_pdf_ext_toks();
return;}
if(scan_keyword("file")){
scan_pdf_ext_toks();
pdf_action_file= 1;
}
if(scan_keyword("struct")){
if(pdf_action!=pdf_action_goto)
pdf_error("ext1","only GoTo action can be used with `struct'");
if(pdf_action_file!=0){
scan_pdf_ext_toks();
}
else if(scan_keyword("name")){
scan_pdf_ext_toks();
}
else if(scan_keyword("num")){
scan_int();
if(cur_val<=0)
pdf_error("ext1","num identifier must be positive");
}
else
pdf_error("ext1","identifier type missing");
}
if(scan_keyword("page")){
if(pdf_action!=pdf_action_goto)
pdf_error("ext1","only GoTo action can be used with `page'");
pdf_action= pdf_action_page;
scan_int();
if(cur_val<=0)
pdf_error("ext1","page number must be positive");
scan_pdf_ext_toks();
}
else if(scan_keyword("name")){
scan_pdf_ext_toks();
}
else if(scan_keyword("num")){
if((pdf_action==pdf_action_goto)&&
(pdf_action_file!=0))
pdf_error("ext1",
"`goto' option cannot be used with both `file' and `num'");
scan_int();
if(cur_val<=0)
pdf_error("ext1","num identifier must be positive");
}
else
pdf_error("ext1","identifier type missing");
if(scan_keyword("newwindow")){
pdf_action_new_window= 1;
/*442:*/
#line 9230 "texprof.w"

{get_x_token();if(cur_cmd!=spacer)back_input();
}

/*:442*/
#line 32980 "texprof.w"
;}
else if(scan_keyword("nonewwindow")){
pdf_action_new_window= 2;
/*442:*/
#line 9230 "texprof.w"

{get_x_token();if(cur_cmd!=spacer)back_input();
}

/*:442*/
#line 32983 "texprof.w"
;}
else
pdf_action_new_window= 0;
if((pdf_action_new_window> 0)&&
(((pdf_action!=pdf_action_goto)&&
(pdf_action!=pdf_action_page))||
(pdf_action_file==0)))
pdf_error("ext1",
"`newwindow'/`nonewwindow' must be used with `goto' and `file' option");
}

/*:1819*//*1821:*/
#line 33056 "texprof.w"

static void scan_alt_rule(void)
{
reswitch:
if(scan_keyword("width")){
scan_normal_dimen;
goto reswitch;
}
if(scan_keyword("height")){
scan_normal_dimen;
goto reswitch;
}
if(scan_keyword("depth")){
scan_normal_dimen;
goto reswitch;
}
}



/*:1821*//*1823:*/
#line 33086 "texprof.w"

static void read_expand_font(void)
{int shrink_limit,stretch_limit,font_step;
internal_font_number f;


scan_font_ident();
f= cur_val;
if(f==null_font)
pdf_error("font expansion","invalid font identifier");
scan_optional_equals();
scan_int();
scan_int();
scan_int();
if(scan_keyword("autoexpand")){
/*442:*/
#line 9230 "texprof.w"

{get_x_token();if(cur_cmd!=spacer)back_input();
}

/*:442*/
#line 33101 "texprof.w"
;
}
}

/*:1823*//*1824:*/
#line 33106 "texprof.w"

static void pdf_include_chars(void)
{str_number s;
pool_pointer k;
internal_font_number f;

scan_font_ident();
f= cur_val;
if(f==null_font)
pdf_error("font","invalid font identifier");
scan_pdf_ext_toks();
}

/*:1824*//*1830:*/
#line 33195 "texprof.w"

static void scan_thread_id(void)
{if(scan_keyword("num"))scan_int();
else if(scan_keyword("name"))scan_pdf_ext_toks();
}

/*:1830*//*1831:*/
#line 33202 "texprof.w"

static void scan_pdf_box_spec(void)
{
if(scan_keyword("mediabox"))return;
else if(scan_keyword("cropbox"))return;
else if(scan_keyword("bleedbox"))return;
else if(scan_keyword("trimbox"))return;
else if(scan_keyword("artbox"))return;
}

static void scan_image(void)
{scan_alt_rule();
if(scan_keyword("attr"))scan_pdf_ext_toks();
if(scan_keyword("named"))scan_pdf_ext_toks();
else if(scan_keyword("page"))scan_int();
if(scan_keyword("colorspace"))scan_int();
scan_pdf_box_spec();
scan_pdf_ext_toks();
}


/*:1831*/
#line 25496 "texprof.w"

static void do_extension(void)
{int k;
pointer p;
switch(cur_chr){
case open_node:/*1350:*/
#line 25538 "texprof.w"

{new_write_whatsit(open_node_size);
scan_optional_equals();scan_file_name();
open_name(tail)= cur_name;open_area(tail)= cur_area;open_ext(tail)= cur_ext;
}

/*:1350*/
#line 25501 "texprof.w"
break;
case write_node:/*1351:*/
#line 25548 "texprof.w"

{k= cur_cs;new_write_whatsit(write_node_size);
cur_cs= k;p= scan_toks(false,false);write_tokens(tail)= def_ref;
}

/*:1351*/
#line 25502 "texprof.w"
break;
case close_node:/*1352:*/
#line 25553 "texprof.w"

{new_write_whatsit(write_node_size);write_tokens(tail)= null;
}

/*:1352*/
#line 25503 "texprof.w"
break;
case special_node:/*1353:*/
#line 25561 "texprof.w"

{if(scan_keyword("shipout"))
{new_whatsit(latespecial_node,write_node_size);write_stream(tail)= null;
p= scan_toks(false,false);write_tokens(tail)= def_ref;
}else
{new_whatsit(special_node,write_node_size);write_stream(tail)= null;
p= scan_toks(false,true);write_tokens(tail)= def_ref;
}}

/*:1353*/
#line 25504 "texprof.w"
break;
case immediate_code:/*1374:*/
#line 25795 "texprof.w"

{get_x_token();
if((cur_cmd==extension)&&(cur_chr<=close_node))
{p= tail;do_extension();
out_what(tail);
flush_node_list(tail);tail= p;link(p)= null;
}
else back_input();
}

/*:1374*/
#line 25505 "texprof.w"
break;
case set_language_code:/*1376:*/
#line 25823 "texprof.w"

if(abs(mode)!=hmode)report_illegal_case();
else{new_whatsit(language_node,small_node_size);
scan_int();
if(cur_val<=0)clang= 0;
else if(cur_val> 255)clang= 0;
else clang= cur_val;
what_lang(tail)= clang;
what_lhm(tail)= norm_min(left_hyphen_min);
what_rhm(tail)= norm_min(right_hyphen_min);
}

/*:1376*/
#line 25506 "texprof.w"
break;
/*1608:*/
#line 28837 "texprof.w"

case reset_timer_code:reset_timer= start_sec*1.0+start_nsec/1000000000.0;break;

/*:1608*//*1678:*/
#line 29667 "texprof.w"

case save_pos_code:/*1679:*/
#line 29674 "texprof.w"

{new_whatsit(save_pos_code,small_node_size);write_stream(tail)= null;
write_tokens(tail)= null;
}

/*:1679*/
#line 29668 "texprof.w"
break;

/*:1678*//*1744:*/
#line 31019 "texprof.w"

case profile_on_code:
if(!profile_on)
{profile_on= true;
/*1763:*/
#line 31353 "texprof.w"

/*1756:*/
#line 31198 "texprof.w"

#if GETTIME==0
time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#elif GETTIME==1
#line 31202 "texprof.w"
 time_error= clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&ts);
#elif GETTIME==2
#line 31204 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
#elif GETTIME==3
#line 31206 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC,&ts);
#else
#line 31208 "texprof.w"
 time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#endif
#line 31210 "texprof.w"

/*:1756*/
#line 31354 "texprof.w"

diff_nsec= 0;
start_nsec= ts.tv_nsec;
start_sec= ts.tv_sec;
prof_file_line= cur_file_line;
prof_cmd= system_profile_on;
prof_depth= cur_depth;
/*1778:*/
#line 31651 "texprof.w"

if(unchanged_depth<prof_depth)
/*1780:*/
#line 31676 "texprof.w"

{int i;
if(last_depth> unchanged_depth)
{
#if SHOW_RECORD_TIMING
print_char('{');print_int(cmd_count);
print_char(':');print_int(system_macro_pop);
print_char(':');print_int(last_depth);
print_char('>');print_int(unchanged_depth);
print_char('}');print_ln();
#endif
#line 31687 "texprof.w"
 cmd_count++;
}
if(st_count+2*(prof_depth-unchanged_depth)> MAX_STAMPS)
overflow("profile data",MAX_STAMPS);
for(i= unchanged_depth+1;i<=prof_depth;i++)
{
#if SHOW_RECORD_TIMING
print_char('[');print_int(cmd_count);
print_char(':');print_int(i-1);
print_char('<');print_int(CALL_DEPTH(macro_stack[i]));
print_char(':');print_cs(CALL_EQTB(macro_stack[i]));
print_char(']');print_ln();
#endif
#line 31700 "texprof.w"
 cmd_count++;
stamp[st_count++]= CALL_CFL(macro_stack[i]);
stamp[st_count++]= CALL_DE(macro_stack[i]);
}
last_depth= unchanged_depth= prof_depth;
if(prof_depth> prof_max_depth)prof_max_depth= prof_depth;
}


/*:1780*/
#line 31653 "texprof.w"



/*:1778*/
#line 31361 "texprof.w"


/*:1763*/
#line 31023 "texprof.w"

}
break;
case profile_off_code:
if(profile_on)
{/*1762:*/
#line 31339 "texprof.w"

prof_file_line= cur_file_line;
prof_cmd= system_profile_off;
prof_depth= cur_depth;
/*1778:*/
#line 31651 "texprof.w"

if(unchanged_depth<prof_depth)
/*1780:*/
#line 31676 "texprof.w"

{int i;
if(last_depth> unchanged_depth)
{
#if SHOW_RECORD_TIMING
print_char('{');print_int(cmd_count);
print_char(':');print_int(system_macro_pop);
print_char(':');print_int(last_depth);
print_char('>');print_int(unchanged_depth);
print_char('}');print_ln();
#endif
#line 31687 "texprof.w"
 cmd_count++;
}
if(st_count+2*(prof_depth-unchanged_depth)> MAX_STAMPS)
overflow("profile data",MAX_STAMPS);
for(i= unchanged_depth+1;i<=prof_depth;i++)
{
#if SHOW_RECORD_TIMING
print_char('[');print_int(cmd_count);
print_char(':');print_int(i-1);
print_char('<');print_int(CALL_DEPTH(macro_stack[i]));
print_char(':');print_cs(CALL_EQTB(macro_stack[i]));
print_char(']');print_ln();
#endif
#line 31700 "texprof.w"
 cmd_count++;
stamp[st_count++]= CALL_CFL(macro_stack[i]);
stamp[st_count++]= CALL_DE(macro_stack[i]);
}
last_depth= unchanged_depth= prof_depth;
if(prof_depth> prof_max_depth)prof_max_depth= prof_depth;
}


/*:1780*/
#line 31653 "texprof.w"



/*:1778*/
#line 31343 "texprof.w"

/*1761:*/
#line 31310 "texprof.w"

if(profile_on)
{if(st_count+3> MAX_STAMPS)
overflow("profile data",MAX_STAMPS);
/*1779:*/
#line 31656 "texprof.w"

if(last_depth> prof_depth)
{if(last_depth==prof_depth+1)
prof_cmd= prof_cmd|POP_BIT;
else
stamp[st_count++]= (system_macro_pop<<24)|(last_depth-prof_depth);
#if SHOW_RECORD_TIMING
print_char('{');print_int(cmd_count);
print_char(':');print_int(system_macro_pop);
print_char(':');print_int(last_depth);
print_char('>');print_int(prof_depth);
print_char('}');print_ln();
#endif
#line 31669 "texprof.w"
 cmd_count++;
last_depth= unchanged_depth= prof_depth;
}


/*:1779*/
#line 31314 "texprof.w"

stamp[st_count++]= (prof_cmd<<24)|prof_file_line;
prof_cmd= prof_cmd&~POP_BIT;
#if SHOW_RECORD_TIMING
print_char('<');print_int(cmd_count);
print_char(':');
if(prof_cmd&POP_BIT)print_char('-');
print_int(prof_cmd&~POP_BIT);
print_char(':');print_int(prof_depth);
print_char('>');print_ln();
#endif
#line 31325 "texprof.w"
 cmd_count++;
/*1756:*/
#line 31198 "texprof.w"

#if GETTIME==0
time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#elif GETTIME==1
#line 31202 "texprof.w"
 time_error= clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&ts);
#elif GETTIME==2
#line 31204 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
#elif GETTIME==3
#line 31206 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC,&ts);
#else
#line 31208 "texprof.w"
 time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#endif
#line 31210 "texprof.w"

/*:1756*/
#line 31326 "texprof.w"

/*1757:*/
#line 31215 "texprof.w"

diff_nsec= (ts.tv_sec-start_sec)*1000000000+(ts.tv_nsec-start_nsec);
#if 0
printf("time: %ld %ld %ld\n",diff_nsec,(ts.tv_sec),(ts.tv_nsec));
#endif
#line 31220 "texprof.w"

start_nsec= ts.tv_nsec;
start_sec= ts.tv_sec;

/*:1757*/
#line 31327 "texprof.w"

stamp[st_count++]= diff_nsec;
}


/*:1761*/
#line 31344 "texprof.w"


/*:1762*/
#line 31028 "texprof.w"

profile_on= false;
}
break;

/*:1744*//*1816:*/
#line 32850 "texprof.w"

case pdf_annot_node:/*1817:*/
#line 32897 "texprof.w"

{if(scan_keyword("reserveobjnum")){/*442:*/
#line 9230 "texprof.w"

{get_x_token();if(cur_cmd!=spacer)back_input();
}

/*:442*/
#line 32898 "texprof.w"
;}
else{if(scan_keyword("useobjnum")){scan_int();}
scan_pdf_ext_toks();
}
}

/*:1817*/
#line 32851 "texprof.w"
break;
case pdf_catalog_code:/*1818:*/
#line 32904 "texprof.w"

{scan_pdf_ext_toks();
if(scan_keyword("openaction"))scan_action();
}

/*:1818*/
#line 32852 "texprof.w"
break;
case pdf_dest_node:/*1820:*/
#line 33005 "texprof.w"

{int pdf_dest_type;
if(scan_keyword("struct")){
scan_int();
if(cur_val<=0)
pdf_error("ext1","struct identifier must be positive");
}
if(scan_keyword("num")){
scan_int();
if(cur_val<=0)
pdf_error("ext1","num identifier must be positive");
if(cur_val> max_halfword)
pdf_error("ext1","number too big");
}
else if(scan_keyword("name")){
scan_pdf_ext_toks();
}
else
pdf_error("ext1","identifier type missing");
if(scan_keyword("xyz")){
pdf_dest_type= pdf_dest_xyz;
if(scan_keyword("zoom")){
scan_int();
if(cur_val> max_halfword)
pdf_error("ext1","number too big");
}
}
else if(scan_keyword("fitbh"))
pdf_dest_type= pdf_dest_fitbh;
else if(scan_keyword("fitbv"))
pdf_dest_type= pdf_dest_fitbv;
else if(scan_keyword("fitb"))
pdf_dest_type= pdf_dest_fitb;
else if(scan_keyword("fith"))
pdf_dest_type= pdf_dest_fith;
else if(scan_keyword("fitv"))
pdf_dest_type= pdf_dest_fitv;
else if(scan_keyword("fitr"))
pdf_dest_type= pdf_dest_fitr;
else if(scan_keyword("fit"))
pdf_dest_type= pdf_dest_fit;
else
pdf_error("ext1","destination type missing");
/*442:*/
#line 9230 "texprof.w"

{get_x_token();if(cur_cmd!=spacer)back_input();
}

/*:442*/
#line 33048 "texprof.w"
;
if(pdf_dest_type==pdf_dest_fitr){
scan_alt_rule();
}
}



/*:1820*/
#line 32853 "texprof.w"
break;
case pdf_end_link_node:break;
case pdf_end_thread_node:break;
case pdf_font_attr_code:/*1822:*/
#line 33076 "texprof.w"

{
scan_font_ident();
if(cur_val==null_font)
pdf_error("font","invalid font identifier");
scan_pdf_ext_toks();
}

/*:1822*/
#line 32856 "texprof.w"
break;
case pdf_font_expand_code:read_expand_font();break;
case pdf_include_chars_code:pdf_include_chars();break;
case pdf_info_code:scan_pdf_ext_toks();break;
case pdf_literal_node:/*1825:*/
#line 33119 "texprof.w"

{int k;
if(scan_keyword("shipout"))k= pdf_lateliteral_node;
else k= pdf_literal_node;
if(scan_keyword("direct"))do_nothing;
else if(scan_keyword("page"))do_nothing;
else do_nothing;
if(k==pdf_literal_node)scan_pdf_ext_toks();
else scan_pdf_ext_late_toks();
}

/*:1825*/
#line 32860 "texprof.w"
break;
case pdf_colorstack_node:/*1826:*/
#line 33138 "texprof.w"

{int i;
scan_int();
if(scan_keyword("set")){
i= colorstack_set;
}
else if(scan_keyword("push")){
i= colorstack_push;
}
else if(scan_keyword("pop")){
i= colorstack_pop;
}
else if(scan_keyword("current")){
i= colorstack_current;
}
else{
i= -1;
}
if(i>=0){
if(i<=colorstack_data){
scan_pdf_ext_toks();
}
}
}

/*:1826*/
#line 32861 "texprof.w"
break;
case pdf_setmatrix_node:scan_pdf_ext_toks();break;
case pdf_save_node:break;
case pdf_restore_node:break;
case pdf_map_file_code:scan_pdf_ext_toks();break;
case pdf_map_line_code:scan_pdf_ext_toks();break;
case pdf_names_code:scan_pdf_ext_toks();break;
case pdf_obj_code:/*1827:*/
#line 33163 "texprof.w"

{
if(scan_keyword("reserveobjnum")){
/*442:*/
#line 9230 "texprof.w"

{get_x_token();if(cur_cmd!=spacer)back_input();
}

/*:442*/
#line 33166 "texprof.w"
;
}
else{
if(scan_keyword("useobjnum"))scan_int();
if(scan_keyword("stream")){
if(scan_keyword("attr"))scan_pdf_ext_toks();
}
if(scan_keyword("file"))do_nothing;
scan_pdf_ext_toks();
}
}

/*:1827*/
#line 32868 "texprof.w"
break;
case pdf_outline_code:/*1828:*/
#line 33178 "texprof.w"

{
if(scan_keyword("attr"))scan_pdf_ext_toks();
scan_action();
if(scan_keyword("count"))scan_int();
scan_pdf_ext_toks();
}

/*:1828*/
#line 32869 "texprof.w"
break;
case pdf_refobj_node:scan_int();break;
case pdf_refxform_node:scan_int();break;
case pdf_refximage_node:scan_int();break;
case pdf_snap_ref_point_node:break;
case pdf_snapy_comp_node:scan_int();break;
case pdf_snapy_node:break;
case pdf_start_link_node:scan_action();break;
case pdf_start_thread_node:scan_thread_id();break;
case pdf_thread_node:scan_thread_id();break;
case pdf_trailer_code:scan_pdf_ext_toks();break;
case pdf_trailer_id_code:scan_pdf_ext_toks();break;
case pdf_xform_code:/*1829:*/
#line 33186 "texprof.w"

{
if(scan_keyword("attr"))scan_pdf_ext_toks();
if(scan_keyword("resources"))scan_pdf_ext_toks();
scan_register_num();
}

/*:1829*/
#line 32881 "texprof.w"
break;
case pdf_ximage_code:scan_image();break;
case pdf_glyph_to_unicode_code:scan_pdf_ext_toks();scan_pdf_ext_toks();break;
case pdf_nobuiltin_tounicode_code:scan_font_ident();break;
case pdf_interword_space_on_node:break;
case pdf_interword_space_off_node:break;
case pdf_fake_space_node:break;
case pdf_running_link_off_node:break;
case pdf_running_link_on_node:break;
case pdf_space_font_code:scan_pdf_ext_toks();break;
case tracing_stack_level_code:scan_int();break;
case pdf_par_token_context_code:scan_optional_equals();scan_int();break;
case pdf_par_token_name_code:scan_optional_equals();get_token();break;
case pdf_show_stream_code:scan_optional_equals();scan_int();break;


/*:1816*/
#line 25507 "texprof.w"

default:confusion("ext1");

}
}

/*:1347*//*1375:*/
#line 25809 "texprof.w"

static void fix_language(void)
{ASCII_code l;
if(language<=0)l= 0;
else if(language> 255)l= 0;
else l= language;
if(l!=clang)
{new_whatsit(language_node,small_node_size);
what_lang(tail)= l;clang= l;
what_lhm(tail)= norm_min(left_hyphen_min);
what_rhm(tail)= norm_min(right_hyphen_min);
}
}

/*:1375*/
#line 20682 "texprof.w"

/*1067:*/
#line 21381 "texprof.w"

static void handle_right_brace(void)
{pointer p,q;
scaled d;
int f;
switch(cur_group){
case simple_group:unsave();break;
case bottom_level:{print_err("Too many }'s");

help2("You've closed more groups than you opened.",
"Such booboos are generally harmless, so keep going.");error();
}break;
case semi_simple_group:case math_shift_group:
case math_left_group:extra_right_brace();break;
/*1084:*/
#line 21731 "texprof.w"

case hbox_group:package(0);break;
case adjusted_hbox_group:{adjust_tail= adjust_head;package(0);
}break;
case vbox_group:{end_graf();package(0);
}break;
case vtop_group:{end_graf();package(vtop_code);
}break;

/*:1084*//*1099:*/
#line 21893 "texprof.w"

case insert_group:{end_graf();q= split_top_skip;add_glue_ref(q);
d= split_max_depth;f= floating_penalty;unsave();decr(save_ptr);

p= vpack(link(head),natural);pop_nest();
if(saved(0)<255)
{tail_append(get_node(ins_node_size));
type(tail)= ins_node;subtype(tail)= qi(saved(0));
height(tail)= height(p)+depth(p);ins_ptr(tail)= list_ptr(p);
split_top_ptr(tail)= q;depth(tail)= d;float_cost(tail)= f;
}
else{tail_append(get_node(small_node_size));
type(tail)= adjust_node;
subtype(tail)= 0;
adjust_ptr(tail)= list_ptr(p);delete_glue_ref(q);
}
free_node(p,box_node_size);
if(nest_ptr==0)build_page();
}break;
case output_group:/*1025:*/
#line 20595 "texprof.w"

{if((loc!=null)||
((token_type!=output_text)&&(token_type!=backed_up)))
/*1026:*/
#line 20616 "texprof.w"

{print_err("Unbalanced output routine");

help2("Your sneaky output routine has problematic {'s and/or }'s.",
"I can't handle that very well; good luck.");error();
do{get_token();
}while(!(loc==null));
}

/*:1026*/
#line 20598 "texprof.w"
;
end_token_list();
end_graf();unsave();output_active= false;insert_penalties= 0;
/*1027:*/
#line 20625 "texprof.w"

if(box(255)!=null)
{print_err("Output routine didn't use all of ");
print_esc("box");print_int(255);

help3("Your \\output commands should empty \\box255,",
"e.g., by saying `\\shipout\\box255'.",
"Proceed; I'll discard its present contents.");
box_error(255);
}

/*:1027*/
#line 20601 "texprof.w"
;
if(tail!=head)
{link(page_tail)= link(head);
page_tail= tail;
}
if(link(page_head)!=null)
{if(link(contrib_head)==null)contrib_tail= page_tail;
link(page_tail)= link(contrib_head);
link(contrib_head)= link(page_head);
link(page_head)= null;page_tail= page_head;
}
flush_node_list(page_disc);page_disc= null;
pop_nest();build_page();
}

/*:1025*/
#line 21912 "texprof.w"
break;

/*:1099*//*1117:*/
#line 22105 "texprof.w"

case disc_group:build_discretionary();break;

/*:1117*//*1131:*/
#line 22341 "texprof.w"

case align_group:{back_input();cur_tok= cs_token_flag+frozen_cr;
print_err("Missing ");print_esc("cr");print(" inserted");

help1("I'm guessing that you meant to end an alignment here.");
ins_error();
}break;

/*:1131*//*1132:*/
#line 22349 "texprof.w"

case no_align_group:{end_graf();unsave();align_peek();
}break;

/*:1132*//*1167:*/
#line 22803 "texprof.w"

case vcenter_group:{end_graf();unsave();save_ptr= save_ptr-2;
p= vpack(link(head),saved(1),saved(0));pop_nest();
tail_append(new_noad());type(tail)= vcenter_noad;
math_type(nucleus(tail))= sub_box;info(nucleus(tail))= p;
}break;

/*:1167*//*1172:*/
#line 22841 "texprof.w"

case math_choice_group:build_choices();break;

/*:1172*//*1185:*/
#line 23015 "texprof.w"

case math_group:{unsave();decr(save_ptr);
math_type(saved(0))= sub_mlist;p= fin_mlist(null);info(saved(0))= p;
if(p!=null)if(link(p)==null)
if(type(p)==ord_noad)
{if(math_type(subscr(p))==empty)
if(math_type(supscr(p))==empty)
{mem[saved(0)].hh= mem[nucleus(p)].hh;
free_node(p,noad_size);
}
}
else if(type(p)==accent_noad)if(saved(0)==nucleus(tail))
if(type(tail)==ord_noad)/*1186:*/
#line 23030 "texprof.w"

{q= head;while(link(q)!=tail)q= link(q);
link(q)= p;free_node(tail,noad_size);tail= p;
}

/*:1186*/
#line 23027 "texprof.w"
;
}break;

/*:1185*/
#line 21396 "texprof.w"

default:confusion("rightbrace");

}
}

/*:1067*/
#line 20683 "texprof.w"

static void main_control(void)
{
int t;
/*1759:*/
#line 31267 "texprof.w"

/*1773:*/
#line 31551 "texprof.w"

{int macro_depth= -1,macro_cs= 0;
uint32_t macro_fl= FILE_LINE(terminal_file,0);
/*1775:*/
#line 31573 "texprof.w"

macro_depth++;
cur_depth= macro_depth;
if(macro_depth>=MAX_MACRO_STACK)
overflow("macro stack size",macro_depth);
macro_stack[macro_depth]= CALL_INFO(macro_depth,macro_cs,macro_fl);
if(macro_depth<=unchanged_depth)
unchanged_depth= macro_depth-1;

/*:1775*/
#line 31554 "texprof.w"

cmd_count++;
stamp[st_count++]= CALL_CFL(macro_stack[0]);
stamp[st_count++]= CALL_DE(macro_stack[0]);
last_depth= unchanged_depth= prof_depth= 0;
}

/*:1773*/
#line 31268 "texprof.w"

prof_cmd= system_cmd;
prof_file_line= FILE_LINE(system_file,system_start);
/*1778:*/
#line 31651 "texprof.w"

if(unchanged_depth<prof_depth)
/*1780:*/
#line 31676 "texprof.w"

{int i;
if(last_depth> unchanged_depth)
{
#if SHOW_RECORD_TIMING
print_char('{');print_int(cmd_count);
print_char(':');print_int(system_macro_pop);
print_char(':');print_int(last_depth);
print_char('>');print_int(unchanged_depth);
print_char('}');print_ln();
#endif
#line 31687 "texprof.w"
 cmd_count++;
}
if(st_count+2*(prof_depth-unchanged_depth)> MAX_STAMPS)
overflow("profile data",MAX_STAMPS);
for(i= unchanged_depth+1;i<=prof_depth;i++)
{
#if SHOW_RECORD_TIMING
print_char('[');print_int(cmd_count);
print_char(':');print_int(i-1);
print_char('<');print_int(CALL_DEPTH(macro_stack[i]));
print_char(':');print_cs(CALL_EQTB(macro_stack[i]));
print_char(']');print_ln();
#endif
#line 31700 "texprof.w"
 cmd_count++;
stamp[st_count++]= CALL_CFL(macro_stack[i]);
stamp[st_count++]= CALL_DE(macro_stack[i]);
}
last_depth= unchanged_depth= prof_depth;
if(prof_depth> prof_max_depth)prof_max_depth= prof_depth;
}


/*:1780*/
#line 31653 "texprof.w"



/*:1778*/
#line 31271 "texprof.w"

#if 0
clock_getres(CLOCK_MONOTONIC,&ts);
printf("CLOCK_MONOTONIC: %ld %ld\n",ts.tv_sec,ts.tv_nsec);

clock_getres(CLOCK_MONOTONIC_RAW,&ts);
printf("CLOCK_MONOTONIC_RAW: %ld %ld\n",ts.tv_sec,ts.tv_nsec);

clock_getres(CLOCK_PROCESS_CPUTIME_ID,&ts);
printf("CLOCK_PROCESS_CPUTIME_ID: %ld %ld\n",ts.tv_sec,ts.tv_nsec);

clock_getres(CLOCK_THREAD_CPUTIME_ID,&ts);
printf("CLOCK_THREAD_CPUTIME_ID: %ld %ld\n",ts.tv_sec,ts.tv_nsec);
#endif
#line 31285 "texprof.w"
/*1756:*/
#line 31198 "texprof.w"

#if GETTIME==0
time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#elif GETTIME==1
#line 31202 "texprof.w"
 time_error= clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&ts);
#elif GETTIME==2
#line 31204 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
#elif GETTIME==3
#line 31206 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC,&ts);
#else
#line 31208 "texprof.w"
 time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#endif
#line 31210 "texprof.w"

/*:1756*/
#line 31285 "texprof.w"

diff_nsec= 0;
start_nsec= ts.tv_nsec;
start_sec= ts.tv_sec;

/*:1759*/
#line 20687 "texprof.w"

if(every_job!=null)begin_token_list(every_job,every_job_text);
big_switch:
/*1761:*/
#line 31310 "texprof.w"

if(profile_on)
{if(st_count+3> MAX_STAMPS)
overflow("profile data",MAX_STAMPS);
/*1779:*/
#line 31656 "texprof.w"

if(last_depth> prof_depth)
{if(last_depth==prof_depth+1)
prof_cmd= prof_cmd|POP_BIT;
else
stamp[st_count++]= (system_macro_pop<<24)|(last_depth-prof_depth);
#if SHOW_RECORD_TIMING
print_char('{');print_int(cmd_count);
print_char(':');print_int(system_macro_pop);
print_char(':');print_int(last_depth);
print_char('>');print_int(prof_depth);
print_char('}');print_ln();
#endif
#line 31669 "texprof.w"
 cmd_count++;
last_depth= unchanged_depth= prof_depth;
}


/*:1779*/
#line 31314 "texprof.w"

stamp[st_count++]= (prof_cmd<<24)|prof_file_line;
prof_cmd= prof_cmd&~POP_BIT;
#if SHOW_RECORD_TIMING
print_char('<');print_int(cmd_count);
print_char(':');
if(prof_cmd&POP_BIT)print_char('-');
print_int(prof_cmd&~POP_BIT);
print_char(':');print_int(prof_depth);
print_char('>');print_ln();
#endif
#line 31325 "texprof.w"
 cmd_count++;
/*1756:*/
#line 31198 "texprof.w"

#if GETTIME==0
time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#elif GETTIME==1
#line 31202 "texprof.w"
 time_error= clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&ts);
#elif GETTIME==2
#line 31204 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
#elif GETTIME==3
#line 31206 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC,&ts);
#else
#line 31208 "texprof.w"
 time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#endif
#line 31210 "texprof.w"

/*:1756*/
#line 31326 "texprof.w"

/*1757:*/
#line 31215 "texprof.w"

diff_nsec= (ts.tv_sec-start_sec)*1000000000+(ts.tv_nsec-start_nsec);
#if 0
printf("time: %ld %ld %ld\n",diff_nsec,(ts.tv_sec),(ts.tv_nsec));
#endif
#line 31220 "texprof.w"

start_nsec= ts.tv_nsec;
start_sec= ts.tv_sec;

/*:1757*/
#line 31327 "texprof.w"

stamp[st_count++]= diff_nsec;
}


/*:1761*/
#line 20690 "texprof.w"

get_x_token();
big_reswitch:
/*1765:*/
#line 31380 "texprof.w"

if(profile_on)
{prof_cmd= cur_cmd;
prof_depth= cur_depth;
prof_file_line= cur_file_line;
/*1778:*/
#line 31651 "texprof.w"

if(unchanged_depth<prof_depth)
/*1780:*/
#line 31676 "texprof.w"

{int i;
if(last_depth> unchanged_depth)
{
#if SHOW_RECORD_TIMING
print_char('{');print_int(cmd_count);
print_char(':');print_int(system_macro_pop);
print_char(':');print_int(last_depth);
print_char('>');print_int(unchanged_depth);
print_char('}');print_ln();
#endif
#line 31687 "texprof.w"
 cmd_count++;
}
if(st_count+2*(prof_depth-unchanged_depth)> MAX_STAMPS)
overflow("profile data",MAX_STAMPS);
for(i= unchanged_depth+1;i<=prof_depth;i++)
{
#if SHOW_RECORD_TIMING
print_char('[');print_int(cmd_count);
print_char(':');print_int(i-1);
print_char('<');print_int(CALL_DEPTH(macro_stack[i]));
print_char(':');print_cs(CALL_EQTB(macro_stack[i]));
print_char(']');print_ln();
#endif
#line 31700 "texprof.w"
 cmd_count++;
stamp[st_count++]= CALL_CFL(macro_stack[i]);
stamp[st_count++]= CALL_DE(macro_stack[i]);
}
last_depth= unchanged_depth= prof_depth;
if(prof_depth> prof_max_depth)prof_max_depth= prof_depth;
}


/*:1780*/
#line 31653 "texprof.w"



/*:1778*/
#line 31385 "texprof.w"

}

/*:1765*/
#line 20693 "texprof.w"

/*1030:*/
#line 20724 "texprof.w"

if(interrupt!=0)if(OK_to_interrupt)
{back_input();check_interrupt;goto big_switch;
}
#ifdef DEBUG
if(panicking)check_mem(false);
#endif
#line 20731 "texprof.w"
 if(tracing_commands> 0)show_cur_cmd_chr()

/*:1030*/
#line 20694 "texprof.w"
;
switch(abs(mode)+cur_cmd){
case hmode+letter:case hmode+other_char:
case hmode+char_given:goto main_loop;
case hmode+char_num:{scan_char_num();cur_chr= cur_val;goto main_loop;}
case hmode+no_boundary:{get_x_token();
if((cur_cmd==letter)||(cur_cmd==other_char)||(cur_cmd==char_given)||
(cur_cmd==char_num))cancel_boundary= true;
goto big_reswitch;
}
case hmode+spacer:if(space_factor==1000)goto append_normal_space;
else app_space();break;
case hmode+ex_space:case mmode+ex_space:goto append_normal_space;
/*1044:*/
#line 21040 "texprof.w"

any_mode(relax):case vmode+spacer:case mmode+spacer:
case mmode+no_boundary:do_nothing;break;
any_mode(ignore_spaces):{/*405:*/
#line 8629 "texprof.w"

do{get_x_token();
}while(!(cur_cmd!=spacer))

/*:405*/
#line 21043 "texprof.w"
;
goto big_reswitch;
}
case vmode+stop:
if(its_all_over())
{/*1764:*/
#line 31366 "texprof.w"

/*1760:*/
#line 31294 "texprof.w"

prof_cmd= cur_cmd;
prof_file_line= cur_file_line;
prof_depth= 0;
profile_on= true;
/*1756:*/
#line 31198 "texprof.w"

#if GETTIME==0
time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#elif GETTIME==1
#line 31202 "texprof.w"
 time_error= clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&ts);
#elif GETTIME==2
#line 31204 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
#elif GETTIME==3
#line 31206 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC,&ts);
#else
#line 31208 "texprof.w"
 time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#endif
#line 31210 "texprof.w"

/*:1756*/
#line 31299 "texprof.w"

/*1757:*/
#line 31215 "texprof.w"

diff_nsec= (ts.tv_sec-start_sec)*1000000000+(ts.tv_nsec-start_nsec);
#if 0
printf("time: %ld %ld %ld\n",diff_nsec,(ts.tv_sec),(ts.tv_nsec));
#endif
#line 31220 "texprof.w"

start_nsec= ts.tv_nsec;
start_sec= ts.tv_sec;

/*:1757*/
#line 31300 "texprof.w"

/*1761:*/
#line 31310 "texprof.w"

if(profile_on)
{if(st_count+3> MAX_STAMPS)
overflow("profile data",MAX_STAMPS);
/*1779:*/
#line 31656 "texprof.w"

if(last_depth> prof_depth)
{if(last_depth==prof_depth+1)
prof_cmd= prof_cmd|POP_BIT;
else
stamp[st_count++]= (system_macro_pop<<24)|(last_depth-prof_depth);
#if SHOW_RECORD_TIMING
print_char('{');print_int(cmd_count);
print_char(':');print_int(system_macro_pop);
print_char(':');print_int(last_depth);
print_char('>');print_int(prof_depth);
print_char('}');print_ln();
#endif
#line 31669 "texprof.w"
 cmd_count++;
last_depth= unchanged_depth= prof_depth;
}


/*:1779*/
#line 31314 "texprof.w"

stamp[st_count++]= (prof_cmd<<24)|prof_file_line;
prof_cmd= prof_cmd&~POP_BIT;
#if SHOW_RECORD_TIMING
print_char('<');print_int(cmd_count);
print_char(':');
if(prof_cmd&POP_BIT)print_char('-');
print_int(prof_cmd&~POP_BIT);
print_char(':');print_int(prof_depth);
print_char('>');print_ln();
#endif
#line 31325 "texprof.w"
 cmd_count++;
/*1756:*/
#line 31198 "texprof.w"

#if GETTIME==0
time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#elif GETTIME==1
#line 31202 "texprof.w"
 time_error= clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&ts);
#elif GETTIME==2
#line 31204 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
#elif GETTIME==3
#line 31206 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC,&ts);
#else
#line 31208 "texprof.w"
 time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#endif
#line 31210 "texprof.w"

/*:1756*/
#line 31326 "texprof.w"

/*1757:*/
#line 31215 "texprof.w"

diff_nsec= (ts.tv_sec-start_sec)*1000000000+(ts.tv_nsec-start_nsec);
#if 0
printf("time: %ld %ld %ld\n",diff_nsec,(ts.tv_sec),(ts.tv_nsec));
#endif
#line 31220 "texprof.w"

start_nsec= ts.tv_nsec;
start_sec= ts.tv_sec;

/*:1757*/
#line 31327 "texprof.w"

stamp[st_count++]= diff_nsec;
}


/*:1761*/
#line 31301 "texprof.w"



/*:1760*/
#line 31367 "texprof.w"


/*:1764*/
#line 21048 "texprof.w"

return;
}
break;
/*1047:*/
#line 21094 "texprof.w"

case vmode+vmove:case hmode+hmove:case mmode+hmove:any_mode(last_item):

/*:1047*//*1097:*/
#line 21874 "texprof.w"

case vmode+vadjust:

/*:1097*//*1110:*/
#line 22044 "texprof.w"
case vmode+ital_corr:

/*:1110*//*1143:*/
#line 22440 "texprof.w"
non_math(eq_no):

/*:1143*/
#line 21052 "texprof.w"
any_mode(mac_param):
report_illegal_case();break;
/*1045:*/
#line 21064 "texprof.w"

non_math(sup_mark):non_math(sub_mark):non_math(math_char_num):
non_math(math_given):non_math(math_comp):non_math(delim_num):
non_math(left_right):non_math(above):non_math(radical):
non_math(math_style):non_math(math_choice):non_math(vcenter):
non_math(non_script):non_math(mkern):non_math(limit_switch):
non_math(mskip):non_math(math_accent):
case mmode+endv:case mmode+par_end:case mmode+stop:
case mmode+vskip:case mmode+un_vbox:
case mmode+valign:case mmode+hrule

/*:1045*/
#line 21054 "texprof.w"
:insert_dollar_sign();break;
/*1055:*/
#line 21183 "texprof.w"

case vmode+hrule:case hmode+vrule:case mmode+vrule:{tail_append(scan_rule_spec());
if(abs(mode)==vmode)prev_depth= ignore_depth;
else if(abs(mode)==hmode)space_factor= 1000;
}break;

/*:1055*//*1056:*/
#line 21194 "texprof.w"

case vmode+vskip:case hmode+hskip:case mmode+hskip:
case mmode+mskip:append_glue();break;
any_mode(kern):case mmode+mkern:append_kern();break;

/*:1056*//*1062:*/
#line 21308 "texprof.w"

non_math(left_brace):new_save_level(simple_group);break;
any_mode(begin_group):new_save_level(semi_simple_group);break;
any_mode(end_group):if(cur_group==semi_simple_group)unsave();
else off_save();break;

/*:1062*//*1066:*/
#line 21378 "texprof.w"

any_mode(right_brace):handle_right_brace();break;

/*:1066*//*1072:*/
#line 21527 "texprof.w"

case vmode+hmove:case hmode+vmove:case mmode+vmove:{t= cur_chr;
scan_normal_dimen;
if(t==0)scan_box(cur_val);else scan_box(-cur_val);
}break;
any_mode(leader_ship):scan_box(leader_flag-a_leaders+cur_chr);break;
any_mode(make_box):begin_box(0);break;

/*:1072*//*1089:*/
#line 21777 "texprof.w"

case vmode+start_par:new_graf(cur_chr> 0);break;
case vmode+letter:case vmode+other_char:
case vmode+char_num:case vmode+char_given:
case vmode+math_shift:case vmode+un_hbox:
case vmode+vrule:
case vmode+accent:case vmode+discretionary:
case vmode+hskip:case vmode+valign:
case vmode+ex_space:case vmode+no_boundary:
{back_input();new_graf(true);
}break;

/*:1089*//*1091:*/
#line 21809 "texprof.w"

case hmode+start_par:case mmode+start_par:indent_in_hmode();break;

/*:1091*//*1093:*/
#line 21829 "texprof.w"

case vmode+par_end:{normal_paragraph();
if(mode> 0)build_page();
}break;
case hmode+par_end:{if(align_state<0)off_save();

end_graf();
if(mode==vmode)build_page();
}break;
case hmode+stop:case hmode+vskip:case hmode+hrule:
case hmode+un_vbox:case hmode+halign:head_for_vmode();break;

/*:1093*//*1096:*/
#line 21869 "texprof.w"

any_mode(insert):case hmode+vadjust:
case mmode+vadjust:begin_insert_or_adjust();break;
any_mode(mark):make_mark();break;

/*:1096*//*1101:*/
#line 21930 "texprof.w"

any_mode(break_penalty):append_penalty();break;

/*:1101*//*1103:*/
#line 21946 "texprof.w"

any_mode(remove_item):delete_last();break;

/*:1103*//*1108:*/
#line 22015 "texprof.w"

case vmode+un_vbox:case hmode+un_hbox:
case mmode+un_hbox:unpackage();break;

/*:1108*//*1111:*/
#line 22050 "texprof.w"

case hmode+ital_corr:append_italic_correction();break;
case mmode+ital_corr:tail_append(new_kern(0))break;

/*:1111*//*1115:*/
#line 22082 "texprof.w"

case hmode+discretionary:case mmode+discretionary:append_discretionary();break;

/*:1115*//*1121:*/
#line 22173 "texprof.w"

case hmode+accent:make_accent();break;

/*:1121*//*1125:*/
#line 22243 "texprof.w"

any_mode(car_ret):any_mode(tab_mark):align_error();break;
any_mode(no_align):no_align_error();break;
any_mode(omit):omit_error();break;

/*:1125*//*1129:*/
#line 22310 "texprof.w"

case vmode+halign:case hmode+valign:init_align();break;
case mmode+halign:if(privileged())
if(cur_group==math_shift_group)init_align();
else off_save();break;
case vmode+endv:case hmode+endv:do_endv();break;

/*:1129*//*1133:*/
#line 22355 "texprof.w"

any_mode(end_cs_name):cs_error();break;

/*:1133*//*1136:*/
#line 22386 "texprof.w"

case hmode+math_shift:init_math();break;

/*:1136*//*1139:*/
#line 22416 "texprof.w"

case mmode+eq_no:if(privileged())
if(cur_group==math_shift_group)start_eq_no();
else off_save();break;

/*:1139*//*1149:*/
#line 22554 "texprof.w"

case mmode+left_brace:{tail_append(new_noad());
back_input();scan_math(nucleus(tail));
}break;

/*:1149*//*1153:*/
#line 22618 "texprof.w"

case mmode+letter:case mmode+other_char:
case mmode+char_given:
set_math_char(ho(math_code(cur_chr)));break;
case mmode+char_num:{scan_char_num();cur_chr= cur_val;
set_math_char(ho(math_code(cur_chr)));
}break;
case mmode+math_char_num:{scan_fifteen_bit_int();set_math_char(cur_val);
}break;
case mmode+math_given:set_math_char(cur_chr);break;
case mmode+delim_num:{scan_twenty_seven_bit_int();
set_math_char(cur_val/010000);
}break;

/*:1153*//*1157:*/
#line 22703 "texprof.w"

case mmode+math_comp:{tail_append(new_noad());
type(tail)= cur_chr;scan_math(nucleus(tail));
}break;
case mmode+limit_switch:math_limit_switch();break;

/*:1157*//*1161:*/
#line 22755 "texprof.w"

case mmode+radical:math_radical();break;

/*:1161*//*1163:*/
#line 22768 "texprof.w"

case mmode+accent:case mmode+math_accent:math_ac();break;

/*:1163*//*1166:*/
#line 22797 "texprof.w"

case mmode+vcenter:{scan_spec(vcenter_group,false);normal_paragraph();
push_nest();mode= -vmode;prev_depth= ignore_depth;
if(every_vbox!=null)begin_token_list(every_vbox,every_vbox_text);
}break;

/*:1166*//*1170:*/
#line 22825 "texprof.w"

case mmode+math_style:tail_append(new_style(cur_chr))break;
case mmode+non_script:{tail_append(new_glue(zero_glue));
subtype(tail)= cond_math_glue;
}break;
case mmode+math_choice:append_choices();break;

/*:1170*//*1174:*/
#line 22865 "texprof.w"

case mmode+sub_mark:case mmode+sup_mark:sub_sup();break;

/*:1174*//*1179:*/
#line 22935 "texprof.w"

case mmode+above:math_fraction();break;

/*:1179*//*1189:*/
#line 23051 "texprof.w"

case mmode+left_right:math_left_right();break;

/*:1189*//*1192:*/
#line 23102 "texprof.w"

case mmode+math_shift:if(cur_group==math_shift_group)after_math();
else off_save();break;

/*:1192*/
#line 21055 "texprof.w"

/*1209:*/
#line 23391 "texprof.w"

any_mode(toks_register):
any_mode(assign_toks):
any_mode(assign_int):
any_mode(assign_dimen):
any_mode(assign_glue):
any_mode(assign_mu_glue):
any_mode(assign_font_dimen):
any_mode(assign_font_int):
any_mode(set_aux):
any_mode(set_prev_graf):
any_mode(set_page_dimen):
any_mode(set_page_int):
any_mode(set_box_dimen):
any_mode(set_shape):
any_mode(def_code):
any_mode(def_family):
any_mode(set_font):
any_mode(def_font):
any_mode(internal_register):
any_mode(advance):
any_mode(multiply):
any_mode(divide):
any_mode(prefix):
any_mode(let):
any_mode(shorthand_def):
any_mode(read_to_cs):
any_mode(def):
any_mode(set_box):
any_mode(hyph_data):
any_mode(set_interaction):prefixed_command();break;

/*:1209*//*1267:*/
#line 24245 "texprof.w"

any_mode(after_assignment):{get_token();after_token= cur_tok;
}break;

/*:1267*//*1270:*/
#line 24266 "texprof.w"

any_mode(after_group):{get_token();save_for_after(cur_tok);
}break;

/*:1270*//*1273:*/
#line 24282 "texprof.w"

any_mode(in_stream):open_or_close_in();break;

/*:1273*//*1275:*/
#line 24306 "texprof.w"

any_mode(message):issue_message();break;

/*:1275*//*1284:*/
#line 24373 "texprof.w"

any_mode(case_shift):shift_case();break;

/*:1284*//*1289:*/
#line 24415 "texprof.w"

any_mode(xray):show_whatever();break;

/*:1289*/
#line 21056 "texprof.w"

/*1346:*/
#line 25492 "texprof.w"

any_mode(extension):do_extension();

/*:1346*/
#line 21057 "texprof.w"


/*:1044*/
#line 20707 "texprof.w"

}
goto big_switch;
main_loop:
/*1761:*/
#line 31310 "texprof.w"

if(profile_on)
{if(st_count+3> MAX_STAMPS)
overflow("profile data",MAX_STAMPS);
/*1779:*/
#line 31656 "texprof.w"

if(last_depth> prof_depth)
{if(last_depth==prof_depth+1)
prof_cmd= prof_cmd|POP_BIT;
else
stamp[st_count++]= (system_macro_pop<<24)|(last_depth-prof_depth);
#if SHOW_RECORD_TIMING
print_char('{');print_int(cmd_count);
print_char(':');print_int(system_macro_pop);
print_char(':');print_int(last_depth);
print_char('>');print_int(prof_depth);
print_char('}');print_ln();
#endif
#line 31669 "texprof.w"
 cmd_count++;
last_depth= unchanged_depth= prof_depth;
}


/*:1779*/
#line 31314 "texprof.w"

stamp[st_count++]= (prof_cmd<<24)|prof_file_line;
prof_cmd= prof_cmd&~POP_BIT;
#if SHOW_RECORD_TIMING
print_char('<');print_int(cmd_count);
print_char(':');
if(prof_cmd&POP_BIT)print_char('-');
print_int(prof_cmd&~POP_BIT);
print_char(':');print_int(prof_depth);
print_char('>');print_ln();
#endif
#line 31325 "texprof.w"
 cmd_count++;
/*1756:*/
#line 31198 "texprof.w"

#if GETTIME==0
time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#elif GETTIME==1
#line 31202 "texprof.w"
 time_error= clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&ts);
#elif GETTIME==2
#line 31204 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
#elif GETTIME==3
#line 31206 "texprof.w"
 time_error= clock_gettime(CLOCK_MONOTONIC,&ts);
#else
#line 31208 "texprof.w"
 time_error= clock_gettime(CLOCK_THREAD_CPUTIME_ID,&ts);
#endif
#line 31210 "texprof.w"

/*:1756*/
#line 31326 "texprof.w"

/*1757:*/
#line 31215 "texprof.w"

diff_nsec= (ts.tv_sec-start_sec)*1000000000+(ts.tv_nsec-start_nsec);
#if 0
printf("time: %ld %ld %ld\n",diff_nsec,(ts.tv_sec),(ts.tv_nsec));
#endif
#line 31220 "texprof.w"

start_nsec= ts.tv_nsec;
start_sec= ts.tv_sec;

/*:1757*/
#line 31327 "texprof.w"

stamp[st_count++]= diff_nsec;
}


/*:1761*/
#line 20711 "texprof.w"

/*1765:*/
#line 31380 "texprof.w"

if(profile_on)
{prof_cmd= cur_cmd;
prof_depth= cur_depth;
prof_file_line= cur_file_line;
/*1778:*/
#line 31651 "texprof.w"

if(unchanged_depth<prof_depth)
/*1780:*/
#line 31676 "texprof.w"

{int i;
if(last_depth> unchanged_depth)
{
#if SHOW_RECORD_TIMING
print_char('{');print_int(cmd_count);
print_char(':');print_int(system_macro_pop);
print_char(':');print_int(last_depth);
print_char('>');print_int(unchanged_depth);
print_char('}');print_ln();
#endif
#line 31687 "texprof.w"
 cmd_count++;
}
if(st_count+2*(prof_depth-unchanged_depth)> MAX_STAMPS)
overflow("profile data",MAX_STAMPS);
for(i= unchanged_depth+1;i<=prof_depth;i++)
{
#if SHOW_RECORD_TIMING
print_char('[');print_int(cmd_count);
print_char(':');print_int(i-1);
print_char('<');print_int(CALL_DEPTH(macro_stack[i]));
print_char(':');print_cs(CALL_EQTB(macro_stack[i]));
print_char(']');print_ln();
#endif
#line 31700 "texprof.w"
 cmd_count++;
stamp[st_count++]= CALL_CFL(macro_stack[i]);
stamp[st_count++]= CALL_DE(macro_stack[i]);
}
last_depth= unchanged_depth= prof_depth;
if(prof_depth> prof_max_depth)prof_max_depth= prof_depth;
}


/*:1780*/
#line 31653 "texprof.w"



/*:1778*/
#line 31385 "texprof.w"

}

/*:1765*/
#line 20712 "texprof.w"

/*1033:*/
#line 20789 "texprof.w"

adjust_space_factor;
main_f= cur_font;
bchar= font_bchar[main_f];false_bchar= font_false_bchar[main_f];
if(mode> 0)if(language!=clang)fix_language();
fast_get_avail(lig_stack);font(lig_stack)= main_f;cur_l= qi(cur_chr);
character(lig_stack)= cur_l;
cur_q= tail;
if(cancel_boundary)
{cancel_boundary= false;main_k= non_address;
}
else main_k= bchar_label[main_f];
if(main_k==non_address)goto main_loop_move2;
cur_r= cur_l;cur_l= non_char;
goto main_lig_loop1;

main_loop_wrapup:/*1034:*/
#line 20847 "texprof.w"

wrapup(rt_hit)

/*:1034*/
#line 20806 "texprof.w"
;
main_loop_move:/*1035:*/
#line 20850 "texprof.w"


if(lig_stack==null)goto big_reswitch;
cur_q= tail;cur_l= character(lig_stack);
main_loop_move1:if(!is_char_node(lig_stack))goto main_loop_move_lig;
main_loop_move2:if((cur_chr<font_bc[main_f])||(cur_chr> font_ec[main_f]))
{char_warning(main_f,cur_chr);free_avail(lig_stack);goto big_switch;
}
main_i= char_info(main_f,cur_l);
if(!char_exists(main_i))
{char_warning(main_f,cur_chr);free_avail(lig_stack);goto big_switch;
}
link(tail)= lig_stack;tail= lig_stack

/*:1035*/
#line 20809 "texprof.w"
;
main_loop_lookahead:/*1037:*/
#line 20882 "texprof.w"

get_next();
if(cur_cmd==letter)goto main_loop_lookahead1;
if(cur_cmd==other_char)goto main_loop_lookahead1;
if(cur_cmd==char_given)goto main_loop_lookahead1;
x_token();
if(cur_cmd==letter)goto main_loop_lookahead1;
if(cur_cmd==other_char)goto main_loop_lookahead1;
if(cur_cmd==char_given)goto main_loop_lookahead1;
if(cur_cmd==char_num)
{scan_char_num();cur_chr= cur_val;goto main_loop_lookahead1;
}
if(cur_cmd==no_boundary)bchar= non_char;
cur_r= bchar;lig_stack= null;goto main_lig_loop;
main_loop_lookahead1:adjust_space_factor;
fast_get_avail(lig_stack);font(lig_stack)= main_f;
cur_r= qi(cur_chr);character(lig_stack)= cur_r;
if(cur_r==false_bchar)cur_r= non_char

/*:1037*/
#line 20811 "texprof.w"
;
main_lig_loop:/*1038:*/
#line 20911 "texprof.w"

if(char_tag(main_i)!=lig_tag)goto main_loop_wrapup;
if(cur_r==non_char)goto main_loop_wrapup;
main_k= lig_kern_start(main_f,main_i);main_j= font_info[main_k].qqqq;
if(skip_byte(main_j)<=stop_flag)goto main_lig_loop2;
main_k= lig_kern_restart(main_f,main_j);
main_lig_loop1:main_j= font_info[main_k].qqqq;
main_lig_loop2:if(next_char(main_j)==cur_r)
if(skip_byte(main_j)<=stop_flag)
/*1039:*/
#line 20937 "texprof.w"

{if(op_byte(main_j)>=kern_flag)
{wrapup(rt_hit);
tail_append(new_kern(char_kern(main_f,main_j)));goto main_loop_move;
}
if(cur_l==non_char)lft_hit= true;
else if(lig_stack==null)rt_hit= true;
check_interrupt;
switch(op_byte(main_j)){
case qi(1):case qi(5):{cur_l= rem_byte(main_j);
main_i= char_info(main_f,cur_l);ligature_present= true;
}break;
case qi(2):case qi(6):{cur_r= rem_byte(main_j);
if(lig_stack==null)
{lig_stack= new_lig_item(cur_r);bchar= non_char;
}
else if(is_char_node(lig_stack))
{main_p= lig_stack;lig_stack= new_lig_item(cur_r);
lig_ptr(lig_stack)= main_p;
}
else character(lig_stack)= cur_r;
}break;
case qi(3):{cur_r= rem_byte(main_j);
main_p= lig_stack;lig_stack= new_lig_item(cur_r);
link(lig_stack)= main_p;
}break;
case qi(7):case qi(11):{wrapup(false);
cur_q= tail;cur_l= rem_byte(main_j);
main_i= char_info(main_f,cur_l);ligature_present= true;
}break;
default:{cur_l= rem_byte(main_j);ligature_present= true;
if(lig_stack==null)goto main_loop_wrapup;
else goto main_loop_move1;
}
}
if(op_byte(main_j)> qi(4))
if(op_byte(main_j)!=qi(7))goto main_loop_wrapup;
if(cur_l<non_char)goto main_lig_loop;
main_k= bchar_label[main_f];goto main_lig_loop1;
}

/*:1039*/
#line 20921 "texprof.w"
;
if(skip_byte(main_j)==qi(0))incr(main_k);
else{if(skip_byte(main_j)>=stop_flag)goto main_loop_wrapup;
main_k= main_k+qo(skip_byte(main_j))+1;
}
goto main_lig_loop1

/*:1038*/
#line 20813 "texprof.w"
;
main_loop_move_lig:/*1036:*/
#line 20867 "texprof.w"

main_p= lig_ptr(lig_stack);
if(main_p> null)tail_append(main_p);
temp_ptr= lig_stack;lig_stack= link(temp_ptr);
free_node(temp_ptr,small_node_size);
main_i= char_info(main_f,cur_l);ligature_present= true;
if(lig_stack==null)
if(main_p> null)goto main_loop_lookahead;
else cur_r= bchar;
else cur_r= character(lig_stack);
goto main_lig_loop

/*:1036*/
#line 20815 "texprof.w"


/*:1033*/
#line 20715 "texprof.w"
;
append_normal_space:/*1040:*/
#line 20989 "texprof.w"

if(space_skip==zero_glue)
{/*1041:*/
#line 21004 "texprof.w"

{main_p= font_glue[cur_font];
if(main_p==null)
{main_p= new_spec(zero_glue);main_k= param_base[cur_font]+space_code;
width(main_p)= font_info[main_k].sc;
stretch(main_p)= font_info[main_k+1].sc;
shrink(main_p)= font_info[main_k+2].sc;
font_glue[cur_font]= main_p;
}
}

/*:1041*/
#line 20992 "texprof.w"
;
temp_ptr= new_glue(main_p);
}
else temp_ptr= new_param_glue(space_skip_code);
link(tail)= temp_ptr;tail= temp_ptr;
goto big_switch

/*:1040*/
#line 20717 "texprof.w"
;
}

/*:1029*//*1283:*/
#line 24366 "texprof.w"
static void give_err_help(void)
{token_show(err_help);
}

/*:1283*//*1302:*/
#line 24585 "texprof.w"
/*523:*/
#line 10632 "texprof.w"

static bool open_fmt_file(void);

/*:523*/
#line 24585 "texprof.w"

static bool load_fmt_file(void)
{
int j,k;
int p,q;
int x;
four_quarters w;
/*1307:*/
#line 24664 "texprof.w"

x= fmt_file.d.i;
if(x!=0)goto bad_fmt;
/*1385:*/
#line 25919 "texprof.w"

undump(0,1,eTeX_mode);
if(eTeX_ex)
{/*1495:*/
#line 27375 "texprof.w"

max_reg_num= 32767;
max_reg_help_line= "A register number must be between 0 and 32767.";

/*:1495*//*1540:*/
#line 28175 "texprof.w"

expand_depth= 10000;
expand_depth_count= 0;

/*:1540*/
#line 25922 "texprof.w"
;
}
else{/*1494:*/
#line 27371 "texprof.w"

max_reg_num= 255;
max_reg_help_line= "A register number must be between 0 and 255.";

/*:1494*/
#line 25924 "texprof.w"
;
}

/*:1385*/
#line 24667 "texprof.w"

/*1544:*/
#line 28203 "texprof.w"

undump(0,1,Prote_mode);

/*:1544*/
#line 24668 "texprof.w"

/*1585:*/
#line 28617 "texprof.w"

for(k= ROM_base;k<=ROM_size;k++)undump_wd(ROM[k]);

/*:1585*/
#line 24669 "texprof.w"

undump_int(x);
if(x!=mem_bot)goto bad_fmt;
undump_int(x);
if(x!=mem_top)goto bad_fmt;
undump_int(x);
if(x!=eqtb_size)goto bad_fmt;
undump_int(x);
if(x!=hash_prime)goto bad_fmt;
undump_int(x);
if(x!=hyph_size)goto bad_fmt

/*:1307*/
#line 24592 "texprof.w"
;
/*1309:*/
#line 24703 "texprof.w"

undump_size(0,pool_size,"string pool size",pool_ptr);
undump_size(0,max_strings,"max strings",str_ptr);
for(k= 0;k<=str_ptr;k++)undump(0,pool_ptr,str_start[k]);
k= 0;
while(k+4<pool_ptr)
{undump_four_ASCII;k= k+4;
}
k= pool_ptr-4;undump_four_ASCII;
init_str_ptr= str_ptr;init_pool_ptr= pool_ptr

/*:1309*/
#line 24593 "texprof.w"
;
/*1311:*/
#line 24745 "texprof.w"

undump(lo_mem_stat_max+1000,hi_mem_stat_min-1,lo_mem_max);
undump(lo_mem_stat_max+1,lo_mem_max,rover);
if(eTeX_ex)for(k= int_val;k<=tok_val;k++)
undump(null,lo_mem_max,sa_root[k]);
p= mem_bot;q= rover;
do{for(k= p;k<=q+1;k++)undump_wd(mem[k]);
p= q+node_size(q);
if((p> lo_mem_max)||((q>=rlink(q))&&(rlink(q)!=rover)))goto bad_fmt;
q= rlink(q);
}while(!(q==rover));
for(k= p;k<=lo_mem_max;k++)undump_wd(mem[k]);
if(mem_min<mem_bot-2)
{p= llink(rover);q= mem_min+1;
link(mem_min)= null;info(mem_min)= null;
rlink(p)= q;llink(rover)= q;
rlink(q)= rover;llink(q)= p;link(q)= empty_flag;
node_size(q)= mem_bot-q;
}
undump(lo_mem_max+1,hi_mem_stat_min,hi_mem_min);
undump(null,mem_top,avail);mem_end= mem_top;
for(k= hi_mem_min;k<=mem_end;k++)undump_wd(mem[k]);
undump_int(var_used);undump_int(dyn_used)

/*:1311*/
#line 24594 "texprof.w"
;
/*1313:*/
#line 24776 "texprof.w"

/*1316:*/
#line 24831 "texprof.w"

k= active_base;
do{undump_int(x);
if((x<1)||(k+x> eqtb_size+1))goto bad_fmt;
for(j= k;j<=k+x-1;j++)undump_wd(eqtb[j]);
k= k+x;
undump_int(x);
if((x<0)||(k+x> eqtb_size+1))goto bad_fmt;
for(j= k;j<=k+x-1;j++)eqtb[j]= eqtb[k-1];
k= k+x;
}while(!(k> eqtb_size))

/*:1316*/
#line 24777 "texprof.w"
;
undump(hash_base,frozen_control_sequence,par_loc);
par_token= cs_token_flag+par_loc;
undump(hash_base,frozen_control_sequence,write_loc);
undump(hash_base,frozen_control_sequence,input_loc);
input_token= cs_token_flag+input_loc;
/*1318:*/
#line 24857 "texprof.w"

undump(hash_base,frozen_control_sequence,hash_used);p= hash_base-1;
do{undump(p+1,hash_used,p);undump_hh(hash[p]);
}while(!(p==hash_used));
for(p= hash_used+1;p<=undefined_control_sequence-1;p++)undump_hh(hash[p]);
undump_int(cs_count)

/*:1318*/
#line 24783 "texprof.w"


/*:1313*/
#line 24595 "texprof.w"
;
/*1320:*/
#line 24874 "texprof.w"

undump_size(7,font_mem_size,"font mem size",fmem_ptr);
for(k= 0;k<=fmem_ptr-1;k++)undump_wd(font_info[k]);
undump_size(font_base,font_max,"font max",font_ptr);
for(k= null_font;k<=font_ptr;k++)
/*1322:*/
#line 24912 "texprof.w"

{undump_qqqq(font_check[k]);
undump_int(font_size[k]);
undump_int(font_dsize[k]);
undump(min_halfword,max_halfword,font_params[k]);
undump_int(hyphen_char[k]);
undump_int(skew_char[k]);
undump(0,str_ptr,font_name[k]);
undump(0,str_ptr,font_area[k]);
undump(0,255,font_bc[k]);
undump(0,255,font_ec[k]);
undump_int(char_base[k]);
undump_int(width_base[k]);
undump_int(height_base[k]);
undump_int(depth_base[k]);
undump_int(italic_base[k]);
undump_int(lig_kern_base[k]);
undump_int(kern_base[k]);
undump_int(exten_base[k]);
undump_int(param_base[k]);
undump(min_halfword,lo_mem_max,font_glue[k]);
undump(0,fmem_ptr-1,bchar_label[k]);
undump(min_quarterword,non_char,font_bchar[k]);
undump(min_quarterword,non_char,font_false_bchar[k]);
}

/*:1322*/
#line 24879 "texprof.w"


/*:1320*/
#line 24596 "texprof.w"
;
/*1324:*/
#line 24968 "texprof.w"

undump(0,hyph_size,hyph_count);
for(k= 1;k<=hyph_count;k++)
{undump(0,hyph_size,j);
undump(0,str_ptr,hyph_word[j]);
undump(min_halfword,max_halfword,hyph_list[j]);
}
undump_size(0,trie_size,"trie size",j);
#ifdef INIT
trie_max= j;
#endif
#line 24979 "texprof.w"
 undump(0,j,hyph_start);
for(k= 0;k<=j;k++)undump_hh(trie[k]);
undump_size(0,trie_op_size,"trie op size",j);
#ifdef INIT
trie_op_ptr= j;
#endif
#line 24985 "texprof.w"
 for(k= 1;k<=j;k++)
{undump(0,63,hyf_distance[k]);
undump(0,63,hyf_num[k]);
undump(min_quarterword,max_quarterword,hyf_next[k]);
}
#ifdef INIT
for(k= 0;k<=255;k++)trie_used[k]= min_quarterword;
#endif
#line 24993 "texprof.w"

k= 256;
while(j> 0)
{undump(0,k-1,k);undump(1,j,x);
#ifdef INIT
trie_used[k]= qi(x);
#endif
#line 25000 "texprof.w"

j= j-x;op_start[k]= qo(j);
}
#ifdef INIT
trie_not_ready= false
#endif
#line 25006 "texprof.w"

/*:1324*/
#line 24597 "texprof.w"
;
/*1789:*/
#line 31947 "texprof.w"


{two_halves hw;
memory_word m;
int byte_count= 0;
int i,j;
char*buf;
undump_hh(hw);
file_num= hw.rh;
if(file_num> MAX_FILE_NUM)overflow("file number",file_num);
i= hw.lh;
buf= malloc(i+1);
if(buf==NULL)
{print_err("Out of memory while reading filenames from format file");
succumb;
}
for(k= 0;k<=file_num;k++)
{char*s= buf;
do
{if(byte_count==0)
{undump_wd(m);byte_count= 8;}
*s= (m.w>>56)&0xFF;m.w= m.w<<8;
byte_count--;
}while(*s++!=0);
file_num_name[k]= strdup(buf);
if(file_num_name[k]==NULL)
{print_err("Out of memory while reading filenames from format file");
succumb;
}
}
free(buf);
}


/*:1789*/
#line 24598 "texprof.w"
;
/*1792:*/
#line 32023 "texprof.w"

k= hi_mem_min;
while(k<=mem_end)
{two_halves hw;
halfword e;
undump_hh(hw);
e= hw.rh;
/*1793:*/
#line 32037 "texprof.w"

if(e&0x80000000)
fl_mem[k++]= e&~0x80000000;
else
{int i;
i= e;
while(i> 0)
{i--;k++;}
}

/*:1793*/
#line 32030 "texprof.w"

if(k<=mem_end)
{e= hw.lh;
/*1793:*/
#line 32037 "texprof.w"

if(e&0x80000000)
fl_mem[k++]= e&~0x80000000;
else
{int i;
i= e;
while(i> 0)
{i--;k++;}
}

/*:1793*/
#line 32033 "texprof.w"

}
}

/*:1792*/
#line 24599 "texprof.w"
;
/*1326:*/
#line 25014 "texprof.w"

undump(batch_mode,error_stop_mode,interaction);
if(interaction_option>=0)interaction= interaction_option;
undump(0,str_ptr,format_ident);
undump_int(x);
if((x!=69069)||eof(fmt_file))goto bad_fmt

/*:1326*/
#line 24600 "texprof.w"
;
return true;
bad_fmt:wake_up_terminal;
wterm_ln("(Fatal format file error; I'm stymied)");

return false;
}

/*:1302*//*1329:*/
#line 25048 "texprof.w"
/*1332:*/
#line 25146 "texprof.w"

static void close_files_and_terminate(void)
{int k;
/*1377:*/
#line 25835 "texprof.w"

for(k= 0;k<=15;k++)if(write_open[k])a_close(&write_file[k]);

/*:1377*//*1781:*/
#line 31720 "texprof.w"

{FILE*prof;
pack_job_name(".tprof");
prof= fopen((char*)name_of_file0,"wb");
if(prof==NULL)print_err("Unable to write the profile data\n");
else{
int i;
prof_file_line= cur_file_line;
/*1782:*/
#line 31743 "texprof.w"

fputs("TEX PROF",prof);


/*:1782*/
#line 31728 "texprof.w"

/*1783:*/
#line 31767 "texprof.w"

PUT2(file_num+1);
{int n,m;
m= 0;
for(i= 0;i<=file_num;i++)
{n= strlen(file_num_name[i]);
m+= n+1;
}
PUT2(m);
}
PUT4(cmd_count);
{int k,m;
m= k= 0;
for(i= hash_base;i<undefined_control_sequence;i++)
if(text(i)!=0)
{k++;
m+= (str_start[text(i)+1]-str_start[text(i)])+1;
}
PUT2(k);
PUT4(m);
PUT2(prof_max_depth);
}


/*:1783*/
#line 31729 "texprof.w"

/*1782:*/
#line 31743 "texprof.w"

fputs("TEX PROF",prof);


/*:1782*/
#line 31730 "texprof.w"

/*1784:*/
#line 31793 "texprof.w"

for(i= 0;i<=file_num;i++)
{fputs(file_num_name[i],prof);
PUT1(0);
}

/*:1784*/
#line 31731 "texprof.w"

/*1782:*/
#line 31743 "texprof.w"

fputs("TEX PROF",prof);


/*:1782*/
#line 31732 "texprof.w"

/*1785:*/
#line 31804 "texprof.w"

for(i= hash_base;i<undefined_control_sequence;i++)
if(text(i)!=0)
{int k;
PUT2(i);
for(k= str_start[text(i)];k<str_start[text(i)+1];k++)
PUT1(str_pool[k]);
PUT1(0);
}


/*:1785*/
#line 31733 "texprof.w"

/*1782:*/
#line 31743 "texprof.w"

fputs("TEX PROF",prof);


/*:1782*/
#line 31734 "texprof.w"

/*1787:*/
#line 31852 "texprof.w"


i= 0;
{int j= 0;
last_depth= -1;
while(i<st_count)
{int8_t c= stamp[i]>>24;
if(c==system_macro_pop)
{int n= stamp[i]&0xFFFF;
/*1786:*/
#line 31832 "texprof.w"

#if SHOW_WRITE_TIMING
printf("!%d:%d:%d>%d\n",j++,i,last_depth,last_depth-n);
#endif
#line 31836 "texprof.w"
 if(n<=10)
PUT1(system_macro_pop_0+n);
else if(n<=255)
{PUT1(system_macro_pop_small);
PUT1(n);
}
else
{PUT1(system_macro_pop);
PUT2(n);
}
last_depth= last_depth-n;

/*:1786*/
#line 31861 "texprof.w"

i++;
}
else if(c==system_macro_push)
{int d= stamp[i+1]>>16;
if(d<=last_depth)
{int n= last_depth-d+1;
/*1786:*/
#line 31832 "texprof.w"

#if SHOW_WRITE_TIMING
printf("!%d:%d:%d>%d\n",j++,i,last_depth,last_depth-n);
#endif
#line 31836 "texprof.w"
 if(n<=10)
PUT1(system_macro_pop_0+n);
else if(n<=255)
{PUT1(system_macro_pop_small);
PUT1(n);
}
else
{PUT1(system_macro_pop);
PUT2(n);
}
last_depth= last_depth-n;

/*:1786*/
#line 31868 "texprof.w"



}
#if SHOW_WRITE_TIMING
print_char('!');print_int(j++);
print_char(':');print_int(i);
print_char(':');print_int(system_macro_push);
print_char(':');print_int(d);
print_char(':');print_cs(stamp[i+1]&0xffff);
print_char(']');print_ln();
#endif
#line 31880 "texprof.w"
 PUT4(stamp[i]);i++;
PUT2(stamp[i]);i++;
last_depth= d;
}
else
{
if(c&POP_BIT)
{last_depth--;
#if SHOW_WRITE_TIMING
printf("!%d:%d:%d>%d}\n",j++,i,last_depth+1,last_depth);
#endif
#line 31891 "texprof.w"
}
#if SHOW_WRITE_TIMING
printf("!%d:%d:%d:%d>\n",j++,i,stamp[i]>>24,last_depth);
#endif
#line 31895 "texprof.w"
 PUT4(stamp[i]);i++;
PUT4(stamp[i]);i++;
}
}
}

/*:1787*/
#line 31735 "texprof.w"

/*1782:*/
#line 31743 "texprof.w"

fputs("TEX PROF",prof);


/*:1782*/
#line 31736 "texprof.w"

fclose(prof);
}
}

/*:1781*/
#line 25149 "texprof.w"
;new_line_char= -1;
#ifdef STAT
if(tracing_stats> 0)/*1333:*/
#line 25168 "texprof.w"

if(log_opened)
{wlog_ln(" ");
wlog_ln("Here is how much of TeX's memory you used:");

wlog(" %d string",str_ptr-init_str_ptr);
if(str_ptr!=init_str_ptr+1)wlog("s");
wlog_ln(" out of %d",max_strings-init_str_ptr);
wlog_ln(" %d string characters out of %d",pool_ptr-init_pool_ptr,
pool_size-init_pool_ptr);
wlog_ln(" %d words of memory out of %d",lo_mem_max-mem_min+mem_end-hi_mem_min+2,
mem_end+1-mem_min);
wlog_ln(" %d multiletter control sequences out of %d",cs_count,hash_size);
wlog(" %d words of font info for %d font",fmem_ptr,font_ptr-font_base);
if(font_ptr!=font_base+1)wlog("s");
wlog_ln(", out of %d for %d",font_mem_size,font_max-font_base);
wlog(" %d hyphenation exception",hyph_count);
if(hyph_count!=1)wlog("s");
wlog_ln(" out of %d",hyph_size);
wlog_ln(" %di,%dn,%dp,%db,%ds stack positions out of %di,%dn,%dp,%db,%ds",
max_in_stack,max_nest_stack,
max_param_stack,
max_buf_stack+1,
max_save_stack+6,
stack_size,
nest_size,
param_size,
buf_size,
save_size);
}

/*:1333*/
#line 25151 "texprof.w"
;
#endif
#line 25153 "texprof.w"
 wake_up_terminal;/*641:*/
#line 13309 "texprof.w"

while(cur_s> -1)
{if(cur_s> 0)dvi_out(pop)
else{dvi_out(eop);incr(total_pages);
}
decr(cur_s);
}
if(total_pages==0)print_nl("No pages of output.");

else{dvi_out(post);
dvi_four(last_bop);last_bop= dvi_offset+dvi_ptr-5;
dvi_four(25400000);dvi_four(473628672);
prepare_mag();dvi_four(mag);
dvi_four(max_v);dvi_four(max_h);
dvi_out(max_push/256);dvi_out(max_push%256);
dvi_out((total_pages/256)%256);dvi_out(total_pages%256);
/*642:*/
#line 13340 "texprof.w"

while(font_ptr> font_base)
{if(font_used[font_ptr])dvi_font_def(font_ptr);
decr(font_ptr);
}

/*:642*/
#line 13325 "texprof.w"
;
dvi_out(post_post);dvi_four(last_bop);dvi_out(id_byte);
k= 4+((dvi_buf_size-dvi_ptr)%4);
while(k> 0)
{dvi_out(223);decr(k);
}
/*598:*/
#line 12480 "texprof.w"

if(dvi_limit==half_buf)write_dvi(half_buf,dvi_buf_size-1);
if(dvi_ptr> 0)write_dvi(0,dvi_ptr-1)

/*:598*/
#line 13331 "texprof.w"
;
print_nl("Output written on ");slow_print(output_file_name);

print(" (");print_int(total_pages);print(" page");
if(total_pages!=1)print_char('s');
print(", ");print_int(dvi_offset+dvi_ptr);print(" bytes).");
b_close(&dvi_file);
}

/*:641*/
#line 25153 "texprof.w"
;
if(log_opened)
{wlog_cr;a_close(&log_file);selector= selector-2;
if(selector==term_only)
{print_nl("Transcript written on ");

slow_print(log_name);print_char('.');print_nl("");
}
}
}

/*:1332*//*1334:*/
#line 25202 "texprof.w"

static void final_cleanup(void)
{
int c;
c= cur_chr;if(c!=1)new_line_char= -1;
if(job_name==0)open_log_file();
while(input_ptr> 0)
if(state==token_list)end_token_list();else end_file_reading();
while(open_parens> 0)
{print(" )");decr(open_parens);
}
if(cur_level> level_one)
{print_nl("(");print_esc("end occurred ");
print("inside a group at level ");

print_int(cur_level-level_one);print_char(')');
if(eTeX_ex)show_save_groups();
}
while(cond_ptr!=null)
{print_nl("(");print_esc("end occurred ");
print("when ");print_cmd_chr(if_test,cur_if);
if(if_line!=0)
{print(" on line ");print_int(if_line);
}
print(" was incomplete)");
if_line= if_line_field(cond_ptr);
cur_if= subtype(cond_ptr);temp_ptr= cond_ptr;
cond_ptr= link(cond_ptr);free_node(temp_ptr,if_node_size);
}
if(history!=spotless)
if(((history==warning_issued)||(interaction<error_stop_mode)))
if(selector==term_and_log)
{selector= term_only;
print_nl("(see the transcript file for additional information)");

selector= term_and_log;
}
if(c==1)
{
#ifdef INIT
for(c= top_mark_code;c<=split_bot_mark_code;c++)
if(cur_mark[c]!=null)delete_token_ref(cur_mark[c]);
if(sa_mark!=null)
if(do_marks(destroy_marks,0,sa_mark))sa_mark= null;
for(c= last_box_code;c<=vsplit_code;c++)flush_node_list(disc_ptr[c]);
if(last_glue!=max_halfword)delete_glue_ref(last_glue);
store_fmt_file();return;
#endif
#line 25250 "texprof.w"
 print_nl("(\\dump is performed only by INITEX)");return;

}
}

/*:1334*//*1335:*/
#line 25255 "texprof.w"

#ifdef INIT
static void init_prim(void)
{no_new_control_sequence= false;
first= 0;
/*225:*/
#line 4781 "texprof.w"

primitive("lineskip",assign_glue,glue_base+line_skip_code);

primitive("baselineskip",assign_glue,glue_base+baseline_skip_code);

primitive("parskip",assign_glue,glue_base+par_skip_code);

primitive("abovedisplayskip",assign_glue,glue_base+above_display_skip_code);

primitive("belowdisplayskip",assign_glue,glue_base+below_display_skip_code);

primitive("abovedisplayshortskip",
assign_glue,glue_base+above_display_short_skip_code);

primitive("belowdisplayshortskip",
assign_glue,glue_base+below_display_short_skip_code);

primitive("leftskip",assign_glue,glue_base+left_skip_code);

primitive("rightskip",assign_glue,glue_base+right_skip_code);

primitive("topskip",assign_glue,glue_base+top_skip_code);

primitive("splittopskip",assign_glue,glue_base+split_top_skip_code);

primitive("tabskip",assign_glue,glue_base+tab_skip_code);

primitive("spaceskip",assign_glue,glue_base+space_skip_code);

primitive("xspaceskip",assign_glue,glue_base+xspace_skip_code);

primitive("parfillskip",assign_glue,glue_base+par_fill_skip_code);

primitive("thinmuskip",assign_mu_glue,glue_base+thin_mu_skip_code);

primitive("medmuskip",assign_mu_glue,glue_base+med_mu_skip_code);

primitive("thickmuskip",assign_mu_glue,glue_base+thick_mu_skip_code);


/*:225*//*229:*/
#line 4916 "texprof.w"

primitive("output",assign_toks,output_routine_loc);

primitive("everypar",assign_toks,every_par_loc);

primitive("everymath",assign_toks,every_math_loc);

primitive("everydisplay",assign_toks,every_display_loc);

primitive("everyhbox",assign_toks,every_hbox_loc);

primitive("everyvbox",assign_toks,every_vbox_loc);

primitive("everyjob",assign_toks,every_job_loc);

primitive("everycr",assign_toks,every_cr_loc);

primitive("errhelp",assign_toks,err_help_loc);


/*:229*//*237:*/
#line 5281 "texprof.w"

primitive("pretolerance",assign_int,int_base+pretolerance_code);

primitive("tolerance",assign_int,int_base+tolerance_code);

primitive("linepenalty",assign_int,int_base+line_penalty_code);

primitive("hyphenpenalty",assign_int,int_base+hyphen_penalty_code);

primitive("exhyphenpenalty",assign_int,int_base+ex_hyphen_penalty_code);

primitive("clubpenalty",assign_int,int_base+club_penalty_code);

primitive("widowpenalty",assign_int,int_base+widow_penalty_code);

primitive("displaywidowpenalty",
assign_int,int_base+display_widow_penalty_code);

primitive("brokenpenalty",assign_int,int_base+broken_penalty_code);

primitive("binoppenalty",assign_int,int_base+bin_op_penalty_code);

primitive("relpenalty",assign_int,int_base+rel_penalty_code);

primitive("predisplaypenalty",assign_int,int_base+pre_display_penalty_code);

primitive("postdisplaypenalty",assign_int,int_base+post_display_penalty_code);

primitive("interlinepenalty",assign_int,int_base+inter_line_penalty_code);

primitive("doublehyphendemerits",
assign_int,int_base+double_hyphen_demerits_code);

primitive("finalhyphendemerits",
assign_int,int_base+final_hyphen_demerits_code);

primitive("adjdemerits",assign_int,int_base+adj_demerits_code);

primitive("mag",assign_int,int_base+mag_code);

primitive("delimiterfactor",assign_int,int_base+delimiter_factor_code);

primitive("looseness",assign_int,int_base+looseness_code);

primitive("time",assign_int,int_base+time_code);

primitive("day",assign_int,int_base+day_code);

primitive("month",assign_int,int_base+month_code);

primitive("year",assign_int,int_base+year_code);

primitive("showboxbreadth",assign_int,int_base+show_box_breadth_code);

primitive("showboxdepth",assign_int,int_base+show_box_depth_code);

primitive("hbadness",assign_int,int_base+hbadness_code);

primitive("vbadness",assign_int,int_base+vbadness_code);

primitive("pausing",assign_int,int_base+pausing_code);

primitive("tracingonline",assign_int,int_base+tracing_online_code);

primitive("tracingmacros",assign_int,int_base+tracing_macros_code);

primitive("tracingstats",assign_int,int_base+tracing_stats_code);

primitive("tracingparagraphs",assign_int,int_base+tracing_paragraphs_code);

primitive("tracingpages",assign_int,int_base+tracing_pages_code);

primitive("tracingoutput",assign_int,int_base+tracing_output_code);

primitive("tracinglostchars",assign_int,int_base+tracing_lost_chars_code);

primitive("tracingcommands",assign_int,int_base+tracing_commands_code);

primitive("tracingrestores",assign_int,int_base+tracing_restores_code);

primitive("uchyph",assign_int,int_base+uc_hyph_code);

primitive("outputpenalty",assign_int,int_base+output_penalty_code);

primitive("maxdeadcycles",assign_int,int_base+max_dead_cycles_code);

primitive("hangafter",assign_int,int_base+hang_after_code);

primitive("floatingpenalty",assign_int,int_base+floating_penalty_code);

primitive("globaldefs",assign_int,int_base+global_defs_code);

primitive("fam",assign_int,int_base+cur_fam_code);

primitive("escapechar",assign_int,int_base+escape_char_code);

primitive("defaulthyphenchar",assign_int,int_base+default_hyphen_char_code);

primitive("defaultskewchar",assign_int,int_base+default_skew_char_code);

primitive("endlinechar",assign_int,int_base+end_line_char_code);

primitive("newlinechar",assign_int,int_base+new_line_char_code);

primitive("language",assign_int,int_base+language_code);

primitive("lefthyphenmin",assign_int,int_base+left_hyphen_min_code);

primitive("righthyphenmin",assign_int,int_base+right_hyphen_min_code);

primitive("holdinginserts",assign_int,int_base+holding_inserts_code);

primitive("errorcontextlines",assign_int,int_base+error_context_lines_code);


/*:237*//*247:*/
#line 5566 "texprof.w"

primitive("parindent",assign_dimen,dimen_base+par_indent_code);

primitive("mathsurround",assign_dimen,dimen_base+math_surround_code);

primitive("lineskiplimit",assign_dimen,dimen_base+line_skip_limit_code);

primitive("hsize",assign_dimen,dimen_base+hsize_code);

primitive("vsize",assign_dimen,dimen_base+vsize_code);

primitive("maxdepth",assign_dimen,dimen_base+max_depth_code);

primitive("splitmaxdepth",assign_dimen,dimen_base+split_max_depth_code);

primitive("boxmaxdepth",assign_dimen,dimen_base+box_max_depth_code);

primitive("hfuzz",assign_dimen,dimen_base+hfuzz_code);

primitive("vfuzz",assign_dimen,dimen_base+vfuzz_code);

primitive("delimitershortfall",
assign_dimen,dimen_base+delimiter_shortfall_code);

primitive("nulldelimiterspace",
assign_dimen,dimen_base+null_delimiter_space_code);

primitive("scriptspace",assign_dimen,dimen_base+script_space_code);

primitive("predisplaysize",assign_dimen,dimen_base+pre_display_size_code);

primitive("displaywidth",assign_dimen,dimen_base+display_width_code);

primitive("displayindent",assign_dimen,dimen_base+display_indent_code);

primitive("overfullrule",assign_dimen,dimen_base+overfull_rule_code);

primitive("hangindent",assign_dimen,dimen_base+hang_indent_code);

primitive("hoffset",assign_dimen,dimen_base+h_offset_code);

primitive("voffset",assign_dimen,dimen_base+v_offset_code);

primitive("emergencystretch",assign_dimen,dimen_base+emergency_stretch_code);


/*:247*//*264:*/
#line 5858 "texprof.w"

primitive(" ",ex_space,0);

primitive("/",ital_corr,0);

primitive("accent",accent,0);

primitive("advance",advance,0);

primitive("afterassignment",after_assignment,0);

primitive("aftergroup",after_group,0);

primitive("begingroup",begin_group,0);

primitive("char",char_num,0);

primitive("csname",cs_name,0);

primitive("delimiter",delim_num,0);

primitive("divide",divide,0);

primitive("endcsname",end_cs_name,0);

primitive("endgroup",end_group,0);

text(frozen_end_group)= text(cur_val);eqtb[frozen_end_group]= eqtb[cur_val];
primitive("expandafter",expand_after,0);

primitive("font",def_font,0);

primitive("fontdimen",assign_font_dimen,0);

primitive("halign",halign,0);

primitive("hrule",hrule,0);

primitive("ignorespaces",ignore_spaces,0);

primitive("insert",insert,0);

primitive("mark",mark,0);

primitive("mathaccent",math_accent,0);

primitive("mathchar",math_char_num,0);

primitive("mathchoice",math_choice,0);

primitive("multiply",multiply,0);

primitive("noalign",no_align,0);

primitive("noboundary",no_boundary,0);

primitive("noexpand",no_expand,0);

primitive("nonscript",non_script,0);

primitive("omit",omit,0);

primitive("parshape",set_shape,par_shape_loc);

primitive("penalty",break_penalty,0);

primitive("prevgraf",set_prev_graf,0);

primitive("radical",radical,0);

primitive("read",read_to_cs,0);

primitive("relax",relax,256);

text(frozen_relax)= text(cur_val);eqtb[frozen_relax]= eqtb[cur_val];
primitive("setbox",set_box,0);

primitive("the",the,0);

primitive("toks",toks_register,mem_bot);

primitive("vadjust",vadjust,0);

primitive("valign",valign,0);

primitive("vcenter",vcenter,0);

primitive("vrule",vrule,0);


/*:264*//*333:*/
#line 7497 "texprof.w"

primitive("par",par_end,256);

par_loc= cur_val;par_token= cs_token_flag+par_loc;

/*:333*//*375:*/
#line 8193 "texprof.w"

primitive("input",input,0);

input_loc= cur_val;input_token= cs_token_flag+input_loc;
primitive("endinput",input,1);


/*:375*//*383:*/
#line 8285 "texprof.w"

primitive("topmark",top_bot_mark,top_mark_code);

primitive("firstmark",top_bot_mark,first_mark_code);

primitive("botmark",top_bot_mark,bot_mark_code);

primitive("splitfirstmark",top_bot_mark,split_first_mark_code);

primitive("splitbotmark",top_bot_mark,split_bot_mark_code);


/*:383*//*410:*/
#line 8739 "texprof.w"

primitive("count",internal_register,mem_bot+int_val);

primitive("dimen",internal_register,mem_bot+dimen_val);

primitive("skip",internal_register,mem_bot+glue_val);

primitive("muskip",internal_register,mem_bot+mu_val);


/*:410*//*415:*/
#line 8852 "texprof.w"

primitive("spacefactor",set_aux,hmode);

primitive("prevdepth",set_aux,vmode);

primitive("deadcycles",set_page_int,0);

primitive("insertpenalties",set_page_int,1);

primitive("wd",set_box_dimen,width_offset);

primitive("ht",set_box_dimen,height_offset);

primitive("dp",set_box_dimen,depth_offset);

primitive("lastpenalty",last_item,int_val);

primitive("lastkern",last_item,dimen_val);

primitive("lastskip",last_item,glue_val);

primitive("inputlineno",last_item,input_line_no_code);

primitive("badness",last_item,badness_code);


/*:415*//*467:*/
#line 9712 "texprof.w"

primitive("number",convert,number_code);

primitive("romannumeral",convert,roman_numeral_code);

primitive("string",convert,string_code);

primitive("meaning",convert,meaning_code);

primitive("fontname",convert,font_name_code);

primitive("jobname",convert,job_name_code);


/*:467*//*486:*/
#line 10048 "texprof.w"

primitive("if",if_test,if_char_code);

primitive("ifcat",if_test,if_cat_code);

primitive("ifnum",if_test,if_int_code);

primitive("ifdim",if_test,if_dim_code);

primitive("ifodd",if_test,if_odd_code);

primitive("ifvmode",if_test,if_vmode_code);

primitive("ifhmode",if_test,if_hmode_code);

primitive("ifmmode",if_test,if_mmode_code);

primitive("ifinner",if_test,if_inner_code);

primitive("ifvoid",if_test,if_void_code);

primitive("ifhbox",if_test,if_hbox_code);

primitive("ifvbox",if_test,if_vbox_code);

primitive("ifx",if_test,ifx_code);

primitive("ifeof",if_test,if_eof_code);

primitive("iftrue",if_test,if_true_code);

primitive("iffalse",if_test,if_false_code);

primitive("ifcase",if_test,if_case_code);


/*:486*//*490:*/
#line 10140 "texprof.w"

primitive("fi",fi_or_else,fi_code);

text(frozen_fi)= text(cur_val);eqtb[frozen_fi]= eqtb[cur_val];
primitive("or",fi_or_else,or_code);

primitive("else",fi_or_else,else_code);


/*:490*//*552:*/
#line 11336 "texprof.w"

primitive("nullfont",set_font,null_font);

text(frozen_null_font)= text(cur_val);eqtb[frozen_null_font]= eqtb[cur_val];

/*:552*//*779:*/
#line 15955 "texprof.w"

primitive("span",tab_mark,span_code);

primitive("cr",car_ret,cr_code);

text(frozen_cr)= text(cur_val);eqtb[frozen_cr]= eqtb[cur_val];
primitive("crcr",car_ret,cr_cr_code);

text(frozen_end_template)= text(frozen_endv)= s_no("endtemplate");

eq_type(frozen_endv)= endv;equiv(frozen_endv)= null_list;
eq_level(frozen_endv)= level_one;
eqtb[frozen_end_template]= eqtb[frozen_endv];
eq_type(frozen_end_template)= end_template;

/*:779*//*982:*/
#line 19875 "texprof.w"

primitive("pagegoal",set_page_dimen,0);

primitive("pagetotal",set_page_dimen,1);

primitive("pagestretch",set_page_dimen,2);

primitive("pagefilstretch",set_page_dimen,3);

primitive("pagefillstretch",set_page_dimen,4);

primitive("pagefilllstretch",set_page_dimen,5);

primitive("pageshrink",set_page_dimen,6);

primitive("pagedepth",set_page_dimen,7);


/*:982*//*1051:*/
#line 21133 "texprof.w"

primitive("end",stop,0);

primitive("dump",stop,1);


/*:1051*//*1057:*/
#line 21210 "texprof.w"

primitive("hskip",hskip,skip_code);

primitive("hfil",hskip,fil_code);

primitive("hfill",hskip,fill_code);

primitive("hss",hskip,ss_code);

primitive("hfilneg",hskip,fil_neg_code);

primitive("vskip",vskip,skip_code);

primitive("vfil",vskip,fil_code);

primitive("vfill",vskip,fill_code);

primitive("vss",vskip,ss_code);

primitive("vfilneg",vskip,fil_neg_code);

primitive("mskip",mskip,mskip_code);

primitive("kern",kern,explicit);

primitive("mkern",mkern,mu_glue);


/*:1057*//*1070:*/
#line 21473 "texprof.w"

primitive("moveleft",hmove,1);

primitive("moveright",hmove,0);

primitive("raise",vmove,1);

primitive("lower",vmove,0);


primitive("box",make_box,box_code);

primitive("copy",make_box,copy_code);

primitive("lastbox",make_box,last_box_code);

primitive("vsplit",make_box,vsplit_code);

primitive("vtop",make_box,vtop_code);

primitive("vbox",make_box,vtop_code+vmode);

primitive("hbox",make_box,vtop_code+hmode);

primitive("shipout",leader_ship,a_leaders-1);

primitive("leaders",leader_ship,a_leaders);

primitive("cleaders",leader_ship,c_leaders);

primitive("xleaders",leader_ship,x_leaders);


/*:1070*//*1087:*/
#line 21768 "texprof.w"

primitive("indent",start_par,1);

primitive("noindent",start_par,0);


/*:1087*//*1106:*/
#line 21987 "texprof.w"

primitive("unpenalty",remove_item,penalty_node);

primitive("unkern",remove_item,kern_node);

primitive("unskip",remove_item,glue_node);

primitive("unhbox",un_hbox,box_code);

primitive("unhcopy",un_hbox,copy_code);

primitive("unvbox",un_vbox,box_code);

primitive("unvcopy",un_vbox,copy_code);


/*:1106*//*1113:*/
#line 22072 "texprof.w"

primitive("-",discretionary,1);

primitive("discretionary",discretionary,0);


/*:1113*//*1140:*/
#line 22421 "texprof.w"

primitive("eqno",eq_no,0);

primitive("leqno",eq_no,1);


/*:1140*//*1155:*/
#line 22658 "texprof.w"

primitive("mathord",math_comp,ord_noad);

primitive("mathop",math_comp,op_noad);

primitive("mathbin",math_comp,bin_noad);

primitive("mathrel",math_comp,rel_noad);

primitive("mathopen",math_comp,open_noad);

primitive("mathclose",math_comp,close_noad);

primitive("mathpunct",math_comp,punct_noad);

primitive("mathinner",math_comp,inner_noad);

primitive("underline",math_comp,under_noad);

primitive("overline",math_comp,over_noad);

primitive("displaylimits",limit_switch,normal);

primitive("limits",limit_switch,limits);

primitive("nolimits",limit_switch,no_limits);


/*:1155*//*1168:*/
#line 22812 "texprof.w"

primitive("displaystyle",math_style,display_style);

primitive("textstyle",math_style,text_style);

primitive("scriptstyle",math_style,script_style);

primitive("scriptscriptstyle",math_style,script_script_style);


/*:1168*//*1177:*/
#line 22911 "texprof.w"

primitive("above",above,above_code);

primitive("over",above,over_code);

primitive("atop",above,atop_code);

primitive("abovewithdelims",above,delimited_code+above_code);

primitive("overwithdelims",above,delimited_code+over_code);

primitive("atopwithdelims",above,delimited_code+atop_code);


/*:1177*//*1187:*/
#line 23039 "texprof.w"

primitive("left",left_right,left_noad);

primitive("right",left_right,right_noad);

text(frozen_right)= text(cur_val);eqtb[frozen_right]= eqtb[cur_val];

/*:1187*//*1207:*/
#line 23360 "texprof.w"

primitive("long",prefix,1);

primitive("outer",prefix,2);

primitive("global",prefix,4);

primitive("def",def,0);

primitive("gdef",def,1);

primitive("edef",def,2);

primitive("xdef",def,3);


/*:1207*//*1218:*/
#line 23552 "texprof.w"

primitive("let",let,normal);

primitive("futurelet",let,normal+1);


/*:1218*//*1221:*/
#line 23597 "texprof.w"

primitive("chardef",shorthand_def,char_def_code);

primitive("mathchardef",shorthand_def,math_char_def_code);

primitive("countdef",shorthand_def,count_def_code);

primitive("dimendef",shorthand_def,dimen_def_code);

primitive("skipdef",shorthand_def,skip_def_code);

primitive("muskipdef",shorthand_def,mu_skip_def_code);

primitive("toksdef",shorthand_def,toks_def_code);


/*:1221*//*1229:*/
#line 23762 "texprof.w"

primitive("catcode",def_code,cat_code_base);

primitive("mathcode",def_code,math_code_base);

primitive("lccode",def_code,lc_code_base);

primitive("uccode",def_code,uc_code_base);

primitive("sfcode",def_code,sf_code_base);

primitive("delcode",def_code,del_code_base);

primitive("textfont",def_family,math_font_base);

primitive("scriptfont",def_family,math_font_base+script_size);

primitive("scriptscriptfont",def_family,math_font_base+script_script_size);


/*:1229*//*1249:*/
#line 24070 "texprof.w"

primitive("hyphenation",hyph_data,0);

primitive("patterns",hyph_data,1);


/*:1249*//*1253:*/
#line 24107 "texprof.w"

primitive("hyphenchar",assign_font_int,0);

primitive("skewchar",assign_font_int,1);


/*:1253*//*1261:*/
#line 24206 "texprof.w"

primitive("batchmode",set_interaction,batch_mode);

primitive("nonstopmode",set_interaction,nonstop_mode);

primitive("scrollmode",set_interaction,scroll_mode);

primitive("errorstopmode",set_interaction,error_stop_mode);


/*:1261*//*1271:*/
#line 24272 "texprof.w"

primitive("openin",in_stream,1);

primitive("closein",in_stream,0);


/*:1271*//*1276:*/
#line 24309 "texprof.w"

primitive("message",message,0);

primitive("errmessage",message,1);


/*:1276*//*1285:*/
#line 24376 "texprof.w"

primitive("lowercase",case_shift,lc_code_base);

primitive("uppercase",case_shift,uc_code_base);


/*:1285*//*1290:*/
#line 24423 "texprof.w"

primitive("show",xray,show_code);

primitive("showbox",xray,show_box_code);

primitive("showthe",xray,show_the_code);

primitive("showlists",xray,show_lists_code);


/*:1290*//*1343:*/
#line 25455 "texprof.w"

primitive("openout",extension,open_node);

primitive("write",extension,write_node);write_loc= cur_val;

primitive("closeout",extension,close_node);

primitive("special",extension,special_node);

primitive("immediate",extension,immediate_code);

primitive("setlanguage",extension,set_language_code);


/*:1343*//*1742:*/
#line 31009 "texprof.w"

primitive("profileon",extension,profile_on_code);

primitive("profileoff",extension,profile_off_code);


/*:1742*//*1799:*/
#line 32112 "texprof.w"

if(pdf_on)
{
primitive("pdftexversion",last_item,pdftex_version_code);

primitive("pdflastobj",last_item,pdf_last_obj_code);

primitive("pdflastxform",last_item,pdf_last_xform_code);

primitive("pdflastximage",last_item,pdf_last_ximage_code);

primitive("pdflastximagepages",last_item,pdf_last_ximage_pages_code);

primitive("pdflastannot",last_item,pdf_last_annot_code);

primitive("pdfretval",last_item,pdf_retval_code);

primitive("pdflastximagecolordepth",last_item,pdf_last_ximage_colordepth_code);

primitive("pdflastlink",last_item,pdf_last_link_code);

}

/*:1799*//*1803:*/
#line 32239 "texprof.w"

if(pdf_on)
{
primitive("pdfpagesattr",assign_toks,pdf_pages_attr_loc);

primitive("pdfpageattr",assign_toks,pdf_page_attr_loc);

primitive("pdfpageresources",assign_toks,pdf_page_resources_loc);

primitive("pdfpkmode",assign_toks,pdf_pk_mode_loc);


primitive("pdfoutput",assign_int,int_base+pdf_output_code);

primitive("pdfcompresslevel",assign_int,int_base+pdf_compress_level_code);

primitive("pdfobjcompresslevel",assign_int,int_base+pdf_objcompresslevel_code);

primitive("pdfdecimaldigits",assign_int,int_base+pdf_decimal_digits_code);

primitive("pdfmovechars",assign_int,int_base+pdf_move_chars_code);

primitive("pdfimageresolution",assign_int,int_base+pdf_image_resolution_code);

primitive("pdfpkresolution",assign_int,int_base+pdf_pk_resolution_code);

primitive("pdfuniqueresname",assign_int,int_base+pdf_unique_resname_code);

primitive("pdfoptionpdfminorversion",assign_int,int_base+pdf_minor_version_code);

primitive("pdfoptionalwaysusepdfpagebox",assign_int,int_base+pdf_option_always_use_pdfpagebox_code);

primitive("pdfoptionpdfinclusionerrorlevel",assign_int,int_base+pdf_option_pdf_inclusion_errorlevel_code);

primitive("pdfmajorversion",assign_int,int_base+pdf_major_version_code);

primitive("pdfminorversion",assign_int,int_base+pdf_minor_version_code);

primitive("pdfforcepagebox",assign_int,int_base+pdf_force_pagebox_code);

primitive("pdfpagebox",assign_int,int_base+pdf_pagebox_code);

primitive("pdfinclusionerrorlevel",assign_int,int_base+pdf_inclusion_errorlevel_code);

primitive("pdfgamma",assign_int,int_base+pdf_gamma_code);


primitive("pdfimagegamma",assign_int,int_base+pdf_image_gamma_code);

primitive("pdfimagehicolor",assign_int,int_base+pdf_image_hicolor_code);

primitive("pdfimageapplygamma",assign_int,int_base+pdf_image_apply_gamma_code);

primitive("pdfadjustspacing",assign_int,int_base+pdf_adjust_spacing_code);

primitive("pdfprotrudechars",assign_int,int_base+pdf_protrude_chars_code);

primitive("pdftracingfonts",assign_int,int_base+pdf_tracing_fonts_code);

primitive("pdfadjustinterwordglue",assign_int,int_base+pdf_adjust_interword_glue_code);

primitive("pdfprependkern",assign_int,int_base+pdf_prepend_kern_code);

primitive("pdfappendkern",assign_int,int_base+pdf_append_kern_code);

primitive("pdfgentounicode",assign_int,int_base+pdf_gen_tounicode_code);

primitive("pdfdraftmode",assign_int,int_base+pdf_draftmode_code);

primitive("pdfinclusioncopyfonts",assign_int,int_base+pdf_inclusion_copy_font_code);

primitive("pdfsuppresswarningdupdest",assign_int,int_base+pdf_suppress_warning_dup_dest_code);

primitive("pdfsuppresswarningdupmap",assign_int,int_base+pdf_suppress_warning_dup_map_code);

primitive("pdfsuppresswarningpagegroup",assign_int,int_base+pdf_suppress_warning_page_group_code);

primitive("pdfinfoomitdate",assign_int,int_base+pdf_info_omit_date_code);

primitive("pdfsuppressptexinfo",assign_int,int_base+pdf_suppress_ptex_info_code);

primitive("pdfomitcharset",assign_int,int_base+pdf_omit_charset_code);

primitive("pdfomitinfodict",assign_int,int_base+pdf_omit_info_dict_code);

primitive("pdfomitprocset",assign_int,int_base+pdf_omit_procset_code);


primitive("pdfhorigin",assign_dimen,dimen_base+pdf_h_origin_code);

primitive("pdfvorigin",assign_dimen,dimen_base+pdf_v_origin_code);

primitive("pdflinkmargin",assign_dimen,dimen_base+pdf_link_margin_code);

primitive("pdfdestmargin",assign_dimen,dimen_base+pdf_dest_margin_code);

primitive("pdfthreadmargin",assign_dimen,dimen_base+pdf_thread_margin_code);

primitive("pdffirstlineheight",assign_dimen,dimen_base+pdf_first_line_height_code);

primitive("pdflastlinedepth",assign_dimen,dimen_base+pdf_last_line_depth_code);

primitive("pdfeachlineheight",assign_dimen,dimen_base+pdf_each_line_height_code);

primitive("pdfeachlinedepth",assign_dimen,dimen_base+pdf_each_line_depth_code);

primitive("pdfignoreddimen",assign_dimen,dimen_base+pdf_ignored_dimen_code);

primitive("pdfpxdimen",assign_dimen,dimen_base+pdf_px_dimen_code);

primitive("ifpdfprimitive",if_test,if_primitive_code);



}

/*:1803*//*1808:*/
#line 32457 "texprof.w"

if(pdf_on)
{
primitive("pdftexrevision",convert,pdftex_revision_code);

primitive("pdftexbanner",convert,pdftex_banner_code);

primitive("pdffontname",convert,pdf_font_name_code);

primitive("pdffontobjnum",convert,pdf_font_objnum_code);

primitive("pdffontsize",convert,pdf_font_size_code);

primitive("pdfpageref",convert,pdf_page_ref_code);

primitive("leftmarginkern",convert,left_margin_kern_code);

primitive("rightmarginkern",convert,right_margin_kern_code);

primitive("pdfxformname",convert,pdf_xform_name_code);

primitive("pdfescapestring",convert,pdf_escape_string_code);

primitive("pdfescapename",convert,pdf_escape_name_code);

primitive("pdfescapehex",convert,pdf_escape_hex_code);

primitive("pdfunescapehex",convert,pdf_unescape_hex_code);

primitive("pdfmatch",convert,pdf_match_code);

primitive("pdflastmatch",convert,pdf_last_match_code);

primitive("pdfcolorstackinit",convert,pdf_colorstack_init_code);

}

/*:1808*//*1814:*/
#line 32701 "texprof.w"

if(pdf_on)
{
primitive("pdfliteral",extension,pdf_literal_node);

primitive("pdfobj",extension,pdf_obj_code);

primitive("pdfrefobj",extension,pdf_refobj_node);

primitive("pdfxform",extension,pdf_xform_code);

primitive("pdfrefxform",extension,pdf_refxform_node);

primitive("pdfximage",extension,pdf_ximage_code);

primitive("pdfrefximage",extension,pdf_refximage_node);

primitive("pdfannot",extension,pdf_annot_node);

primitive("pdfstartlink",extension,pdf_start_link_node);

primitive("pdfendlink",extension,pdf_end_link_node);

primitive("pdfoutline",extension,pdf_outline_code);

primitive("pdfdest",extension,pdf_dest_node);

primitive("pdfthread",extension,pdf_thread_node);

primitive("pdfstartthread",extension,pdf_start_thread_node);

primitive("pdfendthread",extension,pdf_end_thread_node);


primitive("pdfinfo",extension,pdf_info_code);

primitive("pdfcatalog",extension,pdf_catalog_code);

primitive("pdfnames",extension,pdf_names_code);


primitive("pdffontattr",extension,pdf_font_attr_code);

primitive("pdfincludechars",extension,pdf_include_chars_code);

primitive("pdfmapfile",extension,pdf_map_file_code);

primitive("pdfmapline",extension,pdf_map_line_code);

primitive("pdftrailer",extension,pdf_trailer_code);

primitive("pdftrailerid",extension,pdf_trailer_id_code);


primitive("pdffontexpand",extension,pdf_font_expand_code);


primitive("pdfsnaprefpoint",extension,pdf_snap_ref_point_node);

primitive("pdfsnapy",extension,pdf_snapy_node);

primitive("pdfsnapycomp",extension,pdf_snapy_comp_node);

primitive("pdfglyphtounicode",extension,pdf_glyph_to_unicode_code);

primitive("pdfcolorstack",extension,pdf_colorstack_node);

primitive("pdfsetmatrix",extension,pdf_setmatrix_node);

primitive("pdfsave",extension,pdf_save_node);

primitive("pdfrestore",extension,pdf_restore_node);

primitive("pdfnobuiltintounicode",extension,pdf_nobuiltin_tounicode_code);

primitive("pdfinterwordspaceon",extension,pdf_interword_space_on_node);

primitive("pdfinterwordspaceoff",extension,pdf_interword_space_off_node);

primitive("pdffakespace",extension,pdf_fake_space_node);

primitive("pdfrunninglinkoff",extension,pdf_running_link_off_node);

primitive("pdfrunninglinkon",extension,pdf_running_link_on_node);

primitive("pdfspacefont",extension,pdf_space_font_code);


primitive("tracingstacklevels",extension,tracing_stack_level_code);

primitive("partokencontext",extension,pdf_par_token_context_code);

primitive("partokenname",extension,pdf_par_token_name_code);

primitive("showstream",extension,pdf_show_stream_code);

}

/*:1814*/
#line 25260 "texprof.w"
;
no_new_control_sequence= true;
}
#endif
#line 25264 "texprof.w"

/*:1335*//*1337:*/
#line 25316 "texprof.w"

#ifdef DEBUG
static void debug_help(void)
{
int k,l,m,n;
clear_terminal;
loop{wake_up_terminal;
print_nl("debug # (-1 to exit):");update_terminal;

if(fscanf(term_in.f," %d",&m)<1||
m<0)return;
else if(m==0)
{goto breakpoint;
breakpoint:m= 0;
}
else{fscanf(term_in.f," %d",&n);
switch(m){
/*1338:*/
#line 25341 "texprof.w"

case 1:print_word(mem[n]);break;
case 2:print_int(info(n));break;
case 3:print_int(link(n));break;
case 4:print_word(eqtb[n]);break;
case 5:print_word(font_info[n]);break;
case 6:print_word(save_stack[n]);break;
case 7:show_box(n);break;

case 8:{breadth_max= 10000;depth_threshold= pool_size-pool_ptr-10;
show_node_list(n);
}break;
case 9:show_token_list(n,null,1000);break;
case 10:slow_print(n);break;
case 11:check_mem(n> 0);break;
case 12:search_mem(n);break;
case 13:{fscanf(term_in.f," %d",&l);print_cmd_chr(n,l);
}break;
case 14:for(k= 0;k<=n;k++)printn(buffer[k]);break;
case 15:{font_in_short_display= null_font;short_display(n);
}break;
case 16:panicking= !panicking;break;

/*:1338*/
#line 25333 "texprof.w"

default:print("?");
}
}
}
}
#endif
#line 25340 "texprof.w"

/*:1337*//*1545:*/
#line 28211 "texprof.w"

static void Prote_initialize(void)
{int k;
/*1567:*/
#line 28420 "texprof.w"

xchg_buffer_length= 0;

/*:1567*//*1573:*/
#line 28475 "texprof.w"

incsname_state= 0;

/*:1573*//*1632:*/
#line 29090 "texprof.w"

two_to_the[0]= 1;
for(k= 1;k<=30;k++)two_to_the[k]= 2*two_to_the[k-1];
spec_log[1]= 93032640;
spec_log[2]= 38612034;
spec_log[3]= 17922280;
spec_log[4]= 8662214;
spec_log[5]= 4261238;
spec_log[6]= 2113709;
spec_log[7]= 1052693;
spec_log[8]= 525315;
spec_log[9]= 262400;
spec_log[10]= 131136;
spec_log[11]= 65552;
spec_log[12]= 32772;
spec_log[13]= 16385;
for(k= 14;k<=27;k++)spec_log[k]= two_to_the[27-k];
spec_log[28]= 1;

/*:1632*//*1647:*/
#line 29338 "texprof.w"

random_seed= sys_time;
init_randoms();

/*:1647*//*1669:*/
#line 29602 "texprof.w"

last_saved_xpos= 0;last_saved_ypos= 0;

/*:1669*//*1675:*/
#line 29650 "texprof.w"

last_save_pos_number= 0;

/*:1675*/
#line 28214 "texprof.w"
;
}

/*:1545*/
#line 25048 "texprof.w"


/*:1329*//*1331:*/
#line 25102 "texprof.w"

int main(int argc,char*argv[]){
main_init(argc,argv);
history= fatal_error_stop;
t_open_out;
if(ready_already==314159)goto start_of_TEX;
/*14:*/
#line 564 "texprof.w"

bad= 0;
if((half_error_line<30)||(half_error_line> error_line-15))bad= 1;
if(max_print_line<60)bad= 2;
if(dvi_buf_size%8!=0)bad= 3;
if(mem_bot+1100> mem_top)bad= 4;
if(hash_prime> hash_size)bad= 5;
if(max_in_open>=128)bad= 6;
if(mem_top<256+11)bad= 7;

/*:14*//*110:*/
#line 2493 "texprof.w"

#ifdef INIT
if((mem_min!=mem_bot)||(mem_max!=mem_top))bad= 10;
#endif
#line 2497 "texprof.w"

if((mem_min> mem_bot)||(mem_max<mem_top))bad= 10;
if((min_quarterword> 0)||(max_quarterword<127))bad= 11;
if((min_halfword> 0)||(max_halfword<32767))bad= 12;
if((min_quarterword<min_halfword)||
(max_quarterword> max_halfword))bad= 13;
if((mem_min<min_halfword)||(mem_max>=max_halfword)||
(mem_bot-mem_min> max_halfword+1))bad= 14;
if((font_base<min_quarterword)||(font_max> max_quarterword))bad= 15;
if(font_max> font_base+256)bad= 16;
if((save_size> max_halfword)||(max_strings> max_halfword))bad= 17;
if(buf_size> max_halfword)bad= 18;
if(max_quarterword-min_quarterword<255)bad= 19;

/*:110*//*289:*/
#line 6470 "texprof.w"

if(cs_token_flag+undefined_control_sequence> max_halfword)bad= 21;

/*:289*//*1248:*/
#line 24065 "texprof.w"

if(2*max_halfword<mem_top-mem_min)bad= 41;

/*:1248*/
#line 25108 "texprof.w"

if(bad> 0)
{wterm_ln("Ouch---my internal constants have been clobbered!"
"---case %d",bad);

exit(0);
}
get_strings_started();
initialize();
#ifdef INIT
if(iniversion)
{init_prim();
init_str_ptr= str_ptr;init_pool_ptr= pool_ptr;fix_date_and_time();}
#endif
#line 25122 "texprof.w"
 ready_already= 314159;
start_of_TEX:/*54:*/
#line 1451 "texprof.w"

selector= term_only;tally= 0;term_offset= 0;file_offset= 0;

/*:54*//*60:*/
#line 1601 "texprof.w"

wterm("%s",banner);
if(format_ident==0)wterm_ln(" (preloaded format=%s)",dump_name);
else{slow_print(format_ident);print_ln();
}
update_terminal;

/*:60*//*527:*/
#line 10731 "texprof.w"

job_name= 0;name_in_progress= false;log_opened= false;

/*:527*//*532:*/
#line 10804 "texprof.w"
output_file_name= 0;

/*:532*/
#line 25123 "texprof.w"
;
/*1336:*/
#line 25272 "texprof.w"

{/*330:*/
#line 7445 "texprof.w"

{input_ptr= 0;max_in_stack= 0;
in_open= 0;open_parens= 0;max_buf_stack= 0;
grp_stack[0]= 0;if_stack[0]= null;
param_ptr= 0;max_param_stack= 0;
first= buf_size;do{buffer[first]= 0;decr(first);}while(!(first==0));
scanner_status= normal;warning_index= null;first= 1;
state= new_line;start= 1;index= 0;line= 0;name= 0;cur_depth= 0;
force_eof= false;
align_state= 1000000;
if(!init_terminal())exit(0);
limit= last;first= last+1;
}

/*:330*/
#line 25273 "texprof.w"
;
/*1378:*/
#line 25857 "texprof.w"

#ifdef INIT
if(iniversion&&(buffer[loc]=='*'||etexp))
{no_new_control_sequence= false;
/*1379:*/
#line 25891 "texprof.w"

primitive("lastnodetype",last_item,last_node_type_code);

primitive("eTeXversion",last_item,eTeX_version_code);

primitive("eTeXrevision",convert,eTeX_revision_code);


/*:1379*//*1387:*/
#line 25944 "texprof.w"

primitive("everyeof",assign_toks,every_eof_loc);

primitive("tracingassigns",assign_int,int_base+tracing_assigns_code);

primitive("tracinggroups",assign_int,int_base+tracing_groups_code);

primitive("tracingifs",assign_int,int_base+tracing_ifs_code);

primitive("tracingscantokens",assign_int,int_base+tracing_scan_tokens_code);

primitive("tracingnesting",assign_int,int_base+tracing_nesting_code);

primitive("savingvdiscards",assign_int,int_base+saving_vdiscards_code);

primitive("savinghyphcodes",assign_int,int_base+saving_hyph_codes_code);


/*:1387*//*1393:*/
#line 26045 "texprof.w"

primitive("currentgrouplevel",last_item,current_group_level_code);

primitive("currentgrouptype",last_item,current_group_type_code);


/*:1393*//*1396:*/
#line 26067 "texprof.w"

primitive("currentiflevel",last_item,current_if_level_code);

primitive("currentiftype",last_item,current_if_type_code);

primitive("currentifbranch",last_item,current_if_branch_code);


/*:1396*//*1399:*/
#line 26103 "texprof.w"

primitive("fontcharwd",last_item,font_char_wd_code);

primitive("fontcharht",last_item,font_char_ht_code);

primitive("fontchardp",last_item,font_char_dp_code);

primitive("fontcharic",last_item,font_char_ic_code);


/*:1399*//*1402:*/
#line 26144 "texprof.w"

primitive("parshapelength",last_item,par_shape_length_code);

primitive("parshapeindent",last_item,par_shape_indent_code);

primitive("parshapedimen",last_item,par_shape_dimen_code);


/*:1402*//*1405:*/
#line 26176 "texprof.w"

primitive("showgroups",xray,show_groups);


/*:1405*//*1414:*/
#line 26347 "texprof.w"

primitive("showtokens",xray,show_tokens);


/*:1414*//*1416:*/
#line 26362 "texprof.w"

primitive("unexpanded",the,1);

primitive("detokenize",the,show_tokens);


/*:1416*//*1419:*/
#line 26388 "texprof.w"

primitive("showifs",xray,show_ifs);


/*:1419*//*1422:*/
#line 26419 "texprof.w"

primitive("interactionmode",set_page_int,2);


/*:1422*//*1427:*/
#line 26448 "texprof.w"

primitive("middle",left_right,middle_noad);


/*:1427*//*1429:*/
#line 26458 "texprof.w"

primitive("scantokens",input,2);


/*:1429*//*1441:*/
#line 26588 "texprof.w"

primitive("readline",read_to_cs,1);


/*:1441*//*1444:*/
#line 26615 "texprof.w"

primitive("unless",expand_after,1);

primitive("ifdefined",if_test,if_def_code);

primitive("ifcsname",if_test,if_cs_code);

primitive("iffontchar",if_test,if_font_char_code);


/*:1444*//*1452:*/
#line 26708 "texprof.w"

primitive("protected",prefix,8);


/*:1452*//*1460:*/
#line 26843 "texprof.w"

primitive("numexpr",last_item,eTeX_expr-int_val+int_val);

primitive("dimexpr",last_item,eTeX_expr-int_val+dimen_val);

primitive("glueexpr",last_item,eTeX_expr-int_val+glue_val);

primitive("muexpr",last_item,eTeX_expr-int_val+mu_val);


/*:1460*//*1483:*/
#line 27263 "texprof.w"

primitive("gluestretchorder",last_item,glue_stretch_order_code);

primitive("glueshrinkorder",last_item,glue_shrink_order_code);

primitive("gluestretch",last_item,glue_stretch_code);

primitive("glueshrink",last_item,glue_shrink_code);


/*:1483*//*1487:*/
#line 27302 "texprof.w"

primitive("mutoglue",last_item,mu_to_glue_code);

primitive("gluetomu",last_item,glue_to_mu_code);


/*:1487*//*1491:*/
#line 27340 "texprof.w"

primitive("marks",mark,marks_code);

primitive("topmarks",top_bot_mark,top_mark_code+marks_code);

primitive("firstmarks",top_bot_mark,first_mark_code+marks_code);

primitive("botmarks",top_bot_mark,bot_mark_code+marks_code);

primitive("splitfirstmarks",top_bot_mark,split_first_mark_code+marks_code);

primitive("splitbotmarks",top_bot_mark,split_bot_mark_code+marks_code);


/*:1491*//*1531:*/
#line 28114 "texprof.w"

primitive("pagediscards",un_vbox,last_box_code);

primitive("splitdiscards",un_vbox,vsplit_code);


/*:1531*//*1534:*/
#line 28134 "texprof.w"

primitive("interlinepenalties",set_shape,inter_line_penalties_loc);

primitive("clubpenalties",set_shape,club_penalties_loc);

primitive("widowpenalties",set_shape,widow_penalties_loc);

primitive("displaywidowpenalties",set_shape,display_widow_penalties_loc);


/*:1534*//*1538:*/
#line 28168 "texprof.w"

primitive("expanddepth",assign_int,int_base+expand_depth_code);


/*:1538*/
#line 25861 "texprof.w"

if(buffer[loc]=='*')incr(loc);
eTeX_mode= 1;
/*1495:*/
#line 27375 "texprof.w"

max_reg_num= 32767;
max_reg_help_line= "A register number must be between 0 and 32767.";

/*:1495*//*1540:*/
#line 28175 "texprof.w"

expand_depth= 10000;
expand_depth_count= 0;

/*:1540*/
#line 25864 "texprof.w"

if(buffer[loc]=='*'||ltxp){
/*1566:*/
#line 28413 "texprof.w"

if(xchg_buffer_size<64)bad= 51;

/*:1566*/
#line 25866 "texprof.w"

/*1553:*/
#line 28297 "texprof.w"

if(!pdf_on){
primitive("Proteversion",last_item,Prote_version_code);

primitive("Proterevision",convert,Prote_revision_code);

}
/*:1553*//*1568:*/
#line 28431 "texprof.w"

if(pdf_on){
primitive("pdfshellescape",last_item,shell_escape_code);

}else{primitive("shellescape",last_item,shell_escape_code);

}

/*:1568*//*1571:*/
#line 28453 "texprof.w"

primitive("ifincsname",if_test,if_incsname_code);

if(pdf_on)
primitive("ifpdfprimitive",if_test,if_primitive_code);

else primitive("ifprimitive",if_test,if_primitive_code);



/*:1571*//*1578:*/
#line 28516 "texprof.w"

if(pdf_on)
primitive("pdfprimitive",expand_after,primitive_code);

else
primitive("primitive",expand_after,primitive_code);

text(frozen_primitive)= text(cur_val);eqtb[frozen_primitive]= eqtb[cur_val];

/*:1578*//*1588:*/
#line 28643 "texprof.w"

primitive("expanded",expand_after,expanded_code);


/*:1588*//*1591:*/
#line 28669 "texprof.w"

if(pdf_on)
primitive("pdfstrcmp",convert,strcmp_code);

else
primitive("strcmp",convert,strcmp_code);



/*:1591*//*1598:*/
#line 28741 "texprof.w"

if(!pdf_on)
primitive("pdfcreationdate",convert,creation_date_code);

else
primitive("creationdate",convert,creation_date_code);



/*:1598*//*1603:*/
#line 28785 "texprof.w"

if(pdf_on){
primitive("pdfresettimer",extension,reset_timer_code);

primitive("pdfelapsedtime",last_item,elapsed_time_code);

}else{
primitive("resettimer",extension,reset_timer_code);

primitive("elapsedtime",last_item,elapsed_time_code);

}

/*:1603*//*1610:*/
#line 28851 "texprof.w"

if(pdf_on)
primitive("pdffilesize",convert,file_size_code);

else
primitive("filesize",convert,file_size_code);



/*:1610*//*1615:*/
#line 28889 "texprof.w"

if(pdf_on)
primitive("pdffilemoddate",convert,file_mod_date_code);

else
primitive("filemoddate",convert,file_mod_date_code);



/*:1615*//*1620:*/
#line 28940 "texprof.w"

if(pdf_on)
primitive("pdffiledump",convert,file_dump_code);

else
primitive("filedump",convert,file_dump_code);



/*:1620*//*1625:*/
#line 29014 "texprof.w"

if(pdf_on)
primitive("pdfmdfivesum",convert,mdfive_sum_code);

else
primitive("mdfivesum",convert,mdfive_sum_code);



/*:1625*//*1644:*/
#line 29314 "texprof.w"

if(pdf_on)
primitive("pdfrandomseed",last_item,random_seed_code);

else
primitive("randomseed",last_item,random_seed_code);



/*:1644*//*1648:*/
#line 29346 "texprof.w"

if(pdf_on)
primitive("pdfsetrandomseed",convert,set_random_seed_code);

else
primitive("setrandomseed",convert,set_random_seed_code);



/*:1648*//*1655:*/
#line 29430 "texprof.w"

if(pdf_on)
primitive("pdfuniformdeviate",convert,uniform_deviate_code);

else
primitive("uniformdeviate",convert,uniform_deviate_code);



/*:1655*//*1662:*/
#line 29522 "texprof.w"

if(pdf_on)
primitive("pdfnormaldeviate",convert,normal_deviate_code);

else
primitive("normaldeviate",convert,normal_deviate_code);



/*:1662*//*1667:*/
#line 29577 "texprof.w"

if(!pdf_on){
primitive("pdfpagewidth",assign_dimen,dimen_base+page_width_code);

primitive("pdfpageheight",assign_dimen,dimen_base+page_height_code);

}else{
primitive("pagewidth",assign_dimen,dimen_base+page_width_code);

primitive("pageheight",assign_dimen,dimen_base+page_height_code);

}



/*:1667*//*1671:*/
#line 29609 "texprof.w"

if(!pdf_on){
primitive("pdflastxpos",last_item,last_xpos_code);

primitive("lastypos",last_item,last_ypos_code);

}else{
primitive("lastxpos",last_item,last_xpos_code);

primitive("lastypos",last_item,last_ypos_code);

}

/*:1671*//*1676:*/
#line 29653 "texprof.w"

if(pdf_on)
primitive("pdfsavepos",extension,save_pos_code);

else
primitive("savepos",extension,save_pos_code);



/*:1676*/
#line 25867 "texprof.w"

if(buffer[loc]=='*')incr(loc);
Prote_mode= 1;
}
}
#endif
#line 25873 "texprof.w"

if(!no_new_control_sequence)
no_new_control_sequence= true;else

/*:1378*/
#line 25274 "texprof.w"

if((format_ident==0)||(buffer[loc]=='&'))
{if(format_ident!=0)initialize();
if(!open_fmt_file())exit(0);
if(!load_fmt_file())
{w_close(&fmt_file);exit(0);
}
w_close(&fmt_file);
while((loc<limit)&&(buffer[loc]==' '))incr(loc);
}
if(eTeX_ex)wterm_ln("entering extended mode");
if(Prote_ex){Prote_initialize();
}
if(end_line_char_inactive)decr(limit);
else buffer[limit]= end_line_char;
fix_date_and_time();
/*74:*/
#line 1816 "texprof.w"

if(interaction==batch_mode)selector= no_print;else selector= term_only

/*:74*/
#line 25290 "texprof.w"
;
if((loc<limit)&&(cat_code(buffer[loc])!=escape))start_input();

}

/*:1336*/
#line 25124 "texprof.w"
;
history= spotless;
main_control();
final_cleanup();
close_files_and_terminate();
ready_already= 0;
return 0;}

/*:1331*//*1687:*/
#line 29769 "texprof.w"
/*1695:*/
#line 29914 "texprof.w"

static struct option long_options[]= {
{"help",0,0,0},
{"version",0,0,0},
{"interaction",1,0,0},
{"mktex",1,0,0},
{"no-mktex",1,0,0},
{"kpathsea-debug",1,0,0},
{"progname",1,0,0},
{"fmt",1,0,0},
{"output-directory",1,0,0},
{"jobname",1,0,0},
{"cnf-line",1,0,0},
{"ini",0,&iniversion,1},
{"etex",0,&etexp,1},
{"ltx",0,&ltxp,1},
{"recorder",0,&recorder_enabled,1},
{"parse-first-line",0,&parsefirstlinep,1},
{"no-parse-first-line",0,&parsefirstlinep,0},
{"file-line-error",0,&filelineerrorstylep,1},
{"no-file-line-error",0,&filelineerrorstylep,0},
/*1740:*/
#line 30996 "texprof.w"

{"prof",0,&profile_on,1},

/*:1740*//*1796:*/
#line 32079 "texprof.w"

{"pdf",0,0,0},

/*:1796*/
#line 29935 "texprof.w"

{0,0,0,0}};


/*:1695*/
#line 29769 "texprof.w"

/*1691:*/
#line 29814 "texprof.w"

static void usage_help(void)
{/*1692:*/
#line 29824 "texprof.w"

fprintf(stdout,
"Usage: %s [OPTION]... [TEXNAME[.tex]] [COMMANDS]\n"
"   or: %s [OPTION]... \\FIRST-LINE\n"
"   or: %s [OPTION]... &FMT ARGS\n\n",
argv[0],argv[0],argv[0]);
fprintf(stdout,
"  Run TeX on TEXNAME, creating TEXNAME.dvi.\n"
"  Any remaining COMMANDS are processed\n"
"  as TeX input after TEXNAME is read.\n"
"  If the first line of TEXNAME starts with %%&FMT, and FMT is\n"
"  an existing .fmt file, use it. Else use `NAME.fmt', where\n"
"  NAME is the program invocation name.\n"
"\n"
"  Alternatively, if the first non-option argument begins\n"
"  with a backslash, interpret all non-option arguments as\n"
"  a line of TeX input.\n"
"\n"
"  Alternatively, if the first non-option argument begins\n"
"  with a &, the next word is taken as the FMT to read,\n"
"  overriding all else.  Any remaining arguments are\n"
"  processed as above.\n"
"\n"
"  If no arguments or options are specified, prompt for input.\n"
"\n");


/*:1692*/
#line 29816 "texprof.w"

fprintf(stdout,"Options:\n"/*1693:*/
#line 29854 "texprof.w"

" -help                 "
"\t display this help and exit\n"
" -version              "
"\t output version information and exit\n"
" -etex                 "
"\t enable e-TeX extensions\n"
" -ltx                 "
"\t enable LaTeX extensions, implies -etex\n"
" -ini                  "
"\t be initex for dumping formats; this is\n"
"\t\t\t also true if the program name is `kinitex'\n"
" -progname=STRING      "
"\t set program (and fmt) name to STRING\n"
" -fmt=FMTNAME          "
"\t use FMTNAME instead of program name or a %%& line\n"
" -output-directory=DIR "
"\t use existing DIR as the directory to write files to\n"
" -jobname=STRING       "
"\t set the TeX \\jobname to STRING\n"
" [-no]-mktex=FMT       "
"\t disable/enable mktexFMT generation (FMT=tex/tfm/fmt)\n"
" -interaction=STRING   "
"\t set interaction mode (STRING=batchmode/\n"
"\t\t\t nonstopmode/scrollmode/errorstopmode)\n"
" -kpathsea-debug=NUMBER"
"\t set path searching debugging flags according\n"
"\t\t\t to the bits of NUMBER\n"
" -recorder"
"\t\t enable filename recorder\n"
" [-no]-parse-first-line"
"\t disable/enable parsing of the first line of\n"
"\t\t\t the input file\n"
" [-no]-file-line-error"
"\t disable/enable file:line:error style\n"
" -cnf-line=STRING"
"\t process STRING like a line in texmf.cnf\n"


/*:1693*//*1739:*/
#line 30990 "texprof.w"

" -prof                 "
"\t enable profiling\n"

/*:1739*//*1794:*/
#line 32061 "texprof.w"

" -pdf                 "
"\t pretend to be pdftex; requires -ini; implies -ltx\n"

/*:1794*/
#line 29817 "texprof.w"
);
fprintf(stdout,"\nFor further information and reporting bugs see https://hint.userweb.mwn.de/\n");
exit(0);
}

/*:1691*//*1705:*/
#line 30060 "texprof.w"

static char*normalize_quotes(const char*nom,const char*mesg)
{int quoted= false;
int must_quote= (strchr(nom,' ')!=NULL);
char*ret= xmalloc(strlen(nom)+3);
char*p= ret;
const char*q;

if(must_quote)
*p++= '"';
for(q= nom;*q;q++)
if(*q=='"')
quoted= !quoted;
else
*p++= *q;

if(must_quote)
*p++= '"';
*p= '\0';
if(quoted){
fprintf(stderr,"! Unbalanced quotes in %s %s\n",mesg,nom);
exit(1);
}
return ret;
}

/*:1705*//*1709:*/
#line 30157 "texprof.w"

static char*recorder_name= NULL;
static FILE*recorder_file= NULL;
static void
recorder_start(void)
{char*cwd;
char pid_str[MAX_INT_LENGTH];
sprintf(pid_str,"%ld",(long)getpid());
recorder_name= concat3(kpse_program_name,pid_str,".fls");
if(output_directory){
char*temp= concat3(output_directory,DIR_SEP_STRING,recorder_name);
free(recorder_name);
recorder_name= temp;
}
recorder_file= xfopen(recorder_name,FOPEN_W_MODE);
cwd= xgetcwd();
fprintf(recorder_file,"PWD %s\n",cwd);
free(cwd);
}

/*:1709*//*1712:*/
#line 30188 "texprof.w"

static void
recorder_change_filename(const char*new_name)
{char*temp= NULL;
if(!recorder_file)
return;
#if defined(_WIN32)
fclose(recorder_file);
#endif 
#line 30197 "texprof.w"
if(output_directory){
temp= concat3(output_directory,DIR_SEP_STRING,new_name);
new_name= temp;
}

#if defined(_WIN32)
remove(new_name);
#endif 
#line 30205 "texprof.w"
rename(recorder_name,new_name);
free(recorder_name);
recorder_name= xstrdup(new_name);
#if defined(_WIN32)
recorder_file= xfopen(recorder_name,FOPEN_A_MODE);
#endif 
#line 30211 "texprof.w"
if(temp)
free(temp);
}

/*:1712*//*1713:*/
#line 30220 "texprof.w"

static void
recorder_record_name(const char*pfx,const char*fname)
{if(recorder_enabled){
if(!recorder_file)
recorder_start();
fprintf(recorder_file,"%s %s\n",pfx,fname);
fflush(recorder_file);
}
}


static void
recorder_record_input(const char*fname)
{recorder_record_name("INPUT",fname);
}

static void
recorder_record_output(const char*fname)
{recorder_record_name("OUTPUT",fname);
}

/*:1713*//*1718:*/
#line 30292 "texprof.w"

static void add_cnf_line(char*arg)
{cnf_count++;
cnf_lines= xrealloc(cnf_lines,sizeof(char*)*cnf_count);
cnf_lines[cnf_count-1]= arg;
}

/*:1718*//*1721:*/
#line 30346 "texprof.w"

#ifdef WIN32
static void clean_windows_filename(char*filename)
{if(strlen(filename)> 2&&isalpha(filename[0])&&
filename[1]==':'&&filename[2]=='\\')
{char*pp;
for(pp= filename;*pp;pp++)
if(*pp=='\\')
*pp= '/';
}
}
#endif
#line 30358 "texprof.w"

static char*find_file(char*fname,kpse_file_format_type t,int mx)
{char*filename;
int final_quote= (int)strlen(fname)-1;
int quoted= final_quote> 1&&fname[0]=='"'&&fname[final_quote]=='"';
if(quoted){

fname[final_quote]= '\0';
fname++;
}
filename= kpse_find_file(fname,t,mx);
if(full_name_of_file!=NULL)
{free(full_name_of_file);full_name_of_file= NULL;}
if(filename!=NULL)
full_name_of_file= strdup(filename);
if(quoted){

fname--;
fname[final_quote]= '"';
}
return filename;
}

static char*get_input_file_name(void)
{
char*input_file_name= NULL;

if(argv[optind]&&argv[optind][0]!='&'&&argv[optind][0]!='\\')
{
#ifdef WIN32
clean_windows_filename(argv[optind]);
#endif
#line 30390 "texprof.w"
 argv[optind]= normalize_quotes(argv[optind],"input file");
input_file_name= find_file(argv[optind],kpse_tex_format,false);
}
return input_file_name;
}


/*:1721*//*1724:*/
#line 30427 "texprof.w"

static int texmf_yesno(const char*var)
{
char*value= kpse_var_value(var);
return value&&(*value=='t'||*value=='y'||*value=='1');
}

/*:1724*//*1728:*/
#line 30501 "texprof.w"

static void parse_first_line(char*filename)
{FILE*f= NULL;
if(filename==NULL)return;
f= open_in(filename,kpse_tex_format,"r");
if(f!=NULL)
{char*r,*s,*t= read_line(f);
xfclose(f,filename);
if(t==NULL)return;
s= t;
if(s[0]=='%'&&s[1]=='&'){
s= s+2;
while(ISBLANK(*s))++s;
r= s;
while(*s!=0&&*s!=' '&&*s!='\r'&&*s!='\n')s++;
*s= 0;
if(dump_name==NULL){
char*f_name= concat(r,".fmt");
char*d_name= kpse_find_file(f_name,kpse_fmt_format,false);
if(d_name&&kpse_readable_file(d_name)){
dump_name= xstrdup(r);
kpse_reset_program_name(dump_name);
}
free(f_name);
}
}
free(t);
}
}

/*:1728*//*1729:*/
#line 30550 "texprof.w"

static void input_add_char(unsigned int c)
{if(last>=max_buf_stack)
{max_buf_stack= last+1;
if(max_buf_stack==buf_size)
/*35:*/
#line 1085 "texprof.w"

if(format_ident==0)
{write_ln(term_out,"Buffer size exceeded!");exit(0);

}
else{cur_input.loc_field= first;cur_input.limit_field= last-1;
overflow("buffer size",buf_size);

}

/*:35*/
#line 30555 "texprof.w"
;
}
buffer[last]= xord[c];incr(last);
}

static void input_add_str(const char*str)
{int prev_last;
while(*str==' ')str++;
prev_last= last;
while(*str!=0)

input_add_char(*str++);
for(--last;last>=first;--last)
{char c= buffer[last];
if((c)!=' '&&(c)!='\r'&&(c)!='\n')break;
}
last++;
if(last> prev_last)input_add_char(' ');
}

static int input_command_line(void)
{
last= first;
while(optind<argc)input_add_str(argv[optind++]);
loc= first;
return(loc<last);
}

/*:1729*//*1732:*/
#line 30659 "texprof.w"

static void update_name_of_file(const char*s,int k)
{int j;
if(k<=file_name_size)name_length= k;
else name_length= file_name_size;
for(j= 0;j<name_length;j++)name_of_file[j+1]= xchr[(int)s[j]];
name_of_file[name_length+1]= 0;
}

/*:1732*//*1733:*/
#line 30673 "texprof.w"

static FILE*open_in(char*filename,kpse_file_format_type t,const char*rwb)
{char*fname= NULL;
FILE*f= NULL;
fname= find_file(filename,t,true);
if(fname!=NULL)
{
f= fopen(fname,rwb);
if(f!=NULL)recorder_record_input(fname);
if(full_name_of_file!=NULL)free(full_name_of_file);
full_name_of_file= fname;
}
return f;
}

static bool a_open_in(alpha_file*f)
{f->f= open_in((char*)name_of_file+1,kpse_tex_format,"r");
if(f->f!=NULL)get(*f);
return f->f!=NULL&&ferror(f->f)==0;
}

static bool b_open_in(byte_file*f)
{f->f= open_in((char*)name_of_file+1,kpse_tfm_format,"rb");
if(f->f!=NULL)get(*f);
return f->f!=NULL&&ferror(f->f)==0;
}

static bool w_open_in(word_file*f)
{
f->f= NULL;
if(name_of_file[1]!=0)
f->f= open_in((char*)name_of_file+1,kpse_fmt_format,"rb");
if(f->f!=NULL)get(*f);
return f->f!=NULL&&ferror(f->f)==0;
}

/*:1733*//*1738:*/
#line 30825 "texprof.w"


static void
make_time_str(time_t t,bool utc)
{
struct tm lt,gmt;
size_t size;
int off,off_hours,off_mins;


if(utc){
lt= *gmtime(&t);
}
else{
lt= *localtime(&t);
}
size= strftime(time_str,TIME_STR_SIZE,"D:%Y%m%d%H%M%S",&lt);

if(size==0){

time_str[0]= '\0';
return;
}




if(time_str[14]=='6'){
time_str[14]= '5';
time_str[15]= '9';
time_str[16]= '\0';
}


gmt= *gmtime(&t);


off= 60*(lt.tm_hour-gmt.tm_hour)+lt.tm_min-gmt.tm_min;
if(lt.tm_year!=gmt.tm_year){
off+= (lt.tm_year> gmt.tm_year)?1440:-1440;
}else if(lt.tm_yday!=gmt.tm_yday){
off+= (lt.tm_yday> gmt.tm_yday)?1440:-1440;
}

if(off==0){
time_str[size++]= 'Z';
time_str[size]= 0;
}else{
off_hours= off/60;
off_mins= abs(off-off_hours*60);
snprintf(&time_str[size],TIME_STR_SIZE-size,"%+03d'%02d'",off_hours,off_mins);
}
}

static void get_creation_date(void)
{make_time_str(start_time,source_date_epoch!=NULL);
}


#ifdef WIN32
static struct _stat file_stat;
#define GET_FILE_STAT _stat(fname,&file_stat)
#else
#line 30888 "texprof.w"
 static struct stat file_stat;
#define GET_FILE_STAT stat(fname,&file_stat)
#endif
#line 30891 "texprof.w"


static char*find_input_file(void)
{char*fname;
int r;
if(output_directory&&!kpse_absolute_p((char*)name_of_file0,false))
{int r= -1;
fname= concat3(output_directory,DIR_SEP_STRING,(char*)name_of_file0);
r= GET_FILE_STAT;
if(r==0)
return fname;
free(fname);
}
fname= kpse_find_tex((char*)name_of_file0);
if(fname!=NULL)
{r= GET_FILE_STAT;
if(r==0)
return fname;
free(fname);
}
fname= (char*)name_of_file0;
r= GET_FILE_STAT;
if(r==0)
return strdup(fname);
return NULL;
}


static void get_file_mod_date(void)
{char*fname= NULL;
fname= find_input_file();
time_str[0]= 0;
if(fname!=NULL)
{make_time_str(file_stat.st_mtime,source_date_epoch!=NULL&&force_source_date!=NULL);
free(fname);
}
}

static int get_file_size(void)
{int s= -1;
char*fname= NULL;
fname= find_input_file();
if(fname!=NULL)
{s= file_stat.st_size;
free(fname);
}
return s;
}


static int get_md5_sum(int s,int file)
{md5_state_t st;
memset(md5_digest,0,DIGEST_SIZE);
if(file)
{char*fname;
pack_file_name(s,empty_string,empty_string,NULL);
fname= find_input_file();
if(fname!=NULL)
{FILE*f;
f= fopen(fname,"rb");
if(f!=NULL)
{int r;
char file_buf[FILE_BUF_SIZE];
recorder_record_input(fname);
md5_init(&st);
while((r= fread(&file_buf,1,FILE_BUF_SIZE,f))> 0)
md5_append(&st,(const md5_byte_t*)file_buf,r);
md5_finish(&st,md5_digest);
fclose(f);
}
free(fname);
}
else
return 0;
}
else
{md5_init(&st);
md5_append(&st,(md5_byte_t*)&str_pool[str_start[s]],
str_start[s+1]-str_start[s]);
md5_finish(&st,md5_digest);
}
return DIGEST_SIZE;
}

/*:1738*/
#line 29770 "texprof.w"

/*1689:*/
#line 29783 "texprof.w"

static void main_init(int ac,char*av[])
{
char*main_input_file;
argc= ac;
argv= av;
interaction= error_stop_mode;
kpse_record_input= recorder_record_input;
kpse_record_output= recorder_record_output;

/*1698:*/
#line 29966 "texprof.w"

#if defined(WIN32)
{char*enc;
kpse_set_program_name(argv[0],NULL);
enc= kpse_var_value("command_line_encoding");
get_command_line_args_utf8(enc,&argc,&argv);
parse_options(argc,argv);
/*1715:*/
#line 30253 "texprof.w"

if(recorder_enabled){
char**p= kpse_find_file_generic("texmf.cnf",kpse_cnf_format,0,1);
if(p&&*p){
char**pp= p;
while(*p){
recorder_record_input(*p);
free(*p);
p++;
}
free(pp);
}
}




/*:1715*/
#line 29973 "texprof.w"

}
#else
#line 29976 "texprof.w"
 parse_options(ac,av);
#endif
#line 29978 "texprof.w"


/*:1698*/
#line 29793 "texprof.w"

/*1720:*/
#line 30321 "texprof.w"

if(!user_progname)
user_progname= dump_name;
#if defined(WIN32)
if(user_progname)
kpse_reset_program_name(user_progname);
#else
#line 30328 "texprof.w"
 kpse_set_program_name(argv[0],user_progname);
#endif
#line 30330 "texprof.w"
 xputenv("engine","texprof");


/*:1720*/
#line 29794 "texprof.w"

/*1719:*/
#line 30302 "texprof.w"

#if 1 
{int i;
for(i= 0;i<cnf_count;i++)
kpathsea_cnf_line_env_progname(kpse_def,cnf_lines[i]);
free(cnf_lines);
}
#endif
#line 30310 "texprof.w"


/*:1719*/
#line 29795 "texprof.w"

/*1722:*/
#line 30400 "texprof.w"

main_input_file= get_input_file_name();

#ifdef WIN32

if(main_input_file==NULL){
char*file_name= argv[argc-1];
if(file_name&&file_name[0]!='-'&&file_name[0]!='&'&&file_name[0]!='\\'){
clean_windows_filename(file_name);
file_name= normalize_quotes(file_name,"argument");
main_input_file= find_file(file_name,kpse_tex_format,false);
argv[argc-1]= file_name;
}
}
#endif
#line 30415 "texprof.w"


/*:1722*/
#line 29796 "texprof.w"

/*1723:*/
#line 30420 "texprof.w"

if(filelineerrorstylep<0)
filelineerrorstylep= texmf_yesno("file_line_error_style");
if(parsefirstlinep<0)
parsefirstlinep= texmf_yesno("parse_first_line");

/*:1723*/
#line 29797 "texprof.w"

/*1727:*/
#line 30477 "texprof.w"

if(parsefirstlinep&&!dump_name)
parse_first_line(main_input_file);
if(!main_input_file&&argv[1]&&argv[1][0]=='&')
dump_name= argv[1]+1;
if(strcmp(kpse_program_name,"kinitex")==0)iniversion= true;
else if(strcmp(kpse_program_name,"kvirtex")==0&&!dump_name)
dump_name= "ktex";
if(!dump_name)
dump_name= kpse_program_name;
if(!dump_name)
{fprintf(stderr,"Unable to determine format name\n");
exit(1);
}
if(ltxp)etexp= 1;
if(etexp&&!iniversion)
{fprintf(stderr,"-etex and -ltx require -ini\n");
exit(1);
}

/*:1727*/
#line 29798 "texprof.w"

/*1735:*/
#line 30739 "texprof.w"

kpse_set_program_enabled(kpse_tfm_format,MAKE_TEX_TFM_BY_DEFAULT,
kpse_src_compile);
kpse_set_program_enabled(kpse_tex_format,MAKE_TEX_TEX_BY_DEFAULT,
kpse_src_compile);
kpse_set_program_enabled(kpse_fmt_format,MAKE_TEX_FMT_BY_DEFAULT,
kpse_src_compile);



/*:1735*/
#line 29799 "texprof.w"

}

/*:1689*//*1696:*/
#line 29944 "texprof.w"

static void parse_options(int argc,char*argv[])
{while(true){
int option_index;
int g= getopt_long_only(argc,argv,"+",long_options,&option_index);
if(g==0)
{/*1700:*/
#line 30000 "texprof.w"

if(ARGUMENT_IS("help"))usage_help();
else if(ARGUMENT_IS("version")){
printf(TeX_banner"\n"
"Prote version "Prote_version_string"\n");
exit(0);
}


/*:1700*//*1701:*/
#line 30014 "texprof.w"

else if(ARGUMENT_IS("interaction")){
if(STREQ(optarg,"batchmode"))interaction_option= batch_mode;
else if(STREQ(optarg,"nonstopmode"))interaction_option= nonstop_mode;
else if(STREQ(optarg,"scrollmode"))interaction_option= scroll_mode;
else if(STREQ(optarg,"errorstopmode"))interaction_option= error_stop_mode;
else WARNING1("Ignoring unknown argument `%s' to --interaction",optarg);
}

/*:1701*//*1702:*/
#line 30026 "texprof.w"

else if(ARGUMENT_IS("mktex"))kpse_maketex_option(optarg,true);
else if(ARGUMENT_IS("no-mktex"))kpse_maketex_option(optarg,false);


/*:1702*//*1703:*/
#line 30035 "texprof.w"

else if(ARGUMENT_IS("kpathsea-debug"))
kpathsea_debug|= atoi(optarg);



/*:1703*//*1704:*/
#line 30044 "texprof.w"

else if(ARGUMENT_IS("progname"))
user_progname= normalize_quotes(optarg,"program name");
else if(ARGUMENT_IS("fmt"))
dump_name= normalize_quotes(optarg,"format name");
else if(ARGUMENT_IS("output-directory"))
output_directory= normalize_quotes(optarg,"output directory");
else if(ARGUMENT_IS("jobname"))
c_job_name= normalize_quotes(optarg,"job name");

/*:1704*//*1717:*/
#line 30285 "texprof.w"

else if(ARGUMENT_IS("cnf-line"))
add_cnf_line(optarg);

/*:1717*//*1795:*/
#line 32071 "texprof.w"

else if(ARGUMENT_IS("pdf"))
if(iniversion)pdf_on= ltxp= true;
else
{fprintf(stderr,"-pdf requires -ini; try -ini -pdf\n");
exit(1);
}

/*:1795*/
#line 29950 "texprof.w"
}
else if(g=='?')
{fprintf(stderr,"Try '%s --help' for more information\n",argv[0]);
exit(1);
}
else if(g==-1)break;
}
/*1706:*/
#line 30093 "texprof.w"

if(output_directory)
xputenv("TEXMF_OUTPUT_DIRECTORY",output_directory);
else if(getenv("TEXMF_OUTPUT_DIRECTORY"))
output_directory= getenv("TEXMF_OUTPUT_DIRECTORY");

/*:1706*/
#line 29957 "texprof.w"

}

/*:1696*//*1731:*/
#line 30598 "texprof.w"

static FILE*open_out(const char*file_name,const char*file_mode)
{FILE*f= NULL;
char*new_name= NULL;
int absolute= kpse_absolute_p(file_name,false);
if(absolute)
{f= fopen(file_name,file_mode);
if(f!=NULL)recorder_record_output(file_name);
return f;
}
if(output_directory)
{new_name= concat3(output_directory,DIR_SEP_STRING,file_name);
f= fopen(new_name,file_mode);
if(f==NULL){free(new_name);new_name= NULL;}
}
if(f==NULL)
f= fopen(file_name,file_mode);
if(f==NULL)
{const char*texmfoutput= kpse_var_value("TEXMFOUTPUT");
if(texmfoutput!=NULL&&texmfoutput[0]!=0)
{new_name= concat3(texmfoutput,DIR_SEP_STRING,file_name);
f= fopen(new_name,file_mode);
if(f==NULL){free(new_name);new_name= NULL;}
}
}
if(f!=NULL&&new_name!=NULL)
update_name_of_file(new_name,(int)strlen(new_name));
if(f!=NULL)recorder_record_output((char*)name_of_file+1);
if(new_name!=NULL)free(new_name);
return f;
}

static bool a_open_out(alpha_file*f)
{f->f= open_out((char*)name_of_file+1,"w");
return f->f!=NULL&&ferror(f->f)==0;
}

static bool b_open_out(byte_file*f)
{f->f= open_out((char*)name_of_file+1,"wb");
return f->f!=NULL&&ferror(f->f)==0;
}

#ifdef INIT
static bool w_open_out(word_file*f)
{f->f= open_out((char*)name_of_file+1,"wb");
return f->f!=NULL&&ferror(f->f)==0;
}
#endif
#line 30646 "texprof.w"


/*:1731*//*1734:*/
#line 30716 "texprof.w"

static bool open_fmt_file(void)
{int j= loc;
if(buffer[loc]=='&')
{incr(loc);j= loc;buffer[last]= ' ';
while(buffer[j]!=' ')incr(j);
update_name_of_file((char*)buffer+loc,j-loc);
if(w_open_in(&fmt_file))goto found;
}
update_name_of_file(dump_name,(int)strlen(dump_name));
if(w_open_in(&fmt_file))goto found;
name_of_file[1]= 0;
wake_up_terminal;
wterm_ln("I can't find a format file!");
return false;
found:loc= j;return true;
}


/*:1734*/
#line 29771 "texprof.w"


/*:1687*/
