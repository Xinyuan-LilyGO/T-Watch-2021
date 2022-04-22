#ifndef _PAGE_WATCHFACE_H_
#define _PAGE_WATCHFACE_H_

#include "./libraries/lvgl/lvgl.h"
#include "Page_type.h"

typedef void *watchface_handle;

typedef void (*watchface_item_init_t)(lv_obj_t *screen);
typedef void (*watchface_item_loop_t)(lv_obj_t *screen, void *user_data);
typedef void (*watchface_item_close_t)();

struct watchface_item_t
{
    watchface_item_init_t init;
    watchface_item_loop_t loop;
    watchface_item_close_t exit;
    lv_img_dsc_t icon;
    char *name;
    void *user_data;
};

void watchface_init(lv_obj_t *screen);
void watchface_create(watchface_item_t *item);
void watchface_loop(void);

void watchface_load(uint8_t index);
bool register_watchface(watchface_item_t *watchface);
uint8_t page_get_watchface_qauetity(void);
watchface_item_t *page_get_watchface(uint8_t index);
uint8_t page_get_running_watchface_index(void);
#endif /* _PAGE_WATCHFACE_H_ */