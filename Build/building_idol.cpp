#include "building_idol.h"
#include "buildingfactory.h"

Building_Idol::Building_Idol()
{

}

Building *Building_Idol::create(string id, float x, float y)
{
    Building_Idol* bi = new Building_Idol;
    bi->type = string("Storage");
    bi->x = x;
    bi->y = y;
    BuildingPrepare *bpfab = &(BuildingFactory::the()->buildingPrefabs[id]);
    bi->w = bpfab->w;
    bi->h = bpfab->h;
    bi->maxHp = bpfab->maxHp;
    bi->hp = bi->maxHp;
    bi->id = bpfab->name;
    bi->drawID = bpfab->name;
    bi->createPhyx();
    return dynamic_cast<Building*>(bi);
}

