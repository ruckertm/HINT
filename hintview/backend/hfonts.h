/*403:*/
#line 8317 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H

/*327:*/
#line 6147 "hint.w"

typedef enum{no_format,pk_format,ft_format}FontFormat;
/*:327*//*328:*/
#line 6159 "hint.w"

/*367:*/
#line 7391 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
double ds;
unsigned char id;
}PKfont;
/*:367*//*379:*/
#line 7722 "hint.w"

typedef struct
{FT_Face face;
}FTfont;
/*:379*//*380:*/
#line 7729 "hint.w"

typedef struct
{int dummy;
}FTglyph;
/*:380*/
#line 6160 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int data_size;
double s;
double hpxs,vpxs;
/*334:*/
#line 6254 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:334*/
#line 6168 "hint.w"

FontFormat ff;
union{PKfont pk;FTfont tt;};
}Font;
/*:328*//*339:*/
#line 6466 "hint.w"

/*368:*/
#line 7404 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}PKglyph;
/*:368*//*370:*/
#line 7431 "hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*data;
}PKparse;
/*:370*/
#line 6467 "hint.w"


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
/*:339*/
#line 8321 "hint.w"



#endif
/*:403*/
