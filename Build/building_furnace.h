#ifndef BUILDING_FURNACE_H
#define BUILDING_FURNACE_H

#include "building_workbench.h"

class Building_Furnace : public Building_Workbench
{
public:
    Building_Furnace();
    static Building *create(float x, float y);
private:
    Container fuel;
};

#endif // BUILDING_FURNACE_H
