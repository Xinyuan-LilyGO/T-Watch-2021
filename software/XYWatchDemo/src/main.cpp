#include "XYWatch_hal.h"

void setup()
{
   pinMode(PWR_ON, OUTPUT);
   digitalWrite(PWR_ON, HIGH);

   Serial.begin(115200); /* prepare for possible serial debug */
   Serial.println("Hello T-Watch");
   XYWatch::HAL_Init();

   XYWatchApp::AppInit();
   Serial.println("XYWatch Setup done");
}

void loop()
{
   XYWatch::HAL_Update();
   lv_timer_handler();
}