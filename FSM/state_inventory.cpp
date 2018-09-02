#include "state_inventory.h"
#include <CEGUI/CEGUI.h>
#include <render/nglrender.h>
#include <global.h>
#include <avatar.h>
#include <itemlayout.h>

using namespace CEGUI;
Window* guiRoot;
Obj_Human* obj;

State_Inventory::State_Inventory()
{

}

void State_Inventory::update()
{

}

void State_Inventory::render()
{
//    NGLRender *r = &SDL_Render::the()->nglRender;
//    r->beginRender();
//    NGLWindow * w = r->setCurrent(NGLRender::windowGame);
//    NGUI::the()->draw();
//    w->swap();
//    r->endRender();
}

bool State_Inventory::onEnter()
{
    updateUI();
    return true;
}

bool State_Inventory::onExit()
{
    return true;
}

bool State_Inventory::injectKeyDown(int keyCode)
{
    cout<<__FUNCTION__<<keyCode<<endl;
    if(keyCode == SDL_SCANCODE_ESCAPE){
        FSM::the()->popState();
        return true;
    }
    return false;
}

void State_Inventory::updateUI()
{
    using namespace CEGUI;
    WindowManager& winMgr = WindowManager::getSingleton();
    winMgr.destroyAllWindows();
    guiRoot = winMgr.loadLayoutFromFile( "IC_Inventory.layout" );
    System::getSingleton().getDefaultGUIContext().setRootWindow( guiRoot );

    obj = Global::the()->world.avatarObj;
    Container* bag = &obj->bag;

    ItemLayout::itemLayout(guiRoot->getChild("Inventory"),bag,&State_Inventory::buttonClickItem);
    if(obj->mainhand){
    guiRoot->getChild("Equipment/MainHand")->setText(obj->mainhand->getDrawID());
    }
    if(obj->offhand){
    guiRoot->getChild("Equipment/OffHand")->setText(obj->offhand->getDrawID());
    }

    TabControl *tabCtrl = static_cast<TabControl *>(guiRoot->getChild("Craft/TabControl"));
    tabCtrl->addTab(winMgr.loadLayoutFromFile("TabControlDemo.layout"));

    guiRoot->getChild("Inventory")->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,Event::Subscriber(&State_Inventory::buttonClose));
}

void State_Inventory::buttonClickItem(const CEGUI::EventArgs & evt)
{
    cout<<__FUNCTION__<<":";
    using namespace CEGUI;
    const WindowEventArgs& wea = static_cast<const WindowEventArgs&>(evt);
    cout<<wea.window->getID();
    cout<<endl;

    int index = wea.window->getID();
    if(obj){
        Item* item = obj->bag.at(index);
        if(item){
            if(item->isWeapon()){
                cout<<__FUNCTION__<<__LINE__<<endl;
                //Item_MeleeWeapon* itm = Item_MeleeWeapon::convert(item);
                cout<<__FUNCTION__<<__LINE__<<endl;
                obj->bag.put(obj->mainhand);
                cout<<__FUNCTION__<<__LINE__<<endl;
                obj->mainhand = item;
                cout<<__FUNCTION__<<__LINE__<<endl;
                obj->bag.take(index);
                cout<<__FUNCTION__<<__LINE__<<endl;
            }
            if(item->getDrawID() == "arrow"){
                if(obj->mainhand){
                    if(obj->mainhand->getDrawID() == "Bow"){
                        cout<<__FUNCTION__<<__LINE__<<endl;
                        obj->bag.put(obj->offhand);
                        cout<<__FUNCTION__<<__LINE__<<endl;
                        obj->offhand = item;
                        cout<<__FUNCTION__<<__LINE__<<endl;
                        obj->bag.take(index);
                        cout<<__FUNCTION__<<__LINE__<<endl;
                    }
                }
            }
        }
    }
    updateUI();
}

void State_Inventory::buttonClose(const CEGUI::EventArgs &)
{
    FSM::the()->popState();
}
