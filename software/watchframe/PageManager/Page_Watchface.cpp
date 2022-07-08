#include "Page_Watchface.h"

#define MAX_REGISTERED_WATCHFACE 20

static lv_obj_t *_watchface_disp = nullptr;
static watchface_item_t *watchface_ptr = nullptr;
// static bool _watchface_is_run = false;
static bool _watchface_has_been_load = false;

static watchface_item_t *_watchface_ptr[MAX_REGISTERED_WATCHFACE] = {nullptr};
static uint8_t _watchface_quantity = 0;
static uint8_t _watchface_running_index = 0;

extern struct watchface_item_t watchface_concise; // Initial default dial
static void watchface_setup(uint8_t index);
static void watchface_exit(void);

void watchface_init(lv_obj_t *screen)
{
    _watchface_disp = screen;
    watchface_load(_watchface_running_index);
}

void watchface_load(uint8_t index)
{
    watchface_exit();
    lv_obj_remove_style_all(_watchface_disp); // Clear all subitems and styles
    lv_obj_center(_watchface_disp);
    lv_obj_remove_style(_watchface_disp, NULL, LV_PART_SCROLLBAR);
    lv_obj_add_style(_watchface_disp, &Initial_screen_style, 0);
    watchface_setup(index);
    _watchface_has_been_load = true;
}

static void watchface_setup(uint8_t index)
{
    if (_watchface_has_been_load == false)
    {
        _watchface_running_index = index;
        watchface_ptr = _watchface_ptr[index];
        watchface_ptr->init(_watchface_disp);
    }
}
void watchface_loop(void)
{
    if (_watchface_has_been_load == true)
        watchface_ptr->loop(_watchface_disp, watchface_ptr->user_data);
}
static void watchface_exit(void)
{
    if (_watchface_has_been_load == true)
    {
        watchface_ptr->exit();
        _watchface_has_been_load = false;
        lv_obj_clean(_watchface_disp);
    }
}

bool register_watchface(watchface_item_t *watchface)
{
    if (_watchface_quantity > MAX_REGISTERED_WATCHFACE)
        return false;

    _watchface_ptr[_watchface_quantity] = watchface;
    _watchface_quantity++;
    return true;
}

uint8_t page_get_watchface_qauetity(void)
{
    return _watchface_quantity;
}

watchface_item_t *page_get_watchface(uint8_t index)
{
    return _watchface_ptr[index];
}
uint8_t page_get_running_watchface_index(void)
{
    return _watchface_running_index;
}