#include "./TWatch_hal.h"

#if defined(CONFIG_TWATCH_HAS_PCF8563)

void TWatchClass::rtc_init() {
  Rtc = new PCF8563_Class;
  Wire.begin(TWATCH_IICSDA, TWATCH_IICSCL);

  if (Rtc->begin(Wire)) {
    _isinited_pcf8563 = true;
  }else{
    DEBUGLN("pcf8563 not find");
  }
  if (_isinited_pcf8563) {
    Rtc->syncToSystem();
  }

#if (USE_RTC_ALARM == 1)
  Rtc->enableAlarm();
#endif
}

void TWatchClass::rtc_get_time(uint8_t *hour, uint8_t *minute, uint8_t *second) {
  if (_isinited_pcf8563) {
    *hour = LocalTime.hour;
    *minute = LocalTime.minute;
    *second = LocalTime.second;
  }
}
void TWatchClass::rtc_get_date(uint16_t *year, uint8_t *month, uint8_t *day) {
  if (_isinited_pcf8563) {
    *year = LocalTime.year;
    *month = LocalTime.month;
    *day = LocalTime.day;
  }
}

void TWatchClass::rtc_set_time(uint16_t year, uint8_t month, uint8_t day,
                             uint8_t hour, uint8_t minute, uint8_t second) {
  if (_isinited_pcf8563) {
    Rtc->setDateTime(year, month, day, hour, minute, second);
  }
}
#if defined(USE_RTC_ALARM)
void TWatchClass::rtc_set_alarm_time(uint8_t hour, uint8_t minute, uint8_t day, uint8_t weekday) {
  if (_isinited_pcf8563) {
    Rtc->setAlarm(hour, minute, day, weekday);
  }
}
#endif
RTC_Date TWatchClass::rtc_get_time() {
  _is_time_updated = false;
  return LocalTime;
}

PCF8563_Class *TWatchClass::rtc_get_instance() {
  return Rtc;
}

void TWatchClass::rtc_updata(uint32_t millis, uint32_t time_ms) {
  static uint32_t Millis;

  if (millis - Millis > time_ms) {

    if (_isinited_pcf8563) {
      LocalTime = Rtc->getDateTime();
    }
    _is_time_updated = true;
    Millis = millis;
  }
}

bool TWatchClass::rtc_is_updated() {
  return _is_time_updated;
}

#endif