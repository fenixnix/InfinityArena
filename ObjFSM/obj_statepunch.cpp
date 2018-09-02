#include "obj_statepunch.h"
#include "objfactory.h"
#include "obj_statedisable.h"
#include "obj_dmg.h"
#include "obj_creature.h"

Obj_StatePunch::Obj_StatePunch()
{

}

void Obj_StatePunch::begin()
{
    cout<<__FUNCTION__<<" id: "<<parent->objID<<endl;
    Obj_Creature *oc = ObjFactory::Instance()->getCreatureObj(aimID);
    if(oc){
        Obj_Dmg *dmg = new Obj_Dmg;
        dmg->parentID = parent->objID;
        DMG d;
        d.type = BLUNT;
        d.value = 7;
        dmg->dmgs.push_back(d);
        oc->processDmg(dmg);
    }else{
        cout<<__FUNCTION__<<" id: "<<parent->objID<<"taget miss!!!"<<aimID<<endl;
        parent->pop();
        return;
    }

}

void Obj_StatePunch::end()
{
    cout<<__FUNCTION__<<endl;
}

void Obj_StatePunch::update()
{
    cout<<__FUNCTION__<<" id: "<<parent->objID<<endl;
    Obj_StateDisable *s = new Obj_StateDisable;
    s->parent = parent;
    s->delayTime = 500;
    parent->change(s);
    return;
}
