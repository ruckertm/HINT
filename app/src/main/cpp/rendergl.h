#ifndef RENDERNATIVE_H
#define RENDERNATIVE_H



void nativeInit();
/* initialize the renderer */

void nativeSetSize(int px_h, int px_v, double dpi);
/* set the size of the drawing aerea in pixel and the resolution in dots (pixel) per inch */

void nativeSetColors(double fr, double fg, double fb, double br, double bg, double bb);
/* set foreground and background colors as rgb values in the range 0 to 255 */

void setLightMode();
void setDarkMode();

void nativeBlank();
/* renders an empty page */

/* Dimensions
   If not otherwise stated, all dimensions are given as double values in point
   72.27 pt = 1 inch
   1 inch = 2.54 cm
*/

void nativeGlyph(double x, double y, double w, double h, gcache_t *g);
/* render the glyph g at position x,y with width w and height h. */


void nativeRule(double x, double y, double w, double h);
/* render a black rectangle at position x,y with width w and height h. */

void nativeImage(double x, double y, double w, double h, unsigned char *istart, unsigned char *iend);
/* Render an image at position x,y with width w and height h. 
   The image data is found in memory from istart to (but not including) iend.
*/
void nativeFreeGlyph(gcache_t *g);
/* Free resources associated with g. */


/* Extracting glyphs from font files */

/* PK fonts */
 
void nativeSetRunlength(gcache_t *g, unsigned char *data);
/* Extract a runlength encoded glyph */

void nativeSetBitmaped(gcache_t *g, unsigned char *data);
/* Extract a bitmap encoded glyph */


/* Type 1 fonts (PFA and PFB) */


/* TrueType fonts */

/* OpenType fonts */

#endif /* RENDERNATIVE_H */
