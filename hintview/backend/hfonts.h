/*394:*/
#line 7798 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H

/*324:*/
#line 5857 "hint.w"

typedef enum{no_format,pk_format,ft_format}FontFormat;
/*:324*//*325:*/
#line 5869 "hint.w"

/*358:*/
#line 6873 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
double ds;
unsigned char id;
}PKfont;
/*:358*//*370:*/
#line 7204 "hint.w"

typedef struct
{FT_Face face;
}FTfont;
/*:370*//*371:*/
#line 7211 "hint.w"

typedef struct
{int dummy;
}FTglyph;
/*:371*/
#line 5870 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int data_size;
double s;
double hpxs,vpxs;
/*331:*/
#line 5964 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:331*/
#line 5878 "hint.w"

FontFormat ff;
union{PKfont pk;FTfont tt;};
}Font;
/*:325*//*336:*/
#line 6176 "hint.w"

/*359:*/
#line 6886 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}PKglyph;
/*:359*//*361:*/
#line 6913 "hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*data;
}PKparse;
/*:361*/
#line 6177 "hint.w"


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
/*:336*/
#line 7802 "hint.w"



#endif
/*:394*/
