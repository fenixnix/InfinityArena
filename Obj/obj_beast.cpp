#include "obj_beast.h"
#include "Render/nglrender.h"

Obj_Beast::Obj_Beast()
{
    sid = "Beast";
}

Obj_Beast::~Obj_Beast()
{
    release();
}

void Obj_Beast::draw()
{
    //cout<<__FUNCTION__<<endl;
    b2Transform tra = this->phyxBody->GetTransform();
    NGLRender* render = NGLRender::the();
    render->setMode(MODE_GEO);
    float cl[] = {0,1,0,0.7};
    render->drawCircle(tra.p.x,tra.p.y,0.01,dimension,cl,GL_LINE_LOOP);
    render->setMode(MODE_SPRITE);
    render->drawTextSprite(drawID,tra.p.x,tra.p.y,dimension/2,64);
//    float framePercent;
//    string stateID = fsm.getCurrentState(framePercent);

//    //    if(this->phyxBody->GetLinearVelocity().Length()<0.3){
//    //        drawFrame = 0;
//    //        frame = 0;
//    //    }else{
//    //        drawFrame++;
//    //        if(drawFrame%10==0){
//    //            frame++;
//    //        }
//    //    }

//    b2Transform tra = this->phyxBody->GetTransform();
//    float dx = tra.p.x;
//    float dy = tra.p.y;
//    //if(crickCD.isOn()){
//    if(stateID == string("disable")){
//        dx+=(float)(rand()%7-3)*0.02f;
//        dy+=(float)(rand()%7-3)*0.02f;
//    }
//    glPushMatrix();
//    glTranslated(dx,dy,dimension/2);
//    glScalef(dimension,dimension,dimension);
//    SDL_Render::the()->drawObj(drawID);
//    glPopMatrix();
}

void Obj_Beast::drawBillboard(float pitch, float yaw)
{
//    float framePercent;
//    string stateID = fsm.getCurrentState(framePercent);
//    b2Transform tra = this->phyxBody->GetTransform();
//    float dx = tra.p.x;
//    float dy = tra.p.y;
//    float fx = tra.q.c;
//    float fy = tra.q.s;
//    float fz = 0.0f;
//    if(!gtInjured.getTo()){
//        dx+=(float)(rand()%7-3)*0.02f;
//        dy+=(float)(rand()%7-3)*0.02f;
//    }
//    if(stateID == string("busy")){
//        dx -= (sin(framePercent*M_PI)*dimension/3);
//        dy -= (sin(framePercent*M_PI)*dimension/3);
//    }
//    if(stateID == string("disable")){
//        dx = dx+(fx*2*(sqrt(framePercent)-1)*dimension);
//        dy = dy+(fy*2*(sqrt(framePercent)-1)*dimension);
//        fz = sin(framePercent*M_PI);
//    }
//    glPushMatrix();
//    glColor4f(1,1,1,0.5);
//    glTranslated(dx,dy,dimension/2+fz);
//    glRotatef(yaw,0,0,1);
//    glRotatef(pitch,1,0,0);
//    glScalef(dimension,dimension,dimension);
//    //SDL_Render::the()->drawObj(drawID);
//    glPopMatrix();

//    glDisable(GL_TEXTURE_2D);
//    ostringstream oss;
//    float p;
//    oss<<this->drawID<<" "<<this->fsm.getCurrentState(p)<<endl<<" T: ";
//    for(auto itr = fsm.threats.begin();itr!=fsm.threats.end();itr++){
//        oss<<itr->first<<"*"<<itr->second<<endl;
//    }
//    SDL_Render::the()->text.drawText(oss.str(),tra.p.x,tra.p.y,1);
//    glDepthFunc(GL_LEQUAL);
}

void Obj_Beast::update()
{
    Obj_Creature::update();

    if(!sights.empty()){
        float minDistance = 255;
        int minID = -1;
        for(int i = 0;i<sights.size();i++){
            Obj* obj = ObjFactory::Instance()->getObjOnMap(sights[i]);
            if(obj==nullptr){
                continue;
            }
            if(obj){
                if(obj->isCreature()){
                    Obj_Creature* oc = dynamic_cast<Obj_Creature*>(obj);
                    if(oc->classify() == string("Beast")){
                        continue;
                    }
                    float d = (this->phyxBody->GetTransform().p - oc->phyxBody->GetTransform().p).Length();
                    if(d<minDistance){
                        minDistance = d;
                        minID = oc->id;
                    }
                }
            }
        }
        if(minID!=-1){
            //            AI_StateChase * ai = new AI_StateChase;
            //            //cout<<__FUNCTION__<<"id: "<<this->id<<" sights size:"<<sights.size()<<endl;
            //            ai->taget = dynamic_cast<PhysxObj*>(ObjFactory::Instance()->objsMap[minID]);
            //            ai->tagetID = sights.at(0);
            //            this->ai.changeState(ai);
        }
    }
}

Obj *Obj_Beast::create(string id, int x, int y)
{
    Obj_Beast * beast = new Obj_Beast();
    if(id == string("slime")){
        beast->drawID = "slime";
        beast->dimension = 0.2f;
        beast->movSpeed = 0.3;
        beast->fsm.AI_Feature::stroll = true;
        beast->fsm.AI_Feature::rage = true;
        beast->bag.put(Item_Common::create("log",3));
    }
    if(id == string("slinail")){
        beast->drawID = "slinail";
        beast->dimension = 0.3f;
        beast->fsm.AI_Feature::stroll = true;
        beast->fsm.AI_Feature::coward = true;
        beast->bag.put(Item_Common::create("stone",5));
    }
    if(id == string("deer")){
        beast->drawID = "deer";
        beast->life = 80;
        beast->maxLife = 80;
        beast->dimension = 0.2f;
        beast->fsm.AI_Feature::stroll = true;
        beast->fsm.AI_Feature::coward = true;
        beast->bag.put(Item_Common::create("meat",5));
        beast->bag.put(Item_Common::create("bone",3));
        beast->bag.put(Item_Common::create("leather",2));
    }
    if(id == string("wolf")){
        beast->drawID = "wolf";
        beast->life = 120;
        beast->maxLife = 120;
        beast->dimension = 0.2f;
        beast->fsm.AI_Feature::warlike = true;
        beast->fsm.AI_Feature::stroll = true;
        beast->fsm.AI_Feature::rage = true;
        beast->bag.put(Item_Common::create("meat",5));
        beast->bag.put(Item_Common::create("bone",3));
        beast->bag.put(Item_Common::create("leather",2));
    }
    //beast->phyxBody = Physx::the()->createDynamicBox(x,y,beast->dimension,beast->dimension,beast,true);
    beast->phyxBody = B2Physx::the()->createDynamicCircle(x,y,beast->dimension,beast);
    beast->fsm.objID = ObjFactory::Instance()->addObj2Map(dynamic_cast<Obj*>(beast));
    cout<<__FUNCTION__<<" id: "<<beast->id<<" "<<beast->phyxBody<<endl;
    return dynamic_cast<Obj*>(beast);
}

void Obj_Beast::seek()
{

}

void Obj_Beast::attack()
{
    cout<<__FUNCTION__<<endl;
    for(auto itr = sights.begin();itr!=sights.end();itr++){
        Obj* obj = ObjFactory::Instance()->getObjOnMap( *itr);
        if(obj==nullptr){
            continue;
        }
        if(obj->isCreature()){
            Obj_Creature *oc = dynamic_cast<Obj_Creature*>(obj);
            if(oc->classify() == string("Beast")){
                continue;
            }
            Obj_Dmg *dmg = new Obj_Dmg;
            dmg->parentID = this->id;
            DMG d;
            d.type = SLASH;
            d.value = 7;
            dmg->dmgs.push_back(d);
            oc->processDmg(dmg);
        }
    }
}

