
#include "./TWatch_hal.h"
#if CONFIG_TWATCH_APP_LVGL

#if defined(CONFIG_TWATCH_HAS_CST816S)
void TWatchClass::lv_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
  if (xEventGroupGetBits(_ttgo->_Hal_IRQ_event) & TOUCH_IRQ_BIT) {
    xEventGroupClearBits(_ttgo->_Hal_IRQ_event, TOUCH_IRQ_BIT);
    data->state = LV_INDEV_STATE_PR;
    data->point.x = _ttgo->touch_getX();
    data->point.y = _ttgo->touch_getY();
  } else {
    data->state = LV_INDEV_STATE_REL;
  }
}
#endif

#if defined(CONFIG_TWATCH_HAS_ENCODER)
void TWatchClass::lv_encoder_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
  data->enc_diff = _ttgo->encoder_get_diff();
  EventBits_t bit = xEventGroupClearBits(_hal_button_event, EVENT_CLICK_BIT(4));
  data->state = bit ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
}
#endif

#if defined(CONFIG_TWATCH_HAS_BUTTON)

void TWatchClass::lv_button_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
  //   EventBits_t bit = xEventGroupGetBits(_ttgo->_hal_button_event);
  //   bool isPress = false;
  // if (bit & EVENT_CLICK_BIT(1))
  // {
  //     DEBUGLN("EVENT_CLICK_BIT EVENT :1");
  //     xEventGroupClearBits(_ttgo->_hal_button_event, EVENT_CLICK_BIT(1));
  //     data->key = LV_KEY_ENTER;
  //     isPress = true;
  // }
  // else
  //   if (bit & EVENT_CLICK_BIT(2)) {
  //     DEBUGLN("EVENT_CLICK_BIT EVENT :2");
  //     xEventGroupClearBits(_ttgo->_hal_button_event, EVENT_CLICK_BIT(2));
  //     data->key = LV_KEY_LEFT;
  //     // data->enc_diff = 1;
  //     isPress = true;
  //   } else if (bit & EVENT_CLICK_BIT(3)) {
  //     DEBUGLN("EVENT_CLICK_BIT EVENT :3");
  //     xEventGroupClearBits(_ttgo->_hal_button_event, EVENT_CLICK_BIT(3));
  //     data->key = LV_KEY_RIGHT;
  //     // data->enc_diff = -1;
  //     isPress = true;
  //   }
  //   data->state = isPress ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
  //   if (isPress)
  //     DEBUGF("EVENT_CLICK_BIT EVENT :0x%X\n", bit);
}

#endif

void TWatchClass::lv_port_indev_init(void) {
#if defined(CONFIG_TWATCH_HAS_CST816S)
  // Touch
  static lv_indev_drv_t lv_touch_drv;
  lv_indev_drv_init(&lv_touch_drv);
  lv_touch_drv.type = LV_INDEV_TYPE_POINTER;
  lv_touch_drv.read_cb = lv_touchpad_read;
  lv_touch_handle = lv_indev_drv_register(&lv_touch_drv);
#endif

#if defined(CONFIG_TWATCH_HAS_ENCODER)
  static lv_indev_drv_t lv_encoder_drv;
  lv_indev_drv_init(&lv_encoder_drv);
  lv_encoder_drv.type = LV_INDEV_TYPE_ENCODER;
  lv_encoder_drv.read_cb = lv_encoder_read;
  lv_encoder_handle = lv_indev_drv_register(&lv_encoder_drv);
#endif

#if defined(CONFIG_TWATCH_HAS_BUTTON)
  static lv_indev_drv_t lv_button_drv;
  lv_indev_drv_init(&lv_button_drv);
  lv_button_drv.type = LV_INDEV_TYPE_BUTTON;
  lv_button_drv.read_cb = lv_button_read;
  lv_button_handle = lv_indev_drv_register(&lv_button_drv);
#endif
}

#endif