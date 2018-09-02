#ifndef PLANT_H
#define PLANT_H

#include "building.h"

class Plant : public Building
{
public:
    Plant();
    void update();
    void draw();
    void operate();
    void createPhyx();
    static Building *create(string t,float x, float y);
    void drop();//wood&seed
    float growth;//生长进度，到了100%后开始结果，不满100%砍伐量减少
    float fruit;//结果进度，到了100%后可以采集果实
    bool taskChop;
    bool taskGather;
    static map<string,float> growthSpeed;
    static map<string,float> fruitSpeed;
    bool isOperating;
    float chopProcessing;
};

#endif // PLANT_H
