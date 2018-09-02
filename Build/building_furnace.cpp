#include "building_furnace.h"
#include "buildingfactory.h"

Building_Furnace::Building_Furnace()
{
    type = string("furnace");
}

Building *Building_Furnace::create(float x, float y)
{
    Building_Furnace* bd = new Building_Furnace;
    bd->x = x;
    bd->y = y;
    BuildingPrepare *bpfab = &(BuildingFactory::the()->buildingPrefabs["Furnace"]);
    bd->w = bpfab->w;
    bd->h = bpfab->h;
    bd->maxHp = bpfab->maxHp;
    bd->hp = bd->maxHp;
    bd->id = bpfab->name;
    bd->drawID = bd->id;
    return dynamic_cast<Building*>(bd);
}

