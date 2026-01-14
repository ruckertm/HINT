/*688:*/
#line 15001 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H
/*514:*/
#line 10024 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:514*//*515:*/
#line 10034 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double pt_x,double pt_v);
/*:515*//*516:*/
#line 10040 "hint.w"

extern void nativeSetForeground(uint32_t fg);
extern void nativeSetGamma(double gamma);
/*:516*//*517:*/
#line 10047 "hint.w"

extern void nativeBlank(uint32_t bg);
/*:517*//*518:*/
#line 10057 "hint.w"

extern void nativeGlyph(double x,double y,double w,double h,
unsigned int t);
/*:518*//*519:*/
#line 10067 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:519*//*520:*/
#line 10073 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:520*//*521:*/
#line 10079 "hint.w"

extern unsigned int nativeTexture(unsigned char*bits,int w,int h);
/*:521*//*522:*/
#line 10085 "hint.w"

unsigned int nativeFreeTexture(unsigned int t);
/*:522*//*663:*/
#line 13768 "hint.w"

extern void nativeBackground(double x,double y,double h,double w,uint32_t bg);
/*:663*/
#line 15004 "hint.w"

#endif
/*:688*/
