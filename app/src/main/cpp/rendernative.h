/*346:*/
#line 6719 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H

/*298:*/
#line 5653 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
/*:298*//*299:*/
#line 5660 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double dpi);
/*:299*//*300:*/
#line 5665 "hint.w"

extern void nativeSetDark(int dark);
/*:300*//*301:*/
#line 5670 "hint.w"

extern void nativeBlank(void);
/*:301*//*302:*/
#line 5680 "hint.w"

typedef struct gcache_s*gcache_s_ptr;

extern void nativeGlyph(double x,double dx,double y,double dy,double w,double h,struct gcache_s*g,uint8_t s);
/*:302*//*303:*/
#line 5691 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:303*//*304:*/
#line 5697 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:304*//*305:*/
#line 5703 "hint.w"

extern void nativeSetPK(struct gcache_s*g);
extern void nativeSetFreeType(struct gcache_s*g);
/*:305*//*306:*/
#line 5710 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:306*/
#line 6723 "hint.w"


#endif
/*:346*/
