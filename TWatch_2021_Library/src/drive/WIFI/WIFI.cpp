#include "./TWatch_hal.h"

#if defined(TWatch_HAL_WIFI)

void TWatchClass::WIFI_Init(void)
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
}

uint8_t TWatchClass::WIFI_Scan(void)
{
    int n = WiFi.scanNetworks();
    return n;
}

bool TWatchClass::WIFI_Connect(String ssid, String password, uint32_t waittime)
{
    uint32_t count = 0;
    WiFi.begin(ssid.c_str(), password.c_str());
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(waittime / 10);
        count += waittime / 10;
        Serial.print(".");
        if (count > waittime)
            return false;
    }
    return true;
}

bool TWatchClass::is_WIFI_Connected(void)
{
    return WiFi.isConnected();
}

void TWatchClass::WIFI_Stop(void)
{
    WiFi.disconnect();
}

WiFiClass TWatchClass::Get_WIFI(void)
{
    return WiFi;
}

#endif