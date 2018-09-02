#ifndef GLOBAL_H
#define GLOBAL_H
#include "FSM/fsm.h"
#include "world.h"
#include "render/nglrender.h"
#include "Render/physxdraw.h"

class Global
{
public:
    Global();
    static Global* the(){
        if(p_Static == NULL){
            p_Static = new Global;
        }
        return p_Static;
    }

    World world;
    PhysxDraw draw;
    //FSM fsm;
    bool reloadFlag;
    bool isDrawDebug;

    static float distance(float x1, float y1, float x2, float y2);

private:
    static Global* p_Static;
};

#endif // GLOBAL_H
