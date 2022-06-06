#ifndef OSW_APP_MOTORDEBUG_H
#define OSW_APP_MOTORDEBUG_H

#include <osw_hal.h>

#include "osw_app.h"

class OswAppMotorDebug : public OswApp {
 public:
  OswAppMotorDebug(void){};
  void setup(OswHal* hal);
  void loop(OswHal* hal);
  void stop(OswHal* hal);
  ~OswAppMotorDebug(){};

 private:
 
};

#endif
