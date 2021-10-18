#ifndef __TWatch_CONFIG_H__
#define __TWatch_CONFIG_H__

#define TWatch2021_V1

#ifdef TWatch2021_V1

// HAL
#include "TWatch2021_V1.h"
#define TWatch_HAL_Power
// #define TWatch_HAL_WIFI
// #define TWatch_HAL_BLE
#define TWatch_HAL_MOTOR
#define TWatch_HAL_Display
/* ├─ */ #define USE_TFT_DMA 0
/* ├─ */ #define TFT_Rotation 0 // 0-7
/* ├─ */
/* └─ */

#define TWatch_HAL_BOTTON
#define TWatch_HAL_BMA423
#define TWatch_HAL_QMC5883L
#define TWatch_HAL_PCF8563
#define TWatch_HAL_Touch

// APP
//#define TWatch_APP_LVGL 1

#endif

#endif /* __TWatch_CONFIG_H__ */