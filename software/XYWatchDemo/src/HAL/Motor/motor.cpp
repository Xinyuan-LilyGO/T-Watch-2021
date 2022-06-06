#include "./XYWatch_hal.h"

static bool isShake;
static uint32_t _cnt, _interval_ms;
void XYWatch::Motor_Init()
{
    pinMode(Motor, OUTPUT);
    Motor_Stop();
}

void XYWatch::Motor_Shake(const uint32_t cnt, const uint32_t interval)
{
    _cnt = (cnt + 1) * 2;
    _interval_ms = interval;
    isShake = true;
}

void XYWatch::Motor_Loop(uint32_t millis)
{
    static uint32_t Millis;

    if (millis - Millis > _interval_ms && isShake)
    {
        digitalWrite(Motor, _cnt % 2);
        if (!--_cnt)
            Motor_Stop();
        Millis = millis;
    }
}

void XYWatch::Motor_Stop()
{
    digitalWrite(Motor, LOW);
    isShake = false;
    _cnt = 0;
    _interval_ms = 0xFFFFFFFF;
}
