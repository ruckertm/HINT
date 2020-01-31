<<<<<<< HEAD
/*300:*/
#line 5651 "hint.w"
=======
/*304:*/
#line 5718 "hint.w"
>>>>>>> socher

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H

<<<<<<< HEAD
/*264:*/
#line 4955 "hint.w"

extern void nativeInit(void);
/*:264*//*265:*/
#line 4961 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double dpi);
/*:265*//*266:*/
#line 4966 "hint.w"

extern void nativeSetDark(int dark);
/*:266*//*267:*/
#line 4971 "hint.w"

extern void nativeBlank(void);
/*:267*//*268:*/
#line 4980 "hint.w"

extern void nativeGlyph(double x,double y,double w,double h,gcache_t*g);
/*:268*//*269:*/
#line 4985 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:269*//*270:*/
#line 4991 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:270*//*271:*/
#line 5000 "hint.w"

extern void nativeSetRunlength(gcache_t*g,unsigned char*g_data);
extern void nativeSetBitmaped(gcache_t*g,unsigned char*g_data);
/*:271*//*272:*/
#line 5010 "hint.w"

void nativeFreeGlyph(gcache_t*g);
/*:272*/
#line 5655 "hint.w"


#endif
/*:300*/
=======
/*266:*/
#line 5000 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
/*:266*//*267:*/
#line 5007 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double dpi);
/*:267*//*268:*/
#line 5012 "hint.w"

extern void nativeSetDark(int dark);
/*:268*//*269:*/
#line 5017 "hint.w"

extern void nativeBlank(void);
/*:269*//*270:*/
#line 5026 "hint.w"

typedef struct gcache_s*gcache_s_ptr;
extern void nativeGlyph(double x,double y,double w,double h,struct gcache_s*g);
/*:270*//*271:*/
#line 5032 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:271*//*272:*/
#line 5038 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:272*//*273:*/
#line 5045 "hint.w"

extern void nativeSetRunlength(struct gcache_s*g,unsigned char*g_data);
extern void nativeSetBitmaped(struct gcache_s*g,unsigned char*g_data);
extern void nativeSetTrueType(struct gcache_s*g);
/*:273*//*274:*/
#line 5056 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:274*/
#line 5722 "hint.w"


#endif
/*:304*/
>>>>>>> socher
