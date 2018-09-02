#include "item_meleeweapon.h"
#include "Box2D/Box2D.h"
#include "Obj/objfactory.h"
#include "b2physx.h"

Item_MeleeWeapon::Item_MeleeWeapon()
{
    hitNum = 1;
    length = 1;
    range = 0.5;

    as = 120.0f;
    ae = -30.0f;
}

void Item_MeleeWeapon::setAttackRange(float angleStart, float angleEnd)
{
    as = angleStart;
    ae = angleEnd;
}



