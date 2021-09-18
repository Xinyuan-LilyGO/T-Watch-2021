#include "./XYWatch_hal.h"

#if XYWATCH_HAS_SD

static SdFat SD;
static bool SD_IsReady = false;
SPIClass _sdspi(HSPI);

static XYWatch::SD_CallbackFunction_t SD_EventCallback = nullptr;

/*
 * User provided date time callback function.
 * See SdFile::dateTimeCallback() for usage.
 */
static void SD_GetDateTime(uint16_t *date, uint16_t *time)
{
    /*     RTC_Date clock;
    clock = GetRTCTime();
    // return date using FAT_DATE macro to format fields
    *date = FAT_DATE(clock.year, clock.month, clock.day);

    // return time using FAT_TIME macro to format fields
    *time = FAT_TIME(clock.hour, clock.minute, clock.second); */
}

static bool SD_CheckDir(const char *path)
{
    bool retval = true;
    if (!SD.exists(path))
    {
        Serial.printf("SD: Auto create path \"%s\"...", path);
        retval = SD.mkdir(path);
        Serial.println(retval ? "success" : "failed");
    }
    return retval;
}

bool XYWatch::SD_Init()
{
    bool retval = true;

    pinMode(SD_CS, INPUT_PULLUP);
    if (digitalRead(SD_CS))
    {
        Serial.println("SD: CARD was not insert");
        retval = false;
    }
    _sdspi.begin(SD_CLK, SD_MISO, SD_MOSI, SD_CS);
    retval = SD.begin(SdSpiConfig(SD_CS, SHARED_SPI, SD_SCK_MHZ(20), &_sdspi));

    if (retval)
    {
        SdFile::dateTimeCallback(SD_GetDateTime);
        //SD_CheckDir(CONFIG_TRACK_RECORD_FILE_DIR_NAME);
        //SD_CheckDir(CONFIG_MAP_FILE_DIR_NAME);
        Serial.println("SD: Init success");
    }
    else
    {
        Serial.println("SD: CARD ERROR");
    }

    SD_IsReady = retval;

    return retval;
}

bool XYWatch::SD_GetReady()
{
    return SD_IsReady;
}

static void SD_Check(bool isInsert)
{
    if (isInsert)
    {
        bool ret = XYWatch::SD_Init();

        if (ret && SD_EventCallback)
        {
            SD_EventCallback(true);
        }
    }
    else
    {
        SD_IsReady = false;

        if (SD_EventCallback)
        {
            SD_EventCallback(false);
        }
    }
}

void XYWatch::SD_SetEventCallback(SD_CallbackFunction_t callback)
{
    SD_EventCallback = callback;
}

void XYWatch::SD_Update()
{
    bool isInsert = (digitalRead(SD_CS) == LOW);
    //__ValueMonitor(isInsert, SD_Check(isInsert));
}

#endif