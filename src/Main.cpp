#include "include/Game.h"
#include "include/TitleState.h"


int main(int argc, char** argv) {

        Game game = Game::GetInstance();
        //*game = game->GetInstance();
        State *initialState = new TitleState();
        game.Push(initialState);
        game.Run();

        //delete game;
        return 0;
}