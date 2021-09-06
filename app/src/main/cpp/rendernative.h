/*372:*/
#line 7428 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H

/*324:*/
#line 6362 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
/*:324*//*325:*/
#line 6369 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double dpi);
/*:325*//*326:*/
#line 6374 "hint.w"

extern void nativeSetDark(int dark);
/*:326*//*327:*/
#line 6379 "hint.w"

extern void nativeBlank(void);
/*:327*//*328:*/
#line 6389 "hint.w"

typedef struct gcache_s*gcache_s_ptr;

extern void nativeGlyph(double x,double dx,double y,double dy,double w,double h,struct gcache_s*g,uint8_t s);
/*:328*//*329:*/
#line 6400 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:329*//*330:*/
#line 6406 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:330*//*331:*/
#line 6412 "hint.w"

extern void nativeSetPK(struct gcache_s*g);
extern void nativeSetFreeType(struct gcache_s*g);
/*:331*//*332:*/
#line 6419 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:332*/
#line 7432 "hint.w"


#endif
/*:372*/
