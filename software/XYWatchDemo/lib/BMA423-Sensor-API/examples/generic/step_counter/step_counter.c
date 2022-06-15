/**\
 * Copyright (c) 2020 Bosch Sensortec GmbH. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

/*!
 * @ingroup bma423Examples
 * @defgroup bma423ExampleStep Step counter
 * @brief Example shows basic setup application of step counter feature.
 * \include step_counter.c
 */

#include <stdio.h>
#include "bma423.h"
#include "bma4_common.h"

int main(void)
{
    struct bma4_dev bma;
    struct bma4_accel_config accel_conf;
    uint16_t rslt;

    /* Variable to get the step counter output */
    uint32_t step_out = 0;

    /* Variable to get the interrupt status */
    uint16_t int_status = 0;

    /* Function to select interface between SPI and I2C, according to that the device structure gets updated
     * Variant information given as parameter
     *         For B variant        : BMA42X_B_VARIANT
     *         For Non-B variant    : BMA42X_VARIANT
     */
    rslt = bma4_interface_selection(&bma, BMA42X_VARIANT);
    bma4_error_codes_print_result("bma4_interface_selection status", rslt);

    /* Sensor initialization */
    rslt = bma423_init(&bma);
    bma4_error_codes_print_result("bma423_init", rslt);

    /* Upload the configuration file to enable the features of the sensor. */
    rslt = bma423_write_config_file(&bma);
    bma4_error_codes_print_result("bma423_write_config", rslt);

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
     * Note2 : A higher number of averaged samples will result in a lower noise level of the signal, but since the
     * performance power mode phase is increased, the power consumption will also rise.
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

    /* Enable step counter */
    rslt = bma423_feature_enable(BMA423_STEP_CNTR, 1, &bma);
    bma4_error_codes_print_result("bma423_feature_enable status", rslt);

    /* Map the interrupt pin with that of step counter interrupts
     * Interrupt will  be generated when step activity is generated.
     */
    rslt = bma423_map_interrupt(BMA4_INTR1_MAP, BMA423_STEP_CNTR_INT, 1, &bma);
    bma4_error_codes_print_result("bma423_map_interrupt status", rslt);

    /* Set water-mark level 1 to get interrupt after 20 steps.
     * Range of step counter interrupt is 0 to 20460(resolution of 20 steps).
     */
    rslt = bma423_step_counter_set_watermark(1, &bma);
    bma4_error_codes_print_result("bma423_step_counter status", rslt);

    printf("Move/perform the walk/step action with the sensor\n");
    while (1)
    {
        /* Read the interrupt register to check whether step counter interrupt is received. */
        rslt = bma423_read_int_status(&int_status, &bma);

        /* Check if step counter interrupt is triggered */
        if (int_status & BMA423_STEP_CNTR_INT)
        {
            printf("\nStep counter interrupt received\n");

            /* On interrupt, Get step counter output */
            rslt = bma423_step_counter_output(&step_out, &bma);
            bma4_error_codes_print_result("bma423_step_counter_output status", rslt);

            break;
        }
    }

    printf("\nThe step counter output is %lu\r\n", step_out);

    return rslt;
}
