#include "include/Game.h"
#include "include/StageState.h"


int main(int argc, char** argv) {

        Game game = Game::GetInstance();
        //*game = game->GetInstance();
        State *initialState = new StageState();
        game.Push(initialState);
        game.Run();

        //delete game;
        return 0;
}