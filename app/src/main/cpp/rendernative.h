/*297:*/
#line 5594 "hint.w"

#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H

/*256:*/
#line 4749 "hint.w"

extern void nativeInit(void);
extern void nativeClear(void);
/*:256*//*257:*/
#line 4756 "hint.w"

extern void nativeSetSize(int px_h,int px_v,double dpi);
/*:257*//*258:*/
#line 4761 "hint.w"

extern void nativeSetDark(int dark);
/*:258*//*259:*/
#line 4766 "hint.w"

extern void nativeBlank(void);
/*:259*//*260:*/
#line 4775 "hint.w"

typedef struct gcache_s*gcache_s_ptr;
extern void nativeGlyph(double x,double y,double w,double h,struct gcache_s*g);
/*:260*//*261:*/
#line 4781 "hint.w"

void nativeRule(double x,double y,double w,double h);
/*:261*//*262:*/
#line 4787 "hint.w"

void nativeImage(double x,double y,double w,double h,unsigned char*istart,unsigned char*iend);
/*:262*//*263:*/
#line 4794 "hint.w"

extern void nativeSetRunlength(struct gcache_s*g,unsigned char*g_data);
extern void nativeSetBitmaped(struct gcache_s*g,unsigned char*g_data);
extern void nativeSetTrueType(struct gcache_s*g);
/*:263*//*264:*/
#line 4805 "hint.w"

void nativeFreeGlyph(struct gcache_s*g);
/*:264*/
#line 5598 "hint.w"


#endif
/*:297*/
