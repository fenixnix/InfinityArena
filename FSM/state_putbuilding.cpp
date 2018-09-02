#include "state_putbuilding.h"
#include "Build/buildingfactory.h"
#include "global.h"
#include "avatar.h"
#include "SDL.h"
#include "ic_map.h"

string State_PutBuilding::selectedID;
int dw,dh;
bool ok;
float cx,cy;

using namespace CEGUI;

State_PutBuilding::State_PutBuilding()
{

}

void State_PutBuilding::update()
{

}

void State_PutBuilding::render()
{
    NGLRender *r = NGLRender::the();
    //r->beginRender();
    //NGLWindow * w = r->setCurrent(NGLRender::windowGame);
//    w->setPerspectiveView();
//    r->setVP(w);
//    Avatar::the()->drawN();

    float mx,my,mz;
    r->getMousePos(mx,my,mz);

    int tlx,tly;
    IC_Map::getFloorSpace(mx,my,dw,dh,cx,cy,tlx,tly);
    r->setMode(MODE_GEO);
    float clr[] = {1,0,0,0.7};
    float clg[] = {0,1,0,0.7};
    ok = true;
    for(int y = 0;y<dh;y++){
        for(int x = 0;x<dw;x++){
            Building* b = IC_Map::Instance()->takeBuilding(tlx+x,tly+y);
            if(b){
                r->drawRect(tlx+x,tly+y,0.1,0.9,0.9,clr,GL_LINE_LOOP);
                ok = false;
            }else{
                r->drawRect(tlx+x,tly+y,0.1,0.9,0.9,clg,GL_LINE_LOOP);
            }
        }
    }
}

bool State_PutBuilding::onEnter()
{
    WindowManager::getSingleton().destroyAllWindows();
    BuildingPrepare bp = BuildingFactory::the()->buildingPrefabs[selectedID];
    cout<<bp.w<<"*"<<bp.h<<endl;
    dw = bp.w;
    dh = bp.h;
    return true;
}

bool State_PutBuilding::onExit()
{
    return true;
}

bool State_PutBuilding::injectKeyDown(int keyCode)
{
    cout<<__FUNCTION__<<keyCode<<endl;
    if(keyCode == SDL_SCANCODE_ESCAPE){
        FSM::the()->popState();
        return true;
    }
    return false;
}

bool State_PutBuilding::injectMouseClick()
{
    if(ok){
        BuildingFactory::the()->createPrefab(selectedID,cx,cy);
    }
    return true;
}

void State_PutBuilding::setID(string id)
{
    selectedID = id;
}
