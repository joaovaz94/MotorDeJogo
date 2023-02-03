#include "include/Text.h"
#include "include/Camera.h"
#include "include/Game.h"
#include "include/Resources.h"

Text::Text(GameObject &associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, float timeShowing) : Component(associated) {

    this->texture = nullptr;
    this->fontFile = fontFile;
    this->fontSize = fontSize;
    this->style = style;
    this->text = text;
    this->color = color;
    this->showText = true;
    this->timeShowing = timeShowing;
    RemakeTexture();
}

Text::~Text() {

    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Text::Update(float dt ) {

    timer.Update(dt);
    if((timer.Get() > timeShowing) && (timeShowing != 0) ) {
        showText = !showText;
        timer.Restart();
    }
}

void Text::Render() {
    
    if(texture != nullptr && showText) {

        SDL_Rect src;
        SDL_Rect dst;

        src.x = 0;
        src.y = 0;
        src.w = associated.box.w;
        src.h = associated.box.h;

        dst.x = associated.box.x - Camera::pos.x;
        dst.y = associated.box.y - Camera::pos.y;
        dst.w = src.w;
        dst.h = src.h;

        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &src, &dst, 0, nullptr, SDL_FLIP_NONE);
    } 
}

void Text::SetText(std::string text) {
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
    this->style = style;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture() {

    font = TTF_OpenFont(fontFile.c_str(), fontSize);
    SDL_Surface *surface;
    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
    switch (style)
    {
    case SOLID:
        surface = TTF_RenderText_Solid(font, text.c_str(), color );
        break;
    
    case SHADED:
        surface = TTF_RenderText_Shaded(font, text.c_str(), color , {255, 0, 0, SDL_ALPHA_OPAQUE});
        break;
    
    case BLENDED:
        surface = TTF_RenderText_Blended(font, text.c_str(), color );
        break;
    
    default:
        surface = TTF_RenderText_Solid(font, text.c_str(), color );
        break;
    }

    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);

    associated.box.w = surface->w;
    associated.box.h = surface->h;
    SDL_FreeSurface(surface);

}

bool Text::Is(std::string type) {

    if(type == "Text") {
        return true;
    }
    else {
        return false;
    }
}