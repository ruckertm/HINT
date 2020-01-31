<<<<<<< HEAD
/*295:*/
#line 5548 "hint.w"
=======
/*299:*/
#line 5613 "hint.w"
>>>>>>> socher

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

#include "texextern.h"
#include "hint.h"
#include "hrender.h"
<<<<<<< HEAD
#include "hfonts.h"
=======
>>>>>>> socher

#include "texdefs.h"

/*1:*/
#line 92 "hint.w"

#define HQUIT QUIT("HGET overrun at " SIZE_F "\n",hpos-hstart)
#define HEND   ((hpos<=hend)?0:HQUIT)

#define HGET8      ((hpos<hend)?hpos+= 1,*(hpos-1):(HQUIT,0))
#define HGET16(X) ((X)= (hpos[0]<<8)+hpos[1],hpos+= 2,HEND)
#define HGET24(X) ((X)= (hpos[0]<<16)+(hpos[1]<<8)+hpos[2],hpos+= 3,HEND)
#define HGET32(X) ((X)= (hpos[0]<<24)+(hpos[1]<<16)+(hpos[2]<<8)+hpos[3],hpos+= 4,HEND)
#define HGETTAG(A) A= HGET8,DBGTAG(A,hpos-1)
/*:1*//*2:*/
#line 107 "hint.w"

#define HGET_SIZE(S,X,I) \
  if ((I)&b100) { \
    if (((I)&b011)==0) s= HGET8,xs= HGET8; \
    else if (((I)&b011)==1) HGET16(s),HGET16(xs); \
    else if (((I)&b011)==2) HGET24(s),HGET24(xs); \
    else if (((I)&b011)==3) HGET32(s),HGET32(xs); \
   } \
  else { \
    if (((I)&b011)==0) s= HGET8; \
    else if (((I)&b011)==1) HGET16(s); \
    else if (((I)&b011)==2) HGET24(s); \
    else if (((I)&b011)==3) HGET32(s); \
   }

#define HGET_ENTRY(I,E) \
{ uint16_t i; \
  uint32_t s= 0,xs= 0; \
  char *file_name; \
  HGET16(i); HGET_SIZE(s,xs,I); HGET_STRING(file_name); \
  hset_entry(&(E),i,s,xs,file_name); \
}
/*:2*//*72:*/
#line 1213 "hint.w"

#define HGET_STRING(S) S= (char*)hpos;\
 while(hpos<hend && *hpos!=0) { RNG("String character",*hpos,0x20,0x7E); hpos++;}\
 hpos++;
/*:72*//*73:*/
#line 1221 "hint.w"

#define HGET_UTF8C(X)  (X)= HGET8; if ((X&0xC0)!=0x80) \
  QUIT("UTF8 continuation byte expected at " SIZE_F " got 0x%02X\n",hpos-hstart-1,X)
/*:73*//*77:*/
#line 1273 "hint.w"

#define HGET_XDIMEN(I,X) \
{ if((I)&b100) HGET32((X).w); else (X).w= 0;\
  if((I)&b010) (X).h= hget_float32();  else (X).h= 0.0;\
  if((I)&b001) (X).v= hget_float32(); else (X).v= 0.0;\
}
/*:77*//*81:*/
#line 1355 "hint.w"

#define HGET_STRETCH(F,O) { stch_t _st;  HGET32(_st.u); (O)= _st.u&3;  _st.u&= ~3; (F)= (scaled)(_st.f*ONE); }
/*:81*//*83:*/
#line 1366 "hint.w"

#define HGET_GLYPH(I) \
{uint8_t f; uint32_t c;\
  if (I==1) c= HGET8;\
  else if (I==2) HGET16(c);\
  else if (I==3) HGET24(c);\
  else if (I==4) HGET32(c);\
  f= HGET8; REF(font_kind,f);\
  tail_append(new_character(f,c));\
}
/*:83*//*91:*/
#line 1438 "hint.w"

#define HGET_MATH(I,M)  \
{ scaled w;\
if ((I)&b001) HGET32(w); else w= 0; \
if ((I)&b100)  tail_append(new_math(w,before)); \
if ((I)&b010)  tail_append(new_math(w,after)); }
/*:91*//*96:*/
#line 1476 "hint.w"

#define HGET_RULE(I)\
{ pointer p= new_rule();\
if ((I)&b100) HGET32(height(p)); else height(p)= null_flag;\
if ((I)&b010) HGET32(depth(p)); else depth(p)= null_flag;\
if ((I)&b001) HGET32(width(p)); else width(p)= null_flag;\
tail_append(p);}
/*:96*//*102:*/
#line 1540 "hint.w"

#define HGET_GLUE(I) \
  p=  get_node(glue_spec_size); \
  if(I==b111) width(p)= hget_xdimen_node(); \
  else { width(p)= 0; if((I)&b100) HGET32(width(p));} \
  if((I)&b010) HGET_STRETCH(stretch(p),stretch_order(p)) else stretch(p)= 0, stretch_order(p)= normal;\
  if((I)&b001) HGET_STRETCH(shrink(p),shrink_order(p)) else shrink(p)= 0, shrink_order(p)= normal;
/*:102*//*110:*/
#line 1653 "hint.w"

#define IS_LIST(X)  (KIND(X)==list_kind || KIND(X)==adjust_kind || \
        KIND(X)==text_kind  || KIND(X)==param_kind)
/*:110*//*115:*/
#line 1856 "hint.w"

#define HGET_BOX(I) \
pointer p= new_null_box();\
HGET32(height(p));\
if ((I)&b001) HGET32(depth(p));\
HGET32(width(p));\
if ((I)&b010) HGET32(shift_amount(p));\
if ((I)&b100) {uint8_t x; glue_set(p)= hget_float32();\
  x= HGET8;  glue_order(p)= x&0xF; glue_sign(p)= x>>4; }\
list_ptr(p)= hget_list();
/*:115*//*122:*/
#line 1979 "hint.w"

#define HGET_SET(I) \
 scaled x, st, sh; uint8_t sto, sho; \
 p= new_null_box();\
 if ((I)&b100) x=  hget_xdimen_node();  else x= hget_xdimen_ref(HGET8);\
 HGET32(height(p)); if ((I)&b001) HGET32(depth(p)); HGET32(width(p));\
 if ((I)&b010) HGET32(shift_amount(p));\
 HGET_STRETCH(st,sto);   HGET_STRETCH(sh,sho);\
 list_ptr(p)= hget_list();
/*:122*//*128:*/
#line 2122 "hint.w"

#define HGET_PACK(I) \
 pointer p; scaled x, d;  uint8_t m; \
 if ((I)&b100) x=  hget_xdimen_node();  else x= hget_xdimen_ref(HGET8);\
 if ((I)&b010) m= additional; else m= exactly; \
 if ((I)&b001) HGET32(d); else d=  MAX_DIMEN; \
 p= hget_list();
/*:128*//*132:*/
#line 2174 "hint.w"

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
#line 2225 "hint.w"

#define HGET_LEADERS(I) \
{pointer p= hget_glue_node();subtype(p)= a_leaders+((I)&b011)-1;\
if (KIND(*hpos)==rule_kind) leader_ptr(p)= hget_rule_node(); \
else if (KIND(*hpos)==hbox_kind) leader_ptr(p)= hget_hbox_node(); \
else  leader_ptr(p)= hget_vbox_node();\
tail_append(p);}
/*:136*//*140:*/
#line 2261 "hint.w"

#define HGET_BASELINE(I) \
  cur_list.bs_pos= hpos-1; \
  if((I)&b100) cur_bs= hget_glue_spec(); else cur_bs= zero_glue; \
  if((I)&b010) cur_ls= hget_glue_spec(); else cur_ls= zero_glue; \
  if((I)&b001) HGET32(cur_lsl); else cur_lsl= 0; \
/*:140*//*144:*/
#line 2302 "hint.w"

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
#line 2357 "hint.w"

#define HGET_HYPHEN(I)\
  pointer p= new_disc(); \
  if ((I)&b100) pre_break(p)= hget_list(); \
  if ((I)&b010) post_break(p)= hget_list(); \
  if ((I)&b001) {uint8_t r; r= HGET8; set_replace_count(p,r); \
                 if ((r&0x80)==0) set_auto_disc(p); }\
  else  set_auto_disc(p);
/*:148*//*154:*/
#line 2430 "hint.w"

#define HGET_PAR(I) \
{ scaled x= 0;\
  param_def_t *q;\
  if ((I)&b100) x= hget_xdimen_node(); else x= hget_xdimen_ref(HGET8);\
  if ((I)&b010) q= hget_param_list_node(); else q= hget_param_list_ref(HGET8);\
  hget_paragraph(x,q,0);\
}
/*:154*//*167:*/
#line 2826 "hint.w"

#define HGET_DISPLAY(I) \
{ param_def_t *q; pointer p= null, a= null;\
if ((I)&b100) q= hget_param_list_node(); else q= hget_param_list_ref(HGET8);\
if ((I)&b010) a= hget_hbox_node(); \
p= hget_list(); \
if ((I)&b001) a= hget_hbox_node();\
hset_param_list(q); hdisplay(p,a,((I)&b010)!=0); hrestore_param_list();\
}
/*:167*//*171:*/
#line 2885 "hint.w"

#define HGET_ADJUST(I) \
{ pointer p; uint32_t s,t;\
  p= get_node(small_node_size); type(p)= adjust_node; subtype(p)= normal;\
  s= hget_list_size(I); hget_size_boundary(I); \
  adjust_ptr(p)= hget_node_list(s);\
  tail_append(p);\
  hget_size_boundary(I);  t= hget_list_size(I); \
  if (t!=s) QUIT("List sizes at " SIZE_F " do not match 0x%x != 0x%x",hpos-hstart-1,s,t);\
}
/*:171*//*173:*/
#line 2908 "hint.w"

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
/*:173*/
<<<<<<< HEAD
#line 5567 "hint.w"
=======
#line 5631 "hint.w"
>>>>>>> socher

/*68:*/
#line 1157 "hint.w"

#define HBACK(X) ((hpos-(X)<hstart)?(QUIT("HTEG underflow\n"),NULL):(hpos-= (X)))

#define HTEG8     (HBACK(1),hpos[0])
#define HTEG16(X) (HBACK(2),(X)= (hpos[0]<<8)+hpos[1])
#define HTEG24(X) (HBACK(3),(X)= (hpos[0]<<16)+(hpos[1]<<8)+hpos[2])
#define HTEG32(X) (HBACK(4),(X)= (hpos[0]<<24)+(hpos[1]<<16)+(hpos[2]<<8)+hpos[3])
/*:68*//*78:*/
#line 1281 "hint.w"

#define HTEG_XDIMEN(I,X) \
  if((I)&b001) (X).v= hteg_float32(); else (X).v= 0.0;\
  if((I)&b010) (X).h= hteg_float32();  else (X).h= 0.0;\
  if((I)&b100) HTEG32((X).w); else (X).w= 0;\
/*:78*//*82:*/
#line 1358 "hint.w"

#define HTEG_STRETCH(F,O) { stch_t _st;  HTEG32(_st.u); (O)= _st.u&3;  _st.u&= ~3; (F)= (scaled)(_st.f*ONE); }
/*:82*//*84:*/
#line 1378 "hint.w"

#define HTEG_GLYPH(I) \
{uint8_t f; uint32_t c;\
  f= HTEG8; REF(font_kind,f);\
  if (I==1) c= HTEG8;\
  else if (I==2) HTEG16(c);\
  else if (I==3) HTEG24(c);\
  else if (I==4) HTEG32(c);\
  tail_append(new_character(f,c));\
}
/*:84*//*92:*/
#line 1446 "hint.w"

#define HTEG_MATH(I,M)  \
{ scaled w;\
if ((I)&b001) HTEG32(w); else w= 0; \
if ((I)&b100)  tail_append(new_math(w,before)); \
if ((I)&b010)  tail_append(new_math(w,after)); }
/*:92*//*97:*/
#line 1486 "hint.w"

#define HTEG_RULE(I)\
{ pointer p= new_rule();\
if ((I)&b001) HTEG32(width(p)); else width(p)= null_flag;\
if ((I)&b010) HTEG32(depth(p)); else depth(p)= null_flag;\
if ((I)&b100) HTEG32(height(p)); else height(p)= null_flag;\
tail_append(p);}
/*:97*//*104:*/
#line 1553 "hint.w"

#define HTEG_GLUE(I) \
  p=  get_node(glue_spec_size); \
  if((I)&b001) HTEG_STRETCH(shrink(p),shrink_order(p)) else shrink(p)= 0, shrink_order(p)= normal;\
  if((I)&b010) HTEG_STRETCH(stretch(p),stretch_order(p)) else stretch(p)= 0, stretch_order(p)= normal;\
  if(I==b111) width(p)= hteg_xdimen_node(); \
  else { width(p)= 0; if((I)&b100) HTEG32(width(p));}
/*:104*//*111:*/
#line 1657 "hint.w"

#define IS_LIST(X)  (KIND(X)==list_kind || KIND(X)==adjust_kind || \
        KIND(X)==text_kind  || KIND(X)==param_kind)
/*:111*//*116:*/
#line 1868 "hint.w"

#define HTEG_BOX(I) \
pointer p= new_null_box();\
list_ptr(p)= hteg_list();\
if ((I)&b100) {uint8_t x= HTEG8; glue_order(p)= x&0xF; glue_sign(p)= x>>4; glue_set(p)= hteg_float32(); }\
if ((I)&b010) HTEG32(shift_amount(p));\
HTEG32(width(p));\
if ((I)&b001) HTEG32(depth(p));\
HTEG32(height(p));\
node_pos= hpos-hstart-1;
/*:116*//*123:*/
#line 1991 "hint.w"

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
#line 2131 "hint.w"

#define HTEG_PACK(I) \
 pointer p; scaled x, d;  uint8_t m; \
 p= hteg_list();\
 if ((I)&b001)  HTEG32(d); else d=  MAX_DIMEN; \
 if ((I)&b010) m= additional; else m= exactly; \
 if ((I)&b100) x= hteg_xdimen_node();  else x= hget_xdimen_ref(HTEG8);\
 node_pos= hpos-hstart-1;
/*:129*//*133:*/
#line 2187 "hint.w"

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
#line 2234 "hint.w"

#define HTEG_LEADERS(I) \
{pointer p= hteg_glue_node();subtype(p)= a_leaders+((I)&b011)-1;\
if (KIND(*(hpos-1))==rule_kind) leader_ptr(p)= hteg_rule_node(); \
else if (KIND(*(hpos-1))==hbox_kind) leader_ptr(p)= hteg_hbox_node(); \
else  leader_ptr(p)= hteg_vbox_node();\
tail_append(p);}
/*:137*//*141:*/
#line 2269 "hint.w"

#define HTEG_BASELINE(I) \
  if((I)&b001) HTEG32(cur_lsl); else cur_lsl= 0; \
  if((I)&b010) cur_ls= hteg_glue_spec(); else cur_ls= zero_glue; \
  if((I)&b100) cur_bs= hteg_glue_spec(); else cur_bs= zero_glue; \
  cur_list.bs_pos= hpos-1;
/*:141*//*145:*/
#line 2316 "hint.w"

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
#line 2367 "hint.w"

#define HTEG_HYPHEN(I)\
  pointer p= new_disc(); \
  if ((I)&b001) {uint8_t r; r= HTEG8; set_replace_count(p,r); \
                 if ((r&0x80)==0) set_auto_disc(p); }\
  else  set_auto_disc(p);\
  if ((I)&b010) post_break(p)= hteg_list(); \
  if ((I)&b100) pre_break(p)= hteg_list();
/*:149*//*168:*/
#line 2837 "hint.w"

#define HTEG_DISPLAY(I) \
{ param_def_t *q; pointer p= null, a= null;\
if ((I)&b001) a= hteg_hbox_node();\
p= hteg_list(); \
if ((I)&b010) a= hteg_hbox_node(); \
if ((I)&b100) q= hteg_param_list_node(); else q= hget_param_list_ref(HTEG8);\
hset_param_list(q); hdisplay(p,a,((I)&b010)!=0); hrestore_param_list();\
}
/*:168*//*174:*/
#line 2921 "hint.w"

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
/*:174*/
<<<<<<< HEAD
#line 5568 "hint.w"
=======
#line 5632 "hint.w"
>>>>>>> socher


/*33:*/
#line 649 "hint.w"

typedef struct{pointer bs,ls;scaled lsl;}bs_t;
/*:33*//*40:*/
#line 728 "hint.w"

typedef struct{
char*n;
uint16_t m,q;
scaled s;
pointer g;
pointer h;
pointer p[MAX_FONT_PARAMS+1];
}font_def_t;
extern font_def_t*font_def;
/*:40*//*47:*/
#line 820 "hint.w"

typedef struct param_t{
uint8_t n,k;
union{int32_t i;
scaled d;
pointer g;};
}param_t;

typedef struct param_def_t{
struct param_def_t*next;
param_t p;}param_def_t;
/*:47*/
<<<<<<< HEAD
#line 5570 "hint.w"
=======
#line 5634 "hint.w"
>>>>>>> socher



/*4:*/
#line 163 "hint.w"

uint8_t*hpos,*hstart,*hend;
static uint8_t*hbase;
#ifdef WIN32
static HANDLE hMap;
#else
static size_t hbase_size;
#endif
/*:4*//*12:*/
#line 484 "hint.w"

pointer*pointer_def[32]= {NULL};
/*:12*//*16:*/
#line 524 "hint.w"

int32_t*integer_def;
/*:16*//*20:*/
#line 554 "hint.w"

scaled*dimen_def;
/*:20*//*24:*/
#line 581 "hint.w"

xdimen_t*xdimen_def;
/*:24*//*34:*/
#line 653 "hint.w"

bs_t*baseline_def= NULL;
/*:34*//*41:*/
#line 740 "hint.w"

font_def_t*font_def;
/*:41*//*48:*/
#line 834 "hint.w"

param_def_t**param_def;
/*:48*//*55:*/
#line 963 "hint.w"

typedef struct{
uint8_t pg;
uint32_t f,t;
}range_def_t;
range_def_t*range_def;
/*:55*//*59:*/
#line 1013 "hint.w"

typedef struct{
pointer p;
}page_def_t;
page_def_t*page_def;
/*:59*//*211:*/
#line 3593 "hint.w"

static uint32_t map[0x10000];
/*:211*//*215:*/
#line 3657 "hint.w"

#define MAX_PAGE_POS (1<<3) 

uint64_t page_loc[MAX_PAGE_POS];
int cur_loc;
static int lo_loc,hi_loc;
/*:215*//*230:*/
#line 3970 "hint.w"

scaled hvsize,hhsize;
/*:230*/
<<<<<<< HEAD
#line 5573 "hint.w"
=======
#line 5637 "hint.w"
>>>>>>> socher

/*13:*/
#line 489 "hint.w"

static void hget_font_def(uint8_t a,uint8_t n);
static int32_t hget_integer_def(uint8_t a);
static scaled hget_dimen_def(void);
static void hget_xdimen_def(uint8_t a,uint8_t n);
static pointer hget_glue_def(uint8_t a);
static void hget_baseline_def(uint8_t a,uint8_t n);
static param_def_t*hget_param_list(uint8_t a);
static void hget_range_def(uint8_t a,uint8_t pg);
static void hget_page_def(uint8_t a,uint8_t n);
static void hget_font_metrics();
static pointer hget_definition(uint8_t a);
/*:13*//*45:*/
#line 804 "hint.w"

static pointer hget_glue_node(void);
static pointer hget_hyphen_node(void);
/*:45*//*53:*/
#line 915 "hint.w"

static uint32_t hget_list_size(info_t info);
static void hget_size_boundary(info_t info);
/*:53*//*103:*/
#line 1549 "hint.w"

static scaled hget_xdimen_node(void);
/*:103*//*117:*/
#line 1882 "hint.w"

static float32_t hget_float32(void);
static float32_t hteg_float32(void);
static pointer hget_list(void);
static pointer hteg_list(void);
/*:117*//*124:*/
#line 2002 "hint.w"

static scaled hget_xdimen_node(void);
/*:124*/
<<<<<<< HEAD
#line 5574 "hint.w"
=======
#line 5638 "hint.w"
>>>>>>> socher

/*19:*/
#line 537 "hint.w"

static int32_t hget_integer_def(uint8_t a)
{if(INFO(a)==1){int8_t n= HGET8;return n;}
else if(INFO(a)==2){int16_t n;HGET16(n);return n;}
else if(INFO(a)==4){int32_t n;HGET32(n);return n;}
else TAGERR(a);
return 0;
}

static int32_t hget_integer_ref(uint8_t n)
{REF(int_kind,n);
return integer_def[n];
}
/*:19*//*28:*/
#line 595 "hint.w"

static void hget_xdimen_def(uint8_t a,uint8_t n)
{HGET_XDIMEN(INFO(a),xdimen_def[n]);
}

static scaled hget_xdimen_ref(uint8_t n)
{REF(xdimen_kind,n);
return xdimen_def[n].w+xdimen_def[n].h*hhsize+xdimen_def[n].v*hvsize;
}
/*:28*//*30:*/
#line 616 "hint.w"

static pointer hget_glue_def(uint8_t a)
{pointer p;
HGET_GLUE(INFO(a));
return p;
}

static pointer hget_glue_ref(uint8_t n)
{REF(glue_kind,n);
return pointer_def[glue_kind][n];
}

pointer hget_param_glue(uint8_t n)
{REF(glue_kind,n);
return new_glue(pointer_def[glue_kind][n]);
}
/*:30*//*44:*/
#line 752 "hint.w"


static void hget_font_params(uint8_t n,font_def_t*f)
{HGET16(f->m);RNG("Font metrics",f->m,3,max_section_no);
HGET16(f->q);RNG("Font glyphs",f->q,3,max_section_no);
f->g= hget_glue_node();
f->h= hget_hyphen_node();
DBG(dbgdef,"Start font parameters\n");
while(KIND(*hpos)!=font_kind)
{kind_t k;
uint8_t n;
/*65:*/
#line 1107 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:65*/
#line 763 "hint.w"

k= KIND(a);
n= HGET8;
DBG(dbgdef,"Reading font parameter %d: %s\n",n,definition_name[k]);
if(k!=penalty_kind&&k!=kern_kind&&k!=ligature_kind&&
k!=hyphen_kind&&k!=glue_kind&&k!=math_kind&&k!=rule_kind&&k!=image_kind)
QUIT("Font parameter %d has invalid type %s",n,content_name[n]);
RNG("Font parameter",n,0,MAX_FONT_PARAMS);
f->p[n]= hget_definition(a);
/*66:*/
#line 1112 "hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:66*/
#line 772 "hint.w"

}
DBG(dbgdef,"End font definition\n");
}
static void hget_font_def(uint8_t a,uint8_t n)
{char*t;
HGET_STRING(t);font_def[n].n= strdup(t);
DBG(dbgdef,"Font %d: %s\n",n,t);
if(INFO(a)&b001)HGET32(font_def[n].s);else font_def[n].s= 0;
hget_font_params(n,&(font_def[n]));
}

static void hget_font_metrics(void)
{int i;
for(i= 0;i<=max_ref[font_kind];i++)
if(font_def[i].m!=0)
{hget_section(font_def[i].m);
read_font_info(i,font_def[i].n,font_def[i].s);
}
}

uint16_t hglyph_section(uint8_t f)
{return font_def[f].q;
}
int32_t font_at_size(uint8_t f)
{return font_def[f].s;
}

/*:44*//*51:*/
#line 851 "hint.w"

static void free_param_list(param_def_t*p)
{while(p!=NULL)
{param_def_t*q= p;
p= p->next;
free(q);
}
}
/*:51*//*52:*/
#line 863 "hint.w"

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
/*65:*/
#line 1107 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:65*/
#line 876 "hint.w"

ALLOCATE(r,1,param_def_t);
q= &(r->p);
q->n= HGET8;
q->k= KIND(a);
DBG(dbgtags,"Defining %s %d\n",definition_name[KIND(a)],q->n);
if(KIND(a)==int_kind)q->i= hget_integer_def(a);
else if(KIND(a)==dimen_kind)q->d= hget_dimen_def();
else if(KIND(a)==glue_kind)q->g= hget_glue_def(a);
else TAGERR(a);
/*66:*/
#line 1112 "hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:66*/
#line 886 "hint.w"

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
/*65:*/
#line 1107 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:65*/
#line 901 "hint.w"

p= hget_param_list(a);
/*66:*/
#line 1112 "hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:66*/
#line 903 "hint.w"

return p;
}
}

param_def_t*hget_param_list_ref(uint8_t n)
{REF(param_kind,n);
return param_def[n];
}
/*:52*//*54:*/
#line 923 "hint.w"

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
/*:54*//*58:*/
#line 978 "hint.w"

static void hget_range_def(uint8_t a,uint8_t pg)
{static uint8_t n= 0;
uint32_t f,t;
REF(page_kind,pg);
REF(range_kind,n);
if(INFO(a)&b100)
{if(INFO(a)&b001)HGET32(f);else HGET16(f);}
else f= 0;
if(INFO(a)&b010)
{if(INFO(a)&b001)HGET32(t);else HGET16(t);}
else t= 0xFFFFFFFF;
range_def[n].pg= pg;
range_def[n].f= f;
range_def[n].t= t;
DBG(dbgrange,"Range *%d from 0x%x\n",pg,f);
DBG(dbgrange,"Range *%d to 0x%x\n",pg,t);
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
/*:58*//*62:*/
#line 1028 "hint.w"

static void hget_page_def(uint8_t a,uint8_t n)
{page_def[n].p= null;
}
/*:62*//*63:*/
#line 1038 "hint.w"

static pointer hget_ligature_ref(uint8_t n)
{REF(ligature_kind,n);
return copy_node_list(pointer_def[ligature_kind][n]);
}

static pointer hget_math_ref(uint8_t n)
{REF(math_kind,n);
return copy_node_list(pointer_def[math_kind][n]);
}

static pointer hget_rule_ref(uint8_t n)
{REF(rule_kind,n);
return copy_node_list(pointer_def[rule_kind][n]);
}

static pointer hget_image_ref(uint16_t n)
{REF(image_kind,n);
return copy_node_list(pointer_def[image_kind][n]);
}

static pointer hget_hyphen_ref(uint8_t n)
{REF(hyphen_kind,n);
return copy_node_list(pointer_def[hyphen_kind][n]);
}

static pointer hget_leaders_ref(uint8_t n)
{REF(leaders_kind,n);
return copy_node_list(pointer_def[leaders_kind][n]);
}




/*:63*//*75:*/
#line 1253 "hint.w"

static float32_t hget_float32(void)
{union{float32_t d;uint32_t bits;}u;
HGET32(u.bits);
return u.d;
}
/*:75*//*76:*/
#line 1261 "hint.w"

static float32_t hteg_float32(void)
{union{float32_t d;uint32_t bits;}u;
HTEG32(u.bits);
return u.d;
}
/*:76*//*79:*/
#line 1288 "hint.w"

static scaled hget_xdimen(uint8_t a)
{xdimen_t x;
switch(a)
{
case TAG(xdimen_kind,b000):return hget_xdimen_ref(HGET8);
case TAG(xdimen_kind,b001):HGET_XDIMEN(b001,x);break;
case TAG(xdimen_kind,b010):HGET_XDIMEN(b010,x);break;
case TAG(xdimen_kind,b011):HGET_XDIMEN(b011,x);break;
case TAG(xdimen_kind,b100):HGET_XDIMEN(b100,x);break;
case TAG(xdimen_kind,b101):HGET_XDIMEN(b101,x);break;
case TAG(xdimen_kind,b110):HGET_XDIMEN(b110,x);break;
case TAG(xdimen_kind,b111):HGET_XDIMEN(b111,x);break;
default:
x.w= 0;x.h= x.v= 0.0;
QUIT("Extent expected got [%s,%d]",NAME(a),INFO(a));
}
return x.w+x.h*hhsize+x.v*hvsize;
}

static scaled hget_xdimen_node(void)
{scaled x= 0;
/*65:*/
#line 1107 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:65*/
#line 1310 "hint.w"

if(KIND(a)==xdimen_kind)
x= hget_xdimen(a);
else
QUIT("Extent expected at 0x%x got %s",node_pos,NAME(a));
/*66:*/
#line 1112 "hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:66*/
#line 1315 "hint.w"

return x;
}
/*:79*//*80:*/
#line 1320 "hint.w"

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
/*69:*/
#line 1168 "hint.w"

uint8_t a,z;
z= HTEG8,DBGTAG(z,hpos);
/*:69*/
#line 1342 "hint.w"

if(KIND(z)==xdimen_kind)
x= hteg_xdimen(z);
else
QUIT("Extent expected at 0x%x got %s",node_pos,NAME(z));
/*70:*/
#line 1173 "hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:70*/
#line 1347 "hint.w"

return x;
}
/*:80*//*101:*/
#line 1525 "hint.w"

static pointer hteg_rule_node(void)
{pointer p= null;
/*69:*/
#line 1168 "hint.w"

uint8_t a,z;
z= HTEG8,DBGTAG(z,hpos);
/*:69*/
#line 1528 "hint.w"

if(KIND(z)==rule_kind){HTEG_RULE(INFO(z));}
else QUIT("Rule expected at 0x%x got %s",node_pos,NAME(z));
/*70:*/
#line 1173 "hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:70*/
#line 1531 "hint.w"

return p;
}
/*:101*//*107:*/
#line 1587 "hint.w"

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
/*66:*/
#line 1112 "hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:66*/
#line 1598 "hint.w"

return p;
}


static pointer hget_glue_node(void)
{pointer p= hget_glue_spec();
if(p!=null)p= new_glue(p);
return p;
}
/*:107*//*108:*/
#line 1610 "hint.w"

static pointer hteg_glue_spec(void)
{pointer p= null;
uint8_t a,z;
if(hpos<=hstart)return null;
if(KIND(*(hpos-1))!=glue_kind)return null;
z= HTEG8,DBGTAG(z,hpos);
if(INFO(z)==b000)p= hget_glue_ref(HTEG8);
else
{HTEG_GLUE(INFO(z));}
/*70:*/
#line 1173 "hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:70*/
#line 1620 "hint.w"

return p;
}


static pointer hteg_glue_node(void)
{pointer p= hteg_glue_spec();
if(p!=null)p= new_glue(p);
return p;
}
/*:108*//*112:*/
#line 1662 "hint.w"

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
/*65:*/
#line 1107 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:65*/
#line 1706 "hint.w"

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
/*66:*/
#line 1112 "hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:66*/
#line 1717 "hint.w"

return p;
}
}
/*:112*//*113:*/
#line 1727 "hint.w"

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

void hskip_list()
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
hskip_list();
list_start= hpos;
p= hget_list();
hpos= list_start;
return p;
}
/*:113*//*114:*/
#line 1795 "hint.w"

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
/*69:*/
#line 1168 "hint.w"

uint8_t a,z;
z= HTEG8,DBGTAG(z,hpos);
/*:69*/
#line 1817 "hint.w"

ALLOCATE(r,1,param_def_t);
q= &(r->p);
q->k= KIND(z);
if(KIND(z)==int_kind)q->i= hteg_integer_def(a);
else if(KIND(a)==dimen_kind)HTEG32(q->d);
else if(KIND(a)==glue_kind){pointer p;HTEG_GLUE(INFO(z));q->g= p;}
else TAGERR(a);
q->n= HTEG8;
DBG(dbgtags,"Defining %s %d\n",definition_name[KIND(z)],q->n);
/*70:*/
#line 1173 "hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:70*/
#line 1827 "hint.w"

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
/*:114*//*121:*/
#line 1953 "hint.w"

static pointer hteg_hbox_node(void)
{/*69:*/
#line 1168 "hint.w"

uint8_t a,z;
z= HTEG8,DBGTAG(z,hpos);
/*:69*/
#line 1955 "hint.w"

if(KIND(z)!=hbox_kind)QUIT("Hbox expected at 0x%x got %s",node_pos,NAME(z));
{
HTEG_BOX(INFO(z));
/*70:*/
#line 1173 "hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:70*/
#line 1959 "hint.w"

return p;
}
}
static pointer hteg_vbox_node(void)
{/*69:*/
#line 1168 "hint.w"

uint8_t a,z;
z= HTEG8,DBGTAG(z,hpos);
/*:69*/
#line 1964 "hint.w"

if(KIND(z)!=vbox_kind)QUIT("Vbox expected at 0x%x got %s",node_pos,NAME(z));
{
HTEG_BOX(INFO(z));
/*70:*/
#line 1173 "hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:70*/
#line 1968 "hint.w"

type(p)= vlist_node;
return p;
}
}

/*:121*//*127:*/
#line 2050 "hint.w"

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
#line 2401 "hint.w"

static pointer hget_hyphen_node(void)
{/*65:*/
#line 1107 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:65*/
#line 2403 "hint.w"

if(KIND(a)!=hyphen_kind||INFO(a)==b000)
QUIT("Hyphen expected at 0x%x got %s,%d",node_pos,NAME(a),INFO(a));
{
HGET_HYPHEN(INFO(a));
/*66:*/
#line 1112 "hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:66*/
#line 2408 "hint.w"

return p;
}
}
/*:152*//*156:*/
#line 2470 "hint.w"

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
#line 2532 "hint.w"

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
(type(p)==glue_node||type(p)==kern_node||type(p)==penalty_node||type(p)==disc_node||type(p)==math_node))
store_map(p,node_pos,0);
}
}
hget_size_boundary(INFO(a));
t= hget_list_size(INFO(a));
if(t!=s)
QUIT("List sizes at 0x%x and "SIZE_F" do not match 0x%x != 0x%x",node_pos+1,hpos-hstart-s-1,s,t);
/*66:*/
#line 1112 "hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:66*/
#line 2562 "hint.w"

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
#line 2594 "hint.w"

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
/*66:*/
#line 1112 "hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:66*/
#line 2622 "hint.w"

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
/*:158*//*160:*/
#line 2708 "hint.w"

pointer hget_paragraph(scaled x,param_def_t*q,uint32_t offset)
{
pointer p,par_head;
hset_param_list(q);
par_head= tail;
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
hrestore_param_list();
return par_head;
}

void hget_par_node(uint32_t offset)
{scaled x= 0;
param_def_t*q;
/*65:*/
#line 1107 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:65*/
#line 2731 "hint.w"

node_pos= (hpos-hstart)-1;
if(INFO(a)&b100)x= hget_xdimen_node();else x= hget_xdimen_ref(HGET8);
if(INFO(a)&b010)q= hget_param_list_node();else q= hget_param_list_ref(HGET8);
hget_paragraph(x,q,offset);
/*66:*/
#line 1112 "hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:66*/
#line 2736 "hint.w"

}
/*:160*//*163:*/
#line 2755 "hint.w"

void hteg_paragraph(info_t i)
{scaled x= 0;
param_def_t*q;
pointer par_head;
uint8_t*list_start,*par_start;
hskip_list();
list_start= hpos;
if(INFO(i)&b010)q= hteg_param_list_node();else q= hget_param_list_ref(HTEG8);
if(INFO(i)&b100)x= hteg_xdimen_node();else x= hget_xdimen_ref(HTEG8);
par_start= hpos;
node_pos= par_start-hstart-1;
hpos= list_start;
par_head= hget_paragraph(x,q,0);
/*166:*/
#line 2809 "hint.w"

{pointer p,r,par_tail;
p= null;
r= par_tail= link(par_head);
while(r!=null)
{pointer q= link(r);
link(r)= p;
p= r;
r= q;
}
link(par_head)= p;
tail= par_tail;
}
/*:166*/
#line 2769 "hint.w"

hpos= par_start;
}
/*:163*//*214:*/
#line 3636 "hint.w"

uint64_t hlocation(pointer p)
{return(uint64_t)(map[p])+(((uint64_t)map[p+1])<<32);
}
/*:214*//*217:*/
#line 3681 "hint.w"

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


/*:217*//*220:*/
#line 3742 "hint.w"


void hloc_set(uint64_t h)
{int i;
if(page_loc[cur_loc]==h)return;
for(i= lo_loc,NEXT_PAGE(i);i!=hi_loc;NEXT_PAGE(i))
if(page_loc[i]==h)
{cur_loc= i;return;}
page_loc[cur_loc]= h;
hloc_clear();
MESSAGE("loc_set: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
}
/*:220*//*221:*/
#line 3766 "hint.w"


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
MESSAGE("loc_set_next: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
}
/*:221*//*222:*/
#line 3802 "hint.w"

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
MESSAGE("loc_set_prev: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
}
<<<<<<< HEAD
/*:222*//*292:*/
#line 5474 "hint.w"
=======
/*:222*//*296:*/
#line 5539 "hint.w"
>>>>>>> socher

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
leaks[p]= s;
#endif
}

void leak_out(pointer p,int s)
{
#ifdef DEBUG
if(s!=leaks[p])
fprintf(stderr,"p=%d, s out=%d != %d = s in\n",p,s,leaks[p]);
leaks[p]= 0;
#endif
}

static void list_leaks(void)
{
#ifdef DEBUG
int i;
for(i= 0;i<0x10000;i++)
if(leaks[i]!=0)
fprintf(stderr,"p=%d, s=%d\n",i,leaks[i]);
#endif
}
<<<<<<< HEAD
/*:292*/
#line 5575 "hint.w"
=======
/*:296*/
#line 5639 "hint.w"
>>>>>>> socher

/*3:*/
#line 131 "hint.w"

void hget_entry(entry_t*e)
{/*65:*/
#line 1107 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:65*/
#line 133 "hint.w"

DBG(dbgdir,"Reading directory entry\n");
switch(a)
{case TAG(0,b000+0):HGET_ENTRY(b000+0,*e);break;
case TAG(0,b000+1):HGET_ENTRY(b000+1,*e);break;
case TAG(0,b000+2):HGET_ENTRY(b000+2,*e);break;
case TAG(0,b000+3):HGET_ENTRY(b000+3,*e);break;
case TAG(0,b100+0):HGET_ENTRY(b100+0,*e);break;
case TAG(0,b100+1):HGET_ENTRY(b100+1,*e);break;
case TAG(0,b100+2):HGET_ENTRY(b100+2,*e);break;
case TAG(0,b100+3):HGET_ENTRY(b100+3,*e);break;
default:TAGERR(a);break;
}
/*66:*/
#line 1112 "hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:66*/
#line 146 "hint.w"

DBG(dbgdir,"entry %d: size=0x%x xsize=0x%x\n",e->section_no,e->size,e->xsize);
}
/*:3*//*5:*/
#line 172 "hint.w"

void hopen_file(const char*in_name)
{
#ifdef WIN32
HANDLE hFile;
uint64_t s;
hFile= CreateFile(in_name,FILE_READ_DATA,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_READONLY,NULL);
if(hFile==INVALID_HANDLE_VALUE)
QUIT("Unable to open file %s",in_name);
{DWORD hs,ls;
ls= GetFileSize(hFile,&hs);
s= hs;
s= s<<32;
s= s+ls;
}
if(s==0)QUIT("File %s is empty",in_name);
hMap= CreateFileMapping(
hFile,
NULL,
PAGE_READONLY,
0,
0,
NULL);
if(hMap==NULL)QUIT("Unable to map file into memory");
hbase= MapViewOfFile(hMap,FILE_MAP_READ,0,0,0);
if(hbase==NULL)
QUIT("Unable to obtain address of mapping for file %s",in_name);
CloseHandle(hFile);
hpos= hstart= hbase;
hend= hstart+s;
#else
struct stat st;
int fd;
fd= open(in_name,O_RDONLY,0);
if(fd<0)QUIT("Unable to open file %s",in_name);
if(fstat(fd,&st)<0)QUIT("Unable to get file size");
hbase_size= st.st_size;
hbase= mmap(NULL,hbase_size,PROT_READ,MAP_PRIVATE,fd,0);
if(hbase==MAP_FAILED)QUIT("Unable to map file into memory");
close(fd);
hpos= hstart= hbase;
hend= hstart+hbase_size;
#endif
}

void hclose_file(void)
{
#ifdef WIN32
UnmapViewOfFile(hbase);
CloseHandle(hMap);
hMap= NULL;
#else
munmap(hbase,hbase_size);
#endif
hbase= NULL;
hpos= hstart= hend= NULL;
}

/*:5*//*6:*/
#line 235 "hint.w"

bool hget_banner(void)
{char*t;
int i;
for(i= 0;i<MAX_BANNER;i++)
{hbanner[i]= HGET8;
if(hbanner[i]=='\n')break;
}
hbanner[++i]= 0;
t= hbanner;
if(strncmp("hint",hbanner,4)!=0)QUIT("This is not a hint file");
else t+= 4;
hbanner_size= (int)strlen(hbanner);
if(hbanner[hbanner_size-1]!='\n')QUIT("Banner exceeds maximum size=0x%x",MAX_BANNER);
if(*t!=' ')QUIT("Space expected after hint");
else t++;
version= strtol(t,&t,10);
if(*t!='.')QUIT("Dot expected after version number %d",version);
else t++;
subversion= strtol(t,&t,10);
if(*t!=' '&&*t!='\n')QUIT("Space expected after subversion number %d",subversion);
MESSAGE("hint file version %d.%d:%s",version,subversion,t);
DBG(dbgdir,"banner size=0x%x\n",hbanner_size);
return true;
}

/*:6*//*7:*/
#line 267 "hint.w"

void hget_section(uint16_t n)
{DBG(dbgbasic,"Reading section %d\n",n);
RNG("Section number",n,0,max_section_no);
if(dir[n].buffer!=NULL&&dir[n].xsize> 0)
{hpos= hstart= dir[n].buffer;
hend= hstart+dir[n].xsize;
}
else
{hpos= hstart= hbase+dir[n].pos;
hend= hstart+dir[n].size;
if(dir[n].xsize> 0)hdecompress(n);
}
}
/*:7*//*8:*/
#line 295 "hint.w"

void hdecompress(uint16_t n)
{z_stream z;
uint8_t*buffer;
int i;

DBG(dbgcompress,"Decompressing section %d from 0x%x to 0x%x byte\n",n,dir[n].size,dir[n].xsize);
z.zalloc= (alloc_func)0;
z.zfree= (free_func)0;
z.opaque= (voidpf)0;
z.next_in= hstart;
z.avail_in= hend-hstart;
if(inflateInit(&z)!=Z_OK)
QUIT("Unable to initialize decompression: %s",z.msg);
ALLOCATE(buffer,dir[n].xsize+SAFETY_MARGIN,uint8_t);
DBG(dbgbuffer,"Allocating output buffer size=0x%x, margin=0x%x\n",dir[n].xsize,SAFETY_MARGIN);
z.next_out= buffer;
z.avail_out= dir[n].xsize+SAFETY_MARGIN;
i= inflate(&z,Z_FINISH);
DBG(dbgcompress,"in: avail/total=0x%x/0x%lx ""out: avail/total=0x%x/0x%lx, return %d;\n",
z.avail_in,z.total_in,z.avail_out,z.total_out,i);
if(i!=Z_STREAM_END)
QUIT("Unable to complete decompression: %s",z.msg);
if(z.avail_in!=0)
QUIT("Decompression missed input data");
if(z.total_out!=dir[n].xsize)
QUIT("Decompression output size missmatch 0x%lx != 0x%x",z.total_out,dir[n].xsize);
if(inflateEnd(&z)!=Z_OK)
QUIT("Unable to finalize decompression: %s",z.msg);
dir[n].buffer= buffer;
dir[n].bsize= dir[n].xsize;
hpos= hstart= buffer;
hend= hstart+dir[n].xsize;
}
/*:8*//*9:*/
#line 334 "hint.w"

void hget_root(entry_t*root)
{DBG(dbgbasic,"Get Root\n");
hget_entry(root);
root->pos= hpos-hstart;
max_section_no= root->section_no;
root->section_no= 0;
if(max_section_no<2)QUIT("Sections 0, 1, and 2 are mandatory");
}

void hget_directory_section(void)
{int i;
entry_t root= {0};
hget_root(&root);
DBG(dbgbasic,"Get Directory\n");
new_directory(max_section_no+1);
dir[0]= root;
hget_section(0);
for(i= 1;i<=max_section_no;i++)
{hget_entry(&(dir[i]));
dir[i].pos= dir[i-1].pos+dir[i-1].size;
}
}

void hclear_dir(void)
{int i;
if(dir==NULL)return;
for(i= 0;i<3;i++)
if(dir[i].xsize> 0)
free(dir[i].buffer);
free(dir);dir= NULL;
}

/*:9*//*10:*/
#line 382 "hint.w"

void hallocate_definitions(void)
{kind_t k;
/*14:*/
#line 504 "hint.w"

for(k= 0;k<32;k++)
{if(k==font_kind||k==int_kind||k==dimen_kind||k==xdimen_kind||k==glue_kind||k==baseline_kind||k==range_kind||k==page_kind||k==param_kind)continue;
if(max_ref[k]>=0&&max_ref[k]<=256)
{DBG(dbgdef,"Allocating Definitions for %s=%d: %d entries of "SIZE_F" byte each\n",definition_name[k],k,max_ref[k]+1,sizeof(pointer));
ALLOCATE(pointer_def[k],max_ref[k]+1,pointer);
}
}
/*:14*//*17:*/
#line 529 "hint.w"

ALLOCATE(integer_def,max_ref[int_kind]+1,int32_t);
/*:17*//*21:*/
#line 558 "hint.w"

ALLOCATE(dimen_def,max_ref[dimen_kind]+1,dimen_t);
/*:21*//*25:*/
#line 585 "hint.w"

ALLOCATE(xdimen_def,max_ref[xdimen_kind]+1,xdimen_t);
/*:25*//*32:*/
#line 638 "hint.w"

ALLOCATE(pointer_def[glue_kind],max_ref[glue_kind]+1,pointer);
/*:32*//*35:*/
#line 657 "hint.w"

ALLOCATE(baseline_def,max_ref[baseline_kind]+1,bs_t);
/*:35*//*42:*/
#line 744 "hint.w"

ALLOCATE(font_def,max_ref[font_kind]+1,font_def_t);
/*:42*//*49:*/
#line 838 "hint.w"

ALLOCATE(param_def,max_ref[param_kind]+1,param_def_t);
/*:49*//*56:*/
#line 970 "hint.w"

ALLOCATE(range_def,max_ref[range_kind]+1,range_def_t);
/*:56*//*60:*/
#line 1020 "hint.w"

ALLOCATE(page_def,max_ref[page_kind]+1,page_def_t);
/*:60*/
#line 385 "hint.w"

}

void hget_max_definitions(void)
{kind_t k;
/*65:*/
#line 1107 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:65*/
#line 390 "hint.w"

if(a!=TAG(list_kind,0))QUIT("Start of maximum list expected");
/*15:*/
#line 514 "hint.w"

for(k= 0;k<32;k++)
{free(pointer_def[k]);pointer_def[k]= NULL;}
/*:15*//*18:*/
#line 533 "hint.w"

free(integer_def);integer_def= NULL;
/*:18*//*22:*/
#line 562 "hint.w"

free(dimen_def);dimen_def= NULL;
/*:22*//*26:*/
#line 588 "hint.w"

free(xdimen_def);xdimen_def= NULL;
/*:26*//*36:*/
#line 661 "hint.w"

free(baseline_def);baseline_def= NULL;
/*:36*//*43:*/
#line 748 "hint.w"

free(font_def);font_def= NULL;
/*:43*//*50:*/
#line 842 "hint.w"

if(param_def!=NULL)
{int i;
for(i= 0;i<=max_ref[param_kind];i++)
free_param_list(param_def[i]);
}
free(param_def);param_def= NULL;
/*:50*//*57:*/
#line 974 "hint.w"

free(range_def);range_def= NULL;
/*:57*//*61:*/
#line 1024 "hint.w"

free(page_def);page_def= NULL;
/*:61*/
#line 392 "hint.w"

hset_max();
while(true)
{uint8_t n;
if(hpos>=hend)QUIT("Unexpected end of maximum list");
node_pos= hpos-hstart;
HGETTAG(a);
if(KIND(a)==list_kind)break;
if(INFO(a)!=1)QUIT("Maximum info %d not supported",INFO(a));
k= KIND(a);
if(max_fixed[k]> max_default[k])QUIT("Maximum value for kind %s not supported",definition_name[k]);
n= HGET8;
RNG("Maximum number",n,max_ref[k],0xFF);
max_ref[k]= n;
DBG(dbgdef,"max(%s) = %d\n",definition_name[k],max_ref[k]);
/*66:*/
#line 1112 "hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:66*/
#line 407 "hint.w"

}
if(INFO(a)!=0)QUIT("End of maximum list with info %d",INFO(a));
hallocate_definitions();
}
/*:10*//*11:*/
#line 417 "hint.w"

void hget_def_node(void)
{uint8_t n;
/*65:*/
#line 1107 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:65*/
#line 420 "hint.w"

n= HGET8;
if(max_fixed[KIND(a)]> max_default[KIND(a)])
QUIT("Definitions for kind %s not supported",definition_name[KIND(a)]);
if(n> max_ref[KIND(a)]||n<=max_fixed[KIND(a)])
QUIT("Definition %d for %s out of range [%d - %d]",
n,definition_name[KIND(a)],max_fixed[KIND(a)]+1,max_ref[KIND(a)]);

if(KIND(a)!=range_kind)REF(KIND(a),n);
DBG(dbgtags,"Defining %s %d\n",definition_name[KIND(a)],n);
if(KIND(a)==font_kind)hget_font_def(a,n);
else if(KIND(a)==int_kind)integer_def[n]= hget_integer_def(a);
else if(KIND(a)==dimen_kind)dimen_def[n]= hget_dimen_def();
else if(KIND(a)==xdimen_kind)hget_xdimen_def(a,n);
else if(KIND(a)==baseline_kind)hget_baseline_def(a,n);
else if(KIND(a)==glue_kind)pointer_def[glue_kind][n]= hget_glue_def(a);
else if(KIND(a)==param_kind)param_def[n]= hget_param_list(a);
else if(KIND(a)==range_kind)hget_range_def(a,n);
else if(KIND(a)==page_kind)hget_page_def(a,n);
else pointer_def[KIND(a)][n]= hget_definition(a);
/*66:*/
#line 1112 "hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:66*/
#line 440 "hint.w"

}

pointer hset_glue(glue_t*g)
{if(ZERO_GLUE(*g))
return zero_glue;
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
{DBG(dbgbasic,"Definitions\n");
hget_section(1);
DBG(dbgdef,"Reading list of maximum values\n");
hget_max_definitions();
hset_default_definitions();
DBG(dbgdef,"Reading list of definitions\n");
while(hpos<hend)
hget_def_node();
hget_font_metrics();
hvsize= dimen_def[vsize_dimen_no];
hhsize= dimen_def[hsize_dimen_no];
}
/*:11*//*23:*/
#line 566 "hint.w"

static scaled hget_dimen_def(void)
{scaled d;HGET32(d);return d;
}

scaled hget_dimen_ref(uint8_t n)
{REF(dimen_kind,n);
return dimen_def[n];
}
/*:23*//*37:*/
#line 665 "hint.w"

static void hget_baseline_def(uint8_t a,uint8_t n)
{HGET_BASELINE(INFO(a));
baseline_def[n].bs= cur_bs;
baseline_def[n].ls= cur_ls;
baseline_def[n].lsl= cur_lsl;
}

void hget_baseline_ref(uint8_t n)
{REF(baseline_kind,n);
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
/*:37*//*64:*/
#line 1093 "hint.w"

void hget_content_section()
{DBG(dbgbasic,"Get Content\n");
hget_section(2);
}
/*:64*//*74:*/
#line 1226 "hint.w"

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
/*:74*//*100:*/
#line 1514 "hint.w"

pointer hget_rule_node(void)
{pointer p= null;
/*65:*/
#line 1107 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:65*/
#line 1517 "hint.w"

if(KIND(a)==rule_kind){HGET_RULE(INFO(a));}
else QUIT("Rule expected at 0x%x got %s",node_pos,NAME(a));
/*66:*/
#line 1112 "hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:66*/
#line 1520 "hint.w"

return p;
}
/*:100*//*120:*/
#line 1928 "hint.w"

pointer hget_hbox_node(void)
{/*65:*/
#line 1107 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:65*/
#line 1930 "hint.w"

if(KIND(a)!=hbox_kind)QUIT("Hbox expected at 0x%x got %s",node_pos,NAME(a));
{
HGET_BOX(INFO(a));
/*66:*/
#line 1112 "hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:66*/
#line 1934 "hint.w"

return p;
}
}


pointer hget_vbox_node(void)
{
/*65:*/
#line 1107 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:65*/
#line 1942 "hint.w"

if(KIND(a)!=vbox_kind)QUIT("Vbox expected at 0x%x got %s",node_pos,NAME(a));
{
HGET_BOX(INFO(a));
/*66:*/
#line 1112 "hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:66*/
#line 1946 "hint.w"

type(p)= vlist_node;
return p;
}
}
/*:120*//*159:*/
#line 2650 "hint.w"

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
{uint8_t*list_end= hpos+s;;
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
/*66:*/
#line 1112 "hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:66*/
#line 2686 "hint.w"

if(needs_bs)
QUIT("Unexpected trailing baseline node");
if(head==tail)
{pop_nest();
return null;
}
else
{pointer par_ptr= link(head);
pop_nest();
store_map(par_ptr,node_pos,0);
return par_ptr;
}
}
else
QUIT("Text in paragraph not yet implemented");
return null;
}
/*:159*//*164:*/
#line 2775 "hint.w"


void hteg_par_node(uint32_t offset)
{scaled x= 0;
param_def_t*q;
pointer p;
/*65:*/
#line 1107 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:65*/
#line 2781 "hint.w"

node_pos= (hpos-hstart)-1;
if(INFO(a)&b100)x= hget_xdimen_node();else x= hget_xdimen_ref(HGET8);
if(INFO(a)&b010)q= hget_param_list_node();else q= hget_param_list_ref(HGET8);
hset_param_list(q);
prev_graf= 0;
p= hget_paragraph_initial(x,hstart+node_pos+offset);
/*66:*/
#line 1112 "hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:66*/
#line 2788 "hint.w"

if(p!=null)
{pointer par_head= tail;
line_break(hget_integer_ref(widow_penalty_no),p);
/*166:*/
#line 2809 "hint.w"

{pointer p,r,par_tail;
p= null;
r= par_tail= link(par_head);
while(r!=null)
{pointer q= link(r);
link(r)= p;
p= r;
r= q;
}
link(par_head)= p;
tail= par_tail;
}
/*:166*/
#line 2792 "hint.w"

}
hrestore_param_list();
hpos= hstart+node_pos;
}

/*:164*/
<<<<<<< HEAD
#line 5576 "hint.w"
=======
#line 5640 "hint.w"
>>>>>>> socher

/*71:*/
#line 1185 "hint.w"

static void hteg_node(uint8_t z)
{switch(z)
{
/*86:*/
#line 1396 "hint.w"

case TAG(glyph_kind,1):HTEG_GLYPH(1);break;
case TAG(glyph_kind,2):HTEG_GLYPH(2);break;
case TAG(glyph_kind,3):HTEG_GLYPH(3);break;
case TAG(glyph_kind,4):HTEG_GLYPH(4);break;
/*:86*//*89:*/
#line 1416 "hint.w"

case TAG(penalty_kind,0):tail_append(new_penalty(hget_integer_ref(HTEG8)));break;
case TAG(penalty_kind,1):{tail_append(new_penalty(HTEG8));}break;
case TAG(penalty_kind,2):{int16_t n;HTEG16(n);RNG("Penalty",n,-20000,+20000);tail_append(new_penalty(n));}break;
/*:89*//*94:*/
#line 1461 "hint.w"

case TAG(math_kind,b000):tail_append(hget_math_ref(HTEG8));break;
case TAG(math_kind,b100):HTEG_MATH(b100,m);break;
case TAG(math_kind,b010):HTEG_MATH(b010,m);break;
case TAG(math_kind,b101):HTEG_MATH(b101,m);break;
case TAG(math_kind,b011):HTEG_MATH(b011,m);break;
/*:94*//*99:*/
#line 1504 "hint.w"

case TAG(rule_kind,b000):tail_append(hget_rule_ref(HTEG8));prev_depth= ignore_depth;break;
case TAG(rule_kind,b011):HTEG_RULE(b011);prev_depth= ignore_depth;break;
case TAG(rule_kind,b101):HTEG_RULE(b101);prev_depth= ignore_depth;break;
case TAG(rule_kind,b001):HTEG_RULE(b001);prev_depth= ignore_depth;break;
case TAG(rule_kind,b110):HTEG_RULE(b110);prev_depth= ignore_depth;break;
case TAG(rule_kind,b111):HTEG_RULE(b111);prev_depth= ignore_depth;break;
/*:99*//*106:*/
#line 1575 "hint.w"

case TAG(glue_kind,b000):tail_append(new_glue(hget_glue_ref(HTEG8)));break;
case TAG(glue_kind,b001):{pointer p;HTEG_GLUE(b001);tail_append(new_glue(p));}break;
case TAG(glue_kind,b010):{pointer p;HTEG_GLUE(b010);tail_append(new_glue(p));}break;
case TAG(glue_kind,b011):{pointer p;HTEG_GLUE(b011);tail_append(new_glue(p));}break;
case TAG(glue_kind,b100):{pointer p;HTEG_GLUE(b100);tail_append(new_glue(p));}break;
case TAG(glue_kind,b101):{pointer p;HTEG_GLUE(b101);tail_append(new_glue(p));}break;
case TAG(glue_kind,b110):{pointer p;HTEG_GLUE(b110);tail_append(new_glue(p));}break;
case TAG(glue_kind,b111):{pointer p;HTEG_GLUE(b111);tail_append(new_glue(p));}break;
/*:106*//*119:*/
#line 1909 "hint.w"

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
/*:119*//*126:*/
#line 2027 "hint.w"

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
/*:126*//*131:*/
#line 2156 "hint.w"

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
/*:131*//*135:*/
#line 2211 "hint.w"

case TAG(kern_kind,b000):{HTEG_KERN(b000);}break;
case TAG(kern_kind,b001):{HTEG_KERN(b001);}break;
case TAG(kern_kind,b010):{HTEG_KERN(b010);}break;
case TAG(kern_kind,b011):{HTEG_KERN(b011);}break;
case TAG(kern_kind,b100):{HTEG_KERN(b100);}break;
case TAG(kern_kind,b101):{HTEG_KERN(b101);}break;
case TAG(kern_kind,b110):{HTEG_KERN(b110);}break;
case TAG(kern_kind,b111):{HTEG_KERN(b111);}break;
/*:135*//*139:*/
#line 2251 "hint.w"

case TAG(leaders_kind,0):tail_append(hget_leaders_ref(HTEG8));break;
case TAG(leaders_kind,1):HTEG_LEADERS(1);break;
case TAG(leaders_kind,2):HTEG_LEADERS(2);break;
case TAG(leaders_kind,3):HTEG_LEADERS(3);break;
/*:139*//*143:*/
#line 2289 "hint.w"

case TAG(baseline_kind,b000):{hget_baseline_ref(HTEG8);cur_list.bs_pos= hpos-1;}break;
case TAG(baseline_kind,b010):{HTEG_BASELINE(b010);}break;
case TAG(baseline_kind,b011):{HTEG_BASELINE(b011);}break;
case TAG(baseline_kind,b100):{HTEG_BASELINE(b100);}break;
case TAG(baseline_kind,b101):{HTEG_BASELINE(b101);}break;
case TAG(baseline_kind,b110):{HTEG_BASELINE(b110);}break;
case TAG(baseline_kind,b111):{HTEG_BASELINE(b111);}break;
/*:143*//*147:*/
#line 2340 "hint.w"

case TAG(ligature_kind,0):tail_append(hget_ligature_ref(HTEG8));break;
case TAG(ligature_kind,1):HTEG_LIG(1);break;
case TAG(ligature_kind,2):HTEG_LIG(2);break;
case TAG(ligature_kind,3):HTEG_LIG(3);break;
case TAG(ligature_kind,4):HTEG_LIG(4);break;
case TAG(ligature_kind,5):HTEG_LIG(5);break;
case TAG(ligature_kind,6):HTEG_LIG(6);break;
case TAG(ligature_kind,7):HTEG_LIG(7);break;
/*:147*//*151:*/
#line 2389 "hint.w"

case TAG(hyphen_kind,b000):tail_append(hget_hyphen_ref(HTEG8));break;
case TAG(hyphen_kind,b001):{HTEG_HYPHEN(b001);tail_append(p);}break;
case TAG(hyphen_kind,b010):{HTEG_HYPHEN(b010);tail_append(p);}break;
case TAG(hyphen_kind,b011):{HTEG_HYPHEN(b011);tail_append(p);}break;
case TAG(hyphen_kind,b100):{HTEG_HYPHEN(b100);tail_append(p);}break;
case TAG(hyphen_kind,b101):{HTEG_HYPHEN(b101);tail_append(p);}break;
case TAG(hyphen_kind,b110):{HTEG_HYPHEN(b110);tail_append(p);}break;
case TAG(hyphen_kind,b111):{HTEG_HYPHEN(b111);tail_append(p);}break;
/*:151*//*162:*/
#line 2748 "hint.w"

case TAG(par_kind,b000):hteg_paragraph(b000);break;
case TAG(par_kind,b010):hteg_paragraph(b010);break;
case TAG(par_kind,b100):hteg_paragraph(b100);break;
case TAG(par_kind,b110):hteg_paragraph(b110);break;
/*:162*//*170:*/
#line 2858 "hint.w"

case TAG(display_kind,b000):HTEG_DISPLAY(b000);break;
case TAG(display_kind,b001):HTEG_DISPLAY(b001);break;
case TAG(display_kind,b010):HTEG_DISPLAY(b010);break;
case TAG(display_kind,b100):HTEG_DISPLAY(b100);break;
case TAG(display_kind,b101):HTEG_DISPLAY(b101);break;
case TAG(display_kind,b110):HTEG_DISPLAY(b110);break;
/*:170*//*176:*/
#line 2941 "hint.w"

case TAG(image_kind,b000):hget_image_ref(HTEG8);break;
case TAG(image_kind,b100):HTEG_IMAGE(b100);break;
case TAG(image_kind,b101):HTEG_IMAGE(b101);break;
case TAG(image_kind,b110):HTEG_IMAGE(b110);break;
case TAG(image_kind,b111):HTEG_IMAGE(b111);break;
/*:176*/
#line 1189 "hint.w"

default:
TAGERR(z);
}
}

void hteg_content(void)
{/*69:*/
#line 1168 "hint.w"

uint8_t a,z;
z= HTEG8,DBGTAG(z,hpos);
/*:69*/
#line 1196 "hint.w"

node_pos= hpos-hstart;
hteg_node(z);
/*70:*/
#line 1173 "hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:70*/
#line 1199 "hint.w"

node_pos= hpos-hstart;
if(nest_ptr==0&&tail!=head&&(type(tail)==penalty_node||type(tail)==glue_node||type(tail)==kern_node))
store_map(tail,node_pos,0);
}
/*:71*//*153:*/
#line 2414 "hint.w"

pointer hteg_hyphen_node(void)
{/*69:*/
#line 1168 "hint.w"

uint8_t a,z;
z= HTEG8,DBGTAG(z,hpos);
/*:69*/
#line 2416 "hint.w"

if(KIND(z)!=hyphen_kind||INFO(z)==b000)
QUIT("Hyphen expected at 0x%x got %s,%d",node_pos,NAME(z),INFO(z));
{
HTEG_HYPHEN(INFO(z));
/*70:*/
#line 1173 "hint.w"

a= HTEG8,DBGTAG(a,hpos);
if(z!=a)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at "SIZE_F" to 0x%x\n",
NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

/*:70*/
#line 2421 "hint.w"

return p;
}
}
/*:153*/
<<<<<<< HEAD
#line 5577 "hint.w"
=======
#line 5641 "hint.w"
>>>>>>> socher

/*29:*/
#line 608 "hint.w"

void print_xdimen(int i)
{}
/*:29*//*39:*/
#line 708 "hint.w"

void print_baseline_skip(int i)
{}
/*:39*//*67:*/
#line 1121 "hint.w"


static void hget_node(uint8_t a)
{switch(a)
{
/*85:*/
#line 1390 "hint.w"

case TAG(glyph_kind,1):HGET_GLYPH(1);break;
case TAG(glyph_kind,2):HGET_GLYPH(2);break;
case TAG(glyph_kind,3):HGET_GLYPH(3);break;
case TAG(glyph_kind,4):HGET_GLYPH(4);break;
/*:85*//*88:*/
#line 1410 "hint.w"

case TAG(penalty_kind,0):tail_append(new_penalty(hget_integer_ref(HGET8)));break;
case TAG(penalty_kind,1):{tail_append(new_penalty(HGET8));}break;
case TAG(penalty_kind,2):{int16_t n;HGET16(n);RNG("Penalty",n,-20000,+20000);tail_append(new_penalty(n));}break;
/*:88*//*93:*/
#line 1454 "hint.w"

case TAG(math_kind,b000):tail_append(hget_math_ref(HGET8));break;
case TAG(math_kind,b100):HGET_MATH(b100,m);break;
case TAG(math_kind,b010):HGET_MATH(b010,m);break;
case TAG(math_kind,b101):HGET_MATH(b101,m);break;
case TAG(math_kind,b011):HGET_MATH(b011,m);break;
/*:93*//*98:*/
#line 1495 "hint.w"

case TAG(rule_kind,b000):tail_append(hget_rule_ref(HGET8));prev_depth= ignore_depth;break;
case TAG(rule_kind,b011):HGET_RULE(b011);prev_depth= ignore_depth;break;
case TAG(rule_kind,b101):HGET_RULE(b101);prev_depth= ignore_depth;break;
case TAG(rule_kind,b001):HGET_RULE(b001);prev_depth= ignore_depth;break;
case TAG(rule_kind,b110):HGET_RULE(b110);prev_depth= ignore_depth;break;
case TAG(rule_kind,b111):HGET_RULE(b111);prev_depth= ignore_depth;break;
/*:98*//*105:*/
#line 1563 "hint.w"

case TAG(glue_kind,b000):tail_append(new_glue(hget_glue_ref(HGET8)));break;
case TAG(glue_kind,b001):{pointer p;HGET_GLUE(b001);tail_append(new_glue(p));}break;
case TAG(glue_kind,b010):{pointer p;HGET_GLUE(b010);tail_append(new_glue(p));}break;
case TAG(glue_kind,b011):{pointer p;HGET_GLUE(b011);tail_append(new_glue(p));}break;
case TAG(glue_kind,b100):{pointer p;HGET_GLUE(b100);tail_append(new_glue(p));}break;
case TAG(glue_kind,b101):{pointer p;HGET_GLUE(b101);tail_append(new_glue(p));}break;
case TAG(glue_kind,b110):{pointer p;HGET_GLUE(b110);tail_append(new_glue(p));}break;
case TAG(glue_kind,b111):{pointer p;HGET_GLUE(b111);tail_append(new_glue(p));}break;
/*:105*//*118:*/
#line 1890 "hint.w"

case TAG(hbox_kind,b000):{HGET_BOX(b000);happend_to_vlist(p);}break;
case TAG(hbox_kind,b001):{HGET_BOX(b001);happend_to_vlist(p);}break;
case TAG(hbox_kind,b010):{HGET_BOX(b010);happend_to_vlist(p);}break;
case TAG(hbox_kind,b011):{HGET_BOX(b011);happend_to_vlist(p);}break;
case TAG(hbox_kind,b100):{HGET_BOX(b100);happend_to_vlist(p);}break;
case TAG(hbox_kind,b101):{HGET_BOX(b101);happend_to_vlist(p);}break;
case TAG(hbox_kind,b110):{HGET_BOX(b110);happend_to_vlist(p);}break;
case TAG(hbox_kind,b111):{HGET_BOX(b111);happend_to_vlist(p);}break;
case TAG(vbox_kind,b000):{HGET_BOX(b000);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b001):{HGET_BOX(b001);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b010):{HGET_BOX(b010);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b011):{HGET_BOX(b011);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b100):{HGET_BOX(b100);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b101):{HGET_BOX(b101);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b110):{HGET_BOX(b110);type(p)= vlist_node;happend_to_vlist(p);}break;
case TAG(vbox_kind,b111):{HGET_BOX(b111);type(p)= vlist_node;happend_to_vlist(p);}break;
/*:118*//*125:*/
#line 2006 "hint.w"

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
#line 2141 "hint.w"

case TAG(hpack_kind,b000):{HGET_PACK(b000);p= hpack(p,x,m);happend_to_vlist(p);}break;
case TAG(hpack_kind,b010):{HGET_PACK(b010);p= hpack(p,x,m);happend_to_vlist(p);}break;
case TAG(hpack_kind,b100):{HGET_PACK(b100);p= hpack(p,x,m);happend_to_vlist(p);}break;
case TAG(hpack_kind,b110):{HGET_PACK(b110);p= hpack(p,x,m);happend_to_vlist(p);}break;

case TAG(vpack_kind,b000):{HGET_PACK(b000);p= vpackage(p,x,m,d);happend_to_vlist(p);}break;
case TAG(vpack_kind,b010):{HGET_PACK(b010);p= vpackage(p,x,m,d);happend_to_vlist(p);}break;
case TAG(vpack_kind,b100):{HGET_PACK(b100);p= vpackage(p,x,m,d);happend_to_vlist(p);}break;
case TAG(vpack_kind,b110):{HGET_PACK(b110);p= vpackage(p,x,m,d);happend_to_vlist(p);}break;
case TAG(vpack_kind,b001):{HGET_PACK(b001);p= vpackage(p,x,m,d);happend_to_vlist(p);}break;
case TAG(vpack_kind,b011):{HGET_PACK(b011);p= vpackage(p,x,m,d);happend_to_vlist(p);}break;
case TAG(vpack_kind,b101):{HGET_PACK(b101);p= vpackage(p,x,m,d);happend_to_vlist(p);}break;
case TAG(vpack_kind,b111):{HGET_PACK(b111);p= vpackage(p,x,m,d);happend_to_vlist(p);}break;
/*:130*//*134:*/
#line 2200 "hint.w"

case TAG(kern_kind,b000):{HGET_KERN(b000);}break;
case TAG(kern_kind,b001):{HGET_KERN(b001);}break;
case TAG(kern_kind,b010):{HGET_KERN(b010);}break;
case TAG(kern_kind,b011):{HGET_KERN(b011);}break;
case TAG(kern_kind,b100):{HGET_KERN(b100);}break;
case TAG(kern_kind,b101):{HGET_KERN(b101);}break;
case TAG(kern_kind,b110):{HGET_KERN(b110);}break;
case TAG(kern_kind,b111):{HGET_KERN(b111);}break;
/*:134*//*138:*/
#line 2245 "hint.w"

case TAG(leaders_kind,0):tail_append(hget_leaders_ref(HGET8));break;
case TAG(leaders_kind,1):HGET_LEADERS(1);break;
case TAG(leaders_kind,2):HGET_LEADERS(2);break;
case TAG(leaders_kind,3):HGET_LEADERS(3);break;
/*:138*//*142:*/
#line 2279 "hint.w"

case TAG(baseline_kind,b000):{cur_list.bs_pos= hpos-1;hget_baseline_ref(HGET8);}break;
case TAG(baseline_kind,b010):{HGET_BASELINE(b010);}break;
case TAG(baseline_kind,b011):{HGET_BASELINE(b011);}break;
case TAG(baseline_kind,b100):{HGET_BASELINE(b100);}break;
case TAG(baseline_kind,b101):{HGET_BASELINE(b101);}break;
case TAG(baseline_kind,b110):{HGET_BASELINE(b110);}break;
case TAG(baseline_kind,b111):{HGET_BASELINE(b111);}break;
/*:142*//*146:*/
#line 2329 "hint.w"

case TAG(ligature_kind,0):tail_append(hget_ligature_ref(HGET8));break;
case TAG(ligature_kind,1):HGET_LIG(1);break;
case TAG(ligature_kind,2):HGET_LIG(2);break;
case TAG(ligature_kind,3):HGET_LIG(3);break;
case TAG(ligature_kind,4):HGET_LIG(4);break;
case TAG(ligature_kind,5):HGET_LIG(5);break;
case TAG(ligature_kind,6):HGET_LIG(6);break;
case TAG(ligature_kind,7):HGET_LIG(7);break;
/*:146*//*150:*/
#line 2379 "hint.w"

case TAG(hyphen_kind,b000):tail_append(hget_hyphen_ref(HGET8));break;
case TAG(hyphen_kind,b001):{HGET_HYPHEN(b001);tail_append(p);}break;
case TAG(hyphen_kind,b010):{HGET_HYPHEN(b010);tail_append(p);}break;
case TAG(hyphen_kind,b011):{HGET_HYPHEN(b011);tail_append(p);}break;
case TAG(hyphen_kind,b100):{HGET_HYPHEN(b100);tail_append(p);}break;
case TAG(hyphen_kind,b101):{HGET_HYPHEN(b101);tail_append(p);}break;
case TAG(hyphen_kind,b110):{HGET_HYPHEN(b110);tail_append(p);}break;
case TAG(hyphen_kind,b111):{HGET_HYPHEN(b111);tail_append(p);}break;
/*:150*//*155:*/
#line 2440 "hint.w"

case TAG(par_kind,b000):HGET_PAR(b000);break;
case TAG(par_kind,b010):HGET_PAR(b010);break;
case TAG(par_kind,b100):HGET_PAR(b100);break;
case TAG(par_kind,b110):HGET_PAR(b110);break;
/*:155*//*169:*/
#line 2849 "hint.w"

case TAG(display_kind,b000):HGET_DISPLAY(b000);break;
case TAG(display_kind,b001):HGET_DISPLAY(b001);break;
case TAG(display_kind,b010):HGET_DISPLAY(b010);break;
case TAG(display_kind,b100):HGET_DISPLAY(b100);break;
case TAG(display_kind,b101):HGET_DISPLAY(b101);break;
case TAG(display_kind,b110):HGET_DISPLAY(b110);break;
/*:169*//*172:*/
#line 2898 "hint.w"

case TAG(adjust_kind,1):HGET_ADJUST(1);break;
case TAG(adjust_kind,2):HGET_ADJUST(2);break;
case TAG(adjust_kind,3):HGET_ADJUST(3);break;
case TAG(adjust_kind,4):HGET_ADJUST(4);break;
case TAG(adjust_kind,5):HGET_ADJUST(5);break;
/*:172*//*175:*/
#line 2934 "hint.w"

case TAG(image_kind,b000):hget_image_ref(HGET8);break;
case TAG(image_kind,b100):HGET_IMAGE(b100);break;
case TAG(image_kind,b101):HGET_IMAGE(b101);break;
case TAG(image_kind,b110):HGET_IMAGE(b110);break;
case TAG(image_kind,b111):HGET_IMAGE(b111);break;
/*:175*/
#line 1126 "hint.w"

default:
TAGERR(a);
}
}

void hget_content(void)
{/*65:*/
#line 1107 "hint.w"

uint8_t a,z;
HGETTAG(a);
/*:65*/
#line 1133 "hint.w"

node_pos= (hpos-hstart)-1;
hget_node(a);
/*66:*/
#line 1112 "hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:66*/
#line 1136 "hint.w"

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


/*:67*//*188:*/
#line 3178 "hint.w"


void hpage_init(void)
{if(stream[0].p!=null)
flush_node_list(stream[0].p);
stream[0].p= null;
page_contents= empty;page_tail= page_head;link(page_head)= null;
page_depth= 0;page_max_depth= 0;
}
/*:188*//*189:*/
#line 3193 "hint.w"

void hclear_page(void)
{int i;
for(i= 0;i<0x100;i++)
if(stream[i].p!=null)
{flush_node_list(stream[i].p);
stream[i].p= null;
}
if(link(contrib_head)!=null)
{flush_node_list(link(contrib_head));
link(contrib_head)= null;tail= contrib_head;
}
}
/*:189*//*192:*/
#line 3256 "hint.w"

bool hbuild_page_up(void)
{
static scaled page_max_height;
static scaled page_height;
static scaled top_so_far[8];
pointer p;
pointer q;
int b,c;
int pi;


if(link(contrib_head)==null)return false;
do{p= link(contrib_head);
/*197:*/
#line 3380 "hint.w"

switch(type(p)){
case hlist_node:case vlist_node:case rule_node:
/*193:*/
#line 3321 "hint.w"

if(page_contents==empty)
{/*194:*/
#line 3343 "hint.w"

memset(page_so_far,0,sizeof(page_so_far));
memset(top_so_far,0,sizeof(top_so_far));
page_goal= hvsize;
page_max_depth= max_depth;
page_height= 0;
least_page_cost= awful_bad;
/*:194*/
#line 3323 "hint.w"

if(depth(p)> page_max_depth)
page_total= depth(p)-page_max_depth;
depth(p)= 0;
}
if(page_contents<box_there)
/*195:*/
#line 3353 "hint.w"

{page_max_height= width(pointer_def[glue_kind][top_skip_no]);
page_total= page_total+page_max_height;
}
/*:195*/
#line 3329 "hint.w"

page_contents= box_there;
/*196:*/
#line 3359 "hint.w"

{int i;
for(i= 1;i<=6;i++)
{page_so_far[i]+= top_so_far[i];
top_so_far[i]= 0;
}
}
/*:196*/
#line 3331 "hint.w"

page_total+= page_height+depth(p);
if(height(p)> page_max_height)
{page_total= page_total+height(p)-page_max_height;
page_height= page_max_height;
}
else
page_height= height(p);
/*:193*/
#line 3383 "hint.w"
goto contribute;
case whatsit_node:goto contribute;
case glue_node:/*200:*/
#line 3420 "hint.w"

if(link(p)==null)return false;
if(page_contents==empty)
{/*194:*/
#line 3343 "hint.w"

memset(page_so_far,0,sizeof(page_so_far));
memset(top_so_far,0,sizeof(top_so_far));
page_goal= hvsize;
page_max_depth= max_depth;
page_height= 0;
least_page_cost= awful_bad;
/*:194*/
#line 3423 "hint.w"

page_contents= inserts_only;
}
/*201:*/
#line 3431 "hint.w"

#define top_shrink top_so_far[6]
#define top_total top_so_far[1]

{pointer q= glue_ptr(p);
top_so_far[2+stretch_order(q)]+= stretch(q);
top_shrink+= shrink(q);
if((shrink_order(q)!=normal)&&(shrink(q)!=0))
MESSAGE("Infinite glue shrinkage found on current page");
top_total+= width(q);
}
/*:201*/
#line 3426 "hint.w"

if(!precedes_break(link(p)))goto contribute;
pi= 0;
/*:200*/
#line 3385 "hint.w"
break;
case kern_node:/*202:*/
#line 3447 "hint.w"

if(page_contents==empty)
{/*194:*/
#line 3343 "hint.w"

memset(page_so_far,0,sizeof(page_so_far));
memset(top_so_far,0,sizeof(top_so_far));
page_goal= hvsize;
page_max_depth= max_depth;
page_height= 0;
least_page_cost= awful_bad;
/*:194*/
#line 3449 "hint.w"

page_contents= inserts_only;
}
top_total+= width(p);
if(page_contents<box_there)goto done1;
else if(link(page_head)==null)return false;
else if(type(link(page_head))!=glue_node)
goto contribute;
pi= 0;
/*:202*/
#line 3386 "hint.w"
break;

case penalty_node:if(page_contents==empty)goto done1;else pi= penalty(p);break;
case mark_node:goto contribute;
case ins_node:/*203:*/
#line 3461 "hint.w"

QUIT("Prepending insertions not yet implemented\n");
/*:203*/
#line 3390 "hint.w"

default:MESSAGE("Unexpected node type %d in build_page_up ignored\n",type(p));
}
if(pi<inf_penalty)
/*206:*/
#line 3490 "hint.w"

{/*204:*/
#line 3470 "hint.w"

/*205:*/
#line 3481 "hint.w"

if(page_total<page_goal)
{if((page_so_far[3]!=0)||(page_so_far[4]!=0)||(page_so_far[5]!=0))b= 0;
else b= badness(page_goal-page_total,page_so_far[2]);
}
else if(page_total-page_goal> page_shrink)b= awful_bad;
else b= badness(page_total-page_goal,page_shrink)
/*:205*/
#line 3471 "hint.w"
;
if(b<awful_bad)
{if(pi<=eject_penalty)c= pi;
else if(b<inf_bad)c= b+pi+insert_penalties;
else c= deplorable;
}
else c= b;
if(insert_penalties>=10000)c= awful_bad;
/*:204*/
#line 3491 "hint.w"

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
{/*207:*/
#line 3517 "hint.w"

if(p!=best_page_break)
{while(link(page_head)!=best_page_break)
{q= link(page_head);
link(page_head)= link(q);
link(q)= null;
tail_append(q);
}
}
/*:207*/
#line 3504 "hint.w"

/*208:*/
#line 3529 "hint.w"

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
temp_ptr= new_spec(pointer_def[glue_kind][top_skip_no]);
q= new_glue(temp_ptr);glue_ref_count(temp_ptr)= null;
if(width(temp_ptr)> page_height)width(temp_ptr)= width(temp_ptr)-page_height;
else width(temp_ptr)= 0;
link(q)= link(page_head);
link(page_head)= q;
/*:208*/
#line 3505 "hint.w"

/*209:*/
#line 3548 "hint.w"

if(box(0)!=null)QUIT("Box 0 must be empty");
box(0)= vpackage(link(page_head),best_size,exactly,0x100000);
/*210:*/
#line 3555 "hint.w"

/*:210*/
#line 3551 "hint.w"

/*:209*/
#line 3506 "hint.w"

return true;
}
}
/*:206*/
#line 3394 "hint.w"

contribute:
/*198:*/
#line 3401 "hint.w"

link(contrib_head)= link(p);
link(p)= link(page_head);
link(page_head)= p;
goto done;
/*:198*/
#line 3396 "hint.w"

done1:/*199:*/
#line 3408 "hint.w"

link(contrib_head)= link(p);link(p)= null;flush_node_list(p);
/*:199*/
#line 3397 "hint.w"

done:
/*:197*/
#line 3270 "hint.w"
;
}while(!(link(contrib_head)==null));
tail= contrib_head;
return false;
}
/*:192*//*212:*/
#line 3600 "hint.w"

void clear_map(void)
{memset(map,0,sizeof(map));
}
/*:212*//*213:*/
#line 3613 "hint.w"

void store_map(pointer p,uint32_t pos,uint32_t offset)
{map[p]= pos;
map[p+1]= offset;
}

uint32_t hposition(pointer p)
{return map[p];
}
/*:213*//*219:*/
#line 3722 "hint.w"

void hloc_init(void)
{cur_loc= 0;
hloc_clear();
page_loc[cur_loc]= 0;
MESSAGE("loc_init: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
}
/*:219*//*224:*/
#line 3846 "hint.w"

static bool hint_is_open= false;
void hint_open(const char*file_name)
{if(hint_is_open)
hint_close();
mem_init();
list_init();
hclear_dir();
hopen_file(file_name);
hget_banner();
hget_directory_section();
hget_definition_section();
hget_content_section();
leak_clear();
clear_map();
hloc_init();
hint_is_open= true;
}

void hint_close(void)
{if(!hint_is_open)return;
hclear_page();
list_leaks();
hclose_file();
hclear_dir();
hint_is_open= false;
}
/*:224*//*226:*/
#line 3885 "hint.w"

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
/*:226*//*227:*/
#line 3925 "hint.w"

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
/*:227*//*229:*/
#line 3952 "hint.w"

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
/*:229*/
<<<<<<< HEAD
#line 5578 "hint.w"


/*:295*/
=======
#line 5642 "hint.w"


/*:299*/
>>>>>>> socher
