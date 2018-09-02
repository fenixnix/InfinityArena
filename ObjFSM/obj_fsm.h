#ifndef OBJ_FSM_H
#define OBJ_FSM_H

#include "ai_feature.h"
#include "obj_state.h"
#include <vector>
#include <map>

using namespace std;

class Obj_Creature;

class Obj_FSM : public AI_Feature
{
public:
    Obj_FSM();
    string getCurrentState();
    string getCurrentState(float &percent);
    void update();
    void push(Obj_State* state);
    void change(Obj_State* state);
    void pop();
    void clear();
    void act1(float x, float y);
    void act2(float x, float y);
    int objID;
    Obj_Creature* obj;
    int maxThreatsID();
//private:
    vector<Obj_State*> objStates;
    map<int,int> threats;
    Obj_State* anyState;
};

#endif // OBJ_FSM_H
