#ifndef ITEM_CHARGERANGEWEAPON_H
#define ITEM_CHARGERANGEWEAPON_H

#include "Item/item.h"
#include <string>
#include <tinyxml2.h>
#include <Box2D/Box2D.h>

using namespace tinyxml2;
using namespace std;

class Item_ChargeRangeWeapon : public Item
{
public:
    Item_ChargeRangeWeapon();
    bool isChargeRangeWeapon(){
        return true;
    }
    string getDrawID(){
        return drawID;
    }
    string getType(){
        return "range";
    }
    bool isWeapon(){
        return true;
    }
    static Item_ChargeRangeWeapon *create(XMLElement* ele);
    static Item_ChargeRangeWeapon *convert(Item* itm){
        return dynamic_cast<Item_ChargeRangeWeapon*>(itm);
    }

    void drawWeapon(Item* itm);
    void update();
    void loss(Item* itm,b2Vec2 pos,b2Vec2 dir);
    string id;
    string drawID;
    string type;
    int ownerID;
    float baseForce;
    float chargeSpeed;
    float maxChargeTime;
    float attackRate;
    //int durability;
    //int maxDurability;
    //int strNeed;
    //int agiNeed;
    //int intNeed;
    float chargeValue;
    int chargeTime;
    bool isDrawing;
};

#endif // ITEM_CHARGERANGEWEAPON_H
