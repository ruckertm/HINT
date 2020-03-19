/*300:*/
#line 5729 ".\\hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H

/*259:*/
#line 4884 ".\\hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
/*:259*//*260:*/
#line 4891 ".\\hint.w"

extern void nativeSetSize(int px_h,int px_v,double dpi);
/*:260*//*261:*/
#line 4896 ".\\hint.w"

extern void nativeSetDark(int dark);
/*:261*//*262:*/
#line 4901 ".\\hint.w"

extern void nativeBlank(void);
/*:262*//*263:*/
#line 4910 ".\\hint.w"

typedef struct gcache_s*gcache_s_ptr;
extern void nativeGlyph(double x,double y,double w,double h,struct gcache_s*g);
/*:263*//*264:*/
#line 4916 ".\\hint.w"

void nativeRule(double x,double y,double w,double h);
/*:264*//*265:*/
#line 4922 ".\\hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:265*//*266:*/
#line 4929 ".\\hint.w"

extern void nativeSetRunlength(struct gcache_s*g,unsigned char*g_data);
extern void nativeSetBitmaped(struct gcache_s*g,unsigned char*g_data);
extern void nativeSetTrueType(struct gcache_s*g);
/*:266*//*267:*/
#line 4940 ".\\hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:267*/
#line 5733 ".\\hint.w"


#endif
/*:300*/
