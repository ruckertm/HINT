/*329:*/
#line 6249 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H

/*288:*/
#line 5395 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
/*:288*//*289:*/
#line 5402 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double dpi);
/*:289*//*290:*/
#line 5407 "hint.w"

extern void nativeSetDark(int dark);
/*:290*//*291:*/
#line 5412 "hint.w"

extern void nativeBlank(void);
/*:291*//*292:*/
#line 5421 "hint.w"

typedef struct gcache_s*gcache_s_ptr;
extern void nativeGlyph(double x,double y,double w,double h,struct gcache_s*g);
/*:292*//*293:*/
#line 5427 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:293*//*294:*/
#line 5433 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:294*//*295:*/
#line 5440 "hint.w"

extern void nativeSetRunlength(struct gcache_s*g,unsigned char*g_data);
extern void nativeSetBitmaped(struct gcache_s*g,unsigned char*g_data);
extern void nativeSetTrueType(struct gcache_s*g);
/*:295*//*296:*/
#line 5451 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:296*/
#line 6253 "hint.w"


#endif
/*:329*/
