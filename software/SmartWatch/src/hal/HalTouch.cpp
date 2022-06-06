#include <Wire.h>
#include "osw_hal.h"
#include "osw_pins.h"
#include "focaltech.h"

#include "CST816S.h"

CST816S Touch;

void TouchInterrupt(void)
{
    Touch.TouchInt();
}

void OswHal::Init_Cst816s(void)
{
    uint8_t data;
    Wire.begin(SDA, SCL, 100000L);
    Touch.begin(Wire, Touch_Res, Touch_Int);
    Touch._readReg(0xA7, &data, 1);
    if (data = 0xB4)
        _hasCST816S = true;
}

bool OswHal::hasCST816S(void) { return _hasCST816S; }

void OswHal::Cst816s_Sleep(void)
{
    Touch.cst816s_deep_sleep();
}

uint8_t OswHal::Cst816s_GetType(void)
{
    return Touch.getTouchType();
}

uint16_t OswHal::Cst816s_GetX(void)
{
    return Touch.getX();
}

uint16_t OswHal::Cst816s_GetY(void)
{
    return Touch.getY();
}

void OswHal::Cst816s_Read(void)
{
    Touch.TouchInt();
}
