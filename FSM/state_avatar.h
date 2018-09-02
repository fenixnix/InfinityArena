#ifndef STATE_AVATAR_H
#define STATE_AVATAR_H

#include "fsm/finitystate.h"
#include "Render/nglrender.h"
#include <CEGUI/CEGUI.h>

class State_Avatar : public FinityState
{
public:
    State_Avatar();
    void update();
    void render();
    bool onEnter();
    bool onExit();
    std::string getStateID(){
        return "avatar";
    }
private:
    static void buttonMenu(const CEGUI::EventArgs&);
    static void buttonItem(const CEGUI::EventArgs&);
    static void buttonCraft(const CEGUI::EventArgs&);
    static void buttonAvatar(const CEGUI::EventArgs&);
    static void buttonBuilding(const CEGUI::EventArgs&);
};

#endif // STATE_AVATAR_H
