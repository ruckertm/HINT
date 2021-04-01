/*333:*/
#line 6403 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H

/*285:*/
#line 5349 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
/*:285*//*286:*/
#line 5356 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double dpi);
/*:286*//*287:*/
#line 5361 "hint.w"

extern void nativeSetDark(int dark);
/*:287*//*288:*/
#line 5366 "hint.w"

extern void nativeBlank(void);
/*:288*//*289:*/
#line 5375 "hint.w"

typedef struct gcache_s*gcache_s_ptr;
extern void nativeGlyph(double x,double y,double w,double h,struct gcache_s*g);
/*:289*//*290:*/
#line 5381 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:290*//*291:*/
#line 5387 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:291*//*292:*/
#line 5393 "hint.w"

extern void nativeSetPK(struct gcache_s*g);
extern void nativeSetFreeType(struct gcache_s*g);
/*:292*//*293:*/
#line 5400 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:293*/
#line 6407 "hint.w"


#endif
/*:333*/
