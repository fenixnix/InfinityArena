#include "building_Storage.h"
#include "buildingfactory.h"
#include "render/nglrender.h"
#include "FSM/state_barter.h"
#include "global.h"

Building_Storage::Building_Storage()
{
    type = "Storage";
}

Building *Building_Storage::create(string id,float x, float y)
{
    Building_Storage* bd = new Building_Storage;
    bd->type = string("Storage");
    bd->x = x;
    bd->y = y;
    BuildingPrepare *bpfab = &(BuildingFactory::the()->buildingPrefabs[id]);
    bd->w = bpfab->w;
    bd->h = bpfab->h;
    bd->dimension = 0.3;
    bd->maxHp = bpfab->maxHp;
    bd->hp = bd->maxHp;
    bd->id = bpfab->name;
    bd->drawID = bpfab->name;
    bd->outputItems.init(12);
    return dynamic_cast<Building*>(bd);
}

void Building_Storage::draw()
{
    //cout<<__FUNCTION__<<drawID<<endl;
    NGLRender* render = NGLRender::the();
    render->setMode(MODE_GEO);
    float cl[] = {1,1,0,0.7};
    render->drawRect(x,y,0.1,dimension,dimension,cl);
    render->setMode(MODE_SPRITE);
    render->drawTextSprite(drawID,x,y,0.5,128);
}

void Building_Storage::operate()
{
    cout<<__FUNCTION__<<endl;
    State_Barter* s = new State_Barter;
    s->setContainer(&outputItems,&Global::the()->world.avatarObj->bag);
    FSM::the()->pushState(s);
}

void Building_Storage::createPhyx()
{
    body = B2Physx::the()->createStaticBox(x,y,dimension,dimension,NULL);
}

