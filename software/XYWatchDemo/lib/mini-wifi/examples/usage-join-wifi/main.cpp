#include <Arduino.h>
#include "mini-wifi.h"

MiniWifi wifi("client", "<your-ssid>", "<your-password>");

#define HTTP_GET_BUF_LEN 10
char httpGetBuffer[HTTP_GET_BUF_LEN];

void setup() {
  Serial.begin(115200);
  wifi.setDebugStream(&Serial); // optional

  wifi.joinWifi(); // will connect to a wifi
}


void loop() {
  String result;

  // make sure if we are connected, if not, try to reconnect until connected
  wifi.checkWifi();

  // fetch a value from a URL
  wifi.get("http://192.168.1.111/temperature/celsius", httpGetBuffer, HTTP_GET_BUF_LEN);
  float celsius = String(httpGetBuffer).toFloat();
  
  Serial.print("Temperature is ");
  Serial.println(celsius, 2);

  delay(100);
}