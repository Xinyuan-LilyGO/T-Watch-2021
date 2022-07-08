#include <TWatch_hal.h>
#include "PageManager/PageManager.h"
#include "Utils/Utils.h"
#include "WiFi.h"
#include "esp_task_wdt.h"

static TWatchClass *ttgo = nullptr;

void btn2_event_cb(void *param)
{
  if (ttgo->_hal_botton_event)
  {
    xEventGroupSetBits(ttgo->_hal_botton_event, EVENT_CLICK_BIT(2));
  }
}
void btn3_event_cb(void *param)
{
  if (ttgo->_hal_botton_event)
  {
    xEventGroupSetBits(ttgo->_hal_botton_event, EVENT_CLICK_BIT(3));
  }
}
void btn1_event_cb(void *param)
{
  if (ttgo->_hal_botton_event)
  {
    xEventGroupSetBits(ttgo->_hal_botton_event, EVENT_CLICK_BIT(1));
  }
}

void setup(void)
{
  Serial.begin(115200);
  esp_task_wdt_deinit();
  ttgo = TWatchClass::getWatch();
  ttgo->Backlight_SetValue(100);

  ttgo->Botton_BindEvent(TWATCH_BTN_1, TWatchClass::Click, btn1_event_cb, nullptr);
  ttgo->Botton_BindEvent(TWATCH_BTN_2, TWatchClass::DuringLongPress, btn2_event_cb, nullptr);
  ttgo->Botton_BindEvent(TWATCH_BTN_3, TWatchClass::DuringLongPress, btn3_event_cb, nullptr);

  Page_Init();
  ttgo->Auto_update_HAL(true, 1);
}

void loop(void)
{
  Page_Loop();
}
