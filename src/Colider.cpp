#include "include/Collider.h"
#include "include/Camera.h"
#include "include/Game.h"
#include <math.h>

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset) : Component(associated) {
    this->scale = scale;
    this->offset = offset;
}

void Collider::Update(float dt) {
    this->box.w = associated.box.w * scale.x;
    this->box.h = associated.box.h * scale.y;
    this->box.SetPosicaoCentro(associated.box.Center() + offset);
    this->box = this->box + this->box.Center().RotateAroundVec(offset, associated.angleDeg * M_PI / 180);
}

void Collider::Render() {

}

bool Collider::Is(std::string type) {

    if(type == "Collider") {
        return true;
    }
    else {
        return false;
    }
}
 
 void Collider::SetScale(Vec2 scale) {
    this->scale = scale;
 }

 void Collider::SetOffset(Vec2 offset) {
    this->offset = offset;
 }