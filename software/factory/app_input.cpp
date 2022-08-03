#include "TWatch_hal.h"
#include "app_common.h"

void app_sleep_cb(lv_event_t *e);
void app_button_cb(lv_event_t *e);
void app_return_cb(lv_event_t *e);
void app_motor_cb(lv_event_t *e);

static bool app_flag_return_invalid = false;
static lv_obj_t *button[3];
static uint32_t press_count[3] = {0, 0, 0};
bool get_app_io_test(void) {
  return app_flag_return_invalid;
}

void app_io_test(lv_event_t *e) {
  TWatchClass *ttgo = TWatchClass::getWatch();
  app_flag_return_invalid = true;
  lv_obj_t *cout = (lv_obj_t *)lv_event_get_user_data(e);

  lv_obj_t *btn = app_create_btn(cout, LV_ALIGN_TOP_LEFT, 40, 30, LV_SYMBOL_NEW_LINE);
  lv_obj_set_size(btn, 40, 40);
  lv_obj_add_event_cb(btn, app_return_cb, LV_EVENT_CLICKED, cout);

  btn = app_create_btn(cout, LV_ALIGN_TOP_LEFT, 90, 30, "Motor");
  lv_obj_set_size(btn, 50, 40);
  lv_obj_add_event_cb(btn, app_motor_cb, LV_EVENT_CLICKED, NULL);

  btn = app_create_btn(cout, LV_ALIGN_LEFT_MID, 10, 0, "Sleep");
  lv_obj_set_size(btn, 70, 50);
  lv_obj_add_event_cb(btn, app_sleep_cb, LV_EVENT_CLICKED, NULL);

  button[0] = app_create_btn(cout, LV_ALIGN_CENTER, -80, 60, "btn 1");
  lv_obj_set_size(button[0], 50, 50);
  lv_obj_set_style_radius(button[0], LV_RADIUS_CIRCLE, 0);
  lv_obj_add_flag(button[0], LV_OBJ_FLAG_CHECKABLE);
  lv_obj_add_event_cb(button[0], app_button_cb, LV_EVENT_CLICKED, &press_count[0]);

  button[1] = app_create_btn(cout, LV_ALIGN_CENTER, 80, -60, "btn 2");
  lv_obj_set_size(button[1], 50, 50);
  lv_obj_set_style_radius(button[1], LV_RADIUS_CIRCLE, 0);
  lv_obj_add_flag(button[1], LV_OBJ_FLAG_CHECKABLE);
  lv_obj_add_event_cb(button[1], app_button_cb, LV_EVENT_CLICKED, &press_count[1]);

  button[2] = app_create_btn(cout, LV_ALIGN_CENTER, 80, 60, "btn 3");
  lv_obj_set_size(button[2], 50, 50);
  lv_obj_set_style_radius(button[2], LV_RADIUS_CIRCLE, 0);
  lv_obj_add_flag(button[2], LV_OBJ_FLAG_CHECKABLE);
  lv_obj_add_event_cb(button[2], app_button_cb, LV_EVENT_CLICKED, &press_count[2]);

  lv_obj_set_tile(lv_obj_get_parent(cout), cout, LV_ANIM_ON);

#if defined(TWatch2021_V2)
  lv_group_t *g = lv_group_create();
  lv_indev_set_group(ttgo->lv_encoder_handle, g);
  lv_group_set_default(g);

  const char *opts = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10";
  lv_obj_t *roller = lv_roller_create(cout);
  lv_roller_set_options(roller, opts, LV_ROLLER_MODE_INFINITE);
  lv_roller_set_visible_row_count(roller, 3);
  lv_obj_align(roller, LV_ALIGN_CENTER, 0, 30);
  lv_roller_set_selected(roller, 5, LV_ANIM_ON);

  // lv_group_add_obj(g, roller);

  lv_event_send(roller, LV_EVENT_FOCUSED, NULL);
#endif
}

void app_send_clicked_event(uint8_t btn) {
  switch (btn) {
  case TWATCH_BTN_1:
    lv_event_send(button[0], LV_EVENT_CLICKED, &press_count[0]);
    break;
  case TWATCH_BTN_2:
    lv_event_send(button[1], LV_EVENT_CLICKED, &press_count[1]);
    break;
  case TWATCH_BTN_3:
    lv_event_send(button[2], LV_EVENT_CLICKED, &press_count[2]);
    break;
  default:
    break;
  }
}

void app_button_cb(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *instance = (lv_obj_t *)lv_event_get_target(e);
  uint32_t *count = (uint32_t *)lv_event_get_user_data(e);
  if (code == LV_EVENT_CLICKED) {

    lv_obj_t *label = lv_obj_get_child(instance, 0);
    lv_label_set_text_fmt(label, "%" LV_PRId32, *count);
    *count = *(count) + 1;
  }
}

void app_sleep_cb(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *instance = (lv_obj_t *)lv_event_get_target(e);
  uint32_t *count = (uint32_t *)lv_event_get_user_data(e);
  TWatchClass *ttgo = TWatchClass::getWatch();
  if (code == LV_EVENT_CLICKED) {
    ttgo->touch_interrupt(true);
    ttgo->hal_sleep(true);
  }
}

void app_return_cb(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *parent = (lv_obj_t *)lv_event_get_user_data(e);
  if (code == LV_EVENT_CLICKED) {
    app_flag_return_invalid = false;
    lv_obj_clean(parent);
    lv_obj_set_tile_id(lv_obj_get_parent(parent), 0, 0, LV_ANIM_ON);
  }
}

void app_motor_cb(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  TWatchClass *ttgo = TWatchClass::getWatch();
  if (code == LV_EVENT_CLICKED) {
    ttgo->motor_shake(4, 500);
  }
}
