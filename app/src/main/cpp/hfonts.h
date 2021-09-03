/*370:*/
#line 7364 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H

/*301:*/
#line 5466 "hint.w"

typedef enum{no_format,pk_format,ft_format}font_format_t;
/*:301*//*302:*/
#line 5478 "hint.w"

/*334:*/
#line 6453 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
double ds;
unsigned char id;
}pk_t;
/*:334*//*346:*/
#line 6784 "hint.w"

typedef struct
{FT_Face face;
}ft_t;
/*:346*//*347:*/
#line 6791 "hint.w"

typedef struct
{int dummy;
}ftg_t;
/*:347*/
#line 5479 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int data_size;
double s;
double hpxs,vpxs;
/*307:*/
#line 5566 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:307*/
#line 5487 "hint.w"

font_format_t ff;
union{pk_t pk;ft_t tt;};
}font_t;
/*:302*//*308:*/
#line 5578 "hint.w"

typedef struct gcache_s gcache_t;
/*:308*//*313:*/
#line 5782 "hint.w"

/*335:*/
#line 6466 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}pkg_t;
/*:335*//*337:*/
#line 6493 "hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*data;
}pk_parse_t;
/*:337*/
#line 5783 "hint.w"


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
#line 7368 "hint.w"



#endif
/*:370*/
