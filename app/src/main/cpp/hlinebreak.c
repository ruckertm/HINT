/*834:*/
#line 16047 ".\\dummy.w"

#include "htex.h"
#include "hformat.h"
#include "hdefaults.h"
#include "hpos.h"
#include "texdef.h"

/*664:*/
#line 12930 ".\\dummy.w"

/*:664*//*833:*/
#line 16039 ".\\dummy.w"

pointer just_box;

/*:833*//*841:*/
#line 16189 ".\\dummy.w"

pointer passive;
pointer printed_node;
halfword pass_number;

/*:841*//*844:*/
#line 16229 ".\\dummy.w"

scaled active_width0[6],*const active_width= active_width0-1;

scaled cur_active_width0[6],*const cur_active_width= cur_active_width0-1;
scaled background0[6],*const background= background0-1;
scaled break_width0[6],*const break_width= break_width0-1;

/*:844*//*847:*/
#line 16287 ".\\dummy.w"

bool no_shrink_error_yet;

/*:847*//*851:*/
#line 16330 ".\\dummy.w"

pointer cur_p;
bool second_pass;
bool final_pass;
int threshold;

/*:851*//*857:*/
#line 16431 ".\\dummy.w"

int minimal_demerits0[tight_fit-very_loose_fit+1],*const minimal_demerits= minimal_demerits0-very_loose_fit;

int minimum_demerits;

pointer best_place0[tight_fit-very_loose_fit+1],*const best_place= best_place0-very_loose_fit;

halfword best_pl_line0[tight_fit-very_loose_fit+1],*const best_pl_line= best_pl_line0-very_loose_fit;


/*:857*//*864:*/
#line 16550 ".\\dummy.w"

scaled disc_width;

/*:864*//*873:*/
#line 16689 ".\\dummy.w"

halfword easy_line;
halfword last_special_line;

scaled first_width;

scaled second_width;
scaled first_indent;
scaled second_indent;

/*:873*//*899:*/
#line 17186 ".\\dummy.w"

pointer best_bet;
int fewest_demerits;
halfword best_line;
int actual_looseness;

int line_diff;


/*:899*/
#line 16054 ".\\dummy.w"


/*697:*/
#line 13321 ".\\dummy.w"

void append_to_vlist(pointer b,uint32_t offset)
{scaled d;
pointer p;
if(prev_depth> ignore_depth)
{d= width(baseline_skip)-prev_depth-height(b);
if(d<line_skip_limit)p= hget_param_glue(line_skip_no);
else{temp_ptr= new_spec(pointer_def[glue_kind][baseline_skip_no]);
p= new_glue(temp_ptr);glue_ref_count(temp_ptr)= null;
width(temp_ptr)= d;
}
store_map(p,node_pos,offset,0);
link(tail)= p;tail= p;
}
link(tail)= b;tail= b;prev_depth= depth(b);
}

/*:697*//*848:*/
#line 16290 ".\\dummy.w"

pointer finite_shrink(pointer p)
{pointer q;
QUIT("Infinite glue shrinkage found in a paragraph");
q= new_spec(p);shrink_order(q)= normal;
delete_glue_ref(p);return q;
}

/*:848*//*852:*/
#line 16353 ".\\dummy.w"

void try_break(int pi,small_number break_type)
{
pointer r;
pointer prev_r;
halfword old_l;
bool no_break_yet;
/*853:*/
#line 16381 ".\\dummy.w"

pointer prev_prev_r;
pointer s;
pointer q;
pointer v;
int t;
internal_font_number f;
halfword l;
bool node_r_stays_active;
scaled line_width;
uint8_t fit_class;
halfword b;
int d;
bool artificial_demerits;
#ifdef STAT
#endif
scaled shortfall;

/*:853*/
#line 16360 ".\\dummy.w"

/*854:*/
#line 16399 ".\\dummy.w"

if(abs(pi)>=inf_penalty)
if(pi> 0)goto end;
else pi= eject_penalty

/*:854*/
#line 16361 ".\\dummy.w"
;
no_break_yet= true;prev_r= active;old_l= 0;
do_all_six(copy_to_cur_active);
loop{resume:r= link(prev_r);
/*855:*/
#line 16409 ".\\dummy.w"


if(type(r)==delta_node)
{do_all_six(update_width);
prev_prev_r= prev_r;prev_r= r;goto resume;
}

/*:855*/
#line 16366 ".\\dummy.w"
;
/*859:*/
#line 16455 ".\\dummy.w"

{l= line_number(r);
if(l> old_l)
{
if((minimum_demerits<awful_bad)&&
((old_l!=easy_line)||(r==last_active)))
/*860:*/
#line 16473 ".\\dummy.w"

{if(no_break_yet)/*861:*/
#line 16509 ".\\dummy.w"

{no_break_yet= false;do_all_six(set_break_width_to_background);
s= cur_p;
if(break_type> unhyphenated)if(cur_p!=null)
/*865:*/
#line 16553 ".\\dummy.w"

{t= replace_count(cur_p);v= cur_p;s= post_break(cur_p);
while(t> 0)
{decr(t);v= link(v);
/*866:*/
#line 16571 ".\\dummy.w"

if(is_char_node(v))
{f= font(v);
break_width[1]= break_width[1]-char_width(f)(char_info(f)(character(v)));
}
else switch(type(v)){
case ligature_node:{f= font(lig_char(v));
break_width[1]= break_width[1]-
char_width(f)(char_info(f)(character(lig_char(v))));
}break;
case hlist_node:case vlist_node:case rule_node:case kern_node:
break_width[1]= break_width[1]-width(v);break;
default:QUIT("Replacement texts must contain only characters, kerns, ligatures, boxes or rules got %d",type(v));

}

/*:866*/
#line 16557 ".\\dummy.w"
;
}
while(s!=null)
{/*867:*/
#line 16587 ".\\dummy.w"

if(is_char_node(s))
{f= font(s);
break_width[1]= break_width[1]+char_width(f)(char_info(f)(character(s)));
}
else switch(type(s)){
case ligature_node:{f= font(lig_char(s));
break_width[1]= break_width[1]+
char_width(f)(char_info(f)(character(lig_char(s))));
}break;
case hlist_node:case vlist_node:case rule_node:case kern_node:
break_width[1]= break_width[1]+width(s);break;
default:QUIT("Replacement texts must contain only characters, kerns, ligatures, boxes or rules got %d",type(s));

}

/*:867*/
#line 16560 ".\\dummy.w"
;
s= link(s);
}
break_width[1]= break_width[1]+disc_width;
if(post_break(cur_p)==null)s= link(v);

}

/*:865*/
#line 16513 ".\\dummy.w"
;
while(s!=null)
{if(is_char_node(s))goto done;
switch(type(s)){
case glue_node:/*862:*/
#line 16528 ".\\dummy.w"

{v= glue_ptr(s);break_width[1]= break_width[1]-width(v);
break_width[2+stretch_order(v)]= break_width[2+stretch_order(v)]-stretch(v);
break_width[6]= break_width[6]-shrink(v);
}

/*:862*/
#line 16517 ".\\dummy.w"
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

/*:861*/
#line 16474 ".\\dummy.w"
;
/*868:*/
#line 16612 ".\\dummy.w"

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

/*:868*/
#line 16475 ".\\dummy.w"
;
if(abs(adj_demerits)>=awful_bad-minimum_demerits)
minimum_demerits= awful_bad-1;
else minimum_demerits= minimum_demerits+abs(adj_demerits);
for(fit_class= very_loose_fit;fit_class<=tight_fit;fit_class++)
{if(minimal_demerits[fit_class]<=minimum_demerits)
/*870:*/
#line 16642 ".\\dummy.w"

{q= get_node(passive_node_size);
link(q)= passive;passive= q;cur_break(q)= cur_p;
#ifdef STAT
incr(pass_number);serial(q)= pass_number;
#endif

prev_break(q)= best_place[fit_class];
q= get_node(active_node_size);break_node(q)= passive;
line_number(q)= best_pl_line[fit_class]+1;
fitness(q)= fit_class;type(q)= break_type;
total_demerits(q)= minimal_demerits[fit_class];
link(q)= r;link(prev_r)= q;prev_r= q;
#ifdef STAT
#endif

}

/*:870*/
#line 16481 ".\\dummy.w"
;
minimal_demerits[fit_class]= awful_bad;
}
minimum_demerits= awful_bad;
/*869:*/
#line 16631 ".\\dummy.w"

if(r!=last_active)
{q= get_node(delta_node_size);link(q)= r;type(q)= delta_node;
subtype(q)= 0;
do_all_six(new_delta_from_break_width);
link(prev_r)= q;prev_prev_r= prev_r;prev_r= q;
}

/*:869*/
#line 16485 ".\\dummy.w"
;
}

/*:860*/
#line 16461 ".\\dummy.w"
;
if(r==last_active)goto end;
/*876:*/
#line 16734 ".\\dummy.w"

if(l> easy_line)
{line_width= second_width;old_l= max_halfword-1;
}
else{old_l= l;
if(l> last_special_line)line_width= second_width;
else if(par_shape_ptr==null)line_width= first_width;
else line_width= mem[par_shape_ptr+2*l].sc;
}

/*:876*/
#line 16463 ".\\dummy.w"
;
}
}

/*:859*/
#line 16369 ".\\dummy.w"
;
/*877:*/
#line 16754 ".\\dummy.w"

{artificial_demerits= false;

shortfall= line_width-cur_active_width[1];
if(shortfall> 0)
/*878:*/
#line 16784 ".\\dummy.w"

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

/*:878*/
#line 16760 ".\\dummy.w"

else/*879:*/
#line 16803 ".\\dummy.w"

{if(-shortfall> cur_active_width[6])b= inf_bad+1;
else b= badness(-shortfall,cur_active_width[6]);
if(b> 12)fit_class= tight_fit;else fit_class= decent_fit;
}

/*:879*/
#line 16762 ".\\dummy.w"
;
if((b> inf_bad)||(pi==eject_penalty))
/*880:*/
#line 16818 ".\\dummy.w"

{if(final_pass&&(minimum_demerits==awful_bad)&&
(link(r)==last_active)&&
(prev_r==active))
artificial_demerits= true;
else if(b> threshold)goto deactivate;
node_r_stays_active= false;
}

/*:880*/
#line 16765 ".\\dummy.w"

else{prev_r= r;
if(b> threshold)goto resume;
node_r_stays_active= true;
}
/*881:*/
#line 16834 ".\\dummy.w"

if(artificial_demerits)d= 0;
else/*885:*/
#line 16893 ".\\dummy.w"

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

/*:885*/
#line 16836 ".\\dummy.w"
;
#ifdef STAT
#endif

d= d+total_demerits(r);

if(d<=minimal_demerits[fit_class])
{minimal_demerits[fit_class]= d;
best_place[fit_class]= break_node(r);best_pl_line[fit_class]= l;
if(d<minimum_demerits)minimum_demerits= d;
}

/*:881*/
#line 16770 ".\\dummy.w"
;
if(node_r_stays_active)goto resume;
deactivate:/*886:*/
#line 16915 ".\\dummy.w"

link(prev_r)= link(r);free_node(r,active_node_size);
if(prev_r==active)/*887:*/
#line 16940 ".\\dummy.w"

{r= link(active);
if(type(r)==delta_node)
{do_all_six(update_active);
do_all_six(copy_to_cur_active);
link(active)= link(r);free_node(r,delta_node_size);
}
}

/*:887*/
#line 16918 ".\\dummy.w"

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

/*:886*/
#line 16772 ".\\dummy.w"
;
}

/*:877*/
#line 16372 ".\\dummy.w"
;
}
end:;
#ifdef STAT
/*884:*/
#line 16885 ".\\dummy.w"

if(cur_p==printed_node)if(cur_p!=null)if(type(cur_p)==disc_node)
{t= replace_count(cur_p);
while(t> 0)
{decr(t);printed_node= link(printed_node);
}
}

/*:884*/
#line 16376 ".\\dummy.w"
;
#endif

}

/*:852*//*904:*/
#line 17257 ".\\dummy.w"

void post_line_break(int final_widow_penalty)
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
/*905:*/
#line 17309 ".\\dummy.w"

q= break_node(best_bet);cur_p= null;
do{r= q;q= prev_break(q);next_break(r)= cur_p;cur_p= r;
}while(!(q==null))

/*:905*/
#line 17270 ".\\dummy.w"
;
cur_line= prev_graf+1;
next_offset= hmap(link(temp_head));
if(next_offset> node_pos)
next_offset= next_offset-node_pos;
else
next_offset= 0;
do{
line_offset= next_offset;
{pointer q= cur_break(cur_p);
if(q==null)
next_offset= (hstart-hpos);
else
next_offset= hmap(q);
if(next_offset> node_pos)
next_offset= next_offset-node_pos;
else
next_offset= 0;
}
/*907:*/
#line 17346 ".\\dummy.w"

/*908:*/
#line 17358 ".\\dummy.w"

q= cur_break(cur_p);disc_break= false;post_disc_break= false;
if(q!=null)
if(type(q)==glue_node)
{delete_glue_ref(glue_ptr(q));
glue_ptr(q)= right_skip;
subtype(q)= right_skip_code+1;add_glue_ref(right_skip);
goto done;
}
else{if(type(q)==disc_node)
/*909:*/
#line 17377 ".\\dummy.w"

{t= replace_count(q);
/*910:*/
#line 17385 ".\\dummy.w"

if(t==0)r= link(q);
else{r= q;
while(t> 1)
{r= link(r);decr(t);
}
s= link(r);
r= link(s);link(s)= null;
flush_node_list(link(q));set_replace_count(q,0);
}

/*:910*/
#line 17379 ".\\dummy.w"
;
if(post_break(q)!=null)/*911:*/
#line 17399 ".\\dummy.w"

{s= post_break(q);
while(link(s)!=null)s= link(s);
link(s)= r;r= post_break(q);post_break(q)= null;post_disc_break= true;
}

/*:911*/
#line 17380 ".\\dummy.w"
;
if(pre_break(q)!=null)/*912:*/
#line 17408 ".\\dummy.w"

{s= pre_break(q);link(q)= s;
while(link(s)!=null)s= link(s);
pre_break(q)= null;q= s;
}

/*:912*/
#line 17381 ".\\dummy.w"
;
link(q)= r;disc_break= true;
}

/*:909*/
#line 17368 ".\\dummy.w"

else if((type(q)==math_node)||(type(q)==kern_node))width(q)= 0;
}
else{q= temp_head;
while(link(q)!=null)q= link(q);
}
/*913:*/
#line 17414 ".\\dummy.w"

r= hget_param_glue(right_skip_no);link(r)= link(q);link(q)= r;q= r

/*:913*/
#line 17374 ".\\dummy.w"
;
done:

/*:908*/
#line 17348 ".\\dummy.w"
;
/*914:*/
#line 17421 ".\\dummy.w"

r= link(q);link(q)= null;q= link(temp_head);link(temp_head)= r;
if(left_skip!=zero_glue)
{r= hget_param_glue(left_skip_no);
link(r)= q;q= r;
}

/*:914*/
#line 17349 ".\\dummy.w"
;
/*916:*/
#line 17446 ".\\dummy.w"

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

/*:916*/
#line 17350 ".\\dummy.w"
;
/*915:*/
#line 17428 ".\\dummy.w"

if(first_line)
{pointer p= happend_to_vlist(just_box);
hset_map_offset(p,line_offset);
first_line= false;
}
else
append_to_vlist(just_box,line_offset);
if(adjust_head!=adjust_tail)
{link(tail)= link(adjust_head);tail= adjust_tail;
}
adjust_tail= null

/*:915*/
#line 17352 ".\\dummy.w"
;
/*917:*/
#line 17466 ".\\dummy.w"

if(cur_line+1!=best_line)
{pen= inter_line_penalty;
if(cur_line==prev_graf+1)pen= pen+club_penalty;
if(cur_line+2==best_line)pen= pen+final_widow_penalty;
if(disc_break)pen= pen+broken_penalty;
if(pen!=0)
{r= new_penalty(pen);store_map(r,node_pos,next_offset,0);
link(tail)= r;tail= r;
}
}

/*:917*/
#line 17353 ".\\dummy.w"


/*:907*/
#line 17290 ".\\dummy.w"
;

incr(cur_line);cur_p= next_break(cur_p);

if(cur_p!=null)if(!post_disc_break)
/*906:*/
#line 17321 ".\\dummy.w"

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

/*:906*/
#line 17295 ".\\dummy.w"
;
}while(!(cur_p==null));
if((cur_line!=best_line)||(link(temp_head)!=null))
QUIT("Error in line breaking");

prev_graf= best_line-1;
}

/*:904*//*922:*/
#line 17577 ".\\dummy.w"

/*:922*//*970:*/
#line 18390 ".\\dummy.w"

#ifdef INIT
#endif

/*:970*/
#line 16056 ".\\dummy.w"


void line_break(int final_widow_penalty)
{scaled x;
/*888:*/
#line 16969 ".\\dummy.w"

bool auto_breaking;
pointer prev_p;
pointer q,r,s;
internal_font_number f;

/*:888*//*920:*/
#line 17560 ".\\dummy.w"


/*:920*/
#line 16060 ".\\dummy.w"

/*835:*/
#line 16079 ".\\dummy.w"

link(temp_head)= link(head);
if(is_char_node(tail))tail_append(new_penalty(inf_penalty))
else if(type(tail)!=glue_node)tail_append(new_penalty(inf_penalty))
else{type(tail)= penalty_node;delete_glue_ref(glue_ptr(tail));
flush_node_list(leader_ptr(tail));penalty(tail)= inf_penalty;
}
link(tail)= hget_param_glue(par_fill_skip_no);
pop_nest();
x= cur_list.hs_field;

/*:835*//*849:*/
#line 16298 ".\\dummy.w"

no_shrink_error_yet= true;
check_shrinkage(left_skip);check_shrinkage(right_skip);
q= left_skip;r= right_skip;background[1]= width(q)+width(r);
background[2]= 0;background[3]= 0;background[4]= 0;background[5]= 0;
background[2+stretch_order(q)]= stretch(q);
background[2+stretch_order(r)]= background[2+stretch_order(r)]+stretch(r);
background[6]= shrink(q)+shrink(r);

/*:849*//*858:*/
#line 16441 ".\\dummy.w"

minimum_demerits= awful_bad;
minimal_demerits[tight_fit]= awful_bad;
minimal_demerits[decent_fit]= awful_bad;
minimal_demerits[loose_fit]= awful_bad;
minimal_demerits[very_loose_fit]= awful_bad;

/*:858*//*874:*/
#line 16702 ".\\dummy.w"

if(par_shape_ptr==null)
if(hang_indent==0)
{last_special_line= 0;second_width= x;
second_indent= 0;
}
else/*875:*/
#line 16713 ".\\dummy.w"

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

/*:875*/
#line 16708 ".\\dummy.w"

else QUIT("parshape not yet implemented");
if(looseness==0)easy_line= last_special_line;
else easy_line= max_halfword

/*:874*/
#line 16061 ".\\dummy.w"
;
/*889:*/
#line 16979 ".\\dummy.w"

threshold= pretolerance;
if(threshold>=0)
{
#ifdef STAT
#endif

second_pass= false;final_pass= false;
}
else{threshold= tolerance;second_pass= true;
final_pass= (emergency_stretch<=0);

#ifdef STAT
#endif

}
loop{if(threshold> inf_bad)threshold= inf_bad;
/*890:*/
#line 17028 ".\\dummy.w"

q= get_node(active_node_size);
type(q)= unhyphenated;fitness(q)= decent_fit;
link(q)= last_active;break_node(q)= null;
line_number(q)= prev_graf+1;total_demerits(q)= 0;link(active)= q;
do_all_six(store_background);
passive= null;printed_node= temp_head;pass_number= 0;
font_in_short_display= null_font

/*:890*/
#line 16996 ".\\dummy.w"
;
cur_p= link(temp_head);auto_breaking= true;
prev_p= cur_p;
while((cur_p!=null)&&(link(active)!=last_active))
/*892:*/
#line 17064 ".\\dummy.w"

{if(is_char_node(cur_p))
/*893:*/
#line 17096 ".\\dummy.w"

{prev_p= cur_p;
do{f= font(cur_p);
act_width= act_width+char_width(f)(char_info(f)(character(cur_p)));
cur_p= link(cur_p);
}while(!(!is_char_node(cur_p)));
}

/*:893*/
#line 17066 ".\\dummy.w"
;
switch(type(cur_p)){
case hlist_node:case vlist_node:case rule_node:act_width= act_width+width(cur_p);break;
case whatsit_node:/*1397:*/
#line 25019 ".\\dummy.w"

adv_past(cur_p)

/*:1397*/
#line 17069 ".\\dummy.w"
break;
case glue_node:{/*894:*/
#line 17107 ".\\dummy.w"

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

/*:894*/
#line 17071 ".\\dummy.w"
;
}break;
case kern_node:if(subtype(cur_p)==explicit)kern_break
else act_width= act_width+width(cur_p);break;
case ligature_node:{f= font(lig_char(cur_p));
act_width= act_width+char_width(f)(char_info(f)(character(lig_char(cur_p))));
}break;
case disc_node:/*895:*/
#line 17123 ".\\dummy.w"

{if(!is_auto_disc(cur_p)||second_pass||final_pass)
{s= pre_break(cur_p);disc_width= 0;
if(s==null)try_break(ex_hyphen_penalty,hyphenated);
else{do{/*896:*/
#line 17143 ".\\dummy.w"

if(is_char_node(s))
{f= font(s);
disc_width= disc_width+char_width(f)(char_info(f)(character(s)));
}
else switch(type(s)){
case ligature_node:{f= font(lig_char(s));
disc_width= disc_width+
char_width(f)(char_info(f)(character(lig_char(s))));
}break;
case hlist_node:case vlist_node:case rule_node:case kern_node:
disc_width= disc_width+width(s);break;
default:QUIT("Error in line break");

}

/*:896*/
#line 17127 ".\\dummy.w"
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
{/*897:*/
#line 17159 ".\\dummy.w"

if(is_char_node(s))
{f= font(s);
act_width= act_width+char_width(f)(char_info(f)(character(s)));
}
else switch(type(s)){
case ligature_node:{f= font(lig_char(s));
act_width= act_width+
char_width(f)(char_info(f)(character(lig_char(s))));
}break;
case hlist_node:case vlist_node:case rule_node:case kern_node:
act_width= act_width+width(s);break;
default:QUIT("Error in line break");

}

/*:897*/
#line 17137 ".\\dummy.w"
;
decr(r);s= link(s);
}
prev_p= cur_p;cur_p= s;goto done5;
}

/*:895*/
#line 17078 ".\\dummy.w"

case math_node:{auto_breaking= (subtype(cur_p)==after);kern_break;
}break;
case penalty_node:try_break(penalty(cur_p),unhyphenated);break;
case mark_node:case ins_node:case adjust_node:do_nothing;break;
default:QUIT("Error in line break");

}
prev_p= cur_p;cur_p= link(cur_p);
done5:;}

/*:892*/
#line 17002 ".\\dummy.w"
;
if(cur_p==null)
/*900:*/
#line 17195 ".\\dummy.w"

{try_break(eject_penalty,hyphenated);
if(link(active)!=last_active)
{/*901:*/
#line 17205 ".\\dummy.w"

r= link(active);fewest_demerits= awful_bad;
do{if(type(r)!=delta_node)if(total_demerits(r)<fewest_demerits)
{fewest_demerits= total_demerits(r);best_bet= r;
}
r= link(r);
}while(!(r==last_active));
best_line= line_number(best_bet)

/*:901*/
#line 17198 ".\\dummy.w"
;
if(looseness==0)goto done;
/*902:*/
#line 17219 ".\\dummy.w"

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

/*:902*/
#line 17200 ".\\dummy.w"
;
if((actual_looseness==looseness)||final_pass)goto done;
}
}

/*:900*/
#line 17005 ".\\dummy.w"
;
/*891:*/
#line 17037 ".\\dummy.w"

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

/*:891*/
#line 17006 ".\\dummy.w"
;
if(!second_pass)
{
#ifdef STAT
#endif
threshold= tolerance;second_pass= true;final_pass= (emergency_stretch<=0);
}
else{
#ifdef STAT
#endif
background[2]= background[2]+emergency_stretch;final_pass= true;
}
}
done:
#ifdef STAT
#endif

/*:889*/
#line 16062 ".\\dummy.w"
;
/*903:*/
#line 17243 ".\\dummy.w"

post_line_break(final_widow_penalty)

/*:903*/
#line 16064 ".\\dummy.w"
;
/*891:*/
#line 17037 ".\\dummy.w"

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

/*:891*/
#line 16065 ".\\dummy.w"
;
}

/*:834*/
