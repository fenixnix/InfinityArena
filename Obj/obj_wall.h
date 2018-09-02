#ifndef OBJ_WALL_H
#define OBJ_WALL_H

#include "physxobj.h"

class Obj_Wall : public PhysxObj
{
public:
    Obj_Wall();
    static Obj_Wall *create(float x, float y);

    void draw();
    void update();
    void begin(PhysxObj*);
    string type(){
        return "wall";
    }

    bool isCreature(){
        return false;
    }
};

#endif // OBJ_WALL_H
