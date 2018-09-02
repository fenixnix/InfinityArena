#ifndef ITEM_MELEEWEAPON_H
#define ITEM_MELEEWEAPON_H

#include "Item/item.h"
#include <string>

using namespace std;

class Item_MeleeWeapon : public Item
{
public:
    Item_MeleeWeapon();
    string getType(){
        return "melee";
    }
    bool isWeapon(){
        return true;
    }

    string getDrawID(){
        return drawID;
    }
    static Item_MeleeWeapon *convert(Item* itm){
        return dynamic_cast<Item_MeleeWeapon*>(itm);
    }

    //void swing(float dx, float dy,Obj_Creature* objc);
    void setAttackRange(float angleStart,float angleEnd);
    int ownerID;
    string id;
    string drawID;
    string type;
    string dmgType;
    float dmg;
    float length;
    float range;
    float attackRate;
    int hitNum;
    int durability;
    int maxDurability;
    int strNeed;
    int agiNeed;
    int intNeed;

    float as;
    float ae;
};

#endif // ITEM_MELEEWEAPON_H
