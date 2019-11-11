/*251:*/
#line 3838 ".\\hint.w"

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
#line 3854 ".\\hint.w"


/*1:*/
#line 91 ".\\hint.w"

#define HQUIT QUIT("HGET overrun at " SIZE_F "\n",hpos-hstart)
#define HEND   ((hpos<=hend)?0:HQUIT)

#define HGET8      ((hpos<hend)?hpos+= 1,*(hpos-1):(HQUIT,0))
#define HGET16(X) ((X)= (hpos[0]<<8)+hpos[1],hpos+= 2,HEND)
#define HGET24(X) ((X)= (hpos[0]<<16)+(hpos[1]<<8)+hpos[2],hpos+= 3,HEND)
#define HGET32(X) ((X)= (hpos[0]<<24)+(hpos[1]<<16)+(hpos[2]<<8)+hpos[3],hpos+= 4,HEND)
#define HGETTAG(A) A= HGET8,DBGTAG(A,hpos-1)
/*:1*//*2:*/
#line 106 ".\\hint.w"

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
  char *name; \
  HGET16(i); HGET_SIZE(s,xs,I); HGET_STRING(name); \
  hset_entry(&(E),i,s,xs,name); \
}
/*:2*//*77:*/
#line 1223 ".\\hint.w"

#define HGET_STRING(S) S= (char*)hpos;\
 while(hpos<hend && *hpos!=0) { RNG("String character",*hpos,0x20,0x7E); hpos++;}\
 hpos++;
/*:77*//*78:*/
#line 1231 ".\\hint.w"

#define HGET_UTF8C(X)  (X)= HGET8; if ((X&0xC0)!=0x80) \
  QUIT("UTF8 continuation byte expected at " SIZE_F " got 0x%02X\n",hpos-hstart-1,X)
/*:78*//*82:*/
#line 1283 ".\\hint.w"

#define HGET_XDIMEN(I,X) \
{ if((I)&b100) HGET32((X).w); else (X).w= 0;\
  if((I)&b010) (X).h= hget_float32();  else (X).h= 0.0;\
  if((I)&b001) (X).v= hget_float32(); else (X).v= 0.0;\
}
/*:82*//*89:*/
#line 1377 ".\\hint.w"

#define HGET_STRETCH(F,O) { stch_t _st;  HGET32(_st.u); (O)= _st.u&3;  _st.u&= ~3; (F)= (scaled)(_st.f*ONE); }
/*:89*//*91:*/
#line 1388 ".\\hint.w"

#define HGET_GLYPH(I) \
{uint8_t f; uint32_t c;\
  if (I==1) c= HGET8;\
  else if (I==2) HGET16(c);\
  else if (I==3) HGET24(c);\
  else if (I==4) HGET32(c);\
  f= HGET8; REF(font_kind,f);\
  tail_append(new_character(f,c));\
}
/*:91*//*99:*/
#line 1460 ".\\hint.w"

#define HGET_MATH(I,M)  \
{ scaled w;\
if ((I)&b001) HGET32(w); else w= 0; \
if ((I)&b100)  tail_append(new_math(w,before)); \
if ((I)&b010)  tail_append(new_math(w,after)); }
/*:99*//*106:*/
#line 1508 ".\\hint.w"

#define HGET_RULE(I)\
{ pointer p= new_rule();\
if ((I)&b100) HGET32(height(p)); else height(p)= null_flag;\
if ((I)&b010) HGET32(depth(p)); else depth(p)= null_flag;\
if ((I)&b001) HGET32(width(p)); else width(p)= null_flag;\
tail_append(p);}
/*:106*//*114:*/
#line 1598 ".\\hint.w"

#define HGET_GLUE(I) \
  p=  get_node(glue_spec_size); \
  if(I==b111) width(p)= hget_xdimen_node(); \
  else { width(p)= 0; if((I)&b100) HGET32(width(p));} \
  if((I)&b010) HGET_STRETCH(stretch(p),stretch_order(p)) else stretch(p)= 0, stretch_order(p)= normal;\
  if((I)&b001) HGET_STRETCH(shrink(p),shrink_order(p)) else shrink(p)= 0, shrink_order(p)= normal;
/*:114*//*124:*/
#line 1739 ".\\hint.w"

#define IS_LIST(X)  (KIND(X)==list_kind || KIND(X)==adjust_kind || \
        KIND(X)==text_kind  || KIND(X)==param_kind)
/*:124*//*129:*/
#line 1939 ".\\hint.w"

#define HGET_BOX(I) \
pointer p= new_null_box();\
HGET32(height(p));\
if ((I)&b001) HGET32(depth(p));\
HGET32(width(p));\
if ((I)&b010) HGET32(shift_amount(p));\
if ((I)&b100) {uint8_t x; glue_set(p)= hget_float32();\
  x= HGET8;  glue_order(p)= x&0xF; glue_sign(p)= x>>4; }\
list_ptr(p)= hget_list();
/*:129*//*138:*/
#line 2076 ".\\hint.w"

#define HGET_SET(I) \
 scaled x, st, sh; uint8_t sto, sho; \
 p= new_null_box();\
 if ((I)&b100) x=  hget_xdimen_node();  else x= hget_xdimen_ref(HGET8);\
 HGET32(height(p)); if ((I)&b001) HGET32(depth(p)); HGET32(width(p));\
 if ((I)&b010) HGET32(shift_amount(p));\
 HGET_STRETCH(st,sto);   HGET_STRETCH(sh,sho);\
 list_ptr(p)= hget_list();
/*:138*//*143:*/
#line 2215 ".\\hint.w"

#define HGET_PACK(I) \
 pointer p; scaled x, d;  uint8_t m; \
 if ((I)&b100) x=  hget_xdimen_node();  else x= hget_xdimen_ref(HGET8);\
 if ((I)&b010) m= additional; else m= exactly; \
 if ((I)&b001) HGET32(d); else d=  MAX_DIMEN; \
 p= hget_list();
/*:143*//*149:*/
#line 2276 ".\\hint.w"

#define HGET_KERN(I) \
pointer p; scaled x; \
if (((I)&b011)==0) x= hget_dimen_ref(HGET8);\
else if (((I)&b011)==1) x= hget_xdimen_ref(HGET8);\
else if (((I)&b011)==2) HGET32(x);\
else if (((I)&b011)==3) x= hget_xdimen_node();\
p= new_kern(x);\
if ((I)&b100) subtype(p)= explicit;\
tail_append(p);
/*:149*//*155:*/
#line 2336 ".\\hint.w"

#define HGET_LEADERS(I) \
{pointer p= hget_glue_node();subtype(p)= a_leaders+((I)&b011)-1;\
if (KIND(*hpos)==rule_kind) leader_ptr(p)= hget_rule_node(); \
else if (KIND(*hpos)==hbox_kind) leader_ptr(p)= hget_hbox_node(); \
else  leader_ptr(p)= hget_vbox_node();\
tail_append(p);}
/*:155*//*160:*/
#line 2377 ".\\hint.w"

#define HGET_BASELINE(I,B) \
  if((I)&b100) (B).bs= hget_glue_spec(); else (B).bs= zero_glue; \
  if((I)&b010) (B).ls= hget_glue_spec(); else (B).ls= zero_glue; \
  if((I)&b001) HGET32((B).lsl); else (B).lsl= 0; \
/*:160*//*165:*/
#line 2419 ".\\hint.w"

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
/*:165*//*170:*/
#line 2477 ".\\hint.w"

#define HGET_HYPHEN(I)\
  pointer p= new_disc(); \
  if ((I)&b100) pre_break(p)= hget_list(); \
  if ((I)&b010) post_break(p)= hget_list(); \
  if ((I)&b001) {uint8_t r; r= HGET8; set_replace_count(p,r); \
                 if ((r&0x80)==0) set_auto_disc(p); }\
  else  set_auto_disc(p);
/*:170*//*177:*/
#line 2565 ".\\hint.w"

#define HGET_PAR(I) \
{ scaled x= 0;\
  param_def_t *q;\
  if ((I)&b100) x= hget_xdimen_node(); else x= hget_xdimen_ref(HGET8);\
  if ((I)&b010) q= hget_param_list_node(); else q= hget_param_list_ref(HGET8);\
  hget_paragraph(x,q,0);\
}
/*:177*//*184:*/
#line 2737 ".\\hint.w"

#define HGET_DISPLAY(I) \
{ param_def_t *q; pointer p= null, a= null;\
if ((I)&b100) q= hget_param_list_node(); else q= hget_param_list_ref(HGET8);\
if ((I)&b010) a= hget_hbox_node(); \
p= hget_list(); \
if ((I)&b001) a= hget_hbox_node();\
hset_param_list(q); hdisplay(p,a,((I)&b010)!=0); hrestore_param_list();\
}
/*:184*//*188:*/
#line 2796 ".\\hint.w"

#define HGET_ADJUST(I) \
{ pointer p; uint32_t s,t;\
  p= get_node(small_node_size); type(p)= adjust_node; subtype(p)= normal;\
  s= hget_list_size(I); hget_size_boundary(I); \
  adjust_ptr(p)= hget_node_list(s);\
  tail_append(p);\
  hget_size_boundary(I);  t= hget_list_size(I); \
  if (t!=s) QUIT("List sizes at " SIZE_F " do not match 0x%x != 0x%x",hpos-hstart-1,s,t);\
}
/*:188*//*191:*/
#line 2824 ".\\hint.w"

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
/*:191*/
#line 3856 ".\\hint.w"


/*4:*/
#line 160 ".\\hint.w"

uint8_t*hbase,*hpos,*hstart,*hend;

/*:4*//*12:*/
#line 452 ".\\hint.w"

pointer*pointer_def[32]= {NULL};
/*:12*//*17:*/
#line 496 ".\\hint.w"

int32_t*integer_def;
/*:17*//*23:*/
#line 533 ".\\hint.w"

scaled*dimen_def;
/*:23*//*28:*/
#line 562 ".\\hint.w"

xdimen_t*xdimen_def;
/*:28*//*39:*/
#line 635 ".\\hint.w"

bs_t*baseline_def= NULL;
/*:39*//*45:*/
#line 708 ".\\hint.w"

font_def_t*font_def;
/*:45*//*51:*/
#line 785 ".\\hint.w"

param_def_t**param_def;
/*:51*//*57:*/
#line 908 ".\\hint.w"

typedef struct{
uint8_t pg;
uint32_t f,t;
}range_def_t;
range_def_t*range_def;
/*:57*//*61:*/
#line 956 ".\\hint.w"

typedef struct{
pointer p;
}page_def_t;
page_def_t*page_def;
/*:61*/
#line 3858 ".\\hint.w"


/*14:*/
#line 461 ".\\hint.w"

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
/*:14*//*86:*/
#line 1362 ".\\hint.w"

static scaled hget_xdimen_node(void);
/*:86*//*131:*/
#line 1964 ".\\hint.w"

static float32_t hget_float32(void);
/*:131*//*247:*/
#line 3761 ".\\hint.w"

static void hget_font_params(uint8_t n,font_def_t*f);
extern pointer hget_node_list(uint32_t s);
extern pointer hget_list(void);
extern pointer hget_text_list(uint32_t s);
extern pointer hget_rule_node(void);
extern pointer hget_glue_node(void);
extern pointer hget_glue_spec(void);
extern pointer hget_hyphen_node(void);
extern pointer hget_hbox_node(void);
extern pointer hget_vbox_node(void);



static void free_param_list(param_def_t*p);
/*:247*/
#line 3860 ".\\hint.w"


/*3:*/
#line 130 ".\\hint.w"

void hget_entry(entry_t*e)
{/*67:*/
#line 1050 ".\\hint.w"

uint8_t a,z;
HGETTAG(a);
/*:67*/
#line 132 ".\\hint.w"

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
/*68:*/
#line 1055 ".\\hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:68*/
#line 145 ".\\hint.w"

DBG(dbgdir,"entry %d: size=0x%x xsize=0x%x\n",e->section_no,e->size,e->xsize);
}
/*:3*//*5:*/
#line 164 ".\\hint.w"

void hopen_file(const char*in_name)
{
#ifdef WIN32
HANDLE hFile,hMap;
uint64_t s;
hFile= CreateFile(in_name,FILE_READ_DATA,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
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
hbase= mmap(NULL,st.st_size,PROT_READ,MAP_PRIVATE,fd,0);
if(hbase==MAP_FAILED)QUIT("Unable to map file into memory");
close(fd);
hpos= hstart= hbase;
hend= hstart+st.st_size;
#endif
}
/*:5*//*6:*/
#line 212 ".\\hint.w"

bool hget_banner(void)
{char*t;
int i;
for(i= 0;i<MAX_BANNER;i++)
{banner[i]= HGET8;
if(banner[i]=='\n')break;
}
banner[++i]= 0;
t= banner;
if(strncmp("hint",banner,4)!=0)QUIT("This is not a hint file");
else t+= 4;
banner_size= (int)strlen(banner);
if(banner[banner_size-1]!='\n')QUIT("Banner exceeds maximum size=0x%x",MAX_BANNER);
if(*t!=' ')QUIT("Space expected after hint");
else t++;
version= strtol(t,&t,10);
if(*t!='.')QUIT("Dot expected after version number %d",version);
else t++;
subversion= strtol(t,&t,10);
if(*t!=' '&&*t!='\n')QUIT("Space expected after subversion number %d",subversion);
MESSAGE("hint file version %d.%d:%s",version,subversion,t);
DBG(dbgdir,"banner size=0x%x\n",banner_size);
return true;
}

/*:6*//*7:*/
#line 244 ".\\hint.w"

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
#line 272 ".\\hint.w"

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
#line 311 ".\\hint.w"

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

/*:9*//*10:*/
#line 350 ".\\hint.w"

void hallocate_definitions(void)
{kind_t k;
/*15:*/
#line 476 ".\\hint.w"

for(k= 0;k<32;k++)
{if(k==font_kind||k==int_kind||k==dimen_kind||k==xdimen_kind||k==glue_kind||k==baseline_kind||k==range_kind||k==page_kind||k==param_kind)continue;
if(max_ref[k]>=0&&max_ref[k]<=256)
{DBG(dbgdef,"Allocating Definitions for %s=%d: %d entries of "SIZE_F" byte each\n",definition_name[k],k,max_ref[k]+1,sizeof(pointer));
ALLOCATE(pointer_def[k],max_ref[k]+1,pointer);
}
}
/*:15*//*19:*/
#line 505 ".\\hint.w"

ALLOCATE(integer_def,max_ref[int_kind]+1,int32_t);
/*:19*//*24:*/
#line 537 ".\\hint.w"

ALLOCATE(dimen_def,max_ref[dimen_kind]+1,dimen_t);
/*:24*//*29:*/
#line 566 ".\\hint.w"

ALLOCATE(xdimen_def,max_ref[xdimen_kind]+1,xdimen_t);
/*:29*//*36:*/
#line 615 ".\\hint.w"

ALLOCATE(pointer_def[glue_kind],max_ref[glue_kind]+1,pointer);
/*:36*//*40:*/
#line 639 ".\\hint.w"

ALLOCATE(baseline_def,max_ref[baseline_kind]+1,bs_t);
/*:40*//*46:*/
#line 712 ".\\hint.w"

ALLOCATE(font_def,max_ref[font_kind]+1,font_def_t);
/*:46*//*52:*/
#line 789 ".\\hint.w"

ALLOCATE(param_def,max_ref[param_kind]+1,param_def_t);
/*:52*//*58:*/
#line 915 ".\\hint.w"

ALLOCATE(range_def,max_ref[range_kind]+1,range_def_t);
/*:58*//*62:*/
#line 963 ".\\hint.w"

ALLOCATE(page_def,max_ref[page_kind]+1,page_def_t);
/*:62*/
#line 353 ".\\hint.w"

}

void hget_max_definitions(void)
{kind_t k;
/*67:*/
#line 1050 ".\\hint.w"

uint8_t a,z;
HGETTAG(a);
/*:67*/
#line 358 ".\\hint.w"

if(a!=TAG(list_kind,0))QUIT("Start of maximum list expected");
/*16:*/
#line 486 ".\\hint.w"

for(k= 0;k<32;k++)
{free(pointer_def[k]);pointer_def[k]= NULL;}
/*:16*//*20:*/
#line 509 ".\\hint.w"

free(integer_def);integer_def= NULL;
/*:20*//*25:*/
#line 541 ".\\hint.w"

free(dimen_def);dimen_def= NULL;
/*:25*//*30:*/
#line 569 ".\\hint.w"

free(xdimen_def);xdimen_def= NULL;
/*:30*//*41:*/
#line 643 ".\\hint.w"

free(baseline_def);baseline_def= NULL;
/*:41*//*47:*/
#line 716 ".\\hint.w"

free(font_def);font_def= NULL;
/*:47*//*53:*/
#line 793 ".\\hint.w"

if(param_def!=NULL)
{int i;
for(i= 0;i<=max_ref[param_kind];i++)
free_param_list(param_def[i]);
}
free(param_def);param_def= NULL;
/*:53*//*59:*/
#line 919 ".\\hint.w"

free(range_def);range_def= NULL;
/*:59*//*63:*/
#line 967 ".\\hint.w"

free(page_def);page_def= NULL;
/*:63*/
#line 360 ".\\hint.w"

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
/*68:*/
#line 1055 ".\\hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:68*/
#line 375 ".\\hint.w"

}
if(INFO(a)!=0)QUIT("End of maximum list with info %d",INFO(a));
hallocate_definitions();
}
/*:10*//*11:*/
#line 385 ".\\hint.w"

void hget_def_node(void)
{uint8_t n;
/*67:*/
#line 1050 ".\\hint.w"

uint8_t a,z;
HGETTAG(a);
/*:67*/
#line 388 ".\\hint.w"

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
/*68:*/
#line 1055 ".\\hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:68*/
#line 408 ".\\hint.w"

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
/*:11*//*21:*/
#line 513 ".\\hint.w"

static int32_t hget_integer_def(uint8_t a)
{if(INFO(a)==1){int8_t n= HGET8;return n;}
else if(INFO(a)==2){int16_t n;HGET16(n);return n;}
else if(INFO(a)==4){int32_t n;HGET32(n);return n;}
else TAGERR(a);
return 0;
}

int32_t hget_integer_ref(uint8_t n)
{REF(int_kind,n);
return integer_def[n];
}
/*:21*//*26:*/
#line 545 ".\\hint.w"

static scaled hget_dimen_def(void)
{scaled d;HGET32(d);return d;
}

scaled hget_dimen_ref(uint8_t n)
{REF(dimen_kind,n);
return dimen_def[n];
}
/*:26*//*32:*/
#line 576 ".\\hint.w"

static void hget_xdimen_def(uint8_t a,uint8_t n)
{HGET_XDIMEN(INFO(a),xdimen_def[n]);
}

scaled hget_xdimen_ref(uint8_t n)
{REF(xdimen_kind,n);
return xdimen_def[n].w+xdimen_def[n].h*hhsize+xdimen_def[n].v*hvsize;
}
/*:32*//*33:*/
#line 589 ".\\hint.w"

static pointer hget_glue_def(uint8_t a)
{pointer p;
HGET_GLUE(INFO(a));
return p;
}

pointer hget_glue_ref(uint8_t n)
{REF(glue_kind,n);
return pointer_def[glue_kind][n];
}

pointer hget_param_glue(uint8_t n)
{REF(glue_kind,n);
return new_glue(pointer_def[glue_kind][n]);
}
/*:33*//*42:*/
#line 647 ".\\hint.w"

static void hget_baseline_def(uint8_t a,uint8_t n)
{HGET_BASELINE(INFO(a),baseline_def[n]);
}

void hget_baseline_ref(uint8_t n,bs_t*b)
{REF(baseline_kind,n);
*b= baseline_def[n];
}



pointer happend_to_vlist(pointer b)
{scaled d;
pointer p= null;

if(needs_bs&&prev_depth> ignore_depth)
{d= width(cur_bs)-prev_depth-height(b);
if(d<cur_lsl)p= new_glue(cur_ls);
else{p= new_spec(cur_bs);
width(p)= d;p= new_glue(p);
}
link(tail)= p;tail= p;
if(nest_ptr==0)
store_map(p,node_pos,0,0);
}
link(tail)= b;tail= b;prev_depth= depth(b);
needs_bs= false;
return p;
}
/*:42*//*48:*/
#line 719 ".\\hint.w"

static void hget_font_def(uint8_t a,uint8_t n)
{char*t;
HGET_STRING(t);font_def[n].n= strdup(t);
DBG(dbgdef,"Font %d: %s\n",n,t);
if(INFO(a)&b001)HGET32(font_def[n].s);else font_def[n].s= 0;
hget_font_params(n,&(font_def[n]));
}

static void hget_font_params(uint8_t n,font_def_t*f)
{HGET16(f->m);RNG("Font metrics",f->m,3,max_section_no);
HGET16(f->q);RNG("Font glyphs",f->q,3,max_section_no);
f->g= hget_glue_node();
f->h= hget_hyphen_node();
DBG(dbgdef,"Start font parameters\n");
while(KIND(*hpos)!=font_kind)
{kind_t k;
uint8_t n;
/*67:*/
#line 1050 ".\\hint.w"

uint8_t a,z;
HGETTAG(a);
/*:67*/
#line 737 ".\\hint.w"

k= KIND(a);
n= HGET8;
DBG(dbgdef,"Reading font parameter %d: %s\n",n,definition_name[k]);
if(k!=penalty_kind&&k!=kern_kind&&k!=ligature_kind&&
k!=hyphen_kind&&k!=glue_kind&&k!=math_kind&&k!=rule_kind&&k!=image_kind)
QUIT("Font parameter %d has invalid type %s",n,content_name[n]);
RNG("Font parameter",n,0,MAX_FONT_PARAMS);
f->p[n]= hget_definition(a);
/*68:*/
#line 1055 ".\\hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:68*/
#line 746 ".\\hint.w"

}
DBG(dbgdef,"End font definition\n");
}

static void hget_font_metrics(void)
{int i;
for(i= 0;i<=max_ref[font_kind];i++)
if(font_def[i].m!=0)
{hget_section(font_def[i].m);
read_font_info(i,font_def[i].n,font_def[i].s);
}
}
/*:48*//*54:*/
#line 802 ".\\hint.w"

void free_param_list(param_def_t*p)
{while(p!=NULL)
{param_def_t*q= p;
p= p->next;
free(q);
}
}
/*:54*//*55:*/
#line 814 ".\\hint.w"

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
/*67:*/
#line 1050 ".\\hint.w"

uint8_t a,z;
HGETTAG(a);
/*:67*/
#line 827 ".\\hint.w"

ALLOCATE(r,1,param_def_t);
q= &(r->p);
q->n= HGET8;
q->k= KIND(a);
DBG(dbgtags,"Defining %s %d\n",definition_name[KIND(a)],q->n);
if(KIND(a)==int_kind)q->i= hget_integer_def(a);
else if(KIND(a)==dimen_kind)q->d= hget_dimen_def();
else if(KIND(a)==glue_kind)q->g= hget_glue_def(a);
else TAGERR(a);
/*68:*/
#line 1055 ".\\hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:68*/
#line 837 ".\\hint.w"

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
/*67:*/
#line 1050 ".\\hint.w"

uint8_t a,z;
HGETTAG(a);
/*:67*/
#line 852 ".\\hint.w"

p= hget_param_list(a);
/*68:*/
#line 1055 ".\\hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:68*/
#line 854 ".\\hint.w"

return p;
}
}

param_def_t*hget_param_list_ref(uint8_t n)
{REF(param_kind,n);
return param_def[n];
}
/*:55*//*56:*/
#line 868 ".\\hint.w"

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
/*:56*//*60:*/
#line 923 ".\\hint.w"

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

uint8_t hget_page_ref(uint32_t pos)
{int i;
for(i= 1;i<=max_ref[range_kind];i++)
if(range_def[i].f<=pos&&pos<range_def[i].t)return range_def[i].pg;
return 0;
}
/*:60*//*64:*/
#line 971 ".\\hint.w"

static void hget_page_def(uint8_t a,uint8_t n)
{page_def[n].p= null;
}
/*:64*//*65:*/
#line 981 ".\\hint.w"

pointer hget_ligature_ref(uint8_t n)
{REF(ligature_kind,n);
return copy_node_list(pointer_def[ligature_kind][n]);
}

pointer hget_math_ref(uint8_t n)
{REF(math_kind,n);
return copy_node_list(pointer_def[math_kind][n]);
}

pointer hget_rule_ref(uint8_t n)
{REF(rule_kind,n);
return copy_node_list(pointer_def[rule_kind][n]);
}

pointer hget_image_ref(uint16_t n)
{REF(image_kind,n);
return copy_node_list(pointer_def[image_kind][n]);
}

pointer hget_hyphen_ref(uint8_t n)
{REF(hyphen_kind,n);
return copy_node_list(pointer_def[hyphen_kind][n]);
}

pointer hget_leaders_ref(uint8_t n)
{REF(leaders_kind,n);
return copy_node_list(pointer_def[leaders_kind][n]);
}




/*:65*//*66:*/
#line 1036 ".\\hint.w"

void hget_content_section()
{DBG(dbgbasic,"Get Content\n");
hget_section(2);
}
/*:66*//*69:*/
#line 1064 ".\\hint.w"


static void hget_node(uint8_t a)
{switch(a)
{
/*93:*/
#line 1412 ".\\hint.w"

case TAG(glyph_kind,1):HGET_GLYPH(1);break;
case TAG(glyph_kind,2):HGET_GLYPH(2);break;
case TAG(glyph_kind,3):HGET_GLYPH(3);break;
case TAG(glyph_kind,4):HGET_GLYPH(4);break;
/*:93*//*96:*/
#line 1432 ".\\hint.w"

case TAG(penalty_kind,0):tail_append(new_penalty(hget_integer_ref(HGET8)));break;
case TAG(penalty_kind,1):{tail_append(new_penalty(HGET8));}break;
case TAG(penalty_kind,2):{int16_t n;HGET16(n);RNG("Penalty",n,-20000,+20000);tail_append(new_penalty(n));}break;
/*:96*//*101:*/
#line 1476 ".\\hint.w"

case TAG(math_kind,b000):tail_append(hget_math_ref(HGET8));break;
case TAG(math_kind,b100):HGET_MATH(b100,m);break;
case TAG(math_kind,b010):HGET_MATH(b010,m);break;
case TAG(math_kind,b101):HGET_MATH(b101,m);break;
case TAG(math_kind,b011):HGET_MATH(b011,m);break;
/*:101*//*108:*/
#line 1527 ".\\hint.w"

case TAG(rule_kind,b000):tail_append(hget_rule_ref(HGET8));prev_depth= ignore_depth;break;
case TAG(rule_kind,b011):HGET_RULE(b011);prev_depth= ignore_depth;break;
case TAG(rule_kind,b101):HGET_RULE(b101);prev_depth= ignore_depth;break;
case TAG(rule_kind,b001):HGET_RULE(b001);prev_depth= ignore_depth;break;
case TAG(rule_kind,b110):HGET_RULE(b110);prev_depth= ignore_depth;break;
case TAG(rule_kind,b111):HGET_RULE(b111);prev_depth= ignore_depth;break;
/*:108*//*116:*/
#line 1617 ".\\hint.w"

case TAG(glue_kind,b000):tail_append(new_glue(hget_glue_ref(HGET8)));break;
case TAG(glue_kind,b001):{pointer p;HGET_GLUE(b001);tail_append(new_glue(p));}break;
case TAG(glue_kind,b010):{pointer p;HGET_GLUE(b010);tail_append(new_glue(p));}break;
case TAG(glue_kind,b011):{pointer p;HGET_GLUE(b011);tail_append(new_glue(p));}break;
case TAG(glue_kind,b100):{pointer p;HGET_GLUE(b100);tail_append(new_glue(p));}break;
case TAG(glue_kind,b101):{pointer p;HGET_GLUE(b101);tail_append(new_glue(p));}break;
case TAG(glue_kind,b110):{pointer p;HGET_GLUE(b110);tail_append(new_glue(p));}break;
case TAG(glue_kind,b111):{pointer p;HGET_GLUE(b111);tail_append(new_glue(p));}break;
/*:116*//*132:*/
#line 1969 ".\\hint.w"

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
/*:132*//*140:*/
#line 2099 ".\\hint.w"

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
/*:140*//*145:*/
#line 2233 ".\\hint.w"

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
/*:145*//*151:*/
#line 2302 ".\\hint.w"

case TAG(kern_kind,b000):{HGET_KERN(b000);}break;
case TAG(kern_kind,b001):{HGET_KERN(b001);}break;
case TAG(kern_kind,b010):{HGET_KERN(b010);}break;
case TAG(kern_kind,b011):{HGET_KERN(b011);}break;
case TAG(kern_kind,b100):{HGET_KERN(b100);}break;
case TAG(kern_kind,b101):{HGET_KERN(b101);}break;
case TAG(kern_kind,b110):{HGET_KERN(b110);}break;
case TAG(kern_kind,b111):{HGET_KERN(b111);}break;
/*:151*//*157:*/
#line 2354 ".\\hint.w"

case TAG(leaders_kind,0):tail_append(hget_leaders_ref(HGET8));break;
case TAG(leaders_kind,1):HGET_LEADERS(1);break;
case TAG(leaders_kind,2):HGET_LEADERS(2);break;
case TAG(leaders_kind,3):HGET_LEADERS(3);break;
/*:157*//*162:*/
#line 2393 ".\\hint.w"

case TAG(baseline_kind,b000):{hget_baseline_ref(HGET8,&cur_list.bs_field);needs_bs= true;}break;
case TAG(baseline_kind,b010):{HGET_BASELINE(b010,cur_list.bs_field);needs_bs= true;}break;
case TAG(baseline_kind,b011):{HGET_BASELINE(b011,cur_list.bs_field);needs_bs= true;}break;
case TAG(baseline_kind,b100):{HGET_BASELINE(b100,cur_list.bs_field);needs_bs= true;}break;
case TAG(baseline_kind,b101):{HGET_BASELINE(b101,cur_list.bs_field);needs_bs= true;}break;
case TAG(baseline_kind,b110):{HGET_BASELINE(b110,cur_list.bs_field);needs_bs= true;}break;
case TAG(baseline_kind,b111):{HGET_BASELINE(b111,cur_list.bs_field);needs_bs= true;}break;
/*:162*//*167:*/
#line 2446 ".\\hint.w"

case TAG(ligature_kind,0):tail_append(hget_ligature_ref(HGET8));break;
case TAG(ligature_kind,1):HGET_LIG(1);break;
case TAG(ligature_kind,2):HGET_LIG(2);break;
case TAG(ligature_kind,3):HGET_LIG(3);break;
case TAG(ligature_kind,4):HGET_LIG(4);break;
case TAG(ligature_kind,5):HGET_LIG(5);break;
case TAG(ligature_kind,6):HGET_LIG(6);break;
case TAG(ligature_kind,7):HGET_LIG(7);break;
/*:167*//*172:*/
#line 2499 ".\\hint.w"

case TAG(hyphen_kind,b000):tail_append(hget_hyphen_ref(HGET8));break;
case TAG(hyphen_kind,b001):{HGET_HYPHEN(b001);tail_append(p);}break;
case TAG(hyphen_kind,b010):{HGET_HYPHEN(b010);tail_append(p);}break;
case TAG(hyphen_kind,b011):{HGET_HYPHEN(b011);tail_append(p);}break;
case TAG(hyphen_kind,b100):{HGET_HYPHEN(b100);tail_append(p);}break;
case TAG(hyphen_kind,b101):{HGET_HYPHEN(b101);tail_append(p);}break;
case TAG(hyphen_kind,b110):{HGET_HYPHEN(b110);tail_append(p);}break;
case TAG(hyphen_kind,b111):{HGET_HYPHEN(b111);tail_append(p);}break;
/*:172*//*178:*/
#line 2575 ".\\hint.w"

case TAG(par_kind,b000):HGET_PAR(b000);break;
case TAG(par_kind,b010):HGET_PAR(b010);break;
case TAG(par_kind,b100):HGET_PAR(b100);break;
case TAG(par_kind,b110):HGET_PAR(b110);break;
/*:178*//*186:*/
#line 2760 ".\\hint.w"

case TAG(display_kind,b000):HGET_DISPLAY(b000);break;
case TAG(display_kind,b001):HGET_DISPLAY(b001);break;
case TAG(display_kind,b010):HGET_DISPLAY(b010);break;
case TAG(display_kind,b100):HGET_DISPLAY(b100);break;
case TAG(display_kind,b101):HGET_DISPLAY(b101);break;
case TAG(display_kind,b110):HGET_DISPLAY(b110);break;
/*:186*//*190:*/
#line 2814 ".\\hint.w"

case TAG(adjust_kind,1):HGET_ADJUST(1);break;
case TAG(adjust_kind,2):HGET_ADJUST(2);break;
case TAG(adjust_kind,3):HGET_ADJUST(3);break;
case TAG(adjust_kind,4):HGET_ADJUST(4);break;
case TAG(adjust_kind,5):HGET_ADJUST(5);break;
/*:190*//*193:*/
#line 2850 ".\\hint.w"

case TAG(image_kind,b000):hget_image_ref(HGET8);break;
case TAG(image_kind,b100):HGET_IMAGE(b100);break;
case TAG(image_kind,b101):HGET_IMAGE(b101);break;
case TAG(image_kind,b110):HGET_IMAGE(b110);break;
case TAG(image_kind,b111):HGET_IMAGE(b111);break;
/*:193*/
#line 1069 ".\\hint.w"

default:
TAGERR(a);
}
}

void hget_content(void)
{/*67:*/
#line 1050 ".\\hint.w"

uint8_t a,z;
HGETTAG(a);
/*:67*/
#line 1076 ".\\hint.w"

node_pos= (hpos-hstart)-1;
hget_node(a);
/*68:*/
#line 1055 ".\\hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:68*/
#line 1079 ".\\hint.w"

if(nest_ptr==0&&tail!=head&&(type(tail)==penalty_node||type(tail)==glue_node||type(tail)==kern_node))
store_map(tail,node_pos,0,0);
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
/*:69*//*79:*/
#line 1236 ".\\hint.w"

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
/*:79*//*80:*/
#line 1263 ".\\hint.w"

float32_t hget_float32(void)
{union{float32_t d;uint32_t bits;}u;
HGET32(u.bits);
return u.d;
}
/*:80*//*84:*/
#line 1298 ".\\hint.w"

scaled hget_xdimen(uint8_t a)
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

scaled hget_xdimen_node(void)
{scaled x= 0;
/*67:*/
#line 1050 ".\\hint.w"

uint8_t a,z;
HGETTAG(a);
/*:67*/
#line 1320 ".\\hint.w"

if(KIND(a)==xdimen_kind)
x= hget_xdimen(a);
else
QUIT("Extent expected at 0x%x got %s",node_pos,NAME(a));
/*68:*/
#line 1055 ".\\hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:68*/
#line 1325 ".\\hint.w"

return x;
}
/*:84*//*110:*/
#line 1546 ".\\hint.w"

pointer hget_rule_node(void)
{pointer p= null;
/*67:*/
#line 1050 ".\\hint.w"

uint8_t a,z;
HGETTAG(a);
/*:67*/
#line 1549 ".\\hint.w"

if(KIND(a)==rule_kind){HGET_RULE(INFO(a));}
else QUIT("Rule expected at 0x%x got %s",node_pos,NAME(a));
/*68:*/
#line 1055 ".\\hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:68*/
#line 1552 ".\\hint.w"

return p;
}
/*:110*//*120:*/
#line 1657 ".\\hint.w"

pointer hget_glue_spec(void)
{pointer p= null;
uint8_t a,z;
if(hpos>=hend)return null;
if(KIND(*hpos)!=glue_kind)return null;
node_pos= hpos-hstart;
HGETTAG(a);
if(INFO(a)==b000)p= hget_glue_ref(HGET8);
else
{HGET_GLUE(INFO(a));}
/*68:*/
#line 1055 ".\\hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:68*/
#line 1668 ".\\hint.w"

return p;
}


pointer hget_glue_node(void)
{pointer p= hget_glue_spec();
if(p!=null)p= new_glue(p);
return p;
}
/*:120*//*126:*/
#line 1748 ".\\hint.w"

void hget_size_boundary(info_t info)
{uint32_t n;
if(info<2)return;
n= HGET8;
if(n-1!=0x100-info)QUIT("Size boundary byte 0x%x with info value %d at "SIZE_F,
n,info,hpos-hstart-1);
}

uint32_t hget_list_size(info_t info)
{uint32_t n;
if(info==1)return 0;
else if(info==2)n= HGET8;
else if(info==3)HGET16(n);
else if(info==4)HGET24(n);
else if(info==5)HGET32(n);
else QUIT("List info %d must be 1, 2, 3, 4, or 5",info);
return n;
}

pointer hget_node_list(uint32_t s)
{uint8_t*list_end= hpos+s;
pointer p;
push_nest();
needs_bs= false;
while(hpos<list_end)
hget_content();
if(needs_bs)
QUIT("Unexpected trailing baseline node");
p= link(head);
pop_nest();
return p;
}

pointer hget_text_list(uint32_t s)
{QUIT("Text not implemented");
return null;
}

pointer hget_list(void)
{if(!IS_LIST(*hpos))return null;
else
{pointer p;
uint32_t s,t;
/*67:*/
#line 1050 ".\\hint.w"

uint8_t a,z;
HGETTAG(a);
/*:67*/
#line 1792 ".\\hint.w"

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
/*68:*/
#line 1055 ".\\hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:68*/
#line 1803 ".\\hint.w"

return p;
}
}
/*:126*//*134:*/
#line 2007 ".\\hint.w"

pointer hget_hbox_node(void)
{/*67:*/
#line 1050 ".\\hint.w"

uint8_t a,z;
HGETTAG(a);
/*:67*/
#line 2009 ".\\hint.w"

if(KIND(a)!=hbox_kind)QUIT("Hbox expected at 0x%x got %s",node_pos,NAME(a));
{
HGET_BOX(INFO(a));
/*68:*/
#line 1055 ".\\hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:68*/
#line 2013 ".\\hint.w"

return p;
}
}


pointer hget_vbox_node(void)
{
/*67:*/
#line 1050 ".\\hint.w"

uint8_t a,z;
HGETTAG(a);
/*:67*/
#line 2021 ".\\hint.w"

if(KIND(a)!=vbox_kind)QUIT("Vbox expected at 0x%x got %s",node_pos,NAME(a));
{
HGET_BOX(INFO(a));
/*68:*/
#line 1055 ".\\hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:68*/
#line 2025 ".\\hint.w"

type(p)= vlist_node;
return p;
}
}
/*:134*//*174:*/
#line 2521 ".\\hint.w"

pointer hget_hyphen_node(void)
{/*67:*/
#line 1050 ".\\hint.w"

uint8_t a,z;
HGETTAG(a);
/*:67*/
#line 2523 ".\\hint.w"

if(KIND(a)!=hyphen_kind||INFO(a)==b000)
QUIT("Hyphen expected at 0x%x got %s,%d",node_pos,NAME(a),INFO(a));
{
HGET_HYPHEN(INFO(a));
/*68:*/
#line 1055 ".\\hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:68*/
#line 2528 ".\\hint.w"

return p;
}
}
/*:174*//*179:*/
#line 2605 ".\\hint.w"

static void transplant_post_break_list(void)
{pointer r,q= link(head);
int t= replace_count(q);
pointer s= post_break(q);
r= q;
while(t> 0){r= link(r);t--;}
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

void hget_paragraph(scaled x,param_def_t*q,uint32_t offset)
{uint32_t s,t;
uint8_t a,z;
if(!IS_LIST(*hpos))return;
HGETTAG(a);
s= hget_list_size(INFO(a));
hget_size_boundary(INFO(a));
if(KIND(a)==list_kind)
{uint8_t*list_end= hpos+s;
cur_list.hs_field= x;
hset_param_list(q);
push_nest();
needs_bs= false;
if(offset> 0)hpos= hstart+node_pos1+offset;
while(hpos<list_end)
{hget_content();
if(nest_ptr==1)
{pointer p= tail;
if(p!=head&&!is_char_node(p)&&
(type(p)==glue_node||type(p)==kern_node||type(p)==penalty_node||type(p)==disc_node||type(p)==math_node))
store_map(p,node_pos,0,0);
}
}
hget_size_boundary(INFO(a));
t= hget_list_size(INFO(a));
if(t!=s)
QUIT("List sizes at 0x%x and "SIZE_F" do not match 0x%x != 0x%x",node_pos+1,hpos-hstart-s-1,s,t);
/*68:*/
#line 1055 ".\\hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:68*/
#line 2665 ".\\hint.w"

if(offset> 0&&link(head)!=null&&!is_char_node(link(head)))
{if(type(link(head))==disc_node)
transplant_post_break_list();
else
hprune_unwanted_nodes();
}
if(needs_bs)
QUIT("Unexpected trailing baseline node");
if(head==tail)
pop_nest();
else
{store_map(link(head),node_pos1,0,0);
line_break(hget_integer_ref(widow_penalty_no));
}
hrestore_param_list();
}
else QUIT("Text in paragraph not yet implemented");
}

void hget_par_node(uint32_t offset)
{scaled x= 0;
param_def_t*q;
/*67:*/
#line 1050 ".\\hint.w"

uint8_t a,z;
HGETTAG(a);
/*:67*/
#line 2688 ".\\hint.w"

node_pos= (hpos-hstart)-1;
if(INFO(a)&b100)x= hget_xdimen_node();else x= hget_xdimen_ref(HGET8);
if(INFO(a)&b010)q= hget_param_list_node();else q= hget_param_list_ref(HGET8);
hget_paragraph(x,q,offset);
/*68:*/
#line 1055 ".\\hint.w"

HGETTAG(z);
if(a!=z)TAGSERR(a,z);
/*:68*/
#line 2693 ".\\hint.w"

}
/*:179*/
#line 3862 ".\\hint.w"

/*:251*/
