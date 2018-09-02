#ifndef BUILDINGINDUNGEON_H
#define BUILDINGINDUNGEON_H

#include "Build/building.h"

class BuildingInDungeon : public Building
{
public:
    BuildingInDungeon();
    static Building* create(int x,int y);
    void draw();
    void active();
    string dungeonType;
};

#endif // BUILDINGINDUNGEON_H
