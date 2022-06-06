/*******************************************************************************
 * Size: 18 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "../lvgl/lvgl.h"
#endif

#ifndef FONT_NIXIE_18
#define FONT_NIXIE_18 1
#endif

#if FONT_NIXIE_18

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0025 "%" */
    0x0, 0x4c, 0x39, 0x86, 0x6d, 0x8d, 0xb0, 0xc4,
    0x18, 0x0, 0x6c, 0x1f, 0x83, 0x4c, 0xc9, 0x98,
    0xc2, 0x18, 0x40, 0x0,

    /* U+002E "." */
    0xf0,

    /* U+0030 "0" */
    0x7d, 0x77, 0x1e, 0x3c, 0x60, 0x0, 0x63, 0xc7,
    0x8e, 0xeb, 0xe0,

    /* U+0031 "1" */
    0x1f, 0xc3, 0xf4,

    /* U+0032 "2" */
    0x7c, 0x74, 0x18, 0x30, 0x67, 0xe, 0x60, 0xc1,
    0x82, 0xe3, 0xe0,

    /* U+0033 "3" */
    0xfc, 0xf4, 0x18, 0x30, 0x6f, 0x1e, 0x3, 0x6,
    0xd, 0xef, 0xe0,

    /* U+0034 "4" */
    0x1, 0x7, 0x1e, 0x3c, 0x67, 0xe, 0x3, 0x6,
    0xc, 0x8, 0x0,

    /* U+0035 "5" */
    0x7d, 0x73, 0x6, 0xc, 0x7, 0xe, 0x3, 0x6,
    0xc, 0xeb, 0xe0,

    /* U+0036 "6" */
    0x7d, 0x73, 0x6, 0xc, 0x7, 0xe, 0x63, 0xc7,
    0x8e, 0xeb, 0xe0,

    /* U+0037 "7" */
    0xfc, 0xf4, 0x18, 0x30, 0x60, 0x40, 0x3, 0x6,
    0xc, 0x18, 0x0,

    /* U+0038 "8" */
    0x7d, 0x77, 0x1e, 0x3c, 0x67, 0xe, 0x63, 0xc7,
    0x8e, 0xeb, 0xe0,

    /* U+0039 "9" */
    0x7d, 0x77, 0x1e, 0x3c, 0x67, 0xe, 0x3, 0x6,
    0xc, 0xeb, 0xe0,

    /* U+0041 "A" */
    0x7d, 0x77, 0x1e, 0x3c, 0x67, 0xe, 0x63, 0xc7,
    0x8f, 0x1c, 0x10,

    /* U+0042 "B" */
    0x79, 0x73, 0x1e, 0x3c, 0x67, 0xe, 0x63, 0xc7,
    0x8e, 0xe3, 0xc0,

    /* U+0043 "C" */
    0x3e, 0x7b, 0x6, 0xc, 0x0, 0x0, 0x60, 0xc1,
    0x80, 0xf1, 0xf0,

    /* U+0044 "D" */
    0x79, 0x73, 0x1e, 0x3c, 0x60, 0x0, 0x63, 0xc7,
    0x8e, 0xe3, 0xc0,

    /* U+0045 "E" */
    0x7e, 0xbc, 0xc0, 0xc0, 0xc0, 0x3c, 0x3c, 0xc0,
    0xc0, 0xc0, 0xbc, 0x7e,

    /* U+0046 "F" */
    0x7e, 0xbc, 0xc0, 0xc0, 0xc0, 0x3c, 0x3c, 0xc0,
    0xc0, 0xc0, 0x80, 0x0,

    /* U+0047 "G" */
    0x3e, 0x7b, 0x6, 0xc, 0x3, 0x6, 0x63, 0xc7,
    0x8c, 0xe1, 0xc0,

    /* U+0048 "H" */
    0x83, 0x8f, 0x1e, 0x3c, 0x67, 0xe, 0x63, 0xc7,
    0x8f, 0x1c, 0x10,

    /* U+0049 "I" */
    0x7f, 0xc3, 0xfd,

    /* U+004A "J" */
    0x1, 0x3, 0x3, 0x3, 0x3, 0x0, 0x1, 0x43,
    0xc3, 0xc3, 0x3c, 0x3c,

    /* U+004B "K" */
    0x8d, 0x9b, 0x67, 0x8e, 0x7, 0xe, 0x63, 0xc7,
    0x8f, 0x1c, 0x10,

    /* U+004C "L" */
    0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0x0, 0x80, 0xc0,
    0xc0, 0xc0, 0xbc, 0x7e,

    /* U+004D "M" */
    0x7e, 0xbd, 0xc3, 0xdb, 0xdb, 0x99, 0x18, 0xc3,
    0xc3, 0xc3, 0xc3, 0x81,

    /* U+004E "N" */
    0xe3, 0xef, 0x7e, 0x7c, 0x60, 0x20, 0xe3, 0xc7,
    0x8e, 0x8, 0x0,

    /* U+004F "O" */
    0x38, 0x73, 0x1e, 0x3c, 0x60, 0x0, 0x63, 0xc7,
    0x8c, 0xe1, 0xc0,

    /* U+0050 "P" */
    0x79, 0x73, 0x1e, 0x3c, 0x67, 0xe, 0x60, 0xc1,
    0x83, 0x4, 0x0,

    /* U+0051 "Q" */
    0x38, 0x73, 0x1e, 0x3c, 0x60, 0x20, 0xe3, 0xcf,
    0x98, 0xf9, 0xb0,

    /* U+0052 "R" */
    0x79, 0x73, 0x1e, 0x3c, 0x67, 0xe, 0x68, 0xd9,
    0xbb, 0x34, 0x30,

    /* U+0053 "S" */
    0x3c, 0x7b, 0x6, 0xc, 0x7, 0xe, 0x3, 0x6,
    0xf, 0xe7, 0xc0,

    /* U+0054 "T" */
    0xff, 0xff, 0x0, 0x18, 0x18, 0x8, 0x0, 0x18,
    0x18, 0x18, 0x18, 0x18,

    /* U+0055 "U" */
    0x83, 0x8f, 0x1e, 0x3c, 0x60, 0x20, 0xe3, 0xc7,
    0x8c, 0xe1, 0xc0,

    /* U+0056 "V" */
    0x83, 0x8f, 0x1e, 0x3c, 0x60, 0x21, 0x66, 0xdd,
    0xb3, 0xc0, 0x0,

    /* U+0057 "W" */
    0x81, 0xc3, 0xc3, 0xc3, 0xc3, 0x18, 0x99, 0xdb,
    0xdb, 0xc3, 0xbd, 0x7e,

    /* U+0058 "X" */
    0x83, 0x8f, 0x1b, 0x62, 0x85, 0xa, 0x14, 0x6d,
    0xcf, 0x1c, 0x10,

    /* U+0059 "Y" */
    0x81, 0xc3, 0xc3, 0xc3, 0xc3, 0x3c, 0x3c, 0x3,
    0x3, 0x3, 0x3c, 0x3c,

    /* U+005A "Z" */
    0x7e, 0xfc, 0x18, 0x30, 0xc1, 0xc, 0x18, 0x60,
    0x81, 0xf3, 0xf0,

    /* U+0061 "a" */
    0x7d, 0x77, 0x1e, 0x3c, 0x67, 0xe, 0x63, 0xc7,
    0x8f, 0x1c, 0x10,

    /* U+0062 "b" */
    0x79, 0x73, 0x1e, 0x3c, 0x67, 0xe, 0x63, 0xc7,
    0x8e, 0xe3, 0xc0,

    /* U+0063 "c" */
    0x3e, 0x7b, 0x6, 0xc, 0x0, 0x0, 0x60, 0xc1,
    0x80, 0xf1, 0xf0,

    /* U+0064 "d" */
    0x79, 0x73, 0x1e, 0x3c, 0x60, 0x0, 0x63, 0xc7,
    0x8e, 0xe3, 0xc0,

    /* U+0065 "e" */
    0x7e, 0xbc, 0xc0, 0xc0, 0xc0, 0x3c, 0x3c, 0xc0,
    0xc0, 0xc0, 0xbc, 0x7e,

    /* U+0066 "f" */
    0x7e, 0xbc, 0xc0, 0xc0, 0xc0, 0x3c, 0x3c, 0xc0,
    0xc0, 0xc0, 0x80, 0x0,

    /* U+0067 "g" */
    0x3e, 0x7b, 0x6, 0xc, 0x3, 0x6, 0x63, 0xc7,
    0x8c, 0xe1, 0xc0,

    /* U+0068 "h" */
    0x83, 0x8f, 0x1e, 0x3c, 0x67, 0xe, 0x63, 0xc7,
    0x8f, 0x1c, 0x10,

    /* U+0069 "i" */
    0x7f, 0xc3, 0xfd,

    /* U+006A "j" */
    0x1, 0x3, 0x3, 0x3, 0x3, 0x0, 0x1, 0x43,
    0xc3, 0xc3, 0x3c, 0x3c,

    /* U+006B "k" */
    0x8d, 0x9b, 0x67, 0x8e, 0x7, 0xe, 0x63, 0xc7,
    0x8f, 0x1c, 0x10,

    /* U+006C "l" */
    0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0x0, 0x80, 0xc0,
    0xc0, 0xc0, 0xbc, 0x7e,

    /* U+006D "m" */
    0x7e, 0xbd, 0xc3, 0xdb, 0xdb, 0x99, 0x18, 0xc3,
    0xc3, 0xc3, 0xc3, 0x81,

    /* U+006E "n" */
    0xe3, 0xef, 0x7e, 0x7c, 0x60, 0x20, 0xe3, 0xc7,
    0x8e, 0x8, 0x0,

    /* U+006F "o" */
    0x38, 0x73, 0x1e, 0x3c, 0x60, 0x0, 0x63, 0xc7,
    0x8c, 0xe1, 0xc0,

    /* U+0070 "p" */
    0x79, 0x73, 0x1e, 0x3c, 0x67, 0xe, 0x60, 0xc1,
    0x83, 0x4, 0x0,

    /* U+0071 "q" */
    0x38, 0x73, 0x1e, 0x3c, 0x60, 0x20, 0xe3, 0xcf,
    0x98, 0xf9, 0xb0,

    /* U+0072 "r" */
    0x79, 0x73, 0x1e, 0x3c, 0x67, 0xe, 0x68, 0xd9,
    0xbb, 0x34, 0x30,

    /* U+0073 "s" */
    0x3c, 0x7b, 0x6, 0xc, 0x7, 0xe, 0x3, 0x6,
    0xf, 0xe7, 0xc0,

    /* U+0074 "t" */
    0xff, 0xff, 0x0, 0x18, 0x18, 0x8, 0x0, 0x18,
    0x18, 0x18, 0x18, 0x18,

    /* U+0075 "u" */
    0x83, 0x8f, 0x1e, 0x3c, 0x60, 0x20, 0xe3, 0xc7,
    0x8c, 0xe1, 0xc0,

    /* U+0076 "v" */
    0x83, 0x8f, 0x1e, 0x3c, 0x60, 0x21, 0x66, 0xdd,
    0xb3, 0xc0, 0x0,

    /* U+0077 "w" */
    0x81, 0xc3, 0xc3, 0xc3, 0xc3, 0x18, 0x99, 0xdb,
    0xdb, 0xc3, 0xbd, 0x7e,

    /* U+0078 "x" */
    0x83, 0x8f, 0x1b, 0x62, 0x85, 0xa, 0x14, 0x6d,
    0xcf, 0x1c, 0x10,

    /* U+0079 "y" */
    0x81, 0xc3, 0xc3, 0xc3, 0xc3, 0x3c, 0x3c, 0x3,
    0x3, 0x3, 0x3c, 0x3c,

    /* U+007A "z" */
    0x7e, 0xfc, 0x18, 0x30, 0xc1, 0xc, 0x18, 0x60,
    0x81, 0xf3, 0xf0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 201, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 20, .adv_w = 52, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 32, .adv_w = 82, .box_w = 2, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 35, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 46, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 57, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 68, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 79, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 101, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 112, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 145, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 156, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 202, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 82, .box_w = 2, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 263, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 274, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 285, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 318, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 329, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 341, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 363, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 386, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 398, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 409, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 420, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 431, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 442, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 453, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 465, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 477, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 488, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 82, .box_w = 2, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 502, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 514, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 525, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 537, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 549, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 560, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 571, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 582, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 593, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 604, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 615, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 627, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 638, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 649, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 661, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 672, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 684, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x9
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 37, .range_length = 10, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 2, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 48, .range_length = 10, .glyph_id_start = 3,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 65, .range_length = 26, .glyph_id_start = 13,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 97, .range_length = 26, .glyph_id_start = 39,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 4,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t font_nixie_18 = {
#else
lv_font_t font_nixie_18 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 14,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if FONT_NIXIE_18*/

