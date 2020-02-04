/*303:*/
#line 5791 "hint.w"

#include "basetypes.h"
#include "error.h"
#include "hformat.h"
#include "hint.h"
/*279:*/
#line 5368 "hint.w"

#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_STATIC
#include "stb_truetype.h"
/*:279*/
#line 5796 "hint.w"

#include "hfonts.h"
#include "hrender.h"
#include "rendernative.h"

/*245:*/
#line 4339 "hint.w"

static font_t*fonts[0x100]= {NULL};
/*:245*//*252:*/
#line 4465 "hint.w"

static gcache_t g_undefined= {0};
/*:252*/
#line 5801 "hint.w"


/*281:*/
#line 5392 "hint.w"

int unpack_ttfile(font_t*f)
{
if(!stbtt_InitFont(&(f->tt),f->font_data,0))
return 0;
f->ds= font_at_size(f->n)/(double)(1<<16);
f->hppp= f->vppp= 600.0/72.27;
f->ff= tt_format;
return 1;
}


static void ttunpack_glyph(font_t*f,gcache_t*g,uint32_t cc)
{float em= f->hppp*f->ds;
float scale;
scale= stbtt_ScaleForMappingEmToPixels(&(f->tt),em);
g->bits= stbtt_GetCodepointBitmap(&(f->tt),scale,scale,cc,&(g->w),&(g->h),&(g->hoff),&(g->voff));
g->ff= tt_format;
nativeSetTrueType(g);
}

/*:281*/
#line 5803 "hint.w"


/*278:*/
#line 5230 "hint.w"


#define PK_READ_1_BYTE() (data[i++])
#define PK_READ_2_BYTE() (k= PK_READ_1_BYTE(),k= k<<8,k= k+data[i++],k)
#define PK_READ_3_BYTE() (k= PK_READ_2_BYTE(),k= k<<8,k= k+data[i++],k)
#define PK_READ_4_BYTE() (k= PK_READ_3_BYTE(),k= k<<8,k= k+data[i++],k)



static void pkunpack_glyph(gcache_t*g)

{int i,k;
unsigned char*data;
if(g==NULL||g->pk.encoding==NULL)return;
g->ff= pk_format;
if(g->bits!=NULL)return;
#if 0
MESSAGE("Unpacking glyph %c (0x%x)",g->cc,g->cc);
#endif
data= g->pk.encoding;
i= 0;
if((g->pk.flag&7)<4)
{i= i+3;
i= i+1;
g->w= PK_READ_1_BYTE();
g->h= PK_READ_1_BYTE();
g->hoff= (signed char)PK_READ_1_BYTE();
g->voff= (signed char)PK_READ_1_BYTE();
}
else if((g->pk.flag&7)<7)
{i= i+3;
i= i+2;
g->w= PK_READ_2_BYTE();
g->h= PK_READ_2_BYTE();
g->hoff= (signed short int)PK_READ_2_BYTE();
g->voff= (signed short int)PK_READ_2_BYTE();
}
else
{i= i+4;
i= i+8;
g->w= PK_READ_4_BYTE();
g->h= PK_READ_4_BYTE();
g->hoff= (signed int)PK_READ_4_BYTE();
g->voff= (signed int)PK_READ_4_BYTE();
}
if((g->pk.flag>>4)==14)nativeSetBitmaped(g,data+i);
else nativeSetRunlength(g,data+i);
#if 0
MESSAGE("Unpacked glyph %c (0x%x) w=%d h=%d hoff=%d voff=%d",g->cc,g->cc,g->w,g->h,g->hoff,g->voff);
#endif
}

static gcache_t*hnew_glyph(font_t*pk,unsigned int cc);



#define PK_XXX1 240
#define PK_XXX2 241
#define PK_XXX3 242
#define PK_XXX4 243
#define PK_YYY  244
#define PK_POST 245
#define PK_NO_OP 246
#define PK_PRE   247
#define PK_ID    89


int unpack_pkfile(font_t*pk)

{int i,j;
unsigned int k;
unsigned char flag;
unsigned char*data;
data= pk->font_data;
i= 0;
while(i<pk->size)
switch(flag= data[i++])
{case PK_XXX1:j= PK_READ_1_BYTE();i= i+j;break;
case PK_XXX2:j= PK_READ_2_BYTE();i= i+j;break;
case PK_XXX3:j= PK_READ_3_BYTE();i= i+j;break;
case PK_XXX4:j= PK_READ_4_BYTE();i= i+j;break;
case PK_YYY:i= i+4;break;
case PK_NO_OP:break;
case PK_PRE:
{int csize;
pk->pk.id= PK_READ_1_BYTE();
if(pk->pk.id!=PK_ID)return 0;
csize= PK_READ_1_BYTE();
pk->pk.pk_comment= pk->font_data+i;
i= i+csize;
pk->ds= PK_READ_4_BYTE()/(double)(1<<20);
pk->pk.cs= PK_READ_4_BYTE();
pk->hppp= PK_READ_4_BYTE()/(double)(1<<16);
pk->vppp= PK_READ_4_BYTE()/(double)(1<<16);
#if 0    
pk->comment[csize]= 0;
#endif
}
break;
case PK_POST:break;
case 248:case 249:case 250:case 251:case 252:case 253:case 254:case 255:break;
default:
{
unsigned int pl;
unsigned int cc;
gcache_t*g;
if((flag&7)==7)
{pl= PK_READ_4_BYTE();
cc= PK_READ_4_BYTE();
}else if((flag&4)==4)
{pl= PK_READ_2_BYTE();
cc= PK_READ_1_BYTE();
pl= pl+((flag&3)<<16);
}else
{pl= PK_READ_1_BYTE();
cc= PK_READ_1_BYTE();
pl= pl+((flag&3)<<8);
}
g= hnew_glyph(pk,cc);
g->pk.flag= flag;
g->pk.encoding= data+i;
g->bits= NULL;
i= i+pl;
}
break;
}
return 1;
}

/*:278*/
#line 5805 "hint.w"


/*246:*/
#line 4346 "hint.w"

struct font_s*hget_font(unsigned char f)
{font_t*fp;
if(fonts[f]!=NULL)return fonts[f];
fp= calloc(1,sizeof(*fp));
if(fp==NULL)
QUIT("Out of memory for font %d",f);
else
{unsigned char*spos,*sstart,*send;
spos= hpos;sstart= hstart;send= hend;
fp->n= f;
hget_section(hglyph_section(f));
fp->size= hend-hstart;
fp->font_data= hstart;
hpos= spos;hstart= sstart;hend= send;
}
/*275:*/
#line 5200 "hint.w"

if(fp->font_data[0]==0xF7&&fp->font_data[1]==0x59)
{fp->ff= pk_format;
if(!unpack_pkfile(fp)){free(fp);fp= NULL;}
}
/*:275*//*282:*/
#line 5417 "hint.w"

else if(unpack_ttfile(fp))
fp->ff= tt_format;
else
{QUIT("Font format not supported for font %d\n",fp->n);
free(fp);fp= NULL;
}
/*:282*/
#line 4362 "hint.w"

fonts[f]= fp;
return fonts[f];
}
/*:246*//*248:*/
#line 4377 "hint.w"

static void hfree_glyph_cache(font_t*f,bool rm);

void hint_clear_fonts(bool rm)
{int f;
for(f= 0;f<=max_ref[font_kind];f++)
if(fonts[f]!=NULL)
{hfree_glyph_cache(fonts[f],rm);
if(rm){free(fonts[f]);fonts[f]= NULL;}
}
}
/*:248*//*251:*/
#line 4422 "hint.w"

#define G0_BITS 7
#define G0_SIZE (1<<G0_BITS)
#define G0_MASK (G0_SIZE-1)
#define G123_BITS 6
#define G123_SIZE (1<<G123_BITS)
#define G123_MASK (G123_SIZE-1)

static gcache_t*g_lookup(font_t*f,unsigned int cc)

{if(cc>>G0_BITS){
unsigned int cc1= (cc>>G0_BITS);
if(cc1>>G123_BITS){
unsigned int cc2= cc1>>G123_BITS;
if(cc2>>G123_BITS){
unsigned int cc3= cc2>>G123_BITS;
if(cc3>>G123_BITS)return NULL;
else if(f->g3&&
f->g3[cc3&G123_MASK]&&
f->g3[cc3&G123_MASK][cc2&G123_MASK]&&
f->g3[cc3&G123_MASK][cc2&G123_MASK][cc1&G123_MASK])
return f->g3[cc3&G123_MASK][cc2&G123_MASK][cc1&G123_MASK][cc&G0_MASK];
}
else if(f->g2&&f->g2[cc2&G123_MASK]&&f->g2[cc2&G123_MASK][cc1&G123_MASK])
return f->g2[cc2&G123_MASK][cc1&G123_MASK][cc&G0_MASK];
}
else if(f->g1&&f->g1[cc1&G123_MASK])
return f->g1[cc1&G123_MASK][cc&G0_MASK];
}
else if(f->g0)
return f->g0[cc];
return NULL;
}
/*:251*//*253:*/
#line 4469 "hint.w"

static gcache_t*hnew_g(gcache_t**g)
{if(*g==NULL)
*g= calloc(1,sizeof(gcache_t));
if(*g==NULL)
return&g_undefined;
(*g)->ff= no_format;
return*g;
}

static gcache_t*hnew_g0(gcache_t***g,unsigned int cc)
{unsigned int cc0= cc&G0_MASK;
if(*g==NULL)
*g= calloc(G0_SIZE,sizeof(gcache_t*));
if(*g==NULL)
return&g_undefined;
return hnew_g((*g)+cc0);
}

static gcache_t*hnew_g1(gcache_t****g,unsigned int cc)
{unsigned int cc1= (cc>>G0_BITS)&G123_MASK;
if(*g==NULL)
*g= calloc(G123_SIZE,sizeof(gcache_t**));
if(*g==NULL)
return&g_undefined;
return hnew_g0((*g)+cc1,cc);
}
static gcache_t*hnew_g2(gcache_t*****g,unsigned int cc)
{unsigned int cc2= (cc>>(G123_BITS+G0_BITS))&G123_MASK;
if(*g==NULL)
*g= calloc(G123_SIZE,sizeof(gcache_t***));
if(*g==NULL)
return&g_undefined;
return hnew_g1((*g)+cc2,cc);
}

static gcache_t*hnew_g3(gcache_t******g,unsigned int cc)
{unsigned int cc3= (cc>>(G123_BITS+G123_BITS+G0_BITS))&G123_MASK;
if(*g==NULL)
*g= calloc(G123_SIZE,sizeof(gcache_t****));
if(*g==NULL)
return&g_undefined;
return hnew_g2((*g)+cc3,cc);
}


static gcache_t*hnew_glyph(font_t*pk,unsigned int cc)
{if(cc<G0_SIZE)return hnew_g0(&(pk->g0),cc);
else if(cc<G123_SIZE*G0_SIZE)return hnew_g1(&(pk->g1),cc);
else if(cc<G123_SIZE*G123_SIZE*G0_SIZE)return hnew_g2(&(pk->g2),cc);
else if(cc<G123_SIZE*G123_SIZE*G123_SIZE*G0_SIZE)return hnew_g3(&(pk->g3),cc);
else return&g_undefined;
}
/*:253*//*254:*/
#line 4528 "hint.w"

static void hfree_g0(struct gcache_s**g,bool rm)
{int i;
if(g==NULL)return;
for(i= 0;i<G0_SIZE;i++)
if(g[i]!=NULL)
{nativeFreeGlyph(g[i]);
if(rm){
if(g[i]->bits!=NULL)free(g[i]->bits);
free(g[i]);g[i]= NULL;}
}
}

static void hfree_g1(struct gcache_s***g,bool rm)
{int i;
if(g==NULL)return;
for(i= 0;i<G123_SIZE;i++)
if(g[i]!=NULL)
{hfree_g0(g[i],rm);
if(rm){free(g[i]);g[i]= NULL;}
}
}

static void hfree_g2(struct gcache_s****g,bool rm)
{int i;
if(g==NULL)return;
for(i= 0;i<G123_SIZE;i++)
if(g[i]!=NULL)
{hfree_g1(g[i],rm);
if(rm){free(g[i]);g[i]= NULL;}
}
}


static void hfree_g3(struct gcache_s*****g,bool rm)
{int i;
if(g==NULL)return;
for(i= 0;i<G123_SIZE;i++)
if(g[i]!=NULL)
{hfree_g2(g[i],rm);
if(rm){free(g[i]);g[i]= NULL;}
}
}


static void hfree_glyph_cache(font_t*f,bool rm)
{if(f->g0!=NULL)
{hfree_g0(f->g0,rm);
if(rm){free(f->g0);f->g0= NULL;}
}
if(f->g1!=NULL)
{hfree_g1(f->g1,rm);
if(rm){free(f->g1);f->g1= NULL;}
}
if(f->g2!=NULL)
{hfree_g2(f->g2,rm);
if(rm){free(f->g2);f->g2= NULL;}
}
if(f->g3!=NULL)
{hfree_g3(f->g3,rm);
if(rm){free(f->g3);f->g3= NULL;}
}
}
/*:254*//*256:*/
#line 4646 "hint.w"

gcache_t*hget_glyph(font_t*fp,unsigned int cc)
{
gcache_t*g= NULL;
g= g_lookup(fp,cc);
if(g==NULL)
{if(fp->ff==tt_format)
g= hnew_glyph(fp,cc);
else
return NULL;
}
if(g->ff==no_format)
{if(fp->ff==pk_format)pkunpack_glyph(g);
else if(fp->ff==tt_format)ttunpack_glyph(fp,g,cc);
else
QUIT("tt t1 and ot formats not yet supported");
}
return g;
}
/*:256*//*257:*/
#line 4670 "hint.w"

void render_char(int x,int y,struct font_s*f,int32_t s,uint32_t cc)

{double w,h,dx,dy,m;
gcache_t*g= hget_glyph(f,cc);
if(g==NULL)return;

if(s==0)m= 1.0;
else m= ((double)s/(double)(1<<16))/f->ds;
dx= ((double)g->hoff/f->hppp)*m;
dy= ((double)g->voff/f->vppp)*m;
w= ((double)g->w/f->hppp)*m;
h= ((double)g->h/f->vppp)*m;

nativeGlyph(SP2PT(x)-dx,SP2PT(y)-dy,w,h,g);
}

/*:257*/
#line 5807 "hint.w"


/*:303*/
