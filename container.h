#ifndef CONTAINER_H
#define CONTAINER_H

#include "item/item.h"
#include "Item/item_common.h"
#include "Item/item_meleeweapon.h"
#include <vector>
#include <iostream>
#include <map>

using namespace std;

#define COLS 8
#define CELLSIZE 40
#define ICONSIZE 32

class Container
{
public:
    Container();
    ~Container();
    void init(unsigned int size);
    void clear();
    void enlarge(unsigned int size);
    bool have(map<int,int> *ml);
    size_t size();
    void update();
    Item* put(Item*);
    Item *take(unsigned int pos);
    Item *at(unsigned int pos);
    Item *take();
    bool cost(int id,int count);
    void swap(unsigned int src,unsigned int dis);

private:
    vector<Item*> items;
};

#endif // CONTAINER_H
