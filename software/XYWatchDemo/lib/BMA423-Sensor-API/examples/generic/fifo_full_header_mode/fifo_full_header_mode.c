/**\
 * Copyright (c) 2020 Bosch Sensortec GmbH. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

/*!
 * @ingroup bma423Examples
 * @defgroup bma423ExampleFIFOH FIFO full header mode
 * @brief Example shows read fifo data in header mode.
 * \include fifo_full_header_mode.c
 */

#include <stdio.h>
#include "bma423.h"
#include "bma4_common.h"

/******************************************************************************/
/*!                Macro definition                                           */

/*! Buffer size allocated to store raw FIFO data */
#define BMA423_FIFO_RAW_DATA_BUFFER_SIZE  UINT16_C(1024)

/*! Length of data to be read from FIFO */
#define BMA423_FIFO_RAW_DATA_USER_LENGTH  UINT16_C(1024)

/*! Number of accel frames to be extracted from FIFO
 * Calculation:
 * fifo_buffer = 1024, accel_frame_len = 6, header_byte = 1.
 * fifo_accel_frame_count = (1024 / (6 + 1)) = 147 frames
 */
#define BMA423_FIFO_ACCEL_FRAME_COUNT     UINT8_C(147)

/*! Macro to read sensortime byte in FIFO */
#define SENSORTIME_OVERHEAD_BYTE          UINT8_C(3)

/******************************************************************************/
/*!            Function                                                       */

/* This function starts the execution of program */
int main(void)
{
    /* Status of API are returned to this variable */
    int8_t rslt;

    /* Accelerometer configuration structure */
    struct bma4_accel_config acc_conf = { 0 };

    /* Sensor initialization configuration */
    struct bma4_dev dev = { 0 };

    /* Number of accelerometer frames */
    uint16_t accel_length;

    /* Variable to idx bytes */
    uint16_t idx = 0;

    /* Variable to store the available frame length count in FIFO */
    uint8_t frame_count;

    /* Number of bytes of FIFO data */
    uint8_t fifo_data[BMA423_FIFO_RAW_DATA_BUFFER_SIZE] = { 0 };

    /* Array of accelerometer frames -> Total bytes =
     * 147 * (6 axes bytes(+/- x,y,z) + 1 header byte) = 1029 bytes */
    struct bma4_accel fifo_accel_data[BMA423_FIFO_ACCEL_FRAME_COUNT] = { { 0 } };

    /* Initialize FIFO frame structure */
    struct bma4_fifo_frame fifoframe = { 0 };

    /* Variable that contains interrupt status value */
    uint16_t int_status = 0;

    /* Variable to hold the length of FIFO data */
    uint16_t fifo_length = 0;

    /* Function to select interface between SPI and I2C, according to that the device structure gets updated
     * Variant information given as parameter
     *         For B variant        : BMA42X_B_VARIANT
     *         For Non-B variant    : BMA42X_VARIANT
     */
    rslt = bma4_interface_selection(&dev, BMA42X_VARIANT);
    bma4_error_codes_print_result("bma4_interface_selection status", rslt);

    /* Initialize BMA423 */
    rslt = bma423_init(&dev);
    bma4_error_codes_print_result("bma423_init status", rslt);

    /* Enable the accelerometer sensor */
    rslt = bma4_set_accel_enable(BMA4_ENABLE, &dev);
    bma4_error_codes_print_result("bma4_set_accel_enable status", rslt);

    /* Accelerometer configuration settings */
    acc_conf.odr = BMA4_OUTPUT_DATA_RATE_100HZ;
    acc_conf.bandwidth = BMA4_ACCEL_NORMAL_AVG4;
    acc_conf.range = BMA4_ACCEL_RANGE_2G;

    /* Set the accel configurations */
    rslt = bma4_set_accel_config(&acc_conf, &dev);
    bma4_error_codes_print_result("bma4_set_accel_config status", rslt);

    /* Disabling advance power save mode as FIFO data is not accessible in advance low power mode */
    rslt = bma4_set_advance_power_save(BMA4_DISABLE, &dev);
    bma4_error_codes_print_result("bma4_set_advance_power_save status", rslt);

    /* Clear FIFO configuration register */
    rslt = bma4_set_fifo_config(BMA4_FIFO_ALL, BMA4_DISABLE, &dev);
    bma4_error_codes_print_result("bma4_set_fifo_config disable status", rslt);

    /* Set FIFO configuration by enabling accel.
     * NOTE 1: The header mode is enabled by default.
     * NOTE 2: By default the FIFO operating mode is FIFO mode. */
    rslt = bma4_set_fifo_config(BMA4_FIFO_ACCEL | BMA4_FIFO_HEADER | BMA4_FIFO_TIME, BMA4_ENABLE, &dev);
    bma4_error_codes_print_result("bma4_set_fifo_config enable status", rslt);

    /* Update FIFO structure */
    fifoframe.data = fifo_data;
    fifoframe.length = BMA423_FIFO_RAW_DATA_USER_LENGTH + SENSORTIME_OVERHEAD_BYTE;

    printf("FIFO is configured in header mode\n");

    rslt = bma423_map_interrupt(BMA4_INTR1_MAP, BMA4_FIFO_FULL_INT, BMA4_ENABLE, &dev);
    bma4_error_codes_print_result("bma4_map_interrupt status", rslt);

    while (1)
    {
        rslt = bma423_read_int_status(&int_status, &dev);
        bma4_error_codes_print_result("bma4_read_int_status", rslt);

        if ((rslt == BMA4_OK) && (int_status & BMA4_FIFO_FULL_INT))
        {
            rslt = bma4_get_fifo_length(&fifo_length, &dev);
            bma4_error_codes_print_result("bma4_get_fifo_length status", rslt);

            printf("FIFO data bytes available : %d\n", fifo_length);
            printf("FIFO data bytes requested : %d\n", fifoframe.length);

            /* Read FIFO data */
            rslt = bma4_read_fifo_data(&fifoframe, &dev);
            bma4_error_codes_print_result("bma4_read_fifo_data status", rslt);

            accel_length = BMA423_FIFO_ACCEL_FRAME_COUNT;

            if (rslt == BMA4_OK)
            {
                printf("Requested data frames before parsing: %d\n", accel_length);

                /* Parse the FIFO data to extract accelerometer data from the FIFO buffer */
                rslt = bma4_extract_accel(fifo_accel_data, &accel_length, &fifoframe, &dev);
                printf("Parsed accelerometer data frames: %d\n", accel_length);

                /* Calculating the frame count from the available bytes in FIFO
                 * frame_length = (available_fifo_bytes / (acc_frame_len + header_byte)) */
                frame_count = (fifo_length / (BMA4_FIFO_A_LENGTH + 1));
                printf("Available frame count: %d\n", frame_count);

                /* Print the parsed accelerometer data from the FIFO buffer */
                for (idx = 0; idx < frame_count; idx++)
                {
                    printf("ACCEL[%d] X : %d Y : %d Z : %d\n",
                           idx,
                           fifo_accel_data[idx].x,
                           fifo_accel_data[idx].y,
                           fifo_accel_data[idx].z);
                }

                /* Print control frames like sensor time and skipped frame count */
                printf("Skipped frame count = %d\n", fifoframe.skipped_frame_count);
                printf("Sensor time = %lu\n", fifoframe.sensor_time);
            }

            break;
        }
    }

    return rslt;
}
