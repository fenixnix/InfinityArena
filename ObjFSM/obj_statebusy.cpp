#include "obj_statebusy.h"
#include "ObjFSM/obj_fsm.h"

Obj_StateBusy::Obj_StateBusy()
{

}

void Obj_StateBusy::begin()
{
    gt.start(delayTime);
    //cout<<__FUNCTION__<<parent->objID<<endl;
}

void Obj_StateBusy::end()
{
    //cout<<__FUNCTION__<<endl;
}

void Obj_StateBusy::update()
{
    //all state to Interupt
    if(gt.getTo()){
        //this->parent->pop();
        this->parent->change(ready);
    }
}
