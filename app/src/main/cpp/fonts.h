#ifndef FONTS_H
#define FONTS_H

/* HINT does support the following font formats:
TeX PK Fonts, TrueType Fonts PostScript Type 1 Fonts, OpenType Fonts
The decoding routines depend in some way on the format used for the cached glyphs 
*/

typedef enum {
    no_format, pk_format, tt_format, t1_format, ot_format,
} font_format;


/* Some information in a glyph is dependent on the font type */
typedef struct {
    unsigned char *data; /* pointer to the pk file buffer where the character data starts, if the character is defined */
    unsigned char flag; /* encoding in the pk file */
} pkglyph;

typedef struct {
    unsigned char *data;
} ttglyph;

typedef struct {
    int dummy;
} t1glyph;

typedef struct {
    int dummy;
} otglyph;

/* Glyphs will be rendered on demand and cached in a form suitable for fast rendering
   depending on the OS and its rendering engine. 
   The dependency on the OS is resolved at compile time using #ifdef
*/

typedef struct {
    unsigned int w, h; /* width and height of the minimum bounding box in pixel */
    int hoff, voff; /* horizontal and vertical offset in pixel from the upper left pixel to the reference pixel (right and down are positive) */
#ifdef WIN32   /* Compiled on WIN32 */
    unsigned char *bits;  /* if the character is decoded, pointer to a windows DIBits, otherwise NULL */
#else
#ifdef __ANDROID__ /* Compiled for Android and OpenEGL 2.0 */
    unsigned char *bits;  /* if the character is decoded, pointer to a bitmap, otherwise NULL */
    unsigned int GLtexture; /* OpenGL texture id */
#endif
#endif
    font_format ff; /* the type of font described in the following union */
    union {
        pkglyph pk;
        ttglyph tt;
        t1glyph t1;
        otglyph ot;
    };
} gcache_t;


/* Some information in a font is dependent on the font type */
typedef struct {
    unsigned char id; /* the id currently always 89 */
    unsigned char *comment; /* usually the program that made the pk font */
    unsigned int cs; /* checksum */
    unsigned char flag; /* encoding in the pk file */
} pkfont;

typedef struct {
    int dummy;
} ttfont;

typedef struct {
    int dummy;
} t1font;
typedef struct {
    int dummy;
} otfont;

/* Some data is available for all fonts, as follows. */

typedef struct {
    unsigned char *data; /* the glyph data in the HINT file */
    int size; /* the size of the glyph data in byte */
    double ds; /* design size in pt */
    double hppp, vppp; /* horizontal and vertical pixel per point */
    /* glyphs are stored in one of 4 trees. The order and depth of the trees reflects UTF-8 encoding.
     The first tree is of oder 0x80 and only 1 level deep. Its root is g0
     The other trees, g1, g2, and g3 are of order 0x40 and have a depth
     of 2, 3, and 4 levels respectively */
    gcache_t **g0; /* codes 0 to 0x7F */
    gcache_t ***g1; /*codes 0x40 to 0x40*0x40 */
    gcache_t ****g2; /*codes =0x40*0x40 to 0x40*0x40*0x40 */
    gcache_t *****g3; /*codes 0x40*0x40*0x40 to 0x40*0x40*0x40*0x40 */
    font_format ff; /* the type of font described in the following union */
    union {
        pkfont pk;
        ttfont tt;
        t1font t1;
        otfont ot;
    };
} font_t;

/* The font interface */
typedef font_t *font_ptr;

extern font_ptr hget_font(unsigned char f);

extern void hclear_fonts(void);

extern gcache_t *hget_glyph(font_ptr f, unsigned int cc);

extern gcache_t *hnew_glyph(font_ptr f, unsigned int cc);

extern void pkunpack_glyph(gcache_t *g);

extern void stb_unpack_glyph(gcache_t *g);

/* unpack the data in the glyph into its internal representation */
extern int unpack_pkfile(font_t *pk);
/* scan pk->data and extract information. Do not unpack glyphs, these are unpacked on demand */
#endif //FONTS_H
