#ifndef BUILDING_WORKBENCH_H
#define BUILDING_WORKBENCH_H

#include "building_Storage.h"
#include "materiallist.h"

class Building_Workbench : public Building_Storage
{
public:
    Building_Workbench();
    static Building *create(float x, float y);
private:
    MaterialList materialList;
    Container* inputItems;
};

#endif // BUILDING_WORKBENCH_H
