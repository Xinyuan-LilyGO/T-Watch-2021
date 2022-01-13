#include <Arduino.h>
#include <TWatch_hal.h>

TWatchClass *twatch = nullptr;
void setup()
{
    twatch = TWatchClass::getWatch();
    twatch->HAL_Init();

    Serial.begin(115200);
    twatch->Power_Init();

    twatch->Botton_BindEvent(TWATCH_BTN_1, TWatchClass::Click, []
                             { Serial.println("BTN1 Click"); });

    twatch->Botton_BindEvent(TWATCH_BTN_2, TWatchClass::Click, []
                             { Serial.println("BTN2 Click"); });

    twatch->Botton_BindEvent(TWATCH_BTN_3, TWatchClass::Click, []
                             { Serial.println("BTN3 Click"); });
}

void loop()
{
    // put your main code here, to run repeatedly:
    twatch->HAL_Update();
}