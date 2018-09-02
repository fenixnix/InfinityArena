#include "actslash1.h"
#include "obj_statebusy.h"
#include "actslash2.h"
#include "obj_fsm.h"
#include "obj_creature.h"
#include "obj_human.h"

ActSlash1::ActSlash1()
{
    as = 60.0f;
    ae = -30.0f;
    cost = 4.0f;
    actTime1 = 200;
    actTime2 = 500;
}

void ActSlash1::act1(float x, float y)
{
    cout<<__FUNCTION__<<x<<"*"<<y<<endl;
    ActSlash2 *p = new ActSlash2;
    Obj_StateBusy *b = new Obj_StateBusy;
    parent->obj->endurance -=3;
    p->parent = parent;
    p->imw = imw;
    p->x = x;
    p->y = y;
    b->parent = parent;
    b->delayTime = 200;
    b->ready = p;
    parent->change(b);
    return;
}

void ActSlash1::begin()
{
    cout<<__FUNCTION__<<endl;
    gt.start(actTime2);
    imw->setAttackRange(as,ae);
    parent->obj->faceTo(b2Vec2(x,y));
    parent->obj->dash(b2Vec2(x,y));
}

void ActSlash1::end()
{

}

void ActSlash1::update()
{
    if(gt.getTo()){
        parent->pop();
    }
}
