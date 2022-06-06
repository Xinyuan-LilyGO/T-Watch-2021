#include "XYWatch_hal.h"

OneButton *buttonLock = nullptr;
OneButton *buttonMenu = nullptr;
OneButton *buttonFastSet = nullptr;

typedef enum
{
    Click = 0,
    DoubleClick,
    LongPressStart,
    LongPressStop,
    DuringLongPress
};

void XYWatch::Botton_Init()
{
    //buttonLock.attachClick(callback);
    buttonLock = new OneButton(BTN_1, true);
    buttonMenu = new OneButton(BTN_2, true);
    buttonFastSet = new OneButton(BTN_3, true);
}

void XYWatch::Botton_Updata(uint32_t millis, uint32_t time_ms)
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

void XYWatch::Botton_BindEvent(uint8_t Btn, uint8_t Event, callbackFunction Screen)
{
    OneButton *_btn;
    switch (Btn)
    {
    case BTN_1:
        _btn = buttonLock;
        break;
    case BTN_2:
        _btn = buttonMenu;
        break;
    case BTN_3:
        _btn = buttonFastSet;
        break;
    default:
        break;
    }

    switch (Event)
    {
    case Click:
        _btn->attachClick((callbackFunction)Screen);
        break;
    case DoubleClick:
        _btn->attachDoubleClick((callbackFunction)Screen);
        break;
    case LongPressStart:
        _btn->attachLongPressStart((callbackFunction)Screen);
        break;
    case LongPressStop:
        _btn->attachLongPressStop((callbackFunction)Screen);
        break;
    case DuringLongPress:
        _btn->attachDuringLongPress((callbackFunction)Screen);
        break;
    default:
        break;
    }
}