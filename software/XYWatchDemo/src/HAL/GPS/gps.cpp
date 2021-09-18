#include "./XYWatch_hal.h"
#if XYWATCH_HAS_GPS
HardwareSerial SerialGPS(1);
TinyGPSPlus gps;

void XYWatch::GPS_Init()
{
    SerialGPS.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);
}

void XYWatch::GPS_Parse()
{
    while (SerialGPS.available())
    {
        gps.encode(SerialGPS.read());
    }
}
#endif