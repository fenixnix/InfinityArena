#include "state_mainui.h"
#include "ic_map.h"
#include "global.h"
#include "input.h"
#include "state_dungeon.h"
#include <sdl2_game.h>
#include <gui/ngui.h>

State_MainUI::State_MainUI()
{

}

void State_MainUI::update()
{
    Input::Instance()->update();
}

void State_MainUI::render()
{
    NGUI::the()->draw();
}

bool State_MainUI::onEnter()
{
    cout<<__FUNCTION__<<endl;
    NGLRender *r = NGLRender::the();
    NGLWindow * w = r->setCurrent(NGLRender::windowGame);
    using namespace CEGUI;
    Window* myRoot = WindowManager::getSingleton().loadLayoutFromFile( "infinityChaos.layout" );
    System::getSingleton().getDefaultGUIContext().setRootWindow( myRoot );
    myRoot->getChild("FrameWindow/ButtonNew")->subscribeEvent(CEGUI::Window::EventMouseClick,Event::Subscriber(&State_MainUI::buttonNew));
    myRoot->getChild("FrameWindow/ButtonQuit")->subscribeEvent(CEGUI::Window::EventMouseClick,Event::Subscriber(&State_MainUI::buttonQuit));
    return true;
}

bool State_MainUI::onExit()
{
    cout<<__FUNCTION__<<endl;
    using namespace CEGUI;
    WindowManager::getSingleton().destroyAllWindows();
    return true;
}

void State_MainUI::buttonNew(const CEGUI::EventArgs &)
{
    cout <<__FUNCTION__<<endl;
    FSM::the()->popState();
    FSM::the()->del("mainUI");
    string type = IC_Map::getType(Global::the()->world.currentMapFileName());
    if(type == string("dungeon")){
        FSM::the()->add(new State_Dungeon);
    }
//    if(type == string("surface")){
//        FSM::the()->add(new State_Surface);
//    }
}

void State_MainUI::buttonQuit(const CEGUI::EventArgs &)
{
    cout <<__FUNCTION__<<endl;
    SDL2_Game::the()->isRuning = false;
}
