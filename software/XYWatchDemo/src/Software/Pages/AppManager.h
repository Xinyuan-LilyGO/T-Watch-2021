#ifndef __APPMANAGER_H__
#define __APPMANAGER_H__

#include "XYWatch_hal.h"
#include "Theme/Theme.h"
#include "Style/Style.h"
#include "DigitalClock/DigitalClock.h"
#include "ClockApp/SimpleClock.h"
#include "SpacerClock/Spacer.h"
#include "Compass/Compass.h"
#include "ConsolePage/Console.h"
#include "Setting/Setting.h"

#define MALLOC malloc
#define FREE free
//#define IS_PAGE(page) ((page) < (page_manager.max_page))

namespace XYWatchApp
{
    void AppInit();
    void Dial_Frame(void);
    void APP_Frame(void);
}

#endif