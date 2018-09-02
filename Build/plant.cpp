#include "plant.h"
#include "render/nglrender.h"
#include "buildingfactory.h"
#include "ic_map.h"

map<string,float> Plant::growthSpeed;
map<string,float> Plant::fruitSpeed;

Plant::Plant()
{
    growthSpeed.clear();
    fruitSpeed.clear();
    growthSpeed["tree"] = 0.01f;
    growthSpeed["bush"] = 0.03f;
    fruitSpeed["tree"] = 0.01f;
    fruitSpeed["bush"] = 0.08f;
    growth = 99.0f;
    fruit = 0.0f;
    isOperating = false;
    chopProcessing = 1.0f;
}

void Plant::update()
{
    if(growth<100.0f){
        growth+=growthSpeed[type];
    }else{
        //if(fruit<100.0f){
            fruit+=fruitSpeed[type];
            //cout<<fruit<<endl;
        //}
    }
}

void Plant::draw()
{
    NGLRender* render = NGLRender::the();

    if(isOperating){
        render->setMode(MODE_GEO);
        float cl[] = {0,1,0,0.5};
        float clc[] = {0,1,0,0.2};
        render->drawCircle(x,y,0.1,0.5,cl,GL_LINE_LOOP);
        render->drawCircle(x,y,0.1,0.5*(1-chopProcessing),clc,GL_POLYGON);
        isOperating = false;
    }

    render->setMode(MODE_SPRITE);
    render->useTex(type);
    render->setSpriteSize(256);
    render->drawPoint(x,y,0.4);

    if(fruit>=100){
        render->setMode(MODE_SPRITE);
        render->drawTextSprite("+",x,y,0.5,64);
    }
}

void Plant::operate()
{
    //cout<<__FUNCTION__<<endl;
    //if(growth>100){
    isOperating = true;
    chopProcessing -=0.01;
    //}


    if(chopProcessing<0){
        drop();
        BuildingFactory::the()->destroyBuilding(this);
    }
}

void Plant::createPhyx()
{
    if(type == "tree"){
        body = B2Physx::the()->createStaticCircle(x,y,0.2,NULL);
        //cout<<__FUNCTION__<<endl;
        //cout<<x<<"*"<<y<<"*"<<endl;
    }
    if(type == "bush"){
        body = B2Physx::the()->createStaticBox(x,y,0.3,0.3,NULL);
    }
}

Building *Plant::create(string t, float x, float y)
{
    Plant* plant = new Plant;
    plant->type = t;
    plant->x = x;
    plant->y = y;
    return dynamic_cast<Building*>(plant);
}

void Plant::drop()
{
    if(type == string("tree")){
        Item_Common* itc = Item_Common::create(0,10);
        itc->loss(0.8f);
        IC_Map::Instance()->putItemf(x,y,itc);
    }
    if(type == string("bush")){
        Item_Common* itc = Item_Common::create(9,10);
        itc->loss(0.8f);
        IC_Map::Instance()->putItemf(x,y,itc);
    }
}
