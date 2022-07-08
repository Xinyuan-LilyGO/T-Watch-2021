
#include "app_common.h"

lv_obj_t *app_create_btn(lv_obj_t *obj, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs, char *text) {
  lv_obj_t *btn = lv_btn_create(obj);
  lv_obj_align(btn, align, x_ofs, y_ofs);

  lv_obj_t *label = lv_label_create(btn);
  lv_label_set_text(label, text);
  lv_obj_center(label);
  return btn;
}

void app_set_table_info(lv_obj_t *table, uint8_t col, char *name, uint32_t addr, char *state) {
  lv_table_set_cell_value(table, col, 0, name);
  lv_table_set_cell_value_fmt(table, col, 1, "0x%02X", addr);
  lv_table_set_cell_value(table, col, 2, state);
}
void app_set_table_info(lv_obj_t *table, uint8_t col, char *name, char *addr, char *state) {
  lv_table_set_cell_value(table, col, 0, name);
  lv_table_set_cell_value(table, col, 1, addr);
  lv_table_set_cell_value(table, col, 2, state);
}

void app_set_table_info(lv_obj_t *table, uint8_t col, int name, const char *addr, int state) {
  lv_table_set_cell_value_fmt(table, col, 0, "%d", name);
  lv_table_set_cell_value(table, col, 1, addr);
  lv_table_set_cell_value_fmt(table, col, 2, "%d", state);
}