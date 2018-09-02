#include "objfactory.h"
#include "physxobj.h"
#include "obj_creature.h"
#include "b2physx.h"
#include "global.h"

ObjFactory* ObjFactory::p_static = 0;

ObjFactory::ObjFactory()
{
    uniid = 0;
}

void ObjFactory::update()
{
    refreshSight();
    for(auto itr = objs.begin();itr!=objs.end();itr++){
        if(*itr!=NULL){
            PhysxObj* po = dynamic_cast<PhysxObj*>(*itr);
            //po->processConnect();
            po->update();
        }
    }

    for(auto itr = objsMap.begin();itr!=objsMap.end();itr++){
        if(itr->second!=NULL){
            PhysxObj* po = dynamic_cast<PhysxObj*>(itr->second);
            //po->processConnect();
            po->update();
        }
    }

    for(auto itr = objs.begin();itr!=objs.end();){
        if(*itr!=NULL){
            PhysxObj* po = dynamic_cast<PhysxObj*>(*itr);
            if(po->isDead){
                //SDL_Physx::Instance()->releaseBody(po->phyxBody);
                delete po;
                itr = objs.erase(itr);
            }else{
                itr++;
            }
        }
    }
    for(auto itr = objsMap.begin();itr!=objsMap.end();){
        if(itr->second!=NULL){
            PhysxObj* po = dynamic_cast<PhysxObj*>(itr->second);
            if(po->isDead){
                //SDL_Physx::Instance()->releaseBody(po->phyxBody);
                delete po;
                itr = objsMap.erase(itr);
            }else{
                itr++;
            }
        }
    }
}

void ObjFactory::draw()
{
    for(auto itr = objs.begin();itr!=objs.end();itr++){
        if(*itr){
            (*itr)->draw();
        }
    }
    for(auto itr = objsMap.begin();itr!=objsMap.end();){
        if(itr->second!=NULL){
            dynamic_cast<Obj_Creature*>(itr->second)->draw();
        }
        itr++;
    }
}

void ObjFactory::draw(float x, float y, float r)
{
    for(auto itr = objs.begin();itr!=objs.end();itr++){
        if(*itr){

            (*itr)->draw();
        }
    }
    for(auto itr = objsMap.begin();itr!=objsMap.end();){
        if(itr->second!=NULL){
            Obj_Creature* oc = dynamic_cast<Obj_Creature*>(itr->second);
            b2Transform tra = oc->phyxBody->GetTransform();
            float d = Global::distance(x,y,tra.p.x,tra.p.y);
            if(d<r){
                oc->draw();
            }
        }
        itr++;
    }
}

void ObjFactory::drawBillboard(float pitch, float yaw)
{
    for(auto itr = objsMap.begin();itr!=objsMap.end();){
        if(itr->second!=NULL){
            //out<<(itr->second)->type()<<endl;
            //if((itr->second)->type() == string("slime")){
            dynamic_cast<Obj_Creature*>(itr->second)->drawBillboard(pitch,yaw);
            //}
        }
        itr++;
    }
    for(auto itr = objs.begin();itr!=objs.end();itr++){
        if(*itr){
            (*itr)->draw();
        }
    }
}

void ObjFactory::drawBillboard(float x, float y, float r, float pitch, float yaw)
{
    for(auto itr = objsMap.begin();itr!=objsMap.end();){
        if(itr->second!=NULL){
            Obj_Creature *oc = dynamic_cast<Obj_Creature*>(itr->second);
            b2Transform t = oc->phyxBody->GetTransform();
            float d = Global::distance(x,y,t.p.x,t.p.y);
            if(d<r){
                oc->drawBillboard(pitch,yaw);
            }
        }
        itr++;
    }
    for(auto itr = objs.begin();itr!=objs.end();itr++){
        if(*itr){
            (*itr)->draw();
        }
    }
}

void ObjFactory::addObj(Obj *o)
{
    objs.push_back(o);
}

int ObjFactory::addObj2Map(Obj *o)
{
    int id = uniid;
    objsMap[id] = o;
    o->id = id;
    if(o->isCreature()){
        Obj_Creature *oc = dynamic_cast<Obj_Creature*>(o);
        oc->fsm.objID = id;
        oc->fsm.obj = oc;
    }
    uniid++;
    return id;
}

Obj *ObjFactory::getObjOnMap(int id)
{
    //cout<<__FUNCTION__<<" "<<id<<endl;
    auto itr = objsMap.find(id);
    if(itr == objsMap.end()){
        return NULL;
    }
    return itr->second;
}

Obj_Human *ObjFactory::getHumanObj(int id)
{
    auto itr = objsMap.find(id);
    if(itr == objsMap.end()){
        return nullptr;
    }
    Obj* o = itr->second;
    if(o->type() == string("human")){
        return dynamic_cast<Obj_Human*>(o);
    }
    return nullptr;
}

Obj_Creature *ObjFactory::getCreatureObj(int id)
{
    Obj* o = getObjOnMap(id);
    if(o){
        if(o->isCreature()){
            Obj_Creature* oc = dynamic_cast<Obj_Creature*>(o);
            return oc;
        }
    }
    return nullptr;
}

void ObjFactory::removeObj(int id)
{
    objsMap.erase(objsMap.find(id));
}

bool ObjFactory::addThreats(int id, int tid, int value)
{
    cout<<__FUNCTION__<<" "<<id<<" "<<tid<<" "<<value<<endl;
    Obj_Creature* oc = getCreatureObj(id);
    if(oc){
        oc->addThreats(tid,value);
        return true;
    }
    return false;
}

void ObjFactory::clearSight()
{
    for(auto itr = objsMap.begin();itr!=objsMap.end();itr++){
        if(itr->second!=NULL){
            Obj_Creature* po = dynamic_cast<Obj_Creature*>(itr->second);
            po->sights.clear();
        }
    }
}

void ObjFactory::checkSight(Obj *A, Obj *B)
{
    //cout<<__FUNCTION__<<" A id:"<<A->id<<" B id:"<<B->id;
    if((A->isCreature())&&(B->isCreature())){
        Obj_Creature* a = dynamic_cast<Obj_Creature*>(A);
        Obj_Creature* b = dynamic_cast<Obj_Creature*>(B);
        float d = (a->phyxBody->GetTransform().p - b->phyxBody->GetTransform().p).Length();
        //cout<<" *"<<d<<"*"<<a->sight<<"*"<<b->sight;
        if(a->sight>d){
            a->sights.push_back(b->id);
        }
        if(b->sight>d){
            b->sights.push_back(a->id);
        }
    }
    //cout<<endl;
}

void ObjFactory::refreshSight()
{
    clearSight();
    for(auto itr = objsMap.begin();itr!=objsMap.end();itr++){
        for(auto i = itr;i!=objsMap.end();i++){
            if(itr==i){
                continue;
            }
            checkSight(itr->second,i->second);
        }
    }
}

void ObjFactory::clear()
{
    //clear all obj with free memory
    for(auto itr = objsMap.begin();itr!=objsMap.end();itr++){
        delete dynamic_cast<PhysxObj*>(itr->second);
    }
    for(auto itr = objs.begin();itr!=objs.end();itr++){
        delete dynamic_cast<PhysxObj*>(*itr);
    }
    cout<<__FUNCTION__<<" objsMap size:"<<objsMap.size()<<endl;
    cout<<__FUNCTION__<<" objs size:"<<objs.size()<<endl;
    objsMap.clear();
    objs.clear();
    uniid = 0;
}
