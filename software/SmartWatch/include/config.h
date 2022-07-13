#ifndef CONFIG_H
#define CONFIG_H

#define DISP_W 240
#define DISP_H 240
// IMPORTANT DISP_H must be divisble by DISP_CHUNK_H!
#define DISP_CHUNK_H 8

// PLEASE CONFIGURE THE VALUES BELOW TO YOUR PREFERENCES

#define CONFIG_WIFI_SSID "your ssid"
#define CONFIG_WIFI_PASS "youe password"

/*
 * Here you can select the language of the compiled os. By compiling the language directly
 * into the os you loose the ability to switch it later on, but the compiled binary is way
 * smaller (and faster)!
 */
#include "locales/en-US.h"

#define DEVICE_NAME "MySmartWatch"
#define BLE_DEVICE_NAME DEVICE_NAME



// The following settings are configureable later on using the web ui, you can still set the defaults here.

// Timezone offset from GMT in hours. E.g. 10 = +10:00
#define CONFIG_TIMEZONE 8
// Daylight saving time offset in hours. E.g. 0.5 = 30 min
#define CONFIG_DAYLIGHTOFFSET 0
#define CONFIG_DATE_FORMAT "5/28/2021"

#define MINI_IOT_DEVICENAME "yourDeviceName"
#define MINI_IOT_SERVER "yourMiniIotServerIp:port"

// Experimentals:
//#define BLUETOOTH_COMPANION

#endif
