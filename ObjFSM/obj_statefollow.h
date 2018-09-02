#ifndef OBJ_STATEFOLLOW_H
#define OBJ_STATEFOLLOW_H

#include "ObjFSM/obj_state.h"

class Obj_StateFollow : public Obj_State
{
public:
    Obj_StateFollow();
    string getID(){
        return "follow";
    }

    float getFrame(){
        return 0.0f;
    }

    void begin();
    void end();
    void update();
    int aimID;
    float distance;
};

#endif // OBJ_STATEFOLLOW_H
