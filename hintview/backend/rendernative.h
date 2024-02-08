/*406:*/
#line 8390 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H
/*345:*/
#line 6579 "hint.w"

extern void nativeSetColor(ColorSet*cs);
extern void nativeBackground(double x,double y,double h,double w);
/*:345*//*358:*/
#line 7299 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:358*//*359:*/
#line 7309 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double xdpi,double ydpi);
/*:359*//*360:*/
#line 7315 "hint.w"

extern void nativeSetDark(int dark);
extern void nativeSetGamma(double gamma);
/*:360*//*361:*/
#line 7322 "hint.w"

extern void nativeBlank(void);
/*:361*//*362:*/
#line 7332 "hint.w"

typedef struct gcache_s*gcache_s_ptr;

extern void nativeGlyph(double x,double dx,double y,double dy,double w,double h,struct gcache_s*g,int style);
/*:362*//*363:*/
#line 7343 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:363*//*364:*/
#line 7349 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:364*//*365:*/
#line 7355 "hint.w"

extern void nativeSetPK(struct gcache_s*g);
extern void nativeSetFreeType(struct gcache_s*g);
/*:365*//*366:*/
#line 7362 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:366*/
#line 8393 "hint.w"

#endif
/*:406*/
