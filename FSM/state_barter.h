#ifndef STATE_BARTER_H
#define STATE_BARTER_H

#include "fsm/stateuibase.h"
#include "container.h"

class State_Barter : public StateUIBase
{
public:
    State_Barter();
    bool onEnter();
    std::string getStateID(){
        return "barter";
    }
    void setContainer(Container* a,Container *b);
private:
    static Container* A;
    static Container* B;
    static void updateUI();
    static void buttonClickAItem(const CEGUI::EventArgs&);
    static void buttonClickBItem(const CEGUI::EventArgs&);
    static void buttonClose(const CEGUI::EventArgs&);
};

#endif // STATE_BARTER_H
