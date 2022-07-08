#include "app_setting.h"
#include "TWatch_hal.h"
#include "WiFi.h"
#include "wifi_tabview.h"
#include "general_setting.h"
#include "factory_test.h"

#include "../../Utils.h"
#include "../../../PageManager/PageManager.h"
#include "../../../PageManager/Page_Watchface.h"
LV_FONT_DECLARE(user_symbol)
LV_IMG_DECLARE(img_icon_by_setting)
#define USER_SYMBOL_BULB "\xEF\x83\xAB" // f0eb
#define USER_SYMBOL_BULB "\xEF\x83\xAB" // f0eb

static lv_obj_t *_screen = nullptr;
static lv_obj_t *wlan_obj;
static lv_obj_t *ble_obj;
static lv_obj_t *general_obj;
static lv_obj_t *factory_obj;

static lv_obj_t *tabview;

static lv_obj_t *kb;

void Ble_page(lv_obj_t *obj)
{
    lv_obj_set_layout(obj, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(obj, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_t *text = lv_label_create(obj);
    lv_label_set_text(text, "BLE");

    lv_obj_t *sw = lv_switch_create(obj);
    lv_obj_set_size(sw, 50, 30);
    // lv_obj_add_event_cb(sw, event_handler, LV_EVENT_ALL, NULL);

    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_COLUMN_WRAP);
}

void app_setting_init(lv_obj_t *screen)
{
    _screen = screen;

    kb = lv_keyboard_create(_screen);
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);

    tabview = lv_tabview_create(_screen, LV_DIR_LEFT, 60);

    lv_obj_set_size(tabview, 220, 180);
    lv_obj_center(tabview);

    wlan_obj = lv_tabview_add_tab(tabview, "WLAN");
    Wifi_page(wlan_obj, kb);
    // ble_obj = lv_tabview_add_tab(tabview, "Ble");
    // Ble_page(ble_obj);
    factory_obj = lv_tabview_add_tab(tabview, "Factory");
    factory_page(factory_obj);
    general_obj = lv_tabview_add_tab(tabview, "General");
    General_page(general_obj);
}

void app_setting_loop(lv_obj_t *screen, void *user_data)
{
    factory_loop();
}

void app_setting_exit()
{
}

struct App_item_t app_setting =
    {
        .init = app_setting_init,
        .loop = app_setting_loop,
        .exit = app_setting_exit,
        .icon = img_icon_by_setting,
        .name = nullptr,
        .user_data = NULL,
};