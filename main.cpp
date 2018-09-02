//#include <QCoreApplication>
#include <sdl2_game.h>

//int main(int argc, char *argv[])
//{
//    //QCoreApplication a(argc, argv);
//    SDL2_Game::Instance()->init("Infinity Arena");
//    while(SDL2_Game::Instance()->isRuning){
//        SDL2_Game::Instance()->update();
//    }
//    SDL2_Game::Instance()->release();


//    SDL_Quit();
//    return 0;
//}

#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int iCmdShow){
    SDL2_Game::the()->init("Infinity Arena");
    SDL2_Game::the()->run();
    SDL2_Game::the()->release();
    SDL_Quit();
    return 0;
}
