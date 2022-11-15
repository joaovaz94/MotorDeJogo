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

    Vec2 Center();
    bool Contains(Vec2 vetor);
    float DistanciaCentros(Rect retangulo);
};


#endif //RECT_H_INCLUDED