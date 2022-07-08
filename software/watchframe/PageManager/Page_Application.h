#ifndef _PAGE_APPLICATION_H_
#define _PAGE_APPLICATION_H_

#include "./libraries/lvgl/lvgl.h"
#include "Page_type.h"

const lv_point_t fixed_coord_table[] = {{0,0},\
{50,0},{25,-43},{-25,-43},{-50,0},{-25,43},{25,43},\
{100,0},{75,-43},{50,-86},{0,-86},{-50,-86},{-75,-43},\
{-100,0},{-75,43},{-50,86},{0,86},{50,86},{75,43},\
{150,0},{125,-43},{100,-86},{75,-130},{25,-130},{-25,-130},\
{-75,-130},{-100,-86},{-125,-43},{-150,0},{-125,43},{-100,86},\
{-75,130},{-25,130},{25,130},{75,130},{100,86},{125,43},\
};

typedef void *App_handle;

typedef void (*App_item_init_t)(lv_obj_t *screen);
typedef void (*App_item_loop_t)(lv_obj_t *screen, void *user_data);
typedef void (*App_item_close_t)();

struct App_item_t
{
    App_item_init_t init;
    App_item_loop_t loop;
    App_item_close_t exit;
    lv_img_dsc_t icon;
    char *name;
    void *user_data;
};

void App_Menu_init(lv_obj_t *screen);
void App_Menu_create(void);
void App_Menu_hide(void);

void App_init(lv_obj_t *tv, lv_obj_t *screen);
void App_loop();
void load_app(uint8_t index);
bool register_app(App_item_t *app);
void exit_app();

#endif /* _PAGE_APPLICATION_H_ */