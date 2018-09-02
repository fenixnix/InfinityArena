#include "container.h"
#include "sdl_render.h"

Container::Container()
{

}

Container::~Container()
{
    clear();
}

void Container::init(unsigned int size)
{
    clear();
    items.assign(size,NULL);
}

void Container::clear()
{
    for(auto itr = items.begin();itr!=items.end();itr++){
        delete *itr;
    }
    items.clear();
}

bool Container::have(map<int, int> *ml)
{
    map<int,int> count;
    for(int i = 0;i<items.size();i++){
        bool ready = true;
        if(items[i]==nullptr){
            continue;
        }
        for(auto itr = ml->begin();itr!=ml->end();itr++){
            if(items[i]->isCommon()){
                Item_Common* itmc = Item_Common::convert(items[i]);
                if(itr->first == itmc->id){
                    count[itr->first] += itmc->stackCount;
                }
            }
            //cout<<"itemID:"<<itr->first<<" count:"<<count[itr->first]<<endl;
            if(count[itr->first]>=itr->second){
                ready &= true;
            }else{
                ready &= false;
            }
        }
        if(ready){
            return true;
        }
    }
    return false;
}

size_t Container::size()
{
    return items.size();
}

Item *Container::put(Item * item)
{
    //cout<<__FUNCTION__<<endl;
    if(item == nullptr){
        return nullptr;
    }

    //can stack
    for(auto itr = items.begin();itr!=items.end();itr++){
        if(item!=nullptr){
//            if(item == *itr){
//                cout<<"!!!same address"<<item<<endl;
//            }
            Item* it = *itr;
            if(it&&item){
                if(it->isCommon()&&item->isCommon()){
                    //cout<<__LINE__<<it->getDrawID()<<endl;
                    //cout<<__LINE__<<item->getDrawID()<<endl;
                    Item_Common* itc = Item_Common::convert(*itr);
                    Item_Common* itemc = Item_Common::convert(item);
                    if(itc->stack(itemc) == nullptr){
                        return nullptr;
                    }
                }
            }
        }
    }

    //put in space
    for(auto itr = items.begin();itr!=items.end();itr++){
        Item* it = *itr;
        if(it == nullptr){
            (*itr) = item;
            return nullptr;
        }
    }
    return item;
}

Item *Container::take(unsigned int pos)
{
    Item* it = items[pos];
    items[pos] = nullptr;
    return it;
}

Item *Container::at(unsigned int pos)
{
    return items[pos];
}

Item *Container::take()
{
    for(int i = 0;i<items.size();i++){
        if(items[i]!=NULL){
            return take(i);
        }
    }
    return NULL;
}

bool Container::cost(int id, int count)
{
    cout<<__FUNCTION__<<endl;
    int sum = 0;
    for(int i = 0;i<items.size();i++){
        if(items[i]!=nullptr){
            if(items[i]->isCommon()){
                Item_Common *itmc = Item_Common::convert(items[i]);
                if(itmc->id == id){
                    if((itmc->stackCount+sum)>count){
                        itmc->stackCount -= (count-sum);
                        sum +=(count-sum);
                    }else{
                        sum += itmc->stackCount;
                        delete itmc;
                        items[i] = nullptr;
                    }
                }
                if(sum==count){
                    return true;
                }
            }
        }
    }
    return false;
}
