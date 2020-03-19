/*297:*/
#line 5677 ".\\hint.w"

#include <math.h> 
#include "texextern.h"
#include "hget.h"
#include "hint.h"
#include "hrender.h"
#include "rendernative.h"
#include "texdefs.h"

/*240:*/
#line 4103 ".\\hint.w"

typedef struct font_s*font_s_ptr;
extern struct font_s*hget_font(unsigned char f);
/*:240*//*251:*/
#line 4427 ".\\hint.w"

extern void render_char(int x,int y,struct font_s*f,int32_t s,uint32_t cc);
/*:251*/
#line 5686 ".\\hint.w"


/*225:*/
#line 3813 ".\\hint.w"

int page_v,page_h,offset_v,offset_h;
/*:225*//*230:*/
#line 3921 ".\\hint.w"

static bool forward_mode= false,backward_mode= false;
/*:230*/
#line 5688 ".\\hint.w"

/*226:*/
#line 3823 ".\\hint.w"

static void hset_margins(void)
{offset_h= page_h/8-0x48000;
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
/*:226*//*227:*/
#line 3841 ".\\hint.w"

static void houtput_template0(void)
{pointer p,q,t,b,l,r;
if(stream[0].p==null)return;

q= new_spec(zero_glue);width(q)= offset_h;
l= new_glue(q);glue_ref_count(q)= null;
r= new_glue(q);
q= new_spec(zero_glue);width(q)= offset_v;
t= new_glue(q);glue_ref_count(q)= null;
b= new_glue(q);

p= stream[0].p;
link(p)= r;
link(l)= p;
p= hpack(l,page_h,exactly);
link(p)= b;
link(t)= p;
p= vpackage(t,page_v,exactly,0);
stream[0].p= p;
}
/*:227*//*228:*/
#line 3875 ".\\hint.w"


uint64_t hint_page_top(uint64_t h)
{hclear_page();
if(hbase==NULL)return 0;
hloc_set(h);
hset_margins();
hpos= hstart+(h&0xffffffff);
if(hpos>=hend)
return hint_page_bottom(hend-hstart);
if(h> 0xffffffff)
hget_par_node(h>>32);
hint_forward();
forward_mode= true;
backward_mode= false;
houtput_template0();
return h;
}
/*:228*//*229:*/
#line 3899 ".\\hint.w"

uint64_t hint_page_get(void)
{
DBG(DBGPAGE,"page_get: %d : 0x%"PRIx64"\n",cur_loc,page_loc[cur_loc]);

return page_loc[cur_loc];
}

uint64_t hint_page(void)
{uint64_t i= hint_page_get();
if(stream[0].p!=null)
return i;
else
return hint_page_top(i);
}
/*:229*//*231:*/
#line 3926 ".\\hint.w"

uint64_t hint_next_page(void)
{if(hbase==NULL)return 0;
if(hloc_next()&&forward_mode)
{hset_margins();
if(!hint_forward())
{hloc_prev();return hint_page();}
forward_mode= true;
backward_mode= false;
houtput_template0();
return hint_page_get();
}
else
{hclear_page();
return hint_page();
}
}
/*:231*//*232:*/
#line 3953 ".\\hint.w"

uint64_t hint_prev_page(void)
{if(hbase==NULL)return 0;
if(hloc_prev())
{hclear_page();
return hint_page();
}
else if(backward_mode)
{hset_margins();
if(!hint_backward())return hint_page_top(0);
backward_mode= true;
forward_mode= false;
houtput_template0();
return hint_page_get();
}
else
return hint_page_bottom(hint_page_get());
}
/*:232*//*233:*/
#line 3980 ".\\hint.w"

uint64_t hint_page_bottom(uint64_t h)
{hclear_page();
if(hbase==NULL)return 0;
hset_margins();
hpos= hstart+(h&0xffffffff);
if(h> 0xffffffff)
hteg_par_node(h>>32);
if(!hint_backward())return hint_page();
backward_mode= true;
forward_mode= false;
houtput_template0();
return hint_page_get();
}
/*:233*//*234:*/
#line 3997 ".\\hint.w"

uint64_t hint_page_center(uint64_t h)
{if(hbase==NULL)return hint_blank();
QUIT("hint_page_center not yet implemented");
}
/*:234*//*235:*/
#line 4008 ".\\hint.w"

void hint_resize(int px_h,int px_v,double dpi)
{static int old_px_h= 0,old_px_v= 0;
static double old_dpi= 0.0;
nativeSetSize(px_h,px_v,dpi);
if(old_px_h==px_h&&old_px_v==px_v&&old_dpi==dpi)return;
old_px_h= px_h;old_px_v= px_v;old_dpi= dpi;
hloc_clear();
hclear_page();
forward_mode= false;
backward_mode= false;
}
/*:235*//*253:*/
#line 4441 ".\\hint.w"

static void render_rule(int x,int y,int w,int h)
{if(w<=0)return;
if(h<=0)return;
nativeRule(SP2PT(x),SP2PT(y),SP2PT(w),SP2PT(h));
}
/*:253*//*254:*/
#line 4453 ".\\hint.w"

void render_image(int x,int y,int w,int h,uint32_t n)
{
uint8_t*spos,*sstart,*send;
spos= hpos;sstart= hstart;send= hend;
hget_section(n);
nativeImage(SP2PT(x),SP2PT(y),SP2PT(w),SP2PT(h),hstart,hend);
hpos= spos;hstart= sstart;hend= send;
}
/*:254*//*255:*/
#line 4477 ".\\hint.w"

static scaled cur_h,cur_v;
static scaled rule_ht,rule_dp,rule_wd;
static int cur_f;
static struct font_s*cur_fp;
static int32_t cur_at_size;

static void vlist_render(pointer this_box);

static void hlist_render(pointer this_box)
{scaled base_line;
scaled left_edge;
scaled save_h;
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
base_line= cur_v;
left_edge= cur_h;

while(p!=null)
{reswitch:
#ifdef DEBUG
if(p==0xffff)
QUIT("Undefined pointer in hlist 0x%x\n",p);
if(link(p)==0xffff)
QUIT("Undefined link in hlist mem[0x%x]=0x%x\n",p,mem[p].i);
#endif
if(is_char_node(p))
{do{
uint8_t f= font(p);
uint32_t c= character(p);
if(f!=cur_f)
{
#ifdef DEBUG
if(f> max_ref[font_kind])
QUIT("Undefined Font %d mem[0x%x]=0x%x\n",
f,p,mem[p].i);
#endif
cur_fp= hget_font(f);
cur_f= f;
cur_at_size= font_at_size(f);
}
render_char(cur_h,cur_v,cur_fp,cur_at_size,c);
cur_h= cur_h+char_width(f)(char_info(f)(c));
#ifdef DEBUG
if(link(p)==0xffff)
QUIT("Undefined link in charlist mem[0x%x]=0x%x\n",p,mem[p].i);
#endif
p= link(p);
}while(!(!is_char_node(p)));
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
if(list_ptr(p)==null)cur_h= cur_h+width(p);
else
{cur_v= base_line+shift_amount(p);
edge= cur_h;
if(type(p)==vlist_node)
vlist_render(p);
else
hlist_render(p);
cur_h= edge+width(p);cur_v= base_line;
}
break;
case rule_node:
rule_ht= height(p);rule_dp= depth(p);rule_wd= width(p);
goto fin_rule;
case whatsit_node:
if(subtype(p)==image_node)
{scaled h,w;
w= image_width(p);
h= image_height(p);
if(g_sign!=normal)
{if(g_sign==stretching)
{if(image_stretch_order(p)==g_order)
{vet_glue((double)(glue_set(this_box))*image_stretch(p));
w= w+round(glue_temp);
}
}
else if(image_shrink_order(p)==g_order)
{vet_glue((double)(glue_set(this_box))*image_shrink(p));
w= w-round(glue_temp);
}
}
if(w!=image_width(p))
{double f;
f= (double)w/(double)image_width(p);
h= round((double)h*f);
}
render_image(cur_h,cur_v,w,h,image_no(p));
cur_h= cur_h+w;
}
break;
case glue_node:
{pointer g= glue_ptr(p);rule_wd= width(g)-cur_g;
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
{save_h= cur_h;
cur_h= left_edge+leader_wd*((cur_h-left_edge)/leader_wd);
if(cur_h<save_h)cur_h= cur_h+leader_wd;
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

{cur_v= base_line+shift_amount(leader_box);
save_h= cur_h;
if(type(leader_box)==vlist_node)
vlist_render(leader_box);
else
hlist_render(leader_box);
cur_v= base_line;
cur_h= save_h+leader_wd+lx;
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
mem[lig_trick]= mem[lig_char(p)];link(lig_trick)= link(p);
p= lig_trick;
goto reswitch;
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
p= link(p);
}
}
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

cur_g= 0;cur_glue= float_constant(0);
g_order= glue_order(this_box);
g_sign= glue_sign(this_box);p= list_ptr(this_box);
#ifdef DEBUG
if(p==0xffff)
QUIT("Undefined list pointer in vbox 0x%x-> mem[0x%x] -> 0x%x\n",
this_box,mem[this_box].i,p);
#endif
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
if(list_ptr(p)==null)cur_v= cur_v+height(p)+depth(p);
else
{cur_v= cur_v+height(p);save_v= cur_v;
cur_h= left_edge+shift_amount(p);
if(type(p)==vlist_node)vlist_render(p);
else hlist_render(p);
cur_v= save_v+depth(p);cur_h= left_edge;
}
break;
case rule_node:
rule_ht= height(p);rule_dp= depth(p);rule_wd= width(p);
goto fin_rule;
case whatsit_node:
if(subtype(p)==image_node)
{scaled h,w;
w= image_width(p);
h= image_height(p);
if(g_sign!=normal)
{if(g_sign==stretching)
{if(image_stretch_order(p)==g_order)
{vet_glue((double)(glue_set(this_box))*image_stretch(p));
h= h+round(glue_temp);
}
}
else if(image_shrink_order(p)==g_order)
{vet_glue((double)(glue_set(this_box))*image_shrink(p));
h= h-round(glue_temp);
}
}
if(h!=image_height(p))
{double f;
f= (double)h/(double)image_height(p);
w= round((double)w*f);
}
cur_v= cur_v+h;
render_image(cur_h,cur_v,w,h,image_no(p));
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
{cur_h= left_edge+shift_amount(leader_box);
cur_v= cur_v+height(leader_box);save_v= cur_v;
if(type(leader_box)==vlist_node)
vlist_render(leader_box);
else
hlist_render(leader_box);
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
#ifdef DEBUG
if(link(p)==1||link(p)==0xffff){
show_box(stream[0].p);
QUIT("vertical node mem[0x%x] =0x%x ->linking to node 0x%x\n",
p,mem[p].i,link(p));
}
#endif
p= link(p);
}
}

/*:255*//*256:*/
#line 4854 ".\\hint.w"

uint64_t hint_blank(void)
{nativeBlank();
return 0;
}
/*:256*//*257:*/
#line 4863 ".\\hint.w"


void hint_render(void)
{nativeBlank();
if(stream[0].p==null)return;
cur_h= 0;
cur_v= height(stream[0].p);
cur_f= -1;cur_fp= NULL;
if(type(stream[0].p)==vlist_node)
vlist_render(stream[0].p);
else
hlist_render(stream[0].p);
}
/*:257*/
#line 5689 ".\\hint.w"

/*:297*/
