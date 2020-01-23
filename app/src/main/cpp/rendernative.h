/*317:*/
#line 5783 ".\\hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H

/*281:*/
#line 5090 ".\\hint.w"

extern void nativeInit(void);
/*:281*//*282:*/
#line 5096 ".\\hint.w"

extern void nativeSetSize(int px_h,int px_v,double dpi);
/*:282*//*283:*/
#line 5101 ".\\hint.w"

/* DEPRECATED!!! Use nativeSetDark */
extern void nativeSetColors(double fr, double fg, double fb, double br, double bg, double bb);

extern void nativeSetDark(int dark);
/*:283*//*284:*/
#line 5106 ".\\hint.w"

extern void nativeBlank(void);
/*:284*//*285:*/
#line 5115 ".\\hint.w"

extern void nativeGlyph(double x,double y,double w,double h,gcache_t*g);
/*:285*//*286:*/
#line 5120 ".\\hint.w"

void nativeRule(double x,double y,double w,double h);
/*:286*//*287:*/
#line 5126 ".\\hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:287*//*288:*/
#line 5135 ".\\hint.w"

extern void nativeSetRunlength(gcache_t*g,unsigned char*g_data);
extern void nativeSetBitmaped(gcache_t*g,unsigned char*g_data);
/*:288*//*289:*/
#line 5145 ".\\hint.w"

void nativeFreeGlyph(gcache_t*g);
/*:289*/
#line 5787 ".\\hint.w"


#endif
/*:317*/
