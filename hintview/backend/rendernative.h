/*399:*/
#line 7878 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H
/*72:*/
#line 1135 "hint.w"

typedef uint8_t ColorSet[2][4][2][4];
extern ColorSet*color_def;
/*:72*//*345:*/
#line 6333 "hint.w"

extern void nativeSetColor(ColorSet*cs);
/*:345*//*351:*/
#line 6792 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:351*//*352:*/
#line 6802 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double xdpi,double ydpi);
/*:352*//*353:*/
#line 6808 "hint.w"

extern void nativeSetDark(int dark);
extern void nativeSetGamma(double gamma);
/*:353*//*354:*/
#line 6814 "hint.w"

extern void nativeBlank(void);
/*:354*//*355:*/
#line 6824 "hint.w"

typedef struct gcache_s*gcache_s_ptr;

extern void nativeGlyph(double x,double dx,double y,double dy,double w,double h,struct gcache_s*g,uint8_t s);
/*:355*//*356:*/
#line 6835 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:356*//*357:*/
#line 6841 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:357*//*358:*/
#line 6847 "hint.w"

extern void nativeSetPK(struct gcache_s*g);
extern void nativeSetFreeType(struct gcache_s*g);
/*:358*//*359:*/
#line 6854 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:359*/
#line 7881 "hint.w"

#endif
/*:399*/
