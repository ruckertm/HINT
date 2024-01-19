/*404:*/
#line 8265 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H

/*330:*/
#line 6138 "hint.w"

typedef enum{no_format,pk_format,ft_format}FontFormat;
/*:330*//*331:*/
#line 6150 "hint.w"

/*368:*/
#line 7340 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
double ds;
unsigned char id;
}PKfont;
/*:368*//*380:*/
#line 7671 "hint.w"

typedef struct
{FT_Face face;
}FTfont;
/*:380*//*381:*/
#line 7678 "hint.w"

typedef struct
{int dummy;
}FTglyph;
/*:381*/
#line 6151 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int data_size;
double s;
double hpxs,vpxs;
/*337:*/
#line 6245 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:337*/
#line 6159 "hint.w"

FontFormat ff;
union{PKfont pk;FTfont tt;};
}Font;
/*:331*//*342:*/
#line 6457 "hint.w"

/*369:*/
#line 7353 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}PKglyph;
/*:369*//*371:*/
#line 7380 "hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*data;
}PKparse;
/*:371*/
#line 6458 "hint.w"


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
/*:342*/
#line 8269 "hint.w"



#endif
/*:404*/
