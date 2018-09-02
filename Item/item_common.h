#ifndef ITEM_COMMON_H
#define ITEM_COMMON_H

#include "item/item.h"

class Item_Common : public Item
{
public:
    Item_Common();
    int id;
    int stackCount;
    Item_Common* stack(Item_Common* newItem);
    void loss(float rate);
    string getDrawID();
    string getType(){
        return "common";
    }
    bool isCommon(){
        return true;
    }

    bool isArrow();
    bool isBolt(){

    }
    bool isBullet(){

    }
    static Item_Common* create(int id,int count);
    static Item_Common* create(string id,int count);
    static Item_Common *convert(Item*);
};

#endif // ITEM_COMMON_H
