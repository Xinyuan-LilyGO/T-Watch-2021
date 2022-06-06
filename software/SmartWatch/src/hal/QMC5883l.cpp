#include "./apps/tools/compass.h"
#include <math.h>
#include <QMC5883LCompass.h>
#include <gfx_util.h>
#include <osw_app.h>
#include <osw_hal.h>
#include <osw_pins.h>
#include <EEPROM.h>

QMC5883LCompass qmc5883;
int8_t Azimuth;

void OswHal::setupQmc5883(void)
{
    qmc5883.init();
    qmc5883._writeReg(0x0A, 0x01);                                 //Disabled hardware DRDY  *Hardware DRDY connection GPIO12, if not enabled will lead to a BUG when burning

    qmc5883.setCalibration(-1170, 1221, -1082, 1466, -1422, 1130); //Debugging data

    if (qmc5883._readReg(0x0B) == 0x01)
        _hasQMC5883L = true;
    else
        _hasQMC5883L = false;
}

void OswHal::qmc5883_Sleep(void)
{
    qmc5883.setReset();
    qmc5883.setMode(0x00, 0x00, 0x00, 0x00);
}

int OswHal::qmc5883_GetAzimuth(void)
{
    return qmc5883.getAzimuth();
}

int OswHal::qmc5883_GetX(void)
{
    return qmc5883.getX();
}

int OswHal::qmc5883_GetY(void)
{
    return qmc5883.getY();
}
int OswHal::qmc5883_GetZ(void)
{
    return qmc5883.getZ();
}

uint8_t OswHal::qmc5883_ReadReg(uint8_t add)
{
    return qmc5883._readReg(add);
}

void OswHal::qmc5883_Read(void)
{
    qmc5883.read();
}

void OswHal::qmc5883_setCalibration(int x_min, int x_max, int y_min, int y_max, int z_min, int z_max)
{
    qmc5883.setCalibration(x_min, x_max, y_min, y_max, z_min, z_max);
}

bool OswHal::hasQMC5883L(void) { return _hasQMC5883L; }