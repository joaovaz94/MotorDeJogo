#include "include/TileSet.h"
#include <iostream>

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) {
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;

    GameObject *gameObject = new GameObject();
    this->tileSet = new Sprite(*gameObject, "assets/img/tileset.png"); 
    gameObject->AddComponent(this->tileSet);

    if(this->tileSet->IsOpen()) {
        this->rows = this->tileSet->GetHeigth() / tileHeight;
        this->colums = this->tileSet->GetWidth() / tileWidth;
    }
}

void TileSet::RenderTile(unsigned index, float x, float y) {

    if(index <= ((unsigned)(rows * colums)-1 )) {

        //Calculo de posição do Tile
        int posX = (index % colums) * tileWidth;
        int posY = (index / colums) * tileHeight;

        //Definição do Clip do Sprite
        tileSet->SetClip(posX, posY, tileWidth, tileHeight);

        //Renderizar o Tile na posição passada pela função
        tileSet->Render((int)x, (int)y, tileWidth, tileHeight);

    }
    else {
        std::cout << "ERRO!! Índice inexistente!" << std::endl;
    }
}

int TileSet::GetTileWidth() {
    return tileWidth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}