#ifndef __TWatch_HAL_H__
#define __TWatch_HAL_H__

//#include <Config/Config.h>
#include <stdio.h>
#include <Arduino.h>
#include "SPI.h"
#include <Wire.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "libraries/TFT_eSPI/TFT_eSPI.h"
#include "libraries/OneButton/src/OneButton.h"
#include "libraries/Cst816s/CST816S.h"
#include "libraries/Ai_Esp32_Rotary_Encoder/src/AiEsp32RotaryEncoder.h"
#include "libraries/QMC5883L-API/QMC5883LCompass.h"
#include "libraries/TinyGPSPlus/src/TinyGPS++.h"
#include "libraries/Adafruit_BME280_Library/Adafruit_BME280.h"
#include "libraries/Adafruit_Sensor/Adafruit_Sensor.h"
#include "libraries/PCF8563_Library/src/pcf8563.h"
#include "libraries/BMA423-Sensor-API/bma423.h"
//#include "libraries/SdFat/src/SdFat.h"
/* #include "WiFi.h"
#include "libraries/BluetoothSerial/src/BluetoothSerial.h"
#include "HTTPClient.h" */
/* #include <ArduinoJson.h> */
#include "libraries/lvgl/lvgl.h"
#include "drive/Lvgl_Driver/Input.h"
#include "Config/TWatch_config.h"

typedef enum
{
    Click = 0,
    DoubleClick,
    LongPressStart,
    LongPressStop,
    DuringLongPress
};

class TWatchClass
{

public:
    TWatchClass() { HAL_Init(); };
    ~TWatchClass();

    void HAL_Init();
    void HAL_Update();
    void HAL_Sleep();

#if defined(TWatch_HAL_Power)
    /* Power */
    void Power_Init();
    uint8_t Get_Power();
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
    uint16_t Backlight_GetValue();
    //void Backlight_GradualLight();
#endif

#if defined(TWatch_HAL_BOTTON)
    /* Botton */
    void Botton_Init();
    void Botton_Updata(uint32_t millis, uint32_t time_ms);
    void Botton_BindEvent(uint8_t Btn, uint8_t Event, callbackFunction Function);
#endif

#if defined(TWatch_HAL_BMA423)
    /* Acceleration Sensor : bma423 */
    void AccSensor_Init();
    void AccSensor_Interface_Init();
    void AccSensor_StepEnable(bool Enable, bool Reset);
    void AccSensor_Sleep(bool Acc, bool Step);
    void AccSensor_Updata(uint32_t millis, uint32_t time_ms);
    float AccSensor_GetX();
    float AccSensor_GetY();
    float AccSensor_GetZ();
    uint32_t AccSensor_GetStep();
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
    PCF8563_Class *GetRTC_Class();
    RTC_Date GetRTCTime();
#endif

#if defined(TWatch_HAL_Touch)
    /* Touch */
    void Touch_Init();
    bool Touch_Updata();
    uint16_t Touch_GetX();
    uint16_t Touch_GetY();
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

private:
#if defined(TWatch_HAL_Power)
    /* Power */
    uint8_t Pow_percent;
#endif

#if defined(TWatch_HAL_MOTOR)
    /* Motor */
    bool isShake;
    uint32_t _cnt, _interval_ms;
#endif

#if defined(TWatch_HAL_Display)
    /* Display */
    TFT_eSPI *tft = nullptr;
#endif

#if defined(TWatch_HAL_Touch)
    /* Touch */
    CST816S *Touch = nullptr;
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
    RTC_Date LocalTime;
#endif
#if defined(TWatch_HAL_QMC5883L)
    /* MAG Sensor : qmc5883l*/
    QMC5883LCompass *MAG = nullptr;
    int Azimuth;
    int magX, magY, magZ;
#endif
};

#endif