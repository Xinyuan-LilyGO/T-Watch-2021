/**\
 * Copyright (c) 2020 Bosch Sensortec GmbH. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

/*!
 * @ingroup bma423Examples
 * @defgroup bma423ExampleAux Read / write from auxiliary sensor
 * @brief Example shows read and write data from auxiliary sensor.
 * \include aux_example.c
 */

#include <stdio.h>
#include "bma423.h"
#include "bma4_common.h"

/* Auxiliary sensor chip id macros */
#define BMM150_CHIP_ID         UINT8_C(0x32)
#define BMA4_AUX_CHIP_ID_ADDR  UINT8_C(0x40)

/* Reading of data from auxiliary sensor BMM150
 * Initialize the auxiliary interface as shown above. Set the power mode to sleep mode and the operation mode
 * to forced mode. Then validate the sensor by reading the chip id.*/

int main(void)
{
    struct bma4_dev dev;
    uint8_t aux_data[5] = { 0 };
    uint8_t aux_write_data[5] = { 0xFF, 0xAA, 0xFD, 0x78, 0x99 };
    uint8_t aux_chip_id = 0;
    uint8_t aux_write;
    uint16_t rslt;

    /* Function to select interface between SPI and I2C, according to that the device structure gets updated
     * Variant information given as parameter
     *         For B variant        : BMA42X_B_VARIANT
     *         For Non-B variant    : BMA42X_VARIANT
     */
    rslt = bma4_interface_selection(&dev, BMA42X_VARIANT);
    bma4_error_codes_print_result("bma4_interface_selection status", rslt);

    /* Sensor initialization */
    rslt = bma423_init(&dev);
    bma4_error_codes_print_result("bma423_init", rslt);

    /* Upload the configuration file to enable the features of the sensor. */
    rslt = bma423_write_config_file(&dev);
    bma4_error_codes_print_result("bma423_write_config", rslt);

    /* Initialize the auxiliary interface */
    rslt = bma4_aux_interface_init(&dev);
    bma4_error_codes_print_result("aux_inetrface_init", rslt);

    /* Switch on the the auxiliary interface mode */
    dev.aux_config.if_mode = BMA4_ENABLE_AUX_IF_MODE;

    /* Set the I2C device address of auxiliary device */
    /* Device address of BMM150 */
    dev.aux_config.aux_dev_addr = BMA4_I2C_BMM150_ADDR;

    /* Set aux interface to manual mode */
    dev.aux_config.manual_enable = BMA4_MANUAL_ENABLE;

    /* Set the number of bytes for burst read */
    dev.aux_config.burst_read_length = BMA4_AUX_READ_LEN_0;

    /* Enable the power control bit for sleep mode in BMM150_POWER_CONTROL_REG register of BMM150 */
    aux_write = 0x01;
    rslt = bma4_aux_write(BMM150_POWER_CONTROL_REG, &aux_write, 1, &dev);

    /* Enable forced mode in BMM150_POWER_MODE_REG register of BMM150 */
    aux_write = 0x02;
    rslt = bma4_aux_write(BMM150_POWER_MODE_REG, &aux_write, 1, &dev);

    /* Read the chip-id of the auxiliary sensor */
    rslt = bma4_aux_read(BMA4_AUX_CHIP_ID_ADDR, &aux_chip_id, 1, &dev);
    bma4_error_codes_print_result("aux_read", rslt);
    if (aux_chip_id == BMM150_CHIP_ID)
    {
        rslt = bma4_aux_read(0x42, aux_data, 1, &dev);
    }

    /* Read the chip-id of the auxiliary sensor */
    rslt = bma4_aux_read(BMA4_AUX_CHIP_ID_ADDR, &aux_chip_id, 1, &dev);
    bma4_error_codes_print_result("aux_read", rslt);
    if (aux_chip_id == BMM150_CHIP_ID)
    {
        rslt = bma4_aux_write(0x50, aux_write_data, 4, &dev);

    }

    return rslt;
}
