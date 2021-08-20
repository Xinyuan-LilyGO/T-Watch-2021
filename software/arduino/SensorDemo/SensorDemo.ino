#include <Arduino.h>
#include <Wire.h>
//Resource
#include "config.h"
#include "img.h"
//External dependency library
#include <TFT_eSPI.h>		 //https://github.com/Bodmer/TFT_eSPI
#include <bma.h>			 //https://github.com/lewisxhe/BMA423_Library
#include <QMC5883LCompass.h> //https://github.com/mprograms/QMC5883Compas
#include "CST816S.h"
#include "pcf8563.h"

bool CheckAcc = false;
bool CheckIMU = false;
bool CheckTouch = false;
bool CheckRTC = false;

TFT_eSPI tft = TFT_eSPI();
BMA423 AccSensor;
QMC5883LCompass IMUSensor;
CST816S TouchSensor;
PCF8563_Class rtc;

uint16_t readRegister(uint8_t address, uint8_t reg, uint8_t *data, uint16_t len)
{
	Wire.beginTransmission(address);
	Wire.write(reg);
	Wire.endTransmission();
	Wire.requestFrom((uint8_t)address, (uint8_t)len);
	uint8_t i = 0;
	while (Wire.available())
	{
		data[i++] = Wire.read();
	}
	return 0; //Pass
}

uint16_t writeRegister(uint8_t address, uint8_t reg, uint8_t *data, uint16_t len)
{
	Wire.beginTransmission(address);
	Wire.write(reg);
	Wire.write(data, len);
	return (0 != Wire.endTransmission());
}

static uint8_t y = 32;
static uint8_t x = 52;
void printStatus(const char *setting, const char *value)
{
	tft.setCursor(x, y);
	tft.print(setting);
	tft.print(": ");
	tft.print(value);
	y += 8;
}

void setup()
{
	//POWER
	pinMode(PWR_ON, OUTPUT);
	digitalWrite(PWR_ON, HIGH);
	//Backlight
	pinMode(TFT_LED, OUTPUT);
	ledcSetup(0, 4000, 8);
	ledcAttachPin(TFT_LED, 0);
	ledcWrite(0, 0);

	tft.init();
	tft.setRotation(0);
	tft.setTextSize(1);
	tft.setTextColor(TFT_GREEN, TFT_BLACK);

	tft.fillScreen(TFT_BLACK);
	tft.setSwapBytes(true);
	tft.pushImage(0, 0, 240, 240, lilygo);
	//Light gradually
	for (int i = 0; i < 0XFF; i++)
	{
		ledcWrite(0, i);
		delay(5);
	}

	Wire.begin(IICSDA, IICSCL);
	//AccSensor
	CheckAcc = AccSensor.begin(readRegister, writeRegister, delay);
	Acfg cfg;
	cfg.odr = BMA4_OUTPUT_DATA_RATE_100HZ;
	cfg.range = BMA4_ACCEL_RANGE_2G;
	cfg.bandwidth = BMA4_ACCEL_NORMAL_AVG4;
	cfg.perf_mode = BMA4_CONTINUOUS_MODE;
	AccSensor.setAccelConfig(cfg);
	AccSensor.enableAccel();
	AccSensor.enableFeature(BMA423_STEP_CNTR, true);
	AccSensor.resetStepCounter();

	//IMU
	Wire.beginTransmission(0x0D);
	CheckIMU = !Wire.endTransmission();

	IMUSensor.init();
	IMUSensor._writeReg(0x0A, 0x01); //Disabled hardware DRDY  *Hardware DRDY connection GPIO12, if not enabled will lead to a BUG when burning                                //Disabled hardware DRDY  *Hardware DRDY connection GPIO12, if not enabled will lead to a BUG when burning

	//Touch
	CheckTouch = TouchSensor.begin(Wire, Touch_Res, Touch_Int);

	//RTC
	Wire.beginTransmission(PCF8563_SLAVE_ADDRESS);
	CheckRTC = !Wire.endTransmission();
	rtc.begin();
	rtc.setDateTime(2021, 1, 1, 12, 33, 59);

	//Gradually darken
	for (int i = 0; i < 0XFF; i++)
	{
		ledcWrite(0, 0XFF - i);
		delay(5);
	}
	tft.fillScreen(TFT_BLACK);
	ledcWrite(0, 0XFF);
}

void loop()
{
	y = 32;
	x = 52;
	printStatus("RTC", CheckRTC == true ? "[success]" : "[NA]");
	printStatus("ACC", CheckAcc == true ? "[success]" : "[NA]");
	printStatus("Touch", CheckTouch == true ? "[success]" : "[NA]");
	printStatus("IMU", CheckIMU == true ? "[success]" : "[NA]");

	tft.setCursor(x, y);
	y += 8;
	tft.print("Time:");
	tft.print(rtc.formatDateTime(PCF_TIMEFORMAT_YYYY_MM_DD_H_M_S));

	tft.setCursor(x, y);
	y += 8;
	IMUSensor.read();
	tft.print("Azimuth:");
	tft.print(IMUSensor.getAzimuth());

	Accel acc;
	AccSensor.getAccel(acc);
	tft.setCursor(x, y);
	y += 8;
	tft.print("Step:");
	tft.print(AccSensor.getCounter());
	tft.setCursor(x, y);
	y += 8;
	tft.printf(" X:%4d", acc.x);
	tft.setCursor(x, y);
	y += 8;
	tft.printf(" Y:%4d", acc.y);
	tft.setCursor(x, y);
	y += 8;
	tft.printf(" Z:%4d", acc.z);

	TouchSensor.ReadTouch();
	static uint16_t tx, ty;
	static bool touchState;
	touchState = TouchSensor.TouchInt();
	if (TouchSensor.getTouchType() == 0x01)
	{
		tx = TouchSensor.getX();
		ty = TouchSensor.getY();
	}
	tft.setCursor(x, y);
	y += 8;
	tft.printf("TouchState:%s", touchState == true ? "press  " : "release");
	tft.setCursor(x, y);
	y += 8;
	tft.printf("x:%4d   y:%4d", tx, ty);
}
