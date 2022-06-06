#ifndef __INPUT_H__
#define __INPUT_H__

#include "./XYWatch_hal.h"


typedef TFT_eSPI SCREEN_CLASS;

void lv_port_disp_init(SCREEN_CLASS *scr);
void lv_port_indev_init(void);
void lv_fs_if_init(void);

#endif