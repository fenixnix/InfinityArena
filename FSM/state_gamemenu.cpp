#include "state_gamemenu.h"
#include <CEGUI/CEGUI.h>
#include <render/nglrender.h>
#include <global.h>
#include <fsm/state_mainui.h>

State_GameMenu::State_GameMenu()
{

}

void State_GameMenu::update()
{

}

void State_GameMenu::render()
{
//    NGLRender *r = &SDL_Render::the()->nglRender;
//    r->beginRender();
//    NGLWindow * w = r->setCurrent(NGLRender::windowGame);
//    NGUI::the()->draw();
//    w->swap();
//    r->endRender();
}

bool State_GameMenu::onEnter()
{
    using namespace CEGUI;
    Window* guiRoot =  WindowManager::getSingleton().loadLayoutFromFile( "IC_gamemenu.layout" );
    System::getSingleton().getDefaultGUIContext().setRootWindow( guiRoot );
    guiRoot->getChild("FrameWindow/ButtonResume")->subscribeEvent(CEGUI::Window::EventMouseClick,Event::Subscriber(&State_GameMenu::buttonResume));
    guiRoot->getChild("FrameWindow")->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,Event::Subscriber(&State_GameMenu::buttonResume));
    guiRoot->getChild("FrameWindow/ButtonQuit")->subscribeEvent(CEGUI::Window::EventMouseClick,Event::Subscriber(&State_GameMenu::buttonQuit));
    return true;
}

bool State_GameMenu::onExit()
{
    return true;
}

void State_GameMenu::buttonResume(const CEGUI::EventArgs &)
{
    FSM::the()->popState();
}

void State_GameMenu::buttonQuit(const CEGUI::EventArgs &)
{
    FSM::the()->delAll();
    FSM::the()->popState();
    FSM::the()->popState();
    FSM::the()->pushState(new State_MainUI);
}
