#include <Arduino.h>
#include <TWatch_hal.h>

TWatchClass *ttgo = nullptr;

void WatchHalUpdataTask(void *param);
static void event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    ttgo->backlight_gradual_light(random(0, 100), 100);
  }
}

void setup() {
  Serial.begin(115200);

  ttgo = TWatchClass::getWatch();

  ttgo->backlight_set_value(100);
  /*Create a container with ROW flex direction*/
  lv_obj_t *cont_row = lv_obj_create(lv_scr_act());
  lv_obj_set_size(cont_row, 300, 75);
  lv_obj_align(cont_row, LV_ALIGN_TOP_MID, 0, 5);
  lv_obj_set_flex_flow(cont_row, LV_FLEX_FLOW_ROW);

  /*Create a container with COLUMN flex direction*/
  lv_obj_t *cont_col = lv_obj_create(lv_scr_act());
  lv_obj_set_size(cont_col, 200, 150);
  lv_obj_align_to(cont_col, cont_row, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
  lv_obj_set_flex_flow(cont_col, LV_FLEX_FLOW_COLUMN);

  unsigned int i;
  for (i = 0; i < 10; i++) {
    lv_obj_t *obj;
    lv_obj_t *label;

    /*Add items to the row*/
    obj = lv_btn_create(cont_row);
    lv_obj_set_size(obj, 100, LV_PCT(100));

    label = lv_label_create(obj);
    lv_label_set_text_fmt(label, "Item: %u", i);
    lv_obj_center(label);

    /*Add items to the column*/
    obj = lv_btn_create(cont_col);
    lv_obj_set_size(obj, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_add_event_cb(obj, event_handler, LV_EVENT_ALL, NULL);

    label = lv_label_create(obj);
    lv_label_set_text_fmt(label, "Item: %u", i);
    lv_obj_center(label);
  }
}

void loop() {}
