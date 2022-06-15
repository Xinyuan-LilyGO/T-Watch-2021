/**\
 * Copyright (c) 2020 Bosch Sensortec GmbH. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

/*!
 * @ingroup bma423Examples
 * @defgroup bma423ExampleTemp Read Temperature
 * @brief Example shows basic application of reading sensor temperature.
 * \include temperature.c
 */

#include <stdio.h>
#include "bma423.h"
#include "bma4_common.h"

int main(void)
{
    struct bma4_dev bma;
    uint16_t rslt;
    int32_t get_temp_C = 0;
    int32_t get_temp_F = 0;
    int32_t get_temp_K = 0;
    float actual_temp = 0;

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

    /* Get temperature in degree C */
    rslt = bma4_get_temperature(&get_temp_C, BMA4_DEG, &bma);
    bma4_error_codes_print_result("bma4_get_temperature in degree C status", rslt);

    /* Get temperature in degree F */
    rslt = bma4_get_temperature(&get_temp_F, BMA4_FAHREN, &bma);
    bma4_error_codes_print_result("bma4_get_temperature in degree F status", rslt);

    /* Get temperature in degree K */
    rslt = bma4_get_temperature(&get_temp_K, BMA4_KELVIN, &bma);
    bma4_error_codes_print_result("bma4_get_temperature in degree K status", rslt);

    /* Scale the output to get the actual temperature  */
    actual_temp = (float)get_temp_C / (float)BMA4_SCALE_TEMP;
    printf("Actual temperature in degree celsius is %10.2f degrees C\r\n", actual_temp);
    actual_temp = (float)get_temp_F / (float)BMA4_SCALE_TEMP;
    printf("Actual temperature in degree fahranheit is %10.2f degrees F\r\n", actual_temp);
    actual_temp = (float)get_temp_K / (float)BMA4_SCALE_TEMP;
    printf("Actual temperature in degree kelvin is %10.2f degrees K\r\n", actual_temp);

    return rslt;
}
