/*690:*/
#line 14964 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H
/*516:*/
#line 10025 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:516*//*517:*/
#line 10035 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double pt_x,double pt_v);
/*:517*//*518:*/
#line 10041 "hint.w"

extern void nativeSetForeground(uint32_t fg);
extern void nativeSetGamma(double gamma);
/*:518*//*519:*/
#line 10048 "hint.w"

extern void nativeBlank(uint32_t bg);
/*:519*//*520:*/
#line 10058 "hint.w"

extern void nativeGlyph(double x,double y,double w,double h,
unsigned int t);
/*:520*//*521:*/
#line 10068 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:521*//*522:*/
#line 10074 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:522*//*523:*/
#line 10080 "hint.w"

extern unsigned int nativeTexture(unsigned char*bits,int w,int h);
/*:523*//*524:*/
#line 10086 "hint.w"

unsigned int nativeFreeTexture(unsigned int t);
/*:524*//*665:*/
#line 13768 "hint.w"

extern void nativeBackground(double x,double y,double h,double w,uint32_t bg);
/*:665*/
#line 14967 "hint.w"

#endif
/*:690*/
