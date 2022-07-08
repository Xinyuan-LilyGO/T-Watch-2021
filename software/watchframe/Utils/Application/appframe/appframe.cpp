#include "appframe.h"
/*
You need to add it in two more places
1:Add the header file path to the utils.h file
2:Register the app in Pagemanager.cpp
 */

LV_IMG_DECLARE(img_icon_by_appframe)
static lv_obj_t *_screen = nullptr;

void app_frame_init(lv_obj_t *screen)
{
    _screen = screen;
}

void app_frame_loop(lv_obj_t *screen, void *user_data)
{
}

void app_frame_exit()
{
}

struct App_item_t app_frame =
    {
        .init = app_frame_init,
        .loop = app_frame_loop,
        .exit = app_frame_exit,
        .icon = img_icon_by_appframe,
        .name = nullptr,
        .user_data = NULL,
};