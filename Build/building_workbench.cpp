#include "building_workbench.h"
#include "buildingfactory.h"

Building_Workbench::Building_Workbench()
{

}

Building *Building_Workbench::create(float x, float y)
{
    cout<<__FUNCTION__<<":"<<x<<" "<<y<<endl;
    Building_Workbench* bd = new Building_Workbench;
    bd->x = x;
    bd->y = y;
    BuildingPrepare *bpfab = &(BuildingFactory::the()->buildingPrefabs["Workbench"]);
    bd->w = bpfab->w;
    bd->h = bpfab->h;
    bd->maxHp = bpfab->maxHp;
    bd->hp = bd->maxHp;
    bd->id = bpfab->name;
    bd->drawID = bd->id;
    return dynamic_cast<Building*>(bd);
}

