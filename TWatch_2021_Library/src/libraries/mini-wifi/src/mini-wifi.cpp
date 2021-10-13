
#include "mini-wifi.h"

#if defined(ESP8266)
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <HTTPClient.h>
#include <WiFi.h>
#else
#error only esp8266 and esp32 are supported
#endif

#define FPM_SLEEP_MAX_TIME 0xFFFFFFF

MiniWifi::MiniWifi(const char *hostName, const char *wifiSsid, const char *wifiPass) {
  this->hostName = hostName;
  this->wifiSsid = wifiSsid;
  this->wifiPass = wifiPass;
  this->wifiWaitDelay = 6000;
  this->wifiWaitRetries = 2;
  this->debugStream = NULL;
  this->joinedWifi = false;
}
void MiniWifi::setWifiWaitRetries(uint8_t retries) { wifiWaitRetries = retries; }

void MiniWifi::disableWiFi() {
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  joinedWifi = false;
  _isEnabled = false;
}

void MiniWifi::joinWifi() {
  joinedWifi = true;
  _isEnabled = true;
#if defined(ESP8266)
  WiFi.hostname(this->hostName);
#elif defined(ESP32)
  WiFi.setHostname(this->hostName);
#endif
  WiFi.mode(WIFI_STA);

  uint16_t retries = 0;

  do {
    if (debugStream != NULL) {
      debugStream->print("Connecting to WiFi ");
      debugStream->print(wifiSsid);
      debugStream->println("...");
    }
    WiFi.begin(wifiSsid, wifiPass);
    // below waits at most wifiWaitDelay millis.
    unsigned long now = millis();
    while (now + wifiWaitDelay > millis()) {
      delay(50);
      if (WiFi.status() == WL_CONNECTED) {
        break;
      }
    }
    retries++;
  } while (WiFi.status() != WL_CONNECTED && retries <= wifiWaitRetries);

  if (debugStream != NULL) {
    if (WiFi.status() == WL_CONNECTED) {
      debugStream->print("Connected to WiFi ");
      debugStream->print("IP: ");
      debugStream->println(WiFi.localIP().toString());
    } else {
      debugStream->print("Connecting to WiFi failed");
    }
  }
}

IPAddress MiniWifi::getIp() {
  return WiFi.localIP();
}

void MiniWifi::checkWifi() {
  if (!joinedWifi) {
    joinWifi();
    return;
  }

  if (WiFi.status() != WL_CONNECTED) {
    joinWifi();
  }
  yield();
}

bool MiniWifi::isEnabled() { return _isEnabled; }

bool MiniWifi::isConnected() { return WiFi.status() == WL_CONNECTED; }
int32_t MiniWifi::getSignalStrength() { return WiFi.RSSI(); }
uint8_t MiniWifi::getSignalQuality() {
  int32_t rssi = getSignalStrength();
  uint8_t quality = 0;
  if (rssi < -100) {
    quality = 0;
  } else if (rssi > -50) {
    quality = 100;
  } else {
    quality = 2 * (rssi + 100);
  }
  return quality;
}

void MiniWifi::createWifi() {
  _isEnabled = true;
  IPAddress Ip(192, 168, 1, 1);
  IPAddress NMask(255, 255, 255, 0);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(Ip, Ip, NMask);
  WiFi.softAP(wifiSsid, wifiPass);
  delay(wifiWaitDelay);

  if (debugStream != NULL) {
    debugStream->println("Started WIFI");
    debugStream->println(WiFi.softAPIP());
  }
}

void MiniWifi::setWifiWaitDelay(uint16_t delay) { wifiWaitDelay = delay; }
void MiniWifi::setDebugStream(Stream *stream) { debugStream = stream; }

int MiniWifi::get(const char *url, char *resultBuf, int resultBufLen) {
  int bytesRead = 0;

  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  delay(50);

  if (debugStream != NULL) {
    debugStream->print("GET ");
    debugStream->print(url);
    debugStream->print(" ");
    debugStream->print(http.getSize());
    debugStream->print(" ");
  }

  if (http.getSize()) {
    while (!http.getStream().available()) {
      // wait until data is here
      yield();
    }
  }

  if (httpCode > 0) {
    // note: http.getString() crashes when calling http.end(),
    // so I had to implement some stream reading manually.

    char buffer[1];
    while (http.getStream().available() && bytesRead < resultBufLen - 1) {
      http.getStream().readBytes(buffer, 1);
      resultBuf[bytesRead] = buffer[0];
      bytesRead++;
    }
    resultBuf[bytesRead] = 0;

    if (debugStream != NULL) {
      debugStream->print("\"");
      debugStream->print(resultBuf);
      debugStream->println("\"");
    }
  }

  http.end();
  return bytesRead;
}
