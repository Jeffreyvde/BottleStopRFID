
#include "state.h"

class SerialState : public State
{
public:
    SerialState();

    enum SerialStates { Scanning = 0, Listen = 1, Cancel = 2};

    //Handle the state
    void handle();
};

