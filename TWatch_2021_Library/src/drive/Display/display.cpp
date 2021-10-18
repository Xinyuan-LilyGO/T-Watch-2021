#include "../../TWatch_hal.h"

#if defined(TWatch_HAL_Display)

void TWatchClass::Display_Init()
{
    int16_t w = 240;
    int16_t h = 240;
    uint32_t drv = 0x9A01;
    uint32_t freq = 27000000;

    pinMode(TWATCH_TFT_RST, OUTPUT);
    digitalWrite(TWATCH_TFT_RST, HIGH);
    delay(5);
    digitalWrite(TWATCH_TFT_RST, LOW);
    delay(20);
    digitalWrite(TWATCH_TFT_RST, HIGH);

    tft = new TFT_eSPI(w, h);
    tft->setDriver(drv, freq);
    tft->setPins(TWATCH_TFT_MOSI, TWATCH_TFT_MISO, TWATCH_TFT_SCLK, TWATCH_TFT_CS, TWATCH_TFT_DC);

    tft->begin();
    tft->setRotation(TFT_Rotation);

#if USE_TFT_DMA == 1
    tft->initDMA();
#endif
}

TFT_eSPI *TWatchClass::Get_TFT()
{
    return tft;
}

#endif