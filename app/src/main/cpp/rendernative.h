/*349:*/
#line 6858 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H

/*301:*/
#line 5793 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
/*:301*//*302:*/
#line 5800 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double dpi);
/*:302*//*303:*/
#line 5805 "hint.w"

extern void nativeSetDark(int dark);
/*:303*//*304:*/
#line 5810 "hint.w"

extern void nativeBlank(void);
/*:304*//*305:*/
#line 5820 "hint.w"

typedef struct gcache_s*gcache_s_ptr;

extern void nativeGlyph(double x,double dx,double y,double dy,double w,double h,struct gcache_s*g,uint8_t s);
/*:305*//*306:*/
#line 5831 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:306*//*307:*/
#line 5837 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:307*//*308:*/
#line 5843 "hint.w"

extern void nativeSetPK(struct gcache_s*g);
extern void nativeSetFreeType(struct gcache_s*g);
/*:308*//*309:*/
#line 5850 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:309*/
#line 6862 "hint.w"


#endif
/*:349*/
