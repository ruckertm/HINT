/*1179:*/
#line 21729 ".\\dummy.w"

#include "htex.h"
#include "hformat.h"
#include "hdefaults.h"
#include "hpos.h"
#include "texdef.h"

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
else{line_break(display_widow_penalty);
x= cur_list.hs_field;
/*1180:*/
#line 21763 ".\\dummy.w"

v= shift_amount(just_box)+2*dimen_def[quad_no];w= -max_dimen;
p= list_ptr(just_box);
while(p!=null)
{/*1181:*/
#line 21780 ".\\dummy.w"

reswitch:if(is_char_node(p))
{f= font(p);d= char_width(f)(char_info(f)(character(p)));
goto found;
}
switch(type(p)){
case hlist_node:case vlist_node:case rule_node:{d= width(p);goto found;
}
case ligature_node:/*670:*/
#line 13000 ".\\dummy.w"

{mem[lig_trick]= mem[lig_char(p)];link(lig_trick)= link(p);
p= lig_trick;goto reswitch;
}

/*:670*/
#line 21788 ".\\dummy.w"

case kern_node:case math_node:d= width(p);break;
case glue_node:/*1182:*/
#line 21802 ".\\dummy.w"

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

/*:1182*/
#line 21791 ".\\dummy.w"
break;
case whatsit_node:/*1396:*/
#line 25015 ".\\dummy.w"
d= 0

/*:1396*/
#line 21792 ".\\dummy.w"
;break;
default:d= 0;
}

/*:1181*/
#line 21768 ".\\dummy.w"
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

/*:1180*/
#line 21756 ".\\dummy.w"
;
}

/*1183:*/
#line 21820 ".\\dummy.w"

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

/*:1183*/
#line 21759 ".\\dummy.w"
;
pre_display_size= w;display_width= l;display_indent= s;
}

/*:1179*//*1234:*/
#line 22486 ".\\dummy.w"

{/*1232:*/
#line 22469 ".\\dummy.w"

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

/*:1232*/
#line 22487 ".\\dummy.w"

adjust_tail= adjust_head;b= hpack(p,natural);p= list_ptr(b);
t= adjust_tail;adjust_tail= null;
w= width(b);z= display_width;s= display_indent;
if(a==null)
{e= 0;q= 0;
}
else{e= width(a);q= e+math_quad;
}
if(w+q> z)
/*1236:*/
#line 22525 ".\\dummy.w"

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

/*:1236*/
#line 22498 ".\\dummy.w"
;
/*1237:*/
#line 22549 ".\\dummy.w"

d= half(z-w);
if((e> 0)&&(d<2*e))
{d= half(z-w-e);
if(p!=null)if(!is_char_node(p))if(type(p)==glue_node)d= 0;
}

/*:1237*/
#line 22500 ".\\dummy.w"
;
/*1238:*/
#line 22562 ".\\dummy.w"

tail_append(new_penalty(pre_display_penalty));
store_map(tail,node_pos,offset,0);
if((d+s<=pre_display_size)||l)
{g1= above_display_skip_no;g2= below_display_skip_no;
}
else{g1= above_display_short_skip_no;
g2= below_display_short_skip_no;
}
if(l&&(e==0))
{shift_amount(a)= s;append_to_vlist(a,offset);
tail_append(new_penalty(inf_penalty));store_map(tail,node_pos,offset,0);
}
else{tail_append(hget_param_glue(g1));store_map(tail,node_pos,offset,0);};

/*:1238*/
#line 22501 ".\\dummy.w"
;
/*1239:*/
#line 22577 ".\\dummy.w"

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

/*:1239*/
#line 22502 ".\\dummy.w"
;
/*1240:*/
#line 22589 ".\\dummy.w"

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
store_map(tail,node_pos,offset,0);
if(g2> 0){tail_append(hget_param_glue(g2));store_map(tail,node_pos,offset,0);}

/*:1240*/
#line 22503 ".\\dummy.w"
;
prev_graf= prev_graf+3;
needs_bs= true;
push_nest();mode= hmode;
}
}

/*:1234*/
