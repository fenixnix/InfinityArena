#ifndef ACTSLASH2_H
#define ACTSLASH2_H

#include "obj_state.h"
#include "Item/item_meleeweapon.h"

class ActSlash2 : public Obj_State
{
public:
    ActSlash2();
    string getID(){
        return "slash2";
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
};

#endif // ACTSLASH2_H
