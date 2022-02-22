#include "./TWatch_hal.h"

#if defined(TWatch_HAL_BOTTON)

void TWatchClass::Botton_Init()
{
    buttonLock = new OneButton(TWATCH_BTN_1, true);
    buttonMenu = new OneButton(TWATCH_BTN_2, true);
    buttonFastSet = new OneButton(TWATCH_BTN_3, true);

    buttonLock->setClickTicks(100);
    buttonMenu->setClickTicks(100);
    buttonFastSet->setClickTicks(100);
}

void TWatchClass::Botton_Updata(uint32_t millis, uint32_t time_ms)
{
    static uint32_t Millis;
    if (millis - Millis > time_ms)
    {
        buttonLock->tick();
        buttonMenu->tick();
        buttonFastSet->tick();
        Millis = millis;
    }
}

void TWatchClass::Botton_BindEvent(uint8_t Btn, uint8_t Event, callbackFunction Function)
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
    default:
        break;
    }

    switch (Event)
    {
    case Click:
        _btn->attachClick((callbackFunction)Function);
        break;
    case DoubleClick:
        _btn->attachDoubleClick((callbackFunction)Function);
        break;
    case LongPressStart:
        _btn->attachLongPressStart((callbackFunction)Function);
        break;
    case LongPressStop:
        _btn->attachLongPressStop((callbackFunction)Function);
        break;
    case DuringLongPress:
        _btn->attachDuringLongPress((callbackFunction)Function);
        break;
    default:
        break;
    }
}

void TWatchClass::Botton_BindEvent(uint8_t Btn, uint8_t Event, parameterizedCallbackFunction Function, void *parameter)
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
    default:
        break;
    }

    switch (Event)
    {
    case Click:
        _btn->attachClick((parameterizedCallbackFunction)Function, parameter);
        break;
    case DoubleClick:
        _btn->attachDoubleClick((parameterizedCallbackFunction)Function, parameter);
        break;
    case LongPressStart:
        _btn->attachLongPressStart((parameterizedCallbackFunction)Function, parameter);
        break;
    case LongPressStop:
        _btn->attachLongPressStop((parameterizedCallbackFunction)Function, parameter);
        break;
    case DuringLongPress:
        _btn->attachDuringLongPress((parameterizedCallbackFunction)Function, parameter);
        break;
    default:
        break;
    }
}

#endif