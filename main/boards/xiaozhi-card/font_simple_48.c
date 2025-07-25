/*******************************************************************************
 * Size: 48 px
 * Bpp: 4
 * Opts: --bpp 4 --size 48 --no-compress --font AlibabaPuHuiTi-3-55-Regular.ttf --range 49,50,51,52,53,54 --format lvgl -o simple_48.c
 ******************************************************************************/


#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef SIMPLE_48
#define SIMPLE_48 1
#endif

#if SIMPLE_48

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0031 "1" */
    0x0, 0x0, 0x0, 0x25, 0x8c, 0xff, 0xf6, 0x1,
    0x47, 0xbe, 0xff, 0xff, 0xff, 0xf6, 0x2f, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf6, 0x2f, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xf6, 0x2f, 0xff, 0xeb, 0x85,
    0x2e, 0xff, 0xf6, 0x18, 0x51, 0x0, 0x0, 0xe,
    0xff, 0xf6, 0x0, 0x0, 0x0, 0x0, 0xe, 0xff,
    0xf6, 0x0, 0x0, 0x0, 0x0, 0xe, 0xff, 0xf6,
    0x0, 0x0, 0x0, 0x0, 0xe, 0xff, 0xf6, 0x0,
    0x0, 0x0, 0x0, 0xe, 0xff, 0xf6, 0x0, 0x0,
    0x0, 0x0, 0xe, 0xff, 0xf6, 0x0, 0x0, 0x0,
    0x0, 0xe, 0xff, 0xf6, 0x0, 0x0, 0x0, 0x0,
    0xe, 0xff, 0xf6, 0x0, 0x0, 0x0, 0x0, 0xe,
    0xff, 0xf6, 0x0, 0x0, 0x0, 0x0, 0xe, 0xff,
    0xf6, 0x0, 0x0, 0x0, 0x0, 0xe, 0xff, 0xf6,
    0x0, 0x0, 0x0, 0x0, 0xe, 0xff, 0xf6, 0x0,
    0x0, 0x0, 0x0, 0xe, 0xff, 0xf6, 0x0, 0x0,
    0x0, 0x0, 0xe, 0xff, 0xf6, 0x0, 0x0, 0x0,
    0x0, 0xe, 0xff, 0xf6, 0x0, 0x0, 0x0, 0x0,
    0xe, 0xff, 0xf6, 0x0, 0x0, 0x0, 0x0, 0xe,
    0xff, 0xf6, 0x0, 0x0, 0x0, 0x0, 0xe, 0xff,
    0xf6, 0x0, 0x0, 0x0, 0x0, 0xe, 0xff, 0xf6,
    0x0, 0x0, 0x0, 0x0, 0xe, 0xff, 0xf6, 0x0,
    0x0, 0x0, 0x0, 0xe, 0xff, 0xf6, 0x0, 0x0,
    0x0, 0x0, 0xe, 0xff, 0xf6, 0x0, 0x0, 0x0,
    0x0, 0xe, 0xff, 0xf6, 0x0, 0x0, 0x0, 0x0,
    0xe, 0xff, 0xf6, 0x0, 0x0, 0x0, 0x0, 0xe,
    0xff, 0xf6, 0x0, 0x0, 0x0, 0x0, 0xe, 0xff,
    0xf6, 0x0, 0x0, 0x0, 0x0, 0xe, 0xff, 0xf6,
    0x0, 0x0, 0x0, 0x0, 0xe, 0xff, 0xf6, 0x0,
    0x0, 0x0, 0x0, 0xe, 0xff, 0xf6,

    /* U+0032 "2" */
    0x0, 0x4, 0x79, 0xcd, 0xef, 0xff, 0xec, 0x94,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xfe, 0x60, 0x0, 0x0, 0x0,
    0xf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xa0, 0x0, 0x0, 0x0, 0xff, 0xfe, 0xcc, 0xbb,
    0xde, 0xff, 0xff, 0xff, 0x90, 0x0, 0x0, 0x6,
    0x30, 0x0, 0x0, 0x0, 0x2, 0xaf, 0xff, 0xff,
    0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x6f, 0xff, 0xfa, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x9f, 0xff, 0xe0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x2, 0xff, 0xff, 0x20, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xe, 0xff, 0xf3, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xdf, 0xff, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xd, 0xff, 0xf4, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff,
    0xff, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x3f, 0xff, 0xf0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0xff, 0xfb,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x1, 0xef, 0xff, 0x50, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x9f, 0xff, 0xe0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4f,
    0xff, 0xf5, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x2e, 0xff, 0xfb, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x1d, 0xff, 0xfe,
    0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x1d, 0xff, 0xff, 0x30, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x1c, 0xff, 0xff, 0x40, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1d, 0xff,
    0xff, 0x50, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x2d, 0xff, 0xff, 0x40, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x3e, 0xff, 0xfe, 0x30,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x5f,
    0xff, 0xfd, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x7f, 0xff, 0xfc, 0x10, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xaf, 0xff, 0xfa,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1,
    0xcf, 0xff, 0xf7, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x4, 0xef, 0xff, 0xe4, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xff, 0xff,
    0xc1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x4f, 0xff, 0xfd, 0xbb, 0xbb, 0xbb, 0xbb,
    0xbb, 0xbb, 0xbb, 0xbb, 0x74, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfa,
    0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xa4, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfa,

    /* U+0033 "3" */
    0x0, 0x26, 0x9c, 0xdf, 0xff, 0xed, 0xb8, 0x30,
    0x0, 0x0, 0x0, 0x1f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xd5, 0x0, 0x0, 0x1, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0x0, 0x0,
    0x1f, 0xff, 0xdb, 0xaa, 0xab, 0xdf, 0xff, 0xff,
    0xf7, 0x0, 0x0, 0x52, 0x0, 0x0, 0x0, 0x0,
    0x17, 0xff, 0xff, 0xf1, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x3, 0xff, 0xff, 0x60, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x9, 0xff,
    0xfa, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x4f, 0xff, 0xb0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x3, 0xff, 0xfc, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4f, 0xff,
    0xb0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xa, 0xff, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x4, 0xff, 0xff, 0x20, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x7, 0xff, 0xff, 0x90,
    0x0, 0x0, 0x0, 0x0, 0x1, 0x25, 0x9e, 0xff,
    0xff, 0x90, 0x0, 0x0, 0x0, 0xaf, 0xff, 0xff,
    0xff, 0xff, 0xfd, 0x40, 0x0, 0x0, 0x0, 0xa,
    0xff, 0xff, 0xff, 0xff, 0xf5, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xaf, 0xff, 0xff, 0xff, 0xff, 0xfd,
    0x70, 0x0, 0x0, 0x0, 0x3, 0x66, 0x67, 0x8a,
    0xdf, 0xff, 0xff, 0xd2, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x18, 0xff, 0xff, 0xe1, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0xef,
    0xff, 0xa0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x4, 0xff, 0xff, 0x10, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xd, 0xff, 0xf5, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x9f,
    0xff, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x8, 0xff, 0xf9, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x8f, 0xff, 0x90, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa, 0xff,
    0xf8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xef, 0xff, 0x60, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x7f, 0xff, 0xf1, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x6f, 0xff, 0xfb,
    0x4, 0x41, 0x0, 0x0, 0x0, 0x0, 0x5, 0xbf,
    0xff, 0xff, 0x30, 0xaf, 0xfe, 0xdc, 0xba, 0xbb,
    0xdf, 0xff, 0xff, 0xff, 0x60, 0xa, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x60, 0x0,
    0xaf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfa,
    0x20, 0x0, 0x4, 0x8a, 0xce, 0xef, 0xff, 0xed,
    0xb8, 0x50, 0x0, 0x0, 0x0,

    /* U+0034 "4" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2f,
    0xff, 0xff, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xc, 0xff, 0xff, 0xf7, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7,
    0xff, 0xff, 0xff, 0x70, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x3, 0xff, 0xff, 0xff, 0xf7,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xdf, 0xff, 0xdf, 0xff, 0x70, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x8f, 0xff, 0x79, 0xff,
    0xf7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x4f, 0xff, 0xc0, 0x9f, 0xff, 0x70, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x1e, 0xff, 0xf2, 0x9,
    0xff, 0xf7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xa, 0xff, 0xf7, 0x0, 0x9f, 0xff, 0x70, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x5, 0xff, 0xfc, 0x0,
    0x9, 0xff, 0xf7, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x1, 0xef, 0xff, 0x20, 0x0, 0x9f, 0xff, 0x70,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xbf, 0xff, 0x60,
    0x0, 0x9, 0xff, 0xf7, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x6f, 0xff, 0xb0, 0x0, 0x0, 0x9f, 0xff,
    0x70, 0x0, 0x0, 0x0, 0x0, 0x2f, 0xff, 0xf2,
    0x0, 0x0, 0x9, 0xff, 0xf7, 0x0, 0x0, 0x0,
    0x0, 0xc, 0xff, 0xf6, 0x0, 0x0, 0x0, 0x9f,
    0xff, 0x70, 0x0, 0x0, 0x0, 0x8, 0xff, 0xfb,
    0x0, 0x0, 0x0, 0x9, 0xff, 0xf7, 0x0, 0x0,
    0x0, 0x3, 0xff, 0xfe, 0x10, 0x0, 0x0, 0x0,
    0x9f, 0xff, 0x70, 0x0, 0x0, 0x0, 0xdf, 0xff,
    0x50, 0x0, 0x0, 0x0, 0x9, 0xff, 0xf7, 0x0,
    0x0, 0x0, 0x9f, 0xff, 0xb0, 0x0, 0x0, 0x0,
    0x0, 0x9f, 0xff, 0x70, 0x0, 0x0, 0x4f, 0xff,
    0xe1, 0x0, 0x0, 0x0, 0x0, 0x9, 0xff, 0xf7,
    0x0, 0x0, 0x1e, 0xff, 0xf5, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x9f, 0xff, 0x70, 0x0, 0x5, 0xff,
    0xfa, 0x0, 0x0, 0x0, 0x0, 0x0, 0x9, 0xff,
    0xf7, 0x0, 0x0, 0x5f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x65,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xf6, 0x5f, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x63, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb,
    0xbe, 0xff, 0xfd, 0xbb, 0xb4, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x9f, 0xff, 0x70,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x9, 0xff, 0xf7, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x9f, 0xff,
    0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x9, 0xff, 0xf7, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x9f,
    0xff, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x9, 0xff, 0xf7, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x9f, 0xff, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x9, 0xff, 0xf7, 0x0,
    0x0,

    /* U+0035 "5" */
    0x0, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0x0, 0x0, 0xb, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xf0, 0x0, 0x0, 0xdf, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0,
    0xf, 0xff, 0xfd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd,
    0xd0, 0x0, 0x2, 0xff, 0xfa, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x4f, 0xff, 0x70,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6,
    0xff, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x9f, 0xff, 0x20, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xb, 0xff, 0xf0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xdf,
    0xfd, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xf, 0xff, 0xa0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x2, 0xff, 0xf7, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4f, 0xff,
    0xdd, 0xef, 0xfe, 0xdb, 0x84, 0x0, 0x0, 0x0,
    0x6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
    0x80, 0x0, 0x0, 0x8f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xd3, 0x0, 0xb, 0xeb, 0x97,
    0x65, 0x66, 0x8b, 0xef, 0xff, 0xff, 0xe2, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4d, 0xff,
    0xff, 0xd0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xa, 0xff, 0xff, 0x50, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xd, 0xff, 0xfb, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6f,
    0xff, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x1, 0xff, 0xff, 0x20, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xf, 0xff, 0xf3, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xdf,
    0xff, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xe, 0xff, 0xf3, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0x10, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xff,
    0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x9, 0xff, 0xfb, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x3, 0xff, 0xff, 0x60, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x4, 0xff, 0xff, 0xe0,
    0x5, 0x30, 0x0, 0x0, 0x0, 0x0, 0x4a, 0xff,
    0xff, 0xf5, 0x0, 0xef, 0xfd, 0xcb, 0xab, 0xbd,
    0xff, 0xff, 0xff, 0xf7, 0x0, 0xe, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf6, 0x0, 0x0,
    0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x91,
    0x0, 0x0, 0x5, 0x9b, 0xde, 0xff, 0xfe, 0xdb,
    0x85, 0x0, 0x0, 0x0, 0x0,

    /* U+0036 "6" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x37, 0xac,
    0xef, 0x90, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x7, 0xdf, 0xff, 0xff, 0xf9, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x6e, 0xff, 0xff, 0xff, 0xff,
    0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0xbf, 0xff,
    0xff, 0xff, 0xfd, 0xc6, 0x0, 0x0, 0x0, 0x0,
    0x1, 0xdf, 0xff, 0xff, 0xc7, 0x30, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xcf, 0xff, 0xfc, 0x30,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x9f,
    0xff, 0xf7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x3f, 0xff, 0xf5, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xc, 0xff, 0xf7,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x3, 0xff, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xaf, 0xff, 0x30, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf,
    0xff, 0xd0, 0x0, 0x3, 0x45, 0x53, 0x0, 0x0,
    0x0, 0x0, 0x4, 0xff, 0xf8, 0x2, 0x9e, 0xff,
    0xff, 0xff, 0xc5, 0x0, 0x0, 0x0, 0x8f, 0xff,
    0x58, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x10,
    0x0, 0xb, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xfe, 0x20, 0x0, 0xef, 0xff, 0xff,
    0xfa, 0x52, 0x0, 0x15, 0xcf, 0xff, 0xfc, 0x0,
    0xf, 0xff, 0xff, 0xe3, 0x0, 0x0, 0x0, 0x0,
    0x8f, 0xff, 0xf6, 0x1, 0xff, 0xff, 0xf2, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x9f, 0xff, 0xd0, 0x3f,
    0xff, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1,
    0xff, 0xff, 0x23, 0xff, 0xff, 0x20, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xb, 0xff, 0xf5, 0x4f, 0xff,
    0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f,
    0xff, 0x73, 0xff, 0xfe, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x6, 0xff, 0xf8, 0x3f, 0xff, 0xe0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x5f, 0xff,
    0x92, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x6, 0xff, 0xf8, 0xf, 0xff, 0xf1, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xff, 0x70,
    0xdf, 0xff, 0x50, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xa, 0xff, 0xf5, 0x9, 0xff, 0xfa, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0x10, 0x4f,
    0xff, 0xf2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f,
    0xff, 0xc0, 0x0, 0xdf, 0xff, 0xd1, 0x0, 0x0,
    0x0, 0x0, 0x4f, 0xff, 0xf5, 0x0, 0x4, 0xff,
    0xff, 0xe5, 0x0, 0x0, 0x1, 0x8f, 0xff, 0xfc,
    0x0, 0x0, 0x9, 0xff, 0xff, 0xff, 0xcb, 0xbd,
    0xff, 0xff, 0xff, 0x20, 0x0, 0x0, 0xa, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x30, 0x0,
    0x0, 0x0, 0x6, 0xef, 0xff, 0xff, 0xff, 0xff,
    0xfa, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x59,
    0xde, 0xff, 0xdb, 0x72, 0x0, 0x0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 442, .box_w = 14, .box_h = 34, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 442, .box_w = 23, .box_h = 34, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 629, .adv_w = 442, .box_w = 21, .box_h = 34, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 986, .adv_w = 442, .box_w = 25, .box_h = 34, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1411, .adv_w = 442, .box_w = 21, .box_h = 34, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 1768, .adv_w = 442, .box_w = 23, .box_h = 34, .ofs_x = 2, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 49, .range_length = 6, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t font_simple_48 = {
#else
lv_font_t font_simple_48 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 34,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -4,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if SIMPLE_48*/

