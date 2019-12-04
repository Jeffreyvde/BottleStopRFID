
#include "state.h"
#include "RFID.h"

class SerialState : public State
{
public:
    SerialState(RFID rfid);

    enum SerialStates { Scanning = 0, Connected = 1, CancelState = 2};

    //Handle the state
    void handle();

private:
    void Scan();
    void Listen();
    void Cancel();

    RFID rfid;


};

