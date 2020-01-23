	/*420:*/
	#line 8049 "format.w"

	/*11:*/
	#line 599 "format.w"

#define KIND(T)      (((T)>>3)&0x1F)
#define NAME(T)      content_name[KIND(T)]
#define INFO(T)      ((T)&0x7)
#define TAG(K,I)     (((K)<<3)|(I))
	/*:11*/	/*29:*/
	#line 907 "format.w"

#define MAX_SCRATCH    (1<<13) 
	/*:29*/	/*114:*/
	#line 2059 "format.w"

#define RUNNING_DIMEN 0xC0000000
	/*:114*/	/*125:*/
	#line 2289 "format.w"

#define ZERO_GLUE(G) ((G).w.w==0  && (G).w.h==0.0  && (G).w.v==0.0  && (G).p.f==0.0 && (G).m.f==0.0)
	/*:125*/	/*253:*/
	#line 5180 "format.w"

#define ALLOCATE(R,S,T) ((R)= calloc((S),sizeof(T)),\
        (((R)==NULL)?QUIT("Out of memory for " #R):0))
#define REALLOCATE(R,S,T) ((R)= realloc((R),(S)*sizeof(T)),\
        (((R)==NULL)?QUIT("Out of memory for " #R):0))
	/*:253*/	/*261:*/
	#line 5354 "format.w"

#define MAX_BANNER 256
	/*:261*/	/*271:*/
	#line 5482 "format.w"

#define SAFETY_MARGIN 32 
	/*:271*/	/*299:*/
	#line 6172 "format.w"

#define REF(K,N) if ((int)(N)>max_ref[K]) QUIT("Reference %d to %s out of range [0 - %d]",\
  (N),definition_name[K],max_ref[K])
	/*:299*/	/*304:*/
	#line 6232 "format.w"

#define HSET_MAX(K,M) RNG("Maximum",(signed)M,max_fixed[K]+1,0xFF); \
if ((signed)M>max_ref[K]) {max_ref[K]= M; DBG(dbgdef,"Setting max %s to %d\n",definition_name[K],M);}
	/*:304*/	/*313:*/
	#line 6397 "format.w"

#define PARAM_REF(D) \
  if((D).k!=int_kind && (D).k!=dimen_kind &&   (D).k!=glue_kind)\
    QUIT("Kind %s not allowed in parameter list", definition_name[D.k]);\
  REF((D).k,(D).n);
	/*:313*/	/*320:*/
	#line 6494 "format.w"

#define MAX_FONT_PARAMS 11
	/*:320*/	/*366:*/
	#line 7340 "format.w"

#ifdef WIN32
#define SIZE_F "0x%x"
#else
#define SIZE_F "0x%zx"
#endif
#ifdef DEBUG
#define DBG(flags,...) ((debugflags & flags)?MESSAGE(__VA_ARGS__):0)
#else
#define DBG(flags,...) (void)0
#endif
#define DBGTAG(A,P) DBG(dbgtags,"tag [%s,%d] at " SIZE_F "\n",NAME(A),INFO(A),(P)-hstart)

	/*:366*/
	#line 8050 "format.w"

	/*1:*/
	#line 314 "format.w"

typedef struct{uint32_t c;uint8_t f;}glyph_t;
	/*:1*/	/*6:*/
	#line 473 "format.w"

#define DEF_KIND(C,D,N) C##_kind= N
typedef enum{	/*8:*/
	#line 520 "format.w"

DEF_KIND(text,text,0),
DEF_KIND(list,list,1),
DEF_KIND(param,param,2),
DEF_KIND(xdimen,xdimen,3),
DEF_KIND(adjust,adjust,4),
DEF_KIND(glyph,font,5),
DEF_KIND(kern,dimen,6),
DEF_KIND(glue,glue,7),
DEF_KIND(ligature,ligature,8),
DEF_KIND(hyphen,hyphen,9),
DEF_KIND(math,math,10),
DEF_KIND(rule,rule,11),
DEF_KIND(image,image,12),
DEF_KIND(leaders,leaders,13),
DEF_KIND(baseline,baseline,14),
DEF_KIND(hbox,hbox,15),
DEF_KIND(vbox,vbox,16),
DEF_KIND(par,par,17),
DEF_KIND(display,display,18),
DEF_KIND(table,table,19),
DEF_KIND(item,item,20),
DEF_KIND(hset,hset,21),
DEF_KIND(vset,vset,22),
DEF_KIND(hpack,hpack,23),
DEF_KIND(vpack,vpack,24),
DEF_KIND(stream,stream,25),
DEF_KIND(page,page,26),
DEF_KIND(range,range,27),
DEF_KIND(undefined1,undefined1,28),
DEF_KIND(undefined2,undefined2,29),
DEF_KIND(undefined3,undefined3,30),
DEF_KIND(penalty,int,31)

	/*:8*/
	#line 475 "format.w"
,	/*9:*/
	#line 559 "format.w"

font_kind= glyph_kind,int_kind= penalty_kind,dimen_kind= kern_kind
	/*:9*/
	#line 475 "format.w"
}kind_t;
#undef DEF_KIND
	/*:6*/	/*10:*/
	#line 585 "format.w"

typedef enum{b000= 0,b001= 1,b010= 2,b011= 3,b100= 4,b101= 5,b110= 6,b111= 7}info_t;
	/*:10*/	/*56:*/
	#line 1217 "format.w"


#define FLT_M_BITS 23
#define FLT_E_BITS 8
#define FLT_EXCESS 127
#if __SIZEOF_DOUBLE__==8
typedef double float64_t;
#else
#error double type must have size 8
#endif
#define DBL_M_BITS 52
#define DBL_E_BITS 11
#define DBL_EXCESS 1023
#if __SIZEOF_FLOAT__==4
typedef float float32_t;
#else
#error float type must have size 4
#endif

	/*:56*/	/*76:*/
	#line 1550 "format.w"

typedef int32_t scaled_t;
#define ONE ((scaled_t)(1<<16))
#define ROUND(X)     ((int)((X)>=0.0?floor((X)+0.5):ceil((X)-0.5)))
	/*:76*/	/*80:*/
	#line 1603 "format.w"

typedef scaled_t dimen_t;
#define MAX_DIMEN ((dimen_t)(0x3FFFFFFF))
	/*:80*/	/*85:*/
	#line 1657 "format.w"

typedef struct{
dimen_t w;float32_t h,v;
}xdimen_t;
	/*:85*/	/*93:*/
	#line 1799 "format.w"

typedef enum{normal_o= 0,fil_o= 1,fill_o= 2,filll_o= 3}order_t;
typedef struct{float64_t f;order_t o;}stretch_t;
typedef union{float32_t f;uint32_t u;}stch_t;
	/*:93*/	/*106:*/
	#line 1972 "format.w"

typedef struct{
bool on;
dimen_t w;
}math_t;
	/*:106*/	/*115:*/
	#line 2086 "format.w"

typedef struct{
dimen_t h,d,w;
}rule_t;
	/*:115*/	/*124:*/
	#line 2279 "format.w"

typedef struct{
xdimen_t w;
stretch_t p,m;
}glue_t;
	/*:124*/	/*134:*/
	#line 2507 "format.w"

typedef struct{
kind_t k;
uint32_t p;
uint32_t s;
}list_t;
	/*:134*/	/*143:*/
	#line 2900 "format.w"

typedef enum{txt_font= 0x00,txt_global= 0x08,txt_local= 0x11,txt_cc= 0x1D,txt_node= 0x1E,
txt_hyphen= 0x1F,txt_glue= 0x20,txt_ignore= 0xFB}txt_t;
	/*:143*/	/*154:*/
	#line 3138 "format.w"

typedef struct{kind_t k;uint8_t n;}ref_t;
	/*:154*/	/*155:*/
	#line 3168 "format.w"

typedef struct{dimen_t h,d,w,a;float32_t r;int8_t s,o;list_t l;}box_t;
	/*:155*/	/*169:*/
	#line 3514 "format.w"

typedef struct{
bool x;
xdimen_t d;
}kern_t;
	/*:169*/	/*183:*/
	#line 3708 "format.w"

typedef struct{
glue_t bs,ls;
dimen_t lsl;
}baseline_t;
	/*:183*/	/*190:*/
	#line 3798 "format.w"

typedef struct{uint8_t f;list_t l;}lig_t;
	/*:190*/	/*198:*/
	#line 3906 "format.w"
typedef struct hyphen_t{bool x;list_t p,q;uint8_t r;}hyphen_t;	/*:198*/	/*229:*/
	#line 4355 "format.w"

typedef struct{
uint16_t n;
dimen_t w,h;
stretch_t p,m;
}image_t;
	/*:229*/	/*250:*/
	#line 5162 "format.w"

typedef
struct{uint8_t pg;uint32_t pos;bool on;int link;}range_pos_t;
	/*:250*/	/*280:*/
	#line 5719 "format.w"

typedef struct{
uint64_t pos;
uint32_t size,xsize;
uint16_t section_no;
char*file_name;
uint8_t*buffer;
uint32_t bsize;
}entry_t;
	/*:280*/	/*308:*/
	#line 6318 "format.w"

typedef struct{kind_t k;int n;}def_t;
	/*:308*/	/*355:*/
	#line 7163 "format.w"

typedef enum{dbgnone= 0x0,
dbgbasic= 0x1,
dbgtags= 0x2,
dbgnode= 0x4,
dbgdef= 0x8,
dbgdir= 0x10,
dbgrange= 0x20,
dbgfloat= 0x40,
dbgcompress= 0x80,
dbgbuffer= 0x100,
dbgflex= 0x200,
dbgbison= 0x400
}debugmode;
	/*:355*/
	#line 8051 "format.w"

extern char in_name[];
extern int version,subversion;
extern char scratch_buffer[];
extern int max_ref[];
extern const char*content_name[],*definition_name[];
extern int32_t int_defaults[];
extern dimen_t dimen_defaults[];
extern xdimen_t xdimen_defaults[];
extern char**hfont_name;
extern entry_t*dir;
extern int next_range,max_range;
extern int*page_on;
extern range_pos_t*range_pos;
extern uint16_t max_section_no,section_no;
extern size_t dir_size,def_size,content_size;
extern uint8_t*hpos,*hend,*hstart;
extern debugmode debugflags;
extern int hbanner_size;
extern FILE*hin,*hout,*hlog;
extern bool option_utf8,option_hex,option_force,option_compress;
extern char hbanner[MAX_BANNER+1];
extern void hallocate_data(void);
extern bool xdimen_eq(xdimen_t*x,xdimen_t*y);
extern void new_directory(uint32_t size);
extern void new_output_buffers(void);
extern void new_section(uint32_t i,char*file_name);
extern void hset_entry(entry_t*e,uint16_t i,uint32_t size,uint32_t xsize,char*file_name);
extern void hset_max(void);
extern void new_max_list(void);
extern void new_content(void);
extern size_t hwrite_banner(char*magic);
extern bool hread_banner(char*magic);
extern void hcompress(uint16_t n);
extern void hdecompress(uint16_t n);
extern int txt_length;
	/*:420*/
