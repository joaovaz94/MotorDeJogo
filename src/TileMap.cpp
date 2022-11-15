#include "include/TileMap.h"
#include <iostream>
#include <fstream>
#include <sstream>

TileMap::TileMap(GameObject &associated, std::string file, TileSet *tileset) : Component(associated) {
    Load(file);
    this->tileset = tileset;
}

TileMap::~TileMap() {

}

void TileMap::Load(std::string file) {
    std::ifstream ArquivoMap("./assets/map/tileMap.txt");

    if(ArquivoMap.is_open()) {

        std::stringstream conteudoArquivo;

        conteudoArquivo << ArquivoMap.rdbuf();
        std::string aux;

        //Pegando as informações do cabeçalho do Map
        getline(conteudoArquivo, aux, ',');
        mapWidth = stoi(aux);
        getline(conteudoArquivo, aux, ',');
        mapHeight = stoi(aux);
        getline(conteudoArquivo, aux, ',');
        mapDepth = stoi(aux);

        //Varrendo as celulas do Map para identificar cada tile
        for(int dep=0; dep < mapDepth; dep++) {
            std::getline(conteudoArquivo, aux, '\n');

            for(int til=0; til < (mapWidth * mapHeight); til++) {
                std::getline(conteudoArquivo, aux, ',');
                int tileAgora = stoi(aux) -1;
                tileMatrix.push_back(tileAgora);
            }

        }

    }
    else std::cout << "Não foi possível abrir o arquivo de Map!" << std::endl;
}

void TileMap::SetTileSet(TileSet *tileset) {
    this->tileset = tileset;
}

int& TileMap::At(int x, int y, int z){
    z = (z * mapWidth * mapHeight);
    y = y * mapWidth;
    return tileMatrix.at(x + y + z);
}

void TileMap::RenderLayer( int layer, int cameraX, int cameraY) {

    int tileHeigth = tileset->GetTileHeight();
    int tileWidth = tileset->GetTileWidth();

    for(int posY = 0; posY < this->GetHeigth(); posY++) {
        for(int posX=0; posX < this->GetWidth(); posX++) {
            int index = At(posX, posY, layer);
            int y = (posY - cameraY) * tileHeigth;
            int x = (posX - cameraX) * tileWidth;
            tileset->RenderTile(index, x, y);
        }
    }
}

void TileMap::Render() {
    for(int camada=0; camada < this->GetDepth(); camada++) {
        //Deixa para implementar camera depois
        this->RenderLayer(camada, associated.box.x, associated.box.y);
    }
}

void TileMap::Update(float dt) {

}

bool TileMap::Is(std::string type) {

    if(type == "TileMap") {
        return true;
    }
    else {
        return false;
    }
}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetHeigth() {
    return mapHeight;
}

int TileMap::GetDepth() {
    return mapDepth;
}