#ifndef OSW_APP_TOUCH_H
#define OSW_APP_TOUCH_H

#include <osw_hal.h>
#include <osw_ui.h>

#include "osw_app.h"

class OswAppTouch : public OswApp
{
public:
    OswAppTouch(void) { ui = OswUI::getInstance(); };
    void setup(OswHal *hal);
    void loop(OswHal *hal);
    void stop(OswHal *hal);
    ~OswAppTouch(){};

private:
    OswUI *ui;
    void drawTouchPad(OswHal *hal);
    void DrawingBoard(OswHal *hal);
    void Coordinates(OswHal *hal);
};

#endif