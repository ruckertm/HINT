/*252:*/
#line 3866 ".\\hint.w"

#ifndef WIN32
#include <sys/mman.h> 
#else
#include <windows.h> 
#endif
#include <sys/stat.h> 
#include <fcntl.h> 
#include <string.h> 
#include <math.h> 
#include <zlib.h> 
#include "htex.h"
#include "hformat.h"
#include "hdefaults.h"
#include "hpos.h"
#include "hget.h"
#include "hteg.h"
/*37:*/
#line 620 ".\\hint.w"

#define null 0
/*:37*//*74:*/
#line 1149 ".\\hint.w"

#define is_char_node(X) (X >= hi_mem_min)   
#define disc_node 7 
#define glue_node 10 
#define kern_node 11 
#define penalty_node 12 
#define empty_flag 0xFFFF
/*:74*//*103:*/
#line 1492 ".\\hint.w"

#define before 0
#define after 1
/*:103*//*112:*/
#line 1568 ".\\hint.w"

#define null_flag -010000000000 
#define prev_depth aux.sc 
#define ignore_depth -65536000 
/*:112*//*113:*/
#line 1576 ".\\hint.w"

#ifdef DEBUG
#define incr_dyn_used (dyn_used++)
#define decr_dyn_used (dyn_used--)
#else
#define incr_dyn_used
#define decr_dyn_used
#endif
#define width_offset 1
#define depth_offset 2
#define height_offset 3
#define sc i  
#define width(X) mem[X+width_offset].i
#define depth(X) mem[X+depth_offset].i
#define height(X) mem[X+height_offset].i


/*:113*//*118:*/
#line 1642 ".\\hint.w"

#define glue_order(X) subtype(X+list_offset) 
#define glue_sign(X) type(X+list_offset) 
#define glue_spec_size 4
#define normal 0 
#define stretching 1 
#define shrinking 2 
/*:118*//*122:*/
#line 1706 ".\\hint.w"

#define glue_spec_size 4

#define type(X) mem[X].hh.b0
#define subtype(X) mem[X].hh.b1

#define stretch(X) mem[X+2].i
#define shrink(X) mem[X+3].i
#define stretch_order type
#define shrink_order subtype
/*:122*//*136:*/
#line 2055 ".\\hint.w"

#define vlist_node 1

#define link(X) mem[X].hh.rh 

#define shift_amount(X) mem[X+4].i
#define list_offset 5
#define list_ptr(X) link(X+list_offset)
#define glue_offset 6
#define glue_set(X) mem[X+glue_offset].gr
#define glue_order(X) subtype(X+list_offset)
#define glue_sign(X) type(X+list_offset)
/*:136*//*147:*/
#line 2265 ".\\hint.w"

#define exactly 0
#define additional 1
/*:147*//*153:*/
#line 2325 ".\\hint.w"

#define explicit 1
/*:153*//*159:*/
#line 2370 ".\\hint.w"

#define a_leaders 100
#define leader_ptr(X) link(X+1)
/*:159*//*164:*/
#line 2413 ".\\hint.w"

#define zero_glue 0
/*:164*//*176:*/
#line 2549 ".\\hint.w"

#define set_replace_count(X,Y) (mem[X].hh.b1=  (Y) &0x7F)
#define replace_count(X)   (mem[X].hh.b1&0x7F)
#define set_auto_disc(X) (mem[X].hh.b1|=  0x80)
#define is_auto_disc(X)  (mem[X].hh.b1 & 0x80)
#define pre_break llink
#define post_break rlink
#define info(X) mem[X].hh.lh
#define llink(X) info(X+1)
#define rlink(X) link(X+1)
extern pointer new_disc(void);
/*:176*//*183:*/
#line 2731 ".\\hint.w"

#define math_node 9 
#define non_discardable(X) (type(X) < math_node)
/*:183*//*189:*/
#line 2808 ".\\hint.w"

#define adjust_node 5
#define adjust_ptr(X) mem[X+1].i
#define small_node_size 2 
/*:189*//*195:*/
#line 2868 ".\\hint.w"

#define whatsit_node 8 
#define image_node 10
#define image_node_size 11
#define image_width(X) width(X)
#define image_height(X) height(X)
#define image_depth(X) depth(X)
#define image_no(X) mem[X+4].u
#define image_stretch(X) mem[X+7].i
#define image_shrink(X) mem[X+8].i
#define image_stretch_order(X) stretch_order(X+9)
#define image_shrink_order(X) shrink_order(X+9)
/*:195*//*197:*/
#line 2919 ".\\hint.w"

#define inf_bad 10000
#define odd(X)       ((X)&1)
#define chr(X)       ((unsigned char)(X))
#define ord(X)       ((int)(X))
#define abs(X)       ((X)> -(X)?(X):-(X))
#define round(X)     ((int)((X)>=0.0?floor((X)+0.5):ceil((X)-0.5)))
/*:197*//*205:*/
#line 3049 ".\\hint.w"

#define mode cur_list.mode_field 
#define head cur_list.head_field 
#define tail cur_list.tail_field 
#define prev_graf cur_list.pg_field 
#define aux cur_list.aux_field 
#define cur_bs  cur_list.bs_field.bs
#define cur_ls  cur_list.bs_field.ls
#define cur_lsl cur_list.bs_field.lsl
#define needs_bs cur_list.insert_bs
#define node_pos cur_list.np_field
#define node_pos1 (nest_ptr==0?0:nest[nest_ptr-1].np_field)
#define tail_append(X) {link(tail)= X;tail= link(tail); }
/*:205*//*212:*/
#line 3143 ".\\hint.w"


#define mem_top 30000
#define contrib_head mem_top-1
#define page_head mem_top-2 
#define vmode 1 
#define empty 0 
#define contrib_tail nest[0].tail_field 
#define max_depth      dimen_par(max_depth_code)
/*:212*/
#line 3883 ".\\hint.w"


/*70:*/
#line 1098 ".\\hint.w"

#define HBACK(X) ((hpos-(X)<hstart)?(QUIT("HTEG underflow\n"),NULL):(hpos-= (X)))

#define HTEG8     (HBACK(1),*(hpos))
#define HTEG16(X) (HBACK(2),(X)= (hpos[0]<<8)+hpos[1])
#define HTEG24(X) (HBACK(3),(X)= (hpos[0]<<16)+(hpos[1]<<8)+hpos[2])
#define HTEG32(X) (HBACK(4),(X)= (hpos[0]<<24)+(hpos[1]<<16)+(hpos[2]<<8)+hpos[3])
/*:70*//*83:*/
#line 1291 ".\\hint.w"

#define HTEG_XDIMEN(I,X) \
  if((I)&b001) (X).v= hteg_float32(); else (X).v= 0.0;\
  if((I)&b010) (X).h= hteg_float32();  else (X).h= 0.0;\
  if((I)&b100) HTEG32((X).w); else (X).w= 0;\
/*:83*//*90:*/
#line 1380 ".\\hint.w"

#define HTEG_STRETCH(F,O) { stch_t _st;  HTEG32(_st.u); (O)= _st.u&3;  _st.u&= ~3; (F)= (scaled)(_st.f*ONE); }
/*:90*//*92:*/
#line 1400 ".\\hint.w"

#define HTEG_GLYPH(I) \
{uint8_t f; uint32_t c;\
  f= HTEG8; REF(font_kind,f);\
  if (I==1) c= HTEG8;\
  else if (I==2) HTEG16(c);\
  else if (I==3) HTEG24(c);\
  else if (I==4) HTEG32(c);\
  tail_append(new_character(f,c));\
}
/*:92*//*100:*/
#line 1468 ".\\hint.w"

#define HTEG_MATH(I,M)  \
{ scaled w;\
if ((I)&b001) HTEG32(w); else w= 0; \
if ((I)&b100)  tail_append(new_math(w,before)); \
if ((I)&b010)  tail_append(new_math(w,after)); }
/*:100*//*107:*/
#line 1518 ".\\hint.w"

#define HTEG_RULE(I)\
{ pointer p= new_rule();\
if ((I)&b001) HTEG32(width(p)); else width(p)= null_flag;\
if ((I)&b010) HTEG32(depth(p)); else depth(p)= null_flag;\
if ((I)&b100) HTEG32(height(p)); else height(p)= null_flag;\
tail_append(p);}
/*:107*//*115:*/
#line 1607 ".\\hint.w"

#define HTEG_GLUE(I) \
  p=  get_node(glue_spec_size); \
  if((I)&b001) HTEG_STRETCH(shrink(p),shrink_order(p)) else shrink(p)= 0, shrink_order(p)= normal;\
  if((I)&b010) HTEG_STRETCH(stretch(p),stretch_order(p)) else stretch(p)= 0, stretch_order(p)= normal;\
  if(I==b111) width(p)= hteg_xdimen_node(); \
  else { width(p)= 0; if((I)&b100) HTEG32(width(p));}
/*:115*//*125:*/
#line 1743 ".\\hint.w"

#define IS_LIST(X)  (KIND(X)==list_kind || KIND(X)==adjust_kind || \
        KIND(X)==text_kind  || KIND(X)==param_kind)
/*:125*//*130:*/
#line 1951 ".\\hint.w"

#define HTEG_BOX(I) \
pointer p= new_null_box();\
list_ptr(p)= hteg_list();\
if ((I)&b100) {uint8_t x= HTEG8; glue_order(p)= x&0xF; glue_sign(p)= x>>4; glue_set(p)= hteg_float32(); }\
if ((I)&b010) HTEG32(shift_amount(p));\
HTEG32(width(p));\
if ((I)&b001) HTEG32(depth(p));\
HTEG32(height(p));
/*:130*//*139:*/
#line 2087 ".\\hint.w"

#define HTEG_SET(I) \
  scaled x, st, sh; uint8_t sto, sho; \
  p= new_null_box();\
  list_ptr(p)= hteg_list();\
  HTEG_STRETCH(sh,sho);HTEG_STRETCH(st,sto);\
  if ((I)&b010) HTEG32(shift_amount(p)); \
  HTEG32(width(p));if ((I)&b001) HTEG32(depth(p));HTEG32(height(p)); \
  if ((I)&b100) x= hteg_xdimen_node(); else x= hget_xdimen_ref(HTEG8);
/*:139*//*144:*/
#line 2224 ".\\hint.w"

#define HTEG_PACK(I) \
 pointer p; scaled x, d;  uint8_t m; \
 p= hteg_list();\
 if ((I)&b001)  HTEG32(d); else d=  MAX_DIMEN; \
 if ((I)&b010) m= additional; else m= exactly; \
 if ((I)&b100) x= hteg_xdimen_node();  else x= hget_xdimen_ref(HTEG8);
/*:144*//*150:*/
#line 2289 ".\\hint.w"

#define HTEG_KERN(I) \
pointer p; scaled x; \
if (((I)&b011)==0) x= hget_dimen_ref(HTEG8);\
else if (((I)&b011)==1) x= hget_xdimen_ref(HTEG8);\
else if (((I)&b011)==2) HTEG32(x);\
else if (((I)&b011)==3) x= hteg_xdimen_node();\
p= new_kern(x);\
if ((I)&b100) subtype(p)= explicit;\
tail_append(p);
/*:150*//*156:*/
#line 2345 ".\\hint.w"

#define HTEG_LEADERS(I) \
{pointer p= hteg_glue_node();subtype(p)= a_leaders+((I)&b011)-1;\
if (KIND(*(hpos-1))==rule_kind) leader_ptr(p)= hteg_rule_node(); \
else if (KIND(*(hpos-1))==hbox_kind) leader_ptr(p)= hteg_hbox_node(); \
else  leader_ptr(p)= hteg_vbox_node();\
tail_append(p);}
/*:156*//*161:*/
#line 2384 ".\\hint.w"

#define HTEG_BASELINE(I,B) \
  if((I)&b001) HTEG32((B).lsl); else B.lsl= 0; \
  if((I)&b010) hteg_glue_spec(); else (B).ls= zero_glue; \
  if((I)&b100) hteg_glue_spec(); else (B).bs= zero_glue;
/*:161*//*166:*/
#line 2433 ".\\hint.w"

#define HTEG_LIG(I) \
{pointer p;uint8_t f; uint32_t c; uint8_t s,*t;\
if ((I)==7) s= HTEG8; else s= (I);\
t= hpos-s; hpos= t; c= hget_utf8(); hpos= t;\
if ((I)==7) { uint8_t n; n= HTEG8;\
  if(n!=s)   QUIT("Sizes in ligature don't match %d!=%d",s,n);}\
f= HTEG8;\
p= new_ligature(f, c, null); tail_append(p); \
}
/*:166*//*171:*/
#line 2487 ".\\hint.w"

#define HTEG_HYPHEN(I)\
  pointer p= new_disc(); \
  if ((I)&b001) {uint8_t r; r= HTEG8; set_replace_count(p,r); \
                 if ((r&0x80)==0) set_auto_disc(p); }\
  else  set_auto_disc(p);\
  if ((I)&b010) post_break(p)= hteg_list(); \
  if ((I)&b100) pre_break(p)= hteg_list();
/*:171*//*185:*/
#line 2748 ".\\hint.w"

#define HTEG_DISPLAY(I) \
{ param_def_t *q; pointer p= null, a= null;\
if ((I)&b001) a= hteg_hbox_node();\
p= hteg_list(); \
if ((I)&b010) a= hteg_hbox_node(); \
if ((I)&b100) q= hteg_param_list_node(); else q= hget_param_list_ref(HTEG8);\
hset_param_list(q); hdisplay(p,a,((I)&b010)!=0); hrestore_param_list();\
}
/*:185*//*192:*/
#line 2837 ".\\hint.w"

#define HTEG_IMAGE(I) \
{ pointer p;\
  p= get_node(image_node_size);  type(p)= whatsit_node; subtype(p)= image_node;\
  if (I&b001) {HTEG_STRETCH(image_shrink(p),image_shrink_order(p));\
               HTEG_STRETCH(image_stretch(p),image_stretch_order(p)); }\
  else { image_stretch(p)= image_shrink(p)= 0;image_stretch_order(p)= image_shrink_order(p)= normal;}\
  if (I&b010) {HTEG32(image_height(p)); HTEG32(image_width(p)); } \
  else image_width(p)= image_height(p)= 0;\
  HTEG16(image_no(p));RNG("Section number",image_no(p),3,max_section_no);  \
  tail_append(p);}
/*:192*/
#line 3885 ".\\hint.w"


/*81:*/
#line 1271 ".\\hint.w"

float32_t hteg_float32(void)
{union{float32_t d;uint32_t bits;}u;
HTEG32(u.bits);
return u.d;
}
/*:81*//*85:*/
#line 1330 ".\\hint.w"

scaled hteg_xdimen(uint8_t a)
{xdimen_t x;
switch(a)
{
case TAG(xdimen_kind,b000):return hget_xdimen_ref(HTEG8);
case TAG(xdimen_kind,b001):HTEG_XDIMEN(b001,x);break;
case TAG(xdimen_kind,b010):HTEG_XDIMEN(b010,x);break;
case TAG(xdimen_kind,b011):HTEG_XDIMEN(b011,x);break;
case TAG(xdimen_kind,b100):HTEG_XDIMEN(b100,x);break;
case TAG(xdimen_kind,b101):HTEG_XDIMEN(b101,x);break;
case TAG(xdimen_kind,b110):HTEG_XDIMEN(b110,x);break;
case TAG(xdimen_kind,b111):HTEG_XDIMEN(b111,x);break;
default:
x.w= 0;x.h= x.v= 0.0;
QUIT("Extent expected got [%s,%d]",NAME(a),INFO(a));
}
return x.w+x.h*hhsize+x.v*hvsize;
}

scaled hteg_xdimen_node(void)
{scaled x= 0;
/*71:*/
#line 1109 ".\\hint.w"

uint8_t a,z;
z= HTEG8,DBGTAG(z,hpos);
/*:71*/
#line 1352 ".\\hint.w"

if(KIND(z)==xdimen_kind)
x= hteg_xdimen(z);
else
QUIT("Extent expected at 0x%x got %s",node_pos,NAME(z));
/*72:*/
#line 1114 ".\\hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:72*/
#line 1357 ".\\hint.w"

return x;
}
/*:85*//*111:*/
#line 1557 ".\\hint.w"

pointer hteg_rule_node(void)
{pointer p= null;
/*71:*/
#line 1109 ".\\hint.w"

uint8_t a,z;
z= HTEG8,DBGTAG(z,hpos);
/*:71*/
#line 1560 ".\\hint.w"

if(KIND(z)==rule_kind){HTEG_RULE(INFO(z));}
else QUIT("Rule expected at 0x%x got %s",node_pos,NAME(z));
/*72:*/
#line 1114 ".\\hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:72*/
#line 1563 ".\\hint.w"

return p;
}
/*:111*//*121:*/
#line 1680 ".\\hint.w"

pointer hteg_glue_spec(void)
{pointer p= null;
uint8_t a,z;
if(hpos<=hstart)return null;
if(KIND(*(hpos-1))!=glue_kind)return null;
z= HTEG8,DBGTAG(z,hpos);
if(INFO(z)==b000)p= hget_glue_ref(HTEG8);
else
{HTEG_GLUE(INFO(z));}
/*72:*/
#line 1114 ".\\hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:72*/
#line 1690 ".\\hint.w"

return p;
}


pointer hteg_glue_node(void)
{pointer p= hteg_glue_spec();
if(p!=null)p= new_glue(p);
return p;
}
/*:121*//*127:*/
#line 1813 ".\\hint.w"

#if 0
void hteg_size_boundary(info_t info)
{uint32_t n;
if(info<2)return;
n= HTEG8;
if(n-1!=0x100-info)QUIT("Size boundary byte 0x%x with info value %d at "SIZE_F,
n,info,hpos-hstart);
}
#endif

uint32_t hteg_list_size(info_t info)
{uint32_t n;
if(info==1)return 0;
else if(info==2)n= HTEG8;
else if(info==3)HTEG16(n);
else if(info==4)HTEG24(n);
else if(info==5)HTEG32(n);
else QUIT("List info %d must be 1, 2, 3, 4, or 5",info);
return n;
}

#if 0
pointer hteg_node_list(uint32_t s)
{uint8_t*list_start= hpos-s;
pointer p;
push_nest();
needs_bs= false;
while(hpos> list_start)
hteg_content();
if(needs_bs)
QUIT("Unexpected trailing baseline node");
p= link(head);
pop_nest();
return p;
}
#endif

void hskip_list()
{uint8_t z;
uint32_t s;
if(!IS_LIST(*(hpos-1)))return;
z= HTEG8;
s= hteg_list_size(INFO(z));
hpos= hpos-(1+s+1+(INFO(z)-1)+1);
}

pointer hteg_list(void)
{uint8_t*list_start;
pointer p;
hskip_list();
list_start= hpos;
p= hget_list();
hpos= list_start;
return p;
}
/*:127*//*128:*/
#line 1878 ".\\hint.w"

#if 0
static int32_t hteg_integer_def(uint8_t z)
{if(INFO(z)==1){int8_t n= HTEG8;return n;}
else if(INFO(z)==2){int16_t n;HTEG16(n);return n;}
else if(INFO(z)==4){int32_t n;HTEG32(n);return n;}
else TAGERR(z);
return 0;
}

static param_def_t*hteg_param_list(uint8_t z)
{uint32_t s,t;
param_def_t*p= NULL;
uint8_t*list_start,*list_end;
list_end= hpos;
s= hteg_list_size(INFO(z));
hteg_size_boundary(INFO(z));
list_start= hpos-s;
if(list_start<=hstart)
QUIT("list start before stream start\n");
while(list_start<hpos)
{param_def_t*r;param_t*q;
/*71:*/
#line 1109 ".\\hint.w"

uint8_t a,z;
z= HTEG8,DBGTAG(z,hpos);
/*:71*/
#line 1900 ".\\hint.w"

ALLOCATE(r,1,param_def_t);
q= &(r->p);
q->k= KIND(z);
if(KIND(z)==int_kind)q->i= hteg_integer_def(a);
else if(KIND(a)==dimen_kind)HTEG32(q->d);
else if(KIND(a)==glue_kind){pointer p;HTEG_GLUE(INFO(z));q->g= p;}
else TAGERR(a);
q->n= HTEG8;
DBG(dbgtags,"Defining %s %d\n",definition_name[KIND(z)],q->n);
/*72:*/
#line 1114 ".\\hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:72*/
#line 1910 ".\\hint.w"

r->next= p;
p= r;
}
hteg_size_boundary(INFO(z));
t= hteg_list_size(INFO(z));
if(t!=s)
QUIT("List sizes at "SIZE_F" and "SIZE_F" do not match 0x%x != 0x%x",list_start-hstart,list_end-hstart,s,t);
return p;
}
#endif

static param_def_t*hteg_param_list_node(void)
{param_def_t*p;
uint8_t*list_start;
hskip_list();
list_start= hpos;
p= hget_param_list_node();
hpos= list_start;
return p;
}
/*:128*//*135:*/
#line 2032 ".\\hint.w"

pointer hteg_hbox_node(void)
{/*71:*/
#line 1109 ".\\hint.w"

uint8_t a,z;
z= HTEG8,DBGTAG(z,hpos);
/*:71*/
#line 2034 ".\\hint.w"

if(KIND(z)!=hbox_kind)QUIT("Hbox expected at 0x%x got %s",node_pos,NAME(z));
{
HTEG_BOX(INFO(z));
/*72:*/
#line 1114 ".\\hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:72*/
#line 2038 ".\\hint.w"

return p;
}
}
pointer hteg_vbox_node(void)
{/*71:*/
#line 1109 ".\\hint.w"

uint8_t a,z;
z= HTEG8,DBGTAG(z,hpos);
/*:71*/
#line 2043 ".\\hint.w"

if(KIND(z)!=vbox_kind)QUIT("Vbox expected at 0x%x got %s",node_pos,NAME(z));
{
HTEG_BOX(INFO(z));
/*72:*/
#line 1114 ".\\hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:72*/
#line 2047 ".\\hint.w"

type(p)= vlist_node;
return p;
}
}

/*:135*//*181:*/
#line 2709 ".\\hint.w"

void hteg_paragraph(info_t i,uint32_t offset)
{scaled x= 0;
param_def_t*q;
uint8_t*list_start,*par_start;
hskip_list();
list_start= hpos;
if(INFO(i)&b010)q= hteg_param_list_node();else q= hget_param_list_ref(HTEG8);
if(INFO(i)&b100)x= hteg_xdimen_node();else x= hget_xdimen_ref(HTEG8);
par_start= hpos;
hpos= list_start;
hget_paragraph(x,q,0);
hpos= par_start;
}
/*:181*/
#line 3887 ".\\hint.w"


/*73:*/
#line 1126 ".\\hint.w"

static void hteg_node(uint8_t z)
{switch(z)
{
/*94:*/
#line 1418 ".\\hint.w"

case TAG(glyph_kind,1):HTEG_GLYPH(1);break;
case TAG(glyph_kind,2):HTEG_GLYPH(2);break;
case TAG(glyph_kind,3):HTEG_GLYPH(3);break;
case TAG(glyph_kind,4):HTEG_GLYPH(4);break;
/*:94*//*97:*/
#line 1438 ".\\hint.w"

case TAG(penalty_kind,0):tail_append(new_penalty(hget_integer_ref(HTEG8)));break;
case TAG(penalty_kind,1):{tail_append(new_penalty(HTEG8));}break;
case TAG(penalty_kind,2):{int16_t n;HTEG16(n);RNG("Penalty",n,-20000,+20000);tail_append(new_penalty(n));}break;
/*:97*//*102:*/
#line 1483 ".\\hint.w"

case TAG(math_kind,b000):tail_append(hget_math_ref(HTEG8));break;
case TAG(math_kind,b100):HTEG_MATH(b100,m);break;
case TAG(math_kind,b010):HTEG_MATH(b010,m);break;
case TAG(math_kind,b101):HTEG_MATH(b101,m);break;
case TAG(math_kind,b011):HTEG_MATH(b011,m);break;
/*:102*//*109:*/
#line 1536 ".\\hint.w"

case TAG(rule_kind,b000):tail_append(hget_rule_ref(HTEG8));prev_depth= ignore_depth;break;
case TAG(rule_kind,b011):HTEG_RULE(b011);prev_depth= ignore_depth;break;
case TAG(rule_kind,b101):HTEG_RULE(b101);prev_depth= ignore_depth;break;
case TAG(rule_kind,b001):HTEG_RULE(b001);prev_depth= ignore_depth;break;
case TAG(rule_kind,b110):HTEG_RULE(b110);prev_depth= ignore_depth;break;
case TAG(rule_kind,b111):HTEG_RULE(b111);prev_depth= ignore_depth;break;
/*:109*//*117:*/
#line 1629 ".\\hint.w"

case TAG(glue_kind,b000):tail_append(new_glue(hget_glue_ref(HTEG8)));break;
case TAG(glue_kind,b001):{pointer p;HTEG_GLUE(b001);tail_append(new_glue(p));}break;
case TAG(glue_kind,b010):{pointer p;HTEG_GLUE(b010);tail_append(new_glue(p));}break;
case TAG(glue_kind,b011):{pointer p;HTEG_GLUE(b011);tail_append(new_glue(p));}break;
case TAG(glue_kind,b100):{pointer p;HTEG_GLUE(b100);tail_append(new_glue(p));}break;
case TAG(glue_kind,b101):{pointer p;HTEG_GLUE(b101);tail_append(new_glue(p));}break;
case TAG(glue_kind,b110):{pointer p;HTEG_GLUE(b110);tail_append(new_glue(p));}break;
case TAG(glue_kind,b111):{pointer p;HTEG_GLUE(b111);tail_append(new_glue(p));}break;
/*:117*//*133:*/
#line 1988 ".\\hint.w"

case TAG(hbox_kind,b000):{HTEG_BOX(b000);happend_to_vlist(p);}break;
case TAG(hbox_kind,b001):{HTEG_BOX(b001);happend_to_vlist(p);}break;
case TAG(hbox_kind,b010):{HTEG_BOX(b010);happend_to_vlist(p);}break;
case TAG(hbox_kind,b011):{HTEG_BOX(b011);happend_to_vlist(p);}break;
case TAG(hbox_kind,b100):{HTEG_BOX(b100);happend_to_vlist(p);}break;
case TAG(hbox_kind,b101):{HTEG_BOX(b101);happend_to_vlist(p);}break;
case TAG(hbox_kind,b110):{HTEG_BOX(b110);happend_to_vlist(p);}break;
case TAG(hbox_kind,b111):{HTEG_BOX(b111);happend_to_vlist(p);}break;
case TAG(vbox_kind,b000):{HTEG_BOX(b000);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b001):{HTEG_BOX(b001);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b010):{HTEG_BOX(b010);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b011):{HTEG_BOX(b011);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b100):{HTEG_BOX(b100);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b101):{HTEG_BOX(b101);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b110):{HTEG_BOX(b110);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b111):{HTEG_BOX(b111);type(p)= vlist_node;happend_to_vlist(p);}break;
/*:133*//*141:*/
#line 2120 ".\\hint.w"

case TAG(hset_kind,b000):{pointer p;HTEG_SET(b000);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(hset_kind,b001):{pointer p;HTEG_SET(b001);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(hset_kind,b010):{pointer p;HTEG_SET(b010);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(hset_kind,b011):{pointer p;HTEG_SET(b011);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(hset_kind,b100):{pointer p;HTEG_SET(b100);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(hset_kind,b101):{pointer p;HTEG_SET(b101);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(hset_kind,b110):{pointer p;HTEG_SET(b110);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(hset_kind,b111):{pointer p;HTEG_SET(b111);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;

case TAG(vset_kind,b000):{pointer p;HTEG_SET(b000);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(vset_kind,b001):{pointer p;HTEG_SET(b001);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(vset_kind,b010):{pointer p;HTEG_SET(b010);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(vset_kind,b011):{pointer p;HTEG_SET(b011);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(vset_kind,b100):{pointer p;HTEG_SET(b100);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(vset_kind,b101):{pointer p;HTEG_SET(b101);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(vset_kind,b110):{pointer p;HTEG_SET(b110);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(vset_kind,b111):{pointer p;HTEG_SET(b111);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
/*:141*//*146:*/
#line 2248 ".\\hint.w"

case TAG(hpack_kind,b000):{HTEG_PACK(b000);p= hpack(p,x,m);happend_to_vlist(p);}break;
case TAG(hpack_kind,b010):{HTEG_PACK(b010);p= hpack(p,x,m);happend_to_vlist(p);}break;
case TAG(hpack_kind,b100):{HTEG_PACK(b100);p= hpack(p,x,m);happend_to_vlist(p);}break;
case TAG(hpack_kind,b110):{HTEG_PACK(b110);p= hpack(p,x,m);happend_to_vlist(p);}break;

case TAG(vpack_kind,b000):{HTEG_PACK(b000);p= vpackage(p,x,m,d);happend_to_vlist(p);}break;
case TAG(vpack_kind,b010):{HTEG_PACK(b010);p= vpackage(p,x,m,d);happend_to_vlist(p);}break;
case TAG(vpack_kind,b100):{HTEG_PACK(b100);p= vpackage(p,x,m,d);happend_to_vlist(p);}break;
case TAG(vpack_kind,b110):{HTEG_PACK(b110);p= vpackage(p,x,m,d);happend_to_vlist(p);}break;
case TAG(vpack_kind,b001):{HTEG_PACK(b001);p= vpackage(p,x,m,d);happend_to_vlist(p);}break;
case TAG(vpack_kind,b011):{HTEG_PACK(b011);p= vpackage(p,x,m,d);happend_to_vlist(p);}break;
case TAG(vpack_kind,b101):{HTEG_PACK(b101);p= vpackage(p,x,m,d);happend_to_vlist(p);}break;
case TAG(vpack_kind,b111):{HTEG_PACK(b111);p= vpackage(p,x,m,d);happend_to_vlist(p);}break;
/*:146*//*152:*/
#line 2313 ".\\hint.w"

case TAG(kern_kind,b000):{HTEG_KERN(b000);}break;
case TAG(kern_kind,b001):{HTEG_KERN(b001);}break;
case TAG(kern_kind,b010):{HTEG_KERN(b010);}break;
case TAG(kern_kind,b011):{HTEG_KERN(b011);}break;
case TAG(kern_kind,b100):{HTEG_KERN(b100);}break;
case TAG(kern_kind,b101):{HTEG_KERN(b101);}break;
case TAG(kern_kind,b110):{HTEG_KERN(b110);}break;
case TAG(kern_kind,b111):{HTEG_KERN(b111);}break;
/*:152*//*158:*/
#line 2360 ".\\hint.w"

case TAG(leaders_kind,0):tail_append(hget_leaders_ref(HTEG8));break;
case TAG(leaders_kind,1):HTEG_LEADERS(1);break;
case TAG(leaders_kind,2):HTEG_LEADERS(2);break;
case TAG(leaders_kind,3):HTEG_LEADERS(3);break;
/*:158*//*163:*/
#line 2403 ".\\hint.w"

case TAG(baseline_kind,b000):{hget_baseline_ref(HTEG8,&cur_list.bs_field);needs_bs= true;}break;
case TAG(baseline_kind,b010):{HTEG_BASELINE(b010,cur_list.bs_field);needs_bs= true;}break;
case TAG(baseline_kind,b011):{HTEG_BASELINE(b011,cur_list.bs_field);needs_bs= true;}break;
case TAG(baseline_kind,b100):{HTEG_BASELINE(b100,cur_list.bs_field);needs_bs= true;}break;
case TAG(baseline_kind,b101):{HTEG_BASELINE(b101,cur_list.bs_field);needs_bs= true;}break;
case TAG(baseline_kind,b110):{HTEG_BASELINE(b110,cur_list.bs_field);needs_bs= true;}break;
case TAG(baseline_kind,b111):{HTEG_BASELINE(b111,cur_list.bs_field);needs_bs= true;}break;
/*:163*//*168:*/
#line 2457 ".\\hint.w"

case TAG(ligature_kind,0):tail_append(hget_ligature_ref(HTEG8));break;
case TAG(ligature_kind,1):HTEG_LIG(1);break;
case TAG(ligature_kind,2):HTEG_LIG(2);break;
case TAG(ligature_kind,3):HTEG_LIG(3);break;
case TAG(ligature_kind,4):HTEG_LIG(4);break;
case TAG(ligature_kind,5):HTEG_LIG(5);break;
case TAG(ligature_kind,6):HTEG_LIG(6);break;
case TAG(ligature_kind,7):HTEG_LIG(7);break;
/*:168*//*173:*/
#line 2509 ".\\hint.w"

case TAG(hyphen_kind,b000):tail_append(hget_hyphen_ref(HTEG8));break;
case TAG(hyphen_kind,b001):{HTEG_HYPHEN(b001);tail_append(p);}break;
case TAG(hyphen_kind,b010):{HTEG_HYPHEN(b010);tail_append(p);}break;
case TAG(hyphen_kind,b011):{HTEG_HYPHEN(b011);tail_append(p);}break;
case TAG(hyphen_kind,b100):{HTEG_HYPHEN(b100);tail_append(p);}break;
case TAG(hyphen_kind,b101):{HTEG_HYPHEN(b101);tail_append(p);}break;
case TAG(hyphen_kind,b110):{HTEG_HYPHEN(b110);tail_append(p);}break;
case TAG(hyphen_kind,b111):{HTEG_HYPHEN(b111);tail_append(p);}break;
/*:173*//*180:*/
#line 2702 ".\\hint.w"

case TAG(par_kind,b000):hteg_paragraph(b000,0);break;
case TAG(par_kind,b010):hteg_paragraph(b010,0);break;
case TAG(par_kind,b100):hteg_paragraph(b100,0);break;
case TAG(par_kind,b110):hteg_paragraph(b110,0);break;
/*:180*//*187:*/
#line 2769 ".\\hint.w"

case TAG(display_kind,b000):HTEG_DISPLAY(b000);break;
case TAG(display_kind,b001):HTEG_DISPLAY(b001);break;
case TAG(display_kind,b010):HTEG_DISPLAY(b010);break;
case TAG(display_kind,b100):HTEG_DISPLAY(b100);break;
case TAG(display_kind,b101):HTEG_DISPLAY(b101);break;
case TAG(display_kind,b110):HTEG_DISPLAY(b110);break;
/*:187*//*194:*/
#line 2857 ".\\hint.w"

case TAG(image_kind,b000):hget_image_ref(HTEG8);break;
case TAG(image_kind,b100):HTEG_IMAGE(b100);break;
case TAG(image_kind,b101):HTEG_IMAGE(b101);break;
case TAG(image_kind,b110):HTEG_IMAGE(b110);break;
case TAG(image_kind,b111):HTEG_IMAGE(b111);break;
/*:194*/
#line 1130 ".\\hint.w"

default:
TAGERR(z);
}
}

void hteg_content(void)
{/*71:*/
#line 1109 ".\\hint.w"

uint8_t a,z;
z= HTEG8,DBGTAG(z,hpos);
/*:71*/
#line 1137 ".\\hint.w"

node_pos= hpos-hstart;
hteg_node(z);
/*72:*/
#line 1114 ".\\hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:72*/
#line 1140 ".\\hint.w"

node_pos= hpos-hstart;
if(nest_ptr==0&&tail!=head&&(type(tail)==penalty_node||type(tail)==glue_node||type(tail)==kern_node))
store_map(tail,node_pos,0,0);
}
/*:73*//*175:*/
#line 2534 ".\\hint.w"

pointer hteg_hyphen_node(void)
{/*71:*/
#line 1109 ".\\hint.w"

uint8_t a,z;
z= HTEG8,DBGTAG(z,hpos);
/*:71*/
#line 2536 ".\\hint.w"

if(KIND(z)!=hyphen_kind||INFO(z)==b000)
QUIT("Hyphen expected at 0x%x got %s,%d",node_pos,NAME(z),INFO(z));
{
HTEG_HYPHEN(INFO(z));
/*72:*/
#line 1114 ".\\hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:72*/
#line 2541 ".\\hint.w"

return p;
}
}
/*:175*/
#line 3889 ".\\hint.w"

/*:252*/
