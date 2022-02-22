#include "./TWatch_hal.h"

#if defined(TWatch_HAL_Touch)

void TWatchClass::Touch_Init()
{
    Touch = new CST816S_Class;
    Wire.begin(TWATCH_IICSDA, TWATCH_IICSCL);
    Touch->begin(Wire, TWATCH_TOUCH_RES, TWATCH_TOUCH_INT);
    Touch->setTouchInt(false);
}

void TWatchClass::Touch_Updata(uint32_t millis, uint32_t time_ms)
{
    static uint32_t Millis;
    portBASE_TYPE xResult;
    if (millis - Millis > time_ms)
    {
        if (Touch->read())
        {
            xResult = xEventGroupSetBits(_Hal_IRQ_event, TOUCH_IRQ_BIT);
            if (xResult == pdTRUE)
            {
                // Serial.println("touch event send done");
            }
        }
        Millis = millis;
    }
}
void TWatchClass::Touch_Interrupt(bool enable)
{
    Touch->setTouchInt(enable);
}

bool TWatchClass::Touch_Check() { return Touch->read(); }
uint16_t TWatchClass::Touch_GetX() { return Touch->getX(); }
uint16_t TWatchClass::Touch_GetY() { return Touch->getY(); }

#endif