#include "./apps/tools/Touch.h"
#include <math.h>

#include <gfx_util.h>
#include <osw_app.h>
#include <osw_hal.h>
#include <osw_pins.h>

uint16_t pdwSampleX = 0, pdwSampleY = 0;
uint16_t LastPdwSampleX = 0, LastPdwSampleY = 0;
uint8_t TouchMode = 1;
uint16_t BrushColor = 0xFFFF;

void OswAppTouch::drawTouchPad(OswHal *hal)
{
}

void OswAppTouch::setup(OswHal *hal)
{
}

void OswAppTouch::DrawingBoard(OswHal *hal)
{
    Graphics2D *gfx = hal->getCanvas()->getGraphics2D();
    if (hal->btnHasGoneDown(BUTTON_3))
    {
        hal->getCanvas()->fillScreen(ui->getBackgroundColor());
    }
    hal->Cst816s_Read();
    if (hal->Cst816s_GetType() == 0x01)
    {
        pdwSampleX = hal->Cst816s_GetX();
        pdwSampleY = hal->Cst816s_GetY();
        if (LastPdwSampleX == 0 && LastPdwSampleY == 0)
        {
            gfx->fillCircle(pdwSampleX, pdwSampleY, 3, BrushColor);
        }
        else
        {
            gfx->drawThickLine(LastPdwSampleX, LastPdwSampleY, pdwSampleX, pdwSampleY, 3, BrushColor);
        }
        LastPdwSampleX = pdwSampleX;
        LastPdwSampleY = pdwSampleY;
    }
    else
    {
        BrushColor = random(0x0001, 0xFFFF);
        LastPdwSampleX = 0;
        LastPdwSampleY = 0;
    }
}
void OswAppTouch::Coordinates(OswHal *hal)
{
    uint8_t temp = 0;
    hal->Cst816s_Read();
    hal->getCanvas()->fillScreen(ui->getBackgroundColor());
    if (hal->Cst816s_GetType() == 0x01)
    {
        pdwSampleX = hal->Cst816s_GetX();
        pdwSampleY = hal->Cst816s_GetY();
        temp = 1;
    }
    hal->getCanvas()->setTextColor(WHITE, BLACK);
    hal->getCanvas()->setTextSize(3);
    hal->getCanvas()->setCursor(20, 62);
    hal->getCanvas()->print("State :");
    hal->getCanvas()->setCursor(20, 86);
    if (temp)
    {
        hal->getCanvas()->setTextColor(GREEN, BLACK);
        hal->getCanvas()->print("Press down");
    }
    else
    {
        hal->getCanvas()->print("Release");
    }

    hal->getCanvas()->setCursor(20, 110);
    hal->getCanvas()->print("X :");
    hal->getCanvas()->print(pdwSampleX);
    hal->getCanvas()->setCursor(20, 134);
    hal->getCanvas()->print("Y :");
    hal->getCanvas()->print(pdwSampleY);
}
void OswAppTouch::loop(OswHal *hal)
{
    if (hal->btnHasGoneDown(BUTTON_2))
    {
        hal->getCanvas()->fillScreen(ui->getBackgroundColor());
        TouchMode = (TouchMode + 1) % 2;
    }
    switch (TouchMode)
    {
    case 0:
        DrawingBoard(hal);
        break;

    default:
        Coordinates(hal);
        break;
    }
    hal->requestFlush();
}

void OswAppTouch::stop(OswHal *hal) {}
