/**
 * Copyright (C) 2020 Bosch Sensortec GmbH. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "bma400.h"
#include "coines.h"

/*! Read write length varies based on user requirement */
#define READ_WRITE_LENGTH  UINT8_C(46)

/* Variable to store the device address */
static uint8_t dev_addr;

/*!
 * @brief I2C read function map to COINES platform
 */
BMA400_INTF_RET_TYPE bma400_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    uint8_t dev_addr = *(uint8_t*)intf_ptr;

    return coines_read_i2c(dev_addr, reg_addr, reg_data, (uint16_t)len);
}

/*!
 * @brief I2C write function map to COINES platform
 */
BMA400_INTF_RET_TYPE bma400_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    uint8_t dev_addr = *(uint8_t*)intf_ptr;

    return coines_write_i2c(dev_addr, reg_addr, (uint8_t *)reg_data, (uint16_t)len);
}

/*!
 * @brief SPI read function map to COINES platform
 */
BMA400_INTF_RET_TYPE bma400_spi_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    uint8_t dev_addr = *(uint8_t*)intf_ptr;

    return coines_read_spi(dev_addr, reg_addr, reg_data, (uint16_t)len);
}

/*!
 * @brief SPI write function map to COINES platform
 */
BMA400_INTF_RET_TYPE bma400_spi_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    uint8_t dev_addr = *(uint8_t*)intf_ptr;

    return coines_write_spi(dev_addr, reg_addr, (uint8_t *)reg_data, (uint16_t)len);
}

/*!
 * @brief Delay function map to COINES platform
 */
void bma400_delay_us(uint32_t period, void *intf_ptr)
{
    coines_delay_usec(period);
}

void bma400_check_rslt(const char api_name[], int8_t rslt)
{
    switch (rslt)
    {
        case BMA400_OK:

            /* Do nothing */
            break;
        case BMA400_E_NULL_PTR:
            printf("Error [%d] : Null pointer\r\n", rslt);
            break;
        case BMA400_E_COM_FAIL:
            printf("Error [%d] : Communication failure\r\n", rslt);
            break;
        case BMA400_E_INVALID_CONFIG:
            printf("Error [%d] : Invalid configuration\r\n", rslt);
            break;
        case BMA400_E_DEV_NOT_FOUND:
            printf("Error [%d] : Device not found\r\n", rslt);
            break;
        default:
            printf("Error [%d] : Unknown error code\r\n", rslt);
            break;
    }
}

int8_t bma400_interface_init(struct bma400_dev *bma400, uint8_t intf)
{
    int8_t rslt = BMA400_OK;

    /* Switch VDD for sensor off */
    coines_set_shuttleboard_vdd_vddio_config(0, 0);
    coines_config_i2c_bus(COINES_I2C_BUS_0, COINES_I2C_FAST_MODE);

    /* Switch VDD for sensor on */
    coines_set_shuttleboard_vdd_vddio_config(3300, 3300);

    if (bma400 != NULL)
    {
        int16_t result = coines_open_comm_intf(COINES_COMM_INTF_USB);
        if (result < COINES_SUCCESS)
        {
            printf(
                "\n Unable to connect with Application Board ! \n" " 1. Check if the board is connected and powered on. \n" " 2. Check if Application Board USB driver is installed. \n"
                " 3. Check if board is in use by another application. (Insufficient permissions to access USB) \n");
            exit(result);
        }

        coines_set_shuttleboard_vdd_vddio_config(0, 0);
        coines_delay_msec(100);

        /* Bus configuration : I2C */
        if (intf == BMA400_I2C_INTF)
        {
            printf("I2C Interface \n");

            dev_addr = BMA400_I2C_ADDRESS_SDO_LOW;
            bma400->read = bma400_i2c_read;
            bma400->write = bma400_i2c_write;
            bma400->intf = BMA400_I2C_INTF;
            coines_config_i2c_bus(COINES_I2C_BUS_0, COINES_I2C_STANDARD_MODE);
        }
        /* Bus configuration : SPI */
        else if (intf == BMA400_SPI_INTF)
        {
            printf("SPI Interface \n");

            dev_addr = COINES_SHUTTLE_PIN_7;
            bma400->read = bma400_spi_read;
            bma400->write = bma400_spi_write;
            bma400->intf = BMA400_SPI_INTF;
            coines_config_spi_bus(COINES_SPI_BUS_0, COINES_SPI_SPEED_7_5_MHZ, COINES_SPI_MODE0);
        }

        bma400->intf_ptr = &dev_addr;
        bma400->delay_us = bma400_delay_us;
        bma400->read_write_len = READ_WRITE_LENGTH;

        coines_delay_msec(100);

        coines_set_shuttleboard_vdd_vddio_config(3300, 3300);

        coines_delay_msec(200);
    }
    else
    {
        rslt = BMA400_E_NULL_PTR;
    }

    return rslt;
}

void bma400_coines_deinit(void)
{
    coines_close_comm_intf(COINES_COMM_INTF_USB);
}
