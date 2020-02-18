/*306:*/
#line 5753 ".\\hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H

/*268:*/
#line 5040 ".\\hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
/*:268*//*269:*/
#line 5047 ".\\hint.w"

extern void nativeSetSize(int px_h,int px_v,double dpi);
/*:269*//*270:*/
#line 5052 ".\\hint.w"

extern void nativeSetDark(int dark);
/*:270*//*271:*/
#line 5057 ".\\hint.w"

extern void nativeBlank(void);
/*:271*//*272:*/
#line 5066 ".\\hint.w"

typedef struct gcache_s*gcache_s_ptr;
extern void nativeGlyph(double x,double y,double w,double h,struct gcache_s*g);
/*:272*//*273:*/
#line 5072 ".\\hint.w"

void nativeRule(double x,double y,double w,double h);
/*:273*//*274:*/
#line 5078 ".\\hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:274*//*275:*/
#line 5085 ".\\hint.w"

extern void nativeSetRunlength(struct gcache_s*g,unsigned char*g_data);
extern void nativeSetBitmaped(struct gcache_s*g,unsigned char*g_data);
extern void nativeSetTrueType(struct gcache_s*g);
/*:275*//*276:*/
#line 5096 ".\\hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:276*/
#line 5757 ".\\hint.w"


#endif
/*:306*/
