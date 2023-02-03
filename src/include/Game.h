#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

//#include "SDL.h"
//#include "SDL_image.h"
//#include "SDL_mixer.h"
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL 
#include "SDL_include.h"
#include "State.h"
#include "InputManager.h"
#include "Resources.h"
#include <iostream>
#include <string>
#include <stack>

#define GAME_SCREEN_WIDTH 1024
#define GAME_SCREEN_HEIGHT 600

class Game {

    private:
        static Game* instance;

        static State* storedState;
        SDL_Window* window;
        SDL_Renderer* renderer;
        static std::stack<std::unique_ptr<State>> stateStack;

        int frameStart;
        float dt;

        void CalculateDeltaTime();
        
    public:
        Game(std::string title, int width, int height);
        ~Game();

        static Game& GetInstance();
        SDL_Renderer* GetRenderer();
        State& GetCurrentState();

        void Push(State *state);

        void Run();

        float GetDeltaTime();
};

#endif //GAME_H_INCLUDED 