/*327:*/
#line 6214 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H
/*265:*/
#line 4549 "hint.w"

typedef enum{no_format,pk_format,t1_format,ot_format,tt_format}font_format_t;
/*:265*//*266:*/
#line 4560 "hint.w"

/*298:*/
#line 5507 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
unsigned char id;
}pk_t;
/*:298*//*302:*/
#line 5676 "hint.w"

typedef stbtt_fontinfo tt_t;
typedef struct
{int dummy;
}ttg_t;
/*:302*//*306:*/
#line 5729 "hint.w"

typedef struct
{int dummy;
}t1_t;
/*:306*//*308:*/
#line 5742 "hint.w"

typedef struct
{int dummy;
}ot_t;
/*:308*/
#line 4561 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int size;
double ds;
double hppp,vppp;
/*271:*/
#line 4654 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:271*/
#line 4569 "hint.w"

font_format_t ff;
union{
pk_t pk;
tt_t tt;
t1_t t1;
ot_t ot;
};
}font_t;
/*:266*//*272:*/
#line 4666 "hint.w"

typedef struct gcache_s gcache_t;
/*:272*//*277:*/
#line 4859 "hint.w"

/*299:*/
#line 5519 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}pkg_t;
/*:299*//*307:*/
#line 5734 "hint.w"

typedef struct
{int dummy;
}t1g_t;
/*:307*//*309:*/
#line 5747 "hint.w"

typedef struct
{int dummy;
}otg_t;
/*:309*/
#line 4860 "hint.w"


struct gcache_s{
int w,h;
int hoff,voff;
unsigned char*bits;
#ifdef __ANDROID__
unsigned int GLtexture;
#endif
font_format_t ff;
union{
pkg_t pk;
ttg_t tt;
t1g_t t1;
otg_t ot;
};
};
/*:277*/
#line 6217 "hint.w"



#endif
/*:327*/
