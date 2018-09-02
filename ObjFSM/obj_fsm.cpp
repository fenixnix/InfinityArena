#include "obj_fsm.h"
#include "ObjFSM/obj_statenormal.h"
#include "obj/objfactory.h"
#include "obj_creature.h"

Obj_FSM::Obj_FSM()
{
    anyState = nullptr;
    objID = -1;
}

string Obj_FSM::getCurrentState()
{
    return objStates.back()->getID();
}

string Obj_FSM::getCurrentState(float &percent)
{
    if(objStates.empty()){
        percent = 0.0f;
        return "";
    }
    percent = objStates.back()->getFrame();
    return getCurrentState();
}

void Obj_FSM::update()
{
    //cout<<__FUNCTION__<<" id: "<<objID<<endl;
    Obj*o = ObjFactory::Instance()->getObjOnMap(objID);
    //cout<<__FUNCTION__<<o<<endl;
    if(o == nullptr){
        cout<<__FUNCTION__<<" null obj!!! "<<objID<<endl;
        return;
    }
    if(o->isCreature()){
         obj = static_cast<Obj_Creature*>(o);
    }else{
        cout<<__FUNCTION__<<" invalid obj!!! "<<objID<<endl;
        return;
    }
    if(anyState){
        anyState->update();
    }
    if(!objStates.empty()){
        objStates.back()->update();
        for(auto i = threats.begin();i!=threats.end();){
            Obj_Creature *oc = ObjFactory::Instance()->getCreatureObj(i->first);
            if((i->second<=0)||(oc == nullptr)||(i->first == objID)){
                i = threats.erase(i);
            }else{
                //i->second--;
                i++;
            }
        }
    }else{
        Obj_StateNormal* obj = new Obj_StateNormal;
        obj->parent = this;
        push(obj);
    }
}

void Obj_FSM::push(Obj_State *state)
{
    objStates.push_back(state);\
    objStates.back()->begin();
}

void Obj_FSM::change(Obj_State *state)
{
    if(objStates.empty())
    {
        objStates.push_back(state);
        objStates.back()->begin();
        return;
    }
    objStates.back()->end();
    delete objStates.back();
    objStates.pop_back();

    objStates.push_back(state);
    objStates.back()->begin();
}

void Obj_FSM::pop()
{
    if(objStates.empty()){
        return ;
    }
    objStates.back()->end();
    delete objStates.back();
    objStates.pop_back();
    objStates.back()->begin();
}

void Obj_FSM::clear()
{
    while(!objStates.empty()){
        pop();
    }
}

void Obj_FSM::act1(float x, float y){
    objStates.back()->act1(x,y);
}

void Obj_FSM::act2(float x, float y){
    objStates.back()->act2(x,y);
}

int Obj_FSM::maxThreatsID()
{
    int tMaxID = -1;int tMax = 0;
    for(auto itr = threats.begin();itr!=threats.end();itr++){
        if(itr->second>tMax){
            tMax = itr->second;
            tMaxID = itr->first;
        }
    }
    cout<<__FUNCTION__<<tMaxID<<"*"<<tMax<<endl;
    return tMaxID;
}
