	/*333:*/
	#line 6968 "format.w"

#ifndef _HFORMAT_H_
#define _HFORMAT_H_
	/*302:*/
	#line 6427 "format.w"

#define REF(K,N) if ((int)(N)>max_ref[K]) QUIT("Reference %d to %s out of range [0 - %d]",\
  (N),definition_name[K],max_ref[K])
	/*:302*/	/*372:*/
	#line 7682 "format.w"

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
	/*:372*/
	#line 6971 "format.w"

	/*357:*/
	#line 7457 "format.w"

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
	/*:357*/
	#line 6972 "format.w"

	/*11:*/
	#line 614 "format.w"

#define KIND(T)      (((T)>>3)&0x1F)
#define NAME(T)      content_name[KIND(T)]
#define INFO(T)      ((T)&0x7)
#define TAG(K,I)     (((K)<<3)|(I))
	/*:11*/	/*75:*/
	#line 1564 "format.w"

#define ROUND(X)     ((int)((X)>=0.0?floor((X)+0.5):ceil((X)-0.5)))
	/*:75*/	/*113:*/
	#line 2071 "format.w"

#define RUNNING_DIMEN 0xC0000000
	/*:113*/	/*124:*/
	#line 2301 "format.w"

#define ZERO_GLUE(G) ((G).w.w==0  && (G).w.h==0.0  && (G).w.v==0.0  && (G).p.f==0.0 && (G).m.f==0.0)
	/*:124*/	/*251:*/
	#line 5213 "format.w"

#define ALLOCATE(R,S,T) ((R)= calloc((S),sizeof(T)),\
        (((R)==NULL)?QUIT("Out of memory for " #R):0))
#define REALLOCATE(R,S,T) ((R)= realloc((R),(S)*sizeof(T)),\
        (((R)==NULL)?QUIT("Out of memory for " #R):0))
	/*:251*/	/*258:*/
	#line 5375 "format.w"

#define MAX_BANNER 256
	/*:258*/	/*270:*/
	#line 5555 "format.w"

#define MAX_TAG_DISTANCE 32 
	/*:270*/
	#line 6973 "format.w"

	/*6:*/
	#line 473 "format.w"

#define DEF_KIND(C,D,N) C##_kind= N
typedef enum{	/*8:*/
	#line 535 "format.w"

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
	#line 574 "format.w"

font_kind= glyph_kind,int_kind= penalty_kind,dimen_kind= kern_kind
	/*:9*/
	#line 475 "format.w"
}kind_t;
#undef DEF_KIND
	/*:6*/	/*10:*/
	#line 600 "format.w"

typedef enum{b000= 0,b001= 1,b010= 2,b011= 3,b100= 4,b101= 5,b110= 6,b111= 7}info_t;
	/*:10*/	/*54:*/
	#line 1235 "format.w"


#define FLT_M_BITS 23
#define FLT_E_BITS 8
#define FLT_EXCESS 127

#define DBL_M_BITS 52
#define DBL_E_BITS 11
#define DBL_EXCESS 1023

	/*:54*/	/*74:*/
	#line 1559 "format.w"

typedef int32_t scaled_t;
#define ONE ((scaled_t)(1<<16))
	/*:74*/	/*79:*/
	#line 1615 "format.w"

typedef scaled_t dimen_t;
#define MAX_DIMEN ((dimen_t)(0x3FFFFFFF))
	/*:79*/	/*84:*/
	#line 1669 "format.w"

typedef struct{
dimen_t w;float32_t h,v;
}xdimen_t;
	/*:84*/	/*92:*/
	#line 1811 "format.w"

typedef enum{normal_o= 0,fil_o= 1,fill_o= 2,filll_o= 3}order_t;
typedef struct{float64_t f;order_t o;}stretch_t;
typedef union{float32_t f;uint32_t u;}stch_t;
	/*:92*/	/*123:*/
	#line 2291 "format.w"

typedef struct{
xdimen_t w;
stretch_t p,m;
}glue_t;
	/*:123*/	/*181:*/
	#line 3743 "format.w"

typedef struct{
glue_t bs,ls;
dimen_t lsl;
}baseline_t;
	/*:181*/	/*322:*/
	#line 6762 "format.w"

#define MAX_FONT_PARAMS 11
	/*:322*/
	#line 6974 "format.w"

	/*336:*/
	#line 7076 "format.w"

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
}int_no_t;
#define MAX_INT_DEFAULT hang_after_no
	/*:336*/	/*338:*/
	#line 7147 "format.w"

typedef enum{
zero_dimen_no= 0,
hsize_dimen_no= 1,
vsize_dimen_no= 2,
line_skip_limit_no= 3,
max_depth_no= 4,
hang_indent_no= 5,
emergency_stretch_no= 6,
quad_no= 7,
math_quad_no= 8
}dimen_no_t;
#define MAX_DIMEN_DEFAULT math_quad_no
	/*:338*/	/*340:*/
	#line 7191 "format.w"

typedef enum{
zero_xdimen_no= 0,
hsize_xdimen_no= 1,
vsize_xdimen_no= 2
}xdimen_no_t;
#define MAX_XDIMEN_DEFAULT vsize_xdimen_no
	/*:340*/	/*342:*/
	#line 7215 "format.w"

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
	/*:342*/	/*344:*/
	#line 7301 "format.w"

typedef enum{
zero_baseline_no= 0
}baseline_no_t;
#define MAX_BASELINE_DEFAULT zero_baseline_no
	/*:344*/	/*346:*/
	#line 7320 "format.w"

typedef enum{
zero_page_no= 0
}page_no_t;
#define MAX_PAGE_DEFAULT zero_page_no
	/*:346*/	/*348:*/
	#line 7339 "format.w"

typedef enum{
zero_range_no= 0
}range_no_t;
#define MAX_RANGE_DEFAULT zero_range_no
	/*:348*/
	#line 6975 "format.w"



extern const char*content_name[32];
extern const char*definition_name[32];
extern unsigned int debugflags;
extern FILE*hlog;
extern int max_fixed[32],max_default[32],max_ref[32];
extern int32_t int_defaults[MAX_INT_DEFAULT+1];
extern dimen_t dimen_defaults[MAX_DIMEN_DEFAULT+1];
extern xdimen_t xdimen_defaults[MAX_XDIMEN_DEFAULT+1];
extern glue_t glue_defaults[MAX_GLUE_DEFAULT+1];
extern baseline_t baseline_defaults[MAX_BASELINE_DEFAULT+1];
#endif
	/*:333*/
