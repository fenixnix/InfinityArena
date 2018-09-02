#include "ic_eventmgr.h"
#include "ic_event_massanimalraid.h"

IC_EventMgr* IC_EventMgr::pStatic = nullptr;

IC_EventMgr::IC_EventMgr()
{
    timer = 60;
}

IC_EventMgr *IC_EventMgr::the(){
    if(pStatic == nullptr){
        pStatic = new IC_EventMgr;
    }
    return pStatic;
}

void IC_EventMgr::update()
{
    timer--;
    if(timer<=0){
        IC_Event_MassAnimalRaid e;
        e.start();
        timer = 1000;
    }
}
