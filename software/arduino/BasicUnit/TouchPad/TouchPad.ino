#include <Arduino.h>
#include <TWatch_hal.h>
//"TWatch_config.h" needs to be configured in the library for the first time
// This routine needs to annotate the LVGL GUI

TWatchClass *twatch = nullptr;
TFT_eSPI *tft = nullptr;

bool clear_irq = false;
uint16_t color;
uint8_t fill_order = 0;
bool isline = false;
int16_t last_x, last_y;
uint16_t point_x, point_y;

char buf[128];

void setup() {
  twatch = TWatchClass::getWatch();
  tft = twatch->tft_get_instance();

  Serial.begin(115200);
  twatch->motor_shake(2, 50);

  tft->fillScreen(TFT_BLACK);
  twatch->backlight_set_value(255);

  Serial.println("Touch Pad Demo (TFT_eSPI)");

  twatch->hal_auto_update(true, 0);

  tft->setTextFont(2);
  tft->setTextColor(TFT_WHITE, TFT_BLACK);
  tft->drawString("T-Watch Touch Test", 62, 90);

  twatch->button_bind_event(TWATCH_BTN_1, BUTTON_CLICK, [](void *param) { clear_irq = true; });
}

void loop() {
  // put your main code here, to run repeatedly:
  if (xEventGroupGetBits(twatch->_Hal_IRQ_event) & TOUCH_IRQ_BIT) {
    xEventGroupClearBits(twatch->_Hal_IRQ_event, TOUCH_IRQ_BIT);
    point_x = twatch->touch_getX();
    point_y = twatch->touch_getY();
    sprintf(buf, "x:%03d  y:%03d", point_x, point_y);
    tft->drawString(buf, 80, 118);
    if (!isline) {
      tft->drawPixel(point_x, point_y, color);
      isline = true;
    } else {
      tft->drawLine(point_x, point_y, last_x, last_y, color);
    }
    last_x = point_x;
    last_y = point_y;
  } else {
    color = random(TFT_BLACK, TFT_WHITE);
    isline = false;
  }
  delay(20);
  if (clear_irq) // Clear the screen
  {
    clear_irq = false;
    if (fill_order == 0) {
      tft->fillScreen(TFT_RED);
      fill_order++;
    } else if (fill_order == 1) {
      tft->fillScreen(TFT_GREEN);
      fill_order++;
    } else if (fill_order == 2) {
      tft->fillScreen(TFT_BLUE);
      fill_order++;
    } else if (fill_order == 3) {
      tft->fillScreen(TFT_WHITE);
      fill_order++;
    } else {
      tft->fillScreen(TFT_BLACK);
      fill_order = 0;
    }
  }
}