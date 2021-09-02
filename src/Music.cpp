#include "include/Music.h"
#include <iostream>

Music::Music(){

    this->music = nullptr;
}

Music::Music(std::string file){

    this->music = nullptr;
    this->Open(file);
}

void Music::Play(int times = -1) {

    std::cout << "musica: " << this->music << std::endl;
    if(IsOpen()){
        
        if(Mix_PlayMusic(music, times) == -1) {
            std::cout << "Problema em Mix_PlayMusic: " << Mix_GetError() << std::endl;
        }
    }

}

void Music::Stop(int msToStop = 1500) {

    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file){

    Mix_Music *mus = Mix_LoadMUS(file.c_str());
    if(mus == nullptr){
        std::cout << "Erro: " << Mix_GetError();
        std::cout << "Erro ao abrir Música";
    }
    this->music = mus;
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