#ifndef __XYWATCH_HAL_H_
#define __XYWATCH_HAL_H_

#include "lvgl.h"
#include <Config/Config.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <TFT_eSPI.h>
#include "./Software/driver/Input.h"
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
#include "../src/Software/Pages/AppManager.h"
#include <../lv_lib_gif/lv_gif.h>
#include "WiFi.h"
#include "BluetoothSerial.h"
#include "HTTPClient.h"
#include <ArduinoJson.h>

namespace XYWatch
{
    void HAL_Init();
    void HAL_Update();
    void HAL_Sleep();

    void Power_Init();
    uint8_t Get_Power();
    void Power_Updata(uint32_t millis, uint32_t time_ms);

    /* WIFI */
    void WIFI_Init(void);
    uint8_t WIFI_Scan(void);
    bool WIFI_Connect(String ssid, String password, uint32_t waittime = 10000U);
    bool is_WIFI_Connected(void);
    void WIFI_Stop(void);
    WiFiClass Get_WIFI(void);

    /* Bluetooth */
    void Bluetooth_Init(String Name);
    void Bluetooth_Scan(char *Str, int Time);
    bool Bluetooth_Connect(String Name);
    void Bluetooth_Stop(void);
    //BluetoothSerial Bluetooth_Serial(void);

    void Motor_Init();
    void Motor_Shake(const uint32_t cnt, const uint32_t interval);
    void Motor_Loop(uint32_t millis);
    void Motor_Stop();

    /* Display */
    void Display_Init();
    void *Get_tft();

    /* Backlight */
    void Backlight_Init();
    void Backlight_SetValue(int16_t val);
    uint16_t Backlight_GetValue();
    void Backlight_GradualLight();

    /* Botton */
    void Botton_Init();
    void Botton_Updata(uint32_t millis, uint32_t time_ms);
    void Botton_BindEvent(uint8_t Btn, uint8_t Event, callbackFunction Screen);

    /* Acceleration Sensor : bma423 */
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

    /* MAG Sensor : qmc5883l*/
    bool CheckMAGSensor();
    void MAG_Init();
    void MAG_Updata(uint32_t millis, uint32_t time_ms);
    int MAG_GetValue();

    /* RTC : pcf8563 */
    void RTC_Init();
    void GetRTCTime(uint8_t *hour, uint8_t *minute, uint8_t *second);
    void GetRTCDate(uint16_t *year, uint8_t *month, uint8_t *day);
    void SetRTCTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
    void Time_Updata(uint32_t millis, uint32_t time_ms);
    RTC_Date GetRTCTime();

    /* Touch */
    void Touch_Init();
    bool Touch_Updata();
    uint16_t Touch_GetX();
    uint16_t Touch_GetY();

#if XYWATCH_HAS_BME280
    /* Temp Humidity Sensor : bme280 */
    void TempSensor_Init();
    void TempSensor_Updata(uint32_t millis, uint32_t time_ms);
    float TempSensor_GetTemperature();
    float TempSensor_GetPressure();
    float TempSensor_GetAltitude();
    float TempSensor_GetHumidity();
#endif

#if XYWATCH_HAS_GPS
    /* GPS : L76K */
    void GPS_Init();
    void GPS_Parse();
#endif

#if XYWATCH_HAS_ENCODER
    /* encoder */
    void Encoder_Init();
    int32_t Encoder_GetDiff();
    bool Encoder_GetIsPush();
#endif

#if XYWATCH_HAS_SD
    /* SD */
    bool SD_Init();
    void SD_Update();
    bool SD_GetReady();
    typedef void (*SD_CallbackFunction_t)(bool insert);
    void SD_SetEventCallback(SD_CallbackFunction_t callback);
#endif
}

#endif