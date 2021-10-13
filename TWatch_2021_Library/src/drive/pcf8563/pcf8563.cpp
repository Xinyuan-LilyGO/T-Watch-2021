#include "./TWatch_hal.h"

#if defined(TWatch_HAL_PCF8563)

void TWatch::RTC_Init()
{
    Rtc = new PCF8563_Class;
    Wire.begin(IICSDA, IICSCL);
    Rtc->begin();
    //Rtc.check();
}
void TWatch::GetRTCTime(uint8_t *hour, uint8_t *minute, uint8_t *second)
{
    *hour = LocalTime.hour;
    *minute = LocalTime.minute;
    *second = LocalTime.second;
}
void TWatch::GetRTCDate(uint16_t *year, uint8_t *month, uint8_t *day)
{
    *year = LocalTime.year;
    *month = LocalTime.month;
    *day = LocalTime.day;
}

void TWatch::SetRTCTime(uint16_t year, uint8_t month, uint8_t day,
                        uint8_t hour, uint8_t minute, uint8_t second)
{
    Rtc->setDateTime(year, month, day, hour, minute, second);
}

RTC_Date TWatch::GetRTCTime()
{
    return Rtc->getDateTime();
}

void TWatch::Time_Updata(uint32_t millis, uint32_t time_ms)
{
    static uint32_t Millis;

    if (millis - Millis > time_ms)
    {
        LocalTime = Rtc->getDateTime();
        //Serial.printf("%d:%d:%d\r\n", LocalTime.hour, LocalTime.minute, LocalTime.second);
        Millis = millis;
    }
}

#endif