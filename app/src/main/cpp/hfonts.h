/*298:*/
#line 5617 "hint.w"

#ifndef _HFONTS_H
#define _HFONTS_H
/*243:*/
#line 4206 "hint.w"

typedef enum{no_format,pk_format,t1_format,ot_format,tt_format}font_format_t;
/*:243*//*244:*/
#line 4214 "hint.w"

/*274:*/
#line 5070 "hint.w"


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
unsigned char id;
#if 0
unsigned char flag;
#endif
}pk_t;
/*:274*//*278:*/
#line 5254 "hint.w"

typedef struct
{int dummy;
}t1_t;
/*:278*//*280:*/
#line 5267 "hint.w"

typedef struct
{int dummy;
}ot_t;
/*:280*//*282:*/
#line 5279 "hint.w"

typedef struct
{int dummy;
}tt_t;
/*:282*/
#line 4215 "hint.w"


typedef struct{
unsigned char*font_data;
int size;
double ds;
double hppp,vppp;
/*248:*/
#line 4287 "hint.w"

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

/*:248*/
#line 4222 "hint.w"

font_format_t ff;
union{
pk_t pk;
tt_t tt;
t1_t t1;
ot_t ot;
};
}font_t;
/*:244*//*249:*/
#line 4299 "hint.w"

typedef struct gcache_s gcache_t;
/*:249*//*254:*/
#line 4495 "hint.w"

/*275:*/
#line 5085 "hint.w"

typedef struct
{unsigned char flag;
unsigned char*encoding;
}pkg_t;
/*:275*//*279:*/
#line 5259 "hint.w"

typedef struct
{int dummy;
}t1g_t;
/*:279*//*281:*/
#line 5272 "hint.w"

typedef struct
{int dummy;
}otg_t;
/*:281*//*283:*/
#line 5284 "hint.w"

typedef struct
{int dummy;
}ttg_t;
/*:283*/
#line 4496 "hint.w"


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
/*:254*/
#line 5620 "hint.w"


extern void render_char(int x,int y,font_t*f,int32_t s,uint32_t cc);
extern font_t*hget_font(unsigned char f);
extern void hclear_fonts(void);
#endif
/*:298*/
