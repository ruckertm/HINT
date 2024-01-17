/*402:*/
#line 8171 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H

/*329:*/
#line 6110 "hint.w"

typedef enum{no_format,pk_format,ft_format}FontFormat;
/*:329*//*330:*/
#line 6122 "hint.w"

/*366:*/
#line 7246 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
double ds;
unsigned char id;
}PKfont;
/*:366*//*378:*/
#line 7577 "hint.w"

typedef struct
{FT_Face face;
}FTfont;
/*:378*//*379:*/
#line 7584 "hint.w"

typedef struct
{int dummy;
}FTglyph;
/*:379*/
#line 6123 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int data_size;
double s;
double hpxs,vpxs;
/*336:*/
#line 6217 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:336*/
#line 6131 "hint.w"

FontFormat ff;
union{PKfont pk;FTfont tt;};
}Font;
/*:330*//*341:*/
#line 6429 "hint.w"

/*367:*/
#line 7259 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}PKglyph;
/*:367*//*369:*/
#line 7286 "hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*data;
}PKparse;
/*:369*/
#line 6430 "hint.w"


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
#line 8175 "hint.w"



#endif
/*:402*/
