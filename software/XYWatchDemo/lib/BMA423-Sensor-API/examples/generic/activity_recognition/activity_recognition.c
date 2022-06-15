/**\
 * Copyright (c) 2020 Bosch Sensortec GmbH. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

/*!
 * @ingroup bma423Examples
 * @defgroup bma423ExampleActivity Step activity recognition
 * @brief Example shows basic application of step activity recognition
 *  where various activities such as walking, running, stationary can be detected.
 * \include activity_recognition.c
 */

#include <stdio.h>
#include "bma423.h"
#include "bma4_common.h"

int main(void)
{
    struct bma4_dev bma;
    struct bma4_accel_config accel_conf;
    uint16_t rslt;

    /* Define a variable to get the status */
    uint16_t int_status = 0;
    uint8_t activity_out = 0;

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

    /* Accelerometer configuration Setting */
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

    /* Enable the sensor activity recognition feature can detect following
     * Stationary
     * Walking
     * Running
     */
    rslt = bma423_feature_enable(BMA423_STEP_ACT, 1, &bma);
    bma4_error_codes_print_result("bma423_feature_enable status", rslt);

    /* Interrupt Mapping:
     * When Activity is recognized, an interrupt will be triggered
     * which can be read by reading the interrupt status register
     */
    rslt = bma423_map_interrupt(BMA4_INTR1_MAP, BMA423_ACTIVITY_INT, BMA4_ENABLE, &bma);
    bma4_error_codes_print_result("bma423_map_interrupt", rslt);

    printf("Move the board in steps to perform activity recognition \n");

    while (1)
    {
        /* Read the interrupt register to check whether any activity recognized */
        rslt = bma423_read_int_status(&int_status, &bma);

        /* An interrupt is set if any activity is recognized  */
        if (int_status & BMA423_ACTIVITY_INT)
        {
            /* Read activity output register for recognizing specific activity */
            rslt = bma423_activity_output(&activity_out, &bma);
            switch (activity_out)
            {
                case BMA423_USER_STATIONARY:
                    printf("User is stationary\n");
                    break;
                case BMA423_USER_WALKING:
                    printf("User is walking\n");
                    break;
                case BMA423_USER_RUNNING:
                    printf("User is running\n");
                    break;
                case BMA423_STATE_INVALID:
                    printf("Invalid activity recognized\n");
                    break;
            }

            /* Break from while loop only if the activity interrupt occurs */
            break;
        }
    }

    return rslt;
}
