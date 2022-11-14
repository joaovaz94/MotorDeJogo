#include "include/Rect.h"

Rect::Rect() {
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
}

Rect::Rect(float x, float y, float w, float h) {

    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

bool Rect::Contains(Vec2 vetor) {
    bool vetorDentroX = ((vetor.x >= this->x) && (vetor.x <= (this->x + this->w)));
    bool vetorDentroY = ((vetor.y >= this->y) && (vetor.y <= (this->y + this->h)));

    if(vetorDentroX && vetorDentroY) {
        return true;
    }
    return false;
}