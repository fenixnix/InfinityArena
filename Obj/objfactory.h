#ifndef OBJFACTORY_H
#define OBJFACTORY_H

#include <vector>
#include <map>
#include "obj.h"
#include "Obj/obj_human.h"

using namespace std;

class ObjFactory
{
public:
    ObjFactory();
    void update();
    void draw();
    void draw(float x, float y, float r);
    void drawBillboard(float pitch,float yaw);
    void drawBillboard(float x, float y, float r, float pitch, float yaw);
    static ObjFactory* Instance(){
        if(p_static == 0){
            p_static = new ObjFactory;
        }
        return p_static;
    }
    void addObj(Obj*);
    int addObj2Map(Obj*);
    Obj *getObjOnMap(int id);
    Obj_Human *getHumanObj(int id);
    Obj_Creature *getCreatureObj(int id);
    void removeObj(int id);//just remove from factory;

    bool addThreats(int id, int tid,int value);

    void clearSight();
    void checkSight(Obj* A,Obj* B);

    void refreshSight();

    void clear();

//private:
    static ObjFactory* p_static;
    vector<Obj*> objs; //no interactive Object
    map<int,Obj*>objsMap;//interactive Object
    int uniid;

};

#endif // OBJFACTORY_H
