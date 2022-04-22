#include "Page_MainMenu.h"

static lv_obj_t *watchface_menu;
static lv_obj_t *app_menu;
static lv_obj_t *view_main;
static lv_obj_t *_screen = nullptr;

void _switch_menu(lv_event_t *e)
{
    lv_obj_t *screen = lv_event_get_current_target(e);
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    _DEBUG_IS_RUN_LINE(dir, d);
}

void Menu_init(lv_obj_t *screen)
{
    _screen = screen;
    lv_obj_center(_screen);
    lv_obj_add_style(_screen, &Initial_screen_style, 0);
    lv_obj_remove_style(_screen, NULL, LV_PART_SCROLLBAR);

    lv_obj_add_event_cb(_screen, _switch_menu, LV_EVENT_GESTURE, NULL);
    // Menu_create();
}

void Menu_create()
{
    view_main = lv_obj_create(_screen);
    lv_obj_remove_style_all(view_main);
    lv_obj_set_size(view_main, LV_PCT(100), LV_PCT(100));
    lv_obj_center(view_main);

    watchface_init(view_main);
    // App_Menu_init(view_main);
    lv_obj_add_event_cb(view_main, _switch_menu, LV_EVENT_SCROLL, NULL);
}

void Menu_loop(void)
{
    // watchface_loop();
}

void Menu_hide(bool en)
{
    if (en)
    {
        // lv_obj_del(view_main);
    }
    else
    {
        // Menu_create();
    }
}