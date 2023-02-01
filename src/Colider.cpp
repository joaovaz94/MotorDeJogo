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
#ifdef DEBUG
	Vec2 center( box.Center() );
	SDL_Point points[5];

	Vec2 point = Vec2::Rotate(Vec2(box.x, box.y) - center, associated.angleDeg /(180/M_PI) ) + center - Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = Vec2::Rotate(Vec2(box.x + box.w, box.y) - center,  associated.angleDeg/(180/M_PI) )+ center - Camera::pos;
	points[1] = {(int)point.x, (int)point.y};
	
	point = Vec2::Rotate(Vec2(box.x + box.w, box.y + box.h) - center, associated.angleDeg/(180/M_PI) )+ center - Camera::pos;
	points[2] = {(int)point.x, (int)point.y};
	
	point = Vec2::Rotate(Vec2(box.x, box.y + box.h) - center, associated.angleDeg/(180/M_PI) )+ center - Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
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