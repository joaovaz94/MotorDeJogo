#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include <string>
#define INCLUDE_SDL 
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Component.h"

class Sprite : public Component {

    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;
        Vec2 scale;
        int frameCount;
        int currentFrame;
        float timeElapsed;
        float frameTime;

    public:
        Sprite(GameObject& associated);
        Sprite(GameObject& associated, std::string file);
        ~Sprite();

        void Open(std::string file);
        void SetClip(int x, int y, int w, int h);
        void Update(float dt); 
        void Render();
        void Render(int x, int y, int w, int h);
        bool Is(std::string type);

        void SetScaleX(float scaleX, float scaleY);
        Vec2 GetScale();

        int GetWidth();
        int GetHeigth();
        bool IsOpen();

    protected:
        //GameObject& associated;
};

#endif //SPRITE_H_INCLUDED