#include "weather.h"
#include "HTTPClient.h"
#include <ArduinoJson.h>

#define USE_CITY_CODE

static String req;
// OpenWeather API Details, replace x's with your API key
static const char *api_key = "e155933b727fea54ed69c8000dec21be"; // Obtain this from your OpenWeather account
// https://api.openweathermap.org/data/2.5/weather?   &appid=

// Set both your longitude and latitude to at least 4 decimal places
#if defined(USE_CITY_CODE)
static String city = "shenzhen";
#else
static String latitude = "22.638397";  // 90.0000 to -90.0000 negative for Southern hemisphere
static String longitude = "114.09116"; // 180.000 to -180.000 negative for West
#endif

static const char *units = "metric"; // or "imperial"
static const char *language = "en";  // See notes tab

static bool is_update = false;
static String weather_main;
static float weather_temp;
static SemaphoreHandle_t xSemaphore = NULL;

void weather_init()
{
    if (xSemaphore == NULL)
        xSemaphore = xSemaphoreCreateMutex();
    // doc = new DynamicJsonDocument(1024);
    // http_client = new HTTPClient;https://api.openweathermap.org/data/2.5/weather?q=shenzhen&appid=e155933b727fea54ed69c8000dec21be&units=metric
    req = "https://api.openweathermap.org/data/2.5/weather?";
#if defined(USE_CITY_CODE)
    req += "q=";
    req += city;
#else
    req += "lat=";
    req += latitude;
    req += "&lon=";
    req += longitude;
#endif
    req += "&appid=";
    req += api_key;

    req += "&units=";
    req += units;
}

void core_0_weather_updata_task(void *param)
{
    StaticJsonDocument<1024> doc;
    xSemaphoreTake(xSemaphore, portMAX_DELAY);
    while (1)
    {
        HTTPClient http;
        Serial.println(req);
        if (http.begin(req))
        // if (http.begin("https://api.openweathermap.org/data/2.5/weather?q=shenzhen&appid=e155933b727fea54ed69c8000dec21be&units=metric"))
        {
            Serial.println("HTTPclient setUp done!");
        }
        int httpCode = http.GET();
        if (httpCode > 0)
        {
            Serial.println(__func__);
            String payload = http.getString();
            Serial.println(payload);

            DeserializationError error = deserializeJson(doc, payload);
            if (error)
            {
                Serial.print(F("deserializeJson() failed: "));
                Serial.println(error.f_str());
            }
            else
            {
                is_update = true;
                String res = doc[String("weather")][0][String("main")];
                weather_main = res;
                weather_temp = doc[String("main")][String("temp")];
            }
            http.end();
            xSemaphoreGive(xSemaphore);
            vTaskDelete(NULL);
        }
        else
        {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        delay(5000);
    }
    xSemaphoreGive(xSemaphore);
    vTaskDelete(NULL);
}

void weather_update()
{
    BaseType_t res = xTaskCreatePinnedToCore(core_0_weather_updata_task, "core_0_weather_updata_task", 1024 * 10, NULL, 2, NULL, 0);
    if (res != pdPASS)
    {
        Serial.println("Task creation failure");
    }
}

bool weather_is_updated()
{
    if (is_update)
    {
        is_update = false;
        return true;
    }
    else
        return false;
}
float weather_get_temp()
{
    return weather_temp;
}
int32_t weather_get_max_temp()
{
}
String weather_get_main_condition_codes()
{
    return weather_main;
}

void weather_close()
{
    // delete doc;
}