#include "./TWatch_hal.h"

#if defined(TWatch_HAL_GPS)
HardwareSerial SerialGPS(1);
TinyGPSPlus gps;

void TWatch::GPS_Init()
{
    SerialGPS.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);
}

void TWatch::GPS_Parse()
{
    while (SerialGPS.available())
    {
        gps.encode(SerialGPS.read());
    }
}
#endif