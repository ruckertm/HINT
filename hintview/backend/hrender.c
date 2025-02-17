/*401:*/
#line 8324 "hint.w"

#include "basetypes.h"
#include "error.h"
#include "format.h"
#include <string.h> 
#include <math.h> 
#include "get.h"
#include "hint.h"
#include "hrender.h"
#include "rendernative.h"
#include "htex.h"

/*342:*/
#line 6560 "hint.w"

extern void render_char(int x,int y,uint8_t f,uint32_t cc,int s);
/*:342*/
#line 8336 "hint.w"


/*255:*/
#line 4516 "hint.w"

double xdpi= 600.0,ydpi= 600.0;
/*:255*//*273:*/
#line 4881 "hint.w"

static bool forward_mode= false,backward_mode= false;
/*:273*//*294:*/
#line 5442 "hint.w"

static char*m_str;
static int m_length,m_chars;
/*:294*//*297:*/
#line 5513 "hint.w"

#define MAX_M_DIST 512
static uint8_t m_dist[MAX_M_DIST+5];
static int m_ptr,m_max;
/*:297*//*298:*/
#line 5551 "hint.w"

static int m_ptr,m_max;
/*:298*//*301:*/
#line 5622 "hint.w"

static int m_state,m_spaces;
static uint32_t m_d;
/*:301*//*304:*/
#line 5675 "hint.w"

static int m_focus;
static uint64_t m_page;
/*:304*//*307:*/
#line 5710 "hint.w"

static bool c_ignore;
/*:307*//*314:*/
#line 5877 "hint.w"

static int cur_link= -1;
/*:314*//*346:*/
#line 6602 "hint.w"

int cur_color= 0,cur_mode= 0,cur_style= 0,next_style= 0;
/*:346*//*350:*/
#line 6657 "hint.w"

static scaled cur_h,cur_v;
static scaled rule_ht,rule_dp,rule_wd;
/*:350*/
#line 8338 "hint.w"

/*256:*/
#line 4520 "hint.w"

void hint_resize(int px_h,int px_v,double x_dpi,double y_dpi)
{
#if 0




static int old_px_h= 0,old_px_v= 0;
static double old_xdpi= 0.0,old_ydpi= 0.0;
if(old_px_h==px_h&&old_px_v==px_v&&old_xdpi==x_dpi&&old_ydpi==y_dpi)
return;
old_px_h= px_h;old_px_v= px_v;old_xdpi= x_dpi;old_ydpi= y_dpi;
#endif
#line 4534 "hint.w"
 xdpi= x_dpi;ydpi= y_dpi;
nativeSetSize(px_h,px_v,xdpi,ydpi);
hloc_clear();
hflush_contribution_list();hpage_init();
forward_mode= false;
backward_mode= false;
}
/*:256*//*267:*/
#line 4745 "hint.w"


uint64_t hint_page_top(uint64_t h)
{if(hin_addr==NULL)return 0;
hpos= hstart+LOC_POS0(h);
if(hpos>=hend)
return hint_page_bottom(hend-hstart);
hflush_contribution_list();
hloc_set(h);
if(LOC_OFF(h))
hget_par_node(LOC_OFF(h));
hint_forward();
#if 0
show_box(streams[0].p);
#endif
#line 4760 "hint.w"
 forward_mode= true;
backward_mode= false;
return h;
}
/*:267*//*268:*/
#line 4768 "hint.w"

uint64_t hint_page_get(void)
{
DBG(DBGPAGE,"page_get: %d : 0x%"PRIx64"\n",cur_loc,page_loc[cur_loc]);

if(hin_addr==NULL)return 0;
return page_loc[cur_loc];
}
/*:268*//*269:*/
#line 4784 "hint.w"

uint64_t hint_page(void)
{uint64_t i;
if(streams==NULL)return 0;
i= hint_page_get();
if(streams[0].p!=null)
return i;
else
return hint_page_top(i);
}
/*:269*//*270:*/
#line 4800 "hint.w"

uint64_t hint_page_home(void)
{uint64_t pos;
uint8_t where;
int n= zero_label_no;
if(hin_addr==NULL)return 0;
/*71:*/
#line 1222 "hint.w"

if(labels==NULL||n> max_ref[label_kind])
{where= LABEL_TOP;pos= 0;}
else
{where= labels[n].where;
#if 1
pos= ((uint64_t)labels[n].pos<<32)+(labels[n].pos-labels[n].pos0);
#else
#line 1230 "hint.w"
 pos= ((uint64_t)labels[n].pos0<<32);

#endif
#line 1233 "hint.w"
}
/*:71*/
#line 4806 "hint.w"

/*288:*/
#line 5241 "hint.w"

if(where==LABEL_TOP)return hint_page_top(pos);
else if(where==LABEL_BOT)return hint_page_bottom(pos);
else if(where==LABEL_MID)return hint_page_middle(pos);
else return hint_page_get();
/*:288*/
#line 4807 "hint.w"

}
/*:270*//*271:*/
#line 4828 "hint.w"

double hint_get_fpos(void)
{
DBG(DBGPAGE,"get_fpos: %d : 0x%"PRIx64"\n",cur_loc,page_loc[cur_loc]);

if(hin_addr==NULL)return 0.0;
return(double)LOC_POS(page_loc[cur_loc])/(double)(hend-hstart);
}
/*:271*//*272:*/
#line 4842 "hint.w"

uint64_t hint_set_fpos(double fpos)
{uint32_t pos,pos0;
uint8_t*p,*q;
DBG(DBGPAGE,"set_fpos: %f\n",fpos);
if(hin_addr==NULL)return 0;
if(fpos<0.0)fpos= 0.0;
if(fpos> 1.0)fpos= 1.0;
pos= round((hend-hstart)*fpos);
p= hstart+pos;
q= hpos= hstart;
while(hpos<p)
{q= hpos;hff_hpos();}
if(hpos> p)
{pos= pos0= q-hstart;
if(KIND(*q)==par_kind&&KIND(hff_tag)==list_kind&&hff_list_size> 0)
{if(p>=hstart+hff_list_pos+hff_list_size)
pos= pos0= hpos-hstart;
else
{q= hpos= hstart+hff_list_pos;
while(hpos<=p)
{if(KIND(*hpos)==glue_kind||KIND(*hpos)==penalty_kind||KIND(*hpos)==disc_kind)
q= hpos;
hff_hpos();
}
pos= q-hstart;
}
}
}
else
pos= pos0= hpos-hstart;
return hint_page_top(PAGE_LOC(pos0,pos-pos0));
}
/*:272*//*274:*/
#line 4886 "hint.w"

uint64_t hint_page_next(void)
{if(hin_addr==NULL)return 0;
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
/*:274*//*275:*/
#line 4911 "hint.w"

uint64_t hint_page_prev(void)
{if(hin_addr==NULL)return 0;
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
/*:275*//*276:*/
#line 4937 "hint.w"

uint64_t hint_page_bottom(uint64_t h)
{if(hin_addr==NULL)return 0;
hloc_set(h);
hflush_contribution_list();
hpos= hstart+LOC_POS0(h);
if(LOC_OFF(h))
hteg_par_node(LOC_OFF(h));
if(!hint_backward())return hint_page();
backward_mode= true;
forward_mode= false;
return hint_page_get();
}
/*:276*//*277:*/
#line 4968 "hint.w"

uint64_t hint_page_middle(uint64_t l)
{uint32_t target_pos,pos0,offset;
pointer p;
scaled h= 0,d= 0,hp,dp,target_dist= 0,break_dist= 0;
int pi= 0;
if(hin_addr==NULL)return 0;
target_pos= LOC_POS(l);
offset= LOC_OFF(l);
pos0= LOC_POS0(l);
if(hstart+pos0+offset>=hend)
return hint_page_bottom(hend-hstart);
hflush_contribution_list();
hpos= hstart+pos0;
hget_content();

if(offset> 0)
/*278:*/
#line 5010 "hint.w"

{pointer q,target_q;
/*279:*/
#line 5027 "hint.w"

target_q= null;
q= contrib_head;p= link(q);
h= d= target_dist= break_dist= 0;
while(p!=null)
{pointer qq;
/*281:*/
#line 5071 "hint.w"

switch(type(p))
{case hlist_node:case vlist_node:case rule_node:
hp= height(p);dp= depth(p);
pi= inf_penalty;
break;
case glue_node:
hp= width(glue_ptr(p));dp= 0;
pi= 0;
break;
case kern_node:
hp= width(p);dp= 0;
pi= inf_penalty;
break;
case penalty_node:
hp= dp= 0;
pi= penalty(p);
break;
default:
pi= hp= dp= 0;
}
/*:281*/
#line 5033 "hint.w"

qq= q;
q= p;
p= link(p);
if(target_q!=null)
{if(pi<=0)
break;
}
else if(p==null||LOC_POS(hlocation(p))> target_pos)
{target_q= qq;
target_dist= h+d;
h= d= 0;
}
h+= d+hp;
d= dp;
}
if(target_q==null)
{target_dist= h;break_dist= 0;}
else
break_dist= h;
/*:279*/
#line 5012 "hint.w"

if(target_dist+break_dist<=hvsize)
offset= 0;
else
{if(break_dist>=hvsize)
q= target_q;
else
/*282:*/
#line 5100 "hint.w"

{scaled dh;
dh= target_dist+break_dist-hvsize;
if(target_dist-dh> hvsize/2)
dh= target_dist-hvsize/2;
q= contrib_head;
p= link(q);
d= 0;
while(p!=null&&q!=target_q&&dh> 0)
{/*281:*/
#line 5071 "hint.w"

switch(type(p))
{case hlist_node:case vlist_node:case rule_node:
hp= height(p);dp= depth(p);
pi= inf_penalty;
break;
case glue_node:
hp= width(glue_ptr(p));dp= 0;
pi= 0;
break;
case kern_node:
hp= width(p);dp= 0;
pi= inf_penalty;
break;
case penalty_node:
hp= dp= 0;
pi= penalty(p);
break;
default:
pi= hp= dp= 0;
}
/*:281*/
#line 5109 "hint.w"

dh= dh-hp-d;
d= dp;
q= p;
p= link(p);
}
}
/*:282*/
#line 5020 "hint.w"

/*280:*/
#line 5056 "hint.w"

{p= link(q);
offset= LOC_OFF(hlocation(p));
link(q)= null;
flush_node_list(link(contrib_head));
link(contrib_head)= p;
}
/*:280*/
#line 5021 "hint.w"

goto found;
}
}
/*:278*/
#line 4985 "hint.w"

/*283:*/
#line 5123 "hint.w"

{pointer h_save= link(contrib_head);
pointer t_save= tail;
uint8_t*hpos_save= hpos;
pointer best_p= null;
int best_pi= 0;
link(contrib_head)= null;tail= contrib_head;
hpos= hstart+pos0;
h= target_dist+break_dist;
d= 0;
p= tail;
while(h<hvsize)
{while(link(p)==null&&hpos> hstart)
hteg_content();
if(link(p)==null)break;
p= link(p);
/*281:*/
#line 5071 "hint.w"

switch(type(p))
{case hlist_node:case vlist_node:case rule_node:
hp= height(p);dp= depth(p);
pi= inf_penalty;
break;
case glue_node:
hp= width(glue_ptr(p));dp= 0;
pi= 0;
break;
case kern_node:
hp= width(p);dp= 0;
pi= inf_penalty;
break;
case penalty_node:
hp= dp= 0;
pi= penalty(p);
break;
default:
pi= hp= dp= 0;
}
/*:281*/
#line 5139 "hint.w"

if(hpos==hstart)pi= eject_penalty;
if(h+hp+d> hvsize)
break;
h= h+d+hp;d= dp;
if(pi<best_pi)
{best_pi= pi;
best_p= p;
if(best_pi<=eject_penalty)break;
}
}
if(best_p==null)
{flush_node_list(link(contrib_head));
hpos= hstart+pos0;
offset= 0;
}
else
{p= link(contrib_head);
do{pointer q;
q= link(p);
link(p)= h_save;
h_save= p;
p= q;
}while(h_save!=best_p);
flush_node_list(p);
pos0= LOC_POS0(hlocation(best_p));
offset= 0;
}
link(contrib_head)= h_save;
if(t_save!=contrib_head)
tail= t_save;
hpos= hpos_save;
}
/*:283*/
#line 4986 "hint.w"

found:
hloc_set(PAGE_LOC(pos0,offset));
if(!hint_forward())return hint_page_top(0);
forward_mode= true;
backward_mode= false;
return hint_page_get();
}
/*:277*//*287:*/
#line 5230 "hint.w"

uint64_t hint_outline_page(int i)
{uint64_t pos;
uint8_t where;
if(i<0||i> max_outline||hint_outlines==NULL)return hint_page_get();
pos= hint_outlines[i].pos;
where= hint_outlines[i].where;
/*288:*/
#line 5241 "hint.w"

if(where==LABEL_TOP)return hint_page_top(pos);
else if(where==LABEL_BOT)return hint_page_bottom(pos);
else if(where==LABEL_MID)return hint_page_middle(pos);
else return hint_page_get();
/*:288*/
#line 5237 "hint.w"

}
/*:287*//*295:*/
#line 5447 "hint.w"

void hint_set_mark(char*m,int s)
{m_str= m;
m_length= s;
/*296:*/
#line 5458 "hint.w"

if(m_length> 0)
{int i,j,k;
for(i= j= k= 0;i<m_length&&m_str[i]==' ';i++)continue;
for(;i<m_length;i++)
if(m_str[i]!=' '||m_str[i+1]!=' ')
{m_str[k]= m_str[i];
if(m_str[k]==' ')j++;
k++;
}
m_str[k]= 0;
m_length= k;
m_chars= m_length-j;
}
/*:296*/
#line 5451 "hint.w"

hmark_page();
}
/*:295*//*299:*/
#line 5555 "hint.w"

static void m_put(uint32_t d)
{if(m_ptr<MAX_M_DIST)
{if(d==HINT_NO_POS)
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
if(x==0xFF)return HINT_NO_POS;
if(x&0x80)return x&0x7F;
while(true)
{y= m_dist[m_ptr++];
if(y&0x80)return(x<<7)+(y&0x7F);
x= (x<<7)+y;
}
}
/*:299*//*300:*/
#line 5596 "hint.w"

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
/*:300*//*302:*/
#line 5627 "hint.w"

static void next_m_char(uint32_t c)
{
reconsider:
if(m_state==0&&c!=m_str[0])
{if(c!=' ')
m_d++;
}
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
/*303:*/
#line 5661 "hint.w"

{int i= 0,j= 0;
do{
if(m_str[i]==' ')j++;
i++;
}while(i<m_state&&strncmp(m_str,m_str+i,m_state-i)!=0);
m_d= m_d+i-j;
m_state= m_state-i;
goto reconsider;
}
/*:303*/
#line 5645 "hint.w"



}
/*:302*//*305:*/
#line 5680 "hint.w"

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
trv_init(next_m_char);
if(type(streams[0].p)==vlist_node)
trv_vlist(list_ptr(streams[0].p));
else
trv_hlist(list_ptr(streams[0].p));
}
m_put(HINT_NO_POS);
if(m_focus>=m_max)m_focus= 0;
}
/*:305*//*312:*/
#line 5792 "hint.w"

void c_ignore_list(pointer p)
{while(p!=null)
{if(is_char_node(p))
{/*309:*/
#line 5734 "hint.w"

{while(m_d==0)
{cur_style= cur_style> 0?0:1;
if(cur_style> 0)
{if(m_ptr==m_focus)cur_style= 2;
m_d= m_chars;
}
else
m_d= m_get();
}
m_d--;
}
/*:309*/
#line 5796 "hint.w"

if(cur_style> next_style)next_style= cur_style;
}
else
{switch(type(p))
{case hlist_node:
case vlist_node:c_ignore_list(list_ptr(p));break;
case ligature_node:
{pointer q= lig_ptr(p);
while(q!=null)
{/*309:*/
#line 5734 "hint.w"

{while(m_d==0)
{cur_style= cur_style> 0?0:1;
if(cur_style> 0)
{if(m_ptr==m_focus)cur_style= 2;
m_d= m_chars;
}
else
m_d= m_get();
}
m_d--;
}
/*:309*/
#line 5806 "hint.w"

if(cur_style> next_style)next_style= cur_style;
q= link(q);
}
}
break;
}
}
p= link(p);
}
}
/*:312*//*313:*/
#line 5839 "hint.w"

bool hint_prev_mark(void)
{m_focus= m_prev(m_focus);
while(m_focus==0&&m_page> 0)
{hint_page_prev();
m_focus= m_prev(0);
}
return(m_focus!=0);
}

bool hint_next_mark(void)
{m_focus= m_next(m_focus);
while(m_focus==0)
{uint64_t p= m_page;
if(p==hint_page_next())break;
m_focus= m_next(0);
}
return(m_focus!=0);
}
/*:313*//*321:*/
#line 5938 "hint.w"

static int links_allocated= 0;
void add_new_link(int n,pointer p,scaled h,scaled v)
{hint_Link*t;
uint64_t pos;
uint8_t where;
max_link++;
if(max_link>=links_allocated)
{if(links_allocated<=0)
{links_allocated= 32;
ALLOCATE(hint_links,links_allocated,hint_Link);
}
else
{links_allocated= links_allocated*1.4142136+0.5;
REALLOCATE(hint_links,links_allocated,hint_Link);
}
DBG(DBGLABEL,"Links allocated %d\n",links_allocated);
}
t= hint_links+max_link;
DBG(DBGLABEL,"Link add %d\n",max_link);
REF_RNG(label_kind,n);
/*71:*/
#line 1222 "hint.w"

if(labels==NULL||n> max_ref[label_kind])
{where= LABEL_TOP;pos= 0;}
else
{where= labels[n].where;
#if 1
pos= ((uint64_t)labels[n].pos<<32)+(labels[n].pos-labels[n].pos0);
#else
#line 1230 "hint.w"
 pos= ((uint64_t)labels[n].pos0<<32);

#endif
#line 1233 "hint.w"
}
/*:71*/
#line 5959 "hint.w"

t->where= where;
t->pos= pos;
if(type(p)==hlist_node)
{scaled hp= height(p),dp= depth(p);
t->top= v-hp;
t->bottom= v+dp;
t->left= h;
t->right= h;
}
else
{t->top= v;
t->bottom= v;
t->left= h;
t->right= h+width(p);
}
}

void end_new_link(int n,pointer p,scaled h,scaled v)
{hint_Link*t;
if(max_link<0)return;
t= hint_links+max_link;
DBG(DBGLABEL,"Link end %d\n",max_link);
if(type(p)==hlist_node)
t->right= h;
else
t->bottom= v;
}
/*:321*//*322:*/
#line 6011 "hint.w"

static scaled hlink_distance(scaled x,scaled y,hint_Link*t)
{scaled d,dx= 0,dy= 0;
d= t->top-y;
if(d> 0)dy= d;
else
{d= y-t->bottom;
if(d> 0)dy= d;
}
d= x-t->right;
if(d> 0)dx= d;
else
{d= t->left-x;
if(d> 0)dx= d;
}
if(dx> dy)return dx;
else return dy;

}

static int last_hit_link= -1;

int hint_find_link(scaled x,scaled y,scaled precission)
{int i;
hint_Link*t;
if(max_link<0)return-1;
if(last_hit_link<0||last_hit_link> max_link)last_hit_link= max_link/2;
i= last_hit_link;
t= hint_links+i;
DBG(DBGLABEL,"Link find %d\n",max_link);
if(hlink_distance(x,y,t)<=precission)
return i;
else if(y<t->top)
{while(i> 0)
{i--;
t= hint_links+i;
DBG(DBGLABEL,"Link up %d\n",max_link);
if(hlink_distance(x,y,t)<=precission)
{last_hit_link= i;return i;}
}
return-1;
}
else
{int k;
scaled d,min_d= precission;
int min_i= -1;
for(k= 0;k<=max_link;k++)
{i= i+1;
if(i> max_link)i= 0;
t= hint_links+i;
DBG(DBGLABEL,"Link scan %d\n",max_link);
d= hlink_distance(x,y,t);
if(d<min_d)
{min_d= d;min_i= i;}
}
last_hit_link= min_i;
return last_hit_link;
}
}
/*:322*//*323:*/
#line 6076 "hint.w"

uint64_t hint_link_page(int i)
{uint64_t h;
uint8_t w;
if(i<0||i> max_link)return hint_page_get();
DBG(DBGLABEL,"Link page %d\n",max_link);
h= hint_links[i].pos;
w= hint_links[i].where;
if(w==LABEL_TOP)return hint_page_top(h);
else if(w==LABEL_BOT)return hint_page_bottom(h);
else if(w==LABEL_MID)return hint_page_middle(h);
else return hint_page_get();
}
/*:323*//*325:*/
#line 6111 "hint.w"

void hint_render_on(void)
{nativeInit();
}

void hint_render_off(void)
{nativeClear();
}
/*:325*//*326:*/
#line 6124 "hint.w"

void hint_dark(int dark)
{nativeSetColor(color_def!=NULL?color_def:color_defaults);
nativeSetDark(dark);
}
void hint_gamma(double gamma)
{nativeSetGamma(gamma);
}
/*:326*//*343:*/
#line 6567 "hint.w"

static void render_rule(int x,int y,int w,int h)
{if(w> 0&&h> 0)
nativeRule(SP2PT(x),SP2PT(y),SP2PT(w),SP2PT(h));
}
/*:343*//*344:*/
#line 6579 "hint.w"

void render_image(int x,int y,int w,int h,uint32_t n)
{
uint8_t*spos,*sstart,*send;
spos= hpos;sstart= hstart;send= hend;
hget_section(n);
nativeImage(SP2PT(x),SP2PT(y),SP2PT(w),SP2PT(h),hstart,hend);
hpos= spos;hstart= sstart;hend= send;
}
/*:344*//*349:*/
#line 6638 "hint.w"

uint64_t hint_blank(void)
{nativeSetColor(color_def!=NULL?color_def:color_defaults);
nativeBlank();
return 0;
}
/*:349*//*351:*/
#line 6662 "hint.w"

static void vlist_render(pointer this_box);
static scaled hcolor_distance(pointer p,
uint8_t g_sign,glue_ord g_order,glue_ratio g_set);
static scaled vcolor_distance(pointer p,
uint8_t g_sign,glue_ord g_order,glue_ratio g_set);
static void hlist_render(pointer this_box)
{scaled base_line;
scaled left_edge;
scaled h_save;
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
int list_color= cur_color;
int local_link= -1;
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
#line 6697 "hint.w"
 base_line= cur_v;
left_edge= cur_h;
/*318:*/
#line 5904 "hint.w"

if(cur_link>=0)
{add_new_link(cur_link,this_box,cur_h,cur_v);
local_link= cur_link;
cur_link= -1;
}
/*:318*/
#line 6699 "hint.w"

while(p!=null)
{
#ifdef DEBUG
if(p==0xffff)
QUIT("Undefined pointer in hlist 0x%x\n",p);
if(link(p)==0xffff)
QUIT("Undefined link in hlist mem[0x%x]=0x%x\n",p,mem[p].i);
#endif
#line 6708 "hint.w"
 if(is_char_node(p))
{do
{f= font(p);
c= character(p);
if(!c_ignore&&c!=' ')
{/*309:*/
#line 5734 "hint.w"

{while(m_d==0)
{cur_style= cur_style> 0?0:1;
if(cur_style> 0)
{if(m_ptr==m_focus)cur_style= 2;
m_d= m_chars;
}
else
m_d= m_get();
}
m_d--;
}
/*:309*/
#line 6713 "hint.w"

next_style= cur_style;
}
render_c:
#ifdef DEBUG
if(f> max_ref[font_kind])
QUIT("Undefined Font %d mem[0x%x]=0x%x\n",
f,p,mem[p].i);
#endif
#line 6722 "hint.w"
 render_char(cur_h,cur_v,f,c,next_style);
cur_h= cur_h+char_width(f,char_info(f,c));
#ifdef DEBUG
if(link(p)==0xffff)
QUIT("Undefined link in charlist mem[0x%x]=0x%x\n",p,mem[p].i);
#endif
#line 6728 "hint.w"
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
#line 6740 "hint.w"
 if(list_ptr(p)==null)cur_h= cur_h+width(p);
else
{int cur_c= cur_color;
cur_v= base_line+shift_amount(p);
edge= cur_h;
if(type(p)==vlist_node)
vlist_render(p);
else
hlist_render(p);
if(cur_color!=cur_c)
{cur_color= cur_c;nativeSetColor(color_def+cur_color);}
cur_h= edge+width(p);cur_v= base_line;
}
break;
case rule_node:
rule_ht= height(p);rule_dp= depth(p);rule_wd= width(p);
goto fin_rule;
case whatsit_node:
switch(subtype(p))
{case ignore_node:/*311:*/
#line 5771 "hint.w"

if(ignore_info(p)==1)
{next_style= 0;
c_ignore_list(ignore_list(p));
c_ignore= true;
}
else
c_ignore= false;
/*:311*/
#line 6759 "hint.w"
break;
case color_node:
cur_color= color_ref(p);
nativeSetColor(color_def+cur_color);
/*347:*/
#line 6606 "hint.w"

if(cur_color!=list_color&&
(BG(CURCOLOR(cur_mode,cur_style,color_def[cur_color]))&0xFF)> 0)
{scaled x,y,w,h;
x= cur_h;
y= cur_v+depth(this_box);
w= hcolor_distance(link(p),g_sign,g_order,glue_set(this_box));
h= height(this_box)+depth(this_box);
if(w> 0&&h> 0)
nativeBackground(SP2PT(x),SP2PT(y),SP2PT(w),SP2PT(h));
}
/*:347*/
#line 6763 "hint.w"

break;
case end_color_node:
cur_color= list_color;
nativeSetColor(color_def+cur_color);
break;
case start_link_node:
/*315:*/
#line 5881 "hint.w"

local_link= label_ref(as_label(p));
add_new_link(local_link,this_box,cur_h,cur_v);
/*:315*/
#line 6770 "hint.w"

cur_color= color_ref(as_color(p));
if(cur_color==0xFF)cur_color= list_color;
nativeSetColor(color_def+cur_color);
/*347:*/
#line 6606 "hint.w"

if(cur_color!=list_color&&
(BG(CURCOLOR(cur_mode,cur_style,color_def[cur_color]))&0xFF)> 0)
{scaled x,y,w,h;
x= cur_h;
y= cur_v+depth(this_box);
w= hcolor_distance(link(p),g_sign,g_order,glue_set(this_box));
h= height(this_box)+depth(this_box);
if(w> 0&&h> 0)
nativeBackground(SP2PT(x),SP2PT(y),SP2PT(w),SP2PT(h));
}
/*:347*/
#line 6774 "hint.w"

break;
case end_link_node:
/*316:*/
#line 5886 "hint.w"

end_new_link(local_link,this_box,cur_h,cur_v);
local_link= -1;
/*:316*/
#line 6777 "hint.w"

cur_color= color_ref(as_color(p));
if(cur_color==0xFF)cur_color= list_color;
nativeSetColor(color_def+cur_color);
/*347:*/
#line 6606 "hint.w"

if(cur_color!=list_color&&
(BG(CURCOLOR(cur_mode,cur_style,color_def[cur_color]))&0xFF)> 0)
{scaled x,y,w,h;
x= cur_h;
y= cur_v+depth(this_box);
w= hcolor_distance(link(p),g_sign,g_order,glue_set(this_box));
h= height(this_box)+depth(this_box);
if(w> 0&&h> 0)
nativeBackground(SP2PT(x),SP2PT(y),SP2PT(w),SP2PT(h));
}
/*:347*/
#line 6781 "hint.w"

break;
case image_node:
{scaled h,w;
w= image_width(p);
h= image_height(p);
render_image(cur_h,cur_v,w,h,image_no(p));
cur_h= cur_h+w;
}break;
default:break;
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
{h_save= cur_h;
cur_h= left_edge+leader_wd*((cur_h-left_edge)/leader_wd);
if(cur_h<h_save)cur_h= cur_h+leader_wd;
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

{int cur_c= cur_color;
cur_v= base_line+shift_amount(leader_box);
h_save= cur_h;
c_ignore= true;
if(type(leader_box)==vlist_node)
vlist_render(leader_box);
else
hlist_render(leader_box);
if(cur_color!=cur_c)
{cur_color= cur_c;nativeSetColor(color_def+cur_color);}
c_ignore= false;
cur_v= base_line;
cur_h= h_save+leader_wd+lx;
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
/*310:*/
#line 5751 "hint.w"


if(!c_ignore)
{pointer q;
next_style= 0;
q= lig_ptr(p);
while(q!=null)
{/*309:*/
#line 5734 "hint.w"

{while(m_d==0)
{cur_style= cur_style> 0?0:1;
if(cur_style> 0)
{if(m_ptr==m_focus)cur_style= 2;
m_d= m_chars;
}
else
m_d= m_get();
}
m_d--;
}
/*:309*/
#line 5758 "hint.w"

if(cur_style> next_style)next_style= cur_style;
q= link(q);
}
}
/*:310*/
#line 6863 "hint.w"

goto render_c;
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
#line 6885 "hint.w"
 p= link(p);
}
}
/*317:*/
#line 5894 "hint.w"

if(local_link>=0)
{end_new_link(local_link,this_box,cur_h,cur_v);
cur_link= local_link;
}
/*:317*/
#line 6888 "hint.w"

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
int local_link= -1;
cur_g= 0;cur_glue= float_constant(0);
int list_color= cur_color;
g_order= glue_order(this_box);
g_sign= glue_sign(this_box);p= list_ptr(this_box);
#ifdef DEBUG
if(p==0xffff)
QUIT("Undefined list pointer in vbox 0x%x-> mem[0x%x] -> 0x%x\n",
this_box,mem[this_box].i,p);
#endif
#line 6916 "hint.w"
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
#line 6929 "hint.w"
 if(list_ptr(p)==null)cur_v= cur_v+height(p)+depth(p);
else
{int cur_c= cur_color;
cur_v= cur_v+height(p);save_v= cur_v;
cur_h= left_edge+shift_amount(p);
if(type(p)==vlist_node)
vlist_render(p);
else
hlist_render(p);
if(cur_color!=cur_c)
{cur_color= cur_c;nativeSetColor(color_def+cur_color);}
cur_v= save_v+depth(p);cur_h= left_edge;
}
break;
case rule_node:
rule_ht= height(p);rule_dp= depth(p);rule_wd= width(p);
goto fin_rule;
case whatsit_node:
switch(subtype(p))
{case color_node:
cur_color= color_ref(p);
nativeSetColor(color_def+cur_color);
/*348:*/
#line 6619 "hint.w"

if(cur_color!=list_color&&
(BG(CURCOLOR(cur_mode,cur_style,color_def[cur_color]))&0xFF)> 0)
{scaled x,y,w,h;
x= left_edge;
h= vcolor_distance(link(p),g_sign,g_order,glue_set(this_box));
y= cur_v+h;
w= width(this_box);
if(w> 0&&h> 0)
nativeBackground(SP2PT(x),SP2PT(y),SP2PT(w),SP2PT(h));
}
/*:348*/
#line 6951 "hint.w"

break;
case end_color_node:
cur_color= list_color;
nativeSetColor(color_def+cur_color);
break;
case start_link_node:
/*315:*/
#line 5881 "hint.w"

local_link= label_ref(as_label(p));
add_new_link(local_link,this_box,cur_h,cur_v);
/*:315*/
#line 6958 "hint.w"

cur_color= color_ref(as_color(p));
if(cur_color==0xFF)cur_color= list_color;
nativeSetColor(color_def+cur_color);
/*348:*/
#line 6619 "hint.w"

if(cur_color!=list_color&&
(BG(CURCOLOR(cur_mode,cur_style,color_def[cur_color]))&0xFF)> 0)
{scaled x,y,w,h;
x= left_edge;
h= vcolor_distance(link(p),g_sign,g_order,glue_set(this_box));
y= cur_v+h;
w= width(this_box);
if(w> 0&&h> 0)
nativeBackground(SP2PT(x),SP2PT(y),SP2PT(w),SP2PT(h));
}
/*:348*/
#line 6962 "hint.w"

break;
case end_link_node:
/*316:*/
#line 5886 "hint.w"

end_new_link(local_link,this_box,cur_h,cur_v);
local_link= -1;
/*:316*/
#line 6965 "hint.w"

cur_color= color_ref(as_color(p));
if(cur_color==0xFF)cur_color= list_color;
nativeSetColor(color_def+cur_color);
/*348:*/
#line 6619 "hint.w"

if(cur_color!=list_color&&
(BG(CURCOLOR(cur_mode,cur_style,color_def[cur_color]))&0xFF)> 0)
{scaled x,y,w,h;
x= left_edge;
h= vcolor_distance(link(p),g_sign,g_order,glue_set(this_box));
y= cur_v+h;
w= width(this_box);
if(w> 0&&h> 0)
nativeBackground(SP2PT(x),SP2PT(y),SP2PT(w),SP2PT(h));
}
/*:348*/
#line 6969 "hint.w"

break;
case image_node:
{scaled h,w;
w= image_width(p);
h= image_height(p);
cur_v= cur_v+h;
render_image(cur_h,cur_v,w,h,image_no(p));
}
break;
default:break;
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
{int cur_c= cur_color;
cur_h= left_edge+shift_amount(leader_box);
cur_v= cur_v+height(leader_box);save_v= cur_v;
c_ignore= true;
if(type(leader_box)==vlist_node)
vlist_render(leader_box);
else
hlist_render(leader_box);
if(cur_color!=cur_c)
{cur_color= cur_c;nativeSetColor(color_def+cur_color);}
c_ignore= false;
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
#line 7070 "hint.w"
 p= link(p);
}
}

/*:351*//*352:*/
#line 7079 "hint.w"

static scaled hcolor_distance(pointer p,uint8_t g_sign,glue_ord g_order,glue_ratio g_set)
{scaled dist= 0;
double cur_glue= 0.0;
scaled cur_g= 0;
double glue_temp;
uint8_t f;
uint32_t c;
while(p!=null)
{if(is_char_node(p))
{do
{f= font(p);
c= character(p);
render_c:
dist= dist+char_width(f,char_info(f,c));
p= link(p);
}while(is_char_node(p));
}
else
{switch(type(p))
{case hlist_node:
case vlist_node:
case rule_node:
case kern_node:
case math_node:
dist= dist+width(p);
break;
case ligature_node:
f= font(lig_char(p));
c= character(lig_char(p));
goto render_c;
case whatsit_node:
switch(subtype(p))
{case start_link_node:
case end_link_node:
case color_node:
case end_color_node:
return dist;
case image_node:
dist= dist+image_width(p);
break;
default:break;
}
break;
case glue_node:
{pointer g;
scaled wd;
g= glue_ptr(p);wd= width(g)-cur_g;
if(g_sign!=normal)
{if(g_sign==stretching)
{if(stretch_order(g)==g_order)
{cur_glue= cur_glue+stretch(g);
vet_glue(g_set*cur_glue);
cur_g= round(glue_temp);
}
}
else if(shrink_order(g)==g_order)
{cur_glue= cur_glue-shrink(g);
vet_glue(g_set*cur_glue);
cur_g= round(glue_temp);
}
}
wd= wd+cur_g;
dist= dist+wd;
}
break;
default:;
}
p= link(p);
}
}
return dist;
}

/*:352*//*353:*/
#line 7155 "hint.w"

static scaled vcolor_distance(pointer p,uint8_t g_sign,glue_ord g_order,glue_ratio g_set)
{scaled dist= 0;
double cur_glue= 0.0;
scaled cur_g= 0;
double glue_temp;

while(p!=null)
{if(is_char_node(p))DBG(DBGTEX,"Glyph in vertical list ignored");
else
{switch(type(p))
{case hlist_node:
case vlist_node:
case rule_node:
dist= dist+height(p)+depth(p);
break;
case kern_node:
dist= dist+width(p);
break;
case whatsit_node:
switch(subtype(p))
{case start_link_node:
case end_link_node:
case color_node:
case end_color_node:
return dist;
case image_node:
dist= dist+image_height(p);
break;
default:break;
}
break;
case glue_node:
{pointer g;
scaled wd;
g= glue_ptr(p);wd= width(g)-cur_g;
if(g_sign!=normal)
{if(g_sign==stretching)
{if(stretch_order(g)==g_order)
{cur_glue= cur_glue+stretch(g);
vet_glue(g_set*cur_glue);
cur_g= round(glue_temp);
}
}
else if(shrink_order(g)==g_order)
{cur_glue= cur_glue-shrink(g);
vet_glue(g_set*cur_glue);
cur_g= round(glue_temp);
}
}
wd= wd+cur_g;
dist= dist+wd;
}
break;
default:;
}
p= link(p);
}
}
return dist;
}

/*:353*//*354:*/
#line 7221 "hint.w"


void hint_render(void)
{cur_color= 0;
nativeSetColor(color_def!=NULL?color_def:color_defaults);
nativeBlank();
if(streams==NULL||streams[0].p==null)return;
cur_h= 0;
cur_v= height(streams[0].p);
cur_link= -1;max_link= -1;last_hit_link= -1;
/*308:*/
#line 5727 "hint.w"

m_ptr= 0;m_d= m_get();c_ignore= false;cur_style= next_style= 0;
/*:308*/
#line 7231 "hint.w"

if(type(streams[0].p)==vlist_node)
vlist_render(streams[0].p);
else
hlist_render(streams[0].p);
}
/*:354*//*355:*/
#line 7259 "hint.w"

int hint_print_on(int w,int h,int bpr,int bpp,unsigned char*bits)
{return nativePrintStart(w,h,bpr,bpp,bits);
}

int hint_print_off(void)
{return nativePrintEnd();
}

int hint_print(unsigned char*bits)
{return nativePrint(bits);
}
/*:355*/
#line 8339 "hint.w"

/*:401*/
