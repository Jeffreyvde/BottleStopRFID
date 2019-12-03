#include "Arduino.h"
#include "RFID.h"

RFID *rfid;

const int rstPin = 5, ssPin = 10;

void setup()
{
  Serial.begin(9600);

  rfid = new RFID(rstPin, ssPin);
}

void loop()
{
  if (rfid->checkID())
  {
    Serial.println(rfid->lastBottleID);
    Serial.println(sizeof(rfid->lastBottleID));
  }
}