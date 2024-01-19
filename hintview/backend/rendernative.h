/*407:*/
#line 8335 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H
/*72:*/
#line 1241 "hint.w"

typedef uint8_t ColorSet[2][4][2][4];
extern ColorSet*color_def;
/*:72*//*349:*/
#line 6581 "hint.w"

extern void nativeSetColor(ColorSet*cs);
extern void nativeSetStyle(int s);
extern void nativeBackground(double x,double y,double h,double w,int style);
/*:349*//*359:*/
#line 7250 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:359*//*360:*/
#line 7260 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double xdpi,double ydpi);
/*:360*//*361:*/
#line 7266 "hint.w"

extern void nativeSetDark(int dark);
extern void nativeSetGamma(double gamma);
/*:361*//*362:*/
#line 7272 "hint.w"

extern void nativeBlank(void);
/*:362*//*363:*/
#line 7282 "hint.w"

typedef struct gcache_s*gcache_s_ptr;

extern void nativeGlyph(double x,double dx,double y,double dy,double w,double h,struct gcache_s*g,int style);
/*:363*//*364:*/
#line 7293 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:364*//*365:*/
#line 7299 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:365*//*366:*/
#line 7305 "hint.w"

extern void nativeSetPK(struct gcache_s*g);
extern void nativeSetFreeType(struct gcache_s*g);
/*:366*//*367:*/
#line 7312 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:367*/
#line 8338 "hint.w"

#endif
/*:407*/
