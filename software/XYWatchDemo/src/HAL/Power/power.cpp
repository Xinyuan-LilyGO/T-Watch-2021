#include "XYWatch_hal.h"

static uint8_t Pow_percent;
void XYWatch::Power_Init()
{
    pinMode(BAT_ADC, INPUT);
}

void XYWatch::Power_Updata(uint32_t millis, uint32_t time_ms)
{
    static uint32_t Millis;
    static uint32_t power_sub;
    static uint8_t cnt;
    if (millis - Millis > time_ms)
    {
        if (cnt < 50)
        {
            power_sub += analogRead(BAT_ADC);
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

uint16_t getBatteryRaw(void)
{
    pinMode(BAT_ADC, INPUT);
    return analogRead(BAT_ADC);
}

uint8_t XYWatch::Get_Power()
{

    uint16_t b = 0;
    uint8_t n = 20;
    // measure n times
    for (uint8_t i = 0; i < n; i++)
    {
        b = b + getBatteryRaw();
    }
    b = b / n;

    float vol = ((b * 3.3) / 4096 + 0.1);
    vol = vol < 1.4 ? 0 : (vol - 1.4) / 0.6 * 100;
    return constrain(vol, 0, 100);
}
