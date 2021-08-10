#include <Wire.h>
#include "pcf8563.h"

PCF8563_Class rtc;

void setup()
{
    Serial.begin(115200);
    Wire.begin(26, 25);
    rtc.begin();
    rtc.setDateTime(2021, 6, 17, 18, 23, 59);
}

void loop()
{
    Serial.println(rtc.formatDateTime(PCF_TIMEFORMAT_YYYY_MM_DD_H_M_S));
    delay(1000);
}
