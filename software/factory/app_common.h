#pragma once

#include "TWatch_hal.h"

lv_obj_t *app_create_btn(lv_obj_t *obj, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs, char *text);
void app_set_table_info(lv_obj_t *table, uint8_t col, char *name, uint32_t addr, char *state);
void app_set_table_info(lv_obj_t *table, uint8_t col, char *name, char *addr, char *state);
void app_set_table_info(lv_obj_t *table, uint8_t col, int name, const char *addr, int state);