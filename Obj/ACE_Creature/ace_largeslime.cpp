#include "ace_largeslime.h"
#include "Render/nglrender.h"
#include "Obj/objfactory.h"
#include "b2physx.h"

ACE_LargeSlime::ACE_LargeSlime()
{
    dimension = 2.0f;
    maxLife = 600;
    life = 600;
}

void ACE_LargeSlime::draw()
{
    //cout<<__FUNCTION__<<endl;
    float x = locX;
    float y = locY;
    float s = 1;
    if(!gtInjured.getTo()){
        x+=(float)(rand()%7-3)*0.02f*dimension;
        y+=(float)(rand()%7-3)*0.02f*dimension;
    }
    if(isWalking()){
        s = 2;
    }
    //SDL_Render::the()->drawObj("slime",x,y,0,dimension*life/maxLife,dimension*s*life/maxLife);
}

void ACE_LargeSlime::drawBillboard(float pitch, float yaw)
{
    //cout<<__FUNCTION__<<endl;
    b2Transform tran =  this->phyxBody->GetTransform();
    float x = tran.p.x;
    float y = tran.p.y;
    float s = 1;
//    if(isInjured()){
//        x+=(float)(rand()%7-3)*0.02f*dimension;
//        y+=(float)(rand()%7-3)*0.02f*dimension;
//    }

    if(isWalking()){
        s = 2;
    }
    //SDL_Render::the()->drawObjBillboard("slime",x,y,dimension*life/maxLife,dimension*s*life/maxLife,pitch,yaw);
}

void ACE_LargeSlime::update()
{
    Obj_Creature::update();
}

int ACE_LargeSlime::createByID(float x, float y){
    ACE_LargeSlime* slm = new ACE_LargeSlime;
    slm->phyxBody = B2Physx::the()->createDynamicCircle(x,y,slm->dimension/2,slm);
    int id = ObjFactory::Instance()->addObj2Map(dynamic_cast<Obj*>(slm));
    //slime->ai.pushState(new AI_StateIdle);
    return id;
}
