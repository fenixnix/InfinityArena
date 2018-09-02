#include "obj_statestroll.h"
#include "ObjFSM/obj_fsm.h"
#include "obj_creature.h"
#include "objfactory.h"

Obj_StateStroll::Obj_StateStroll()
{

}

void Obj_StateStroll::begin()
{
    cout<<__FUNCTION__<<endl;
    b2Vec2 dir;
    dir.x = rand()%200-100;
    dir.y = rand()%200-100;

    dir.x/=100;
    dir.y/=100;

    dir*=0.1;
    x = dir.x;
    y = dir.y;
    //parent->obj->taget = b2Vec2(dir.x,dir.y);
    gt.start(1500);
}

void Obj_StateStroll::end()
{
    //cout<<__FUNCTION__<<endl;
}

void Obj_StateStroll::update()
{
    //cout<<__FUNCTION__<<endl;
     parent->obj->walk(b2Vec2(x,y));
     if(gt.getTo()){
         parent->pop();
         return;
     }
}
