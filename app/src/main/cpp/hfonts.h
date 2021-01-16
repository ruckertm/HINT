/*331:*/
#line 6411 ".\\hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H
/*262:*/
#line 4538 ".\\hint.w"

typedef enum{no_format,pk_format,ft_format}font_format_t;
/*:262*//*263:*/
#line 4550 ".\\hint.w"

/*295:*/
#line 5504 ".\\hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
double ds;
unsigned char id;
}pk_t;
/*:295*//*307:*/
#line 5835 ".\\hint.w"

typedef struct
{FT_Face face;
}ft_t;
/*:307*//*308:*/
#line 5842 ".\\hint.w"

typedef struct
{int dummy;
}ftg_t;
/*:308*/
#line 4551 ".\\hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int data_size;
double s;
double hpxs,vpxs;
/*268:*/
#line 4639 ".\\hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:268*/
#line 4559 ".\\hint.w"

font_format_t ff;
union{pk_t pk;ft_t tt;};
}font_t;
/*:263*//*269:*/
#line 4651 ".\\hint.w"

typedef struct gcache_s gcache_t;
/*:269*//*274:*/
#line 4855 ".\\hint.w"

/*296:*/
#line 5517 ".\\hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}pkg_t;
/*:296*//*298:*/
#line 5544 ".\\hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*data;
}pk_parse_t;
/*:298*/
#line 4856 ".\\hint.w"


struct gcache_s{
int w,h;
int hoff,voff;
bool searched;
unsigned char*bits;
#ifdef WIN32
HBITMAP hbmp;
#endif
#ifdef __ANDROID__
unsigned int GLtexture;
#endif
font_format_t ff;
union{
pkg_t pk;
ftg_t tt;
};
};
/*:274*/
#line 6414 ".\\hint.w"



#endif
/*:331*/
