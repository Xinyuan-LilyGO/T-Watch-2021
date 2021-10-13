#ifndef __TWatch_HAL_H__
#define __TWatch_HAL_H__

#include "lvgl.h"
//#include <Config/Config.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <TFT_eSPI.h>
#include "./drive/Lvgl_Driver/Input.h"
#include "OneButton.h"
#include <CST816S.h>
#include <AiEsp32RotaryEncoder.h>
#include <QMC5883LCompass.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <pcf8563.h>
#include <Wire.h>
#include <SPI.h>
#include "bma423.h"
#include <SdFat.h>
#include "WiFi.h"
#include "BluetoothSerial.h"
#include "HTTPClient.h"
#include <ArduinoJson.h>


class TWatch
{

public:
    void HAL_Init();
    void HAL_Update();
    void HAL_Sleep();

#if defined(TWatch_HAL_Power)
    static uint8_t Pow_percent;
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
    void Bluetooth_Init(String Name);
    void Bluetooth_Scan(char *Str, int Time);
    bool Bluetooth_Connect(String Name);
    void Bluetooth_Stop(void);
    //BluetoothSerial Bluetooth_Serial(void);
#endif

#if defined(TWatch_HAL_MOTOR)
    /* Motor */
    static bool isShake;
    static uint32_t _cnt, _interval_ms;
    void Motor_Init();
    void Motor_Shake(const uint32_t cnt, const uint32_t interval);
    void Motor_Loop(uint32_t millis);
    void Motor_Stop();
#endif

#if defined(TWatch_HAL_Display)
    /* Display */
    TFT_eSPI *tft = nullptr;
    void Display_Init();

    /* Backlight */
    void Backlight_Init();
    void Backlight_SetValue(int16_t val);
    uint16_t Backlight_GetValue();
    void Backlight_GradualLight();
#endif

#if defined(TWatch_HAL_BOTTON)
    /* Botton */
    OneButton *buttonLock = nullptr;
    OneButton *buttonMenu = nullptr;
    OneButton *buttonFastSet = nullptr;
    void Botton_Init();
    void Botton_Updata(uint32_t millis, uint32_t time_ms);
    void Botton_BindEvent(uint8_t Btn, uint8_t Event, callbackFunction Screen);
#endif

#if defined(TWatch_HAL_BMA423)
    /* Acceleration Sensor : bma423 */
    static float AccX, AccY, AccZ;
    static uint32_t stepCount;
    struct bma4_dev *bma423 = nullptr;
    bool CheckAccSensor();
    void AccSensor_Init();
    void AccSensor_Interface_Init();
    void AccSensor_OnStep(bool Step, bool Reset);
    void AccSensor_Sleep(bool Acc, bool Step);
    void AccSensor_GetStepValue(int32_t *val);
    void AccSensor_Updata(uint32_t millis, uint32_t time_ms);
    float AccSensor_GetX();
    float AccSensor_GetY();
    float AccSensor_GetZ();
    uint32_t AccSensor_GetStep();
#endif

#if defined(TWatch_HAL_QMC5883L)
    /* MAG Sensor : qmc5883l*/
    QMC5883LCompass *MAG = nullptr;
    static int Azimuth;
    bool CheckMAGSensor();
    void MAG_Init();
    void MAG_Updata(uint32_t millis, uint32_t time_ms);
    int MAG_GetValue();
#endif

#if defined(TWatch_HAL_PCF8563)
    /* RTC : pcf8563 */
    PCF8563_Class *Rtc = nullptr;
    static RTC_Date LocalTime;
    void RTC_Init();
    void GetRTCTime(uint8_t *hour, uint8_t *minute, uint8_t *second);
    void GetRTCDate(uint16_t *year, uint8_t *month, uint8_t *day);
    void SetRTCTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
    void Time_Updata(uint32_t millis, uint32_t time_ms);
    RTC_Date GetRTCTime();
#endif

#if defined(TWatch_HAL_Touch)
    /* Touch */
    CST816S *Touch = nullptr;
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
};

#endif