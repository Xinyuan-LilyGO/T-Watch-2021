#include <Arduino.h>
#include <TWatch_hal.h>

TWatchClass *twatch = nullptr;

void setup()
{
    twatch = new TWatchClass;
    Serial.begin(115200);
    twatch->Power_Init();
    twatch->Motor_Shake(2, 50);

    twatch->Get_TFT()->fillScreen(TFT_BLACK);
    twatch->Backlight_SetValue(255);

    Serial.println("Display Demo (TFT_eSPI)");

    twatch->Get_TFT()->fillRect(95, 95, 50, 50, TFT_GREEN);
    twatch->Get_TFT()->setTextColor(TFT_WHITE, TFT_BLACK);
    twatch->Get_TFT()->setTextFont(1);
    twatch->Get_TFT()->drawString("Hello T-Watch 2021", 65, 155);
}

void loop()
{
    // put your main code here, to run repeatedly:
    twatch->HAL_Update();

}