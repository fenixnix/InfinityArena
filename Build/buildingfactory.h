#ifndef BUILDINGFACTORY_H
#define BUILDINGFACTORY_H

#include <map>
#include <string>
#include <iostream>
#include <Build/building.h>
#include <Build/building_prefab.h>
#include "materiallist.h"

using namespace std;

class BuildingPrepare
{
public:
    string name;
    int w,h,maxHp;
    int worklord;
    map<int,int> materialNeeds;
    map<int,int> materialDrops;
};

class BuildingFactory
{
public:
    BuildingFactory();
    static BuildingFactory* the(){
        if(p_Static == NULL){
            p_Static  = new BuildingFactory;
            cout<<"new BuildingFactory"<<endl;
        }
        return p_Static;
    }
    bool loadConfig(string fileName);
    bool release();
    void update();
    void draw();
    void draw3D(float x, float y, float r);
    Building *create(string id, float x,float y);
    void createDirectly(string id, float x, float y);
    Building *createPrefab(string id, float x, float y);
    void destroyBuilding(Building* build);
    void completeBuilding(Building_Prefab* bp);
    map<int,int> getMaterialNeeds(string id);

    vector<string> getProductionBuildList();
    vector<string> getMilitaryBuildList();

    void clear();
    //int getMaxStack(int id);
    //string getItemName(int id);
//private:
    static BuildingFactory* p_Static;
    map<string,BuildingPrepare> buildingPrefabs;
    vector<Building*> buildings;
};

#endif // BUILDINGFACTORY_H
