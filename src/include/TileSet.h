#ifndef TILESET_H_INCLUDED
#define TILESET_H_INCLUDED

#include "Sprite.h"
#include <string>

class TileSet {

    private:
        Sprite *tileSet;

        int rows;
        int colums;

        int tileWidth;
        int tileHeight;

    public:
        TileSet(int tilewidth, int tileHeigth, std::string file);
        ~TileSet();
        void RenderTile(unsigned index, float x, float y);
        int GetTileWidth();
        int GetTileHeight();

    protected:
        /* dado */
};

#endif //TILESET_H_INCLUDED