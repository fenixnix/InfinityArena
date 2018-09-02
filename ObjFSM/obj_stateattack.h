#ifndef OBJ_STATEATTACK_H
#define OBJ_STATEATTACK_H

#include "ObjFSM/obj_state.h"

class Obj_StateAttack : public Obj_State
{
public:
    Obj_StateAttack();
    string getID(){
        return "attack";
    }
    float getFrame(){
        return 0.0f;
    }

    void begin();
    void end();
    void update();
    int aimID;
};

#endif // OBJ_STATEATTACK_H
