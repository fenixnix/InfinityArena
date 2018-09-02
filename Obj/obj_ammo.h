#ifndef OBJ_AMMO_H
#define OBJ_AMMO_H

#include <physxobj.h>
#include <b2physx.h>
#include <objfactory.h>
#include <Obj/obj_creature.h>

class Obj_Ammo : public PhysxObj
{
public:
    Obj_Ammo();
    ~Obj_Ammo();
    void draw();
    void update();
    bool isAmmo(){
        return true;
    }

    string type(){
        return "ammo";
    }

    static Obj_Ammo* create(string cid,b2Vec2 pos){
        Obj_Ammo* ammo = new Obj_Ammo;
        if(cid == "arrow"){
            ammo->phyxBody = B2Physx::the()->createCircleBullet(0.05,pos,ammo);
        }
        ammo->sid = cid;
        ObjFactory::Instance()->addObj(ammo);
        return ammo;
    }

    static Obj_Ammo* convert(PhysxObj* o){
        return dynamic_cast<Obj_Ammo*>(o);
    }

    void shooting(b2Vec2 dir);

    void begin(PhysxObj *o){
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
            objc->processDmg(dmg);
        }
        cout<<__FUNCTION__<<endl;
    }
    int parentID;
private:
    int life;
    b2Vec2 boost; 
};

#endif // OBJ_AMMO_H
