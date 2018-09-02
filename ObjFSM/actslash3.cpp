#include "actslash3.h"
#include "obj_fsm.h"
#include "obj_creature.h"

ActSlash3::ActSlash3()
{
    as = 120.0f;
    ae = -30.0f;
}

void ActSlash3::begin()
{
    cout<<__FUNCTION__<<endl;
    gt.start(500);
    imw->setAttackRange(as,ae);
    parent->obj->faceTo(b2Vec2(x,y));
    parent->obj->dash(b2Vec2(-x,-y));
}

void ActSlash3::end()
{

}

void ActSlash3::update()
{
    if(gt.getTo()){
        parent->pop();
    }
}
