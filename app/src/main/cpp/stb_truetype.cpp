#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h" /* http://nothings.org/stb/stb_truetype.h */


#define pixel_height 100

//
// Created by gsocher on 10.01.2020.
//stb_truetype is a public domain C truetype rasterization library
//Following the example: https://github.com/justinmeiners/stb-truetype-example
//

extern "C" {
#include "hfonts.h"
#include "basetypes.h"
#include <stdlib.h>
#include "error.h"
}

//#include "rendergl.h"

extern "C" void stb_unpack_glyph(gcache_t *g, font_t *fp, unsigned int cc) {

    g->bits = stbtt_GetCodepointBitmap(fp->tt, 0,
                                       stbtt_ScaleForPixelHeight(fp->tt, pixel_height), cc,
                                       (int *) &g->w,
                                       (int *) &g->h, 0, 0);
    //GLtexture(g);

}

extern "C" bool stb_unpack_font(font_t *fp) {
    fp->tt = (stbtt_fontinfo *) calloc(1, sizeof(stbtt_fontinfo));
    if (fp->tt == NULL) {
        QUIT("out of memory");
    }
    if (stbtt_InitFont(fp->tt, fp->data, 0)) {
        fp->ff = tt_format;
        return true;
    }
    return false;
}




