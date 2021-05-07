/*348:*/
#line 6915 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H

/*278:*/
#line 5021 "hint.w"

typedef enum{no_format,pk_format,ft_format}font_format_t;
/*:278*//*279:*/
#line 5033 "hint.w"

/*312:*/
#line 6003 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
double ds;
unsigned char id;
}pk_t;
/*:312*//*324:*/
#line 6334 "hint.w"

typedef struct
{FT_Face face;
}ft_t;
/*:324*//*325:*/
#line 6341 "hint.w"

typedef struct
{int dummy;
}ftg_t;
/*:325*/
#line 5034 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int data_size;
double s;
double hpxs,vpxs;
/*284:*/
#line 5122 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:284*/
#line 5042 "hint.w"

font_format_t ff;
union{pk_t pk;ft_t tt;};
}font_t;
/*:279*//*285:*/
#line 5134 "hint.w"

typedef struct gcache_s gcache_t;
/*:285*//*290:*/
#line 5338 "hint.w"

/*313:*/
#line 6016 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}pkg_t;
/*:313*//*315:*/
#line 6043 "hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*data;
}pk_parse_t;
/*:315*/
#line 5339 "hint.w"


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
/*:290*/
#line 6919 "hint.w"



#endif
/*:348*/
