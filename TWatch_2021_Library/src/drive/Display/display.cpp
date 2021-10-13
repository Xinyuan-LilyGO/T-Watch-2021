#include "./TWatch_hal.h"

#if defined(TWatch_HAL_Display)



void TWatch::Display_Init()
{
    tft = new TFT_eSPI();
    tft->begin();
    tft->setRotation(0);
//#if USE_TFT_DMA
    tft->initDMA(TFT_CS);
//#endif
}


#endif