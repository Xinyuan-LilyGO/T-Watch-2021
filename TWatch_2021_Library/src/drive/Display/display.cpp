#include "../../TWatch_hal.h"

#if defined(TWatch_HAL_Display)

// void lv_spi_post_cb(spi_transaction_t *trans);

void TWatchClass::Display_Init()
{
    tft = new TFT_eSPI();
    // tft->setDriver(drv, freq);
    // tft->setPins(TWATCH_TFT_MOSI, TWATCH_TFT_MISO, TWATCH_TFT_SCLK, TWATCH_TFT_CS, TWATCH_TFT_DC);

    tft->begin();
    // tft->invertDisplay(false);
    tft->setSwapBytes(false);
    
    tft->setRotation(TFT_Rotation);

#if USE_TFT_DMA == 1
    tft->initDMA(TWATCH_TFT_CS);
#endif
}
TFT_eSPI *TWatchClass::Get_TFT()
{
    return tft;
}

#endif