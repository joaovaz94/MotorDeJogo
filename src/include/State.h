#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#define INCLUDE_SDL 
#include "SDL_include.h"
#include "GameObject.h"
#include <vector>
#include <memory>


class State {

    private:
        Sprite *bg;
        Music *music;
        bool quitRequested;
        std::vector<std::unique_ptr<GameObject>> objectArray;


    public:
        State();
        ~State();

        void Input();
        void AddObject(int mouseX, int mouseY);
        bool QuitRequested();

        void LoadAssets();
        void Update(float dt);
        void Render();
};

#endif //STATE_H_INCLUDED