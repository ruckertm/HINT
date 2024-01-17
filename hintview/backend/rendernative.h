/*403:*/
#line 8197 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H
/*72:*/
#line 1243 "hint.w"

typedef uint8_t ColorSet[2][4][2][4];
extern ColorSet*color_def;
/*:72*//*348:*/
#line 6551 "hint.w"

extern void nativeSetColor(ColorSet*cs);
extern void nativeBackground(double x,double y,double h,double w,int style);
/*:348*//*355:*/
#line 7112 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:355*//*356:*/
#line 7122 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double xdpi,double ydpi);
/*:356*//*357:*/
#line 7128 "hint.w"

extern void nativeSetDark(int dark);
extern void nativeSetGamma(double gamma);
/*:357*//*358:*/
#line 7134 "hint.w"

extern void nativeBlank(void);
/*:358*//*359:*/
#line 7144 "hint.w"

typedef struct gcache_s*gcache_s_ptr;

extern void nativeGlyph(double x,double dx,double y,double dy,double w,double h,struct gcache_s*g,uint8_t s);
/*:359*//*360:*/
#line 7155 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:360*//*361:*/
#line 7161 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:361*//*362:*/
#line 7167 "hint.w"

extern void nativeSetPK(struct gcache_s*g);
extern void nativeSetFreeType(struct gcache_s*g);
/*:362*//*363:*/
#line 7174 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:363*/
#line 8200 "hint.w"

#endif
/*:403*/
