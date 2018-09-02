#include "obj_stateattack.h"
#include "objfactory.h"
#include "global.h"
#include "obj_statefollow.h"
#include "obj_statebusy.h"
#include "obj_statepunch.h"

Obj_StateAttack::Obj_StateAttack()
{
    aimID = -1;
}

void Obj_StateAttack::begin()
{
    cout<<__FUNCTION__<<parent->objID<<endl;
}

void Obj_StateAttack::end()
{
    cout<<__FUNCTION__<<endl;
}

void Obj_StateAttack::update()
{
    if(parent->objID == Global::the()->world.avatarID){
        parent->pop();
        return;
    }

    if(parent->threats.empty()){
        parent->pop();
        return;
    }
    aimID = parent->maxThreatsID();

    //cout<<__FUNCTION__<<parent->objID<<"line:"<<__LINE__<<endl;
    Obj_Creature *oc = ObjFactory::Instance()->getCreatureObj(aimID);
    if(oc){
        //cout<<__FUNCTION__<<parent->objID<<"line:"<<__LINE__<<endl;
        b2Transform p1 = parent->obj->phyxBody->GetTransform();
        b2Transform p2 = oc->phyxBody->GetTransform();
        float d = Global::distance(p1.p.x,p1.p.y,p2.p.x,p2.p.y);
        if(d>1.0){
            //cout<<__FUNCTION__<<parent->objID<<"line:"<<__LINE__<<endl;
            Obj_StateFollow *t = new Obj_StateFollow;
            t->aimID = aimID;
            t->distance = 1.0f;
            t->parent = this->parent;
            parent->push(t);
            return;
        }else{
            //cout<<__FUNCTION__<<parent->objID<<"line:"<<__LINE__<<endl;
            Obj_StatePunch *p = new Obj_StatePunch;
            Obj_StateBusy *b = new Obj_StateBusy;
            //cout<<__FUNCTION__<<"*"<<p<<"*"<<b<<endl;
            p->parent = parent;
            p->aimID = aimID;
            b->parent = parent;
            b->delayTime = 750;
            b->ready = p;
            parent->push(b);
            return;
        }
    }else{
        //cout<<__FUNCTION__<<parent->objID<<"line:"<<__LINE__<<endl;
        parent->pop();
        return;
    }
}
