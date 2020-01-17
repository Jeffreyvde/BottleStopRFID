#include "serialState.h"
#include "Arduino.h"

SerialState::SerialState(RFID* rfid){
    this->rfid = rfid;
    state = Scanning;
}

void SerialState::handle()
{
    switch (state)
    {
        case Scanning:
            Scan();
            break;
        case Connected:
            Listen();
            break;
        case Canceling:
            Cancel();
            break;
    }
}

//Scan for a bottle
void SerialState::Scan()
{
    if(rfid->isRFIDAvailable() == 2)
    {
        String data = "ID" + String(split) + rfid->getID();
        SendData(data);
        state = Connected;
    }
}

//Listen for a cancel event or if the bottle is no longer there
void SerialState::Listen()
{
    if(rfid->isRFIDAvailable() == 0){
        state = Canceling;
    }else if(Serial.available() > 0){
         String message = Serial.readStringUntil(end);
         if(*message.begin() == start)
         {
            if(CompareSerial(message, cancelRequest))
                state = Canceling;
         }
    }
}

//Send cancel event
void SerialState::Cancel()
{
    SendData(cancelRequest); 
    state = Scanning;
}

//Send datat on serial
void SerialState::SendData(String message)
{
    Serial.print(start + message + end);
}

//Check if received serial data is the same as comparison
bool SerialState::CompareSerial(String serial, String comparison)
{
    serial.remove(0);
    serial.remove(serial.length());

    return serial == comparison;
}