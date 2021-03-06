#include <Arduino.h>
#include <TWatch_hal.h>
//"TWatch_config.h" needs to be configured in the library for the first time
// This routine needs to annotate the LVGL GUI

/*
T-Watch-2021-V1.0:  This version of the alarm clock and motion sensor use independent GPIO, no alarm interrupt pin
*/

/*
T-Watch-2021-V1.2:  Since the ESP32 pins are not enough, the interrupts of the alarm clock, 
                    touch, and motion sensor are concentrated in the "TWATCH_AIO_INT" pin, 
                    so the reason for the wake-up is all the external trigger "TWATCH_AIO_INT" to wake up.
*/
TWatchClass *twatch = nullptr;
TFT_eSPI *tft = nullptr;

char buf[128];

void print_wakeup_reason()
{
    esp_sleep_wakeup_cause_t wakeup_reason;

    wakeup_reason = esp_sleep_get_wakeup_cause();
    tft->setTextColor(TFT_GREEN, TFT_BLACK);
    switch (wakeup_reason)
    {
    case ESP_SLEEP_WAKEUP_EXT0:
        Serial.println("Wakeup caused by external signal using RTC_IO");
        tft->drawString("Wakeup caused by", 20, 144);
        tft->drawString("external signal using RTC_IO", 20, 162);
        break;
    case ESP_SLEEP_WAKEUP_EXT1:
        Serial.println("Wakeup caused by external signal using RTC_CNTL");
        tft->drawString("Wakeup caused by", 20, 144);
        tft->drawString("external signal using RTC_CNTL", 20, 162);
        break;
    case ESP_SLEEP_WAKEUP_TIMER:
        Serial.println("Wakeup caused by timer");
        tft->drawString("Wakeup caused by", 20, 144);
        tft->drawString(" timer", 20, 162);
        break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
        Serial.println("Wakeup caused by touchpad");
        tft->drawString("Wakeup caused by", 20, 144);
        tft->drawString(" touchpad", 20, 162);
        break;
    case ESP_SLEEP_WAKEUP_ULP:
        Serial.println("Wakeup caused by ULP program");
        tft->drawString("Wakeup caused by ", 20, 144);
        tft->drawString("ULP program", 20, 162);
        break;
    default:
        Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason);
        break;
    }
    tft->setTextColor(TFT_WHITE, TFT_BLACK);
}

void setup()
{
    twatch = TWatchClass::getWatch();
    tft = twatch->Get_TFT();

    Serial.begin(115200);
    twatch->Motor_Shake(2, 50);

    tft->fillScreen(TFT_BLACK);
    twatch->Backlight_SetValue(255);

    Serial.println("Touch Wake Up Demo");

    twatch->Auto_update_HAL(true, 0);

    tft->setTextFont(2);
    tft->setTextColor(TFT_WHITE, TFT_BLACK);
    tft->drawString("Touch Wake Up Demo", 62, 90);
    tft->drawString("Enter deep sleep after 5 seconds", 10, 108);
    tft->drawString("touch the screen to wake up", 20, 126);
    print_wakeup_reason();
}

void loop()
{
    // put your main code here, to run repeatedly:
    delay(5000);
    twatch->Touch_Interrupt(true);
    twatch->HAL_Sleep(true);
}