#include "include/Camera.h"
#include "include/Vec2.h"
#include <iostream>

GameObject *Camera::focus;
Vec2 Camera::pos;
Vec2 Camera::speed;

Camera::Camera() {

}

Camera::~Camera() {

}

void Camera::Follow(GameObject *newfocus) {
    focus = newfocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {

    InputManager &input = InputManager::GetInstance();

    speed = Vec2();

    if(focus != nullptr) {
        pos = focus->box.Center();
    }
    else {
        if(input.IsKeyDown(LEFT_ARROW_KEY ) || input.IsKeyDown(A_KEY)) {
            speed = speed + Vec2(-1, 0);
        }
        if(input.IsKeyDown(RIGHT_ARROW_KEY ) || input.IsKeyDown(D_KEY)) {

            speed = speed + Vec2(1, 0);
        }
        if(input.IsKeyDown(UP_ARROW_KEY ) || input.IsKeyDown(W_KEY)) {

            speed = speed + Vec2(0, -1);
        }
        if(input.IsKeyDown(DOWN_ARROW_KEY ) || input.IsKeyDown(S_KEY)) {

            speed = speed + Vec2(0, 1);
        }
        pos = pos + (speed * dt * 5) ;
    }
}