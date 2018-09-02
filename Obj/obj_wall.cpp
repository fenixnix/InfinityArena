#include "obj_wall.h"
#include "b2physx.h"
#include "objfactory.h"

Obj_Wall::Obj_Wall()
{

}

Obj_Wall *Obj_Wall::create(float x, float y)
{
    Obj_Wall * wall = new Obj_Wall;
    wall->phyxBody = B2Physx::the()->createDynamicBox(x,y,0.2,0.2,wall,true);
    //ObjFactory::Instance()->addObj(dynamic_cast<Obj*>(wall));
    ObjFactory::Instance()->addObj(dynamic_cast<Obj*>(wall));
    return wall;
}

void Obj_Wall::draw()
{

}

void Obj_Wall::update()
{

}

void Obj_Wall::begin(PhysxObj *obj)
{
    cout<<__FUNCTION__<<"*"<<Obj_Wall::type()<<endl;
}

