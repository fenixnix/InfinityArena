#ifndef STATE_INVENTORY_H
#define STATE_INVENTORY_H

#include "fsm/finitystate.h"
#include <CEGUI/CEGUI.h>

class State_Inventory : public FinityState
{
public:
    State_Inventory();
    void update();
    void render();
    bool onEnter();
    bool onExit();
    std::string getStateID(){
        return "inventory";
    }
    bool injectKeyDown(int keyCode);
private:
    static void updateUI();
    static void buttonClickItem(const CEGUI::EventArgs&);
//    static void buttonSave(const CEGUI::EventArgs&);
//    static void buttonSetting(const CEGUI::EventArgs&);
    static void buttonClose(const CEGUI::EventArgs&);
};

#endif // STATE_INVENTORY_H
