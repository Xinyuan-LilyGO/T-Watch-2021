#include "Setting.h"
#include "./Software/utils/week/week.h"

static RTC_Date rtc;
static lv_obj_t *Setting;

static lv_obj_t *dd_y;
static lv_obj_t *dd_m;
static lv_obj_t *dd_d;

static lv_obj_t *roller_h;
static lv_obj_t *roller_m;
static lv_obj_t *roller_s;

static const char *hour_opts = "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23";
static const char *second_opts = "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59";
static const char *year_opts = "2025\n2024\n2023\n2022\n2021\n2020\n2019\n2018\n2017\n2016\n2015\n2014\n2013\n2012\n2011\n2010\n2009\n2008\n2007\n2006\n2005\n2004\n2003\n2002\n2001\n2000";
static const char *month_opts = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12";
static const char *day_opts = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31";
static const char *btns[] = {"OK", ""};

static const char *ntpServer1 = "pool.ntp.org";
static const char *ntpServer2 = "ntp1.aliyun.com";
static const long gmtOffset_sec = 60 * 60 * 8;
static const int daylightOffset_sec = 0;

static void Confirm_event_cb(lv_event_t *e);
static void Auto_event_cb(lv_event_t *e);

void TotalSetting(lv_obj_t *screen)
{
    Setting = lv_obj_create(screen);

    lv_obj_add_style(Setting, &ThemeStyle, 0);
    lv_obj_set_size(Setting, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_border_width(Setting, -12, 0);
    lv_obj_clear_flag(Setting, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(Setting, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_style(Setting, &ThemeStyle, 0);
    //lv_obj_set_style_bg_color(Setting,lv_palette_lighten(),0);

    lv_obj_t *TotalText = lv_label_create(Setting);
    lv_obj_align(TotalText, LV_ALIGN_TOP_MID, 0, 20);
    lv_obj_add_style(TotalText, &Font_w_18_Style, 0);
    lv_label_set_text_fmt(TotalText, "Time Setting");

    dd_y = lv_dropdown_create(Setting);
    dd_m = lv_dropdown_create(Setting);
    dd_d = lv_dropdown_create(Setting);

    lv_dropdown_set_options_static(dd_y, year_opts);
    lv_obj_set_size(dd_y, LV_PCT(30), LV_PCT(15));
    lv_obj_align(dd_y, LV_ALIGN_CENTER, -65, -50);

    lv_dropdown_set_options_static(dd_m, month_opts);
    lv_obj_set_size(dd_m, LV_PCT(25), LV_PCT(15));
    lv_obj_align(dd_m, LV_ALIGN_CENTER, 5, -50);

    lv_dropdown_set_options_static(dd_d, day_opts);
    lv_obj_set_size(dd_d, LV_PCT(25), LV_PCT(15));
    lv_obj_align(dd_d, LV_ALIGN_CENTER, 70, -50);

    roller_h = lv_roller_create(Setting);
    lv_roller_set_options(roller_h, hour_opts, LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(roller_h, 3);
    lv_obj_align(roller_h, LV_ALIGN_CENTER, -70, 0);
    lv_roller_set_selected(roller_h, XYWatch::GetRTCTime().hour, LV_ANIM_ON);
    lv_obj_set_size(roller_h, LV_PCT(28), LV_PCT(25));

    roller_m = lv_roller_create(Setting);
    lv_roller_set_options(roller_m, second_opts, LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(roller_m, 3);
    lv_obj_align(roller_m, LV_ALIGN_CENTER, 0, 0);
    lv_roller_set_selected(roller_m, XYWatch::GetRTCTime().minute, LV_ANIM_ON);
    lv_obj_set_size(roller_m, LV_PCT(28), LV_PCT(25));

    roller_s = lv_roller_create(Setting);
    lv_roller_set_options(roller_s, second_opts, LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(roller_s, 3);
    lv_obj_align(roller_s, LV_ALIGN_CENTER, 70, 0);
    lv_roller_set_selected(roller_s, XYWatch::GetRTCTime().second, LV_ANIM_ON);
    lv_obj_set_size(roller_s, LV_PCT(28), LV_PCT(25));

    lv_obj_t *ConfirmBtn = lv_btn_create(Setting);

    lv_obj_add_event_cb(ConfirmBtn, Confirm_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_align(ConfirmBtn, LV_ALIGN_CENTER, -50, 60);
    lv_obj_set_size(ConfirmBtn, LV_PCT(25), LV_PCT(20));

    lv_obj_t *label = lv_label_create(ConfirmBtn);
    lv_label_set_text(label, LV_SYMBOL_OK);
    lv_obj_center(label);

    lv_obj_t *AutoBtn = lv_btn_create(Setting);

    lv_obj_add_event_cb(AutoBtn, Auto_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_align(AutoBtn, LV_ALIGN_CENTER, 50, 60);
    lv_obj_set_size(AutoBtn, LV_PCT(25), LV_PCT(20));

    label = lv_label_create(AutoBtn);
    lv_label_set_text(label, "Auto");
    lv_obj_center(label);
}

static void Confirm_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        uint16_t year;
        uint8_t month, day, hour, minute, second;
        char cache[10];
        lv_dropdown_get_selected_str(dd_y, cache, 0);
        year = String(cache).toInt();
        lv_dropdown_get_selected_str(dd_m, cache, 0);
        month = String(cache).toInt();
        lv_dropdown_get_selected_str(dd_d, cache, 0);
        day = String(cache).toInt();

        lv_roller_get_selected_str(roller_h, cache, 0);
        hour = String(cache).toInt();
        lv_roller_get_selected_str(roller_m, cache, 0);
        minute = String(cache).toInt();
        lv_roller_get_selected_str(roller_s, cache, 0);
        second = String(cache).toInt();
        XYWatch::SetRTCTime(year, month, day, hour, minute, second);
    }
}
static void Msg_event_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_current_target(e);
    lv_msgbox_close(obj);
}
static void Auto_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        XYWatch::WIFI_Connect(WIFI_SSID, WIFI_PASS);
        struct tm timeinfo;
        while (!getLocalTime(&timeinfo))
        {
            //init and get the time
            configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
            Serial.println("Failed to obtain time , try again");
        }
        XYWatch::SetRTCTime(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1,
                            timeinfo.tm_mday, timeinfo.tm_hour,
                            timeinfo.tm_min, timeinfo.tm_sec);
        XYWatch::WIFI_Stop();

        lv_obj_t *mbox1 = lv_msgbox_create(Setting, "New message", "The time has been automatically set.", btns, true);
        lv_obj_add_event_cb(mbox1, Msg_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
        lv_obj_center(mbox1);
    }
}
