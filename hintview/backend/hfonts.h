/*404:*/
#line 8284 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H

/*329:*/
#line 6132 "hint.w"

typedef enum{no_format,pk_format,ft_format}FontFormat;
/*:329*//*330:*/
#line 6144 "hint.w"

/*368:*/
#line 7359 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
double ds;
unsigned char id;
}PKfont;
/*:368*//*380:*/
#line 7690 "hint.w"

typedef struct
{FT_Face face;
}FTfont;
/*:380*//*381:*/
#line 7697 "hint.w"

typedef struct
{int dummy;
}FTglyph;
/*:381*/
#line 6145 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int data_size;
double s;
double hpxs,vpxs;
/*336:*/
#line 6239 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:336*/
#line 6153 "hint.w"

FontFormat ff;
union{PKfont pk;FTfont tt;};
}Font;
/*:330*//*341:*/
#line 6451 "hint.w"

/*369:*/
#line 7372 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}PKglyph;
/*:369*//*371:*/
#line 7399 "hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*data;
}PKparse;
/*:371*/
#line 6452 "hint.w"


struct gcache_s{
int w,h;
int hoff,voff;
unsigned char*bits;
unsigned int GLtexture;
FontFormat ff;
union{
PKglyph pk;
FTglyph tt;
};
};
typedef struct gcache_s Gcache;
/*:341*/
#line 8288 "hint.w"



#endif
/*:404*/
