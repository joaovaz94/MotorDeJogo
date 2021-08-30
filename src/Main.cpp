#include <string>
#include "include/Game.h"


int main(int argc, char** argv) {

        //Game *game = new Game("titulo",640,480);
        Game *game = nullptr;
        *game = Game::GetInstance();
        game->Run();

        delete game;
        return 0;
}