#ifndef OBJ_STATEPUNCH_H
#define OBJ_STATEPUNCH_H

#include "obj_state.h"

class Obj_StatePunch : public Obj_State
{
public:
    Obj_StatePunch();
    string getID(){
        return "punch";
    }

    float getFrame(){
        return 0.0f;
    }

    void begin();
    void end();
    void update();
    int aimID;
};

#endif // OBJ_STATEPUNCH_H
