#include "include/Sprite.h"
#include "include/Game.h"

Sprite::Sprite(GameObject &associated): Component(associated) {
    //this->associated = associated;
    texture = nullptr;
}

Sprite::Sprite(GameObject& associated, std::string file) : Component(associated) {

    //this->associated = associated;
    texture = nullptr;
    this->Open(file);
    SetClip(0, 0, 1024, 600);
    SetClip(0, 0, width, height);
    associated.box.x = 0;
    associated.box.y = 0;
    associated.box.w = width;
    associated.box.h = height;

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
        std::cout << "Erro ao carregar Sprite\n";
    }
    this->texture = img;
    std::cout << "Sprite: " << img << std::endl;
    SDL_QueryTexture(this->texture,nullptr ,nullptr, &this->width, &this->height);

    this->SetClip(0, 0,this->width,this->height);

    std::cout << "Clip: x: " << this->clipRect.x  << "y: " << this->clipRect.y;
    std::cout << "w: " << this->clipRect.w << "h: " << this->clipRect.h << std::endl;
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