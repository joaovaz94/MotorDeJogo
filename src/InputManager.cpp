#include "include/InputManager.h"
#include <iostream>

InputManager::InputManager() {

    //Inicializando o mouseState
    for(int i=0; i < 6; i++){
        mouseState[i] = false;
    }
    //Inicializando o mouseUpdate
    for(int i=0; i < 6; i++){
        mouseUpdate[i] = 0;
    }

    quitRequested = false;
    updateCounter = 0;

    mouseX = 0;
    mouseY = 0;

}

InputManager::~InputManager() {
}

void InputManager::Update() {
    SDL_Event evento;
    updateCounter++;
    SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;

    while (SDL_PollEvent(&evento))
    {
        
        switch (evento.type) {
            case SDL_KEYDOWN:
                if(evento.key.repeat != 1) {
                    keyState[evento.key.keysym.sym] = true;
                    keyUpdate[evento.key.keysym.sym] = updateCounter;
                }
                break;
            case SDL_KEYUP:
                keyState[evento.key.keysym.sym] = false;
                keyUpdate[evento.key.keysym.sym] = updateCounter;

                break;
            case SDL_MOUSEBUTTONDOWN:
                mouseState[evento.button.button] = true;
                mouseUpdate[evento.button.button] = updateCounter;
                break;
            case SDL_MOUSEBUTTONUP:
                mouseState[evento.button.button] = false;
                mouseUpdate[evento.button.button] = updateCounter;
                break;
            case SDL_QUIT:
                quitRequested = true;
                break;
        
            default:
                break;
            }
    }
    
}

bool InputManager::KeyPress(int key) {

    //Consultar no Map o frame atual do botao
    std::unordered_map<int, int>::const_iterator botaoApertado = keyUpdate.find(key);

    if((botaoApertado != keyUpdate.end()) && (botaoApertado->second == updateCounter )){
        //Caso se encontre o botao no map no frame atual retorna o seu estado
        return keyState.find(key)->second; 
    }
    else {
        return false;
    }
}

bool InputManager::KeyRelease(int key) {

    //Consultar no Map o frame atual do botao
    std::unordered_map<int, int>::const_iterator botaoApertado = keyUpdate.find(key);

    if((botaoApertado != keyUpdate.end()) && (botaoApertado->second == updateCounter )){
        //Caso se encontre o botao no map no frame atual retorna o seu estado
        return !keyState.find(key)->second; 
    }
    else {
        return false;
    }
}

bool InputManager::IsKeyDown(int key) {

    std::unordered_map<int, bool>::const_iterator botaoApertado = keyState.find(key);

    if(botaoApertado != keyState.end()){
        return keyState.find(key)->second; 
    }
    else {
        return false;
    }
}

bool InputManager::MousePress(int button) {

    if(mouseUpdate[button] == updateCounter) {
        return IsMouseDown(button);
    }
    else {
        return false;
    }
}

bool InputManager::MouseRelease(int button) {

    if(mouseUpdate[button] == updateCounter) {
        return !IsMouseDown(button);
    }
    else {
        return false;
    }
}

bool InputManager::IsMouseDown(int button) {
    return mouseState[button];
}

int InputManager::GetMouseX() {
    return mouseX;
}

int InputManager::GetMouseY() {
    return mouseY;
}

bool InputManager::QuitRequested() {
    return quitRequested;
}

//Implementação da Classe como Meyer's Singleton
InputManager& InputManager::GetInstance(){

    static InputManager instanciaUnica;
    return instanciaUnica;
}