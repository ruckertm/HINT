/*302:*/
#line 5690 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H
/*243:*/
#line 4218 "hint.w"

typedef enum{no_format,pk_format,t1_format,ot_format,tt_format}font_format_t;
/*:243*//*244:*/
#line 4229 "hint.w"

/*276:*/
#line 5118 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
unsigned char id;
}pk_t;
/*:276*//*280:*/
#line 5287 "hint.w"

typedef stbtt_fontinfo tt_t;
typedef struct
{int dummy;
}ttg_t;
/*:280*//*284:*/
#line 5340 "hint.w"

typedef struct
{int dummy;
}t1_t;
/*:284*//*286:*/
#line 5353 "hint.w"

typedef struct
{int dummy;
}ot_t;
/*:286*/
#line 4230 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int size;
double ds;
double hppp,vppp;
/*249:*/
#line 4315 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:249*/
#line 4238 "hint.w"

font_format_t ff;
union{
pk_t pk;
tt_t tt;
t1_t t1;
ot_t ot;
};
}font_t;
/*:244*//*250:*/
#line 4327 "hint.w"

typedef struct gcache_s gcache_t;
/*:250*//*255:*/
#line 4520 "hint.w"

/*277:*/
#line 5130 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}pkg_t;
/*:277*//*285:*/
#line 5345 "hint.w"

typedef struct
{int dummy;
}t1g_t;
/*:285*//*287:*/
#line 5358 "hint.w"

typedef struct
{int dummy;
}otg_t;
/*:287*/
#line 4521 "hint.w"


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
#line 5693 "hint.w"



#endif
/*:302*/
