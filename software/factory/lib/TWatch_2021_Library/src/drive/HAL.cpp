#include "./TWatch_hal.h"

TWatchClass *TWatchClass::_ttgo = nullptr;
EventGroupHandle_t TWatchClass::_Hal_IRQ_event = nullptr;

#if defined(CONFIG_TWATCH_HAS_BUTTON)
EventGroupHandle_t TWatchClass::_hal_button_event = nullptr;
#endif

void TWatchClass::hal_init(void) {
// #if defined(CONFIG_TWATCH_HAS_DISPLAY) && (TWatch_APP_LVGL == 1)
  // Move the malloc process to Init() to make sure that the largest heap can be used for this buffer.
  // lv_disp_buf_p = static_cast<lv_color_t *>(malloc(DISP_BUF_SIZE * sizeof(lv_color_t)));
  // if (lv_disp_buf_p == nullptr)
  //     LV_LOG_WARN("lv_port_disp_init malloc failed!\n");
// #endif

  DEBUGF("flash size : %d kb\r\n", ESP.getFlashChipSize() / 1024);
  DEBUGF("psram size : %d kb\r\n", ESP.getPsramSize() / 1024);
  DEBUGF("sketch size : %d kb\r\n", ESP.getSketchSize() / 1024);

  // esp_task_wdt_deinit();
  DEBUGLN("Initialize power control");
  power_init();
#if defined(CONFIG_TWATCH_HAS_DISPLAY)
  DEBUGLN("Initialize the backlight");
  backlight_init();
  DEBUGLN("Initialize the TFT");
  tft_init();
#endif

  DEBUGLN("Initialize IIC Bus. (frequency = 400,000)");
  Wire.begin(TWATCH_IICSDA, TWATCH_IICSCL, (uint32_t)400000);

#if defined(CONFIG_TWATCH_HAS_CST816S)
  DEBUGLN("Initialize touch");
  touch_init();
#endif

#if defined(CONFIG_TWATCH_HAS_ENCODER)
  DEBUGLN("Initializing the encoder");
  encoder_init();
#endif

#if defined(CONFIG_TWATCH_HAS_BUTTON)
  DEBUGLN("Initializing the button");
  button_init();
#endif

#if defined(CONFIG_TWATCH_HAS_LFS)
  DEBUGLN("Initializing the LittleFS");
  lfs_init(true, LFS_MOUNT_POINT);
#endif

#if defined(CONFIG_TWATCH_HAS_DISPLAY) && CONFIG_TWATCH_APP_LVGL
  DEBUGLN("Initializing the lvgl");
  lv_init();
  lv_port_disp_init(tft_get_instance());
  lv_port_indev_init();
#endif

#if defined(CONFIG_TWATCH_HAS_SD)
  DEBUGLN("Initializing the sd card");
  sd_init();
#endif

#if defined(CONFIG_TWATCH_HAS_QMC5883L)
  DEBUGLN("Initializing the magnetometer");
  qmc5883l_init();
#endif
#if defined(CONFIG_TWATCH_HAS_PCF8563)
  DEBUGLN("Initializing the rtc");
  rtc_init();
#endif

#if defined(CONFIG_TWATCH_HAS_MOTOR)
  DEBUGLN("Initializing the motor");
  motor_init();
#endif
#if defined(CONFIG_TWATCH_HAS_BME280)
  DEBUGLN("Initializing the barometer");
  bme280_init();
#endif

#if defined(CONFIG_TWATCH_HAS_GPS)
  DEBUGLN("Initializing the gps");
  gps_init();
#endif
#if defined(CONFIG_TWATCH_HAS_BMA423)
  DEBUGLN("Initializing the pedometer");
  bma423_interface_init();
  bma423_begin();
#endif

  DEBUGLN("twatch Initialization completed");
}

void TWatchClass::hal_auto_update(bool en, uint8_t core) {
  if (en) {
    if (HAL_Update_Handle == NULL)
      xTaskCreatePinnedToCore(hal_update_task, "hal_update_task", 1024 * 10, NULL, 2, &HAL_Update_Handle, core);
  } else {
    if (HAL_Update_Handle != NULL) {
      vTaskDelete(HAL_Update_Handle);
      HAL_Update_Handle = NULL;
    }
  }
}

void Debugloop(uint32_t millis, uint32_t time_ms) {
  static uint32_t Millis;
  if (millis - Millis > time_ms) {
    DEBUGF("Total heap: %d\n", ESP.getHeapSize());
    DEBUGF("Free heap: %d\n", ESP.getFreeHeap());
    DEBUGF("Max Alloc Heap: %d\n", ESP.getMaxAllocHeap());
    DEBUGF("Total PSRAM: %d\n", ESP.getPsramSize());
    DEBUGF("Free PSRAM: %d\n", ESP.getFreePsram());
    Millis = millis;
  }
}

void TWatchClass::hal_update_task(void *param) {
  static uint32_t ms;
  while (1) {
    ms = millis();
#if defined(CONFIG_TWATCH_HAS_CST816S)
    _ttgo->touch_updata(ms, 10);
#endif
#if defined(CONFIG_TWATCH_HAS_DISPLAY)
    _ttgo->backlight_updata(ms, 1);
#endif
#if defined(CONFIG_TWATCH_HAS_DISPLAY) && CONFIG_TWATCH_APP_LVGL
    lv_timer_handler();
#endif
#if defined(CONFIG_TWATCH_HAS_PCF8563)
    _ttgo->rtc_updata(ms, 1000);
#endif
#if defined(CONFIG_TWATCH_HAS_QMC5883L)
    _ttgo->qmc5883l_updata(ms, 100);
#endif
#if defined(CONFIG_TWATCH_HAS_BMA423)
    _ttgo->bma423_updata(ms, 100);
#endif
#if defined(CONFIG_TWATCH_HAS_BUTTON)
    _ttgo->button_updata(ms, 10);
#endif
#if defined(CONFIG_TWATCH_HAS_MOTOR)
    _ttgo->motor_loop(ms);
#endif
#if defined(CONFIG_TWATCH_HAS_GPS)
    _ttgo->gps_parse();
#endif
#if defined(CONFIG_TWATCH_HAS_BME280)
    _ttgo->bme280_updata(ms, 41);
#endif
#if defined(TWatch_HAL_AIO_INT)
    _ttgo->hal_aio_irq_cb();
#endif
#if CONFIG_TWATCH_USE_DEBUG
    // Debugloop(ms, 1000);
#endif
    _ttgo->power_updata(ms, 5);
    delay(2);
  }
}

void TWatchClass::hal_sleep(bool deep) {
  uint64_t mask;
#if defined(CONFIG_TWATCH_HAS_DISPLAY)
  uint32_t bl = backlight_get_value();
  tft->writecommand(0x10);
  backlight_set_value(0);
#endif
  // Touch_Interrupt(true);
  // AccSensor_Feature(BMA423_WRIST_WEAR | BMA423_SINGLE_TAP | BMA423_DOUBLE_TAP | BMA423_STEP_CNTR, true);
  // AccSensor_Feature_Int(BMA423_WRIST_WEAR_INT | BMA423_STEP_CNTR_INT | BMA423_SINGLE_TAP_INT | BMA423_DOUBLE_TAP_INT, true);
  // AccSensor_Acc_Feature(false);

  // Backlight_GradualLight();
  pinMode(TWATCH_IICSCL, INPUT_PULLUP);
  pinMode(TWATCH_IICSDA, INPUT_PULLUP);

  pinMode(TWATCH_PWR_ON, OUTPUT);
  digitalWrite(TWATCH_PWR_ON, LOW);

#if defined(TWATCH_AIO_INT)
  mask = 1ull << TWATCH_AIO_INT;
  esp_sleep_enable_ext1_wakeup(mask, ESP_EXT1_WAKEUP_ALL_LOW); // Screen int
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_0 /* BTN_0 */, LOW);
#else
  mask = 1ull << TWATCH_TOUCH_INT;
  esp_sleep_enable_ext1_wakeup(mask, ESP_EXT1_WAKEUP_ALL_LOW); // Screen int
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_39 /* TWATCH_BMA_INT_2 */, LOW);
#endif
  DEBUGF("go to sleep\n");

  if (deep)
    esp_deep_sleep_start();
  else {
    esp_light_sleep_start();
#if defined(CONFIG_TWATCH_HAS_DISPLAY)
    backlight_set_value(bl);
#endif
    digitalWrite(TWATCH_PWR_ON, HIGH);
#if defined(CONFIG_TWATCH_HAS_CST816S)
    touch->setTouchInt(false);
#endif
  }
}

#if defined(TWatch_HAL_AIO_INT)
void TWatchClass::hal_aio_irq_cb() {
  uint16_t int_status = 0;
  if (xEventGroupGetBits(_Hal_IRQ_event) & EVENT_IRQ_BIT) {
    xEventGroupClearBits(_Hal_IRQ_event, EVENT_IRQ_BIT);
    DEBUGLN("get irq");
#if defined(CONFIG_TWATCH_HAS_PCF8563)
    if (Rtc->alarmActive()) // Check if it is an alarm interrupt
    {
      Rtc->resetAlarm();
      DEBUGLN("_alarm_irq_cb");
      if (_alarm_irq_cb != nullptr) {
        _alarm_irq_cb(NULL);
      }
    } else
#endif
    {
#if defined(CONFIG_TWATCH_HAS_BMA423)
      bma423_read_int_status(&int_status, bma423);
      if (int_status & BMA423_SINGLE_TAP_INT) {
        DEBUGLN("Single tap received");
        if (_bma_irq_cb.single_tap_cb != nullptr) {
          _bma_irq_cb.single_tap_cb(NULL);
        }
      } else if (int_status & BMA423_DOUBLE_TAP_INT) {
        DEBUGLN("Double tap received");
        if (_bma_irq_cb.double_tap_cb != nullptr) {
          _bma_irq_cb.double_tap_cb(NULL);
        }
      } else if (int_status & BMA423_WRIST_WEAR_INT) {
        DEBUGLN("Wrist wear received");
        if (_bma_irq_cb.wrist_wear_cb != nullptr) {
          _bma_irq_cb.wrist_wear_cb(NULL);
        }
      } else if (int_status & BMA423_STEP_CNTR_INT) {
        DEBUGLN("Step cntr received");
        if (_bma_irq_cb.step_cntr_cb != nullptr) {
          _bma_irq_cb.step_cntr_cb(NULL);
        }
      } else if (int_status & BMA423_ACTIVITY_INT) {
        DEBUGLN("Activity received");
        if (_bma_irq_cb.activity_cb != nullptr) {
          _bma_irq_cb.activity_cb(NULL);
        }
      } else if (int_status & BMA423_ANY_MOT_INT) {
        DEBUGLN("Any mot received");
        if (_bma_irq_cb.any_mot_cb != nullptr) {
          _bma_irq_cb.any_mot_cb(NULL);
        }
      } else if (int_status & BMA423_NO_MOT_INT) {
        DEBUGLN("No mot received");
        if (_bma_irq_cb.no_mot_cb != nullptr) {
          _bma_irq_cb.no_mot_cb(NULL);
        }
      }
#endif
    }
  }
}
#endif

#if defined(CONFIG_TWATCH_HAS_SD) || defined(CONFIG_TWATCH_HAS_FFAT)
void listDir(fs::FS &fs, const char *dirname, uint8_t levels) {
  DEBUGF("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    DEBUGLN("Failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    DEBUGLN("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
      DEBUGLN(file.name());
      if (levels) {
        listDir(fs, file.path(), levels - 1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      DEBUGLN(file.size());
    }
    file = root.openNextFile();
  }
}

void createDir(fs::FS &fs, const char *path) {
  DEBUGF("Creating Dir: %s\n", path);
  if (fs.mkdir(path)) {
    DEBUGLN("Dir created");
  } else {
    DEBUGLN("mkdir failed");
  }
}

void removeDir(fs::FS &fs, const char *path) {
  DEBUGF("Removing Dir: %s\n", path);
  if (fs.rmdir(path)) {
    DEBUGLN("Dir removed");
  } else {
    DEBUGLN("rmdir failed");
  }
}

void readFile(fs::FS &fs, const char *path) {
  DEBUGF("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    DEBUGLN("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  while (file.available()) {
    Serial.write(file.read());
  }
}

void writeFile(fs::FS &fs, const char *path, const char *message) {
  DEBUGF("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    DEBUGLN("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    DEBUGLN("File written");
  } else {
    DEBUGLN("Write failed");
  }
}

void appendFile(fs::FS &fs, const char *path, const char *message) {
  DEBUGF("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    DEBUGLN("Failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    DEBUGLN("Message appended");
  } else {
    DEBUGLN("Append failed");
  }
}

void renameFile(fs::FS &fs, const char *path1, const char *path2) {
  DEBUGF("Renaming file %s to %s\n", path1, path2);
  if (fs.rename(path1, path2)) {
    DEBUGLN("File renamed");
  } else {
    DEBUGLN("Rename failed");
  }
}

void deleteFile(fs::FS &fs, const char *path) {
  DEBUGF("Deleting file: %s\n", path);
  if (fs.remove(path)) {
    DEBUGLN("File deleted");
  } else {
    DEBUGLN("Delete failed");
  }
}

void testFileIO(fs::FS &fs, const char *path) {
  File file = fs.open(path);
  static uint8_t buf[512];
  size_t len = 0;
  uint32_t start = millis();
  uint32_t end = start;
  if (file) {
    len = file.size();
    size_t flen = len;
    start = millis();
    while (len) {
      size_t toRead = len;
      if (toRead > 512) {
        toRead = 512;
      }
      file.read(buf, toRead);
      len -= toRead;
    }
    end = millis() - start;
    DEBUGF("%u bytes read for %u ms\n", flen, end);
    file.close();
  } else {
    DEBUGLN("Failed to open file for reading");
  }

  file = fs.open(path, FILE_WRITE);
  if (!file) {
    DEBUGLN("Failed to open file for writing");
    return;
  }

  size_t i;
  start = millis();
  for (i = 0; i < 2048; i++) {
    file.write(buf, 512);
  }
  end = millis() - start;
  DEBUGF("%u bytes written for %u ms\n", 2048 * 512, end);
  file.close();
}
#endif
