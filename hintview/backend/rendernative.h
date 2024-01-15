/*402:*/
#line 7973 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H
/*72:*/
#line 1136 "hint.w"

typedef uint8_t ColorSet[2][4][2][4];
extern ColorSet*color_def;
/*:72*//*348:*/
#line 6412 "hint.w"

extern void nativeSetColor(ColorSet*cs);
/*:348*//*354:*/
#line 6888 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:354*//*355:*/
#line 6898 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double xdpi,double ydpi);
/*:355*//*356:*/
#line 6904 "hint.w"

extern void nativeSetDark(int dark);
extern void nativeSetGamma(double gamma);
/*:356*//*357:*/
#line 6910 "hint.w"

extern void nativeBlank(void);
/*:357*//*358:*/
#line 6920 "hint.w"

typedef struct gcache_s*gcache_s_ptr;

extern void nativeGlyph(double x,double dx,double y,double dy,double w,double h,struct gcache_s*g,uint8_t s);
/*:358*//*359:*/
#line 6931 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:359*//*360:*/
#line 6937 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:360*//*361:*/
#line 6943 "hint.w"

extern void nativeSetPK(struct gcache_s*g);
extern void nativeSetFreeType(struct gcache_s*g);
/*:361*//*362:*/
#line 6950 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:362*/
#line 7976 "hint.w"

#endif
/*:402*/
