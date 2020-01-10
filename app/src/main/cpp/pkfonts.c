/* this file reads pk font files and provides functions to 
   extract font and glyph information 
   Read: Thomas Rokicki, Packed (PK) Font File Firmat, TUGboat, Volume 6 (1985), No. 3
   The code from lese-pk.c of the dviforwindows viewer was helpfull when writing this code.
*/

#include "basetypes.h"
#include "hformat.h"
#include "htex.h"
#include "hget.h"
#include "error.h"
#include "fonts.h"
#include "rendergl.h"



/* primitive operations */
#define read_1_byte() (data[i++])
#define read_2_byte() (k=read_1_byte(),k=k<<8,k=k+data[i++],k)
#define read_3_byte() (k=read_2_byte(),k=k<<8,k=k+data[i++],k)
#define read_4_byte() (k=read_3_byte(),k=k<<8,k=k+data[i++],k)


void pkunpack_glyph(gcache_t *g)
/* unpack the data in the glyph into its internal representation */
{
    int i, k;
    unsigned char *data;
    if (g == NULL || g->pk.data == NULL) return; /* no glyph, no data */
    g->ff = pk_format;
    if (g->bits != NULL) return; /* already unpacked */

    //MESSAGE("Unpacking glyph %c (0x%x)",g->cc,g->cc);

    data = g->pk.data;
    i = 0;
    if ((g->pk.flag & 7) < 4)  /* short form */
    {
        i = i + 3; /* the TeX font metrics */
        i = i + 1; /*escapement: g->dy=0; g->dx=read_1_byte(); g->dx= g->dx<<16; */
        g->w = read_1_byte();
        g->h = read_1_byte();
        g->hoff = (signed char) read_1_byte();
        g->voff = (signed char) read_1_byte();
    } else if ((g->pk.flag & 7) < 7) /* extended short form */
    {
        i = i + 3; /* the TeX font metrics */
        i = i + 2; /*escapement: g->dy=0; g->dx=read_2_byte(); g->dx= g->dx<<16; */
        g->w = read_2_byte();
        g->h = read_2_byte();
        g->hoff = (signed short int) read_2_byte();
        g->voff = (signed short int) read_2_byte();
    } else /* long form */
    {
        i = i + 4; /* the TeX font metrics */
        i = i + 8; /*escapement: g->dx=read_4_byte();g->dy=read_4_byte();*/
        g->w = read_4_byte();
        g->h = read_4_byte();
        g->hoff = (signed int) read_4_byte();
        g->voff = (signed int) read_4_byte();
    }
    if ((g->pk.flag >> 4) == 14) nativeSetBitmaped(g, data + i);
    else nativeSetRunlength(g, data + i);
    //MESSAGE("Unpacked glyph %c (0x%x) w=%d h=%d hoff=%d voff=%d",g->cc,g->cc, g->w, g->h, g-> hoff, g->voff);
}

void stb_unpack_glyph (gcache_t *g){
    /* unpack the data in the glyph into its internal representation */
    /* data is stored as bitmap, just return bitmap */
    unsigned char *data;
    if (g == NULL || g->pk.data == NULL) return; /* no glyph, no data */
    data = g->tt.data;
    nativeSetBitmaped(g, data);
}

/* opcodes of pk files */
#define pk_xxx1 240
#define pk_xxx2 241
#define pk_xxx3 242
#define pk_xxx4 243
#define pk_yyy  244
#define pk_post 245
#define pk_no_op 246
#define pk_pre   247
#define pk_id    89


int unpack_pkfile(font_t *pk)
/* scan pk->data and extract information. Do not unpack glyphs, these are unpacked on demand */
{
    int i, j;
    unsigned int k;
    unsigned char flag;
    unsigned char *data;
    data = pk->data;
    i = 0;
    while (i < pk->size)
        switch (flag = data[i++]) {
            case pk_xxx1:
                j = read_1_byte();
                i = i + j;
                break;
            case pk_xxx2:
                j = read_2_byte();
                i = i + j;
                break;
            case pk_xxx3:
                j = read_3_byte();
                i = i + j;
                break;
            case pk_xxx4:
                j = read_4_byte();
                i = i + j;
                break;
            case pk_yyy:
                i = i + 4;
                break;
            case pk_no_op:
                break;
            case pk_pre: {
                int csize;
                pk->pk.id = read_1_byte();
                if (pk->pk.id != pk_id) return 0;
                csize = read_1_byte();
                pk->pk.comment = pk->data + i;
                i = i + csize;
                pk->ds = read_4_byte() / (double) (1 << 20);
                pk->pk.cs = read_4_byte();
                pk->hppp = read_4_byte() / (double) (1 << 16);
                pk->vppp = read_4_byte() / (double) (1 << 16);
                /* pk->comment[csize]=0;  data is RO! after reading the data insert zero byte to terminate comment */
            }
                break;
            case pk_post:
                break;
            case 248:
            case 249:
            case 250:
            case 251:
            case 252:
            case 253:
            case 254:
            case 255:
                break; /* undefined */
            default: /* the character codes */
            {
                unsigned int pl;
                unsigned int cc;
                gcache_t *g;
                if ((flag & 7) == 7) /* long form */
                {
                    pl = read_4_byte();
                    cc = read_4_byte();
                } else if ((flag & 4) == 4) /* extended short form */
                {
                    pl = read_2_byte();
                    cc = read_1_byte();
                    pl = pl + ((flag & 3) << 16);
                } else /* short form */
                {
                    pl = read_1_byte();
                    cc = read_1_byte();
                    pl = pl + ((flag & 3) << 8);
                }
                g = hnew_glyph(pk, cc);
                g->pk.flag = flag;
                g->pk.data = data + i;
                g->bits = NULL;
                i = i + pl;
            }
                break;
        }
    return 1;
}

#if 0

unsigned char test_data[] ={
/*	See: Thomas Rokicki, Packed (PK) Font File Firmat, TUGboat, Volume 6 (1985), No. 3 */
    0x88, // Flag Byte
    0x1A, // Packet length
    0x04, // char code
    0x09, 0xc7, 0x1C, // tfm width
    0x19, // horiz. escapement
    0x14, // width
    0x1D, // height
    0xFE, // h offset
    0x1C, // v offset
    0xD9, 0xE2, 0x97, // Raster Data
    0x2B, 0x1E, 0x22,
    0x93, 0x24, 0xE3,
    0x97, 0x4E, 0x22,
    0x93, 0x2C, 0x5E,
    0x22, 0x97, 0xD9 };

#endif

