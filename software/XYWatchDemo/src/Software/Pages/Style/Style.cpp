#include "Style.h"

lv_style_t Clock2bgStyle;
lv_style_t WhiteStyle;
lv_style_t BlackStyle;

lv_style_t Font_w_48_Style;
lv_style_t Font_w_18_Style;

lv_style_t Font_Nixie_18_Style;
lv_style_t Font_Nixie_32_Style;
lv_style_t Font_Nixie_48_Style;
lv_style_t Font_Nixie_70_Style;

lv_style_t Line_Small_Style;

lv_style_t IconBgStyle;

lv_style_t ThemeStyle;

void DialStyleInit(void)
{
    lv_style_init(&Font_w_18_Style);
    lv_style_set_text_font(&Font_w_18_Style, &lv_font_montserrat_18);
    lv_style_set_text_color(&Font_w_18_Style, lv_color_white());

    lv_style_init(&Font_w_48_Style);
    lv_style_set_text_font(&Font_w_48_Style, &lv_font_montserrat_48);
    lv_style_set_text_color(&Font_w_48_Style, lv_color_white());

    lv_style_init(&Font_Nixie_18_Style);
    lv_style_set_text_font(&Font_Nixie_18_Style, &font_nixie_18);
    lv_style_set_text_color(&Font_Nixie_18_Style, lv_color_black());

    lv_style_init(&Font_Nixie_32_Style);
    lv_style_set_text_font(&Font_Nixie_32_Style, &font_nixie_32);
    lv_style_set_text_color(&Font_Nixie_32_Style, lv_color_black());

    lv_style_init(&Font_Nixie_48_Style);
    lv_style_set_text_font(&Font_Nixie_48_Style, &font_nixie_48);
    lv_style_set_text_color(&Font_Nixie_48_Style, lv_color_black());

    lv_style_init(&Font_Nixie_70_Style);
    lv_style_set_text_font(&Font_Nixie_70_Style, &font_nixie_70);
    lv_style_set_text_color(&Font_Nixie_70_Style, lv_color_black());

    lv_style_init(&Clock2bgStyle);
    lv_style_set_radius(&Clock2bgStyle, 190);

    lv_style_set_bg_opa(&Clock2bgStyle, LV_OPA_COVER);
    lv_style_set_bg_color(&Clock2bgStyle, lv_palette_lighten(LV_PALETTE_GREY, 1));
    lv_style_set_bg_grad_color(&Clock2bgStyle, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_dir(&Clock2bgStyle, LV_GRAD_DIR_VER);

    lv_style_set_bg_main_stop(&Clock2bgStyle, 128);
    lv_style_set_bg_grad_stop(&Clock2bgStyle, 192);

    lv_style_init(&ThemeStyle);
    lv_style_set_radius(&ThemeStyle, 190);
    lv_style_set_bg_color(&ThemeStyle, lv_palette_darken(LV_PALETTE_BLUE_GREY, 1));

    lv_style_init(&WhiteStyle);
    lv_style_set_radius(&WhiteStyle, 190);
    lv_style_set_bg_color(&WhiteStyle, lv_color_white());

    lv_style_init(&BlackStyle);
    lv_style_set_radius(&BlackStyle, 190);
    lv_style_set_bg_color(&BlackStyle, lv_color_black());

    lv_style_init(&Line_Small_Style);
    lv_style_set_line_width(&Line_Small_Style, 2);
    lv_style_set_line_color(&Line_Small_Style, lv_palette_darken(LV_PALETTE_GREY, 2));

    lv_style_init(&IconBgStyle);
    lv_style_set_bg_color(&IconBgStyle, lv_color_black());
    lv_style_set_text_color(&IconBgStyle, lv_color_black());
}