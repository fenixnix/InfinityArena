#include "obj_dmg.h"
#include <Obj/obj_creature.h>

Obj_Dmg::Obj_Dmg()
{

}

void Obj_Dmg::update()
{
    isDead = true;
}

void Obj_Dmg::draw()
{

}

void Obj_Dmg::begin(PhysxObj *o){
    cout<<__FUNCTION__<<o<<"*"<<this<<endl;
    this->isDead = true;
    b2Vec2 vp = this->phyxBody->GetLinearVelocity();
    cout<<"vp: "<<vp.x<<"*"<<vp.y<<endl;
    //??o is exist?
    if(o->isCreature()){
        cout<<__FUNCTION__<<__LINE__<<endl;
        Obj_Creature* objc = dynamic_cast<Obj_Creature*>(o);
        Obj_Dmg *dmg = new Obj_Dmg;
        dmg->parentID = this->parentID;
        DMG d;
        d.type = SLASH;
        d.value = 30;
        dmg->dmgs.push_back(d);
        if(objc->id != parentID){
            objc->processDmg(dmg);
        }
    }
    cout<<__FUNCTION__<<endl;
}

