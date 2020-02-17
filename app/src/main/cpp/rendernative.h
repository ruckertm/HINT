/*305:*/
#line 5713 ".\\hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H

/*267:*/
#line 4995 ".\\hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
/*:267*//*268:*/
#line 5002 ".\\hint.w"

extern void nativeSetSize(int px_h,int px_v,double dpi);
/*:268*//*269:*/
#line 5007 ".\\hint.w"

extern void nativeSetDark(int dark);
/*:269*//*270:*/
#line 5012 ".\\hint.w"

extern void nativeBlank(void);
/*:270*//*271:*/
#line 5021 ".\\hint.w"

typedef struct gcache_s*gcache_s_ptr;
extern void nativeGlyph(double x,double y,double w,double h,struct gcache_s*g);
/*:271*//*272:*/
#line 5027 ".\\hint.w"

void nativeRule(double x,double y,double w,double h);
/*:272*//*273:*/
#line 5033 ".\\hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:273*//*274:*/
#line 5040 ".\\hint.w"

extern void nativeSetRunlength(struct gcache_s*g,unsigned char*g_data);
extern void nativeSetBitmaped(struct gcache_s*g,unsigned char*g_data);
extern void nativeSetTrueType(struct gcache_s*g);
/*:274*//*275:*/
#line 5051 ".\\hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:275*/
#line 5717 ".\\hint.w"


#endif
/*:305*/
