#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include <string>
#define INCLUDE_SDL 
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include "Component.h"
#include "Timer.h"

class Text : public Component
{
public:

    enum TextStyle{SOLID, SHADED, BLENDED};

    Text(GameObject &associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, float timeShowing = 0.5);
    ~Text();

    void Update(float dt);
    void Render();
    bool Is(std::string type);

    void SetText(std:: string text);
    void SetColor(SDL_Color color);
    void SetStyle(TextStyle TextStyle);
    void SetFontFile(std:: string fontFile);
    void SetFontSize(int fontSize);

private:

    TTF_Font *font;
    SDL_Texture *texture;
    std::string type = "Text";

    std::string text;
    TextStyle style;
    std::string fontFile;
    int fontSize;
    SDL_Color color;

    void RemakeTexture();

    Timer timer;
    bool showText;
    float timeShowing;

};


#endif //TEXT_H_INCLUDED