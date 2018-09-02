#ifndef SDL2_GAME_H
#define SDL2_GAME_H

#include "SDL.h"
#include "input.h"
#include <string>
#include "FSM/fsm.h"
#include "globaltimer.h"

using namespace std;

class SDL2_Game
{
public:
    SDL2_Game();
    static SDL2_Game *the();
    void init(string title);
    void run();
    void release();
    bool isRuning;
private:
    static SDL2_Game* p_static;
    //FSM fsm;
};

#endif // SDL2_GAME_H
