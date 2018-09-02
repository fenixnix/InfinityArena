#ifndef INPUT_H
#define INPUT_H

#include "sdl_input.h"

//#include <FSM/fsm.h>
//#include <UI/gl_gui_sheet.h>

class Input : public SDL_Input
{
public:
    Input();
    static Input* Instance(){
        if(p_static == NULL){
            p_static = new Input();
        }  
        return p_static;
    }
    void keyDown(SDL_Scancode);
    void keyUp(SDL_Scancode);
    void mouseLeftButtonDown();
    void mouseLeftButtonUp();
    void mouseWheelDown();
    void mouseWheelUp();
private:
    static Input* p_static;
};

#endif // INPUT_H


    //
