#ifndef OBJ_CREATURE_H
#define OBJ_CREATURE_H

#include "physxobj.h"
#include "obj_dmg.h"
#include "ObjFSM/obj_fsm.h"
#include "globaltimer.h"
#include "container.h"

class Obj_FSM;

class Obj_Creature : public PhysxObj
{
public:
    Obj_Creature();
    ~Obj_Creature();
    virtual void draw() = 0;
    virtual void drawBillboard(float pitch,float yaw) = 0;
    virtual void update();

    virtual string type(){
        return "creature";
    }
    virtual string classify(){
        return "none";
    }

    bool isCreature(){
        return true;
    }
    void begin(PhysxObj * obj);

    b2Vec2 taget;
    virtual void walk(b2Vec2 v);
    virtual void run(b2Vec2 v);
    virtual void dash(b2Vec2 v);
    virtual void faceTo(b2Vec2 v);
    virtual void stop();
    virtual void operateOnMap();
    virtual void activeOnMap(b2Vec2 pos);
    virtual void attack();
    virtual void move();
    virtual void processDmg(Obj_Dmg* dmg);
    virtual void addThreats(int id, int value);
    virtual void die();

    bool isWalking();

    float locX;
    float locY;
    b2Vec2 face;
    float movSpeed;

    Container bag;

    string drawID;
    string alignment;

    float sight;
    vector<int> sights;
    float dimension;

    float life;
    float maxLife;
    float endurance;
    float maxEndurance;
    float stamina;
    float maxStamina;

    float dmgRateSlash;
    float dmgRateStab;
    float dmgRateBlunt;
    float dmgRateHeat;
    float dmgRateCold;
    float dmgRateElectric;
    float dmgRatePosion;

//private:
    GlobalTimer gtInjured;
    Obj_FSM fsm;
    bool getDie() const;
};

#endif // OBJ_CREATURE_H
