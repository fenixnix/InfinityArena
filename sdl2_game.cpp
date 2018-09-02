#include "sdl2_game.h"
#include <Box2D/Box2D.h>
#include "b2physx.h"
#include "FSM/fsm.h"
#include "FSM/state_dungeon.h"
#include "FSM/state_mainui.h"
#include "Build/buildingfactory.h"
#include "global.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <Render/physxdraw.h>
PhysxDraw draw;

SDL2_Game* SDL2_Game::p_static = 0;

SDL2_Game::SDL2_Game()
{
  isRuning = false;
  //time_t time;
  //tm* t = localtime(&time);
  std::srand(0);
}

SDL2_Game *SDL2_Game::the(){
  if(p_static!=0){
      return p_static;
    }
  p_static = new SDL2_Game;
  return p_static;
}

void SDL2_Game::init(string title)
{
  SDL_Init(SDL_INIT_EVERYTHING);
  B2Physx::the()->init();
  B2Physx::the()->setDraw(&draw);
  Input::Instance()->init();
  isRuning = true;
  ItemFactory::the()->loadConfig("itemdata.xml");
  BuildingFactory::the()->loadConfig("buildingdata.xml");
  NGLRender::the()->init(title,800,600);
  NGUI::the()->init();
  FSM::the()->pushState(new State_MainUI);

}

void SDL2_Game::run()
{
  while(isRuning){
      GlobalTimer::update();
      FSM::the()->update();
      FSM::the()->render();
    }
  FSM::the()->popState();
}

void SDL2_Game::release()
{
  cout<<__FUNCTION__<<endl;
  delete this;
}

