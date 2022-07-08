#include "./TWatch_hal.h"

#if defined(CONFIG_TWATCH_HAS_DISPLAY)

// void lv_spi_post_cb(spi_transaction_t *trans);

void TWatchClass::tft_init()
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
TFT_eSPI *TWatchClass::tft_get_instance()
{
    return tft;
}

#endif