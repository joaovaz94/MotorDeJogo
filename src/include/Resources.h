#ifndef RESOURCES_H_INCLUDED
#define RESOURCES_H_INCLUDED

#include <string>
#include <memory>
#include <unordered_map>
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

class Resources {

    private:

        static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
        static std::unordered_map<std::string, Mix_Music *> musicTable;
        static std::unordered_map<std::string, Mix_Chunk *> soundTable;

    public:

        Resources();
        ~Resources();

        static std::shared_ptr<SDL_Texture> GetImage(std::string);
        static void ClearImages();

        static Mix_Music* GetMusic(std::string file);
        static void ClearMusics();

        static Mix_Chunk* GetSound(std::string file);
        static void ClearSounds();

};

#endif //RESOURCES_H_INCLUDED