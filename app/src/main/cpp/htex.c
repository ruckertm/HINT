/*4:*/
#line 16 "htex.ch"

#include "basetypes.h"
#include <string.h> 
#include <math.h> 

#include "error.h"
#include "hformat.h"
#include "hget.h"
#include "htex.h"
#include "hint.h"
/*119:*/
#line 239 "htex.ch"

pointer temp_ptr;
#line 2489 "btex.w"

/*:119*//*120:*/
#line 249 "htex.ch"

memory_word mem0[mem_max-mem_min+1],*const mem= mem0-mem_min;
pointer lo_mem_max;
pointer hi_mem_min;
#line 2523 "btex.w"

/*:120*//*121:*/
#line 259 "htex.ch"

static int var_used,dyn_used;
#line 2534 "btex.w"
#ifdef STAT
#define incr_dyn_used incr(dyn_used)
#define decr_dyn_used decr(dyn_used)
#else
#define incr_dyn_used
#define decr_dyn_used
#endif

/*:121*//*122:*/
#line 269 "htex.ch"

static pointer avail;
#line 2558 "btex.w"

/*:122*//*128:*/
#line 297 "htex.ch"

static pointer rover;
#line 2662 "btex.w"

/*:128*//*657:*/
#line 1051 "htex.ch"

static scaled total_stretch0[filll-normal+1],*const total_stretch= total_stretch0-normal,total_shrink0[filll-normal+1],*const total_shrink= total_shrink0-normal;

#line 12886 "btex.w"

/*:657*//*659:*/
#line 1059 "htex.ch"

pointer adjust_tail= null;
#line 12894 "btex.w"

/*:659*//*828:*/
#line 1173 "htex.ch"

pointer just_box;
#line 16008 "btex.w"

/*:828*//*836:*/
#line 1223 "htex.ch"

static pointer passive;
#line 16151 "btex.w"
static pointer printed_node;
static halfword pass_number;

/*:836*//*839:*/
#line 1230 "htex.ch"

static scaled active_width0[6],*const active_width= active_width0-1;
#line 16190 "btex.w"

static scaled cur_active_width0[6],*const cur_active_width= cur_active_width0-1;
static scaled background0[6],*const background= background0-1;
static scaled break_width0[6],*const break_width= break_width0-1;

/*:839*//*842:*/
#line 1237 "htex.ch"

static bool no_shrink_error_yet;
#line 16247 "btex.w"

/*:842*//*846:*/
#line 1260 "htex.ch"

static pointer cur_p;
#line 16299 "btex.w"
static bool second_pass;
static bool final_pass;
static int threshold;

/*:846*//*852:*/
#line 1268 "htex.ch"

static int minimal_demerits0[tight_fit-very_loose_fit+1],*const minimal_demerits= minimal_demerits0-very_loose_fit;

#line 16401 "btex.w"
static int minimum_demerits;

static pointer best_place0[tight_fit-very_loose_fit+1],*const best_place= best_place0-very_loose_fit;

static halfword best_pl_line0[tight_fit-very_loose_fit+1],*const best_pl_line= best_pl_line0-very_loose_fit;


/*:852*//*859:*/
#line 1276 "htex.ch"

static scaled disc_width;
#line 16518 "btex.w"

/*:859*//*868:*/
#line 1283 "htex.ch"

static halfword easy_line;
#line 16658 "btex.w"
static halfword last_special_line;

static scaled first_width;

static scaled second_width;
static scaled first_indent;
static scaled second_indent;

/*:868*//*894:*/
#line 1387 "htex.ch"

static pointer best_bet;
#line 17168 "btex.w"
static int fewest_demerits;
static halfword best_line;
static int actual_looseness;

static int line_diff;


/*:894*//*995:*/
#line 1582 "htex.ch"

scaled best_height_plus_depth;

#line 18914 "btex.w"

/*:995*//*1004:*/
#line 1612 "htex.ch"

pointer page_tail;
#line 19120 "btex.w"
int page_contents;
scaled page_max_depth;
pointer best_page_break;
int least_page_cost;
scaled best_size;

/*:1004*//*1006:*/
#line 1623 "htex.ch"

scaled page_so_far[8];
#line 19205 "btex.w"
int insert_penalties;

/*:1006*/
#line 26 "htex.ch"


/*96:*/
#line 145 "htex.ch"

void overflow(char*s,int n)
{QUIT("Capacity exceeded, sorry [%s=%d=0x%X]\n",s,n,n);
}
#line 2021 "btex.w"

/*:96*//*97:*/
#line 169 "htex.ch"

void confusion(char*s)

{QUIT("This can't happen(%s)",s);}
#line 2046 "btex.w"

/*:97*/
#line 28 "htex.ch"

#line 266 "btex.w"

/*:4*//*102:*/
#line 178 "htex.ch"


static int half(int x)
#line 2110 "btex.w"
{if(odd(x))return(x+1)/2;
else return x/2;
}

/*:102*//*107:*/
#line 210 "htex.ch"

static bool arith_error;
static scaled rem;
#line 2194 "btex.w"

/*:107*//*109:*/
#line 218 "htex.ch"

static scaled x_over_n(scaled x,int n)
#line 2216 "btex.w"
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

/*:109*//*110:*/
#line 225 "htex.ch"

static scaled xn_over_d(scaled x,int n,int d)
#line 2242 "btex.w"
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

/*:110*//*111:*/
#line 232 "htex.ch"

halfword badness(scaled t,scaled s)
#line 2281 "btex.w"
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

/*:111*//*124:*/
#line 276 "htex.ch"

static pointer get_avail(void)
#line 2576 "btex.w"
{pointer p;
p= avail;
if(p!=null)avail= link(avail);
#line 288 "htex.ch"
else{decr(hi_mem_min);p= hi_mem_min;
if(hi_mem_min<=lo_mem_max)
{
#line 2585 "btex.w"
overflow("main memory size",mem_max+1-mem_min);


}
}
link(p)= null;
#ifdef STAT
incr(dyn_used);
#endif

return p;
}

/*:124*//*129:*/
#line 304 "htex.ch"

pointer get_node(int s)
#line 2672 "btex.w"
{
pointer p;
pointer q;
int r;
int t;
restart:p= rover;
do{/*131:*/
#line 2721 "btex.w"

q= p+node_size(p);

while(is_empty(q))
{t= rlink(q);
if(q==rover)rover= t;
llink(t)= llink(q);rlink(llink(q))= t;
q= q+node_size(q);
}
r= q-s;
if(r> p+1)/*132:*/
#line 2736 "btex.w"

{node_size(p)= r-p;

rover= p;
goto found;
}

/*:132*/
#line 2731 "btex.w"
;
if(r==p)if(rlink(p)!=p)
/*133:*/
#line 2745 "btex.w"

{rover= rlink(p);t= llink(p);
llink(rover)= t;rlink(t)= rover;
goto found;
}

/*:133*/
#line 2733 "btex.w"
;
node_size(p)= q-p

/*:131*/
#line 2679 "btex.w"
;

p= rlink(p);
}while(!(p==rover));
if(s==010000000000)
{return max_halfword;
}
if(lo_mem_max+2<hi_mem_min)if(lo_mem_max+2<=mem_bot+max_halfword)
/*130:*/
#line 2706 "btex.w"

{if(hi_mem_min-lo_mem_max>=1998)t= lo_mem_max+1000;
else t= lo_mem_max+1+(hi_mem_min-lo_mem_max)/2;

p= llink(rover);q= lo_mem_max;rlink(p)= q;llink(rover)= q;
if(t> mem_bot+max_halfword)t= mem_bot+max_halfword;
rlink(q)= rover;llink(q)= p;link(q)= empty_flag;node_size(q)= t-lo_mem_max;
lo_mem_max= t;link(lo_mem_max)= null;info(lo_mem_max)= null;
rover= q;goto restart;
}

/*:130*/
#line 2687 "btex.w"
;
overflow("main memory size",mem_max+1-mem_min);


found:link(r)= null;
#ifdef STAT
var_used= var_used+s;
#endif

#line 311 "htex.ch"
leak_in(r,s);
return r;
#line 2697 "btex.w"
}

/*:129*//*134:*/
#line 320 "htex.ch"

static void free_node(pointer p,halfword s)

{pointer q;
leak_out(p,s);
store_map(p,0,0);
#line 2759 "btex.w"
node_size(p)= s;link(p)= empty_flag;
q= llink(rover);llink(p)= q;rlink(p)= rover;
llink(rover)= p;rlink(q)= p;
#ifdef STAT
var_used= var_used-s;
#endif

}

/*:134*//*140:*/
#line 337 "htex.ch"

pointer new_null_box(void)
#line 2905 "btex.w"
{pointer p;
p= get_node(box_node_size);type(p)= hlist_node;
subtype(p)= min_quarterword;
width(p)= 0;depth(p)= 0;height(p)= 0;shift_amount(p)= 0;list_ptr(p)= null;
glue_sign(p)= normal;glue_order(p)= normal;set_glue_ratio_zero(glue_set(p));
return p;
}

/*:140*//*143:*/
#line 344 "htex.ch"

pointer new_rule(void)
#line 2935 "btex.w"
{pointer p;
p= get_node(rule_node_size);type(p)= rule_node;
subtype(p)= 0;
width(p)= null_flag;depth(p)= null_flag;height(p)= null_flag;
return p;
}

/*:143*//*148:*/
#line 351 "htex.ch"

pointer new_ligature(quarterword f,quarterword c,pointer q)
#line 3004 "btex.w"
{pointer p;
p= get_node(small_node_size);type(p)= ligature_node;
font(lig_char(p))= f;character(lig_char(p))= c;lig_ptr(p)= q;
subtype(p)= 0;return p;
}

#line 3015 "btex.w"

/*:148*//*149:*/
#line 376 "htex.ch"

pointer new_disc(void)
#line 3039 "btex.w"
{pointer p;
p= get_node(small_node_size);type(p)= disc_node;
#line 383 "htex.ch"
subtype(p)= 0;pre_break(p)= null;post_break(p)= null;
#line 3042 "btex.w"
return p;
}

/*:149*//*151:*/
#line 389 "htex.ch"

pointer new_math(scaled w,small_number s)
#line 3073 "btex.w"
{pointer p;
p= get_node(small_node_size);type(p)= math_node;
subtype(p)= s;width(p)= w;return p;
}

/*:151*//*155:*/
#line 396 "htex.ch"

pointer new_spec(pointer p)
#line 3155 "btex.w"
{pointer q;
q= get_node(glue_spec_size);
mem[q]= mem[p];glue_ref_count(q)= null;
width(q)= width(p);stretch(q)= stretch(p);shrink(q)= shrink(p);
return q;
}

/*:155*//*157:*/
#line 403 "htex.ch"

pointer new_glue(pointer q)
#line 3181 "btex.w"
{pointer p;
p= get_node(small_node_size);type(p)= glue_node;subtype(p)= normal;
leader_ptr(p)= null;glue_ptr(p)= q;incr(glue_ref_count(q));
return p;
}

/*:157*//*160:*/
#line 410 "htex.ch"

pointer new_kern(scaled w)
#line 3219 "btex.w"
{pointer p;
p= get_node(small_node_size);type(p)= kern_node;
subtype(p)= normal;
width(p)= w;
return p;
}

/*:160*//*162:*/
#line 417 "htex.ch"

pointer new_penalty(int m)
#line 3242 "btex.w"
{pointer p;
p= get_node(small_node_size);type(p)= penalty_node;
subtype(p)= 0;
penalty(p)= m;return p;
}

/*:162*//*168:*/
#line 437 "htex.ch"

void mem_init(void)
{int k;
/*169:*/
#line 443 "htex.ch"

#line 3326 "btex.w"
for(k= mem_bot+1;k<=lo_mem_stat_max;k++)mem[k].sc= 0;


k= mem_bot;while(k<=lo_mem_stat_max)

{glue_ref_count(k)= null+1;
stretch_order(k)= normal;shrink_order(k)= normal;
k= k+glue_spec_size;
}
#line 3340 "btex.w"
rover= lo_mem_stat_max+1;
link(rover)= empty_flag;
node_size(rover)= 1000;
llink(rover)= rover;rlink(rover)= rover;
lo_mem_max= rover+1000;link(lo_mem_max)= null;info(lo_mem_max)= null;
for(k= hi_mem_stat_min;k<=mem_top;k++)
mem[k]= mem[lo_mem_max];
/*803:*/
#line 15552 "btex.w"

info(omit_template)= end_template_token;

/*:803*//*810:*/
#line 15658 "btex.w"

link(end_span)= max_quarterword+1;info(end_span)= null;

/*:810*//*834:*/
#line 16119 "btex.w"

type(last_active)= hyphenated;line_number(last_active)= max_halfword;
subtype(last_active)= 0;

/*:834*//*1005:*/
#line 19171 "btex.w"

subtype(page_ins_head)= qi(255);
type(page_ins_head)= split_up;link(page_ins_head)= page_ins_head;

/*:1005*//*1012:*/
#line 19327 "btex.w"

type(page_head)= glue_node;subtype(page_head)= normal;

/*:1012*/
#line 3347 "btex.w"
;
#line 458 "htex.ch"
avail= null;
#line 3349 "btex.w"
hi_mem_min= hi_mem_stat_min;
var_used= lo_mem_stat_max+1-mem_bot;dyn_used= hi_mem_stat_usage;


/*:169*/
#line 440 "htex.ch"

}

/*:168*//*209:*/
#line 617 "htex.ch"

void delete_glue_ref(pointer p)
fast_delete_glue_ref(p)
void delete_xdimen_ref(pointer p)
{if(xdimen_ref_count(p)==null)free_node(p,xdimen_node_size);
else decr(xdimen_ref_count(p));
}
#line 3897 "btex.w"

/*:209*//*210:*/
#line 629 "htex.ch"

void flush_node_list(pointer p)
#line 3904 "btex.w"
{
pointer q;
while(p!=null)

{q= link(p);
if(is_char_node(p))free_avail(p)
else{switch(type(p)){
case hlist_node:case vlist_node:case unset_node:{flush_node_list(list_ptr(p));
free_node(p,box_node_size);goto done;
}
case rule_node:{free_node(p,rule_node_size);goto done;
}
case ins_node:{flush_node_list(ins_ptr(p));
delete_glue_ref(split_top_ptr(p));
free_node(p,ins_node_size);goto done;
}
case whatsit_node:/*1386:*/
#line 24730 "btex.w"

{switch(subtype(p)){
#line 2404 "htex.ch"
case close_node:case language_node:free_node(p,small_node_size);break;
case par_node:
if(par_type(p)==glue_type)fast_delete_glue_ref(par_value(p).i);
free_node(p,par_node_size);break;
case graf_node:
delete_xdimen_ref(graf_extent(p));
flush_node_list(graf_params(p));
flush_node_list(graf_list(p));
free_node(p,graf_node_size);break;
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
free_node(p,image_node_size);break;
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
case link_node:
free_node(p,link_node_size);break;
case stream_node:
free_node(p,stream_node_size);break;
case xdimen_node:
free_node(p,xdimen_node_size);
#line 24737 "btex.w"
default:confusion("ext3");

}
goto done;
}

#line 2464 "htex.ch"
/*:1386*/
#line 3920 "btex.w"

case glue_node:{fast_delete_glue_ref(glue_ptr(p));
if(leader_ptr(p)!=null)flush_node_list(leader_ptr(p));
}break;
case kern_node:case math_node:case penalty_node:do_nothing;break;
case ligature_node:flush_node_list(lig_ptr(p));break;
#line 3927 "btex.w"
case disc_node:{flush_node_list(pre_break(p));
flush_node_list(post_break(p));
}break;
case adjust_node:flush_node_list(adjust_ptr(p));break;
#line 642 "htex.ch"
default:QUIT("Confusion while flushing node list");
#line 3933 "btex.w"

}
free_node(p,small_node_size);
done:;}
p= q;
}
}

/*:210*//*212:*/
#line 656 "htex.ch"

pointer copy_node_list(pointer p)

#line 3967 "btex.w"
{pointer h;
pointer q;
pointer r;
int words;
h= get_avail();q= h;
while(p!=null)
{/*213:*/
#line 3980 "btex.w"

words= 1;
if(is_char_node(p))r= get_avail();
else/*214:*/
#line 3989 "btex.w"

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
case whatsit_node:/*1385:*/
#line 24716 "btex.w"

switch(subtype(p)){
case open_node:{r= get_node(open_node_size);words= open_node_size;
}break;
case write_node:case special_node:{r= get_node(write_node_size);
add_token_ref(write_tokens(p));words= write_node_size;
}break;
case close_node:case language_node:{r= get_node(small_node_size);
words= small_node_size;
}break;
#line 2306 "htex.ch"
case par_node:
{r= get_node(par_node_size);
if(par_type(p)==glue_type)add_glue_ref(par_value(p).i);
words= par_node_size;
}break;
case graf_node:
{r= get_node(graf_node_size);
add_xdimen_ref(graf_extent(p));
graf_params(r)= copy_node_list(graf_params(p));
graf_list(r)= copy_node_list(graf_list(p));
words= graf_node_size-1;
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
pack_m(r)= pack_m(p);
list_ptr(r)= copy_node_list(list_ptr(p));
add_xdimen_ref(pack_extent(p));
pack_limit(r)= pack_limit(p);
words= pack_node_size-3;
}break;
case hset_node:case vset_node:
{r= get_node(set_node_size);
mem[r+8]= mem[p+8];mem[r+7]= mem[p+7];mem[r+6]= mem[p+6];mem[r+5]= mem[p+5];
add_xdimen_ref(set_extent(p));
list_ptr(r)= copy_node_list(list_ptr(p));
words= 5;
}break;
case image_node:
r= get_node(image_node_size);
words= image_node_size;
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
case link_node:
r= get_node(link_node_size);
words= link_node_size;
break;
case stream_node:
r= get_node(stream_node_size);
words= stream_node_size;
break;
case xdimen_node:
r= get_node(xdimen_node_size);
words= xdimen_node_size;
break;
default:confusion("ext2");
#line 24727 "btex.w"

}

/*:1385*/
#line 4004 "btex.w"
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

/*:214*/
#line 3984 "btex.w"
;
while(words> 0)
{decr(words);mem[r+words]= mem[p+words];
}

/*:213*/
#line 3973 "btex.w"
;
link(q)= r;q= r;p= link(p);
}
link(q)= null;q= link(h);free_avail(h);
return q;
}

/*:212*//*223:*/
#line 708 "htex.ch"


/*221:*/
#line 694 "htex.ch"

static list_state_record nest[nest_size+1];
int nest_ptr;
static int max_nest_stack;
list_state_record cur_list;
#line 4328 "btex.w"

/*:221*/
#line 710 "htex.ch"


void list_init(void)
{
nest_ptr= 0;max_nest_stack= 0;
memset(&cur_list,0,sizeof(cur_list));
mode= vmode;head= contrib_head;tail= contrib_head;
prev_height= prev_depth= ignore_depth;
}
/*:223*//*225:*/
#line 727 "htex.ch"

void push_nest(void)
#line 4354 "btex.w"
{if(nest_ptr> max_nest_stack)
{max_nest_stack= nest_ptr;
if(nest_ptr==nest_size)overflow("semantic nest size",nest_size);

}
nest[nest_ptr]= cur_list;
#line 734 "htex.ch"
incr(nest_ptr);head= get_avail();tail= head;prev_graf= 0;
cur_list.bs_pos= NULL;cur_bs= baseline_skip;cur_ls= line_skip;cur_lsl= line_skip_limit;
#line 4361 "btex.w"
}

/*:225*//*226:*/
#line 741 "htex.ch"

void pop_nest(void)
#line 4369 "btex.w"
{free_avail(head);decr(nest_ptr);cur_list= nest[nest_ptr];
}

/*:226*//*559:*/
#line 918 "htex.ch"

memory_word font_info[font_mem_size+1];

static font_index fmem_ptr= 0;

void hclear_fonts(void)
{fmem_ptr= 0;
}
#line 10724 "btex.w"
static internal_font_number font_ptr;
static four_quarters font_check0[font_max-font_base+1],*const font_check= font_check0-font_base;
scaled font_size0[font_max-font_base+1],*const font_size= font_size0-font_base;
static scaled font_dsize0[font_max-font_base+1],*const font_dsize= font_dsize0-font_base;
static font_index font_params0[font_max-font_base+1],*const font_params= font_params0-font_base;

#line 932 "htex.ch"
char*font_name0[font_max-font_base+1],**const font_name= font_name0-font_base;
#line 10732 "btex.w"
static eight_bits font_bc0[font_max-font_base+1],*const font_bc= font_bc0-font_base;

static eight_bits font_ec0[font_max-font_base+1],*const font_ec= font_ec0-font_base;

static pointer font_glue0[font_max-font_base+1],*const font_glue= font_glue0-font_base;

static bool font_used0[font_max-font_base+1],*const font_used= font_used0-font_base;

static int hyphen_char0[font_max-font_base+1],*const hyphen_char= hyphen_char0-font_base;

static int skew_char0[font_max-font_base+1],*const skew_char= skew_char0-font_base;

static font_index bchar_label0[font_max-font_base+1],*const bchar_label= bchar_label0-font_base;


static int16_t font_bchar0[font_max-font_base+1],*const font_bchar= font_bchar0-font_base;

static int16_t font_false_bchar0[font_max-font_base+1],*const font_false_bchar= font_false_bchar0-font_base;


/*:559*//*560:*/
#line 939 "htex.ch"

int char_base0[font_max-font_base+1],*const char_base= char_base0-font_base;
#line 10763 "btex.w"

int width_base0[font_max-font_base+1],*const width_base= width_base0-font_base;

static int height_base0[font_max-font_base+1],*const height_base= height_base0-font_base;

static int depth_base0[font_max-font_base+1],*const depth_base= depth_base0-font_base;

static int italic_base0[font_max-font_base+1],*const italic_base= italic_base0-font_base;

static int lig_kern_base0[font_max-font_base+1],*const lig_kern_base= lig_kern_base0-font_base;

static int kern_base0[font_max-font_base+1],*const kern_base= kern_base0-font_base;

static int exten_base0[font_max-font_base+1],*const exten_base= exten_base0-font_base;

static int param_base0[font_max-font_base+1],*const param_base= param_base0-font_base;


/*:560*//*570:*/
#line 947 "htex.ch"

void read_font_info(int f,char*nom,scaled s)
#line 10909 "btex.w"
{
int k;
bool file_opened;
halfword lf,lh,bc,ec,nw,nh,nd,ni,nl,nk,ne,np;

#line 10916 "btex.w"
eight_bits a,b,c,d;
four_quarters qw;scaled sw;
int bch_label;
int bchar;
scaled z;
int alpha;int beta;

#line 10924 "btex.w"
/*572:*/
#line 10960 "btex.w"

/*573:*/
#line 979 "htex.ch"

file_opened= true
#line 10978 "btex.w"

/*:573*/
#line 10961 "btex.w"
;
/*575:*/
#line 11000 "btex.w"

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

/*:575*/
#line 10962 "btex.w"
;
/*576:*/
#line 11027 "btex.w"

lf= lf-6-lh;
if(np<7)lf= lf+7-np;
if((font_ptr==font_max)||(fmem_ptr+lf> font_mem_size))
#line 995 "htex.ch"
QUIT("Not enough room left for font %s\n",nom);
#line 11033 "btex.w"
char_base[f]= fmem_ptr-bc;
width_base[f]= char_base[f]+ec+1;
height_base[f]= width_base[f]+nw;
depth_base[f]= height_base[f]+nh;
italic_base[f]= depth_base[f]+nd;
lig_kern_base[f]= italic_base[f]+ni;
kern_base[f]= lig_kern_base[f]+nl-kern_base_offset;
exten_base[f]= kern_base[f]+kern_base_offset+nk;
param_base[f]= exten_base[f]+ne

/*:576*/
#line 10963 "btex.w"
;
/*578:*/
#line 11056 "btex.w"

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

/*:578*/
#line 10964 "btex.w"
;
/*579:*/
#line 11072 "btex.w"

for(k= fmem_ptr;k<=width_base[f]-1;k++)
{store_four_quarters(font_info[k].qqqq);
if((a>=nw)||(b/020>=nh)||(b%020>=nd)||
(c/4>=ni))abort;
switch(c%4){
case lig_tag:if(d>=nl)abort;break;
case ext_tag:if(d>=ne)abort;break;
case list_tag:/*580:*/
#line 11093 "btex.w"

{check_byte_range(d);
while(d<current_character_being_worked_on)
{qw= char_info(f,d);

if(char_tag(qw)!=list_tag)goto not_found;
d= qo(rem_byte(qw));
}
if(d==current_character_being_worked_on)abort;
not_found:;}

/*:580*/
#line 11080 "btex.w"
break;
default:do_nothing;
}
}

/*:579*/
#line 10965 "btex.w"
;
/*581:*/
#line 11128 "btex.w"

{/*582:*/
#line 11138 "btex.w"

{alpha= 16;
while(z>=040000000)
{z= z/2;alpha= alpha+alpha;
}
beta= 256/alpha;alpha= alpha*z;
}

/*:582*/
#line 11129 "btex.w"
;
for(k= width_base[f];k<=lig_kern_base[f]-1;k++)
store_scaled(font_info[k].sc);
if(font_info[width_base[f]].sc!=0)abort;
if(font_info[height_base[f]].sc!=0)abort;
if(font_info[depth_base[f]].sc!=0)abort;
if(font_info[italic_base[f]].sc!=0)abort;
}

/*:581*/
#line 10966 "btex.w"
;
/*583:*/
#line 11152 "btex.w"

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

/*:583*/
#line 10967 "btex.w"
;
/*584:*/
#line 11172 "btex.w"

for(k= exten_base[f];k<=param_base[f]-1;k++)
{store_four_quarters(font_info[k].qqqq);
if(a!=0)check_existence(a);
if(b!=0)check_existence(b);
if(c!=0)check_existence(c);
check_existence(d);
}

/*:584*/
#line 10968 "btex.w"
;
/*585:*/
#line 11184 "btex.w"

{for(k= 1;k<=np;k++)
if(k==1)
{fget;sw= fbyte;if(sw> 127)sw= sw-256;
fget;sw= sw*0400+fbyte;fget;sw= sw*0400+fbyte;
fget;font_info[param_base[f]].sc= 
(sw*020)+(fbyte/020);
}
else store_scaled(font_info[param_base[f]+k-1].sc);
#line 1001 "htex.ch"
if(hpos>=hend)abort;
#line 11194 "btex.w"
for(k= np+1;k<=7;k++)font_info[param_base[f]+k-1].sc= 0;
}

/*:585*/
#line 10969 "btex.w"
;
/*586:*/
#line 11204 "btex.w"

if(np>=7)font_params[f]= np;else font_params[f]= 7;
#line 1007 "htex.ch"
hyphen_char[f]= skew_char[f]= -1;
#line 11207 "btex.w"
if(bch_label<nl)bchar_label[f]= bch_label+lig_kern_base[f];
else bchar_label[f]= non_address;
font_bchar[f]= qi(bchar);
font_false_bchar[f]= qi(bchar);
if(bchar<=ec)if(bchar>=bc)
{qw= char_info(f,bchar);
if(char_exists(qw))font_false_bchar[f]= non_char;
}
font_name[f]= nom;
#line 11217 "btex.w"
font_bc[f]= bc;font_ec[f]= ec;font_glue[f]= null;
adjust(char_base);adjust(width_base);adjust(lig_kern_base);
adjust(kern_base);adjust(exten_base);
decr(param_base[f]);
#line 1018 "htex.ch"
fmem_ptr= fmem_ptr+lf;goto done
#line 11222 "btex.w"

/*:586*/
#line 10970 "btex.w"


#line 979 "htex.ch"
/*:572*/
#line 10926 "btex.w"
;
#line 967 "htex.ch"
bad_tfm:QUIT("Bad tfm file: %s\n",nom);
done:;
#line 10930 "btex.w"
}

/*:570*//*592:*/
#line 1034 "htex.ch"

pointer new_character(internal_font_number f,eight_bits c)
{pointer p;
#ifdef DEBUG
if(font_bc[f]> c||font_ec[f]<c||!char_exists(char_info(f,qi(c))))
DBG(DBGFONT,"Warning: Character 0x%0X in font %d does not exist\n",c,f);
#endif
p= get_avail();font(p)= f;character(p)= qi(c);
return p;
}
#line 11319 "btex.w"

/*:592*//*661:*/
#line 1066 "htex.ch"

pointer hpack(pointer p,scaled w,small_number m)
#line 12900 "btex.w"
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
#line 1073 "htex.ch"
r= get_node(box_node_size);type(r)= hlist_node;
#line 12911 "btex.w"
subtype(r)= min_quarterword;shift_amount(r)= 0;
q= r+list_offset;link(q)= p;
h= 0;/*662:*/
#line 12926 "btex.w"

d= 0;x= 0;
total_stretch[normal]= 0;total_shrink[normal]= 0;
total_stretch[fil]= 0;total_shrink[fil]= 0;
total_stretch[fill]= 0;total_shrink[fill]= 0;
total_stretch[filll]= 0;total_shrink[filll]= 0

/*:662*/
#line 12913 "btex.w"
;
while(p!=null)/*663:*/
#line 12933 "btex.w"


{reswitch:while(is_char_node(p))
/*666:*/
#line 12976 "btex.w"

{f= font(p);i= char_info(f,character(p));hd= height_depth(i);
x= x+char_width(f,i);
s= char_height(f,hd);if(s> h)h= s;
s= char_depth(f,hd);if(s> d)d= s;
p= link(p);
}

/*:666*/
#line 12937 "btex.w"
;
if(p!=null)
{switch(type(p)){
case hlist_node:case vlist_node:case rule_node:case unset_node:
/*665:*/
#line 12964 "btex.w"

{x= x+width(p);
if(type(p)>=rule_node)s= 0;else s= shift_amount(p);
if(height(p)-s> h)h= height(p)-s;
if(depth(p)+s> d)d= depth(p)+s;
}

/*:665*/
#line 12941 "btex.w"
break;
case ins_node:case mark_node:case adjust_node:if(adjust_tail!=null)
/*667:*/
#line 12991 "btex.w"

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

/*:667*/
#line 12943 "btex.w"
break;
case whatsit_node:/*1388:*/
#line 2477 "htex.ch"

if(subtype(p)==image_node)
{glue_ord o;
if(image_height(p)> h)h= image_height(p);
x= x+image_width(p);
o= image_stretch_order(p);total_stretch[o]= total_stretch[o]+image_stretch(p);
o= image_shrink_order(p);total_shrink[o]= total_shrink[o]+image_shrink(p);
}
#line 24746 "btex.w"

/*:1388*/
#line 12944 "btex.w"
;break;
case glue_node:/*668:*/
#line 13003 "btex.w"

{g= glue_ptr(p);x= x+width(g);
o= stretch_order(g);total_stretch[o]= total_stretch[o]+stretch(g);
o= shrink_order(g);total_shrink[o]= total_shrink[o]+shrink(g);
if(subtype(p)>=a_leaders)
{g= leader_ptr(p);
if(height(g)> h)h= height(g);
if(depth(g)> d)d= depth(g);
}
}

/*:668*/
#line 12945 "btex.w"
break;
case kern_node:case math_node:x= x+width(p);break;
case ligature_node:/*664:*/
#line 12955 "btex.w"

{mem[lig_trick]= mem[lig_char(p)];link(lig_trick)= link(p);
p= lig_trick;goto reswitch;
}

/*:664*/
#line 12947 "btex.w"

default:do_nothing;
}
p= link(p);
}
}


/*:663*/
#line 12916 "btex.w"
;
if(adjust_tail!=null)link(adjust_tail)= null;
height(r)= h;depth(r)= d;
/*669:*/
#line 13017 "btex.w"

if(m==additional)w= x+w;
width(r)= w;x= w-x;
if(x==0)
{glue_sign(r)= normal;glue_order(r)= normal;
set_glue_ratio_zero(glue_set(r));
goto end;
}
else if(x> 0)/*670:*/
#line 13029 "btex.w"

{/*671:*/
#line 13043 "btex.w"

if(total_stretch[filll]!=0)o= filll;
else if(total_stretch[fill]!=0)o= fill;
else if(total_stretch[fil]!=0)o= fil;
else o= normal

/*:671*/
#line 13030 "btex.w"
;
glue_order(r)= o;glue_sign(r)= stretching;
if(total_stretch[o]!=0)glue_set(r)= unfloat(x/(double)total_stretch[o]);

else{glue_sign(r)= normal;
set_glue_ratio_zero(glue_set(r));
}
#line 13040 "btex.w"
goto end;
}

/*:670*/
#line 13026 "btex.w"

else/*676:*/
#line 13088 "btex.w"

{/*677:*/
#line 13107 "btex.w"

if(total_shrink[filll]!=0)o= filll;
else if(total_shrink[fill]!=0)o= fill;
else if(total_shrink[fil]!=0)o= fil;
else o= normal

/*:677*/
#line 13089 "btex.w"
;
glue_order(r)= o;glue_sign(r)= shrinking;
if(total_shrink[o]!=0)glue_set(r)= unfloat((-x)/(double)total_shrink[o]);

else{glue_sign(r)= normal;
set_glue_ratio_zero(glue_set(r));
}
if((total_shrink[o]<-x)&&(o==normal)&&(list_ptr(r)!=null))
#line 1098 "htex.ch"
set_glue_ratio_one(glue_set(r));
#line 13104 "btex.w"
goto end;
}

/*:676*/
#line 13027 "btex.w"


/*:669*/
#line 12920 "btex.w"
;
#line 12923 "btex.w"
end:return r;
}

/*:661*//*681:*/
#line 1108 "htex.ch"

pointer vpackage(pointer p,scaled h,small_number m,scaled l)
#line 13146 "btex.w"
{
pointer r;
scaled w,d,x;
scaled s;
pointer g;
glue_ord o;
#line 1115 "htex.ch"
r= get_node(box_node_size);type(r)= vlist_node;
#line 13153 "btex.w"
subtype(r)= min_quarterword;shift_amount(r)= 0;
list_ptr(r)= p;
w= 0;/*662:*/
#line 12926 "btex.w"

d= 0;x= 0;
total_stretch[normal]= 0;total_shrink[normal]= 0;
total_stretch[fil]= 0;total_shrink[fil]= 0;
total_stretch[fill]= 0;total_shrink[fill]= 0;
total_stretch[filll]= 0;total_shrink[filll]= 0

/*:662*/
#line 13155 "btex.w"
;
while(p!=null)/*682:*/
#line 13170 "btex.w"

{if(is_char_node(p))confusion("vpack");

else switch(type(p)){
case hlist_node:case vlist_node:case rule_node:case unset_node:
/*683:*/
#line 13185 "btex.w"

{x= x+d+height(p);d= depth(p);
if(type(p)>=rule_node)s= 0;else s= shift_amount(p);
if(width(p)+s> w)w= width(p)+s;
}

/*:683*/
#line 13175 "btex.w"
break;
case whatsit_node:/*1387:*/
#line 2464 "htex.ch"

if(subtype(p)==image_node)
{glue_ord o;
if(image_width(p)> w)w= image_width(p);
x= x+d+image_height(p);d= 0;
o= image_stretch_order(p);total_stretch[o]= total_stretch[o]+image_stretch(p);
o= image_shrink_order(p);total_shrink[o]= total_shrink[o]+image_shrink(p);
}
#line 24744 "btex.w"

#line 2477 "htex.ch"
/*:1387*/
#line 13176 "btex.w"
;break;
case glue_node:/*684:*/
#line 13191 "btex.w"

{x= x+d;d= 0;
g= glue_ptr(p);x= x+width(g);
o= stretch_order(g);total_stretch[o]= total_stretch[o]+stretch(g);
o= shrink_order(g);total_shrink[o]= total_shrink[o]+shrink(g);
if(subtype(p)>=a_leaders)
{g= leader_ptr(p);
if(width(g)> w)w= width(g);
}
}

/*:684*/
#line 13177 "btex.w"
break;
case kern_node:{x= x+d+width(p);d= 0;
}break;
default:do_nothing;
}
p= link(p);
}

/*:682*/
#line 13157 "btex.w"
;
width(r)= w;
if(d> l)
{x= x+d-l;depth(r)= l;
}
else depth(r)= d;
/*685:*/
#line 13205 "btex.w"

if(m==additional)h= x+h;
height(r)= h;x= h-x;
if(x==0)
{glue_sign(r)= normal;glue_order(r)= normal;
set_glue_ratio_zero(glue_set(r));
goto end;
}
else if(x> 0)/*686:*/
#line 13217 "btex.w"

{/*671:*/
#line 13043 "btex.w"

if(total_stretch[filll]!=0)o= filll;
else if(total_stretch[fill]!=0)o= fill;
else if(total_stretch[fil]!=0)o= fil;
else o= normal

/*:671*/
#line 13218 "btex.w"
;
glue_order(r)= o;glue_sign(r)= stretching;
if(total_stretch[o]!=0)glue_set(r)= unfloat(x/(double)total_stretch[o]);

else{glue_sign(r)= normal;
set_glue_ratio_zero(glue_set(r));
}
#line 13228 "btex.w"
goto end;
}

/*:686*/
#line 13214 "btex.w"

else/*689:*/
#line 13256 "btex.w"

{/*677:*/
#line 13107 "btex.w"

if(total_shrink[filll]!=0)o= filll;
else if(total_shrink[fill]!=0)o= fill;
else if(total_shrink[fil]!=0)o= fil;
else o= normal

/*:677*/
#line 13257 "btex.w"
;
glue_order(r)= o;glue_sign(r)= shrinking;
if(total_shrink[o]!=0)glue_set(r)= unfloat((-x)/(double)total_shrink[o]);

else{glue_sign(r)= normal;
set_glue_ratio_zero(glue_set(r));
}
if((total_shrink[o]<-x)&&(o==normal)&&(list_ptr(r)!=null))
#line 1140 "htex.ch"
set_glue_ratio_one(glue_set(r));
#line 13272 "btex.w"
goto end;
}

/*:689*/
#line 13215 "btex.w"


/*:685*/
#line 13164 "btex.w"
;
#line 13167 "btex.w"
end:return r;
}

/*:681*//*829:*/
#line 1182 "htex.ch"


/*692:*/
#line 1146 "htex.ch"

void append_to_vlist(pointer b,uint32_t offset)
#line 13296 "btex.w"
{scaled d;
pointer p;
if(prev_depth> ignore_depth)
{d= width(baseline_skip)-prev_depth-height(b);
#line 1156 "htex.ch"
if(d<line_skip_limit)p= new_glue(line_skip);
else{temp_ptr= new_spec(baseline_skip);
p= new_glue(temp_ptr);glue_ref_count(temp_ptr)= null;
width(temp_ptr)= d;
}
store_map(p,node_pos,offset);
#line 13304 "btex.w"
link(tail)= p;tail= p;
}
link(tail)= b;tail= b;prev_depth= depth(b);
}

/*:692*//*843:*/
#line 16248 "btex.w"

static pointer finite_shrink(pointer p)
{pointer q;
#line 1254 "htex.ch"
QUIT("Infinite glue shrinkage found in a paragraph");
#line 16262 "btex.w"
q= new_spec(p);shrink_order(q)= normal;
delete_glue_ref(p);return q;
}

/*:843*//*847:*/
#line 16320 "btex.w"

static void try_break(int pi,small_number break_type)
{
pointer r;
pointer prev_r;
halfword old_l;
bool no_break_yet;
/*848:*/
#line 16348 "btex.w"

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
scaled shortfall;

/*:848*/
#line 16327 "btex.w"

/*849:*/
#line 16367 "btex.w"

if(abs(pi)>=inf_penalty)
if(pi> 0)goto end;
else pi= eject_penalty

/*:849*/
#line 16328 "btex.w"
;
no_break_yet= true;prev_r= active;old_l= 0;
do_all_six(copy_to_cur_active);
loop{resume:r= link(prev_r);
/*850:*/
#line 16377 "btex.w"


if(type(r)==delta_node)
{do_all_six(update_width);
prev_prev_r= prev_r;prev_r= r;goto resume;
}

/*:850*/
#line 16333 "btex.w"
;
/*854:*/
#line 16422 "btex.w"

{l= line_number(r);
if(l> old_l)
{
if((minimum_demerits<awful_bad)&&
((old_l!=easy_line)||(r==last_active)))
/*855:*/
#line 16440 "btex.w"

{if(no_break_yet)/*856:*/
#line 16476 "btex.w"

{no_break_yet= false;do_all_six(set_break_width_to_background);
s= cur_p;
if(break_type> unhyphenated)if(cur_p!=null)
/*860:*/
#line 16519 "btex.w"

{t= replace_count(cur_p);v= cur_p;s= post_break(cur_p);
while(t> 0)
{decr(t);v= link(v);
/*861:*/
#line 16537 "btex.w"

if(is_char_node(v))
{f= font(v);
break_width[1]= break_width[1]-char_width(f,char_info(f,character(v)));
}
else switch(type(v)){
case ligature_node:{f= font(lig_char(v));
break_width[1]= break_width[1]-
char_width(f,char_info(f,character(lig_char(v))));
}break;
case hlist_node:case vlist_node:case rule_node:case kern_node:
break_width[1]= break_width[1]-width(v);break;
default:confusion("disc1");

}

/*:861*/
#line 16523 "btex.w"
;
}
while(s!=null)
{/*862:*/
#line 16553 "btex.w"

if(is_char_node(s))
{f= font(s);
break_width[1]= break_width[1]+char_width(f,char_info(f,character(s)));
}
else switch(type(s)){
case ligature_node:{f= font(lig_char(s));
break_width[1]= break_width[1]+
char_width(f,char_info(f,character(lig_char(s))));
}break;
case hlist_node:case vlist_node:case rule_node:case kern_node:
break_width[1]= break_width[1]+width(s);break;
default:confusion("disc2");

}

/*:862*/
#line 16526 "btex.w"
;
s= link(s);
}
break_width[1]= break_width[1]+disc_width;
if(post_break(cur_p)==null)s= link(v);

}

/*:860*/
#line 16480 "btex.w"
;
while(s!=null)
{if(is_char_node(s))goto done;
switch(type(s)){
case glue_node:/*857:*/
#line 16495 "btex.w"

{v= glue_ptr(s);break_width[1]= break_width[1]-width(v);
break_width[2+stretch_order(v)]= break_width[2+stretch_order(v)]-stretch(v);
break_width[6]= break_width[6]-shrink(v);
}

/*:857*/
#line 16484 "btex.w"
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

/*:856*/
#line 16441 "btex.w"
;
/*863:*/
#line 16578 "btex.w"

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

/*:863*/
#line 16442 "btex.w"
;
if(abs(adj_demerits)>=awful_bad-minimum_demerits)
minimum_demerits= awful_bad-1;
else minimum_demerits= minimum_demerits+abs(adj_demerits);
for(fit_class= very_loose_fit;fit_class<=tight_fit;fit_class++)
{if(minimal_demerits[fit_class]<=minimum_demerits)
/*865:*/
#line 16608 "btex.w"

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
if(tracing_paragraphs> 0)
/*866:*/
#line 16628 "btex.w"

{print_nl("@@");print_int(serial(passive));

print(": line ");print_int(line_number(q)-1);
print_char('.');print_int(fit_class);
if(break_type==hyphenated)print_char('-');
print(" t=");print_int(total_demerits(q));
print(" -> @@");
if(prev_break(passive)==null)print_char('0');
else print_int(serial(prev_break(passive)));
}

/*:866*/
#line 16623 "btex.w"
;
#endif

}

/*:865*/
#line 16448 "btex.w"
;
minimal_demerits[fit_class]= awful_bad;
}
minimum_demerits= awful_bad;
/*864:*/
#line 16597 "btex.w"

if(r!=last_active)
{q= get_node(delta_node_size);link(q)= r;type(q)= delta_node;
subtype(q)= 0;
do_all_six(new_delta_from_break_width);
link(prev_r)= q;prev_prev_r= prev_r;prev_r= q;
}

/*:864*/
#line 16452 "btex.w"
;
}

/*:855*/
#line 16428 "btex.w"
;
if(r==last_active)goto end;
/*871:*/
#line 16704 "btex.w"

if(l> easy_line)
{line_width= second_width;old_l= max_halfword-1;
}
else{old_l= l;
if(l> last_special_line)line_width= second_width;
else if(par_shape_ptr==null)line_width= first_width;
else line_width= mem[par_shape_ptr+2*l].sc;
}

/*:871*/
#line 16430 "btex.w"
;
}
}

/*:854*/
#line 16336 "btex.w"
;
/*872:*/
#line 16724 "btex.w"

{artificial_demerits= false;

shortfall= line_width-cur_active_width[1];
if(shortfall> 0)
/*873:*/
#line 16754 "btex.w"

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

/*:873*/
#line 16730 "btex.w"

else/*874:*/
#line 16773 "btex.w"

{if(-shortfall> cur_active_width[6])b= inf_bad+1;
else b= badness(-shortfall,cur_active_width[6]);
if(b> 12)fit_class= tight_fit;else fit_class= decent_fit;
}

/*:874*/
#line 16732 "btex.w"
;
if((b> inf_bad)||(pi==eject_penalty))
/*875:*/
#line 16788 "btex.w"

{if(final_pass&&(minimum_demerits==awful_bad)&&
(link(r)==last_active)&&
(prev_r==active))
artificial_demerits= true;
else if(b> threshold)goto deactivate;
node_r_stays_active= false;
}

/*:875*/
#line 16735 "btex.w"

else{prev_r= r;
if(b> threshold)goto resume;
node_r_stays_active= true;
}
/*876:*/
#line 16804 "btex.w"

if(artificial_demerits)d= 0;
else/*880:*/
#line 16865 "btex.w"

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

/*:880*/
#line 16806 "btex.w"
;
#ifdef STAT
if(tracing_paragraphs> 0)
/*877:*/
#line 16820 "btex.w"

{if(printed_node!=cur_p)
/*878:*/
#line 16842 "btex.w"

{print_nl("");
if(cur_p==null)short_display(link(printed_node));
else{save_link= link(cur_p);
link(cur_p)= null;print_nl("");short_display(link(printed_node));
link(cur_p)= save_link;
}
printed_node= cur_p;
}

/*:878*/
#line 16822 "btex.w"
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

/*:877*/
#line 16809 "btex.w"
;
#endif

d= d+total_demerits(r);

if(d<=minimal_demerits[fit_class])
{minimal_demerits[fit_class]= d;
best_place[fit_class]= break_node(r);best_pl_line[fit_class]= l;
if(d<minimum_demerits)minimum_demerits= d;
}

/*:876*/
#line 16740 "btex.w"
;
if(node_r_stays_active)goto resume;
deactivate:/*881:*/
#line 16887 "btex.w"

link(prev_r)= link(r);free_node(r,active_node_size);
if(prev_r==active)/*882:*/
#line 16912 "btex.w"

{r= link(active);
if(type(r)==delta_node)
{do_all_six(update_active);
do_all_six(copy_to_cur_active);
link(active)= link(r);free_node(r,delta_node_size);
}
}

/*:882*/
#line 16890 "btex.w"

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

/*:881*/
#line 16742 "btex.w"
;
}

/*:872*/
#line 16339 "btex.w"
;
}
end:;
#ifdef STAT
/*879:*/
#line 16857 "btex.w"

if(cur_p==printed_node)if(cur_p!=null)if(type(cur_p)==disc_node)
{t= replace_count(cur_p);
while(t> 0)
{decr(t);printed_node= link(printed_node);
}
}

/*:879*/
#line 16343 "btex.w"
;
#endif

}

/*:847*//*899:*/
#line 17237 "btex.w"

static void post_line_break(int final_widow_penalty)
{
pointer q,r,s;
bool disc_break;
#line 1394 "htex.ch"
bool post_disc_break;
bool first_line= true;
uint32_t line_offset,next_offset;
#line 17243 "btex.w"
scaled cur_width;
scaled cur_indent;
quarterword t;
int pen;
halfword cur_line;
/*900:*/
#line 17268 "btex.w"

q= break_node(best_bet);cur_p= null;
do{r= q;q= prev_break(q);next_break(r)= cur_p;cur_p= r;
}while(!(q==null))

/*:900*/
#line 17248 "btex.w"
;
cur_line= prev_graf+1;
#line 1403 "htex.ch"
next_offset= hposition(link(temp_head));
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
next_offset= hposition(q);
if(next_offset> node_pos)
next_offset= next_offset-node_pos;
else
next_offset= 0;
}
/*902:*/
#line 17305 "btex.w"

/*903:*/
#line 17317 "btex.w"

q= cur_break(cur_p);disc_break= false;post_disc_break= false;
if(q!=null)
if(type(q)==glue_node)
{delete_glue_ref(glue_ptr(q));
glue_ptr(q)= right_skip;
subtype(q)= right_skip_code+1;add_glue_ref(right_skip);
goto done;
}
else{if(type(q)==disc_node)
/*904:*/
#line 1433 "htex.ch"

{pointer pre_q= pre_break(q);
pointer post_q= post_break(q);
t= replace_count(q);
type(q)= whatsit_node;
subtype(q)= ignore_node;
ignore_info(q)= 1;
/*905:*/
#line 1465 "htex.ch"

if(t==0){ignore_list(q)= null;r= link(q);}
else{r= q;
while(t> 1)
{r= link(r);decr(t);
}
s= link(r);
r= link(s);link(s)= null;
ignore_list(q)= link(q);
}
#line 17354 "btex.w"

/*:905*/
#line 1440 "htex.ch"
;
s= get_node(ignore_node_size);
type(s)= whatsit_node;
subtype(s)= ignore_node;
ignore_info(s)= 0;
ignore_list(s)= null;
link(s)= r;r= s;
if(post_q!=null)/*906:*/
#line 1484 "htex.ch"

{s= post_q;
while(link(s)!=null)s= link(s);
link(s)= r;r= post_q;post_disc_break= true;
}
#line 17363 "btex.w"

/*:906*/
#line 1447 "htex.ch"
;
if(pre_q!=null)/*907:*/
#line 1498 "htex.ch"

{s= pre_q;link(q)= s;
while(link(s)!=null)s= link(s);
q= s;
}
#line 17372 "btex.w"

/*:907*/
#line 1448 "htex.ch"
;
link(q)= r;disc_break= true;
}
#line 17343 "btex.w"

#line 1465 "htex.ch"
/*:904*/
#line 17327 "btex.w"

else if((type(q)==math_node)||(type(q)==kern_node))width(q)= 0;
}
else{q= temp_head;
while(link(q)!=null)q= link(q);
}
/*908:*/
#line 17373 "btex.w"

#line 1508 "htex.ch"
r= new_glue(right_skip);link(r)= link(q);link(q)= r;q= r
#line 17375 "btex.w"

/*:908*/
#line 17333 "btex.w"
;
done:

#line 1433 "htex.ch"
/*:903*/
#line 17307 "btex.w"
;
/*909:*/
#line 17380 "btex.w"

r= link(q);link(q)= null;q= link(temp_head);link(temp_head)= r;
if(left_skip!=zero_glue)
#line 1514 "htex.ch"
{r= new_glue(left_skip);
#line 17384 "btex.w"
link(r)= q;q= r;
}

/*:909*/
#line 17308 "btex.w"
;
/*911:*/
#line 17399 "btex.w"

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

/*:911*/
#line 17309 "btex.w"
;
/*910:*/
#line 17387 "btex.w"

#line 1520 "htex.ch"
if(first_line)
{pointer p= happend_to_vlist(just_box);
uint32_t pos= hposition(p);
store_map(p,pos,line_offset);
first_line= false;
}
else
append_to_vlist(just_box,line_offset);
#line 17389 "btex.w"
if(adjust_head!=adjust_tail)
{link(tail)= link(adjust_head);tail= adjust_tail;
}
adjust_tail= null

/*:910*/
#line 17311 "btex.w"
;
/*912:*/
#line 17419 "btex.w"

if(cur_line+1!=best_line)
{pen= inter_line_penalty;
if(cur_line==prev_graf+1)pen= pen+club_penalty;
if(cur_line+2==best_line)pen= pen+final_widow_penalty;
if(disc_break)pen= pen+broken_penalty;
if(pen!=0)
#line 1533 "htex.ch"
{r= new_penalty(pen);store_map(r,node_pos,next_offset);
#line 17427 "btex.w"
link(tail)= r;tail= r;
}
}

/*:912*/
#line 17312 "btex.w"


/*:902*/
#line 1421 "htex.ch"
;
#line 17252 "btex.w"
incr(cur_line);cur_p= next_break(cur_p);
if(cur_p!=null)if(!post_disc_break)
/*901:*/
#line 17280 "btex.w"

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

/*:901*/
#line 17254 "btex.w"
;
}while(!(cur_p==null));
if((cur_line!=best_line)||(link(temp_head)!=null))
confusion("line breaking");

prev_graf= best_line-1;
}

/*:899*//*917:*/
#line 17532 "btex.w"

#line 1545 "htex.ch"
/*:917*//*965:*/
#line 18345 "btex.w"

#ifdef INIT
#line 18348 "btex.w"
#endif

/*:965*/
#line 1184 "htex.ch"


void line_break(int final_widow_penalty,pointer par_ptr)
{scaled x= cur_list.hs_field;
#line 16017 "btex.w"
/*883:*/
#line 16941 "btex.w"

bool auto_breaking;
pointer prev_p;
#line 1323 "htex.ch"
pointer q,r,s;
#line 16945 "btex.w"
internal_font_number f;

/*:883*//*915:*/
#line 17513 "btex.w"

#line 17516 "btex.w"

/*:915*/
#line 16017 "btex.w"

#line 1193 "htex.ch"
set_line_break_params();
#line 16019 "btex.w"
/*830:*/
#line 1216 "htex.ch"

link(temp_head)= par_ptr;
#line 16050 "btex.w"

/*:830*//*844:*/
#line 16266 "btex.w"

no_shrink_error_yet= true;
check_shrinkage(left_skip);check_shrinkage(right_skip);
q= left_skip;r= right_skip;background[1]= width(q)+width(r);
background[2]= 0;background[3]= 0;background[4]= 0;background[5]= 0;
background[2+stretch_order(q)]= stretch(q);
background[2+stretch_order(r)]= background[2+stretch_order(r)]+stretch(r);
background[6]= shrink(q)+shrink(r);

/*:844*//*853:*/
#line 16408 "btex.w"

minimum_demerits= awful_bad;
minimal_demerits[tight_fit]= awful_bad;
minimal_demerits[decent_fit]= awful_bad;
minimal_demerits[loose_fit]= awful_bad;
minimal_demerits[very_loose_fit]= awful_bad;

/*:853*//*869:*/
#line 16669 "btex.w"

if(par_shape_ptr==null)
if(hang_indent==0)
#line 1290 "htex.ch"
{last_special_line= 0;second_width= x;
#line 16673 "btex.w"
second_indent= 0;
}
else/*870:*/
#line 16683 "btex.w"

{last_special_line= abs(hang_after);
if(hang_after<0)
#line 1305 "htex.ch"
{first_width= x-abs(hang_indent);
#line 16687 "btex.w"
if(hang_indent>=0)first_indent= hang_indent;
else first_indent= 0;
#line 1314 "htex.ch"
second_width= x;second_indent= 0;
}
else{first_width= x;first_indent= 0;
second_width= x-abs(hang_indent);
#line 16693 "btex.w"
if(hang_indent>=0)second_indent= hang_indent;
else second_indent= 0;
}
}

/*:870*/
#line 16675 "btex.w"

#line 1299 "htex.ch"
else QUIT("parshape not yet implemented");
#line 16680 "btex.w"
if(looseness==0)easy_line= last_special_line;
else easy_line= max_halfword

/*:869*/
#line 16019 "btex.w"
;
/*884:*/
#line 16951 "btex.w"

threshold= pretolerance;
if(threshold>=0)
{
#ifdef STAT
#line 1330 "htex.ch"
 if(tracing_paragraphs> 0)
{print_nl("@firstpass");}
#line 16958 "btex.w"
#endif

second_pass= false;final_pass= false;
}
else{threshold= tolerance;second_pass= true;
final_pass= (emergency_stretch<=0);
#ifdef STAT
#line 16966 "btex.w"
#endif

}
loop{if(threshold> inf_bad)threshold= inf_bad;
#line 16971 "btex.w"
/*885:*/
#line 17009 "btex.w"

q= get_node(active_node_size);
type(q)= unhyphenated;fitness(q)= decent_fit;
link(q)= last_active;break_node(q)= null;
line_number(q)= prev_graf+1;total_demerits(q)= 0;link(active)= q;
do_all_six(store_background);
passive= null;printed_node= temp_head;pass_number= 0;
#line 17017 "btex.w"

/*:885*/
#line 16971 "btex.w"
;
cur_p= link(temp_head);auto_breaking= true;
prev_p= cur_p;
while((cur_p!=null)&&(link(active)!=last_active))
/*887:*/
#line 17045 "btex.w"

{if(is_char_node(cur_p))
/*888:*/
#line 17079 "btex.w"

{prev_p= cur_p;
do{f= font(cur_p);
act_width= act_width+char_width(f,char_info(f,character(cur_p)));
cur_p= link(cur_p);
}while(!(!is_char_node(cur_p)));
}

/*:888*/
#line 17047 "btex.w"
;
switch(type(cur_p)){
case hlist_node:case vlist_node:case rule_node:act_width= act_width+width(cur_p);break;
case whatsit_node:/*1390:*/
#line 24752 "btex.w"

adv_past(cur_p)

/*:1390*/
#line 17050 "btex.w"
break;
case glue_node:{/*889:*/
#line 17090 "btex.w"

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

/*:889*/
#line 17052 "btex.w"
;
#line 17055 "btex.w"
}break;
case kern_node:if(subtype(cur_p)==explicit)kern_break
else act_width= act_width+width(cur_p);break;
case ligature_node:{f= font(lig_char(cur_p));
act_width= act_width+char_width(f,char_info(f,character(lig_char(cur_p))));
}break;
case disc_node:/*890:*/
#line 17106 "btex.w"

#line 1373 "htex.ch"
{if(!is_auto_disc(cur_p)||second_pass||final_pass)
{s= pre_break(cur_p);disc_width= 0;
#line 17108 "btex.w"
if(s==null)try_break(ex_hyphen_penalty,hyphenated);
else{do{/*891:*/
#line 17124 "btex.w"

if(is_char_node(s))
{f= font(s);
disc_width= disc_width+char_width(f,char_info(f,character(s)));
}
else switch(type(s)){
case ligature_node:{f= font(lig_char(s));
disc_width= disc_width+
char_width(f,char_info(f,character(lig_char(s))));
}break;
case hlist_node:case vlist_node:case rule_node:case kern_node:
disc_width= disc_width+width(s);break;
default:confusion("disc3");

}

/*:891*/
#line 17109 "btex.w"
;
s= link(s);
}while(!(s==null));
act_width= act_width+disc_width;
try_break(hyphen_penalty,hyphenated);
act_width= act_width-disc_width;
}
#line 1380 "htex.ch"
}
r= replace_count(cur_p);s= link(cur_p);
#line 17117 "btex.w"
while(r> 0)
{/*892:*/
#line 17140 "btex.w"

if(is_char_node(s))
{f= font(s);
act_width= act_width+char_width(f,char_info(f,character(s)));
}
else switch(type(s)){
case ligature_node:{f= font(lig_char(s));
act_width= act_width+
char_width(f,char_info(f,character(lig_char(s))));
}break;
case hlist_node:case vlist_node:case rule_node:case kern_node:
act_width= act_width+width(s);break;
default:confusion("disc4");

}

/*:892*/
#line 17118 "btex.w"
;
decr(r);s= link(s);
}
prev_p= cur_p;cur_p= s;goto done5;
}

/*:890*/
#line 17061 "btex.w"

case math_node:{auto_breaking= (subtype(cur_p)==after);kern_break;
}break;
case penalty_node:try_break(penalty(cur_p),unhyphenated);break;
case mark_node:case ins_node:case adjust_node:do_nothing;break;
default:confusion("paragraph");

}
prev_p= cur_p;cur_p= link(cur_p);
done5:;}

/*:887*/
#line 16977 "btex.w"
;
if(cur_p==null)
/*895:*/
#line 17175 "btex.w"

{try_break(eject_penalty,hyphenated);
if(link(active)!=last_active)
{/*896:*/
#line 17185 "btex.w"

r= link(active);fewest_demerits= awful_bad;
do{if(type(r)!=delta_node)if(total_demerits(r)<fewest_demerits)
{fewest_demerits= total_demerits(r);best_bet= r;
}
r= link(r);
}while(!(r==last_active));
best_line= line_number(best_bet)

/*:896*/
#line 17178 "btex.w"
;
if(looseness==0)goto done;
/*897:*/
#line 17199 "btex.w"

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

/*:897*/
#line 17180 "btex.w"
;
if((actual_looseness==looseness)||final_pass)goto done;
}
}

/*:895*/
#line 16980 "btex.w"
;
/*886:*/
#line 17018 "btex.w"

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

/*:886*/
#line 16981 "btex.w"
;
if(!second_pass)
{
#ifdef STAT
if(tracing_paragraphs> 0)print_nl("@secondpass");
#endif
threshold= tolerance;second_pass= true;final_pass= (emergency_stretch<=0);
}
else{
#ifdef STAT
#line 1348 "htex.ch"
 if(tracing_paragraphs> 0)
print_nl("@emergencypass");
#line 16993 "btex.w"
#endif
background[2]= background[2]+emergency_stretch;final_pass= true;
}
}
done:
#ifdef STAT
#line 17002 "btex.w"
#endif

/*:884*/
#line 16020 "btex.w"
;
/*898:*/
#line 17223 "btex.w"

post_line_break(final_widow_penalty)

/*:898*/
#line 16022 "btex.w"
;
/*886:*/
#line 17018 "btex.w"

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

/*:886*/
#line 16023 "btex.w"
;
#line 1199 "htex.ch"
hrestore_param_list();
#line 16025 "btex.w"
}

/*:829*//*991:*/
#line 1557 "htex.ch"


#define ensure_vbox(N) 

static pointer prune_page_top(pointer p)
#line 18843 "btex.w"
{pointer prev_p;
pointer q;
prev_p= temp_head;link(temp_head)= p;
while(p!=null)
switch(type(p)){
case hlist_node:case vlist_node:case rule_node:/*992:*/
#line 18861 "btex.w"

#line 1567 "htex.ch"
{temp_ptr= new_spec(pointer_def[glue_kind][split_top_skip_no]);
q= new_glue(temp_ptr);glue_ref_count(temp_ptr)= null;link(prev_p)= q;link(q)= p;
#line 18863 "btex.w"

if(width(temp_ptr)> height(p))width(temp_ptr)= width(temp_ptr)-height(p);
else width(temp_ptr)= 0;
p= null;
}

/*:992*/
#line 18849 "btex.w"
break;
case whatsit_node:case mark_node:case ins_node:{prev_p= p;p= link(prev_p);
}break;
case glue_node:case kern_node:case penalty_node:{q= p;p= link(q);link(q)= null;
link(prev_p)= p;flush_node_list(q);
}break;
default:confusion("pruning");

}
return link(temp_head);
}

/*:991*//*993:*/
#line 1574 "htex.ch"

static pointer vert_break(pointer p,scaled h,scaled d)
#line 18886 "btex.w"

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
loop{/*996:*/
#line 18919 "btex.w"

if(p==null)pi= eject_penalty;
else/*997:*/
#line 18934 "btex.w"

switch(type(p)){
case hlist_node:case vlist_node:case rule_node:{
cur_height= cur_height+prev_dp+height(p);prev_dp= depth(p);
goto not_found;
}
case whatsit_node:/*1393:*/
#line 24761 "btex.w"

goto not_found

/*:1393*/
#line 18940 "btex.w"
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

/*:997*/
#line 18923 "btex.w"
;
/*998:*/
#line 18955 "btex.w"

if(pi<inf_penalty)
{/*999:*/
#line 18969 "btex.w"

if(cur_height<h)
if((active_height[3]!=0)||(active_height[4]!=0)||
(active_height[5]!=0))b= 0;
else b= badness(h-cur_height,active_height[2]);
else if(cur_height-h> active_height[6])b= awful_bad;
else b= badness(cur_height-h,active_height[6])

/*:999*/
#line 18957 "btex.w"
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

/*:998*/
#line 18925 "btex.w"
;
if((type(p)<glue_node)||(type(p)> kern_node))goto not_found;
update_heights:/*1000:*/
#line 18981 "btex.w"

if(type(p)==kern_node)q= p;
else{q= glue_ptr(p);
active_height[2+stretch_order(q)]= 
active_height[2+stretch_order(q)]+stretch(q);
active_height[6]= active_height[6]+shrink(q);
#line 1600 "htex.ch"
if((shrink_order(q)!=normal)&&(shrink(q)!=0))
{
DBG(DBGTEX,"Infinite glue shrinkage found in box being split");
r= new_spec(q);shrink_order(r)= normal;delete_glue_ref(q);
glue_ptr(p)= r;q= r;
}
#line 18998 "btex.w"
}
cur_height= cur_height+prev_dp+width(q);prev_dp= 0

/*:1000*/
#line 18928 "btex.w"
;
not_found:if(prev_dp> d)
{cur_height= cur_height+prev_dp-d;
prev_dp= d;
}

/*:996*/
#line 18901 "btex.w"
;
prev_p= p;p= link(prev_p);
}
done:return best_place;
}

/*:993*//*1011:*/
#line 1630 "htex.ch"

void freeze_page_specs(small_number s)
#line 19287 "btex.w"
{page_contents= s;
#line 1637 "htex.ch"
page_goal= hvsize;page_max_depth= max_depth;
#line 19289 "btex.w"
page_depth= 0;do_all_six(set_page_so_far_zero);
least_page_cost= awful_bad;
#line 19300 "btex.w"

}

/*:1011*//*1019:*/
#line 1663 "htex.ch"

bool hbuild_page(void)
#line 19385 "btex.w"
{
pointer p;
pointer q,r;
int b,c;
int pi;
#line 1672 "htex.ch"
if(link(contrib_head)==null)return false;
#line 19393 "btex.w"
do{resume:p= link(contrib_head);
#line 19395 "btex.w"
/*1022:*/
#line 19425 "btex.w"

/*1025:*/
#line 19453 "btex.w"

switch(type(p)){
case hlist_node:case vlist_node:case rule_node:if(page_contents<box_there)
/*1026:*/
#line 19474 "btex.w"

{if(page_contents==empty)freeze_page_specs(box_there);
else page_contents= box_there;
#line 1702 "htex.ch"
temp_ptr= new_spec(pointer_def[glue_kind][top_skip_no]);
q= new_glue(temp_ptr);glue_ref_count(temp_ptr)= null;
#line 19478 "btex.w"
if(width(temp_ptr)> height(p))width(temp_ptr)= width(temp_ptr)-height(p);
else width(temp_ptr)= 0;
link(q)= p;link(contrib_head)= q;goto resume;
}

/*:1026*/
#line 19457 "btex.w"

else/*1027:*/
#line 19483 "btex.w"

{page_total= page_total+page_depth+height(p);
page_depth= depth(p);
goto contribute;
}

/*:1027*/
#line 19458 "btex.w"
break;
case whatsit_node:/*1392:*/
#line 24758 "btex.w"

goto contribute

/*:1392*/
#line 19459 "btex.w"
;
case glue_node:if(page_contents<box_there)goto done1;
else if(precedes_break(page_tail))pi= 0;
else goto update_heights;break;
case kern_node:if(page_contents<box_there)goto done1;
#line 1690 "htex.ch"
else if(link(p)==null)return false;
#line 19465 "btex.w"
else if(type(link(p))==glue_node)pi= 0;
else goto update_heights;break;
case penalty_node:if(page_contents<box_there)goto done1;else pi= penalty(p);break;
case mark_node:goto contribute;
#line 1696 "htex.ch"
case ins_node:happend_insertion(p);goto contribute;
#line 19470 "btex.w"
default:confusion("page");

}

/*:1025*/
#line 19429 "btex.w"
;
/*1030:*/
#line 19517 "btex.w"

if(pi<inf_penalty)
{/*1032:*/
#line 19561 "btex.w"

if(page_total<page_goal)
if((page_so_far[3]!=0)||(page_so_far[4]!=0)||
(page_so_far[5]!=0))b= 0;
else b= badness(page_goal-page_total,page_so_far[2]);
else if(page_total-page_goal> page_shrink)b= awful_bad;
else b= badness(page_total-page_goal,page_shrink)

#line 1753 "htex.ch"
/*:1032*/
#line 19520 "btex.w"
;
if(b<awful_bad)
if(pi<=eject_penalty)c= pi;
else if(b<inf_bad)c= b+pi+insert_penalties;
else c= deplorable;
else c= b;
if(insert_penalties>=10000)c= awful_bad;
#line 19530 "btex.w"

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
#line 1741 "htex.ch"
{hloc_set_next(best_page_break);
if(p==best_page_break)best_page_break= null;
hpack_page();
hfill_page_template();
return true;
}
#line 19545 "btex.w"
}

/*:1030*/
#line 19432 "btex.w"
;
if((type(p)<glue_node)||(type(p)> kern_node))goto contribute;
update_heights:/*1029:*/
#line 19496 "btex.w"

if(type(p)==kern_node)q= p;
else{q= glue_ptr(p);
page_so_far[2+stretch_order(q)]= 
page_so_far[2+stretch_order(q)]+stretch(q);
page_shrink= page_shrink+shrink(q);
#line 1720 "htex.ch"
if((shrink_order(q)!=normal)&&(shrink(q)!=0))
{
DBG(DBGTEX,"Infinite glue shrinkage found on current page");
r= new_spec(q);shrink_order(r)= normal;fast_delete_glue_ref(q);
glue_ptr(p)= r;q= r;
}
#line 19514 "btex.w"
}
page_total= page_total+page_depth+width(q);page_depth= 0

/*:1029*/
#line 19435 "btex.w"
;
contribute:/*1028:*/
#line 19489 "btex.w"

if(page_depth> page_max_depth)
{page_total= 
page_total+page_depth-page_max_depth;
page_depth= page_max_depth;
}

/*:1028*/
#line 19436 "btex.w"
;
/*1023:*/
#line 19441 "btex.w"

link(page_tail)= p;page_tail= p;
link(contrib_head)= link(p);link(p)= null;goto done

/*:1023*/
#line 19437 "btex.w"
;
done1:/*1024:*/
#line 19445 "btex.w"

link(contrib_head)= link(p);link(p)= null;flush_node_list(p)

/*:1024*/
#line 19438 "btex.w"
;
done:

/*:1022*/
#line 19397 "btex.w"
;
}while(!(link(contrib_head)==null));
/*1020:*/
#line 19404 "btex.w"

if(nest_ptr==0)tail= contrib_head;
else contrib_tail= contrib_head

/*:1020*/
#line 19399 "btex.w"
;
#line 1683 "htex.ch"
return false;
}
#line 19401 "btex.w"

/*:1019*//*1033:*/
#line 1753 "htex.ch"

void happend_insertion(pointer p)
{uint8_t n;
scaled delta,h,w;
pointer q,r;
if(page_contents==empty)freeze_page_specs(inserts_only);
#line 19571 "btex.w"
n= subtype(p);r= page_ins_head;
while(n>=subtype(link(r)))r= link(r);
n= qo(n);
if(subtype(r)!=qi(n))
/*1034:*/
#line 19597 "btex.w"

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
#line 1777 "htex.ch"
if((shrink_order(q)!=normal)&&(shrink(q)!=0))
DBG(DBGTEX,"Infinite glue shrinkage inserted from stream %d",n);
#line 19618 "btex.w"
}

/*:1034*/
#line 19576 "btex.w"
;
if(type(r)==split_up)insert_penalties= insert_penalties+float_cost(p);
else{last_ins_ptr(r)= p;
delta= page_goal-page_total-page_depth+page_shrink;

if(count(n)==1000)h= height(p);
else h= x_over_n(height(p),1000)*count(n);
if(((h<=0)||(h<=delta))&&(height(p)+height(r)<=dimen(n)))
{page_goal= page_goal-h;height(r)= height(r)+height(p);
}
else/*1035:*/
#line 19630 "btex.w"

{if(count(n)<=0)w= max_dimen;
else{w= page_goal-page_total-page_depth;
if(count(n)!=1000)w= x_over_n(w,count(n))*1000;
}
if(w> dimen(n)-height(r))w= dimen(n)-height(r);
q= vert_break(ins_ptr(p),w,depth(p));
height(r)= height(r)+best_height_plus_depth;
#line 19641 "btex.w"

if(count(n)!=1000)
best_height_plus_depth= x_over_n(best_height_plus_depth,1000)*count(n);
page_goal= page_goal-best_height_plus_depth;
type(r)= split_up;broken_ptr(r)= q;broken_ins(r)= p;
if(q==null)insert_penalties= insert_penalties+eject_penalty;
else if(type(q)==penalty_node)insert_penalties= insert_penalties+penalty(q);
}

/*:1035*/
#line 19586 "btex.w"
;
}
#line 19589 "btex.w"
}

/*:1033*//*1040:*/
#line 1811 "htex.ch"

void hpack_page(void)
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
if(box(0)!=null)
{flush_node_list(box(0));box(0)= null;}
insert_penalties= 0;
save_split_top_skip= split_top_skip;
/*1044:*/
#line 19794 "btex.w"

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

/*:1044*/
#line 1831 "htex.ch"
;
q= hold_head;link(q)= null;prev_p= page_head;p= link(prev_p);
while(p!=best_page_break)
{if(type(p)==ins_node)
{/*1046:*/
#line 19820 "btex.w"

{r= link(page_ins_head);
while(subtype(r)!=subtype(p))r= link(r);
if(best_ins_ptr(r)==null)wait= true;
else{wait= false;s= last_ins_ptr(r);link(s)= ins_ptr(p);
if(best_ins_ptr(r)==p)
/*1047:*/
#line 19836 "btex.w"

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
#line 1869 "htex.ch"
while(link(s)!=null)s= link(s);
best_ins_ptr(r)= null;
#line 19850 "btex.w"
n= qo(subtype(r));
temp_ptr= list_ptr(box(n));
free_node(box(n),box_node_size);
#line 1876 "htex.ch"
streams[n].p= temp_ptr;
streams[n].t= s;
#line 19854 "btex.w"
}

/*:1047*/
#line 19827 "btex.w"

else{while(link(s)!=null)s= link(s);
last_ins_ptr(r)= s;
}
}
/*1048:*/
#line 19856 "btex.w"

link(prev_p)= link(p);link(p)= null;
if(wait)
{link(q)= p;q= p;incr(insert_penalties);
}
else{delete_glue_ref(split_top_ptr(p));
free_node(p,ins_node_size);
}
p= prev_p

/*:1048*/
#line 19833 "btex.w"
;
}

/*:1046*/
#line 1836 "htex.ch"
;
}
prev_p= p;p= link(prev_p);
}
split_top_skip= save_split_top_skip;
/*1043:*/
#line 19769 "btex.w"

if(p!=null)
{if(link(contrib_head)==null)
if(nest_ptr==0)tail= page_tail;
else contrib_tail= page_tail;
link(page_tail)= link(contrib_head);
link(contrib_head)= p;
link(prev_p)= null;
}
#line 1858 "htex.ch"
streams[0].p= link(page_head);link(page_head)= null;page_tail= page_head;
streams[0].t= prev_p;
if(q!=hold_head)
{link(q)= link(contrib_head);
link(contrib_head)= link(hold_head);
}
#line 19787 "btex.w"

/*:1043*/
#line 1842 "htex.ch"
;
/*1045:*/
#line 19808 "btex.w"

r= link(page_ins_head);
while(r!=page_ins_head)
{q= link(r);free_node(r,page_ins_node_size);r= q;
}
link(page_ins_head)= page_ins_head

/*:1045*/
#line 1843 "htex.ch"
;
}
#line 19739 "btex.w"

/*:1040*//*1172:*/
#line 1893 "htex.ch"

void hdisplay(pointer p,pointer a,bool l)
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
else{pointer par_ptr= link(head);
pop_nest();
store_map(par_ptr,node_pos,0);
line_break(display_widow_penalty,par_ptr);
x= cur_list.hs_field;
#line 21715 "btex.w"
/*1173:*/
#line 21730 "btex.w"

#line 1933 "htex.ch"
v= shift_amount(just_box)+2*dimen_def[quad_no];w= -max_dimen;
#line 21732 "btex.w"
p= list_ptr(just_box);
while(p!=null)
{/*1174:*/
#line 21747 "btex.w"

reswitch:if(is_char_node(p))
{f= font(p);d= char_width(f,char_info(f,character(p)));
goto found;
}
switch(type(p)){
case hlist_node:case vlist_node:case rule_node:{d= width(p);goto found;
}
case ligature_node:/*664:*/
#line 12955 "btex.w"

{mem[lig_trick]= mem[lig_char(p)];link(lig_trick)= link(p);
p= lig_trick;goto reswitch;
}

/*:664*/
#line 21755 "btex.w"

case kern_node:case math_node:d= width(p);break;
case glue_node:/*1175:*/
#line 21769 "btex.w"

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

/*:1175*/
#line 21758 "btex.w"
break;
case whatsit_node:/*1389:*/
#line 24747 "btex.w"
d= 0

#line 2491 "htex.ch"
/*:1389*/
#line 21759 "btex.w"
;break;
default:d= 0;
}

/*:1174*/
#line 21735 "btex.w"
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

/*:1173*/
#line 21717 "btex.w"
;
}

/*1176:*/
#line 21787 "btex.w"

if(par_shape_ptr==null)
if((hang_indent!=0)&&
(((hang_after>=0)&&(prev_graf+2> hang_after))||
(prev_graf+1<-hang_after)))
#line 1939 "htex.ch"
{l= x-abs(hang_indent);
#line 21793 "btex.w"
if(hang_indent> 0)s= hang_indent;else s= 0;
}
#line 1945 "htex.ch"
else{l= x;s= 0;
#line 21796 "btex.w"
}
else{n= info(par_shape_ptr);
if(prev_graf+2>=n)p= par_shape_ptr+2*n;
else p= par_shape_ptr+2*(prev_graf+2);
s= mem[p-1].sc;l= mem[p].sc;
}

/*:1176*/
#line 21720 "btex.w"
;
#line 1927 "htex.ch"
pre_display_size= w;display_width= l;display_indent= s;
#line 21728 "btex.w"
}

/*:1172*//*1227:*/
#line 1957 "htex.ch"

{/*1225:*/
#line 22436 "btex.w"

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

/*:1225*/
#line 1958 "htex.ch"

adjust_tail= adjust_head;b= hpack(p,natural);p= list_ptr(b);
t= adjust_tail;adjust_tail= null;
w= width(b);z= display_width;s= display_indent;
#line 1967 "htex.ch"
if(a==null)
#line 22459 "btex.w"
{e= 0;q= 0;
}
#line 1973 "htex.ch"
else{e= width(a);q= e+math_quad;
#line 22462 "btex.w"
}
if(w+q> z)
/*1229:*/
#line 22488 "btex.w"

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

/*:1229*/
#line 22465 "btex.w"
;
/*1230:*/
#line 22512 "btex.w"

d= half(z-w);
if((e> 0)&&(d<2*e))
{d= half(z-w-e);
if(p!=null)if(!is_char_node(p))if(type(p)==glue_node)d= 0;
}

/*:1230*/
#line 22467 "btex.w"
;
/*1231:*/
#line 22525 "btex.w"

#line 2000 "htex.ch"
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
#line 22538 "btex.w"

/*:1231*/
#line 22468 "btex.w"
;
/*1232:*/
#line 22539 "btex.w"

if(e!=0)
{r= new_kern(z-w-e-d);
if(l)
{link(a)= r;link(r)= b;b= a;d= 0;
}
else{link(b)= r;link(r)= a;
}
b= hpack(b,natural);
}
#line 2018 "htex.ch"
shift_amount(b)= s+d;append_to_vlist(b,offset)
#line 22550 "btex.w"

/*:1232*/
#line 22469 "btex.w"
;
/*1233:*/
#line 22551 "btex.w"

if((a!=null)&&(e==0)&&!l)
{tail_append(new_penalty(inf_penalty));
shift_amount(a)= s+z-width(a);
#line 2024 "htex.ch"
append_to_vlist(a,offset);
#line 22556 "btex.w"
g2= 0;
}
if(t!=adjust_head)
{link(tail)= link(adjust_head);tail= t;
}
#line 2031 "htex.ch"
tail_append(new_penalty(post_display_penalty));
offset= (hpos-hstart)+1-node_pos;
store_map(tail,node_pos,offset);
if(g2> 0){tail_append(new_glue(pointer_def[glue_kind][g2]));store_map(tail,node_pos,offset);}
#line 22563 "btex.w"

/*:1233*/
#line 22470 "btex.w"
;
#line 1979 "htex.ch"
prev_graf= prev_graf+3;
cur_list.bs_pos= hpos+node_pos;
push_nest();mode= hmode;
}
}
#line 22472 "btex.w"

/*:1227*/
