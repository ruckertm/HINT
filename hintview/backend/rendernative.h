/*688:*/
#line 14998 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H
/*514:*/
#line 10022 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:514*//*515:*/
#line 10032 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double pt_x,double pt_v);
/*:515*//*516:*/
#line 10038 "hint.w"

extern void nativeSetForeground(uint32_t fg);
extern void nativeSetGamma(double gamma);
/*:516*//*517:*/
#line 10045 "hint.w"

extern void nativeBlank(uint32_t bg);
/*:517*//*518:*/
#line 10055 "hint.w"

extern void nativeGlyph(double x,double y,double w,double h,
unsigned int t);
/*:518*//*519:*/
#line 10065 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:519*//*520:*/
#line 10071 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:520*//*521:*/
#line 10077 "hint.w"

extern unsigned int nativeTexture(unsigned char*bits,int w,int h);
/*:521*//*522:*/
#line 10083 "hint.w"

unsigned int nativeFreeTexture(unsigned int t);
/*:522*//*663:*/
#line 13765 "hint.w"

extern void nativeBackground(double x,double y,double h,double w,uint32_t bg);
/*:663*/
#line 15001 "hint.w"

#endif
/*:688*/
