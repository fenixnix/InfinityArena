#ifndef OBJ_HUMAN_H
#define OBJ_HUMAN_H

#include "obj_creature.h"
#include "Item/itemfactory.h"

class Obj_Human :  public Obj_Creature
{
public:
    Obj_Human();
    static Obj_Human* create(float x, float y);
    static int createByID(float x,float y);
    static int randCreate(string tag, float x, float y);
    void draw();
    void drawBillboard(float pitch,float yaw);
    void update();
    void updateTip();
    void useWeapon(b2Vec2 dir);
    bool craft(string id);
    void begin(PhysxObj*);
    void processDmg(Obj_Dmg* dmg);
    void die();
    string type(){
        return "human";
    }

    bool isCreature(){
        return true;
    }

    Item* mainhand;
    Item* offhand;
    bool isArming;
    string name;
    string team;

    int tipCount;
};

#endif // OBJ_HUMAN_H
