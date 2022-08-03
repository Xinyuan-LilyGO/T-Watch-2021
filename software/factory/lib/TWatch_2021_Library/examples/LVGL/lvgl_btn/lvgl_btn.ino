#include <Arduino.h>
#include <TWatch_hal.h>

//"TWatch_config.h" needs to be configured in the library for the first time
// This project requires LVGL, please uncomment it

lv_obj_t *count_label;
uint32_t count = 0;
TWatchClass *twatch = nullptr;

static void event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);

  if (code == LV_EVENT_CLICKED) {
    lv_label_set_text_fmt(count_label, "Count:%d", count++);
  } else if (code == LV_EVENT_VALUE_CHANGED) {
    LV_LOG_USER("Toggled");
  }
}

void setup() {
  Serial.begin(115200);
  twatch = TWatchClass::getWatch();

  Serial.println("lvgl btn Demo (LVGL)");
  twatch->backlight_set_value(100);

  twatch->hal_auto_update(true, 0);

  lv_obj_t *label;
  lv_obj_t *btn1 = lv_btn_create(lv_scr_act());
  lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
  lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -40);

  label = lv_label_create(btn1);
  lv_label_set_text(label, "Button");
  lv_obj_center(label);

  count_label = lv_label_create(lv_scr_act());
  lv_label_set_text(count_label, "Count:0");
  lv_obj_center(count_label);

  lv_obj_t *btn2 = lv_btn_create(lv_scr_act());
  lv_obj_add_event_cb(btn2, event_handler, LV_EVENT_ALL, NULL);
  lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 40);
  lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
  lv_obj_set_height(btn2, LV_SIZE_CONTENT);

  label = lv_label_create(btn2);
  lv_label_set_text(label, "Toggle");
  lv_obj_center(label);
}

void loop() {}
