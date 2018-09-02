#include "buildingindungeon.h"
#include "ic_map.h"
#include "Item/itemfactory.h"

BuildingInDungeon::BuildingInDungeon()
{
    dungeonType = "Treasure";
}

Building *BuildingInDungeon::create(int x, int y)
{
    BuildingInDungeon* b = new BuildingInDungeon;
    b->type = string("Dungeon");
    b->x = x;
    b->y = y;
    return dynamic_cast<Building*>(b);
}

void BuildingInDungeon::draw()
{

}

void BuildingInDungeon::active()
{
    IC_Map::Instance()->putItemf(x,y,ItemFactory::Instance()->craftItem("log",1));
    //drop Item;
}
