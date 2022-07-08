#include "./TWatch_hal.h"

#if defined(TWatch_HAL_BME280)
#define SEALEVELPRESSURE_HPA (1013.25)


void TWatchClass::TempSensor_Init()
{
    TempSensor = new Adafruit_BME280;
    Wire.begin(TWATCH_IICSDA, TWATCH_IICSCL);
    if (!TempSensor->begin(0x77, &Wire))
    {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
    }
    else
        Serial.println("BME280 Successful connection ");
    TempSensor->setSampling(Adafruit_BME280::MODE_NORMAL,
                            Adafruit_BME280::SAMPLING_X2,  // temperature
                            Adafruit_BME280::SAMPLING_X16, // pressure
                            Adafruit_BME280::SAMPLING_X1,  // humidity
                            Adafruit_BME280::FILTER_X16,
                            Adafruit_BME280::STANDBY_MS_0_5);
}

void TWatchClass::TempSensor_Updata(uint32_t millis, uint32_t time_ms)
{
    static uint32_t Millis;
    if (millis - Millis > time_ms)
    {
        Temperature = TempSensor->readTemperature();
        Pressure = TempSensor->readPressure();
        Altitude = TempSensor->readAltitude(SEALEVELPRESSURE_HPA);
        Humidity = TempSensor->readHumidity();
        Millis = millis;
    }
}

float TWatchClass::TempSensor_GetTemperature() { return Temperature; }
float TWatchClass::TempSensor_GetPressure() { return Pressure; }
float TWatchClass::TempSensor_GetAltitude() { return Altitude; }
float TWatchClass::TempSensor_GetHumidity() { return Humidity; }
#endif