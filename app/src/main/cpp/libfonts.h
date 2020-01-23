/*315:*/
#line 5749 ".\\hint.w"

#ifndef _LIBFONTS_H
#define _LIBFONTS_H
/*260:*/
#line 4340 ".\\hint.w"

typedef enum{no_format,pk_format,t1_format,ot_format,tt_format}font_format_t;
/*:260*//*261:*/
#line 4348 ".\\hint.w"

/*291:*/
#line 5205 ".\\hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
unsigned char id;
#if 0
unsigned char flag;
#endif
}pk_t;
/*:291*//*295:*/
#line 5389 ".\\hint.w"

typedef struct
{int dummy;
}t1_t;
/*:295*//*297:*/
#line 5402 ".\\hint.w"

typedef struct
{int dummy;
}ot_t;
/*:297*//*299:*/
#line 5414 ".\\hint.w"

typedef struct
{int dummy;
}tt_t;
/*:299*/
#line 4349 ".\\hint.w"


typedef struct{
unsigned char*font_data;
int size;
double ds;
double hppp,vppp;
/*265:*/
#line 4422 ".\\hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:265*/
#line 4356 ".\\hint.w"

font_format_t ff;
union{
pk_t pk;
tt_t tt;
t1_t t1;
ot_t ot;
};
}font_t;
/*:261*//*266:*/
#line 4434 ".\\hint.w"

typedef struct gcache_s gcache_t;
/*:266*//*271:*/
#line 4630 ".\\hint.w"

/*292:*/
#line 5220 ".\\hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}pkg_t;
/*:292*//*296:*/
#line 5394 ".\\hint.w"

typedef struct
{int dummy;
}t1g_t;
/*:296*//*298:*/
#line 5407 ".\\hint.w"

typedef struct
{int dummy;
}otg_t;
/*:298*//*300:*/
#line 5419 ".\\hint.w"

typedef struct
{int dummy;
}ttg_t;
/*:300*/
#line 4631 ".\\hint.w"


struct gcache_s{
unsigned int w,h;
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
/*:271*/
#line 5752 ".\\hint.w"


extern void render_char(int x,int y,font_t*f,int32_t s,uint32_t cc);
extern font_t*hget_font(unsigned char f);
extern void hclear_fonts(void);
#endif
/*:315*/
