#include "./TWatch_hal.h"

#if defined(TWatch_HAL_BME280)
#define SEALEVELPRESSURE_HPA (1013.25)


void TWatch::TempSensor_Init()
{
    TempSensor = new Adafruit_BME280;
    Wire.begin(IICSDA, IICSCL);
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

void TWatch::TempSensor_Updata(uint32_t millis, uint32_t time_ms)
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

float TWatch::TempSensor_GetTemperature() { return Temperature; }
float TWatch::TempSensor_GetPressure() { return Pressure; }
float TWatch::TempSensor_GetAltitude() { return Altitude; }
float TWatch::TempSensor_GetHumidity() { return Humidity; }
#endif