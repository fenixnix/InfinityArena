#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

class Item
{
public:
    Item();
    //int itemID;
    //int stackCount;
    //Item* stack(Item* newItem);
    //void loss(float rate);//1.0>rate>0
    virtual void drawOnMap(float x,float y);
    virtual string getDrawID(){
        return "";
    }
    virtual string getType(){
        return "item";
    }
    virtual bool isCommon(){
        return false;
    }
    virtual bool isWeapon(){
        return false;
    }

};

#endif // ITEM_H
