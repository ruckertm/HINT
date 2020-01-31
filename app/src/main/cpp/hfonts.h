<<<<<<< HEAD
/*298:*/
#line 5617 "hint.w"
=======
/*302:*/
#line 5684 "hint.w"
>>>>>>> socher

#ifndef _HFONTS_H
#define _HFONTS_H
/*243:*/
<<<<<<< HEAD
#line 4206 "hint.w"

typedef enum{no_format,pk_format,t1_format,ot_format,tt_format}font_format_t;
/*:243*//*244:*/
#line 4214 "hint.w"

/*274:*/
#line 5070 "hint.w"
=======
#line 4212 "hint.w"

typedef enum{no_format,pk_format,t1_format,ot_format,tt_format}font_format_t;
/*:243*//*244:*/
#line 4223 "hint.w"

/*276:*/
#line 5112 "hint.w"
>>>>>>> socher


typedef struct
{unsigned char*pk_comment;
unsigned int cs;
unsigned char id;
<<<<<<< HEAD
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
=======
}pk_t;
/*:276*//*280:*/
#line 5281 "hint.w"

typedef stbtt_fontinfo tt_t;
typedef struct
{int dummy;
}ttg_t;
/*:280*//*284:*/
#line 5334 "hint.w"

typedef struct
{int dummy;
}t1_t;
/*:284*//*286:*/
#line 5347 "hint.w"

typedef struct
{int dummy;
}ot_t;
/*:286*/
#line 4224 "hint.w"


typedef struct font_s{
unsigned char n;
>>>>>>> socher
unsigned char*font_data;
int size;
double ds;
double hppp,vppp;
<<<<<<< HEAD
/*248:*/
#line 4287 "hint.w"
=======
/*249:*/
#line 4309 "hint.w"
>>>>>>> socher

struct gcache_s**g0;
struct gcache_s***g1;
struct gcache_s****g2;
struct gcache_s*****g3;

<<<<<<< HEAD
/*:248*/
#line 4222 "hint.w"
=======
/*:249*/
#line 4232 "hint.w"
>>>>>>> socher

font_format_t ff;
union{
pk_t pk;
tt_t tt;
t1_t t1;
ot_t ot;
};
}font_t;
<<<<<<< HEAD
/*:244*//*249:*/
#line 4299 "hint.w"

typedef struct gcache_s gcache_t;
/*:249*//*254:*/
#line 4495 "hint.w"

/*275:*/
#line 5085 "hint.w"
=======
/*:244*//*250:*/
#line 4321 "hint.w"

typedef struct gcache_s gcache_t;
/*:250*//*255:*/
#line 4514 "hint.w"

/*277:*/
#line 5124 "hint.w"
>>>>>>> socher

typedef struct
{unsigned char flag;
unsigned char*encoding;
}pkg_t;
<<<<<<< HEAD
/*:275*//*279:*/
#line 5259 "hint.w"
=======
/*:277*//*285:*/
#line 5339 "hint.w"
>>>>>>> socher

typedef struct
{int dummy;
}t1g_t;
<<<<<<< HEAD
/*:279*//*281:*/
#line 5272 "hint.w"
=======
/*:285*//*287:*/
#line 5352 "hint.w"
>>>>>>> socher

typedef struct
{int dummy;
}otg_t;
<<<<<<< HEAD
/*:281*//*283:*/
#line 5284 "hint.w"

typedef struct
{int dummy;
}ttg_t;
/*:283*/
#line 4496 "hint.w"


struct gcache_s{
unsigned int w,h;
=======
/*:287*/
#line 4515 "hint.w"


struct gcache_s{
int w,h;
>>>>>>> socher
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
<<<<<<< HEAD
/*:254*/
#line 5620 "hint.w"


extern void render_char(int x,int y,font_t*f,int32_t s,uint32_t cc);
extern font_t*hget_font(unsigned char f);
extern void hclear_fonts(void);
#endif
/*:298*/
=======
/*:255*/
#line 5687 "hint.w"



#endif
/*:302*/
>>>>>>> socher
