#include "obj_creature.h"
#include "obj_dmg.h"
#include "ic_map.h"
#include "objfactory.h"

Obj_Creature::Obj_Creature() : maxLife(100),life(maxLife)
{
    isDead = false;
    alignment = "wild";
    movSpeed = 1.0f;
    sight = 3.0f;
    dimension = 1.0f;
    life = 80;
    maxLife = 100;
    endurance = 100;
    maxEndurance = 100;
    stamina = 100;
    maxStamina = 100;
    dmgRateSlash=1.0f;
    dmgRateStab=1.0f;
    dmgRateBlunt=1.0f;
    dmgRateHeat=1.0f;
    dmgRateCold=1.0f;
    dmgRateElectric=1.0f;
    dmgRatePosion=1.0f;
    bag.init(4);
    gtInjured.start(0);
}

Obj_Creature::~Obj_Creature()
{
    release();
}

void Obj_Creature::draw()
{

}

void Obj_Creature::drawBillboard(float pitch, float yaw)
{

}

void Obj_Creature::update()
{
    //cout<<__FUNCTION__<<life<<endl;
    if(phyxBody == nullptr){
        cout<<__FUNCTION__<<"null phyxbody!!!"<<endl;
        return;
    }
    b2Transform tra = phyxBody->GetTransform();
    locX = tra.p.x;
    locY = tra.p.y;

    if(maxEndurance-endurance>=0.1){
        stamina-=0.05;
        endurance+=0.2;
    }
    if(endurance<0){
        endurance = 0;
    }
    if(stamina<0.1){
        life-=0.5;
        stamina += 1;
    }
    if(stamina>maxStamina*0.7){
        if(life<maxLife){
            stamina -= 0.01;
            life += 0.01;
        }
    }

    fsm.update();

    if(life<=0){
        if(!isDead){
            cout<<this<<"die"<<endl;
            die();
        }
    }
}

void Obj_Creature::begin(PhysxObj *obj)
{
    //    cout<<__FUNCTION__<<obj<<endl;
    //    //life-=30;
    //    if(obj->type() == string("dmg")){
    //        cout<<"take damage: "<<life<<endl;


    //        Obj_Dmg *d = dynamic_cast<Obj_Dmg*>(obj);
    //        processDmg(d);

    //        //life-=30;
    //        //cout<<dmg<<"_"<<d<<endl;
    //        AI_StateChase * ai = new AI_StateChase;
    //        ai->taget = d->parent;
    //        ai->tagetID = d->parent->id;
    //        this->ai.changeState(ai);
    //        //cout<<__FUNCTION__<<endl;
    //    }
}

void Obj_Creature::walk(b2Vec2 v)
{
    //cout<<__FUNCTION__<<endl;
    phyxBody->SetLinearDamping(1);
    v.Normalize();
    v.operator *=(movSpeed);
    phyxBody->ApplyForceToCenter(v,true);
    faceTo(v);
}

void Obj_Creature::run(b2Vec2 v)
{
    //cout<<__FUNCTION__<<endl;
    endurance -= 0.2;
    phyxBody->SetLinearDamping(1);
    v.Normalize();
    v.operator *=(movSpeed*2.0f);
    phyxBody->ApplyForceToCenter(v,true);
    faceTo(v);
}

void Obj_Creature::dash(b2Vec2 v)
{
    endurance -=10;
    phyxBody->SetLinearDamping(1);
    v.Normalize();
    v.operator *=(movSpeed*0.7);
    phyxBody->ApplyLinearImpulse(v,phyxBody->GetWorldCenter(),true);
}

void Obj_Creature::faceTo(b2Vec2 v)
{
    //cout<<__FUNCTION__<<" "<<v.x<<"*"<<v.y<<endl;
    b2Rot rot;
    v.Normalize();
    rot.s = v.y;
    rot.c = v.x;
    face = v;
    phyxBody->SetTransform(phyxBody->GetPosition(),rot.GetAngle());
}

void Obj_Creature::stop()
{
    phyxBody->SetLinearDamping(10);
}

void Obj_Creature::operateOnMap()
{
    //cout<<__FUNCTION__<<endl;
    b2Vec2 pos = phyxBody->GetTransform().p;
    Item* it = IC_Map::Instance()->takeItemf(pos.x,pos.y);
    it = bag.put(it);
    if(it){
        IC_Map::Instance()->putItemf(pos.x,pos.y,it);
    }
    //pos = pos+face;
    //IC_Map::Instance()->buildingOperate(pos.x,pos.y,1);
}

void Obj_Creature::activeOnMap(b2Vec2 pos)
{
    IC_Map::Instance()->buildingOperate(pos.x,pos.y,1);
}

void Obj_Creature::attack()
{
    //cout<<__FUNCTION__<<endl;
}

void Obj_Creature::move()
{
    b2Vec2 vec;
    vec = taget - phyxBody->GetTransform().p;
    vec.Normalize();
    vec*=0.3;
    b2Vec2 point = phyxBody->GetWorldCenter();
    point.x += phyxBody->GetTransform().q.c;
    point.y += phyxBody->GetTransform().q.s;
    phyxBody->ApplyForce(vec,point,true);
}

void Obj_Creature::processDmg(Obj_Dmg *dmg)
{
    cout<<__FUNCTION__<<dmg->parentID<<endl;
    gtInjured.start(500);
    //DMGTYPE{SLASH = 0,STAB,BLUNT,HEAT,COLD,ELECTRIC,POSION};
    for(auto itr = dmg->dmgs.begin();itr!=dmg->dmgs.end();itr++){
        switch((*itr).type){
        case SLASH: life-=((*itr).value*dmgRateSlash);break;
        case STAB: life-=((*itr).value*dmgRateStab);break;
        case BLUNT: life-=((*itr).value*dmgRateBlunt);break;
        case HEAT: life-=((*itr).value*dmgRateHeat);break;
        case COLD: life-=((*itr).value*dmgRateCold);break;
        case ELECTRIC: life-=((*itr).value*dmgRateElectric);break;
        case POSION: life-=((*itr).value*dmgRatePosion);break;
        }
    }
    addThreats(dmg->parentID,40);

    if(fsm.getCurrentState() == string("follow")){
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        fsm.pop();
    }
    cout<<"threat size: "<<fsm.threats.size()<<endl;
}

void Obj_Creature::addThreats(int id, int value)
{
    Obj_Creature *oc = ObjFactory::Instance()->getCreatureObj(id);
    if(oc){
        if(oc->alignment != alignment){
            fsm.threats[id] += value;
        }
    }
}

bool Obj_Creature::getDie() const
{
    return isDead;
}

void Obj_Creature::die()
{
    cout << __FUNCTION__ << endl;
    Item* itm = bag.take(0);
    IC_Map::Instance()->putItemf(locX,locY,itm);

    isDead = true;
}

bool Obj_Creature::isWalking()
{
    return(this->phyxBody->GetLinearVelocity().Length()>0.3);
}

