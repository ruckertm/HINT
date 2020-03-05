/*295:*/
#line 5559 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H
/*233:*/
#line 3955 "hint.w"

typedef enum{no_format,pk_format,t1_format,ot_format,tt_format}font_format_t;
/*:233*//*234:*/
#line 3966 "hint.w"

/*266:*/
#line 4861 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
unsigned char id;
}pk_t;
/*:266*//*270:*/
#line 5030 "hint.w"

typedef stbtt_fontinfo tt_t;
typedef struct
{int dummy;
}ttg_t;
/*:270*//*274:*/
#line 5083 "hint.w"

typedef struct
{int dummy;
}t1_t;
/*:274*//*276:*/
#line 5096 "hint.w"

typedef struct
{int dummy;
}ot_t;
/*:276*/
#line 3967 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int size;
double ds;
double hppp,vppp;
/*239:*/
#line 4057 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:239*/
#line 3975 "hint.w"

font_format_t ff;
union{
pk_t pk;
tt_t tt;
t1_t t1;
ot_t ot;
};
}font_t;
/*:234*//*240:*/
#line 4069 "hint.w"

typedef struct gcache_s gcache_t;
/*:240*//*245:*/
#line 4262 "hint.w"

/*267:*/
#line 4873 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}pkg_t;
/*:267*//*275:*/
#line 5088 "hint.w"

typedef struct
{int dummy;
}t1g_t;
/*:275*//*277:*/
#line 5101 "hint.w"

typedef struct
{int dummy;
}otg_t;
/*:277*/
#line 4263 "hint.w"


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
/*:245*/
#line 5562 "hint.w"



#endif
/*:295*/
