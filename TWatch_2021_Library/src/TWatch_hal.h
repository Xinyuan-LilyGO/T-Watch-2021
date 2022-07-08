// #ifndef __TWatch_HAL_H__
// #define __TWatch_HAL_H__
#pragma once
#include "SPI.h"
#include "TWatch_config.h"
#include "esp_log.h"
#include "esp_task_wdt.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include <Arduino.h>
#include <Wire.h>
#include <stdio.h>
#if defined(CONFIG_TWATCH_HAS_FFAT)
#include "FFat.h"
#endif
#if defined(CONFIG_TWATCH_HAS_DISPLAY)
#include "libraries/TFT_eSPI/TFT_eSPI.h"
#endif
#if defined(CONFIG_TWATCH_HAS_BUTTON)
#include "libraries/OneButton/src/OneButton.h"
#endif
#if defined(CONFIG_TWATCH_HAS_CST816S)
#include "libraries/Cst816s/CST816S.h"
#endif
#if defined(CONFIG_TWATCH_HAS_ENCODER)
#include "libraries/Encoder/Encoder.h"
#endif
#if defined(CONFIG_TWATCH_HAS_QMC5883L)
#include "libraries/QMC5883L-API/QMC5883LCompass.h"
#endif
#if defined(CONFIG_TWATCH_HAS_GPS)
#include "libraries/TinyGPSPlus/src/TinyGPS++.h"
#endif
#if defined(CONFIG_TWATCH_HAS_BME280)
#include "libraries/Adafruit_BME280_Library/Adafruit_BME280.h"
#include "libraries/Adafruit_Sensor/Adafruit_Sensor.h"
#endif
#if defined(CONFIG_TWATCH_HAS_PCF8563)
#include "libraries/PCF8563_Library/src/pcf8563.h"
#endif
#if defined(CONFIG_TWATCH_HAS_BMA423)
#include "libraries/BMA423-Sensor-API/bma423.h"
#endif
#if defined(CONFIG_TWATCH_HAS_SD)
#include "SD.h"
#endif
#if defined(CONFIG_TWATCH_HAS_SD) || defined(CONFIG_TWATCH_HAS_FFAT)
#include "FS.h"
#endif
#if CONFIG_TWATCH_APP_LVGL
#include "libraries/lvgl/lvgl.h"
#endif
#include "soc/soc_ulp.h"
//#include "libraries/SdFat/src/SdFat.h"
/* #include "WiFi.h"
#include "HTTPClient.h" */
// #include "libraries/BluetoothSerial/src/BluetoothSerial.h"
/* #include <ArduinoJson.h> */

#if CONFIG_TWATCH_USE_DEBUG

#define DEBUG(x)         Serial.print(x);
#define DEBUGLN(x)       Serial.println(x);
#define DEBUGF(fmt, ...) Serial.printf(fmt, ##__VA_ARGS__);
#define _DEBUG_IS_RUN_LINE(name, param)                                                                                                              \
  do {                                                                                                                                               \
    DEBUGF("%s: %d " #name " : %" #param "\n", __func__, __LINE__, name);                                                                            \
  } while (0);

#else
#define DEBUG(x)                        ;
#define DEBUGLN(x)                      ;
#define DEBUGF(fmt, ...)                ;
#define _DEBUG_IS_RUN_LINE(name, param) ;
#endif

#define EVENT_IRQ_BIT                  (_BV(1))

#define TOUCH_IRQ_BIT                  (_BV(2))
#define ALARM_IRQ_BIT                  (_BV(3))
#define SPORTS_IRQ_BIT                 (_BV(4))

#define EVENT_CLICK_BIT(x)             (_BV(0) << x)
#define EVENT_DOUBLE_CLICK_BIT(x)      (_BV(4) << x)
#define EVENT_DURING_LONG_PRESS_BIT(x) (_BV(8) << x)

#define COLOR_NONE                     "\033[0m"
#define FONT_COLOR_RED                 "\033[0;31m"
#define FONT_COLOR_BLUE                "\033[1;34m"
#define BACKGROUND_COLOR_RED           "\033[41m"
#define BG_RED_FONT_YELLOW             "\033[41;33m"

#define POWER_UPDATA_CYCLE             50

typedef TFT_eSPI SCREEN_CLASS;
typedef void (*irq_Fun_cb_t)(void *user_data_ptr);

typedef enum { BUTTON_CLICK = 0, BUTTON_DOUBLE_CLICK, BUTTON_LONG_PRESS_START, BUTTON_LONG_PRESS_STOP, BUTTON_DURING_LONG_PRESS } button_event_t;

class TWatchClass {
  struct irq_bma_Fun_cb_t {
    irq_Fun_cb_t single_tap_cb;
    irq_Fun_cb_t double_tap_cb;
    irq_Fun_cb_t wrist_wear_cb;
    irq_Fun_cb_t step_cntr_cb;
    irq_Fun_cb_t activity_cb;
    irq_Fun_cb_t any_mot_cb;
    irq_Fun_cb_t no_mot_cb;
  };

private:
public:
  TWatchClass() {
    hal_init();
#if defined(TWatch_HAL_AIO_INT)
    pinMode(TWATCH_AIO_INT, INPUT);
    attachInterrupt(
        TWATCH_AIO_INT,
        []() {
          portBASE_TYPE task_woken, xResult;
          if ((xEventGroupGetBits(_ttgo->_Hal_IRQ_event) & EVENT_IRQ_BIT) != EVENT_IRQ_BIT) {
            xResult = xEventGroupSetBitsFromISR(_ttgo->_Hal_IRQ_event, EVENT_IRQ_BIT, &task_woken);
          }
        },
        FALLING);
#else
    pinMode(TWATCH_TOUCH_INT, INPUT_PULLUP);
    pinMode(TWATCH_BMA_INT_2, INPUT);
#endif
  };

  ~TWatchClass();

  static TWatchClass *getWatch() {
    if (_ttgo == nullptr) {
      _ttgo = new TWatchClass();
      _Hal_IRQ_event = xEventGroupCreate();
#if defined(CONFIG_TWATCH_HAS_BUTTON)
      _hal_button_event = xEventGroupCreate();
#endif
    }
    return _ttgo;
  }

  static TWatchClass *_ttgo;
  static EventGroupHandle_t _Hal_IRQ_event;
#if defined(CONFIG_TWATCH_HAS_BUTTON)
  static EventGroupHandle_t _hal_button_event;
#endif

  void hal_init();
  static void hal_update_task(void *param);
  void hal_sleep(bool deep);
  void hal_aio_irq_cb();
  /* Background tasks automatically refresh sensor data */
  void hal_auto_update(bool en, uint8_t core);

#if defined(CONFIG_TWATCH_HAS_POWER)
  /* Power */
  void power_init();
  float power_get_volt();
  float power_get_percent();
  void power_updata(uint32_t millis, uint32_t time_ms);
#endif

#if defined(CONFIG_TWATCH_HAS_MOTOR)
  /* Motor */
  void motor_init();
  void motor_shake(const uint32_t cnt, const uint32_t interval);
  void motor_loop(uint32_t millis);
  void motor_stop();
#endif

#if defined(CONFIG_TWATCH_HAS_DISPLAY)
  /* Display */
  void tft_init();
  TFT_eSPI *tft_get_instance();

  /* Backlight */
  void backlight_init();
  void backlight_set_value(int16_t val);
  int16_t backlight_get_value();
  void backlight_gradual_light(int16_t val, uint32_t ms);
  void backlight_updata(uint32_t millis, uint32_t time_ms);
#endif

#if defined(CONFIG_TWATCH_HAS_BUTTON)
  /* Button */
  void button_init();
  void button_updata(uint32_t millis, uint32_t time_ms);
  void button_bind_event(uint8_t Btn, button_event_t Event, parameterizedCallbackFunction Function, void *parameter = nullptr);
#endif

#if defined(CONFIG_TWATCH_HAS_BMA423)
  /* Acceleration Sensor : bma423 */
  void bma423_begin();
  void bma423_interface_init();
  void bma423_step_reset();
  void bma423_feature(uint8_t feature, bool Enable);
  void bma423_feature_int(uint8_t feature, bool Enable);
  void bma423_acc_feature(bool Enable);
  void bma423_reset(void);
  void bma423_updata(uint32_t millis, uint32_t time_ms);
  float bma423_getX();
  float bma423_getY();
  float bma423_getZ();
  void bma423_set_feature_event(uint8_t feature, irq_Fun_cb_t cb);
  uint32_t bma423_get_step();
  float bma423_get_temperature(uint8_t temp_unit);
#endif

#if defined(CONFIG_TWATCH_HAS_QMC5883L)
  /* MAG Sensor : qmc5883l*/
  void qmc5883l_init();
  void qmc5883l_updata(uint32_t millis, uint32_t time_ms);
  int qmc5883l_getX();
  int qmc5883l_getY();
  int qmc5883l_getZ();
  int qmc5883l_get_Azimuth();
#endif

#if defined(CONFIG_TWATCH_HAS_PCF8563)
  /* RTC : pcf8563 */
  void rtc_init();
  void rtc_get_time(uint8_t *hour, uint8_t *minute, uint8_t *second);
  void rtc_get_date(uint16_t *year, uint8_t *month, uint8_t *day);
  void rtc_set_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
  void rtc_updata(uint32_t millis, uint32_t time_ms);
  PCF8563_Class *rtc_get_instance();
  RTC_Date rtc_get_time();
  RTC_Date LocalTime;
  bool rtc_is_updated();
#if defined(USE_RTC_ALARM)
  void rtc_set_alarm_time(uint8_t hour, uint8_t minute, uint8_t day, uint8_t weekday);
#endif

#endif

#if defined(CONFIG_TWATCH_HAS_CST816S)
  /* Touch */
  void touch_init();
  bool touch_check();
  void touch_interrupt(bool enable = false);
  uint16_t touch_getX();
  uint16_t touch_getY();
  void touch_updata(uint32_t millis, uint32_t time_ms);

#endif

#if defined(CONFIG_TWATCH_HAS_BME280)
  /* Temp Humidity Sensor : bme280 */
  float Temperature, Pressure, Altitude, Humidity;
  void bme280_init();
  void bme280_updata(uint32_t millis, uint32_t time_ms);
  float bme280_get_temperature();
  float bme280_get_pressure();
  float bme280_get_altitude();
  float bme280_get_humidity();
  Adafruit_BME280 *bme280_get_instance();
#endif

#if defined(CONFIG_TWATCH_HAS_GPS)
  /* GPS : L76K */
  void gps_init();
  void gps_parse();
  void gps_serial_output(bool enable);
  TinyGPSPlus get_gps_instance();
#endif

#if defined(CONFIG_TWATCH_HAS_ENCODER)
  /* encoder */
  Encoder *encoder = nullptr;
  void encoder_init();
  int32_t encoder_get_diff();
#endif

#if defined(CONFIG_TWATCH_HAS_SD)
  /* SD */
  bool sd_init();
  bool sd_check_dir(const char *path, bool create = false);
  bool sd_is_ready();
  fs::SDFS sd_get_instance();
#endif

#if defined(CONFIG_TWATCH_HAS_FFAT)
  /* FFAT */
  bool ffat_init(bool formatOnFail = false, const char *basePath = "/ffat", uint8_t maxOpenFiles = 10,
                 const char *partitionLabel = (char *)FFAT_PARTITION_LABEL);
  bool is_ffat_mounted();
#endif

#if CONFIG_TWATCH_APP_LVGL
  lv_indev_t *lv_touch_handle;
  lv_indev_t *lv_encoder_handle;
  lv_indev_t *lv_button_handle;
#endif

private:
  TaskHandle_t HAL_Update_Handle = NULL;
#if defined(TWatch_HAL_AIO_INT)
  irq_Fun_cb_t _alarm_irq_cb = nullptr;
  struct irq_bma_Fun_cb_t _bma_irq_cb = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
#endif

#if defined(CONFIG_TWATCH_HAS_POWER)
  /* Power */
  uint16_t _pow_temp[POWER_UPDATA_CYCLE];
  float _pow_percent = 0;
  float _pow_cur_vol = 0.0;
  bool _ischarge = false;
  uint32_t _power_sub = 0;
  uint8_t _power_cnt = 0;
#endif

#if defined(CONFIG_TWATCH_HAS_MOTOR)
  /* Motor */
  bool isShake;
  uint32_t _cnt, _interval_ms;
#endif

#if defined(CONFIG_TWATCH_HAS_DISPLAY)
  /* Display */
  TFT_eSPI *tft = nullptr;

  /* Backlight */
  bool _adjust = false;
  uint32_t _endtime;
  int16_t _old_Backlight;
  float _k;
#endif
#if defined(CONFIG_TWATCH_HAS_SD)
  SPIClass _sd_spi;
#endif
#if defined(CONFIG_TWATCH_HAS_CST816S)
  /* Touch */
  CST816S_Class *touch = nullptr;
  bool _isinited_cst816s = false;
#endif

#if defined(CONFIG_TWATCH_HAS_BUTTON)
  /* Button */
  OneButton *buttonLock = nullptr;
  OneButton *buttonMenu = nullptr;
  OneButton *buttonFastSet = nullptr;
#if defined(CONFIG_TWATCH_HAS_ENCODER)
  /* encoder */
  OneButton *buttonEncoder = nullptr;
#endif
#endif

#if defined(CONFIG_TWATCH_HAS_ENCODER)
  /* encoder */
  long _lastPosition = -999;
#endif

#if defined(CONFIG_TWATCH_HAS_BMA423)
  /* Acceleration Sensor : bma423 */
  float AccX, AccY, AccZ;
  uint32_t stepCount;
  bool _isinited_bma423 = false;
  bma4_dev *bma423 = nullptr;
#endif

#if defined(CONFIG_TWATCH_HAS_BME280)
  /* Temp Humidity Sensor : bme280 */
  bool _isinited_bme280 = false;
  Adafruit_BME280 *bme280 = nullptr;
#endif

#if defined(CONFIG_TWATCH_HAS_GPS)
  /* GPS : L76K */
  TinyGPSPlus gps;
  bool _gps_output2serial = false;
#endif

#if defined(CONFIG_TWATCH_HAS_PCF8563)
  /* RTC : pcf8563 */
  bool _isinited_pcf8563 = false;
  PCF8563_Class *Rtc = nullptr;
  bool _is_time_updated = false;
#endif
#if defined(CONFIG_TWATCH_HAS_QMC5883L)
  /* MAG Sensor : qmc5883l*/
  QMC5883LCompass *MAG = nullptr;
  bool _isinited_qmc5883l = false;
  int Azimuth;
  int magX, magY, magZ;
#endif

#if defined(CONFIG_TWATCH_HAS_FFAT)
  bool _is_ffat_mounted = false;

#endif

#if CONFIG_TWATCH_APP_LVGL
  lv_color_t *lv_disp_buf_p = nullptr;

  static void lv_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
  static void lv_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
  static void lv_button_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
  static void lv_encoder_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
  static void wrist_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);

  void lv_port_disp_init(SCREEN_CLASS *scr);
  void lv_port_indev_init(void);
  void lv_ffat_fs_if_init(void);
  // void display_send_DMA_done_cb(spi_transaction_t *trans);
#endif
  void tw_bubble_sort(uint16_t *arr, int len) {
    int i, j;
    uint16_t temp;
    for (i = 0; i < len - 1; i++)
      for (j = 0; j < len - 1 - i; j++)
        if (arr[j] > arr[j + 1]) {
          temp = arr[j];
          arr[j] = arr[j + 1];
          arr[j + 1] = temp;
        }
  }
};
#if defined(CONFIG_TWATCH_HAS_SD) || defined(CONFIG_TWATCH_HAS_FFAT)
void listDir(fs::FS &fs, const char *dirname, uint8_t levels);
void createDir(fs::FS &fs, const char *path);
void removeDir(fs::FS &fs, const char *path);
void readFile(fs::FS &fs, const char *path);
void writeFile(fs::FS &fs, const char *path, const char *message);
void appendFile(fs::FS &fs, const char *path, const char *message);
void renameFile(fs::FS &fs, const char *path1, const char *path2);
void deleteFile(fs::FS &fs, const char *path);
void testFileIO(fs::FS &fs, const char *path);
#endif