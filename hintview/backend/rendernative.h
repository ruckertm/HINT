/*405:*/
#line 8320 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H
/*346:*/
#line 6564 "hint.w"

extern void nativeSetColor(ColorSet*cs);
extern void nativeBackground(double x,double y,double h,double w);
/*:346*//*357:*/
#line 7232 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:357*//*358:*/
#line 7242 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double xdpi,double ydpi);
/*:358*//*359:*/
#line 7248 "hint.w"

extern void nativeSetDark(int dark);
extern void nativeSetGamma(double gamma);
/*:359*//*360:*/
#line 7255 "hint.w"

extern void nativeBlank(void);
/*:360*//*361:*/
#line 7265 "hint.w"

typedef struct gcache_s*gcache_s_ptr;

extern void nativeGlyph(double x,double dx,double y,double dy,double w,double h,struct gcache_s*g,int style);
/*:361*//*362:*/
#line 7276 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:362*//*363:*/
#line 7282 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:363*//*364:*/
#line 7288 "hint.w"

extern void nativeSetPK(struct gcache_s*g);
extern void nativeSetFreeType(struct gcache_s*g);
/*:364*//*365:*/
#line 7295 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:365*/
#line 8323 "hint.w"

#endif
/*:405*/
