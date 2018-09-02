#ifndef STATE_MAINUI_H
#define STATE_MAINUI_H

#include "fsm/finitystate.h"
#include <CEGUI/CEGUI.h>

class State_MainUI : public FinityState
{
public:
    State_MainUI();
    void update();
    void updateTip();
    void render();
    bool onEnter();
    bool onExit();
    std::string getStateID(){
        return "mainUI";
    }

    static void buttonNew(const CEGUI::EventArgs&);
    static void buttonQuit(const CEGUI::EventArgs&);
};

#endif // STATE_MAINUI_H
