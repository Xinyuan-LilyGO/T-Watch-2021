#include "wf_spacerman.h"
#include "WiFi.h"
static lv_obj_t *_src;

static lv_obj_t *time_label;
static lv_obj_t *sec_label;

static lv_obj_t *year_label;
static lv_obj_t *date_label;
static lv_obj_t *spacerman_gif;
static lv_obj_t *weather_icon;

static lv_obj_t *temp_label;

static lv_obj_t *step_label;

LV_IMG_DECLARE(gif_Atmosphere);
LV_IMG_DECLARE(gif_Clear);
LV_IMG_DECLARE(gif_Clouds);
LV_IMG_DECLARE(gif_Rain);
LV_IMG_DECLARE(gif_Snow);
LV_IMG_DECLARE(gif_Thunderstorm);

LV_FONT_DECLARE(spacerman_font_24);
LV_FONT_DECLARE(spacerman_font_48);

LV_IMG_DECLARE(gif_spacer);

static const char *month_names_def[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
static const char *Weather_condition_codes[6] = {"Thunderstorm", "Drizzle", "Rain", "Snow", "Clear", "Clouds"};
static const lv_img_dsc_t Weather_gif[7] = {gif_Thunderstorm, gif_Rain, gif_Rain, gif_Snow, gif_Clear, gif_Clouds, gif_Atmosphere};
void watchface_spacerman_init(lv_obj_t *src)
{
    _src = src;

    year_label = lv_label_create(_src);
    lv_obj_set_pos(year_label, 30, 50);
    lv_label_set_recolor(year_label, true);
    lv_obj_set_style_text_align(year_label, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(year_label, &spacerman_font_24, 0);
    lv_label_set_text(year_label, "2022");

    time_label = lv_label_create(_src);
    lv_obj_set_pos(time_label, 20, 75);
    lv_label_set_recolor(time_label, true);
    lv_obj_set_style_text_align(time_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_font(time_label, &spacerman_font_48, 0);
    lv_label_set_text(time_label, "#FF8000 12#:34");

    sec_label = lv_label_create(_src);
    // lv_obj_align(sec_label, LV_ALIGN_CENTER, 45, -20);
    lv_obj_align_to(sec_label, time_label, LV_ALIGN_OUT_RIGHT_BOTTOM, 10, 0);
    lv_label_set_recolor(sec_label, true);
    lv_obj_set_style_text_align(sec_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_font(sec_label, &spacerman_font_24, 0);
    lv_label_set_text(sec_label, ":#FF8000 56#");

    date_label = lv_label_create(_src);
    lv_obj_set_pos(date_label, 10, 110);
    lv_label_set_recolor(date_label, true);
    lv_label_set_long_mode(date_label, LV_LABEL_LONG_DOT);
    lv_obj_set_style_text_align(date_label, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(date_label, &lv_font_montserrat_20, 0);
    lv_label_set_text(date_label, month_names_def[0]);

    spacerman_gif = lv_gif_create(_src);
    lv_gif_set_src(spacerman_gif, &gif_spacer);
    lv_obj_set_pos(spacerman_gif, 50, 140);

    weather_icon = lv_gif_create(_src);
    lv_gif_set_src(weather_icon, &gif_Clear);
    lv_obj_set_pos(weather_icon, 170, 40);

    temp_label = lv_label_create(_src);
    lv_obj_set_pos(temp_label, 100, 140);
    lv_label_set_recolor(temp_label, true);
    lv_obj_set_style_text_align(temp_label, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(temp_label, &lv_font_montserrat_20, 0);
    lv_label_set_text(temp_label, "#FF8000 Temp:# ???");

    step_label = lv_label_create(_src);
    lv_obj_set_pos(step_label, 100, 165);
    lv_label_set_recolor(step_label, true);
    lv_obj_set_style_text_align(step_label, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(step_label, &lv_font_montserrat_20, 0);
    lv_label_set_text(step_label, "#FF8000 Step:# 0");
}

void watchface_spacerman_loop(lv_obj_t *screen, void *user_data)
{
    TWatchClass *ttgo = TWatchClass::getWatch();
    static uint32_t TenMinute;
    static RTC_Date ten_tm;
    if (ttgo->Time_isUpdated())
    {
        RTC_Date time = ttgo->GetRTCTime();

        int8_t hour = time.hour;
        int8_t minute = time.minute;
        lv_label_set_text_fmt(time_label, "#FF8000 %02d#:%02d", hour, minute);
        // lv_label_set_text_fmt(time_label, "%2d:%2d", hour, minute);
        lv_label_set_text_fmt(year_label, "#FF8000 %4d.#%2d.%2d", time.year, time.month + 1, time.day);
        lv_label_set_text_fmt(sec_label, ":#FF8000 %02d#", time.second);

        lv_label_set_text_fmt(date_label, "#FF8000 %s.#%s", month_names_def[time.month],
                              DAY_NAMES[1].c_str());

        lv_obj_align_to(sec_label, time_label, LV_ALIGN_OUT_RIGHT_BOTTOM, 10, 0);
        lv_label_set_text_fmt(step_label, "#FF8000 Step:# %d", ttgo->AccSensor_GetStep());
        if (WiFi.isConnected())
        {
            if (time.hour != ten_tm.hour)
            {
                weather_init();
                weather_update();
                ten_tm = time;
            }
            if (weather_is_updated())
            {
                String weather = weather_get_main_condition_codes();
                for (uint8_t i = 0; i < 7; i++)
                {
                    if ((i == 6) || weather.equals(Weather_condition_codes[i]))
                    {
                        lv_gif_set_src(weather_icon, &Weather_gif[i]);
                        break;
                    }
                }
                lv_label_set_text_fmt(temp_label, "#FF8000 Temp: #%.2f", weather_get_temp());
            }
        }
    }
}

void watchface_spacerman_close()
{
    weather_close();
}

LV_IMG_DECLARE(img_icon_by_watchface_select)
struct watchface_item_t watchface_spacerman =
    {
        .init = watchface_spacerman_init,
        .loop = watchface_spacerman_loop,
        .exit = watchface_spacerman_close,
        .icon = img_icon_by_watchface_select,
        .name = "Spacerman",
        .user_data = NULL,
};