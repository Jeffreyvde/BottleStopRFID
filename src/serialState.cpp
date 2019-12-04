#include "serialState.h"

SerialState::SerialState(RFID rfid){
    this->rfid = rfid;
}

void SerialState::handle()
{
    switch (static_cast<SerialStates>(state))
    {
        case Scanning:
            Scan();
            break;
        case Connected:
            Listen();
            break;
        case CancelState:
            Cancel();
            break;
    }


}