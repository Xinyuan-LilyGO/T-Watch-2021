#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
#include "lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_IMG_FOOT_WHITE
#define LV_ATTRIBUTE_IMG_IMG_FOOT_WHITE
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_IMG_FOOT_WHITE uint8_t img_foot_white_map[] = {
#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8
  /*Pixel format: Blue: 2 bit, Green: 3 bit, Red: 3 bit, Alpha 8 bit */
  0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0x92, 0x37, 0xdb, 0xef, 0xff, 0xff, 0xdb, 0xef, 0x92, 0x30, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xdb, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0xec, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0x92, 0x6b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb6, 0x7c, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xb7, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0xd4, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xdb, 0xd0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0xef, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0x92, 0x4b, 0xb6, 0xa7, 0x92, 0x5c, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xb7, 0xb4, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x92, 0x0f, 0xff, 0x00, 0xff, 0x00, 0xb6, 0x74, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb6, 0x8f, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0x92, 0x47, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x92, 0x0c, 0xff, 0x00, 0x92, 0x0c, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf4, 0x92, 0x18, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xdb, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0xf0, 0xff, 0x00, 0xff, 0x00, 0xb6, 0x9b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb6, 0xa7, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xb6, 0xa3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0xdb, 0xff, 0x00, 0xff, 0x00, 0xdb, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb7, 0xcb, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0x92, 0x17, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xfc, 0xdb, 0xe0, 0x92, 0x57, 0xff, 0x00, 0xff, 0x00, 0xdb, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0xd0, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0x92, 0x67, 0xb6, 0x87, 0x92, 0x47, 0xb6, 0x73, 0xb6, 0x80, 0xff, 0x00, 0xff, 0x00, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb7, 0xab, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xb7, 0xb8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x92, 0x17, 0xff, 0x00, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x92, 0x30, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb6, 0x94, 0xff, 0x00, 0xdb, 0xe4, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0xd8, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xb7, 0xbb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb7, 0xaf, 0xff, 0x00, 0xb7, 0xbc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb6, 0x87, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0x92, 0x1f, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xfc, 0x92, 0x30, 0xff, 0x00, 0x92, 0x20, 0xb6, 0x74, 0xb7, 0xcc, 0xff, 0xff, 0xdb, 0xf0, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0x92, 0x2f, 0xb7, 0xab, 0x92, 0x50, 0xff, 0x00, 0xff, 0x00, 0xb7, 0xc7, 0xdb, 0xdb, 0xb6, 0x87, 0x92, 0x43, 0x92, 0x27, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0x92, 0x54, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x92, 0x07, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xb7, 0xa8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xb6, 0x8b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb6, 0xa3, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xdb, 0xe0, 0xff, 0xff, 0xdb, 0xd3, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0
  /*Pixel format: Blue: 5 bit, Green: 6 bit, Red: 5 bit, Alpha 8 bit*/
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x31, 0x8c, 0x37, 0x7a, 0xd6, 0xef, 0xff, 0xff, 0xff, 0x79, 0xce, 0xef, 0x31, 0x8c, 0x30, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x18, 0xc6, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x59, 0xce, 0xec, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x92, 0x94, 0x6b, 0x9e, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb3, 0x9c, 0x7c, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0xad, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb7, 0xbd, 0xd4, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x96, 0xb5, 0xd0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x79, 0xce, 0xef, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x71, 0x8c, 0x4b, 0x14, 0xa5, 0xa7, 0x92, 0x94, 0x5c, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x35, 0xad, 0xb4, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xde, 0xf8, 0x10, 0x84, 0x0f, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xb2, 0x94, 0x74, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd3, 0x9c, 0x8f, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x51, 0x8c, 0x47, 0x3c, 0xe7, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0xde, 0xf8, 0x10, 0x84, 0x0c, 0xff, 0xff, 0x00, 0x10, 0x84, 0x0c, 0xfc, 0xe6, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9a, 0xd6, 0xf4, 0x31, 0x8c, 0x18, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xf8, 0xc5, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7a, 0xd6, 0xf0, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xf3, 0x9c, 0x9b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x14, 0xa5, 0xa7, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x14, 0xa5, 0xa3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd7, 0xbd, 0xdb, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xd7, 0xbd, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x96, 0xb5, 0xcb, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x10, 0x84, 0x17, 0x3d, 0xef, 0xfb, 0xff, 0xff, 0xff, 0x3d, 0xef, 0xfc, 0xf8, 0xc5, 0xe0, 0x72, 0x94, 0x57, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x7a, 0xd6, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x96, 0xb5, 0xd0, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x92, 0x94, 0x67, 0xd3, 0x9c, 0x87, 0x51, 0x8c, 0x47, 0x92, 0x94, 0x73, 0xb3, 0x9c, 0x80, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xbb, 0xde, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x14, 0xa5, 0xab, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x35, 0xad, 0xb8, 0x7e, 0xf7, 0xff, 0xff, 0xff, 0xff, 0x7e, 0xf7, 0xff, 0x31, 0x8c, 0x17, 0xff, 0xff, 0x00, 0x9a, 0xd6, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xde, 0xf8, 0x51, 0x8c, 0x30, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xfc, 0xe6, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0x9c, 0x94, 0xff, 0xff, 0x00, 0x18, 0xc6, 0xe4, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd7, 0xbd, 0xd8, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0xad, 0xbb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x34, 0xa5, 0xaf, 0xff, 0xff, 0x00, 0x55, 0xad, 0xbc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd3, 0x9c, 0x87, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x30, 0x84, 0x1f, 0xfb, 0xde, 0xf8, 0xff, 0xff, 0xff, 0x5d, 0xef, 0xfc, 0x51, 0x8c, 0x30, 0xff, 0xff, 0x00, 0x30, 0x84, 0x20, 0xb2, 0x94, 0x74, 0x96, 0xb5, 0xcc, 0x9e, 0xf7, 0xff, 0x7a, 0xd6, 0xf0, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x31, 0x8c, 0x2f, 0x14, 0xa5, 0xab, 0x71, 0x8c, 0x50, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x76, 0xb5, 0xc7, 0xd7, 0xbd, 0xdb, 0xb3, 0x9c, 0x87, 0x51, 0x8c, 0x43, 0x31, 0x8c, 0x27, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x71, 0x8c, 0x54, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xde, 0xf8, 0x10, 0x84, 0x07, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x14, 0xa5, 0xa8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0xde, 0xf7, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xd3, 0x9c, 0x8b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x14, 0xa5, 0xa3, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xf8, 0xc5, 0xe0, 0xff, 0xff, 0xff, 0xb6, 0xb5, 0xd3, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format:  Blue: 5 bit Green: 6 bit, Red: 5 bit, Alpha 8 bit  BUT the 2  color bytes are swapped*/
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x8c, 0x31, 0x37, 0xd6, 0x7a, 0xef, 0xff, 0xff, 0xff, 0xce, 0x79, 0xef, 0x8c, 0x31, 0x30, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xc6, 0x18, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0xec, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x94, 0x92, 0x6b, 0xf7, 0x9e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9c, 0xb3, 0x7c, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xad, 0x55, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbd, 0xb7, 0xd4, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xb5, 0x96, 0xd0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x79, 0xef, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x8c, 0x71, 0x4b, 0xa5, 0x14, 0xa7, 0x94, 0x92, 0x5c, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xad, 0x35, 0xb4, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xde, 0xfb, 0xf8, 0x84, 0x10, 0x0f, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x94, 0xb2, 0x74, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9c, 0xd3, 0x8f, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x8c, 0x51, 0x47, 0xe7, 0x3c, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xde, 0xdb, 0xf8, 0x84, 0x10, 0x0c, 0xff, 0xff, 0x00, 0x84, 0x10, 0x0c, 0xe6, 0xfc, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd6, 0x9a, 0xf4, 0x8c, 0x31, 0x18, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xc5, 0xf8, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd6, 0x7a, 0xf0, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x9c, 0xf3, 0x9b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa5, 0x14, 0xa7, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xa5, 0x14, 0xa3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbd, 0xd7, 0xdb, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xbd, 0xd7, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb5, 0x96, 0xcb, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x84, 0x10, 0x17, 0xef, 0x3d, 0xfb, 0xff, 0xff, 0xff, 0xef, 0x3d, 0xfc, 0xc5, 0xf8, 0xe0, 0x94, 0x72, 0x57, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xd6, 0x7a, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb5, 0x96, 0xd0, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x94, 0x92, 0x67, 0x9c, 0xd3, 0x87, 0x8c, 0x51, 0x47, 0x94, 0x92, 0x73, 0x9c, 0xb3, 0x80, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xde, 0xbb, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa5, 0x14, 0xab, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xad, 0x35, 0xb8, 0xf7, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7e, 0xff, 0x8c, 0x31, 0x17, 0xff, 0xff, 0x00, 0xd6, 0x9a, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xde, 0xfb, 0xf8, 0x8c, 0x51, 0x30, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xe6, 0xfc, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9c, 0xf3, 0x94, 0xff, 0xff, 0x00, 0xc6, 0x18, 0xe4, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbd, 0xd7, 0xd8, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xad, 0x55, 0xbb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa5, 0x34, 0xaf, 0xff, 0xff, 0x00, 0xad, 0x55, 0xbc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9c, 0xd3, 0x87, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x84, 0x30, 0x1f, 0xde, 0xfb, 0xf8, 0xff, 0xff, 0xff, 0xef, 0x5d, 0xfc, 0x8c, 0x51, 0x30, 0xff, 0xff, 0x00, 0x84, 0x30, 0x20, 0x94, 0xb2, 0x74, 0xb5, 0x96, 0xcc, 0xf7, 0x9e, 0xff, 0xd6, 0x7a, 0xf0, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x8c, 0x31, 0x2f, 0xa5, 0x14, 0xab, 0x8c, 0x71, 0x50, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xb5, 0x76, 0xc7, 0xbd, 0xd7, 0xdb, 0x9c, 0xb3, 0x87, 0x8c, 0x51, 0x43, 0x8c, 0x31, 0x27, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x8c, 0x71, 0x54, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xde, 0xfb, 0xf8, 0x84, 0x10, 0x07, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xa5, 0x14, 0xa8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xde, 0xdb, 0xf7, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x9c, 0xd3, 0x8b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa5, 0x14, 0xa3, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xc5, 0xf8, 0xe0, 0xff, 0xff, 0xff, 0xb5, 0xb6, 0xd3, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
#endif
#if LV_COLOR_DEPTH == 32
  /*Pixel format:  Blue: 8 bit, Green: 8 bit, Red: 8 bit, Alpha: 8 bit*/
  0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x86, 0x86, 0x86, 0x37, 0xcd, 0xcd, 0xcd, 0xef, 0xff, 0xff, 0xff, 0xff, 0xcb, 0xcb, 0xcb, 0xef, 0x85, 0x85, 0x85, 0x30, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xbf, 0xbf, 0xbf, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc9, 0xc9, 0xc9, 0xec, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x90, 0x90, 0x90, 0x6b, 0xef, 0xef, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x95, 0x95, 0x95, 0x7c, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xa9, 0xa9, 0xa9, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb5, 0xb5, 0xb5, 0xd4, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xb2, 0xb2, 0xb2, 0xd0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc, 0xcc, 0xcc, 0xef, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x8b, 0x8b, 0x8b, 0x4b, 0xa0, 0xa0, 0xa0, 0xa7, 0x8f, 0x8f, 0x8f, 0x5c, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xa6, 0xa6, 0xa6, 0xb4, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdc, 0xdc, 0xdc, 0xf8, 0x80, 0x80, 0x80, 0x0f, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x93, 0x93, 0x93, 0x74, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x99, 0x99, 0x99, 0x8f, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x8a, 0x8a, 0x8a, 0x47, 0xe3, 0xe3, 0xe3, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xda, 0xda, 0xda, 0xf8, 0x80, 0x80, 0x80, 0x0c, 0xff, 0xff, 0xff, 0x00, 0x80, 0x80, 0x80, 0x0c, 0xde, 0xde, 0xde, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd2, 0xd2, 0xd2, 0xf4, 0x85, 0x85, 0x85, 0x18, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xbe, 0xbe, 0xbe, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcd, 0xcd, 0xcd, 0xf0, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x9c, 0x9c, 0x9c, 0x9b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa0, 0xa0, 0xa0, 0xa7, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x9f, 0x9f, 0x9f, 0xa3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb9, 0xb9, 0xb9, 0xdb, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xb9, 0xb9, 0xb9, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb0, 0xb0, 0xb0, 0xcb, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x80, 0x80, 0x80, 0x17, 0xe5, 0xe5, 0xe5, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xe6, 0xe6, 0xe6, 0xfc, 0xbd, 0xbd, 0xbd, 0xe0, 0x8d, 0x8d, 0x8d, 0x57, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xcd, 0xcd, 0xcd, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb2, 0xb2, 0xb2, 0xd0, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x90, 0x90, 0x90, 0x67, 0x97, 0x97, 0x97, 0x87, 0x8a, 0x8a, 0x8a, 0x47, 0x92, 0x92, 0x92, 0x73, 0x95, 0x95, 0x95, 0x80, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xd6, 0xd6, 0xd6, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa2, 0xa2, 0xa2, 0xab, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xa6, 0xa6, 0xa6, 0xb8, 0xed, 0xed, 0xed, 0xff, 0xff, 0xff, 0xff, 0xff, 0xee, 0xee, 0xee, 0xff, 0x85, 0x85, 0x85, 0x17, 0xff, 0xff, 0xff, 0x00, 0xd1, 0xd1, 0xd1, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdc, 0xdc, 0xdc, 0xf8, 0x87, 0x87, 0x87, 0x30, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xde, 0xde, 0xde, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9b, 0x9b, 0x9b, 0x94, 0xff, 0xff, 0xff, 0x00, 0xc2, 0xc2, 0xc2, 0xe4, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb8, 0xb8, 0xb8, 0xd8, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xa8, 0xa8, 0xa8, 0xbb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa3, 0xa3, 0xa3, 0xaf, 0xff, 0xff, 0xff, 0x00, 0xa9, 0xa9, 0xa9, 0xbc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x97, 0x97, 0x97, 0x87, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x84, 0x84, 0x84, 0x1f, 0xdc, 0xdc, 0xdc, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xe9, 0xe9, 0xe9, 0xfc, 0x87, 0x87, 0x87, 0x30, 0xff, 0xff, 0xff, 0x00, 0x83, 0x83, 0x83, 0x20, 0x93, 0x93, 0x93, 0x74, 0xb0, 0xb0, 0xb0, 0xcc, 0xf1, 0xf1, 0xf1, 0xff, 0xce, 0xce, 0xce, 0xf0, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x85, 0x85, 0x85, 0x2f, 0xa2, 0xa2, 0xa2, 0xab, 0x8c, 0x8c, 0x8c, 0x50, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xae, 0xae, 0xae, 0xc7, 0xb9, 0xb9, 0xb9, 0xdb, 0x96, 0x96, 0x96, 0x87, 0x89, 0x89, 0x89, 0x43, 0x86, 0x86, 0x86, 0x27, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x8c, 0x8c, 0x8c, 0x54, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdc, 0xdc, 0xdc, 0xf8, 0x80, 0x80, 0x80, 0x07, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xa1, 0xa1, 0xa1, 0xa8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd7, 0xd7, 0xd7, 0xf7, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x98, 0x98, 0x98, 0x8b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa0, 0xa0, 0xa0, 0xa3, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xbd, 0xbd, 0xbd, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xb4, 0xb4, 0xb4, 0xd3, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
#endif
};

const lv_img_dsc_t img_foot_white = {
  .header.always_zero = 0,
  .header.w = 20,
  .header.h = 20,
  .data_size = 400 * LV_IMG_PX_SIZE_ALPHA_BYTE,
  .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
  .data = img_foot_white_map,
};
