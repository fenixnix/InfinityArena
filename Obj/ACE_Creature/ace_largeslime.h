#ifndef ACE_LARGESLIME_H
#define ACE_LARGESLIME_H

#include "ace_creature.h"

class ACE_LargeSlime : public ACE_Creature
{
public:
    ACE_LargeSlime();
    void draw();
    void drawBillboard(float pitch,float yaw);
    void update();
    static int createByID(float x, float y);
};

#endif // ACE_LARGESLIME_H
