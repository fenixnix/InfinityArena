#ifndef ACTSLASH3_H
#define ACTSLASH3_H

#include "obj_state.h"
#include "Item/item_meleeweapon.h"

class ActSlash3 : public Obj_State
{
public:
    ActSlash3();
    string getID(){
        return "slash3";
    }
    float getFrame(){
        return gt.getTimePercent();
    }
    void begin();
    void end();
    void update();
    float x,y;
    float as;
    float ae;
    GlobalTimer gt;
    Item_MeleeWeapon* imw;
};

#endif // ACTSLASH3_H
