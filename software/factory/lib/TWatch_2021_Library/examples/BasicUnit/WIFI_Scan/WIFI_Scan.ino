#include "WiFi.h"
#include <Arduino.h>
#include <TWatch_hal.h>
//"TWatch_config.h" needs to be configured in the library for the first time
// This routine needs to annotate the LVGL GUI

TWatchClass *twatch = nullptr;
TFT_eSPI *tft = nullptr;

char buf[128];

void setup() {
  twatch = TWatchClass::getWatch();
  tft = twatch->tft_get_instance();

  Serial.begin(115200);
  twatch->motor_shake(2, 50);

  tft->fillScreen(TFT_BLACK);
  twatch->backlight_set_value(255);

  Serial.println("wifi Scan Demo ");

  twatch->hal_auto_update(true, 0);

  tft->setTextFont(2);
  tft->setTextColor(TFT_WHITE, TFT_BLACK);
  tft->drawString("wifi Scan Test", 62, 90);
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int y = 0;
  tft->fillScreen(TFT_BLACK);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("scan start");
  tft->setCursor(80, y, 2);
  tft->println("scan start");
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  y += 18;
  tft->setCursor(80, y, 2);
  tft->println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
    y += 18;
    tft->setCursor(80, y, 2);
    tft->println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    y += 18;
    tft->setCursor(80, y, 2);
    tft->printf("%d networks found", n);
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      y += 18;
      tft->setCursor(40, y, 2);
      tft->printf("%d:%s(%d)", i + 1, WiFi.SSID(i), WiFi.RSSI(i));
      delay(10);
    }
  }
  Serial.println("");
  // Wait a bit before scanning again
  delay(10000);
}