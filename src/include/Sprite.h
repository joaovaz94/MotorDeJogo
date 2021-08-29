#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include <string>
#define INCLUDE_SDL 
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

class Sprite {

    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;

    public:
        Sprite();
        Sprite(std::string file);
        ~Sprite();
        void Open(std::string file);
        void SetClip(int x, int y, int w, int h);
        void Render(int x, int y);
        int GetWidth();
        int GetHeigth();
        bool IsOpen();
};

#endif //SPRITE_H_INCLUDED