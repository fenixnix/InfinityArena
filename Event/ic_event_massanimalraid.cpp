#include "ic_event_massanimalraid.h"
#include "ic_map.h"
#include "Obj/objfactory.h"
#include "obj/obj_beast.h"

IC_Event_MassAnimalRaid::IC_Event_MassAnimalRaid()
{

}

void IC_Event_MassAnimalRaid::start()
{
    cout<<__FUNCTION__;
    int x,y;
    IC_Map::Instance()->randomRound(x,y);
    cout<<"x:"<<x<<" y:"<<y;
    for(int i = 0;i<1;i++){
        Obj_Beast* bst =  dynamic_cast<Obj_Beast*>(Obj_Beast::create("wolf",x,y));
        bst->fsm.raid = true;
    }
    cout<<endl;
}
