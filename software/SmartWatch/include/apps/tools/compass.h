#ifndef OSW_APP_COMPASS_H
#define OSW_APP_COMPASS_H

#include <osw_hal.h>
#include <osw_ui.h>

#include "osw_app.h"

class OswAppCompass : public OswApp {
 public:
  OswAppCompass(void) { ui = OswUI::getInstance(); };
  void setup(OswHal* hal);
  void loop(OswHal* hal);
  void stop(OswHal* hal);
  ~OswAppCompass(){};

 private:
  OswUI* ui;
  void calibration(OswHal *hal);
  void drawCompass(OswHal* hal);
  void drawPointer(OswHal* hal, const int Azimuth);
  
};

#endif