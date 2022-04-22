#include "wifi_tabview.h"
#include "../../Utils.h"
#include "../../../PageManager/PageManager.h"
#include "../../../PageManager/Page_Watchface.h"
static lv_obj_t *kb;
static lv_obj_t *wifi_info;
static TWatchClass *ttgo;
static QueueHandle_t wifi_list_queue_handle;
static QueueHandle_t wifi_connect_queue_handle;
static lv_obj_t *_screen;

static char ssid[20], password[20];

static lv_obj_t *create_btn_with_label(lv_obj_t *parent, char *text)
{
    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_set_size(btn, 30, 30);

    lv_obj_t *label = lv_label_create(btn);
    lv_obj_center(label);
    lv_label_set_text(label, text);
    return btn;
}

static void close_parent_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    lv_obj_t *parent = lv_obj_get_parent(obj);
    if (code == LV_EVENT_CLICKED)
    {
        lv_obj_del(parent);
    }
}

static void input_textarea_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    lv_obj_t *kb = (lv_obj_t *)lv_event_get_user_data(e);
    lv_obj_t *parent = lv_obj_get_parent(ta);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, [](void *obj, int value)
                        { if(obj != nullptr)
                            lv_obj_align((lv_obj_t *)obj, LV_ALIGN_CENTER, 0, value); });
    lv_anim_set_var(&a, parent);
    lv_anim_set_time(&a, 300);

    if (code == LV_EVENT_FOCUSED)
    {
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_move_foreground(kb);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_anim_set_values(&a, 0, -50);
        lv_anim_start(&a);
    }
    else if (code == LV_EVENT_DEFOCUSED)
    {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_anim_set_values(&a, -50, 0);
        lv_anim_start(&a);
    }
}

static void wait_wifi_connect_timer(lv_timer_t *timer)
{
    if (WiFi.status() == WL_CONNECTED)
    {
        create_notification("The connection is successful", 1500);
        lv_obj_del((lv_obj_t *)timer->user_data);

        lv_obj_clear_flag(wifi_info, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text_fmt(wifi_info, "%s\n%s", ssid, WiFi.gatewayIP().toString().c_str());

        lv_timer_del(timer);
    }
}

static void wifi_connect_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *instance = lv_event_get_target(e);
    lv_obj_t *parent = lv_obj_get_parent(instance);
    lv_obj_t *textarea = (lv_obj_t *)lv_event_get_user_data(e);
    if (code == LV_EVENT_CLICKED)
    {
        strcpy(password, lv_textarea_get_text(textarea));
        WiFi.begin(ssid, password);
        Serial.printf("ssid:%s,password:%s\n", ssid, password);
        create_notification("connecting", 1500);
        lv_timer_t *timer = lv_timer_create(wait_wifi_connect_timer, 500, parent);
    }
}

static void wifi_password_input_interface(const char *ssid)
{
    lv_obj_t *msg = lv_obj_create(_screen);
    lv_obj_set_size(msg, 200, 100);
    lv_obj_align(msg, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_border_width(msg, 0, 0);
    lv_obj_clear_flag(msg, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_flex_flow(msg, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(msg, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

    lv_obj_t *btn = create_btn_with_label(msg, LV_SYMBOL_CLOSE);
    lv_obj_set_size(btn, 30, 30);
    lv_obj_add_event_cb(btn, close_parent_event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *title = lv_label_create(msg);
    lv_obj_set_size(title, 80, 20);
    lv_label_set_text_fmt(title, LV_SYMBOL_RIGHT " %s", ssid);
    lv_obj_set_style_text_align(title, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(title, LV_LABEL_LONG_SCROLL);

    btn = create_btn_with_label(msg, LV_SYMBOL_OK);
    lv_obj_set_size(btn, 30, 30);

    lv_obj_t *textarea = lv_textarea_create(msg);
    lv_obj_set_size(textarea, LV_PCT(100), 40);
    lv_textarea_set_align(textarea, LV_TEXT_ALIGN_CENTER);
    lv_textarea_set_one_line(textarea, true);
    lv_obj_add_event_cb(textarea, input_textarea_event_cb, LV_EVENT_ALL, kb);
    lv_obj_set_style_border_color(textarea, lv_palette_main(LV_PALETTE_ORANGE), 0);

    lv_obj_add_event_cb(btn, wifi_connect_event_cb, LV_EVENT_CLICKED, textarea);
}

static void connect_wifi_event_cb(lv_event_t *e)
{
    lv_obj_t *wifi_list = (lv_obj_t *)lv_event_get_user_data(e);
    lv_obj_t *instance = (lv_obj_t *)lv_event_get_target(e);
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        strcpy(ssid, lv_list_get_btn_text(wifi_list, instance));
        Serial.println(ssid);
        wifi_password_input_interface(ssid);
    }
}

static void core_0_scan_wifi(void *param)
{
    int n = WiFi.scanNetworks();
    xQueueSend(wifi_list_queue_handle, &n, 0);
    vTaskDelete(NULL);
}

static void wait_wifi_queue_timer(lv_timer_t *timer)
{
    lv_obj_t *wifi_list = (lv_obj_t *)timer->user_data;
    int n;
    BaseType_t status = xQueueReceive(wifi_list_queue_handle, &n, 0);
    if (status == pdPASS)
    {
        for (int i = 0; i < n; i++)
        {
            lv_obj_t *wifi_sub = lv_list_add_btn(wifi_list, NULL, WiFi.SSID(i).c_str());
            lv_obj_add_event_cb(wifi_sub, connect_wifi_event_cb, LV_EVENT_CLICKED, wifi_list);
        }
        lv_timer_del(timer);
    }
}

static void scan_wifi_event_cb(lv_event_t *e)
{
    lv_obj_t *wifi_list = (lv_obj_t *)lv_event_get_user_data(e);
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
            lv_anim_set_var(&a, wifi_list);
            lv_anim_set_time(&a, 300);
            lv_anim_set_values(&a, 0, 80);
            lv_anim_start(&a);

            lv_obj_clear_flag(wifi_list, LV_OBJ_FLAG_HIDDEN);

            lv_timer_t *timer = lv_timer_create(wait_wifi_queue_timer, 500, wifi_list);
            WiFi.mode(WIFI_MODE_STA);
            WiFi.disconnect();
            xTaskCreatePinnedToCore(core_0_scan_wifi, "core_0_scan_wifi", 1024 * 2, NULL, 0, NULL, 0);
            create_notification("OPEN WIFI", 1500);
        }
        else
        {
            lv_obj_add_flag(wifi_list, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clean(wifi_list);
            WiFi.disconnect(true);
            WiFi.mode(WIFI_MODE_NULL);
            lv_obj_add_flag(wifi_info, LV_OBJ_FLAG_HIDDEN);
            create_notification("CLOSE WIFI", 1500);
        }
    }
}

static void sync_time_event_cb(lv_event_t *e)
{
    lv_obj_t *instance = (lv_obj_t *)lv_event_get_target(e);
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        if (lv_obj_get_state(instance) & LV_STATE_CHECKED)
        {
            xEventGroupSetBits(local_setting, _BV(0));
            create_notification("SYNC TIME", 1500);
        }
        else
        {
            xEventGroupClearBits(local_setting, _BV(0));
        }
    }
}

void Wifi_page(lv_obj_t *obj, lv_obj_t *input_obj)
{
    kb = input_obj;
    _screen = lv_obj_get_parent(kb);
    wifi_list_queue_handle = xQueueCreate(1, sizeof(int));

    lv_obj_set_layout(obj, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(obj, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

    lv_obj_t *text = lv_label_create(obj);
    lv_label_set_text(text, "WLAN");

    lv_obj_t *wifi_sw = lv_switch_create(obj);
    lv_obj_set_size(wifi_sw, 50, 30);

    wifi_info = lv_label_create(obj);
    lv_label_set_text(wifi_info, "");
    lv_obj_set_size(wifi_info, LV_PCT(100), 30);
    lv_obj_add_flag(wifi_info, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_align(wifi_info, LV_TEXT_ALIGN_CENTER, 0);
    // lv_obj_add_event_cb(sw, event_handler, LV_EVENT_ALL, NULL);

    lv_obj_t *wifi_list = lv_list_create(obj);
    lv_obj_set_size(wifi_list, LV_PCT(100), 80);
    lv_obj_add_flag(wifi_list, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_event_cb(wifi_sw, scan_wifi_event_cb, LV_EVENT_VALUE_CHANGED, wifi_list);

    text = lv_label_create(obj);
    lv_label_set_text(text, "sync time");
    lv_obj_set_size(text, 60, 30);

    lv_obj_t *sync_sw = lv_switch_create(obj);
    lv_obj_set_size(sync_sw, 50, 30);
    lv_obj_add_event_cb(sync_sw, sync_time_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    /* Initialization state */
    if (WiFi.getMode() == WIFI_MODE_STA)
    {
        lv_obj_add_state(wifi_sw, LV_STATE_CHECKED);

        if (WiFi.status() == WL_CONNECTED)
        {
            lv_obj_add_state(wifi_sw, LV_STATE_CHECKED);

            lv_obj_clear_flag(wifi_info, LV_OBJ_FLAG_HIDDEN);
            lv_label_set_text_fmt(wifi_info, "%s\n%s", ssid, WiFi.gatewayIP().toString().c_str());
        }

        lv_obj_clear_flag(wifi_list, LV_OBJ_FLAG_HIDDEN);

        lv_timer_t *timer = lv_timer_create(wait_wifi_queue_timer, 500, wifi_list);
        WiFi.mode(WIFI_MODE_STA);
        WiFi.disconnect();
        xTaskCreatePinnedToCore(core_0_scan_wifi, "core_0_scan_wifi", 1024 * 2, NULL, 0, NULL, 0);
    }

    EventBits_t bit = xEventGroupGetBits(local_setting);
    if (bit & _BV(0))
    {
        lv_obj_add_state(sync_sw, LV_STATE_CHECKED);
    }
}