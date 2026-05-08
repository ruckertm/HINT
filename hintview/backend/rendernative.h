/*696:*/
#line 15200 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H
/*515:*/
#line 10091 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:515*//*516:*/
#line 10101 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double pt_x,double pt_v);
/*:516*//*517:*/
#line 10107 "hint.w"

extern void nativeSetForeground(uint32_t fg);
extern void nativeSetGamma(double gamma);
/*:517*//*518:*/
#line 10114 "hint.w"

extern void nativeBlank(uint32_t bg);
/*:518*//*519:*/
#line 10124 "hint.w"

extern void nativeGlyph(double x,double y,double w,double h,
unsigned int t);
/*:519*//*520:*/
#line 10134 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:520*//*521:*/
#line 10140 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:521*//*522:*/
#line 10146 "hint.w"

extern unsigned int nativeTexture(unsigned char*bits,int w,int h);
/*:522*//*523:*/
#line 10152 "hint.w"

unsigned int nativeFreeTexture(unsigned int t);
/*:523*//*671:*/
#line 13954 "hint.w"

extern void nativeBackground(double x,double y,double h,double w,uint32_t bg);
/*:671*/
#line 15203 "hint.w"

#endif
/*:696*/
