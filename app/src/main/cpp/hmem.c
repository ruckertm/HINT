/*119:*/
#line 2540 ".\\dummy.w"

#include "htex.h"
#include "texdef.h"

/*120:*/
#line 2568 ".\\dummy.w"

pointer temp_ptr;

/*:120*//*121:*/
#line 2600 ".\\dummy.w"

memory_word mem0[mem_max-mem_min+1],*const mem= mem0-mem_min;
pointer lo_mem_max;
pointer hi_mem_min;

/*:121*//*123:*/
#line 2614 ".\\dummy.w"

int var_used,dyn_used;
#ifdef DEBUG
#define incr_dyn_used incr(dyn_used)
#define decr_dyn_used decr(dyn_used)
#else
#define incr_dyn_used
#define decr_dyn_used
#endif

/*:123*//*124:*/
#line 2637 ".\\dummy.w"

pointer avail;
pointer mem_end;

/*:124*//*130:*/
#line 2736 ".\\dummy.w"

pointer rover;

/*:130*/
#line 2544 ".\\dummy.w"

void print_word(memory_word w)

{MESSAGE("0x%08X, %d, %f\n",w.i,w.i,w.gr);
}

/*:119*//*126:*/
#line 2657 ".\\dummy.w"
pointer get_avail(void)
{pointer p;
p= avail;
if(p!=null)avail= link(avail);
else if(mem_end<mem_max)
{incr(mem_end);p= mem_end;
}
else{decr(hi_mem_min);p= hi_mem_min;
if(hi_mem_min<=lo_mem_max)
{QUIT("Memory overflow 0x%X",mem_max+1-mem_min);


}
}
link(p)= null;
incr_dyn_used;
return p;
}

/*:126*//*129:*/
#line 2702 ".\\dummy.w"
void flush_list(pointer p)

{pointer q,r;
if(p!=null)
{r= p;
do{q= r;r= link(r);
decr_dyn_used;
}while(!(r==null));
link(q)= avail;avail= p;
}
}

/*:129*//*131:*/
#line 2747 ".\\dummy.w"
pointer get_node(int s)
{
pointer p;
pointer q;
int r;
int t;
restart:p= rover;
do{/*133:*/
#line 2797 ".\\dummy.w"

q= p+node_size(p);

while(is_empty(q))
{t= rlink(q);
if(q==rover)rover= t;
llink(t)= llink(q);rlink(llink(q))= t;
q= q+node_size(q);
}
r= q-s;
if(r> p+1)/*134:*/
#line 2812 ".\\dummy.w"

{node_size(p)= r-p;

rover= p;
goto found;
}

/*:134*/
#line 2807 ".\\dummy.w"
;
if(r==p)if(rlink(p)!=p)
/*135:*/
#line 2821 ".\\dummy.w"

{rover= rlink(p);t= llink(p);
llink(rover)= t;rlink(t)= rover;
goto found;
}

/*:135*/
#line 2809 ".\\dummy.w"
;
node_size(p)= q-p

/*:133*/
#line 2755 ".\\dummy.w"
;

p= rlink(p);
}while(!(p==rover));
if(s==010000000000)
{return max_halfword;
}
if(lo_mem_max+2<hi_mem_min)if(lo_mem_max+2<=mem_bot+max_halfword)
/*132:*/
#line 2782 ".\\dummy.w"

{if(hi_mem_min-lo_mem_max>=1998)t= lo_mem_max+1000;
else t= lo_mem_max+1+(hi_mem_min-lo_mem_max)/2;

p= llink(rover);q= lo_mem_max;rlink(p)= q;llink(rover)= q;
if(t> mem_bot+max_halfword)t= mem_bot+max_halfword;
rlink(q)= rover;llink(q)= p;link(q)= empty_flag;node_size(q)= t-lo_mem_max;
lo_mem_max= t;link(lo_mem_max)= null;info(lo_mem_max)= null;
rover= q;goto restart;
}

/*:132*/
#line 2763 ".\\dummy.w"
;
QUIT("Memory overflow 0x%X",mem_max+1-mem_min);


found:link(r)= null;
#ifdef STAT
var_used= var_used+s;
#endif

return r;
}

/*:131*//*136:*/
#line 2832 ".\\dummy.w"
void free_node(pointer p,halfword s)

{pointer q;
node_size(p)= s;link(p)= empty_flag;
q= llink(rover);llink(p)= q;rlink(p)= rover;
llink(rover)= p;rlink(q)= p;
#ifdef STAT
var_used= var_used-s;
#endif

}

/*:136*//*170:*/
#line 3410 ".\\dummy.w"

void hmem_init(void)
{int k;
/*171:*/
#line 3416 ".\\dummy.w"

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
/*808:*/
#line 15584 ".\\dummy.w"

info(omit_template)= end_template_token;

/*:808*//*815:*/
#line 15690 ".\\dummy.w"

link(end_span)= max_quarterword+1;info(end_span)= null;

/*:815*//*839:*/
#line 16158 ".\\dummy.w"

type(last_active)= hyphenated;line_number(last_active)= max_halfword;
subtype(last_active)= 0;

/*:839*//*1011:*/
#line 19237 ".\\dummy.w"

subtype(page_ins_head)= qi(255);
type(page_ins_head)= split_up;link(page_ins_head)= page_ins_head;

/*:1011*//*1019:*/
#line 19384 ".\\dummy.w"

type(page_head)= glue_node;subtype(page_head)= normal;

/*:1019*/
#line 3438 ".\\dummy.w"
;
avail= null;mem_end= mem_top;
hi_mem_min= hi_mem_stat_min;
var_used= lo_mem_stat_max+1-mem_bot;dyn_used= hi_mem_stat_usage;


/*:171*/
#line 3413 ".\\dummy.w"

}

/*:170*//*216:*/
#line 3978 ".\\dummy.w"

void flush_node_list(pointer p)
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
fast_delete_glue_ref(split_top_ptr(p));
free_node(p,ins_node_size);goto done;
}
case whatsit_node:goto done;
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

/*:216*/
