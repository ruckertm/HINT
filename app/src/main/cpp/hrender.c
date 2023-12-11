/*330:*/
#line 6394 ".\\hint.w"

#include <math.h> 
#include "texextern.h"
#include "hget.h"
#include "hint.h"
#include "hrender.h"
#include "rendernative.h"
#include "texdefs.h"

/*266:*/
#line 4600 ".\\hint.w"

extern struct font_s*hget_font(unsigned char f);
/*:266*//*278:*/
#line 4946 ".\\hint.w"

extern void render_char(int x,int y,struct font_s*f,uint32_t cc);
/*:278*/
#line 6403 ".\\hint.w"


/*256:*/
#line 4424 ".\\hint.w"

static bool forward_mode= false,backward_mode= false;
/*:256*/
#line 6405 ".\\hint.w"

/*254:*/
#line 4374 ".\\hint.w"

static char *searchString = null;
static int curSearch = 0;

uint64_t hint_page_top(uint64_t h)
{if(hbase==NULL)return 0;
hpos= hstart+(h&0xffffffff);
if(hpos>=hend)
return hint_page_bottom(hend-hstart);
hflush_contribution_list();
hloc_set(h);
if(h> 0xffffffff)
hget_par_node(h>>32);
hint_forward();
#ifdef DEBUG
show_box(streams[0].p);
#endif
forward_mode= true;
backward_mode= false;
return h;
}
/*:254*//*255:*/
#line 4400 ".\\hint.w"

uint64_t hint_page_get(void)
{
DBG(DBGPAGE,"page_get: %d : 0x%"PRIx64"\n",cur_loc,page_loc[cur_loc]);

return page_loc[cur_loc];
}

uint64_t hint_page(void)
{uint64_t i;
if(streams==NULL)return 0;
i= hint_page_get();
if(streams[0].p!=null)
return i;
else
return hint_page_top(i);
}
/*:255*//*257:*/
#line 4429 ".\\hint.w"

uint64_t hint_next_page(void)
{if(hbase==NULL)return 0;
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
/*:257*//*258:*/
#line 4454 ".\\hint.w"

uint64_t hint_prev_page(void)
{if(hbase==NULL)return 0;
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
/*:258*//*259:*/
#line 4479 ".\\hint.w"

uint64_t hint_page_bottom(uint64_t h)
{if(hbase==NULL)return 0;
hflush_contribution_list();
hpos= hstart+(h&0xffffffff);
if(h> 0xffffffff)
hteg_par_node(h>>32);
if(!hint_backward())return hint_page();
backward_mode= true;
forward_mode= false;
return hint_page_get();
}
/*:259*//*260:*/
#line 4494 ".\\hint.w"

uint64_t hint_page_center(uint64_t h)
{if(hbase==NULL)return hint_blank();
QUIT("hint_page_center not yet implemented");
}
/*:260*//*261:*/
#line 4505 ".\\hint.w"

void hint_resize(int px_h,int px_v,double dpi)
{static int old_px_h= 0,old_px_v= 0;
static double old_dpi= 0.0;
nativeSetSize(px_h,px_v,dpi);
if(old_px_h==px_h&&old_px_v==px_v&&old_dpi==dpi)return;
old_px_h= px_h;old_px_v= px_v;old_dpi= dpi;
hloc_clear();
hflush_contribution_list();hpage_init();
forward_mode= false;
backward_mode= false;
}
/*:261*//*279:*/
#line 4953 ".\\hint.w"

static void render_rule(int x,int y,int w,int h)
{if(w> 0&&h> 0)
nativeRule(SP2PT(x),SP2PT(y),SP2PT(w),SP2PT(h));
}
/*:279*//*280:*/
#line 4964 ".\\hint.w"

void render_image(int x,int y,int w,int h,uint32_t n)
{
uint8_t*spos,*sstart,*send;
spos= hpos;sstart= hstart;send= hend;
hget_section(n);
nativeImage(SP2PT(x),SP2PT(y),SP2PT(w),SP2PT(h),hstart,hend);
hpos= spos;hstart= sstart;hend= send;
}
/*:280*//*281:*/
#line 4989 ".\\hint.w"

static scaled cur_h,cur_v;
static scaled rule_ht,rule_dp,rule_wd;
static int cur_f;
static struct font_s*cur_fp;

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
}
render_char(cur_h,cur_v,cur_fp,c);
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
show_box(streams[0].p);
QUIT("vertical node mem[0x%x] =0x%x ->linking to node 0x%x\n",
p,mem[p].i,link(p));
}
#endif
p= link(p);
}
}

/*:281*//*282:*/
#line 5364 ".\\hint.w"

uint64_t hint_blank(void)
{nativeBlank();
return 0;
}
/*:282*//*283:*/
#line 5373 ".\\hint.w"


void hint_render(void)
{nativeBlank();
if(streams==NULL||streams[0].p==null)return;
cur_h= 0;
cur_v= height(streams[0].p);
cur_f= -1;cur_fp= NULL;
if(type(streams[0].p)==vlist_node)
vlist_render(streams[0].p);
else
hlist_render(streams[0].p);
}
/*:283*/
#line 6406 ".\\hint.w"

/*:330*/

void set_search(char *value) {
    searchString = value;
}