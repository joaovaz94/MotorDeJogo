#ifndef STAGESTATE_H_INCLUDED
#define STAGESTATE_H_INCLUDED

#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#define INCLUDE_SDL 
#include "SDL_include.h"
#include "GameObject.h"
#include "InputManager.h"
#include <vector>
#include <memory>


class StageState {

    private:
        Sprite *bg;
        Music *music;
        bool quitRequested;
        bool started;
        std::vector<std::shared_ptr<GameObject>> objectArray;


    public:
        StageState();
        ~StageState();

        void Start();

        //void Input();
        std::weak_ptr< GameObject > AddObject(GameObject *go);
        std::weak_ptr< GameObject > GetObjectPtr(GameObject *go);
        bool QuitRequested();

        void LoadAssets();
        void Update(float dt);
        void Render();
};

#endif //STAGESTATE_H_INCLUDED