#include "Page_Application.h"
#include "PageManager.h"

#define MAX_REGISTERED_APP 20
#define DEFAULT_ICON_SIZE 50

#define CENTER_COORD_X 145 //(SCREEN_WIDTH / 2 + (DEFAULT_ICON_SIZE / 2))
#define CENTER_COORD_Y 145 //(SCREEN_HEIGHT / 2 + (DEFAULT_ICON_SIZE / 2))

static lv_group_t *menu_group = nullptr;
static lv_group_t *app_group = nullptr;
static lv_obj_t *_menu_scr = nullptr;
static lv_obj_t *_menu_disp = nullptr;
static lv_obj_t *_app_disp = nullptr;
static lv_obj_t *_tv = nullptr;

static App_item_t *App[MAX_REGISTERED_APP] = {nullptr};
static uint8_t App_quantity = 0;
static bool _app_is_running = false;
static uint8_t _app_running_index = 0;

static bool _is_scroll_menu = false;
static void AppCoord(uint8_t num, float offset, float r, int16_t *x, int16_t *y);

void App_Menu_init(lv_obj_t *screen)
{
    _menu_scr = screen;
    lv_obj_remove_style(_menu_scr, NULL, LV_PART_SCROLLBAR);
    lv_obj_add_style(_menu_scr, &Initial_screen_style, 0);
    lv_obj_clear_flag(_menu_scr, LV_OBJ_FLAG_SCROLLABLE);
    // App_Menu_create();
}

/*加载app*/
void load_cb(lv_event_t *e)
{
    uint32_t event_code = lv_event_get_code(e);
    lv_obj_t *instance = lv_event_get_target(e);
    uint16_t index = lv_obj_get_index(instance);
    if (event_code == LV_EVENT_SHORT_CLICKED)
    {
        load_app(index);
        switch_interface++;
    }
}
/* 拖动图标 */
void scroll_menu_cb(lv_event_t *e)
{
    uint32_t event_code = lv_event_get_code(e);
    lv_obj_t *get_app = lv_obj_get_child(_menu_disp, 0);
    if (event_code == LV_EVENT_PRESSING)
    {
        _is_scroll_menu = true;
        lv_indev_t *indev = lv_indev_get_act();
        lv_point_t vect;
        lv_indev_get_vect(indev, &vect);
        lv_coord_t x = lv_obj_get_x(get_app) + vect.x;
        lv_coord_t y = lv_obj_get_y(get_app) + vect.y;
        for (int i = 0; i < App_quantity; i++)
        {
            get_app = lv_obj_get_child(_menu_disp, i);
            lv_obj_t *bg_icon = lv_obj_get_child(get_app, 0);
            int16_t icon_x, icon_y;
            AppCoord(i, 0, DEFAULT_ICON_SIZE, &icon_x, &icon_y);
            int16_t coord_x = (x + icon_x + (DEFAULT_ICON_SIZE / 2)) + 25;
            int16_t coord_y = (y + icon_y + (DEFAULT_ICON_SIZE / 2)) + 25;

            int16_t calculate_tmp_1 = (CENTER_COORD_X - coord_x);
            calculate_tmp_1 = calculate_tmp_1 * calculate_tmp_1;
            int16_t calculate_tmp_2 = (CENTER_COORD_Y - coord_y);
            calculate_tmp_2 = calculate_tmp_2 * calculate_tmp_2;
            int16_t distance = sqrt(calculate_tmp_1 + calculate_tmp_2);
            uint8_t quadrant; //象限
            if (coord_y < 95)
            {
                if (coord_x > 95)
                    quadrant = 1;
                else
                    quadrant = 2;
            }
            else
            {
                if (coord_x > 95)
                    quadrant = 4;
                else
                    quadrant = 3;
            }

            if (distance > 90) // Near the edge
            {
                int16_t icon_size = 90 + DEFAULT_ICON_SIZE - distance;
                icon_size = constrain(icon_size, 0, DEFAULT_ICON_SIZE);
                lv_obj_set_size(get_app, icon_size, icon_size);

                float tmp = icon_size * 1.0 / DEFAULT_ICON_SIZE;
                lv_img_set_zoom(bg_icon, LV_IMG_ZOOM_NONE * tmp);

                int16_t x_offset, y_offset;
                int16_t fixed_offset = ((DEFAULT_ICON_SIZE - icon_size) / 2);
                float r = ((x + icon_x) * 1.0) / distance;

                switch (quadrant)
                {
                case 1:
                    x_offset = (fixed_offset * sin(r));
                    y_offset = fixed_offset * cos(r);
                    break;
                case 2:
                    x_offset = -(fixed_offset * sin(r)); //
                    y_offset = fixed_offset * cos(r);
                    break;
                case 3:
                    x_offset = -(fixed_offset * sin(r)); //
                    y_offset = -(fixed_offset * cos(r));
                    break;
                case 4:
                    x_offset = (fixed_offset * sin(r));
                    y_offset = -(fixed_offset * cos(r));
                    break;
                }

                if (i == 0)
                    lv_obj_set_pos(get_app, x + icon_x, y + icon_y);
                else
                    lv_obj_set_pos(get_app, x + icon_x + fixed_offset + x_offset, y + icon_y + fixed_offset + y_offset);
            }
            else
            {
                lv_obj_set_size(get_app, DEFAULT_ICON_SIZE, DEFAULT_ICON_SIZE);
                lv_img_set_zoom(bg_icon, LV_IMG_ZOOM_NONE);
                lv_obj_set_pos(get_app, x + icon_x, y + icon_y);
            }
        }
    }
}

static void AppCoord(uint8_t num, float offset, float r, int16_t *x, int16_t *y)
{
    *x = fixed_coord_table[num].x;
    *y = fixed_coord_table[num].y;
}

void App_Menu_create(void)
{
    int16_t x, y;
    _menu_disp = lv_obj_create(_menu_scr);
    lv_obj_center(_menu_disp);
    lv_obj_remove_style(_menu_disp, NULL, LV_PART_SCROLLBAR);
    lv_obj_clear_flag(_menu_disp, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_style(_menu_disp, &Initial_screen_style, 0);
    lv_obj_set_style_bg_color(_menu_disp, lv_color_black(), 0);

    /* Display icon */
    for (int i = 0; i < App_quantity; i++)
    {
        lv_obj_t *app_icon = lv_btn_create(_menu_disp);
        lv_obj_set_size(app_icon, DEFAULT_ICON_SIZE, DEFAULT_ICON_SIZE);
        AppCoord(i, 0, 50, &x, &y);
        lv_obj_set_pos(app_icon, x + 120 - (DEFAULT_ICON_SIZE / 2), y + 120 - (DEFAULT_ICON_SIZE / 2));
        lv_obj_set_style_radius(app_icon, 90, 0);

        lv_obj_t *bg_icon = lv_img_create(app_icon);
        lv_obj_center(bg_icon);
        lv_img_set_src(bg_icon, (lv_img_dsc_t *)&App[i]->icon);
        lv_img_set_zoom(bg_icon, LV_IMG_ZOOM_NONE);

        lv_obj_add_event_cb(app_icon, scroll_menu_cb, LV_EVENT_PRESSING, nullptr);
        lv_obj_add_event_cb(app_icon, load_cb, LV_EVENT_SHORT_CLICKED, nullptr);
    }
    lv_obj_add_event_cb(_menu_disp, scroll_menu_cb, LV_EVENT_PRESSING, nullptr);
}

void App_Menu_hide(void)
{
}

void App_init(lv_obj_t *tv, lv_obj_t *screen)
{
    _tv = tv;
    _app_disp = screen;
    menu_group = lv_group_create();
    app_group = lv_group_create();

    lv_group_set_default(menu_group);

    lv_obj_add_style(_app_disp, &Initial_screen_style, 0);
    App_Menu_create();
}
void App_loop()
{
    if (_app_is_running == true)
    {
        App[_app_running_index]->loop(_app_disp, nullptr);
    }
}
void load_app(uint8_t index)
{
    exit_app();
    _app_running_index = index;
    lv_obj_add_style(_app_disp, &Initial_screen_style, 0);
    lv_group_set_default(app_group);
    App[_app_running_index]->init(_app_disp);
    lv_group_focus_obj(lv_obj_get_child(_app_disp, 0));
    lv_obj_set_tile(_tv, _app_disp, LV_ANIM_ON);
    _app_is_running = true;
}
void exit_app()
{
    _app_is_running = false;
    lv_obj_clean(_app_disp);
    lv_obj_add_style(_app_disp, &Initial_screen_style, 0);
    lv_group_set_default(menu_group);
}

bool register_app(App_item_t *app)
{
    if (App_quantity > MAX_REGISTERED_APP)
        return false;

    App[App_quantity] = app;
    App_quantity++;
    return true;
}
