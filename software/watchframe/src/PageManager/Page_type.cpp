#include "Page_type.h"

lv_style_t Borderless_style;
lv_style_t icon_64_style;
lv_style_t Initial_screen_style; //圆形初始化屏幕风格

LV_FONT_DECLARE(user_symbol)

void Page_Style_Init(void)
{
    lv_style_init(&Initial_screen_style);
    lv_style_set_border_width(&Initial_screen_style, 0);
    lv_style_set_outline_width(&Initial_screen_style, 0);
    lv_style_set_pad_all(&Initial_screen_style, 0);
    lv_style_set_radius(&Initial_screen_style, LV_RADIUS_CIRCLE);
    lv_style_set_height(&Initial_screen_style, SCREEN_HEIGHT);
    lv_style_set_width(&Initial_screen_style, SCREEN_WIDTH);
    lv_style_set_bg_color(&Initial_screen_style, lv_color_black());
    // lv_style_set_clip_corner(&Initial_screen_style, true);

    lv_style_init(&Borderless_style);
    lv_style_set_border_width(&Borderless_style, 0);
    lv_style_set_outline_width(&Borderless_style, 0);
    // lv_style_remove_prop()

    lv_style_init(&icon_64_style);
    lv_style_set_height(&icon_64_style, 68);
    lv_style_set_width(&icon_64_style, 68);
    lv_style_set_radius(&icon_64_style, 20);
    // lv_style_set_bg_color(&icon_64_style,lv_palette_lighten(LV_PALETTE_GREY, 2));
    // lv_style_set_outline_width(&icon_64_style, 1);
    // lv_style_set_outline_color(&icon_64_style, lv_palette_lighten(LV_PALETTE_GREY, 3));
    // lv_style_remove_prop(&icon_64_style, LV_STYLE_BG_COLOR);
}