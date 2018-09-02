#include "building.h"
#include "render/nglrender.h"
#include "b2physx.h"

Building::Building()
{
    hp = 1;
    maxHp = 1;
    w = 1;
    h = 1;
    dimension = 1.0f;
    dir = 0;
    isPrefab = false;
    body == NULL;
    isDead = false;
    drawID = "none";
}

void Building::operate()
{
    //cout<<__FUNCTION__<<endl;
}

void Building::active()
{
    //cout<<__FUNCTION__<<endl;
}

void Building::createPhyx()
{
    cout<<__FUNCTION__<<endl;
    //cout<<x<<"*"<<y<<"*"<<w<<"*"<<h<<endl;
    body = B2Physx::the()->createStaticBox(x,y,w,h,NULL);
}

void Building::destroyPhyx()
{
    if(body){
        B2Physx::the()->releaseBody(body);
        body = nullptr;
    }
}

void Building::draw()
{
    //cout<<__FUNCTION__<<drawID<<endl;
    NGLRender* render = NGLRender::the();
    render->setMode(MODE_GEO);
    float cl[] = {1,1,0,0.7};
    render->drawRect(x,y,0.1,w,h,cl);
    render->setMode(MODE_SPRITE);
    render->drawTextSprite(drawID,x,y,0.5,128);
}

void Building::update()
{

}

