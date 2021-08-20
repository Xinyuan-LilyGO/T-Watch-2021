/*
===============================================================================================================
QMC5883LCompass.h Library XYZ Example Sketch
Learn more at [https://github.com/mprograms/QMC5883LCompass]

This example shows how to get the XYZ values from the sensor.

===============================================================================================================
Release under the GNU General Public License v3
[https://www.gnu.org/licenses/gpl-3.0.en.html]
===============================================================================================================
*/
#include <QMC5883LCompass.h>

QMC5883LCompass compass;

void setup()
{
  Serial.begin(115200);
  pinMode(5, OUTPUT);
  digitalWrite(5, 1);
  Wire.begin(26, 25);
  for (int i = 0; i < 127; i++)
  {
    Wire.beginTransmission(i);
    int error = Wire.endTransmission();
    if (error == 0)
    {
      Serial.println();
      Serial.print("Device is found at : 0x");
      Serial.println(i, HEX);
    }
  }
  compass.init();
}

void loop()
{
  int a, x, y, z;

  // Read compass values
  compass.read();

  // Return XYZ readings
  x = compass.getX();
  y = compass.getY();
  z = compass.getZ();
  a = compass.getAzimuth();

  Serial.print("A: ");
  Serial.print(a);
  Serial.println();
  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.print(y);
  Serial.print(" Z: ");
  Serial.print(z);
  Serial.println();

  delay(250);
}
