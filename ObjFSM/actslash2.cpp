#include "actslash2.h"
#include "obj_statebusy.h"
#include "actslash3.h"
#include "obj_fsm.h"
#include "obj_creature.h"

ActSlash2::ActSlash2()
{
    as = -30.0f;
    ae = 30.0f;
}

void ActSlash2::act1(float x, float y)
{
    cout<<__FUNCTION__<<x<<"*"<<y<<endl;
    ActSlash3 *p = new ActSlash3;
    Obj_StateBusy *b = new Obj_StateBusy;
    parent->obj->endurance -=5;
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

void ActSlash2::begin()
{
    cout<<__FUNCTION__<<endl;
    gt.start(500);
    imw->setAttackRange(as,ae);
    parent->obj->faceTo(b2Vec2(x,y));
}

void ActSlash2::end()
{

}

void ActSlash2::update()
{
    if(gt.getTo()){
        parent->pop();
    }
}
