#include "config.h"
#include "img.h"
#include <TFT_eSPI.h> //https://github.com/Bodmer/TFT_eSPI

TFT_eSPI tft = TFT_eSPI();

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
	tft.fillScreen(TFT_BLACK);
	tft.setSwapBytes(true);
	tft.pushImage(0, 0, 240, 240, lilygo);
	//Light gradually
	for (int i = 0; i < 0XFF; i++)
	{
		ledcWrite(0, i);
		delay(5);
	}
	delay(4000);
	for (int i = 0; i < 0XFF; i++)
	{
		ledcWrite(0, 0XFF - i);
		delay(5);
	}
	ledcWrite(0, 0XFF);
}

void loop()
{

	tft.fillScreen(TFT_RED);
	delay(2000);
	tft.fillScreen(TFT_GREEN);
	delay(2000);
	tft.fillScreen(TFT_BLUE);
	delay(2000);

	for (int a = 0; a < 256; a += 2) // Alpha 0 = 100% background, alpha 255 = 100% foreground
	{
		for (int c = 0; c < 192; c++)
			tft.drawPixel(c, a / 2, tft.alphaBlend(a, rainbow(c), TFT_WHITE));
	}

	// Blend from full spectrum to black
	for (int a = 255; a > 2; a -= 2)
	{
		for (int c = 0; c < 192; c++)
			tft.drawPixel(c, 128 + (255 - a) / 2, tft.alphaBlend(a, rainbow(c), TFT_BLACK));
	}

	// Blend from white to black (32 grey levels)
	for (uint16_t a = 0; a < 255; a++) // Alpha 0 = 100% background, alpha 255 = 100% foreground
	{
		tft.drawFastHLine(192, a, 12, tft.alphaBlend(a, TFT_BLACK, TFT_WHITE));
		tft.drawFastHLine(204, a, 12, tft.alphaBlend(a, TFT_BLACK, TFT_RED));
		tft.drawFastHLine(216, a, 12, tft.alphaBlend(a, TFT_BLACK, TFT_GREEN));
		tft.drawFastHLine(228, a, 12, tft.alphaBlend(a, TFT_BLACK, TFT_BLUE));
	}

	delay(4000);

	// Blend from white to colour (32 grey levels)
	for (uint16_t a = 0; a < 255; a++) // Alpha 0 = 100% background, alpha 255 = 100% foreground
	{
		//tft.drawFastHLine(192, a, 12, tft.alphaBlend(a, TFT_BLACK, TFT_WHITE));
		tft.drawFastHLine(204, a, 12, tft.alphaBlend(a, TFT_RED, TFT_WHITE));
		tft.drawFastHLine(216, a, 12, tft.alphaBlend(a, TFT_GREEN, TFT_WHITE));
		tft.drawFastHLine(228, a, 12, tft.alphaBlend(a, TFT_BLUE, TFT_WHITE));
	}

	delay(4000);

	//*
	// Decrease to 8 bit colour (3 bits red, 3 bits green, 2 bits blue)
	// Blend from white to full spectrum
	for (int a = 0; a < 256; a += 2) // Alpha 0 = 100% background, alpha 255 = 100% foreground
	{
		// Convert blended 16 bit colour to 8 bits to reduce colour resolution, then map back to 16 bits for displaying
		for (int c = 0; c < 192; c++)
			tft.drawPixel(c, a / 2, tft.color8to16(tft.color16to8(tft.alphaBlend(a, rainbow(c), 0xFFFF))));
	}

	// Blend from full spectrum to black
	for (int a = 255; a > 2; a -= 2)
	{
		// Convert blended 16 bit colour to 8 bits to reduce colour resolution, then map back to 16 bits for displaying
		for (int c = 0; c < 192; c++)
			tft.drawPixel(c, 128 + (255 - a) / 2, tft.color8to16(tft.color16to8(tft.alphaBlend(a, rainbow(c), 0))));
	}

	// Blend from white to black (4 grey levels - it will draw 4 more with a blue tinge due to lower blue bit count)
	// Blend from black to a primary colour
	for (uint16_t a = 0; a < 255; a++) // Alpha 0 = 100% background, alpha 255 = 100% foreground
	{
		tft.drawFastHLine(192, a, 12, tft.color8to16(tft.color16to8(tft.alphaBlend(a, TFT_BLACK, TFT_WHITE))));
		tft.drawFastHLine(204, a, 12, tft.color8to16(tft.color16to8(tft.alphaBlend(a, TFT_BLACK, TFT_RED))));
		tft.drawFastHLine(216, a, 12, tft.color8to16(tft.color16to8(tft.alphaBlend(a, TFT_BLACK, TFT_GREEN))));
		tft.drawFastHLine(228, a, 12, tft.color8to16(tft.color16to8(tft.alphaBlend(a, TFT_BLACK, TFT_BLUE))));
	}

	delay(4000);
}

// #########################################################################
// Return a 16 bit rainbow colour
// #########################################################################
unsigned int rainbow(byte value)
{
	// If 'value' is in the range 0-159 it is converted to a spectrum colour
	// from 0 = red through to 127 = blue to 159 = violet
	// Extending the range to 0-191 adds a further violet to red band

	value = value % 192;

	byte red = 0;	// Red is the top 5 bits of a 16 bit colour value
	byte green = 0; // Green is the middle 6 bits, but only top 5 bits used here
	byte blue = 0;	// Blue is the bottom 5 bits

	byte sector = value >> 5;
	byte amplit = value & 0x1F;

	switch (sector)
	{
	case 0:
		red = 0x1F;
		green = amplit; // Green ramps up
		blue = 0;
		break;
	case 1:
		red = 0x1F - amplit; // Red ramps down
		green = 0x1F;
		blue = 0;
		break;
	case 2:
		red = 0;
		green = 0x1F;
		blue = amplit; // Blue ramps up
		break;
	case 3:
		red = 0;
		green = 0x1F - amplit; // Green ramps down
		blue = 0x1F;
		break;
	case 4:
		red = amplit; // Red ramps up
		green = 0;
		blue = 0x1F;
		break;
	case 5:
		red = 0x1F;
		green = 0;
		blue = 0x1F - amplit; // Blue ramps down
		break;
	}

	return red << 11 | green << 6 | blue;
}
