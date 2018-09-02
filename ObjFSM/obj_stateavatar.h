#ifndef OBJ_STATEAVATAR_H
#define OBJ_STATEAVATAR_H

#include "obj_state.h"

class Obj_StateAvatar : public Obj_State
{
public:
    Obj_StateAvatar();
    string getID(){
        return "avatar";
    }
    float getFrame(){
        return 0.0f;
    }
    void act1(float x, float y);

    void begin();
    void end();
    void update();
    int aimID;
};

#endif // OBJ_STATEAVATAR_H
