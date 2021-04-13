/*344:*/
#line 6748 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H

/*275:*/
#line 4862 "hint.w"

typedef enum{no_format,pk_format,ft_format}font_format_t;
/*:275*//*276:*/
#line 4874 "hint.w"

/*308:*/
#line 5838 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
double ds;
unsigned char id;
}pk_t;
/*:308*//*320:*/
#line 6169 "hint.w"

typedef struct
{FT_Face face;
}ft_t;
/*:320*//*321:*/
#line 6176 "hint.w"

typedef struct
{int dummy;
}ftg_t;
/*:321*/
#line 4875 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int data_size;
double s;
double hpxs,vpxs;
/*281:*/
#line 4963 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:281*/
#line 4883 "hint.w"

font_format_t ff;
union{pk_t pk;ft_t tt;};
}font_t;
/*:276*//*282:*/
#line 4975 "hint.w"

typedef struct gcache_s gcache_t;
/*:282*//*287:*/
#line 5179 "hint.w"

/*309:*/
#line 5851 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}pkg_t;
/*:309*//*311:*/
#line 5878 "hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*data;
}pk_parse_t;
/*:311*/
#line 5180 "hint.w"


struct gcache_s{
int w,h;
int hoff,voff;
unsigned char*bits;
unsigned int GLtexture;
font_format_t ff;
union{
pkg_t pk;
ftg_t tt;
};
};
/*:287*/
#line 6752 "hint.w"



#endif
/*:344*/
