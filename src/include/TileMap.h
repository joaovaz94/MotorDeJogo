
#ifndef TILEMAP_H_INCLUDED
#define TILEMAP_H_INCLUDED

#include "GameObject.h"
#include "TileSet.h"
#include <string>

class TileMap : public Component {
    private:

        std::vector<int> tileMatrix;
        TileSet *tileset;
        
        int mapWidth;
        int mapHeight;
        int mapDepth;

    public:
    
        TileMap(GameObject &associated, std::string file, TileSet *tileset);
        ~TileMap();

        void Load(std::string file);
        void SetTileSet(TileSet* tileset);
        int& At(int x, int y, int z = 0);
        void Render();
        void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
        void Update(float dt);
        bool Is(std::string type);

        int GetWidth();
        int GetHeigth();
        int GetDepth();
};


#endif //TILEMAP_H_INCLUDED