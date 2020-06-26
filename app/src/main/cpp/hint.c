/*320:*/
#line 6072 "hint.w"

#include "basetypes.h"
#include <string.h> 
#include <math.h> 
#include <zlib.h> 
#include "error.h"
#include "hformat.h"

#include "texextern.h"
#include "hint.h"
#include "hrender.h"

#include "texdefs.h"
#include "hget.h"

/*75:*/
#line 1168 "hint.w"

#define HGET_STRING(S) S= (char*)hpos;\
 while(hpos<hend && *hpos!=0) { RNG("String character",*hpos,0x20,0x7E); hpos++;}\
 hpos++;
/*:75*//*76:*/
#line 1176 "hint.w"

#define HGET_UTF8C(X)  (X)= HGET8; if ((X&0xC0)!=0x80) \
  QUIT("UTF8 continuation byte expected at " SIZE_F " got 0x%02X\n",hpos-hstart-1,X)
/*:76*//*80:*/
#line 1228 "hint.w"

#define HGET_XDIMEN(I,X) \
{ if((I)&b100) HGET32((X).w); else (X).w= 0;\
  if((I)&b010) (X).h= hget_float32();  else (X).h= 0.0;\
  if((I)&b001) (X).v= hget_float32(); else (X).v= 0.0;\
}
/*:80*//*84:*/
#line 1332 "hint.w"

#define HGET_STRETCH(F,O) { stch_t _st;  HGET32(_st.u); (O)= _st.u&3;  _st.u&= ~3; (F)= (scaled)(_st.f*ONE); }
/*:84*//*86:*/
#line 1343 "hint.w"

#define HGET_GLYPH(I) \
{uint8_t f; uint32_t c;\
  if (I==1) c= HGET8;\
  else if (I==2) HGET16(c);\
  else if (I==3) HGET24(c);\
  else if (I==4) HGET32(c);\
  f= HGET8; REF_RNG(font_kind,f);\
  tail_append(new_character(f,c));\
}
/*:86*//*96:*/
#line 1434 "hint.w"

#define HGET_RULE(I)\
{ pointer p= new_rule();\
if ((I)&b100) HGET32(height(p)); else height(p)= null_flag;\
if ((I)&b010) HGET32(depth(p)); else depth(p)= null_flag;\
if ((I)&b001) HGET32(width(p)); else width(p)= null_flag;\
tail_append(p);}
/*:96*//*102:*/
#line 1498 "hint.w"

#define HGET_GLUE(I) \
  p=  get_node(glue_spec_size); \
  if(I==b111) width(p)= hget_xdimen_node(); \
  else { width(p)= 0; if((I)&b100) HGET32(width(p));} \
  if((I)&b010) HGET_STRETCH(stretch(p),stretch_order(p)) else stretch(p)= 0, stretch_order(p)= normal;\
  if((I)&b001) HGET_STRETCH(shrink(p),shrink_order(p)) else shrink(p)= 0, shrink_order(p)= normal;
/*:102*//*110:*/
#line 1617 "hint.w"

#define IS_LIST(X)  (KIND(X)==list_kind || KIND(X)==adjust_kind || \
        KIND(X)==text_kind  || KIND(X)==param_kind)
/*:110*//*115:*/
#line 1833 "hint.w"

#define HGET_BOX(I) \
p= new_null_box();\
HGET32(height(p));\
if ((I)&b001) HGET32(depth(p));\
HGET32(width(p));\
if ((I)&b010) HGET32(shift_amount(p));\
if ((I)&b100) {int8_t x; glue_set(p)= hget_float32();\
  x= HGET8;  glue_order(p)= x&0xF;\
  x= x>>4; glue_sign(p)= (x<0?shrinking:(x> 0?stretching:normal));}\
list_ptr(p)= hget_list();
/*:115*//*122:*/
#line 1959 "hint.w"

#define HGET_SET(I) \
 scaled x, st, sh; uint8_t sto, sho; \
 p= new_null_box();\
 if ((I)&b100) x=  hget_xdimen_node();  else x= hget_xdimen_ref(HGET8);\
 HGET32(height(p)); if ((I)&b001) HGET32(depth(p)); HGET32(width(p));\
 if ((I)&b010) HGET32(shift_amount(p));\
 HGET_STRETCH(st,sto);   HGET_STRETCH(sh,sho);\
 list_ptr(p)= hget_list();
/*:122*//*128:*/
#line 2102 "hint.w"

#define HGET_PACK(K,I) \
{ pointer p; scaled x, s= 0, d;  uint8_t m; \
 if ((I)&b100) x=  hget_xdimen_node();  else x= hget_xdimen_ref(HGET8);\
 if ((I)&b001) m= additional; else m= exactly; \
 if ((I)&b010) HGET32(s);\
 if (K==vpack_kind) HGET32(d); \
 p= hget_list(); \
 if (K==vpack_kind) p= vpackage(p,x,m,d); else p= hpack(p,x,m);\
 shift_amount(p)= s;\
 happend_to_vlist(p);}
/*:128*//*132:*/
#line 2169 "hint.w"

#define HGET_KERN(I) \
pointer p; scaled x; \
if (((I)&b011)==0) x= hget_dimen_ref(HGET8);\
else if (((I)&b011)==1) x= hget_xdimen_ref(HGET8);\
else if (((I)&b011)==2) HGET32(x);\
else if (((I)&b011)==3) x= hget_xdimen_node();\
p= new_kern(x);\
if ((I)&b100) subtype(p)= explicit;\
tail_append(p);
/*:132*//*136:*/
#line 2220 "hint.w"

#define HGET_LEADERS(I) \
{pointer p= hget_glue_node();subtype(p)= a_leaders+((I)&b011)-1;\
if (KIND(*hpos)==rule_kind) leader_ptr(p)= hget_rule_node(); \
else if (KIND(*hpos)==hbox_kind) leader_ptr(p)= hget_hbox_node(); \
else  leader_ptr(p)= hget_vbox_node();\
tail_append(p);}
/*:136*//*140:*/
#line 2256 "hint.w"

#define HGET_BASELINE(I) \
  cur_list.bs_pos= hpos-1; \
  if((I)&b100) cur_bs= hget_glue_spec(); else cur_bs= zero_glue; \
  if((I)&b010) cur_ls= hget_glue_spec(); else cur_ls= zero_glue; \
  if((I)&b001) HGET32(cur_lsl); else cur_lsl= 0; \
/*:140*//*144:*/
#line 2297 "hint.w"

#define HGET_LIG(I) \
{pointer p;uint8_t f; uint32_t c; uint8_t s,*t;\
f= HGET8;\
if ((I)==7) s= HGET8;else s= (I);\
t= hpos+s; c= hget_utf8(); hpos= t;\
if ((I)==7)\
{ uint8_t t; t= HGET8; \
  if(t!=s) \
  QUIT("Sizes in ligature don't match %d!=%d",s,t);}\
p= new_ligature(f, c, null); tail_append(p); \
}
/*:144*//*148:*/
#line 2352 "hint.w"

#define HGET_HYPHEN(I)\
  pointer p= new_disc(); \
  if ((I)&b100) pre_break(p)= hget_list(); \
  if ((I)&b010) post_break(p)= hget_list(); \
  if ((I)&b001) {uint8_t r; r= HGET8; set_replace_count(p,r); \
                 if ((r&0x80)==0) set_auto_disc(p); }\
  else  set_auto_disc(p);
/*:148*//*154:*/
#line 2425 "hint.w"

#define HGET_PAR(I) \
{ scaled x= 0;\
  param_def_t *q;\
  if ((I)&b100) x= hget_xdimen_node(); else x= hget_xdimen_ref(HGET8);\
  if ((I)&b010) q= hget_param_list_node(); else q= hget_param_list_ref(HGET8);\
  hget_paragraph(x,q,0);\
}
/*:154*//*168:*/
#line 2871 "hint.w"

#define HGET_MATH(I) \
{ param_def_t *q; pointer p= null, a= null;\
if ((I)&b100) q= hget_param_list_node(); else q= hget_param_list_ref(HGET8);\
if ((I)&b010) a= hget_hbox_node(); \
p= hget_list(); \
if ((I)&b001) a= hget_hbox_node();\
hset_param_list(q); hdisplay(p,a,((I)&b010)!=0); hrestore_param_list();\
}
/*:168*//*175:*/
#line 2945 "hint.w"

#define HGET_ADJUST(I) \
{ pointer p; uint32_t s,t;\
  p= get_node(small_node_size); type(p)= adjust_node; subtype(p)= normal;\
  s= hget_list_size(I); hget_size_boundary(I); \
  adjust_ptr(p)= hget_node_list(s);\
  tail_append(p);\
  hget_size_boundary(I);  t= hget_list_size(I); \
  if (t!=s) QUIT("List sizes at " SIZE_F " do not match 0x%x != 0x%x",hpos-hstart-1,s,t);\
}
/*:175*//*177:*/
#line 2969 "hint.w"

#define HGET_TABLE(I) \
if(I&b010) ; else ;\
if ((I)&b001) ; else ;\
if ((I)&b100) hget_xdimen_node(); else hget_xdimen_ref(HGET8);\
hget_list();  \
hget_list(); 
/*:177*//*182:*/
#line 3060 "hint.w"

#define HGET_STREAM(I) \
{ param_def_t *q;  pointer p;\
  p= get_node(ins_node_size); type(p)= ins_node;\
  subtype(p)= HGET8;RNG("Stream",subtype(p),1,254); \
  if ((I)&b010) q= hget_param_list_node(); else q= hget_param_list_ref(HGET8); \
  ins_ptr(p)= hget_list(); \
  if ((I)&b010) hset_stream_params(p,true,q); else hset_stream_params(p,false,q);\
  tail_append(p);}
/*:182*//*186:*/
#line 3092 "hint.w"

#define HGET_IMAGE(I) \
{ pointer p;\
  p= get_node(image_node_size);  type(p)= whatsit_node; subtype(p)= image_node;\
  HGET16(image_no(p));RNG("Section number",image_no(p),3,max_section_no);  \
  if (I&b010) {HGET32(image_width(p)); HGET32(image_height(p));} \
  else image_width(p)= image_height(p)= 0;\
  if (I&b001) {HGET_STRETCH(image_stretch(p),image_stretch_order(p)); \
               HGET_STRETCH(image_shrink(p),image_shrink_order(p));}\
  else { image_stretch(p)= image_shrink(p)= 0;image_stretch_order(p)= image_shrink_order(p)= normal;}\
  tail_append(p);}
/*:186*/
#line 6087 "hint.w"

/*70:*/
#line 1108 "hint.w"

#define HBACK(X) ((hpos-(X)<hstart)?(QUIT("HTEG underflow\n"),NULL):(hpos-= (X)))

#define HTEG8     (HBACK(1),hpos[0])
#define HTEG16(X) (HBACK(2),(X)= (hpos[0]<<8)+hpos[1])
#define HTEG24(X) (HBACK(3),(X)= (hpos[0]<<16)+(hpos[1]<<8)+hpos[2])
#define HTEG32(X) (HBACK(4),(X)= (hpos[0]<<24)+(hpos[1]<<16)+(hpos[2]<<8)+hpos[3])
/*:70*//*81:*/
#line 1236 "hint.w"

#define HTEG_XDIMEN(I,X) \
  if((I)&b001) (X).v= hteg_float32(); else (X).v= 0.0;\
  if((I)&b010) (X).h= hteg_float32();  else (X).h= 0.0;\
  if((I)&b100) HTEG32((X).w); else (X).w= 0;\
/*:81*//*85:*/
#line 1335 "hint.w"

#define HTEG_STRETCH(F,O) { stch_t _st;  HTEG32(_st.u); (O)= _st.u&3;  _st.u&= ~3; (F)= (scaled)(_st.f*ONE); }
/*:85*//*87:*/
#line 1355 "hint.w"

#define HTEG_GLYPH(I) \
{uint8_t f; uint32_t c;\
  f= HTEG8; REF_RNG(font_kind,f);\
  if (I==1) c= HTEG8;\
  else if (I==2) HTEG16(c);\
  else if (I==3) HTEG24(c);\
  else if (I==4) HTEG32(c);\
  tail_append(new_character(f,c));\
}
/*:87*//*97:*/
#line 1444 "hint.w"

#define HTEG_RULE(I)\
{ pointer p= new_rule();\
if ((I)&b001) HTEG32(width(p)); else width(p)= null_flag;\
if ((I)&b010) HTEG32(depth(p)); else depth(p)= null_flag;\
if ((I)&b100) HTEG32(height(p)); else height(p)= null_flag;\
tail_append(p);}
/*:97*//*104:*/
#line 1511 "hint.w"

#define HTEG_GLUE(I) \
  p=  get_node(glue_spec_size); \
  if((I)&b001) HTEG_STRETCH(shrink(p),shrink_order(p)) else shrink(p)= 0, shrink_order(p)= normal;\
  if((I)&b010) HTEG_STRETCH(stretch(p),stretch_order(p)) else stretch(p)= 0, stretch_order(p)= normal;\
  if(I==b111) width(p)= hteg_xdimen_node(); \
  else { width(p)= 0; if((I)&b100) HTEG32(width(p));}
/*:104*//*111:*/
#line 1621 "hint.w"

#define IS_LIST(X)  (KIND(X)==list_kind || KIND(X)==adjust_kind || \
        KIND(X)==text_kind  || KIND(X)==param_kind)
/*:111*//*116:*/
#line 1846 "hint.w"

#define HTEG_BOX(I) \
p= new_null_box();\
list_ptr(p)= hteg_list();\
if ((I)&b100) {int8_t x= HTEG8; glue_order(p)= x&0xF;\
   x= x>>4; glue_sign(p)= (x<0?shrinking:(x> 0?stretching:normal));\
   glue_set(p)= hteg_float32(); }\
if ((I)&b010) HTEG32(shift_amount(p));\
HTEG32(width(p));\
if ((I)&b001) HTEG32(depth(p));\
HTEG32(height(p));\
node_pos= hpos-hstart-1;
/*:116*//*123:*/
#line 1971 "hint.w"

#define HTEG_SET(I) \
  scaled x, st, sh; uint8_t sto, sho; \
  p= new_null_box();\
  list_ptr(p)= hteg_list();\
  HTEG_STRETCH(sh,sho);HTEG_STRETCH(st,sto);\
  if ((I)&b010) HTEG32(shift_amount(p)); \
  HTEG32(width(p));if ((I)&b001) HTEG32(depth(p));HTEG32(height(p)); \
  if ((I)&b100) x= hteg_xdimen_node(); else x= hget_xdimen_ref(HTEG8);\
  node_pos= hpos-hstart-1;
/*:123*//*129:*/
#line 2115 "hint.w"

#define HTEG_PACK(K,I) \
{ pointer p; scaled x, s, d;  uint8_t m; \
 p= hteg_list();\
 if (K==vpack_kind) HTEG32(d); \
 if ((I)&b010) HTEG32(s);\
 if ((I)&b001) m= additional; else m= exactly; \
 if ((I)&b100) x= hteg_xdimen_node();  else x= hget_xdimen_ref(HTEG8);\
 node_pos= hpos-hstart-1;\
 if (K==vpack_kind) p= vpackage(p,x,m,d); else p= hpack(p,x,m);\
 hprepend_to_vlist(p);}
/*:129*//*133:*/
#line 2182 "hint.w"

#define HTEG_KERN(I) \
pointer p; scaled x; \
if (((I)&b011)==0) x= hget_dimen_ref(HTEG8);\
else if (((I)&b011)==1) x= hget_xdimen_ref(HTEG8);\
else if (((I)&b011)==2) HTEG32(x);\
else if (((I)&b011)==3) x= hteg_xdimen_node();\
p= new_kern(x);\
if ((I)&b100) subtype(p)= explicit;\
tail_append(p);
/*:133*//*137:*/
#line 2229 "hint.w"

#define HTEG_LEADERS(I) \
{pointer p= hteg_glue_node();subtype(p)= a_leaders+((I)&b011)-1;\
if (KIND(*(hpos-1))==rule_kind) leader_ptr(p)= hteg_rule_node(); \
else if (KIND(*(hpos-1))==hbox_kind) leader_ptr(p)= hteg_hbox_node(); \
else  leader_ptr(p)= hteg_vbox_node();\
tail_append(p);}
/*:137*//*141:*/
#line 2264 "hint.w"

#define HTEG_BASELINE(I) \
  if((I)&b001) HTEG32(cur_lsl); else cur_lsl= 0; \
  if((I)&b010) cur_ls= hteg_glue_spec(); else cur_ls= zero_glue; \
  if((I)&b100) cur_bs= hteg_glue_spec(); else cur_bs= zero_glue; \
  cur_list.bs_pos= hpos-1;
/*:141*//*145:*/
#line 2311 "hint.w"

#define HTEG_LIG(I) \
{pointer p;uint8_t f; uint32_t c; uint8_t s,*t;\
if ((I)==7) s= HTEG8; else s= (I);\
t= hpos-s; hpos= t; c= hget_utf8(); hpos= t;\
if ((I)==7) { uint8_t n; n= HTEG8;\
  if(n!=s)   QUIT("Sizes in ligature don't match %d!=%d",s,n);}\
f= HTEG8;\
p= new_ligature(f, c, null); tail_append(p); \
}
/*:145*//*149:*/
#line 2362 "hint.w"

#define HTEG_HYPHEN(I)\
  pointer p= new_disc(); \
  if ((I)&b001) {uint8_t r; r= HTEG8; set_replace_count(p,r); \
                 if ((r&0x80)==0) set_auto_disc(p); }\
  else  set_auto_disc(p);\
  if ((I)&b010) post_break(p)= hteg_list(); \
  if ((I)&b100) pre_break(p)= hteg_list();
/*:149*//*169:*/
#line 2882 "hint.w"

#define HTEG_MATH(I) \
{ param_def_t *q; pointer p= null, a= null;\
if ((I)&b001) a= hteg_hbox_node();\
p= hteg_list(); \
if ((I)&b010) a= hteg_hbox_node(); \
if ((I)&b100) q= hteg_param_list_node(); else q= hget_param_list_ref(HTEG8);\
hset_param_list(q); hdisplay(p,a,((I)&b010)!=0); hrestore_param_list();\
}
/*:169*//*178:*/
#line 2978 "hint.w"

#define HTEG_TABLE(I) \
if(I&b010) ; else ;\
if ((I)&b001) ; else ;\
hteg_list();   \
hteg_list();  \
if ((I)&b100) hteg_xdimen_node(); else hget_xdimen_ref(HTEG8);
/*:178*//*183:*/
#line 3071 "hint.w"

#define HTEG_STREAM(I) \
{pointer p= get_node(ins_node_size); type(p)= ins_node;\
 ins_ptr(p)= hteg_list();\
 if ((I)&b010) {param_def_t *q= hteg_param_list_node();  hset_stream_params(p,true,q);}\
 else {param_def_t *q= hget_param_list_ref(HTEG8);  hset_stream_params(p,false,q);}\
 subtype(p)= HTEG8;RNG("Stream",subtype(p),1,254);\
 tail_append(p);}
/*:183*//*187:*/
#line 3105 "hint.w"

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
/*:187*/
#line 6088 "hint.w"



/*23:*/
#line 358 "hint.w"

typedef struct{pointer bs,ls;scaled lsl;}bs_t;
/*:23*//*32:*/
#line 480 "hint.w"

typedef struct{
char*n;
uint16_t m,q;
scaled s;
pointer g;
pointer h;
pointer p[MAX_FONT_PARAMS+1];
}font_def_t;
extern font_def_t*font_def;
/*:32*//*39:*/
#line 576 "hint.w"

typedef struct param_t{
uint8_t n,k;
union{int32_t i;
scaled d;
pointer g;};
}param_t;

typedef struct param_def_t{
struct param_def_t*next;
param_t p;}param_def_t;
/*:39*/
#line 6091 "hint.w"



/*2:*/
#line 187 "hint.w"

pointer*pointer_def[32]= {NULL};
/*:2*//*6:*/
#line 233 "hint.w"

int32_t*integer_def;
/*:6*//*10:*/
#line 263 "hint.w"

scaled*dimen_def;
/*:10*//*14:*/
#line 290 "hint.w"

xdimen_t*xdimen_def;
/*:14*//*24:*/
#line 362 "hint.w"

bs_t*baseline_def= NULL;
/*:24*//*33:*/
#line 492 "hint.w"

font_def_t*font_def;
/*:33*//*40:*/
#line 590 "hint.w"

param_def_t**param_def;
/*:40*//*47:*/
#line 719 "hint.w"

typedef struct{
uint8_t pg;
uint32_t f,t;
}range_def_t;
range_def_t*range_def;
/*:47*//*53:*/
#line 779 "hint.w"

typedef struct{
xdimen_t x;
int f;
int p,n,r;
pointer b,a;
xdimen_t w;
pointer g;
pointer h;
}stream_def_t;
/*:53*//*57:*/
#line 852 "hint.w"

typedef struct{
char*n;
dimen_t d;
pointer g;
uint8_t p;
uint32_t t;
xdimen_t v,h;
stream_def_t*s;
}page_def_t;
page_def_t*page_def;
page_def_t*cur_page;
/*:57*//*208:*/
#line 3503 "hint.w"

static scaled page_height;
static scaled top_so_far[8];
/*:208*//*228:*/
#line 3829 "hint.w"

static uint32_t map[0x10000];
/*:228*//*232:*/
#line 3893 "hint.w"

#define MAX_PAGE_POS (1<<3) 

uint64_t page_loc[MAX_PAGE_POS];
int cur_loc;
static int lo_loc,hi_loc;
/*:232*//*247:*/
#line 4226 "hint.w"

scaled hvsize,hhsize;
/*:247*//*249:*/
#line 4254 "hint.w"

int page_v,page_h,offset_v,offset_h;
/*:249*//*307:*/
#line 5774 "hint.w"

jmp_buf error_exit;
char herror_string[MAX_HERROR];
/*:307*/
#line 6094 "hint.w"

/*3:*/
#line 192 "hint.w"

static void hget_font_def(uint8_t a,uint8_t n);
static int32_t hget_integer_def(uint8_t a);
static scaled hget_dimen_def(void);
static pointer hget_glue_def(uint8_t a);
static void hget_baseline_def(uint8_t a,uint8_t n);
static param_def_t*hget_param_list(uint8_t a);
static void hget_range_def(uint8_t a,uint8_t pg);
static void hget_page_def(uint8_t a,uint8_t n);
static void hget_font_metrics();
static pointer hget_definition(uint8_t a);
/*:3*//*30:*/
#line 454 "hint.w"

static pointer hprepend_to_vlist(pointer b);
/*:30*//*37:*/
#line 560 "hint.w"

static pointer hget_glue_spec(void);
static pointer hget_hyphen_node(void);
/*:37*//*45:*/
#line 671 "hint.w"

static uint32_t hget_list_size(info_t info);
static void hget_size_boundary(info_t info);
/*:45*//*69:*/
#line 1102 "hint.w"

static void hget_content(void);
/*:69*//*74:*/
#line 1157 "hint.w"

static void hteg_content(void);
/*:74*//*103:*/
#line 1507 "hint.w"

static scaled hget_xdimen_node(void);
/*:103*//*117:*/
#line 1862 "hint.w"

static float32_t hget_float32(void);
static float32_t hteg_float32(void);
static pointer hget_list(void);
static pointer hteg_list(void);
/*:117*//*124:*/
#line 1982 "hint.w"

static scaled hget_xdimen_node(void);
/*:124*/
#line 6095 "hint.w"

/*9:*/
#line 246 "hint.w"

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
/*:9*//*18:*/
#line 305 "hint.w"

static scaled xdimen(xdimen_t*x)
{return round(x->w+(double)x->h*(double)hhsize+(double)x->v*(double)hvsize);
}
static scaled hget_xdimen_ref(uint8_t n)
{REF_RNG(xdimen_kind,n);
return xdimen(xdimen_def+n);
}
/*:18*//*20:*/
#line 325 "hint.w"

static pointer hget_glue_def(uint8_t a)
{pointer p;
HGET_GLUE(INFO(a));
return p;
}

static pointer hget_glue_ref(uint8_t n)
{REF_RNG(glue_kind,n);
return pointer_def[glue_kind][n];
}

pointer hget_param_glue(uint8_t n)
{REF_RNG(glue_kind,n);
return new_glue(pointer_def[glue_kind][n]);
}
/*:20*//*36:*/
#line 504 "hint.w"


static void hget_font_params(uint8_t n,font_def_t*f)
{HGET16(f->m);RNG("Font metrics",f->m,3,max_section_no);
HGET16(f->q);RNG("Font glyphs",f->q,3,max_section_no);
f->g= hget_glue_spec();
f->h= hget_hyphen_node();
DBG(DBGDEF,"Start font parameters\n");
while(KIND(*hpos)!=font_kind)
{kind_t k;
uint8_t n;
/*66:*/
#line 1050 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:66*/
#line 515 "hint.w"

k= KIND(a);
n= HGET8;
DBG(DBGDEF,"Reading font parameter %d: %s\n",n,definition_name[k]);
if(k!=penalty_kind&&k!=kern_kind&&k!=ligature_kind&&
k!=hyphen_kind&&k!=glue_kind&&k!=language_kind&&k!=rule_kind&&k!=image_kind)
QUIT("Font parameter %d has invalid type %s",n,content_name[n]);
RNG("Font parameter",n,0,MAX_FONT_PARAMS);
f->p[n]= hget_definition(a);
/*67:*/
#line 1055 "hint.w"

HGETTAG(z);
if(a!=z)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to "SIZE_F"\n",
NAME(a),INFO(a),NAME(z),INFO(z),node_pos,hpos-hstart-1);
/*:67*/
#line 524 "hint.w"

}
DBG(DBGDEF,"End font definition\n");
}
static void hget_font_def(uint8_t a,uint8_t n)
{char*t;
HGET_STRING(t);font_def[n].n= strdup(t);
DBG(DBGDEF,"Font %d: %s\n",n,t);
if(INFO(a)&b001)HGET32(font_def[n].s);else font_def[n].s= 0;
hget_font_params(n,&(font_def[n]));
}

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

uint16_t hglyph_section(uint8_t f)
{return font_def[f].q;
}
int32_t font_at_size(uint8_t f)
{return font_def[f].s;
}

/*:36*//*43:*/
#line 607 "hint.w"

static void free_param_list(param_def_t*p)
{while(p!=NULL)
{param_def_t*q= p;
p= p->next;
free(q);
}
}
/*:43*//*44:*/
#line 619 "hint.w"

static param_def_t*hget_param_list(uint8_t a)
{uint32_t s,t;
param_def_t*p= NULL;
uint8_t*list_start,*list_end;
list_start= hpos;
s= hget_list_size(INFO(a));
hget_size_boundary(INFO(a));
list_end= hpos+s;
if(list_end>=hend)
QUIT("list end after before stream end\n");
while(hpos<list_end)
{param_def_t*r;param_t*q;
/*66:*/
#line 1050 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:66*/
#line 632 "hint.w"

ALLOCATE(r,1,param_def_t);
q= &(r->p);
q->n= HGET8;
q->k= KIND(a);
DBG(DBGTAGS,"Defining %s %d\n",definition_name[KIND(a)],q->n);
if(KIND(a)==int_kind)q->i= hget_integer_def(a);
else if(KIND(a)==dimen_kind)q->d= hget_dimen_def();
else if(KIND(a)==glue_kind)q->g= hget_glue_def(a);
else TAGERR(a);
/*67:*/
#line 1055 "hint.w"

HGETTAG(z);
if(a!=z)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to "SIZE_F"\n",
NAME(a),INFO(a),NAME(z),INFO(z),node_pos,hpos-hstart-1);
/*:67*/
#line 642 "hint.w"

r->next= p;
p= r;
}
hget_size_boundary(INFO(a));
t= hget_list_size(INFO(a));
if(t!=s)
QUIT("List sizes at "SIZE_F" and "SIZE_F" do not match 0x%x != 0x%x",list_start-hstart,list_end-hstart,s,t);
return p;
}

param_def_t*hget_param_list_node(void)
{if(KIND(*hpos)!=param_kind)return NULL;
else
{param_def_t*p;
/*66:*/
#line 1050 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:66*/
#line 657 "hint.w"

p= hget_param_list(a);
/*67:*/
#line 1055 "hint.w"

HGETTAG(z);
if(a!=z)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to "SIZE_F"\n",
NAME(a),INFO(a),NAME(z),INFO(z),node_pos,hpos-hstart-1);
/*:67*/
#line 659 "hint.w"

return p;
}
}

param_def_t*hget_param_list_ref(uint8_t n)
{REF_RNG(param_kind,n);
return param_def[n];
}
/*:44*//*46:*/
#line 679 "hint.w"

#define MAX_SAVE 100
static param_t par_save[MAX_SAVE];
static int par_save_ptr;

void hset_param_list(param_def_t*p)
{par_save_ptr= 0;
while(p!=NULL)
{param_t*q;
if(par_save_ptr>=MAX_SAVE)QUIT("Parameter save stack overflow");
q= &(par_save[par_save_ptr++]);
q->k= p->p.k;
q->n= p->p.n;
if(q->k==int_kind)
{q->i= integer_def[q->n];integer_def[q->n]= p->p.i;}
else if(q->k==dimen_kind)
{q->d= dimen_def[q->n];dimen_def[q->n]= p->p.d;}
else if(q->k==glue_kind)
{q->g= pointer_def[glue_kind][q->n];pointer_def[glue_kind][q->n]= p->p.g;}
p= p->next;
}
}

void hrestore_param_list(void)
{
while(par_save_ptr> 0)
{param_t*q;
q= &(par_save[--par_save_ptr]);
if(q->k==int_kind)
{integer_def[q->n]= q->i;}
else if(q->k==dimen_kind)
{dimen_def[q->n]= q->d;}
else if(q->k==glue_kind)
{pointer_def[glue_kind][q->n]= q->g;}
}
par_save_ptr= 0;
}
/*:46*//*50:*/
#line 734 "hint.w"

static void hget_range_def(uint8_t a,uint8_t pg)
{static uint8_t n= 0;
uint32_t f,t;
REF_RNG(page_kind,pg);
REF_RNG(range_kind,n);
if(INFO(a)&b100)
{if(INFO(a)&b001)HGET32(f);else HGET16(f);}
else f= 0;
if(INFO(a)&b010)
{if(INFO(a)&b001)HGET32(t);else HGET16(t);}
else t= 0xFFFFFFFF;
range_def[n].pg= pg;
range_def[n].f= f;
range_def[n].t= t;
DBG(DBGRANGE,"Range *%d from 0x%x\n",pg,f);
DBG(DBGRANGE,"Range *%d to 0x%x\n",pg,t);
n++;
}
#if 0

static uint8_t hget_page_ref(uint32_t pos)
{int i;
for(i= 1;i<=max_ref[range_kind];i++)
if(range_def[i].f<=pos&&pos<range_def[i].t)return range_def[i].pg;
return 0;
}
#endif
/*:50*//*54:*/
#line 796 "hint.w"

static void hget_xdimen_def_node(xdimen_t*x);

static bool hget_stream_def(stream_def_t*s)
{if(KIND(*hpos)!=stream_kind||!(INFO(*hpos)&b100))
return false;
else
{uint8_t n;
/*66:*/
#line 1050 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:66*/
#line 804 "hint.w"

DBG(DBGDEF,"Defining stream %d at "SIZE_F"\n",*hpos,hpos-hstart-1);
n= HGET8;REF_RNG(stream_kind,n);
s= s+n;
if(n> 0)
{if(INFO(a)==b100)/*55:*/
#line 827 "hint.w"

{DBG(DBGDEF,"Defining normal stream %d at "SIZE_F"\n",*(hpos-1),hpos-hstart-2);
hget_xdimen_def_node(&(s->x));
HGET16(s->f);RNG("magnification factor",s->f,0,1000);
s->p= HGET8;if(s->p!=255)REF_RNG(stream_kind,s->p);
s->n= HGET8;if(s->n!=255)REF_RNG(stream_kind,s->n);
HGET16(s->r);RNG("split ratio",s->r,0,1000);
}
/*:55*/
#line 809 "hint.w"

else if(INFO(a)==b101)QUIT("first stream not yet implemented");
else if(INFO(a)==b110)QUIT("last stream not yet implemented");
else if(INFO(a)==b111)QUIT("top stream not yet implemented");
s->b= hget_list();
hget_xdimen_def_node(&(s->w));
s->g= hget_glue_spec();
s->a= hget_list();
s->h= hget_glue_spec();
}
/*67:*/
#line 1055 "hint.w"

HGETTAG(z);
if(a!=z)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to "SIZE_F"\n",
NAME(a),INFO(a),NAME(z),INFO(z),node_pos,hpos-hstart-1);
/*:67*/
#line 819 "hint.w"

return true;
}
}
/*:54*//*61:*/
#line 896 "hint.w"


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
ALLOCATE(cur_page->s,max_ref[stream_kind]+1,stream_def_t);
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
/*:61*//*64:*/
#line 986 "hint.w"

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

static pointer hget_hyphen_ref(uint8_t n)
{REF_RNG(hyphen_kind,n);
return copy_node_list(pointer_def[hyphen_kind][n]);
}

static pointer hget_leaders_ref(uint8_t n)
{REF_RNG(leaders_kind,n);
return copy_node_list(pointer_def[leaders_kind][n]);
}




/*:64*//*78:*/
#line 1208 "hint.w"

static float32_t hget_float32(void)
{union{float32_t d;uint32_t bits;}u;
HGET32(u.bits);
return u.d;
}
/*:78*//*79:*/
#line 1216 "hint.w"

static float32_t hteg_float32(void)
{union{float32_t d;uint32_t bits;}u;
HTEG32(u.bits);
return u.d;
}
/*:79*//*82:*/
#line 1243 "hint.w"


static void hget_xdimen_def(uint8_t a,xdimen_t*x)
{switch(a)
{
case TAG(xdimen_kind,b000):
{int n= HGET8;
REF_RNG(xdimen_kind,n);
x->w= xdimen_def[n].w;
x->h= xdimen_def[n].h;
x->v= xdimen_def[n].v;
break;
}
case TAG(xdimen_kind,b001):HGET_XDIMEN(b001,*x);break;
case TAG(xdimen_kind,b010):HGET_XDIMEN(b010,*x);break;
case TAG(xdimen_kind,b011):HGET_XDIMEN(b011,*x);break;
case TAG(xdimen_kind,b100):HGET_XDIMEN(b100,*x);break;
case TAG(xdimen_kind,b101):HGET_XDIMEN(b101,*x);break;
case TAG(xdimen_kind,b110):HGET_XDIMEN(b110,*x);break;
case TAG(xdimen_kind,b111):HGET_XDIMEN(b111,*x);break;
default:
x->w= 0;x->h= x->v= 0.0;
QUIT("Extent expected got [%s,%d]",NAME(a),INFO(a));
}
}
static scaled hget_xdimen(uint8_t a)
{xdimen_t x;
hget_xdimen_def(a,&x);
return xdimen(&x);
}

static scaled hget_xdimen_node(void)
{scaled x= 0;
/*66:*/
#line 1050 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:66*/
#line 1276 "hint.w"

if(KIND(a)==xdimen_kind)
x= hget_xdimen(a);
else
QUIT("Extent expected at 0x%x got %s",node_pos,NAME(a));
/*67:*/
#line 1055 "hint.w"

HGETTAG(z);
if(a!=z)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to "SIZE_F"\n",
NAME(a),INFO(a),NAME(z),INFO(z),node_pos,hpos-hstart-1);
/*:67*/
#line 1281 "hint.w"

return x;
}

static void hget_xdimen_def_node(xdimen_t*x)
{/*66:*/
#line 1050 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:66*/
#line 1286 "hint.w"

if(KIND(a)==xdimen_kind)
hget_xdimen_def(a,x);
else
QUIT("Extent expected at 0x%x got %s",node_pos,NAME(a));
/*67:*/
#line 1055 "hint.w"

HGETTAG(z);
if(a!=z)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to "SIZE_F"\n",
NAME(a),INFO(a),NAME(z),INFO(z),node_pos,hpos-hstart-1);
/*:67*/
#line 1291 "hint.w"

}


/*:82*//*83:*/
#line 1297 "hint.w"

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
return xdimen(&x);
}

scaled hteg_xdimen_node(void)
{scaled x= 0;
/*71:*/
#line 1119 "hint.w"

uint8_t a,z;
z= HTEG8,DBGTAG(z,hpos);
/*:71*/
#line 1319 "hint.w"

if(KIND(z)==xdimen_kind)
x= hteg_xdimen(z);
else
QUIT("Extent expected at 0x%x got %s",node_pos,NAME(z));
/*72:*/
#line 1124 "hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:72*/
#line 1324 "hint.w"

return x;
}
/*:83*//*101:*/
#line 1483 "hint.w"

static pointer hteg_rule_node(void)
{pointer p= null;
/*71:*/
#line 1119 "hint.w"

uint8_t a,z;
z= HTEG8,DBGTAG(z,hpos);
/*:71*/
#line 1486 "hint.w"

if(KIND(z)==rule_kind){HTEG_RULE(INFO(z));}
else QUIT("Rule expected at 0x%x got %s",node_pos,NAME(z));
/*72:*/
#line 1124 "hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:72*/
#line 1489 "hint.w"

return p;
}
/*:101*//*107:*/
#line 1545 "hint.w"

static pointer hget_glue_spec(void)
{pointer p= null;
uint8_t a,z;
if(hpos>=hend)return null;
if(KIND(*hpos)!=glue_kind)return null;
node_pos= hpos-hstart;
HGETTAG(a);
if(INFO(a)==b000)p= hget_glue_ref(HGET8);
else
{HGET_GLUE(INFO(a));}
/*67:*/
#line 1055 "hint.w"

HGETTAG(z);
if(a!=z)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to "SIZE_F"\n",
NAME(a),INFO(a),NAME(z),INFO(z),node_pos,hpos-hstart-1);
/*:67*/
#line 1556 "hint.w"

return p;
}

static pointer spec2glue(pointer q)
{pointer p;
p= get_node(small_node_size);type(p)= glue_node;subtype(p)= normal;
leader_ptr(p)= null;glue_ptr(p)= q;
return p;
}

static pointer hget_glue_node(void)
{pointer p= hget_glue_spec();
if(p!=null)return spec2glue(p);
else return new_glue(zero_glue);
}
/*:107*//*108:*/
#line 1574 "hint.w"

static pointer hteg_glue_spec(void)
{pointer p= null;
uint8_t a,z;
if(hpos<=hstart)return null;
if(KIND(*(hpos-1))!=glue_kind)return null;
z= HTEG8,DBGTAG(z,hpos);
if(INFO(z)==b000)p= hget_glue_ref(HTEG8);
else
{HTEG_GLUE(INFO(z));}
/*72:*/
#line 1124 "hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:72*/
#line 1584 "hint.w"

return p;
}


static pointer hteg_glue_node(void)
{pointer p= hteg_glue_spec();
if(p!=null)return spec2glue(p);
else return new_glue(zero_glue);
}
/*:108*//*112:*/
#line 1626 "hint.w"

static void hget_size_boundary(info_t info)
{uint32_t n;
if(info<2)return;
n= HGET8;
if(n-1!=0x100-info)QUIT("Size boundary byte 0x%x with info value %d at "SIZE_F,
n,info,hpos-hstart-1);
}

static uint32_t hget_list_size(info_t info)
{uint32_t n;
if(info==1)return 0;
else if(info==2)n= HGET8;
else if(info==3)HGET16(n);
else if(info==4)HGET24(n);
else if(info==5)HGET32(n);
else QUIT("List info %d must be 1, 2, 3, 4, or 5",info);
return n;
}

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

static pointer hget_text_list(uint32_t s)
{QUIT("Text not implemented");
return null;
}

static pointer hget_list(void)
{if(!IS_LIST(*hpos))return null;
else
{pointer p;
uint32_t s,t;
/*66:*/
#line 1050 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:66*/
#line 1670 "hint.w"

s= hget_list_size(INFO(a));
hget_size_boundary(INFO(a));
if(KIND(a)==list_kind)
p= hget_node_list(s);
else if(KIND(a)==text_kind)
p= hget_text_list(s);
hget_size_boundary(INFO(a));
t= hget_list_size(INFO(a));
if(t!=s)
QUIT("List sizes at 0x%x and "SIZE_F" do not match 0x%x != 0x%x",node_pos+1,hpos-hstart-s-1,s,t);
/*67:*/
#line 1055 "hint.w"

HGETTAG(z);
if(a!=z)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to "SIZE_F"\n",
NAME(a),INFO(a),NAME(z),INFO(z),node_pos,hpos-hstart-1);
/*:67*/
#line 1681 "hint.w"

return p;
}
}
/*:112*//*113:*/
#line 1691 "hint.w"

#if 0
void hteg_size_boundary(info_t info)
{uint32_t n;
if(info<2)return;
n= HTEG8;
if(n-1!=0x100-info)QUIT("Size boundary byte 0x%x with info value %d at "SIZE_F,
n,info,hpos-hstart);
}
#endif

static uint32_t hteg_list_size(info_t info)
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
cur_list.bs_pos= NULL;
while(hpos> list_start)
hteg_content();
if(needs_bs)
QUIT("Unexpected trailing baseline node");
p= link(head);
pop_nest();
return p;
}
#endif

static void hskip_list()
{if(IS_LIST(*hpos))
{uint32_t s;
uint8_t a;
HGETTAG(a);
s= hget_list_size(INFO(a));
if(s> 0)
hpos= hpos+(1+s+1+(INFO(a)-1)+1);
else
hpos= hpos+1;
}
}

static void hskip_list_back()
{uint8_t z;
uint32_t s;
if(!IS_LIST(*(hpos-1)))return;
z= HTEG8;
s= hteg_list_size(INFO(z));
if(s> 0)
hpos= hpos-(1+s+1+(INFO(z)-1)+1);
else
hpos= hpos-1;
}

pointer hteg_list(void)
{uint8_t*list_start;
pointer p;
hskip_list_back();
list_start= hpos;
p= hget_list();
hpos= list_start;
return p;
}
/*:113*//*114:*/
#line 1772 "hint.w"

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
#line 1119 "hint.w"

uint8_t a,z;
z= HTEG8,DBGTAG(z,hpos);
/*:71*/
#line 1794 "hint.w"

ALLOCATE(r,1,param_def_t);
q= &(r->p);
q->k= KIND(z);
if(KIND(z)==int_kind)q->i= hteg_integer_def(a);
else if(KIND(a)==dimen_kind)HTEG32(q->d);
else if(KIND(a)==glue_kind){pointer p;HTEG_GLUE(INFO(z));q->g= p;}
else TAGERR(a);
q->n= HTEG8;
DBG(DBGTAGS,"Defining %s %d\n",definition_name[KIND(z)],q->n);
/*72:*/
#line 1124 "hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:72*/
#line 1804 "hint.w"

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
hskip_list_back();
list_start= hpos;
p= hget_param_list_node();
hpos= list_start;
return p;
}
/*:114*//*121:*/
#line 1933 "hint.w"

static pointer hteg_hbox_node(void)
{/*71:*/
#line 1119 "hint.w"

uint8_t a,z;
z= HTEG8,DBGTAG(z,hpos);
/*:71*/
#line 1935 "hint.w"

if(KIND(z)!=hbox_kind)QUIT("Hbox expected at 0x%x got %s",node_pos,NAME(z));
{pointer p;
HTEG_BOX(INFO(z));
/*72:*/
#line 1124 "hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:72*/
#line 1939 "hint.w"

return p;
}
}
static pointer hteg_vbox_node(void)
{/*71:*/
#line 1119 "hint.w"

uint8_t a,z;
z= HTEG8,DBGTAG(z,hpos);
/*:71*/
#line 1944 "hint.w"

if(KIND(z)!=vbox_kind)QUIT("Vbox expected at 0x%x got %s",node_pos,NAME(z));
{pointer p;
HTEG_BOX(INFO(z));
/*72:*/
#line 1124 "hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:72*/
#line 1948 "hint.w"

type(p)= vlist_node;
return p;
}
}

/*:121*//*127:*/
#line 2030 "hint.w"

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
}
/*:127*//*152:*/
#line 2396 "hint.w"

static pointer hget_hyphen_node(void)
{/*66:*/
#line 1050 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:66*/
#line 2398 "hint.w"

if(KIND(a)!=hyphen_kind||INFO(a)==b000)
QUIT("Hyphen expected at 0x%x got %s,%d",node_pos,NAME(a),INFO(a));
{
HGET_HYPHEN(INFO(a));
/*67:*/
#line 1055 "hint.w"

HGETTAG(z);
if(a!=z)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to "SIZE_F"\n",
NAME(a),INFO(a),NAME(z),INFO(z),node_pos,hpos-hstart-1);
/*:67*/
#line 2403 "hint.w"

return p;
}
}
/*:152*//*156:*/
#line 2471 "hint.w"

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


static void hprune_unwanted_nodes(void)
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
/*:156*//*157:*/
#line 2538 "hint.w"

pointer hget_paragraph_all(scaled x)
{
uint32_t s,t;
uint8_t a,z;
if(!IS_LIST(*hpos))return null;
HGETTAG(a);
s= hget_list_size(INFO(a));
hget_size_boundary(INFO(a));
if(KIND(a)==list_kind)
{uint8_t*list_end= hpos+s;
cur_list.hs_field= x;
push_nest();
cur_list.bs_pos= NULL;
#if 0
if(offset> 0)hpos= hstart+node_pos1+offset;
#endif
while(hpos<list_end)
{hget_content();
if(nest_ptr==1)
{pointer p= tail;
if(p!=head&&!is_char_node(p)&&
(type(p)==glue_node||type(p)==kern_node||type(p)==penalty_node
||type(p)==disc_node||type(p)==math_node))
store_map(p,node_pos,0);

}
}
hget_size_boundary(INFO(a));
t= hget_list_size(INFO(a));
if(t!=s)
QUIT("List sizes at 0x%x and "SIZE_F" do not match 0x%x != 0x%x",node_pos+1,hpos-hstart-s-1,s,t);
/*67:*/
#line 1055 "hint.w"

HGETTAG(z);
if(a!=z)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to "SIZE_F"\n",
NAME(a),INFO(a),NAME(z),INFO(z),node_pos,hpos-hstart-1);
/*:67*/
#line 2570 "hint.w"

#if 0
if(offset> 0&&link(head)!=null&&!is_char_node(link(head)))
{if(type(link(head))==disc_node)
transplant_post_break_list();
else
hprune_unwanted_nodes();
}
#endif
if(needs_bs)
QUIT("Unexpected trailing baseline node");
if(head==tail)
{pop_nest();
return null;
}
else
{pointer par_ptr= link(head);
add_par_fill_skip();
pop_nest();
store_map(par_ptr,node_pos,0);
return par_ptr;
}
}
else
QUIT("Text in paragraph not yet implemented");
return null;
}
/*:157*//*158:*/
#line 2602 "hint.w"

pointer hget_paragraph_final(scaled x,uint8_t*from)
{
uint32_t s,t;
uint8_t a,z;
if(!IS_LIST(*hpos))return null;
HGETTAG(a);
s= hget_list_size(INFO(a));
hget_size_boundary(INFO(a));
if(KIND(a)==list_kind)
{uint8_t*list_end= hpos+s;
cur_list.hs_field= x;
push_nest();
cur_list.bs_pos= NULL;
hpos= from;
while(hpos<list_end)
{hget_content();
if(nest_ptr==1)
{pointer p= tail;
if(p!=head&&!is_char_node(p)&&
(type(p)==glue_node||type(p)==kern_node||type(p)==penalty_node||type(p)==disc_node||type(p)==math_node))
store_map(p,node_pos,0);
}
}
hget_size_boundary(INFO(a));
t= hget_list_size(INFO(a));
if(t!=s)
QUIT("List sizes at 0x%x and "SIZE_F" do not match 0x%x != 0x%x",node_pos+1,hpos-hstart-s-1,s,t);
/*67:*/
#line 1055 "hint.w"

HGETTAG(z);
if(a!=z)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to "SIZE_F"\n",
NAME(a),INFO(a),NAME(z),INFO(z),node_pos,hpos-hstart-1);
/*:67*/
#line 2630 "hint.w"

if(link(head)!=null&&!is_char_node(link(head)))
{if(type(link(head))==disc_node)
transplant_post_break_list();
else
hprune_unwanted_nodes();
}
if(needs_bs)
QUIT("Unexpected trailing baseline node");
if(head==tail)
{pop_nest();
return null;
}
else
{pointer par_ptr= link(head);
add_par_fill_skip();
pop_nest();
store_map(par_ptr,node_pos,0);
return par_ptr;
}
}
else
QUIT("Text in paragraph not yet implemented");
return null;
}
/*:158*//*161:*/
#line 2733 "hint.w"

pointer hget_paragraph(scaled x,param_def_t*q,uint32_t offset)
{
pointer p,par_head;
par_head= tail;
if(offset==0)
{prev_graf= 0;
p= hget_paragraph_all(x);
}
else
{prev_graf= 3;
p= hget_paragraph_final(x,hstart+node_pos+offset);
}
hset_param_list(q);
if(p!=null)
line_break(hget_integer_ref(widow_penalty_no),p);
hrestore_param_list();
return par_head;
}

void hget_par_node(uint32_t offset)
{scaled x= 0;
param_def_t*q;
/*66:*/
#line 1050 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:66*/
#line 2756 "hint.w"

node_pos= (hpos-hstart)-1;
if(INFO(a)&b100)x= hget_xdimen_node();else x= hget_xdimen_ref(HGET8);
if(INFO(a)&b010)q= hget_param_list_node();else q= hget_param_list_ref(HGET8);
hget_paragraph(x,q,offset);
/*67:*/
#line 1055 "hint.w"

HGETTAG(z);
if(a!=z)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to "SIZE_F"\n",
NAME(a),INFO(a),NAME(z),INFO(z),node_pos,hpos-hstart-1);
/*:67*/
#line 2761 "hint.w"

}
/*:161*//*164:*/
#line 2783 "hint.w"

void hteg_paragraph(info_t i)
{scaled x= 0;
param_def_t*q;
pointer par_head;
uint8_t*bs_pos= cur_list.bs_pos;
scaled ph= prev_height;
uint8_t*list_start,*par_start;
hskip_list_back();
list_start= hpos;
if(INFO(i)&b010)q= hteg_param_list_node();else q= hget_param_list_ref(HTEG8);
if(INFO(i)&b100)x= hteg_xdimen_node();else x= hget_xdimen_ref(HTEG8);
par_start= hpos;
node_pos= par_start-hstart-1;
hpos= list_start;
cur_list.bs_pos= NULL;
par_head= hget_paragraph(x,q,0);
/*165:*/
#line 2813 "hint.w"

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
/*:165*/
#line 2800 "hint.w"

hpos= par_start;
}
/*:164*//*181:*/
#line 3038 "hint.w"

void hset_stream_params(pointer p,bool f,param_def_t*q)
{param_def_t*r;
pointer s;
while(q!=null)
{r= q;
if(q->p.k==int_kind&&q->p.n==floating_penalty_no)float_cost(p)= q->p.i;
else if(q->p.k==dimen_kind&&q->p.n==split_max_depth_no)depth(p)= q->p.d;
else if(q->p.k==glue_kind&&q->p.n==split_top_skip_no)
{split_top_ptr(p)= q->p.g;if(!f)add_glue_ref(q->p.g);}
else QUIT("Unexpected parameter in stream");
q= q->next;
if(f)free(r);
}
s= vpack(ins_ptr(p),natural);
height(p)= height(s)+depth(s);
ins_ptr(p)= list_ptr(s);
list_ptr(s)= null;flush_node_list(s);
}
/*:181*//*231:*/
#line 3872 "hint.w"

uint64_t hlocation(pointer p)
{return(uint64_t)(map[p])+(((uint64_t)map[p+1])<<32);
}
/*:231*//*234:*/
#line 3917 "hint.w"

#define NEXT_PAGE(X) (X= (X+1)&(MAX_PAGE_POS-1))
#define PREV_PAGE(X) (X= (X-1)&(MAX_PAGE_POS-1))

void hloc_clear(void)
{lo_loc= hi_loc= cur_loc;PREV_PAGE(lo_loc);NEXT_PAGE(hi_loc);
}

bool hloc_next(void)
{int i= cur_loc;
if((page_loc[cur_loc]&0xffffffff)>=hend-hstart)
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


/*:234*//*237:*/
#line 3978 "hint.w"


void hloc_set(uint64_t h)
{int i;
if(page_loc[cur_loc]==h)return;
for(i= lo_loc,NEXT_PAGE(i);i!=hi_loc;NEXT_PAGE(i))
if(page_loc[i]==h)
{cur_loc= i;return;}
page_loc[cur_loc]= h;
hloc_clear();
DBG(DBGPAGE,"loc_set: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
}
/*:237*//*238:*/
#line 4002 "hint.w"


void hloc_set_next(pointer p)
{int i= cur_loc;
uint64_t h= hlocation(p);

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
/*:238*//*239:*/
#line 4038 "hint.w"

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
/*:239*//*250:*/
#line 4264 "hint.w"

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
}
}
/*:250*//*252:*/
#line 4294 "hint.w"

static void houtput_template0(void)
{pointer p,q,r;
if(streams[0].p==null)return;
p= vpackage(streams[0].p,hvsize,exactly,page_max_depth);
r= new_kern(offset_v);
link(r)= p;
q= new_null_box();
type(q)= vlist_node;
width(q)= width(p)+offset_h;
height(q)= height(p)+offset_v;depth(q)= depth(p);
list_ptr(q)= r;
shift_amount(p)+= offset_h;
streams[0].p= q;
}
/*:252*//*317:*/
#line 6003 "hint.w"

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
/*:317*/
#line 6096 "hint.w"

/*1:*/
#line 111 "hint.w"

void hget_def_node(void)
{uint8_t n;
/*66:*/
#line 1050 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:66*/
#line 114 "hint.w"

n= HGET8;
if(max_fixed[KIND(a)]> max_default[KIND(a)])
QUIT("Definitions for kind %s not supported",definition_name[KIND(a)]);
if(n> max_ref[KIND(a)]||n<=max_fixed[KIND(a)])
QUIT("Definition %d for %s out of range [%d - %d]",
n,definition_name[KIND(a)],max_fixed[KIND(a)]+1,max_ref[KIND(a)]);

if(KIND(a)!=range_kind)REF_RNG(KIND(a),n);
DBG(DBGTAGS,"Defining %s %d\n",definition_name[KIND(a)],n);
switch(KIND(a))
{case language_kind:{char*t;HGET_STRING(t);break;}
case font_kind:hget_font_def(a,n);break;
case int_kind:integer_def[n]= hget_integer_def(a);break;
case dimen_kind:dimen_def[n]= hget_dimen_def();break;
case xdimen_kind:hget_xdimen_def(a,&(xdimen_def[n]));break;
case baseline_kind:hget_baseline_def(a,n);break;
case glue_kind:pointer_def[glue_kind][n]= hget_glue_def(a);break;
case param_kind:param_def[n]= hget_param_list(a);break;
case range_kind:hget_range_def(a,n);break;
case page_kind:hget_page_def(a,n);break;
default:pointer_def[KIND(a)][n]= hget_definition(a);break;
}
/*67:*/
#line 1055 "hint.w"

HGETTAG(z);
if(a!=z)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to "SIZE_F"\n",
NAME(a),INFO(a),NAME(z),INFO(z),node_pos,hpos-hstart-1);
/*:67*/
#line 137 "hint.w"

}

pointer hset_glue(glue_t*g)
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
}


void hget_definition_section(void)
{DBG(DBGDEF,"Definitions\n");
hget_section(1);
DBG(DBGDEF,"Reading list of maximum values\n");
/*5:*/
#line 221 "hint.w"

{int k;
for(k= 0;k<32;k++)
{free(pointer_def[k]);pointer_def[k]= NULL;}
}
/*:5*//*8:*/
#line 242 "hint.w"

free(integer_def);integer_def= NULL;
/*:8*//*12:*/
#line 271 "hint.w"

free(dimen_def);dimen_def= NULL;
/*:12*//*16:*/
#line 297 "hint.w"

free(xdimen_def);xdimen_def= NULL;
/*:16*//*26:*/
#line 370 "hint.w"

free(baseline_def);baseline_def= NULL;
/*:26*//*35:*/
#line 500 "hint.w"

free(font_def);font_def= NULL;
/*:35*//*42:*/
#line 598 "hint.w"

if(param_def!=NULL)
{int i;
for(i= 0;i<=max_ref[param_kind];i++)
free_param_list(param_def[i]);
}
free(param_def);param_def= NULL;
/*:42*//*49:*/
#line 730 "hint.w"

free(range_def);range_def= NULL;
/*:49*//*52:*/
#line 773 "hint.w"

free(streams);streams= NULL;
/*:52*//*60:*/
#line 886 "hint.w"

if(page_def!=NULL)
{int k;
for(k= 0;k<=max_ref[page_kind];k++)
{free(page_def[k].s);free(page_def[k].n);
}
free(page_def);page_def= NULL;cur_page= NULL;
}
/*:60*/
#line 172 "hint.w"

hget_max_definitions();
/*4:*/
#line 206 "hint.w"

{kind_t k;
for(k= 0;k<32;k++)
{if(k==font_kind||k==int_kind||k==dimen_kind||k==xdimen_kind||
k==glue_kind||k==baseline_kind||k==range_kind||k==page_kind||k==param_kind||k==stream_kind)
continue;
if(max_ref[k]>=0&&max_ref[k]<=256)
{DBG(DBGDEF,"Allocating definitions for %s (kind %d): %d entries of "SIZE_F" byte each\n",
definition_name[k],k,max_ref[k]+1,sizeof(pointer));
ALLOCATE(pointer_def[k],max_ref[k]+1,pointer);
}
}
}
/*:4*//*7:*/
#line 238 "hint.w"

ALLOCATE(integer_def,max_ref[int_kind]+1,int32_t);
/*:7*//*11:*/
#line 267 "hint.w"

ALLOCATE(dimen_def,max_ref[dimen_kind]+1,dimen_t);
/*:11*//*15:*/
#line 294 "hint.w"

ALLOCATE(xdimen_def,max_ref[xdimen_kind]+1,xdimen_t);
/*:15*//*22:*/
#line 347 "hint.w"

ALLOCATE(pointer_def[glue_kind],max_ref[glue_kind]+1,pointer);
/*:22*//*25:*/
#line 366 "hint.w"

ALLOCATE(baseline_def,max_ref[baseline_kind]+1,bs_t);
/*:25*//*34:*/
#line 496 "hint.w"

ALLOCATE(font_def,max_ref[font_kind]+1,font_def_t);
/*:34*//*41:*/
#line 594 "hint.w"

ALLOCATE(param_def,max_ref[param_kind]+1,param_def_t*);
/*:41*//*48:*/
#line 726 "hint.w"

ALLOCATE(range_def,max_ref[range_kind]+1,range_def_t);
/*:48*//*51:*/
#line 769 "hint.w"

ALLOCATE(streams,max_ref[stream_kind]+1,stream_t);
/*:51*//*58:*/
#line 866 "hint.w"

ALLOCATE(page_def,max_ref[page_kind]+1,page_def_t);
/*:58*/
#line 174 "hint.w"

hset_default_definitions();
DBG(DBGDEF,"Reading list of definitions\n");
while(hpos<hend)
hget_def_node();
hget_font_metrics();
page_v= hvsize= dimen_def[vsize_dimen_no];
page_h= hhsize= dimen_def[hsize_dimen_no];
/*59:*/
#line 870 "hint.w"

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
ALLOCATE(page_def[0].s,max_ref[stream_kind]+1,stream_def_t);
cur_page= &(page_def[0]);
/*:59*/
#line 182 "hint.w"

}
/*:1*//*13:*/
#line 275 "hint.w"

static scaled hget_dimen_def(void)
{scaled d;HGET32(d);return d;
}

scaled hget_dimen_ref(uint8_t n)
{REF_RNG(dimen_kind,n);
return dimen_def[n];
}
/*:13*//*27:*/
#line 374 "hint.w"

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
/*:27*//*29:*/
#line 433 "hint.w"

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
/*:29*//*65:*/
#line 1036 "hint.w"

void hget_content_section()
{DBG(DBGDIR,"Reading Content Section\n");
hget_section(2);
}
/*:65*//*77:*/
#line 1181 "hint.w"

uint32_t hget_utf8(void)
{uint8_t a;
a= HGET8;
if(a<0x80)return a;
else
{if((a&0xE0)==0xC0)
{uint8_t b;HGET_UTF8C(b);
return((a&~0xE0)<<6)+(b&~0xC0);
}
else if((a&0xF0)==0xE0)
{uint8_t b,c;HGET_UTF8C(b);HGET_UTF8C(c);
return((a&~0xF0)<<12)+((b&~0xC0)<<6)+(c&~0xC0);
}
else if((a&0xF8)==0xF0)
{uint8_t b,c,d;HGET_UTF8C(b);HGET_UTF8C(c);HGET_UTF8C(d);
return((a&~0xF8)<<18)+((b&~0xC0)<<12)+((c&~0xC0)<<6)+(d&~0xC0);
}
else QUIT("UTF8 byte sequence expected");
}
}
/*:77*//*100:*/
#line 1472 "hint.w"

pointer hget_rule_node(void)
{pointer p= null;
/*66:*/
#line 1050 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:66*/
#line 1475 "hint.w"

if(KIND(a)==rule_kind){HGET_RULE(INFO(a));}
else QUIT("Rule expected at 0x%x got %s",node_pos,NAME(a));
/*67:*/
#line 1055 "hint.w"

HGETTAG(z);
if(a!=z)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to "SIZE_F"\n",
NAME(a),INFO(a),NAME(z),INFO(z),node_pos,hpos-hstart-1);
/*:67*/
#line 1478 "hint.w"

return p;
}
/*:100*//*120:*/
#line 1908 "hint.w"

pointer hget_hbox_node(void)
{/*66:*/
#line 1050 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:66*/
#line 1910 "hint.w"

if(KIND(a)!=hbox_kind)QUIT("Hbox expected at 0x%x got %s",node_pos,NAME(a));
{pointer p;
HGET_BOX(INFO(a));
/*67:*/
#line 1055 "hint.w"

HGETTAG(z);
if(a!=z)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to "SIZE_F"\n",
NAME(a),INFO(a),NAME(z),INFO(z),node_pos,hpos-hstart-1);
/*:67*/
#line 1914 "hint.w"

return p;
}
}


pointer hget_vbox_node(void)
{
/*66:*/
#line 1050 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:66*/
#line 1922 "hint.w"

if(KIND(a)!=vbox_kind)QUIT("Vbox expected at 0x%x got %s",node_pos,NAME(a));
{pointer p;
HGET_BOX(INFO(a));
/*67:*/
#line 1055 "hint.w"

HGETTAG(z);
if(a!=z)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to "SIZE_F"\n",
NAME(a),INFO(a),NAME(z),INFO(z),node_pos,hpos-hstart-1);
/*:67*/
#line 1926 "hint.w"

type(p)= vlist_node;
return p;
}
}
/*:120*//*159:*/
#line 2658 "hint.w"

pointer hget_paragraph_initial(scaled x,uint8_t*to)
{
uint8_t*node_start;
uint32_t s,t;
uint8_t a,z;
node_start= hpos;
HGETTAG(a);
if(!IS_LIST(a))
{hpos= node_start;return null;}
s= hget_list_size(INFO(a));
hget_size_boundary(INFO(a));
if(KIND(a)==list_kind)
{uint8_t*list_end= hpos+s;if(to> list_end){LOG("Value of to greater than list_end");to= list_end;}
cur_list.hs_field= x;
push_nest();
cur_list.bs_pos= NULL;
while(hpos<to)
{hget_content();
if(nest_ptr==1)
{pointer p= tail;
if(p!=head&&!is_char_node(p)&&
(type(p)==glue_node||type(p)==kern_node||type(p)==penalty_node||type(p)==disc_node||type(p)==math_node))
store_map(p,node_pos,0);
}
}
if(KIND(*to)==hyphen_kind)
{hget_content();
store_map(tail,node_pos,0);
transplant_pre_break_list();
}
hpos= list_end;
hget_size_boundary(INFO(a));
t= hget_list_size(INFO(a));
if(t!=s)
QUIT("List sizes at 0x%x and "SIZE_F" do not match 0x%x != 0x%x",node_pos+1,hpos-hstart-s-1,s,t);
/*67:*/
#line 1055 "hint.w"

HGETTAG(z);
if(a!=z)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to "SIZE_F"\n",
NAME(a),INFO(a),NAME(z),INFO(z),node_pos,hpos-hstart-1);
/*:67*/
#line 2694 "hint.w"

if(needs_bs)
QUIT("Unexpected trailing baseline node");
if(head==tail)
{pop_nest();
return null;
}
else
{pointer par_ptr= link(head);
/*160:*/
#line 2722 "hint.w"

if(is_char_node(tail))tail_append(new_penalty(inf_penalty))
else if(type(tail)!=glue_node)tail_append(new_penalty(inf_penalty))
else
{type(tail)= penalty_node;delete_glue_ref(glue_ptr(tail));
flush_node_list(leader_ptr(tail));penalty(tail)= inf_penalty;
}
tail_append(new_glue(zero_glue));
/*:160*/
#line 2703 "hint.w"

pop_nest();
store_map(par_ptr,node_pos,0);
return par_ptr;
}
}
else
QUIT("Text in paragraph not yet implemented");
return null;
}
/*:159*//*166:*/
#line 2837 "hint.w"


void hteg_par_node(uint32_t offset)
{scaled x= 0;
param_def_t*q;
pointer p;
pointer par_head= tail;
uint8_t*bs_pos= cur_list.bs_pos;
scaled ph= prev_height;
/*66:*/
#line 1050 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:66*/
#line 2846 "hint.w"

node_pos= (hpos-hstart)-1;
if(INFO(a)&b100)x= hget_xdimen_node();else x= hget_xdimen_ref(HGET8);
if(INFO(a)&b010)q= hget_param_list_node();else q= hget_param_list_ref(HGET8);
prev_graf= 0;
p= hget_paragraph_initial(x,hstart+node_pos+offset);
/*67:*/
#line 1055 "hint.w"

HGETTAG(z);
if(a!=z)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to "SIZE_F"\n",
NAME(a),INFO(a),NAME(z),INFO(z),node_pos,hpos-hstart-1);
/*:67*/
#line 2852 "hint.w"

cur_list.bs_pos= NULL;
hset_param_list(q);
if(p!=null)
line_break(hget_integer_ref(widow_penalty_no),p);
if(par_head!=tail)
/*165:*/
#line 2813 "hint.w"

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
/*:165*/
#line 2858 "hint.w"

hrestore_param_list();
hpos= hstart+node_pos;
}

/*:166*/
#line 6097 "hint.w"

/*73:*/
#line 1136 "hint.w"

static void hteg_node(uint8_t z)
{switch(z)
{
/*89:*/
#line 1373 "hint.w"

case TAG(glyph_kind,1):HTEG_GLYPH(1);break;
case TAG(glyph_kind,2):HTEG_GLYPH(2);break;
case TAG(glyph_kind,3):HTEG_GLYPH(3);break;
case TAG(glyph_kind,4):HTEG_GLYPH(4);break;
/*:89*//*92:*/
#line 1393 "hint.w"

case TAG(penalty_kind,0):tail_append(new_penalty(hget_integer_ref(HTEG8)));break;
case TAG(penalty_kind,1):{tail_append(new_penalty(HTEG8));}break;
case TAG(penalty_kind,2):{int16_t n;HTEG16(n);RNG("Penalty",n,-20000,+20000);tail_append(new_penalty(n));}break;
/*:92*//*95:*/
#line 1417 "hint.w"

case TAG(language_kind,b000):(void)HTEG8;
case TAG(language_kind,1):
case TAG(language_kind,2):
case TAG(language_kind,3):
case TAG(language_kind,4):
case TAG(language_kind,5):
case TAG(language_kind,6):
case TAG(language_kind,7):break;
/*:95*//*99:*/
#line 1462 "hint.w"

case TAG(rule_kind,b000):tail_append(hget_rule_ref(HTEG8));prev_height= ignore_depth;break;
case TAG(rule_kind,b011):HTEG_RULE(b011);prev_height= ignore_depth;break;
case TAG(rule_kind,b101):HTEG_RULE(b101);prev_height= ignore_depth;break;
case TAG(rule_kind,b001):HTEG_RULE(b001);prev_height= ignore_depth;break;
case TAG(rule_kind,b110):HTEG_RULE(b110);prev_height= ignore_depth;break;
case TAG(rule_kind,b111):HTEG_RULE(b111);prev_height= ignore_depth;break;
/*:99*//*106:*/
#line 1533 "hint.w"

case TAG(glue_kind,b000):tail_append(new_glue(hget_glue_ref(HTEG8)));break;
case TAG(glue_kind,b001):{pointer p;HTEG_GLUE(b001);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b010):{pointer p;HTEG_GLUE(b010);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b011):{pointer p;HTEG_GLUE(b011);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b100):{pointer p;HTEG_GLUE(b100);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b101):{pointer p;HTEG_GLUE(b101);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b110):{pointer p;HTEG_GLUE(b110);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b111):{pointer p;HTEG_GLUE(b111);tail_append(spec2glue(p));}break;
/*:106*//*119:*/
#line 1889 "hint.w"

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
/*:119*//*126:*/
#line 2007 "hint.w"

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
/*:126*//*131:*/
#line 2147 "hint.w"

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
/*:131*//*135:*/
#line 2206 "hint.w"

case TAG(kern_kind,b000):{HTEG_KERN(b000);}break;
case TAG(kern_kind,b001):{HTEG_KERN(b001);}break;
case TAG(kern_kind,b010):{HTEG_KERN(b010);}break;
case TAG(kern_kind,b011):{HTEG_KERN(b011);}break;
case TAG(kern_kind,b100):{HTEG_KERN(b100);}break;
case TAG(kern_kind,b101):{HTEG_KERN(b101);}break;
case TAG(kern_kind,b110):{HTEG_KERN(b110);}break;
case TAG(kern_kind,b111):{HTEG_KERN(b111);}break;
/*:135*//*139:*/
#line 2246 "hint.w"

case TAG(leaders_kind,0):tail_append(hget_leaders_ref(HTEG8));break;
case TAG(leaders_kind,1):HTEG_LEADERS(1);break;
case TAG(leaders_kind,2):HTEG_LEADERS(2);break;
case TAG(leaders_kind,3):HTEG_LEADERS(3);break;
/*:139*//*143:*/
#line 2284 "hint.w"

case TAG(baseline_kind,b000):{hget_baseline_ref(HTEG8);cur_list.bs_pos= hpos-1;}break;
case TAG(baseline_kind,b010):{HTEG_BASELINE(b010);}break;
case TAG(baseline_kind,b011):{HTEG_BASELINE(b011);}break;
case TAG(baseline_kind,b100):{HTEG_BASELINE(b100);}break;
case TAG(baseline_kind,b101):{HTEG_BASELINE(b101);}break;
case TAG(baseline_kind,b110):{HTEG_BASELINE(b110);}break;
case TAG(baseline_kind,b111):{HTEG_BASELINE(b111);}break;
/*:143*//*147:*/
#line 2335 "hint.w"

case TAG(ligature_kind,0):tail_append(hget_ligature_ref(HTEG8));break;
case TAG(ligature_kind,1):HTEG_LIG(1);break;
case TAG(ligature_kind,2):HTEG_LIG(2);break;
case TAG(ligature_kind,3):HTEG_LIG(3);break;
case TAG(ligature_kind,4):HTEG_LIG(4);break;
case TAG(ligature_kind,5):HTEG_LIG(5);break;
case TAG(ligature_kind,6):HTEG_LIG(6);break;
case TAG(ligature_kind,7):HTEG_LIG(7);break;
/*:147*//*151:*/
#line 2384 "hint.w"

case TAG(hyphen_kind,b000):tail_append(hget_hyphen_ref(HTEG8));break;
case TAG(hyphen_kind,b001):{HTEG_HYPHEN(b001);tail_append(p);}break;
case TAG(hyphen_kind,b010):{HTEG_HYPHEN(b010);tail_append(p);}break;
case TAG(hyphen_kind,b011):{HTEG_HYPHEN(b011);tail_append(p);}break;
case TAG(hyphen_kind,b100):{HTEG_HYPHEN(b100);tail_append(p);}break;
case TAG(hyphen_kind,b101):{HTEG_HYPHEN(b101);tail_append(p);}break;
case TAG(hyphen_kind,b110):{HTEG_HYPHEN(b110);tail_append(p);}break;
case TAG(hyphen_kind,b111):{HTEG_HYPHEN(b111);tail_append(p);}break;
/*:151*//*163:*/
#line 2770 "hint.w"

case TAG(par_kind,b000):hteg_paragraph(b000);break;
case TAG(par_kind,b010):hteg_paragraph(b010);break;
case TAG(par_kind,b100):hteg_paragraph(b100);break;
case TAG(par_kind,b110):hteg_paragraph(b110);break;
/*:163*//*171:*/
#line 2903 "hint.w"

case TAG(math_kind,b000):HTEG_MATH(b000);break;
case TAG(math_kind,b001):HTEG_MATH(b001);break;
case TAG(math_kind,b010):HTEG_MATH(b010);break;
case TAG(math_kind,b100):HTEG_MATH(b100);break;
case TAG(math_kind,b101):HTEG_MATH(b101);break;
case TAG(math_kind,b110):HTEG_MATH(b110);break;
/*:171*//*173:*/
#line 2927 "hint.w"

case TAG(math_kind,b111):tail_append(new_math(0,before));break;
case TAG(math_kind,b011):tail_append(new_math(0,after));break;
/*:173*//*180:*/
#line 3010 "hint.w"

case TAG(table_kind,b000):HTEG_TABLE(b000);break;
case TAG(table_kind,b001):HTEG_TABLE(b001);break;
case TAG(table_kind,b010):HTEG_TABLE(b010);break;
case TAG(table_kind,b011):HTEG_TABLE(b011);break;
case TAG(table_kind,b100):HTEG_TABLE(b100);break;
case TAG(table_kind,b101):HTEG_TABLE(b101);break;
case TAG(table_kind,b110):HTEG_TABLE(b110);break;
case TAG(table_kind,b111):HTEG_TABLE(b111);break;

case TAG(item_kind,b000):hteg_list();break;
case TAG(item_kind,b001):hteg_content();break;
case TAG(item_kind,b010):hteg_content();break;
case TAG(item_kind,b011):hteg_content();break;
case TAG(item_kind,b100):hteg_content();break;
case TAG(item_kind,b101):hteg_content();break;
case TAG(item_kind,b110):hteg_content();break;
case TAG(item_kind,b111):(void)HTEG8;hteg_content();break;
/*:180*//*185:*/
#line 3086 "hint.w"

case TAG(stream_kind,b000):HTEG_STREAM(b000);break;
case TAG(stream_kind,b010):HTEG_STREAM(b010);break;
/*:185*//*189:*/
#line 3125 "hint.w"

case TAG(image_kind,b000):hget_image_ref(HTEG8);break;
case TAG(image_kind,b100):HTEG_IMAGE(b100);break;
case TAG(image_kind,b101):HTEG_IMAGE(b101);break;
case TAG(image_kind,b110):HTEG_IMAGE(b110);break;
case TAG(image_kind,b111):HTEG_IMAGE(b111);break;
/*:189*/
#line 1140 "hint.w"

default:
TAGERR(z);
}
}

void hteg_content(void)
{/*71:*/
#line 1119 "hint.w"

uint8_t a,z;
z= HTEG8,DBGTAG(z,hpos);
/*:71*/
#line 1147 "hint.w"

node_pos= hpos-hstart;
hteg_node(z);
/*72:*/
#line 1124 "hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:72*/
#line 1150 "hint.w"

node_pos= hpos-hstart;
if(nest_ptr==0&&tail!=head&&(type(tail)==penalty_node||type(tail)==glue_node||type(tail)==kern_node))
store_map(tail,node_pos,0);
}
/*:73*//*153:*/
#line 2409 "hint.w"

pointer hteg_hyphen_node(void)
{/*71:*/
#line 1119 "hint.w"

uint8_t a,z;
z= HTEG8,DBGTAG(z,hpos);
/*:71*/
#line 2411 "hint.w"

if(KIND(z)!=hyphen_kind||INFO(z)==b000)
QUIT("Hyphen expected at 0x%x got %s,%d",node_pos,NAME(z),INFO(z));
{
HTEG_HYPHEN(INFO(z));
/*72:*/
#line 1124 "hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:72*/
#line 2416 "hint.w"

return p;
}
}
/*:153*/
#line 6098 "hint.w"


/*19:*/
#line 317 "hint.w"

void print_xdimen(int i)
{}
/*:19*//*31:*/
#line 460 "hint.w"

void print_baseline_skip(int i)
{}
/*:31*//*62:*/
#line 924 "hint.w"

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
#line 954 "hint.w"

void hfill_page_template(void)
{pointer p;
#if 0
print_str("\npage_head:\n");
show_box(link(page_head));
print_str("\nstream 0:\n");
show_box(streams[0].p);
print_str("\nstream 1:\n");
show_box(streams[1].p);
print_str("\ncontributions:\n");
show_box(link(contrib_head));
#endif
if(cur_page->t!=0)
{
uint8_t*spos= hpos,*sstart= hstart,*send= hend;
hget_section(1);
hpos= hpos+cur_page->t;
p= hget_list();
hpos= spos,hstart= sstart,hend= send;
streams[0].p= vpackage(p,page_v,exactly,page_max_depth);
}
else
houtput_template0();
#if 0
streams[0].p= vpackage(streams[0].p,hvsize,exactly,page_max_depth);
#endif
}
/*:63*//*68:*/
#line 1070 "hint.w"


static void hget_node(uint8_t a)
{switch(a)
{
/*56:*/
#line 845 "hint.w"

case TAG(stream_kind,b100):hinsert_stream(HGET8);break;
/*:56*//*88:*/
#line 1367 "hint.w"

case TAG(glyph_kind,1):HGET_GLYPH(1);break;
case TAG(glyph_kind,2):HGET_GLYPH(2);break;
case TAG(glyph_kind,3):HGET_GLYPH(3);break;
case TAG(glyph_kind,4):HGET_GLYPH(4);break;
/*:88*//*91:*/
#line 1387 "hint.w"

case TAG(penalty_kind,0):tail_append(new_penalty(hget_integer_ref(HGET8)));break;
case TAG(penalty_kind,1):{tail_append(new_penalty(HGET8));}break;
case TAG(penalty_kind,2):{int16_t n;HGET16(n);RNG("Penalty",n,-20000,+20000);tail_append(new_penalty(n));}break;
/*:91*//*94:*/
#line 1405 "hint.w"

case TAG(language_kind,b000):(void)HGET8;
case TAG(language_kind,1):
case TAG(language_kind,2):
case TAG(language_kind,3):
case TAG(language_kind,4):
case TAG(language_kind,5):
case TAG(language_kind,6):
case TAG(language_kind,7):break;
/*:94*//*98:*/
#line 1453 "hint.w"

case TAG(rule_kind,b000):tail_append(hget_rule_ref(HGET8));prev_depth= ignore_depth;break;
case TAG(rule_kind,b011):HGET_RULE(b011);prev_depth= ignore_depth;break;
case TAG(rule_kind,b101):HGET_RULE(b101);prev_depth= ignore_depth;break;
case TAG(rule_kind,b001):HGET_RULE(b001);prev_depth= ignore_depth;break;
case TAG(rule_kind,b110):HGET_RULE(b110);prev_depth= ignore_depth;break;
case TAG(rule_kind,b111):HGET_RULE(b111);prev_depth= ignore_depth;break;
/*:98*//*105:*/
#line 1521 "hint.w"

case TAG(glue_kind,b000):tail_append(new_glue(hget_glue_ref(HGET8)));break;
case TAG(glue_kind,b001):{pointer p;HGET_GLUE(b001);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b010):{pointer p;HGET_GLUE(b010);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b011):{pointer p;HGET_GLUE(b011);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b100):{pointer p;HGET_GLUE(b100);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b101):{pointer p;HGET_GLUE(b101);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b110):{pointer p;HGET_GLUE(b110);tail_append(spec2glue(p));}break;
case TAG(glue_kind,b111):{pointer p;HGET_GLUE(b111);tail_append(spec2glue(p));}break;
/*:105*//*118:*/
#line 1870 "hint.w"

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
/*:118*//*125:*/
#line 1986 "hint.w"

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
/*:125*//*130:*/
#line 2128 "hint.w"

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
/*:130*//*134:*/
#line 2195 "hint.w"

case TAG(kern_kind,b000):{HGET_KERN(b000);}break;
case TAG(kern_kind,b001):{HGET_KERN(b001);}break;
case TAG(kern_kind,b010):{HGET_KERN(b010);}break;
case TAG(kern_kind,b011):{HGET_KERN(b011);}break;
case TAG(kern_kind,b100):{HGET_KERN(b100);}break;
case TAG(kern_kind,b101):{HGET_KERN(b101);}break;
case TAG(kern_kind,b110):{HGET_KERN(b110);}break;
case TAG(kern_kind,b111):{HGET_KERN(b111);}break;
/*:134*//*138:*/
#line 2240 "hint.w"

case TAG(leaders_kind,0):tail_append(hget_leaders_ref(HGET8));break;
case TAG(leaders_kind,1):HGET_LEADERS(1);break;
case TAG(leaders_kind,2):HGET_LEADERS(2);break;
case TAG(leaders_kind,3):HGET_LEADERS(3);break;
/*:138*//*142:*/
#line 2274 "hint.w"

case TAG(baseline_kind,b000):{cur_list.bs_pos= hpos-1;hget_baseline_ref(HGET8);}break;
case TAG(baseline_kind,b010):{HGET_BASELINE(b010);}break;
case TAG(baseline_kind,b011):{HGET_BASELINE(b011);}break;
case TAG(baseline_kind,b100):{HGET_BASELINE(b100);}break;
case TAG(baseline_kind,b101):{HGET_BASELINE(b101);}break;
case TAG(baseline_kind,b110):{HGET_BASELINE(b110);}break;
case TAG(baseline_kind,b111):{HGET_BASELINE(b111);}break;
/*:142*//*146:*/
#line 2324 "hint.w"

case TAG(ligature_kind,0):tail_append(hget_ligature_ref(HGET8));break;
case TAG(ligature_kind,1):HGET_LIG(1);break;
case TAG(ligature_kind,2):HGET_LIG(2);break;
case TAG(ligature_kind,3):HGET_LIG(3);break;
case TAG(ligature_kind,4):HGET_LIG(4);break;
case TAG(ligature_kind,5):HGET_LIG(5);break;
case TAG(ligature_kind,6):HGET_LIG(6);break;
case TAG(ligature_kind,7):HGET_LIG(7);break;
/*:146*//*150:*/
#line 2374 "hint.w"

case TAG(hyphen_kind,b000):tail_append(hget_hyphen_ref(HGET8));break;
case TAG(hyphen_kind,b001):{HGET_HYPHEN(b001);tail_append(p);}break;
case TAG(hyphen_kind,b010):{HGET_HYPHEN(b010);tail_append(p);}break;
case TAG(hyphen_kind,b011):{HGET_HYPHEN(b011);tail_append(p);}break;
case TAG(hyphen_kind,b100):{HGET_HYPHEN(b100);tail_append(p);}break;
case TAG(hyphen_kind,b101):{HGET_HYPHEN(b101);tail_append(p);}break;
case TAG(hyphen_kind,b110):{HGET_HYPHEN(b110);tail_append(p);}break;
case TAG(hyphen_kind,b111):{HGET_HYPHEN(b111);tail_append(p);}break;
/*:150*//*155:*/
#line 2435 "hint.w"

case TAG(par_kind,b000):HGET_PAR(b000);break;
case TAG(par_kind,b010):HGET_PAR(b010);break;
case TAG(par_kind,b100):HGET_PAR(b100);break;
case TAG(par_kind,b110):HGET_PAR(b110);break;
/*:155*//*170:*/
#line 2894 "hint.w"

case TAG(math_kind,b000):HGET_MATH(b000);break;
case TAG(math_kind,b001):HGET_MATH(b001);break;
case TAG(math_kind,b010):HGET_MATH(b010);break;
case TAG(math_kind,b100):HGET_MATH(b100);break;
case TAG(math_kind,b101):HGET_MATH(b101);break;
case TAG(math_kind,b110):HGET_MATH(b110);break;
/*:170*//*172:*/
#line 2923 "hint.w"

case TAG(math_kind,b111):tail_append(new_math(0,before));break;
case TAG(math_kind,b011):tail_append(new_math(0,after));break;
/*:172*//*176:*/
#line 2958 "hint.w"

case TAG(adjust_kind,1):HGET_ADJUST(1);break;
case TAG(adjust_kind,2):HGET_ADJUST(2);break;
case TAG(adjust_kind,3):HGET_ADJUST(3);break;
case TAG(adjust_kind,4):HGET_ADJUST(4);break;
case TAG(adjust_kind,5):HGET_ADJUST(5);break;
/*:176*//*179:*/
#line 2990 "hint.w"

case TAG(table_kind,b000):HGET_TABLE(b000);break;
case TAG(table_kind,b001):HGET_TABLE(b001);break;
case TAG(table_kind,b010):HGET_TABLE(b010);break;
case TAG(table_kind,b011):HGET_TABLE(b011);break;
case TAG(table_kind,b100):HGET_TABLE(b100);break;
case TAG(table_kind,b101):HGET_TABLE(b101);break;
case TAG(table_kind,b110):HGET_TABLE(b110);break;
case TAG(table_kind,b111):HGET_TABLE(b111);break;

case TAG(item_kind,b000):hget_list();break;
case TAG(item_kind,b001):hget_content();break;
case TAG(item_kind,b010):hget_content();break;
case TAG(item_kind,b011):hget_content();break;
case TAG(item_kind,b100):hget_content();break;
case TAG(item_kind,b101):hget_content();break;
case TAG(item_kind,b110):hget_content();break;
case TAG(item_kind,b111):hget_content();(void)HGET8;break;
/*:179*//*184:*/
#line 3081 "hint.w"

case TAG(stream_kind,b000):HGET_STREAM(b000);break;
case TAG(stream_kind,b010):HGET_STREAM(b010);break;
/*:184*//*188:*/
#line 3118 "hint.w"

case TAG(image_kind,b000):hget_image_ref(HGET8);break;
case TAG(image_kind,b100):HGET_IMAGE(b100);break;
case TAG(image_kind,b101):HGET_IMAGE(b101);break;
case TAG(image_kind,b110):HGET_IMAGE(b110);break;
case TAG(image_kind,b111):HGET_IMAGE(b111);break;
/*:188*/
#line 1075 "hint.w"

default:
TAGERR(a);
}
}

void hget_content(void)
{/*66:*/
#line 1050 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:66*/
#line 1082 "hint.w"

node_pos= (hpos-hstart)-1;
hget_node(a);
/*67:*/
#line 1055 "hint.w"

HGETTAG(z);
if(a!=z)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to "SIZE_F"\n",
NAME(a),INFO(a),NAME(z),INFO(z),node_pos,hpos-hstart-1);
/*:67*/
#line 1085 "hint.w"

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
/*:68*//*201:*/
#line 3362 "hint.w"

pointer skip(uint8_t n)
{return cur_page->s[n].g;}
pointer*box_ptr(uint8_t n)
{return&streams[n].p;}
int count(uint8_t n)
{return cur_page->s[n].f;}
scaled dimen(uint8_t n)
{return xdimen(&cur_page->s[n].x);}

/*:201*//*202:*/
#line 3387 "hint.w"

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
/*:202*//*203:*/
#line 3415 "hint.w"

void hclear_page(void)
{if(link(contrib_head)!=null)
{flush_node_list(link(contrib_head));
link(contrib_head)= null;tail= contrib_head;
}
hpage_init();
}
/*:203*//*207:*/
#line 3486 "hint.w"

bool hbuild_page_up(void)
{
static scaled page_top_height;
pointer p;
pointer q,r;
int b,c;
int pi;
if(link(contrib_head)==null)return false;
do{p= link(contrib_head);
/*213:*/
#line 3611 "hint.w"

switch(type(p)){
case hlist_node:case vlist_node:case rule_node:
/*209:*/
#line 3552 "hint.w"

if(page_contents<box_there)
{if(page_contents==empty)freeze_page_specs(box_there);
else page_contents= box_there;
if(depth(p)> page_max_depth)
page_total= depth(p)-page_max_depth;
depth(p)= 0;
/*211:*/
#line 3581 "hint.w"

{page_top_height= width(top_skip);
page_total= page_total+page_top_height;
}
/*:211*/
#line 3559 "hint.w"

}
/*212:*/
#line 3590 "hint.w"

{int i;
for(i= 1;i<=6;i++)
{page_so_far[i]+= top_so_far[i];
top_so_far[i]= 0;
}
}
/*:212*/
#line 3561 "hint.w"

page_total+= page_height+depth(p);
if(height(p)> page_top_height)
{page_total= page_total+height(p)-page_top_height;
page_height= page_top_height;
}
else
page_height= height(p);
/*:209*/
#line 3614 "hint.w"
goto contribute;
case whatsit_node:goto contribute;
case glue_node:/*216:*/
#line 3649 "hint.w"

if(link(p)==null)return false;
/*217:*/
#line 3656 "hint.w"

#define top_shrink top_so_far[6]
#define top_total top_so_far[1]

{pointer q= glue_ptr(p);
top_so_far[2+stretch_order(q)]+= stretch(q);
if((shrink_order(q)!=normal)&&(shrink(q)!=0))
DBG(DBGTEX,"Infinite glue shrinkage found on current page");
top_shrink+= shrink(q);
top_total+= width(q);
}
/*:217*/
#line 3651 "hint.w"

if(page_contents==empty||!precedes_break(link(p)))goto contribute;
pi= 0;
/*:216*/
#line 3616 "hint.w"
break;
case kern_node:/*218:*/
#line 3672 "hint.w"

top_total+= width(p);
if(page_contents==empty||
link(page_head)==null||
type(link(page_head))!=glue_node)
goto contribute;
pi= 0;
/*:218*/
#line 3617 "hint.w"
break;
case penalty_node:if(page_contents==empty)goto done1;else pi= penalty(p);break;
case ins_node:happend_insertion(p);goto contribute;
default:DBG(DBGTEX,"Unexpected node type %d in build_page_up ignored\n",type(p));
}
/*221:*/
#line 3706 "hint.w"

if(pi<inf_penalty)
{/*219:*/
#line 3686 "hint.w"

/*220:*/
#line 3697 "hint.w"

if(page_total<page_goal)
{if((page_so_far[3]!=0)||(page_so_far[4]!=0)||(page_so_far[5]!=0))b= 0;
else b= badness(page_goal-page_total,page_so_far[2]);
}
else if(page_total-page_goal> page_shrink)b= awful_bad;
else b= badness(page_total-page_goal,page_shrink)
/*:220*/
#line 3687 "hint.w"
;
if(b<awful_bad)
{if(pi<=eject_penalty)c= pi;
else if(b<inf_bad)c= b+pi+insert_penalties;
else c= deplorable;
}
else c= b;
if(insert_penalties>=10000)c= awful_bad;
/*:219*/
#line 3708 "hint.w"

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
/*222:*/
#line 3736 "hint.w"

if(p!=best_page_break)
{while(link(page_head)!=best_page_break)
{q= link(page_head);
link(page_head)= link(q);
link(q)= null;
link(q)= link(head);
link(head)= q;
}
}
/*:222*/
#line 3720 "hint.w"

/*223:*/
#line 3754 "hint.w"

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
/*:223*/
#line 3721 "hint.w"

hpack_page();
hfill_page_template();
return true;
}
}
/*:221*/
#line 3622 "hint.w"

contribute:
/*214:*/
#line 3629 "hint.w"

link(contrib_head)= link(p);
link(p)= link(page_head);
if(link(page_head)==null)page_tail= p;
link(page_head)= p;
goto done;
/*:214*/
#line 3624 "hint.w"

done1:/*215:*/
#line 3637 "hint.w"

link(contrib_head)= link(p);link(p)= null;flush_node_list(p);
/*:215*/
#line 3625 "hint.w"

done:
/*:213*/
#line 3496 "hint.w"
;
}while(!(link(contrib_head)==null));
tail= contrib_head;
return false;
}
/*:207*//*229:*/
#line 3836 "hint.w"

void clear_map(void)
{memset(map,0,sizeof(map));
}
/*:229*//*230:*/
#line 3849 "hint.w"

void store_map(pointer p,uint32_t pos,uint32_t offset)
{map[p]= pos;
map[p+1]= offset;
}

uint32_t hposition(pointer p)
{return map[p];
}
/*:230*//*236:*/
#line 3958 "hint.w"

void hloc_init(void)
{cur_loc= 0;
hloc_clear();
page_loc[cur_loc]= 0;
DBG(DBGPAGE,"loc_init: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
}
/*:236*//*241:*/
#line 4094 "hint.w"

static bool hint_is_open= false;
void hint_begin(void)
{if(hint_is_open)
hint_end();
mem_init();
list_init();
hclear_dir();
hclear_fonts();
hint_map();
hget_banner();
hcheck_banner("hint");
hget_directory();
hget_definition_section();
hget_content_section();
leak_clear();
clear_map();
hloc_init();
hint_is_open= true;
}

void hint_end(void)
{if(!hint_is_open)return;
hclear_page();
flush_node_list(link(page_head));
list_leaks();
hint_unmap();
hclear_dir();
hint_is_open= false;
}
/*:241*//*243:*/
#line 4140 "hint.w"

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
/*:243*//*244:*/
#line 4180 "hint.w"

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
/*:244*//*246:*/
#line 4208 "hint.w"

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
/*:246*/
#line 6100 "hint.w"


/*:320*/
