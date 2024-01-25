/*402:*/
#line 8310 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H

/*327:*/
#line 6149 "hint.w"

typedef enum{no_format,pk_format,ft_format}FontFormat;
/*:327*//*328:*/
#line 6161 "hint.w"

/*366:*/
#line 7382 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
double ds;
unsigned char id;
}PKfont;
/*:366*//*378:*/
#line 7713 "hint.w"

typedef struct
{FT_Face face;
}FTfont;
/*:378*//*379:*/
#line 7720 "hint.w"

typedef struct
{int dummy;
}FTglyph;
/*:379*/
#line 6162 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int data_size;
double s;
double hpxs,vpxs;
/*333:*/
#line 6251 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:333*/
#line 6170 "hint.w"

FontFormat ff;
union{PKfont pk;FTfont tt;};
}Font;
/*:328*//*338:*/
#line 6463 "hint.w"

/*367:*/
#line 7395 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}PKglyph;
/*:367*//*369:*/
#line 7422 "hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*pk_data;
}PKparse;
/*:369*/
#line 6464 "hint.w"


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
/*:338*/
#line 8314 "hint.w"



#endif
#line 8318 "hint.w"
/*:402*/
