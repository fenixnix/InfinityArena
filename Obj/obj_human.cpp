#include "obj_human.h"
#include "b2physx.h"
#include "objfactory.h"
#include "obj_dmg.h"
#include "Item/itemfactory.h"
#include "materiallist.h"
#include "global.h"


Obj_Human::Obj_Human()
{
    sid = "Human";
    dimension = 0.2f;
    movSpeed = 2.0;
    bag.init(12);

    name = "Nix";

    mainhand = nullptr;
    offhand = nullptr;
    isArming = false;
    //bag.put(ItemFactory::Instance()->craftItem("Club",0));
    mainhand = ItemFactory::the()->craftItem("Club",0);
    if(mainhand->getType() == string("melee")){
        Item_MeleeWeapon* imw = Item_MeleeWeapon::convert(mainhand);
        imw->ownerID = id;
    }
    bag.put(ItemFactory::the()->craftItem("Bow",0));
    bag.put(ItemFactory::the()->craftItem("arrow",0));
    bag.put(ItemFactory::the()->craftItem("arrow",0));
    bag.put(ItemFactory::the()->craftItem("arrow",0));
    bag.put(Item_Common::create("log",30));
    bag.put(Item_Common::create("pile",30));
}

Obj_Human *Obj_Human::create(float x, float y)
{
    Obj_Human * human = new Obj_Human;
    human->fsm.AI_Feature::stroll = false;
    human->fsm.AI_Feature::rage = true;
    human->fsm.AI_Feature::cmd_defence = true;
    human->phyxBody = B2Physx::the()->createDynamicCircle(x,y,human->dimension,human);
    return human;
}

int Obj_Human::createByID(float x, float y)
{
    Obj_Human* human = create(x,y);
    int id =  ObjFactory::Instance()->addObj2Map(dynamic_cast<Obj*>(human));
    return id;
}

int Obj_Human::randCreate(string tag, float x, float y)
{
    Obj_Human *hm = new Obj_Human;
    if(tag == string("zombie")){
        //cout<<__FUNCTION__<<x<<"*"<<y<<endl;
        hm->maxLife = 200;
        hm->life = 200;
        hm->movSpeed = 1.0f;
        hm->alignment = "wild";
        hm->fsm.stroll = false;
        hm->fsm.warlike = true;
        hm->fsm.rage = true;
        hm->sight = 3.5f;
    }
    //cout<<__FUNCTION__<<__LINE__<<endl;
    hm->phyxBody = B2Physx::the()->createDynamicCircle(x,y,hm->dimension,hm);
    int id =  ObjFactory::Instance()->addObj2Map(dynamic_cast<Obj*>(hm));
    //cout<<__FUNCTION__<<__LINE__<<"id: "<<id<<endl;
    return id;
}

void Obj_Human::draw()
{
    b2Transform tra = this->phyxBody->GetTransform();
    NGLRender* render = NGLRender::the();
    render->setMode(MODE_SPRITE);
    render->drawTextSprite("@",tra.p.x,tra.p.y,dimension/2,64);
    render->setMode(MODE_GEO);
    float cl[] = {0,1,0,0.7};
    render->drawCircle(tra.p.x,tra.p.y,0.01,dimension,cl,GL_LINE_LOOP);
//    glPushMatrix();
//    glTranslated(tra.p.x,tra.p.y,dimension/2);
//    glScalef(dimension,dimension,dimension);

//    b2Vec2 v;
//    v.x = face.x;
//    v.y = face.y;
//    v.Normalize();
//    sprite.draw(v.x,v.y);


//    glPopMatrix();
}

void Obj_Human::drawBillboard(float pitch, float yaw)
{

}

void Obj_Human::update()
{
    //cout<<__FUNCTION__<<endl;
    Obj_Creature::update();
    tipCount++;
    if(tipCount>=15){
        updateTip();
        tipCount = 0;
    }
}

void Obj_Human::updateTip()
{

}

void Obj_Human::useWeapon(b2Vec2 dir)
{
    cout<<__FUNCTION__<<" x:"<<dir.x<<" y: "<<dir.y<<endl;
    Obj_Dmg* dmg = new Obj_Dmg;
    cout<<dmg<<endl;
    DMG d;
    d.type = SLASH;
    d.value = 8;
    dmg->dmgs.push_back(d);
    dmg->parentID = id;
    b2Transform tra = this->phyxBody->GetTransform();
    dmg->phyxBody = B2Physx::the()->createFanSenser(tra.p,dir,0.3,dmg);
    ObjFactory::Instance()->addObj(dmg);

//    if(mainhand){
//        cout<<__FUNCTION__<<__LINE__<<endl;
//        if(mainhand->getType() == string("melee")){
//            Item_MeleeWeapon * weapon = Item_MeleeWeapon::convert(mainhand);
//            dir *= weapon->length;
//            b2Vec2 attackPoint = this->phyxBody->GetTransform().p+dir;
//            //AnimateEffect::instance()->emitEffect("punch","",attackPoint.x,attackPoint.y,weapon->length);

//            int count = weapon->hitNum;
//            //cout<<__FUNCTION__<<__LINE__<<endl;
//            for(auto itr = sights.begin();itr!=sights.end();itr++){
//                Obj* obj = ObjFactory::Instance()->getObjOnMap( *itr);
//                if(obj->isCreature()){
//                    Obj_Creature *oc = dynamic_cast<Obj_Creature*>(obj);
//                    if((attackPoint-oc->phyxBody->GetTransform().p).Length()<weapon->range){
//                        Obj_Dmg *dmg = new Obj_Dmg;
//                        dmg->parentID = this->id;
//                        DMG d;
//                        d.type = SLASH;
//                        d.value = 30;
//                        dmg->dmgs.push_back(d);
//                        oc->processDmg(dmg);
//                        count--;
//                    }
//                }

//                if(count<=0){
//                    break;
//                }
//            }
//        }
//    }
}

bool Obj_Human::craft(string id)
{
    //cout<<__FUNCTION__<<" "<<id<<endl;
    map <int,int> mlpre = ItemFactory::the()->getMaterialList(id);
    //cout<<__FUNCTION__<<" "<<mlpre.size()<<endl;
    bool h = bag.have(&mlpre);
    //cout<<__FUNCTION__<<" have:" << h<<endl;
    if(h){
        Item* itm = ItemFactory::the()->craftItem(id,1);
        if(itm == nullptr){
            //cout<<__FUNCTION__<<"*"<<__LINE__<<"*"<<"createFault!!!"<<endl;
        }
        if(itm){
            for(auto itr = mlpre.begin();itr!=mlpre.end();itr++){
                if(!bag.cost(itr->first,itr->second)){
                    //cout<<__FUNCTION__<<" "<<id<<" cost material error!!!"<<endl;
                }
            }
            bag.put(itm);
            //cout<<__FUNCTION__<<__LINE__<<endl;
            //throw rest to floor;
            //Global::the()->craftUI()->updateContainer(&bag);
        }
        return true;
    }
    return false;
}

void Obj_Human::begin(PhysxObj *obj)
{
    Obj_Creature::begin(obj);
}

void Obj_Human::processDmg(Obj_Dmg *dmg)
{
    Obj_Creature::processDmg(dmg);
//    vector<int> team = Global::Instance()->world.getTeamList();
//    cout<<__FUNCTION__<<"team size: "<<team.size()<<" tagID:"<<dmg->parentID;
//    for(int i = 0;i<team.size();i++)
//    {
//        cout<<"*"<<team[i];
//        ObjFactory::Instance()->addThreats(team[i],dmg->parentID,40);
//    }
//    cout<<endl;
}

void Obj_Human::die()
{
    if(id == Global::the()->world.avatarID){
        cout<<"Avatar die ! auto change Avatar"<<endl;
        if(Global::the()->world.getTeamList().empty()){
            cout<<"no Avatar to Change!! Game Over"<<endl;
        }
        Global::the()->world.nextAvatar();
    }
    Obj_Creature::die();
}

