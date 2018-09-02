#include "world.h"
#include <sstream>
#include "ic_map.h"
#include "avatar.h"
#include "obj/objfactory.h"

World::World()
{
    id = "Nix";
    currentMap = "nixgaia";

    //Avatar::Instance()->avatarID = -1;
    avatarName = "";
    avatarID = -1;
    avatarObj = nullptr;
    {
        int id = Obj_Human::createByID(32,32);
        Obj* obj = ObjFactory::Instance()->getObjOnMap(id);
        if(obj->isCreature()){
            Obj_Creature *oc = dynamic_cast<Obj_Creature*>(obj);
            if(oc->type() == "human"){
                Obj_Human *hm = dynamic_cast<Obj_Human*>(oc);
                hm->alignment = "player";
                hm->name = "Nix";
            }
        }
        team.push_back(id);
    }
    {
        int id = Obj_Human::createByID(32,32);
        Obj* obj = ObjFactory::Instance()->getObjOnMap(id);
        if(obj->isCreature()){
            Obj_Creature *oc = dynamic_cast<Obj_Creature*>(obj);
            if(oc->type() == "human"){
                Obj_Human *hm = dynamic_cast<Obj_Human*>(oc);
                hm->alignment = "player";
                hm->name = "Bonnie";
            }
        }
        team.push_back(id);
    }

//    {
//        int id = Obj_Human::createByID(16,16);
//        Obj* obj = ObjFactory::Instance()->getObjOnMap(id);
//        if(obj->isCreature()){
//            Obj_Creature *oc = dynamic_cast<Obj_Creature*>(obj);
//            if(oc->type() == "human"){
//                Obj_Human *hm = dynamic_cast<Obj_Human*>(oc);
//                hm->alignment = "player";
//                hm->name = "Jerry";
//            }
//        }
//        team.push_back(id);
//    }

    updateAvatar();
}

bool World::updateAvatar()
{
    bool res = setAvatar(avatarName);
    if(res){
        //cout<<"                      "<<avatarName<<__FUNCTION__<<__LINE__<<endl;
        return true;
    }
    res = setFirstMemberAvater();
    if(res){
        //cout<<"                      "<<__FUNCTION__<<__LINE__<<endl;
        return true;
    }
    avatarName = "";
    avatarID = -1;
    avatarObj = nullptr;
    return false;
}

bool World::setAvatar(string name)
{
    for(auto itr = team.begin();itr!=team.end();){
        Obj* obj = ObjFactory::Instance()->getObjOnMap(*itr);
        if(obj == nullptr){
            itr = team.erase(itr);
            continue;
        }
        if(obj->isCreature()){
            Obj_Creature *oc = dynamic_cast<Obj_Creature*>(obj);
            if(oc->type() == "human"){
                Obj_Human *hm = dynamic_cast<Obj_Human*>(oc);
                if(hm->name == name){
                    avatarName = name;
                    avatarID = hm->id;
                    avatarObj = hm;
                    return true;
                }
            }
        }
        itr++;
    }
    avatarName = "";
    avatarID = -1;
    avatarObj = nullptr;
    return false;
}

bool World::setFirstMemberAvater()
{
    for(auto itr = team.begin();itr!=team.end();){
        Obj* obj = ObjFactory::Instance()->getObjOnMap(*itr);
        if(obj == nullptr){
            itr = team.erase(itr);
            continue;
        }
        if(obj->isCreature()){
            Obj_Creature *oc = dynamic_cast<Obj_Creature*>(obj);
            if(oc->type() == "human"){
                Obj_Human *hm = dynamic_cast<Obj_Human*>(oc);
                avatarName = hm->name;
                avatarID = hm->id;
                avatarObj = hm;
                return true;
            }
        }
        itr++;
    }
    avatarName = "";
    avatarID = -1;
    avatarObj = nullptr;
    return false;
}

void World::removeInvalidMemeber()
{
    for(auto itr = team.begin();itr!=team.end();){
        Obj_Human*hm = ObjFactory::Instance()->getHumanObj(*itr);
        if(hm == nullptr){
            itr = team.erase(itr);
        }else{
            itr++;
        }
    }
}

void World::nextAvatar()
{
    removeInvalidMemeber();
    cout<<__FUNCTION__<<__LINE__<<endl;
    auto iitr = team.begin();
    Obj_Human* hm;
    for(auto itr = team.begin();itr!=team.end();itr++){
        hm = ObjFactory::Instance()->getHumanObj(*itr);
        if(hm->id == avatarID){
            iitr = itr;
            break;
        }
    }
    //cout<<__FUNCTION__<<__LINE__<<endl;
    if(*iitr!=team.back()){
        //cout<<__FUNCTION__<<__LINE__<<endl;
        iitr++;
        hm = ObjFactory::Instance()->getHumanObj(*iitr);
    }else{
        //cout<<__FUNCTION__<<__LINE__<<endl;
        hm = ObjFactory::Instance()->getHumanObj(team.front());
    }
    cout<<__FUNCTION__<<__LINE__<<hm<<endl;

    avatarName = hm->name;
    avatarID = hm->id;
    avatarObj = hm;
}

void World::prevAvatar()
{
    removeInvalidMemeber();
    cout<<__FUNCTION__<<__LINE__<<endl;
    auto iitr = team.begin();
    Obj_Human* hm;
    for(auto itr = team.begin();itr!=team.end();itr++){
        hm = ObjFactory::Instance()->getHumanObj(*itr);
        if(hm->id == avatarID){
            iitr = itr;
            break;
        }
    }
    //cout<<__FUNCTION__<<__LINE__<<endl;
    if(*iitr!=team.front()){
        //cout<<__FUNCTION__<<__LINE__<<endl;
        iitr--;
        hm = ObjFactory::Instance()->getHumanObj(*iitr);
    }else{
        //cout<<__FUNCTION__<<__LINE__<<endl;
        hm = ObjFactory::Instance()->getHumanObj(team.back());
    }
    avatarName = hm->name;
    avatarID = hm->id;
    avatarObj = hm;
}

string World::currentMapFileName()
{
    ostringstream fileName;
    fileName<<"./save/"<<id<<"/map/"<<currentMap<<".ictmx";
    return fileName.str();
}

void World::loadTeam()
{
    for(int i = 0;i<team.size();i++){
        Obj* o = ObjFactory::Instance()->getObjOnMap(team[i]);
        if(o){
            tmp.push_back(o);
            ObjFactory::Instance()->removeObj(team[i]);
        }
    }
    team.clear();
}

void World::putTeam()
{
    for(int i = 0;i<tmp.size();i++){
        team.push_back(ObjFactory::Instance()->addObj2Map(tmp[i]));
    }
    tmp.clear();
    cout<<__FUNCTION__<<"team size:"<<team.size()<<endl;
}

void World::setTeamPos(float x, float y)
{
    cout<<__FUNCTION__<<x<<"*"<<y<<endl;
    for(int i = 0;i<team.size();i++){
        Obj_Human* o = ObjFactory::Instance()->getHumanObj(team[i]);
        if(o)
        {
            o->phyxBody->SetTransform(b2Vec2(x,y),0);
        }
    }
}

vector<int> World::getTeamList()
{
    removeInvalidMemeber();
    return team;
}
