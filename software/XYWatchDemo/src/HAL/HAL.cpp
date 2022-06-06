#include "XYWatch_hal.h"

void lv_inc_loop(uint32_t millis, uint32_t time_ms)
{
    static uint32_t Millis;
    if (millis - Millis > time_ms)
    {
        lv_tick_inc(time_ms);
        Millis = millis;
    }
}

void XYWatch::HAL_Init(void)
{
    Display_Init();
    Touch_Init();
#if XYWATCH_HAS_ENCODER
    Encoder_Init();
#endif
    Backlight_Init();
    lv_init();
    lv_port_disp_init((TFT_eSPI *)Get_tft());
    lv_port_indev_init();
#if XYWATCH_HAS_SD
    SD_Init();
    lv_fs_if_init();
#endif

    MAG_Init();
    RTC_Init();
    Botton_Init();
    Motor_Init();
#if XYWATCH_HAS_BME280
    TempSensor_Init();
#endif

#if XYWATCH_HAS_GPS
    GPS_Init();
#endif
    AccSensor_Interface_Init();
    esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
    Serial.printf("wakeup_reason:%d\r\n", wakeup_reason);
    if (wakeup_reason == 0) //Sleep wake up without initialization
    {
        AccSensor_Init();
    }
    //SetRTCTime(2021, 9, 14, 18, 35, 10);
    Time_Updata(1, 0);
    Backlight_SetValue(255);
    WIFI_Init();
    Motor_Shake(2, 50);
    //AccSensor_OnStep(true, false);
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

void XYWatch::HAL_Update(void)
{
    static uint32_t ms;
    ms = millis();
    lv_inc_loop(ms, 5);
    Time_Updata(ms, 1000);
    MAG_Updata(ms, 100);
    AccSensor_Updata(ms, 100);
    Botton_Updata(ms, 10);
    Motor_Loop(ms);

#if XYWATCH_HAS_GPS
    GPS_Parse();
#endif
#if XYWATCH_HAS_BME280
    TempSensor_Updata(ms, 41);
#endif

    //Debugloop(ms, 1000);
}

void XYWatch::HAL_Sleep()
{
    uint64_t mask;
    mask = 1ull << 32;
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
