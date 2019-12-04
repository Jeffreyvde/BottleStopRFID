//Must be an enum
template <typename T> 
class State
{
protected:
    T state;

public:

    //Handle the state
    virtual void handle();
};

