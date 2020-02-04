/*304:*/
#line 5815 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H

/*266:*/
#line 5096 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
/*:266*//*267:*/
#line 5103 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double dpi);
/*:267*//*268:*/
#line 5108 "hint.w"

extern void nativeSetDark(int dark);
/*:268*//*269:*/
#line 5113 "hint.w"

extern void nativeBlank(void);
/*:269*//*270:*/
#line 5122 "hint.w"

typedef struct gcache_s*gcache_s_ptr;
extern void nativeGlyph(double x,double y,double w,double h,struct gcache_s*g);
/*:270*//*271:*/
#line 5128 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:271*//*272:*/
#line 5134 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:272*//*273:*/
#line 5141 "hint.w"

extern void nativeSetRunlength(struct gcache_s*g,unsigned char*g_data);
extern void nativeSetBitmaped(struct gcache_s*g,unsigned char*g_data);
extern void nativeSetTrueType(struct gcache_s*g);
/*:273*//*274:*/
#line 5152 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:274*/
#line 5819 "hint.w"


#endif
/*:304*/
