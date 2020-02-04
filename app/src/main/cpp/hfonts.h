/*302:*/
#line 5781 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H
/*243:*/
#line 4307 "hint.w"

typedef enum{no_format,pk_format,t1_format,ot_format,tt_format}font_format_t;
/*:243*//*244:*/
#line 4318 "hint.w"

/*276:*/
#line 5208 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
unsigned char id;
}pk_t;
/*:276*//*280:*/
#line 5377 "hint.w"

typedef stbtt_fontinfo tt_t;
typedef struct
{int dummy;
}ttg_t;
/*:280*//*284:*/
#line 5430 "hint.w"

typedef struct
{int dummy;
}t1_t;
/*:284*//*286:*/
#line 5443 "hint.w"

typedef struct
{int dummy;
}ot_t;
/*:286*/
#line 4319 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int size;
double ds;
double hppp,vppp;
/*249:*/
#line 4404 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:249*/
#line 4327 "hint.w"

font_format_t ff;
union{
pk_t pk;
tt_t tt;
t1_t t1;
ot_t ot;
};
}font_t;
/*:244*//*250:*/
#line 4416 "hint.w"

typedef struct gcache_s gcache_t;
/*:250*//*255:*/
#line 4609 "hint.w"

/*277:*/
#line 5220 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}pkg_t;
/*:277*//*285:*/
#line 5435 "hint.w"

typedef struct
{int dummy;
}t1g_t;
/*:285*//*287:*/
#line 5448 "hint.w"

typedef struct
{int dummy;
}otg_t;
/*:287*/
#line 4610 "hint.w"


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
/*:255*/
#line 5784 "hint.w"



#endif
/*:302*/
