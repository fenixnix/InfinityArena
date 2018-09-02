#include "obj_ammo.h"
#include "Render/nglrender.h"

Obj_Ammo::Obj_Ammo()
{
    life = 30;
    boost.x = 0;
    boost.y = 0;
    parentID = -1;
}

Obj_Ammo::~Obj_Ammo()
{
    release();
}

void Obj_Ammo::draw()
{
    b2Transform tf = this->phyxBody->GetTransform();
    float x = tf.p.x;
    float y = tf.p.y;
    b2Vec2 v = this->phyxBody->GetLinearVelocity();
    v.Normalize();
    v.x = v.x * 0.4;
    v.y = v.y * 0.4;
    //SDL_Render::Instance()->drawObj(sid,x,y,0.5,0.2,0.2);
}

void Obj_Ammo::update()
{
    life -- ;
    if(life<=0){
       isDead = true;
    }
    phyxBody->ApplyForceToCenter(boost,true);
}

void Obj_Ammo::shooting(b2Vec2 dir)
{
    b2Vec2 d;
    dir.Normalize();
    d.x = dir.x*0.3;
    d.y = dir.y*0.3;
    boost = dir;
    //phyxBody->ApplyLinearImpulse(dir,b2Vec2(0,0),true);
}
