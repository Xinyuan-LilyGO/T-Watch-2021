#include "./XYWatch_hal.h"

CST816S touch;

void XYWatch::Touch_Init()
{
    Wire.begin(IICSDA, IICSCL, 100000L);
    touch.begin(Wire, Touch_Res, Touch_Int);
}

bool XYWatch::Touch_Updata() { return touch.ReadTouch(); }
uint16_t XYWatch::Touch_GetX() { return touch.getX(); }
uint16_t XYWatch::Touch_GetY() { return touch.getY(); }
