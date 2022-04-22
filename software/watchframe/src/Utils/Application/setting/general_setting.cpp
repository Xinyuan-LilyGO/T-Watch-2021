#include "general_setting.h"
#include "../../Utils.h"
#include "../../../PageManager/PageManager.h"

static TWatchClass *ttgo;

static void setting_brightness_event_cb(lv_event_t *e)
{
    lv_obj_t *slider = lv_event_get_target(e);
    ttgo->Backlight_SetValue((int)lv_slider_get_value(slider));
}

static void dynamic_load_event_cb(lv_event_t *e)
{
    lv_obj_t *obj = (lv_obj_t *)lv_event_get_user_data(e);
    lv_obj_t *instance = (lv_obj_t *)lv_event_get_target(e);
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        if (lv_obj_get_state(instance) & LV_STATE_CHECKED)
        {
            lv_anim_t a;
            lv_anim_init(&a);
            lv_anim_set_exec_cb(&a, [](void *obj, int value)
                                { if(obj != nullptr)
                            lv_obj_set_height((lv_obj_t *)obj,  value); });
            lv_anim_set_var(&a, obj);
            lv_anim_set_time(&a, 300);
            lv_anim_set_values(&a, 0, 230);
            lv_anim_start(&a);

            lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
            Serial.printf("hight:%d\n", lv_obj_get_height(obj));
            auto_sleep_start();
            xEventGroupSetBits(local_setting, _BV(1));
            create_notification("OPEN Auto\nSleep", 1500);
        }
        else
        {
            auto_sleep_close();
            xEventGroupClearBits(local_setting, _BV(1));
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            create_notification("CLOSE Auto\nSleep", 1500);
        }
    }
}
static void wake_up_setting_time_event_cb(lv_event_t *e)
{
    lv_obj_t *obj = (lv_obj_t *)lv_event_get_user_data(e);
    lv_obj_t *instance = (lv_obj_t *)lv_event_get_target(e);
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        String str;
        char buf[10];
        lv_dropdown_get_selected_str(instance, buf, 0);
        str = buf;
        auto_sleep_set_time(str.toInt());
        create_notification("change time", 1500);
    }
}

static void wake_up_setting_event_cb(lv_event_t *e)
{
    lv_obj_t *obj = (lv_obj_t *)lv_event_get_user_data(e);
    lv_obj_t *instance = (lv_obj_t *)lv_event_get_target(e);
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        const char *num = lv_checkbox_get_text(instance);
        DEBUGF("wake_up:%s\n", num);

        switch (*num)
        {
        case '1':
            DEBUGLN('1');
            if (lv_obj_get_state(instance) & LV_STATE_CHECKED)
                auto_sleep_set_wake_up(WAKE_UP_REASON_WRIST_UP, true);
            else
                auto_sleep_set_wake_up(WAKE_UP_REASON_WRIST_UP, false);
            break;
        case '2':
            DEBUGLN('2');
            if (lv_obj_get_state(instance) & LV_STATE_CHECKED)
                auto_sleep_set_wake_up(WAKE_UP_REASON_DOUBLE_TAG, true);
            else
                auto_sleep_set_wake_up(WAKE_UP_REASON_DOUBLE_TAG, false);
            break;
        case '3':
            DEBUGLN('3');
            if (lv_obj_get_state(instance) & LV_STATE_CHECKED)
                auto_sleep_set_wake_up(WAKE_UP_REASON_SCREEN, true);
            else
                auto_sleep_set_wake_up(WAKE_UP_REASON_SCREEN, false);
            break;
        default:
            DEBUGLN("default");
            break;
        }
    }
}

void General_page(lv_obj_t *obj)
{
    ttgo = TWatchClass::getWatch();
    lv_obj_set_layout(obj, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(obj, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

    lv_obj_t *text = lv_label_create(obj);
    lv_label_set_text(text, "Brightness");

    lv_obj_t *slider = lv_slider_create(obj);
    lv_obj_set_size(slider, LV_PCT(80), 10);
    int8_t brightness = ttgo->Backlight_GetValue();
    lv_slider_set_value(slider, brightness, LV_ANIM_ON);
    lv_obj_add_event_cb(slider, setting_brightness_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    text = lv_label_create(obj);
    lv_label_set_text(text, "Auto\nsleep");

    lv_obj_t *sw = lv_switch_create(obj);
    lv_obj_set_size(sw, 50, 30);

    lv_obj_t *auto_sleep = lv_obj_create(obj);
    lv_obj_set_size(auto_sleep, LV_PCT(100), 230);
    lv_obj_set_flex_flow(auto_sleep, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(auto_sleep, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_add_flag(auto_sleep, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_event_cb(sw, dynamic_load_event_cb, LV_EVENT_VALUE_CHANGED, auto_sleep);

    text = lv_label_create(auto_sleep);
    lv_label_set_text(text, "delay unit:s");
    lv_obj_set_style_text_align(text, LV_TEXT_ALIGN_CENTER, 0);

    lv_obj_t *delay_time = lv_dropdown_create(auto_sleep);
    lv_obj_set_size(delay_time, LV_PCT(100), 40);
    lv_dropdown_set_dir(delay_time, LV_DIR_LEFT);
    lv_dropdown_set_symbol(delay_time, LV_SYMBOL_LEFT);
    lv_dropdown_set_options(delay_time, "5\n10\n30\n60");
    lv_obj_add_event_cb(delay_time, wake_up_setting_time_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_t *cb = lv_checkbox_create(auto_sleep);
    lv_checkbox_set_text(cb, "1.Wrist up");
    lv_obj_add_event_cb(cb, wake_up_setting_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    cb = lv_checkbox_create(auto_sleep);
    lv_checkbox_set_text(cb, "2.Double tap");
    lv_obj_add_event_cb(cb, wake_up_setting_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    cb = lv_checkbox_create(auto_sleep);
    lv_checkbox_set_text(cb, "3.Screen");
    lv_obj_add_event_cb(cb, wake_up_setting_event_cb, LV_EVENT_VALUE_CHANGED, NULL);



}