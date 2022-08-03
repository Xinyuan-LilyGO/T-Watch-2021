#include "./TWatch_hal.h"

#if defined(CONFIG_TWATCH_HAS_BUTTON)

void TWatchClass::button_init()
{
  buttonLock = new OneButton(TWATCH_BTN_1, true);
  buttonMenu = new OneButton(TWATCH_BTN_2, true);
  buttonFastSet = new OneButton(TWATCH_BTN_3, true);
#if defined(CONFIG_TWATCH_HAS_ENCODER)
  buttonEncoder = new OneButton(TWATCH_ENCODER_BTN, true);

  buttonEncoder->setClickTicks(100);
#endif

  buttonLock->setClickTicks(100);
  buttonMenu->setClickTicks(100);
  buttonFastSet->setClickTicks(100);
}

void TWatchClass::button_updata(uint32_t millis, uint32_t time_ms)
{
  static uint32_t Millis;
  if (millis - Millis > time_ms)
  {
    buttonLock->tick();
    buttonMenu->tick();
    buttonFastSet->tick();
#if defined(CONFIG_TWATCH_HAS_ENCODER)
    buttonEncoder->tick();
#endif
    Millis = millis;
  }
}

void TWatchClass::button_bind_event(uint8_t Btn, button_event_t Event, parameterizedCallbackFunction Function, void *parameter)
{
  OneButton *_btn;
  switch (Btn)
  {
  case TWATCH_BTN_1:
    _btn = buttonLock;
    break;
  case TWATCH_BTN_2:
    _btn = buttonMenu;
    break;
  case TWATCH_BTN_3:
    _btn = buttonFastSet;
    break;
#if defined(CONFIG_TWATCH_HAS_ENCODER)
  case TWATCH_ENCODER_BTN:
    _btn = buttonEncoder;
    break;
#endif
  default:
    break;
  }

  switch (Event)
  {
  case BUTTON_CLICK:
    _btn->attachClick((parameterizedCallbackFunction)Function, parameter);
    break;
  case BUTTON_DOUBLE_CLICK:
    _btn->attachDoubleClick((parameterizedCallbackFunction)Function, parameter);
    break;
  case BUTTON_LONG_PRESS_START:
    _btn->attachLongPressStart((parameterizedCallbackFunction)Function, parameter);
    break;
  case BUTTON_LONG_PRESS_STOP:
    _btn->attachLongPressStop((parameterizedCallbackFunction)Function, parameter);
    break;
  case BUTTON_DURING_LONG_PRESS:
    _btn->attachDuringLongPress((parameterizedCallbackFunction)Function, parameter);
    break;
  default:
    break;
  }
}

#endif