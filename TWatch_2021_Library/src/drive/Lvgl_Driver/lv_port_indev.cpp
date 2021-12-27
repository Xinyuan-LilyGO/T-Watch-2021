//#include "Input.h"
#include "../../TWatch_hal.h"
#if (TWatch_APP_LVGL == 1)

#if defined(TWatch_HAL_Touch)
void TWatchClass::touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    if (xEventGroupGetBits(_ttgo->_Hal_IRQ_event) & TOUCH_IRQ_BIT)
    {
        xEventGroupClearBits(_ttgo->_Hal_IRQ_event, TOUCH_IRQ_BIT);
        data->state = LV_INDEV_STATE_PR;
        data->point.x = _ttgo->Touch_GetX();
        data->point.y = _ttgo->Touch_GetY();
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }
}
#endif

#if defined(TWatch_HAS_ENCODER)
static void my_encoder_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    data->enc_diff = TWatch::Encoder_GetDiff();
    bool isPush = TWatch::Encoder_GetIsPush();
    data->state = isPush ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
}
#endif

void TWatchClass::lv_port_indev_init(void)
{
#if defined(TWatch_HAL_Touch)
    // Touch
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touchpad_read;
    lv_indev_drv_register(&indev_drv);
#endif

#if defined(TWatch_HAS_ENCODER)
    static lv_indev_drv_t encoder_drv;
    lv_indev_drv_init(&encoder_drv);
    encoder_drv.type = LV_INDEV_TYPE_ENCODER;
    encoder_drv.read_cb = my_encoder_read;
    lv_indev_drv_register(&encoder_drv);
#endif
}

#endif