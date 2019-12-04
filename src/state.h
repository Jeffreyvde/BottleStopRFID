class State
{
protected:
    int state;

public:
    State();
    State(int state);

    //Handle the state
    virtual void handle();
};

