/*404:*/
#line 8385 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H
/*345:*/
#line 6597 "hint.w"

extern void nativeSetColor(ColorSet*cs);
extern void nativeBackground(double x,double y,double h,double w);
/*:345*//*356:*/
#line 7284 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:356*//*357:*/
#line 7294 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double xdpi,double ydpi);
/*:357*//*358:*/
#line 7300 "hint.w"

extern void nativeSetDark(int dark);
extern void nativeSetGamma(double gamma);
/*:358*//*359:*/
#line 7307 "hint.w"

extern void nativeBlank(void);
/*:359*//*360:*/
#line 7317 "hint.w"

typedef struct gcache_s*gcache_s_ptr;

extern void nativeGlyph(double x,double dx,double y,double dy,double w,double h,struct gcache_s*g,int style);
/*:360*//*361:*/
#line 7328 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:361*//*362:*/
#line 7334 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:362*//*363:*/
#line 7340 "hint.w"

extern void nativeSetPK(struct gcache_s*g);
extern void nativeSetFreeType(struct gcache_s*g);
/*:363*//*364:*/
#line 7347 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:364*/
#line 8388 "hint.w"

#endif
#line 8390 "hint.w"
/*:404*/
