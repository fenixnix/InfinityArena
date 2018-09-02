#include "building_prefab.h"
#include "render/nglrender.h"
#include "buildingfactory.h"
#include "ic_map.h"
#include "global.h"
#include <FSM/state_fillmaterial.h>

Building_Prefab::Building_Prefab()
{
    build = NULL;
    buildingProcess = 1.0f;
    workload = 100;
    isPrefab = true;
    type = "Prefab";
    drawID = "site";
}

void Building_Prefab::draw()
{
    //cout<<__FUNCTION__<<endl;
    NGLRender* render = NGLRender::the();
    render->setMode(MODE_GEO);
    float cl[] = {0,0.5,0,0.7};
    render->drawRect(x,y,0.1,w,h,cl);
    render->setMode(MODE_SPRITE);
    ostringstream os;

    //os<<drawID;
    if(build){
        os<<this->build->drawID;
    }

    render->drawTextSprite("###",x,y,0.0,64);

    render->drawTextSprite(os.str(),x,y,0.5,128);


    if(isOperating){
        render->setMode(MODE_GEO);
        float cl[] = {0,1,0,0.5};
        float clc[] = {0,1,0,0.2};
        render->drawCircle(x,y,0.1,0.5,cl,GL_LINE_LOOP);
        render->drawCircle(x,y,0.1,0.5*(1-buildingProcess),clc,GL_POLYGON);
        isOperating = false;
    }
}

void Building_Prefab::update()
{
    if(hp<=0){
        demolish();
    }
}

void Building_Prefab::setBuilding(Building *b)
{
    cout<<__FUNCTION__<<"*"<<b<<"*"<<b->x<<"*"<<b->y<<endl;
    isPrefab = true;
    build = b;
    x = build->x;
    y = build->y;
    w = build->w;
    h = build->h;
    map<int,int> * mlPrefab = &(BuildingFactory::the()->buildingPrefabs[build->id].materialNeeds);
    materialList.init(mlPrefab);
    cout<<__FUNCTION__<<":";
    materialList.printState();
    cout<<x<<"*"<<y<<"*"<<build->x<<"*"<<build->y;
    cout<<endl;
}

void Building_Prefab::operate()
{
    isOperating = true;
    buildWork(0.01);
}

bool Building_Prefab::buildWork(float delta)
{
    //cout<<__FUNCTION__<<"*"<<x<<"*"<<y<<"*"<<build->x<<"*"<<build->y;
    //cout<<"*"<<this->buildingProcess;
    //cout<<endl;

    if(!materialList.ready()){
        cout<<__FUNCTION__<<"lack of material!!!"<<endl;
        State_FillMaterial* s = new State_FillMaterial;
        s->setMaterialList(&materialList);
        FSM::the()->pushState(s);
        return false;
    }

    buildingProcess -=0.01;
    if(buildingProcess<=0){
        ///$$$ debug
        BuildingFactory::the()->completeBuilding(this);
        cout<<"build work complete!"<<endl;
        return true;
    }
}

bool Building_Prefab::takeDmg(float dmg)
{
    hp-=dmg;
    if(hp<=0){
        return true;
    }
    return false;
}

void Building_Prefab::demolish()
{
    //buildingProcess
    vector<Item_Common *> items = materialList.returnMaterials();
    for(auto itr = items.begin();itr!= items.end();itr++){
        ///$$$
        (*itr)->loss(buildingProcess/(maxHp*10.0f));
        IC_Map::Instance()->putItem(IC_Map::nearIntValue(build->x),IC_Map::nearIntValue(build->y),(*itr));
    }
    BuildingFactory::the()->destroyBuilding(this);
}

Building_Prefab *Building_Prefab::toPrefab(Building *b)
{
    return dynamic_cast<Building_Prefab*>(b);
}

