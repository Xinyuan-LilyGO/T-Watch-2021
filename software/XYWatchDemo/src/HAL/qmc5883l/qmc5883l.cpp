#include "./XYWatch_hal.h"

QMC5883LCompass MAG;
static int Azimuth;

void XYWatch::MAG_Init()
{

    MAG.init();
    if (MAG._readReg(0x0B) == 0x01)
        Serial.println("QMC5883L Successful connection");
    else
        Serial.println("QMC5883L not find");
    //MAG.setCalibration(0, 2433, -2528, 0, -467, 1760);
}
bool XYWatch::CheckMAGSensor()
{
}

void XYWatch::MAG_Updata(uint32_t millis, uint32_t time_ms)
{
    static uint32_t Millis;
    int x, y, z;
    static int cali[6];
    int new_Azimuth;
    if (millis - Millis > time_ms)
    {
        MAG.read();
        new_Azimuth = MAG.getAzimuth();
        Azimuth = (0.5 * Azimuth) + (0.5 * new_Azimuth);

        x = MAG.getX();
        y = MAG.getY();
        z = MAG.getZ();

        cali[0] = x < cali[0] ? x : cali[0];
        cali[1] = x > cali[1] ? x : cali[1];

        cali[2] = y < cali[2] ? y : cali[2];
        cali[3] = y > cali[3] ? y : cali[3];

        cali[4] = z < cali[4] ? z : cali[4];
        cali[5] = z > cali[5] ? z : cali[5];

        MAG.setCalibration(cali[0], cali[1], cali[2], cali[3], cali[4], cali[5]);

        Millis = millis;
    }
}

int XYWatch::MAG_GetValue() { return Azimuth; }
