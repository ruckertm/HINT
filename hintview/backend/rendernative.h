/*404:*/
#line 8210 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H
/*72:*/
#line 1243 "hint.w"

typedef uint8_t ColorSet[2][4][2][4];
extern ColorSet*color_def;
/*:72*//*348:*/
#line 6553 "hint.w"

extern void nativeSetColor(ColorSet*cs);
extern void nativeBackground(double x,double y,double h,double w,int style);
/*:348*//*356:*/
#line 7125 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:356*//*357:*/
#line 7135 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double xdpi,double ydpi);
/*:357*//*358:*/
#line 7141 "hint.w"

extern void nativeSetDark(int dark);
extern void nativeSetGamma(double gamma);
/*:358*//*359:*/
#line 7147 "hint.w"

extern void nativeBlank(void);
/*:359*//*360:*/
#line 7157 "hint.w"

typedef struct gcache_s*gcache_s_ptr;

extern void nativeGlyph(double x,double dx,double y,double dy,double w,double h,struct gcache_s*g,uint8_t s);
/*:360*//*361:*/
#line 7168 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:361*//*362:*/
#line 7174 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:362*//*363:*/
#line 7180 "hint.w"

extern void nativeSetPK(struct gcache_s*g);
extern void nativeSetFreeType(struct gcache_s*g);
/*:363*//*364:*/
#line 7187 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:364*/
#line 8213 "hint.w"

#endif
/*:404*/
