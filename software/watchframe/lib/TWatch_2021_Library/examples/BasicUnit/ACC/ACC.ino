#include <Arduino.h>
#include <TWatch_hal.h>
//"TWatch_config.h" needs to be configured in the library for the first time
// This routine needs to annotate the LVGL GUI

TWatchClass *twatch = nullptr;
TFT_eSPI *tft = nullptr;
bool isSingle_tag_irq, isDouble_tag_irq, isWrist_up_irq;

void single_tap_cb(void *p)
{
    isSingle_tag_irq = true;
}
void double_tap_cb(void *p)
{
    isDouble_tag_irq = true;
}
void wrist_cb(void *p)
{
    isWrist_up_irq = true;
}

void setup()
{
    twatch = TWatchClass::getWatch();
    tft = twatch->Get_TFT();

    Serial.begin(115200);
    twatch->Motor_Shake(2, 50);
    tft->fillScreen(TFT_BLACK);
    twatch->Backlight_SetValue(255);
    twatch->Auto_update_HAL(true, 1);

    tft->setTextFont(2);
    tft->setTextColor(TFT_WHITE, TFT_BLACK);
    tft->drawString("Motion Sensor Demo Test", 42, 90);
    Serial.println("Motion Sensor Demo");

    twatch->AccSensor_Feature(BMA423_STEP_CNTR |
                                  BMA423_WRIST_WEAR |
                                  BMA423_SINGLE_TAP |
                                  BMA423_DOUBLE_TAP,
                              true);

    twatch->AccSensor_Set_Feature_CB(BMA423_SINGLE_TAP_INT, single_tap_cb);
    twatch->AccSensor_Set_Feature_CB(BMA423_DOUBLE_TAP_INT, double_tap_cb);
    twatch->AccSensor_Set_Feature_CB(BMA423_WRIST_WEAR_INT, wrist_cb);

    twatch->AccSensor_Feature_Int(BMA423_SINGLE_TAP_INT |
                                      BMA423_DOUBLE_TAP_INT |
                                      BMA423_WRIST_WEAR_INT,
                                  true);

    Serial.println("   X   |   Y   |   Z   |   step");
}

void loop()
{
    // put your main code here, to run repeatedly:
    char buf[100];
    delay(10);
    sprintf(buf, "%02.3f | %02.3f | %02.3f | %03d\r\n",
            twatch->AccSensor_GetX(),
            twatch->AccSensor_GetY(),
            twatch->AccSensor_GetZ(),
            twatch->AccSensor_GetStep());
    Serial.printf(buf);
    tft->drawString("Motion Sensor Demo Test", 42, 90);
    tft->drawString("   X   |   Y   |   Z   |   step", 30, 108);
    tft->drawString(buf, 30, 126);

    if (isSingle_tag_irq)
    {
        isSingle_tag_irq = false;
        Serial.println("single_tap");
        tft->fillScreen(TFT_BLACK);
        tft->drawString("motion:  single_tap", 30, 146);
    }
    else if (isDouble_tag_irq)
    {
        isDouble_tag_irq = false;
        Serial.println("double_tap");
        tft->fillScreen(TFT_BLACK);
        tft->drawString("motion:  double_tap", 30, 146);
    }
    else if (isWrist_up_irq)
    {
        isWrist_up_irq = false;
        Serial.println("wrist up");
        tft->fillScreen(TFT_BLACK);
        tft->drawString("motion:  wrist up", 30, 146);
    }
}