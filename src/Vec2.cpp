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

float Vec2::GetMagnitude() {
    return sqrt((x * x) + (y * y));
}

Vec2 Vec2::Normalize() {
    float magnitude = this->GetMagnitude();
    Vec2 aux = Vec2(x,y);
    return (aux / magnitude);
}

float Vec2::DistanciaDoVetor(Vec2 &vetor) {
    Vec2 aux = Vec2(0,0);
    aux = *this - vetor;
    return aux.GetMagnitude();
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

Vec2 Vec2::operator/(float num) {
    Vec2 aux = Vec2(0,0);
    aux.x = this->x / num;
    aux.y = this->y / num;
    return aux;
}

//Artigos de referência: 
//https://www.khanacademy.org/computing/computer-programming/programming-natural-simulations/programming-vectors/a/vector-magnitude-normalization
//https://www.khanacademy.org/computing/computer-programming/programming-natural-simulations/programming-vectors/a/more-vector-math
