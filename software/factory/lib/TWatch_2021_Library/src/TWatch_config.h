#pragma once

/*
select board
If you don't know which one to choose, look at the silkscreen on the circuit board
*/

// #define TWatch2021_V1
// #define TWatch2021_V1_2
// #define TWatch2021_V2
/****************** Generic function, no need to be annotable *******************/
// BSP CONFIG
#define CONFIG_TWATCH_HAS_PSRAM
#define CONFIG_TWATCH_HAS_POWER
#define CONFIG_TWATCH_HAS_LFS
/*   ├─ */ #define LFS_MOUNT_POINT "/lfs"
#define CONFIG_TWATCH_HAS_MOTOR
#define CONFIG_TWATCH_HAS_DISPLAY
    /*   ├─ */ #define USE_TFT_DMA   0 // 0-1  If this option is enabled, DISP_BUF_FROM_PSRAM conflicts. Only one of the two can be enabled
    /*   ├─ */ #define TFT_ROTATION  0 // 0-7
    /*   ├─ */ #define SCREEN_WIDTH  240
    /*   ├─ */ #define SCREEN_HEIGHT 240

#define CONFIG_TWATCH_HAS_BUTTON
#define CONFIG_TWATCH_HAS_BMA423
#define CONFIG_TWATCH_HAS_QMC5883L
#define CONFIG_TWATCH_HAS_PCF8563
#define CONFIG_TWATCH_HAS_CST816S

// APP CONFIG
#define CONFIG_TWATCH_USE_DEBUG             1
#define CONFIG_TWATCH_APP_LVGL              1
    /*    ├─ */ #define DISP_BUF_SIZE       /**/ (SCREEN_WIDTH *SCREEN_HEIGHT * 0.5)
    /*    ├─ */ #define DISP_BUF_FROM_PSRAM 0 // Turning this on makes the screen appear smoother, but it uses a lot of RAM.
/*
Use LVGL built-in file system
SD: lv_img_set_src(wp, "A:/sd/logo.sjpg");
LFS: lv_img_set_src(wp, "A:/lfs/logo.jpg");
 */
#define CONFIG_TWATCH_APP_LVGL_LFS          1
/****************** Generic function, no need to be annotable *******************/

/************************* Version exclusive features ***************************/
#if defined(TWatch2021_V1)
#include "board/TWatch2021_V1.h"

#elif defined(TWatch2021_V1_2)
#include "board/TWatch2021_V1_2.h"

#define TWatch_HAL_AIO_INT // All in one.There is only one interrupt foot

    /*   ├─ */ #define USE_RTC_ALARM 1
#elif defined(TWatch2021_V2)
#include "board/TWatch2021_V2.h"

#define TWatch_HAL_AIO_INT // All in one.There is only one interrupt foot
    /*   ├─ */ #define USE_RTC_ALARM 1

#define CONFIG_TWATCH_HAS_GPS
#define CONFIG_TWATCH_HAS_SD
    /* ├─ */ #define SD_MOUNT_POINT  "/sd"
    /* ├─ */ #define SD_SPI_BUS      HSPI

#define CONFIG_TWATCH_HAS_ENCODER
#define CONFIG_TWATCH_HAS_BME280
#else

#error "Please define Watch model"

#endif
