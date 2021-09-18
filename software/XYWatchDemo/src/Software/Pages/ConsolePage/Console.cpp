#include "Console.h"
#define jump(TargetAddr)  (*((void(*)())(TargetAddr))()
static lv_obj_t *Cons;
static lv_obj_t *dd;
static lv_obj_t *RefreshBtn;
static lv_obj_t *ConfirmBtn;

static lv_obj_t *KT = NULL;

static lv_timer_t *Ctimer = NULL;
static bool isBegin;
static const char *btnm_map[] = {"kt1", "kt2", "\n",
                                 "kt3", "kt4", ""};

static void anim_timeline_create(bool positive);

static void Refresh_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED) //RefreshBtn
    {
        int n = XYWatch::WIFI_Scan();
        String str;

        for (uint8_t i = 0; i < n; i++)
        {
            str += XYWatch::Get_WIFI().SSID(i);
            str += "\n";
        }
        lv_dropdown_set_options(dd, str.c_str());
    }
}

void isConnect_timer(lv_timer_t *timer)
{
    if (!isBegin)
    {
        char ssid[50];
        memset(ssid, '\0', 50);
        lv_dropdown_get_selected_str(dd, ssid, 0);
        XYWatch::Get_WIFI().begin(String(ssid).c_str(), "XYdriver");
        isBegin = true;
    }
    if (XYWatch::Get_WIFI().status() == WL_CONNECTED)
    {
        lv_timer_del(Ctimer);
        lv_obj_set_style_bg_color(ConfirmBtn, lv_palette_main(LV_PALETTE_RED), 0);
        anim_timeline_create(true);
        XYWatch::Motor_Shake(2, 50);
    }
}
static void Connect_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED) //RefreshBtn
    {
        if (XYWatch::is_WIFI_Connected())
        {
            XYWatch::WIFI_Stop();
            isBegin = false;
            lv_obj_set_style_bg_color((lv_obj_t *)e->user_data, lv_palette_main(LV_PALETTE_BLUE), 0);
            anim_timeline_create(false);
        }
        else
        {
            if (!isBegin)
            {
                Ctimer = lv_timer_create(isConnect_timer, 500, nullptr);
            }
        }
    }
}

static void KT_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    WiFiClient client;

    if (code == LV_EVENT_VALUE_CHANGED) //ktBtn
    {
        XYWatch::Motor_Shake(1, 20);
        if (!client.connect(XYWatch::Get_WIFI().dnsIP().toString().c_str(), 80))
        {
            Serial.println("connection failed");
        }
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);
        const char *txt = lv_btnmatrix_get_btn_text(obj, id);
        client.print(String("GET /") + txt);
        /* uint32_t Millis = millis();
         while (!client.find("OK"))
        {
            if (millis() - Millis > 10)
                return;
        } */
    }
    client.stop();
}

void Console(lv_obj_t *screen)
{
    Cons = lv_obj_create(screen);
    lv_obj_add_style(Cons, &ThemeStyle, 0);

    lv_obj_set_size(Cons, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_border_width(Cons, -12, 0);

    lv_obj_clear_flag(Cons, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(Cons, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *label = lv_label_create(Cons);
    lv_label_set_text(label, "Relay Console");
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 20);


    dd = lv_dropdown_create(Cons);
    lv_dropdown_set_options(dd, "unfound");
    lv_obj_clear_flag(dd, LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_align(dd, LV_ALIGN_CENTER, 0, 0);
    //lv_obj_align(dd, LV_ALIGN_CENTER, -20, -60);
    //lv_obj_add_event_cb(dd, event_handler, LV_EVENT_ALL, NULL);

    RefreshBtn = lv_btn_create(Cons);

    lv_obj_add_event_cb(RefreshBtn, Refresh_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_align(RefreshBtn, LV_ALIGN_CENTER, -90, 0);

    label = lv_label_create(RefreshBtn);
    lv_label_set_text(label, LV_SYMBOL_REFRESH);
    lv_obj_center(label);

    ConfirmBtn = lv_btn_create(Cons);
    lv_obj_add_event_cb(ConfirmBtn, Connect_event_cb, LV_EVENT_ALL, ConfirmBtn);
    lv_obj_align(ConfirmBtn, LV_ALIGN_CENTER, 90, 0);
    //lv_obj_align(ConfirmBtn, LV_ALIGN_CENTER, 70, -60);
    //lv_obj_add_flag(ConfirmBtn, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_height(ConfirmBtn, LV_SIZE_CONTENT);

    label = lv_label_create(ConfirmBtn);
    lv_label_set_text(label, LV_SYMBOL_OK);
    lv_obj_center(label);

    KT = lv_btnmatrix_create(Cons);
    lv_btnmatrix_set_map(KT, btnm_map);
    /*     lv_btnmatrix_set_btn_width(KT, 10, 2);
    lv_btnmatrix_set_btn_ctrl(KT, 10, LV_BTNMATRIX_CTRL_CHECKABLE);
    lv_btnmatrix_set_btn_ctrl(KT, 11, LV_BTNMATRIX_CTRL_CHECKED); */
    lv_obj_align(KT, LV_ALIGN_CENTER, 0, 20);
    lv_obj_add_event_cb(KT, KT_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_clear_flag(KT, LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_set_size(KT, 0, 0);
    
}

/* animation */
static void dd_ExAnim_cb(void *obj, int32_t v)
{
    lv_obj_align(dd, LV_ALIGN_CENTER, -1 * (v), -3 * (v));
}

static void r_ExAnim_cb(void *obj, int32_t v)
{
    lv_obj_align(RefreshBtn, LV_ALIGN_CENTER, v, 0);
}

static void c_ExAnim_cb(void *obj, int32_t v)
{
    lv_obj_align(ConfirmBtn, LV_ALIGN_CENTER, 90 - (-1 * v / 3), v);
}

static void kt_ExAnim_cb(void *obj, int32_t v)
{
    lv_obj_set_size(KT, v, v < 120 ? v : 120);
}

static void anim_timeline_create(bool positive)
{
    lv_anim_t a1;
    lv_anim_t a2;
    lv_anim_t a3;
    lv_anim_t a4;

    lv_anim_init(&a1);
    lv_anim_set_var(&a1, dd);
    lv_anim_set_exec_cb(&a1, dd_ExAnim_cb);
    lv_anim_set_repeat_count(&a1, 0);
    lv_anim_init(&a2);
    lv_anim_set_var(&a2, RefreshBtn);
    lv_anim_set_exec_cb(&a2, r_ExAnim_cb);
    lv_anim_set_repeat_count(&a2, 0);
    lv_anim_init(&a3);
    lv_anim_set_var(&a3, ConfirmBtn);
    lv_anim_set_exec_cb(&a3, c_ExAnim_cb);
    lv_anim_set_repeat_count(&a3, 0);

    lv_anim_init(&a4);
    lv_anim_set_var(&a4, KT);
    lv_anim_set_exec_cb(&a4, kt_ExAnim_cb);
    lv_anim_set_repeat_count(&a4, 0);

    lv_anim_set_time(&a1, 500);
    lv_anim_set_time(&a2, 500);
    lv_anim_set_time(&a3, 500);
    lv_anim_set_time(&a4, 500);
    if (positive)
    {
        lv_anim_set_values(&a1, 0, 20);
        lv_anim_set_values(&a2, -90, -140);
        lv_anim_set_values(&a3, 0, -60);
        lv_anim_set_values(&a4, 0, 170);
    }
    else
    {
        lv_anim_set_values(&a1, 20, 0);
        lv_anim_set_values(&a2, -140, -90);
        lv_anim_set_values(&a3, -60, 0);
        lv_anim_set_values(&a4, 170, 0);
    }

    lv_anim_start(&a1);
    lv_anim_start(&a2);
    lv_anim_start(&a3);
    lv_anim_start(&a4);
}