#pragma once

#include "TWatch_hal.h"

struct unit_t
{
    uint8_t hex;
    char *name;
};

void factory_page(lv_obj_t *obj);
void factory_loop(void);