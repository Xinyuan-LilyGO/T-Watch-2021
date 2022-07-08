#include "watchface_select.h"
LV_IMG_DECLARE(img_icon_by_watchface_select)
static lv_obj_t *_screen = nullptr;

static void scroll_event_cb(lv_event_t *e)
{
    lv_obj_t *cont = lv_event_get_target(e);

    lv_area_t cont_a;
    lv_obj_get_coords(cont, &cont_a);
    lv_coord_t cont_y_center = cont_a.y1 + lv_area_get_height(&cont_a) / 2;

    lv_coord_t r = lv_obj_get_height(cont) * 7 / 10;
    uint32_t i;
    uint32_t child_cnt = lv_obj_get_child_cnt(cont);
    for (i = 0; i < child_cnt; i++)
    {
        lv_obj_t *child = lv_obj_get_child(cont, i);
        lv_area_t child_a;
        lv_obj_get_coords(child, &child_a);

        lv_coord_t child_y_center = child_a.y1 + lv_area_get_height(&child_a) / 2;

        lv_coord_t diff_y = child_y_center - cont_y_center;
        diff_y = LV_ABS(diff_y);

        /*Get the x of diff_y on a circle.*/
        lv_coord_t x;
        /*If diff_y is out of the circle use the last point of the circle (the radius)*/
        if (diff_y >= r)
        {
            x = r;
        }
        else
        {
            /*Use Pythagoras theorem to get x from radius and y*/
            uint32_t x_sqr = r * r - diff_y * diff_y;
            lv_sqrt_res_t res;
            lv_sqrt(x_sqr, &res, 0x8000); /*Use lvgl's built in sqrt root function*/
            x = r - res.i;
        }

        /*Translate the item by the calculated X coordinate*/
        lv_obj_set_style_translate_x(child, x, 0);

        /*Use some opacity with larger translations*/
        lv_opa_t opa = lv_map(x, 0, r, LV_OPA_TRANSP, LV_OPA_COVER);
        lv_obj_set_style_opa(child, LV_OPA_COVER - opa, 0);
    }
}

static void switch_watchface_event_cb(lv_event_t *e)
{
    uint32_t event_code = lv_event_get_code(e);
    lv_obj_t *instance = lv_event_get_target(e);
    lv_obj_t *parent = lv_obj_get_parent(instance);
    uint8_t index = lv_obj_get_index(instance);

    if (event_code == LV_EVENT_SHORT_CLICKED)
    {
        uint8_t watchface_quanlity = page_get_watchface_qauetity();
        for (uint32_t i = 0; i < watchface_quanlity; i++)
        {
            lv_obj_t *tmp_obj = lv_obj_get_child(parent, i);
            lv_obj_clear_state(tmp_obj, LV_STATE_CHECKED);
        }
        lv_obj_add_state(instance, LV_STATE_CHECKED);
        watchface_load(index);
        lv_obj_t *parent = lv_obj_get_parent(_screen);
        lv_obj_set_tile_id(parent, 0, 0, LV_ANIM_ON);
    }
}

void app_watchface_select_init(lv_obj_t *screen)
{
    _screen = screen;
    lv_obj_t *cont = lv_obj_create(_screen);
    lv_obj_set_size(cont, 240, 240);
    lv_obj_center(cont);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_add_event_cb(cont, scroll_event_cb, LV_EVENT_SCROLL, NULL);
    lv_obj_set_style_radius(cont, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_clip_corner(cont, true, 0);
    lv_obj_set_scroll_dir(cont, LV_DIR_VER);
    lv_obj_set_scroll_snap_y(cont, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);

    uint8_t watchface_quanlity = page_get_watchface_qauetity();

    for (uint32_t i = 0; i < watchface_quanlity; i++)
    {
        lv_obj_t *btn = lv_btn_create(cont);
        lv_obj_set_size(btn, lv_pct(100), 50);
        lv_obj_set_style_radius(btn, 90, 0);
        // lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE);
        watchface_item_t *tmp = page_get_watchface(i);

        lv_obj_t *icon = lv_img_create(btn);
        lv_obj_align(icon, LV_ALIGN_LEFT_MID, -16, 0);
        lv_img_set_src(icon, &tmp->icon);
        lv_obj_set_style_radius(icon, 90, 0);

        lv_obj_t *label = lv_label_create(btn);
        lv_obj_align_to(label, icon, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
        lv_label_set_text_fmt(label, "%s", tmp->name);

        lv_obj_add_event_cb(btn, switch_watchface_event_cb, LV_EVENT_SHORT_CLICKED, NULL);
    }

    uint8_t is_running_watchface_index = page_get_running_watchface_index();

    lv_obj_t *instance = lv_obj_get_child(cont, is_running_watchface_index);
    lv_obj_add_state(instance, LV_STATE_CHECKED);

    /*Update the buttons position manually for first*/
    lv_event_send(cont, LV_EVENT_SCROLL, NULL);

    /*Be sure the fist button is in the middle*/
    lv_obj_scroll_to_view(lv_obj_get_child(cont, 0), LV_ANIM_OFF);
}

void app_watchface_select_loop(lv_obj_t *screen, void *user_data)
{
}

void app_watchface_select_exit()
{
}

struct App_item_t app_watchface_select =
    {
        .init = app_watchface_select_init,
        .loop = app_watchface_select_loop,
        .exit = app_watchface_select_exit,
        .icon = img_icon_by_watchface_select,
        .name = nullptr,
        .user_data = NULL,
};