/*
 * Copyright (C) 2020 Bosch Sensortec GmbH
 *
 * The license is available at root folder
 *
 */

/*!
 * @ingroup bma400Examples
 * @defgroup bma400ExamplesSelfTest Self test
 * @brief Perform accelerometer self test
 * \include selftest.c
 */

#include <stdio.h>
#include "bma400.h"
#include "common.h"

int main(int argc, char const *argv[])
{
    struct bma400_dev bma;
    int8_t rslt;

    /* Interface reference is given as a parameter
     *         For I2C : BMA400_I2C_INTF
     *         For SPI : BMA400_SPI_INTF
     */
    rslt = bma400_interface_init(&bma, BMA400_I2C_INTF);
    bma400_check_rslt("bma400_interface_init", rslt);

    rslt = bma400_init(&bma);
    bma400_check_rslt("bma400_init", rslt);

    rslt = bma400_soft_reset(&bma);
    bma400_check_rslt("bma400_soft_reset", rslt);

    rslt = bma400_perform_self_test(&bma);
    bma400_check_rslt("bma400_perform_self_test", rslt);

    if (rslt == BMA400_OK)
    {
        printf("\nSelf-test passed.\r\n");
    }

    bma400_coines_deinit();

    return rslt;
}
