/*297:*/
#line 5574 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H
/*242:*/
#line 4163 "hint.w"

typedef enum{no_format,pk_format,t1_format,ot_format,tt_format}font_format_t;
/*:242*//*243:*/
#line 4171 "hint.w"

/*273:*/
#line 5027 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
unsigned char id;
#if 0
unsigned char flag;
#endif
}pk_t;
/*:273*//*277:*/
#line 5211 "hint.w"

typedef struct
{int dummy;
}t1_t;
/*:277*//*279:*/
#line 5224 "hint.w"

typedef struct
{int dummy;
}ot_t;
/*:279*//*281:*/
#line 5236 "hint.w"

typedef struct
{int dummy;
}tt_t;
/*:281*/
#line 4172 "hint.w"


typedef struct{
unsigned char*font_data;
int size;
double ds;
double hppp,vppp;
/*247:*/
#line 4244 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:247*/
#line 4179 "hint.w"

font_format_t ff;
union{
pk_t pk;
tt_t tt;
t1_t t1;
ot_t ot;
};
}font_t;
/*:243*//*248:*/
#line 4256 "hint.w"

typedef struct gcache_s gcache_t;
/*:248*//*253:*/
#line 4452 "hint.w"

/*274:*/
#line 5042 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}pkg_t;
/*:274*//*278:*/
#line 5216 "hint.w"

typedef struct
{int dummy;
}t1g_t;
/*:278*//*280:*/
#line 5229 "hint.w"

typedef struct
{int dummy;
}otg_t;
/*:280*//*282:*/
#line 5241 "hint.w"

typedef struct
{int dummy;
}ttg_t;
/*:282*/
#line 4453 "hint.w"


struct gcache_s{
unsigned int w,h;
int hoff,voff;
unsigned char*bits;
#ifdef __ANDROID__
unsigned int GLtexture;
#endif
font_format_t ff;
union{
pkg_t pk;
ttg_t tt;
t1g_t t1;
otg_t ot;
};
};
/*:253*/
#line 5577 "hint.w"


extern void render_char(int x,int y,font_t*f,int32_t s,uint32_t cc);
extern font_t*hget_font(unsigned char f);
extern void hclear_fonts(void);
#endif
/*:297*/
