/*754:*/
#line 16162 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H
/*696:*/
#line 14211 "hint.w"

extern void nativeBackground(double x,double y,double h,double w,uint32_t bg);
/*:696*//*707:*/
#line 14884 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:707*//*708:*/
#line 14894 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double pt_x,double pt_v);
/*:708*//*709:*/
#line 14900 "hint.w"

extern void nativeSetForeground(uint32_t fg);
extern void nativeSetGamma(double gamma);
/*:709*//*710:*/
#line 14907 "hint.w"

extern void nativeBlank(uint32_t bg);
/*:710*//*711:*/
#line 14917 "hint.w"

extern void nativeGlyph(double x,double y,double w,double h,
unsigned int t);
/*:711*//*712:*/
#line 14927 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:712*//*713:*/
#line 14933 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:713*//*714:*/
#line 14939 "hint.w"

extern unsigned int nativeTexture(unsigned char*bits,int w,int h);
/*:714*//*715:*/
#line 14945 "hint.w"

unsigned int nativeFreeTexture(unsigned int t);
/*:715*/
#line 16165 "hint.w"

#endif
/*:754*/
