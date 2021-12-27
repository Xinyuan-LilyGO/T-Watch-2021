#ifndef MINI_WIFI_H
#define MINI_WIFI_H

#include <Arduino.h>

class MiniWifi {
 private:
  const char* hostName;
  const char* wifiSsid;
  const char* wifiPass;
  uint16_t wifiWaitDelay;
  Stream* debugStream;
  boolean joinedWifi;
  uint8_t wifiWaitRetries;
  boolean _isEnabled;

 public:
  MiniWifi(const char* hostName, const char* wifiSsid, const char* wifiPass);

  void setWifiWaitDelay(uint16_t delay);
  void setDebugStream(Stream* stream);
  void setWifiWaitRetries(uint8_t retries);

  void disableWiFi();
  bool isEnabled();
  void joinWifi();

  void checkWifi();
  bool isConnected();
  int32_t getSignalStrength();
  uint8_t getSignalQuality();

  IPAddress getIp();

  void createWifi();

  void begin();
  int get(const char* url, char* resultBuf, int resultBufLen);
  // TODO: post
};

#endif
