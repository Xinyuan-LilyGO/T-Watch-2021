#include "PageManager.h"
#include "TWatch_hal.h"

static TWatchClass *ttgo = nullptr;
static lv_group_t *g;
static lv_indev_t *cur_indev = nullptr;
static lv_obj_t *main_scr = nullptr;
static lv_obj_t *app_scr = nullptr;
static lv_obj_t *watchface_scr = nullptr;
static lv_obj_t *menu_scr = nullptr;

static lv_disp_t *disp = nullptr;
static lv_theme_t *default_theme;

uint8_t switch_interface;

EventGroupHandle_t local_setting;
static bool bit0_reset;
static bool bit0_isCalibration; // Calibration time interval

QueueHandle_t goto_sleep_queue_handle;

void Page_Init()
{
    ttgo = TWatchClass::getWatch();

    local_setting = xEventGroupCreate();
    goto_sleep_queue_handle = xQueueCreate(1, sizeof(uint8_t));

    default_theme = lv_theme_default_get();
    // default_theme->color_primary = lv_palette_main(LV_PALETTE_DEEP_ORANGE);
    // default_theme->color_secondary = lv_palette_main(LV_PALETTE_DEEP_ORANGE);
    lv_theme_default_init(NULL, lv_color_hex(0x66CC66), lv_palette_main(LV_PALETTE_DEEP_ORANGE), LV_THEME_DEFAULT_DARK, &lv_font_montserrat_14);

    Page_Style_Init();

    g = lv_group_create();
    lv_group_set_default(g);

    cur_indev = lv_indev_get_next(cur_indev);
    if (cur_indev->driver->type == LV_INDEV_TYPE_ENCODER)
    {
        lv_indev_set_group(cur_indev, g);
    }

    lv_obj_add_style(lv_scr_act(), &Initial_screen_style, 0);
    main_scr = lv_tileview_create(lv_scr_act());
    lv_obj_add_style(main_scr, &Initial_screen_style, 0);
    lv_obj_set_style_radius(main_scr, 60, 0);
    lv_obj_remove_style(main_scr, NULL, LV_PART_SCROLLBAR);
    lv_obj_center(main_scr);

    watchface_scr = lv_tileview_add_tile(main_scr, 0, 0, LV_DIR_NONE); // watchface

    /**
     * @brief Construct a new register watchface object
     *
     */
    register_watchface(&watchface_spacerman);
    register_watchface(&watchface_frame);
    register_watchface(&watchface_concise);

    watchface_init(watchface_scr);

    menu_scr = lv_tileview_add_tile(main_scr, 1, 0, LV_DIR_NONE); // menu
    App_Menu_init(menu_scr);

    app_scr = lv_tileview_add_tile(main_scr, 2, 0, LV_DIR_NONE); // app

    /**
     * @brief Construct a new register app object
     *
     */
    register_app(&app_watchface_select);
    register_app(&app_setting);
    register_app(&app_frame);

    App_init(main_scr, app_scr);
    switch_interface = 0;
}

static void notification_timer_cb(lv_timer_t *timer)
{
    lv_obj_t *msg = (lv_obj_t *)timer->user_data;

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, [](void *obj, int value)
                        { if(obj != nullptr)
                            lv_obj_align((lv_obj_t *)obj, LV_ALIGN_TOP_MID, 0, value); 
                            if(value == (-50))
                                lv_obj_add_flag((lv_obj_t *)obj,LV_OBJ_FLAG_HIDDEN); });
    lv_anim_set_var(&a, msg);
    lv_anim_set_time(&a, 300);
    lv_anim_set_values(&a, 10, -50);
    lv_anim_start(&a);

    lv_timer_del(timer);
}

void create_notification(char *details, uint32_t delay)
{

    lv_obj_t *msg = lv_obj_create(lv_scr_act());
    lv_obj_set_size(msg, 120, LV_SIZE_CONTENT);
    lv_obj_set_style_radius(msg, 10, 0);
    lv_obj_set_style_bg_color(msg, lv_theme_default_get()->color_primary, 0);
    lv_obj_set_style_border_width(msg, 0, 0);
    lv_obj_set_layout(msg, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(msg, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(msg, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

    lv_obj_t *label = lv_label_create(msg);
    lv_obj_center(label);
    lv_label_set_text(label, details);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);

    lv_obj_set_width(label, LV_PCT(100));

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, [](void *obj, int value)
                        { if(obj != nullptr)
                            lv_obj_align((lv_obj_t *)obj, LV_ALIGN_TOP_MID, 0, value); });
    lv_anim_set_var(&a, msg);
    lv_anim_set_time(&a, 300);
    lv_anim_set_values(&a, -50, 10);
    lv_anim_start(&a);

    lv_obj_clear_flag(msg, LV_OBJ_FLAG_HIDDEN);
    lv_timer_t *timer = lv_timer_create(notification_timer_cb, delay + 300, msg);
}

void Page_Loop()
{
    watchface_loop();
    App_loop();

    EventBits_t bit = xEventGroupGetBits(ttgo->_hal_botton_event);
    if (bit & EVENT_CLICK_BIT(1))
    {
        xEventGroupClearBits(ttgo->_hal_botton_event, EVENT_CLICK_BIT(1));

        if (switch_interface)
            switch_interface--;
        else
            switch_interface = 1;

        lv_obj_set_tile(main_scr, switch_interface ? menu_scr : watchface_scr, LV_ANIM_ON);
    }

    bit = xEventGroupGetBits(local_setting);
    if ((bit & _BV(0)) && bit0_isCalibration == false)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            bit0_isCalibration = true;
            core_0_get_ntp();
            create_notification("Successful calibration", 1500);
        }
    }
    else if ((bit & _BV(0)) == false)
    {
        bit0_isCalibration = false;
    }

    if ((bit & _BV(1)))
    {
        if (switch_interface)
        {
            auto_sleep_updeta();
        }
        wait_auto_sleep();
    }
}