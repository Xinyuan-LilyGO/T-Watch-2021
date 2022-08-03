#include "ui_main.h"
#include "TWatch_hal.h"
#include "app_ble.h"
#include "app_input.h"
#include "app_sensor.h"
#include "app_wifi.h"

void ui_create_test_project(lv_obj_t *parent, char *text, lv_event_cb_t event_cb);
static lv_obj_t *main_window = nullptr;
static lv_obj_t *sub_window = nullptr;
static lv_group_t *g;

void ui_init(void) {
  g = lv_group_create();
  lv_group_set_default(g);

  lv_indev_t *cur_drv = NULL;
  for (;;) {
    cur_drv = lv_indev_get_next(cur_drv);
    if (!cur_drv) {
      break;
    }
    if (cur_drv->driver->type == LV_INDEV_TYPE_ENCODER) {
      lv_indev_set_group(cur_drv, g);
    }
  }

  main_window = lv_tileview_create(lv_scr_act());
  lv_obj_set_size(main_window, 240, 240);

  lv_obj_t *menu_window = lv_tileview_add_tile(main_window, 0, 0, LV_DIR_NONE);
  sub_window = lv_tileview_add_tile(main_window, 1, 0, LV_DIR_NONE);

  //   lv_obj_set_size(menu_window, LV_PCT(100), LV_PCT(100));
  lv_obj_t *version_info = lv_label_create(menu_window);
  lv_obj_align(version_info, LV_ALIGN_TOP_MID, 0, 20);
  lv_obj_set_style_text_align(version_info, LV_TEXT_ALIGN_CENTER, 0);
#if defined(TWatch2021_V1)
  lv_label_set_text(version_info, "T-WATCH-2021-V1");
#elif defined(TWatch2021_V1_2)
  lv_label_set_text(version_info, "T-WATCH-2021-V1_2");
#elif defined(TWatch2021_V2)
  lv_label_set_text(version_info, "T-WATCH-2021-V2");
#endif

  lv_obj_t *cont = lv_obj_create(menu_window);
  lv_obj_set_size(cont, 240, 200);
  lv_obj_align(cont, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);

  ui_create_test_project(cont, "Sensor Status Check", app_sensor_test);
  ui_create_test_project(cont, "input device detection", app_io_test);
  ui_create_test_project(cont, "WIFI", app_wifi_func);
  ui_create_test_project(cont, "Bluetooth", app_bluetooth_scan_func);


}

void ui_create_test_project(lv_obj_t *parent, char *text, lv_event_cb_t event_cb) {
  lv_obj_t *btn = lv_btn_create(parent);
  lv_obj_set_width(btn, lv_pct(100));

  lv_obj_t *label = lv_label_create(btn);
  lv_label_set_text(label, text);
  lv_obj_add_event_cb(btn, event_cb, LV_EVENT_CLICKED, sub_window);
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
}

void ui_send_event_cb(uint8_t btn) {

  switch (btn) {
  case TWATCH_BTN_1:
    if (!get_app_io_test()) {
      lv_obj_set_tile_id(main_window, 0, 0, LV_ANIM_ON);
      lv_obj_clean(sub_window);
    } else {
      app_send_clicked_event(TWATCH_BTN_1);
    }
    break;
  default:
    app_send_clicked_event(btn);
    break;
  }
}