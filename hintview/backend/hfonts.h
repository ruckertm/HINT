/*399:*/
#line 7886 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H

/*328:*/
#line 5922 "hint.w"

typedef enum{no_format,pk_format,ft_format}FontFormat;
/*:328*//*329:*/
#line 5934 "hint.w"

/*363:*/
#line 6960 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
double ds;
unsigned char id;
}PKfont;
/*:363*//*375:*/
#line 7291 "hint.w"

typedef struct
{FT_Face face;
}FTfont;
/*:375*//*376:*/
#line 7298 "hint.w"

typedef struct
{int dummy;
}FTglyph;
/*:376*/
#line 5935 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int data_size;
double s;
double hpxs,vpxs;
/*335:*/
#line 6029 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:335*/
#line 5943 "hint.w"

FontFormat ff;
union{PKfont pk;FTfont tt;};
}Font;
/*:329*//*340:*/
#line 6241 "hint.w"

/*364:*/
#line 6973 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}PKglyph;
/*:364*//*366:*/
#line 7000 "hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*data;
}PKparse;
/*:366*/
#line 6242 "hint.w"


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
/*:340*/
#line 7890 "hint.w"



#endif
/*:399*/
