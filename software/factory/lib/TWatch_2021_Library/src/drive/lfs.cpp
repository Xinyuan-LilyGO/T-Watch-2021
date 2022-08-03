#include "./TWatch_hal.h"

#if defined(CONFIG_TWATCH_HAS_LFS)

bool TWatchClass::lfs_init(bool formatOnFail, const char *basePath, uint8_t maxOpenFiles, const char *partitionLabel) {
  if (!_is_lfs_mounted) {
    if (!LittleFS.begin(formatOnFail, basePath, maxOpenFiles, partitionLabel)) {
      DEBUGLN("LittleFS mount failed");
      return false;
    }
    _is_lfs_mounted = true;
    DEBUGLN("LittleFS mounted successfully");
  } else {
    DEBUGLN("LittleFS has been mounted");
  }

  DEBUGF("LittleFS total space: %u kb\n", LittleFS.totalBytes() / 1024);
  DEBUGF("LittleFS used space: %u kb\n", LittleFS.usedBytes() / 1024);
  // listDir(LittleFS, "/", 3);
  return true;
}

bool TWatchClass::is_lfs_mounted() {
  return _is_lfs_mounted;
}

#endif