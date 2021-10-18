#include <Arduino.h>
#include <TWatch_hal.h>

TWatchClass *twatch = nullptr;

void setup()
{
    twatch = new TWatchClass;
    Serial.begin(115200);
    twatch->Power_Init();

    Serial.println("Acc Demo");
    twatch->AccSensor_StepEnable(true, true);
    Serial.println("   X   |   Y   |   Z   |   step");
}

void loop()
{
    // put your main code here, to run repeatedly:
    static uint32_t Millis;
    twatch->HAL_Update();

    if (millis() - Millis > 1000)
    {
        Serial.printf("%2.3f |  %2.3f |  %2.3f  |   %d\r\n",
                      twatch->AccSensor_GetX(),
                      twatch->AccSensor_GetY(),
                      twatch->AccSensor_GetZ(),
                      twatch->AccSensor_GetStep());

        Millis = millis();
    }
}