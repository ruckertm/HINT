/*219:*/
#line 3231 ".\\hint.w"

#include <string.h> 
#include "htex.h"
#include "hformat.h"
#include "hdefaults.h"
#include "texdef.h"

scaled page_max_height;

bool hbuild_page_up(void)
{
static scaled page_height;
static scaled top_so_far[8];
pointer p;
pointer q;
int b,c;
int pi;


if(link(contrib_head)==null)return false;
do{p= link(contrib_head);
/*226:*/
#line 3370 ".\\hint.w"

switch(type(p)){
case hlist_node:case vlist_node:case rule_node:
/*221:*/
#line 3306 ".\\hint.w"

if(page_contents==empty)
{/*222:*/
#line 3328 ".\\hint.w"

memset(page_so_far,0,sizeof(page_so_far));
memset(top_so_far,0,sizeof(top_so_far));
page_goal= hvsize;
page_max_depth= max_depth;
page_height= 0;
least_page_cost= awful_bad;
/*:222*/
#line 3308 ".\\hint.w"

if(depth(p)> page_max_depth)
page_total= depth(p)-page_max_depth;
depth(p)= 0;
}
if(page_contents<box_there)
/*223:*/
#line 3338 ".\\hint.w"

{page_max_height= width(pointer_def[glue_kind][top_skip_no]);
page_total= page_total+page_max_height;
}
/*:223*/
#line 3314 ".\\hint.w"

page_contents= box_there;
/*224:*/
#line 3344 ".\\hint.w"

{int i;
for(i= 1;i<=6;i++)
{page_so_far[i]+= top_so_far[i];
top_so_far[i]= 0;
}
}
/*:224*/
#line 3316 ".\\hint.w"

page_total+= page_height+depth(p);
if(height(p)> page_max_height)
{page_total= page_total+height(p)-page_max_height;
page_height= page_max_height;
}
else
page_height= height(p);
/*:221*/
#line 3373 ".\\hint.w"
goto contribute;
case whatsit_node:goto contribute;
case glue_node:/*229:*/
#line 3410 ".\\hint.w"

if(link(p)==null)return false;
if(page_contents==empty)
{/*222:*/
#line 3328 ".\\hint.w"

memset(page_so_far,0,sizeof(page_so_far));
memset(top_so_far,0,sizeof(top_so_far));
page_goal= hvsize;
page_max_depth= max_depth;
page_height= 0;
least_page_cost= awful_bad;
/*:222*/
#line 3413 ".\\hint.w"

page_contents= inserts_only;
}
/*230:*/
#line 3421 ".\\hint.w"

#define top_shrink top_so_far[6]
#define top_total top_so_far[1]

{pointer q= glue_ptr(p);
top_so_far[2+stretch_order(q)]+= stretch(q);
top_shrink+= shrink(q);
if((shrink_order(q)!=normal)&&(shrink(q)!=0))
MESSAGE("Infinite glue shrinkage found on current page");
top_total+= width(q);
}
/*:230*/
#line 3416 ".\\hint.w"

if(!precedes_break(link(p)))goto contribute;
pi= 0;
/*:229*/
#line 3375 ".\\hint.w"
break;
case kern_node:/*231:*/
#line 3437 ".\\hint.w"

if(page_contents==empty)
{/*222:*/
#line 3328 ".\\hint.w"

memset(page_so_far,0,sizeof(page_so_far));
memset(top_so_far,0,sizeof(top_so_far));
page_goal= hvsize;
page_max_depth= max_depth;
page_height= 0;
least_page_cost= awful_bad;
/*:222*/
#line 3439 ".\\hint.w"

page_contents= inserts_only;
}
top_total+= width(p);
if(page_contents<box_there)goto done1;
else if(link(page_head)==null)return false;
else if(type(link(page_head))!=glue_node)
goto contribute;
pi= 0;
/*:231*/
#line 3376 ".\\hint.w"
break;

case penalty_node:if(page_contents==empty)goto done1;else pi= penalty(p);break;
case mark_node:goto contribute;
case ins_node:/*232:*/
#line 3451 ".\\hint.w"

QUIT("Prepending insertions not yet implemented\n");
/*:232*/
#line 3380 ".\\hint.w"

default:MESSAGE("Unexpected node type %d in build_page_up ignored\n",type(p));
}
if(pi<inf_penalty)
/*235:*/
#line 3480 ".\\hint.w"

{/*233:*/
#line 3460 ".\\hint.w"

/*234:*/
#line 3471 ".\\hint.w"

if(page_total<page_goal)
{if((page_so_far[3]!=0)||(page_so_far[4]!=0)||(page_so_far[5]!=0))b= 0;
else b= badness(page_goal-page_total,page_so_far[2]);
}
else if(page_total-page_goal> page_shrink)b= awful_bad;
else b= badness(page_total-page_goal,page_shrink)
/*:234*/
#line 3461 ".\\hint.w"
;
if(b<awful_bad)
{if(pi<=eject_penalty)c= pi;
else if(b<inf_bad)c= b+pi+insert_penalties;
else c= deplorable;
}
else c= b;
if(insert_penalties>=10000)c= awful_bad;
/*:233*/
#line 3481 ".\\hint.w"

if(c<=least_page_cost)
{best_page_break= p;best_size= page_goal;
least_page_cost= c;
#if 0
r= link(page_ins_head);
while(r!=page_ins_head)
{best_ins_ptr(r)= last_ins_ptr(r);
r= link(r);
}
#endif
}
if((c==awful_bad)||(pi<=eject_penalty))
{/*236:*/
#line 3501 ".\\hint.w"

while(true){
q= link(page_head);
if(q==null)return false;
else if(type(q)==penalty_node||type(q)==glue_node||type(q)==kern_node)
{link(page_head)= link(q);link(q)= null;flush_node_list(q);}
else break;
}
temp_ptr= new_spec(pointer_def[glue_kind][top_skip_no]);
q= new_glue(temp_ptr);glue_ref_count(temp_ptr)= null;
if(width(temp_ptr)> page_height)width(temp_ptr)= width(temp_ptr)-page_height;
else width(temp_ptr)= 0;
link(q)= link(page_head);
link(page_head)= q;
/*:236*/
#line 3494 ".\\hint.w"

/*237:*/
#line 3517 ".\\hint.w"

if(box(0)!=null)QUIT("Box 0 must be empty");
box(0)= vpackage(link(page_head),best_size,exactly,0x100000);
/*238:*/
#line 3524 ".\\hint.w"

/*:238*/
#line 3520 ".\\hint.w"

/*:237*/
#line 3495 ".\\hint.w"

return true;
}
}
/*:235*/
#line 3384 ".\\hint.w"

contribute:
/*227:*/
#line 3391 ".\\hint.w"

link(contrib_head)= link(p);
link(p)= link(page_head);
link(page_head)= p;
goto done;
/*:227*/
#line 3386 ".\\hint.w"

done1:/*228:*/
#line 3398 ".\\hint.w"

link(contrib_head)= link(p);link(p)= null;flush_node_list(p);
/*:228*/
#line 3387 ".\\hint.w"

done:
/*:226*/
#line 3252 ".\\hint.w"
;
}while(!(link(contrib_head)==null));
tail= contrib_head;
return false;
}
/*:219*/
