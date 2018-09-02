#include "itemlayout.h"
using namespace CEGUI;

ItemLayout::ItemLayout()
{

}

void ItemLayout::itemLayout(Window *win, Container *bag,FunPtr funPtr)
{
    WindowManager& winMgr = WindowManager::getSingleton();
    const int cols = 8;
    for(int i = 0;i<bag->size();i++){
        Window* ico = winMgr.createWindow("TaharezLook/StaticImage");
        ico->setPosition( UVector2( UDim( ((float)(i%cols)*(1.0f/(float)cols)), 0.0f ), UDim( ((float)(i/cols)*0.125), 0.0f ) ) );
        //    // set size to be half the size of the parent
        ico->setSize( USize( UDim( (1.0f/(float)cols), 0.0f ), UDim( 0.125f, 0.0f ) ) );
        Window* label = winMgr.createWindow("TaharezLook/Label");
        label->setID(i);
        label->setPosition( UVector2( UDim( 0.0f, 0.0f ), UDim( 0.0f, 0.0f ) ) );
        label->setSize( USize( UDim( 1.0f, 0.0f ), UDim( 1.0f, 0.0f ) ) );
        Item* itm = bag->at(i);
        if(itm){
            ostringstream os;
            os<<itm->getDrawID();
            if(itm->isCommon()){
                Item_Common* itmc = Item_Common::convert(itm);
                os<<" "<<itmc->stackCount;
            }
            label->setText(os.str());
        }
        ico->addChild(label);
        label->subscribeEvent(CEGUI::Window::EventActivated,CEGUI::Event::Subscriber(funPtr));
        win->addChild(ico);
    }
}
