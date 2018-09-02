#ifndef STATE_DUNGEON_H
#define STATE_DUNGEON_H

#include "fsm/finitystate.h"

class State_Dungeon : public FinityState
{
public:
    State_Dungeon();
    void update();
    void render();
    bool onEnter();
    bool onExit();
    std::string getStateID(){
        return "dungeon";
    }
};

#endif // STATE_DUNGEON_H
