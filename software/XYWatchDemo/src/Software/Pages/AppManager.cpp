#include "AppManager.h"

static lv_obj_t *Dial_Screen;
static lv_obj_t *APP_Screen;
static lv_obj_t *LOGO_Screen;
LV_IMG_DECLARE(logoSetup);
void LogoSetup(void)
{
    LOGO_Screen = lv_obj_create(NULL);
    lv_obj_t *logo = lv_img_create(LOGO_Screen);
    lv_img_set_src(logo, &logoSetup);
    lv_obj_align(logo, LV_ALIGN_CENTER, 0, 0);
    lv_scr_load_anim(LOGO_Screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, true);
}

void XYWatchApp::AppInit()
{
    XYWatch::Botton_BindEvent(BTN_1, 0, XYWatch::HAL_Sleep);
    XYWatch::Botton_BindEvent(BTN_2, 0, Dial_Frame);
    /*XYWatch::Botton_BindEvent(BTN_3, 0, APP_Frame); */
    lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), LV_THEME_DEFAULT_DARK, &lv_font_montserrat_12);
    DialStyleInit();
    LogoSetup();
    //Dial_Frame();
}

void XYWatchApp::Dial_Frame()
{
    Serial.println("Dial_Frame Setup");
    //lv_obj_del(NULL);

    Dial_Screen = lv_tileview_create(NULL);
    //lv_scr_load(Dial_Screen);

    lv_obj_set_size(Dial_Screen, LV_PCT(100), LV_PCT(100));
    lv_obj_set_scrollbar_mode(Dial_Screen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *pointerclock_t = lv_tileview_add_tile(Dial_Screen, 0, 0, LV_DIR_ALL);
    lv_obj_t *digitalclock_t = lv_tileview_add_tile(Dial_Screen, 1, 0, LV_DIR_ALL);
    lv_obj_t *spacerclock_t = lv_tileview_add_tile(Dial_Screen, 2, 0, LV_DIR_ALL);
    lv_obj_t *compass_t = lv_tileview_add_tile(Dial_Screen, 0, 1, LV_DIR_ALL);
    lv_obj_t *console_t = lv_tileview_add_tile(Dial_Screen, 1, 1, LV_DIR_ALL);
    lv_obj_t *setting_t = lv_tileview_add_tile(Dial_Screen, 2, 1, LV_DIR_ALL);

    SimpleClock(pointerclock_t);
    DigitalClock(digitalclock_t);
    SpacerClock(spacerclock_t);
    CompassScreen(compass_t);
    Console(console_t);
    TotalSetting(setting_t);

    lv_scr_load_anim(Dial_Screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, true);
}

void XYWatchApp::APP_Frame()
{
    Serial.println("APP_Frame Setup");
    lv_obj_del(Dial_Screen);
    APP_Screen = lv_obj_create(lv_scr_act());
    lv_scr_load(APP_Screen);

    lv_obj_set_size(APP_Screen, LV_PCT(100), LV_PCT(100));
    //DigitalClock(APP_Screen);
}
