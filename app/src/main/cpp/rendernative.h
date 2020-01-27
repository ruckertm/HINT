/*299:*/
#line 5609 ".\\hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H

/*263:*/
#line 4913 ".\\hint.w"

extern void nativeInit(void);
/*:263*//*264:*/
#line 4919 ".\\hint.w"

extern void nativeSetSize(int px_h,int px_v,double dpi);
/*:264*//*265:*/
#line 4924 ".\\hint.w"

extern void nativeSetDark(int dark);
/*:265*//*266:*/
#line 4929 ".\\hint.w"

extern void nativeBlank(void);
/*:266*//*267:*/
#line 4938 ".\\hint.w"

extern void nativeGlyph(double x,double y,double w,double h,gcache_t*g);
/*:267*//*268:*/
#line 4943 ".\\hint.w"

void nativeRule(double x,double y,double w,double h);
/*:268*//*269:*/
#line 4949 ".\\hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:269*//*270:*/
#line 4958 ".\\hint.w"

extern void nativeSetRunlength(gcache_t*g,unsigned char*g_data);
extern void nativeSetBitmaped(gcache_t*g,unsigned char*g_data);
/*:270*//*271:*/
#line 4968 ".\\hint.w"

void nativeFreeGlyph(gcache_t*g);
/*:271*/
#line 5613 ".\\hint.w"


#endif
/*:299*/
