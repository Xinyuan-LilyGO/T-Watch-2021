#include "DigitalClock.h"
#include "./Software/utils/week/week.h"

static RTC_Date rtc;

static lv_obj_t *Clock;

static lv_meter_indicator_t *StepIndic;

static lv_obj_t *date_text;
static lv_obj_t *week_text;

static lv_obj_t *time_text;
static lv_obj_t *stepnum_text;

static void set_value(void *indic, int32_t v)
{
    if (v == 0)
    {
        rtc = XYWatch::GetRTCTime();
    }
    lv_meter_set_indicator_end_value(Clock, (lv_meter_indicator_t *)indic, (int32_t)(v + (rtc.second * 6)) % 360);
}

void updated_timer(lv_timer_t *timer)
{
    int32_t step_t = XYWatch::AccSensor_GetStep();

    uint8_t week = Day(rtc.year, rtc.month, rtc.day);
    lv_meter_set_indicator_end_value(Clock, (lv_meter_indicator_t *)StepIndic, step_t * 0.03);
    lv_label_set_text_fmt(stepnum_text, "%2d", step_t);
    lv_label_set_text_fmt(date_text, "%d.%02d.%02d", rtc.year, rtc.month, rtc.day);
    lv_label_set_text_fmt(week_text, "%s", DAY_NAMES[week]);
    lv_label_set_text_fmt(time_text, "%02d:%02d", rtc.hour, rtc.minute);
}

void DigitalClock(lv_obj_t *screen)
{
    Clock = lv_meter_create(screen);
    lv_obj_add_style(Clock, &Clock2bgStyle, 0);

    lv_obj_set_size(Clock, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_border_width(Clock, -12, 0);

    static lv_meter_scale_t *SecondScale = lv_meter_add_scale(Clock);
    lv_meter_scale_t *StepsCale = lv_meter_add_scale(Clock);

    lv_meter_set_scale_range(Clock, SecondScale, 0, 360, 360, 90);
    lv_meter_set_scale_range(Clock, StepsCale, 0, 300, 300, 120);

    lv_obj_remove_style(Clock, NULL, LV_PART_INDICATOR);

    lv_meter_set_scale_ticks(Clock, StepsCale, 0, 0, 0, lv_palette_main(LV_PALETTE_NONE));
    lv_meter_set_scale_ticks(Clock, SecondScale, 0, 0, 0, lv_palette_main(LV_PALETTE_NONE));

    lv_meter_indicator_t *second = lv_meter_add_arc(Clock, SecondScale, 10, lv_palette_main(LV_PALETTE_GREEN), 0);
    StepIndic = lv_meter_add_arc(Clock, StepsCale, 10, lv_color_make(231, 62, 97), -12);

    date_text = lv_label_create(Clock);
    week_text = lv_label_create(Clock);
    time_text = lv_label_create(Clock);
    stepnum_text = lv_label_create(Clock);

    LV_IMG_DECLARE(img_lilygo);
    lv_obj_t *logo = lv_img_create(Clock);
    lv_img_set_src(logo, &img_lilygo);
    lv_obj_align(logo, LV_ALIGN_CENTER, 0, 45);

    lv_obj_add_style(stepnum_text, &Font_w_18_Style, 0);
    lv_obj_align(stepnum_text, LV_ALIGN_BOTTOM_MID, 0, -15);

    LV_IMG_DECLARE(img_foot_white);
    lv_obj_t *footlogo = lv_img_create(Clock);
    lv_img_set_src(footlogo, &img_foot_white);
    lv_obj_align(footlogo, LV_ALIGN_CENTER, -30, 90);

    lv_obj_align_to(footlogo, stepnum_text, LV_ALIGN_OUT_LEFT_MID, 0, 0);

    lv_obj_add_style(date_text, &Font_w_18_Style, 0);
    lv_obj_align(date_text, LV_ALIGN_CENTER, 0, -50);

    lv_obj_add_style(week_text, &Font_w_18_Style, 0);
    lv_obj_align(week_text, LV_ALIGN_CENTER, 0, -30);

    lv_obj_add_style(time_text, &Font_w_48_Style, 0);
    lv_obj_align(time_text, LV_ALIGN_CENTER, 0, 0);

    /*     LV_IMG_DECLARE(UI_step);
    lv_obj_t *ui_step = lv_img_create(Clock);
    lv_img_set_src(ui_step, &UI_step);
    lv_obj_align(ui_step, LV_ALIGN_CENTER, 0, 83);
    lv_obj_move_background(ui_step);
    lv_obj_move_foreground(Clock); */

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, second);
    lv_anim_set_exec_cb(&a, set_value);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_values(&a, 0, 6);
    lv_anim_set_time(&a, 1000);
    lv_anim_start(&a);
    lv_timer_t *timer = lv_timer_create(updated_timer, 1000, nullptr);
}