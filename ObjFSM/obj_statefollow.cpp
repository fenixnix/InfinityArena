#include "obj_statefollow.h"
#include "objfactory.h"
#include "global.h"

Obj_StateFollow::Obj_StateFollow()
{

}

void Obj_StateFollow::begin()
{
    //cout<<__FUNCTION__<<endl;
}

void Obj_StateFollow::end()
{
    //cout<<__FUNCTION__<<endl;
}

void Obj_StateFollow::update()
{
    Obj_Creature* oc = ObjFactory::Instance()->getCreatureObj(aimID);
    if(oc){
        //cout<<__FUNCTION__<<this->getID()<<"*"<<this->parent->objID<<endl;
        b2Transform p1 = parent->obj->phyxBody->GetTransform();
        b2Transform p2 = oc->phyxBody->GetTransform();
        float d = Global::distance(p1.p.x,p1.p.y,p2.p.x,p2.p.y);
        if(d>distance){
            b2Vec2 v = p2.p - p1.p;
            parent->obj->walk(v);
        }else{
            parent->pop();
            return;
        }
    }else{
        //cout<<__FUNCTION__<<__LINE__<<"*W"<<this->getID()<<"*"<<this->parent->objID<<endl;
        //taget miss
        parent->threats.erase(parent->threats.find(aimID));
        parent->pop();
        return;
    }

}
