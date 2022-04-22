#pragma once

/*
select board
If you don't know which one to choose, look at the silkscreen on the circuit board
*/

// #define TWatch2021_V1
#define TWatch2021_V1_2

/****************** Generic function, no need to be annotable *******************/
// BSP CONFIG
// #define TWatch_HAL_PSRAM //V1 and V1.2 cannot be enabled on platformIO, causing a reset. They can be enabled on Arduino IDE
#define TWatch_HAL_Power 
// #define TWatch_HAL_WIFI
// #define TWatch_HAL_BLE
#define TWatch_HAS_FFAT
#define TWatch_HAL_MOTOR
#define TWatch_HAL_Display
    /*       ├─ */ #define USE_TFT_DMA 1 // 0-1
    /*   ├─ */ #define TFT_Rotation 0    // 0-7
    /*   ├─ */ #define SCREEN_WIDTH 240
    /*   ├─ */ #define SCREEN_HEIGHT 240

#define TWatch_HAL_BOTTON
#define TWatch_HAL_BMA423
#define TWatch_HAL_QMC5883L
#define TWatch_HAL_PCF8563
#define TWatch_HAL_Touch

// APP CONFIG
#define TWatch_DEBUG 1
#define TWatch_APP_LVGL 1
    /*    ├─ */ #define DISP_BUF_SIZE  (SCREEN_WIDTH * SCREEN_HEIGHT *0.5)

/****************** Generic function, no need to be annotable *******************/

/************************* Version exclusive features ***************************/
#if defined(TWatch2021_V1)
#include "board/TWatch2021_V1.h"

#elif defined(TWatch2021_V1_2)
#include "board/TWatch2021_V1_2.h"

#define TWatch_HAL_AIO_INT // All in one.There is only one interrupt foot
#define TWatch_HAL_QMC5883L
    /*   ├─ */ #define USE_RTC_ALARM 1
#else

#error "Please define Watch model"

#endif
