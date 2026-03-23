/*688:*/
#line 15053 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H
/*515:*/
#line 10083 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:515*//*516:*/
#line 10093 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double pt_x,double pt_v);
/*:516*//*517:*/
#line 10099 "hint.w"

extern void nativeSetForeground(uint32_t fg);
extern void nativeSetGamma(double gamma);
/*:517*//*518:*/
#line 10106 "hint.w"

extern void nativeBlank(uint32_t bg);
/*:518*//*519:*/
#line 10116 "hint.w"

extern void nativeGlyph(double x,double y,double w,double h,
unsigned int t);
/*:519*//*520:*/
#line 10126 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:520*//*521:*/
#line 10132 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:521*//*522:*/
#line 10138 "hint.w"

extern unsigned int nativeTexture(unsigned char*bits,int w,int h);
/*:522*//*523:*/
#line 10144 "hint.w"

unsigned int nativeFreeTexture(unsigned int t);
/*:523*//*663:*/
#line 13807 "hint.w"

extern void nativeBackground(double x,double y,double h,double w,uint32_t bg);
/*:663*/
#line 15056 "hint.w"

#endif
/*:688*/
