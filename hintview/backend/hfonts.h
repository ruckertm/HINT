/*391:*/
#line 7750 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H

/*321:*/
#line 5820 "hint.w"

typedef enum{no_format,pk_format,ft_format}FontFormat;
/*:321*//*322:*/
#line 5832 "hint.w"

/*355:*/
#line 6825 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
double ds;
unsigned char id;
}PKfont;
/*:355*//*367:*/
#line 7156 "hint.w"

typedef struct
{FT_Face face;
}FTfont;
/*:367*//*368:*/
#line 7163 "hint.w"

typedef struct
{int dummy;
}FTglyph;
/*:368*/
#line 5833 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int data_size;
double s;
double hpxs,vpxs;
/*328:*/
#line 5927 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:328*/
#line 5841 "hint.w"

FontFormat ff;
union{PKfont pk;FTfont tt;};
}Font;
/*:322*//*333:*/
#line 6139 "hint.w"

/*356:*/
#line 6838 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}PKglyph;
/*:356*//*358:*/
#line 6865 "hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*data;
}PKparse;
/*:358*/
#line 6140 "hint.w"


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
/*:333*/
#line 7754 "hint.w"



#endif
/*:391*/
