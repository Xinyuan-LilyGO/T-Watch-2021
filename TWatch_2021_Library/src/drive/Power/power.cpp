#include "../../TWatch_hal.h"

#if defined(TWatch_HAL_Power)

void TWatchClass::Power_Init()
{
    pinMode(TWATCH_PWR_ON, OUTPUT);
    pinMode(TWATCH_BAT_ADC, INPUT);
    digitalWrite(TWATCH_PWR_ON, HIGH);
}

void TWatchClass::Power_Updata(uint32_t millis, uint32_t time_ms)
{
    static uint32_t Millis;
    static uint32_t power_sub;
    static uint8_t cnt;
    if (millis - Millis > time_ms)
    {
        if (cnt < 50)
        {
            power_sub += analogRead(TWATCH_BAT_ADC);
            cnt++;
        }
        else
        {
            uint32_t Pow = power_sub / cnt;
            float Volts = (Pow * 3.3 * 2 / 4096);
            Pow_percent = ((constrain(Volts, 3.7, 4.2) - 3.7) / 0.5) * 100;
            power_sub = cnt = 0;
            Serial.printf("Volts:%d\r\n", Pow);
        }

        Millis = millis;
    }
}

uint8_t TWatchClass::Get_Power()
{

    uint16_t b = 0;
    uint8_t n = 20;
    // measure n times
    for (uint8_t i = 0; i < n; i++)
    {
        b = b + analogRead(TWATCH_BAT_ADC);
    }
    b = b / n;

    float vol = ((b * 3.3) / 4096 + 0.1);
    vol = vol < 1.4 ? 0 : (vol - 1.4) / 0.6 * 100;
    return constrain(vol, 0, 100);
}

#endif