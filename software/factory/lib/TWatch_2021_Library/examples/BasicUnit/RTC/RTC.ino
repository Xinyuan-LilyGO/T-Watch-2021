#include <Arduino.h>
#include <TWatch_hal.h>
#include <WiFi.h>
//"TWatch_config.h" needs to be configured in the library for the first time
// This routine needs to annotate the LVGL GUI

TWatchClass *twatch = nullptr;
TFT_eSPI *tft = nullptr;
PCF8563_Class *rtc = nullptr;
/*****************Time synchronization parameters********************/
const char *ntpServer1 = "pool.ntp.org";
const char *ntpServer2 = "ntp1.aliyun.com";
const long gmtOffset_sec = 60 * 60 * 8;
const int daylightOffset_sec = 0;

const char *ssid = "your 2.4G wifi ssid";
const char *pass = "your password";

void SyncTime(void *param) {
  struct tm timeinfo;
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  // Synchronize RTC time
  while (!getLocalTime(&timeinfo)) {
    // init and get the time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer2, ntpServer1);
    Serial.println("Failed to obtain time , try again");
  }
  twatch->rtc_set_time(timeinfo.tm_year + 1900, timeinfo.tm_mon, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
  // disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void setup() {
  twatch = TWatchClass::getWatch();
  tft = twatch->tft_get_instance();
  rtc = twatch->rtc_get_instance();

  Serial.begin(115200);

  Serial.println("RTC Demo");

  twatch->hal_auto_update(true, 0);

  tft->fillScreen(TFT_BLACK);
  twatch->backlight_set_value(255);
  tft->setTextFont(2);
  tft->setTextColor(TFT_WHITE, TFT_BLACK);
  tft->drawString("T-Watch RTC Test", 62, 90);
  tft->drawString("Press BTN1 to synchronize time", 20, 108);
  twatch->button_bind_event(TWATCH_BTN_1, BUTTON_CLICK, SyncTime);

  twatch->rtc_set_time(2022, 2, 19, 10, 56, 30);
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println(rtc->formatDateTime(PCF_TIMEFORMAT_YYYY_MM_DD_H_M_S));
  tft->drawString(rtc->formatDateTime(PCF_TIMEFORMAT_YYYY_MM_DD), 90, 126);
  tft->drawString(rtc->formatDateTime(PCF_TIMEFORMAT_HMS), 95, 144);
  delay(1000);
}