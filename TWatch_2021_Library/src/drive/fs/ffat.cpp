#include "../../TWatch_hal.h"

#if defined(TWatch_HAS_FFAT)

bool TWatchClass::FFat_Init()
{
    if (!_is_ffat_mounted)
    {
        if (!FFat.begin())
        {
            DEBUGLN("ffat mount failed");
            return false;
        }
        _is_ffat_mounted = true;
        DEBUGLN("ffat mounted successfully");
    }
    else
    {
        DEBUGLN("ffat has been mounted");
    }

    DEBUGF("ffat total space: %u kb\n", FFat.totalBytes() / 1024);
    DEBUGF("ffat free space: %u kb\n", FFat.freeBytes() / 1024);

    return true;
}

bool TWatchClass::is_FFat_Mounted()
{
    return _is_ffat_mounted;
}

bool TWatchClass::FFat_format(bool mount)
{
    bool res = FFat.format();
    if (!res)
    {
        return false;
    }
    if (mount)
    {
        return FFat_Init();
    }
    return true;
}

#endif