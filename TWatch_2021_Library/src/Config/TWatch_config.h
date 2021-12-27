#ifndef __TWatch_CONFIG_H__
#define __TWatch_CONFIG_H__

#define TWatch2021_V1
//#define TWatch2021_V1_1

#if defined(TWatch2021_V1)

// HAL
#include "TWatch2021_V1.h"
#define TWatch_HAL_Power
// #define TWatch_HAL_WIFI
// #define TWatch_HAL_BLE
#define TWatch_HAL_MOTOR
#define TWatch_HAL_Display
/*       ├─ */ #define USE_TFT_DMA 1
    /*   ├─ */ #define TFT_Rotation 0 // 0-7
    /*   ├─ */ #define SCREEN_WIDTH 240
    /*   ├─ */ #define SCREEN_HEIGHT 240

#define TWatch_HAL_BOTTON
#define TWatch_HAL_BMA423
#define TWatch_HAL_QMC5883L
#define TWatch_HAL_PCF8563
#define TWatch_HAL_Touch

// APP
//#define TWatch_APP_LVGL 1
#elif defined(TWatch2021_V1_1)

// HAL
#include "TWatch2021_V1_1.h"
#define TWatch_HAL_Power
#define TWatch_HAL_AIO_INT // All in one.There is only one interrupt foot
// #define TWatch_HAL_WIFI
// #define TWatch_HAL_BLE
#define TWatch_HAL_MOTOR
#define TWatch_HAL_Display
/*       ├─ */ #define USE_TFT_DMA 1
    /*   ├─ */ #define TFT_Rotation 0 // 0-7
    /*   ├─ */ #define SCREEN_WIDTH 240
    /*   ├─ */ #define SCREEN_HEIGHT 240

#define TWatch_HAL_BOTTON
#define TWatch_HAL_BMA423
#define TWatch_HAL_QMC5883L
    /*   ├─ */ #define USE_RTC_ALARM 1

#define TWatch_HAL_PCF8563
#define TWatch_HAL_Touch

#endif

// APP CONFIG
#define TWatch_DEBUG 1

#define TWatch_APP_LVGL 1
    /*    ├─ */ #define DISP_BUF_SIZE /*  */ ((SCREEN_WIDTH * SCREEN_HEIGHT) / 2)

#endif /* __TWatch_CONFIG_H__ */