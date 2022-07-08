#include "app_ble.h"
#include "NimBLEDevice.h"
#include "app_common.h"

static int scanTime = 5; // In seconds
static NimBLEScan *pBLEScan;
static uint32_t n = 0;
static lv_obj_t *table;
static lv_obj_t *label;

void app_refresh_ble(lv_event_t *e);
void app_table_add_ble_row(uint32_t n, const char *name, int rssi, const char *mac);

class MyAdvertisedDeviceCallbacks : public NimBLEAdvertisedDeviceCallbacks {
  void onResult(NimBLEAdvertisedDevice *advertisedDevice) {
    Serial.printf("Advertised Device: %s \n", advertisedDevice->toString().c_str());
    app_table_add_ble_row(n + 1,
                          advertisedDevice->getName().c_str(),
                          advertisedDevice->getRSSI(),
                          advertisedDevice->getAddress().toString().c_str());
    n++;
  }
};

void app_bluetooth_scan_func(lv_event_t *e) {
  lv_obj_t *cout = (lv_obj_t *)lv_event_get_user_data(e);

  label = lv_label_create(cout);
  lv_obj_set_width(label, 200);
  lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 50);
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
  lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
  lv_label_set_text(label, "  ");

  table = lv_table_create(cout);
  lv_obj_set_size(table, 240, 170);
  lv_obj_align(table, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_table_set_col_width(table, 0, 70);
  lv_table_set_col_width(table, 1, 100);
  lv_table_set_col_width(table, 2, 70);
  lv_table_set_col_width(table, 3, 200);

  lv_table_set_cell_value(table, 0, 0, "Num");
  lv_table_set_cell_value(table, 0, 1, "Name");
  lv_table_set_cell_value(table, 0, 2, "rssi");
  lv_table_set_cell_value(table, 0, 3, "Mac");

  lv_obj_t *btn = app_create_btn(cout, LV_ALIGN_TOP_MID, 0, 5, LV_SYMBOL_REFRESH);
  lv_obj_set_size(btn, 60, 40);
  lv_obj_add_event_cb(btn, app_refresh_ble, LV_EVENT_CLICKED, table);

  NimBLEDevice::setScanFilterMode(CONFIG_BTDM_SCAN_DUPL_TYPE_DEVICE);
  NimBLEDevice::setScanDuplicateCacheSize(200);
  NimBLEDevice::init("");

  pBLEScan = NimBLEDevice::getScan(); // create new scan
  // Set the callback for when devices are discovered, no duplicates.
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks(), false);
  pBLEScan->setActiveScan(true); // Set active scanning, this will get more data from the advertiser.
  pBLEScan->setInterval(97);     // How often the scan occurs / switches channels; in milliseconds,
  pBLEScan->setWindow(37);       // How long to scan during the interval; in milliseconds.
  pBLEScan->setMaxResults(0);    // do not store the scan results, use callback only.

  lv_obj_set_tile(lv_obj_get_parent(cout), cout, LV_ANIM_ON);
}

void app_refresh_ble(lv_event_t *e) {

  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  lv_label_set_text_fmt(label, "Devices found: %d ", n);
  pBLEScan->clearResults(); // delete results fromBLEScan buffer to release memory
  n = 0;
}

void app_table_add_ble_row(uint32_t n, const char *name, int rssi, const char *mac) {
  lv_table_set_cell_value_fmt(table, n, 0, "%d", n);
  lv_table_set_cell_value(table, n, 1, name);
  lv_table_set_cell_value_fmt(table, n, 2, "%d", rssi);
  lv_table_set_cell_value(table, n, 3, mac);
}