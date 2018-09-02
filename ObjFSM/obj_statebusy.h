#ifndef OBJ_STATEBUSY_H
#define OBJ_STATEBUSY_H

#include "obj_state.h"
#include "globaltimer.h"

class Obj_StateBusy : public Obj_State
{
public:
    Obj_StateBusy();
    string getID(){
        return "busy";
    }

    float getFrame(){
        return gt.getTimePercent();
    }

    void begin();
    void end();
    void update();
    Obj_State* ready;
    GlobalTimer gt;
    int delayTime;
};

#endif // OBJ_STATEBUSY_H
