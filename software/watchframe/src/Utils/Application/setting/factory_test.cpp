#include "factory_test.h"
#include "../../Utils.h"
#include "../../../PageManager/PageManager.h"

static lv_obj_t *bat_label;
static TWatchClass *ttgo;
static lv_obj_t *heap_table;
const unit_t unit_comparison_table[4] = {
    {CTP_SLAVER_ADDR, "CST816 Touch"},
    {BMA4_I2C_ADDR_PRIMARY, "BMA423 Motion"},
    {PCF8563_SLAVE_ADDRESS, "PCF8563 RTC"},
    {0x0D, "QMC5883 MAG"},
};

static lv_obj_t *create_btn_with_label(lv_obj_t *parent, char *text)
{
    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_set_size(btn, 30, 30);

    lv_obj_t *label = lv_label_create(btn);
    lv_obj_center(label);
    lv_label_set_text(label, text);
    return btn;
}

static void refresh_unit_event_cb(lv_event_t *e)
{
    lv_obj_t *instance = (lv_obj_t *)lv_event_get_target(e);
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *unit_table = (lv_obj_t *)lv_event_get_user_data(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_clean(unit_table);
        uint8_t count = 0;
        uint8_t list[10] = {0};
        for (uint8_t i = 1; i < 127; i++)
        {
            Wire.beginTransmission(i);
            if (Wire.endTransmission() == 0)
            {
                list[count] = i;
                count++;
            }
        }

        for (uint8_t i = 0; i < count; i++)
        {
            char buf[10] = {0};
            sprintf(buf, "0x%02X", list[i]);
            lv_table_set_cell_value(unit_table, i + 1, 0, buf);

            for (uint8_t j = 0; j < 4; j++)
            {
                if (unit_comparison_table[j].hex == list[i])
                {
                    lv_table_set_cell_value(unit_table, i + 1, 1, unit_comparison_table[j].name);
                    break;
                }
                else
                    lv_table_set_cell_value(unit_table, i + 1, 1, "Unknown");
            }
            // lv_list_add_btn(unit_table, NULL, buf);
        }
    }
}

void factory_page(lv_obj_t *obj)
{
    ttgo = TWatchClass::getWatch();
    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(obj, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

    lv_obj_t *text = lv_label_create(obj);
    lv_label_set_text(text, "Bat Volt:");

    bat_label = lv_label_create(obj);
    lv_label_set_text(bat_label, "0");
    lv_obj_set_style_text_color(bat_label, lv_palette_main(LV_PALETTE_ORANGE), 0);

    text = lv_label_create(obj);
    lv_label_set_text(text, "Scan unit");

    lv_obj_t *btn = create_btn_with_label(obj, LV_SYMBOL_REFRESH);

    lv_obj_t *unit_table = lv_table_create(obj);
    lv_obj_set_size(unit_table, LV_PCT(100), LV_PCT(100));
    lv_table_set_col_width(unit_table, 0, 70);
    lv_table_set_col_width(unit_table, 1, 150);
    lv_table_set_cell_value(unit_table, 0, 0, "HEX");
    lv_table_set_cell_value(unit_table, 0, 1, "Name");

    lv_obj_add_event_cb(btn, refresh_unit_event_cb, LV_EVENT_CLICKED, unit_table);

    heap_table = lv_table_create(obj);
    lv_obj_set_size(heap_table, LV_PCT(100), LV_PCT(100));
    lv_table_set_col_width(heap_table, 0, 70);
    lv_table_set_col_width(heap_table, 1, 150);
    lv_table_set_cell_value(heap_table, 0, 0, "heap");
    lv_table_set_cell_value(heap_table, 0, 1, "kb");

    lv_table_set_cell_value(heap_table, 1, 0, "Total heap:");
    lv_table_set_cell_value(heap_table, 2, 0, "Free heap:");
    lv_table_set_cell_value(heap_table, 3, 0, "Max Alloc Heap:");
    lv_table_set_cell_value(heap_table, 4, 0, "Total PSRAM:");
    lv_table_set_cell_value(heap_table, 5, 0, "Free PSRAM:");

    lv_table_set_cell_value_fmt(heap_table, 1, 1, "%d", ESP.getHeapSize());
    lv_table_set_cell_value_fmt(heap_table, 2, 1, "%d", ESP.getFreeHeap());
    lv_table_set_cell_value_fmt(heap_table, 3, 1, "%d", ESP.getMaxAllocHeap());
    lv_table_set_cell_value_fmt(heap_table, 4, 1, "%d", ESP.getPsramSize());
    lv_table_set_cell_value_fmt(heap_table, 5, 1, "%d", ESP.getFreePsram());
}

void factory_loop(void)
{
    static uint32_t Millis;
    if (millis() - Millis > 1000)
    {
        lv_label_set_text_fmt(bat_label, "%.0fmv", ttgo->Get_Power_Volt());
        lv_table_set_cell_value_fmt(heap_table, 1, 1, "%d", ESP.getHeapSize());
        lv_table_set_cell_value_fmt(heap_table, 2, 1, "%d", ESP.getFreeHeap());
        lv_table_set_cell_value_fmt(heap_table, 3, 1, "%d", ESP.getMaxAllocHeap());
        lv_table_set_cell_value_fmt(heap_table, 4, 1, "%d", ESP.getPsramSize());
        lv_table_set_cell_value_fmt(heap_table, 5, 1, "%d", ESP.getFreePsram());
        Millis = millis();
    }
}