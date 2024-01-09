/*396:*/
#line 7837 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H
typedef uint32_t Color;
typedef Color ColorPair[2];
typedef ColorPair ColorSet[8];
extern ColorSet*color_def;
extern void nativeSetForeground(uint32_t f,uint32_t b);
/*348:*/
#line 6751 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:348*//*349:*/
#line 6761 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double xdpi,double ydpi);
/*:349*//*350:*/
#line 6767 "hint.w"

extern void nativeSetDark(int dark);
extern void nativeSetGamma(double gamma);
extern void nativeSetColor(uint32_t fg,uint32_t bg);
/*:350*//*351:*/
#line 6774 "hint.w"

extern void nativeBlank(void);
/*:351*//*352:*/
#line 6784 "hint.w"

typedef struct gcache_s*gcache_s_ptr;

extern void nativeGlyph(double x,double dx,double y,double dy,double w,double h,struct gcache_s*g,uint8_t s);
/*:352*//*353:*/
#line 6795 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:353*//*354:*/
#line 6801 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:354*//*355:*/
#line 6807 "hint.w"

extern void nativeSetPK(struct gcache_s*g);
extern void nativeSetFreeType(struct gcache_s*g);
/*:355*//*356:*/
#line 6814 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:356*/
#line 7845 "hint.w"


#endif
/*:396*/
