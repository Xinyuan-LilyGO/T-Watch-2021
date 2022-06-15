# 1 "d:\\Users\\19021\\Documents\\Arduino\\libraries\\TinyGPSPlus\\examples\\DeviceExample\\DeviceExample.ino"
# 2 "d:\\Users\\19021\\Documents\\Arduino\\libraries\\TinyGPSPlus\\examples\\DeviceExample\\DeviceExample.ino" 2
# 3 "d:\\Users\\19021\\Documents\\Arduino\\libraries\\TinyGPSPlus\\examples\\DeviceExample\\DeviceExample.ino" 2
/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 21, TXPin = 22;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  pinMode(23, 0x02);
  digitalWrite(23, 1);
  Serial.begin(115200);
  ss.begin(GPSBaud);
  delay(100);
  Serial.println(((reinterpret_cast<const __FlashStringHelper *>(("DeviceExample.ino")))));
  Serial.println(((reinterpret_cast<const __FlashStringHelper *>(("A simple demonstration of TinyGPS++ with an attached GPS module")))));
  Serial.print(((reinterpret_cast<const __FlashStringHelper *>(("Testing TinyGPS++ library v. ")))));
  Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(((reinterpret_cast<const __FlashStringHelper *>(("by Mikal Hart")))));
  Serial.println();
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(((reinterpret_cast<const __FlashStringHelper *>(("No GPS detected: check wiring.")))));
    while (true)
      ;
  }
}

void displayInfo()
{
  Serial.print(((reinterpret_cast<const __FlashStringHelper *>(("Location: ")))));
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(((reinterpret_cast<const __FlashStringHelper *>((",")))));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(((reinterpret_cast<const __FlashStringHelper *>(("INVALID")))));
  }

  Serial.print(((reinterpret_cast<const __FlashStringHelper *>(("  Date/Time: ")))));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(((reinterpret_cast<const __FlashStringHelper *>(("/")))));
    Serial.print(gps.date.day());
    Serial.print(((reinterpret_cast<const __FlashStringHelper *>(("/")))));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(((reinterpret_cast<const __FlashStringHelper *>(("INVALID")))));
  }

  Serial.print(((reinterpret_cast<const __FlashStringHelper *>((" ")))));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10)
      Serial.print(((reinterpret_cast<const __FlashStringHelper *>(("0")))));
    Serial.print(gps.time.hour());
    Serial.print(((reinterpret_cast<const __FlashStringHelper *>((":")))));
    if (gps.time.minute() < 10)
      Serial.print(((reinterpret_cast<const __FlashStringHelper *>(("0")))));
    Serial.print(gps.time.minute());
    Serial.print(((reinterpret_cast<const __FlashStringHelper *>((":")))));
    if (gps.time.second() < 10)
      Serial.print(((reinterpret_cast<const __FlashStringHelper *>(("0")))));
    Serial.print(gps.time.second());
    Serial.print(((reinterpret_cast<const __FlashStringHelper *>((".")))));
    if (gps.time.centisecond() < 10)
      Serial.print(((reinterpret_cast<const __FlashStringHelper *>(("0")))));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(((reinterpret_cast<const __FlashStringHelper *>(("INVALID")))));
  }

  Serial.println();
}
