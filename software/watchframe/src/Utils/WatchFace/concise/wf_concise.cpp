#include "wf_concise.h"

static lv_obj_t *Clock;
static lv_meter_indicator_t *indic_h;
static lv_meter_indicator_t *indic_m;
static lv_meter_indicator_t *indic_s;
static bool _is_init_anim_done = false;

LV_IMG_DECLARE(img_icon_by_wf_concise)

void set_anim(void *indic, int32_t v)
{
    lv_meter_set_indicator_value(Clock, (lv_meter_indicator_t *)indic, v);
}

void watchface_concise_init(lv_obj_t *src)
{
    _is_init_anim_done = false;
    lv_obj_t *_src = src;

    Clock = lv_meter_create(_src);
    lv_obj_set_width(Clock, LV_PCT(100));
    lv_obj_set_height(Clock, LV_PCT(100));
    lv_obj_set_style_border_width(Clock, -12, 0);
    lv_obj_clear_flag(_src, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(Clock, LV_ALIGN_CENTER, 0, 0);

    lv_meter_scale_t *Scale = lv_meter_add_scale(Clock);
    lv_meter_set_scale_range(Clock, Scale, 0, 360, 360, 270);
    lv_meter_set_scale_ticks(Clock, Scale, 60 + 1, 2, 12, lv_color_white());

    lv_meter_scale_t *HourScale = lv_meter_add_scale(Clock);
    lv_meter_set_scale_range(Clock, HourScale, 0, 360, 360, 270);
    lv_meter_set_scale_ticks(Clock, HourScale, 12 + 1, 2, 22, lv_color_white());

    indic_h = lv_meter_add_needle_line(Clock, Scale, 6, lv_palette_darken(LV_PALETTE_GREEN, 4), -60);
    indic_m = lv_meter_add_needle_line(Clock, Scale, 5, lv_palette_darken(LV_PALETTE_BLUE, 2), -45);
    indic_s = lv_meter_add_needle_line(Clock, Scale, 4, lv_palette_darken(LV_PALETTE_RED, 4), -15);
}

void watchface_concise_loop(lv_obj_t *screen, void *user_data)
{
    TWatchClass *ttgo = TWatchClass::getWatch();

    if (ttgo->Time_isUpdated() && Clock != nullptr)
    {
        RTC_Date time = ttgo->GetRTCTime();
        Serial.printf("%d,%d,%d\n", time.hour, time.minute, time.second);
        if (_is_init_anim_done)
        {
            lv_anim_t s_a;
            lv_anim_init(&s_a);
            lv_anim_set_repeat_count(&s_a, 0);
            lv_anim_set_time(&s_a, 1000);
            lv_anim_set_exec_cb(&s_a, set_anim);

            lv_anim_set_var(&s_a, indic_s);
            if (time.second != 0)
                lv_anim_set_values(&s_a, (int32_t)((time.second - 1) * 6) % 360, (int32_t)(time.second * 6) % 360);
            else
                lv_anim_set_values(&s_a, 354, 360);
            lv_anim_start(&s_a);

            lv_meter_set_indicator_value(Clock, indic_h, ((time.hour % 12) * 30) + (time.minute / 5));
            lv_meter_set_indicator_value(Clock, indic_m, (time.minute * 6) + (time.second / 5));
        }
        else
        {
            lv_anim_t a;
            lv_anim_init(&a);
            lv_anim_set_exec_cb(&a, set_anim);
            lv_anim_set_time(&a, 1000);

            lv_anim_set_var(&a, (lv_meter_indicator_t *)indic_h);
            lv_anim_set_values(&a, 0, (time.hour % 12) * 30);
            lv_anim_start(&a);

            lv_anim_set_var(&a, (lv_meter_indicator_t *)indic_m);
            lv_anim_set_values(&a, 0, time.minute * 6);
            lv_anim_start(&a);

            lv_anim_set_var(&a, (lv_meter_indicator_t *)indic_s);
            lv_anim_set_values(&a, 0, time.second * 6);
            lv_anim_start(&a);
            _is_init_anim_done = true;
        }
    }
}
void watchface_concise_close()
{
    lv_anim_del_all();
}

struct watchface_item_t watchface_concise =
    {
        .init = watchface_concise_init,
        .loop = watchface_concise_loop,
        .exit = watchface_concise_close,
        .icon = img_icon_by_wf_concise,
        .name = "simple clock",
        .user_data = NULL,
};