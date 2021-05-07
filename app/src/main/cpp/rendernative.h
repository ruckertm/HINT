/*350:*/
#line 6954 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H

/*302:*/
#line 5887 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
/*:302*//*303:*/
#line 5894 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double dpi);
/*:303*//*304:*/
#line 5899 "hint.w"

extern void nativeSetDark(int dark);
/*:304*//*305:*/
#line 5904 "hint.w"

extern void nativeBlank(void);
/*:305*//*306:*/
#line 5914 "hint.w"

typedef struct gcache_s*gcache_s_ptr;

extern void nativeGlyph(double x,double dx,double y,double dy,double w,double h,struct gcache_s*g,uint8_t s);
/*:306*//*307:*/
#line 5925 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:307*//*308:*/
#line 5931 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:308*//*309:*/
#line 5937 "hint.w"

extern void nativeSetPK(struct gcache_s*g);
extern void nativeSetFreeType(struct gcache_s*g);
/*:309*//*310:*/
#line 5944 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:310*/
#line 6958 "hint.w"


#endif
/*:350*/
