/*
 * Copyright (C) 2020 Bosch Sensortec GmbH
 *
 * The license is available at root folder
 *
 */

/*!
 * @ingroup bma400Examples
 * @defgroup bma400ExamplesActChange Activity change
 * @brief To showcase activity change feature
 * \include activity_change.c
 */

#include <stdio.h>
#include "bma400.h"
#include "common.h"

/* Macro to determine count of activity change for each axis */
#define BMA400_INT_COUNTER  UINT8_C(5)

/* struct to act as counter to test activity change interrupt - axis wise */
struct test_axes_wise_counter
{
    uint8_t x_counter;
    uint8_t y_counter;
    uint8_t z_counter;
};

int main(int argc, char const *argv[])
{
    struct bma400_dev bma;

    int8_t rslt = 0;
    uint16_t int_status;

    struct test_axes_wise_counter act_ch_cnt = { 0 };
    struct bma400_sensor_data accel;
    struct bma400_sensor_conf accel_settin[2] = { { 0 } };
    struct bma400_int_enable int_en;

    printf("Functionality test for Activity change interrupt\n");

    /* Interface reference is given as a parameter
     *         For I2C : BMA400_I2C_INTF
     *         For SPI : BMA400_SPI_INTF
     */
    rslt = bma400_interface_init(&bma, BMA400_SPI_INTF);
    bma400_check_rslt("bma400_interface_init", rslt);

    rslt = bma400_soft_reset(&bma);
    bma400_check_rslt("bma400_soft_reset", rslt);

    rslt = bma400_init(&bma);
    bma400_check_rslt("bma400_init", rslt);

    accel_settin[0].type = BMA400_ACTIVITY_CHANGE_INT;
    accel_settin[1].type = BMA400_ACCEL;

    rslt = bma400_get_sensor_conf(accel_settin, 2, &bma);
    bma400_check_rslt("bma400_get_sensor_conf", rslt);

    accel_settin[0].param.act_ch.int_chan = BMA400_INT_CHANNEL_1;
    accel_settin[0].param.act_ch.axes_sel = BMA400_AXIS_XYZ_EN;
    accel_settin[0].param.act_ch.act_ch_ntps = BMA400_ACT_CH_SAMPLE_CNT_64;
    accel_settin[0].param.act_ch.data_source = BMA400_DATA_SRC_ACC_FILT1;
    accel_settin[0].param.act_ch.act_ch_thres = 10;

    accel_settin[1].param.accel.odr = BMA400_ODR_100HZ;
    accel_settin[1].param.accel.range = BMA400_RANGE_2G;
    accel_settin[1].param.accel.data_src = BMA400_DATA_SRC_ACCEL_FILT_1;

    /* Set the desired configurations to the sensor */
    rslt = bma400_set_sensor_conf(accel_settin, 2, &bma);
    bma400_check_rslt("bma400_set_sensor_conf", rslt);

    rslt = bma400_set_power_mode(BMA400_MODE_NORMAL, &bma);
    bma400_check_rslt("bma400_set_power_mode", rslt);

    int_en.type = BMA400_ACTIVITY_CHANGE_INT_EN;
    int_en.conf = BMA400_ENABLE;

    rslt = bma400_enable_interrupt(&int_en, 1, &bma);
    bma400_check_rslt("bma400_enable_interrupt", rslt);

    printf("Show activity on x y z axes of the board\n");

    while (1)
    {
        rslt = bma400_get_sensor_conf(accel_settin, 2, &bma);
        bma400_check_rslt("bma400_get_sensor_conf", rslt);

        rslt = bma400_get_interrupt_status(&int_status, &bma);
        bma400_check_rslt("bma400_get_interrupt_status", rslt);

        if (int_status & BMA400_ASSERTED_ACT_CH_X)
        {
            printf("Activity change interrupt asserted on X axis\n");
            act_ch_cnt.x_counter++;

            rslt = bma400_get_accel_data(BMA400_DATA_SENSOR_TIME, &accel, &bma);
            bma400_check_rslt("bma400_get_accel_data_X", rslt);

            if (rslt == BMA400_OK)
            {
                printf("Accel Data :  X : %d    Y : %d    Z : %d    SENSOR_TIME : %d\n",
                       accel.x,
                       accel.y,
                       accel.z,
                       accel.sensortime);
            }
        }

        if (int_status & BMA400_ASSERTED_ACT_CH_Y)
        {
            printf("Activity change interrupt asserted on Y axis\n");
            act_ch_cnt.y_counter++;

            rslt = bma400_get_accel_data(BMA400_DATA_SENSOR_TIME, &accel, &bma);
            bma400_check_rslt("bma400_get_accel_data_Y", rslt);

            if (rslt == BMA400_OK)
            {
                printf("Accel Data :  X : %d    Y : %d    Z : %d    SENSOR_TIME : %d\n",
                       accel.x,
                       accel.y,
                       accel.z,
                       accel.sensortime);
            }
        }

        if (int_status & BMA400_ASSERTED_ACT_CH_Z)
        {
            printf("Activity change interrupt asserted on Z axis\n");
            act_ch_cnt.z_counter++;

            rslt = bma400_get_accel_data(BMA400_DATA_SENSOR_TIME, &accel, &bma);
            bma400_check_rslt("bma400_get_accel_data_Z", rslt);

            if (rslt == BMA400_OK)
            {
                printf("Accel Data :  X : %d    Y : %d    Z : %d    SENSOR_TIME : %d\n",
                       accel.x,
                       accel.y,
                       accel.z,
                       accel.sensortime);
            }
        }

        if ((act_ch_cnt.x_counter >= BMA400_INT_COUNTER) && (act_ch_cnt.y_counter >= BMA400_INT_COUNTER) &&
            (act_ch_cnt.z_counter >= BMA400_INT_COUNTER))
        {
            printf("Activity change interrupt test done !\n");
            break;
        }
    }

    bma400_coines_deinit();

    return rslt;
}
