	/*365:*/
	#line 7915 "format.w"

#ifndef _HFORMAT_H_
#define _HFORMAT_H_
	/*331:*/
	#line 7197 "format.w"

#define REF_RNG(K,N) if ((int)(N)>max_ref[K]) QUIT("Reference %d to %s out of range [0 - %d]",\
  (N),definition_name[K],max_ref[K])
	/*:331*/	/*332:*/
	#line 7211 "format.w"

#define MAX_REF(K) ((K)==label_kind?0xFFFF:0xFF)
	/*:332*/	/*406:*/
	#line 8655 "format.w"

#ifdef WIN32
#define SIZE_F "0x%x"
#else
#define SIZE_F "0x%zx"
#endif
#ifdef DEBUG
#define DBG(FLAGS,...) ((debugflags & (FLAGS))?LOG(__VA_ARGS__):0)
#else
#define DBG(FLAGS,...) 0
#endif
#define DBGTAG(A,P) DBG(DBGTAGS,"tag [%s,%d] at " SIZE_F "\n",NAME(A),INFO(A),(P)-hstart)

#define RNG(S,N,A,Z) \
  if ((int)(N)<(int)(A)||(int)(N)>(int)(Z)) QUIT(S " %d out of range [%d - %d]",N,A,Z)

#define TAGERR(A) QUIT("Unknown tag [%s,%d] at " SIZE_F "\n",NAME(A),INFO(A),hpos-hstart)
	/*:406*/
	#line 7918 "format.w"

	/*391:*/
	#line 8430 "format.w"

#define DBGNONE     0x0
#define DBGBASIC    0x1
#define DBGTAGS     0x2
#define DBGNODE     0x4
#define DBGDEF      0x8
#define DBGDIR      0x10
#define DBGRANGE    0x20
#define DBGFLOAT    0x40
#define DBGCOMPRESS 0x80
#define DBGBUFFER   0X100
#define DBGFLEX     0x200
#define DBGBISON    0x400
#define DBGTEX      0x800
#define DBGPAGE     0x1000
#define DBGFONT     0x2000
#define DBGRENDER   0x4000
	/*:391*/
	#line 7919 "format.w"

	/*11:*/
	#line 620 "format.w"

#define KIND(T)      (((T)>>3)&0x1F)
#define NAME(T)      content_name[KIND(T)]
#define INFO(T)      ((T)&0x7)
#define TAG(K,I)     (((K)<<3)|(I))
	/*:11*/	/*75:*/
	#line 1590 "format.w"

#define ROUND(X)     ((int)((X)>=0.0?floor((X)+0.5):ceil((X)-0.5)))
	/*:75*/	/*110:*/
	#line 2091 "format.w"

#define RUNNING_DIMEN 0xC0000000
	/*:110*/	/*121:*/
	#line 2330 "format.w"

#define ZERO_GLUE(G) ((G).w.w==0  && (G).w.h==0.0  && (G).w.v==0.0  && (G).p.f==0.0 && (G).m.f==0.0)
	/*:121*/	/*236:*/
	#line 4604 "format.w"

#define HINT_NO_POS 0xFFFFFFFF
	/*:236*/	/*245:*/
	#line 4899 "format.w"

#define HINT_TOP 1
#define HINT_BOT 2
#define HINT_MID 3
	/*:245*/	/*278:*/
	#line 5949 "format.w"

#define ALLOCATE(R,S,T) ((R)= (T *)calloc((S),sizeof(T)),\
        (((R)==NULL)?QUIT("Out of memory for " #R):0))
#define REALLOCATE(R,S,T) ((R)= (T *)realloc((R),(S)*sizeof(T)),\
        (((R)==NULL)?QUIT("Out of memory for " #R):0))
	/*:278*/	/*286:*/
	#line 6114 "format.w"

#define MAX_BANNER 256
	/*:286*/	/*299:*/
	#line 6303 "format.w"

#define MAX_TAG_DISTANCE 32 
	/*:299*/
	#line 7920 "format.w"

	/*6:*/
	#line 477 "format.w"

#define DEF_KIND(C,D,N) C##_kind= N
typedef enum{	/*8:*/
	#line 541 "format.w"

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
DEF_KIND(language,language,10),
DEF_KIND(rule,rule,11),
DEF_KIND(image,image,12),
DEF_KIND(leaders,leaders,13),
DEF_KIND(baseline,baseline,14),
DEF_KIND(hbox,hbox,15),
DEF_KIND(vbox,vbox,16),
DEF_KIND(par,par,17),
DEF_KIND(math,math,18),
DEF_KIND(table,table,19),
DEF_KIND(item,item,20),
DEF_KIND(hset,hset,21),
DEF_KIND(vset,vset,22),
DEF_KIND(hpack,hpack,23),
DEF_KIND(vpack,vpack,24),
DEF_KIND(stream,stream,25),
DEF_KIND(page,page,26),
DEF_KIND(range,range,27),
DEF_KIND(link,label,28),
DEF_KIND(undefined2,undefined2,29),
DEF_KIND(undefined3,undefined3,30),
DEF_KIND(penalty,int,31)

	/*:8*/
	#line 479 "format.w"
,	/*9:*/
	#line 580 "format.w"

font_kind= glyph_kind,int_kind= penalty_kind,dimen_kind= kern_kind,label_kind= link_kind,
	/*:9*/
	#line 479 "format.w"
}kind_t;
#undef DEF_KIND
	/*:6*/	/*10:*/
	#line 606 "format.w"

typedef enum{b000= 0,b001= 1,b010= 2,b011= 3,b100= 4,b101= 5,b110= 6,b111= 7}info_t;
	/*:10*/	/*54:*/
	#line 1259 "format.w"


#define FLT_M_BITS 23
#define FLT_E_BITS 8
#define FLT_EXCESS 127

#define DBL_M_BITS 52
#define DBL_E_BITS 11
#define DBL_EXCESS 1023

	/*:54*/	/*74:*/
	#line 1585 "format.w"

typedef int32_t scaled_t;
#define ONE ((scaled_t)(1<<16))
	/*:74*/	/*79:*/
	#line 1641 "format.w"

typedef scaled_t dimen_t;
#define MAX_DIMEN ((dimen_t)(0x3FFFFFFF))
	/*:79*/	/*84:*/
	#line 1697 "format.w"

typedef struct{
dimen_t w;float32_t h,v;
}xdimen_t;
	/*:84*/	/*93:*/
	#line 1842 "format.w"

typedef enum{normal_o= 0,fil_o= 1,fill_o= 2,filll_o= 3}order_t;
typedef struct{float64_t f;order_t o;}stretch_t;
typedef union{float32_t f;uint32_t u;}stch_t;
	/*:93*/	/*120:*/
	#line 2320 "format.w"

typedef struct{
xdimen_t w;
stretch_t p,m;
}glue_t;
	/*:120*/	/*178:*/
	#line 3810 "format.w"

typedef struct{
glue_t bs,ls;
dimen_t lsl;
}baseline_t;
	/*:178*/	/*354:*/
	#line 7709 "format.w"

#define MAX_FONT_PARAMS 11
	/*:354*/
	#line 7921 "format.w"

	/*368:*/
	#line 8029 "format.w"

typedef enum{
zero_int_no= 0,
pretolerance_no= 1,
tolerance_no= 2,
line_penalty_no= 3,
hyphen_penalty_no= 4,
ex_hyphen_penalty_no= 5,
club_penalty_no= 6,
widow_penalty_no= 7,
display_widow_penalty_no= 8,
broken_penalty_no= 9,
pre_display_penalty_no= 10,
post_display_penalty_no= 11,
inter_line_penalty_no= 12,
double_hyphen_demerits_no= 13,
final_hyphen_demerits_no= 14,
adj_demerits_no= 15,
looseness_no= 16,
time_no= 17,
day_no= 18,
month_no= 19,
year_no= 20,
hang_after_no= 21,
floating_penalty_no= 22
}int_no_t;
#define MAX_INT_DEFAULT floating_penalty_no
	/*:368*/	/*370:*/
	#line 8103 "format.w"

typedef enum{
zero_dimen_no= 0,
hsize_dimen_no= 1,
vsize_dimen_no= 2,
line_skip_limit_no= 3,
max_depth_no= 4,
split_max_depth_no= 5,
hang_indent_no= 6,
emergency_stretch_no= 7,
quad_no= 8,
math_quad_no= 9
}dimen_no_t;
#define MAX_DIMEN_DEFAULT math_quad_no
	/*:370*/	/*372:*/
	#line 8148 "format.w"

typedef enum{
zero_xdimen_no= 0,
hsize_xdimen_no= 1,
vsize_xdimen_no= 2
}xdimen_no_t;
#define MAX_XDIMEN_DEFAULT vsize_xdimen_no
	/*:372*/	/*374:*/
	#line 8172 "format.w"

typedef enum{
zero_skip_no= 0,
fil_skip_no= 1,
fill_skip_no= 2,
line_skip_no= 3,
baseline_skip_no= 4,
above_display_skip_no= 5,
below_display_skip_no= 6,
above_display_short_skip_no= 7,
below_display_short_skip_no= 8,
left_skip_no= 9,
right_skip_no= 10,
top_skip_no= 11,
split_top_skip_no= 12,
tab_skip_no= 13,
par_fill_skip_no= 14
}glue_no_t;
#define MAX_GLUE_DEFAULT par_fill_skip_no
	/*:374*/	/*376:*/
	#line 8258 "format.w"

typedef enum{
zero_baseline_no= 0
}baseline_no_t;
#define MAX_BASELINE_DEFAULT zero_baseline_no
	/*:376*/	/*378:*/
	#line 8275 "format.w"

typedef enum{
zero_stream_no= 0
}stream_no_t;
#define MAX_STREAM_DEFAULT zero_stream_no
	/*:378*/	/*380:*/
	#line 8291 "format.w"

typedef enum{
zero_page_no= 0
}page_no_t;
#define MAX_PAGE_DEFAULT zero_page_no
	/*:380*/	/*382:*/
	#line 8308 "format.w"

typedef enum{
zero_range_no= 0
}range_no_t;
#define MAX_RANGE_DEFAULT zero_range_no
	/*:382*/
	#line 7922 "format.w"



extern const char*content_name[32];
extern const char*definition_name[32];
extern unsigned int debugflags;
extern FILE*hlog;
extern int max_fixed[32],max_default[32],max_ref[32],max_public;
extern int32_t int_defaults[MAX_INT_DEFAULT+1];
extern dimen_t dimen_defaults[MAX_DIMEN_DEFAULT+1];
extern xdimen_t xdimen_defaults[MAX_XDIMEN_DEFAULT+1];
extern glue_t glue_defaults[MAX_GLUE_DEFAULT+1];
extern baseline_t baseline_defaults[MAX_BASELINE_DEFAULT+1];
#endif
	/*:365*/
