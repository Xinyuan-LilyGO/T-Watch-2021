/**\
 * Copyright (c) 2020 Bosch Sensortec GmbH. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

/*!
 * @ingroup bma423Examples
 * @defgroup bma423ExampleMotionInt Motion interrupt
 * @brief Example shows basic application of motion interrupt
 *  where no motion or/and any motion are detected.
 * \include motion_interrupt.c
 */

#include <stdio.h>
#include "bma423.h"
#include "bma4_common.h"

int main(void)
{
    struct bma4_dev bma;
    struct bma423_any_no_mot_config any_no_mot;
    struct bma4_accel_config accel_conf;
    uint16_t rslt;
    uint16_t int_status = 0;

    /* Loop variable */
    uint8_t iteration = 20;

    /* Function to select interface between SPI and I2C, according to that the device structure gets updated
     * Variant information given as parameter
     *         For B variant        : BMA42X_B_VARIANT
     *         For Non-B variant    : BMA42X_VARIANT
     */
    rslt = bma4_interface_selection(&bma, BMA42X_VARIANT);
    bma4_error_codes_print_result("bma4_interface_selection status", rslt);

    /* Sensor initialization */
    rslt = bma423_init(&bma);
    bma4_error_codes_print_result("bma423_init status", rslt);

    /* Upload the configuration file to enable the features of the sensor. */
    rslt = bma423_write_config_file(&bma);
    bma4_error_codes_print_result("bma423_write_config status", rslt);

    /* Enable the accelerometer */
    rslt = bma4_set_accel_enable(1, &bma);
    bma4_error_codes_print_result("bma4_set_accel_enable status", rslt);

    /* Accelerometer Configuration Setting */
    /* Output data Rate */
    accel_conf.odr = BMA4_OUTPUT_DATA_RATE_100HZ;

    /* Gravity range of the sensor (+/- 2G, 4G, 8G, 16G) */
    accel_conf.range = BMA4_ACCEL_RANGE_2G;

    /* Bandwidth configure number of sensor samples required to average
     * if value = 2, then 4 samples are averaged
     * averaged samples = 2^(val(accel bandwidth))
     * Note1 : More info refer datasheets
     * Note2 : A higher number of averaged samples will result in a lower noise level of the signal, but
     * since the performance power mode phase is increased, the power consumption will also rise.
     */
    accel_conf.bandwidth = BMA4_ACCEL_NORMAL_AVG4;

    /* Enable the filter performance mode where averaging of samples
     * will be done based on above set bandwidth and ODR.
     * There are two modes
     *  0 -> Averaging samples (Default)
     *  1 -> No averaging
     * For more info on No Averaging mode refer datasheets.
     */
    accel_conf.perf_mode = BMA4_CIC_AVG_MODE;

    /* Set the accel configurations */
    rslt = bma4_set_accel_config(&accel_conf, &bma);
    bma4_error_codes_print_result("bma4_set_accel_config status", rslt);

    /* Select the axis for which any/no motion interrupt should be generated */
    any_no_mot.axes_en = BMA423_EN_ALL_AXIS;

    /*
     * Set the slope threshold:
     * Interrupt will be generated if the slope of all the axis exceeds the threshold (1 bit = 0.48mG)
     */
    any_no_mot.threshold = 10;

    /*
     * Set the duration for any/no motion interrupt:
     * Duration defines the number of consecutive data points for which threshold condition must be true(1 bit = 20ms)
     */
    any_no_mot.duration = 4;

    /* Set the threshold, duration and axis enable configuration */
    rslt = bma423_set_any_mot_config(&any_no_mot, &bma);
    bma4_error_codes_print_result("bma423_set_any_mot_config status", rslt);
    rslt = bma423_set_no_mot_config(&any_no_mot, &bma);
    bma4_error_codes_print_result("bma423_set_no_mot_config status", rslt);

    /* Map the interrupt pin with that of any-motion and no-motion interrupts.
     * Interrupt will be generated when any or no-motion is recognized.
     */
    rslt = bma423_map_interrupt(BMA4_INTR1_MAP, BMA423_ANY_MOT_INT | BMA423_NO_MOT_INT, BMA4_ENABLE, &bma);
    bma4_error_codes_print_result("bma423_map_interrupt status", rslt);

    printf("Shake the board for any-motion interrupt whereas do not shake the board for no-motion interrupt\n");

    while (1)
    {
        /* Read the interrupt register to check whether any-motion or no-motion interrupt is received */
        rslt = bma423_read_int_status(&int_status, &bma);

        /* Check if any-motion interrupt is triggered */
        if (int_status & BMA423_ANY_MOT_INT)
        {
            printf("Any-Motion interrupt received\n");
            iteration--;
        }

        /* Check if no-motion interrupt is triggered */
        if (int_status & BMA423_NO_MOT_INT)
        {
            printf("No-Motion interrupt received\n");
            iteration--;
        }

        int_status = 0;

        /* Break out of the loop when iteration has reached zero */
        if (iteration == 0)
        {
            printf("Iterations are done. Exiting !");
            break;
        }
    }

    return rslt;
}
