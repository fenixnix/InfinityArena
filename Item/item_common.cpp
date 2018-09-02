#include "item_common.h"
#include "item/itemfactory.h"

Item_Common::Item_Common()
{

}

Item_Common *Item_Common::stack(Item_Common *newItem)
{
    if(newItem->id!=id){
        return newItem;
    }
    int maxStack = ItemFactory::the()->getMaxStack(id);
    if(stackCount>=maxStack){
        return newItem;
    }
    stackCount = stackCount+newItem->stackCount;
    if(stackCount>maxStack){
        newItem->stackCount = stackCount - maxStack;
        stackCount = maxStack;
        return newItem;
    }
    delete newItem;
    return nullptr;
}

void Item_Common::loss(float rate)
{
    int count = 0;
    for(int i = 0;i<stackCount;i++){
        if(rand()%100<rate*100){
            count++;
        }
    }
    stackCount = count;
}

string Item_Common::getDrawID(){
    return ItemFactory::the()->getItemName(id);
}

bool Item_Common::isArrow(){
    if(ItemFactory::the()->getItemName(id)==string("arrow")){
        return true;
    }
}

Item_Common *Item_Common::create(int id, int count){
    Item_Common *itm = new Item_Common;
    itm->id = id;
    itm->stackCount = count;
    return itm;
}

Item_Common *Item_Common::create(string id, int count){
    Item_Common *itm = new Item_Common;
    itm->id = ItemFactory::the()->getItemID(id);
    itm->stackCount = count;
    //cout<<__FUNCTION__<<": "<<itm->id<<"*"<<itm->stackCount<<endl;
    return itm;
}



Item_Common *Item_Common::convert(Item *itm)
{
    return dynamic_cast<Item_Common*>(itm);
}
