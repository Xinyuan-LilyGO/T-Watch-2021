#include "TWatch_hal.h"

#if defined(TWatch_HAL_Display) && (TWatch_APP_LVGL == 1)
void lv_inc_loop(uint32_t millis, uint32_t time_ms)
{
    static uint32_t Millis;
    if (millis - Millis > time_ms)
    {
        lv_tick_inc(time_ms);
        Millis = millis;
    }
}
#endif

void TWatch::HAL_Init(void)
{
#if defined(TWatch_HAL_Display)
    Backlight_Init();
    Display_Init();
#endif
#if defined(TWatch_HAL_Touch)
    Touch_Init();
#endif
#if defined(TWatch_HAS_ENCODER)
    Encoder_Init();
#endif
#if defined(TWatch_HAL_Display) && (TWatch_APP_LVGL == 1)
    lv_init();
    lv_port_disp_init(tft);
    lv_port_indev_init(Touch);
#endif

#if defined(TWatch_HAS_SD)
    SD_Init();
    lv_fs_if_init();
#endif

//Bluetooth_Init("blue");
#if defined(TWatch_HAL_QMC5883L)
    MAG_Init();
#endif
#if defined(TWatch_HAL_PCF8563)
    RTC_Init();
#endif
#if defined(TWatch_HAL_BOTTON)
    Botton_Init();
#endif
#if defined(TWatch_HAL_MOTOR)
    Motor_Init();
    Motor_Shake(2, 50);
#endif
#if defined(TWatch_HAS_BME280)
    TempSensor_Init();
#endif

#if defined(TWatch_HAS_GPS)
    GPS_Init();
#endif
#if defined(TWatch_HAL_BMA423)
    AccSensor_Interface_Init();
    AccSensor_Init();
#endif

    /*     Time_Updata(1, 0);
    Backlight_SetValue(255);
    WIFI_Init(); */

    /* WIFI_Init();
    WIFI_Scan(); */
}

void Debugloop(uint32_t millis, uint32_t time_ms)
{
    static uint32_t Millis;
    if (millis - Millis > time_ms)
    {
        log_d("Total heap: %d", ESP.getHeapSize());
        log_d("Free heap: %d", ESP.getFreeHeap());
        log_d("Total PSRAM: %d", ESP.getPsramSize());
        log_d("Free PSRAM: %d", ESP.getFreePsram());
        Millis = millis;
    }
}

void TWatch::HAL_Update(void)
{
    static uint32_t ms;
    ms = millis();
#if defined(TWatch_HAL_Display) && (TWatch_APP_LVGL == 1)
    lv_inc_loop(ms, 5);
#endif
#if defined(TWatch_HAL_PCF8563)
    Time_Updata(ms, 1000);
#endif
#if defined(TWatch_HAL_QMC5883L)
    MAG_Updata(ms, 100);
#endif
#if defined(TWatch_HAL_BMA423)
    AccSensor_Updata(ms, 100);
#endif
#if defined(TWatch_HAL_BOTTON)
    Botton_Updata(ms, 10);
#endif
#if defined(TWatch_HAL_MOTOR)
    Motor_Loop(ms);
#endif
#if defined(TWatch_HAS_GPS)
    GPS_Parse();
#endif
#if defined(TWatch_HAS_BME280)
    TempSensor_Updata(ms, 41);
#endif
    Debugloop(ms, 1000);
}

void TWatch::HAL_Sleep()
{
    uint64_t mask;
    mask = 1ull << Touch_Int;
    Backlight_GradualLight();
    pinMode(IICSCL, INPUT_PULLUP);
    pinMode(IICSDA, INPUT_PULLUP);
    pinMode(Touch_Int, INPUT_PULLUP);
    pinMode(PWR_ON, OUTPUT);
    digitalWrite(PWR_ON, LOW);

    esp_sleep_enable_ext1_wakeup(mask, ESP_EXT1_WAKEUP_ALL_LOW); //Screen int
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_0 /* BTN_0 */, LOW);
    esp_deep_sleep_start();
}
