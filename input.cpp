#include "input.h"
#include "sdl2_game.h"
#include "avatar.h"
#include  "render/nglrender.h"
#include "Item/itemfactory.h"
#include "Obj/objfactory.h"
#include "obj_beast.h"
#include "global.h"

Input* Input::p_static = NULL;

Input::Input()
{

}

void Input::keyDown(SDL_Scancode code)
{
    Avatar::the()->injectKeyDown(code);
    //cout<<__FUNCTION__<<code<<endl;
    if(code == SDL_SCANCODE_ESCAPE){
        //SDL2_Game::Instance()->isRuning = false;
    }

    if(code == SDL_SCANCODE_N){
        Global::the()->world.nextAvatar();
        //SDL2_Game::Instance()->isRuning = false;
    }
    if(code == SDL_SCANCODE_M){
        Global::the()->world.prevAvatar();
        //SDL2_Game::Instance()->isRuning = false;
    }

    if(code == SDL_SCANCODE_F10){
        Global::the()->isDrawDebug = !Global::the()->isDrawDebug;
    }

}

void Input::keyUp(SDL_Scancode code)
{

}

void Input::mouseLeftButtonDown()
{
    Avatar::the()->injectMouseLeftDown();
}

void Input::mouseLeftButtonUp()
{
    Avatar::the()->injectMouseLeftUp();
}

void Input::mouseWheelDown()
{
    //SDL_GL_Window * gameWindow = SDL_Render::the()->windows["game"];
    NGLRender::the()->getWindow(NGLRender::windowGame)->zoomOut();
    //gameWindow->zoomOut();
}

void Input::mouseWheelUp()
{
    //SDL_GL_Window * gameWindow = SDL_Render::the()->windows["game"];
    NGLRender::the()->getWindow(NGLRender::windowGame)->zoomIn();
    //gameWindow->zoomIn();
}

