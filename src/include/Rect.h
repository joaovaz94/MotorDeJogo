#ifndef RECT_H_INCLUDED
#define RECT_H_INCLUDED
#include "Vec2.h"

class Rect
{
private:
    /* data */
public:
    Rect();
    Rect(float x, float y, float w, float h);
    ~Rect() {}

    float x;
    float y;
    float w;
    float h;

    Vec2 Posicao();
    Vec2 Center();
    Vec2 Medidas();
    bool Contains(Vec2 vetor);
    float DistanciaCentros(Rect retangulo);

    void SetPosicao(float posX, float posY);
    void SetPosicao(Vec2 novaPos);
    void SetPosicaoCentro(float posCentroX, float posCentroY);
    void SetPosicaoCentro(Vec2 NovaPos);

    Rect operator+(Vec2 const &vetor);
    Rect operator+=(Vec2 const &vetor);
};


#endif //RECT_H_INCLUDED