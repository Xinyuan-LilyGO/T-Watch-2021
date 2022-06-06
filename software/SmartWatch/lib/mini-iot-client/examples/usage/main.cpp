#include <Arduino.h>

#include "config.h"  // create this in include/ (and add it to .gitignore)

#include "mini-iot-client.h"

MiniIotClient miniIot(HOSTNAME, MINI_IOT_SERVER, WIFI_SSID, WIFI_PASS);

void setup() {
  Serial.begin(115200);
  // miniIot.setDebugStream(&Serial);

  miniIot.connectToWifi();

  /* write a file */
  miniIot.save("status.txt", "it works");
  // miniIot.saveWithTimestamp("status.txt", "it works");

  // miniIot.disableWifi(); // turn it back off again
}

void loop() {
  // check if connected to wifi, if not it calls connectToWifi()
  miniIot.checkWifi();

  /* Write lines to a file: */
  // miniIot.append("status.csv", "running");
  miniIot.appendWithTimestamp("status.csv", "running");

  delay(5000);
}