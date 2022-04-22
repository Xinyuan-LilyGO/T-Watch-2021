#ifndef _PAGE_TYPE_H_
#define _PAGE_TYPE_H_

#include <libraries/lvgl/lvgl.h>
#include "TWatch_hal.h"

#define FONT_12 lv_font_montserrat_12
#define FONT_14 lv_font_montserrat_14
#define FONT_16 lv_font_montserrat_16
#define FONT_20 lv_font_montserrat_20

extern lv_style_t Borderless_style;
extern lv_style_t icon_64_style;
extern lv_style_t Initial_screen_style;

LV_IMG_DECLARE(img_src_bg_cat);

void Page_Style_Init(void);

#endif /* _PAGE_TYPE_H_ */