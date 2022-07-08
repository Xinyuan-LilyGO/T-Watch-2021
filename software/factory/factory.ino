#include "Arduino.h"
#include "ui_main.h"

#include <TWatch_hal.h>

static TWatchClass *ttgo = nullptr;

void btn2_event_cb(void *param) {
  ui_send_event_cb(TWATCH_BTN_2);
}
void btn3_event_cb(void *param) {
  ui_send_event_cb(TWATCH_BTN_3);
}
void btn1_event_cb(void *param) {
  ui_send_event_cb(TWATCH_BTN_1);
}

void encoder_btn_event_cb(void *param) {
  xEventGroupSetBits(ttgo->_hal_button_event, EVENT_CLICK_BIT(4));
}

void setup(void) {
  Serial.begin(115200);
  Serial.println("factory test");
  // esp_task_wdt_deinit();
  ttgo = TWatchClass::getWatch();
  ttgo->backlight_set_value(100);

  ttgo->button_bind_event(TWATCH_BTN_1, BUTTON_CLICK, btn1_event_cb, nullptr);
  ttgo->button_bind_event(TWATCH_BTN_2, BUTTON_CLICK, btn2_event_cb, nullptr);
  ttgo->button_bind_event(TWATCH_BTN_3, BUTTON_CLICK, btn3_event_cb, nullptr);
#if defined(TWatch2021_V2)
  ttgo->button_bind_event(TWATCH_ENCODER_BTN, BUTTON_CLICK, encoder_btn_event_cb, nullptr);
#endif
  ui_init();
  ttgo->hal_auto_update(true, 1);
}

void loop(void) {
}
