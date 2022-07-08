#ifndef __WEATHER_H_
#define __WEATHER_H_

#include <stdio.h>
#include <stdlib.h>
#include <WString.h>

void weather_init();
void weather_update();
bool weather_is_updated();
float weather_get_temp();
String weather_get_main_condition_codes();
void weather_close();
#endif