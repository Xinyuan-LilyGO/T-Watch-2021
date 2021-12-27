#include "Input.h"

#if (TWatch_APP_LVGL == 1)

#if defined(TWatch_HAL_Touch)
static void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    CST816S *indev = (CST816S *)indev_driver->user_data;
    bool isTouch = indev->ReadTouch();
    data->state = isTouch ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
    data->point.x = indev->getX();
    data->point.y = indev->getY();
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

void lv_port_indev_init(void *indev)
{
#if defined(TWatch_HAL_Touch)
    // Touch
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    indev_drv.user_data = indev;
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