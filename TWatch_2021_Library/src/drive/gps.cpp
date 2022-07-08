#include "./TWatch_hal.h"

#if defined(CONFIG_TWATCH_HAS_GPS)

static const char SET_L76K_BAUDRATE[20] = {0xBA, 0xCE, 0x08, 0x00, 0x06, 0x00, 0xFF, 0x33, 0xC0, 0x08, 0x00, 0xC2, 0x01, 0x00, 0x07, 0xF6, 0xC7, 0x08 /* , 0x0D, 0x0A */};
void TWatchClass::gps_init() {
  pinMode(TWATCH_GPS_WAKE_UP, OUTPUT);
  digitalWrite(TWATCH_GPS_WAKE_UP, HIGH);
  Serial.begin(9600);
  while (!Serial.available())
    ;
  delay(100);
  Serial.write(SET_L76K_BAUDRATE, 20);
  delay(100);
  Serial.write(SET_L76K_BAUDRATE, 20);
  Serial.begin(115200);
}

void TWatchClass::gps_parse() {
  while (Serial.available()) {
    if (_gps_output2serial)
      Serial.write(Serial.read());
    else
      gps.encode(Serial.read());
  }
}

void TWatchClass::gps_serial_output(bool enable) {
  _gps_output2serial = enable;
}

TinyGPSPlus TWatchClass::get_gps_instance(void) {
  return gps;
}
#endif