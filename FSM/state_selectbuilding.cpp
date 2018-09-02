#include "state_selectbuilding.h"
#include <render/nglrender.h>
#include <Build/buildingfactory.h>
#include <global.h>
#include <FSM/state_putbuilding.h>

string State_SelectBuilding::selectedID = "";

using namespace CEGUI;

State_SelectBuilding::State_SelectBuilding()
{

}

void State_SelectBuilding::update()
{

}

void State_SelectBuilding::render()
{
//    NGLRender *r = &SDL_Render::the()->nglRender;
//    r->beginRender();
//    NGLWindow * w = r->setCurrent(NGLRender::windowGame);
//    NGUI::the()->draw();
//    w->swap();
//    r->endRender();
}

bool State_SelectBuilding::onEnter()
{
    cout<<__FUNCTION__<<endl;
    using namespace CEGUI;
    WindowManager& winMgr = WindowManager::getSingleton();
    Window *guiRoot = winMgr.loadLayoutFromFile( "IC_SelectBuilding.layout" );
    System::getSingleton().getDefaultGUIContext().setRootWindow( guiRoot );

    //Avatar::human->bag.
    TabControl *tabCtrl = static_cast<TabControl *>(guiRoot->getChild("FrameWindow/TabControl"));

    Window* tabProduction = winMgr.createWindow("DefaultWindow");
    tabProduction->setName("Production");
    tabProduction->setText("Production");
    vector<string> productionList = BuildingFactory::the()->getProductionBuildList();
    for(int i = 0;i<productionList.size();i++){
        Window* ico = winMgr.createWindow("TaharezLook/StaticImage");
        ico->setPosition( UVector2( UDim( ((float)(i%8)*0.1)+0.05f, 0.0f ), UDim( ((float)(i/8)*0.1)+0.05f, 0.0f ) ) );
        ico->setSize( USize( UDim( 0.08f, 0.0f ), UDim( 0.08f, 0.0f ) ) );
        Window* label = winMgr.createWindow("TaharezLook/Label");
        label->setID(i);
        label->setPosition( UVector2( UDim( 0.0f, 0.0f ), UDim( 0.0f, 0.0f ) ) );
        label->setSize( USize( UDim( 1.0f, 0.0f ), UDim( 1.0f, 0.0f ) ) );
        label->setText(productionList[i]);
        ico->addChild(label);
        label->subscribeEvent(CEGUI::Window::EventActivated,Event::Subscriber(&State_SelectBuilding::buttonSelectBuilding));
        label->subscribeEvent(CEGUI::Window::EventMouseDoubleClick,Event::Subscriber(&State_SelectBuilding::buttonOK));
        tabProduction->addChild(ico);
    }
    tabCtrl->addTab(tabProduction);
    Window* tabMilitary = winMgr.createWindow("DefaultWindow");
    tabMilitary->setName("Military");
    tabMilitary->setText("Military");
    vector<string> militaryList = BuildingFactory::the()->getMilitaryBuildList();
    for(int i = 0;i<militaryList.size();i++){
        Window* ico = winMgr.createWindow("TaharezLook/StaticImage");
        ico->setPosition( UVector2( UDim( ((float)(i%8)*0.1)+0.05f, 0.0f ), UDim( ((float)(i/8)*0.1)+0.05f, 0.0f ) ) );
        ico->setSize( USize( UDim( 0.08f, 0.0f ), UDim( 0.08f, 0.0f ) ) );
        Window* label = winMgr.createWindow("TaharezLook/Label");
        label->setID(i);
        label->setPosition( UVector2( UDim( 0.0f, 0.0f ), UDim( 0.0f, 0.0f ) ) );
        label->setSize( USize( UDim( 1.0f, 0.0f ), UDim( 1.0f, 0.0f ) ) );
        label->setText(militaryList[i]);
        ico->addChild(label);
        label->subscribeEvent(CEGUI::Window::EventActivated,Event::Subscriber(&State_SelectBuilding::buttonSelectBuilding));
        label->subscribeEvent(CEGUI::Window::EventMouseDoubleClick,Event::Subscriber(&State_SelectBuilding::buttonOK));
        tabMilitary->addChild(ico);
    }
    tabCtrl->addTab(tabMilitary);
    //tabCtrl->addTab(winMgr.loadLayoutFromFile("TabControlDemo.layout"));

    guiRoot->getChild("FrameWindow")->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,Event::Subscriber(&State_SelectBuilding::buttonClose));
    //guiRoot->getChild("Inventory")->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,Event::Subscriber(&State_Inventory::buttonClose));
    return true;
}

bool State_SelectBuilding::onExit()
{
    return true;
}

void State_SelectBuilding::buttonSelectBuilding(const CEGUI::EventArgs &evt)
{
    const WindowEventArgs& wea = static_cast<const WindowEventArgs&>(evt);
    ostringstream os;
    os<<wea.window->getText();
    string selectedID = os.str();
    cout<<selectedID;
    cout<<endl;
}

void State_SelectBuilding::buttonOK(const CEGUI::EventArgs &evt)
{
    cout<<__FUNCTION__<<endl;
    const WindowEventArgs& wea = static_cast<const WindowEventArgs&>(evt);
    ostringstream os;
    os<<wea.window->getText();
    string selectedID = os.str();
    cout<<selectedID;
    cout<<endl;
    State_PutBuilding* s = new State_PutBuilding;
    s->setID(selectedID);
    FSM::the()->pushState(s);
}

void State_SelectBuilding::buttonClose(const CEGUI::EventArgs &)
{
    FSM::the()->popState();
}

bool State_SelectBuilding::injectKeyDown(int keyCode)
{
    cout<<__FUNCTION__<<keyCode<<endl;
    if(keyCode == SDL_SCANCODE_ESCAPE){
        FSM::the()->popState();
        return true;
    }
    return false;
}
