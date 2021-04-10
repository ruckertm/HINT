/*345:*/
#line 6737 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H

/*276:*/
#line 4851 "hint.w"

typedef enum{no_format,pk_format,ft_format}font_format_t;
/*:276*//*277:*/
#line 4863 "hint.w"

/*309:*/
#line 5827 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
double ds;
unsigned char id;
}pk_t;
/*:309*//*321:*/
#line 6158 "hint.w"

typedef struct
{FT_Face face;
}ft_t;
/*:321*//*322:*/
#line 6165 "hint.w"

typedef struct
{int dummy;
}ftg_t;
/*:322*/
#line 4864 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int data_size;
double s;
double hpxs,vpxs;
/*282:*/
#line 4952 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:282*/
#line 4872 "hint.w"

font_format_t ff;
union{pk_t pk;ft_t tt;};
}font_t;
/*:277*//*283:*/
#line 4964 "hint.w"

typedef struct gcache_s gcache_t;
/*:283*//*288:*/
#line 5168 "hint.w"

/*310:*/
#line 5840 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}pkg_t;
/*:310*//*312:*/
#line 5867 "hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*data;
}pk_parse_t;
/*:312*/
#line 5169 "hint.w"


struct gcache_s{
int w,h;
int hoff,voff;
unsigned char*bits;
unsigned int GLtexture;
font_format_t ff;
union{
pkg_t pk;
ftg_t tt;
};
};
/*:288*/
#line 6741 "hint.w"



#endif
/*:345*/
