#include "Spacer.h"
#include "./Software/utils/week/week.h"

static lv_obj_t *Clock;

static lv_point_t line_H1[] = {{28, 40}, {210, 40}};
static lv_point_t line_V1[] = {{130, -40}, {130, 40}};
static lv_point_t line_H2[] = {{10, 170}, {227, 170}};
static lv_point_t line_V2[] = {{144, 170}, {144, 205}, {72, 205}, {72, 230}};

static lv_obj_t *power;
static lv_obj_t *percent;

static lv_obj_t *second;
static lv_obj_t *hour;
static lv_obj_t *minut;
static lv_obj_t *colon;

static lv_obj_t *step;

static lv_obj_t *date_text;
static lv_obj_t *week_text;

static lv_obj_t *temp_text;
static lv_obj_t *weather_text;

static RTC_Date rtc;

static const char *host = "https://api.seniverse.com"; //心知天气APIhost
static const char *apiKey = "SOLy-aC_1gUQ-v6js";       //API key 私钥
static const char *city = "shenzhen";                  //查询的城市
//示例: https://api.seniverse.com/v3/weather/now.json?key=your_private_key&location=beijing&language=zh-Hans&unit=c

static StaticJsonDocument<500> doc;
static HTTPClient http_client;

void Spacer_timer(lv_timer_t *timer);
void Updata_event_cb(lv_event_t *e);

void SpacerClock(lv_obj_t *screen)
{
    Clock = lv_obj_create(screen);
    lv_obj_add_style(Clock, &WhiteStyle, 0);

    lv_obj_set_size(Clock, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_border_width(Clock, -12, 0);

    extern const uint8_t gif_spacer_map[];
    lv_obj_t *spacer = lv_gif_create_from_data(Clock, gif_spacer_map);
    lv_obj_align(spacer, LV_ALIGN_CENTER, 0, 18);

    power = lv_label_create(Clock);
    lv_obj_add_style(power, &IconBgStyle, 0);
    lv_obj_align(power, LV_ALIGN_TOP_MID, 30, 8);
    lv_label_set_text(power, LV_SYMBOL_BATTERY_FULL);

    percent = lv_label_create(Clock);
    lv_obj_add_style(percent, &Font_Nixie_18_Style, 0);
    lv_obj_align(percent, LV_ALIGN_TOP_MID, 35, 25);
    lv_label_set_text(percent, "89%");

    lv_obj_t *FrameLine1 = lv_line_create(Clock);
    lv_obj_t *FrameLine2 = lv_line_create(Clock);
    lv_obj_t *FrameLine3 = lv_line_create(Clock);
    lv_obj_t *FrameLine4 = lv_line_create(Clock);

    lv_obj_align(FrameLine1, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_align(FrameLine2, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_align(FrameLine3, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_align(FrameLine4, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_line_set_points(FrameLine1, line_H1, 2);
    lv_line_set_points(FrameLine2, line_V1, 2);
    lv_line_set_points(FrameLine3, line_H2, 2);
    lv_line_set_points(FrameLine4, line_V2, 4);

    lv_obj_add_style(FrameLine1, &Line_Small_Style, 0);
    lv_obj_add_style(FrameLine2, &Line_Small_Style, 0);
    lv_obj_add_style(FrameLine3, &Line_Small_Style, 0);
    lv_obj_add_style(FrameLine4, &Line_Small_Style, 0);

    hour = lv_label_create(Clock);
    lv_obj_add_style(hour, &Font_Nixie_70_Style, 0);
    lv_obj_align(hour, LV_ALIGN_CENTER, -70, -40);
    lv_label_set_text(hour, "00");

    minut = lv_label_create(Clock);
    lv_obj_add_style(minut, &Font_Nixie_70_Style, 0);
    lv_obj_align(minut, LV_ALIGN_CENTER, 25, -40);
    lv_label_set_text(minut, "00");

    colon = lv_label_create(Clock);
    lv_obj_add_style(colon, &Font_Nixie_70_Style, 0);
    //lv_obj_align(colon, LV_ALIGN_CENTER, -27, -40);
    lv_obj_align(colon, LV_ALIGN_CENTER, -15, -40);

    second = lv_label_create(Clock);
    lv_obj_add_style(second, &Font_Nixie_32_Style, 0);
    lv_obj_align(second, LV_ALIGN_CENTER, 80, -25);
    lv_label_set_text(second, "00");

    LV_IMG_DECLARE(img_foot_white);
    lv_obj_t *footlogo = lv_img_create(Clock);
    lv_img_set_src(footlogo, &img_foot_white);
    lv_obj_set_style_img_recolor_opa(footlogo, LV_OPA_100, 0);
    lv_obj_set_style_img_recolor(footlogo, lv_color_black(), 0);
    lv_obj_align(footlogo, LV_ALIGN_CENTER, 40, 35);

    step = lv_label_create(Clock);
    lv_obj_add_style(step, &Font_Nixie_18_Style, 0);
    lv_obj_align_to(step, footlogo, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
    lv_label_set_text(step, "12314");

    date_text = lv_label_create(Clock);
    lv_obj_add_style(date_text, &Font_Nixie_18_Style, 0);
    lv_obj_align(date_text, LV_ALIGN_LEFT_MID, 15, 10);
    lv_label_set_text(date_text, "2021.9.7");

    week_text = lv_label_create(Clock);
    lv_obj_add_style(week_text, &Font_Nixie_18_Style, 0);
    lv_obj_align(week_text, LV_ALIGN_LEFT_MID, 13, 30);
    lv_label_set_text(week_text, "Wednesday");

    temp_text = lv_label_create(Clock);
    lv_obj_add_style(temp_text, &Font_Nixie_32_Style, 0);
    lv_obj_align(temp_text, LV_ALIGN_TOP_LEFT, 64, 15);
    lv_label_set_text(temp_text, "31*C");

    weather_text = lv_label_create(Clock);
    lv_obj_add_style(weather_text, &Font_Nixie_32_Style, 0);
    lv_obj_align(weather_text, LV_ALIGN_LEFT_MID, 25, 68);
    lv_label_set_text(weather_text, "CLOUDY");

    lv_obj_t *UpBTN = lv_btn_create(Clock);

    lv_obj_add_event_cb(UpBTN, Updata_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_align(UpBTN, LV_ALIGN_CENTER, 50, 75);
    lv_obj_set_style_bg_color(UpBTN, lv_color_white(), 0);
    lv_obj_set_size(UpBTN, LV_PCT(20), LV_PCT(18));

    lv_obj_t *label = lv_label_create(UpBTN);
    lv_label_set_text(label, LV_SYMBOL_REFRESH);
    lv_obj_set_style_text_color(label, lv_color_black(), 0);
    lv_obj_center(label);

    lv_timer_t *timer = lv_timer_create(Spacer_timer, 500, nullptr);
}

void Spacer_timer(lv_timer_t *timer)
{
    static bool reversal;
    rtc = XYWatch::GetRTCTime();

    int32_t step_t = XYWatch::AccSensor_GetStep();
    uint8_t week = Day(rtc.year, rtc.month, rtc.day);

    lv_label_set_text_fmt(step, "%d", step_t);
    lv_label_set_text_fmt(date_text, "%d.%02d.%02d", rtc.year, rtc.month, rtc.day);
    lv_label_set_text_fmt(week_text, "%s", DAY_NAMES[week]);
    lv_label_set_text_fmt(hour, "%02d", rtc.hour);
    lv_label_set_text_fmt(minut, "%02d", rtc.minute);

    lv_label_set_text_fmt(colon, "%c", reversal ? ':' : ' ');
    reversal = !reversal;

    lv_label_set_text_fmt(second, "%02d", rtc.second);

    uint8_t p = XYWatch::Get_Power();
    lv_label_set_text_fmt(percent, "%d%%", p);
    lv_label_set_text(power, (p < 20 ? LV_SYMBOL_BATTERY_EMPTY : (p < 40 ? LV_SYMBOL_BATTERY_1 : (p < 60 ? LV_SYMBOL_BATTERY_2 : (p < 60 ? LV_SYMBOL_BATTERY_3 : LV_SYMBOL_BATTERY_FULL)))));
}

void Updata_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    String req;
    String rsp;

    if (code == LV_EVENT_CLICKED)
    {
        XYWatch::WIFI_Connect(WIFI_SSID, WIFI_PASS);

        req = (String)host + "/v3/weather/now.json?key=";
        req += apiKey;
        req += "&location=";
        req += city;
        req += "&language=en&unit=c";
        Serial.println(req);
        if (http_client.begin(req))
        {
            Serial.println("HTTPclient setUp done!");
        }

        int http_code = http_client.GET();
        if (http_code == HTTP_CODE_OK)
        {
            rsp = http_client.getString();
            //Serial.println(rsp);
            DeserializationError error = deserializeJson(doc, rsp);
            // Test if parsing succeeds.
            if (error)
            {
                Serial.print(F("deserializeJson() failed: "));
                Serial.println(error.f_str());
            }
        }

        const char *weather = doc["results"][0]["now"]["text"];
        const char *temperature = doc["results"][0]["now"]["temperature"];

        lv_label_set_text_fmt(temp_text, "%s*C", temperature);
        //lv_label_set_text_fmt(weather_text, "%s", weather);
        lv_label_set_text(weather_text, weather);
        XYWatch::WIFI_Stop();
    }
}
