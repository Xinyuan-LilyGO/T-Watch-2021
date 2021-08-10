/*
 * Copyright (C) 2020 Bosch Sensortec GmbH
 *
 * The license is available at root folder
 *
 */

/*!
 * @ingroup bma400Examples
 * @defgroup bma400ExamplesOrientation Orientation
 * @brief To showcase orientation feature
 * \include orientation.c
 */

#include <stdio.h>
#include "bma400.h"
#include "common.h"

/* Macro to determine count of activity change for each axis */
#define BMA400_INT_COUNTER  UINT8_C(5)

/* orient_feature interrupts */
static void test_bma400_orient_feature_int(struct bma400_orient_int_conf test_orient_conf, struct bma400_dev *dev)
{
    int8_t rslt = 0;

    struct bma400_sensor_conf accel_settin[2];
    struct bma400_sensor_data accel;
    struct bma400_int_enable int_en[2];

    uint16_t int_status = 0;
    uint8_t orient_cnter = 0;

    accel_settin[0].type = BMA400_ORIENT_CHANGE_INT;
    accel_settin[1].type = BMA400_ACCEL;

    rslt = bma400_get_sensor_conf(accel_settin, 2, dev);
    bma400_check_rslt("bma400_get_sensor_conf", rslt);

    accel_settin[0].param.orient.axes_sel = test_orient_conf.axes_sel;
    accel_settin[0].param.orient.data_src = test_orient_conf.data_src;
    accel_settin[0].param.orient.int_chan = test_orient_conf.int_chan;
    accel_settin[0].param.orient.orient_int_dur = test_orient_conf.orient_int_dur;
    accel_settin[0].param.orient.orient_thres = test_orient_conf.orient_thres;
    accel_settin[0].param.orient.ref_update = test_orient_conf.ref_update;
    accel_settin[0].param.orient.stability_thres = test_orient_conf.stability_thres;
    accel_settin[0].param.orient.orient_ref_x = test_orient_conf.orient_ref_x;
    accel_settin[0].param.orient.orient_ref_y = test_orient_conf.orient_ref_y;
    accel_settin[0].param.orient.orient_ref_z = test_orient_conf.orient_ref_z;

    accel_settin[1].param.accel.odr = BMA400_ODR_100HZ;
    accel_settin[1].param.accel.range = BMA400_RANGE_2G;
    accel_settin[1].param.accel.data_src = BMA400_DATA_SRC_ACCEL_FILT_1;

    rslt = bma400_set_sensor_conf(accel_settin, 2, dev);
    bma400_check_rslt("bma400_set_sensor_conf", rslt);

    rslt = bma400_set_power_mode(BMA400_MODE_NORMAL, dev);
    bma400_check_rslt("bma400_set_power_mode", rslt);

    int_en[0].type = BMA400_ORIENT_CHANGE_INT_EN;
    int_en[0].conf = BMA400_ENABLE;

    int_en[1].type = BMA400_LATCH_INT_EN;
    int_en[1].conf = BMA400_ENABLE;

    rslt = bma400_enable_interrupt(int_en, 2, dev);
    bma400_check_rslt("bma400_enable_interrupt", rslt);

    accel_settin[0].param.orient.axes_sel = 0;
    accel_settin[0].param.orient.data_src = 0;
    accel_settin[0].param.orient.int_chan = 0;
    accel_settin[0].param.orient.orient_int_dur = 0;
    accel_settin[0].param.orient.orient_thres = 0;
    accel_settin[0].param.orient.ref_update = 0;
    accel_settin[0].param.orient.stability_thres = 0;
    accel_settin[0].param.orient.orient_ref_x = 0;
    accel_settin[0].param.orient.orient_ref_y = 0;
    accel_settin[0].param.orient.orient_ref_z = 0;

    rslt = bma400_get_sensor_conf(accel_settin, 1, dev);
    bma400_check_rslt("bma400_interface_init", rslt);

    printf("Shake board for Orientation change interrupt\n");

    while (1)
    {
        rslt = bma400_get_sensor_conf(accel_settin, 1, dev);
        bma400_check_rslt("bma400_interface_init", rslt);

        rslt = bma400_get_interrupt_status(&int_status, dev);
        bma400_check_rslt("bma400_interface_init", rslt);

        if (int_status & BMA400_ASSERTED_ORIENT_CH)
        {
            printf("Orientation interrupt detected\n");

            if (orient_cnter == 0)
            {
                printf("Reference  : X: %d     Y : %d     Z : %d\n",
                       accel_settin[0].param.orient.orient_ref_x,
                       accel_settin[0].param.orient.orient_ref_y,
                       accel_settin[0].param.orient.orient_ref_z);
            }

            rslt = bma400_get_accel_data(BMA400_DATA_ONLY, &accel, dev);
            if (rslt == BMA400_OK)
            {
                printf("Accel data : X : %d   Y : %d    Z : %d\n", accel.x, accel.y, accel.z);
            }

            orient_cnter++;
        }

        /* Loop breaker */
        if (orient_cnter >= BMA400_INT_COUNTER)
        {
            printf("Orientation interrupt test done. Exiting!\n");
            break;
        }
    }
}

int main(int argc, char const *argv[])
{
    struct bma400_dev bma;

    int8_t rslt = 0;

    struct bma400_orient_int_conf test_orient_conf = { 0 };

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

    printf("Orient change interrupt with XYZ Axes enabled\n");
    test_orient_conf.axes_sel = BMA400_AXIS_XYZ_EN;
    test_orient_conf.data_src = BMA400_DATA_SRC_ACC_FILT1;
    test_orient_conf.int_chan = BMA400_INT_CHANNEL_2;
    test_orient_conf.orient_int_dur = 7; /* 10ms/LSB */
    test_orient_conf.orient_thres = 125; /* 1 LSB = 8mg */
    test_orient_conf.ref_update = BMA400_ORIENT_REFU_ACC_FILT_2;
    test_orient_conf.stability_thres = 10; /* 1 LSB = 8mg */

    test_bma400_orient_feature_int(test_orient_conf, &bma);

    printf("Orient change interrupt with Y Axis enabled\n");
    test_orient_conf.axes_sel = BMA400_AXIS_Y_EN;
    test_orient_conf.data_src = BMA400_DATA_SRC_ACC_FILT2;
    test_orient_conf.int_chan = BMA400_UNMAP_INT_PIN;
    test_orient_conf.orient_int_dur = 7; /* 10ms/LSB */
    test_orient_conf.orient_thres = 125; /* 1 LSB = 8mg */
    test_orient_conf.stability_thres = 10; /* 1 LSB = 8mg */

    test_bma400_orient_feature_int(test_orient_conf, &bma);

    printf("Orient change interrupt with X Axis enabled\n");
    test_orient_conf.axes_sel = BMA400_AXIS_X_EN;
    test_orient_conf.data_src = BMA400_DATA_SRC_ACC_FILT2;
    test_orient_conf.int_chan = BMA400_MAP_BOTH_INT_PINS;
    test_orient_conf.orient_int_dur = 7; /* 10ms/LSB */
    test_orient_conf.orient_thres = 100; /* 1 LSB = 8mg */
    test_orient_conf.ref_update = BMA400_ORIENT_REFU_ACC_FILT_2;
    test_orient_conf.stability_thres = 10; /* 1 LSB = 8mg */

    test_bma400_orient_feature_int(test_orient_conf, &bma);

    printf("Orient change interrupt with Z Axis enabled\n");
    test_orient_conf.axes_sel = BMA400_AXIS_Z_EN;
    test_orient_conf.data_src = BMA400_DATA_SRC_ACC_FILT2;
    test_orient_conf.int_chan = BMA400_INT_CHANNEL_1;
    test_orient_conf.orient_int_dur = 7; /* 10ms/LSB */
    test_orient_conf.orient_thres = 125; /* 1 LSB = 8mg */
    test_orient_conf.ref_update = BMA400_ORIENT_REFU_ACC_FILT_2;
    test_orient_conf.stability_thres = 10; /* 1 LSB = 8mg */

    test_bma400_orient_feature_int(test_orient_conf, &bma);

    /* Manual update of ref value is reflected while we read only when we enable that specific axes */

    printf("Orient change interrupt with Z Axis enabled and manual update\n");
    test_orient_conf.axes_sel = BMA400_AXIS_Z_EN;
    test_orient_conf.data_src = BMA400_DATA_SRC_ACC_FILT2;
    test_orient_conf.int_chan = BMA400_INT_CHANNEL_1;
    test_orient_conf.orient_int_dur = 7; /* 10ms/LSB */
    test_orient_conf.orient_thres = 125; /* 1 LSB = 8mg */
    test_orient_conf.ref_update = BMA400_UPDATE_MANUAL;
    test_orient_conf.stability_thres = 10; /* 1 LSB = 8mg */
    test_orient_conf.orient_ref_x = 200;
    test_orient_conf.orient_ref_y = 300;
    test_orient_conf.orient_ref_z = 2000;

    test_bma400_orient_feature_int(test_orient_conf, &bma);

    bma400_coines_deinit();

    return rslt;
}
