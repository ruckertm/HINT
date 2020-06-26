/*323:*/
#line 6144 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H
/*261:*/
#line 4482 "hint.w"

typedef enum{no_format,pk_format,t1_format,ot_format,tt_format}font_format_t;
/*:261*//*262:*/
#line 4493 "hint.w"

/*294:*/
#line 5440 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
unsigned char id;
}pk_t;
/*:294*//*298:*/
#line 5609 "hint.w"

typedef stbtt_fontinfo tt_t;
typedef struct
{int dummy;
}ttg_t;
/*:298*//*302:*/
#line 5662 "hint.w"

typedef struct
{int dummy;
}t1_t;
/*:302*//*304:*/
#line 5675 "hint.w"

typedef struct
{int dummy;
}ot_t;
/*:304*/
#line 4494 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int size;
double ds;
double hppp,vppp;
/*267:*/
#line 4587 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:267*/
#line 4502 "hint.w"

font_format_t ff;
union{
pk_t pk;
tt_t tt;
t1_t t1;
ot_t ot;
};
}font_t;
/*:262*//*268:*/
#line 4599 "hint.w"

typedef struct gcache_s gcache_t;
/*:268*//*273:*/
#line 4792 "hint.w"

/*295:*/
#line 5452 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}pkg_t;
/*:295*//*303:*/
#line 5667 "hint.w"

typedef struct
{int dummy;
}t1g_t;
/*:303*//*305:*/
#line 5680 "hint.w"

typedef struct
{int dummy;
}otg_t;
/*:305*/
#line 4793 "hint.w"


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
/*:273*/
#line 6147 "hint.w"



#endif
/*:323*/
