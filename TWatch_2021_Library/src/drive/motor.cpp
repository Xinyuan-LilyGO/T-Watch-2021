#include "./TWatch_hal.h"

#if defined(TWatch_HAL_MOTOR)

void TWatchClass::Motor_Init()
{
    pinMode(TWATCH_MOTOR, OUTPUT);
    Motor_Stop();
}

void TWatchClass::Motor_Shake(const uint32_t cnt, const uint32_t interval)
{
    _cnt = (cnt + 1) * 2;
    _interval_ms = interval;
    isShake = true;
}

void TWatchClass::Motor_Loop(uint32_t millis)
{
    static uint32_t Millis;

    if (millis - Millis > _interval_ms && isShake)
    {
        digitalWrite(TWATCH_MOTOR, _cnt % 2);
        if (!--_cnt)
            Motor_Stop();
        Millis = millis;
    }
}

void TWatchClass::Motor_Stop()
{
    digitalWrite(TWATCH_MOTOR, LOW);
    isShake = false;
    _cnt = 0;
    _interval_ms = 0xFFFFFFFF;
}
#endif