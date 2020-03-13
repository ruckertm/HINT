/*298:*/
#line 5641 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H
/*236:*/
#line 4037 "hint.w"

typedef enum{no_format,pk_format,t1_format,ot_format,tt_format}font_format_t;
/*:236*//*237:*/
#line 4048 "hint.w"

/*269:*/
#line 4943 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
unsigned char id;
}pk_t;
/*:269*//*273:*/
#line 5112 "hint.w"

typedef stbtt_fontinfo tt_t;
typedef struct
{int dummy;
}ttg_t;
/*:273*//*277:*/
#line 5165 "hint.w"

typedef struct
{int dummy;
}t1_t;
/*:277*//*279:*/
#line 5178 "hint.w"

typedef struct
{int dummy;
}ot_t;
/*:279*/
#line 4049 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int size;
double ds;
double hppp,vppp;
/*242:*/
#line 4139 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:242*/
#line 4057 "hint.w"

font_format_t ff;
union{
pk_t pk;
tt_t tt;
t1_t t1;
ot_t ot;
};
}font_t;
/*:237*//*243:*/
#line 4151 "hint.w"

typedef struct gcache_s gcache_t;
/*:243*//*248:*/
#line 4344 "hint.w"

/*270:*/
#line 4955 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}pkg_t;
/*:270*//*278:*/
#line 5170 "hint.w"

typedef struct
{int dummy;
}t1g_t;
/*:278*//*280:*/
#line 5183 "hint.w"

typedef struct
{int dummy;
}otg_t;
/*:280*/
#line 4345 "hint.w"


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
/*:248*/
#line 5644 "hint.w"



#endif
/*:298*/
