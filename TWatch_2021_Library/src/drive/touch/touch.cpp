#include "../../TWatch_hal.h"

#if defined(TWatch_HAL_Touch)

void TWatchClass::Touch_Init()
{
    Touch = new CST816S;
    Wire.begin(TWATCH_IICSDA, TWATCH_IICSCL, 100000);
    Touch->begin(Wire, TWATCH_TOUCH_RES, TWATCH_TOUCH_INT);
}

bool TWatchClass::Touch_Updata() { return Touch->ReadTouch(); }
uint16_t TWatchClass::Touch_GetX() { return Touch->getX(); }
uint16_t TWatchClass::Touch_GetY() { return Touch->getY(); }

#endif