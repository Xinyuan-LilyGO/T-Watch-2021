#include "mini-iot-client.h"

MiniIotClient::MiniIotClient(const char* clientHostName, const char* serverHostName, const char* wifiSsid,
                             const char* wifiPass) {
  this->clientHostName = clientHostName;
  this->serverHostName = serverHostName;
  this->wifiSsid = wifiSsid;
  this->wifiPass = wifiPass;
  this->wifiWaitDelay = 4000;
  this->wifiWaitRetries = 0;
  this->debugStream = NULL;
}

void MiniIotClient::connectToWifi() {
#if defined(ESP8266)
  WiFi.hostname(clientHostName);
#elif defined(ESP32)
  WiFi.setHostname(clientHostName);
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
}

void MiniIotClient::checkWifi() {
  if (debugStream != NULL) {
    debugStream->println("Checking WiFi...");
  }
  if (WiFi.status() != WL_CONNECTED) {
    connectToWifi();
  }
}

void MiniIotClient::disableWifi() {
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
}

int MiniIotClient::postData(String filename, String payload, boolean append, boolean tsprefix) {
  HTTPClient http;
  http.begin(String("http://") + serverHostName          //
             + "/files/" + clientHostName                //
             + "/" + filename                            //
             + "?append=" + (append ? "true" : "false")  //
             + "&tsprefix=" + (tsprefix ? "true" : "false"));
  http.addHeader("Content-Type", "text/plain");
  int code = http.POST(payload);
  if (debugStream != NULL) {
    http.writeToStream(debugStream);
  }
  http.end();
  return code;
}

int MiniIotClient::save(String filename, String data) { return postData(filename, data, false, false); }
int MiniIotClient::saveWithTimestamp(String filename, String data) { return postData(filename, data, false, true); }
int MiniIotClient::append(String filename, String line) { return postData(filename, line, true, false); }
int MiniIotClient::appendWithTimestamp(String filename, String line) { return postData(filename, line, true, true); }