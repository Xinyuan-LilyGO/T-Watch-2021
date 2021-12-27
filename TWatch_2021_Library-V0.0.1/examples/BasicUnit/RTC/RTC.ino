#include <Arduino.h>
#include <TWatch_hal.h>

TWatchClass *twatch = nullptr;

void setup()
{
    twatch = new TWatchClass;
    Serial.begin(115200);
    twatch->Power_Init();

    Serial.println("RTC Demo");
    twatch->SetRTCTime(2021, 10, 18, 10, 56, 30);
}

void loop()
{
    // put your main code here, to run repeatedly:
    static uint32_t Millis;
    twatch->HAL_Update();

    if (millis() - Millis > 1000)
    {
        Serial.println(twatch->GetRTC_Class()->formatDateTime());
        Millis = millis();
    }
}