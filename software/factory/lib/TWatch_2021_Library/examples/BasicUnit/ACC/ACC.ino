#include "TWatch_config.h"
#include "TWatch_hal.h"
#include <Arduino.h>

//"TWatch_config.h" needs to be configured in the library for the first time
// This routine needs to annotate the LVGL GUI

TWatchClass *twatch = nullptr;
TFT_eSPI *tft = nullptr;
bool isSingle_tag_irq, isDouble_tag_irq, isWrist_up_irq;

void single_tap_cb(void *p) { isSingle_tag_irq = true; }
void double_tap_cb(void *p) { isDouble_tag_irq = true; }
void wrist_cb(void *p) { isWrist_up_irq = true; }

void setup() {
  twatch = TWatchClass::getWatch();
  tft = twatch->tft_get_instance();

  Serial.begin(115200);
  twatch->motor_shake(2, 50);
  tft->fillScreen(TFT_BLACK);

  twatch->backlight_set_value(255);

  tft->setTextFont(2);
  tft->setTextColor(TFT_WHITE, TFT_BLACK);
  tft->drawString("Motion Sensor Demo Test", 42, 90);
  Serial.println("Motion Sensor Demo");

  twatch->bma423_feature(BMA423_STEP_CNTR | BMA423_WRIST_WEAR | BMA423_SINGLE_TAP | BMA423_DOUBLE_TAP, true);

  twatch->bma423_set_feature_event(BMA423_SINGLE_TAP_INT, single_tap_cb);
  twatch->bma423_set_feature_event(BMA423_DOUBLE_TAP_INT, double_tap_cb);
  twatch->bma423_set_feature_event(BMA423_WRIST_WEAR_INT, wrist_cb);

  twatch->bma423_feature_int(BMA423_SINGLE_TAP_INT | BMA423_DOUBLE_TAP_INT | BMA423_WRIST_WEAR_INT, true);

  Serial.println("   X   |   Y   |   Z   |   step");
  twatch->hal_auto_update(true, 1);
}

void loop() {
  // put your main code here, to run repeatedly:
  char buf[100];
  delay(10);
  sprintf(buf, "%02.3f | %02.3f | %02.3f | %03d\r\n", twatch->bma423_getX(), twatch->bma423_getY(), twatch->bma423_getZ(), twatch->bma423_get_step());
  Serial.printf(buf);
  tft->drawString("Motion Sensor Demo Test", 42, 90);
  tft->drawString("   X   |   Y   |   Z   |   step", 30, 108);
  tft->drawString(buf, 30, 126);

  if (isSingle_tag_irq) {
    isSingle_tag_irq = false;
    Serial.println("single_tap");
    tft->fillScreen(TFT_BLACK);
    tft->drawString("motion:  single_tap", 30, 146);
  } else if (isDouble_tag_irq) {
    isDouble_tag_irq = false;
    Serial.println("double_tap");
    tft->fillScreen(TFT_BLACK);
    tft->drawString("motion:  double_tap", 30, 146);
  } else if (isWrist_up_irq) {
    isWrist_up_irq = false;
    Serial.println("wrist up");
    tft->fillScreen(TFT_BLACK);
    tft->drawString("motion:  wrist up", 30, 146);
  }
}