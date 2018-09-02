#include "obj_statenormal.h"
#include "objfsm/obj_fsm.h"
#include "objfactory.h"
#include "obj_statestroll.h"
#include "obj_stateattack.h"
#include "obj_statefollow.h"
#include "obj_stateavatar.h"
#include "obj_statetobuilding.h"
#include "global.h"

Obj_StateNormal::Obj_StateNormal()
{

}

void Obj_StateNormal::begin()
{
    //cout<<__FUNCTION__<<endl;
}

void Obj_StateNormal::end()
{
    //cout<<__FUNCTION__<<endl;
}

void Obj_StateNormal::update()
{
    //cout<<__FUNCTION__<<endl;
    if(parent->obj == nullptr){
        cout<<__FUNCTION__<<"null obj!!!"<<endl;
        return;
    }

    if(parent->objID == Global::the()->world.avatarID){
        Obj_StateAvatar *t = new Obj_StateAvatar;
        t->parent = this->parent;
        parent->push(t);
        return;
    }

    //any condition
    //warlike
    if(parent->AI_Feature::warlike){
        for(int i = 0;i<parent->obj->sights.size();i++){
            int id = parent->obj->sights[i];
            Obj_Creature* oc = ObjFactory::Instance()->getCreatureObj(id);
            if(oc->alignment!=parent->obj->alignment){
                if(parent->threats[id]<10){
                    parent->threats[id] = 10;
                }
            }
        }
    }

    //cout<<__FUNCTION__<<parent->objID<<endl;
    if(parent->AI_Feature::cmd_defence){
        b2Transform tra =  Global::the()->world.avatarObj->phyxBody->GetTransform();
        b2Transform tra1 = parent->obj->phyxBody->GetTransform();
        float d = Global::distance(tra.p.x,tra.p.y,tra1.p.x,tra1.p.y);
        if(d>4){
            Obj_StateFollow *t = new Obj_StateFollow;
            t->aimID = Global::the()->world.avatarID;
            t->distance = 3;
            t->parent = parent;
            parent->push(t);
        }
    }

    //cout<<__FUNCTION__<<parent->objID<<endl;
    if(parent->AI_Feature::rage){
        if(parent->threats.size()>0){
            Obj_StateAttack *t = new Obj_StateAttack;
            t->aimID = parent->maxThreatsID();
            cout<<__FUNCTION__<<" taget:"<<t->aimID;
            t->parent = this->parent;
            parent->push(t);
        }
    }
    //cout<<__FUNCTION__<<parent->objID<<endl;
    if(parent->AI_Feature::raid){
        Obj_StateToBuilding *t = new Obj_StateToBuilding;
        t->parent = this->parent;
        parent->push(t);
    }

    if(parent->AI_Feature::stroll){
        Obj_StateStroll *t = new Obj_StateStroll;
        t->parent = this->parent;
        parent->push(t);
    }

}
