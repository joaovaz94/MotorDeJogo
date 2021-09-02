#include "include/State.h"
#include <iostream>

State::State() {
    this->quitRequested = false;
    this->bg = Sprite();
    this->music = Music();
    this->LoadAssets();
    //this->music.Play(1);
}

void State::LoadAssets() {
    this->bg = Sprite("./resources/img/ocean.jpg");
    this->music = Music("./resources/audio/stageState.ogg");
    //this->bg = Sprite("../resources/img/ocean.jpg");
    //this->music = Music("../resources/audio/stageState.ogg");

}

void State::Update(float dt){
    //Tratará da parte 3 de Game::Run

    //Retorna se apertou o x da janela ou Alt+F4
    //Fazer condição de entender evento de apertar X na janela
    // ou Alt+F4 para mudar quitRequested = true
    //Talvez procurar SDL_PollEvent()
    if(SDL_QuitRequested()) {
        std::cout << "Pedir para fechar a janela de jogo\n";
        this->quitRequested = true;
    }
}

void State::Render() {
    //Trata da Parte 4 de Game::Run

    //Não entendi muito bem
    //bg.Render(this->bg.GetWidth(),this->bg.GetWidth());
    bg.Render(0,0);
}

bool State::QuitRequested() {
    return quitRequested;
}