#ifndef BUILDING_PLAN_H
#define BUILDING_PLAN_H

#include "building.h"

class Building_Plan : public Building
{
public:
    Building_Plan();
    void draw();
private:
    float buildingProcess;
    int buildingTime;
};

#endif // BUILDING_PLAN_H
