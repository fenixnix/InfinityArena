#include "itemfactory.h"
#include "item_common.h"
#include "item_meleeweapon.h"
#include "item_chargerangeweapon.h"

ItemFactory* ItemFactory::p_Static = NULL;

ItemFactory::ItemFactory()
{

}

bool ItemFactory::loadConfig(string fileName)
{
    cout<<__FUNCTION__<<endl;
    itemDoc.LoadFile("ItemPrefab.xml");

    XMLDocument doc;
    doc.LoadFile(fileName.c_str());
    XMLElement* root = doc.RootElement();
    XMLNode* itemNode = root->FirstChild();
    int id = 0;
    //    itemIDIndex.clear();
    //itemNameIndex[0] = "hello";
    while(itemNode){
        XMLElement* itemEle = itemNode->ToElement();
        cout<<string(itemEle->Name());
        string str(itemEle->Name());
        itemIDIndex[str] = id;
        itemNameIndex[id] = str;
        maxStackCountIndex[id] = atoi(itemEle->Attribute("maxStack"));
        cout<<" maxStackCount: "<<maxStackCountIndex[id]<<endl;
        id++;
        itemNode = itemNode->NextSibling();
    }
    return true;
}

int ItemFactory::getMaxStack(int id)
{
    return maxStackCountIndex[id];
}

string ItemFactory::getItemName(int id)
{
    return itemNameIndex[id];
}

int ItemFactory::getItemID(string id)
{
    return itemIDIndex[id];
}

vector<string> ItemFactory::getCraftList()
{
    cout<<__FUNCTION__;
    vector<string> list;
    XMLElement* root = itemDoc.RootElement();
    {
        XMLElement* weapon = root->FirstChildElement("Weapon");
        XMLNode *n = weapon->FirstChild();
        while(n){
            string s = string(n->ToElement()->Name());
            cout<<" "<<s;
            list.push_back(s);
            n = n->NextSibling();
        }
    }
    {
        XMLElement* item = root->FirstChildElement("Item");
        XMLNode *n = item->FirstChild();
        while(n){
            string s = string(n->ToElement()->Name());
            cout<<" "<<s;
            list.push_back(s);
            n = n->NextSibling();
        }
    }
    cout<<endl;
    return list;
}

map<int, int> ItemFactory::getMaterialList(string id)
{
    map<int ,int > materialList;
    XMLElement* item = getItemData(id);
    XMLElement* material = item->FirstChildElement("materialList");
    XMLNode* n = material->FirstChild();
    while(n){
        materialList[n->ToElement()->IntAttribute("id")] = n->ToElement()->IntAttribute("ct");
        n = n->NextSibling();
    }
    return materialList;
}

XMLElement *ItemFactory::getItemData(string id)
{
    XMLElement* root = itemDoc.RootElement();
    XMLNode* typeNode = root->FirstChild();
    while(typeNode){
        XMLNode* n = typeNode->FirstChild();
        while(n){
            if(string(n->ToElement()->Name()) == id){
                return n->ToElement();
            }
            n = n->NextSibling();
        }
        typeNode = typeNode->NextSibling();
    }
    return nullptr;
}

Item *ItemFactory::craftItem(string id, int level)
{
    cout<<__FUNCTION__<<" "<<id<<endl;
    XMLElement* itemData = getItemData(id);
    string type = string(itemData->Attribute("type"));
    cout<<type<<endl;
    if(type == "common"){
        Item_Common *itm = Item_Common::create(id,itemData->IntAttribute("createCount"));
        return dynamic_cast<Item*>(itm);
    }
    if(type == "chargeRange"){
        Item_ChargeRangeWeapon *itm = Item_ChargeRangeWeapon::create(itemData);
        cout<<itm->type<<itm->drawID<<itm->attackRate<<itm<<endl;
        Item* titm = static_cast<Item*>(itm);
        cout<<titm<<endl;
        return titm;
    }
    if(type == "melee"){
        Item_MeleeWeapon *item = new Item_MeleeWeapon;
        item->id = id;
        item->drawID = string(itemData->Attribute("drawID"));
        item->type = string(itemData->Attribute("type"));
        item->dmgType = string(itemData->Attribute("dmgType"));
        item->dmg = itemData->DoubleAttribute("dmg");
        item->attackRate = itemData->DoubleAttribute("attackRate");
        item->maxDurability = itemData->IntAttribute("maxDurability");
        item->durability = item->maxDurability;
        item->strNeed = itemData->IntAttribute("strNeed");
        item->agiNeed = itemData->IntAttribute("agiNeed");
        item->intNeed = itemData->IntAttribute("intNeed");
        return dynamic_cast<Item*>(item);
    }
    return nullptr;
}

