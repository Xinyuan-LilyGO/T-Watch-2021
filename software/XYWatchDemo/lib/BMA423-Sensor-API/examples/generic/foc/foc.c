/**\
 * Copyright (c) 2020 Bosch Sensortec GmbH. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

#include <stdio.h>
#include "bma423.h"
#include "bma4_common.h"

/******************************************************************************/

/*!         Local Function Prototypes
 ******************************************************************************/

/*!
 *  @brief This internal API is to copy the contents from sensor data to foc data.
 *
 *  @param[in] acc_foc_data    : Accel foc data
 *  @param[in] acc_sensor_data : Accel sensor data
 *  @param[in] size            : Limit to copy the sensor data to foc data
 *  @return void.
 */
static void memcopy(void *acc_foc_data, void *acc_sensor_data, int8_t size);

/*!
 *  @brief This internal API is used to clear the buffer.
 *
 *  @param[in] generic_void_pntr    : Void pointer stores accel FOC structure
 *  @param[in] number : Number to fill the array
 *  @param[in] size            : Limit to copy the sensor data to FOC data
 *  @return void.
 */
static void memset_function(void* generic_void_pntr, uint8_t number, size_t limit);

/******************************************************************************/

/*!          Function Prototypes
 ******************************************************************************/

/* This function starts the execution of program. */
int main(void)
{
    struct bma4_dev bma;
    int16_t x_diff_before = 0;
    int16_t y_diff_before = 0;
    int16_t z_diff_before = 0;
    int16_t x_diff_after = 0;
    int16_t y_diff_after = 0;
    int16_t z_diff_after = 0;
    int8_t matched_axis = 0;
    struct bma4_accel accel_foc_data[20] = { { 0 } };
    struct bma4_temp_axes_val temp_foc_data = { 0 };
    struct bma4_accel avg_bef_foc_data = { 0 };
    struct bma4_accel avg_aft_foc_data = { 0 };
    struct bma4_accel sensor_data = { 0 };

    /* Set accel FOC axis and it's sign (x, y, z, sign) */
    struct bma4_accel_foc_g_value g_value_foc = { 0, 0, 1, 0 };

    struct bma4_accel_config accel = { 0, 0, 0, 0 };

    /* Range for choosing 2G */
    uint8_t range = BMA4_ACCEL_RANGE_2G;

    /* Reference value is taken as 2G value */
    int16_t reference = 1024;

    int8_t rslt;

    uint8_t indx;

    /* Limit to print accel FOC data */
    uint16_t limit = 20;

    /* Function to select interface between SPI and I2C, according to that the device structure gets updated
     * Variant information given as parameter
     *         For B variant        : BMA42X_B_VARIANT
     *         For Non-B variant    : BMA42X_VARIANT
     */
    rslt = bma4_interface_selection(&bma, BMA42X_VARIANT);
    bma4_error_codes_print_result("bma4_interface_selection status", rslt);

    /* Sensor initialization */
    rslt = bma423_init(&bma);
    bma4_error_codes_print_result("bma4_init", rslt);

    /* Upload the configuration file to enable the features of the sensor. */
    rslt = bma423_write_config_file(&bma);
    bma4_error_codes_print_result("bma4_write_config", rslt);

    /* Enable the accelerometer */
    rslt = bma4_set_accel_enable(BMA4_ENABLE, &bma);
    bma4_error_codes_print_result("bma4_set_accel_enable status", rslt);
    bma.delay_us(BMA4_MS_TO_US(1), bma.intf_ptr);

    /* Function to get default configurations of accel */
    rslt = bma4_get_accel_config(&accel, &bma);

    accel.odr = BMA4_OUTPUT_DATA_RATE_50HZ;
    accel.bandwidth = BMA4_ACCEL_NORMAL_AVG4;
    accel.perf_mode = BMA4_ENABLE;
    accel.range = BMA4_ACCEL_RANGE_2G;

    /* Set current configurations for accel */
    rslt = bma4_set_accel_config(&accel, &bma);

    printf("Do not move the board while performing foc\n");

    printf("***** BEFORE ACCEL FOC *****\n");

    /* Read 20 samples of accelerometer values before FOC */
    for (indx = 0; indx < limit; indx++)
    {
        /* Giving a delay of 20ms before reading accelerometer data */
        bma.delay_us(BMA4_MS_TO_US(20), bma.intf_ptr);

        rslt = bma4_read_accel_xyz(&sensor_data, &bma);

        memcopy(&accel_foc_data[indx], &sensor_data, sizeof(struct bma4_accel));
        printf("X[%d] = %5d   Y[%d] = %5d   Z[%d] = %5d\n",
               indx,
               accel_foc_data[indx].x,
               indx,
               accel_foc_data[indx].y,
               indx,
               accel_foc_data[indx].z);

        temp_foc_data.x += accel_foc_data[indx].x;
        temp_foc_data.y += accel_foc_data[indx].y;
        temp_foc_data.z += accel_foc_data[indx].z;
    }

    /* Taking average values to calculate percentage deviation */
    avg_bef_foc_data.x = (int16_t)(temp_foc_data.x / 20);
    avg_bef_foc_data.y = (int16_t)(temp_foc_data.y / 20);
    avg_bef_foc_data.z = (int16_t)(temp_foc_data.z / 20);

    printf("***** AVERAGE BEFORE ACCEL FOC *****\n");
    printf("A-X = %d        A-Y = %d        A-Z = %d\n", avg_bef_foc_data.x, avg_bef_foc_data.y, avg_bef_foc_data.z);

    /* Taking modulus for comparison */
    if (avg_bef_foc_data.x < 0)
    {
        avg_bef_foc_data.x = avg_bef_foc_data.x * -1;
    }

    if (avg_bef_foc_data.y < 0)
    {
        avg_bef_foc_data.y = avg_bef_foc_data.y * -1;
    }

    if (avg_bef_foc_data.z < 0)
    {
        avg_bef_foc_data.z = avg_bef_foc_data.z * -1;
    }

    /* Checking the difference with reference if input is 'x' axis */
    if (g_value_foc.x == 1)
    {
        if (reference > avg_bef_foc_data.x)
        {
            x_diff_before = reference - avg_bef_foc_data.x;
        }
        else if (reference < avg_bef_foc_data.x)
        {
            x_diff_before = avg_bef_foc_data.x - reference;
        }

        matched_axis = 'X';
    }
    /* Checking the difference with reference if input is 'y' axis */
    else if (g_value_foc.y == 1)
    {
        if (reference > avg_bef_foc_data.y)
        {
            y_diff_before = reference - avg_bef_foc_data.y;
        }
        else if (reference < avg_bef_foc_data.y)
        {
            y_diff_before = avg_bef_foc_data.y - reference;
        }

        matched_axis = 'Y';
    }
    /* Checking the difference with reference if input is 'z' axis */
    else if (g_value_foc.z == 1)
    {
        if (reference > avg_bef_foc_data.z)
        {
            z_diff_before = reference - avg_bef_foc_data.z;
        }
        else if (reference < avg_bef_foc_data.z)
        {
            z_diff_before = avg_bef_foc_data.z - reference;
        }

        matched_axis = 'Z';
    }

    printf("\n");

    /* Perform accel FOC. */
    rslt = bma4_perform_accel_foc(&g_value_foc, &bma);

    if (rslt == BMA4_OK)
    {
        memset_function(accel_foc_data, 0, (20 * sizeof(struct bma4_accel)));
        memset_function(&temp_foc_data, 0, sizeof(struct bma4_temp_axes_val));

        printf("\n***** AFTER ACCEL FOC *****");

        /* Read accelerometer values after FOC */
        for (indx = 0; indx < 20; indx++)
        {
            /* Giving a delay of 20ms before reading accelerometer data */
            bma.delay_us(BMA4_MS_TO_US(20), bma.intf_ptr);
            rslt = bma4_read_accel_xyz(&sensor_data, &bma);

            memcopy(&accel_foc_data[indx], &sensor_data, sizeof(struct bma4_accel));
            printf("\nX[%d] = %5d   Y[%d] = %5d   Z[%d] = %5d",
                   indx,
                   accel_foc_data[indx].x,
                   indx,
                   accel_foc_data[indx].y,
                   indx,
                   accel_foc_data[indx].z);
            temp_foc_data.x += accel_foc_data[indx].x;
            temp_foc_data.y += accel_foc_data[indx].y;
            temp_foc_data.z += accel_foc_data[indx].z;
        }

        /* Taking average values to calculate percentage deviation */
        avg_aft_foc_data.x = (int16_t)(temp_foc_data.x / 20);
        avg_aft_foc_data.y = (int16_t)(temp_foc_data.y / 20);
        avg_aft_foc_data.z = (int16_t)(temp_foc_data.z / 20);
        printf("\n***** AVERAGE AFTER ACCEL FOC *****");
        printf("\nA-X = %d        A-Y = %d        A-Z = %d", avg_aft_foc_data.x, avg_aft_foc_data.y,
               avg_aft_foc_data.z);

        /* Taking modulus for comparison */
        if (avg_aft_foc_data.x < 0)
        {
            avg_aft_foc_data.x = avg_aft_foc_data.x * -1;
        }

        if (avg_aft_foc_data.y < 0)
        {
            avg_aft_foc_data.y = avg_aft_foc_data.y * -1;
        }

        if (avg_aft_foc_data.z < 0)
        {
            avg_aft_foc_data.z = avg_aft_foc_data.z * -1;
        }

        /* Checking the difference with reference if input is 'x' axis */
        if (matched_axis == 'X')
        {
            if (reference > avg_aft_foc_data.x)
            {
                x_diff_after = reference - avg_aft_foc_data.x;
            }
            else if (reference < avg_aft_foc_data.x)
            {
                x_diff_after = avg_aft_foc_data.x - reference;
            }
        }
        /* Checking the difference with reference if input is 'y' axis */
        else if (matched_axis == 'Y')
        {
            if (reference > avg_aft_foc_data.y)
            {
                y_diff_after = reference - avg_aft_foc_data.y;
            }
            else if (reference < avg_aft_foc_data.y)
            {
                y_diff_after = avg_aft_foc_data.y - reference;
            }
        }
        /* Checking the difference with reference if input is 'z' axis */
        else if (matched_axis == 'Z')
        {
            if (reference > avg_aft_foc_data.z)
            {
                z_diff_after = reference - avg_aft_foc_data.z;
            }
            else if (reference < avg_aft_foc_data.z)
            {
                z_diff_after = avg_aft_foc_data.z - reference;
            }
        }

        if (matched_axis == 'X')
        {
            if ((x_diff_after) <= x_diff_before)
            {
                if ((avg_aft_foc_data.x <= (reference + 255)) && (avg_aft_foc_data.x > (reference - 255)))
                {
                    printf("\n## PASS | Range = %d | Before FOC = %d | After FOC = %d | X_Difference = %d ##",
                           range,
                           x_diff_before,
                           x_diff_after,
                           x_diff_before - x_diff_after);
                    rslt = BMA4_OK;
                }
            }
            else if (x_diff_after > x_diff_before)
            {
                printf("\n## FAIL | Range = %d | Before FOC = %d | After FOC = %d | X_Difference = %d ##",
                       range,
                       x_diff_before,
                       x_diff_after,
                       x_diff_after - x_diff_before);
                rslt = BMA4_E_OUT_OF_RANGE;
            }
        }
        else if (matched_axis == 'Y')
        {
            if ((y_diff_after) <= y_diff_before)
            {
                if ((avg_aft_foc_data.y <= (reference + 255)) && (avg_aft_foc_data.y > (reference - 255)))
                {
                    printf("\n## PASS | Range = %d | Before FOC = %d | After FOC = %d | Y_Difference = %d ##",
                           range,
                           y_diff_before,
                           y_diff_after,
                           y_diff_before - y_diff_after);
                    rslt = BMA4_OK;
                }
            }
            else if (y_diff_after > y_diff_before)
            {
                printf("\n## FAIL | Range = %d | Before FOC = %d | After FOC = %d | Y_Difference = %d ##",
                       range,
                       y_diff_before,
                       y_diff_after,
                       y_diff_after - y_diff_before);

                rslt = BMA4_E_OUT_OF_RANGE;
            }
        }
        else if (matched_axis == 'Z')
        {
            if ((z_diff_after) <= z_diff_before)
            {
                if ((avg_aft_foc_data.z <= (reference + 255)) && (avg_aft_foc_data.z > (reference - 255)))
                {
                    printf("\n## PASS | Range = %d | Before FOC = %d | After FOC = %d | Z_Difference = %d ##",
                           range,
                           z_diff_before,
                           z_diff_after,
                           z_diff_before - z_diff_after);
                    rslt = BMA4_OK;
                }
            }
            else if (z_diff_after > z_diff_before)
            {
                printf("\n## FAIL | Range = %d | Before FOC = %d | After FOC = %d | Z_Difference = %d ##",
                       range,
                       z_diff_before,
                       z_diff_after,
                       z_diff_after - z_diff_before);

                rslt = BMA4_E_OUT_OF_RANGE;
            }
        }
        else
        {
            printf("\n## MATCHED AXIS = %d", matched_axis);
            printf("\n## UNEXPECTED | Range = %d | Before FOC = %d | After FOC = %d | X_Difference = %d ##",
                   range,
                   x_diff_before,
                   x_diff_after,
                   x_diff_after - x_diff_before);
            printf("\n## UNEXPECTED | Range = %d | Before FOC = %d | After FOC = %d | Y_Difference = %d ##",
                   range,
                   y_diff_before,
                   y_diff_after,
                   y_diff_after - y_diff_before);
            printf("\n## UNEXPECTED | Range = %d | Before FOC = %d | After FOC = %d | Z_Difference = %d ##",
                   range,
                   z_diff_before,
                   z_diff_after,
                   z_diff_after - z_diff_before);
            rslt = BMA4_E_OUT_OF_RANGE;
        }
    }

    if (rslt == BMA4_E_FOC_FAIL)
    {
        printf("\nInvalid position. FOC fails.");
    }
    else if (rslt == BMA4_E_OUT_OF_RANGE)
    {
        printf("\nAfter FOC is not better than Before FOC ");
    }
    else if (rslt == BMA4_OK)
    {
        printf("\nValid position");
    }

    return rslt;
}

/*!         Local Function Definitions
 ****************************************************************************/

/*!
 *  @brief This internal API is to copy contents from sensor data to foc data.
 */
static void memcopy(void *acc_foc_data, void *acc_sensor_data, int8_t size)
{
    /* Typecast gyr_sensor_data and acc_foc_data to (int8_t *). */
    int8_t *sensor_data = (int8_t *)acc_sensor_data;
    int8_t *foc_data = (int8_t *)acc_foc_data;

    /* Loop to copy the contents from sensor_data to foc_data. */
    for (int8_t indx = 0; indx < size; indx++)
    {
        foc_data[indx] = sensor_data[indx];
    }
}

/*!
 *  @brief This internal API is used to clear the buffer.
 */
static void memset_function(void* generic_void_pntr, uint8_t number, size_t limit)
{
    uint8_t indx;

    /* Type cast the string from void* to uint8_t* */
    uint8_t *ptr_data_u8 = (uint8_t*) generic_void_pntr;

    /* Fill elements/blocks within the limits with number in second argument */
    for (indx = 0; indx < limit; indx++)
    {
        ptr_data_u8[indx] = number;
    }
}
