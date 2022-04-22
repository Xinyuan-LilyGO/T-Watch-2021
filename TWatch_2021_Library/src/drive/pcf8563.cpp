#include "./TWatch_hal.h"

#if defined(TWatch_HAL_PCF8563)

void TWatchClass::RTC_Init()
{
    Rtc = new PCF8563_Class;
    Wire.begin(TWATCH_IICSDA, TWATCH_IICSCL);
    Rtc->begin(Wire);
    Rtc->syncToSystem();
#if (USE_RTC_ALARM == 1)
    Rtc->enableAlarm();
#endif
}

void TWatchClass::GetRTCTime(uint8_t *hour, uint8_t *minute, uint8_t *second)
{
    *hour = LocalTime.hour;
    *minute = LocalTime.minute;
    *second = LocalTime.second;
}
void TWatchClass::GetRTCDate(uint16_t *year, uint8_t *month, uint8_t *day)
{
    *year = LocalTime.year;
    *month = LocalTime.month;
    *day = LocalTime.day;
}

void TWatchClass::SetRTCTime(uint16_t year, uint8_t month, uint8_t day,
                             uint8_t hour, uint8_t minute, uint8_t second)
{
    Rtc->setDateTime(year, month, day, hour, minute, second);
}
#if defined(USE_RTC_ALARM)
void TWatchClass::SetAlarmTime(uint8_t hour, uint8_t minute, uint8_t day, uint8_t weekday)
{
    Rtc->setAlarm(hour, minute, day, weekday);
}
#endif
RTC_Date TWatchClass::GetRTCTime()
{
    _is_time_updated = false;
    return LocalTime;
}

PCF8563_Class *TWatchClass::GetRTC()
{
    return Rtc;
}

void TWatchClass::Time_Updata(uint32_t millis, uint32_t time_ms)
{
    static uint32_t Millis;

    if (millis - Millis > time_ms)
    {
        LocalTime = Rtc->getDateTime();
        _is_time_updated = true;
        Millis = millis;
    }
}

bool TWatchClass::Time_isUpdated()
{
    return _is_time_updated;
}

#endif