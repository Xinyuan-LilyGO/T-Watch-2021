#include "./TWatch_hal.h"

TWatchClass *TWatchClass::_ttgo = nullptr;
EventGroupHandle_t TWatchClass::_Hal_IRQ_event = nullptr;

#if defined(TWatch_HAL_BOTTON)
EventGroupHandle_t TWatchClass::_hal_botton_event = nullptr;
#endif

void TWatchClass::HAL_Init(void)
{
#if defined(TWatch_HAL_Display) && (TWatch_APP_LVGL == 1)
    // Move the malloc process to Init() to make sure that the largest heap can be used for this buffer.
    // lv_disp_buf_p = static_cast<lv_color_t *>(malloc(DISP_BUF_SIZE * sizeof(lv_color_t)));
    // if (lv_disp_buf_p == nullptr)
    //     LV_LOG_WARN("lv_port_disp_init malloc failed!\n");
#endif
    esp_task_wdt_deinit();
    Power_Init();
#if defined(TWatch_HAL_Display)
    Backlight_Init();
    Display_Init();
#endif

#if defined(TWatch_HAL_Touch)
    Touch_Init();
#endif

#if defined(TWatch_HAS_ENCODER)
    Encoder_Init();
#endif

#if defined(TWatch_HAL_BOTTON)
    Botton_Init();
#endif

#if defined(TWatch_HAS_FFAT)
    FFat_Init();
#endif

#if defined(TWatch_HAL_Display) && (TWatch_APP_LVGL == 1)
    lv_init();
    lv_port_disp_init(Get_TFT());
    lv_port_indev_init();
    lv_ffat_fs_if_init();
#endif

#if defined(TWatch_HAS_SD)
    SD_Init();

#endif

#if defined(TWatch_HAL_QMC5883L)
    MAG_Init();
#endif
#if defined(TWatch_HAL_PCF8563)
    RTC_Init();
#endif

#if defined(TWatch_HAL_MOTOR)
    Motor_Init();
#endif
#if defined(TWatch_HAS_BME280)
    TempSensor_Init();
#endif

#if defined(TWatch_HAS_GPS)
    GPS_Init();
#endif
#if defined(TWatch_HAL_BMA423)
    AccSensor_Interface_Init();
    AccSensor_Init();
#endif

    /*     Time_Updata(1, 0);
    Backlight_SetValue(255);
    WIFI_Init(); */

    /* WIFI_Init();
    WIFI_Scan(); */
}

void TWatchClass::Auto_update_HAL(bool en, uint8_t core)
{
    if (en)
    {
        if (HAL_Update_Handle == NULL)
            xTaskCreatePinnedToCore(HAL_Update, "HAL_Update", 1024 * 8, NULL, 2, &HAL_Update_Handle, core);
    }
    else
    {
        if (HAL_Update_Handle != NULL)
        {
            vTaskDelete(HAL_Update_Handle);
            HAL_Update_Handle = NULL;
        }
    }
}

void Debugloop(uint32_t millis, uint32_t time_ms)
{
    static uint32_t Millis;
    if (millis - Millis > time_ms)
    {
        DEBUGF("Total heap: %d\n", ESP.getHeapSize());
        DEBUGF("Free heap: %d\n", ESP.getFreeHeap());
        DEBUGF("Max Alloc Heap: %d\n", ESP.getMaxAllocHeap());
        DEBUGF("Total PSRAM: %d\n", ESP.getPsramSize());
        DEBUGF("Free PSRAM: %d\n", ESP.getFreePsram());
        Millis = millis;
    }
}

void TWatchClass::HAL_Update(void *param)
{
    static uint32_t ms;
    while (1)
    {
        ms = millis();
#if defined(TWatch_HAL_Touch)
        _ttgo->Touch_Updata(ms, 10);
#endif
#if defined(TWatch_HAL_Display)
        _ttgo->Backlight_Updata(ms, 1);
#endif
#if defined(TWatch_HAL_Display) && (TWatch_APP_LVGL == 1)
        lv_timer_handler();
#endif
#if defined(TWatch_HAL_PCF8563)
        _ttgo->Time_Updata(ms, 1000);
#endif
#if defined(TWatch_HAL_QMC5883L)
        _ttgo->MAG_Updata(ms, 100);
#endif
#if defined(TWatch_HAL_BMA423)
        _ttgo->AccSensor_Updata(ms, 100);
#endif
#if defined(TWatch_HAL_BOTTON)
        _ttgo->Botton_Updata(ms, 10);
#endif
#if defined(TWatch_HAL_MOTOR)
        _ttgo->Motor_Loop(ms);
#endif
#if defined(TWatch_HAS_GPS)
        _ttgo->GPS_Parse();
#endif
#if defined(TWatch_HAS_BME280)
        _ttgo->TempSensor_Updata(ms, 41);
#endif
#if defined(TWatch_HAL_AIO_INT)
        _ttgo->HAL_AIO_IRQ_cb();
#endif
#if (TWatch_DEBUG == 1)
        // Debugloop(ms, 1000);
#endif
        _ttgo->Power_Updata(ms, 5);
        delay(1);
    }
}

void TWatchClass::HAL_Sleep(bool deep)
{
    uint64_t mask;
    uint32_t bl = Backlight_GetValue();
    // Touch_Interrupt(true);
    // AccSensor_Feature(BMA423_WRIST_WEAR | BMA423_SINGLE_TAP | BMA423_DOUBLE_TAP | BMA423_STEP_CNTR, true);
    // AccSensor_Feature_Int(BMA423_WRIST_WEAR_INT | BMA423_STEP_CNTR_INT | BMA423_SINGLE_TAP_INT | BMA423_DOUBLE_TAP_INT, true);
    // AccSensor_Acc_Feature(false);

    // Backlight_GradualLight();
    pinMode(TWATCH_IICSCL, INPUT_PULLUP);
    pinMode(TWATCH_IICSDA, INPUT_PULLUP);

    pinMode(TWATCH_PWR_ON, OUTPUT);
    digitalWrite(TWATCH_PWR_ON, LOW);

    Backlight_SetValue(0);
#if defined(TWATCH_AIO_INT)
    mask = 1ull << TWATCH_AIO_INT;
    esp_sleep_enable_ext1_wakeup(mask, ESP_EXT1_WAKEUP_ALL_LOW); // Screen int
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_0 /* BTN_0 */, LOW);
#else
    mask = 1ull << TWATCH_TOUCH_INT;
    esp_sleep_enable_ext1_wakeup(mask, ESP_EXT1_WAKEUP_ALL_LOW); // Screen int
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_39 /* TWATCH_BMA_INT_2 */, LOW);
#endif
    Serial.printf("go to sleep\n");

    if (deep)
        esp_deep_sleep_start();
    else
    {
        esp_light_sleep_start();

        Backlight_SetValue(bl);
        digitalWrite(TWATCH_PWR_ON, HIGH);
        Touch->setTouchInt(false);
    }
}

#if defined(TWatch_HAL_AIO_INT)
void TWatchClass::HAL_AIO_IRQ_cb()
{
    uint16_t int_status = 0;
    if (xEventGroupGetBits(_Hal_IRQ_event) & EVENT_IRQ_BIT)
    {
        xEventGroupClearBits(_Hal_IRQ_event, EVENT_IRQ_BIT);
        if (Rtc->alarmActive()) // Check if it is an alarm interrupt
        {
            Rtc->resetAlarm();
            DEBUGLN("_alarm_irq_cb");
            if (_alarm_irq_cb != nullptr)
            {
                _alarm_irq_cb(NULL);
            }
        }
        else
        {
            bma423_read_int_status(&int_status, bma423);
            if (int_status & BMA423_SINGLE_TAP_INT)
            {
                DEBUGLN("Single tap received");
                if (_bma_irq_cb.single_tap_cb != nullptr)
                {
                    _bma_irq_cb.single_tap_cb(NULL);
                }
            }
            else if (int_status & BMA423_DOUBLE_TAP_INT)
            {
                DEBUGLN("Double tap received");
                if (_bma_irq_cb.double_tap_cb != nullptr)
                {
                    _bma_irq_cb.double_tap_cb(NULL);
                }
            }
            else if (int_status & BMA423_WRIST_WEAR_INT)
            {
                DEBUGLN("Wrist wear received");
                if (_bma_irq_cb.wrist_wear_cb != nullptr)
                {
                    _bma_irq_cb.wrist_wear_cb(NULL);
                }
            }
            else if (int_status & BMA423_STEP_CNTR_INT)
            {
                DEBUGLN("Step cntr received");
                if (_bma_irq_cb.step_cntr_cb != nullptr)
                {
                    _bma_irq_cb.step_cntr_cb(NULL);
                }
            }
            else if (int_status & BMA423_ACTIVITY_INT)
            {
                DEBUGLN("Activity received");
                if (_bma_irq_cb.activity_cb != nullptr)
                {
                    _bma_irq_cb.activity_cb(NULL);
                }
            }
            else if (int_status & BMA423_ANY_MOT_INT)
            {
                DEBUGLN("Any mot received");
                if (_bma_irq_cb.any_mot_cb != nullptr)
                {
                    _bma_irq_cb.any_mot_cb(NULL);
                }
            }
            else if (int_status & BMA423_NO_MOT_INT)
            {
                DEBUGLN("No mot received");
                if (_bma_irq_cb.no_mot_cb != nullptr)
                {
                    _bma_irq_cb.no_mot_cb(NULL);
                }
            }
        }
    }
}
#endif