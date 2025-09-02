/*735:*/
#line 15661 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H
/*679:*/
#line 13731 "hint.w"

extern void nativeBackground(double x,double y,double h,double w,uint32_t bg);
/*:679*//*690:*/
#line 14404 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:690*//*691:*/
#line 14414 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double pt_x,double pt_v);
/*:691*//*692:*/
#line 14420 "hint.w"

extern void nativeSetForeground(uint32_t fg);
extern void nativeSetGamma(double gamma);
/*:692*//*693:*/
#line 14427 "hint.w"

extern void nativeBlank(uint32_t bg);
/*:693*//*694:*/
#line 14437 "hint.w"

extern void nativeGlyph(double x,double y,double w,double h,
unsigned int t);
/*:694*//*695:*/
#line 14447 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:695*//*696:*/
#line 14453 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:696*//*697:*/
#line 14459 "hint.w"

extern unsigned int nativeTexture(unsigned char*bits,int w,int h);
/*:697*//*698:*/
#line 14465 "hint.w"

unsigned int nativeFreeTexture(unsigned int t);
/*:698*/
#line 15664 "hint.w"

#endif
/*:735*/
