#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

//#include "SDL.h"
//#include "SDL_image.h"
//#include "SDL_mixer.h"
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL 
#include "SDL_include.h"
#include "State.h"
#include "InputManager.h"
#include <iostream>
#include <string>

#define GAME_SCREEN_WIDTH 1024
#define GAME_SCREEN_HEIGHT 600

class Game {

    private:
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;

        int frameStart;
        float dt;

        void CalculateDeltaTime();
        
        //Game(std::string title, int width, int height);

    public:
        ~Game();
        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();
        Game(std::string title, int width, int height);

        float GetDeltaTime();
};

#endif //GAME_H_INCLUDED 