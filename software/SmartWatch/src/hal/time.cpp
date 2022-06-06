#include "pcf8563.h"
#include <time.h>
#include <sys/time.h>

#include <Wire.h>
#include <config.h>
#include <osw_config.h>

#include <map>
#include <string>

#include "osw_hal.h"

PCF8563_Class rtc;
const uint32_t My_Epoch32OfOriginYear = 946684800;
const uint8_t My_daysInMonth[] PROGMEM = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
uint32_t MyDaysSinceFirstOfYear2000(uint16_t year, uint8_t month, uint8_t dayOfMonth)
{
  uint32_t days = 0;
  for (uint8_t indexMonth = 1; indexMonth < month; ++indexMonth)
  {
    days += pgm_read_byte(My_daysInMonth + indexMonth - 1);
  }
  if (month > 2 && year % 4 == 0)
  {
    days++;
  }
  return days + 365 * year + (year + 3) / 4 - 1;
}

void OswHal::setupTime(void)
{
  Wire.begin(SDA, SCL, 100000L);
  rtc.begin();

  rtc.enableAlarm();

}

bool OswHal::hasPCF8563(void) { return getUTCTime() > 0; }

uint32_t OswHal::getUTCTime(void)
{
  uint32_t Epoch32Time = 0;
  RTC_Date t = rtc.getDateTime();

  uint32_t days = 0;
  days = MyDaysSinceFirstOfYear2000(t.year - 2000, t.month, t.day);

  Epoch32Time = ((days * 24L + t.hour) * 60 + t.minute) * 60 + t.second + My_Epoch32OfOriginYear;

  return Epoch32Time;
}

uint32_t OswHal::getLocalTime(void) { return getUTCTime() + 3600 * OswConfigAllKeys::timeZone.get() + (long)(3600 * OswConfigAllKeys::daylightOffset.get()); }

void OswHal::setUTCTime(long epoch)
{
  RtcDateTime t = RtcDateTime();
  t.InitWithEpoch32Time(epoch);
  rtc.setDateTime(t.Year(), t.Month(), t.Day(), t.Hour(), t.Minute(), t.Second());
}

void OswHal::getUTCTime(uint32_t *hour, uint32_t *minute, uint32_t *second)
{
  RtcDateTime d = RtcDateTime();
  d.InitWithEpoch32Time(getUTCTime());
  *hour = d.Hour();
  *minute = d.Minute();
  *second = d.Second();
}

void OswHal::getLocalTime(uint32_t *hour, uint32_t *minute, uint32_t *second)
{
  RtcDateTime d = RtcDateTime();
  d.InitWithEpoch32Time(getLocalTime());
  if (!OswConfigAllKeys::timeFormat.get())
  {
    if (d.Hour() > 12)
    {
      *hour = d.Hour() - 12;
    }
    else if (d.Hour() == 0)
    {
      *hour = 12;
    }
    else
    {
      *hour = d.Hour();
    }
  }
  else
  {
    *hour = d.Hour();
  }
  *minute = d.Minute();
  *second = d.Second();
}

void OswHal::getLocalTime(uint32_t *hour, uint32_t *minute, uint32_t *second, bool *afterNoon)
{
  RtcDateTime d = RtcDateTime();
  d.InitWithEpoch32Time(getLocalTime());
  if (!OswConfigAllKeys::timeFormat.get())
  {
    if (d.Hour() > 12)
    {
      *hour = d.Hour() - 12;
      *afterNoon = true;
    }
    else if (d.Hour() == 0)
    {
      *hour = 12;
      *afterNoon = false;
    }
    else if (d.Hour() == 12)
    {
      *hour = d.Hour();
      *afterNoon = true;
    }
    else
    {
      *hour = d.Hour();
      *afterNoon = false;
    }
  }
  else
  {
    *hour = d.Hour();
    *afterNoon = false;
  }
  *minute = d.Minute();
  *second = d.Second();
}

void OswHal::getDate(uint32_t *day, uint32_t *weekDay)
{
  RtcDateTime d = RtcDateTime();
  d.InitWithEpoch32Time(getLocalTime());
  *weekDay = d.DayOfWeek();
  *day = d.Day();
}

void OswHal::getDate(uint32_t *day, uint32_t *month, uint32_t *year)
{
  RtcDateTime d = RtcDateTime();
  d.InitWithEpoch32Time(getLocalTime());
  *day = d.Day();
  *month = d.Month();
  *year = d.Year();
}

void OswHal::getWeekdayString(int firstNChars, string *output)
{
  uint32_t day = 0;
  uint32_t weekDay = 0;
  getDate(&day, &weekDay);

  std::map<int, std::string> dayMap;

  dayMap[0] = LANG_SUNDAY;
  dayMap[1] = LANG_MONDAY;
  dayMap[2] = LANG_TUESDAY;
  dayMap[3] = LANG_WEDNESDAY;
  dayMap[4] = LANG_THURSDAY;
  dayMap[5] = LANG_FRIDAY;
  dayMap[6] = LANG_SATURDAY;

  string value = dayMap[weekDay];
  int valueLength = value.length();

  if (firstNChars == 0 || valueLength <= firstNChars)
  {
    *output = value;
  }

  *output = value.substr(0, firstNChars);
}

void OswHal::updateTimeViaNTP(long gmtOffset_sec, int daylightOffset_sec, uint32_t timeout_sec)
{
  long start = millis();
  if (getWiFi()->isConnected())
  {
    // this configures the timezone and sets the esps time to UTC
    configTime(gmtOffset_sec + 3600, daylightOffset_sec, "pool.ntp.org", "time.nist.gov");

    Serial.println("Waiting for time");

    while (!time(nullptr) && millis() - start < timeout_sec * 1000)
    {
      Serial.print(".");
      delay(1000);
    }

    // sometimes time(nullptr) returns seconds since boot
    // so check the request was resolved
    if (time(nullptr) > 1600000000)
    {
      Serial.println(time(nullptr));
      setUTCTime(time(nullptr));
    }
  }
}

void OswHal::pcf8563_sleep(void)
{
}