#include "app_wifi.h"
#include "WiFi.h"
#include "app_common.h"

void app_refresh_wifi(lv_event_t *e);
void app_wait_wifi_scan(lv_timer_t *t);
void app_connect_wifi(lv_event_t *e);
static lv_obj_t *label;

void app_wifi_func(lv_event_t *e) {
  lv_obj_t *cout = (lv_obj_t *)lv_event_get_user_data(e);

  label = lv_label_create(cout);
  lv_obj_set_width(label, 200);
  lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 50);
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
  lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
  lv_label_set_text(label, "  ");

  lv_obj_t *table = lv_table_create(cout);
  lv_obj_set_size(table, 240, 170);
  lv_obj_align(table, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_set_style_pad_all(table, 0, 0);
  lv_table_set_col_width(table, 0, 70);
  lv_table_set_col_width(table, 1, 150);
  lv_table_set_col_width(table, 2, 70);
  app_set_table_info(table, 0, "Num", "SSID", "rssi");

  lv_obj_t *btn = app_create_btn(cout, LV_ALIGN_TOP_MID, 0, 5, LV_SYMBOL_REFRESH);
  lv_obj_set_size(btn, 60, 40);
  lv_obj_add_event_cb(btn, app_refresh_wifi, LV_EVENT_CLICKED, table);

  lv_obj_set_tile(lv_obj_get_parent(cout), cout, LV_ANIM_ON);
}

void app_refresh_wifi(lv_event_t *e) {
  lv_obj_t *table = (lv_obj_t *)lv_event_get_user_data(e);

  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  delay(100);

  int n = WiFi.scanNetworks();
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");

      app_set_table_info(table, i + 1, i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
      delay(10);
    }
  }
  Serial.println("");
  lv_obj_add_event_cb(table, app_connect_wifi, LV_EVENT_VALUE_CHANGED, NULL);
}

void app_connect_wifi(lv_event_t *e) {
  lv_obj_t *obj = lv_event_get_target(e);
  uint16_t col, row;

  lv_table_get_selected_cell(obj, &row, &col);
  if (row != 0) {
    const char *ssid = lv_table_get_cell_value(obj, row, 1);
    Serial.println(ssid);
    if (!strcmp(FACTORY_SSID, ssid)) {
      lv_label_set_text(label, "connecting " FACTORY_SSID);
      WiFi.begin(FACTORY_SSID, FACTORY_PASS);
      lv_timer_t *timer = lv_timer_create(app_wait_wifi_scan, 500, NULL);
    }
  }
}

void app_wait_wifi_scan(lv_timer_t *t) {
  if (WiFi.status() != WL_CONNECTED) {
    lv_label_set_text(label, "Waiting for WiFi to connect");
  } else {
    lv_label_set_text(label, "WiFi connection successful");
    lv_timer_del(t);
  }
}