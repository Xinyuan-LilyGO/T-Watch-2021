#ifndef MINIIOTCLIENT_H
#define MINIIOTCLIENT_H

#include <Arduino.h>
#if defined(ESP8266)
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <HTTPClient.h>
#include <WiFi.h>
#else
#error only esp8266 and esp32 are supported
#endif

class MiniIotClient {
 private:
  Stream* debugStream;
  const char* clientHostName;
  const char* serverHostName;
  const char* wifiSsid;
  const char* wifiPass;
  uint16_t wifiWaitDelay;
  uint8_t wifiWaitRetries;

  int postData(String filename, String payload, boolean append, boolean tsprefix);

 public:
  MiniIotClient(const char* clientHostName, const char* serverHostName, const char* wifiSsid, const char* wifiPass);
  void setWifiWaitDelay(uint16_t delay) { wifiWaitDelay = delay; }
  void setWifiWaitRetries(uint8_t retries) { wifiWaitRetries = retries; }
  void setDebugStream(Stream* stream) { debugStream = stream; }


  void connectToWifi();
  void checkWifi();
  void disableWifi();

  int save(String filename, String data);
  int saveWithTimestamp(String filename, String data);

  int append(String filename, String line);
  int appendWithTimestamp(String filename, String line);
};

#endif