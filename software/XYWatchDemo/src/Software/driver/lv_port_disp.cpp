#include "Input.h"

#define USE_TFT_DMA 1
#define USE_PSRAM 0

#if USE_TFT_DMA && USE_PSRAM
#error "USE TFT DMA and USE PSRAM cannot be used at the same time"
#endif

#define DISP_BUF_SIZE (screenWidth * screenHeight) / 10

static const uint32_t screenWidth = 240;
static const uint32_t screenHeight = 240;
static lv_disp_draw_buf_t draw_buf;

static lv_color_t *buf1;
//static lv_color_t *buf2;

static void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    SCREEN_CLASS *screen = (SCREEN_CLASS *)disp->user_data;
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    screen->startWrite();
    screen->setAddrWindow(area->x1, area->y1, w, h);
#if USE_TFT_DMA
    screen->pushPixelsDMA((uint16_t *)color_p, w * h);
    //screen->pushImageDMA(area->x1, area->y1, w, h, (uint16_t *)&color_p->full);
#else
    screen->pushColors((uint16_t *)&color_p->full, w * h);
#endif
    screen->endWrite();
    lv_disp_flush_ready(disp);
}

void lv_port_disp_init(SCREEN_CLASS *scr)
{

#if USE_PSRAM
    buf1 = (lv_color_t *)ps_calloc(sizeof(lv_color_t), DISP_BUF_SIZE);
    buf2 = (lv_color_t *)ps_calloc(sizeof(lv_color_t), DISP_BUF_SIZE);
    lv_disp_draw_buf_init(&draw_buf, buf1, buf2, DISP_BUF_SIZE);
#else
    buf1 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * DISP_BUF_SIZE, MALLOC_CAP_DMA | MALLOC_CAP_8BIT);
    //buf2 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * DISP_BUF_SIZE, MALLOC_CAP_DMA | MALLOC_CAP_8BIT);
    lv_disp_draw_buf_init(&draw_buf, buf1, NULL, DISP_BUF_SIZE);
#endif
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.user_data = scr;
    lv_disp_drv_register(&disp_drv);
}