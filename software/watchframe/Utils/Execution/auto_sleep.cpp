// #include "FreeRTOS.h"
#include "TWatch_hal.h"
#include "auto_sleep.h"
// #include "PageManager/PageManager.h"

static uint32_t delay_time = 10;
static uint32_t timekeeper = 0;
static TWatchClass *ttgo;
static QueueHandle_t updata_timekeeper;
static bool start_auto_sleep;
/**
 * @brief
 * bit 0:wrist_up
 * bit 1:double_tap
 * bit 2:screen
 */
static uint8_t wake_up_bit;

void wait_auto_sleep(void)
{
    static uint32_t Millis;
    if (millis() - Millis > 1000 && start_auto_sleep)
    {
        DEBUGF("timekeeper :%d,delay_time :%d\n", timekeeper, delay_time);
        timekeeper++;
        int tmp = 0;
        if (xQueueReceive(updata_timekeeper, &tmp, 0))
        {
            timekeeper = tmp;
        }

        if (timekeeper > delay_time)
        {
            timekeeper = 0;
            // xQueueSend(goto_sleep_queue_handle, &wake_up_bit, 0);
            uint8_t bma423_bit = 0;
            uint8_t bma423_int_bit = 0;
            if (wake_up_bit & _BV(0))
            {
                bma423_bit |= BMA423_WRIST_WEAR;
                bma423_int_bit |= BMA423_WRIST_WEAR_INT;
            }

            if (wake_up_bit & _BV(1))
            {
                bma423_bit |= BMA423_DOUBLE_TAP;
                bma423_int_bit |= BMA423_DOUBLE_TAP_INT;
            }

            DEBUGLN("sleep");
            ttgo->AccSensor_Feature(bma423_bit, true);
            ttgo->AccSensor_Feature_Int(bma423_int_bit, true);

            if (wake_up_bit & _BV(2))
                ttgo->Touch_Interrupt(true);

            ttgo->HAL_Sleep(false);
        }
        Millis = millis();
    }
}

void auto_sleep_start(void)
{
    ttgo = TWatchClass::getWatch();
    updata_timekeeper = xQueueCreate(1, sizeof(int));
    start_auto_sleep = true;
}

void auto_sleep_set_time(uint32_t delay)
{
    delay_time = delay;
    DEBUGF("auto_sleep:%d\n", delay_time);
}

/**
 * @brief Setting the Wake Source
 *
 * @param Wake_up_reason
 * @param Enable
 */
void auto_sleep_set_wake_up(wake_up_reason_t reason, bool Enable)
{
    if (Enable)
        wake_up_bit |= _BV(reason);
    else
        wake_up_bit &= !_BV(reason);
}

void auto_sleep_close(void)
{
    start_auto_sleep = false;
}

void auto_sleep_updeta(void)
{
    int i = 0;
    xQueueSend(updata_timekeeper, &i, 0);
}