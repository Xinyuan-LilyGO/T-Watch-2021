#include <Wire.h>
#include "CST816S.h"

CST816S Touch;
void setup(void)
{
    Serial.begin(115200);
    Wire.begin(26, 25);
    if (Touch.begin(Wire, 33, 32))
    {
        Serial.println("connect CST816S success");
    }
}

void loop(void)
{
    if (Touch.TouchInt())
    {
        uint16_t pdwSampleX, pdwSampleY;

        pdwSampleX = Touch.getX();
        pdwSampleY = Touch.getY();

        if (Data[1] == 0x00)
        {
            uint8_t touch_type = Touch.getTouchType();
            Serial.printf("touch_type = %x\r\n", touch_type);
            if (touch_type == 0x08)
            {
                Serial.printf("Touch press down  x = %d , y = %d\r\n", pdwSampleX, pdwSampleY);
            }
            else if (touch_type == 0x04)
            {
                Serial.printf("Touch press up  x = %d , y = %d\r\n", pdwSampleX, pdwSampleY);
            }
        }

        /* switch (Data[1])
        {
        case 0x00:
            Serial.println("No gesture");
            break;
        case 0x01:
            Serial.println("↑ ↑ ↑ ↑ ↑ ↑");
            break;
        case 0x02:
            Serial.println("↓ ↓ ↓ ↓ ↓ ↓");
            break;
        case 0x03:
            Serial.println("← ← ← ← ← ←");
            break;
        case 0x04:
            Serial.println("→ → → → → →");
            break;
        case 0x05:
            Serial.println("Click on");
            break;
        case 0x0B:
            Serial.println("Double click");
            break;
        case 0x0C:
            Serial.println("Press");
            break;
        default:
            break;
        } */
        /* Serial.print("Data[0] = ");
        Serial.println(Data[0]);
        Serial.print("Data[1] = ");
        Serial.println(Data[1]);
        Serial.print("Data[2] = ");
        Serial.println(Data[2]);
        Serial.print("Data[3] = ");
        Serial.println(Data[3]);
        Serial.print("Data[4] = ");
        Serial.println(Data[4]);
        Serial.print("Data[5] = ");
        Serial.println(Data[5]);
        Serial.print("Data[6] = ");
        Serial.println(Data[6]);
        Serial.print("Data[7] = ");
        Serial.println(Data[7]); */
    }
}
