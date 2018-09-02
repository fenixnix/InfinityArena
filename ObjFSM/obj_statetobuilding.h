#ifndef OBJ_STATETOBUILDING_H
#define OBJ_STATETOBUILDING_H

#include "ObjFSM/obj_state.h"

class Obj_StateToBuilding : public Obj_State
{
public:
    Obj_StateToBuilding();
    string getID(){
        return "toBuilding";
    }

    float getFrame(){
        return 0.0f;
    }

    void begin();
    void end();
    void update();
    int x,y;
    GlobalTimer gt;
};

#endif // OBJ_STATETOBUILDING_H
