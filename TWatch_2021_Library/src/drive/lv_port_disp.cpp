//#include "Input.h"
#include "./TWatch_hal.h"

#if CONFIG_TWATCH_APP_LVGL  && defined(CONFIG_TWATCH_HAS_DISPLAY)

lv_disp_drv_t *disp_drv_p;

void TWatchClass::lv_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    TFT_eSPI *screen = (TFT_eSPI *)disp->user_data;
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    screen->startWrite();
    screen->setAddrWindow(area->x1, area->y1, w, h);
#if USE_TFT_DMA == 1
    disp_drv_p = disp;
    screen->pushPixelsDMA((uint16_t *)color_p, w * h);
    screen->endWrite();
    // lv_disp_flush_ready(disp);
#else
    screen->pushColors((uint16_t *)&color_p->full, w * h);
    screen->endWrite();
    lv_disp_flush_ready(disp);
#endif
}

#if USE_TFT_DMA == 1
void display_send_DMA_done_cb(spi_transaction_t *trans)
{
    lv_disp_flush_ready(disp_drv_p);
}
#endif

void display_wait_cb(_lv_disp_drv_t *disp_drv)
{
    delay(1);
}

void TWatchClass::lv_port_disp_init(SCREEN_CLASS *scr)
{
    static lv_disp_draw_buf_t draw_buf;

#if USE_TFT_DMA == 1
    tft->initDMA(true, display_send_DMA_done_cb);
    // tft->initDMA(true);
#endif
#if defined(TWatch_HAL_PSRAM)
    lv_disp_buf_p = (lv_color_t *)ps_calloc(sizeof(lv_color_t), DISP_BUF_SIZE);
    lv_disp_draw_buf_init(&draw_buf, lv_disp_buf_p, NULL, DISP_BUF_SIZE);
#else
    if (lv_disp_buf_p == nullptr)
    {
        lv_disp_buf_p = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * DISP_BUF_SIZE, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    }
    lv_disp_draw_buf_init(&draw_buf, lv_disp_buf_p, NULL, DISP_BUF_SIZE);
#endif
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = SCREEN_WIDTH;
    disp_drv.ver_res = SCREEN_HEIGHT;
    disp_drv.flush_cb = lv_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.wait_cb = display_wait_cb;
    disp_drv.user_data = scr;
    lv_disp_drv_register(&disp_drv);
}

#endif
