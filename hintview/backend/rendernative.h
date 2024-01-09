/*393:*/
#line 7789 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H

/*345:*/
#line 6704 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:345*//*346:*/
#line 6714 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double xdpi,double ydpi);
/*:346*//*347:*/
#line 6720 "hint.w"

extern void nativeSetDark(int dark);
extern void nativeSetGamma(double gamma);
/*:347*//*348:*/
#line 6726 "hint.w"

extern void nativeBlank(void);
/*:348*//*349:*/
#line 6736 "hint.w"

typedef struct gcache_s*gcache_s_ptr;

extern void nativeGlyph(double x,double dx,double y,double dy,double w,double h,struct gcache_s*g,uint8_t s);
/*:349*//*350:*/
#line 6747 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:350*//*351:*/
#line 6753 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:351*//*352:*/
#line 6759 "hint.w"

extern void nativeSetPK(struct gcache_s*g);
extern void nativeSetFreeType(struct gcache_s*g);
/*:352*//*353:*/
#line 6766 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:353*/
#line 7793 "hint.w"


#endif
/*:393*/
