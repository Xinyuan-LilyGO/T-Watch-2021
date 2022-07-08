#include "./TWatch_hal.h"

#if defined(CONFIG_TWATCH_HAS_FFAT)

bool TWatchClass::ffat_init(bool formatOnFail, const char *basePath, uint8_t maxOpenFiles, const char *partitionLabel) {
  if (!_is_ffat_mounted) {
    if (!FFat.begin(formatOnFail, basePath, maxOpenFiles, partitionLabel)) {
      DEBUGLN("ffat mount failed");
      return false;
    }
    _is_ffat_mounted = true;
    DEBUGLN("ffat mounted successfully");
  } else {
    DEBUGLN("ffat has been mounted");
  }

  DEBUGF("ffat total space: %u kb\n", FFat.totalBytes() / 1024);
  DEBUGF("ffat free space: %u kb\n", FFat.freeBytes() / 1024);

  return true;
}

bool TWatchClass::is_ffat_mounted() {
  return _is_ffat_mounted;
}

#endif