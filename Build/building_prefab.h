#ifndef BUILDING_PREFAB_H
#define BUILDING_PREFAB_H

#include "building.h"
#include "materiallist.h"

class Building_Prefab : public Building
{
public:
    Building_Prefab();
    void draw();
    void update();
    void setBuilding(Building* b);
    void operate();
    bool buildWork(float delta);
    bool takeDmg(float dmg);
    void demolish();
    static Building_Prefab *toPrefab(Building* b);

//private:
    bool isOperating;
    float buildingProcess;
    int workload;
    Building* build;
    MaterialList materialList;
};

#endif // BUILDING_PREFAB_H
