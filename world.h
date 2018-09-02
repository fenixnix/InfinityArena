#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <obj/obj_human.h>
#include <vector>

using namespace std;

class World
{
public:
    World();
    string id;
    string currentMap;

    string avatarName;
    int avatarID;
    Obj_Human* avatarObj;

    bool updateAvatar();
    bool setAvatar(string name);
    bool setFirstMemberAvater();
    void removeInvalidMemeber();
    void nextAvatar();
    void prevAvatar();

    string currentMapFileName();
    //vector<int> allys;
    void loadTeam();
    void putTeam();
    void setTeamPos(float x, float y);
    vector<int> getTeamList();
private:
    vector<int> team;
    vector<Obj*> tmp;
};

#endif // WORLD_H
