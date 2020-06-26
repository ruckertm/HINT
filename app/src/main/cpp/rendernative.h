/*325:*/
#line 6179 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H

/*284:*/
#line 5328 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
/*:284*//*285:*/
#line 5335 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double dpi);
/*:285*//*286:*/
#line 5340 "hint.w"

extern void nativeSetDark(int dark);
/*:286*//*287:*/
#line 5345 "hint.w"

extern void nativeBlank(void);
/*:287*//*288:*/
#line 5354 "hint.w"

typedef struct gcache_s*gcache_s_ptr;
extern void nativeGlyph(double x,double y,double w,double h,struct gcache_s*g);
/*:288*//*289:*/
#line 5360 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:289*//*290:*/
#line 5366 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:290*//*291:*/
#line 5373 "hint.w"

extern void nativeSetRunlength(struct gcache_s*g,unsigned char*g_data);
extern void nativeSetBitmaped(struct gcache_s*g,unsigned char*g_data);
extern void nativeSetTrueType(struct gcache_s*g);
/*:291*//*292:*/
#line 5384 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:292*/
#line 6183 "hint.w"


#endif
/*:325*/
