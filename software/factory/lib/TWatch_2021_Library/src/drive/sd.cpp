#include "./TWatch_hal.h"

#if defined(CONFIG_TWATCH_HAS_SD)

bool TWatchClass::sd_check_dir(const char *path, bool create) {
  if (!SD.exists(path)) {
    if (create)
      SD.mkdir(path);
    else
      return false;
  }
  return true;
}

bool TWatchClass::sd_init() {
  bool retval = true;
  _sd_spi.begin(TWATCH_SD_CLK, TWATCH_SD_MISO, TWATCH_SD_MOSI, TWATCH_SD_CS);

  retval = SD.begin(TWATCH_SD_CS, _sd_spi);
  if (retval) {
    uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE) {
      DEBUGLN("No SD card attached");
      return false;
    }
    Serial.print("SD Card Type: ");
    if (cardType == CARD_MMC) {
      DEBUGLN("MMC");
    } else if (cardType == CARD_SD) {
      DEBUGLN("SDSC");
    } else if (cardType == CARD_SDHC) {
      DEBUGLN("SDHC");
    } else {
      DEBUGLN("UNKNOWN");
    }
    DEBUGF("sd card size:%d MB", SD.cardSize() / 1024 / 1024);
    DEBUGLN();
  } else {
  }

  return retval;
}

bool TWatchClass::sd_is_ready() {
  if (SD.numSectors() > 0)
    return true;
  else
    return false;
}

fs::SDFS TWatchClass::sd_get_instance() {
  return SD;
}

#endif