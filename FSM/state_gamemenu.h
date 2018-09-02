#ifndef STATE_GAMEMENU_H
#define STATE_GAMEMENU_H

#include "fsm/finitystate.h"
#include <CEGUI/CEGUI.h>

class State_GameMenu : public FinityState
{
public:
    State_GameMenu();
    void update();
    void render();
    bool onEnter();
    bool onExit();
    std::string getStateID(){
        return "gameMenu";
    }
private:
    static void buttonResume(const CEGUI::EventArgs&);
    //static void buttonSave(const CEGUI::EventArgs&);
    //static void buttonSetting(const CEGUI::EventArgs&);
    static void buttonQuit(const CEGUI::EventArgs&);

};

#endif // STATE_GAMEMENU_H
