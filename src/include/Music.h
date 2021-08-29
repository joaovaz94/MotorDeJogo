#ifndef MUSIC_H_INCLUDED
#define MUSIC_H_INCLUDED

#include<string>
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

class Music {

    private:
        Mix_Music* music;

    public:
        Music();
        Music(std::string file);

        void Play(int times);
        void Stop(int msToStop);
        void Open(std::string file);
        bool IsOpen();

        ~Music();

};

#endif //MUSIC_H_INCLUDED