#include "obj_stateavatar.h"
#include "obj_fsm.h"
#include "obj_statebusy.h"
#include "actslash1.h"
#include "global.h"

Obj_StateAvatar::Obj_StateAvatar()
{

}

void Obj_StateAvatar::act1(float x, float y)
{
    cout<<__FUNCTION__<<x<<"*"<<y<<endl;
    Obj_Human* hm;
    if(parent->obj->type() == string("human")){
        hm = dynamic_cast<Obj_Human*>(parent->obj);
    }else{
        cout<<__FUNCTION__<<"avatar no human!!!"<<endl;
    }
    if(hm->mainhand){
        if(hm->mainhand->getType() == string("melee")){
            Item_MeleeWeapon* imw = Item_MeleeWeapon::convert(hm->mainhand);
            ActSlash1 *p = new ActSlash1;
            Obj_StateBusy *b = new Obj_StateBusy;
            parent->obj->endurance -=p->cost;
            p->imw = imw;
            p->parent = parent;
            p->x = x;
            p->y = y;
            b->parent = parent;
            b->delayTime = p->actTime1;
            b->ready = p;
            parent->push(b);
            return;
        }
    }


}

void Obj_StateAvatar::begin()
{

}

void Obj_StateAvatar::end()
{

}

void Obj_StateAvatar::update()
{
    //do something;
    if(parent->objID != Global::the()->world.avatarID){
        parent->pop();
        return;
    }
}
