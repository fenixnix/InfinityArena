#include "item_chargerangeweapon.h"
#include <Obj/obj_ammo.h>
#include <Item/item_common.h>

Item_ChargeRangeWeapon::Item_ChargeRangeWeapon()
{
    ownerID = -1;
}

Item_ChargeRangeWeapon *Item_ChargeRangeWeapon::create(XMLElement *ele)
{
    Item_ChargeRangeWeapon* itm = new Item_ChargeRangeWeapon;
    itm->id = string(ele->Name());
    itm->drawID = string(ele->Attribute("drawID"));
    itm->type = string(ele->Attribute("type"));
    itm->attackRate = ele->DoubleAttribute("attackRate");
    itm->baseForce = ele->DoubleAttribute("baseForce");
    itm->chargeSpeed =  ele->DoubleAttribute("chargeSpeed");
    itm->maxChargeTime = ele->DoubleAttribute("maxChargeTime");
    return itm;
}

void Item_ChargeRangeWeapon::drawWeapon(Item *itm)
{
    if(itm){
        if(itm->isCommon()){
            Item_Common* itmc = Item_Common::convert(itm);
            if(itmc->isArrow()){
                cout<<__FUNCTION__<<endl;
                chargeValue = 0.0f;
                chargeTime = 0;
                isDrawing = true;
            }
        }
    }
}

void Item_ChargeRangeWeapon::update()
{
    cout<<__FUNCTION__<<endl;
    if(isDrawing){
        if(chargeTime<maxChargeTime){
            chargeValue+=chargeSpeed;
        }
        chargeTime++;
        if(chargeTime>(2*maxChargeTime)){
            chargeValue = 0.0f;
            chargeTime = 0;
            isDrawing = false;
        }
    }
}

void Item_ChargeRangeWeapon::loss(Item *itm, b2Vec2 pos, b2Vec2 dir)
{
    cout<<__FUNCTION__<<endl;
    if(isDrawing){
        cout<<__FUNCTION__<<__LINE__<<endl;
        Obj_Ammo* ammo = Obj_Ammo::create("arrow",pos);
        ammo->parentID = ownerID;
        ammo->shooting(dir);
        if(itm->isCommon()){
            Item_Common* itmc = Item_Common::convert(itm);
            itmc->stackCount--;
        }
    }
}
