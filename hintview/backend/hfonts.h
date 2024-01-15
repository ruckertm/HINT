/*400:*/
#line 7934 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H

/*329:*/
#line 5971 "hint.w"

typedef enum{no_format,pk_format,ft_format}FontFormat;
/*:329*//*330:*/
#line 5983 "hint.w"

/*364:*/
#line 7009 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
double ds;
unsigned char id;
}PKfont;
/*:364*//*376:*/
#line 7340 "hint.w"

typedef struct
{FT_Face face;
}FTfont;
/*:376*//*377:*/
#line 7347 "hint.w"

typedef struct
{int dummy;
}FTglyph;
/*:377*/
#line 5984 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int data_size;
double s;
double hpxs,vpxs;
/*336:*/
#line 6078 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:336*/
#line 5992 "hint.w"

FontFormat ff;
union{PKfont pk;FTfont tt;};
}Font;
/*:330*//*341:*/
#line 6290 "hint.w"

/*365:*/
#line 7022 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}PKglyph;
/*:365*//*367:*/
#line 7049 "hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*data;
}PKparse;
/*:367*/
#line 6291 "hint.w"


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
/*:341*/
#line 7938 "hint.w"



#endif
/*:400*/
