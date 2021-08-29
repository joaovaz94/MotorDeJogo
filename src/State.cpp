#include "include/State.h"

State::State() {
    quitRequested = false;
    bg = Sprite();
}

void State::LoadAssets() {
    //A fazer ainda
}

void State::Update(float dt){
    //Tratará da parte 3 de Game::Run

    //Retorna se apertou o x da janela ou Alt+F4
    //Fazer condição de entender evento de apertar X na janela
    // ou Alt+F4 para mudar quitRequested = true
    //Talvez procurar SDL_PollEvent()
    if(SDL_QuitRequested()) {
        quitRequested = true;
    }
}

void State::Render() {
    //Trata da Parte 4 de Game::Run

    //Não entendi muito bem
    bg.Render(this->bg.GetWidth(),this->bg.GetWidth());
}

bool State::QuitRequested() {
    return quitRequested;
}