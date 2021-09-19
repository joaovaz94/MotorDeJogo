#include "include/Sound.h"

#include <iostream>

Sound::Sound(GameObject& associated) : Component(associated) {
    this->chunk = nullptr;
}

Sound::Sound(GameObject& associated, std::string file) : Sound(associated) {
    this->Open(file);
}

void Sound::Play(int times=1) {

    int c = Mix_PlayChannel(-1,this->chunk,times - 1);
    if(c == -1){
        std::cout << "Erro ao tocar som: " << Mix_GetError() << std::endl;
    }
    this->channel = c;
}

void Sound::Stop() {

    if(this->chunk != nullptr) {
        Mix_HaltChannel(this->channel);
    }
}

void Sound::Open(std::string file) {

    this->chunk = Mix_LoadWAV(file.c_str());
    if(!this->chunk){
        std::cout << "Erro ao abrir som" << Mix_GetError() << std::endl;
    }
}

Sound::~Sound() {
    if(!this->chunk) {

        Mix_HaltChannel(this->channel);
        Mix_FreeChunk(this->chunk);
    }
}

bool Sound::IsOpen() { 
    return this->chunk != nullptr; 
}

bool Sound::Is(std::string type) { 
    if (type == "Sound"){
        return true;
    }
    else {
        return false;
    }
}

void Sound::Update(float dt) { if (dt) {} }

void Sound::Render() {}