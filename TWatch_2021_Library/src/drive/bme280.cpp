#include "./TWatch_hal.h"

#if defined(CONFIG_TWATCH_HAS_BME280)
#define SEALEVELPRESSURE_HPA (1013.25)

void TWatchClass::bme280_init() {
  bme280 = new Adafruit_BME280;
  Wire.begin(TWATCH_IICSDA, TWATCH_IICSCL);
  if (!bme280->begin(0x77, &Wire)) {
    DEBUGLN("Could not find a valid BME280 sensor, check wiring!");
  } else
    _isinited_bme280 = true;
  bme280->setSampling(Adafruit_BME280::MODE_NORMAL,
                      Adafruit_BME280::SAMPLING_X2,  // temperature
                      Adafruit_BME280::SAMPLING_X16, // pressure
                      Adafruit_BME280::SAMPLING_X1,  // humidity
                      Adafruit_BME280::FILTER_X16,
                      Adafruit_BME280::STANDBY_MS_0_5);
}

void TWatchClass::bme280_updata(uint32_t millis, uint32_t time_ms) {
  static uint32_t Millis;
  if (millis - Millis > time_ms) {
    if (_isinited_bme280) {
      Temperature = bme280->readTemperature();
      Pressure = bme280->readPressure();
      Altitude = bme280->readAltitude(SEALEVELPRESSURE_HPA);
      Humidity = bme280->readHumidity();
    }
    Millis = millis;
  }
}

float TWatchClass::bme280_get_temperature() { return Temperature; }
float TWatchClass::bme280_get_pressure() { return Pressure; }
float TWatchClass::bme280_get_altitude() { return Altitude; }
float TWatchClass::bme280_get_humidity() { return Humidity; }

Adafruit_BME280 *TWatchClass::bme280_get_instance() { return bme280; }

#endif