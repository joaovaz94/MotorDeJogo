#include "include/Rect.h"
#include <cmath>

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

Vec2 Rect::Posicao() {
    return Vec2(x,y);
}

Vec2 Rect::Center() {
    return Vec2((this->x + this->w)/2 , (this->y + this->h)/2 );
}


float Rect::DistanciaCentros(Rect retangulo) {
    Vec2 centro1 = this->Center();
    Vec2 centro2 = retangulo.Center();

    return ( sqrt(pow(centro1.x - centro2.x, 2) + pow(centro1.y + centro2.y, 2) )*1.0 );
}

void Rect::SetPosicao(float posX, float posY) {
    this->x = posX;
    this->y = posY;
}

void Rect::SetPosicao(Vec2 novaPos) {
    this->x = novaPos.x;
    this->y = novaPos.y;
}

void Rect::SetPosicaoCentro(float posCentroX, float posCentroY) {
    float posX = posCentroX - (this->w/2);
    float posY = posCentroY - (this->h/2);

    this->x = posX;
    this->y = posY;
}

void Rect::SetPosicaoCentro(Vec2 novaPos) {
    float posX = novaPos.x - (this->w/2);
    float posY = novaPos.y - (this->h/2);

    this->x = posX;
    this->y = posY;
}