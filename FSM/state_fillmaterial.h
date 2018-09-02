#ifndef STATE_FILLMATERIAL_H
#define STATE_FILLMATERIAL_H

#include "FSM/finitystate.h"
#include <CEGUI/CEGUI.h>
#include "container.h"
#include "materiallist.h"

class State_FillMaterial : public FinityState
{
public:
    State_FillMaterial();
    void update();
    void render();
    bool onEnter();
    bool onExit();
    std::string getStateID(){
        return "inventory";
    }
    void setMaterialList(MaterialList* m);
    bool injectKeyDown(int keyCode);
private:
    static void updateUI();
    static void buttonClickItem(const CEGUI::EventArgs&);
    static void buttonClose(const CEGUI::EventArgs&);
};

#endif // STATE_FILLMATERIAL_H
