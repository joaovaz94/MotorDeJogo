#include "include/Sprite.h"
#include "include/Game.h"
#include "include/Resources.h"
#include "include/Camera.h"

Sprite::Sprite(GameObject &associated): Component(associated) {
    texture = nullptr;
    scale = Vec2(1,1);

    frameCount = 1;
    frameTime = 1;

    currentFrame = 0;
    timeElapsed = 0;
}

Sprite::Sprite(GameObject& associated, std::string file, int frameCount, float frameTime, float secondsToSelfDestruct) : Component(associated) {

    texture = nullptr;
    scale = Vec2(1,1);

    this->frameCount = frameCount;
    this->frameTime = frameTime;

    this->secondsToSelfDestruct = secondsToSelfDestruct;

    currentFrame = 0;
    timeElapsed = 0;

    this->Open(file);
}

Sprite::~Sprite() {
}

void Sprite::Open(std::string file) {
    
    texture = Resources::GetImage(file);

    if(!IsOpen()) {
        SDL_LogError(0, "Nao foi possivel carregar textura: %s", IMG_GetError());
    }
    if (SDL_QueryTexture(
            texture,
            nullptr ,
            nullptr, 
            &width, 
            &height
            ) != 0) 
    {
        SDL_LogError(0, "Não foi possivel Requerer textura: %s", IMG_GetError());
    }


    SetClip(0, 0, width / frameCount, height);
    associated.box.w = width / frameCount;
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

    timeElapsed += dt;

    if(timeElapsed > frameTime) {
        currentFrame += 1;
        timeElapsed = 0;
        if(currentFrame < frameCount) {
            SetFrame(currentFrame + 1);
        }
        else {
            SetFrame(0);
        }
        SetClip((currentFrame)*GetWidth(), 0, GetWidth(), GetHeigth());
    }

    if(secondsToSelfDestruct > 0) {
        selfDestructCount.Update(dt);
        if(selfDestructCount.Get() > secondsToSelfDestruct) {
            associated.RequestDelete();
        }
    }
}

void Sprite::SetFrame(int frame) {
    currentFrame = frame;
    timeElapsed = 0;

    int novoClipX = width * currentFrame / frameCount;
    int novoClipY = 0;
    int novoClipW = width / frameCount;
    int novoClipH = height;

    SetClip(novoClipX, novoClipY, novoClipW, novoClipH);

}

void Sprite::SetFrameCount(int frameCount) {
    this->frameCount = frameCount;
    currentFrame = 0;

    SetFrame(0);
    associated.box.w = GetWidth();
}

void Sprite::SetFrameTime(float frameTime) {
    this->frameTime = frameTime;
    timeElapsed = 0;
}

int Sprite::GetWidth() { return this->width * scale.x / frameCount; }

int Sprite::GetHeigth() { return this->height * scale.y; }

bool Sprite::IsOpen() {

    if (texture != nullptr){
        return true;
    }
    else {
        return false;
    }
}