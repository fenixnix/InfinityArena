#ifndef BUILDING_IDOL_H
#define BUILDING_IDOL_H

#include "building_Storage.h"

class Building_Idol : public Building_Storage
{
public:
    Building_Idol();
    static Building *create(string id, float x, float y);
};

#endif // BUILDING_IDOL_H
