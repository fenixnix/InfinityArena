#include "buildingfactory.h"
#include <tinyxml2.h>
#include "building_prefab.h"
#include "building_Storage.h"
#include "building_workbench.h"
#include "building_furnace.h"
#include "building_idol.h"
#include "building_treasure.h"
#include "plant.h"
#include "ic_map.h"
#include "global.h"

using namespace tinyxml2;

BuildingFactory * BuildingFactory::p_Static = NULL;

BuildingFactory::BuildingFactory()
{

}

bool BuildingFactory::loadConfig(string fileName)
{
    cout<<__FUNCTION__<<endl;
    buildingPrefabs.clear();
    XMLDocument doc;
    doc.LoadFile(fileName.c_str());
    XMLElement* root = doc.RootElement();
    XMLNode* buildNode = root->FirstChild();
    while(buildNode){
        XMLElement* buildEle = buildNode->ToElement();
        cout<<string(buildEle->Name())<<" ";
        BuildingPrepare bp;
        bp.name = string(buildEle->Name());

        bp.w = buildEle->FloatAttribute("w");
        cout<<"w: "<<bp.w;
        bp.h = buildEle->FloatAttribute("h");
        cout<<"h: "<<bp.h;
        bp.maxHp = buildEle->IntAttribute("maxHp");
        cout<<"mapHP: "<<bp.maxHp;
        bp.worklord = buildEle->IntAttribute("worklord");
        cout<<"worklord: "<<bp.worklord;


        XMLNode* materialListNode = buildEle->FirstChildElement("materialList");
        if(materialListNode){
            XMLNode* mln = materialListNode->FirstChild();
            cout<<"materialList"<<endl;
            while(mln){
                XMLElement* mle = mln->ToElement();
                bp.materialNeeds[atoi(mle->Attribute("id"))] = atoi(mle->Attribute("ct"));
                mln = mln->NextSibling();
            }
        }

        XMLNode* materialDropNode = buildEle->FirstChildElement("materialDrop");
        if(materialDropNode){
            XMLNode* mln = materialDropNode->FirstChild();
            cout<<"materialDrop"<<endl;
            while(mln){
                XMLElement* mle = mln->ToElement();
                bp.materialDrops[atoi(mle->Attribute("id"))] = atoi(mle->Attribute("ct"));
                mln = mln->NextSibling();
            }
        }
        cout<<endl;
        buildingPrefabs[bp.name] = bp;
        buildNode = buildNode->NextSibling();
    }
    return true;
}

bool BuildingFactory::release()
{
    for(auto itr = buildings.begin();itr!=buildings.end();itr++){
        delete (*itr);
    }
    buildings.clear();
    return true;
}

void BuildingFactory::update()
{
    for(auto itr = buildings.begin();itr!=buildings.end();){
        Building* bd = *itr;
        if(bd->isDead){
            IC_Map::Instance()->destoryBuilding(bd);
            bd->destroyPhyx();
            delete bd;
            itr = buildings.erase(itr);
        }else{
            itr++;
        }
    }
    for(auto itr = buildings.begin();itr!=buildings.end();itr++){
        Building* bd = *itr;
        bd->update();
    }
}

void BuildingFactory::draw()
{
    for(auto itr = buildings.begin();itr!=buildings.end();itr++){
        (*itr)->draw();
    }
}

void BuildingFactory::draw3D(float x, float y, float r)
{
    for(auto itr = buildings.begin();itr!=buildings.end();itr++){
        Building* b = *itr;
        float d = Global::distance(x,y,b->x,b->y);
        if(d<r){
            b->draw();
        }
    }
}

Building *BuildingFactory::create(string id, float x, float y)
{
    //cout<<__FUNCTION__<<"*"<<id;
    //cout<<endl;
    if(id == string("Chest"))
        return Building_Storage::create(id,x,y);

    if(id == string("Warehouse"))
        return Building_Storage::create(id,x,y);

    if(id == string("Workbench"))
        return Building_Workbench::create(x,y);

    if(id == string("Furnace"))
        return Building_Furnace::create(x,y);

    if(id == string("tree"))
        return Plant::create("tree",x,y);

    if(id == string("bush"))
        return Plant::create("bush",x,y);

    if(id == string("Idol"))
        return Building_Idol::create(id,x,y);
    if(id == string("Treasure")){
        return Building_Treasure::create(id,x,y);
    }

}

void BuildingFactory::createDirectly(string id, float x, float y)
{
    //cout<<__FUNCTION__<<id<<"x: "<<x<<" y: "<<y<<endl;
    Building* build = create(id,x,y);
    buildings.push_back(build);
    build->createPhyx();
    IC_Map::Instance()->putBuilding(build);
}

Building *BuildingFactory::createPrefab(string id, float x, float y)
{
    cout<<__FUNCTION__<<"*"<<id<<"*"<<x<<"*"<<y<<"++";
    Building_Prefab* prefab = new Building_Prefab;
    prefab->setBuilding(create(id,x,y));
    cout<<"p:"<<prefab->x<<"*"<<prefab->y<<endl;
    buildings.push_back(prefab);
    IC_Map::Instance()->putBuilding(dynamic_cast<Building*>(prefab));
    cout<<"p:"<<prefab->x<<"*"<<prefab->y<<endl;
    return dynamic_cast<Building*>(prefab);
}

void BuildingFactory::destroyBuilding(Building *build)
{
    if(build==NULL){
        return;
    }
    build->isDead = true;
}

void BuildingFactory::completeBuilding(Building_Prefab *bp)
{
    cout<<__FUNCTION__<<endl;
    if(bp==NULL){
        return;
    }
    Building* b = bp->build;
    IC_Map::Instance()->destoryBuilding(bp);

    for(auto itr = buildings.begin();itr!=buildings.end();){
        if((*itr)==bp){
            itr = buildings.erase(itr);
        }else{
            itr++;
        }
    }
    buildings.push_back(b);
    IC_Map::Instance()->putBuilding(b);
    b->createPhyx();
}

map<int, int> BuildingFactory::getMaterialNeeds(string id)
{
    return buildingPrefabs[id].materialNeeds;
}

vector<string> BuildingFactory::getProductionBuildList()
{
    vector<string> tmpList;
    tmpList.push_back("Chest");
    tmpList.push_back("Workbench");
    return tmpList;
}

vector<string> BuildingFactory::getMilitaryBuildList()
{
    vector<string> tmpList;
    tmpList.push_back("Crate");
    tmpList.push_back("Fence");
    return tmpList;
}

void BuildingFactory::clear()
{
    for(int i = 0; i<buildings.size(); i++){
        delete buildings[i];
    }
    buildings.clear();
}
