#ifndef BUILDING_STORAGE_H
#define BUILDING_STORAGE_H

#include "building.h"
#include "container.h"

class Building_Storage : public Building
{
public:
    Building_Storage();
    //void draw();
    static Building *create(string id, float x, float y);
    void draw();
    void operate();
    void createPhyx();
    Container outputItems;
};

#endif // BUILDING_STORAGE_H
