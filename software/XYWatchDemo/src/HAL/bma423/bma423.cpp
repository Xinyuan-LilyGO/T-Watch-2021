#include "./XYWatch_hal.h"

static float AccX, AccY, AccZ;
static uint32_t stepCount;

struct bma4_dev bma423;

#define GRAVITY_EARTH (9.80665f)

static float lsb_to_ms2(int16_t val, float g_range, uint8_t bit_width)
{
    float half_scale = (float)(1 << bit_width) / 2.0f;

    return GRAVITY_EARTH * val * g_range / half_scale;
}

int8_t readRegister(uint8_t reg, uint8_t *data, uint32_t len, void *intf_ptr)
{
    Wire.beginTransmission(BMA4_I2C_ADDR_PRIMARY);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom((uint8_t)BMA4_I2C_ADDR_PRIMARY, (uint8_t)len);
    uint8_t i = 0;
    while (Wire.available())
    {
        data[i++] = Wire.read();
    }
    return 0; //Pass
}

int8_t writeRegister(uint8_t reg, const uint8_t *data, uint32_t len, void *intf_ptr)
{
    Wire.beginTransmission(BMA4_I2C_ADDR_PRIMARY);
    Wire.write(reg);
    Wire.write(data, len);
    return (0 != Wire.endTransmission());
}

void delay_us(uint32_t period, void *intf_ptr)
{
    ets_delay_us(period);
}

int8_t bma4_interface_selection(struct bma4_dev *bma, uint8_t variant)
{
    int8_t rslt = BMA4_OK;
    uint8_t dev_addr;
    if (bma != NULL)
    {
        /* Select the interface for execution
         * For I2C : BMA4_I2C_INTF
         * For SPI : BMA4_SPI_INTF
         */
        bma->intf = BMA4_I2C_INTF;
        /* Bus configuration : I2C */
        if (bma->intf == BMA4_I2C_INTF)
        {
            printf("I2C Interface \n");

            /* To initialize the user I2C function */
            Wire.begin(IICSDA, IICSCL);
            dev_addr = BMA4_I2C_ADDR_PRIMARY;
            bma->bus_read = readRegister;
            bma->bus_write = writeRegister;
        }

        /* Assign variant parameter */
        bma->variant = BMA42X_VARIANT;
        /* Assign device address to interface pointer */
        bma->intf_ptr = &dev_addr;
        /* Configure delay in microseconds */
        bma->delay_us = delay_us;
        /* Configure max read/write length (in bytes) ( Supported length depends on target machine) */
        bma->read_write_len = 8;
    }
    else
    {
        rslt = BMA4_E_NULL_PTR;
    }

    return rslt;
}

void bma4_error_codes_print_result(const char api_name[], uint16_t rslt)
{
    if (rslt != BMA4_OK)
    {
        Serial.printf("%s\t", api_name);
        if (rslt & BMA4_E_NULL_PTR)
        {
            Serial.printf("Error [%d] : Null pointer\r\n", rslt);
        }
        else if (rslt & BMA4_E_CONFIG_STREAM_ERROR)
        {
            Serial.printf("Error [%d] : Invalid configuration stream\r\n", rslt);
        }
        else if (rslt & BMA4_E_SELF_TEST_FAIL)
        {
            Serial.printf("Error [%d] : Self test failed\r\n", rslt);
        }
        else if (rslt & BMA4_E_INVALID_SENSOR)
        {
            Serial.printf("Error [%d] : Device not found\r\n", rslt);
        }
        else
        {
            /* For more error codes refer "*_defs.h" */
            Serial.printf("Error [%d] : Unknown error code\r\n", rslt);
        }
    }
}

void XYWatch::AccSensor_Interface_Init()
{
    uint16_t rslt = bma4_interface_selection(&bma423, BMA42X_VARIANT);
    bma4_error_codes_print_result("bma4_interface_selection status", rslt);
}

void XYWatch::AccSensor_Init()
{
    uint16_t rslt;
    struct bma4_accel_config accel_conf;

    rslt = bma423_init(&bma423);
    bma4_error_codes_print_result("bma423_init", rslt);

    bma4_set_command_register(0xB6, &bma423);
    delay(50);

    rslt = bma423_write_config_file(&bma423);
    bma4_error_codes_print_result("bma423_write_config", rslt);

    rslt = bma4_set_accel_enable(1, &bma423);
    bma4_error_codes_print_result("bma4_set_accel_enable status", rslt);

    accel_conf.odr = BMA4_OUTPUT_DATA_RATE_100HZ;
    accel_conf.range = BMA4_ACCEL_RANGE_16G;
    accel_conf.bandwidth = BMA4_ACCEL_NORMAL_AVG4;
    accel_conf.perf_mode = BMA4_CIC_AVG_MODE;

    rslt = bma4_set_accel_config(&accel_conf, &bma423);
    bma4_error_codes_print_result("bma4_set_accel_config status", rslt);

    rslt = bma423_feature_enable(BMA423_STEP_CNTR, 1, &bma423);
    bma4_error_codes_print_result("bma423_feature_enable status", rslt);

    /*     rslt = bma423_map_interrupt(BMA4_INTR1_MAP, BMA423_STEP_CNTR_INT, 1, &bma423);
    bma4_error_codes_print_result("bma423_map_interrupt status", rslt); */

    rslt = bma423_step_counter_set_watermark(1, &bma423);
    bma4_error_codes_print_result("bma423_step_counter status", rslt);
}

bool XYWatch::CheckAccSensor()
{
}

void XYWatch::AccSensor_Updata(uint32_t millis, uint32_t time_ms)
{
    static uint32_t Millis;
    uint16_t int_status = 0;
    struct bma4_accel sens_data;
    if (millis - Millis > time_ms)
    {
        uint16_t rslt = bma423_read_int_status(&int_status, &bma423);
        /* if (int_status & BMA423_STEP_CNTR_INT)
        {
            Serial.printf("\nStep counter interrupt received\n");

            rslt = bma423_step_counter_output(&stepCount, &bma423);

            bma4_error_codes_print_result("bma423_step_counter_output status", rslt);
        } */
        rslt = bma423_step_counter_output(&stepCount, &bma423);

        rslt = bma4_read_accel_xyz(&sens_data, &bma423);
        AccX = lsb_to_ms2(sens_data.x, 16, bma423.resolution);
        AccY = lsb_to_ms2(sens_data.y, 16, bma423.resolution);
        AccZ = lsb_to_ms2(sens_data.z, 16, bma423.resolution);

        //Serial.printf("%.2f, %.2f, %.2f\r\n", AccX, AccY, AccZ);
        Millis = millis;
    }
}

void XYWatch::AccSensor_OnStep(bool Step, bool Reset)
{
}

void XYWatch::AccSensor_Sleep(bool Acc, bool Step)
{
}

void XYWatch::AccSensor_GetStepValue(int32_t *val)
{
}

float XYWatch::AccSensor_GetX() { return AccX; }
float XYWatch::AccSensor_GetY() { return AccY; }
float XYWatch::AccSensor_GetZ() { return AccZ; }

uint32_t XYWatch::AccSensor_GetStep() { return stepCount; }
