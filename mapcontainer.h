#ifndef MAPCONTAINER_H
#define MAPCONTAINER_H

#include "item/item.h"

class MapContainer
{
public:
    MapContainer();
    int x;
    int y;
    Item* item;
};

#endif // MAPCONTAINER_H
