#include <Arduino.h>
#include <TWatch_hal.h>

//"TWatch_config.h" needs to be configured in the library for the first time
// This routine needs to annotate the LVGL GUI

TWatchClass *twatch = nullptr;
TFT_eSPI *tft = nullptr;

void btn1_click()
{
    Serial.println("BTN1 Click");
    tft->drawString("BTN1 Click", 80, 118);
}
void btn2_click()
{
    Serial.println("BTN2 Click");
    tft->drawString("BTN2 Click", 80, 118);
}
void btn3_click()
{
    Serial.println("BTN3 Click");
    tft->drawString("BTN3 Click", 80, 118);
}

void setup()
{
    twatch = TWatchClass::getWatch();
    tft = twatch->Get_TFT();
    
    Serial.begin(115200);
    Serial.println("Button Demo (TFT_eSPI)");

    twatch->Motor_Shake(2, 50);

    tft->fillScreen(TFT_BLACK);
    twatch->Backlight_SetValue(255);

    twatch->Auto_update_HAL(true, 1);

    tft->setTextFont(2);
    tft->setTextColor(TFT_BLACK, TFT_WHITE);
    tft->drawString("T-Watch Button Test", 62, 90);

    twatch->Botton_BindEvent(TWATCH_BTN_1, TWatchClass::Click, btn1_click);
    twatch->Botton_BindEvent(TWATCH_BTN_2, TWatchClass::Click, btn2_click);
    twatch->Botton_BindEvent(TWATCH_BTN_3, TWatchClass::Click, btn3_click);
}

void loop()
{
    // put your main code here, to run repeatedly:


}
