#include <TWatch_hal.h>
//"TWatch_config.h" needs to be configured in the library for the first time
// This routine needs to annotate the LVGL GUI

TWatchClass *twatch = nullptr;
TFT_eSPI *tft = nullptr;
static bool btn_sw = false;
static bool clean = false;

static int i, j;
static float last_X = 120;
static float last_Y = 1;
static float PointerX, PointerY;
void setup() {
  twatch = TWatchClass::getWatch();

  Serial.begin(115200);
  twatch->motor_shake(2, 50);

  twatch->tft_get_instance()->fillScreen(TFT_BLACK);
  twatch->backlight_set_value(255);
  twatch->button_bind_event(TWATCH_BTN_1, BUTTON_CLICK, [](void *param) { clean = true; });

  Serial.println("Edge color Demo (TFT_eSPI)");

  twatch->hal_auto_update(true, 0);

  tft = twatch->tft_get_instance();
  tft->setFreeFont(&FreeSans12pt7b);
  tft->setTextColor(TFT_WHITE, TFT_BLACK);
  tft->drawCentreString("Hello Lilygo", 120, 110, 1);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (clean) {
    clean = false;
    btn_sw = !btn_sw;
    i = 0;
    last_X = PointerX = 120;
    last_Y = PointerY = 1;
    tft->fillScreen(TFT_BLACK);
    tft->drawCentreString("Hello Lilygo", 120, 110, 1);
  }

  if (btn_sw) {
    if (i < 192) {
      tft->drawCircle(120, 120, (tft->height() / 2) - 1, rainbow(i));
      i++;
      delay(5);
    } else {
      i = 0;
    }
  } else {
    if (i < 360) {
      if (j > 192)
        j = 0;
      else
        j++;

      i++;
      PointerX = 120 + (sin(i * PI / 180) * 119);
      PointerY = 120 - (cos(i * PI / 180) * 119);
      tft->drawLine(last_X, last_Y, PointerX, PointerY, rainbow(i + j));
      last_X = PointerX;
      last_Y = PointerY;

      delay(10);
    } else {
      i = 0;
    }
  }
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
