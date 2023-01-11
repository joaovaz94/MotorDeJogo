#include "include/Sprite.h"
#include "include/Game.h"
#include "include/Resources.h"
#include "include/Camera.h"

Sprite::Sprite(GameObject &associated): Component(associated) {
    texture = nullptr;
    scale = Vec2(1,1);
}

Sprite::Sprite(GameObject& associated, std::string file) : Component(associated) {

    texture = nullptr;
    scale = Vec2(1,1);
    this->Open(file);


}

Sprite::~Sprite() {
}

void Sprite::Open(std::string file) {
    
    texture = Resources::GetImage(file);

    //if(IsOpen()) {
    //    SDL_LogError(0, "Nao foi possivel carregar textura: %s", IMG_GetError());
    //}
    if (SDL_QueryTexture(
            this->texture,
            nullptr ,
            nullptr, 
            &this->width, 
            &this->height
            ) != 0) 
    {
        SDL_LogError(0, "Não foi possivel Requerer textura: %s", IMG_GetError());
    }


    this->SetClip(0, 0,this->width,this->height);
    associated.box.w = width;
    associated.box.h = height;

}

void Sprite::SetClip(int x, int y, int w, int h) {
    this->clipRect.x = x;
    this->clipRect.y = y;
    this->clipRect.w = w;
    this->clipRect.h = h;
}

void Sprite::Render(int x, int y, int w, int h) {
    SDL_Rect rct;
    rct.x = x;
    rct.y = y;
    rct.w = w * scale.x;
    rct.h = h * scale.y;
    

    if(SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),
        texture, &clipRect, &rct, associated.angleDeg, nullptr, SDL_FLIP_NONE)){
            SDL_LogError(0, "Nao conseguiu renderizar a copia: %s", IMG_GetError());
    }

}

void Sprite::Render(){
    this->Render(
        associated.box.x - Camera::pos.x,
        associated.box.y - Camera::pos.y,
        associated.box.w,
        associated.box.h
    );

}


bool Sprite::Is(std::string type){
    if(type == "Sprite") {
        return true;
    }
    else {
        return false;
    }
}

void Sprite::SetScaleX(float scaleX, float scaleY) {
    if(scaleX == 0){
        scaleX = scale.x;
    }
    if(scaleY == 0){
        scaleY = scale.y;
    }
    scale = Vec2(scaleX, scaleY);
}

Vec2 Sprite::GetScale() {
    return scale;
}

void Sprite::Update(float dt) {

}

int Sprite::GetWidth() { return this->width * scale.x; }

int Sprite::GetHeigth() { return this->height * scale.y; }

bool Sprite::IsOpen() {

    if (texture != nullptr){
        return true;
    }
    else {
        return false;
    }
}