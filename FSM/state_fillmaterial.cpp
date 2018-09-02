#include "state_fillmaterial.h"
#include <render/nglrender.h>
#include <global.h>
#include "itemlayout.h"

using namespace CEGUI;
MaterialList* ml;

State_FillMaterial::State_FillMaterial()
{

}

void State_FillMaterial::update()
{

}

void State_FillMaterial::render()
{

}

bool State_FillMaterial::onEnter()
{
    updateUI();
    return true;
}

bool State_FillMaterial::onExit()
{
    return true;
}

void State_FillMaterial::setMaterialList(MaterialList *m)
{
    ml = m;
}

bool State_FillMaterial::injectKeyDown(int keyCode)
{
    cout<<__FUNCTION__<<keyCode<<endl;
    if(keyCode == SDL_SCANCODE_ESCAPE){
        FSM::the()->popState();
        return true;
    }
    return false;
}

void State_FillMaterial::updateUI()
{
    WindowManager& winMgr = WindowManager::getSingleton();
    winMgr.destroyAllWindows();
    Window* guiRoot = winMgr.loadLayoutFromFile( "IC_FillMaterial.layout" );
    System::getSingleton().getDefaultGUIContext().setRootWindow( guiRoot );

    int i = 0;
    for(auto itr = ml->mtls.begin();itr!=ml->mtls.end();itr++){
        Window* ico = winMgr.createWindow("TaharezLook/StaticImage");
        ico->setPosition( UVector2( UDim(0.05f, 0.0f ), UDim( (((float)i/8.0)*0.5)+0.05f, 0.0f ) ) );
        ico->setSize( USize( UDim( 0.90f, 0.0f ), UDim( 0.08f, 0.0f ) ) );
        Window* label = winMgr.createWindow("TaharezLook/Label");
        label->setID(i);
        label->setPosition( UVector2( UDim( 0.0f, 0.0f ), UDim( 0.0f, 0.0f ) ) );
        label->setSize( USize( UDim( 1.0f, 0.0f ), UDim( 1.0f, 0.0f ) ) );

        ostringstream os;
        os<<ItemFactory::the()->getItemName(itr->first)<<":"<<itr->second.cnt<<"/"<<itr->second.max;
        label->setText(os.str());
        ico->addChild(label);

        guiRoot->getChild("Material")->addChild(ico);
        i++;
    }
    Container* bag = &Global::the()->world.avatarObj->bag;
    ItemLayout::itemLayout(guiRoot->getChild("Inventory"),bag,&State_FillMaterial::buttonClickItem);
    guiRoot->getChild("Inventory")->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,Event::Subscriber(&State_FillMaterial::buttonClose));
}

void State_FillMaterial::buttonClickItem(const EventArgs &evt)
{
    cout<<__FUNCTION__<<":";
    using namespace CEGUI;
    const WindowEventArgs& wea = static_cast<const WindowEventArgs&>(evt);
    cout<<wea.window->getID();
    cout<<endl;
    Container* bag = &Global::the()->world.avatarObj->bag;
    Item *itm = bag->take(wea.window->getID());
    if(itm){
        if(itm->isCommon()){
            Item_Common *itc = ml->addMaterial(Item_Common::convert(itm));
            if(itc){
                bag->put(itc);
            }
        }else{
            bag->put(itm);
        }
        updateUI();
    }
}

void State_FillMaterial::buttonClose(const EventArgs &)
{
    FSM::the()->popState();
}
