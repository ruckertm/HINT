/*385:*/
#line 7691 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H

/*315:*/
#line 5761 "hint.w"

typedef enum{no_format,pk_format,ft_format}FontFormat;
/*:315*//*316:*/
#line 5773 "hint.w"

/*349:*/
#line 6766 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
double ds;
unsigned char id;
}PKfont;
/*:349*//*361:*/
#line 7097 "hint.w"

typedef struct
{FT_Face face;
}FTfont;
/*:361*//*362:*/
#line 7104 "hint.w"

typedef struct
{int dummy;
}FTglyph;
/*:362*/
#line 5774 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int data_size;
double s;
double hpxs,vpxs;
/*322:*/
#line 5868 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:322*/
#line 5782 "hint.w"

FontFormat ff;
union{PKfont pk;FTfont tt;};
}Font;
/*:316*//*327:*/
#line 6080 "hint.w"

/*350:*/
#line 6779 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}PKglyph;
/*:350*//*352:*/
#line 6806 "hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*data;
}PKparse;
/*:352*/
#line 6081 "hint.w"


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
/*:327*/
#line 7695 "hint.w"



#endif
/*:385*/
