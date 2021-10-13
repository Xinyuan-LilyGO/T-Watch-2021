#ifndef __TWATCH2021_V1_H__
#define __TWATCH2021_V1_H__
//HAL
#define TWatch_HAL_Power
#define TWatch_HAL_WIFI
#define TWatch_HAL_BLE
#define TWatch_HAL_MOTOR
#define TWatch_HAL_Display
#define TWatch_HAL_BOTTON
#define TWatch_HAL_BMA423
#define TWatch_HAL_QMC5883L
#define TWatch_HAL_PCF8563
#define TWatch_HAL_Touch
//app
#define TWatch_APP_LVGL 1
//Pin definition

#define PWR_ON 5

#define Charging 2
#define BAT_ADC 36

#define BTN_1 0
#define BTN_2 34
#define BTN_3 35

#define Motor 4

#define TFT_CS 15
#define TFT_DC 19
#define TFT_RST 27
#define TFT_MOSI 13
#define TFT_MISO -1
#define TFT_SCK 14

#define TFT_LED 21

#define IICSCL 25
#define IICSDA 26

#define Touch_Res 33
#define Touch_Int 35
#define BMA_INT_1 22
#define BMA_INT_2 39

#endif