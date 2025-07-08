/*762:*/
#line 16089 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H
/*704:*/
#line 14154 "hint.w"

extern void nativeBackground(double x,double y,double h,double w,uint32_t bg);
/*:704*//*715:*/
#line 14825 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:715*//*716:*/
#line 14835 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double pt_x,double pt_v);
/*:716*//*717:*/
#line 14841 "hint.w"

extern void nativeSetForeground(uint32_t fg);
extern void nativeSetGamma(double gamma);
/*:717*//*718:*/
#line 14848 "hint.w"

extern void nativeBlank(uint32_t bg);
/*:718*//*719:*/
#line 14858 "hint.w"

extern void nativeGlyph(double x,double y,double w,double h,
unsigned int t);
/*:719*//*720:*/
#line 14868 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:720*//*721:*/
#line 14874 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:721*//*722:*/
#line 14880 "hint.w"

extern unsigned int nativeTexture(unsigned char*bits,int w,int h);
/*:722*//*723:*/
#line 14886 "hint.w"

unsigned int nativeFreeTexture(unsigned int t);
/*:723*/
#line 16092 "hint.w"

#endif
#line 16094 "hint.w"
/*:762*/
