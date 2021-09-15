
#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include "Component.h"
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

class Sound : public Component {

    private:

        Mix_Chunk* chunk;
        int channel;

    public:

        Sound(GameObject& associated);
        Sound(GameObject& associated, std::string file);
        ~Sound();

        void Play(int times);
        void Stop();
        void Open (std::string file);
        bool IsOpen();

        void Update(float dt);
        void Render();
        bool Is(std::string type);
};


#endif //SOUND_H_INCLUDED