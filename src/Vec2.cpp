#include "include/Vec2.h"
#include <math.h>

Vec2::Vec2(float x, float y) {
    this->x = x;
    this->y = y;
}

Vec2::Vec2() {
    this->x = 0;
    this->y = 0;
}

Vec2 Vec2::GetRotated(float rad) {
    float posX = ((this->x * cos(rad)) - (this->y * sin(rad)));
    float posY = ((this->y * cos(rad)) - (this->x * sin(rad)));

    return Vec2(posX, posY);
}

Vec2 Vec2::operator+(Vec2 const &vetor) {
    Vec2 aux = Vec2(0,0);
    aux.x = this->x + vetor.x;
    aux.y = this->y + vetor.y;
    return aux;
}

Vec2 Vec2::operator-(Vec2 const &vetor) {
    Vec2 aux = Vec2(0,0);
    aux.x = this->x - vetor.x;
    aux.y = this->y - vetor.y;
    return aux;
}

Vec2 Vec2::operator*(float num) {
    Vec2 aux = Vec2(0,0);
    aux.x = this->x * num;
    aux.y = this->y * num;
    return aux;
}