/*405:*/
#line 8357 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H
/*346:*/
#line 6591 "hint.w"

extern void nativeSetColor(ColorSet*cs);
extern void nativeBackground(double x,double y,double h,double w);
/*:346*//*357:*/
#line 7269 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:357*//*358:*/
#line 7279 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double xdpi,double ydpi);
/*:358*//*359:*/
#line 7285 "hint.w"

extern void nativeSetDark(int dark);
extern void nativeSetGamma(double gamma);
/*:359*//*360:*/
#line 7292 "hint.w"

extern void nativeBlank(void);
/*:360*//*361:*/
#line 7302 "hint.w"

typedef struct gcache_s*gcache_s_ptr;

extern void nativeGlyph(double x,double dx,double y,double dy,double w,double h,struct gcache_s*g,int style);
/*:361*//*362:*/
#line 7313 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:362*//*363:*/
#line 7319 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:363*//*364:*/
#line 7325 "hint.w"

extern void nativeSetPK(struct gcache_s*g);
extern void nativeSetFreeType(struct gcache_s*g);
/*:364*//*365:*/
#line 7332 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:365*/
#line 8360 "hint.w"

#endif
/*:405*/
