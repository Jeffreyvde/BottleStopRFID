
#include "state.h"
#include "RFID.h"
enum SerialStates { Scanning = 0, Connected = 1, Canceling = 2};

class SerialState : public State<SerialStates>
{
public:
    SerialState(RFID* rfid);

    //Handle the state
    void handle();

private:
    void Scan();
    void Listen();
    void Cancel();

    void SendData(String message);
    bool CompareSerial(String serial, String comparison);
    
    const String cancelRequest = "Cancel";

    RFID* rfid;

    const char start = '$', end = '=', split = ':';

};

