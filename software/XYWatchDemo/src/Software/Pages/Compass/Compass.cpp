#include "Compass.h"

#define Pointerlength 68

#define OriginX 114
#define OriginY 110

static lv_obj_t *Compass;
lv_meter_scale_t *Scale;

static lv_obj_t *directionN;
static lv_obj_t *directionS;
static lv_obj_t *directionE;
static lv_obj_t *directionW;

static int Azimuth;

static void Excessive_cb(void *indic, int32_t v)
{
    double PointerX;
    double PointerY;
    lv_meter_set_scale_range(Compass, Scale, 0, 360, 330, v);

    PointerX = OriginX + (sin(((v + 90) % 360) * PI / 180) * Pointerlength);
    PointerY = OriginY - (cos(((v + 90) % 360) * PI / 180) * Pointerlength);
    lv_obj_align(directionN, LV_ALIGN_TOP_LEFT, PointerX, PointerY);

    PointerX = OriginX + (sin(((v + 180) % 360) * PI / 180) * Pointerlength);
    PointerY = OriginY - (cos(((v + 180) % 360) * PI / 180) * Pointerlength);
    lv_obj_align(directionE, LV_ALIGN_TOP_LEFT, PointerX, PointerY);

    PointerX = OriginX + (sin(((v + 270) % 360) * PI / 180) * Pointerlength);
    PointerY = OriginY - (cos(((v + 270) % 360) * PI / 180) * Pointerlength);
    lv_obj_align(directionS, LV_ALIGN_TOP_LEFT, PointerX, PointerY);

    PointerX = OriginX + (sin(v * PI / 180) * Pointerlength);
    PointerY = OriginY - (cos(v * PI / 180) * Pointerlength);
    lv_obj_align(directionW, LV_ALIGN_TOP_LEFT, PointerX, PointerY);
}

static void Compass_timer(lv_timer_t *timer)
{
    Azimuth = XYWatch::MAG_GetValue();
    static int last_Azimuth;
    int last_Azimuth_t;

    lv_anim_t Excessive_a;
    lv_anim_init(&Excessive_a);
    if (abs(Azimuth - last_Azimuth) > 300)
    {
        last_Azimuth_t = (Azimuth - last_Azimuth) > 0 ? 0 : 360;
        lv_anim_set_values(&Excessive_a, last_Azimuth, last_Azimuth_t);
        last_Azimuth = Azimuth;
    }
    else
    {
        lv_anim_set_values(&Excessive_a, last_Azimuth, Azimuth);
        last_Azimuth = Azimuth;
    }
    lv_anim_set_repeat_count(&Excessive_a, 0);
    lv_anim_set_exec_cb(&Excessive_a, Excessive_cb);
    lv_anim_set_var(&Excessive_a, Scale);
    lv_anim_set_time(&Excessive_a, 100);
    lv_anim_start(&Excessive_a);
}

void CompassScreen(lv_obj_t *screen)
{
    double PointerX;
    double PointerY;
    Compass = lv_meter_create(screen);
    lv_obj_add_style(Compass, &BlackStyle, 0);

    lv_obj_set_size(Compass, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_border_width(Compass, -12, 0);

    lv_obj_remove_style(Compass, NULL, LV_PART_INDICATOR);

    Scale = lv_meter_add_scale(Compass);
    lv_meter_set_scale_range(Compass, Scale, 0, 360, 330, 270);
    lv_meter_set_scale_ticks(Compass, Scale, 13, 2, 5, lv_color_white());

    lv_meter_set_scale_major_ticks(Compass, Scale, 1, 2, 10, lv_color_white(), 15);

    LV_IMG_DECLARE(img_pointer);
    lv_obj_t *CompassPointer = lv_img_create(Compass);
    lv_img_set_src(CompassPointer, &img_pointer);
    lv_obj_align(CompassPointer, LV_ALIGN_CENTER, 3, -15);

    directionN = lv_label_create(Compass);
    PointerX = OriginX + (sin(Azimuth * PI / 180) * Pointerlength);
    PointerY = OriginY - (cos(Azimuth * PI / 180) * Pointerlength);
    lv_obj_align(directionN, LV_ALIGN_TOP_LEFT, PointerX, PointerY);
    lv_obj_add_style(directionN, &Font_w_18_Style, 0);
    lv_obj_set_style_text_color(directionN, lv_palette_darken(LV_PALETTE_RED, 1), 0);
    lv_label_set_text(directionN, "N");

    directionE = lv_label_create(Compass);
    PointerX = OriginX + (sin(((Azimuth + 90) % 360) * PI / 180) * Pointerlength);
    PointerY = OriginY - (cos(((Azimuth + 90) % 360) * PI / 180) * Pointerlength);
    lv_obj_align(directionE, LV_ALIGN_TOP_LEFT, PointerX, PointerY);
    lv_obj_add_style(directionN, &Font_w_18_Style, 0);
    lv_label_set_text(directionE, "E");

    directionS = lv_label_create(Compass);
    PointerX = OriginX + (sin(((Azimuth + 180) % 360) * PI / 180) * Pointerlength);
    PointerY = OriginY - (cos(((Azimuth + 180) % 360) * PI / 180) * Pointerlength);
    lv_obj_align(directionS, LV_ALIGN_TOP_LEFT, PointerX, PointerY);
    lv_obj_add_style(directionN, &Font_w_18_Style, 0);
    lv_obj_set_style_text_color(directionS, lv_palette_darken(LV_PALETTE_BLUE, 1), 0);
    lv_label_set_text(directionS, "S");

    directionW = lv_label_create(Compass);
    PointerX = OriginX + (sin(((Azimuth + 270) % 360) * PI / 180) * Pointerlength);
    PointerY = OriginY - (cos(((Azimuth + 270) % 360) * PI / 180) * Pointerlength);
    lv_obj_align(directionW, LV_ALIGN_TOP_LEFT, PointerX, PointerY);
    lv_obj_add_style(directionN, &Font_w_18_Style, 0);
    lv_label_set_text(directionW, "W");

    lv_timer_t *timer = lv_timer_create(Compass_timer, 100, nullptr);
}
