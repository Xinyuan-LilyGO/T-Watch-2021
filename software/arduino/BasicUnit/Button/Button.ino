#include <Arduino.h>
#include <TWatch_hal.h>

//"TWatch_config.h" needs to be configured in the library for the first time
// This routine needs to annotate the LVGL GUI

TWatchClass *twatch = nullptr;
TFT_eSPI *tft = nullptr;

void btn1_click(void *param) {
  Serial.println("BTN1 Click");
  tft->drawString("BTN1 Click", 80, 118);
}
void btn2_click(void *param) {
  Serial.println("BTN2 Click");
  tft->drawString("BTN2 Click", 80, 118);
}
void btn3_click(void *param) {
  Serial.println("BTN3 Click");
  tft->drawString("BTN3 Click", 80, 118);
}

void setup() {
  twatch = TWatchClass::getWatch();
  tft = twatch->tft_get_instance();

  Serial.begin(115200);
  Serial.println("Button Demo (TFT_eSPI)");

  twatch->motor_shake(2, 50);

  tft->fillScreen(TFT_BLACK);
  twatch->backlight_set_value(255);

  twatch->hal_auto_update(true, 1);

  tft->setTextFont(2);
  tft->setTextColor(TFT_BLACK, TFT_WHITE);
  tft->drawString("T-Watch Button Test", 62, 90);

  twatch->button_bind_event(TWATCH_BTN_1, BUTTON_CLICK, btn1_click);
  twatch->button_bind_event(TWATCH_BTN_2, BUTTON_CLICK, btn2_click);
  twatch->button_bind_event(TWATCH_BTN_3, BUTTON_CLICK, btn3_click);
}

void loop() {
  // put your main code here, to run repeatedly:
}
