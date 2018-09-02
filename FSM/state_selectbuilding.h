#ifndef STATE_SELECTBUILDING_H
#define STATE_SELECTBUILDING_H

#include "fsm/finitystate.h"
#include <CEGUI/CEGUI.h>

using namespace std;

class State_SelectBuilding : public FinityState
{
public:
    State_SelectBuilding();
    void update();
    void render();
    bool onEnter();
    bool onExit();
    std::string getStateID(){
        return "selectBuilding";
    }
    bool injectKeyDown(int keyCode);
private:
    static void buttonSelectBuilding(const CEGUI::EventArgs&);
    static void buttonOK(const CEGUI::EventArgs&);
    static void buttonClose(const CEGUI::EventArgs&);
    static string selectedID;
};

#endif // STATE_SELECTBUILDING_H
