#ifndef BUILDING_TREASURE_H
#define BUILDING_TREASURE_H

#include "build/building.h"

class Building_Treasure : public Building
{
public:
    Building_Treasure();
    void draw();
    void active();
    void createPhyx();
    static Building *create(string id, float x, float y);
};

#endif // BUILDING_TREASURE_H
