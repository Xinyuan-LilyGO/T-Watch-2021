/////////////////////////////////////////////////////////////////
/*
MIT License

Copyright (c) 2020 lewis he

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

BMA423_Direction.ino - Arduino library for Bosch BMA423 accelerometer software library.
Created by Lewis he on July 27, 2020.
github:https://github.com/lewisxhe/BMA423_Library
*/
/////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <Wire.h>
#include <bma.h>

const uint8_t sda = 21;
const uint8_t scl = 22;
uint8_t prevRotation;
BMA423 sensor;

//
// Low-level I2C Communication
// Provided to BMA423_Library communication interface
//
uint16_t readRegister(uint8_t address, uint8_t reg, uint8_t *data, uint16_t len)
{
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom((uint8_t)address, (uint8_t)len);
    uint8_t i = 0;
    while (Wire.available()) {
        data[i++] = Wire.read();
    }
    return 0; //Pass
}

uint16_t writeRegister(uint8_t address, uint8_t reg, uint8_t *data, uint16_t len)
{
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.write(data, len);
    return (0 !=  Wire.endTransmission());
}

void setup()
{
    Serial.begin(115200);

    Serial.println("BMA423 Direction Example");

    Wire.begin(sda, scl);

    if (sensor.begin(readRegister, writeRegister, delay) == false) {
        Serial.println("BMA423 was not found. Please check wiring/power. ");
        while (1);
    }

    // Accel parameter structure
    Acfg cfg;
    /*!
        Output data rate in Hz, Optional parameters:
            - BMA4_OUTPUT_DATA_RATE_0_78HZ
            - BMA4_OUTPUT_DATA_RATE_1_56HZ
            - BMA4_OUTPUT_DATA_RATE_3_12HZ
            - BMA4_OUTPUT_DATA_RATE_6_25HZ
            - BMA4_OUTPUT_DATA_RATE_12_5HZ
            - BMA4_OUTPUT_DATA_RATE_25HZ
            - BMA4_OUTPUT_DATA_RATE_50HZ
            - BMA4_OUTPUT_DATA_RATE_100HZ
            - BMA4_OUTPUT_DATA_RATE_200HZ
            - BMA4_OUTPUT_DATA_RATE_400HZ
            - BMA4_OUTPUT_DATA_RATE_800HZ
            - BMA4_OUTPUT_DATA_RATE_1600HZ
    */
    cfg.odr = BMA4_OUTPUT_DATA_RATE_100HZ;
    /*!
        G-range, Optional parameters:
            - BMA4_ACCEL_RANGE_2G
            - BMA4_ACCEL_RANGE_4G
            - BMA4_ACCEL_RANGE_8G
            - BMA4_ACCEL_RANGE_16G
    */
    cfg.range = BMA4_ACCEL_RANGE_2G;
    /*!
        Bandwidth parameter, determines filter configuration, Optional parameters:
            - BMA4_ACCEL_OSR4_AVG1
            - BMA4_ACCEL_OSR2_AVG2
            - BMA4_ACCEL_NORMAL_AVG4
            - BMA4_ACCEL_CIC_AVG8
            - BMA4_ACCEL_RES_AVG16
            - BMA4_ACCEL_RES_AVG32
            - BMA4_ACCEL_RES_AVG64
            - BMA4_ACCEL_RES_AVG128
    */
    cfg.bandwidth = BMA4_ACCEL_NORMAL_AVG4;

    /*! Filter performance mode , Optional parameters:
        - BMA4_CIC_AVG_MODE
        - BMA4_CONTINUOUS_MODE
    */
    cfg.perf_mode = BMA4_CONTINUOUS_MODE;

    // Configure the BMA423 accelerometer
    sensor.setAccelConfig(cfg);

    // Enable BMA423 accelerometer
    sensor.enableAccel();

    // You can also turn it off
    // sensor.disableAccel();

}

void loop()
{
    // Obtain the BMA423 direction,
    // so that the screen orientation is consistent with the sensor
    uint8_t rotation = sensor.getDirection();
    if (prevRotation != rotation) {
        prevRotation = rotation;
        switch (rotation) {
        case DIRECTION_DISP_DOWN:
            Serial.println("DIRECTION_DISP_DOWN");
            break;
        case DIRECTION_DISP_UP:
            Serial.println("DIRECTION_DISP_UP");
            break;
        case DIRECTION_BOTTOM_EDGE:
            Serial.println("DIRECTION_BOTTOM_EDGE");
            break;
        case DIRECTION_TOP_EDGE:
            Serial.println("DIRECTION_TOP_EDGE");
            break;
        case DIRECTION_RIGHT_EDGE:
            Serial.println("DIRECTION_RIGHT_EDGE");
            break;
        case DIRECTION_LEFT_EDGE:
            Serial.println("DIRECTION_LEFT_EDGE");
            break;
        default:
            Serial.println("ERROR!!!");
            break;
        }
    }
    delay(500);
}
