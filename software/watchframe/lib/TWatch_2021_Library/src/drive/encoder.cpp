#include "./TWatch_hal.h"
#if defined(TWatch_HAL_ENCODER)
#define ROTARY_ENCODER_STEPS 4

void TWatchClass::Encoder_Init()
{
    Encoder = new AiEsp32RotaryEncoder(ENCODER_A, ENCODER_B, ENCODER_C, -1, ROTARY_ENCODER_STEPS);
    Encoder->begin();
    Encoder->setup(
        []
        { Encoder->readEncoder_ISR(); },
        []
        { BottonState = true; });
    Encoder->disableAcceleration();
}

int32_t TWatchClass::Encoder_GetDiff()
{
    int32_t diff = Encoder->encoderChanged();
    return diff;
}

bool TWatchClass::Encoder_GetIsPush()
{
    bool Botton = BottonState;
    BottonState = false;
    return Botton;
}
#endif