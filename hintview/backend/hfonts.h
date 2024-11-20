/*402:*/
#line 8332 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H

/*327:*/
#line 6143 "hint.w"

typedef enum{no_format,pk_format,ft_format}FontFormat;
/*:327*//*328:*/
#line 6155 "hint.w"

/*366:*/
#line 7394 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
double ds;
unsigned char id;
}PKfont;
/*:366*//*378:*/
#line 7725 "hint.w"

typedef struct
{FT_Face face;
}FTfont;
/*:378*//*379:*/
#line 7732 "hint.w"

typedef struct
{int dummy;
}FTglyph;
/*:379*/
#line 6156 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int data_size;
double s;
double hpxs,vpxs;
/*333:*/
#line 6245 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:333*/
#line 6164 "hint.w"

FontFormat ff;
union{PKfont pk;FTfont tt;};
}Font;
/*:328*//*338:*/
#line 6457 "hint.w"

/*367:*/
#line 7407 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}PKglyph;
/*:367*//*369:*/
#line 7434 "hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*pk_data;
}PKparse;
/*:369*/
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
/*:338*/
#line 8336 "hint.w"



#endif
/*:402*/
