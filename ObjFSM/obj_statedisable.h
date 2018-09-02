#ifndef OBJ_STATEDISABLE_H
#define OBJ_STATEDISABLE_H

#include "obj_state.h"
#include "globaltimer.h"

class Obj_StateDisable : public Obj_State
{
public:
    Obj_StateDisable();
    string getID(){
        return "disable";
    }

    float getFrame(){
        return gt.getTimePercent();
    }

    void begin();
    void end();
    void update();
    GlobalTimer gt;
    int delayTime;
};

#endif // OBJ_STATEDISABLE_H
