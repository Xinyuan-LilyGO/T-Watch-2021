#include <Arduino.h>
#include <TWatch_hal.h>
//"TWatch_config.h" needs to be configured in the library for the first time
// This routine needs to annotate the LVGL GUI

TWatchClass *twatch = nullptr;
TFT_eSPI *tft = nullptr;
void setup()
{
    twatch = TWatchClass::getWatch();
    tft = twatch->Get_TFT();
    Serial.begin(115200);

    twatch->Motor_Shake(2, 50);

    tft->fillScreen(TFT_BLACK);
    twatch->Backlight_SetValue(255);
    Serial.println("Magnetometer Demo (TFT_eSPI)");

    twatch->Auto_update_HAL(true, 0);

    tft->setTextFont(2);
    tft->setTextColor(TFT_WHITE, TFT_BLACK);
    tft->drawString("Magnetometer Demo Test", 42, 90);
}

void loop()
{
    // put your main code here, to run repeatedly:
    char buf1[50];
    char buf2[50];
    delay(50);

    sprintf(buf1, "Azimuth : %03d ", twatch->MAG_GetAzimuthValue());
    sprintf(buf2, "X : %06d Y : %06d Z : %06d",
            twatch->MAG_GetX(),
            twatch->MAG_GetY(),
            twatch->MAG_GetZ());

    Serial.println(buf1);
    Serial.println(buf2);

    tft->drawString(buf1, 80, 108);
    tft->drawString(buf2, 10, 136);
}