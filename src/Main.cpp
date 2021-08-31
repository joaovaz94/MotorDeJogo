#include <string>
#include <iostream>
#include "include/Game.h"


int main(int argc, char** argv) {

        std::cout << "programa iniciado";
        //Game *game = nullptr;
        Game *game = new Game("Janela", 640, 480);
        *game = game->GetInstance();
        std::cout << "jogo instanciado na mais";
        game->Run();

        delete game;
        return 0;
}