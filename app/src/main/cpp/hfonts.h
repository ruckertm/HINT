/*347:*/
#line 6819 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H

/*277:*/
#line 4927 "hint.w"

typedef enum{no_format,pk_format,ft_format}font_format_t;
/*:277*//*278:*/
#line 4939 "hint.w"

/*311:*/
#line 5909 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
double ds;
unsigned char id;
}pk_t;
/*:311*//*323:*/
#line 6240 "hint.w"

typedef struct
{FT_Face face;
}ft_t;
/*:323*//*324:*/
#line 6247 "hint.w"

typedef struct
{int dummy;
}ftg_t;
/*:324*/
#line 4940 "hint.w"


typedef struct font_s{
unsigned char n;
unsigned char*font_data;
int data_size;
double s;
double hpxs,vpxs;
/*283:*/
#line 5028 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:283*/
#line 4948 "hint.w"

font_format_t ff;
union{pk_t pk;ft_t tt;};
}font_t;
/*:278*//*284:*/
#line 5040 "hint.w"

typedef struct gcache_s gcache_t;
/*:284*//*289:*/
#line 5244 "hint.w"

/*312:*/
#line 5922 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}pkg_t;
/*:312*//*314:*/
#line 5949 "hint.w"

typedef struct{
int j;
int r;
int f;
unsigned char*data;
}pk_parse_t;
/*:314*/
#line 5245 "hint.w"


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
/*:289*/
#line 6823 "hint.w"



#endif
/*:347*/
