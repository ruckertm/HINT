/*406:*/
#line 8304 "hint.w"

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
/*:349*//*358:*/
#line 7219 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:358*//*359:*/
#line 7229 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double xdpi,double ydpi);
/*:359*//*360:*/
#line 7235 "hint.w"

extern void nativeSetDark(int dark);
extern void nativeSetGamma(double gamma);
/*:360*//*361:*/
#line 7241 "hint.w"

extern void nativeBlank(void);
/*:361*//*362:*/
#line 7251 "hint.w"

typedef struct gcache_s*gcache_s_ptr;

extern void nativeGlyph(double x,double dx,double y,double dy,double w,double h,struct gcache_s*g,int style);
/*:362*//*363:*/
#line 7262 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:363*//*364:*/
#line 7268 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:364*//*365:*/
#line 7274 "hint.w"

extern void nativeSetPK(struct gcache_s*g);
extern void nativeSetFreeType(struct gcache_s*g);
/*:365*//*366:*/
#line 7281 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:366*/
#line 8307 "hint.w"

#endif
/*:406*/
