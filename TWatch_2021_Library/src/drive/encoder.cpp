#include "./TWatch_hal.h"
#if defined(CONFIG_TWATCH_HAS_ENCODER)

void TWatchClass::encoder_init() {
  encoder = new Encoder(TWATCH_ENCODER_A, TWATCH_ENCODER_B);
  _lastPosition = encoder->readAndReset();
}

int32_t TWatchClass::encoder_get_diff() {
  int32_t new_position = encoder->read();
  int8_t diff = 0;
  if (abs(_lastPosition - new_position) > 3) {
    if (_lastPosition > new_position)
      diff = 1;
    else
      diff = -1;

    _lastPosition = new_position;
    DEBUGLN(diff);
    return diff;
  } else
    return 0;
}

#endif