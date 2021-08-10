#ifndef OSW_APP_GETACCLERATIONXYZ_H
#define OSW_APP_GETACCLERATIONXYZ_H

#include <osw_hal.h>
#include <osw_ui.h>

#include "osw_app.h"

class OswAppgetAcclerationXYZ : public OswApp {
 public:
  OswAppgetAcclerationXYZ(void) { ui = OswUI::getInstance(); };
  void setup(OswHal* hal);
  void loop(OswHal* hal);
  void stop(OswHal* hal);
  ~OswAppgetAcclerationXYZ(){};

 private:
  OswUI* ui;
};

#endif
