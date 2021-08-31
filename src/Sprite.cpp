#include "include/Sprite.h"
#include "include/Game.h"

Sprite::Sprite() {
    texture = nullptr;
}

Sprite::Sprite(std::string file) {

    texture = nullptr;
    this->Open(file);
}

Sprite::~Sprite() {
    SDL_DestroyTexture(texture);
}

void Sprite::Open(std::string file) {
    
    if(texture != nullptr) {
        texture = nullptr;
    }

    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    //Ver melhor como passar o renderizador de Game
    SDL_Texture* img = IMG_LoadTexture(renderer,file.c_str());
    if(img == nullptr){
        std::cout << "Erro: " << SDL_GetError();
        std::cout << "Erro ao carregar Sprite";
    }
    SDL_QueryTexture(img,nullptr ,nullptr, &this->width, &this->height);

}

void Sprite::SetClip(int x, int y, int w, int h) {
    this->clipRect.x = x;
    this->clipRect.y = y;
    this->clipRect.w = w;
    this->clipRect.h = h;
}

void Sprite::Render(int x, int y){
    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    SDL_Rect posRect;
    posRect.x = x;
    posRect.y = y;
    posRect.w = this->clipRect.w;
    posRect.h = this->clipRect.h;

    SDL_RenderCopy(renderer,
                   this->texture,
                   &this->clipRect,
                   &posRect);
}

int Sprite::GetWidth() { return this->width; }

int Sprite::GetHeigth() { return this->height; }

bool Sprite::IsOpen() {

    if (texture != nullptr){
        return true;
    }
    else {
        return false;
    }
}