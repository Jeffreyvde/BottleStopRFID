#include "Arduino.h"
#include "RFID.h"
#include "serialState.h"

SerialState* stateMachine;


const int rstPin = 9, ssPin = 10;

void setup()
{
  Serial.begin(9600);
  stateMachine = new SerialState(new RFID(rstPin, ssPin));
}

void loop()
{
  stateMachine->handle();
}