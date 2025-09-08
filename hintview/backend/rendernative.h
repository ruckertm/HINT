/*685:*/
#line 14791 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H
/*512:*/
#line 9902 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
extern int nativePrintStart(int w,int h,int bpr,int bpp,unsigned char*bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char*bits);
/*:512*//*513:*/
#line 9912 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double pt_x,double pt_v);
/*:513*//*514:*/
#line 9918 "hint.w"

extern void nativeSetForeground(uint32_t fg);
extern void nativeSetGamma(double gamma);
/*:514*//*515:*/
#line 9925 "hint.w"

extern void nativeBlank(uint32_t bg);
/*:515*//*516:*/
#line 9935 "hint.w"

extern void nativeGlyph(double x,double y,double w,double h,
unsigned int t);
/*:516*//*517:*/
#line 9945 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:517*//*518:*/
#line 9951 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:518*//*519:*/
#line 9957 "hint.w"

extern unsigned int nativeTexture(unsigned char*bits,int w,int h);
/*:519*//*520:*/
#line 9963 "hint.w"

unsigned int nativeFreeTexture(unsigned int t);
/*:520*//*660:*/
#line 13609 "hint.w"

extern void nativeBackground(double x,double y,double h,double w,uint32_t bg);
/*:660*/
#line 14794 "hint.w"

#endif
/*:685*/
