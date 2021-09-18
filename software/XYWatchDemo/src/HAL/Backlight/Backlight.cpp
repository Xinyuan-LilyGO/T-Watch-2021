#include "./XYWatch_hal.h"

void XYWatch::Backlight_Init()
{
    pinMode(TFT_LED, OUTPUT);
    ledcSetup(0, 2000, 8);
    ledcAttachPin(TFT_LED, 0);
    ledcWrite(0, 0);
}

void XYWatch::Backlight_SetValue(int16_t val)
{
    if (val < 100)
        ledcWrite(0, (uint32_t)(val * 2.56));
    else
        ledcWrite(0, 0xFF);
}

uint16_t XYWatch::Backlight_GetValue()
{
    return (ledcRead(0) * 100) / 256;
}

void XYWatch::Backlight_GradualLight()
{
    static bool state;
    Serial.println("Gradually");
    if (state)
    {
        for (uint8_t i = 0; i < 100; i++)
        {
            delay(3);
            Backlight_SetValue(i);
        }
    }
    else
    {
        for (uint8_t i = 100; i > 0; i--)
        {
            delay(3);
            Backlight_SetValue(i);
        }
    }
    state = !state;
}
