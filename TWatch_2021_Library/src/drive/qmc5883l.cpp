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

#elif defined(CONFIG_TWATCH_HAS_QMC5883P)

static void _writeReg(uint8_t addr,uint8_t *buffer ,uint32_t length)
{
    Wire.beginTransmission(0x2c);
    Wire.write(addr);
    Wire.write(buffer,length);
    Wire.endTransmission();
}

static void _readReg(uint8_t addr,uint8_t *buffer ,uint32_t length)
{
    Wire.beginTransmission(0x2c);
    Wire.write(addr);
    Wire.endTransmission();
    Wire.requestFrom(0x2c,length);
    Wire.readBytes(buffer,length);
}

static void _writeReg(uint8_t addr,uint8_t data)
{
  _writeReg(addr,&data,1);
}

void TWatchClass::qmc5883l_init() {
  Wire.beginTransmission(0x2C);
  _isinited_qmc5883l = Wire.endTransmission() == 0; 
  if(!_isinited_qmc5883l)return;
  _writeReg( 0x0d, 0x40 );
  delay( 10 );
  _writeReg( 0x29, 0x06 );
  delay( 10 );
  _writeReg( 0x0A, 0xCF );                               /* 0x0A = 0xC3/0xC7/0xCB/0xCF;  / *ODR = 10/50/100/200Hz,  MODE = continuous* / */
  delay( 10 );
  _writeReg( 0x0B, 0x00 );                               /* 0x0B = 0x00/0x04/0x08/0x0C;  / *RNG = ¡À 30G / ¡À 12G / ¡À 8G / ¡À 2G * / */
  delay( 10 );
}

void TWatchClass::qmc5883l_updata(uint32_t millis, uint32_t time_ms) {
    uint8_t		mag_data[6];
    short		hw_d[3] = { 0 };
    short		raw_c[3];
    int		t1	= 0;
    unsigned char	rdy	= 0;
    t1		= 0;
    /* Check status register for data availability */
    while ( !(rdy & 0x01) && (t1 < 5) )
    {
      rdy = 0x09;
      _readReg( 0x09, &rdy, 1 );
      t1++;
    }

    mag_data[0] = 0x01;

    _readReg( 0x01, mag_data, 6 );

    hw_d[0] = ( ( (mag_data[1]) << 8) | mag_data[0]);
    hw_d[1] = ( ( (mag_data[3]) << 8) | mag_data[2]);
    hw_d[2] = ( ( (mag_data[5]) << 8) | mag_data[4]);

    magX = hw_d[0];
    magY = hw_d[1];
    magZ = hw_d[2];

}

int TWatchClass::qmc5883l_getX() { return magX; }
int TWatchClass::qmc5883l_getY() { return magY; }
int TWatchClass::qmc5883l_getZ() { return magZ; }
int TWatchClass::qmc5883l_get_Azimuth() { return Azimuth; }


#endif