#ifndef _PAGE_MAIN_MENU_H_
#define _PAGE_MAIN_MENU_H_

#include "./libraries/lvgl/lvgl.h"
#include "Page_type.h"
#include "Page_Watchface.h"
#include "Page_Application.h"

void Menu_init(lv_obj_t *screen);
void Menu_hide(bool en);
void Menu_loop(void);
void Menu_create();
bool isMenuHide();

#endif /* _PAGE_MAIN_MENU_H_ */