#include "./TWatch_hal.h"

#if defined(CONFIG_TWATCH_HAS_MOTOR)

void TWatchClass::motor_init()
{
    pinMode(TWATCH_MOTOR, OUTPUT);
    motor_stop();
}

void TWatchClass::motor_shake(const uint32_t cnt, const uint32_t interval)
{
    _cnt = (cnt + 1) * 2;
    _interval_ms = interval;
    isShake = true;
}

void TWatchClass::motor_loop(uint32_t millis)
{
    static uint32_t Millis;

    if (millis - Millis > _interval_ms && isShake)
    {
        digitalWrite(TWATCH_MOTOR, _cnt % 2);
        if (!--_cnt)
            motor_stop();
        Millis = millis;
    }
}

void TWatchClass::motor_stop()
{
    digitalWrite(TWATCH_MOTOR, LOW);
    isShake = false;
    _cnt = 0;
    _interval_ms = 0xFFFFFFFF;
}
#endif