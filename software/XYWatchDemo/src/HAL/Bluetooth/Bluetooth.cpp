#include "./XYWatch_hal.h"

#define NameBufSize 200
//BluetoothSerial *SerialBT = nullptr;

/* const char *Bluetooth_Pin = "1234";
static char Namebuf[NameBufSize];
static uint16_t BufCount; */
static bool connected;

/*void btAdvertisedDeviceFound(BTAdvertisedDevice *pDevice)
{
    Serial.printf("Found a device asynchronously: %s\n", pDevice->toString().c_str());
}*/

void XYWatch::Bluetooth_Init(String Name)
{
    /*   SerialBT = new BluetoothSerial();
    SerialBT->begin(Name, true);
    SerialBT->~BluetoothSerial(); */
}

void XYWatch::Bluetooth_Scan(char *Str, int Time)
{
    //Serial.println("Starting discover...");
    //BTScanResults *pResults = SerialBT.discover(Time);
    /*   if (pResults)
        pResults->dump(&Serial);
    else
        Serial.println("Error on BT Scan, no result!");
 */
    //return 0;
}

bool XYWatch::Bluetooth_Connect(String Name)
{
    //connected = SerialBT->connect(Name);
    return connected;
}

void XYWatch::Bluetooth_Stop(void)
{
    //SerialBT->disconnect();
}
/* BluetoothSerial XYWatch::Bluetooth_Serial(void)
{
    return SerialBT;
}
 */