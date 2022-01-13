#include <Arduino.h>
#include <TWatch_hal.h>

TWatchClass *twatch = nullptr;

void setup()
{
    twatch = TWatchClass::getWatch();
    twatch->HAL_Init();
    
    Serial.begin(115200);
    twatch->Power_Init();

    Serial.println("MAG Demo");
}

void loop()
{
    // put your main code here, to run repeatedly:
    static uint32_t Millis;
    twatch->HAL_Update();

    if (millis() - Millis > 1000)
    {
        Serial.printf("Azimuth : %d X : %d Y : %d Z : %d\r\n",
                      twatch->MAG_GetAzimuthValue(),
                      twatch->MAG_GetX(),
                      twatch->MAG_GetY(),
                      twatch->MAG_GetZ());
        Millis = millis();
    }
}