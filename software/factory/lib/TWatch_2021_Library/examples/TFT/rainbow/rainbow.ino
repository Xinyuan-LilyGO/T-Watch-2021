#include <TWatch_hal.h>
//"TWatch_config.h" needs to be configured in the library for the first time
// This routine needs to annotate the LVGL GUI

TWatchClass *twatch = nullptr;
TFT_eSPI *tft = nullptr;
void setup() {
  twatch = TWatchClass::getWatch();
  tft = twatch->tft_get_instance();

  Serial.begin(115200);
  twatch->motor_shake(2, 50);

  tft->fillScreen(TFT_BLACK);
  twatch->backlight_set_value(255);

  Serial.println("Rainbow Demo (TFT_eSPI)");

  twatch->hal_auto_update(true, 0);
}
uint16_t j = 0;
void loop() {
  // put your main code here, to run repeatedly:
  for (uint8_t i = 0; i < 240; i++) {
    tft->drawFastVLine(i, 0, 240, rainbow(i + j));
  }
  if (j >= 192)
    j = 0;
  else
    j++;
}

unsigned int rainbow(uint16_t value) {
  // If 'value' is in the range 0-159 it is converted to a spectrum colour
  // from 0 = red through to 127 = blue to 159 = violet
  // Extending the range to 0-191 adds a further violet to red band

  value = value % 192;

  byte red = 0;   // Red is the top 5 bits of a 16 bit colour value
  byte green = 0; // Green is the middle 6 bits, but only top 5 bits used here
  byte blue = 0;  // Blue is the bottom 5 bits

  byte sector = value >> 5;
  byte amplit = value & 0x1F;

  switch (sector) {
  case 0:
    red = 0x1F;
    green = amplit; // Green ramps up
    blue = 0;
    break;
  case 1:
    red = 0x1F - amplit; // Red ramps down
    green = 0x1F;
    blue = 0;
    break;
  case 2:
    red = 0;
    green = 0x1F;
    blue = amplit; // Blue ramps up
    break;
  case 3:
    red = 0;
    green = 0x1F - amplit; // Green ramps down
    blue = 0x1F;
    break;
  case 4:
    red = amplit; // Red ramps up
    green = 0;
    blue = 0x1F;
    break;
  case 5:
    red = 0x1F;
    green = 0;
    blue = 0x1F - amplit; // Blue ramps down
    break;
  }

  return red << 11 | green << 6 | blue;
}
