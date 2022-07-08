#include "frame.h"

static lv_obj_t *Clock;

static bool _is_init_anim_done = false;
LV_IMG_DECLARE(img_bulb_gif);

void watchface_frame_init(lv_obj_t *src)
{
    _is_init_anim_done = false;
    lv_obj_t *_src = src;
    lv_obj_t *img;

    img = lv_gif_create(_src);
    lv_gif_set_src(img, &img_bulb_gif);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
}

void watchface_frame_loop(lv_obj_t *screen, void *user_data)
{

}
void watchface_frame_close()
{
}

LV_IMG_DECLARE(img_icon_by_watchface_select)
struct watchface_item_t watchface_frame =
    {
        .init = watchface_frame_init,
        .loop = watchface_frame_loop,
        .exit = watchface_frame_close,
        .icon = img_icon_by_watchface_select,
        .name = "frame",
        .user_data = NULL,
};