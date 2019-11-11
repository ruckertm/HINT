/* This files contains the functions and intrefaces common to all font formats 
*/

#include "basetypes.h"
#include "hformat.h"
#include "htex.h"
#include "hget.h"
#include "error.h"
#include "fonts.h"
#include "rendernative.h"

/* Handling the glyph cache of a font */
static gcache_t g_undefined ={0}; /* if a glyph is undefined it can point to this glyph. */
#define G0_BITS 7
#define G0_SIZE (1<<G0_BITS)
#define G0_MASK (G0_SIZE-1)
#define G123_BITS 6
#define G123_SIZE (1<<G123_BITS)
#define G123_MASK (G123_SIZE-1)
 
static gcache_t *g_lookup(font_t *pk, unsigned int cc)
/* given a font and a charactercode return a pointer to the glyph or NULL */
{ if (cc >> G0_BITS) {
	unsigned int cc1= (cc>>G0_BITS);
	if (cc1>>G123_BITS) {
		unsigned int cc2= cc1>>G123_BITS;
		if (cc2>>G123_BITS) {
			unsigned int cc3=cc2>>G123_BITS;
			if (cc3>>G123_BITS) return NULL;
			else if (pk->g3 && 
				pk->g3[cc3&G123_MASK] && 
				pk->g3[cc3&G123_MASK][cc2&G123_MASK] &&  
				pk->g3[cc3&G123_MASK][cc2&G123_MASK][cc1&G123_MASK])  
			return pk->g3[cc3&G123_MASK][cc2&G123_MASK][cc1&G123_MASK][cc&G0_MASK];
		}
		else if (pk->g2 && pk->g2[cc2&G123_MASK] && pk->g2[cc2&G123_MASK][cc1&G123_MASK]) 
			return pk->g2[cc2&G123_MASK][cc1&G123_MASK][cc&G0_MASK];
	}
	else if (pk->g1 && pk->g1[cc1&G123_MASK]) 
		return pk->g1[cc1&G123_MASK][cc&G0_MASK];
  }
  else if (pk->g0) 
	  return pk->g0[cc];
  return NULL;
}

/* Allocating new entries in the glyph cache */
static gcache_t *hnew_g(gcache_t **g)
{ if (*g==NULL)
    *g=calloc(1, sizeof(gcache_t));
  if (*g==NULL) 
    return &g_undefined;
  (*g)->ff=no_format;
  return *g;
}

static gcache_t *hnew_g0(gcache_t ***g,unsigned int cc)
{ unsigned int cc0=cc&G0_MASK;
  if (*g==NULL)
    *g=calloc(G0_SIZE, sizeof(gcache_t*));
  if (*g==NULL) 
    return &g_undefined;
  return hnew_g((*g)+cc0);
}
 
static gcache_t *hnew_g1(gcache_t ****g,unsigned int cc)
{ unsigned int cc1=(cc>>G0_BITS)&G123_MASK;
  if (*g==NULL)
    *g=calloc(G123_SIZE, sizeof(gcache_t**));
  if (*g==NULL) 
    return &g_undefined;
  return hnew_g0((*g)+cc1,cc);
}
static gcache_t *hnew_g2(gcache_t *****g,unsigned int cc)
{ unsigned int cc2=(cc>>(G123_BITS+G0_BITS))&G123_MASK;
  if (*g==NULL)
    *g=calloc(G123_SIZE, sizeof(gcache_t***));
  if (*g==NULL) 
    return &g_undefined;
  return hnew_g1((*g)+cc2,cc);
}
  
static gcache_t *hnew_g3(gcache_t ******g,unsigned int cc)
{ unsigned int cc3=(cc>>(G123_BITS+G123_BITS+G0_BITS))&G123_MASK;
  if (*g==NULL)
    *g=calloc(G123_SIZE, sizeof(gcache_t****));
  if (*g==NULL) 
    return &g_undefined;
  return hnew_g2((*g)+cc3,cc);
}


gcache_t *hnew_glyph(font_t *pk, unsigned int cc)
/* given a font and a charactercode return a pointer to the glyph
   allocate a glyph if none is yet allocated.
   Return a pointer to the undefined glyph if no more memory is available
*/
{ if (cc<G0_SIZE) return hnew_g0(&(pk->g0),cc);
  else if (cc<G123_SIZE*G0_SIZE) return hnew_g1(&(pk->g1),cc);
  else if (cc<G123_SIZE*G123_SIZE*G0_SIZE) return hnew_g2(&(pk->g2),cc);
  else if (cc<G123_SIZE*G123_SIZE*G123_SIZE*G0_SIZE) return hnew_g3(&(pk->g3),cc);
  else return &g_undefined;
}

/* Deallocating entries in the glyph cache */

static void hfree_g0(gcache_t **g)
{ int i;
  if (g==NULL) return;
  for (i=0;i<G0_SIZE;i++)
    if (g[i]!=NULL)
	{ nativeFreeGlyph(g[i]);
      free(g[i]);
      g[i]=NULL;
    }
}

static void hfree_g1(gcache_t ***g)
{ int i;
  if (g==NULL) return;
  for (i=0;i<G123_SIZE;i++)
	if (g[i]!=NULL)
	{ hfree_g0(g[i]);
	  free(g[i]);
          g[i]=NULL;
	}
}

static void hfree_g2(gcache_t ****g)
{ int i;
  if (g==NULL) return;
  for (i=0;i<G123_SIZE;i++)
	if (g[i]!=NULL)
	{ hfree_g1(g[i]);
	  free(g[i]);
          g[i]=NULL;
	}
}


static void hfree_g3(gcache_t *****g)
{ int i;
  if (g==NULL) return;
  for (i=0;i<G123_SIZE;i++)
	if (g[i]!=NULL)
	{ hfree_g2(g[i]);
	  free(g[i]);
          g[i]=NULL;
	}
}


static void hfree_glyphs(font_t *pk)
{ if (pk->g0!=NULL)
  { hfree_g0(pk->g0);
    free(pk->g0);
    pk->g0=NULL;
  }
  if (pk->g1!=NULL)
  { hfree_g1(pk->g1);
    free(pk->g1);
    pk->g1=NULL;
  }
  if (pk->g2!=NULL)
  { hfree_g2(pk->g2);
    free(pk->g2);
    pk->g2=NULL;
  }
  if (pk->g3!=NULL)
  { hfree_g3(pk->g3);
    free(pk->g3);
    pk->g3=NULL;
  }
}





gcache_t *hget_glyph(font_t *fp, unsigned int cc)
{
  gcache_t *g=g_lookup(fp,cc);
  
  if (g==NULL) return NULL;

  if (g->ff==no_format) 	  
  { if (fp->ff==pk_format) pkunpack_glyph(g);
    else
		QUIT("tt t1 and ot formats not yet supported");
  }
  return g;
}


static font_t *fonts[0x100]={NULL}; /* fonts 0 to 255 */

font_t *hget_font(unsigned char f)
{ font_t *fp;
  if (fonts[f]!=NULL) return fonts[f];
  fp = calloc(1,sizeof(*fp));
  if (fp==NULL) 
    QUIT("Out of memory for font %d",f);
  else
  { unsigned char *spos, *sstart, *send;
    spos=hpos; sstart=hstart;send=hend;
    hget_section(font_def[f].q);
    fp->size=hend-hstart;
    fp->data=hstart;
    hpos=spos; hstart=sstart;hend=send;
  }
  /* Determine the font format and unpack the font*/
  if (fp->data[0]==0xF7 &&  fp->data[1]==0x59)
  { fp->ff=pk_format;
    if (!unpack_pkfile(fp)) { free(fp); fp=NULL; }
  }
  else 
	QUIT("tt, t1, ot fonts not yet implemented");
  fonts[f]=fp;
  return fonts[f];
}



void hclear_fonts(void)
/* remove all fonts from memory */
{ int f;
  for (f=0;f<0x100;f++)
    if (fonts[f]!=NULL)
    { hfree_glyphs(fonts[f]);
	  free(fonts[f]);
	  fonts[f]=NULL;
    }
}

