// #ifndef __TWatch_HAL_H__
// #define __TWatch_HAL_H__
#pragma once

#include "TWatch_config.h"
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <Arduino.h>
#include "SPI.h"
#include <Wire.h>
#include "FS.h"
#include "FFat.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/queue.h"
#include "esp_task_wdt.h"
#if defined(TWatch_HAL_Display)
#include "libraries/TFT_eSPI/TFT_eSPI.h"
#endif
#if defined(TWatch_HAL_BOTTON)
#include "libraries/OneButton/src/OneButton.h"
#endif
#if defined(TWatch_HAL_Touch)
#include "libraries/Cst816s/CST816S.h"
#endif
#if defined(TWatch_HAL_ENCODER)
#include "libraries/Ai_Esp32_Rotary_Encoder/src/AiEsp32RotaryEncoder.h"
#endif
#if defined(TWatch_HAL_QMC5883L)
#include "libraries/QMC5883L-API/QMC5883LCompass.h"
#endif
#if defined(TWatch_HAL_GPS)
#include "libraries/TinyGPSPlus/src/TinyGPS++.h"
#endif
#if defined(TWatch_HAL_BME280)
#include "libraries/Adafruit_BME280_Library/Adafruit_BME280.h"
#include "libraries/Adafruit_Sensor/Adafruit_Sensor.h"
#endif
#if defined(TWatch_HAL_PCF8563)
#include "libraries/PCF8563_Library/src/pcf8563.h"
#endif
#if defined(TWatch_HAL_BMA423)
#include "libraries/BMA423-Sensor-API/bma423.h"
#endif
#if (TWatch_APP_LVGL == 1)
#include "libraries/lvgl/lvgl.h"
#endif
#include "soc/soc_ulp.h"
//#include "libraries/SdFat/src/SdFat.h"
/* #include "WiFi.h"
#include "libraries/BluetoothSerial/src/BluetoothSerial.h"
#include "HTTPClient.h" */
/* #include <ArduinoJson.h> */

#if (TWatch_DEBUG) == 1

#define DEBUG(x) Serial.print(x);
#define DEBUGLN(x) Serial.println(x);
#define DEBUGF(fmt, ...) Serial.printf(fmt, ##__VA_ARGS__);
#define _DEBUG_IS_RUN_LINE(name, param)              \
    do                                               \
    {                                                \
        DEBUGF("%s: %d " #name " : %" #param "\n", \
               __func__, __LINE__, name);            \
    } while (0);

#else
#define DEBUG(x) ;
#define DEBUGLN(x) ;
#define DEBUGF(fmt, ...) ;
#define _DEBUG_IS_RUN_LINE(name, param) ;
#endif

#define EVENT_IRQ_BIT (_BV(1))

#define TOUCH_IRQ_BIT (_BV(2))
#define ALARM_IRQ_BIT (_BV(3))
#define SPORTS_IRQ_BIT (_BV(4))

#define EVENT_CLICK_BIT(x) (_BV(0) << x)
#define EVENT_DOUBLE_CLICK_BIT(x) (_BV(4) << x)
#define EVENT_DURING_LONG_PRESS_BIT(x) (_BV(8) << x)

#define COLOR_NONE "\033[0m"
#define FONT_COLOR_RED "\033[0;31m"
#define FONT_COLOR_BLUE "\033[1;34m"
#define BACKGROUND_COLOR_RED "\033[41m"
#define BG_RED_FONT_YELLOW "\033[41;33m"

#define POWER_UPDATA_CYCLE 50

typedef TFT_eSPI SCREEN_CLASS;
typedef void (*irq_Fun_cb_t)(void *user_data_ptr);

class TWatchClass
{
    struct irq_bma_Fun_cb_t
    {
        irq_Fun_cb_t single_tap_cb;
        irq_Fun_cb_t double_tap_cb;
        irq_Fun_cb_t wrist_wear_cb;
        irq_Fun_cb_t step_cntr_cb;
        irq_Fun_cb_t activity_cb;
        irq_Fun_cb_t any_mot_cb;
        irq_Fun_cb_t no_mot_cb;
    };

private:
public:
    enum
    {
        Click = 0,
        DoubleClick,
        LongPressStart,
        LongPressStop,
        DuringLongPress
    };
    TWatchClass()
    {
        HAL_Init();
#if defined(TWatch_HAL_AIO_INT)
        pinMode(TWATCH_AIO_INT, INPUT);
        attachInterrupt(TWATCH_AIO_INT, _IRQ_AIO_event, FALLING);
#else
        pinMode(TWATCH_TOUCH_INT, INPUT_PULLUP);
        pinMode(TWATCH_BMA_INT_2, INPUT);
#endif
    };

    ~TWatchClass();

    static TWatchClass *getWatch()
    {
        if (_ttgo == nullptr)
        {
            _ttgo = new TWatchClass();
            _Hal_IRQ_event = xEventGroupCreate();
#if defined(TWatch_HAL_BOTTON)
            _hal_botton_event = xEventGroupCreate();
#endif
        }
        return _ttgo;
    }

    static TWatchClass *_ttgo;
    static EventGroupHandle_t _Hal_IRQ_event;
#if defined(TWatch_HAL_BOTTON)
    static EventGroupHandle_t _hal_botton_event;
#endif

    void HAL_Init();
    static void HAL_Update(void *param);
    void HAL_Sleep(bool deep);
    void HAL_AIO_IRQ_cb();
    void Auto_update_HAL(bool en, uint8_t core);
    static void _IRQ_AIO_event(void)
    {
        portBASE_TYPE task_woken, xResult;
        DEBUGLN("get irq");
        if ((xEventGroupGetBits(_ttgo->_Hal_IRQ_event) & EVENT_IRQ_BIT) != EVENT_IRQ_BIT)
        {
            xResult = xEventGroupSetBitsFromISR(_ttgo->_Hal_IRQ_event, EVENT_IRQ_BIT, &task_woken);
            if (xResult == pdTRUE)
            {
                portYIELD_FROM_ISR();
            }
        }
    }
#if defined(TWatch_HAL_Power)
    /* Power */
    void Power_Init();
    float Get_Power_Volt();
    float Get_Power_Percent();
    void Power_Updata(uint32_t millis, uint32_t time_ms);
#endif

#if defined(TWatch_HAL_WIFI)
    /* WIFI */
    void WIFI_Init(void);
    uint8_t WIFI_Scan(void);
    bool WIFI_Connect(String ssid, String password, uint32_t waittime = 10000U);
    bool is_WIFI_Connected(void);
    void WIFI_Stop(void);
    WiFiClass Get_WIFI(void);
#endif

#if defined(TWatch_HAL_BLE)
    /* Bluetooth */
    /*     void Bluetooth_Init(String Name);
        void Bluetooth_Scan(char *Str, int Time);
        bool Bluetooth_Connect(String Name);
        void Bluetooth_Stop(void); */
    // BluetoothSerial Bluetooth_Serial(void);
#endif

#if defined(TWatch_HAL_MOTOR)
    /* Motor */
    void Motor_Init();
    void Motor_Shake(const uint32_t cnt, const uint32_t interval);
    void Motor_Loop(uint32_t millis);
    void Motor_Stop();
#endif

#if defined(TWatch_HAL_Display)
    /* Display */
    void Display_Init();
    TFT_eSPI *Get_TFT();

    /* Backlight */
    void Backlight_Init();
    void Backlight_SetValue(int16_t val);
    int16_t Backlight_GetValue();
    void Backlight_GradualLight(int16_t val, uint32_t ms);
    void Backlight_Updata(uint32_t millis, uint32_t time_ms);
#endif

#if defined(TWatch_HAL_BOTTON)
    /* Botton */
    void Botton_Init();
    void Botton_Updata(uint32_t millis, uint32_t time_ms);
    void Botton_BindEvent(uint8_t Btn, uint8_t Event, callbackFunction Function);
    void Botton_BindEvent(uint8_t Btn, uint8_t Event, parameterizedCallbackFunction Function, void *parameter);
#endif

#if defined(TWatch_HAL_BMA423)
    /* Acceleration Sensor : bma423 */
    void AccSensor_Init();
    void AccSensor_Interface_Init();
    void AccSensor_Step_Reset();
    void AccSensor_Feature(uint8_t feature, bool Enable);
    void AccSensor_Feature_Int(uint8_t feature, bool Enable);
    void AccSensor_Acc_Feature(bool Enable);
    void AccSensor_Reset(void);
    void AccSensor_Updata(uint32_t millis, uint32_t time_ms);
    float AccSensor_GetX();
    float AccSensor_GetY();
    float AccSensor_GetZ();
    void AccSensor_Set_Feature_CB(uint8_t feature, irq_Fun_cb_t cb);
    uint32_t AccSensor_GetStep();
    float AccSensor_GetTemperature(uint8_t temp_unit);
#endif

#if defined(TWatch_HAL_QMC5883L)
    /* MAG Sensor : qmc5883l*/
    bool CheckMAGSensor();
    void MAG_Init();
    void MAG_Updata(uint32_t millis, uint32_t time_ms);
    int MAG_GetX();
    int MAG_GetY();
    int MAG_GetZ();
    int MAG_GetAzimuthValue();
#endif

#if defined(TWatch_HAL_PCF8563)
    /* RTC : pcf8563 */
    void RTC_Init();
    void GetRTCTime(uint8_t *hour, uint8_t *minute, uint8_t *second);
    void GetRTCDate(uint16_t *year, uint8_t *month, uint8_t *day);
    void SetRTCTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
    void Time_Updata(uint32_t millis, uint32_t time_ms);
    PCF8563_Class *GetRTC();
    RTC_Date GetRTCTime();
    RTC_Date LocalTime;
    bool Time_isUpdated();
#if defined(USE_RTC_ALARM)
    void SetAlarmTime(uint8_t hour, uint8_t minute, uint8_t day, uint8_t weekday);
#endif

#endif

#if defined(TWatch_HAL_Touch)
    /* Touch */
    void Touch_Init();
    bool Touch_Check();
    void Touch_Interrupt(bool enable = false);
    uint16_t Touch_GetX();
    uint16_t Touch_GetY();
    void Touch_Updata(uint32_t millis, uint32_t time_ms);

#endif

#if defined(TWatch_HAL_BME280)
    /* Temp Humidity Sensor : bme280 */
    Adafruit_BME280 *TempSensor = nullptr;
    float Temperature, Pressure, Altitude, Humidity;
    void TempSensor_Init();
    void TempSensor_Updata(uint32_t millis, uint32_t time_ms);
    float TempSensor_GetTemperature();
    float TempSensor_GetPressure();
    float TempSensor_GetAltitude();
    float TempSensor_GetHumidity();
#endif

#if defined(TWatch_HAL_GPS)
    /* GPS : L76K */
    void GPS_Init();
    void GPS_Parse();
#endif

#if defined(TWatch_HAL_ENCODER)
    /* encoder */
    static uint8_t BottonState = false;
    AiEsp32RotaryEncoder *Encoder = nullptr;
    void Encoder_Init();
    int32_t Encoder_GetDiff();
    bool Encoder_GetIsPush();
#endif

#if defined(TWatch_HAL_SD)
    /* SD */
    bool SD_Init();
    void SD_Update();
    bool SD_GetReady();
    typedef void (*SD_CallbackFunction_t)(bool insert);
    void SD_SetEventCallback(SD_CallbackFunction_t callback);
#endif

#if defined(TWatch_HAS_FFAT)
    /* FFAT */
    bool FFat_Init();
    bool is_FFat_Mounted();
    bool FFat_format(bool mount);
#endif

private:
    TaskHandle_t HAL_Update_Handle = NULL;
#if defined(TWatch_HAL_AIO_INT)
    irq_Fun_cb_t _alarm_irq_cb = nullptr;
    struct irq_bma_Fun_cb_t _bma_irq_cb = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
#endif

#if defined(TWatch_HAL_Power)
    /* Power */
    uint16_t _pow_temp[POWER_UPDATA_CYCLE];
    float _pow_percent = 0;
    float _pow_cur_vol = 0.0;
    bool _ischarge = false;
    uint32_t _power_sub = 0;
    uint8_t _power_cnt = 0;
#endif

#if defined(TWatch_HAL_MOTOR)
    /* Motor */
    bool isShake;
    uint32_t _cnt, _interval_ms;
#endif

#if defined(TWatch_HAL_Display)
    /* Display */
    TFT_eSPI *tft = nullptr;

    /* Backlight */
    bool _adjust = false;
    uint32_t _endtime;
    int16_t _old_Backlight;
    float _k;
#endif

#if defined(TWatch_HAL_Touch)
    /* Touch */
    CST816S_Class *Touch = nullptr;
#endif

#if defined(TWatch_HAL_BOTTON)
    /* Botton */
    OneButton *buttonLock = nullptr;
    OneButton *buttonMenu = nullptr;
    OneButton *buttonFastSet = nullptr;

#endif

#if defined(TWatch_HAL_BMA423)
    /* Acceleration Sensor : bma423 */
    float AccX, AccY, AccZ;
    uint32_t stepCount;
    bma4_dev *bma423 = nullptr;

#endif

#if defined(TWatch_HAL_PCF8563)
    /* RTC : pcf8563 */
    PCF8563_Class *Rtc = nullptr;
    bool _is_time_updated = false;
#endif
#if defined(TWatch_HAL_QMC5883L)
    /* MAG Sensor : qmc5883l*/
    QMC5883LCompass *MAG = nullptr;
    int Azimuth;
    int magX, magY, magZ;
#endif

#if defined(TWatch_HAS_FFAT)
    bool _is_ffat_mounted = false;

#endif

#if (TWatch_APP_LVGL == 1)
    lv_color_t *lv_disp_buf_p = nullptr;

    static void touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
    static void disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
    static void botton_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
    static void wrist_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);

    void lv_port_disp_init(SCREEN_CLASS *scr);
    void lv_port_indev_init(void);
    void lv_ffat_fs_if_init(void);
    // void display_send_DMA_done_cb(spi_transaction_t *trans);
#endif
    void tw_bubble_sort(uint16_t *arr, int len)
    {
        int i, j;
        uint16_t temp;
        for (i = 0; i < len - 1; i++)
            for (j = 0; j < len - 1 - i; j++)
                if (arr[j] > arr[j + 1])
                {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
    }
};

// #endif