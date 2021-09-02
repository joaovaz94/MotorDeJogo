#include <string>
#include <iostream>
#include "include/Game.h"


int main(int argc, char** argv) {

        //Game *game = nullptr;
        Game *game = new Game("João Paulo Vaz Mendes - 170002934", 1024, 600);
        *game = game->GetInstance();
        game->Run();

        delete game;
        return 0;
}