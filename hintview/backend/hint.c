/*399:*/
#line 8244 "hint.w"

#include "basetypes.h"
#include <string.h> 
#include <math.h> 
#include <zlib.h> 
#include "error.h"
#include "format.h"
#include "hint.h"
#include "hrender.h"
#include "rendernative.h"
#include "get.h"
#include "htex.h"

/*92:*/
#line 1585 "hint.w"

#define HGET_STRING(S) S= (char*)hpos;\
 while(hpos<hend && *hpos!=0) { RNG("String character",*hpos,0x20,0x7E); hpos++;}\
 hpos++;
/*:92*//*93:*/
#line 1597 "hint.w"

#define HGET_XDIMEN(I,X) \
{ if((I)&b100) HGET32((X).w); else (X).w= 0;\
  if((I)&b010) (X).h= hget_float32();  else (X).h= 0.0;\
  if((I)&b001) (X).v= hget_float32(); else (X).v= 0.0;\
}
/*:93*//*97:*/
#line 1700 "hint.w"

#define HGET_STRETCH(F,O) { Stch _st;  HGET32(_st.u); (O)= _st.u&3;  _st.u&= ~3; (F)= (scaled)(_st.f*ONE); }
/*:97*//*99:*/
#line 1711 "hint.w"

#define HGET_GLYPH(I) \
{uint8_t f; uint32_t c;\
  if (I==1) c= HGET8;\
  else if (I==2) HGET16(c);\
  else if (I==3) HGET24(c);\
  else if (I==4) HGET32(c);\
  f= HGET8; REF_RNG(font_kind,f);\
  tail_append(new_character(f,c));\
}
/*:99*//*107:*/
#line 1793 "hint.w"

#define HGET_RULE(I)\
pointer p= new_rule();\
if ((I)&b100) HGET32(height(p)); else height(p)= null_flag;\
if ((I)&b010) HGET32(depth(p)); else depth(p)= null_flag;\
if ((I)&b001) HGET32(width(p)); else width(p)= null_flag;
/*:107*//*113:*/
#line 1855 "hint.w"

#define HGET_GLUE(I) \
  p=  get_node(glue_spec_size); \
  if((I)!=b111) { if ((I)&b100) HGET32(width(p)); else width(p)= 0; }\
  if((I)&b010) HGET_STRETCH(stretch(p),stretch_order(p)) else stretch(p)= 0, stretch_order(p)= normal;\
  if((I)&b001) HGET_STRETCH(shrink(p),shrink_order(p)) else shrink(p)= 0, shrink_order(p)= normal;\
  if(I==b111) width(p)= hget_xdimen_node();
/*:113*//*123:*/
#line 2132 "hint.w"

#define HGET_BOX(I) \
p= new_null_box();\
HGET32(height(p));\
if ((I)&b001) HGET32(depth(p));\
HGET32(width(p));\
if ((I)&b010) HGET32(shift_amount(p));\
if ((I)&b100) {int8_t x; glue_set(p)= hget_float32();\
  x= HGET8;  glue_order(p)= x&0xF;\
  x= x>>4; glue_sign(p)= (x<0?shrinking:(x> 0?stretching:normal));}\
list_ptr(p)= hget_list_pointer();
/*:123*//*130:*/
#line 2256 "hint.w"

#define HGET_SET(I) \
 scaled x, st, sh; uint8_t sto, sho; \
 p= new_null_box();\
 HGET32(height(p)); if ((I)&b001) HGET32(depth(p)); HGET32(width(p));\
 if ((I)&b010) HGET32(shift_amount(p));\
 HGET_STRETCH(st,sto);   HGET_STRETCH(sh,sho);\
 if ((I)&b100) x=  hget_xdimen_node();  else x= hget_xdimen_ref(HGET8);\
 list_ptr(p)= hget_list_pointer();
/*:130*//*137:*/
#line 2416 "hint.w"

#define HGET_PACK(K,I) \
{ pointer p; scaled x, s= 0, d;  uint8_t m; \
 if ((I)&b001) m= additional; else m= exactly; \
 if ((I)&b010) HGET32(s);\
 if (K==vpack_kind) HGET32(d); \
 if ((I)&b100) x=  hget_xdimen_node();  else x= hget_xdimen_ref(HGET8);\
 p= hget_list_pointer(); \
 if (K==vpack_kind) { if (d<=MAX_DIMEN && d>=-MAX_DIMEN) p= vpackage(p,x,m,d); else p= vtop(p,x,m,d); } \
 else p= hpack(p,x,m);\
 shift_amount(p)= s;\
 happend_to_vlist(p);}
/*:137*//*142:*/
#line 2501 "hint.w"

#define HGET_KERN(I) \
pointer p; scaled x; \
if (((I)&b011)==0) x= hget_dimen_ref(HGET8);\
else if (((I)&b011)==1) x= hget_xdimen_ref(HGET8);\
else if (((I)&b011)==2) HGET32(x);\
else if (((I)&b011)==3) x= hget_xdimen_node();\
p= new_kern(x);\
if ((I)&b100) subtype(p)= explicit;\
tail_append(p);
/*:142*//*146:*/
#line 2552 "hint.w"

#define HGET_LEADERS(I) \
{pointer p;\
 if ((I)&b100)p= hget_glue_node(); else {p= spec2glue(zero_glue); incr(glue_ref_count(zero_glue));} \
subtype(p)= a_leaders+((I)&b011)-1;\
if (KIND(*hpos)==rule_kind) leader_ptr(p)= hget_rule_node(); \
else if (KIND(*hpos)==hbox_kind) leader_ptr(p)= hget_hbox_node(); \
else  leader_ptr(p)= hget_vbox_node();\
tail_append(p);}
/*:146*//*150:*/
#line 2598 "hint.w"

#define HGET_BASELINE(I) \
  cur_list.bs_pos= hpos-1; \
  if((I)&b001) HGET32(cur_lsl); else cur_lsl= 0; \
  if((I)&b100) cur_bs= hget_glue_spec(); else cur_bs= zero_glue; \
  if((I)&b010) cur_ls= hget_glue_spec(); else cur_ls= zero_glue;
/*:150*//*155:*/
#line 2652 "hint.w"

#define HGET_LIG(I) \
{pointer p,q;uint8_t f;\
f= HGET8;\
if ((I)==7) q= hget_list_pointer(); else q= hget_text_list(I);\
if (q==null) QUIT("Ligature with empty list");\
p= new_ligature(f, character(q), link(q)); tail_append(p);\
link(q)= null; flush_node_list(q);\
}
/*:155*//*159:*/
#line 2704 "hint.w"

#define HGET_DISC(I)\
  pointer p= new_disc(); \
  if ((I)&b100) {uint8_t r; r= HGET8; set_replace_count(p,r); \
                 if ((r&0x80)==0) set_auto_disc(p); }\
  else  set_auto_disc(p); \
  if ((I)&b010) pre_break(p)= hget_list_pointer(); \
  if ((I)&b001) post_break(p)= hget_list_pointer();
/*:159*//*165:*/
#line 2777 "hint.w"

#define HGET_PAR(I) \
{ scaled x= 0;\
  ParamDef *q;\
  if ((I)==b100) q= hget_param_list_ref(HGET8);\
  if ((I)&b100) x= hget_xdimen_node(); else x= hget_xdimen_ref(HGET8);\
  if ((I)&b010) q= hget_param_list_node(); \
  else if ((I)!=b100) q= hget_param_list_ref(HGET8);\
  hget_paragraph(x,0,q);\
}
/*:165*//*188:*/
#line 3258 "hint.w"

#define HGET_MATH(I) \
{ ParamDef *q; pointer p= null, a= null;\
if ((I)&b100) q= hget_param_list_node(); else q= hget_param_list_ref(HGET8);\
if ((I)&b010) a= hget_hbox_node(); \
p= hget_list_pointer(); \
if ((I)&b001) a= hget_hbox_node();\
hset_param_list(q); hdisplay(p,a,((I)&b010)!=0); hrestore_param_list();\
}
/*:188*//*194:*/
#line 3327 "hint.w"

#define HGET_ADJUST(I) \
{ pointer p;\
  p= get_node(small_node_size); type(p)= adjust_node; subtype(p)= normal;\
  adjust_ptr(p)= hget_list_pointer(); \
  tail_append(p);\
}
/*:194*//*196:*/
#line 3343 "hint.w"

#define HGET_TABLE(I) \
if(I&b010) ; else ;\
if ((I)&b001) ; else ;\
if ((I)&b100) hget_xdimen_node(); else hget_xdimen_ref(HGET8);\
hget_list_pointer();  \
hget_list_pointer(); 
/*:196*//*201:*/
#line 3430 "hint.w"

#define HGET_STREAM(I) \
{ ParamDef *q;  pointer p;\
  p= get_node(ins_node_size); type(p)= ins_node;\
  subtype(p)= HGET8;RNG("Stream",subtype(p),1,254); \
  if ((I)&b010) q= hget_param_list_node(); else q= hget_param_list_ref(HGET8); \
  ins_ptr(p)= hget_list_pointer(); \
  hset_stream_params(p,q); \
  tail_append(p);}
/*:201*//*205:*/
#line 3462 "hint.w"

#define HGET_IMAGE(I) \
{pointer p; float32_t a= 0.0; scaled w,h;\
p= get_node(image_node_size);  type(p)= whatsit_node; subtype(p)= image_node;\
HGET16(image_no(p));RNG("Section number",image_no(p),3,max_section_no);  \
if ((I)&b100) { a= hget_float32();\
  if ((I)==b111) {w= hget_xdimen_node();h= hget_xdimen_node();}\
  else if ((I)==b110) {h= hget_xdimen_ref(HGET8);w= hget_xdimen_node();}\
  else if ((I)==b101) {w= hget_xdimen_ref(HGET8);h= hget_xdimen_node();}\
  else  {w= hget_xdimen_ref(HGET8);h= hget_xdimen_ref(HGET8);}\
  if (a!=0.0) { if (h==0) h= round(w/a); else if (w==0) w= round(h*a);\
  else if (w> round(h*a)) w= round(h*a); else if (h> round(w/a)) h= round(w/a);}}\
else if((I)==b011) {HGET32(w);HGET32(h);} \
else if((I)==b010) { a= hget_float32(); HGET32(w); h= round(w/a);}\
else if((I)==b001){ a= hget_float32(); HGET32(h); w= round(h*a);}\
if (w==0 || h==0) QUIT("Incomplete dimensions in image %d",image_no(p));\
image_width(p)= w; image_height(p)= h;\
image_alt(p)= hget_list_pointer();\
tail_append(p);}
/*:205*//*213:*/
#line 3562 "hint.w"

#define HGET_LINK(I) \
{ pointer p;\
  p= get_node(link_node_size);  type(p)= whatsit_node;\
  if (I&b010) subtype(p)= start_link_node; else subtype(p)= end_link_node;\
  if (I&b001) HGET16(label_ref(as_label(p))); else label_ref(as_label(p))= HGET8; \
  if (I&b100) color_ref(as_color(p))= HGET8; else color_ref(as_color(p))= (I&b010)?1:0xFF;\
  RNG("label",label_ref(as_label(p)),0,max_ref[label_kind]);\
  if (color_ref(as_color(p))!=0xFF)\
    RNG("label color",color_ref(as_color(p)),0,max_ref[color_kind]);\
  tail_append(p);}
/*:213*/
#line 8257 "hint.w"

/*94:*/
#line 1605 "hint.w"

#define HTEG_XDIMEN(I,X) \
  if((I)&b001) (X).v= hteg_float32(); else (X).v= 0.0;\
  if((I)&b010) (X).h= hteg_float32();  else (X).h= 0.0;\
  if((I)&b100) HTEG32((X).w); else (X).w= 0;\
/*:94*//*98:*/
#line 1703 "hint.w"

#define HTEG_STRETCH(F,O) { Stch _st;  HTEG32(_st.u); (O)= _st.u&3;  _st.u&= ~3; (F)= (scaled)(_st.f*ONE); }
/*:98*//*100:*/
#line 1723 "hint.w"

#define HTEG_GLYPH(I) \
{uint8_t f; uint32_t c;\
  f= HTEG8; REF_RNG(font_kind,f);\
  if (I==1) c= HTEG8;\
  else if (I==2) HTEG16(c);\
  else if (I==3) HTEG24(c);\
  else if (I==4) HTEG32(c);\
  tail_append(new_character(f,c));\
}
/*:100*//*108:*/
#line 1802 "hint.w"

#define HTEG_RULE(I)\
pointer p= new_rule();\
if ((I)&b001) HTEG32(width(p)); else width(p)= null_flag;\
if ((I)&b010) HTEG32(depth(p)); else depth(p)= null_flag;\
if ((I)&b100) HTEG32(height(p)); else height(p)= null_flag;
/*:108*//*115:*/
#line 1868 "hint.w"

#define HTEG_GLUE(I) \
  p=  get_node(glue_spec_size); \
  if(I==b111) width(p)= hget_xdimen_node();\
  if((I)&b001) HTEG_STRETCH(shrink(p),shrink_order(p)) else shrink(p)= 0, shrink_order(p)= normal;\
  if((I)&b010) HTEG_STRETCH(stretch(p),stretch_order(p)) else stretch(p)= 0, stretch_order(p)= normal;\
  if((I)!=b111) { if ((I)&b100) HGET32(width(p)); else width(p)= 0; }
/*:115*//*124:*/
#line 2145 "hint.w"

#define HTEG_BOX(I) \
p= new_null_box();\
list_ptr(p)= hteg_list_pointer();\
if ((I)&b100) {int8_t x= HTEG8; glue_order(p)= x&0xF;\
   x= x>>4; glue_sign(p)= (x<0?shrinking:(x> 0?stretching:normal));\
   glue_set(p)= hteg_float32(); }\
if ((I)&b010) HTEG32(shift_amount(p));\
HTEG32(width(p));\
if ((I)&b001) HTEG32(depth(p));\
HTEG32(height(p));\
node_pos= hpos-hstart-1;
/*:124*//*131:*/
#line 2268 "hint.w"

#define HTEG_SET(I) \
  scaled x, st, sh; uint8_t sto, sho; \
  p= new_null_box();\
  list_ptr(p)= hteg_list_pointer();\
  if ((I)&b100) x= hteg_xdimen_node(); else x= hget_xdimen_ref(HTEG8);\
  HTEG_STRETCH(sh,sho);HTEG_STRETCH(st,sto);\
  if ((I)&b010) HTEG32(shift_amount(p)); \
  HTEG32(width(p));if ((I)&b001) HTEG32(depth(p));HTEG32(height(p)); \
  node_pos= hpos-hstart-1;
/*:131*//*138:*/
#line 2430 "hint.w"

#define HTEG_PACK(K,I) \
{ pointer p; scaled x, s, d;  uint8_t m; \
 p= hteg_list_pointer();\
 if ((I)&b100) x= hteg_xdimen_node();  else x= hget_xdimen_ref(HTEG8);\
 if (K==vpack_kind) HTEG32(d); \
 if ((I)&b010) HTEG32(s);\
 if ((I)&b001) m= additional; else m= exactly; \
 node_pos= hpos-hstart-1;\
 if (K==vpack_kind)  { if (d<=MAX_DIMEN && d>=-MAX_DIMEN) p= vpackage(p,x,m,d); else p= vtop(p,x,m,d); } \
 else p= hpack(p,x,m);\
 hprepend_to_vlist(p);}
/*:138*//*143:*/
#line 2514 "hint.w"

#define HTEG_KERN(I) \
pointer p; scaled x; \
if (((I)&b011)==0) x= hget_dimen_ref(HTEG8);\
else if (((I)&b011)==1) x= hget_xdimen_ref(HTEG8);\
else if (((I)&b011)==2) HTEG32(x);\
else if (((I)&b011)==3) x= hteg_xdimen_node();\
p= new_kern(x);\
if ((I)&b100) subtype(p)= explicit;\
tail_append(p);
/*:143*//*147:*/
#line 2563 "hint.w"

#define HTEG_LEADERS(I) \
{pointer p,q;\
if (KIND(*(hpos-1))==rule_kind) q= hteg_rule_node(); \
else if (KIND(*(hpos-1))==hbox_kind) q= hteg_hbox_node(); \
else  q= hteg_vbox_node();\
if ((I)&b100) p= hteg_glue_node(); else {p= spec2glue(zero_glue); incr(glue_ref_count(zero_glue));} \
leader_ptr(p)= q;subtype(p)= a_leaders+((I)&b011)-1;\
tail_append(p);}
/*:147*//*151:*/
#line 2606 "hint.w"

#define HTEG_BASELINE(I) \
  if((I)&b010) cur_ls= hteg_glue_spec(); else cur_ls= zero_glue; \
  if((I)&b100) cur_bs= hteg_glue_spec(); else cur_bs= zero_glue; \
  if((I)&b001) HTEG32(cur_lsl); else cur_lsl= 0; \
  cur_list.bs_pos= hpos-1;
/*:151*//*156:*/
#line 2663 "hint.w"

#define HTEG_LIG(I) \
{pointer p,q;\
if ((I)==7) q= hteg_list_pointer();\
else {uint8_t *t= hpos; hpos= t-I; q= hget_text_list(I); hpos= t-I;}\
if (q==null) QUIT("Ligature with empty list");\
p= new_ligature(0, character(q), link(q)); tail_append(p);\
link(q)= null; flush_node_list(q);\
font(lig_char(p))= HTEG8;\
}
/*:156*//*160:*/
#line 2714 "hint.w"

#define HTEG_DISC(I)\
  pointer p= new_disc(); \
  if ((I)&b001) post_break(p)= hteg_list_pointer(); \
  if ((I)&b010) pre_break(p)= hteg_list_pointer(); \
  if ((I)&b100) {uint8_t r; r= HTEG8; set_replace_count(p,r); \
                 if ((r&0x80)==0) set_auto_disc(p); }\
  else  set_auto_disc(p);
/*:160*//*189:*/
#line 3269 "hint.w"

#define HTEG_MATH(I) \
{ ParamDef *q; pointer p= null, a= null;\
if ((I)&b001) a= hteg_hbox_node();\
p= hteg_list_pointer(); \
if ((I)&b010) a= hteg_hbox_node(); \
if ((I)&b100) q= hteg_param_list_node(); else q= hget_param_list_ref(HTEG8);\
hset_param_list(q); hdisplay(p,a,((I)&b010)!=0); hrestore_param_list();\
}
/*:189*//*197:*/
#line 3352 "hint.w"

#define HTEG_TABLE(I) \
if(I&b010) ; else ;\
if ((I)&b001) ; else ;\
hteg_list_pointer();   \
hteg_list_pointer();  \
if ((I)&b100) hteg_xdimen_node(); else hget_xdimen_ref(HTEG8);
/*:197*//*202:*/
#line 3441 "hint.w"

#define HTEG_STREAM(I) \
{pointer p= get_node(ins_node_size); type(p)= ins_node;\
 ins_ptr(p)= hteg_list_pointer();\
 if ((I)&b010) {ParamDef *q= hteg_param_list_node();  hset_stream_params(p,q);}\
 else {ParamDef *q= hget_param_list_ref(HTEG8);  hset_stream_params(p,q);}\
 subtype(p)= HTEG8;RNG("Stream",subtype(p),1,254);\
 tail_append(p);}
/*:202*//*206:*/
#line 3483 "hint.w"

#define HTEG_IMAGE(I) \
{ pointer p; float32_t a= 0.0; scaled w,h;\
p= get_node(image_node_size);  type(p)= whatsit_node; subtype(p)= image_node;\
image_alt(p)= hteg_list_pointer();\
if ((I)&b100) {\
  if ((I)==b111) {h= hteg_xdimen_node();w= hteg_xdimen_node();}\
  else if ((I)==b110) {w= hteg_xdimen_node();h= hget_xdimen_ref(HTEG8);}\
  else if ((I)==b101) {h= hteg_xdimen_node();w= hget_xdimen_ref(HTEG8);}\
  else  {h= hget_xdimen_ref(HTEG8);w= hget_xdimen_ref(HTEG8);}\
  a= hteg_float32();\
  if (a!=0.0) { if (h==0) h= round(w/a); else if (w==0) w= round(h*a);\
  else if (w> round(h*a)) w= round(h*a); else if (h> round(w/a)) h= round(w/a); }}\
else if((I)==b011) {HTEG32(h);HTEG32(w);} \
else if((I)==b010) {  HTEG32(w); a= hteg_float32(); h= round(w/a);}\
else if((I)==b001){ HTEG32(h); a= hteg_float32();  w= round(h*a);}\
HTEG16(image_no(p));RNG("Section number",image_no(p),3,max_section_no);  \
if (w==0 || h==0) QUIT("Incomplete dimensions in image %d",image_no(p));\
image_width(p)= w; image_height(p)= h;\
tail_append(p);}
/*:206*//*214:*/
#line 3575 "hint.w"

#define HTEG_LINK(I) \
{ pointer p;\
  p= get_node(link_node_size);  type(p)= whatsit_node;\
  if (I&b010) subtype(p)= start_link_node; else subtype(p)= end_link_node;\
  if (I&b100) color_ref(as_color(p))= HTEG8; else color_ref(as_color(p))= (I&b010)?1:0xFF;\
  if (I&b001) HTEG16(label_ref(as_label(p))); else label_ref(as_label(p))= HTEG8; \
  RNG("label",label_ref(as_label(p)),0,max_ref[label_kind]);\
  if (color_ref(as_color(p))!=0xFF)\
    RNG("label color",color_ref(as_color(p)),0,max_ref[color_kind]);\
  tail_append(p);}
/*:214*/
#line 8258 "hint.w"


/*21:*/
#line 501 "hint.w"

typedef struct{pointer bs,ls;scaled lsl;}BaselineSkip;
/*:21*//*28:*/
#line 611 "hint.w"

typedef struct{
char*n;
uint16_t m,q;
scaled s;
pointer g;
pointer h;
pointer p[MAX_FONT_PARAMS+1];
}FontDef;
extern FontDef*font_def;
/*:28*//*37:*/
#line 716 "hint.w"

typedef struct{
uint8_t n,k;
int32_t v;
}Param;

typedef struct ParamDef{
struct ParamDef*next;
Param p;}ParamDef;
/*:37*/
#line 8260 "hint.w"


/*2:*/
#line 322 "hint.w"

pointer*pointer_def[32]= {NULL};
/*:2*//*6:*/
#line 375 "hint.w"

int32_t*integer_def;
/*:6*//*10:*/
#line 405 "hint.w"

scaled*dimen_def;
/*:10*//*14:*/
#line 435 "hint.w"

Xdimen*xdimen_def;
/*:14*//*22:*/
#line 505 "hint.w"

BaselineSkip*baseline_def= NULL;
/*:22*//*29:*/
#line 623 "hint.w"

FontDef*font_def;
/*:29*//*38:*/
#line 728 "hint.w"

ParamDef**param_def;
/*:38*//*45:*/
#line 881 "hint.w"

typedef struct{
uint8_t pg;
uint32_t f,t;
}RangeDef;
RangeDef*range_def;
/*:45*//*50:*/
#line 938 "hint.w"

Stream*streams;
/*:50*//*53:*/
#line 952 "hint.w"

typedef struct{
Xdimen x;
int f;
int p,n,r;
pointer b,a;
Xdimen w;
pointer g;
pointer h;
}StreamDef;
/*:53*//*57:*/
#line 1025 "hint.w"

typedef struct{
char*n;
Dimen d;
pointer g;
uint8_t p;
uint32_t t;
Xdimen v,h;
StreamDef*s;
}PageDef;
PageDef*page_def;
PageDef*cur_page;
/*:57*//*65:*/
#line 1160 "hint.w"

hint_Outline*hint_outlines= NULL;
int outline_no= -1;
/*:65*//*73:*/
#line 1253 "hint.w"

ColorSet*color_def= NULL;
static bool first_color= true;
/*:73*//*178:*/
#line 3098 "hint.w"

static ParamDef*line_break_params= NULL;
/*:178*//*224:*/
#line 3886 "hint.w"

static scaled page_height;
static scaled top_so_far[8];
/*:224*//*239:*/
#line 4164 "hint.w"

static uint32_t map[0x10000];
/*:239*//*244:*/
#line 4230 "hint.w"

#define MAX_PAGE_POS (1<<3) 

uint64_t page_loc[MAX_PAGE_POS];
int cur_loc;
static int lo_loc,hi_loc;
/*:244*//*261:*/
#line 4628 "hint.w"

scaled hvsize,hhsize;
/*:261*//*263:*/
#line 4656 "hint.w"

int page_v,page_h,offset_v,offset_h;
/*:263*//*320:*/
#line 5918 "hint.w"

hint_Link*hint_links= NULL;
int max_link= -1;
/*:320*//*386:*/
#line 7939 "hint.w"

jmp_buf hint_error_exit;
char hint_error_string[MAX_HINT_ERROR];
/*:386*/
#line 8262 "hint.w"

/*3:*/
#line 327 "hint.w"

static void hget_font_def(uint8_t a,uint8_t n);
static int32_t hget_integer_def(uint8_t a);
static scaled hget_dimen_def(uint8_t a);
static pointer hget_glue_def(uint8_t a);
static void hget_baseline_def(uint8_t a,uint8_t n);
static ParamDef*hget_param_list(uint8_t a);
static void hget_range_def(uint8_t a,uint8_t pg);
static void hget_page_def(uint8_t a,uint8_t n);
static void hget_outline_or_label_def(Info i,int n);
static void hget_unknown_def(void);
static void hget_font_metrics(void);
static void hget_color_def(uint8_t a,int n);
static pointer hget_definition(uint8_t a);
static int hget_label_ref(void);
static int hget_link_color(void);
/*:3*//*27:*/
#line 592 "hint.w"

static pointer hprepend_to_vlist(pointer b);
/*:27*//*36:*/
#line 704 "hint.w"

static pointer hget_glue_spec(void);
static pointer hget_disc_node(void);
/*:36*//*85:*/
#line 1478 "hint.w"

static void tag_mismatch(uint8_t a,uint8_t z,uint32_t a_pos,uint32_t z_pos);
/*:85*//*114:*/
#line 1864 "hint.w"

static scaled hget_xdimen_node(void);
/*:114*//*125:*/
#line 2161 "hint.w"

static pointer hget_list_pointer(void);
static pointer hteg_list_pointer(void);
/*:125*//*132:*/
#line 2279 "hint.w"

static scaled hget_xdimen_node(void);
/*:132*/
#line 8263 "hint.w"

/*35:*/
#line 697 "hint.w"

extern uint16_t hglyph_section(uint8_t f);
extern int32_t font_at_size(uint8_t f);
/*:35*/
#line 8264 "hint.w"

/*9:*/
#line 388 "hint.w"

static int32_t hget_integer_def(uint8_t a)
{if(INFO(a)==1){int8_t n= HGET8;return n;}
else if(INFO(a)==2){int16_t n;HGET16(n);return n;}
else if(INFO(a)==4){int32_t n;HGET32(n);return n;}
else TAGERR(a);
return 0;
}

static int32_t hget_integer_ref(uint8_t n)
{REF_RNG(int_kind,n);
return integer_def[n];
}
/*:9*//*17:*/
#line 446 "hint.w"

static scaled xdimen(Xdimen*x)
{return round(x->w+(double)x->h*(double)hhsize+(double)x->v*(double)hvsize);
}
static scaled hget_xdimen_ref(uint8_t n)
{REF_RNG(xdimen_kind,n);
return xdimen(xdimen_def+n);
}
/*:17*//*19:*/
#line 466 "hint.w"


static pointer hget_glue_ref(uint8_t n)
{REF_RNG(glue_kind,n);
return pointer_def[glue_kind][n];
}

static pointer hget_glue_def(uint8_t a)
{pointer p;
if(INFO(a)==b000)
{p= hget_glue_ref(HGET8);
add_glue_ref(p);
}
else
{HGET_GLUE(INFO(a));}
return p;
}

pointer hget_param_glue(uint8_t n)
{REF_RNG(glue_kind,n);
return new_glue(pointer_def[glue_kind][n]);
}
/*:19*//*32:*/
#line 636 "hint.w"

static void hget_font_def(uint8_t a,uint8_t n)
{char*t;
FontDef*f= font_def+n;
HGET_STRING(t);f->n= strdup(t);
DBG(DBGDEF,"Font %d: %s\n",n,t);
HGET32(f->s);RNG("Font size",f->s,1,0x7fffffff);
HGET16(f->m);RNG("Font metrics",f->m,3,max_section_no);
HGET16(f->q);RNG("Font glyphs",f->q,3,max_section_no);
f->g= hget_glue_spec();
f->h= hget_disc_node();
DBG(DBGDEF,"Start font parameters\n");
while(KIND(*hpos)!=font_kind)
{Kind k;
uint8_t n;
/*82:*/
#line 1456 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:82*/
#line 651 "hint.w"

k= KIND(a);
n= HGET8;
DBG(DBGDEF,"Reading font parameter %d: %s\n",n,definition_name[k]);
if(k!=penalty_kind&&k!=kern_kind&&k!=ligature_kind&&
k!=disc_kind&&k!=glue_kind&&k!=language_kind&&k!=rule_kind&&k!=image_kind)
QUIT("Font parameter %d has invalid type %s",n,content_name[n]);
RNG("Font parameter",n,0,MAX_FONT_PARAMS);
f->p[n]= hget_definition(a);
/*83:*/
#line 1461 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:83*/
#line 660 "hint.w"

}
DBG(DBGDEF,"End font definition\n");
}
/*:32*//*33:*/
#line 669 "hint.w"

static void hget_font_metrics(void)
{int i;
for(i= 0;i<=max_ref[font_kind];i++)
if(font_def[i].m!=0)
{int s;
hget_section(font_def[i].m);
s= font_def[i].s;
if(s==0)s= -1000;
read_font_info(i,font_def[i].n,s);
font_def[i].s= font_size[i];
}
}
/*:33*//*41:*/
#line 745 "hint.w"

static void free_param_list(ParamDef*p)
{while(p!=NULL)
{ParamDef*q= p;
p= p->next;
free(q);
}
}
/*:41*//*42:*/
#line 757 "hint.w"

static ParamDef*hget_param_list(uint8_t a)
{uint32_t s,t;
ParamDef*p= NULL;
uint8_t*list_start,*list_end;
list_start= hpos;
s= hget_list_size(INFO(a));
hget_size_boundary(INFO(a));
list_end= hpos+s;
if(list_end>=hend)
QUIT("list end after before stream end\n");
while(hpos<list_end)
{ParamDef*r;Param*q;
/*82:*/
#line 1456 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:82*/
#line 770 "hint.w"

ALLOCATE(r,1,ParamDef);
q= &(r->p);
q->n= HGET8;
q->k= KIND(a);
DBG(DBGTAGS,"Defining %s %d\n",definition_name[KIND(a)],q->n);
if(KIND(a)==int_kind)q->v= hget_integer_def(a);
else if(KIND(a)==dimen_kind)q->v= hget_dimen_def(a);
else if(KIND(a)==glue_kind)q->v= hget_glue_def(a);
else TAGERR(a);
/*83:*/
#line 1461 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:83*/
#line 780 "hint.w"

r->next= p;
p= r;
}
hget_size_boundary(INFO(a));
t= hget_list_size(INFO(a));
if(t!=s)
QUIT("List sizes at "SIZE_F" and "SIZE_F" do not match 0x%x != 0x%x",list_start-hstart,list_end-hstart,s,t);
return p;
}

ParamDef*hget_param_list_node(void)
{if(KIND(*hpos)!=param_kind)return NULL;
else
{ParamDef*p;
/*82:*/
#line 1456 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:82*/
#line 795 "hint.w"

p= hget_param_list(a);
/*83:*/
#line 1461 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:83*/
#line 797 "hint.w"

return p;
}
}

ParamDef*hget_param_list_ref(uint8_t n)
{REF_RNG(param_kind,n);
return param_def[n];
}
/*:42*//*43:*/
#line 832 "hint.w"

#define MAX_SAVE 100
#define SAVE_BOUNDARY 0xFF
static Param par_save[MAX_SAVE];
static int par_save_ptr= 0;

static void hset_param(uint8_t k,uint8_t n,int32_t v)
{Param*q;
if(par_save_ptr>=MAX_SAVE)QUIT("Parameter save stack overflow");
q= &(par_save[par_save_ptr++]);
q->k= k;
q->n= n;
if(q->k==int_kind)
{q->v= integer_def[q->n];integer_def[q->n]= v;}
else if(q->k==dimen_kind)
{q->v= dimen_def[q->n];dimen_def[q->n]= (scaled)v;}
else if(q->k==glue_kind)
{q->v= pointer_def[glue_kind][q->n];pointer_def[glue_kind][q->n]= (pointer)v;}
}

void hset_param_list(ParamDef*p)
{hset_param(SAVE_BOUNDARY,0,0);
while(p!=NULL)
{hset_param(p->p.k,p->p.n,p->p.v);
p= p->next;
}
}

void hrestore_param_list(void)
{
while(par_save_ptr> 0)
{Param*q;
q= &(par_save[--par_save_ptr]);
if(q->k==SAVE_BOUNDARY)return;
if(q->k==int_kind)
{integer_def[q->n]= q->v;}
else if(q->k==dimen_kind)
{dimen_def[q->n]= (scaled)q->v;}
else if(q->k==glue_kind)
{pointer_def[glue_kind][q->n]= (pointer)q->v;}
}
QUIT("Parameter save stack flow");
}
/*:43*//*48:*/
#line 897 "hint.w"

static void hget_range_def(uint8_t a,uint8_t pg)
{uint32_t f,t;
max_range++;
REF_RNG(page_kind,pg);
REF_RNG(range_kind,max_range);
if(INFO(a)&b100)
{if(INFO(a)&b001)HGET32(f);else HGET16(f);}
else f= 0;
if(INFO(a)&b010)
{if(INFO(a)&b001)HGET32(t);else HGET16(t);}
else t= HINT_NO_POS;
range_def[max_range].pg= pg;
range_def[max_range].f= f;
range_def[max_range].t= t;
DBG(DBGRANGE,"Range *%d from 0x%x\n",pg,f);
DBG(DBGRANGE,"Range *%d to 0x%x\n",pg,t);
}
#if 0

static uint8_t hget_page_ref(uint32_t pos)
{int i;
for(i= 1;i<=max_ref[range_kind];i++)
if(range_def[i].f<=pos&&pos<range_def[i].t)return range_def[i].pg;
return 0;
}
#endif
/*:48*//*54:*/
#line 969 "hint.w"

static void hget_xdimen_def_node(Xdimen*x);

static bool hget_stream_def(StreamDef*s)
{if(KIND(*hpos)!=stream_kind||!(INFO(*hpos)&b100))
return false;
else
{uint8_t n;
/*82:*/
#line 1456 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:82*/
#line 977 "hint.w"

DBG(DBGDEF,"Defining stream %d at "SIZE_F"\n",*hpos,hpos-hstart-1);
n= HGET8;REF_RNG(stream_kind,n);
s= s+n;
if(n> 0)
{if(INFO(a)==b100)/*55:*/
#line 1000 "hint.w"

{DBG(DBGDEF,"Defining normal stream %d at "SIZE_F"\n",*(hpos-1),hpos-hstart-2);
hget_xdimen_def_node(&(s->x));
HGET16(s->f);RNG("magnification factor",s->f,0,1000);
s->p= HGET8;if(s->p!=255)REF_RNG(stream_kind,s->p);
s->n= HGET8;if(s->n!=255)REF_RNG(stream_kind,s->n);
HGET16(s->r);RNG("split ratio",s->r,0,1000);
}
/*:55*/
#line 982 "hint.w"

else if(INFO(a)==b101)QUIT("first stream not yet implemented");
else if(INFO(a)==b110)QUIT("last stream not yet implemented");
else if(INFO(a)==b111)QUIT("top stream not yet implemented");
s->b= hget_list_pointer();
hget_xdimen_def_node(&(s->w));
s->g= hget_glue_spec();
s->a= hget_list_pointer();
s->h= hget_glue_spec();
}
/*83:*/
#line 1461 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:83*/
#line 992 "hint.w"

return true;
}
}
/*:54*//*61:*/
#line 1069 "hint.w"


static void hset_cur_page(void)
{int i;
cur_page= &(page_def[0]);
for(i= 1;i<=max_ref[page_kind];i++)
if(page_def[i].p>=cur_page->p)
cur_page= &(page_def[i]);
}

static void hskip_list(void);
static void hget_page_def(uint8_t a,uint8_t i)
{char*n;
cur_page= &(page_def[i]);
ALLOCATE(cur_page->s,max_ref[stream_kind]+1,StreamDef);
HGET_STRING(n);cur_page->n= strdup(n);
cur_page->p= HGET8;
cur_page->g= hget_glue_spec();
HGET32(cur_page->d);
hget_xdimen_def_node(&(cur_page->v));
hget_xdimen_def_node(&(cur_page->h));
cur_page->t= hpos-hstart;
hskip_list();
while(hget_stream_def(cur_page->s))continue;
}
/*:61*//*76:*/
#line 1270 "hint.w"

void hset_default_colors(void)
{int i;
for(i= 0;i<=MAX_COLOR_DEFAULT;i++)
memcpy(color_def+i,color_defaults+i,sizeof(ColorSet));
}
/*:76*//*78:*/
#line 1351 "hint.w"

static pointer hget_ligature_ref(uint8_t n)
{REF_RNG(ligature_kind,n);
return copy_node_list(pointer_def[ligature_kind][n]);
}

static pointer hget_rule_ref(uint8_t n)
{REF_RNG(rule_kind,n);
return copy_node_list(pointer_def[rule_kind][n]);
}

static pointer hget_image_ref(uint16_t n)
{REF_RNG(image_kind,n);
return copy_node_list(pointer_def[image_kind][n]);
}

static pointer hget_color_ref(uint8_t n)
{pointer p;
p= get_node(color_node_size);
type(p)= whatsit_node;
if(n==0xFF)subtype(p)= end_color_node;
else
{subtype(p)= color_node;REF_RNG(color_kind,n);
}
color_ref(p)= n;
return p;
}


static pointer hget_hyphen_ref(uint8_t n)
{REF_RNG(disc_kind,n);
return copy_node_list(pointer_def[disc_kind][n]);
}

static pointer hget_leaders_ref(uint8_t n)
{REF_RNG(leaders_kind,n);
return copy_node_list(pointer_def[leaders_kind][n]);
}
/*:78*//*84:*/
#line 1471 "hint.w"

static void tag_mismatch(uint8_t a,uint8_t z,uint32_t a_pos,uint32_t z_pos)
{QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),a_pos,z_pos);
}
/*:84*//*95:*/
#line 1612 "hint.w"


static void hget_xdimen_def(Info i,Xdimen*x)
{switch(i)
{
case b000:
{int n= HGET8;
REF_RNG(xdimen_kind,n);
x->w= xdimen_def[n].w;
x->h= xdimen_def[n].h;
x->v= xdimen_def[n].v;
break;
}
case b001:HGET_XDIMEN(b001,*x);break;
case b010:HGET_XDIMEN(b010,*x);break;
case b011:HGET_XDIMEN(b011,*x);break;
case b100:HGET_XDIMEN(b100,*x);break;
case b101:HGET_XDIMEN(b101,*x);break;
case b110:HGET_XDIMEN(b110,*x);break;
case b111:HGET_XDIMEN(b111,*x);break;
default:
x->w= 0;x->h= x->v= 0.0;
}
}
static scaled hget_xdimen(Info i)
{Xdimen x;
hget_xdimen_def(i,&x);
return xdimen(&x);
}

static void tag_expected(uint8_t b,uint8_t a,uint32_t a_pos)
{QUIT("%s expected at 0x%x got [%s,%d]",NAME(b),a_pos,NAME(a),INFO(a));
}

static scaled hget_xdimen_node(void)
{scaled x= 0;
/*82:*/
#line 1456 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:82*/
#line 1648 "hint.w"

if(KIND(a)==xdimen_kind)
x= hget_xdimen(INFO(a));
else tag_expected(TAG(xdimen_kind,0),a,node_pos);
/*83:*/
#line 1461 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:83*/
#line 1652 "hint.w"

return x;
}

static void hget_xdimen_def_node(Xdimen*x)
{/*82:*/
#line 1456 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:82*/
#line 1657 "hint.w"

if(KIND(a)==xdimen_kind)
hget_xdimen_def(INFO(a),x);
else tag_expected(TAG(xdimen_kind,0),a,node_pos);
/*83:*/
#line 1461 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:83*/
#line 1661 "hint.w"

}
/*:95*//*96:*/
#line 1665 "hint.w"

scaled hteg_xdimen(uint8_t a)
{Xdimen x;
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
tag_expected(TAG(xdimen_kind,0),a,node_pos);
}
return xdimen(&x);
}

scaled hteg_xdimen_node(void)
{scaled x= 0;
/*88:*/
#line 1531 "hint.w"

uint8_t a,z;
z= HTEG8;DBGTAG(z,hpos);
/*:88*/
#line 1687 "hint.w"

if(KIND(z)==xdimen_kind)
x= hteg_xdimen(z);
else
tag_expected(TAG(xdimen_kind,0),z,node_pos);
/*89:*/
#line 1536 "hint.w"

a= HTEG8;DBGTAG(a,hpos);
if(z!=a)tag_mismatch(a,z,hpos-hstart,node_pos);
/*:89*/
#line 1692 "hint.w"

return x;
}
/*:96*//*112:*/
#line 1840 "hint.w"

static pointer hteg_rule_node(void)
{pointer q= null;
/*88:*/
#line 1531 "hint.w"

uint8_t a,z;
z= HTEG8;DBGTAG(z,hpos);
/*:88*/
#line 1843 "hint.w"

if(KIND(z)==rule_kind){HTEG_RULE(INFO(z));q= p;}
else tag_expected(TAG(rule_kind,0),z,node_pos);
/*89:*/
#line 1536 "hint.w"

a= HTEG8;DBGTAG(a,hpos);
if(z!=a)tag_mismatch(a,z,hpos-hstart,node_pos);
/*:89*/
#line 1846 "hint.w"

return q;
}
/*:112*//*118:*/
#line 1909 "hint.w"

static pointer hget_glue_spec(void)
{pointer p= null;
uint8_t a,z;
if(hpos>=hend||KIND(*hpos)!=glue_kind)
{p= zero_glue;incr(glue_ref_count(p));}
else
{node_pos= hpos-hstart;
HGETTAG(a);
if(INFO(a)==b000)
{p= hget_glue_ref(HGET8);incr(glue_ref_count(p));}
else
{HGET_GLUE(INFO(a));}
/*83:*/
#line 1461 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:83*/
#line 1922 "hint.w"

}
return p;
}

static pointer spec2glue(pointer q)
{pointer p;
p= get_node(small_node_size);type(p)= glue_node;subtype(p)= normal;
leader_ptr(p)= null;glue_ptr(p)= q;
return p;
}

static pointer hget_glue_node(void)
{return spec2glue(hget_glue_spec());
}
/*:118*//*119:*/
#line 1939 "hint.w"

static pointer hteg_glue_spec(void)
{pointer p= null;
uint8_t a,z;
if(hpos<=hstart)return null;
if(KIND(*(hpos-1))!=glue_kind)return null;
z= HTEG8,DBGTAG(z,hpos);
if(INFO(z)==b000)p= hget_glue_ref(HTEG8);
else
{HTEG_GLUE(INFO(z));}
/*89:*/
#line 1536 "hint.w"

a= HTEG8;DBGTAG(a,hpos);
if(z!=a)tag_mismatch(a,z,hpos-hstart,node_pos);
/*:89*/
#line 1949 "hint.w"

return p;
}


static pointer hteg_glue_node(void)
{pointer p= hteg_glue_spec();
if(p!=null)return spec2glue(p);
else return new_glue(zero_glue);
}
/*:119*//*120:*/
#line 1974 "hint.w"

static pointer hget_node_list(uint32_t s)
{uint8_t*list_end= hpos+s;
pointer p;
push_nest();
cur_list.bs_pos= NULL;
while(hpos<list_end)
hget_content();
if(needs_bs)
QUIT("Unexpected trailing baseline node");
p= link(head);
pop_nest();
return p;
}

static pointer hget_text_list(uint32_t s);
static pointer hget_list_pointer(void)
{pointer p= null;
uint32_t s,t;
if(KIND(*hpos)==list_kind)
{/*82:*/
#line 1456 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:82*/
#line 1994 "hint.w"

if((INFO(a)&b011)==0)
HGET8;
else
{s= hget_list_size(INFO(a));
hget_size_boundary(INFO(a));
if((INFO(a)&b100)==0)
p= hget_node_list(s);
else
p= hget_text_list(s);
hget_size_boundary(INFO(a));
t= hget_list_size(INFO(a));
if(t!=s)
QUIT("List sizes at 0x%x and "SIZE_F" do not match 0x%x != 0x%x",
node_pos+1,hpos-hstart-s-1,s,t);
}
/*83:*/
#line 1461 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:83*/
#line 2010 "hint.w"

}
return p;
}
/*:120*//*121:*/
#line 2021 "hint.w"


static void hskip_list(void)
{if(KIND(*hpos)==list_kind||KIND(*hpos)==param_kind)
{Info i;
uint8_t a;
HGETTAG(a);
i= INFO(a)&0x3;
if(i==0)hpos= hpos+2;
else
{uint32_t s= hget_list_size(INFO(a));
if(i==3)i= 4;
hpos= hpos+(1+s+1+i+1);
}
}
}

static void hskip_list_back(void)
{if(KIND(*(hpos-1))==list_kind||KIND(*(hpos-1))==param_kind)
{Info i;
uint8_t z;
z= HTEG8;
i= INFO(z)&0x3;
if(i==0)hpos= hpos-2;
else
{uint32_t s= hteg_list_size(INFO(z));
if(i==3)i= 4;
hpos= hpos-(1+s+1+i+1);
}
}
}

pointer hteg_list_pointer(void)
{uint8_t*list_start;
pointer p;
hskip_list_back();
list_start= hpos;
p= hget_list_pointer();
hpos= list_start;
return p;
}
/*:121*//*122:*/
#line 2071 "hint.w"

#if 0
static int32_t hteg_integer_def(uint8_t z)
{if(INFO(z)==1){int8_t n= HTEG8;return n;}
else if(INFO(z)==2){int16_t n;HTEG16(n);return n;}
else if(INFO(z)==4){int32_t n;HTEG32(n);return n;}
else TAGERR(z);
return 0;
}

static ParamDef*hteg_param_list(uint8_t z)
{uint32_t s,t;
ParamDef*p= NULL;
uint8_t*list_start,*list_end;
list_end= hpos;
s= hteg_list_size(INFO(z));
hteg_size_boundary(INFO(z));
list_start= hpos-s;
if(list_start<=hstart)
QUIT("list start before stream start\n");
while(list_start<hpos)
{ParamDef*r;Param*q;
/*88:*/
#line 1531 "hint.w"

uint8_t a,z;
z= HTEG8;DBGTAG(z,hpos);
/*:88*/
#line 2093 "hint.w"

ALLOCATE(r,1,ParamDef);
q= &(r->p);
q->k= KIND(z);
if(KIND(z)==int_kind)q->i= hteg_integer_def(a);
else if(KIND(a)==dimen_kind)HTEG32(q->d);
else if(KIND(a)==glue_kind){pointer p;HTEG_GLUE(INFO(z));q->g= p;}
else TAGERR(a);
q->n= HTEG8;
DBG(DBGTAGS,"Defining %s %d\n",definition_name[KIND(z)],q->n);
/*89:*/
#line 1536 "hint.w"

a= HTEG8;DBGTAG(a,hpos);
if(z!=a)tag_mismatch(a,z,hpos-hstart,node_pos);
/*:89*/
#line 2103 "hint.w"

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

static ParamDef*hteg_param_list_node(void)
{ParamDef*p;
uint8_t*list_start;
hskip_list_back();
list_start= hpos;
p= hget_param_list_node();
hpos= list_start;
return p;
}
/*:122*//*129:*/
#line 2230 "hint.w"

static pointer hteg_hbox_node(void)
{/*88:*/
#line 1531 "hint.w"

uint8_t a,z;
z= HTEG8;DBGTAG(z,hpos);
/*:88*/
#line 2232 "hint.w"

if(KIND(z)!=hbox_kind)tag_expected(TAG(hbox_kind,0),z,node_pos);
{pointer p;
HTEG_BOX(INFO(z));
/*89:*/
#line 1536 "hint.w"

a= HTEG8;DBGTAG(a,hpos);
if(z!=a)tag_mismatch(a,z,hpos-hstart,node_pos);
/*:89*/
#line 2236 "hint.w"

return p;
}
}
static pointer hteg_vbox_node(void)
{/*88:*/
#line 1531 "hint.w"

uint8_t a,z;
z= HTEG8;DBGTAG(z,hpos);
/*:88*/
#line 2241 "hint.w"

if(KIND(z)!=vbox_kind)tag_expected(TAG(vbox_kind,0),z,node_pos);
{pointer p;
HTEG_BOX(INFO(z));
/*89:*/
#line 1536 "hint.w"

a= HTEG8;DBGTAG(a,hpos);
if(z!=a)tag_mismatch(a,z,hpos-hstart,node_pos);
/*:89*/
#line 2245 "hint.w"

type(p)= vlist_node;
return p;
}
}

/*:129*//*135:*/
#line 2326 "hint.w"

static void hset(pointer p,
uint8_t sto,scaled st,uint8_t sho,scaled sh,scaled w)
{scaled x;
x= width(p);
width(p)= w;

x= w-x;
if(x==0)
{glue_sign(p)= normal;glue_order(p)= normal;
glue_set(p)= 0.0;
}
else if(x> 0)
{glue_order(p)= sto;glue_sign(p)= stretching;
if(st!=0)
glue_set(p)= (float32_t)(x/(double)st);
else
{glue_sign(p)= normal;
glue_set(p)= 0.0;
}
}
else
{glue_order(p)= sho;glue_sign(p)= shrinking;
if(sh!=0)
glue_set(p)= (float32_t)((-x)/(double)sh);
else
{glue_sign(p)= normal;
glue_set(p)= 0.0;
}
if((sh<-x)&&(sho==normal)&&(list_ptr(p)!=null))
glue_set(p)= 1.0;
}
}
/*:135*//*136:*/
#line 2369 "hint.w"


void vset(pointer p,uint8_t sto,scaled st,
uint8_t sho,scaled sh,scaled h)
{scaled x;
type(p)= vlist_node;
x= height(p);
height(p)= h;
x= h-x;
if(x==0)
{glue_sign(p)= normal;glue_order(p)= normal;
glue_set(p)= 0.0;
}
else if(x> 0)
{glue_order(p)= sto;glue_sign(p)= stretching;
if(st!=0)
glue_set(p)= (float32_t)(x/(double)st);
else
{glue_sign(p)= normal;
glue_set(p)= 0.0;
}
}
else
{glue_order(p)= sho;glue_sign(p)= shrinking;
if(sh!=0)
glue_set(p)= (float32_t)((-x)/(double)sh);
else
{glue_sign(p)= normal;
glue_set(p)= 0.0;
}
}
if(depth(p)==MAX_DIMEN+1)
{if(list_ptr(p)!=null&&(type(list_ptr(p))==hlist_node||type(list_ptr(p))==vlist_node||type(list_ptr(p))==rule_node))
{h= height(list_ptr(p));
depth(p)= height(p)-h;
height(p)= h;
}
else
{depth(p)= depth(p)+height(p);height(p)= 0;}
DBG(DBGTEX,"vset top node adjusted height=%f depth=%f\n",height(p)/(double)ONE,depth(p)/(double)ONE);
}
}
/*:136*//*141:*/
#line 2483 "hint.w"

static pointer vtop(pointer p,scaled h,small_number m,scaled d)
{d= d^0x40000000;
p= vpackage(p,h,m,d);
if(list_ptr(p)!=null&&(type(list_ptr(p))==hlist_node||type(list_ptr(p))==vlist_node||type(list_ptr(p))==rule_node))
{h= height(list_ptr(p));
depth(p)= depth(p)+height(p)-h;
height(p)= h;
}
else
{depth(p)= depth(p)+height(p);height(p)= 0;}
DBG(DBGTEX,"vpack top node adjusted height=%f depth=%f\n",height(p)/(double)ONE,depth(p)/(double)ONE);
return p;
}
/*:141*//*154:*/
#line 2641 "hint.w"

static pointer hget_text_list(uint32_t s)
{pointer p= null;
pointer*pp= &p;
uint8_t*t= hpos+s;
while(hpos<t){*pp= new_character(0,hget_utf8());pp= &link(*pp);}
return p;
}
/*:154*//*163:*/
#line 2748 "hint.w"

static pointer hget_disc_node(void)
{/*82:*/
#line 1456 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:82*/
#line 2750 "hint.w"

if(KIND(a)!=disc_kind||INFO(a)==b000)
tag_expected(TAG(disc_kind,1),a,node_pos);
{
HGET_DISC(INFO(a));
/*83:*/
#line 1461 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:83*/
#line 2755 "hint.w"

return p;
}
}
/*:163*//*167:*/
#line 2823 "hint.w"

static void transplant_post_break_list(void)
{pointer r,q= link(head);
int t= replace_count(q);
pointer s= post_break(q);
r= q;
while(t> 0&&r!=null){r= link(r);t--;}
if(s!=null)
{while(link(s)!=null)s= link(s);
link(s)= link(r);link(r)= post_break(q);post_break(q)= null;
}
q= link(r);
if(r!=head)
{link(r)= null;flush_node_list(link(head));
link(head)= q;
}
}
static void transplant_pre_break_list(void)
{pointer q= tail;
set_replace_count(q,0);
link(q)= pre_break(q);
pre_break(q)= null;
while(link(q)!=null)q= link(q);
tail= q;
}


void hprune_unwanted_nodes(void)
{pointer q,r= head;
while(true){q= link(r);
if(q==null)goto done;
if(is_char_node(q))goto done;
if(non_discardable(q))goto done;
if(type(q)==kern_node&&subtype(q)!=explicit)goto done;
r= q;
}
done:if(r!=head)
{link(r)= null;flush_node_list(link(head));
link(head)= q;
}
}
/*:167*//*169:*/
#line 2896 "hint.w"

pointer hget_paragraph_all(scaled x)
{uint8_t*to;
/*170:*/
#line 2910 "hint.w"

pointer par_ptr= null;
if(KIND(*hpos)==list_kind)
{uint32_t s,t;
/*82:*/
#line 1456 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:82*/
#line 2914 "hint.w"

if((INFO(a)&b011)==0)
HGET8;
else if(INFO(a)&b100)
QUIT("Text in paragraph not yet implemented");
else
{uint8_t*list_end;
s= hget_list_size(INFO(a));
hget_size_boundary(INFO(a));
list_end= hpos+s;
cur_list.hs_field= x;
push_nest();
cur_list.bs_pos= NULL;

/*:170*/
#line 2899 "hint.w"

to= list_end;
/*171:*/
#line 2930 "hint.w"

while(hpos<to)
{hget_content();
if(nest_ptr==1)
{pointer p= tail;
if(p!=head&&!is_char_node(p)&&
(type(p)==glue_node||type(p)==kern_node||type(p)==penalty_node
||type(p)==disc_node||type(p)==math_node))
store_map(p,node_pos,0);
}
}

/*:171*/
#line 2901 "hint.w"

/*172:*/
#line 2944 "hint.w"

if(head!=tail)
{par_ptr= link(head);
store_map(par_ptr,node_pos,0);
if(needs_bs)
QUIT("Unexpected trailing baseline node");
}
pop_nest();
}
hget_size_boundary(INFO(a));
t= hget_list_size(INFO(a));
if(t!=s)
QUIT("List sizes at 0x%x and "SIZE_F" do not match 0x%x != 0x%x",
node_pos+1,hpos-hstart-s-1,s,t);
/*83:*/
#line 1461 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:83*/
#line 2958 "hint.w"

}



/*:172*/
#line 2902 "hint.w"

return par_ptr;
}

/*:169*//*173:*/
#line 2969 "hint.w"

pointer hget_paragraph_final(scaled x,uint8_t*from)
{uint8_t*to;
int par_color,par_label_ref;
/*170:*/
#line 2910 "hint.w"

pointer par_ptr= null;
if(KIND(*hpos)==list_kind)
{uint32_t s,t;
/*82:*/
#line 1456 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:82*/
#line 2914 "hint.w"

if((INFO(a)&b011)==0)
HGET8;
else if(INFO(a)&b100)
QUIT("Text in paragraph not yet implemented");
else
{uint8_t*list_end;
s= hget_list_size(INFO(a));
hget_size_boundary(INFO(a));
list_end= hpos+s;
cur_list.hs_field= x;
push_nest();
cur_list.bs_pos= NULL;

/*:170*/
#line 2973 "hint.w"

/*174:*/
#line 2993 "hint.w"

par_color= -1;par_label_ref= -1;
while(hpos<from)
{if(hpos[0]==TAG(color_kind,b000))par_color= hpos[1];
else if(KIND(hpos[0])==link_kind)
{if(INFO(hpos[0])&b010)
{par_label_ref= hget_label_ref();par_color= hget_link_color();}
else
{par_color= hget_link_color();
par_label_ref= -1;
}
}
if(par_color==0xFF)par_color= -1;
hff_hpos();
}
/*:174*/
#line 2974 "hint.w"

hpos= from;to= list_end;
/*171:*/
#line 2930 "hint.w"

while(hpos<to)
{hget_content();
if(nest_ptr==1)
{pointer p= tail;
if(p!=head&&!is_char_node(p)&&
(type(p)==glue_node||type(p)==kern_node||type(p)==penalty_node
||type(p)==disc_node||type(p)==math_node))
store_map(p,node_pos,0);
}
}

/*:171*/
#line 2976 "hint.w"

if(link(head)!=null&&!is_char_node(link(head)))
{if(type(link(head))==disc_node)
transplant_post_break_list();
else
hprune_unwanted_nodes();
}
/*172:*/
#line 2944 "hint.w"

if(head!=tail)
{par_ptr= link(head);
store_map(par_ptr,node_pos,0);
if(needs_bs)
QUIT("Unexpected trailing baseline node");
}
pop_nest();
}
hget_size_boundary(INFO(a));
t= hget_list_size(INFO(a));
if(t!=s)
QUIT("List sizes at 0x%x and "SIZE_F" do not match 0x%x != 0x%x",
node_pos+1,hpos-hstart-s-1,s,t);
/*83:*/
#line 1461 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:83*/
#line 2958 "hint.w"

}



/*:172*/
#line 2983 "hint.w"

/*175:*/
#line 3013 "hint.w"

if(par_ptr!=null)
{if(par_label_ref>=0)
{pointer p;
p= get_node(link_node_size);type(p)= whatsit_node;
subtype(p)= start_link_node;label_ref(as_label(p))= par_label_ref;
link(p)= par_ptr;
if(par_color>=0)color_ref(as_color(p))= par_color;
else color_ref(as_color(p))= 0xFF;
par_ptr= p;
}
else if(par_color>=0)
{pointer p;
p= get_node(color_node_size);
type(p)= whatsit_node;subtype(p)= color_node;
color_ref(p)= par_color;
link(p)= par_ptr;
par_ptr= p;
}
}
/*:175*/
#line 2984 "hint.w"

return par_ptr;
}
/*:173*//*181:*/
#line 3115 "hint.w"

pointer hget_paragraph(scaled x,uint32_t offset,ParamDef*q)
{
pointer p,par_head;
ParamDef*save_lbp= line_break_params;
par_head= tail;
line_break_params= q;
if(offset==0)
{prev_graf= 0;
p= hget_paragraph_all(x);
}
else
{prev_graf= 3;
p= hget_paragraph_final(x,hstart+node_pos+offset);
}
if(p!=null)
line_break(hget_integer_ref(widow_penalty_no),p);
line_break_params= save_lbp;
return par_head;
}

void hget_par_node(uint32_t offset)
{scaled x= 0;
ParamDef*q;
/*82:*/
#line 1456 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:82*/
#line 3139 "hint.w"

node_pos= (hpos-hstart)-1;
if(KIND(a)!=par_kind)
tag_expected(TAG(par_kind,0),a,node_pos);
node_pos= (hpos-hstart)-1;
if(INFO(a)==b100)q= hget_param_list_ref(HGET8);
if(INFO(a)&b100)x= hget_xdimen_node();else x= hget_xdimen_ref(HGET8);
if(INFO(a)&b010)q= hget_param_list_node();else q= hget_param_list_ref(HGET8);
hget_paragraph(x,offset,q);
/*83:*/
#line 1461 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:83*/
#line 3148 "hint.w"

}
/*:181*//*184:*/
#line 3170 "hint.w"

void hteg_paragraph(Info i)
{scaled x= 0;
ParamDef*q= null;
pointer par_head;
uint8_t*bs_pos= cur_list.bs_pos;
scaled ph= prev_height;
uint8_t*list_start,*par_start;
hskip_list_back();
list_start= hpos;
if(INFO(i)&b010)q= hteg_param_list_node();
else if(INFO(i)!=b100)q= hget_param_list_ref(HTEG8);
if(INFO(i)&b100)x= hteg_xdimen_node();else x= hget_xdimen_ref(HTEG8);
if(INFO(i)==b100)q= hget_param_list_ref(HTEG8);
par_start= hpos;
node_pos= par_start-hstart-1;
hpos= list_start;
cur_list.bs_pos= NULL;
par_head= hget_paragraph(x,0,q);
/*185:*/
#line 3202 "hint.w"

{pointer p,r,par_tail;
p= null;
r= par_tail= link(par_head);

tail= par_head;
link(tail)= null;
while(r!=null)
{pointer q= link(r);
link(r)= p;
p= r;
r= q;
}
cur_list.bs_pos= bs_pos;
prev_height= ph;
hprepend_to_vlist(p);
tail= par_tail;
if(type(tail)==hlist_node||type(tail)==vlist_node)
prev_height= height(tail);
}
/*:185*/
#line 3189 "hint.w"

hpos= par_start;
}
/*:184*//*200:*/
#line 3413 "hint.w"

static void hset_stream_params(pointer p,ParamDef*q)
{pointer s;
hset_param_list(q);
float_cost(p)= integer_def[floating_penalty_no];
depth(p)= dimen_def[split_max_depth_no];
split_top_ptr(p)= pointer_def[glue_kind][split_top_skip_no];
add_glue_ref(split_top_ptr(p));
hrestore_param_list();
s= vpack(ins_ptr(p),natural);
height(p)= height(s)+depth(s);
ins_ptr(p)= list_ptr(s);
list_ptr(s)= null;flush_node_list(s);
}
/*:200*//*215:*/
#line 3595 "hint.w"

static int hget_label_ref(void)
{if(INFO(hpos[0])&b001)return(hpos[1]<<8)+hpos[2];
else return hpos[1];
}
static int hget_link_color(void)
{if(INFO(hpos[0]&b100))
{if(INFO(hpos[0]&b001))return hpos[3];
else return hpos[2];
}
else
{if(INFO(hpos[0]&b010))return 1;else return 0xFF;}
}
/*:215*//*243:*/
#line 4206 "hint.w"

uint64_t hlocation(pointer p)
{uint64_t h= PAGE_LOC(map[p],map[p+1]);
while(h==0&&link(p)!=null)
{p= link(p);h= PAGE_LOC(map[p],map[p+1]);}
return h;
}
/*:243*//*246:*/
#line 4254 "hint.w"

#define NEXT_PAGE(X) (X= (X+1)&(MAX_PAGE_POS-1))
#define PREV_PAGE(X) (X= (X-1)&(MAX_PAGE_POS-1))

void hloc_clear(void)
{lo_loc= hi_loc= cur_loc;PREV_PAGE(lo_loc);NEXT_PAGE(hi_loc);
}

bool hloc_next(void)
{int i= cur_loc;
if(hstart+LOC_POS(page_loc[cur_loc])>=hend)
return false;
NEXT_PAGE(i);
if(i==hi_loc)
return false;
cur_loc= i;
return true;
}

bool hloc_prev(void)
{int i= cur_loc;
if(page_loc[cur_loc]==0)
return false;
PREV_PAGE(i);
if(i==lo_loc)
return false;
cur_loc= i;
return true;
}


/*:246*//*249:*/
#line 4316 "hint.w"


void hloc_set(uint64_t h)
{int i;
if(page_loc[cur_loc]==h)return;
for(i= lo_loc,NEXT_PAGE(i);i!=hi_loc;NEXT_PAGE(i))
if(page_loc[i]==h)
{cur_loc= i;
DBG(DBGPAGE,"loc_set: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
return;}
page_loc[cur_loc]= h;
hloc_clear();
DBG(DBGPAGE,"loc_set: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
}
/*:249*//*250:*/
#line 4342 "hint.w"


void hloc_set_next(pointer p)
{int i= cur_loc;
uint64_t h= hlocation(p);
if(h==page_loc[cur_loc])return;

NEXT_PAGE(i);
if(i==hi_loc)
{if(hi_loc==lo_loc)
NEXT_PAGE(lo_loc);
NEXT_PAGE(hi_loc);
page_loc[i]= h;
}
else if(h!=page_loc[i])
{page_loc[i]= h;
NEXT_PAGE(i);
hi_loc= i;
}
DBG(DBGPAGE,"loc_set_next: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
}
/*:250*//*251:*/
#line 4379 "hint.w"

void hloc_set_prev(pointer p)
{int i= cur_loc;
uint64_t h= hlocation(p);
PREV_PAGE(i);
if(i==lo_loc)
{if(lo_loc==hi_loc)
PREV_PAGE(hi_loc);
PREV_PAGE(lo_loc);
page_loc[i]= h;
}
else if(h!=page_loc[i])
{page_loc[i]= h;
lo_loc= i;
PREV_PAGE(lo_loc);
}
hi_loc= cur_loc;
NEXT_PAGE(hi_loc);
cur_loc= i;
DBG(DBGPAGE,"loc_set_prev: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
}
/*:251*//*264:*/
#line 4666 "hint.w"

static void hset_margins(void)
{if(cur_page==&(page_def[0])){
offset_h= page_h/8-0x48000;
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
else
{hhsize= round((double)(page_h-cur_page->h.w)/(double)cur_page->h.h);
if(hhsize> page_h)hhsize= page_h;
hvsize= round((double)(page_v-cur_page->v.w)/(double)cur_page->v.v);
if(hvsize> page_v)hvsize= page_v;
offset_h= (page_h-hhsize)/2;
offset_v= (page_v-hvsize)/2;
}
}
/*:264*//*266:*/
#line 4698 "hint.w"

static void houtput_template(pointer p)
{pointer q,r;
if(p==null)return;
p= vpackage(p,hvsize,exactly,page_max_depth);
if(offset_v!=0)
{r= new_kern(offset_v);
link(r)= p;
}
else
r= p;
q= new_null_box();
type(q)= vlist_node;
width(q)= width(p)+offset_h;
height(q)= height(p)+offset_v;depth(q)= depth(p);
list_ptr(q)= r;
shift_amount(p)+= offset_h;
streams[0].p= q;
}
/*:266*//*293:*/
#line 5392 "hint.w"

static int trv_string_size= 0;
static char trv_string[256];
#define TRV_UTF8(C) (trv_string[trv_string_size++]= (C))
static void trv_string_collect(uint32_t c)
{if(trv_string_size<256-5)
{if(c<0x80)
TRV_UTF8(c);
else if(c<0x800)
{TRV_UTF8(0xC0|(c>>6));TRV_UTF8(0x80|(c&0x3F));}
else if(c<0x10000)
{TRV_UTF8(0xE0|(c>>12));TRV_UTF8(0x80|((c>>6)&0x3F));TRV_UTF8(0x80|(c&0x3F));}
else if(c<0x200000)
{TRV_UTF8(0xF0|(c>>18));TRV_UTF8(0x80|((c>>12)&0x3F));
TRV_UTF8(0x80|((c>>6)&0x3F));TRV_UTF8(0x80|(c&0x3F));}
else
RNG("character code in outline",c,0,0x1FFFFF);
}
}

char*hlist_to_string(pointer p)
{trv_string_size= 0;
trv_init(trv_string_collect);
trv_hlist(p);
trv_string[trv_string_size]= 0;
return trv_string;
}
/*:293*//*396:*/
#line 8173 "hint.w"

static pointer leaks[1<<16]= {0};

static void leak_clear(void)
{
#ifdef DEBUG
int i;
for(i= 0;i<0x10000;i++)
leaks[i]= 0;
#endif
}

void leak_in(pointer p,int s)
{
#ifdef DEBUG
if(0!=leaks[p])
fprintf(stderr,"ERROR leak in: p=%d, s in=%d, leaks[p]= %d != 0\n",p,s,leaks[p]);
leaks[p]= s;
#endif
}

void leak_out(pointer p,int s)
{
#ifdef DEBUG
if(s!=leaks[p])
fprintf(stderr,"ERROR: leak out: p=%d, s out=%d != %d = s in\n",p,s,leaks[p]);
leaks[p]= 0;
#endif
}

static void list_leaks(void)
{
#ifdef DEBUG
int i;
for(i= 0;i<0x10000;i++)
if(leaks[i]!=0)
fprintf(stderr,"ERROR:leak final: p=%d, s=%d\n",i,leaks[i]);
#endif
}
/*:396*/
#line 8265 "hint.w"

/*1:*/
#line 231 "hint.w"

void hget_def_node(void)
{Kind k;
int n;
/*82:*/
#line 1456 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:82*/
#line 235 "hint.w"

k= KIND(a);
if(k==unknown_kind&&INFO(a)==b100)
{hget_unknown_def();
/*83:*/
#line 1461 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:83*/
#line 239 "hint.w"

return;
}
if(k==label_kind&&(INFO(a)&b001))HGET16(n);
else n= HGET8;
if(max_fixed[k]> max_default[k])
{MESSAGE("Definitions for kind %s not supported\n",definition_name[k]);
while(hpos<hend&&*hpos!=a)hpos++;
/*83:*/
#line 1461 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:83*/
#line 247 "hint.w"

return;
}
if(k!=range_kind)REF_RNG(k,n);
DBG(DBGTAGS,"Defining %s %d\n",definition_name[KIND(a)],n);
switch(KIND(a))
{case language_kind:{char*t;HGET_STRING(t);break;}
case font_kind:hget_font_def(a,n);break;
case int_kind:integer_def[n]= hget_integer_def(a);break;
case dimen_kind:dimen_def[n]= hget_dimen_def(a);break;
case xdimen_kind:hget_xdimen_def(INFO(a),&(xdimen_def[n]));break;
case baseline_kind:hget_baseline_def(a,n);break;
case glue_kind:pointer_def[glue_kind][n]= hget_glue_def(a);break;
case param_kind:param_def[n]= hget_param_list(a);break;
case range_kind:hget_range_def(a,n);break;
case page_kind:hget_page_def(a,n);break;
case label_kind:hget_outline_or_label_def(INFO(a),n);break;
case color_kind:hget_color_def(INFO(a),n);break;
default:pointer_def[KIND(a)][n]= hget_definition(a);break;
}
if(n> max_ref[k]||n<=max_fixed[k])
QUIT("Definition %d for %s out of range [%d - %d]",
n,definition_name[k],max_fixed[k]+1,max_ref[k]);
/*83:*/
#line 1461 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:83*/
#line 270 "hint.w"

}

pointer hset_glue(Glue*g)
{if(ZERO_GLUE(*g))
{add_glue_ref(zero_glue);
return zero_glue;
}
else
{pointer p= get_node(glue_spec_size);
width(p)= g->w.w;
stretch(p)= round(g->p.f*ONE);stretch_order(p)= g->p.o;
shrink(p)= round(g->m.f*ONE);shrink_order(p)= g->m.o;
return p;
}
}

void hset_default_definitions(void)
{int i;
for(i= 0;i<=MAX_INT_DEFAULT;i++)integer_def[i]= int_defaults[i];
for(i= 0;i<=MAX_DIMEN_DEFAULT;i++)dimen_def[i]= dimen_defaults[i];
for(i= 0;i<=MAX_XDIMEN_DEFAULT;i++)xdimen_def[i]= xdimen_defaults[i];
for(i= 0;i<=MAX_GLUE_DEFAULT;i++)pointer_def[glue_kind][i]= hset_glue(&(glue_defaults[i]));
for(i= 0;i<=MAX_BASELINE_DEFAULT;i++)
{baseline_def[i].bs= hset_glue(&(baseline_defaults[i].bs));
baseline_def[i].ls= hset_glue(&(baseline_defaults[i].ls));
baseline_def[i].lsl= baseline_defaults[i].lsl;
}
hset_default_colors();
}

void free_definitions(void)
{/*5:*/
#line 361 "hint.w"

{int k;
for(k= 0;k<32;k++)
{free(pointer_def[k]);pointer_def[k]= NULL;}
}
/*:5*//*8:*/
#line 384 "hint.w"

free(integer_def);integer_def= NULL;
/*:8*//*12:*/
#line 413 "hint.w"

free(dimen_def);dimen_def= NULL;
/*:12*//*16:*/
#line 442 "hint.w"

free(xdimen_def);xdimen_def= NULL;
/*:16*//*24:*/
#line 513 "hint.w"

free(baseline_def);baseline_def= NULL;
/*:24*//*31:*/
#line 631 "hint.w"

free(font_def);font_def= NULL;
/*:31*//*40:*/
#line 736 "hint.w"

if(param_def!=NULL)
{int i;
for(i= 0;i<=max_ref[param_kind];i++)
free_param_list(param_def[i]);
}
free(param_def);param_def= NULL;
/*:40*//*47:*/
#line 893 "hint.w"

free(range_def);range_def= NULL;
/*:47*//*52:*/
#line 946 "hint.w"

free(streams);streams= NULL;
/*:52*//*60:*/
#line 1059 "hint.w"

if(page_def!=NULL)
{int k;
for(k= 0;k<=max_ref[page_kind];k++)
{free(page_def[k].s);free(page_def[k].n);
}
free(page_def);page_def= NULL;cur_page= NULL;
}
/*:60*//*67:*/
#line 1172 "hint.w"

free(labels);labels= NULL;
{int k;
for(k= 0;k<=max_outline;k++)free(hint_outlines[k].title);
}
free(hint_outlines);hint_outlines= NULL;outline_no= -1;
max_outline= -1;
/*:67*//*75:*/
#line 1264 "hint.w"

free(color_def);color_def= NULL;
/*:75*/
#line 302 "hint.w"

}

void hget_definition_section(void)
{DBG(DBGDEF,"Definitions\n");
hget_section(1);
DBG(DBGDEF,"Reading list of maximum values\n");
free_definitions();
hget_max_definitions();
/*4:*/
#line 346 "hint.w"

{Kind k;
for(k= 0;k<32;k++)
{if(k==font_kind||k==int_kind||k==dimen_kind||k==xdimen_kind||
k==glue_kind||k==baseline_kind||k==range_kind||k==page_kind||k==param_kind||k==stream_kind||k==label_kind)
continue;
if(max_ref[k]>=0&&max_ref[k]<=256)
{DBG(DBGDEF,"Allocating definitions for %s (kind %d): %d entries of "SIZE_F" byte each\n",
definition_name[k],k,max_ref[k]+1,sizeof(pointer));
ALLOCATE(pointer_def[k],max_ref[k]+1,pointer);
}
}
}
/*:4*//*7:*/
#line 380 "hint.w"

ALLOCATE(integer_def,max_ref[int_kind]+1,int32_t);
/*:7*//*11:*/
#line 409 "hint.w"

ALLOCATE(dimen_def,max_ref[dimen_kind]+1,Dimen);
/*:11*//*15:*/
#line 439 "hint.w"

ALLOCATE(xdimen_def,max_ref[xdimen_kind]+1,Xdimen);
/*:15*//*20:*/
#line 490 "hint.w"

ALLOCATE(pointer_def[glue_kind],max_ref[glue_kind]+1,pointer);
/*:20*//*23:*/
#line 509 "hint.w"

ALLOCATE(baseline_def,max_ref[baseline_kind]+1,BaselineSkip);
/*:23*//*30:*/
#line 627 "hint.w"

ALLOCATE(font_def,max_ref[font_kind]+1,FontDef);
/*:30*//*39:*/
#line 732 "hint.w"

ALLOCATE(param_def,max_ref[param_kind]+1,ParamDef*);
/*:39*//*46:*/
#line 888 "hint.w"

ALLOCATE(range_def,max_ref[range_kind]+1,RangeDef);
max_range= -1;
/*:46*//*51:*/
#line 942 "hint.w"

ALLOCATE(streams,max_ref[stream_kind]+1,Stream);
/*:51*//*58:*/
#line 1039 "hint.w"

ALLOCATE(page_def,max_ref[page_kind]+1,PageDef);
/*:58*//*66:*/
#line 1165 "hint.w"

if(max_ref[label_kind]>=0)
ALLOCATE(labels,max_ref[label_kind]+1,Label);
if(max_outline>=0)
ALLOCATE(hint_outlines,max_outline+1,hint_Outline);
/*:66*//*74:*/
#line 1258 "hint.w"

if(color_def!=NULL){free(color_def);color_def= NULL;}
ALLOCATE(color_def,max_ref[color_kind]+1,ColorSet);
first_color= true;
/*:74*/
#line 311 "hint.w"

hset_default_definitions();
DBG(DBGDEF,"Reading list of definitions\n");
while(hpos<hend)
hget_def_node();
hget_font_metrics();
/*59:*/
#line 1043 "hint.w"

page_def[0].d= max_depth;
page_def[0].g= top_skip;add_glue_ref(top_skip);
page_def[0].p= 0;
page_def[0].n= strdup("default");
page_def[0].v.w= -9*ONE;
page_def[0].v.h= 0.0;
page_def[0].v.v= 1.25;
page_def[0].h.w= -9*ONE;
page_def[0].h.h= 1.25;
page_def[0].h.v= 0.0;
page_def[0].t= 0;
ALLOCATE(page_def[0].s,max_ref[stream_kind]+1,StreamDef);
cur_page= &(page_def[0]);
/*:59*/
#line 317 "hint.w"

}
/*:1*//*13:*/
#line 417 "hint.w"

scaled hget_dimen_ref(uint8_t n)
{REF_RNG(dimen_kind,n);
return dimen_def[n];
}

static scaled hget_dimen_def(uint8_t a)
{if(INFO(a)==b000)
return hget_dimen_ref(HGET8);
else
{scaled d;HGET32(d);return d;}
}
/*:13*//*25:*/
#line 517 "hint.w"

static void hget_baseline_def(uint8_t a,uint8_t n)
{HGET_BASELINE(INFO(a));
baseline_def[n].bs= cur_bs;add_glue_ref(cur_bs);
baseline_def[n].ls= cur_ls;add_glue_ref(cur_ls);
baseline_def[n].lsl= cur_lsl;
}

void hget_baseline_ref(uint8_t n)
{REF_RNG(baseline_kind,n);
cur_bs= baseline_def[n].bs;
cur_ls= baseline_def[n].ls;
cur_lsl= baseline_def[n].lsl;
}

pointer happend_to_vlist(pointer b)
{scaled d;
pointer p= null;

if(needs_bs&&prev_depth> ignore_depth)
{d= width(cur_bs)-prev_depth-height(b);
if(d<cur_lsl)p= new_glue(cur_ls);
else{pointer q= new_spec(cur_bs);
width(q)= d;p= new_glue(q);glue_ref_count(q)= null;
}
link(tail)= p;tail= p;
if(nest_ptr==0)
store_map(p,cur_list.bs_pos-hstart,0);
}
link(tail)= b;tail= b;prev_depth= depth(b);
cur_list.bs_pos= NULL;
return p;
}
/*:25*//*26:*/
#line 571 "hint.w"

static pointer hprepend_to_vlist(pointer b)
{scaled d;
pointer p= null;

if(needs_bs&&prev_height> ignore_depth)
{d= width(cur_bs)-prev_height-depth(b);
if(d<cur_lsl)p= new_glue(cur_ls);
else{pointer q= new_spec(cur_bs);
width(q)= d;p= new_glue(q);glue_ref_count(q)= null;
}
link(tail)= p;tail= p;
if(nest_ptr==0)
store_map(p,cur_list.bs_pos-hstart,0);
}
link(tail)= b;tail= b;prev_height= height(b);
cur_list.bs_pos= NULL;
return p;
}
/*:26*//*68:*/
#line 1185 "hint.w"

void hget_outline_or_label_def(Info i,int n)
{if(i&b100)
/*70:*/
#line 1206 "hint.w"

{hint_Outline*t;
uint64_t pos;
uint8_t where;
outline_no++;
RNG("Outline",outline_no,0,max_outline);
t= hint_outlines+outline_no;
t->depth= HGET8;
t->p= hget_list_pointer();
t->title= strdup(hlist_to_string(t->p));
/*71:*/
#line 1222 "hint.w"

if(labels==NULL||n> max_ref[label_kind])
{where= LABEL_TOP;pos= 0;}
else
{where= labels[n].where;
#if 1
pos= ((uint64_t)labels[n].pos<<32)+(labels[n].pos-labels[n].pos0);
#else
pos= ((uint64_t)labels[n].pos0<<32);

#endif
}
/*:71*/
#line 1216 "hint.w"

t->where= where;
t->pos= pos;
}
/*:70*/
#line 1188 "hint.w"

else
/*69:*/
#line 1194 "hint.w"

{Label*t= labels+n;
HGET32(t->pos);
t->where= HGET8;
if(t->where> LABEL_MID)t->where= LABEL_UNDEF;
if(i&b010)
{HGET32(t->pos0);t->f= HGET8;}
else t->pos0= t->pos;
DBG(DBGDEF,"Label 0x%x+0x%x where=%d font=%d\n",t->pos0,t->pos,t->where,t->f);
}
/*:69*/
#line 1190 "hint.w"

}
/*:68*//*77:*/
#line 1287 "hint.w"

static void hget_color_def(uint8_t a,int i)
{int j,k;
if(INFO(a)!=b000)
QUIT("Color Definition %d with Info value %d!=000",i,INFO(a));
k= HGET8;
if(k!=6)
QUIT("Definition %d of color set needs 6 color pairs %d given\n",i,k);
if(i==0&&!first_color)
QUIT("Definition of color 0 must come first");
first_color= false;
for(j= 0;j<6*2;j++)
HGET32(color_def[i][j]);
}
/*:77*//*79:*/
#line 1392 "hint.w"

static void hget_unknown_def(void)
{Tag t;signed char i;
t= HGET8;
i= HGET8;
if(i==0)
QUIT("Zero not allowed for unknown node size at 0x%x\n",(uint32_t)(hpos-hstart-2));
if(hnode_size[t]==0)
{hnode_size[t]= i;
DBG(DBGTAGS,"Defining node size %d,%d for tag 0x%x (%s)\n",NODE_HEAD(i),NODE_TAIL(i),t,content_name[KIND(t)]);
}
}
/*:79*//*80:*/
#line 1410 "hint.w"

int hget_unknown(Tag a)
{DBG(DBGTAGS,"Trying unknown tag 0x%x at 0x%x\n",a,(uint32_t)(hpos-hstart-1));
hpos--;
hff_hpos();
hpos--;
return 1;
}
/*:80*//*81:*/
#line 1442 "hint.w"

static void hget_content_section()
{DBG(DBGDIR,"Reading Content Section\n");
hget_section(2);
}
/*:81*//*111:*/
#line 1829 "hint.w"

pointer hget_rule_node(void)
{pointer q= null;
/*82:*/
#line 1456 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:82*/
#line 1832 "hint.w"

if(KIND(a)==rule_kind){HGET_RULE(INFO(a));q= p;}
else tag_expected(TAG(rule_kind,0),a,node_pos);
/*83:*/
#line 1461 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:83*/
#line 1835 "hint.w"

return q;
}
/*:111*//*128:*/
#line 2205 "hint.w"

pointer hget_hbox_node(void)
{/*82:*/
#line 1456 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:82*/
#line 2207 "hint.w"

if(KIND(a)!=hbox_kind)tag_expected(TAG(hbox_kind,0),a,node_pos);
{pointer p;
HGET_BOX(INFO(a));
/*83:*/
#line 1461 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:83*/
#line 2211 "hint.w"

return p;
}
}


pointer hget_vbox_node(void)
{
/*82:*/
#line 1456 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:82*/
#line 2219 "hint.w"

if(KIND(a)!=vbox_kind)tag_expected(TAG(vbox_kind,0),a,node_pos);
{pointer p;
HGET_BOX(INFO(a));
/*83:*/
#line 1461 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:83*/
#line 2223 "hint.w"

type(p)= vlist_node;
return p;
}
}
/*:128*//*176:*/
#line 3038 "hint.w"

pointer hget_paragraph_initial(scaled x,uint8_t*to)
{/*170:*/
#line 2910 "hint.w"

pointer par_ptr= null;
if(KIND(*hpos)==list_kind)
{uint32_t s,t;
/*82:*/
#line 1456 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:82*/
#line 2914 "hint.w"

if((INFO(a)&b011)==0)
HGET8;
else if(INFO(a)&b100)
QUIT("Text in paragraph not yet implemented");
else
{uint8_t*list_end;
s= hget_list_size(INFO(a));
hget_size_boundary(INFO(a));
list_end= hpos+s;
cur_list.hs_field= x;
push_nest();
cur_list.bs_pos= NULL;

/*:170*/
#line 3040 "hint.w"

if(to> list_end)
{LOG("Value of to greater than list_end");
to= list_end;
}
/*171:*/
#line 2930 "hint.w"

while(hpos<to)
{hget_content();
if(nest_ptr==1)
{pointer p= tail;
if(p!=head&&!is_char_node(p)&&
(type(p)==glue_node||type(p)==kern_node||type(p)==penalty_node
||type(p)==disc_node||type(p)==math_node))
store_map(p,node_pos,0);
}
}

/*:171*/
#line 3045 "hint.w"

if(KIND(*to)==disc_kind)
{hget_content();
store_map(tail,node_pos,0);
transplant_pre_break_list();
}
if(head!=tail)
/*177:*/
#line 3066 "hint.w"

{if(is_char_node(tail))tail_append(new_penalty(inf_penalty))
else if(type(tail)!=glue_node)tail_append(new_penalty(inf_penalty))
else
{type(tail)= penalty_node;delete_glue_ref(glue_ptr(tail));
flush_node_list(leader_ptr(tail));penalty(tail)= inf_penalty;
}
tail_append(new_glue(zero_glue));
}
/*:177*/
#line 3052 "hint.w"

hpos= list_end;
/*172:*/
#line 2944 "hint.w"

if(head!=tail)
{par_ptr= link(head);
store_map(par_ptr,node_pos,0);
if(needs_bs)
QUIT("Unexpected trailing baseline node");
}
pop_nest();
}
hget_size_boundary(INFO(a));
t= hget_list_size(INFO(a));
if(t!=s)
QUIT("List sizes at 0x%x and "SIZE_F" do not match 0x%x != 0x%x",
node_pos+1,hpos-hstart-s-1,s,t);
/*83:*/
#line 1461 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:83*/
#line 2958 "hint.w"

}



/*:172*/
#line 3054 "hint.w"

return par_ptr;
}
/*:176*/
#line 8266 "hint.w"

/*90:*/
#line 1547 "hint.w"

static void hteg_node(uint8_t z)
{switch(z)
{
/*102:*/
#line 1741 "hint.w"

case TAG(glyph_kind,1):HTEG_GLYPH(1);break;
case TAG(glyph_kind,2):HTEG_GLYPH(2);break;
case TAG(glyph_kind,3):HTEG_GLYPH(3);break;
case TAG(glyph_kind,4):HTEG_GLYPH(4);break;
/*:102*//*104:*/
#line 1756 "hint.w"

case TAG(penalty_kind,0):tail_append(new_penalty(hget_integer_ref(HTEG8)));break;
case TAG(penalty_kind,1):{tail_append(new_penalty(HTEG8));}break;
case TAG(penalty_kind,2):{int16_t n;HTEG16(n);RNG("Penalty",n,-20000,+20000);tail_append(new_penalty(n));}break;
/*:104*//*106:*/
#line 1776 "hint.w"

case TAG(language_kind,b000):(void)HTEG8;
case TAG(language_kind,1):
case TAG(language_kind,2):
case TAG(language_kind,3):
case TAG(language_kind,4):
case TAG(language_kind,5):
case TAG(language_kind,6):
case TAG(language_kind,7):break;
/*:106*//*110:*/
#line 1819 "hint.w"

case TAG(rule_kind,b000):tail_append(hget_rule_ref(HTEG8));prev_height= ignore_depth;break;
case TAG(rule_kind,b011):{HTEG_RULE(b011);tail_append(p);prev_height= ignore_depth;}break;
case TAG(rule_kind,b101):{HTEG_RULE(b101);tail_append(p);prev_height= ignore_depth;}break;
case TAG(rule_kind,b001):{HTEG_RULE(b001);tail_append(p);prev_height= ignore_depth;}break;
case TAG(rule_kind,b110):{HTEG_RULE(b110);tail_append(p);prev_height= ignore_depth;}break;
case TAG(rule_kind,b111):{HTEG_RULE(b111);tail_append(p);prev_height= ignore_depth;}break;
/*:110*//*117:*/
#line 1890 "hint.w"

case TAG(glue_kind,b000):tail_append(new_glue(hget_glue_ref(HTEG8)));break;
case TAG(glue_kind,b001):{pointer p;HTEG_GLUE(b001);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b010):{pointer p;HTEG_GLUE(b010);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b011):{pointer p;HTEG_GLUE(b011);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b100):{pointer p;HTEG_GLUE(b100);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b101):{pointer p;HTEG_GLUE(b101);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b110):{pointer p;HTEG_GLUE(b110);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b111):{pointer p;HTEG_GLUE(b111);tail_append(spec2glue(p));}break;
/*:117*//*127:*/
#line 2186 "hint.w"

case TAG(hbox_kind,b000):{pointer p;HTEG_BOX(b000);hprepend_to_vlist(p);}break;
case TAG(hbox_kind,b001):{pointer p;HTEG_BOX(b001);hprepend_to_vlist(p);}break;
case TAG(hbox_kind,b010):{pointer p;HTEG_BOX(b010);hprepend_to_vlist(p);}break;
case TAG(hbox_kind,b011):{pointer p;HTEG_BOX(b011);hprepend_to_vlist(p);}break;
case TAG(hbox_kind,b100):{pointer p;HTEG_BOX(b100);hprepend_to_vlist(p);}break;
case TAG(hbox_kind,b101):{pointer p;HTEG_BOX(b101);hprepend_to_vlist(p);}break;
case TAG(hbox_kind,b110):{pointer p;HTEG_BOX(b110);hprepend_to_vlist(p);}break;
case TAG(hbox_kind,b111):{pointer p;HTEG_BOX(b111);hprepend_to_vlist(p);}break;
case TAG(vbox_kind,b000):{pointer p;HTEG_BOX(b000);type(p)= vlist_node;hprepend_to_vlist(p);}break;
case TAG(vbox_kind,b001):{pointer p;HTEG_BOX(b001);type(p)= vlist_node;hprepend_to_vlist(p);}break;
case TAG(vbox_kind,b010):{pointer p;HTEG_BOX(b010);type(p)= vlist_node;hprepend_to_vlist(p);}break;
case TAG(vbox_kind,b011):{pointer p;HTEG_BOX(b011);type(p)= vlist_node;hprepend_to_vlist(p);}break;
case TAG(vbox_kind,b100):{pointer p;HTEG_BOX(b100);type(p)= vlist_node;hprepend_to_vlist(p);}break;
case TAG(vbox_kind,b101):{pointer p;HTEG_BOX(b101);type(p)= vlist_node;hprepend_to_vlist(p);}break;
case TAG(vbox_kind,b110):{pointer p;HTEG_BOX(b110);type(p)= vlist_node;hprepend_to_vlist(p);}break;
case TAG(vbox_kind,b111):{pointer p;HTEG_BOX(b111);type(p)= vlist_node;hprepend_to_vlist(p);}break;
/*:127*//*134:*/
#line 2304 "hint.w"

case TAG(hset_kind,b000):{pointer p;HTEG_SET(b000);hset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(hset_kind,b001):{pointer p;HTEG_SET(b001);hset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(hset_kind,b010):{pointer p;HTEG_SET(b010);hset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(hset_kind,b011):{pointer p;HTEG_SET(b011);hset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(hset_kind,b100):{pointer p;HTEG_SET(b100);hset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(hset_kind,b101):{pointer p;HTEG_SET(b101);hset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(hset_kind,b110):{pointer p;HTEG_SET(b110);hset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(hset_kind,b111):{pointer p;HTEG_SET(b111);hset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;

case TAG(vset_kind,b000):{pointer p;HTEG_SET(b000);vset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(vset_kind,b001):{pointer p;HTEG_SET(b001);vset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(vset_kind,b010):{pointer p;HTEG_SET(b010);vset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(vset_kind,b011):{pointer p;HTEG_SET(b011);vset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(vset_kind,b100):{pointer p;HTEG_SET(b100);vset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(vset_kind,b101):{pointer p;HTEG_SET(b101);vset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(vset_kind,b110):{pointer p;HTEG_SET(b110);vset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
case TAG(vset_kind,b111):{pointer p;HTEG_SET(b111);vset(p,sto,st,sho,sh,x);hprepend_to_vlist(p);}break;
/*:134*//*140:*/
#line 2463 "hint.w"

case TAG(hpack_kind,b000):HTEG_PACK(hpack_kind,b000);break;
case TAG(hpack_kind,b010):HTEG_PACK(hpack_kind,b010);break;
case TAG(hpack_kind,b100):HTEG_PACK(hpack_kind,b100);break;
case TAG(hpack_kind,b110):HTEG_PACK(hpack_kind,b110);break;
case TAG(hpack_kind,b001):HTEG_PACK(hpack_kind,b001);break;
case TAG(hpack_kind,b011):HTEG_PACK(hpack_kind,b011);break;
case TAG(hpack_kind,b101):HTEG_PACK(hpack_kind,b101);break;
case TAG(hpack_kind,b111):HTEG_PACK(hpack_kind,b111);break;

case TAG(vpack_kind,b000):HTEG_PACK(vpack_kind,b000);break;
case TAG(vpack_kind,b010):HTEG_PACK(vpack_kind,b010);break;
case TAG(vpack_kind,b100):HTEG_PACK(vpack_kind,b100);break;
case TAG(vpack_kind,b110):HTEG_PACK(vpack_kind,b110);break;
case TAG(vpack_kind,b001):HTEG_PACK(vpack_kind,b001);break;
case TAG(vpack_kind,b011):HTEG_PACK(vpack_kind,b011);break;
case TAG(vpack_kind,b101):HTEG_PACK(vpack_kind,b101);break;
case TAG(vpack_kind,b111):HTEG_PACK(vpack_kind,b111);break;
/*:140*//*145:*/
#line 2538 "hint.w"

case TAG(kern_kind,b000):{HTEG_KERN(b000);}break;
case TAG(kern_kind,b001):{HTEG_KERN(b001);}break;
case TAG(kern_kind,b010):{HTEG_KERN(b010);}break;
case TAG(kern_kind,b011):{HTEG_KERN(b011);}break;
case TAG(kern_kind,b100):{HTEG_KERN(b100);}break;
case TAG(kern_kind,b101):{HTEG_KERN(b101);}break;
case TAG(kern_kind,b110):{HTEG_KERN(b110);}break;
case TAG(kern_kind,b111):{HTEG_KERN(b111);}break;
/*:145*//*149:*/
#line 2585 "hint.w"

case TAG(leaders_kind,0):tail_append(hget_leaders_ref(HTEG8));break;
case TAG(leaders_kind,1):HTEG_LEADERS(1);break;
case TAG(leaders_kind,2):HTEG_LEADERS(2);break;
case TAG(leaders_kind,3):HTEG_LEADERS(3);break;
case TAG(leaders_kind,b100|1):HTEG_LEADERS(b100|1);break;
case TAG(leaders_kind,b100|2):HTEG_LEADERS(b100|2);break;
case TAG(leaders_kind,b100|3):HTEG_LEADERS(b100|3);break;
/*:149*//*153:*/
#line 2626 "hint.w"

case TAG(baseline_kind,b000):{hget_baseline_ref(HTEG8);cur_list.bs_pos= hpos-1;}break;
case TAG(baseline_kind,b010):{HTEG_BASELINE(b010);}break;
case TAG(baseline_kind,b011):{HTEG_BASELINE(b011);}break;
case TAG(baseline_kind,b100):{HTEG_BASELINE(b100);}break;
case TAG(baseline_kind,b101):{HTEG_BASELINE(b101);}break;
case TAG(baseline_kind,b110):{HTEG_BASELINE(b110);}break;
case TAG(baseline_kind,b111):{HTEG_BASELINE(b111);}break;
/*:153*//*158:*/
#line 2687 "hint.w"

case TAG(ligature_kind,0):tail_append(hget_ligature_ref(HTEG8));break;
case TAG(ligature_kind,1):HTEG_LIG(1);break;
case TAG(ligature_kind,2):HTEG_LIG(2);break;
case TAG(ligature_kind,3):HTEG_LIG(3);break;
case TAG(ligature_kind,4):HTEG_LIG(4);break;
case TAG(ligature_kind,5):HTEG_LIG(5);break;
case TAG(ligature_kind,6):HTEG_LIG(6);break;
case TAG(ligature_kind,7):HTEG_LIG(7);break;
/*:158*//*162:*/
#line 2736 "hint.w"

case TAG(disc_kind,b000):tail_append(hget_hyphen_ref(HTEG8));break;
case TAG(disc_kind,b001):{HTEG_DISC(b001);tail_append(p);}break;
case TAG(disc_kind,b010):{HTEG_DISC(b010);tail_append(p);}break;
case TAG(disc_kind,b011):{HTEG_DISC(b011);tail_append(p);}break;
case TAG(disc_kind,b100):{HTEG_DISC(b100);tail_append(p);}break;
case TAG(disc_kind,b101):{HTEG_DISC(b101);tail_append(p);}break;
case TAG(disc_kind,b110):{HTEG_DISC(b110);tail_append(p);}break;
case TAG(disc_kind,b111):{HTEG_DISC(b111);tail_append(p);}break;
/*:162*//*183:*/
#line 3157 "hint.w"

case TAG(par_kind,b000):hteg_paragraph(b000);break;
case TAG(par_kind,b010):hteg_paragraph(b010);break;
case TAG(par_kind,b100):hteg_paragraph(b100);break;
case TAG(par_kind,b110):hteg_paragraph(b110);break;
/*:183*//*191:*/
#line 3290 "hint.w"

case TAG(math_kind,b000):HTEG_MATH(b000);break;
case TAG(math_kind,b001):HTEG_MATH(b001);break;
case TAG(math_kind,b010):HTEG_MATH(b010);break;
case TAG(math_kind,b100):HTEG_MATH(b100);break;
case TAG(math_kind,b101):HTEG_MATH(b101);break;
case TAG(math_kind,b110):HTEG_MATH(b110);break;
/*:191*//*193:*/
#line 3314 "hint.w"

case TAG(math_kind,b111):tail_append(new_math(0,before));break;
case TAG(math_kind,b011):tail_append(new_math(0,after));break;
/*:193*//*199:*/
#line 3384 "hint.w"

case TAG(table_kind,b000):HTEG_TABLE(b000);break;
case TAG(table_kind,b001):HTEG_TABLE(b001);break;
case TAG(table_kind,b010):HTEG_TABLE(b010);break;
case TAG(table_kind,b011):HTEG_TABLE(b011);break;
case TAG(table_kind,b100):HTEG_TABLE(b100);break;
case TAG(table_kind,b101):HTEG_TABLE(b101);break;
case TAG(table_kind,b110):HTEG_TABLE(b110);break;
case TAG(table_kind,b111):HTEG_TABLE(b111);break;

case TAG(item_kind,b000):hteg_list_pointer();break;
case TAG(item_kind,b001):hteg_content();break;
case TAG(item_kind,b010):hteg_content();break;
case TAG(item_kind,b011):hteg_content();break;
case TAG(item_kind,b100):hteg_content();break;
case TAG(item_kind,b101):hteg_content();break;
case TAG(item_kind,b110):hteg_content();break;
case TAG(item_kind,b111):hteg_content();(void)HTEG8;break;
/*:199*//*204:*/
#line 3456 "hint.w"

case TAG(stream_kind,b000):HTEG_STREAM(b000);break;
case TAG(stream_kind,b010):HTEG_STREAM(b010);break;
/*:204*//*208:*/
#line 3515 "hint.w"

case TAG(image_kind,b000):hget_image_ref(HTEG8);break;
case TAG(image_kind,b001):HTEG_IMAGE(b001);break;
case TAG(image_kind,b010):HTEG_IMAGE(b010);break;
case TAG(image_kind,b011):HTEG_IMAGE(b011);break;
case TAG(image_kind,b100):HTEG_IMAGE(b100);break;
case TAG(image_kind,b101):HTEG_IMAGE(b101);break;
case TAG(image_kind,b110):HTEG_IMAGE(b110);break;
case TAG(image_kind,b111):HTEG_IMAGE(b111);break;
/*:208*//*210:*/
#line 3530 "hint.w"

case TAG(color_kind,b000):tail_append(hget_color_ref(HTEG8));break;
/*:210*//*212:*/
#line 3548 "hint.w"

case TAG(link_kind,b000):HTEG_LINK(b000);break;
case TAG(link_kind,b001):HTEG_LINK(b001);break;
case TAG(link_kind,b010):HTEG_LINK(b010);break;
case TAG(link_kind,b011):HTEG_LINK(b011);break;
case TAG(link_kind,b100):HTEG_LINK(b100);break;
case TAG(link_kind,b101):HTEG_LINK(b101);break;
case TAG(link_kind,b110):HTEG_LINK(b110);break;
case TAG(link_kind,b111):HTEG_LINK(b111);break;
/*:212*/
#line 1551 "hint.w"

default:
TAGERR(z);
}
}

void hteg_content(void)
{/*88:*/
#line 1531 "hint.w"

uint8_t a,z;
z= HTEG8;DBGTAG(z,hpos);
/*:88*/
#line 1558 "hint.w"

node_pos= hpos-hstart;
hteg_node(z);
/*89:*/
#line 1536 "hint.w"

a= HTEG8;DBGTAG(a,hpos);
if(z!=a)tag_mismatch(a,z,hpos-hstart,node_pos);
/*:89*/
#line 1561 "hint.w"

node_pos= hpos-hstart;
if(nest_ptr==0&&tail!=head
#if 0
&&(type(tail)==penalty_node||type(tail)==glue_node
||type(tail)==hlist_node||type(tail)==vlist_node
||type(tail)==kern_node)
#endif
)
store_map(tail,node_pos,0);
}
/*:90*//*164:*/
#line 2761 "hint.w"

pointer hteg_disc_node(void)
{/*88:*/
#line 1531 "hint.w"

uint8_t a,z;
z= HTEG8;DBGTAG(z,hpos);
/*:88*/
#line 2763 "hint.w"

if(KIND(z)!=disc_kind||INFO(z)==b000)
tag_expected(TAG(disc_kind,1),z,node_pos);
{
HTEG_DISC(INFO(z));
/*89:*/
#line 1536 "hint.w"

a= HTEG8;DBGTAG(a,hpos);
if(z!=a)tag_mismatch(a,z,hpos-hstart,node_pos);
/*:89*/
#line 2768 "hint.w"

return p;
}
}
/*:164*//*186:*/
#line 3226 "hint.w"

void hteg_par_node(uint32_t offset)
{scaled x= 0;
ParamDef*save_lbp= line_break_params;
pointer p;
pointer par_head= tail;
uint8_t*bs_pos= cur_list.bs_pos;
scaled ph= prev_height;
/*82:*/
#line 1456 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:82*/
#line 3234 "hint.w"

node_pos= (hpos-hstart)-1;
if(INFO(a)&b100)x= hget_xdimen_node();else x= hget_xdimen_ref(HGET8);
if(INFO(a)&b010)line_break_params= hget_param_list_node();else line_break_params= hget_param_list_ref(HGET8);
prev_graf= 0;
p= hget_paragraph_initial(x,hstart+node_pos+offset);
/*83:*/
#line 1461 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:83*/
#line 3240 "hint.w"

cur_list.bs_pos= NULL;
if(p!=null)
line_break(hget_integer_ref(widow_penalty_no),p);
if(par_head!=tail)
/*185:*/
#line 3202 "hint.w"

{pointer p,r,par_tail;
p= null;
r= par_tail= link(par_head);

tail= par_head;
link(tail)= null;
while(r!=null)
{pointer q= link(r);
link(r)= p;
p= r;
r= q;
}
cur_list.bs_pos= bs_pos;
prev_height= ph;
hprepend_to_vlist(p);
tail= par_tail;
if(type(tail)==hlist_node||type(tail)==vlist_node)
prev_height= height(tail);
}
/*:185*/
#line 3245 "hint.w"

hpos= hstart+node_pos;
line_break_params= save_lbp;
}

/*:186*/
#line 8267 "hint.w"



/*18:*/
#line 458 "hint.w"

void print_xdimen(int i)
{}
/*:18*//*34:*/
#line 687 "hint.w"

uint16_t hglyph_section(uint8_t f)
{return font_def[f].q;
}

int32_t font_at_size(uint8_t f)
{return font_def[f].s;
}
/*:34*//*62:*/
#line 1097 "hint.w"

static void hinsert_stream(uint8_t n)
{REF_RNG(stream_kind,n);
if(streams[n].p==null)return;
DBG(DBGPAGE,"Filling in stream %d\n",n);
if(n> 0&&cur_page->s[n].b!=0)
{pointer p= copy_node_list(cur_page->s[n].b);
link(tail)= p;
while(link(p)!=null)p= link(p);
tail= p;
DBG(DBGPAGE,"Filling in before list %d\n",n);
}
link(tail)= streams[n].p;
tail= streams[n].t;
if(tail==null)QUIT("Tail of nonempty stream %d is null\n",n);
streams[n].p= streams[n].t= null;
DBG(DBGPAGE,"Filling in content list %d\n",n);
if(n> 0&&cur_page->s[n].a!=0)
{pointer p= copy_node_list(cur_page->s[n].a);
link(tail)= p;
while(link(p)!=null)p= link(p);
tail= p;
DBG(DBGPAGE,"Filling in after list %d\n",n);
}
}
/*:62*//*63:*/
#line 1127 "hint.w"

void hfill_page_template(void)
{pointer p;
if(cur_page->t!=0)
{
uint8_t*spos= hpos,*sstart= hstart,*send= hend;
hget_section(1);
hpos= hpos+cur_page->t;
p= hget_list_pointer();
hpos= spos,hstart= sstart,hend= send;
if(streams[0].p!=null)flush_node_list(streams[0].p);
}
else
{p= streams[0].p;
}
streams[0].p= streams[0].t= null;
houtput_template(p);
hmark_page();
}
/*:63*//*86:*/
#line 1488 "hint.w"


static void hget_node(uint8_t a)
{switch(a)
{
/*56:*/
#line 1018 "hint.w"

case TAG(stream_kind,b100):hinsert_stream(HGET8);break;
/*:56*//*101:*/
#line 1735 "hint.w"

case TAG(glyph_kind,1):HGET_GLYPH(1);break;
case TAG(glyph_kind,2):HGET_GLYPH(2);break;
case TAG(glyph_kind,3):HGET_GLYPH(3);break;
case TAG(glyph_kind,4):HGET_GLYPH(4);break;
/*:101*//*103:*/
#line 1750 "hint.w"

case TAG(penalty_kind,0):tail_append(new_penalty(hget_integer_ref(HGET8)));break;
case TAG(penalty_kind,1):{tail_append(new_penalty(HGET8));}break;
case TAG(penalty_kind,2):{int16_t n;HGET16(n);RNG("Penalty",n,-20000,+20000);tail_append(new_penalty(n));}break;
/*:103*//*105:*/
#line 1764 "hint.w"

case TAG(language_kind,b000):(void)HGET8;
case TAG(language_kind,1):
case TAG(language_kind,2):
case TAG(language_kind,3):
case TAG(language_kind,4):
case TAG(language_kind,5):
case TAG(language_kind,6):
case TAG(language_kind,7):break;
/*:105*//*109:*/
#line 1810 "hint.w"

case TAG(rule_kind,b000):tail_append(hget_rule_ref(HGET8));prev_depth= ignore_depth;break;
case TAG(rule_kind,b011):{HGET_RULE(b011);tail_append(p);prev_depth= ignore_depth;}break;
case TAG(rule_kind,b101):{HGET_RULE(b101);tail_append(p);prev_depth= ignore_depth;}break;
case TAG(rule_kind,b001):{HGET_RULE(b001);tail_append(p);prev_depth= ignore_depth;}break;
case TAG(rule_kind,b110):{HGET_RULE(b110);tail_append(p);prev_depth= ignore_depth;}break;
case TAG(rule_kind,b111):{HGET_RULE(b111);tail_append(p);prev_depth= ignore_depth;}break;
/*:109*//*116:*/
#line 1878 "hint.w"

case TAG(glue_kind,b000):tail_append(new_glue(hget_glue_ref(HGET8)));break;
case TAG(glue_kind,b001):{pointer p;HGET_GLUE(b001);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b010):{pointer p;HGET_GLUE(b010);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b011):{pointer p;HGET_GLUE(b011);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b100):{pointer p;HGET_GLUE(b100);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b101):{pointer p;HGET_GLUE(b101);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b110):{pointer p;HGET_GLUE(b110);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b111):{pointer p;HGET_GLUE(b111);tail_append(spec2glue(p));}break;
/*:116*//*126:*/
#line 2167 "hint.w"

case TAG(hbox_kind,b000):{pointer p;HGET_BOX(b000);happend_to_vlist(p);}break;
case TAG(hbox_kind,b001):{pointer p;HGET_BOX(b001);happend_to_vlist(p);}break;
case TAG(hbox_kind,b010):{pointer p;HGET_BOX(b010);happend_to_vlist(p);}break;
case TAG(hbox_kind,b011):{pointer p;HGET_BOX(b011);happend_to_vlist(p);}break;
case TAG(hbox_kind,b100):{pointer p;HGET_BOX(b100);happend_to_vlist(p);}break;
case TAG(hbox_kind,b101):{pointer p;HGET_BOX(b101);happend_to_vlist(p);}break;
case TAG(hbox_kind,b110):{pointer p;HGET_BOX(b110);happend_to_vlist(p);}break;
case TAG(hbox_kind,b111):{pointer p;HGET_BOX(b111);happend_to_vlist(p);}break;
case TAG(vbox_kind,b000):{pointer p;HGET_BOX(b000);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b001):{pointer p;HGET_BOX(b001);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b010):{pointer p;HGET_BOX(b010);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b011):{pointer p;HGET_BOX(b011);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b100):{pointer p;HGET_BOX(b100);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b101):{pointer p;HGET_BOX(b101);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b110):{pointer p;HGET_BOX(b110);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b111):{pointer p;HGET_BOX(b111);type(p)= vlist_node;happend_to_vlist(p);}break;
/*:126*//*133:*/
#line 2283 "hint.w"

case TAG(hset_kind,b000):{pointer p;HGET_SET(b000);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(hset_kind,b001):{pointer p;HGET_SET(b001);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(hset_kind,b010):{pointer p;HGET_SET(b010);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(hset_kind,b011):{pointer p;HGET_SET(b011);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(hset_kind,b100):{pointer p;HGET_SET(b100);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(hset_kind,b101):{pointer p;HGET_SET(b101);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(hset_kind,b110):{pointer p;HGET_SET(b110);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(hset_kind,b111):{pointer p;HGET_SET(b111);hset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;

case TAG(vset_kind,b000):{pointer p;HGET_SET(b000);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(vset_kind,b001):{pointer p;HGET_SET(b001);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(vset_kind,b010):{pointer p;HGET_SET(b010);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(vset_kind,b011):{pointer p;HGET_SET(b011);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(vset_kind,b100):{pointer p;HGET_SET(b100);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(vset_kind,b101):{pointer p;HGET_SET(b101);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(vset_kind,b110):{pointer p;HGET_SET(b110);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
case TAG(vset_kind,b111):{pointer p;HGET_SET(b111);vset(p,sto,st,sho,sh,x);happend_to_vlist(p);}break;
/*:133*//*139:*/
#line 2444 "hint.w"

case TAG(hpack_kind,b000):HGET_PACK(hpack_kind,b000);break;
case TAG(hpack_kind,b010):HGET_PACK(hpack_kind,b010);break;
case TAG(hpack_kind,b100):HGET_PACK(hpack_kind,b100);break;
case TAG(hpack_kind,b110):HGET_PACK(hpack_kind,b110);break;
case TAG(hpack_kind,b001):HGET_PACK(hpack_kind,b001);break;
case TAG(hpack_kind,b011):HGET_PACK(hpack_kind,b011);break;
case TAG(hpack_kind,b101):HGET_PACK(hpack_kind,b101);break;
case TAG(hpack_kind,b111):HGET_PACK(hpack_kind,b111);break;

case TAG(vpack_kind,b000):HGET_PACK(vpack_kind,b000);break;
case TAG(vpack_kind,b010):HGET_PACK(vpack_kind,b010);break;
case TAG(vpack_kind,b100):HGET_PACK(vpack_kind,b100);break;
case TAG(vpack_kind,b110):HGET_PACK(vpack_kind,b110);break;
case TAG(vpack_kind,b001):HGET_PACK(vpack_kind,b001);break;
case TAG(vpack_kind,b011):HGET_PACK(vpack_kind,b011);break;
case TAG(vpack_kind,b101):HGET_PACK(vpack_kind,b101);break;
case TAG(vpack_kind,b111):HGET_PACK(vpack_kind,b111);break;
/*:139*//*144:*/
#line 2527 "hint.w"

case TAG(kern_kind,b000):{HGET_KERN(b000);}break;
case TAG(kern_kind,b001):{HGET_KERN(b001);}break;
case TAG(kern_kind,b010):{HGET_KERN(b010);}break;
case TAG(kern_kind,b011):{HGET_KERN(b011);}break;
case TAG(kern_kind,b100):{HGET_KERN(b100);}break;
case TAG(kern_kind,b101):{HGET_KERN(b101);}break;
case TAG(kern_kind,b110):{HGET_KERN(b110);}break;
case TAG(kern_kind,b111):{HGET_KERN(b111);}break;
/*:144*//*148:*/
#line 2576 "hint.w"

case TAG(leaders_kind,0):tail_append(hget_leaders_ref(HGET8));break;
case TAG(leaders_kind,1):HGET_LEADERS(1);break;
case TAG(leaders_kind,2):HGET_LEADERS(2);break;
case TAG(leaders_kind,3):HGET_LEADERS(3);break;
case TAG(leaders_kind,b100|1):HGET_LEADERS(b100|1);break;
case TAG(leaders_kind,b100|2):HGET_LEADERS(b100|2);break;
case TAG(leaders_kind,b100|3):HGET_LEADERS(b100|3);break;
/*:148*//*152:*/
#line 2616 "hint.w"

case TAG(baseline_kind,b000):{cur_list.bs_pos= hpos-1;hget_baseline_ref(HGET8);}break;
case TAG(baseline_kind,b010):{HGET_BASELINE(b010);}break;
case TAG(baseline_kind,b011):{HGET_BASELINE(b011);}break;
case TAG(baseline_kind,b100):{HGET_BASELINE(b100);}break;
case TAG(baseline_kind,b101):{HGET_BASELINE(b101);}break;
case TAG(baseline_kind,b110):{HGET_BASELINE(b110);}break;
case TAG(baseline_kind,b111):{HGET_BASELINE(b111);}break;
/*:152*//*157:*/
#line 2676 "hint.w"

case TAG(ligature_kind,0):tail_append(hget_ligature_ref(HGET8));break;
case TAG(ligature_kind,1):HGET_LIG(1);break;
case TAG(ligature_kind,2):HGET_LIG(2);break;
case TAG(ligature_kind,3):HGET_LIG(3);break;
case TAG(ligature_kind,4):HGET_LIG(4);break;
case TAG(ligature_kind,5):HGET_LIG(5);break;
case TAG(ligature_kind,6):HGET_LIG(6);break;
case TAG(ligature_kind,7):HGET_LIG(7);break;
/*:157*//*161:*/
#line 2726 "hint.w"

case TAG(disc_kind,b000):tail_append(hget_hyphen_ref(HGET8));break;
case TAG(disc_kind,b001):{HGET_DISC(b001);tail_append(p);}break;
case TAG(disc_kind,b010):{HGET_DISC(b010);tail_append(p);}break;
case TAG(disc_kind,b011):{HGET_DISC(b011);tail_append(p);}break;
case TAG(disc_kind,b100):{HGET_DISC(b100);tail_append(p);}break;
case TAG(disc_kind,b101):{HGET_DISC(b101);tail_append(p);}break;
case TAG(disc_kind,b110):{HGET_DISC(b110);tail_append(p);}break;
case TAG(disc_kind,b111):{HGET_DISC(b111);tail_append(p);}break;
/*:161*//*166:*/
#line 2789 "hint.w"

case TAG(par_kind,b000):HGET_PAR(b000);break;
case TAG(par_kind,b010):HGET_PAR(b010);break;
case TAG(par_kind,b100):HGET_PAR(b100);break;
case TAG(par_kind,b110):HGET_PAR(b110);break;
/*:166*//*190:*/
#line 3281 "hint.w"

case TAG(math_kind,b000):HGET_MATH(b000);break;
case TAG(math_kind,b001):HGET_MATH(b001);break;
case TAG(math_kind,b010):HGET_MATH(b010);break;
case TAG(math_kind,b100):HGET_MATH(b100);break;
case TAG(math_kind,b101):HGET_MATH(b101);break;
case TAG(math_kind,b110):HGET_MATH(b110);break;
/*:190*//*192:*/
#line 3310 "hint.w"

case TAG(math_kind,b111):tail_append(new_math(0,before));break;
case TAG(math_kind,b011):tail_append(new_math(0,after));break;
/*:192*//*195:*/
#line 3336 "hint.w"

case TAG(adjust_kind,1):HGET_ADJUST(1);break;
/*:195*//*198:*/
#line 3364 "hint.w"

case TAG(table_kind,b000):HGET_TABLE(b000);break;
case TAG(table_kind,b001):HGET_TABLE(b001);break;
case TAG(table_kind,b010):HGET_TABLE(b010);break;
case TAG(table_kind,b011):HGET_TABLE(b011);break;
case TAG(table_kind,b100):HGET_TABLE(b100);break;
case TAG(table_kind,b101):HGET_TABLE(b101);break;
case TAG(table_kind,b110):HGET_TABLE(b110);break;
case TAG(table_kind,b111):HGET_TABLE(b111);break;

case TAG(item_kind,b000):hget_list_pointer();break;
case TAG(item_kind,b001):hget_content();break;
case TAG(item_kind,b010):hget_content();break;
case TAG(item_kind,b011):hget_content();break;
case TAG(item_kind,b100):hget_content();break;
case TAG(item_kind,b101):hget_content();break;
case TAG(item_kind,b110):hget_content();break;
case TAG(item_kind,b111):(void)HGET8;hget_content();break;
/*:198*//*203:*/
#line 3451 "hint.w"

case TAG(stream_kind,b000):HGET_STREAM(b000);break;
case TAG(stream_kind,b010):HGET_STREAM(b010);break;
/*:203*//*207:*/
#line 3505 "hint.w"

case TAG(image_kind,b000):hget_image_ref(HGET8);break;
case TAG(image_kind,b001):HGET_IMAGE(b001);break;
case TAG(image_kind,b010):HGET_IMAGE(b010);break;
case TAG(image_kind,b011):HGET_IMAGE(b011);break;
case TAG(image_kind,b100):HGET_IMAGE(b100);break;
case TAG(image_kind,b101):HGET_IMAGE(b101);break;
case TAG(image_kind,b110):HGET_IMAGE(b110);break;
case TAG(image_kind,b111):HGET_IMAGE(b111);break;
/*:207*//*209:*/
#line 3527 "hint.w"

case TAG(color_kind,b000):tail_append(hget_color_ref(HGET8));break;
/*:209*//*211:*/
#line 3538 "hint.w"

case TAG(link_kind,b000):HGET_LINK(b000);break;
case TAG(link_kind,b001):HGET_LINK(b001);break;
case TAG(link_kind,b010):HGET_LINK(b010);break;
case TAG(link_kind,b011):HGET_LINK(b011);break;
case TAG(link_kind,b100):HGET_LINK(b100);break;
case TAG(link_kind,b101):HGET_LINK(b101);break;
case TAG(link_kind,b110):HGET_LINK(b110);break;
case TAG(link_kind,b111):HGET_LINK(b111);break;
/*:211*/
#line 1493 "hint.w"

default:
if(!hget_unknown(a))
TAGERR(a);
break;
}
}

void hget_content(void)
{/*82:*/
#line 1456 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:82*/
#line 1502 "hint.w"

node_pos= (hpos-hstart)-1;
hget_node(a);
/*83:*/
#line 1461 "hint.w"

HGETTAG(z);
if(a!=z)tag_mismatch(a,z,node_pos,(uint32_t)(hpos-hstart-1));
/*:83*/
#line 1505 "hint.w"

if(nest_ptr==0&&tail!=head&&(type(tail)==penalty_node||type(tail)==glue_node||type(tail)==kern_node))
store_map(tail,node_pos,0);
}

static pointer hget_definition(uint8_t a)
{pointer p;
if(link(head)!=null)QUIT("Calling get_node with nonempty curent list");
hget_node(a);
p= link(head);
if(p!=null&&link(p)!=null)QUIT("get_node returns multiple nodes");
link(head)= null;
tail= head;
return p;
}
/*:86*//*179:*/
#line 3105 "hint.w"

void set_line_break_params(void)
{hset_param_list(line_break_params);
}
/*:179*//*218:*/
#line 3730 "hint.w"

pointer skip(uint8_t n)
{return cur_page->s[n].g;}
pointer*box_ptr(uint8_t n)
{return&streams[n].p;}
int count(uint8_t n)
{return cur_page->s[n].f;}
scaled dimen(uint8_t n)
{return xdimen(&cur_page->s[n].x);}

/*:218*//*219:*/
#line 3755 "hint.w"

void hpage_init(void)
{int i;
if(streams==NULL||cur_page==NULL)return;
for(i= 0;i<=max_ref[stream_kind];i++)
if(streams[i].p!=null)
{flush_node_list(streams[i].p);
streams[i].p= streams[i].t= null;
}
page_contents= empty;page_tail= page_head;link(page_head)= null;
hset_cur_page();
hset_margins();
page_depth= page_height= 0;
memset(top_so_far,0,sizeof(top_so_far));
max_depth= cur_page->d;
if(top_skip!=cur_page->g)
{delete_glue_ref(top_skip);
top_skip= cur_page->g;
add_glue_ref(top_skip);
}
}
/*:219*//*221:*/
#line 3786 "hint.w"

void hflush_contribution_list(void)
{if(link(contrib_head)!=null)
{flush_node_list(link(contrib_head));
link(contrib_head)= null;tail= contrib_head;
}
}
/*:221*//*223:*/
#line 3830 "hint.w"

static bool hbuild_page_up(void)
{
static scaled page_top_height;
pointer p;
pointer q,r;
int b,c;
int pi= 0;
if(link(contrib_head)==null)return false;
do{p= link(contrib_head);
/*228:*/
#line 3952 "hint.w"

switch(type(p)){
case hlist_node:case vlist_node:case rule_node:
/*225:*/
#line 3896 "hint.w"

if(page_contents<box_there)
{if(page_contents==empty)freeze_page_specs(box_there);
else page_contents= box_there;
if(depth(p)> page_max_depth)
page_total= depth(p)-page_max_depth;
depth(p)= 0;
/*226:*/
#line 3922 "hint.w"

{page_top_height= width(top_skip);
page_total= page_total+page_top_height;
}
/*:226*/
#line 3903 "hint.w"

}
/*227:*/
#line 3931 "hint.w"

{int i;
for(i= 1;i<=6;i++)
{page_so_far[i]+= top_so_far[i];
top_so_far[i]= 0;
}
}
/*:227*/
#line 3905 "hint.w"

page_total+= page_height+depth(p);
if(height(p)> page_top_height)
{page_total= page_total+height(p)-page_top_height;
page_height= page_top_height;
}
else
page_height= height(p);
/*:225*/
#line 3955 "hint.w"
goto contribute;
case whatsit_node:goto contribute;
case glue_node:/*231:*/
#line 3990 "hint.w"

if(link(p)==null)return false;
/*232:*/
#line 3997 "hint.w"

#define top_shrink top_so_far[6]
#define top_total top_so_far[1]

{pointer q= glue_ptr(p);
top_so_far[2+stretch_order(q)]+= stretch(q);
if((shrink_order(q)!=normal)&&(shrink(q)!=0))
DBG(DBGTEX,"Infinite glue shrinkage found on current page");
top_shrink+= shrink(q);
top_total+= width(q);
}
/*:232*/
#line 3992 "hint.w"

if(page_contents==empty||!precedes_break(link(p)))goto contribute;
pi= 0;
/*:231*/
#line 3957 "hint.w"
break;
case kern_node:/*233:*/
#line 4013 "hint.w"

top_total+= width(p);
if(page_contents==empty||
link(page_head)==null||
type(link(page_head))!=glue_node)
goto contribute;
pi= 0;
/*:233*/
#line 3958 "hint.w"
break;
case penalty_node:if(page_contents==empty)goto done1;else pi= penalty(p);break;
case ins_node:happend_insertion(p);goto contribute;
default:DBG(DBGTEX,"Unexpected node type %d in build_page_up ignored\n",type(p));
}
/*236:*/
#line 4047 "hint.w"

if(pi<inf_penalty)
{/*234:*/
#line 4027 "hint.w"

/*235:*/
#line 4038 "hint.w"

if(page_total<page_goal)
{if((page_so_far[3]!=0)||(page_so_far[4]!=0)||(page_so_far[5]!=0))b= 0;
else b= badness(page_goal-page_total,page_so_far[2]);
}
else if(page_total-page_goal> page_shrink)b= awful_bad;
else b= badness(page_total-page_goal,page_shrink)
/*:235*/
#line 4028 "hint.w"
;
if(b<awful_bad)
{if(pi<=eject_penalty)c= pi;
else if(b<inf_bad)c= b+pi+insert_penalties;
else c= deplorable;
}
else c= b;
if(insert_penalties>=10000)c= awful_bad;
/*:234*/
#line 4049 "hint.w"

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
{
/*237:*/
#line 4077 "hint.w"

if(p!=best_page_break)
{while(link(page_head)!=best_page_break)
{q= link(page_head);
link(page_head)= link(q);
link(q)= null;
link(q)= link(head);
link(head)= q;
}
}
/*:237*/
#line 4061 "hint.w"

/*238:*/
#line 4095 "hint.w"

hloc_set_prev(link(page_head));
while(true){
q= link(page_head);
if(q==null)return false;
else if(q==best_page_break)
break;
else if(type(q)==penalty_node||type(q)==glue_node||type(q)==kern_node)
{link(page_head)= link(q);link(q)= null;flush_node_list(q);}
else break;
}
temp_ptr= new_spec(top_skip);
q= new_glue(temp_ptr);glue_ref_count(temp_ptr)= null;
if(width(temp_ptr)> page_height)width(temp_ptr)= width(temp_ptr)-page_height;
else width(temp_ptr)= 0;
link(q)= link(page_head);
link(page_head)= q;
best_page_break= null;
/*:238*/
#line 4062 "hint.w"

hpack_page();
hfill_page_template();
return true;
}
}
/*:236*/
#line 3963 "hint.w"

contribute:
/*229:*/
#line 3970 "hint.w"

link(contrib_head)= link(p);
link(p)= link(page_head);
if(link(page_head)==null)page_tail= p;
link(page_head)= p;
goto done;
/*:229*/
#line 3965 "hint.w"

done1:/*230:*/
#line 3978 "hint.w"

link(contrib_head)= link(p);link(p)= null;flush_node_list(p);
/*:230*/
#line 3966 "hint.w"

done:
/*:228*/
#line 3840 "hint.w"
;
}while(link(contrib_head)!=null);
tail= contrib_head;
return false;
}
/*:223*//*240:*/
#line 4171 "hint.w"

static void clear_map(void)
{memset(map,0,sizeof(map));
}
/*:240*//*241:*/
#line 4184 "hint.w"

void store_map(pointer p,uint32_t pos0,uint32_t offset)
{map[p]= pos0;
map[p+1]= offset;
}

uint32_t hposition(pointer p)
{return map[p];
}
/*:241*//*248:*/
#line 4296 "hint.w"

void hloc_init(void)
{cur_loc= 0;
hloc_clear();
page_loc[cur_loc]= 0;
DBG(DBGPAGE,"loc_init: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
}
/*:248*//*253:*/
#line 4435 "hint.w"

int hint_begin(void)
{if(!hint_map())return 0;
hpos= hstart= hin_addr;
hend= hstart+hin_size;
hint_clear_fonts(true);
hflush_contribution_list();hpage_init();
flush_node_list(link(page_head));
free_definitions();
mem_init();
list_init();
hclear_dir();
hclear_fonts();
hget_banner();
if(!hcheck_banner("hint"))
{hint_unmap();return 0;}
hget_directory();
hget_definition_section();
hvsize= dimen_def[vsize_dimen_no];
hhsize= dimen_def[hsize_dimen_no];
hget_content_section();
leak_clear();
clear_map();
hloc_init();
return 1;
}

void hint_end(void)
{if(hin_addr==NULL)return;
hint_unmap();
hin_addr= hpos= hstart= hend= NULL;
hflush_contribution_list();hpage_init();
flush_node_list(link(page_head));
free_definitions();
list_leaks();
hclear_dir();
}
/*:253*//*257:*/
#line 4541 "hint.w"

bool hint_forward(void)
{hpage_init();
if(hbuild_page())return true;
while(hpos<hend)
{hget_content();
if(hbuild_page())return true;
}
while(!flush_pages(hend-hstart))
if(hbuild_page())return true;
return false;
}
/*:257*//*258:*/
#line 4582 "hint.w"

bool hint_backward(void)
{hpage_init();
if(hbuild_page_up())return true;
while(hpos> hstart)
{hteg_content();
if(hbuild_page_up())return true;
}
while(!flush_pages(0x0))
if(hbuild_page_up())return true;
return false;
}
/*:258*//*260:*/
#line 4610 "hint.w"

bool flush_pages(uint32_t pos)
{pointer p= link(head);
while(p!=null&&
(type(p)==penalty_node||type(p)==glue_node||type(p)==kern_node))
p= link(p);
if(p==null&&link(page_head)==null)return true;
tail_append(new_null_box());
width(tail)= hhsize;
tail_append(hget_param_glue(fill_skip_no));
store_map(tail,pos,0);
tail_append(new_penalty(-010000000000));
store_map(tail,pos,0);
return false;
}
/*:260*//*284:*/
#line 5176 "hint.w"

int hint_get_outline_max(void)
{return max_outline;}
/*:284*//*289:*/
#line 5256 "hint.w"

hint_Outline*hint_get_outlines(void)
{return hint_outlines;
}
/*:289*//*291:*/
#line 5315 "hint.w"

static bool trv_ignore= false;
static bool trv_skip_space= false;
static void(*trv_stream)(uint32_t c);
void trv_init(void(*f)(uint32_t c))
{trv_ignore= false;trv_skip_space= false;trv_stream= f;}

static void trv_char(uint32_t c)
{if(c==0x20)trv_skip_space= true;
else
{if(trv_skip_space)
{trv_skip_space= false;trv_stream(0x20);}
trv_stream(c);
}
}

void trv_hlist(pointer p)
{while(p!=null)
{if(is_char_node(p))
{if(!trv_ignore)trv_char(character(p));
}
else switch(type(p))
{case hlist_node:if(list_ptr(p)!=null)trv_hlist(list_ptr(p));break;
case vlist_node:if(list_ptr(p)!=null)trv_vlist(list_ptr(p));break;
case ligature_node:
if(!trv_ignore)
{pointer q= lig_ptr(p);
while(q!=null)
{trv_char(character(q));
q= link(q);
}
}
break;
case glue_node:
if(!trv_ignore)trv_skip_space= true;
break;
case whatsit_node:
if(subtype(p)==ignore_node)
{if(ignore_info(p)==1)
{trv_hlist(ignore_list(p));
trv_ignore= true;
}
else
trv_ignore= false;
}
break;
default:break;
}
p= link(p);
}
}

void trv_vlist(pointer p)
{while(p!=null)
{switch(type(p))
{case hlist_node:if(list_ptr(p)!=null)trv_hlist(list_ptr(p));
if(!trv_ignore)trv_skip_space= true;
break;
case vlist_node:if(list_ptr(p)!=null)trv_vlist(list_ptr(p));break;
default:break;
}
p= link(p);
}
}
/*:291*/
#line 8270 "hint.w"


/*:399*/
