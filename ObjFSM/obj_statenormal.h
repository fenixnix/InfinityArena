#ifndef OBJ_STATENORMAL_H
#define OBJ_STATENORMAL_H

#include "obj_State.h"

class Obj_StateNormal : public Obj_State
{
public:
    Obj_StateNormal();
    string getID(){
        return "normal";
    }

    float getFrame(){
        return 0.0f;
    }

    void begin();
    void end();
    void update();
};

#endif // OBJ_STATENORMAL_H
