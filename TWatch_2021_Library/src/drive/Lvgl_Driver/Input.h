#ifndef __INPUT_H__
#define __INPUT_H__

#include "./TWatch_hal.h"

#if (TWatch_APP_LVGL == 1)

typedef TFT_eSPI SCREEN_CLASS;
//typedef CST816S TOUCH_CLASS;

void lv_port_disp_init(void *scr);
void lv_port_indev_init(void *indev);
void lv_fs_if_init(void);

#endif

#endif