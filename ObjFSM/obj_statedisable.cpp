#include "obj_statedisable.h"
#include "obj_fsm.h"

Obj_StateDisable::Obj_StateDisable()
{

}

void Obj_StateDisable::begin()
{
    gt.start(delayTime);
    cout<<__FUNCTION__<<parent->objID<<endl;
}

void Obj_StateDisable::end()
{
    cout<<__FUNCTION__<<endl;
}

void Obj_StateDisable::update()
{
    //cout<<__FUNCTION__<<parent->objID<<endl;
    if(gt.getTo()){
        parent->pop();
        return;
    }
}
