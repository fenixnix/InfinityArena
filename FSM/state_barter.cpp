#include "state_barter.h"
#include "global.h"
#include "itemlayout.h"

using namespace CEGUI;
Container* State_Barter::A = nullptr;
Container* State_Barter::B = nullptr;

State_Barter::State_Barter()
{

}

bool State_Barter::onEnter()
{
    updateUI();
    return true;
}

void State_Barter::setContainer(Container *a, Container *b)
{
    A = a;
    B = b;
}

void State_Barter::updateUI()
{
    using namespace CEGUI;
    WindowManager& winMgr = WindowManager::getSingleton();
    winMgr.destroyAllWindows();
    Window* guiRoot = winMgr.loadLayoutFromFile( "IC_Barter.layout" );
    System::getSingleton().getDefaultGUIContext().setRootWindow( guiRoot );
    ItemLayout::itemLayout(guiRoot->getChild("FrameA"),A,State_Barter::buttonClickAItem);
    ItemLayout::itemLayout(guiRoot->getChild("FrameB"),B,State_Barter::buttonClickBItem);
}

void State_Barter::buttonClickAItem(const EventArgs &evt)
{
    cout<<__FUNCTION__<<":";
    const WindowEventArgs& wea = static_cast<const WindowEventArgs&>(evt);
    cout<<wea.window->getID();
    cout<<endl;
    Item *itm = A->take(wea.window->getID());
    if(itm){
        Item * itmt = B->put(itm);
        if(itmt){
            A->put(itmt);
        }
        updateUI();
    }
}

void State_Barter::buttonClickBItem(const EventArgs &evt)
{
    cout<<__FUNCTION__<<":";
    const WindowEventArgs& wea = static_cast<const WindowEventArgs&>(evt);
    cout<<wea.window->getID();
    cout<<endl;
    Item *itm = B->take(wea.window->getID());
    if(itm){
        Item * itmt = A->put(itm);
        if(itmt){
            B->put(itmt);
        }
        updateUI();
    }
}
