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
#include <iostream>
#include <string>

class Game {

    private:
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;
        
        Game(std::string title, int width, int height);

    public:
        ~Game();
        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();
};

#endif //GAME_H_INCLUDED 