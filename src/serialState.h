
#include "state.h"
#include "RFID.h"
enum SerialStates { Scanning = 0, Connected = 1, CancelState = 2};

class SerialState : public State<SerialStates>
{
public:
    SerialState(RFID rfid);

    //Handle the state
    void handle();

private:
    void Scan();
    void Listen();
    void Cancel();

    RFID rfid;


};

