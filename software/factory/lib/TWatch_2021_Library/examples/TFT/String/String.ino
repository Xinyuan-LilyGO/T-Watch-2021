#include <TWatch_hal.h>
//"TWatch_config.h" needs to be configured in the library for the first time
// This routine needs to annotate the LVGL GUI

TWatchClass *twatch = nullptr;
TFT_eSPI *tft = nullptr;
void setup() {
  twatch = TWatchClass::getWatch();

  Serial.begin(115200);
  twatch->motor_shake(2, 50);

  twatch->tft_get_instance()->fillScreen(TFT_BLACK);
  twatch->backlight_set_value(255);

  Serial.println("String Demo (TFT_eSPI)");

  tft = twatch->tft_get_instance();
  tft->setFreeFont(&FreeSans12pt7b);
  tft->setTextColor(TFT_WHITE, TFT_BLACK);
  tft->drawCentreString("Hello Lilygo", 120, 110, 1);
}

void loop() {
  // put your main code here, to run repeatedly:
}
