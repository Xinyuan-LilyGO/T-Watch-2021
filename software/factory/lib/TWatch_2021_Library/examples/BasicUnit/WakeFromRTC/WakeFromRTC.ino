#include <Arduino.h>
#include <TWatch_hal.h>
//"TWatch_config.h" needs to be configured in the library for the first time
// This routine needs to annotate the LVGL GUI

/*
T-Watch-2021-V1.0:  This version of the alarm clock and motion sensor use independent GPIO, no alarm interrupt pin
*/

/*
T-Watch-2021-V1.2:  Since the ESP32 pins are not enough, the interrupts of the alarm clock,
                    touch, and motion sensor are concentrated in the "TWATCH_AIO_INT" pin,
                    so the reason for the wake-up is all the external trigger "TWATCH_AIO_INT" to wake up.
*/

#if defined(TWatch2021_V1)
#error This version is not supported by the current experiment.
#endif
TWatchClass *twatch = nullptr;
TFT_eSPI *tft = nullptr;
PCF8563_Class *rtc = nullptr;
char buf[128];

void print_wakeup_reason() {
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();
  tft->setTextColor(TFT_GREEN, TFT_BLACK);
  switch (wakeup_reason) {
  case ESP_SLEEP_WAKEUP_EXT0:
    Serial.println("Wakeup caused by external signal using RTC_IO");
    tft->drawString("Wakeup caused by", 20, 144);
    tft->drawString("external signal using RTC_IO", 20, 162);
    break;
  case ESP_SLEEP_WAKEUP_EXT1:
    Serial.println("Wakeup caused by external signal using RTC_CNTL");
    tft->drawString("Wakeup caused by", 20, 144);
    tft->drawString("external signal using RTC_CNTL", 20, 162);
    break;
  case ESP_SLEEP_WAKEUP_TIMER:
    Serial.println("Wakeup caused by timer");
    tft->drawString("Wakeup caused by", 20, 144);
    tft->drawString(" timer", 20, 162);
    break;
  case ESP_SLEEP_WAKEUP_TOUCHPAD:
    Serial.println("Wakeup caused by touchpad");
    tft->drawString("Wakeup caused by", 20, 144);
    tft->drawString(" touchpad", 20, 162);
    break;
  case ESP_SLEEP_WAKEUP_ULP:
    Serial.println("Wakeup caused by ULP program");
    tft->drawString("Wakeup caused by ", 20, 144);
    tft->drawString("ULP program", 20, 162);
    break;
  default:
    Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason);
    break;
  }
  tft->setTextColor(TFT_WHITE, TFT_BLACK);
}

void setup() {
  twatch = TWatchClass::getWatch();
  tft = twatch->tft_get_instance();
  rtc = twatch->rtc_get_instance();
  Serial.begin(115200);
  twatch->motor_shake(2, 50);

  tft->fillScreen(TFT_BLACK);
  twatch->backlight_set_value(255);

  Serial.println("RTC Wake Up Demo");

  twatch->hal_auto_update(true, 0);

  tft->setTextFont(2);
  tft->setTextColor(TFT_WHITE, TFT_BLACK);
  tft->drawString("RTC Wake Up Demo", 62, 90);
  tft->drawString("Enter deep sleep after 5 seconds", 10, 108);
  tft->drawString("RTC wakes up after waiting for 5S", 20, 126);
  print_wakeup_reason();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);
  rtc->setDateTime(2021, 12, 21, 18, 04, 50);
  rtc->setAlarm(99, 05, 99, 99); // wake up after 5 seconds
  rtc->setAlarmByMinutes(5);
  twatch->hal_sleep(true);
}