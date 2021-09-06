/*370:*/
#line 7389 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H

/*301:*/
#line 5491 "hint.w"

typedef enum{no_format,pk_format,ft_format}font_format_t;
/*:301*//*302:*/
#line 5503 "hint.w"

/*334:*/
#line 6478 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
double ds;
unsigned char id;
}pk_t;
/*:334*//*346:*/
#line 6809 "hint.w"

typedef struct
{FT_Face face;
}ft_t;
/*:346*//*347:*/
#line 6816 "hint.w"

typedef struct
{int dummy;
}ftg_t;
/*:347*/
#line 5504 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int data_size;
double s;
double hpxs,vpxs;
/*307:*/
#line 5591 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:307*/
#line 5512 "hint.w"

font_format_t ff;
union{pk_t pk;ft_t tt;};
}font_t;
/*:302*//*308:*/
#line 5603 "hint.w"

typedef struct gcache_s gcache_t;
/*:308*//*313:*/
#line 5807 "hint.w"

/*335:*/
#line 6491 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}pkg_t;
/*:335*//*337:*/
#line 6518 "hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*data;
}pk_parse_t;
/*:337*/
#line 5808 "hint.w"


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
/*:313*/
#line 7393 "hint.w"



#endif
/*:370*/
