#include "./TWatch_hal.h"

#if defined(TWatch_HAL_Touch)


void TWatch::Touch_Init()
{
    Touch = new CST816S;
    Wire.begin(IICSDA, IICSCL, 100000L);
    Touch->begin(Wire, Touch_Res, Touch_Int);
}

bool TWatch::Touch_Updata() { return Touch->ReadTouch(); }
uint16_t TWatch::Touch_GetX() { return Touch->getX(); }
uint16_t TWatch::Touch_GetY() { return Touch->getY(); }

#endif