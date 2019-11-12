/*996:*/
#line 18886 ".\\dummy.w"

#include "htex.h"
#include "hformat.h"
#include "hdefaults.h"
#include "texdef.h"
#include "hpos.h"


#define ensure_vbox(N)

/*662:*/
#line 12919 ".\\dummy.w"

scaled total_stretch0[filll-normal+1],*const total_stretch= total_stretch0-normal,total_shrink0[filll-normal+1],*const total_shrink= total_shrink0-normal;

int last_badness;

/*:662*//*1000:*/
#line 18981 ".\\dummy.w"

scaled best_height_plus_depth;


/*:1000*//*1010:*/
#line 19184 ".\\dummy.w"

pointer page_tail;
uint8_t page_contents;
scaled page_max_depth;
pointer best_page_break;
int least_page_cost;
scaled best_size;

/*:1010*//*1013:*/
#line 19267 ".\\dummy.w"

scaled page_so_far[8];
int insert_penalties;

/*:1013*/
#line 18896 ".\\dummy.w"

bool output_active= false;
int holding_inserts= 0;

extern void freeze_page_specs(small_number s);
extern pointer vert_break(pointer p,scaled h,scaled d);
extern void hship_out(pointer p);


stream_t stream[256]= {{0}};

extern scaled hvsize;

pointer prune_page_top(pointer p)
{pointer prev_p;
pointer q;
prev_p= temp_head;link(temp_head)= p;
while(p!=null)
switch(type(p)){
case hlist_node:case vlist_node:case rule_node:/*997:*/
#line 18928 ".\\dummy.w"

{temp_ptr= new_spec(pointer_def[glue_kind][split_top_skip_no]);
q= new_glue(temp_ptr);glue_ref_count(temp_ptr)= null;link(prev_p)= q;link(q)= p;

if(width(temp_ptr)> height(p))width(temp_ptr)= width(temp_ptr)-height(p);
else width(temp_ptr)= 0;
p= null;
}

/*:997*/
#line 18916 ".\\dummy.w"
break;
case whatsit_node:case mark_node:case ins_node:{prev_p= p;p= link(prev_p);
}break;
case glue_node:case kern_node:case penalty_node:{q= p;p= link(q);link(q)= null;
link(prev_p)= p;flush_node_list(q);
}break;
default:QUIT("Confusion in prune page top");

}
return link(temp_head);
}

/*:996*//*998:*/
#line 18953 ".\\dummy.w"

pointer vert_break(pointer p,scaled h,scaled d)

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
loop{/*1001:*/
#line 18989 ".\\dummy.w"

if(p==null)pi= eject_penalty;
else/*1002:*/
#line 19004 ".\\dummy.w"

switch(type(p)){
case hlist_node:case vlist_node:case rule_node:{
cur_height= cur_height+prev_dp+height(p);prev_dp= depth(p);
goto not_found;
}
case whatsit_node:/*1400:*/
#line 25028 ".\\dummy.w"

goto not_found

/*:1400*/
#line 19010 ".\\dummy.w"
;
case glue_node:if(precedes_break(prev_p))pi= 0;
else goto update_heights;break;
case kern_node:{if(link(p)==null)t= penalty_node;
else t= type(link(p));
if(t==glue_node)pi= 0;else goto update_heights;
}break;
case penalty_node:pi= penalty(p);break;
case mark_node:case ins_node:goto not_found;
default:QUIT("Confusion in vert_break");

}

/*:1002*/
#line 18993 ".\\dummy.w"
;
/*1003:*/
#line 19025 ".\\dummy.w"

if(pi<inf_penalty)
{/*1004:*/
#line 19039 ".\\dummy.w"

if(cur_height<h)
if((active_height[3]!=0)||(active_height[4]!=0)||
(active_height[5]!=0))b= 0;
else b= badness(h-cur_height,active_height[2]);
else if(cur_height-h> active_height[6])b= awful_bad;
else b= badness(cur_height-h,active_height[6])

/*:1004*/
#line 19027 ".\\dummy.w"
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

/*:1003*/
#line 18995 ".\\dummy.w"
;
if((type(p)<glue_node)||(type(p)> kern_node))goto not_found;
update_heights:/*1005:*/
#line 19051 ".\\dummy.w"

if(type(p)==kern_node)q= p;
else{q= glue_ptr(p);
active_height[2+stretch_order(q)]= 
active_height[2+stretch_order(q)]+stretch(q);
active_height[6]= active_height[6]+shrink(q);
if((shrink_order(q)!=normal)&&(shrink(q)!=0))
{
MESSAGE("Infinite glue shrinkage found in box being split");
r= new_spec(q);shrink_order(r)= normal;delete_glue_ref(q);
glue_ptr(p)= r;q= r;
}
}
cur_height= cur_height+prev_dp+width(q);prev_dp= 0

/*:1005*/
#line 18998 ".\\dummy.w"
;
not_found:if(prev_dp> d)
{cur_height= cur_height+prev_dp-d;
prev_dp= d;
}

/*:1001*/
#line 18970 ".\\dummy.w"
;
prev_p= p;p= link(prev_p);
}
done:return best_place;
}

/*:998*//*1018:*/
#line 19351 ".\\dummy.w"

void freeze_page_specs(small_number s)
{page_contents= s;
page_goal= hvsize;page_max_depth= max_depth;
page_depth= 0;do_all_six(set_page_so_far_zero);
least_page_cost= awful_bad;

}

/*:1018*//*1026:*/
#line 19440 ".\\dummy.w"

/*1044:*/
#line 19717 ".\\dummy.w"

void fire_up(pointer c)
{
pointer p,q,r,s;
pointer prev_p;
uint8_t n;
bool wait;
pointer save_split_top_skip;
hpos_set_next(best_page_break);
/*1046:*/
#line 19744 ".\\dummy.w"

if(c==best_page_break)best_page_break= null;
if(box(0)!=null)QUIT("Box 0 must be empty");
insert_penalties= 0;
save_split_top_skip= split_top_skip;
if(holding_inserts<=0)
/*1050:*/
#line 19815 ".\\dummy.w"

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

/*:1050*/
#line 19750 ".\\dummy.w"
;
q= hold_head;link(q)= null;prev_p= page_head;p= link(prev_p);
while(p!=best_page_break)
{if(type(p)==ins_node)
{if(holding_inserts<=0)
/*1052:*/
#line 19841 ".\\dummy.w"

{r= link(page_ins_head);
while(subtype(r)!=subtype(p))r= link(r);
if(best_ins_ptr(r)==null)wait= true;
else{wait= false;s= last_ins_ptr(r);link(s)= ins_ptr(p);
if(best_ins_ptr(r)==p)
/*1053:*/
#line 19857 ".\\dummy.w"

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
best_ins_ptr(r)= null;
n= qo(subtype(r));
temp_ptr= list_ptr(box(n));
free_node(box(n),box_node_size);
box(n)= vpack(temp_ptr,natural);
}

/*:1053*/
#line 19848 ".\\dummy.w"

else{while(link(s)!=null)s= link(s);
last_ins_ptr(r)= s;
}
}
/*1054:*/
#line 19877 ".\\dummy.w"

link(prev_p)= link(p);link(p)= null;
if(wait)
{link(q)= p;q= p;incr(insert_penalties);
}
else{delete_glue_ref(split_top_ptr(p));
free_node(p,ins_node_size);
}
p= prev_p

/*:1054*/
#line 19854 ".\\dummy.w"
;
}

/*:1052*/
#line 19756 ".\\dummy.w"
;
}
prev_p= p;p= link(prev_p);
}
split_top_skip= save_split_top_skip;
/*1049:*/
#line 19794 ".\\dummy.w"

if(p!=null)
{if(link(contrib_head)==null)
if(nest_ptr==0)tail= page_tail;
else contrib_tail= page_tail;
link(page_tail)= link(contrib_head);
link(contrib_head)= p;
link(prev_p)= null;
}
box(0)= vpackage(link(page_head),best_size,exactly,0x100000);
/*1022:*/
#line 19400 ".\\dummy.w"

page_contents= empty;page_tail= page_head;link(page_head)= null;
page_depth= 0;page_max_depth= 0

/*:1022*/
#line 19804 ".\\dummy.w"
;
if(q!=hold_head)
{link(page_head)= link(hold_head);page_tail= q;
}

/*:1049*/
#line 19762 ".\\dummy.w"
;
/*1051:*/
#line 19829 ".\\dummy.w"

r= link(page_ins_head);
while(r!=page_ins_head)
{q= link(r);free_node(r,page_ins_node_size);r= q;
}
link(page_ins_head)= page_ins_head

/*:1051*/
#line 19763 ".\\dummy.w"


/*:1046*/
#line 19728 ".\\dummy.w"
;
/*1055:*/
#line 19891 ".\\dummy.w"

{if(link(page_head)!=null)
{if(link(contrib_head)==null)
if(nest_ptr==0)tail= page_tail;else contrib_tail= page_tail;
else link(page_tail)= link(contrib_head);
link(contrib_head)= link(page_head);
link(page_head)= null;page_tail= page_head;
}
}

/*:1055*/
#line 19729 ".\\dummy.w"
;
}

/*:1044*/
#line 19441 ".\\dummy.w"

bool hbuild_page(void)
{
pointer p;
pointer q,r;
int b,c;
int pi;
uint8_t n;
scaled delta,h,w;
if((link(contrib_head)==null)||output_active)return false;
do{resume:p= link(contrib_head);
/*1029:*/
#line 19483 ".\\dummy.w"

/*1032:*/
#line 19511 ".\\dummy.w"

switch(type(p)){
case hlist_node:case vlist_node:case rule_node:if(page_contents<box_there)
/*1033:*/
#line 19531 ".\\dummy.w"

{if(page_contents==empty)freeze_page_specs(box_there);
else page_contents= box_there;
temp_ptr= new_spec(pointer_def[glue_kind][top_skip_no]);
q= new_glue(temp_ptr);glue_ref_count(temp_ptr)= null;
if(width(temp_ptr)> height(p))width(temp_ptr)= width(temp_ptr)-height(p);
else width(temp_ptr)= 0;
link(q)= p;link(contrib_head)= q;goto resume;
}

/*:1033*/
#line 19515 ".\\dummy.w"

else/*1034:*/
#line 19541 ".\\dummy.w"

{page_total= page_total+page_depth+height(p);
page_depth= depth(p);
goto contribute;
}

/*:1034*/
#line 19516 ".\\dummy.w"
break;
case whatsit_node:/*1399:*/
#line 25025 ".\\dummy.w"

goto contribute

/*:1399*/
#line 19517 ".\\dummy.w"
;
case glue_node:if(page_contents<box_there)goto done1;
else if(precedes_break(page_tail))pi= 0;
else goto update_heights;break;
case kern_node:if(page_contents<box_there)goto done1;
else if(link(p)==null)return false;
else if(type(link(p))==glue_node)pi= 0;
else goto update_heights;break;
case penalty_node:if(page_contents<box_there)goto done1;else pi= penalty(p);break;
case mark_node:goto contribute;
case ins_node:/*1040:*/
#line 19619 ".\\dummy.w"

{if(page_contents==empty)freeze_page_specs(inserts_only);
n= subtype(p);r= page_ins_head;
while(n>=subtype(link(r)))r= link(r);
n= qo(n);
if(subtype(r)!=qi(n))
/*1041:*/
#line 19647 ".\\dummy.w"

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
MESSAGE("Infinite glue shrinkage inserted from stream %d",n);
}

/*:1041*/
#line 19626 ".\\dummy.w"
;
if(type(r)==split_up)insert_penalties= insert_penalties+float_cost(p);
else{last_ins_ptr(r)= p;
delta= page_goal-page_total-page_depth+page_shrink;

if(count(n)==1000)h= height(p);
else h= x_over_n(height(p),1000)*count(n);
if(((h<=0)||(h<=delta))&&(height(p)+height(r)<=dimen(n)))
{page_goal= page_goal-h;height(r)= height(r)+height(p);
}
else/*1042:*/
#line 19673 ".\\dummy.w"

{if(count(n)<=0)w= max_dimen;
else{w= page_goal-page_total-page_depth;
if(count(n)!=1000)w= x_over_n(w,count(n))*1000;
}
if(w> dimen(n)-height(r))w= dimen(n)-height(r);
q= vert_break(ins_ptr(p),w,depth(p));
height(r)= height(r)+best_height_plus_depth;

if(count(n)!=1000)
best_height_plus_depth= x_over_n(best_height_plus_depth,1000)*count(n);
page_goal= page_goal-best_height_plus_depth;
type(r)= split_up;broken_ptr(r)= q;broken_ins(r)= p;
if(q==null)insert_penalties= insert_penalties+eject_penalty;
else if(type(q)==penalty_node)insert_penalties= insert_penalties+penalty(q);
}

/*:1042*/
#line 19636 ".\\dummy.w"
;
}
goto contribute;
}

/*:1040*/
#line 19527 ".\\dummy.w"

default:QUIT("This cant happen in build page");
}

/*:1032*/
#line 19487 ".\\dummy.w"
;
/*1037:*/
#line 19569 ".\\dummy.w"

if(pi<inf_penalty)
{/*1039:*/
#line 19611 ".\\dummy.w"

if(page_total<page_goal)
if((page_so_far[3]!=0)||(page_so_far[4]!=0)||
(page_so_far[5]!=0))b= 0;
else b= badness(page_goal-page_total,page_so_far[2]);
else if(page_total-page_goal> page_shrink)b= awful_bad;
else b= badness(page_total-page_goal,page_shrink)

/*:1039*/
#line 19572 ".\\dummy.w"
;
if(b<awful_bad)
if(pi<=eject_penalty)c= pi;
else if(b<inf_bad)c= b+pi+insert_penalties;
else c= deplorable;
else c= b;
if(insert_penalties>=10000)c= awful_bad;


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
return true;
goto done;
}
}

/*:1037*/
#line 19490 ".\\dummy.w"
;
if((type(p)<glue_node)||(type(p)> kern_node))goto contribute;
update_heights:/*1036:*/
#line 19554 ".\\dummy.w"

if(type(p)==kern_node)q= p;
else{q= glue_ptr(p);
page_so_far[2+stretch_order(q)]= 
page_so_far[2+stretch_order(q)]+stretch(q);
page_shrink= page_shrink+shrink(q);
if((shrink_order(q)!=normal)&&(shrink(q)!=0))
{
MESSAGE("Infinite glue shrinkage found on current page");
r= new_spec(q);shrink_order(r)= normal;fast_delete_glue_ref(q);
glue_ptr(p)= r;q= r;
}
}
page_total= page_total+page_depth+width(q);page_depth= 0

/*:1036*/
#line 19493 ".\\dummy.w"
;
contribute:/*1035:*/
#line 19547 ".\\dummy.w"

if(page_depth> page_max_depth)
{page_total= 
page_total+page_depth-page_max_depth;
page_depth= page_max_depth;
}

/*:1035*/
#line 19494 ".\\dummy.w"
;
/*1030:*/
#line 19499 ".\\dummy.w"

link(page_tail)= p;page_tail= p;
link(contrib_head)= link(p);link(p)= null;goto done

/*:1030*/
#line 19495 ".\\dummy.w"
;
done1:/*1031:*/
#line 19503 ".\\dummy.w"

link(contrib_head)= link(p);link(p)= null;flush_node_list(p)

/*:1031*/
#line 19496 ".\\dummy.w"
;
done:

/*:1029*/
#line 19454 ".\\dummy.w"
;
}while(!(link(contrib_head)==null));
/*1027:*/
#line 19462 ".\\dummy.w"

if(nest_ptr==0)tail= contrib_head;
else contrib_tail= contrib_head

/*:1027*/
#line 19456 ".\\dummy.w"
;
return false;
}

/*:1026*//*1087:*/
#line 20464 ".\\dummy.w"

bool hits_all_over(void)
{
if((link(page_head)==null)&&(head==tail))return true;
tail_append(new_null_box());
width(tail)= hhsize;
tail_append(hget_param_glue(fill_skip_no));
store_map(tail,0xffffffff,0,0);
tail_append(new_penalty(-010000000000));
store_map(tail,0xffffffff,0,0);
return false;
}

/*:1087*/
