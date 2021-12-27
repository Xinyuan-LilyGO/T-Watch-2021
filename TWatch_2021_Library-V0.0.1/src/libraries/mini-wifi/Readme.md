# mini-wifi

This is a utility library to make the use of WiFi easier for the ESP8266.

```c++
#include "mini-wifi.h"

MiniWifi wifi("client", "<your-ssid>", "<your-password>");

void setup() {
    // will connect to a wifi, and retry connecting every 4s (default)
    wifi.joinWifi();

    // or AP mode
    wifi.createWifi();
}

void loop() {
    // will check you are still connected, if not it will reconenct
    wifi.checkWifi();
}
```

Further helpers:

```c++
wifi.getSignalStrength(); // RSSI dBm
wifi.getSignalQuality(); // signal quality in 0 - 100 %

wifi.get(url, char* resultBuf, int resultBufLen); // oneliner to fetch HTTP GET data to a buffer
```