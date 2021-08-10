#include <Adafruit_Sensor.h>
#include <Wire.h>

// #include "BlueDot_BMA400.h"
// #include "bma400_defs.h"
#include "bma.h"

//#include "QMC5883LCompass.h"

#include "osw_hal.h"
#include "osw_pins.h"

/* Earth's gravity in m/s^2 */
#define GRAVITY_EARTH (9.80665f)

/* 39.0625us per tick */
#define SENSOR_TICK_TO_S (0.0000390625f)

BMA423 sensor;
Accel acc;
bool BMA_IRQ = false;
float accelT4, accelX4, accelY4, accelZ4;
uint32_t stepCount = 0;
/* static uint8_t dev_addr;
uint8_t act_int;
uint32_t step_count = 0; */

static float lsb_to_ms2(int16_t accel_data, uint8_t g_range, uint8_t bit_width)
{
    float accel_ms2;
    int16_t half_scale;

    half_scale = 1 << (bit_width - 1);
    accel_ms2 = (GRAVITY_EARTH * accel_data * g_range) / half_scale;

    return accel_ms2;
}

uint16_t readRegister(uint8_t address, uint8_t reg, uint8_t *data, uint16_t len)
{
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom((uint8_t)address, (uint8_t)len);
    uint8_t i = 0;
    while (Wire.available())
    {
        data[i++] = Wire.read();
    }
    return 0; //Pass
}

uint16_t writeRegister(uint8_t address, uint8_t reg, uint8_t *data, uint16_t len)
{
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.write(data, len);
    return (0 != Wire.endTransmission());
}

void IRAM_ATTR isrStep()
{
    // TODO: read INT_STAT0,INT_STAT1,INT_STAT2
    // check which interrupt fired
}

void IRAM_ATTR isrTap() { Serial.println("Tap"); }

void OswHal::setupSensors()
{
    Wire.begin(SDA, SCL);

    if (sensor.begin(readRegister, writeRegister, delay) == true)
    {
        _hasBMA423 = true;
    }
    else
    {
        _hasBMA423 = false;
        Serial.println("BMA423 was not found. Please check wiring/power. ");
    }
    sensor.softReset();

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
    cfg.range = BMA4_ACCEL_RANGE_16G;
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
    // Warning : Need to use feature, you must first enable the accelerometer
    // Warning : Need to use feature, you must first enable the accelerometer
    sensor.enableAccel();

    // You can also turn it off
    // sensor.disableAccel();
    /* struct bma4_int_pin_config config;
    config.edge_ctrl = BMA4_LEVEL_TRIGGER;
    config.lvl = BMA4_ACTIVE_HIGH;
    config.od = BMA4_PUSH_PULL;
    config.output_en = BMA4_OUTPUT_ENABLE;
    config.input_en = BMA4_INPUT_DISABLE;
    // The correct trigger interrupt needs to be configured as needed
    sensor.setINTPinConfig(config, BMA4_INTR1_MAP); */

    /* pinMode(BMA_INT_1, INPUT);
    attachInterrupt(
        BMA_INT_1, []
        {
            // Set interrupt to set irq value to true
            BMA_IRQ = true;
        },
        RISING); //Select the interrupt mode according to the actual circuit */

    struct bma423_axes_remap remap_data;
    remap_data.x_axis = 0;
    remap_data.x_axis_sign = 1;
    remap_data.y_axis = 1;
    remap_data.y_axis_sign = 0;
    remap_data.z_axis = 2;
    remap_data.z_axis_sign = 1;
    // Need to raise the wrist function, need to set the correct axis
    sensor.setRemapAxes(&remap_data);

    // Enable BMA423 isStepCounter feature
    sensor.enableFeature(BMA423_STEP_CNTR, true);

    // Enable BMA423 isTilt feature
    sensor.enableFeature(BMA423_TILT, true);
    // Enable BMA423 isDoubleClick feature
    sensor.enableFeature(BMA423_WAKEUP, true);

    // Reset steps
    sensor.resetStepCounter();

    // Turn on feature interrupt
    sensor.enableStepCountInterrupt();
    //sensor.enableTiltInterrupt();
    // It corresponds to isDoubleClick interrupt
    //sensor.enableWakeupInterrupt();

    pinMode(BMA_INT_1, INPUT_PULLUP);
    pinMode(BMA_INT_2, INPUT_PULLUP);
    attachInterrupt(BMA_INT_1, isrStep, FALLING);
    //attachInterrupt(BMA_INT_2, isrTap, FALLING);
}

bool OswHal::hasBMA423(void) { return _hasBMA423; }

void OswHal::updateAccelerometer(void)
{
    bool res = sensor.getAccel(acc);
    if (res == false)
    {
        Serial.println("getAccel FAIL");
    }
    accelX4 = lsb_to_ms2(acc.x, 2, 12);
    accelY4 = lsb_to_ms2(acc.y, 2, 12);
    accelZ4 = lsb_to_ms2(acc.z, 2, 12);
}

float OswHal::getAccelerationX(void)
{
    return accelX4;
};
float OswHal::getAccelerationY(void)
{
    return -accelY4;
};
float OswHal::getAccelerationZ(void) { return accelZ4; };

uint32_t OswHal::getStepCount(void) { return (sensor.getCounter() / 4); };

uint8_t OswHal::getActivityMode(void) { return 0; };

void OswHal::BMA423shutdown(void)
{
    sensor.disableAccel();
    sensor.disalbeIRQ();
    //sensor.shutDown();
};