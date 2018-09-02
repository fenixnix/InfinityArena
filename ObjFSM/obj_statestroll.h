#ifndef OBJ_STATESTROLL_H
#define OBJ_STATESTROLL_H

#include "ObjFSM/obj_state.h"
#include "globaltimer.h"

class Obj_StateStroll : public Obj_State
{
public:
    Obj_StateStroll();
    string getID(){
        return "stroll";
    }
    float getFrame(){
        return gt.getTimePercent();
    }

    void begin();
    void end();
    void update();
    float x;
    float y;
    GlobalTimer gt;
};

#endif // OBJ_STATESTROLL_H
