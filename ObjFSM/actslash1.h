#ifndef ACTSLASH1_H
#define ACTSLASH1_H

#include "obj_state.h"
#include "Item/item_meleeweapon.h"

class ActSlash1 : public Obj_State
{
public:
    ActSlash1();
    string getID(){
        return "slash1";
    }
    float getFrame(){
        return gt.getTimePercent();
    }
    void act1(float x, float y);
    void begin();
    void end();
    void update();
    float x,y;
    float as;
    float ae;
    GlobalTimer gt;
    Item_MeleeWeapon* imw;
    float cost;
    float actTime1;
    float actTime2;
};

#endif // ACTSLASH1_H
