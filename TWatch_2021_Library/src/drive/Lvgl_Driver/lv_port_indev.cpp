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
static void encoder_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    data->enc_diff = TWatch::Encoder_GetDiff();
    bool isPush = TWatch::Encoder_GetIsPush();
    data->state = isPush ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
}
#endif

#if defined(TWatch_HAL_BOTTON)


void TWatchClass::botton_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    EventBits_t bit = xEventGroupGetBits(_ttgo->_hal_botton_event);
    bool isPress = false;
    if (bit & EVENT_CLICK_BIT(1))
    {
        DEBUGLN("EVENT_CLICK_BIT EVENT :1");
        xEventGroupClearBits(_ttgo->_hal_botton_event, EVENT_CLICK_BIT(1));
        data->key = LV_KEY_ENTER;
        isPress = true;
    }
    else if (bit & EVENT_CLICK_BIT(2))
    {
        DEBUGLN("EVENT_CLICK_BIT EVENT :2");
        xEventGroupClearBits(_ttgo->_hal_botton_event, EVENT_CLICK_BIT(2));
        data->key = LV_KEY_LEFT;
        //data->enc_diff = 1;
        isPress = true;
    }
    else if (bit & EVENT_CLICK_BIT(3))
    {
        DEBUGLN("EVENT_CLICK_BIT EVENT :3");
        xEventGroupClearBits(_ttgo->_hal_botton_event, EVENT_CLICK_BIT(3));
        data->key = LV_KEY_RIGHT;
        //data->enc_diff = -1;
        isPress = true;
    }
    data->state = isPress ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
    if (isPress)
        DEBUGF("EVENT_CLICK_BIT EVENT :0x%X\n", bit);
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
    encoder_drv.read_cb = encoder_read;
    lv_indev_drv_register(&encoder_drv);
#endif

#if defined(TWatch_HAL_BOTTON)
    static lv_indev_drv_t botton_drv;
    Botton_BindEvent(TWATCH_BTN_1, Click, []
                     {
        if (_ttgo->_hal_botton_event)
        {
            xEventGroupSetBits(_ttgo->_hal_botton_event, EVENT_CLICK_BIT(1));
        } 
        DEBUGLN("TWATCH_BTN_1 EVENT :Click"); });

    Botton_BindEvent(TWATCH_BTN_2, Click, []
                     {
        if (_ttgo->_hal_botton_event)
        {
            xEventGroupSetBits(_ttgo->_hal_botton_event, EVENT_CLICK_BIT(2));
        }
        DEBUGLN("TWATCH_BTN_2 EVENT :Click"); });
    Botton_BindEvent(TWATCH_BTN_3, Click, []
                     {
        if (_ttgo->_hal_botton_event)
        {
            xEventGroupSetBits(_ttgo->_hal_botton_event, EVENT_CLICK_BIT(3));
        }
        DEBUGLN("TWATCH_BTN_3 EVENT :Click"); });

    lv_indev_drv_init(&botton_drv);
    botton_drv.type = LV_INDEV_TYPE_ENCODER;
    botton_drv.read_cb = botton_read;
    lv_indev_drv_register(&botton_drv);
#endif


}

#endif