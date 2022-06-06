#include "./XYWatch_hal.h"

TFT_eSPI *tft = nullptr;

void XYWatch::Display_Init()
{
    tft = new TFT_eSPI();
    tft->begin();
    tft->setRotation(0);
//#if USE_TFT_DMA
    tft->initDMA(TFT_CS);
//#endif
}

void *XYWatch::Get_tft()
{
    return tft;
}