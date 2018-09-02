#include "materiallist.h"
#include "sdl_render.h"
#include "Item/itemfactory.h"
#include "Build/buildingfactory.h"

MaterialList::MaterialList()
{

}

MaterialList::~MaterialList()
{
//    materials.clear();
//    needs.clear();
    mtls.clear();
}

Item_Common *MaterialList::addMaterial(Item_Common * itm)
{
    if(itm==nullptr){
        return nullptr;
    }

    for(auto itr = mtls.begin();itr!=mtls.end();itr++){
        if(itm->id == itr->first){
            int rt = itr->second.add(itm->stackCount);
            if(rt<=0){
                delete itm;
                return nullptr;
            }
            itm->stackCount = rt;
            return itm;
        }
    }
    return itm;
}

vector<Item_Common *> MaterialList::returnMaterials()
{
    vector<Item_Common *> items;
    for(auto itr = mtls.begin();itr!=mtls.end();itr++){
        if(itr->second.cnt>0){
            Item_Common* itc = Item_Common::create(itr->first,itr->second.cnt);
            items.push_back(itc);
        }
    }
    return items;
}

void MaterialList::init(map<int, int> *mats)
{
    for(auto itr = mats->begin();itr != mats->end();itr++){
        //materials[itr->first] = 0;
        //needs[itr->first] = itr->second;
        ItemSlot slot;
        slot.set(0,itr->second);
        mtls[itr->first] = slot;
    }
}

void MaterialList::clone(MaterialList *mp)
{
    if(mp==NULL){
        return;
    }
    id = mp->id;
    mtls.clear();
    mtls = mp->mtls;
}

bool MaterialList::ready()
{
    for(auto itr = mtls.begin();itr!=mtls.end();itr++){
        if(!itr->second.full()){
            return false;
        }
    }
    return true;
}

void MaterialList::printState()
{
    cout<<__FUNCTION__<<endl;
    for(auto itr = mtls.begin();itr!=mtls.end();itr++){
        ItemSlot slot = itr->second;
        cout<<itr->first<<":"<<slot.cnt<<"/"<<slot.max<<endl;
    }
}

