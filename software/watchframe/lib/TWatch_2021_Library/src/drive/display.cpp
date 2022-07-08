#include "./TWatch_hal.h"

#if defined(TWatch_HAL_Display)

// void lv_spi_post_cb(spi_transaction_t *trans);

void TWatchClass::Display_Init()
{
    tft = new TFT_eSPI();

    tft->begin();

    tft->invertDisplay(true);
    tft->setSwapBytes(true);
    tft->setRotation(TFT_Rotation);
// #if USE_TFT_DMA == 1
//     // tft->initDMA(true, display_send_DMA_done_cb);
//     tft->initDMA(true);
// #endif
}
TFT_eSPI *TWatchClass::Get_TFT()
{
    return tft;
}

#endif