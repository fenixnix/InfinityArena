#ifndef STATE_PUTBUILDING_H
#define STATE_PUTBUILDING_H

#include <FSM/finitystate.h>

class State_PutBuilding : public FinityState
{
public:
    State_PutBuilding();
    void update();
    void render();
    bool onEnter();
    bool onExit();
    bool injectKeyDown(int keyCode);
    bool injectMouseClick();
    std::string getStateID(){
        return "putBuilding";
    }
    void setID(string id);
private:
    static string selectedID;
};

#endif // STATE_PUTBUILDING_H
