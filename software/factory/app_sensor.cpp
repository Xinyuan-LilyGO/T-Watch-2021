#include "TWatch_hal.h"
#include "app_common.h"

typedef struct {
  char *name;
  uint8_t address;
} Peripherals_unit_t;

Peripherals_unit_t peri_list[] = {
    {"QMC5883L", 0x0D},
    {"CST816", 0X15},
    {"BMA423", 0X18},
    {"PCF8563", 0X51},
#if defined(TWatch2021_V2)
    {"BME280", 0x77},
    {"SD card", 0},
    {"GPS locat", 0},
    {"GPS time", 0},
    {"GPS alt", 0},
#endif
};

void timer_event_cb(lv_timer_t *timer);

void app_sensor_test(lv_event_t *e) {
  lv_obj_t *cout = (lv_obj_t *)lv_event_get_user_data(e);

  lv_obj_t *table = lv_table_create(cout);
  lv_obj_set_size(table, 240, 200);
  lv_obj_center(table);
  lv_obj_set_style_pad_all(table, 0, 0);
  lv_table_set_col_width(table, 0, 120);
  lv_table_set_col_width(table, 1, 70);
  lv_table_set_col_width(table, 2, 70);
  lv_table_set_col_width(table, 3, 500);

  app_set_table_info(table, 0, "Name", "Addr", "State");
  lv_table_set_cell_value(table, 0, 3, "Raw");
  /* battery voltage status */
  app_set_table_info(table, 1, "VOLT (mv)", "0", LV_SYMBOL_OK);
  lv_timer_t *timer = lv_timer_create(timer_event_cb, 200, table);

  /* Scan for IIC devices */
  uint8_t count = 0;
  uint8_t iic_list[10] = {0};
  for (uint8_t i = 1; i < 127; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      iic_list[count] = i;
      count++;
    }
  }
  bool state = false;
  for (uint8_t i = 0; i < sizeof(peri_list) / sizeof(Peripherals_unit_t); i++) {
    state = false;
    for (uint8_t j = 0; j < count; j++) {
      if (peri_list[i].address == iic_list[j]) {
        state = true;
        break;
      }
    }
    if (state)
      app_set_table_info(table, i + 2, peri_list[i].name, peri_list[i].address, LV_SYMBOL_OK);
    else
      app_set_table_info(table, i + 2, peri_list[i].name, peri_list[i].address, LV_SYMBOL_CLOSE);
  }
  lv_obj_set_tile(lv_obj_get_parent(cout), cout, LV_ANIM_ON);
}

void timer_event_cb(lv_timer_t *timer) {
  lv_obj_t *table = (lv_obj_t *)timer->user_data;
  if (lv_obj_is_valid(table)) {
    TWatchClass *ttgo = TWatchClass::getWatch();
    uint32_t volt = ttgo->power_get_volt();

    lv_table_set_cell_value_fmt(table, 1, 3, "%d", volt);

    char buf[50];

    sprintf(buf, "X:%d Y:%d Z:%d", ttgo->qmc5883l_getX(), ttgo->qmc5883l_getY(), ttgo->qmc5883l_getZ());
    lv_table_set_cell_value(table, 2, 3, buf);

    sprintf(buf, "X:%d Y:%d", ttgo->touch_getX(), ttgo->touch_getY());
    lv_table_set_cell_value(table, 3, 3, buf);

    sprintf(buf, "X:%.2f Y:%.2f Z:%.2f", ttgo->bma423_getX(), ttgo->bma423_getY(), ttgo->bma423_getZ());
    lv_table_set_cell_value(table, 4, 3, buf);

    RTC_Date time = ttgo->rtc_get_time();
    sprintf(buf, "%02d : %02d : %02d", time.hour, time.minute, time.second);
    lv_table_set_cell_value(table, 5, 3, buf);

#if defined(TWatch2021_V2)
    sprintf(buf, "T:%.2f P:%.2f A:%.2f H:%.2f ", ttgo->bme280_get_temperature(),
                                                 ttgo->bme280_get_pressure(),
                                                 ttgo->bme280_get_altitude(),
                                                 ttgo->bme280_get_humidity());
    lv_table_set_cell_value(table, 6, 3, buf);

    if (ttgo->sd_is_ready()) {
      sprintf(buf, "SD size:%d MB", SD.cardSize() / 1024 / 1024);
      lv_table_set_cell_value(table, 7, 3, buf);
      lv_table_set_cell_value(table, 7, 2, LV_SYMBOL_OK);
    } else {
      lv_table_set_cell_value(table, 7, 2, LV_SYMBOL_CLOSE);
      // ttgo->sd_init();
    }

    TinyGPSPlus gps = ttgo->get_gps_instance();
    if (gps.location.isValid() && gps.satellites.isUpdated()) {
      sprintf(buf, "lat:%.6f lng:%.6f sat:%d", gps.location.lat(), gps.location.lng(), gps.satellites.value());
      lv_table_set_cell_value(table, 8, 3, buf);
      lv_table_set_cell_value(table, 8, 2, LV_SYMBOL_OK);
    }
    if (gps.location.isValid()) {
      sprintf(buf, "%02d : %02d : %02d", gps.time.hour(), gps.time.minute(), gps.time.second());
      lv_table_set_cell_value(table, 9, 3, buf);
      lv_table_set_cell_value(table, 9, 2, LV_SYMBOL_OK);
    }
    if (gps.altitude.isValid()) {
      sprintf(buf, "ALT:%.3f", gps.altitude.meters());
      lv_table_set_cell_value(table, 10, 3, buf);
      lv_table_set_cell_value(table, 10, 2, LV_SYMBOL_OK);
    }
#endif

  } else {
    lv_timer_del(timer);
  }
}
