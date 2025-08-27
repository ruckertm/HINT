/*759:*/
#line 16214 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H
/*701:*/
#line 14248 "hint.w"

extern void nativeBackground(double x,double y,double h,double w,uint32_t bg);
/*:701*//*712:*/
#line 14921 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:712*//*713:*/
#line 14931 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double pt_x,double pt_v);
/*:713*//*714:*/
#line 14937 "hint.w"

extern void nativeSetForeground(uint32_t fg);
extern void nativeSetGamma(double gamma);
/*:714*//*715:*/
#line 14944 "hint.w"

extern void nativeBlank(uint32_t bg);
/*:715*//*716:*/
#line 14954 "hint.w"

extern void nativeGlyph(double x,double y,double w,double h,
unsigned int t);
/*:716*//*717:*/
#line 14964 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:717*//*718:*/
#line 14970 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:718*//*719:*/
#line 14976 "hint.w"

extern unsigned int nativeTexture(unsigned char*bits,int w,int h);
/*:719*//*720:*/
#line 14982 "hint.w"

unsigned int nativeFreeTexture(unsigned int t);
/*:720*/
#line 16217 "hint.w"

#endif
#line 16219 "hint.w"
/*:759*/
