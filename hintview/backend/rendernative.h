/*401:*/
#line 7925 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H
/*72:*/
#line 1135 "hint.w"

typedef uint8_t ColorSet[2][4][2][4];
extern ColorSet*color_def;
/*:72*//*347:*/
#line 6363 "hint.w"

extern void nativeSetColor(ColorSet*cs);
/*:347*//*353:*/
#line 6839 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:353*//*354:*/
#line 6849 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double xdpi,double ydpi);
/*:354*//*355:*/
#line 6855 "hint.w"

extern void nativeSetDark(int dark);
extern void nativeSetGamma(double gamma);
/*:355*//*356:*/
#line 6861 "hint.w"

extern void nativeBlank(void);
/*:356*//*357:*/
#line 6871 "hint.w"

typedef struct gcache_s*gcache_s_ptr;

extern void nativeGlyph(double x,double dx,double y,double dy,double w,double h,struct gcache_s*g,uint8_t s);
/*:357*//*358:*/
#line 6882 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:358*//*359:*/
#line 6888 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:359*//*360:*/
#line 6894 "hint.w"

extern void nativeSetPK(struct gcache_s*g);
extern void nativeSetFreeType(struct gcache_s*g);
/*:360*//*361:*/
#line 6901 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:361*/
#line 7928 "hint.w"

#endif
/*:401*/
