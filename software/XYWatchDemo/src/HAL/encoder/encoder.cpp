#include "./XYWatch_hal.h"
#if XYWATCH_HAS_ENCODER
#define ROTARY_ENCODER_STEPS 4
AiEsp32RotaryEncoder Encoder = AiEsp32RotaryEncoder(ENCODER_A, ENCODER_B, ENCODER_C, -1, ROTARY_ENCODER_STEPS);
static uint8_t BottonState = false;

void XYWatch::Encoder_Init()
{
    Encoder.begin();
    Encoder.setup(
        []
        { Encoder.readEncoder_ISR(); },
        []
        { BottonState = true; });
    Encoder.disableAcceleration();
}

int32_t XYWatch::Encoder_GetDiff()
{
    int32_t diff = Encoder.encoderChanged();
    return diff;
}

bool XYWatch::Encoder_GetIsPush()
{
    bool Botton = BottonState;
    BottonState = false;
    return Botton;
}
#endif