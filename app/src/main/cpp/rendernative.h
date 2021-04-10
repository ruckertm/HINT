/*347:*/
#line 6776 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H

/*299:*/
#line 5711 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
/*:299*//*300:*/
#line 5718 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double dpi);
/*:300*//*301:*/
#line 5723 "hint.w"

extern void nativeSetDark(int dark);
/*:301*//*302:*/
#line 5728 "hint.w"

extern void nativeBlank(void);
/*:302*//*303:*/
#line 5738 "hint.w"

typedef struct gcache_s*gcache_s_ptr;

extern void nativeGlyph(double x,double dx,double y,double dy,double w,double h,struct gcache_s*g,uint8_t s);
/*:303*//*304:*/
#line 5749 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:304*//*305:*/
#line 5755 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:305*//*306:*/
#line 5761 "hint.w"

extern void nativeSetPK(struct gcache_s*g);
extern void nativeSetFreeType(struct gcache_s*g);
/*:306*//*307:*/
#line 5768 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:307*/
#line 6780 "hint.w"


#endif
/*:347*/
