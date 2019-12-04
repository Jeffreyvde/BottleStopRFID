#include "serialState.h"

SerialState::SerialState(RFID* rfid){
    this->rfid = rfid;
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
    if(rfid->isRFIDAvailable())
    {
        Serial.print(rfid->getID());
        state = Connected;
    }
}

//Listen for a cancel event or if the bottle is no longer there
void SerialState::Listen()
{
    if(!rfid->isRFIDAvailable()){
        state = Canceling;
    }else if(Serial.available() > 0){
         String message = Serial.readStringUntil('\n');
         if(message == cancelRequest)
            state = Canceling;
    }
}

//Send cancel event
void SerialState::Cancel()
{
    Serial.write("Cancel"); 
    state = Scanning;
}