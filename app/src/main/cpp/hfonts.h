/*302:*/
#line 5693 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H
/*243:*/
#line 4221 "hint.w"

typedef enum{no_format,pk_format,t1_format,ot_format,tt_format}font_format_t;
/*:243*//*244:*/
#line 4232 "hint.w"

/*276:*/
#line 5121 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
unsigned char id;
}pk_t;
/*:276*//*280:*/
#line 5290 "hint.w"

typedef stbtt_fontinfo tt_t;
typedef struct
{int dummy;
}ttg_t;
/*:280*//*284:*/
#line 5343 "hint.w"

typedef struct
{int dummy;
}t1_t;
/*:284*//*286:*/
#line 5356 "hint.w"

typedef struct
{int dummy;
}ot_t;
/*:286*/
#line 4233 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int size;
double ds;
double hppp,vppp;
/*249:*/
#line 4318 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:249*/
#line 4241 "hint.w"

font_format_t ff;
union{
pk_t pk;
tt_t tt;
t1_t t1;
ot_t ot;
};
}font_t;
/*:244*//*250:*/
#line 4330 "hint.w"

typedef struct gcache_s gcache_t;
/*:250*//*255:*/
#line 4523 "hint.w"

/*277:*/
#line 5133 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}pkg_t;
/*:277*//*285:*/
#line 5348 "hint.w"

typedef struct
{int dummy;
}t1g_t;
/*:285*//*287:*/
#line 5361 "hint.w"

typedef struct
{int dummy;
}otg_t;
/*:287*/
#line 4524 "hint.w"


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
#line 5696 "hint.w"



#endif
/*:302*/
