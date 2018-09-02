#include "state_avatar.h"
#include "avatar.h"
#include "global.h"
#include "input.h"
#include "FSM/state_dungeon.h"
#include "FSM/state_gamemenu.h"
#include "FSM/state_inventory.h"
#include "FSM/state_SelectBuilding.h"
#include <CEGUI/CEGUI.h>

State_Avatar::State_Avatar()
{

}

void State_Avatar::update()
{
    //cout<<__FUNCTION__<<endl;
    if(!Global::the()->world.updateAvatar()){
        cout<<"none avatar!!!"<<endl;
        return;
    }
    Avatar::the()->avatarID = Global::the()->world.avatarID;
    Avatar::the()->human = Global::the()->world.avatarObj;

    Avatar::the()->update();

    if(Avatar::the()->human == nullptr){
        cout<<__FUNCTION__<<"null avatar"<<endl;
    }

    if(Input::Instance()->getKeyState(SDL_SCANCODE_Q)){
        NGLRender::the()->getWindow(NGLRender::windowGame)->rotateCamera(0.05f);
    }
    if(Input::Instance()->getKeyState(SDL_SCANCODE_E)){
        NGLRender::the()->getWindow(NGLRender::windowGame)->rotateCamera(-0.05f);
    }

    //    MapAccess ac;
    //    if(IC_Map::Instance()->checkAccess(Avatar::the()->human->locX,Avatar::the()->human->locY,ac)){
    //        cout<<__FUNCTION__<<": "<<"access to: "<<ac.id<<" sx:"<<ac.srcLoc.x<<" sy:"<<ac.srcLoc.y<<" x:"<<ac.dstLoc.x<<" y:"<<ac.dstLoc.y<<endl;
    //        Global::the()->world.currentMap = ac.id;
    //        FSM::the()->del("surface");
    //        FSM::the()->add(new State_Dungeon);
    //        //Avatar::Instance()->human->phyxBody->SetTransform(b2Vec2(ac.dstLoc.x,ac.dstLoc.y),0);
    //        Global::the()->world.setTeamPos(ac.dstLoc.x,ac.dstLoc.y);
    //    }
}

void State_Avatar::render()
{
    //cout<<__FUNCTION__<<endl;
    if(!Global::the()->world.updateAvatar()){
        cout<<"none avatar!!!"<<endl;
        return;
    }
    Avatar::the()->avatarID = Global::the()->world.avatarID;
    Avatar::the()->human = Global::the()->world.avatarObj;
    NGLRender* render = NGLRender::the();
    float mx,my,mz;
    render->getMousePos(mx,my,mz);
    render->setMode(MODE_GEO);
    float cl[] = {0,1,0,0.5};
    render->drawCircle(mx,my,0.1,0.1,cl,GL_LINE_LOOP);

    using namespace CEGUI;
    Window* guiRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
    Window* label = guiRoot->getChild("LabelInfo");
    if(label){
        label->setText(Avatar::the()->infoString);
    }

    Obj_Human* hum = Global::the()->world.avatarObj;
    {
        ostringstream os;
        os<<hum->life/hum->maxLife;
        guiRoot->getChild("BarLife")->setProperty("CurrentProgress",os.str());
    }
    {
        ostringstream os;
        os<<(hum->endurance/hum->maxEndurance);
        guiRoot->getChild("BarEndurance")->setProperty("CurrentProgress",os.str());
    }
    {
        ostringstream os;
        os<<(hum->stamina/hum->maxStamina);
        guiRoot->getChild("BarStamina")->setProperty("CurrentProgress",os.str());
    }

}

bool State_Avatar::onEnter()
{
    cout<<__FUNCTION__<<endl;
    FSM::the()->del("god");
    NGLRender *r = NGLRender::the();
    NGLWindow * win = r->setCurrent(NGLRender::windowGame);
    using namespace CEGUI;
    Window* guiRoot = WindowManager::getSingleton().loadLayoutFromFile( "IC_avatar.layout" );
    System::getSingleton().getDefaultGUIContext().setRootWindow( guiRoot );
    guiRoot->getChild("ButtonMenu")->subscribeEvent(CEGUI::Window::EventMouseClick,Event::Subscriber(&State_Avatar::buttonMenu));
    guiRoot->getChild("ButtonItem")->subscribeEvent(CEGUI::Window::EventMouseClick,Event::Subscriber(&State_Avatar::buttonItem));
    guiRoot->getChild("ButtonBuilding")->subscribeEvent(CEGUI::Window::EventMouseClick,Event::Subscriber(&State_Avatar::buttonBuilding));
    return true;
}

bool State_Avatar::onExit()
{
    return true;
}

void State_Avatar::buttonMenu(const CEGUI::EventArgs &)
{
    FSM::the()->pushState(new State_GameMenu);
}

void State_Avatar::buttonItem(const CEGUI::EventArgs &)
{
    FSM::the()->pushState(new State_Inventory);
}

void State_Avatar::buttonBuilding(const CEGUI::EventArgs &)
{
    FSM::the()->pushState(new State_SelectBuilding);
}
