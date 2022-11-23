#include "include/Resources.h"
#include "include/Game.h"

std::unordered_map<std::string, SDL_Texture *> Resources::imageTable;
std::unordered_map<std::string, Mix_Music *> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk *> Resources::soundTable;

Resources::Resources() {

}

Resources::~Resources() {

}

SDL_Texture *Resources::GetImage( std::string file) {

    //Consultar tabela de imagem se a imagem já existe nela
    std::unordered_map<std::string, SDL_Texture *>::const_iterator imagemPedida = imageTable.find(file);

    if(imagemPedida != imageTable.end()){
        //Caso se encontre a imagem na tabela, retorna ela
        return imagemPedida->second; 
    }
    else{
        //Senão aloca uma nova textura
        SDL_Texture *novaTextura = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
        if(novaTextura == nullptr){
            std::cout << "Erro: " << SDL_GetError();
            std::cout << "Erro ao carregar Sprite\n";
        }
        //Adiciona na Tabela
        imageTable.insert(std::make_pair(file, novaTextura));
        //E retorna na função
        return novaTextura;
    }
}

void Resources::ClearImages() {
    for(auto& elementoTabela: imageTable) {
        SDL_DestroyTexture(elementoTabela.second);
        elementoTabela.second = nullptr;
    }
}

Mix_Music *Resources::GetMusic(std::string file) {

    std::unordered_map<std::string, Mix_Music *>::const_iterator musicaPedida = musicTable.find(file);

    if(musicaPedida != musicTable.end()) {
        return musicaPedida->second;
    }
    else {
        Mix_Music *novaMusica = Mix_LoadMUS(file.c_str());
        musicTable.insert(std::make_pair(file, novaMusica));
        return novaMusica;
    }
}

void Resources::ClearMusics() {
    for(auto& elementoTabela: musicTable) {
        Mix_FreeMusic(elementoTabela.second);
        elementoTabela.second = nullptr;
    }
}

Mix_Chunk *Resources::GetSound(std::string file) {
    std::unordered_map<std::string, Mix_Chunk *>::const_iterator somPedido = soundTable.find(file);

    if(somPedido != soundTable.end()) {
        return somPedido->second;
    }
    else {
        Mix_Chunk *novoSom = Mix_LoadWAV(file.c_str());
        soundTable.insert(std::make_pair(file, novoSom));
        return novoSom;
    }
}

void Resources::ClearSounds() {
    for(auto& elementoTabela: soundTable) {
        Mix_FreeChunk(elementoTabela.second);
        elementoTabela.second = nullptr;
    }
}