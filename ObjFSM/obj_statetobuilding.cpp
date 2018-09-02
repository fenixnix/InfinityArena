#include "obj_statetobuilding.h"
#include "ic_map.h"
#include "ObjFSM/obj_fsm.h"
#include "obj_creature.h"

Obj_StateToBuilding::Obj_StateToBuilding()
{

}

void Obj_StateToBuilding::begin()
{
    cout<<__FUNCTION__<<endl;
    gt.start(2000);
}

void Obj_StateToBuilding::end()
{
    cout<<__FUNCTION__<<endl;
}

void Obj_StateToBuilding::update()
{
    //cout<<__FUNCTION__<<endl;
    b2Transform p1 = parent->obj->phyxBody->GetTransform();
    int w,h;
    w = IC_Map::Instance()->getMapWidth();
    h = IC_Map::Instance()->getMapHeight();
    b2Vec2 d(w/2,h/2);
    //cout<<p1.p.x<<"*"<<p1.p.y<<endl;
    b2Vec2 v = d - p1.p;
    parent->obj->walk(v);
//    if(gt.getTimePercent()>1){
//        parent->pop();
//    }
}
