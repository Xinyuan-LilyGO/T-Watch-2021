// #include "FreeRTOS.h"
#include "TWatch_hal.h"
#include "WiFi.h"
#include "time.h"
#include "auto_calibration_time.h"
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 8 * 60 * 60;
const int daylightOffset_sec = 0;

static TWatchClass *ttgo;

static void core_0_get_network_time(void *param)
{
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return;
    }
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
    // ttgo->GetRTC()->syncToRtc();
    ttgo->SetRTCTime(timeinfo.tm_year, timeinfo.tm_mon, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    vTaskDelete(NULL);
}

void core_0_get_ntp(void)
{
    ttgo = TWatchClass::getWatch();
    xTaskCreatePinnedToCore(core_0_get_network_time, "core_0_get_network_time", 1024 * 2, NULL, 0, NULL, 0);
}