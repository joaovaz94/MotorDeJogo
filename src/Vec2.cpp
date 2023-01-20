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

std::string Vec2::toStr() {
    std::string aux = "";

    aux += "x: " + std::to_string(this->x);
    aux += " y: " + std::to_string(this->y);

    return aux;
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
    //Vec2 aux = Vec2(x,y);
    return Vec2(this->x / magnitude,this->y / magnitude);
}

float Vec2::DistanciaDoVetor(Vec2 &vetor) {
    Vec2 aux = Vec2(0,0);
    aux = *this - vetor;
    return aux.GetMagnitude();
}


float Vec2::AnguloParaAlvo(Vec2 &vetor) {
    
    //float dot = x * vetor.x + y *vetor.y;
    //float det = x * vetor.y + y * vetor.x;
    //return atan2(det, dot);
    Vec2 aux = vetor - *this; 
    return -atan2(aux.y, aux.x);
}

float Vec2::atan() {
    return atan2(y,x);
}

Vec2 Vec2::RotateAroundVec(Vec2 &vetor, float rad) {
    Vec2 aux = Vec2();
    aux.x = ((this->x -vetor.x) * cos(rad)) - ((vetor.y - this->y) * sin(rad)) + vetor.x;
    aux.y = vetor.y -((vetor.y - this->y) * cos(rad)) + ((this->x - vetor.x) * sin(rad));
    return aux;
}

Vec2 Vec2::operator+(Vec2 const &vetor) {
    Vec2 aux = Vec2(0,0);
    aux.x = this->x + vetor.x;
    aux.y = this->y + vetor.y;
    return aux;
}

Vec2 Vec2::operator+=(Vec2 const &vetor) {
    return *this + vetor;
}

Vec2 Vec2::operator-(Vec2 const &vetor) {
    Vec2 aux = Vec2(0,0);
    aux.x = this->x - vetor.x;
    aux.y = this->y - vetor.y;
    return aux;
}

Vec2 Vec2::operator-=(Vec2 const &vetor) {
    return *this - vetor;
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
