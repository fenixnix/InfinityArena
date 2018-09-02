#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <b2physx.h>

using namespace std;

class Building
{
public:
    Building();
    ~Building(){
        if(body){
        B2Physx::the()->releaseBody(body);
        body = nullptr;
        }
    }

    float x;
    float y;
    int w;
    int h;
    float wSize;
    float hSize;
    float dimension;
    int dir;
    int hp;
    float dirX;
    float dirY;

    //int id;
    string id;
    string type;
    string drawID;
    int maxHp;


    bool isPrefab;
    bool isHarvestable;
    bool isDead;
    virtual void operate();
    virtual void active();
    b2Body* body;

    virtual void createPhyx();
    virtual void destroyPhyx();

    virtual void draw();
    virtual void update();
};

#endif // BUILDING_H
