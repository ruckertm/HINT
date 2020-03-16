/*300:*/
#line 5677 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H

/*259:*/
#line 4832 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
/*:259*//*260:*/
#line 4839 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double dpi);
/*:260*//*261:*/
#line 4844 "hint.w"

extern void nativeSetDark(int dark);
/*:261*//*262:*/
#line 4849 "hint.w"

extern void nativeBlank(void);
/*:262*//*263:*/
#line 4858 "hint.w"

typedef struct gcache_s*gcache_s_ptr;
extern void nativeGlyph(double x,double y,double w,double h,struct gcache_s*g);
/*:263*//*264:*/
#line 4864 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:264*//*265:*/
#line 4870 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:265*//*266:*/
#line 4877 "hint.w"

extern void nativeSetRunlength(struct gcache_s*g,unsigned char*g_data);
extern void nativeSetBitmaped(struct gcache_s*g,unsigned char*g_data);
extern void nativeSetTrueType(struct gcache_s*g);
/*:266*//*267:*/
#line 4888 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:267*/
#line 5681 "hint.w"


#endif
/*:300*/
