#include "state_dungeon.h"
#include "ic_map.h"
#include "b2physx.h"
#include "avatar.h"
#include "objfactory.h"
#include "obj_human.h"
#include "obj_beast.h"
#include "render/nglrender.h"
#include "input.h"
#include "item/itemfactory.h"
#include "Build/buildingfactory.h"
#include "global.h"
#include "fsm/state_avatar.h"


State_Dungeon::State_Dungeon()
{
}

void State_Dungeon::update()
{
    //cout<<__FUNCTION__<<__LINE__<<endl;
    Input::Instance()->update();
    //cout<<__FUNCTION__<<__LINE__<<endl;
    B2Physx::the()->update();
    //cout<<__FUNCTION__<<__LINE__<<endl;
    ObjFactory::Instance()->update();
    //cout<<__FUNCTION__<<__LINE__<<endl;
    BuildingFactory::the()->update();
    //cout<<__FUNCTION__<<__LINE__<<endl;
}

void State_Dungeon::render()
{
    if(!Global::the()->world.updateAvatar()){
        cout<<"none avatar!!!"<<endl;
        return;
    }
    Avatar::the()->avatarID = Global::the()->world.avatarID;
    Avatar::the()->human = Global::the()->world.avatarObj;
    NGLRender *r = NGLRender::the();
    NGLWindow * w = r->getWindow(NGLRender::windowGame);
    w->setPerspectiveView();
    r->setVP(w);

    Avatar::the()->drawN();
    if(Global::the()->isDrawDebug){
        NGLRender* render = NGLRender::the();
        render->setMode(MODE_GEO);
        B2Physx::the()->render();
    }
    NGUI::the()->draw();

}

bool State_Dungeon::onEnter()
{
    cout<<__FUNCTION__<<endl;
    //IC_Map::Instance()->loadMap(Global::the()->world.currentMapFileName());
    IC_Map::Instance()->generateFromGaia(Global::the()->world.currentMapFileName());
    FSM::the()->del("surface");
    FSM::the()->pushState(new State_Avatar);
    return true;
}

bool State_Dungeon::onExit()
{
    cout<<__FUNCTION__<<endl;
    return true;
}

