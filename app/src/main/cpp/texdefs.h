/*5:*/
#line 261 ".\\dummy.w"

#ifndef _TEXDEF_H_
#define _TEXDEF_H_
/*12:*/
#line 352 ".\\dummy.w"

#include "basetypes.h"
#include "error.h"
#include <string.h> 
#include <math.h> 

#define odd(X)       ((X)&1)
#define chr(X)       ((unsigned char)(X))
#define ord(X)       ((int)(X))
#define abs(X)       ((X)> -(X)?(X):-(X))
#define round(X)     ((int)((X)>=0.0?floor((X)+0.5):ceil((X)-0.5)))

#if __SIZEOF_FLOAT__==4
typedef float float32_t;
#else
#error  float type must have size 4
#endif

#define banner "This is TeX, Version 3.14159265 (HINT)" \

#define mem_bot 0 \

#define mem_top mem_max \
 \

#define font_base 0 \

#define hash_size 15000 \

#define hash_prime 12721
#define hyph_size 307 \
 \

#define done6 36
#define incr(X) X= X+1
#define decr(X) X= X-1
#define negate(X) X= -X
#define loop while(true) 
#define do_nothing 
#define empty 0 \

#define first_text_char 0
#define last_text_char 255 \

#define null_code 00
#define carriage_return 015
#define invalid_code 0177 \

#define reset_OK(X) erstat(X) ==0
#define rewrite_OK(X) erstat(X) ==0 \

#define t_open_in term_in.f= stdin
#define t_open_out term_out.f= stdout \

#define update_terminal fflush(term_out.f) 
#define clear_terminal fflush(term_in.f) 
#define wake_up_terminal do_nothing \

#define loc cur_input.loc_field \

#define si(X) X
#define so(X) X \

#define length(X) (str_start[X+1]-str_start[X])  \
 \

#define cur_length (pool_ptr-str_start[str_ptr])  \

#define append_char(X)  \
{str_pool[pool_ptr]= si(X) ;incr(pool_ptr) ; \
}
#define flush_char decr(pool_ptr) 
#define str_room(X)  \
{if(pool_ptr+X> pool_size)  \
overflow("pool size",pool_size-init_pool_ptr) ; \
 \
} \

#define flush_string {decr(str_ptr) ;pool_ptr= str_start[str_ptr]; \
} \

#define app_lc_hex(X) l= X; \
if(l<10) append_char(l+'0') else append_char(l-10+'a')  \

#define bad_pool(X) {wake_up_terminal;write_ln(term_out,X) ; \
a_close(&pool_file) ;return false; \
}
#define no_print 16
#define term_only 17
#define log_only 18
#define term_and_log 19
#define pseudo 20
#define new_string 21
#define max_selector 21 \

#define print_ASCII print \

#define prompt_input(X) {wake_up_terminal;print_str(X) ;term_input() ; \
} \

#define batch_mode 0
#define nonstop_mode 1
#define scroll_mode 2
#define error_stop_mode 3
#define print_err(X) {if(interaction==error_stop_mode) wake_up_terminal; \
print_nl("! ") ;print_str(X) ; \
} \

#define spotless 0
#define warning_issued 1
#define error_message_issued 2
#define fatal_error_stop 3 \

#define hlp1(X) help_line[0]= X;}
#define hlp2(X) help_line[1]= X;hlp1
#define hlp3(X) help_line[2]= X;hlp2
#define hlp4(X) help_line[3]= X;hlp3
#define hlp5(X) help_line[4]= X;hlp4
#define hlp6(X) help_line[5]= X;hlp5
#define help0 help_ptr= 0
#define help1 {help_ptr= 1;hlp1
#define help2 {help_ptr= 2;hlp2
#define help3 {help_ptr= 3;hlp3
#define help4 {help_ptr= 4;hlp4
#define help5 {help_ptr= 5;hlp5
#define help6 {help_ptr= 6;hlp6 \

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

#define nx_plus_y(X,Y,Z) mult_and_add(X,Y,Z,07777777777) 
#define mult_integers(X,Y) mult_and_add(X,Y,0,017777777777)  \

#define inf_bad 10000 \

#define set_glue_ratio_zero(X) X= 0.0
#define set_glue_ratio_one(X) X= 1.0
#define float(X) ((double) (X) ) 
#define unfloat(X) ((glue_ratio) (X) ) 
#define float_constant(X) ((double) (X) )  \

#define min_quarterword 0
#define max_quarterword 255
#define min_halfword 0
#define max_halfword 65535 \

#define qi(X) X+min_quarterword \

#define qo(X) X-min_quarterword \

#define hi(X) X+min_halfword \

#define ho(X) X-min_halfword \
 \

#define sc i \

#define null min_halfword \

#define link(X) mem[X].hh.rh
#define info(X) mem[X].hh.lh \

#define mem_end mem_top
#define free_avail(X)  \
{link(X) = avail;avail= X; \
decr_dyn_used; \
} \

#define fast_get_avail(X)  \
{X= avail; \
if(X==null) X= get_avail() ; \
else{avail= link(X) ;link(X) = null; \
incr_dyn_used; \
} \
} \

#define empty_flag max_halfword
#define is_empty(X) (link(X) ==empty_flag) 
#define node_size info
#define llink(X) info(X+1) 
#define rlink(X) link(X+1)  \

#define type(X) mem[X].hh.b0
#define subtype(X) mem[X].hh.b1 \

#define is_char_node(X) (X>=hi_mem_min)  \

#define font type
#define character subtype \

#define hlist_node 0
#define box_node_size 9
#define width_offset 1
#define depth_offset 2
#define height_offset 3
#define width(X) mem[X+width_offset].sc
#define depth(X) mem[X+depth_offset].sc
#define height(X) mem[X+height_offset].sc
#define shift_amount(X) mem[X+4].sc
#define list_offset 5
#define list_ptr(X) link(X+list_offset) 
#define glue_order(X) subtype(X+list_offset) 
#define glue_sign(X) type(X+list_offset) 
#define normal 0
#define stretching 1
#define shrinking 2
#define glue_offset 6
#define glue_set(X) mem[X+glue_offset].gr \
 \

#define vlist_node 1 \

#define rule_node 2
#define rule_node_size 4
#define null_flag -010000000000
#define is_running(X) (X==null_flag)  \

#define ins_node 3
#define ins_node_size 5
#define float_cost(X) mem[X+1].i
#define ins_ptr(X) info(X+4) 
#define split_top_ptr(X) link(X+4)  \

#define mark_node 4
#define small_node_size 2
#define mark_ptr(X) mem[X+1].i \

#define adjust_node 5
#define adjust_ptr mark_ptr \

#define ligature_node 6
#define lig_char(X) X+1
#define lig_ptr(X) link(lig_char(X) )  \

#define disc_node 7
#define replace_count(X) (subtype(X) &0x7F) 
#define set_replace_count(X,Y) (subtype(X) = (Y) &0x7F) 
#define set_auto_disc(X) (subtype(X) |= 0x80) 
#define is_auto_disc(X) (subtype(X) &0x80) 
#define pre_break llink
#define post_break rlink \

#define whatsit_node 8 \

#define math_node 9
#define before 0
#define after 1 \

#define precedes_break(X) (type(X) <math_node) 
#define non_discardable(X) (type(X) <math_node)  \

#define glue_node 10
#define cond_math_glue 98
#define mu_glue 99
#define a_leaders 100
#define c_leaders 101
#define x_leaders 102
#define glue_ptr llink
#define leader_ptr rlink \

#define glue_spec_size 4
#define glue_ref_count(X) link(X) 
#define stretch(X) mem[X+2].sc
#define shrink(X) mem[X+3].sc
#define stretch_order type
#define shrink_order subtype
#define fil 1
#define fill 2
#define filll 3 \

#define kern_node 11
#define explicit 1
#define acc_kern 2 \

#define penalty_node 12
#define inf_penalty inf_bad
#define eject_penalty (-inf_penalty) 
#define penalty(X) mem[X+1].i \

#define unset_node 13
#define glue_stretch(X) mem[X+glue_offset].sc
#define glue_shrink shift_amount
#define span_count subtype \

#define zero_glue mem_bot
#define lo_mem_stat_max zero_glue+glue_spec_size-1 \

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

#define token_ref_count(X) info(X)  \

#define fast_delete_glue_ref(X)  \
{if(glue_ref_count(X) ==null) free_node(X,glue_spec_size) ; \
else decr(glue_ref_count(X) ) ; \
} \

#define add_token_ref(X) incr(token_ref_count(X) ) 
#define add_glue_ref(X) incr(glue_ref_count(X) )  \

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
#define un_vbox 24
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
#define left_right 49
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

#define set_box_dimen 83
#define set_shape 84
#define def_code 85
#define def_family 86
#define set_font 87
#define def_font 88
#define internal_register 89
#define max_internal 89
#define advance 90
#define multiply 91
#define divide 92
#define prefix 93
#define let 94
#define shorthand_def 95
#define read_to_cs 96
#define def 97
#define set_box 98
#define hyph_data 99
#define set_interaction 100
#define max_command 100 \

#define undefined_cs (max_command+1) 
#define expand_after (max_command+2) 
#define no_expand (max_command+3) 
#define input (max_command+4) 
#define if_test (max_command+5) 
#define fi_or_else (max_command+6) 
#define cs_name (max_command+7) 
#define convert (max_command+8) 
#define the (max_command+9) 
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
#define prev_graf cur_list.pg_field
#define aux cur_list.aux_field
#define prev_depth aux.sc
#define space_factor aux.hh.lh
#define clang aux.hh.rh
#define incompleat_noad aux.i
#define cur_bs cur_list.bs_field
#define cur_ls cur_list.ls_field
#define cur_lsl cur_list.lsl_field
#define needs_bs (cur_list.bs_pos!=NULL) 
#define node_pos cur_list.np_field
#define node_pos1 (nest_ptr==0?0:nest[nest_ptr-1].np_field)  \

#define tail_append(X) {link(tail) = X;tail= link(tail) ; \
} \

#define eq_level_field(X) X.hh.b1
#define eq_type_field(X) X.hh.b0
#define equiv_field(X) X.hh.rh
#define eq_level(X) eq_level_field(eqtb[X]) 
#define eq_type(X) eq_type_field(eqtb[X]) 
#define equiv(X) equiv_field(eqtb[X]) 
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

#define frozen_null_font (frozen_control_sequence+10)  \

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

#define skip(X) stream[X].g
#define mu_skip(X) equiv(mu_skip_base+X) 
#define glue_par(X) equiv(glue_base+X) 
#define line_skip pointer_def[glue_kind][line_skip_no]
#define baseline_skip pointer_def[glue_kind][baseline_skip_no]
#define above_display_skip pointer_def[glue_kind][above_display_skip_no]
#define below_display_skip pointer_def[glue_kind][below_display_skip_no]
#define above_display_short_skip pointer_def[glue_kind][above_display_short_skip_no]
#define below_display_short_skip pointer_def[glue_kind][below_display_short_skip_no]
#define left_skip pointer_def[glue_kind][left_skip_no]
#define right_skip pointer_def[glue_kind][right_skip_no]
#define top_skip pointer_def[glue_kind][top_skip_no]
#define split_top_skip pointer_def[glue_kind][split_top_skip_no]
#define tab_skip pointer_def[glue_kind][tab_skip_no]
#define par_fill_skip pointer_def[glue_kind][par_fill_skip_no]
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
#define toks_base (local_base+10) 
#define box_base (toks_base+256) 
#define cur_font_loc (box_base+256) 
#define math_font_base (cur_font_loc+1) 
#define cat_code_base (math_font_base+48)  \

#define lc_code_base (cat_code_base+256) 
#define uc_code_base (lc_code_base+256) 
#define sf_code_base (uc_code_base+256) 
#define math_code_base (sf_code_base+256) 
#define int_base (math_code_base+256)  \

#define par_shape_ptr null
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
#define box(X) stream[X].p
#define cur_font equiv(cur_font_loc) 
#define fam_fnt(X) equiv(math_font_base+X) 
#define cat_code(X) equiv(cat_code_base+X) 
#define lc_code(X) equiv(lc_code_base+X) 
#define uc_code(X) equiv(uc_code_base+X) 
#define sf_code(X) equiv(sf_code_base+X) 
#define math_code(X) equiv(math_code_base+X)  \
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
#define int_pars 55
#define count_base (int_base+int_pars) 
#define del_code_base (count_base+256) 
#define dimen_base (del_code_base+256)  \

#define del_code(X) eqtb[del_code_base+X].i
#define count(X) stream[X].i
#define int_par(X) eqtb[int_base+X].i
#define pretolerance integer_def[pretolerance_no]
#define tolerance integer_def[tolerance_no]
#define line_penalty integer_def[line_penalty_no]
#define hyphen_penalty integer_def[hyphen_penalty_no]
#define ex_hyphen_penalty integer_def[ex_hyphen_penalty_no]
#define club_penalty integer_def[club_penalty_no]
#define widow_penalty integer_def[widow_penalty_no]
#define display_widow_penalty integer_def[display_widow_penalty_no]
#define broken_penalty integer_def[broken_penalty_no]
#define pre_display_penalty integer_def[pre_display_penalty_no]
#define post_display_penalty integer_def[post_display_penalty_no]
#define inter_line_penalty integer_def[inter_line_penalty_no]
#define double_hyphen_demerits integer_def[double_hyphen_demerits_no]
#define final_hyphen_demerits integer_def[final_hyphen_demerits_no]
#define adj_demerits integer_def[adj_demerits_no]
#define looseness integer_def[looseness_no]
#define time integer_def[time_no]
#define day integer_def[day_no]
#define month integer_def[month_no]
#define year integer_def[year_no]
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
#define hang_after integer_def[hang_after_no]
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
#define error_context_lines int_par(error_context_lines_code)  \

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
#define dimen_pars 21
#define scaled_base (dimen_base+dimen_pars)  \

#define eqtb_size (scaled_base+255)  \

#define dimen(X) stream[X].s
#define dimen_par(X) eqtb[dimen_base+X].sc
#define par_indent dimen_par(par_indent_code) 
#define math_surround dimen_par(math_surround_code) 
#define line_skip_limit dimen_def[line_skip_limit_no]
#define hsize dimen_par(hsize_code) 
#define vsize dimen_par(vsize_code) 
#define max_depth dimen_def[max_depth_no]
#define split_max_depth dimen_par(split_max_depth_code) 
#define box_max_depth dimen_par(box_max_depth_code) 
#define hfuzz dimen_par(hfuzz_code) 
#define vfuzz dimen_par(vfuzz_code) 
#define delimiter_shortfall dimen_par(delimiter_shortfall_code) 
#define null_delimiter_space dimen_par(null_delimiter_space_code) 
#define script_space dimen_par(script_space_code) 
#define pre_display_size cur_list.ds_field
#define display_width cur_list.dw_field
#define display_indent cur_list.di_field
#define overfull_rule dimen_par(overfull_rule_code) 
#define hang_indent dimen_def[hang_indent_no]
#define h_offset dimen_par(h_offset_code) 
#define v_offset dimen_par(v_offset_code) 
#define emergency_stretch dimen_def[emergency_stretch_no] \

#define next(X) hash[X].lh
#define text(X) hash[X].rh
#define hash_is_full (hash_used==hash_base) 
#define font_id_text(X) text(font_id_base+X)  \

#define save_type(X) save_stack[X].hh.b0
#define save_level(X) save_stack[X].hh.b1 \

#define save_index(X) save_stack[X].hh.rh \

#define restore_old_value 0
#define restore_zero 1
#define insert_token 2
#define level_boundary 3 \

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
if(max_save_stack> save_size-6) overflow("save size",save_size) ; \
 \
} \

#define saved(X) save_stack[save_ptr+X].i \

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
#define end_match_token 07000 \

#define chr_cmd(X) {print_str(X) ;print_ASCII(chr_code) ; \
} \

#define state cur_input.state_field
#define index cur_input.index_field
#define start cur_input.start_field
#define limit cur_input.limit_field
#define name cur_input.name_field \

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
#define mark_text 14
#define write_text 15 \

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

#define back_list(X) begin_token_list(X,backed_up) 
#define ins_list(X) begin_token_list(X,inserted)  \

#define any_state_plus(X) case mid_line+X:case skip_blanks+X:case new_line+X \

#define add_delims_to(X) X+math_shift:X+tab_mark:X+mac_param: \
X+sub_mark:X+letter:X+other_char \

#define is_hex(X) (((X>='0') &&(X<='9') ) ||((X>='a') &&(X<='f') ) ) 
#define hex_to_cur_chr  \
if(c<='9') cur_chr= c-'0';else cur_chr= c-'a'+10; \
if(cc<='9') cur_chr= 16*cur_chr+cc-'0'; \
else cur_chr= 16*cur_chr+cc-'a'+10 \

#define no_expand_flag 257 \

#define end_line_char_inactive (end_line_char<0) ||(end_line_char> 255)  \

#define store_new_token(X) {q= get_avail() ;link(p) = q;info(q) = X; \
p= q; \
}
#define fast_store_new_token(X) {fast_get_avail(q) ;link(p) = q;info(q) = X; \
p= q; \
} \

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

#define scanned_result_end(X) cur_val_level= X;}
#define scanned_result(X) {cur_val= X;scanned_result_end \

#define input_line_no_code (glue_val+1) 
#define badness_code (glue_val+2)  \

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

#define set_conversion_end(X) denom= X;}
#define set_conversion(X) {num= X;set_conversion_end \

#define default_rule 26214 \

#define number_code 0
#define roman_numeral_code 1
#define string_code 2
#define meaning_code 3
#define font_name_code 4
#define job_name_code 5 \

#define closed 2
#define just_open 1 \

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
#define if_line_field(X) mem[X+1].i
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

#define append_to_name(X) {c= X;incr(k) ; \
if(k<=file_name_size) name_of_file[k]= xchr[c]; \
} \

#define format_default_length 20
#define format_area_length 11
#define format_ext_length 4
#define format_extension_str ".fmt" \

#define pack_cur_name pack_file_name(cur_name,cur_area,cur_ext)  \

#define no_tag 0
#define lig_tag 1
#define list_tag 2
#define ext_tag 3 \

#define stop_flag qi(128) 
#define kern_flag qi(128) 
#define skip_byte(X) X.b0
#define next_char(X) X.b1
#define op_byte(X) X.b2
#define rem_byte(X) X.b3 \

#define ext_top(X) X.b0
#define ext_mid(X) X.b1
#define ext_bot(X) X.b2
#define ext_rep(X) X.b3 \

#define slant_code 1
#define space_code 2
#define space_stretch_code 3
#define space_shrink_code 4
#define x_height_code 5
#define quad_code 6
#define extra_space_code 7 \

#define non_char qi(256) 
#define non_address 0 \

#define char_info_end(X) X].qqqq
#define char_info(X) font_info[char_base[X]+char_info_end
#define char_width_end(X) X.b0].sc
#define char_width(X) font_info[width_base[X]+char_width_end
#define char_exists(X) (X.b0> min_quarterword) 
#define char_italic_end(X) (qo(X.b2) ) /4].sc
#define char_italic(X) font_info[italic_base[X]+char_italic_end
#define height_depth(X) qo(X.b1) 
#define char_height_end(X) (X) /16].sc
#define char_height(X) font_info[height_base[X]+char_height_end
#define char_depth_end(X) (X) %16].sc
#define char_depth(X) font_info[depth_base[X]+char_depth_end
#define char_tag(X) ((qo(X.b2) ) %4)  \

#define char_kern_end(X) 256*op_byte(X) +rem_byte(X) ].sc
#define char_kern(X) font_info[kern_base[X]+char_kern_end
#define kern_base_offset 256*(128+min_quarterword) 
#define lig_kern_start(X) lig_kern_base[X]+rem_byte
#define lig_kern_restart_end(X) 256*op_byte(X) +rem_byte(X) +32768-kern_base_offset
#define lig_kern_restart(X) lig_kern_base[X]+lig_kern_restart_end \

#define param_end(X) param_base[X]].sc
#define param(X) font_info[X+param_end
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
{print_str(" at ") ;print_scaled(s) ;print_str("pt") ; \
} \
else if(s!=-1000)  \
{print_str(" scaled ") ;print_int(-s) ; \
} \

#define fget (hpos++) 
#define fbyte (*hpos) 
#define read_sixteen(X) {X= fbyte; \
if(X> 127) abort; \
fget;X= X*0400+fbyte; \
}
#define store_four_quarters(X) {fget;a= fbyte;qw.b0= qi(a) ; \
fget;b= fbyte;qw.b1= qi(b) ; \
fget;c= fbyte;qw.b2= qi(c) ; \
fget;d= fbyte;qw.b3= qi(d) ; \
X= qw; \
} \

#define check_byte_range(X) {if((X<bc) ||(X> ec) ) abort;}
#define current_character_being_worked_on k+bc-fmem_ptr \

#define store_scaled(X) {fget;a= fbyte;fget;b= fbyte; \
fget;c= fbyte;fget;d= fbyte; \
sw= (((((d*z) /0400) +(c*z) ) /0400) +(b*z) ) /beta; \
if(a==0) X= sw;else if(a==255) X= sw-alpha;else abort; \
} \

#define check_existence(X)  \
{check_byte_range(X) ; \
qw= char_info(f) (X) ; \
if(!char_exists(qw) ) abort; \
} \

#define adjust(X) X[f]= qo(X[f])  \
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

#define dvi_out(X) {dvi_buf[dvi_ptr]= X;incr(dvi_ptr) ; \
if(dvi_ptr==dvi_limit) dvi_swap() ; \
} \

#define movement_node_size 3
#define location(X) mem[X+2].i \

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
#define vet_glue(X) glue_temp= X; \
if(glue_temp> billion)  \
glue_temp= billion; \
else if(glue_temp<-billion)  \
glue_temp= -billion \

#define exactly 0
#define additional 1
#define natural 0,additional \

#define noad_size 4
#define nucleus(X) X+1
#define supscr(X) X+2
#define subscr(X) X+3
#define math_type link
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

#define left_delimiter(X) X+4
#define right_delimiter(X) X+5
#define radical_noad (inner_noad+1) 
#define radical_noad_size 5
#define fraction_noad (radical_noad+1) 
#define fraction_noad_size 6
#define small_fam(X) mem[X].qqqq.b0
#define small_char(X) mem[X].qqqq.b1
#define large_fam(X) mem[X].qqqq.b2
#define large_char(X) mem[X].qqqq.b3
#define thickness width
#define default_code 010000000000
#define numerator supscr
#define denominator subscr \

#define under_noad (fraction_noad+1) 
#define over_noad (under_noad+1) 
#define accent_noad (over_noad+1) 
#define accent_noad_size 5
#define accent_chr(X) X+4
#define vcenter_noad (accent_noad+1) 
#define left_noad (vcenter_noad+1) 
#define right_noad (left_noad+1) 
#define delimiter nucleus
#define scripts_allowed(X) (type(X) >=ord_noad) &&(type(X) <left_noad)  \

#define style_node (unset_node+1) 
#define style_node_size 3
#define display_style 0
#define text_style 2
#define script_style 4
#define script_script_style 6
#define cramped 1 \

#define choice_node (unset_node+2) 
#define display_mlist(X) info(X+1) 
#define text_mlist(X) link(X+1) 
#define script_mlist(X) info(X+2) 
#define script_script_mlist(X) link(X+2)  \

#define text_size 0
#define script_size 16
#define script_script_size 32 \

#define mathsy_end(X) fam_fnt(2+X) ]].sc
#define mathsy(X) font_info[X+param_base[mathsy_end
#define math_x_height mathsy(5) 
#define math_quad dimen_def[math_quad_no]
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

#define mathex(X) font_info[X+param_base[fam_fnt(3+cur_size) ]].sc
#define default_rule_thickness mathex(8) 
#define big_op_spacing1 mathex(9) 
#define big_op_spacing2 mathex(10) 
#define big_op_spacing3 mathex(11) 
#define big_op_spacing4 mathex(12) 
#define big_op_spacing5 mathex(13) 
#define total_mathex_params 13 \

#define cramped_style(X) 2*(X/2) +cramped
#define sub_style(X) 2*(X/4) +script_style+cramped
#define sup_style(X) 2*(X/4) +script_style+(X%2) 
#define num_style(X) X+2-2*(X/6) 
#define denom_style(X) 2*(X/2) +cramped+2-2*(X/6)  \

#define mu_mult(X) nx_plus_y(n,X,xn_over_d(X,f,0200000) )  \

#define new_hlist(X) mem[nucleus(X) ].i \

#define choose_mlist(X) {p= X(q) ;X(q) = null;} \

#define math_spacing_str  \
 \
"math_spacing" \
 \

#define u_part(X) mem[X+height_offset].i
#define v_part(X) mem[X+depth_offset].i
#define extra_info(X) info(X+list_offset)  \

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
#define fitness subtype
#define break_node rlink
#define line_number llink
#define total_demerits(X) mem[X+2].i
#define unhyphenated 0
#define hyphenated 1
#define last_active active \

#define passive_node_size 2
#define cur_break rlink
#define prev_break llink
#define serial info \

#define delta_node_size 7
#define delta_node 2 \

#define do_all_six(X) X(1) ;X(2) ;X(3) ;X(4) ;X(5) ;X(6)  \

#define check_shrinkage(X) if((shrink_order(X) !=normal) &&(shrink(X) !=0) )  \
{X= finite_shrink(X) ; \
} \

#define copy_to_cur_active(X) cur_active_width[X]= active_width[X]
#define update_width(X)  \
cur_active_width[X]= cur_active_width[X]+mem[r+X].sc \

#define awful_bad 07777777777 \

#define set_break_width_to_background(X) break_width[X]= background[X] \

#define convert_to_break_width(X)  \
mem[prev_r+X].sc= mem[prev_r+X].sc \
-cur_active_width[X]+break_width[X]
#define store_break_width(X) active_width[X]= break_width[X]
#define new_delta_to_break_width(X)  \
mem[q+X].sc= break_width[X]-cur_active_width[X] \

#define new_delta_from_break_width(X) mem[q+X].sc=  \
cur_active_width[X]-break_width[X] \

#define combine_two_deltas(X) mem[prev_r+X].sc= mem[prev_r+X].sc+mem[r+X].sc
#define downdate_width(X) cur_active_width[X]= cur_active_width[X]- \
mem[prev_r+X].sc \

#define update_active(X) active_width[X]= active_width[X]+mem[r+X].sc \

#define store_background(X) active_width[X]= background[X] \

#define act_width active_width[1]
#define kern_break {if(!is_char_node(link(cur_p) ) &&auto_breaking)  \
if(type(link(cur_p) ) ==glue_node) try_break(0,unhyphenated) ; \
act_width= act_width+width(cur_p) ; \
} \

#define next_break prev_break \

#define append_charnode_to_t(X) {link(t) = get_avail() ;t= link(t) ; \
font(t) = hf;character(t) = X; \
}
#define set_cur_r {if(j<n) cur_r= qi(hu[j+1]) ;else cur_r= bchar; \
if(odd(hyf[j]) ) cur_rh= hchar;else cur_rh= non_char; \
} \

#define wrap_lig(X) if(ligature_present)  \
{p= new_ligature(hf,cur_l,link(cur_q) ) ; \
if(lft_hit)  \
{subtype(p) = 2;lft_hit= false; \
} \
if(X) if(lig_stack==null)  \
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

#define trie_link(X) trie[X].rh
#define trie_char(X) trie[X].b1
#define trie_op(X) trie[X].b0 \

#define set_cur_lang if(language<=0) cur_lang= 0; \
else if(language> 255) cur_lang= 0; \
else cur_lang= language \

#define trie_root trie_l[0] \

#define trie_ref trie_hash
#define trie_back(X) trie[X].lh \

#define active_height active_width
#define cur_height active_height[1]
#define set_height_zero(X) active_height[X]= 0 \

#define deplorable 100000 \

#define inserts_only 1 \

#define box_there 2 \

#define page_ins_node_size 4
#define inserting 0
#define split_up 1
#define broken_ptr(X) link(X+1)  \

#define broken_ins(X) info(X+1) 
#define last_ins_ptr(X) link(X+2) 
#define best_ins_ptr(X) info(X+2)  \

#define page_goal page_so_far[0]
#define page_total page_so_far[1]
#define page_shrink page_so_far[6] \

#define print_plus_end(X) print_str(X) ;}
#define print_plus(X) if(page_so_far[X]!=0)  \
{print_str(" plus ") ;print_scaled(page_so_far[X]) ;print_plus_end \

#define set_page_so_far_zero(X) page_so_far[X]= 0 \

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

#define wrapup(X) if(cur_l<non_char)  \
{if(link(cur_q) > null)  \
if(character(tail) ==qi(hyphen_char[main_f]) ) ins_disc= true; \
if(ligature_present) pack_lig(X) ; \
if(ins_disc)  \
{ins_disc= false; \
if(mode> 0) tail_append(new_disc() ) ; \
} \
} \

#define any_mode(X) case vmode+X:case hmode+X:case mmode+X \

#define non_math(X) case vmode+X:case hmode+X \

#define fil_code 0
#define fill_code 1
#define ss_code 2
#define fil_neg_code 3
#define skip_code 4
#define mskip_code 5 \

#define box_flag 010000000000
#define ship_out_flag box_flag+512
#define leader_flag box_flag+513
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
#define define(X,Y,Z) if(global) geq_define(X,Y,Z) ;else eq_define(X,Y,Z) 
#define word_define(X,Y) if(global) geq_word_define(X,Y) ;else eq_word_define(X,Y)  \

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
#define show_lists 3 \

#define too_small(X) {wake_up_terminal; \
wterm_ln("---! Must increase the %s",X) ; \
 \
goto bad_fmt; \
} \

#define dump_wd(X) {fmt_file.d= X;put(fmt_file) ;}
#define dump_int(X) {fmt_file.d.i= X;put(fmt_file) ;}
#define dump_hh(X) {fmt_file.d.hh= X;put(fmt_file) ;}
#define dump_qqqq(X) {fmt_file.d.qqqq= X;put(fmt_file) ;} \

#define undump_wd(X) {get(fmt_file) ;X= fmt_file.d;}
#define undump_int(X) {get(fmt_file) ;X= fmt_file.d.i;}
#define undump_hh(X) {get(fmt_file) ;X= fmt_file.d.hh;}
#define undump_qqqq(X) {get(fmt_file) ;X= fmt_file.d.qqqq;}
#define undump_end_end(X) X= x;}
#define undump_end(X) (x> X) ) goto bad_fmt;else undump_end_end
#define undump(X) {undump_int(x) ;if((x<X) ||undump_end
#define undump_size_end_end(X) too_small(X) else undump_end_end
#define undump_size_end(X) if(x> X) undump_size_end_end
#define undump_size(X) {undump_int(x) ; \
if(x<X) goto bad_fmt;undump_size_end \

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
#define what_lang(X) link(X+1) 
#define what_lhm(X) type(X+1) 
#define what_rhm(X) subtype(X+1) 
#define write_tokens(X) link(X+1) 
#define write_stream(X) info(X+1) 
#define open_name(X) link(X+1) 
#define open_area(X) info(X+2) 
#define open_ext(X) link(X+2)  \

#define par_node 6
#define par_node_size 3
#define par_type(X) type(X+1) 
#define int_type 0
#define dimen_type 1
#define glue_type 2
#define par_number(X) subtype(X+1) 
#define par_value(X) mem[X+2] \

#define graf_node 7
#define graf_node_size 6
#define graf_penalty(X) mem[X+1].i
#define graf_continue(X) type(X+2) 
#define graf_first_line(X) link(X+2) 
#define graf_params(X) link(X+3) 
#define graf_list_offset 4
#define graf_list(X) link(X+graf_list_offset) 
#define graf_extent(X) mem[X+5].i \

#define disp_node 8
#define disp_node_size 3
#define display_left(X) type(X+1) 
#define display_no_bs(X) subtype(X+1) 
#define display_params(X) link(X+1) 
#define display_formula(X) link(X+2) 
#define display_eqno(X) info(X+2)  \

#define baseline_node 9
#define baseline_node_size small_node_size
#define baseline_node_no(X) mem[X+1].i \

#define image_node 10
#define image_node_size 9
#define image_width(X) width(X) 
#define image_height(X) height(X) 
#define image_depth(X) depth(X) 
#define image_no(X) mem[X+4].i
#define image_stretch(X) mem[X+5].sc
#define image_shrink(X) mem[X+6].sc
#define image_stretch_order(X) stretch_order(X+7) 
#define image_shrink_order(X) shrink_order(X+7) 
#define image_name(X) link(X+7) 
#define image_area(X) info(X+8) 
#define image_ext(X) link(X+8)  \

#define hpack_node 12
#define vpack_node 13
#define pack_node_size box_node_size
#define pack_m(X) type(X+list_offset) 
#define pack_limit(X) mem[(X) +glue_offset].sc
#define pack_extent(X) mem[(X) +1+glue_offset].i \

#define hset_node 14
#define vset_node 15
#define set_node_size box_node_size
#define set_stretch_order glue_sign
#define set_shrink_order glue_order
#define set_stretch(X) mem[(X) +glue_offset].sc
#define set_extent(X) pack_extent(X) 
#define set_shrink(X) mem[(X) +2+glue_offset].sc \

#define align_node 16
#define align_node_size 4
#define align_preamble(X) info(X+1) 
#define align_list(X) link(X+1) 
#define align_extent(X) mem[X+2].i
#define align_m(X) type(X+3) 
#define align_v(X) subtype(X+3)  \

#define immediate_code 4
#define set_language_code 5 \

#define adv_past(X) {} \

#define end_write_token cs_token_flag+end_write \

#define str_0_255 "^^@^^A^^B^^C^^D^^E^^F^^G^^H^^I^^J^^K^^L^^M^^N^^O" \
"^^P^^Q^^R^^S^^T^^U^^V^^W^^X^^Y^^Z^^[^^\\^^]^^^^^_" \
" !\"#$%&'()*+,-./" \
"0123456789:;<=>?" \
"@ABCDEFGHIJKLMNO" \
"PQRSTUVWXYZ[\\]^_" \
"`abcdefghijklmno" \
"pqrstuvwxyz{|}~^^?" \
"^^80^^81^^82^^83^^84^^85^^86^^87^^88^^89^^8a^^8b^^8c^^8d^^8e^^8f" \
"^^90^^91^^92^^93^^94^^95^^96^^97^^98^^99^^9a^^9b^^9c^^9d^^9e^^9f" \
"^^a0^^a1^^a2^^a3^^a4^^a5^^a6^^a7^^a8^^a9^^aa^^ab^^ac^^ad^^ae^^af" \
"^^b0^^b1^^b2^^b3^^b4^^b5^^b6^^b7^^b8^^b9^^ba^^bb^^bc^^bd^^be^^bf" \
"^^c0^^c1^^c2^^c3^^c4^^c5^^c6^^c7^^c8^^c9^^ca^^cb^^cc^^cd^^ce^^cf" \
"^^d0^^d1^^d2^^d3^^d4^^d5^^d6^^d7^^d8^^d9^^da^^db^^dc^^dd^^de^^df" \
"^^e0^^e1^^e2^^e3^^e4^^e5^^e6^^e7^^e8^^e9^^ea^^eb^^ec^^ed^^ee^^ef" \
"^^f0^^f1^^f2^^f3^^f4^^f5^^f6^^f7^^f8^^f9^^fa^^fb^^fc^^fd^^fe^^ff"
#define str_start_0_255 0,3,6,9,12,15,18,21,24,27,30,33,36,39,42,45, \
48,51,54,57,60,63,66,69,72,75,78,81,84,87,90,93, \
96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111, \
112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127, \
128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143, \
144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159, \
160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175, \
176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191, \
194,198,202,206,210,214,218,222,226,230,234,238,242,246,250,254, \
258,262,266,270,274,278,282,286,290,294,298,302,306,310,314,318, \
322,326,330,334,338,342,346,350,354,358,362,366,370,374,378,382, \
386,390,394,398,402,406,410,414,418,422,426,430,434,438,442,446, \
450,454,458,462,466,470,474,478,482,486,490,494,498,502,506,510, \
514,518,522,526,530,534,538,542,546,550,554,558,562,566,570,574, \
578,582,586,590,594,598,602,606,610,614,618,622,626,630,634,638, \
642,646,650,654,658,662,666,670,674,678,682,686,690,694,698,702,
#define str_256 "???"
#define str_257 "m2d5c2l5x2v5i"
#define str_258 "batchmode"
#define str_259 "nonstopmode"
#define str_260 "scrollmode"
#define str_261 "CLOBBERED."
#define str_262 "fil"
#define str_263 "unset"
#define str_264 "rule("
#define str_265 "insert"
#define str_266 "glue"
#define str_267 "nonscript"
#define str_268 "mskip"
#define str_269 "mu"
#define str_270 ""
#define empty_string 270
#define str_271 "kern"
#define str_272 "mkern"
#define str_273 "math"
#define str_274 "penalty "
#define str_275 "discretionary"
#define str_276 "mark"
#define str_277 "vadjust"
#define str_278 "flushing"
#define str_279 "copying"
#define str_280 "lineskip"
#define str_281 "baselineskip"
#define str_282 "parskip"
#define str_283 "abovedisplayskip"
#define str_284 "belowdisplayskip"
#define str_285 "abovedisplayshortskip"
#define str_286 "belowdisplayshortskip"
#define str_287 "leftskip"
#define str_288 "rightskip"
#define str_289 "topskip"
#define str_290 "splittopskip"
#define str_291 "tabskip"
#define str_292 "spaceskip"
#define str_293 "xspaceskip"
#define str_294 "parfillskip"
#define str_295 "thinmuskip"
#define str_296 "medmuskip"
#define str_297 "thickmuskip"
#define str_298 "skip"
#define str_299 "muskip"
#define str_300 "pt"
#define str_301 "output"
#define str_302 "everypar"
#define str_303 "everymath"
#define str_304 "everydisplay"
#define str_305 "everyhbox"
#define str_306 "everyvbox"
#define str_307 "everyjob"
#define str_308 "everycr"
#define str_309 "errhelp"
#define str_310 "toks"
#define str_311 "parshape"
#define str_312 "box"
#define str_313 "textfont"
#define str_314 "scriptfont"
#define str_315 "scriptscriptfont"
#define str_316 "catcode"
#define str_317 "lccode"
#define str_318 "uccode"
#define str_319 "sfcode"
#define str_320 "mathcode"
#define str_321 "pretolerance"
#define str_322 "tolerance"
#define str_323 "linepenalty"
#define str_324 "hyphenpenalty"
#define str_325 "exhyphenpenalty"
#define str_326 "clubpenalty"
#define str_327 "widowpenalty"
#define str_328 "displaywidowpenalty"
#define str_329 "brokenpenalty"
#define str_330 "binoppenalty"
#define str_331 "relpenalty"
#define str_332 "predisplaypenalty"
#define str_333 "postdisplaypenalty"
#define str_334 "interlinepenalty"
#define str_335 "doublehyphendemerits"
#define str_336 "finalhyphendemerits"
#define str_337 "adjdemerits"
#define str_338 "mag"
#define str_339 "delimiterfactor"
#define str_340 "looseness"
#define str_341 "time"
#define str_342 "day"
#define str_343 "month"
#define str_344 "year"
#define str_345 "showboxbreadth"
#define str_346 "showboxdepth"
#define str_347 "hbadness"
#define str_348 "vbadness"
#define str_349 "pausing"
#define str_350 "tracingonline"
#define str_351 "tracingmacros"
#define str_352 "tracingstats"
#define str_353 "tracingparagraphs"
#define str_354 "tracingpages"
#define str_355 "tracingoutput"
#define str_356 "tracinglostchars"
#define str_357 "tracingcommands"
#define str_358 "tracingrestores"
#define str_359 "uchyph"
#define str_360 "outputpenalty"
#define str_361 "maxdeadcycles"
#define str_362 "hangafter"
#define str_363 "floatingpenalty"
#define str_364 "globaldefs"
#define str_365 "fam"
#define str_366 "escapechar"
#define str_367 "defaulthyphenchar"
#define str_368 "defaultskewchar"
#define str_369 "endlinechar"
#define str_370 "newlinechar"
#define str_371 "language"
#define str_372 "lefthyphenmin"
#define str_373 "righthyphenmin"
#define str_374 "holdinginserts"
#define str_375 "errorcontextlines"
#define str_376 "count"
#define str_377 "delcode"
#define str_378 "parindent"
#define str_379 "mathsurround"
#define str_380 "lineskiplimit"
#define str_381 "hsize"
#define str_382 "vsize"
#define str_383 "maxdepth"
#define str_384 "splitmaxdepth"
#define str_385 "boxmaxdepth"
#define str_386 "hfuzz"
#define str_387 "vfuzz"
#define str_388 "delimitershortfall"
#define str_389 "nulldelimiterspace"
#define str_390 "scriptspace"
#define str_391 "predisplaysize"
#define str_392 "displaywidth"
#define str_393 "displayindent"
#define str_394 "overfullrule"
#define str_395 "hangindent"
#define str_396 "hoffset"
#define str_397 "voffset"
#define str_398 "emergencystretch"
#define str_399 "dimen"
#define str_400 "notexpanded:"
#define str_401 "csname"
#define str_402 "endcsname"
#define str_403 "IMPOSSIBLE."
#define str_404 "NONEXISTENT."
#define str_405 "accent"
#define str_406 "advance"
#define str_407 "afterassignment"
#define str_408 "aftergroup"
#define str_409 "begingroup"
#define str_410 "char"
#define str_411 "delimiter"
#define str_412 "divide"
#define str_413 "endgroup"
#define str_414 "expandafter"
#define str_415 "font"
#define str_416 "fontdimen"
#define str_417 "halign"
#define str_418 "hrule"
#define str_419 "ignorespaces"
#define str_420 "mathaccent"
#define str_421 "mathchar"
#define str_422 "mathchoice"
#define str_423 "multiply"
#define str_424 "noalign"
#define str_425 "noboundary"
#define str_426 "noexpand"
#define str_427 "omit"
#define str_428 "penalty"
#define str_429 "prevgraf"
#define str_430 "radical"
#define str_431 "read"
#define str_432 "relax"
#define str_433 "setbox"
#define str_434 "the"
#define str_435 "valign"
#define str_436 "vcenter"
#define str_437 "vrule"
#define str_438 "curlevel"
#define str_439 "retaining"
#define str_440 "restoring"
#define str_441 "ETC."
#define str_442 "BAD."
#define str_443 "write"
#define str_444 "par"
#define str_445 "input"
#define str_446 "endinput"
#define str_447 "topmark"
#define str_448 "firstmark"
#define str_449 "botmark"
#define str_450 "splitfirstmark"
#define str_451 "splitbotmark"
#define str_452 "spacefactor"
#define str_453 "prevdepth"
#define str_454 "deadcycles"
#define str_455 "insertpenalties"
#define str_456 "wd"
#define str_457 "ht"
#define str_458 "dp"
#define str_459 "lastpenalty"
#define str_460 "lastkern"
#define str_461 "lastskip"
#define str_462 "inputlineno"
#define str_463 "badness"
#define str_464 "true"
#define str_465 "em"
#define str_466 "ex"
#define str_467 "in"
#define str_468 "pc"
#define str_469 "cm"
#define str_470 "mm"
#define str_471 "bp"
#define str_472 "dd"
#define str_473 "cc"
#define str_474 "sp"
#define str_475 "plus"
#define str_476 "minus"
#define str_477 "width"
#define str_478 "height"
#define str_479 "depth"
#define str_480 "number"
#define str_481 "romannumeral"
#define str_482 "string"
#define str_483 "meaning"
#define str_484 "fontname"
#define str_485 "jobname"
#define str_486 "if"
#define str_487 "ifcat"
#define str_488 "ifnum"
#define str_489 "ifdim"
#define str_490 "ifodd"
#define str_491 "ifvmode"
#define str_492 "ifhmode"
#define str_493 "ifmmode"
#define str_494 "ifinner"
#define str_495 "ifvoid"
#define str_496 "ifhbox"
#define str_497 "ifvbox"
#define str_498 "ifx"
#define str_499 "ifeof"
#define str_500 "iftrue"
#define str_501 "iffalse"
#define str_502 "ifcase"
#define str_503 "fi"
#define str_504 "or"
#define str_505 "else"
#define str_506 "TeXinputs/"
#define TEX_area 506
#define str_507 "TeXfonts/"
#define TEX_font_area 507
#define str_508 ".fmt"
#define format_extension 508
#define str_509 ".log"
#define str_510 ".dvi"
#define str_511 "input file name"
#define str_512 ".tex"
#define str_513 "texput"
#define str_514 "nullfont"
#define str_515 ".tfm"
#define str_516 "vlistout"
#define str_517 "to"
#define str_518 "spread"
#define str_519 "vpack"
#define str_520 "displaystyle"
#define str_521 "textstyle"
#define str_522 "scriptstyle"
#define str_523 "scriptscriptstyle"
#define str_524 "mathord"
#define str_525 "mathop"
#define str_526 "mathbin"
#define str_527 "mathrel"
#define str_528 "mathopen"
#define str_529 "mathclose"
#define str_530 "mathpunct"
#define str_531 "mathinner"
#define str_532 "overline"
#define str_533 "underline"
#define str_534 "left"
#define str_535 "right"
#define str_536 "limits"
#define str_537 "nolimits"
#define str_538 "fraction, thickness "
#define str_539 "mlist1"
#define str_540 "mlist2"
#define str_541 "mlist3"
#define str_542 "0234000122*4000133**3**344*0400400*000000234000111*1111112341011"
#define math_spacing 542
#define str_543 "mlist4"
#define str_544 "span"
#define str_545 "cr"
#define str_546 "crcr"
#define str_547 "endtemplate"
#define str_548 "endv"
#define str_549 "256 spans"
#define str_550 "align1"
#define str_551 "align0"
#define str_552 "disc1"
#define str_553 "disc2"
#define str_554 "paragraph"
#define str_555 "disc3"
#define str_556 "disc4"
#define str_557 "line breaking"
#define str_558 "hyphenation"
#define str_559 "patterns"
#define str_560 "pruning"
#define str_561 "vertbreak"
#define str_562 "vsplit"
#define str_563 "vbox"
#define str_564 "pagegoal"
#define str_565 "pagetotal"
#define str_566 "pagestretch"
#define str_567 "pagefilstretch"
#define str_568 "pagefillstretch"
#define str_569 "pagefilllstretch"
#define str_570 "pageshrink"
#define str_571 "pagedepth"
#define str_572 "page"
#define str_573 "end"
#define str_574 "dump"
#define str_575 "hskip"
#define str_576 "hfil"
#define str_577 "hfill"
#define str_578 "hss"
#define str_579 "hfilneg"
#define str_580 "vskip"
#define str_581 "vfil"
#define str_582 "vfill"
#define str_583 "vss"
#define str_584 "vfilneg"
#define str_585 "right."
#define str_586 "rightbrace"
#define str_587 "moveleft"
#define str_588 "moveright"
#define str_589 "raise"
#define str_590 "lower"
#define str_591 "copy"
#define str_592 "lastbox"
#define str_593 "vtop"
#define str_594 "hbox"
#define str_595 "shipout"
#define str_596 "leaders"
#define str_597 "cleaders"
#define str_598 "xleaders"
#define str_599 "indent"
#define str_600 "noindent"
#define str_601 "unpenalty"
#define str_602 "unkern"
#define str_603 "unskip"
#define str_604 "unhbox"
#define str_605 "unhcopy"
#define str_606 "unvbox"
#define str_607 "unvcopy"
#define str_608 "eqno"
#define str_609 "leqno"
#define str_610 "displaylimits"
#define str_611 "above"
#define str_612 "over"
#define str_613 "atop"
#define str_614 "abovewithdelims"
#define str_615 "overwithdelims"
#define str_616 "atopwithdelims"
#define str_617 "display"
#define str_618 "long"
#define str_619 "outer"
#define str_620 "global"
#define str_621 "def"
#define str_622 "gdef"
#define str_623 "edef"
#define str_624 "xdef"
#define str_625 "prefix"
#define str_626 "inaccessible"
#define str_627 "let"
#define str_628 "futurelet"
#define str_629 "chardef"
#define str_630 "mathchardef"
#define str_631 "countdef"
#define str_632 "dimendef"
#define str_633 "skipdef"
#define str_634 "muskipdef"
#define str_635 "toksdef"
#define str_636 "by"
#define str_637 "hyphenchar"
#define str_638 "skewchar"
#define str_639 "FONT"
#define str_640 "at"
#define str_641 "scaled"
#define str_642 "errorstopmode"
#define str_643 "openin"
#define str_644 "closein"
#define str_645 "message"
#define str_646 "errmessage"
#define str_647 "lowercase"
#define str_648 "uppercase"
#define str_649 "show"
#define str_650 "showbox"
#define str_651 "showthe"
#define str_652 "showlists"
#define str_653 "long macro"
#define str_654 "outer macro"
#define str_655 "outer endtemplate"
#define str_656 " (INITEX)"
#define str_657 "end occurred "
#define str_658 "openout"
#define str_659 "closeout"
#define str_660 "special"
#define str_661 "immediate"
#define str_662 "setlanguage"
#define str_663 "ext1"
#define str_664 "ext2"
#define str_665 "ext3"
#define str_666 "endwrite"
#define str_667 "ext4"

#line 370 ".\\dummy.w"


/*:12*//*61:*/
#line 1463 ".\\dummy.w"

#define put(file)    fwrite(&((file).d),sizeof((file).d),1,(file).f)
#define get(file)    fread(&((file).d),sizeof((file).d),1,(file).f)

#define reset(file,name,mode)   ((file).f= fopen((char *)(name)+1,mode),\
                                 (file).f!=NULL?get(file):0)
#define rewrite(file,name,mode) ((file).f= fopen((char *)(name)+1,mode))
#define pascal_close(file)    fclose((file).f)
#define eof(file)    feof((file).f)
#define eoln(file)    ((file).d=='\n'||eof(file))
#define erstat(file)   ((file).f==NULL?-1:ferror((file).f))

#define pascal_read(file,x) ((x)= (file).d,get(file))
#define read_ln(file)  do get(file); while (!eoln(file))

#define pascal_write(file, format,...)    fprintf(file.f,format,## __VA_ARGS__)
#define write_ln(file,...)    pascal_write(file,__VA_ARGS__"\n")

#define wterm(format,...) pascal_write(term_out,format, ## __VA_ARGS__)
#define wterm_ln(format,...) wterm(format "\n", ## __VA_ARGS__)
#define wterm_cr         pascal_write(term_out,"\n")
#define wlog(format, ...) pascal_write(log_file,format, ## __VA_ARGS__)
#define wlog_ln(format, ...)   wlog(format "\n", ## __VA_ARGS__)
#define wlog_cr         pascal_write(log_file,"\n")

/*:61*//*130:*/
#line 2637 ".\\dummy.w"

#ifdef DEBUG
#define incr_dyn_used incr(dyn_used)
#define decr_dyn_used decr(dyn_used)
#else
#define incr_dyn_used
#define decr_dyn_used
#endif

/*:130*/
#line 264 ".\\dummy.w"

#endif

/*:5*//*692:*/
#line 13203 ".\\dummy.w"

#define vpack(...) vpackage(__VA_ARGS__, max_dimen)


/*:692*/
