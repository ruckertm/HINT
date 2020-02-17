/*303:*/
#line 5679 ".\\hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H
/*244:*/
#line 4206 ".\\hint.w"

typedef enum{no_format,pk_format,t1_format,ot_format,tt_format}font_format_t;
/*:244*//*245:*/
#line 4217 ".\\hint.w"

/*277:*/
#line 5107 ".\\hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
unsigned char id;
}pk_t;
/*:277*//*281:*/
#line 5276 ".\\hint.w"

typedef stbtt_fontinfo tt_t;
typedef struct
{int dummy;
}ttg_t;
/*:281*//*285:*/
#line 5329 ".\\hint.w"

typedef struct
{int dummy;
}t1_t;
/*:285*//*287:*/
#line 5342 ".\\hint.w"

typedef struct
{int dummy;
}ot_t;
/*:287*/
#line 4218 ".\\hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int size;
double ds;
double hppp,vppp;
/*250:*/
#line 4303 ".\\hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:250*/
#line 4226 ".\\hint.w"

font_format_t ff;
union{
pk_t pk;
tt_t tt;
t1_t t1;
ot_t ot;
};
}font_t;
/*:245*//*251:*/
#line 4315 ".\\hint.w"

typedef struct gcache_s gcache_t;
/*:251*//*256:*/
#line 4508 ".\\hint.w"

/*278:*/
#line 5119 ".\\hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}pkg_t;
/*:278*//*286:*/
#line 5334 ".\\hint.w"

typedef struct
{int dummy;
}t1g_t;
/*:286*//*288:*/
#line 5347 ".\\hint.w"

typedef struct
{int dummy;
}otg_t;
/*:288*/
#line 4509 ".\\hint.w"


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
/*:256*/
#line 5682 ".\\hint.w"



#endif
/*:303*/
