#ifndef OBJ_DMG_H
#define OBJ_DMG_H

#include "physxobj.h"

enum DMGTYPE{SLASH = 0,STAB,BLUNT,HEAT,COLD,ELECTRIC,POSION};

class DMG
{
public:
    DMGTYPE type;
    int value;
};

class Obj_Dmg : public PhysxObj
{
public:
    Obj_Dmg();
    vector<DMG> dmgs;
    int parentID;
    void update();
    void draw();
    string type(){
        return "dmg";
    }
    bool isCreature(){
        return false;
    }
    void begin(PhysxObj *o);
};

#endif // OBJ_DMG_H
