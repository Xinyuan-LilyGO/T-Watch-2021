#include "./TWatch_hal.h"

#if defined(CONFIG_TWATCH_HAS_CST816S)

void TWatchClass::touch_init() {
  touch = new CST816S_Class;
  Wire.begin(TWATCH_IICSDA, TWATCH_IICSCL);
  if (touch->begin(Wire, TWATCH_TOUCH_RES, TWATCH_TOUCH_INT))
    _isinited_cst816s = true;
  if (_isinited_cst816s) {
    touch->setTouchInt(false);
  }
}

void TWatchClass::touch_updata(uint32_t millis, uint32_t time_ms) {
  static uint32_t Millis;
  portBASE_TYPE xResult;
  if (millis - Millis > time_ms) {
    if (_isinited_cst816s) {
      if (touch->read()) {
        xResult = xEventGroupSetBits(_Hal_IRQ_event, TOUCH_IRQ_BIT);
        if (xResult == pdTRUE) {
          // Serial.println("touch event send done");
        }
      }
    }
    Millis = millis;
  }
}
void TWatchClass::touch_interrupt(bool enable) {
  if (_isinited_cst816s) {
    touch->setTouchInt(enable);
  }
}

bool TWatchClass::touch_check() { return touch->read(); }
uint16_t TWatchClass::touch_getX() { return touch->getX(); }
uint16_t TWatchClass::touch_getY() { return touch->getY(); }

#endif