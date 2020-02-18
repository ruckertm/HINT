/*304:*/
#line 5719 ".\\hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H
/*245:*/
#line 4251 ".\\hint.w"

typedef enum{no_format,pk_format,t1_format,ot_format,tt_format}font_format_t;
/*:245*//*246:*/
#line 4262 ".\\hint.w"

/*278:*/
#line 5152 ".\\hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
unsigned char id;
}pk_t;
/*:278*//*282:*/
#line 5321 ".\\hint.w"

typedef stbtt_fontinfo tt_t;
typedef struct
{int dummy;
}ttg_t;
/*:282*//*286:*/
#line 5374 ".\\hint.w"

typedef struct
{int dummy;
}t1_t;
/*:286*//*288:*/
#line 5387 ".\\hint.w"

typedef struct
{int dummy;
}ot_t;
/*:288*/
#line 4263 ".\\hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int size;
double ds;
double hppp,vppp;
/*251:*/
#line 4348 ".\\hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:251*/
#line 4271 ".\\hint.w"

font_format_t ff;
union{
pk_t pk;
tt_t tt;
t1_t t1;
ot_t ot;
};
}font_t;
/*:246*//*252:*/
#line 4360 ".\\hint.w"

typedef struct gcache_s gcache_t;
/*:252*//*257:*/
#line 4553 ".\\hint.w"

/*279:*/
#line 5164 ".\\hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}pkg_t;
/*:279*//*287:*/
#line 5379 ".\\hint.w"

typedef struct
{int dummy;
}t1g_t;
/*:287*//*289:*/
#line 5392 ".\\hint.w"

typedef struct
{int dummy;
}otg_t;
/*:289*/
#line 4554 ".\\hint.w"


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
/*:257*/
#line 5722 ".\\hint.w"



#endif
/*:304*/
