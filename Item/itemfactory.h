#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "item/item.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <tinyxml2.h>

using namespace tinyxml2;

using namespace std;

class ItemFactory
{
public:
    ItemFactory();
    static ItemFactory* the(){
        if(p_Static == NULL){
            p_Static  = new ItemFactory;
            cout<<"new ItemFactory"<<endl;
        }
        return p_Static;
    }
    bool loadConfig(string fileName);
    int getMaxStack(int id);
    string getItemName(int id);
    int getItemID(string id);

    vector<string> getCraftList();
    map<int,int> getMaterialList(string id);
    //XMLElement *getWeaponData(string id);
    XMLElement *getItemData(string id);
    Item* craftItem(string id,int level);
    Item *create(string id);

private:
    static ItemFactory* p_Static;
    map<string, int> itemIDIndex;
    map<int , string> itemNameIndex;
    map<int , int> maxStackCountIndex;
    XMLDocument itemDoc;
};

#endif // ITEMFACTORY_H
