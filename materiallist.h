#ifndef MATERIALLIST_H
#define MATERIALLIST_H

#include "Item/item.h"
#include <Item/item_common.h>
#include <vector>
#include <map>

using namespace std;

class ItemSlot
{
public:
    ItemSlot(){

    }

    void set(int c,int m){
        cnt = c;
        max = m;
    }

    int add(int i){
        cnt += i;
        int rt = cnt - max;
        if(rt>0){
            cnt = max;
        }
        return rt;
    }
    bool full(){
        return cnt>=max;
    }
    int cnt;
    int max;
};

class MaterialList
{
public:
    MaterialList();
    ~MaterialList();
    //void draw(float x, float y);
    Item_Common *addMaterial(Item_Common*);
    vector<Item_Common *> returnMaterials();
    void init(map<int,int> *mats);
    void clone(MaterialList* mp);
    bool ready();
    void printState();
//private:
    int id;//building ID
//    map<int,int> materials;
//    map<int,int> needs;
    map<int,ItemSlot> mtls;
};

#endif // MATERIALLIST_H
