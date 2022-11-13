/*379:*/
#line 7696 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H

/*331:*/
#line 6611 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:331*//*332:*/
#line 6621 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double xdpi,double ydpi);
/*:332*//*333:*/
#line 6627 "hint.w"

extern void nativeSetDark(int dark);
extern void nativeSetGamma(double gamma);
/*:333*//*334:*/
#line 6633 "hint.w"

extern void nativeBlank(void);
/*:334*//*335:*/
#line 6643 "hint.w"

typedef struct gcache_s*gcache_s_ptr;

extern void nativeGlyph(double x,double dx,double y,double dy,double w,double h,struct gcache_s*g,uint8_t s);
/*:335*//*336:*/
#line 6654 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:336*//*337:*/
#line 6660 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:337*//*338:*/
#line 6666 "hint.w"

extern void nativeSetPK(struct gcache_s*g);
extern void nativeSetFreeType(struct gcache_s*g);
/*:338*//*339:*/
#line 6673 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:339*/
#line 7700 "hint.w"


#endif
/*:379*/
