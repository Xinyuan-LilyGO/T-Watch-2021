#ifndef __TWATCH2021_V2_H__
#define __TWATCH2021_V2_H__

/*
log:
1.Add GPS function
2.Added BME280: barometric pressure, temperature, humidity sensor
3.Add SD card read and write function
4.Add rotary encoder function

5.Remove charge indication CHRG pin. The reason is that it does not recognize
the charging state through this IO.
*/

// Pin definition
#define TWATCH_PWR_ON      32

#define TWATCH_CHARGING    -1
#define TWATCH_BAT_ADC     36

#define TWATCH_BTN_1       0
#define TWATCH_BTN_2       39
#define TWATCH_BTN_3       34

#define TWATCH_MOTOR       2

#define TWATCH_IICSCL      26
#define TWATCH_IICSDA      27

#define TWATCH_TOUCH_RES   -1

#define TWATCH_TOUCH_INT   37
#define TWATCH_RTC_INT     37
#define TWATCH_BMA_INT_1   37
#define TWATCH_BMA_INT_2   37

#define TWATCH_AIO_INT     37

#define TFT_WIDTH          240
#define TFT_HEIGHT         240

#define TWATCH_TFT_MISO    -1
#define TWATCH_TFT_MOSI    23
#define TWATCH_TFT_SCLK    18
#define TWATCH_TFT_CS      5
#define TWATCH_TFT_DC      22
#define TWATCH_TFT_RST     -1
#define TWATCH_TFT_BL      21

#define TWATCH_GPS_RX      3
#define TWATCH_GPS_TX      1
#define TWATCH_GPS_WAKE_UP 25

#define TWATCH_ENCODER_A   35
#define TWATCH_ENCODER_B   33
#define TWATCH_ENCODER_C   38
#define TWATCH_ENCODER_BTN TWATCH_ENCODER_C

#define TWATCH_SD_CS       13
#define TWATCH_SD_MOSI     15
#define TWATCH_SD_MISO     14
#define TWATCH_SD_CLK      12
#endif