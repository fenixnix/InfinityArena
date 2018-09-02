#ifndef OBJ_STATE_H
#define OBJ_STATE_H

#include "globaltimer.h"
#include <iostream>

using namespace std;

class Obj_FSM;

class Obj_State
{
public:
    Obj_State(){
        parent = nullptr;
    }

    Obj_State(Obj_FSM* p){
        parent = p;
    }
    virtual string getID() = 0;
    virtual float getFrame() = 0;
    virtual void begin() = 0;
    virtual void end() = 0;
    virtual void update() = 0;
    virtual void act1(float x, float y){

    }
    virtual void act2(float x, float y){

    }
    Obj_FSM* parent;
};

#endif // OBJ_STATE_H
