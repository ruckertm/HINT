/*374:*/
#line 7592 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H

/*306:*/
#line 5694 "hint.w"

typedef enum{no_format,pk_format,ft_format}FontFormat;
/*:306*//*307:*/
#line 5706 "hint.w"

/*338:*/
#line 6679 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
double ds;
unsigned char id;
}PKfont;
/*:338*//*350:*/
#line 7010 "hint.w"

typedef struct
{FT_Face face;
}FTfont;
/*:350*//*351:*/
#line 7017 "hint.w"

typedef struct
{int dummy;
}FTglyph;
/*:351*/
#line 5707 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int data_size;
double s;
double hpxs,vpxs;
/*312:*/
#line 5794 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:312*/
#line 5715 "hint.w"

FontFormat ff;
union{PKfont pk;FTfont tt;};
}Font;
/*:307*//*317:*/
#line 6006 "hint.w"

/*339:*/
#line 6692 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}PKglyph;
/*:339*//*341:*/
#line 6719 "hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*data;
}PKparse;
/*:341*/
#line 6007 "hint.w"


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
/*:317*/
#line 7596 "hint.w"



#endif
/*:374*/
