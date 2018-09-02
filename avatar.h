#ifndef AVATAR_H
#define AVATAR_H

#include "obj_human.h"
#include "ic_map.h"
#include <SDL.h>

class Avatar
{
public:
    Avatar();
    static Avatar* the(){
        if(p_static == NULL){
            p_static = new Avatar;
        }
        return p_static;
    }

    void update();
    void drawN();
    //static void draw3D(float x, float y, float r);

    void injectMouseLeftDown();
    void injectMouseLeftUp();
    void injectKeyDown(SDL_Scancode scan_code );
    int avatarID;
    //Obj_Human *getAvatar();
    Obj_Human* human;
    string infoString;
private:
    static Avatar* p_static;
    float sightX;
    float sightY;
    bool leftButtonDown;
};

#endif // AVATAR_H
