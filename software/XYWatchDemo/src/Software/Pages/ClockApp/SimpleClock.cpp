#include "SimpleClock.h"

static lv_obj_t *Clock;

static lv_meter_indicator_t *indic_h;
static lv_meter_indicator_t *indic_m;
static lv_meter_indicator_t *indic_s;
static RTC_Date rtc;

static void Anim_second_cb(void *indic, int32_t v)
{
    lv_meter_set_indicator_value(Clock, indic_s, (int32_t)(v + (rtc.second * 6)) % 360);
}

static void Anim_frist_cb(void *indic, int32_t v)
{
    lv_meter_set_indicator_value(Clock, (lv_meter_indicator_t *)indic, v);
}

static void SimpleClock_timer(lv_timer_t *timer)
{
    rtc = XYWatch::GetRTCTime();

    lv_meter_set_indicator_value(Clock, indic_h, ((rtc.hour % 12) * 30) % 360);
    lv_meter_set_indicator_value(Clock, indic_m, (rtc.minute * 6) % 360);
    lv_anim_t s_a;

    lv_anim_init(&s_a);
    lv_anim_set_values(&s_a, 0, 6);
    lv_anim_set_repeat_count(&s_a, 0);

    lv_anim_set_exec_cb(&s_a, Anim_second_cb);
    lv_anim_set_var(&s_a, indic_s);
    lv_anim_set_time(&s_a, 1000);
    lv_anim_start(&s_a);
}

void SimpleClock(lv_obj_t *screen)
{
    lv_obj_set_height(screen, LV_PCT(100));
    lv_obj_set_width(screen, LV_PCT(100));
    lv_obj_set_flex_grow(screen, 0);

    lv_obj_set_scrollbar_mode(screen, 0);

    Clock = lv_meter_create(screen);
    lv_obj_set_width(Clock, LV_PCT(100));
    lv_obj_set_height(Clock, LV_PCT(100));
    lv_obj_set_style_border_width(Clock, -12, 0);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
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

    lv_timer_t *timer = lv_timer_create(SimpleClock_timer, 1000, nullptr);

    rtc = XYWatch::GetRTCTime();

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_repeat_count(&a, 0);
    lv_anim_set_time(&a, 1000);
    lv_anim_set_exec_cb(&a, Anim_frist_cb);

    lv_anim_set_var(&a, indic_s);
    lv_anim_set_values(&a, 0, rtc.second * 6);
    lv_anim_start(&a);

    lv_anim_set_var(&a, indic_m);
    lv_anim_set_values(&a, 0, rtc.minute * 6);
    lv_anim_start(&a);

    lv_anim_set_var(&a, indic_h);
    lv_anim_set_values(&a, 0, (rtc.hour % 12) * 30);
    lv_anim_start(&a);
}
