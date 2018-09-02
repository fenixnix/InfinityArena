#ifndef OBJ_BEAST_H
#define OBJ_BEAST_H

#include "Obj/obj_creature.h"
#include "objfactory.h"
#include "b2physx.h"
#include "globaltimer.h"

class Obj_Beast : public Obj_Creature
{
public:
    Obj_Beast();
    ~Obj_Beast();
    string name;
    void draw();
    void drawBillboard(float pitch,float yaw);
    void update();
    static Obj *create(string id,int x, int y);

    virtual string classify(){
        return "Beast";
    }

    void seek();
    void attack();
};

#endif // OBJ_BEAST_H
