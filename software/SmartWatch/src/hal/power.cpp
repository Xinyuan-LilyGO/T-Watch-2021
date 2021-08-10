#include <esp_adc_cal.h>

#include "driver/rtc_io.h"
#include "osw_hal.h"
#include "osw_pins.h"

#define V_REF 1100 // ADC reference voltage
#define CHANNEL ADC2_CHANNEL_8

void WakeUpCallback()
{
  //placeholder callback function
}

void OswHal::setupPower(void)
{
  pinMode(STAT_PWR, INPUT_PULLUP);
  pinMode(B_MON, INPUT);
  pinMode(PWR_ON, OUTPUT);
  digitalWrite(PWR_ON, HIGH);
}

boolean OswHal::isCharging(void)
{
  return !digitalRead(STAT_PWR); // TODO: check if 1 = charging or not :)
}

uint16_t OswHal::getBatteryRaw(void)
{
  pinMode(B_MON, INPUT);
  return analogRead(B_MON);
}

//power 2600 - 2300

uint8_t OswHal::getBatteryPercent(void)
{
  uint16_t b = 0;

  uint8_t n = 20;
  // measure n times
  for (uint8_t i = 0; i < n; i++)
  {
    b = b + getBatteryRaw();
  }
  b = b / n;

  float vol = ((b * 3.3) / 4096 + 0.1);
  vol = vol < 1.4 ? 0 : (vol - 1.4) / 0.6 * 100;
  return vol > 100 ? 100 : vol;
  // magic values through a single experiment:
  /*   if (b >= 2600)
  {
    return 100;
  }
  else if (b >= 2540)
  {
    return 80;
  }
  else if (b >= 2480)
  {
    return 60;
  }
  else if (b >= 2420)
  {
    return 40;
  }
  else if (b >= 2360)
  {
    return 20;
  }
  else if (b >= 2330)
  {
    return 10;
  }
  else if (b >= 2315)
  {
    return 5;
  }
  else
  {
    return 0;
  } */
}

// float OswHal::getBatteryVoltage(void) {
//   adcAttachPin(B_MON);
//   adcStart(B_MON);

//   // adc2_config_width(ADC_WIDTH_12Bit);
//   adc2_config_channel_atten(ADC2_CHANNEL_8, ADC_ATTEN_11db);
//   esp_adc_cal_characteristics_t characteristics;
//   esp_adc_cal_characterize(ADC_UNIT_2, ADC_ATTEN_DB_11, ADC_WIDTH_10Bit, V_REF, &characteristics);
//   uint32_t voltage = 0;
//   esp_adc_cal_get_voltage(ADC_CHANNEL_8, &characteristics, &voltage);

//   // some dodgy math to get a representable value
//   return voltage / (100.0) + 0.3;
// }

void OswHal::setCPUClock(uint8_t mhz)
{
  // https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/esp32-hal-cpu.h
  // ESP32 PICO D4 -> https://docs.espressif.com/projects/esp-idf/en/latest/hw-reference/get-started-pico-kit.html
  // -> 40MHz Oscillator
  // //  240, 160, 80, 40, 20, 10  <<< For 40MHz XTAL
  setCpuFrequencyMhz(mhz);
}
void OswHal::deepSleep()
{
  Serial.println("good night");
  this->setBrightness(0);
  this->displayOff();

  this->Cst816s_Sleep();

  this->qmc5883_Sleep();
  this->BMA423shutdown();

  pinMode(TFT_CS, INPUT);
  pinMode(TFT_DC, INPUT);
  pinMode(TFT_RST, INPUT);
  pinMode(TFT_SCK, INPUT);
  pinMode(TFT_MOSI, INPUT);
  pinMode(TFT_MISO, INPUT);
  pinMode(TFT_LED, INPUT);
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(Touch_Int, INPUT_PULLUP);
  pinMode(Touch_Res, OUTPUT);
  digitalWrite(Touch_Res, HIGH);

  pinMode(SCL, INPUT_PULLUP);
  pinMode(SDA, INPUT_PULLUP);

  pinMode(PWR_ON, OUTPUT);
  digitalWrite(PWR_ON, LOW);
#if defined(GPS_EDITION)
  this->gpsBackupMode();
  this->sdOff();
#endif

  // TODO: this is not optimal / implement this properly
  // rtc_gpio_isolate(GPIO_NUM_5);
  // rtc_gpio_isolate(GPIO_NUM_9);
  // rtc_gpio_isolate(GPIO_NUM_10);
  // rtc_gpio_isolate(GPIO_NUM_12);
  // rtc_gpio_isolate(GPIO_NUM_13);
  // rtc_gpio_isolate(GPIO_NUM_15);
  // rtc_gpio_isolate(GPIO_NUM_18);
  // rtc_gpio_isolate(GPIO_NUM_21);
  // rtc_gpio_isolate(GPIO_NUM_22);
  // rtc_gpio_isolate(GPIO_NUM_23);
  // rtc_gpio_isolate(GPIO_NUM_25);
  // rtc_gpio_isolate(GPIO_NUM_27);
  // rtc_gpio_isolate(GPIO_NUM_32);
  // rtc_gpio_isolate(GPIO_NUM_33);
  // rtc_gpio_isolate(GPIO_NUM_34);
  // rtc_gpio_isolate(GPIO_NUM_35);

  uint64_t mask;
  mask = 1ull << 32;
  //第一个参数：mask位，如果引脚为34 则mask = 1ull<<34
  //第二个参数：是高电平唤醒还是低电平唤醒
  esp_sleep_enable_ext1_wakeup(mask, ESP_EXT1_WAKEUP_ALL_LOW);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_0 /* BTN_0 */, LOW);
  // esp_sleep_enable_ext0_wakeup(GPIO_NUM_35 /* BMA_INT_2 / TAP */, HIGH); // step interrupts (currently)
  //esp_sleep_enable_ext0_wakeup(GPIO_NUM_34 /* BMA_INT_1 */, HIGH);  // tilt to wake and tap interrupts
  //esp_sleep_enable_touchpad_wakeup();
  esp_deep_sleep_start();
};

void OswHal::deepSleep(long millis)
{
  esp_sleep_enable_timer_wakeup(millis * 1000);
  deepSleep();
};
