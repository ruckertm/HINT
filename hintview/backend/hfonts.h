/*403:*/
#line 8319 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H

/*327:*/
#line 6149 "hint.w"

typedef enum{no_format,pk_format,ft_format}FontFormat;
/*:327*//*328:*/
#line 6161 "hint.w"

/*367:*/
#line 7393 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
double ds;
unsigned char id;
}PKfont;
/*:367*//*379:*/
#line 7724 "hint.w"

typedef struct
{FT_Face face;
}FTfont;
/*:379*//*380:*/
#line 7731 "hint.w"

typedef struct
{int dummy;
}FTglyph;
/*:380*/
#line 6162 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int data_size;
double s;
double hpxs,vpxs;
/*334:*/
#line 6256 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:334*/
#line 6170 "hint.w"

FontFormat ff;
union{PKfont pk;FTfont tt;};
}Font;
/*:328*//*339:*/
#line 6468 "hint.w"

/*368:*/
#line 7406 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}PKglyph;
/*:368*//*370:*/
#line 7433 "hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*data;
}PKparse;
/*:370*/
#line 6469 "hint.w"


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
#line 8323 "hint.w"



#endif
/*:403*/
