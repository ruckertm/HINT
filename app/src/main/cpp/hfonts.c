/*332:*/
#line 6421 ".\\hint.w"

#include "basetypes.h"
#include "error.h"
#include "hformat.h"
#include "hint.h"
#include "hget.h"
#include <ft2build.h> 
#include FT_FREETYPE_H
#include "hfonts.h"
#include "hrender.h"
#include "rendernative.h"

/*264:*/
#line 4566 ".\\hint.w"

static font_t*fonts[0x100]= {NULL};
/*:264*//*271:*/
#line 4700 ".\\hint.w"

static gcache_t g_undefined= {0};
/*:271*//*305:*/
#line 5823 ".\\hint.w"

static FT_Library ft_library= NULL;
/*:305*/
#line 6433 ".\\hint.w"


/*270:*/
#line 4657 ".\\hint.w"

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
/*:270*//*272:*/
#line 4704 ".\\hint.w"

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


static gcache_t*hnew_glyph(font_t*f,unsigned int cc)
{if(cc<G0_SIZE)return hnew_g0(&(f->g0),cc);
else if(cc<G123_SIZE*G0_SIZE)return hnew_g1(&(f->g1),cc);
else if(cc<G123_SIZE*G123_SIZE*G0_SIZE)return hnew_g2(&(f->g2),cc);
else if(cc<G123_SIZE*G123_SIZE*G123_SIZE*G0_SIZE)return hnew_g3(&(f->g3),cc);
else return&g_undefined;
}
/*:272*/
#line 6435 ".\\hint.w"


/*309:*/
#line 5857 ".\\hint.w"


int unpack_ft_file(font_t*f)
{int e;
/*306:*/
#line 5827 ".\\hint.w"

if(ft_library==NULL)
{int e= FT_Init_FreeType(&ft_library);
if(e)QUIT("Unable to initialize the FreeType library");
}
/*:306*/
#line 5861 ".\\hint.w"

f->hpxs= f->vpxs= 72.27/600.0;
e= FT_New_Memory_Face(ft_library,
f->font_data,f->data_size,0,&(f->tt.face));
if(e)return 0;
/*310:*/
#line 5881 ".\\hint.w"

e= FT_Select_Charmap(f->tt.face,FT_ENCODING_ADOBE_CUSTOM);
if(e)LOG("Unable to select custom encoding for font %d\n",f->n);
/*:310*/
#line 5866 ".\\hint.w"

/*311:*/
#line 5889 ".\\hint.w"

e= FT_Set_Char_Size(
f->tt.face,
0,
(FT_F26Dot6)(0.5+(f->s*64.0*72.0/72.27)),
72.27/f->hpxs,
72.27/f->vpxs);
if(e)QUIT("Unable to set FreeType glyph size");
FT_Set_Transform(f->tt.face,0,0);
/*:311*/
#line 5867 ".\\hint.w"

f->ff= ft_format;
return 1;
}
/*:309*//*312:*/
#line 5912 ".\\hint.w"

static void ft_unpack_glyph(font_t*f,gcache_t*g,uint32_t cc)
{int e,i;

i= FT_Get_Char_Index(f->tt.face,cc);
e= FT_Load_Glyph(
f->tt.face,
i,
FT_LOAD_RENDER|FT_LOAD_TARGET_NORMAL);
if(e)QUIT("Unable to render FreeType glyph %c (%u)",(char)cc,cc);

g->w= f->tt.face->glyph->bitmap.width;
g->h= f->tt.face->glyph->bitmap.rows;
g->hoff= -f->tt.face->glyph->bitmap_left;
g->voff= f->tt.face->glyph->bitmap_top-1;
g->bits= calloc(g->w*g->h,1);
if(g->bits==NULL)QUIT("Out of memory for FreeType glyph %c (%u)",(char)cc,cc);
memcpy(g->bits,f->tt.face->glyph->bitmap.buffer,g->w*g->h);

g->ff= ft_format;
nativeSetFreeType(g);
}

/*:312*/
#line 6437 ".\\hint.w"


/*297:*/
#line 5528 ".\\hint.w"

#define PK_READ_1_BYTE() (data[i++])
#define PK_READ_2_BYTE() (k= PK_READ_1_BYTE(),k= k<<8,k= k+data[i++],k)
#define PK_READ_3_BYTE() (k= PK_READ_2_BYTE(),k= k<<8,k= k+data[i++],k)
#define PK_READ_4_BYTE() (k= PK_READ_3_BYTE(),k= k<<8,k= k+data[i++],k)
/*:297*//*299:*/
#line 5555 ".\\hint.w"

#define read_nybble(P) ((P).j&1?((P).data[(P).j++>>1]&0xF):(((P).data[(P).j++>>1]>>4)&0xF))
/*:299*//*300:*/
#line 5581 ".\\hint.w"

static int packed_number(pk_parse_t*p)
{int i,k;
i= read_nybble(*p);
if(i==0)
{do{k= read_nybble(*p);i++;}while(k==0);
while(i--> 0)k= k*16+read_nybble(*p);
return k-15+(13-p->f)*16+p->f;
}
else if(i<=p->f)return i;
else if(i<14)return(i-p->f-1)*16+read_nybble(*p)+p->f+1;
else
{if(i==14)p->r= packed_number(p);
else p->r= 1;
return packed_number(p);
}
}
/*:300*//*301:*/
#line 5610 ".\\hint.w"

static void pk_runlength(gcache_t*g,unsigned char*data){
pk_parse_t p;
int x,y;
unsigned char*bits;
int n;
unsigned char gray;
bits= g->bits= (unsigned char*)calloc(g->w*g->h,1);
if(bits==NULL){g->w= g->h= 0;return;}
p.j= 0;
p.r= 0;
p.f= g->pk.flag>>4;
p.data= data;
n= 0;
if((g->pk.flag>>3)&1)gray= 0x00;
else gray= 0xff;
y= 0;
while(y<g->h){
x= 0;
while(x<(int)g->w)
{int d;
if(n<=0){
n= packed_number(&p);
gray= ~gray;
}
d= g->w-x;
if(d> n)d= n;
for(;d> 0;d--,x++,n--)
bits[y*g->w+x]= gray;
}
y++;
while(p.r> 0&&y<g->h)
{int k;
for(k= 0;k<g->w;k++)
bits[y*g->w+k]= bits[(y-1)*g->w+k];
p.r--;
y++;
}
}
}
/*:301*//*302:*/
#line 5662 ".\\hint.w"

static void pk_bitmap(gcache_t*g,unsigned char*data){
unsigned char*bits;
int x,y;
unsigned char mask;

g->bits= bits= (unsigned char*)calloc(g->w*g->h,1);
if(bits==NULL){g->w= g->h= 0;return;}
mask= 0x80;
for(y= 0;y<g->h;y++)
for(x= 0;x<g->w;x++)
{if(*data&mask)
bits[y*g->w+x]= 0x00;
else
bits[y*g->w+x]= 0xFF;
mask= mask>>1;
if(mask==0){data++;mask= 0x80;}
}
}
/*:302*//*303:*/
#line 5685 ".\\hint.w"


static void pkunpack_glyph(gcache_t*g)
{int i,k;
unsigned char*data;
if(g==NULL||g->pk.encoding==NULL)return;
g->ff= pk_format;
if(g->bits!=NULL)return;
#if 0
DBG(DBGRENDER,"Unpacking glyph %c (0x%x)",g->cc,g->cc);
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
if((g->pk.flag>>4)==14)pk_bitmap(g,data+i);
else pk_runlength(g,data+i);
nativeSetPK(g);
}
/*:303*//*304:*/
#line 5730 ".\\hint.w"


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


int unpack_pk_file(font_t*pk)

{int i,j;
unsigned int k;
unsigned char flag;
unsigned char*data;
data= pk->font_data;
i= 0;
while(i<pk->data_size)
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
pk->pk.ds= PK_READ_4_BYTE()/(double)(1<<20);
pk->pk.cs= PK_READ_4_BYTE();
pk->hpxs= (double)(1<<16)/PK_READ_4_BYTE();
pk->vpxs= (double)(1<<16)/PK_READ_4_BYTE();
if(pk->pk.ds!=pk->s)
{double m= pk->s/pk->pk.ds;
pk->hpxs*= m;
pk->vpxs*= m;
}
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

/*:304*/
#line 6439 ".\\hint.w"


/*265:*/
#line 4573 ".\\hint.w"

struct font_s*hget_font(unsigned char f)
{font_t*fp;
if(fonts[f]!=NULL)return fonts[f];
DBG(DBGFONT,"Decoding new font %d\n",f);
if(f> max_ref[font_kind])
QUIT("Undefined font %d\n",f);
fp= calloc(1,sizeof(*fp));
if(fp==NULL)
QUIT("Out of memory for font %d",f);
else
{unsigned char*spos,*sstart,*send;
spos= hpos;sstart= hstart;send= hend;
fp->n= f;
hget_section(hglyph_section(f));
fp->font_data= hstart;
fp->data_size= hend-hstart;
hpos= spos;hstart= sstart;hend= send;
}
fp->s= font_at_size(f)/(double)(1<<16);
/*294:*/
#line 5465 ".\\hint.w"

if(fp->font_data[0]==0xF7&&fp->font_data[1]==0x59)
{fp->ff= pk_format;
if(!unpack_pk_file(fp)){free(fp);fp= NULL;}
}
/*:294*//*313:*/
#line 5939 ".\\hint.w"

else if(unpack_ft_file(fp))
fp->ff= ft_format;
else
{QUIT("Font format not supported for font %d\n",fp->n);
free(fp);fp= NULL;
}
/*:313*/
#line 4593 ".\\hint.w"

fonts[f]= fp;
return fonts[f];
}
/*:265*//*267:*/
#line 4611 ".\\hint.w"

static void hfree_glyph_cache(font_t*f,bool rm);

void hint_clear_fonts(bool rm)
{int f;
DBG(DBGFONT,rm?"Clear font data":"Clear native glyph data");
for(f= 0;f<=max_ref[font_kind];f++)
if(fonts[f]!=NULL)
{hfree_glyph_cache(fonts[f],rm);
if(rm){free(fonts[f]);fonts[f]= NULL;}
}
}
/*:267*//*273:*/
#line 4768 ".\\hint.w"

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
/*:273*//*275:*/
#line 4897 ".\\hint.w"

gcache_t*hget_glyph(font_t*f,unsigned int cc)
{
gcache_t*g= NULL;
g= g_lookup(f,cc);
if(g==NULL)
{if(f->ff==ft_format)
g= hnew_glyph(f,cc);
else
return NULL;
}
if(g->ff==no_format)
{if(f->ff==pk_format)pkunpack_glyph(g);
else if(f->ff==ft_format)ft_unpack_glyph(f,g,cc);
else QUIT("Font format not supported");
}
return g;
}
/*:275*//*277:*/
#line 4929 ".\\hint.w"

void render_char(int x,int y,struct font_s*f,uint32_t cc, bool searched)

{double w,h,dx,dy;
gcache_t*g= hget_glyph(f,cc);
if(g==NULL)return;

g->searched = searched;

dx= (double)g->hoff*f->hpxs;
dy= (double)g->voff*f->vpxs;
w= (double)g->w*f->hpxs;
h= (double)g->h*f->vpxs;

nativeGlyph(SP2PT(x)-dx,SP2PT(y)-dy,w,h,g);
}

/*:277*/
#line 6441 ".\\hint.w"


/*:332*/
