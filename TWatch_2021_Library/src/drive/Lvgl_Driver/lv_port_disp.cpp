//#include "Input.h"
#include "../../TWatch_hal.h"
#if (TWatch_APP_LVGL == 1) && defined(TWatch_HAL_Display)
/*
#define USE_TFT_DMA 0
#define USE_PSRAM 0
 */
#if USE_TFT_DMA && USE_PSRAM
#error "USE TFT DMA and USE PSRAM cannot be used at the same time"
#endif

// lv_disp_drv_t *disp_drv_p;

void TWatchClass::disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    TFT_eSPI *screen = (TFT_eSPI *)disp->user_data;
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    screen->startWrite();
    screen->setAddrWindow(area->x1, area->y1, w, h);
#if USE_TFT_DMA
    screen->pushPixelsDMA((uint16_t *)color_p, w * h);
#else
    screen->pushColors((uint16_t *)&color_p->full, w * h);
#endif
    screen->endWrite();

    lv_disp_flush_ready(disp);
}

void TWatchClass::lv_port_disp_init(SCREEN_CLASS *scr)
{
    static lv_disp_draw_buf_t draw_buf;
    Serial.println("lv_port_disp_init");
#if USE_PSRAM
    lv_disp_buf_p = (lv_color_t *)ps_calloc(sizeof(lv_color_t), DISP_BUF_SIZE);
    lv_disp_draw_buf_init(&draw_buf, lv_disp_buf_p, NULL, DISP_BUF_SIZE);
#else
    lv_disp_buf_p = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * DISP_BUF_SIZE, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    lv_disp_draw_buf_init(&draw_buf, lv_disp_buf_p, NULL, DISP_BUF_SIZE);
#endif
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = SCREEN_WIDTH;
    disp_drv.ver_res = SCREEN_HEIGHT;
    disp_drv.flush_cb = disp_flush;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.user_data = scr;
    lv_disp_drv_register(&disp_drv);
}

#endif
