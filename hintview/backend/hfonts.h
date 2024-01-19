/*405:*/
#line 8296 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H

/*330:*/
#line 6138 "hint.w"

typedef enum{no_format,pk_format,ft_format}FontFormat;
/*:330*//*331:*/
#line 6150 "hint.w"

/*369:*/
#line 7371 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
double ds;
unsigned char id;
}PKfont;
/*:369*//*381:*/
#line 7702 "hint.w"

typedef struct
{FT_Face face;
}FTfont;
/*:381*//*382:*/
#line 7709 "hint.w"

typedef struct
{int dummy;
}FTglyph;
/*:382*/
#line 6151 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int data_size;
double s;
double hpxs,vpxs;
/*337:*/
#line 6245 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:337*/
#line 6159 "hint.w"

FontFormat ff;
union{PKfont pk;FTfont tt;};
}Font;
/*:331*//*342:*/
#line 6457 "hint.w"

/*370:*/
#line 7384 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}PKglyph;
/*:370*//*372:*/
#line 7411 "hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*data;
}PKparse;
/*:372*/
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
/*:342*/
#line 8300 "hint.w"



#endif
/*:405*/
