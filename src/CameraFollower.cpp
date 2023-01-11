#include "include/CameraFollower.h"
#include "include/Camera.h"

CameraFollower::CameraFollower(GameObject &go) : Component(go){
}

CameraFollower::~CameraFollower() {
}

void CameraFollower::Update(float dt) {
    //associated.box.x = Camera::pos.x;
    //associated.box.y = Camera::pos.y;
    associated.box.SetPosicao(Camera::pos);
}

void CameraFollower::Render() {

}

bool CameraFollower::Is( std::string type) {

    if(type == "CameraFollower") {
        return true;
    }
    else {
        return false;
    }
}