#include "include/Sprite.h"
#include "include/Game.h"
#include "include/Resources.h"

Sprite::Sprite(GameObject &associated): Component(associated) {
    texture = nullptr;
}

Sprite::Sprite(GameObject& associated, std::string file) : Component(associated) {

    texture = nullptr;
    this->Open(file);


}

Sprite::~Sprite() {
    SDL_DestroyTexture(texture);
}

void Sprite::Open(std::string file) {
    

    texture = Resources::GetImage(file);
    SDL_QueryTexture(this->texture,nullptr ,nullptr, &this->width, &this->height);

    this->SetClip(0, 0,this->width,this->height);
    associated.box.x = 0;
    associated.box.y = 0;
    associated.box.w = width;
    associated.box.h = height;

}

void Sprite::SetClip(int x, int y, int w, int h) {
    this->clipRect.x = x;
    this->clipRect.y = y;
    this->clipRect.w = w;
    this->clipRect.h = h;
}


void Sprite::Render(){
    SDL_Rect rct;
    rct.x = associated.box.x; 
    rct.y = associated.box.y; 
    rct.w = associated.box.w; 
    rct.h = associated.box.h; 

    if(SDL_RenderCopy(Game::GetInstance().GetRenderer(),
        texture, &clipRect, & rct)){
            SDL_LogError(0, "Nao conseguiu renderizar a copia: %s", IMG_GetError());
        }
}

void Sprite::Render(int x, int y, int w, int h) {
    SDL_Rect rct;
    rct.x = x;
    rct.y = y;
    rct.w = w;
    rct.h = h;

    if(SDL_RenderCopy(Game::GetInstance().GetRenderer(),
        texture, &clipRect, & rct)){
            SDL_LogError(0, "Nao conseguiu renderizar a copia: %s", IMG_GetError());
    }

}

bool Sprite::Is(std::string type){
    if(type == "Sprite") {
        return true;
    }
    else {
        return false;
    }
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