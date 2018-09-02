#include "building_treasure.h"
#include "ic_map.h"
#include "Build/buildingfactory.h"
#include "Item/itemfactory.h"

Building_Treasure::Building_Treasure()
{

}

//void drawChest(float x, float y, float z){

//    glPushMatrix();
//    glTranslatef(x,y,z);

//    glPushMatrix();
//    glTranslatef(0,0,0.5);
//    glScalef(0.4,0.4,1);
//    SDL_Render::the()->drawObj("ChestCover",0,0,0);
//    glPopMatrix();
//    glPushMatrix();
//    glTranslatef(0,0.2,0);
//    glScalef(0.4,0,0.5);
//    SDL_Render::the()->drawHWall("ChestCover");
//    glPopMatrix();
//    glPushMatrix();
//    glTranslatef(0,-0.2,0);
//    glScalef(0.4,0,0.5);
//    SDL_Render::the()->drawHWall("ChestCover");
//    glPopMatrix();
//    glPushMatrix();
//    glTranslatef(0.2,0,0);
//    glScalef(0,0.4,0.5);
//    SDL_Render::the()->drawVWall("ChestCover");
//    glPopMatrix();
//    glPushMatrix();
//    glTranslatef(-0.2,0,0);
//    glScalef(0,0.4,0.5);
//    SDL_Render::the()->drawVWall("ChestCover");
//    glPopMatrix();

//    glPopMatrix();
//}

void Building_Treasure::draw()
{
    //drawChest(x,y,0);
}

void Building_Treasure::active()
{
    IC_Map::Instance()->putItemf(x,y,Item_Common::create("log",10));
    BuildingFactory::the()->destroyBuilding(this);
}

void Building_Treasure::createPhyx()
{
    body = B2Physx::the()->createStaticBox(x,y,wSize,hSize,nullptr);
}

Building *Building_Treasure::create(string id, float x, float y)
{
    Building_Treasure* b = new Building_Treasure;
    b->x = x;
    b->y = y;
    b->w = 1;
    b->h = 1;
    b->wSize = 0.4f;
    b->hSize = 0.4f;
    return dynamic_cast<Building*>(b);
}
