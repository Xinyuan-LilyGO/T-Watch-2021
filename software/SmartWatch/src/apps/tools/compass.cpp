#include "./apps/tools/compass.h"
#include <math.h>
#include <QMC5883LCompass.h>
#include <gfx_util.h>
#include <osw_app.h>
#include <osw_hal.h>
#include <osw_pins.h>

const int middleX = 120;
const int middleY = 120;
const double Pointerlength = 60;
const double PointerWidth = 15;

int calibrationData[3][2];
bool calibrationPrint = true;
bool changed = false;
bool done = false;
int t = 0;
int c = 0;

void OswAppCompass::calibration(OswHal *hal)
{
      int x, y, z;
      hal->qmc5883_Read();
      x = hal->qmc5883_GetX();
      y = hal->qmc5883_GetY();
      z = hal->qmc5883_GetZ();

      changed = false;

      if (x < calibrationData[0][0])
      {
            calibrationData[0][0] = x;
            changed = true;
      }
      if (x > calibrationData[0][1])
      {
            calibrationData[0][1] = x;
            changed = true;
      }

      if (y < calibrationData[1][0])
      {
            calibrationData[1][0] = y;
            changed = true;
      }
      if (y > calibrationData[1][1])
      {
            calibrationData[1][1] = y;
            changed = true;
      }

      if (z < calibrationData[2][0])
      {
            calibrationData[2][0] = z;
            changed = true;
      }
      if (z > calibrationData[2][1])
      {
            calibrationData[2][1] = z;
            changed = true;
      }

      if (changed && !done)
      {
            c = millis();
      }
      t = millis();
      if ((t - c > 5000) && !done)
      {
            done = true;
            hal->qmc5883_setCalibration(calibrationData[0][0],
                                        calibrationData[0][1],
                                        calibrationData[1][0],
                                        calibrationData[1][1],
                                        calibrationData[2][0],
                                        calibrationData[2][1]);
            Serial.println("DONE. Copy the line below and paste it into your projects sketch.);");
            Serial.println();

            Serial.print("compass.setCalibration(");
            Serial.print(calibrationData[0][0]);
            Serial.print(", ");
            Serial.print(calibrationData[0][1]);
            Serial.print(", ");
            Serial.print(calibrationData[1][0]);
            Serial.print(", ");
            Serial.print(calibrationData[1][1]);
            Serial.print(", ");
            Serial.print(calibrationData[2][0]);
            Serial.print(", ");
            Serial.print(calibrationData[2][1]);
            Serial.println(");");
      }
}

void OswAppCompass::drawCompass(OswHal *hal)
{
      hal->gfx()->fillCircle(middleX, middleY, 120, DARKGREY);
      hal->gfx()->fillCircle(middleX, middleY, 112, BLACK);
      hal->getCanvas()->drawFastHLine(0, 120, 240, DARKGREY);
      hal->getCanvas()->drawFastVLine(120, 0, 240, DARKGREY);
      hal->gfx()->fillCircle(middleX, middleY, 100, BLACK);
      hal->getCanvas()->setTextColor(WHITE, BLACK);
      hal->getCanvas()->setTextSize(3);
      hal->getCanvas()->setCursor(110, 25);
      hal->getCanvas()->print("N");
      hal->getCanvas()->setCursor(110, 200);
      hal->getCanvas()->print("S");
      hal->getCanvas()->setCursor(25, 110);
      hal->getCanvas()->print("W");
      hal->getCanvas()->setCursor(200, 110);
      hal->getCanvas()->print("E");
}
void OswAppCompass::drawPointer(OswHal *hal, const int Azimuth)
{

      double PointerRedX = middleX + (sin(Azimuth * PI / 180) * Pointerlength);
      double PointerRedY = middleY - (cos(Azimuth * PI / 180) * Pointerlength);
      double PointerBlueX = PointerRedX - (sin(Azimuth * PI / 180) * 2 * Pointerlength);
      double PointerBlueY = PointerRedY + (cos(Azimuth * PI / 180) * 2 * Pointerlength);

      double PointerWidthY1 = middleY - (sin(Azimuth * PI / 180) * PointerWidth);
      double PointerWidthX1 = middleX - (cos(Azimuth * PI / 180) * PointerWidth);
      double PointerWidthX2 = middleX + (cos(Azimuth * PI / 180) * PointerWidth);
      double PointerWidthY2 = middleY + (sin(Azimuth * PI / 180) * PointerWidth);

      hal->getCanvas()->fillTriangle(PointerRedX, PointerRedY,
                                     PointerWidthX1, PointerWidthY1, PointerWidthX2, PointerWidthY2, RED);
      hal->getCanvas()->fillTriangle(PointerBlueX, PointerBlueY,
                                     PointerWidthX1, PointerWidthY1, PointerWidthX2, PointerWidthY2, WHITE);
      hal->gfx()->fillCircle(middleX, middleY, 4, BLACK);
      hal->gfx()->fillCircle(middleX, middleY, 3, WHITE);

      //hal->getCanvas()->drawLine(middleX, middleY, PointerRedX, PointerRedY,WHITE);
      //hal->getCanvas()->drawLine(middleX, middleY, PointerBlueX, PointerBlueY,WHITE);
      //hal->getCanvas()->drawLine(PointerWidthX1, PointerWidthY1, middleX, middleY,WHITE);
      //hal->getCanvas()->drawLine(middleX, middleY, PointerWidthX2, PointerWidthY2,WHITE);
}

void OswAppCompass::setup(OswHal *hal)
{
      hal->setupQmc5883();
}

void OswAppCompass::loop(OswHal *hal)
{
      Graphics2D *gfx = hal->getCanvas()->getGraphics2D();
      if (hal->btnHasGoneDown(BUTTON_2))
      {
            memset(calibrationData, 0, 6);
            calibrationPrint = true;
            changed = false;
            done = false;
      }

      switch (done)
      {
      case false:
            if (calibrationPrint)
            {
                  calibrationPrint = false;
                  hal->getCanvas()->fillScreen(ui->getBackgroundColor());
                  hal->getCanvas()->setTextColor(WHITE, BLACK);
                  hal->getCanvas()->setTextSize(2);
                  hal->getCanvas()->setCursor(20, 62);
                  hal->getCanvas()->print("CALIBRATING...");
                  hal->getCanvas()->setCursor(10, 78);
                  hal->getCanvas()->print("Keep moving your ");
                  hal->getCanvas()->setCursor(10, 94);
                  hal->getCanvas()->print("sensor around.");
                  hal->requestFlush();
            }
            calibration(hal);

            break;

      default:
            hal->getCanvas()->fillScreen(ui->getBackgroundColor());
            drawCompass(hal);
            hal->qmc5883_Read();
            int a = 90 + atan2(hal->qmc5883_GetY(), hal->qmc5883_GetX()) * 180.0 / PI;
            int compass = a < 0 ? 360 + a : a;
            drawPointer(hal, compass);
            hal->requestFlush();
            break;
      }
}

void OswAppCompass::stop(OswHal *hal)
{
      hal->qmc5883_Sleep();
}
