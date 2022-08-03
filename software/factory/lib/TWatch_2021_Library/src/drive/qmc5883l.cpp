#include "./TWatch_hal.h"

#if defined(CONFIG_TWATCH_HAS_QMC5883L)

void TWatchClass::qmc5883l_init() {
  MAG = new QMC5883LCompass;
  // MAG->init(TWATCH_IICSDA, TWATCH_IICSCL);
  MAG->init();
  if (MAG->_readReg(0x0B) == 0x01) {
    _isinited_qmc5883l = true;
    MAG->setCalibration(0, 2433, -2528, 0, -467, 1760);
  } else
    DEBUGLN("qmc5883l not find");
}

void TWatchClass::qmc5883l_updata(uint32_t millis, uint32_t time_ms) {
  static uint32_t Millis;
  int x, y, z;
  static int cali[6];
  int new_Azimuth;
  if (millis - Millis > time_ms) {
    if (_isinited_qmc5883l) {
      MAG->read();
      new_Azimuth = MAG->getAzimuth();
      // Azimuth = (0.2 * Azimuth) + (0.8 * new_Azimuth);
      Azimuth = new_Azimuth;

      x = MAG->getX();
      y = MAG->getY();
      z = MAG->getZ();

      magX = MAG->getX();
      magY = MAG->getY();
      magZ = MAG->getZ();

      cali[0] = x < cali[0] ? x : cali[0];
      cali[1] = x > cali[1] ? x : cali[1];

      cali[2] = y < cali[2] ? y : cali[2];
      cali[3] = y > cali[3] ? y : cali[3];

      cali[4] = z < cali[4] ? z : cali[4];
      cali[5] = z > cali[5] ? z : cali[5];
      MAG->setCalibration(cali[0], cali[1], cali[2], cali[3], cali[4], cali[5]);
    }
    Millis = millis;
  }
}
int TWatchClass::qmc5883l_getX() { return magX; }
int TWatchClass::qmc5883l_getY() { return magY; }
int TWatchClass::qmc5883l_getZ() { return magZ; }
int TWatchClass::qmc5883l_get_Azimuth() { return Azimuth; }

#endif