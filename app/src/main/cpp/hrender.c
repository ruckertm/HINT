/*343:*/
#line 6728 "hint.w"

#include "basetypes.h"
#include "error.h"
#include "hformat.h"
#include <string.h> 
#include <math.h> 
#include "hget.h"
#include "hrender.h"
#include "rendernative.h"
#include "htex.h"
#include "hint.h"
/*261:*/
#line 4474 "hint.w"

#define MARK_BIT 0x1
#define FOCUS_BIT 0x2
/*:261*//*289:*/
#line 5245 "hint.w"

#define SP2PT(X) ((X)/(double)(1<<16))
/*:289*/
#line 6739 "hint.w"

/*279:*/
#line 4924 "hint.w"

extern struct font_s*hget_font(unsigned char f);
/*:279*//*291:*/
#line 5264 "hint.w"

extern void render_char(int x,int y,struct font_s*f,uint32_t cc,uint8_t s);
/*:291*/
#line 6740 "hint.w"


/*256:*/
#line 4389 "hint.w"

static bool forward_mode= false,backward_mode= false;
/*:256*//*262:*/
#line 4507 "hint.w"

#define MAX_M_DIST 512
static uint8_t m_dist[MAX_M_DIST+5];
static int m_ptr,m_max,m_state,m_length,m_spaces,m_chars,m_focus;
static uint64_t m_page;
static uint32_t m_d;
static char*m_str;
/*:262*/
#line 6742 "hint.w"

/*254:*/
#line 4339 "hint.w"


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
#if 0
show_box(streams[0].p);
#endif
forward_mode= true;
backward_mode= false;
return h;
}
/*:254*//*255:*/
#line 4365 "hint.w"

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
#line 4394 "hint.w"

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
#line 4419 "hint.w"

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
#line 4444 "hint.w"

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
#line 4459 "hint.w"

uint64_t hint_page_center(uint64_t h)
{if(hbase==NULL)return hint_blank();
QUIT("hint_page_center not yet implemented");
}
/*:260*//*263:*/
#line 4536 "hint.w"

static void m_put(uint32_t d)
{if(m_ptr<MAX_M_DIST)
{if(d==0xFF)
m_dist[m_max= m_ptr]= 0xFF;
else if(d<0x7F)
m_dist[m_ptr++]= 0x80+d;
else
{if(d<(1<<14))
{
two_byte:
m_dist[m_ptr++]= d>>7;
m_dist[m_ptr++]= 0x80+(d&0x7F);
return;
}
if(d>=(1<<28))m_dist[m_ptr++]= d>>28;
if(d>=(1<<21))m_dist[m_ptr++]= (d>>21)&0x7F;
if(d>=(1<<14))m_dist[m_ptr++]= (d>>14)&0x7F;
d= d&((1<<14)-1);
goto two_byte;
}
}
}

static uint32_t m_get(void)
{uint32_t x,y;
x= m_dist[m_ptr++];
if(x==0xFF)return 0xFFFFFFFF;
if(x&0x80)return x&0x7F;
while(true)
{y= m_dist[m_ptr++];
if(y&0x80)return(x<<7)+(y&0x7F);
x= (x<<7)+y;
}
}

static int m_next(int i)
{while((0x80&m_dist[i])==0)i++;
if(m_dist[i]==0xFF)return 0;
else return i+1;
}

static int m_prev(int i)
{if(i<=0)return m_max;
i--;
while(i> 0&&(0x80&m_dist[i-1])==0)i--;
return i;
}
/*:263*//*264:*/
#line 4595 "hint.w"

static void next_m_char(uint32_t c)
{if(m_state<0)m_state= -m_state;
reconsider:
if(m_state==0&&c!=m_str[0])
m_d++;
else if(c==m_str[m_state])
{if(m_state==0)m_spaces= 0;
m_state++;
if(m_state==m_length)
{m_put(m_d);
m_d= 0;
m_state= 0;
}
}
else
{int i= 0,k= 0;
do{
if(m_str[i]==' ')k++;
i++;
}while(i<m_state&&strncmp(m_str,m_str+i,m_state-i)!=0);
m_d= m_d+i-k;
m_state= m_state-i;
goto reconsider;
}
}
/*:264*//*266:*/
#line 4645 "hint.w"

static void next_m_space(void)
{if(m_state==0&&m_str[0]==' ')
{m_state= -1;m_spaces= 1;}
else if(m_state>=0&&m_str[m_state]==' ')
{if(m_state==0)m_spaces= 0;
m_state++;m_spaces++;
if(m_state==m_length)
{m_put(m_d);
m_d= 0;
m_state= 0;
}
else
m_state= -m_state;
}
else if(m_state> 0)
{m_d= m_d+m_state-m_spaces;m_state= 0;}
}
/*:266*//*267:*/
#line 4667 "hint.w"

static void vlist_mark(pointer this_box);
static void hlist_mark(pointer this_box)
{pointer p;
p= list_ptr(this_box);
while(p!=null)
{if(is_char_node(p))next_m_char(character(p));
else switch(type(p))
{case hlist_node:if(list_ptr(p)!=null)hlist_mark(p);break;
case vlist_node:if(list_ptr(p)!=null)vlist_mark(p);break;
case ligature_node:
{pointer q= lig_ptr(p);
while(q!=null)
{next_m_char(character(q));q= link(q);
}
}
break;
case glue_node:next_m_space();break;
default:break;
}
p= link(p);
}
}

static void vlist_mark(pointer this_box)
{pointer p;
p= list_ptr(this_box);
while(p!=null)
{switch(type(p))
{case hlist_node:if(list_ptr(p)!=null)hlist_mark(p);next_m_space();break;
case vlist_node:if(list_ptr(p)!=null)vlist_mark(p);break;
default:break;
}
p= link(p);
}
}
/*:267*//*269:*/
#line 4716 "hint.w"

void hmark_page(void)
{if(streams==NULL||streams[0].p==null)return;
m_ptr= 0;
if(m_page!=page_loc[cur_loc])
{m_page= page_loc[cur_loc];
m_focus= 0;
}
if(m_length> 0)
{m_d= 0;
m_state= 0;
if(type(streams[0].p)==vlist_node)
vlist_mark(streams[0].p);
else
hlist_mark(streams[0].p);
}
m_put(0xFF);
if(m_focus>=m_max)m_focus= 0;
}

void hint_set_mark(char*m,int s)
{m_str= m;
m_length= s;
/*265:*/
#line 4624 "hint.w"

if(m_length> 0)
{int i,k;
m_spaces= 0;
for(i= k= 0;i<m_length;i++)
if(m_str[i]!=' '||m_str[i+1]!=' ')
{m_str[k]= m_str[i];
if(m_str[k]==' ')m_spaces++;
k++;
}
m_str[k]= 0;
m_length= k;
m_chars= m_length-m_spaces;
}
/*:265*/
#line 4739 "hint.w"

hmark_page();
}
/*:269*//*273:*/
#line 4804 "hint.w"

bool hint_prev_mark(void)
{m_focus= m_prev(m_focus);
while(m_focus==0&&m_page> 0)
{hint_prev_page();
m_focus= m_prev(0);
}
return(m_focus!=0);
}

bool hint_next_mark(void)
{m_focus= m_next(m_focus);
while(m_focus==0)
{uint64_t p= m_page;
if(p==hint_next_page())break;
m_focus= m_next(0);
}
return(m_focus!=0);
}
/*:273*//*274:*/
#line 4829 "hint.w"

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
/*:274*//*292:*/
#line 5271 "hint.w"

static void render_rule(int x,int y,int w,int h)
{if(w> 0&&h> 0)
nativeRule(SP2PT(x),SP2PT(y),SP2PT(w),SP2PT(h));
}
/*:292*//*293:*/
#line 5282 "hint.w"

void render_image(int x,int y,int w,int h,uint32_t n)
{
uint8_t*spos,*sstart,*send;
spos= hpos;sstart= hstart;send= hend;
hget_section(n);
nativeImage(SP2PT(x),SP2PT(y),SP2PT(w),SP2PT(h),hstart,hend);
hpos= spos;hstart= sstart;hend= send;
}
/*:293*//*294:*/
#line 5307 "hint.w"

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
uint8_t cur_s= 0;
uint8_t f;
uint32_t c;

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
{
#ifdef DEBUG
if(p==0xffff)
QUIT("Undefined pointer in hlist 0x%x\n",p);
if(link(p)==0xffff)
QUIT("Undefined link in hlist mem[0x%x]=0x%x\n",p,mem[p].i);
#endif
if(is_char_node(p))
{do
{/*271:*/
#line 4756 "hint.w"

{while(m_d==0)
{m_state^= MARK_BIT;
if(m_state&MARK_BIT)
{if(m_ptr==m_focus)m_state|= FOCUS_BIT;else m_state&= ~FOCUS_BIT;
m_d= m_chars;
}
else
{m_state&= ~FOCUS_BIT;
m_d= m_get();
}
}
m_d--;
}
/*:271*/
#line 5356 "hint.w"

cur_s= m_state;
f= font(p);
c= character(p);
render_char:
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
render_char(cur_h,cur_v,cur_fp,c,cur_s);
cur_h= cur_h+char_width(f,char_info(f,c));
#ifdef DEBUG
if(link(p)==0xffff)
QUIT("Undefined link in charlist mem[0x%x]=0x%x\n",p,mem[p].i);
#endif
p= link(p);
}while(is_char_node(p));
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
{pointer g;
g= glue_ptr(p);rule_wd= width(g)-cur_g;
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
f= font(lig_char(p));
c= character(lig_char(p));
/*272:*/
#line 4774 "hint.w"

{pointer q;
cur_s= 0;
q= lig_ptr(p);
while(q!=null)
{/*271:*/
#line 4756 "hint.w"

{while(m_d==0)
{m_state^= MARK_BIT;
if(m_state&MARK_BIT)
{if(m_ptr==m_focus)m_state|= FOCUS_BIT;else m_state&= ~FOCUS_BIT;
m_d= m_chars;
}
else
{m_state&= ~FOCUS_BIT;
m_d= m_get();
}
}
m_d--;
}
/*:271*/
#line 4779 "hint.w"

cur_s|= m_state;
q= link(q);
}
}
/*:272*/
#line 5494 "hint.w"

goto render_char;
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
else
hlist_render(p);
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
#if 0
if(link(p)==1||link(p)==0xffff){
show_box(streams[0].p);
QUIT("vertical node mem[0x%x] =0x%x ->linking to node 0x%x\n",
p,mem[p].i,link(p));
}
#endif
p= link(p);
}
}

/*:294*//*295:*/
#line 5691 "hint.w"

uint64_t hint_blank(void)
{nativeBlank();
return 0;
}
/*:295*//*296:*/
#line 5700 "hint.w"


void hint_render(void)
{nativeBlank();
if(streams==NULL||streams[0].p==null)return;
cur_h= 0;
cur_v= height(streams[0].p);
cur_f= -1;cur_fp= NULL;
/*268:*/
#line 4710 "hint.w"

m_ptr= 0;m_d= 0;m_state= MARK_BIT;
/*:268*/
#line 5708 "hint.w"

if(type(streams[0].p)==vlist_node)
vlist_render(streams[0].p);
else
hlist_render(streams[0].p);
}
/*:296*/
#line 6743 "hint.w"

/*:343*/
