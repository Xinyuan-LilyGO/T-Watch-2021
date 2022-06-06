#include "./XYWatch_hal.h"

PCF8563_Class Rtc;
static RTC_Date LocalTime;

void XYWatch::RTC_Init()
{
    Wire.begin(IICSDA, IICSCL);
    Rtc.begin();
    //Rtc.check();
}
void XYWatch::GetRTCTime(uint8_t *hour, uint8_t *minute, uint8_t *second)
{
    *hour = LocalTime.hour;
    *minute = LocalTime.minute;
    *second = LocalTime.second;
}
void XYWatch::GetRTCDate(uint16_t *year, uint8_t *month, uint8_t *day)
{
    *year = LocalTime.year;
    *month = LocalTime.month;
    *day = LocalTime.day;
}

void XYWatch::SetRTCTime(uint16_t year, uint8_t month, uint8_t day,
                         uint8_t hour, uint8_t minute, uint8_t second)
{
    Rtc.setDateTime(year, month, day, hour, minute, second);
}

RTC_Date XYWatch::GetRTCTime()
{
    return Rtc.getDateTime();
}

void XYWatch::Time_Updata(uint32_t millis, uint32_t time_ms)
{
    static uint32_t Millis;

    if (millis - Millis > time_ms)
    {
        LocalTime = Rtc.getDateTime();
        //Serial.printf("%d:%d:%d\r\n", LocalTime.hour, LocalTime.minute, LocalTime.second);
        Millis = millis;
    }
}
