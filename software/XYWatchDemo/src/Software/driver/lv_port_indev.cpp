#include "Input.h"

static void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    bool isTouch = XYWatch::Touch_Updata();
    data->state = isTouch ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
    data->point.x = XYWatch::Touch_GetX();
    data->point.y = XYWatch::Touch_GetY();
}

#if XYWATCH_HAS_ENCODER
static void my_encoder_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    data->enc_diff = XYWatch::Encoder_GetDiff();
    bool isPush = XYWatch::Encoder_GetIsPush();
    data->state = isPush ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
}
#endif
void lv_port_indev_init(void)
{
    //Touch
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

#if XYWATCH_HAS_ENCODER
    static lv_indev_drv_t encoder_drv;
    lv_indev_drv_init(&encoder_drv);
    encoder_drv.type = LV_INDEV_TYPE_ENCODER;
    encoder_drv.read_cb = my_encoder_read;
    lv_indev_drv_register(&encoder_drv);
#endif
}