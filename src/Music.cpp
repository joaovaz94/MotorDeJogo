#include "include/Music.h"
#include <iostream>

Music::Music(){

    music = nullptr;
}

Music::Music(std::string file){

    music = nullptr;
    this->Open(file);
}

void Music::Play(int times = -1) {

    int mus = Mix_PlayMusic(this->music, times);

    if(mus == -1){
        std::cout << "Erro: " << Mix_GetError();
        std::cout << "Erro ao carregar Música";
    }
}

void Music::Stop(int msToStop = 1500) {

    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file){

    Mix_Music* mus = Mix_LoadMUS(file.c_str());
    if(mus == nullptr){
        std::cout << "Erro: " << Mix_GetError();
        std::cout << "Erro ao abrir Música";
    }
}

bool Music::IsOpen() {

    if (music != nullptr){
        return true;
    }
    else {
        return false;
    }
}

Music::~Music() {

    this->Stop(0);
    Mix_FreeMusic(music);
    music = nullptr;
}