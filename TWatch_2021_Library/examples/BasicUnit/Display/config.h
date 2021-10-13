#ifndef __CONFIG_H__
#define __CONFIG_H__

#define TWatch2021_V1
// #define MyOptions   //Filter items yourself

#if !defined(TWatch2021_V1) && !defined(MyOptions)
#error Please choose a board or customize the function yourself
#endif

#ifdef TWatch2021_V1
#include "TWatch2021_V1.h"
#endif

#ifdef MyOptions
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
#define TWatch_HAL_GPS
#define TWatch_HAL_ENCODER
#define TWatch_HAL_SD
#endif

#endif