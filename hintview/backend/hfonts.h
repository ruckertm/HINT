/*397:*/
#line 7839 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H

/*326:*/
#line 5892 "hint.w"

typedef enum{no_format,pk_format,ft_format}FontFormat;
/*:326*//*327:*/
#line 5904 "hint.w"

/*361:*/
#line 6913 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
double ds;
unsigned char id;
}PKfont;
/*:361*//*373:*/
#line 7244 "hint.w"

typedef struct
{FT_Face face;
}FTfont;
/*:373*//*374:*/
#line 7251 "hint.w"

typedef struct
{int dummy;
}FTglyph;
/*:374*/
#line 5905 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int data_size;
double s;
double hpxs,vpxs;
/*333:*/
#line 5999 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:333*/
#line 5913 "hint.w"

FontFormat ff;
union{PKfont pk;FTfont tt;};
}Font;
/*:327*//*338:*/
#line 6211 "hint.w"

/*362:*/
#line 6926 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}PKglyph;
/*:362*//*364:*/
#line 6953 "hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*data;
}PKparse;
/*:364*/
#line 6212 "hint.w"


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
#line 7843 "hint.w"



#endif
/*:397*/
